#ifndef CELL_DATA_FRAME_H
#define CELL_DATA_FRAME_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMetaType>
#include <QVariant>
#include <QString>
#include <QPainter>

#include "ElaText.h"

enum DisplayStyle
{
	DisplayByHorizon = 0,
	DisplayByVertical
};

class UnsupportedTypeException : public std::runtime_error {
public:
	UnsupportedTypeException(const std::string& message)
		: std::runtime_error(message) {}
};

class RectWidget : public QWidget
{
public:
	explicit RectWidget(QWidget* parent = nullptr) : QWidget(parent) {}

protected:
	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		QRect rect(0, 0, width(), height());  // 使用父控件的尺寸绘制矩形
		painter.setBrush(QColor(45, 183, 255));  // 设置颜色
		painter.setPen(Qt::NoPen);  // 去除边框
		painter.drawRoundedRect(rect, 4, 4);  // 绘制圆角矩形
	}
};

template <typename T>
class CellDataFrame : public QWidget
{
public:
	CellDataFrame(QString title, QString unitStr, QChar separator = ':', DisplayStyle style = DisplayByHorizon, QWidget* parent = nullptr) {
		_style = style;
		_separator = separator;
		_valSize = 1;
		// 矩形装饰
		QWidget* rectWidget = new RectWidget(this);
		rectWidget->setFixedWidth(10);
		switch (_style)
		{
		case DisplayByHorizon:
		case DisplayByVertical:
			QHBoxLayout* layout = new QHBoxLayout(this);
			layout->addWidget(rectWidget);
			layout->addSpacing(10);
			_title = new ElaText(title + _separator, this);	
			layout->addWidget(_title);
			layout->addStretch();
			_value = new ElaText("--", this);
			_value->setFixedWidth(70);
			layout->addWidget(_value);
			if (!unitStr.isEmpty())
			{
				_unit = new ElaText(unitStr, this);
				layout->addWidget(_unit);
			}
		}
		rectWidget->update();
	};
	CellDataFrame(QString title, QString unitStr, int valSize, const QList<QString>& regNameList, QChar separator = ':', DisplayStyle style = DisplayByHorizon, QWidget* parent = nullptr) {
		_style = style;
		_separator = separator;
		_valSize = valSize;
		_regNameList = regNameList;
		// 矩形装饰
		QWidget* rectWidget = new RectWidget(this);
		rectWidget->setFixedWidth(10);
		switch (_style)
		{
		case DisplayByHorizon:
		case DisplayByVertical:
			QHBoxLayout* layout = new QHBoxLayout(this);
			layout->addWidget(rectWidget);
			layout->addSpacing(10);
			_title = new ElaText(title + _separator, this);
			layout->addWidget(_title);
			layout->addStretch();
			_value = new ElaText("--", this);
			_value->setFixedWidth(70);
			layout->addWidget(_value);
			if (!unitStr.isEmpty())
			{
				_unit = new ElaText(unitStr, this);
				layout->addWidget(_unit);
			}
		}
		rectWidget->update();
	};
	CellDataFrame(QString title, const T& value, QString unitStr = "", QChar separator = ':', DisplayStyle style = DisplayByHorizon, QWidget* parent = nullptr) {
		_style = style;
		_separator = separator;
		// 矩形装饰
		QWidget* rectWidget = new RectWidget(this);
		rectWidget->setFixedWidth(10);
		switch (_style)
		{
		case DisplayByHorizon:
		case DisplayByVertical:
			QHBoxLayout* layout = new QHBoxLayout(this);
			layout->addWidget(rectWidget);
			layout->addSpacing(10);
			_title = new ElaText(title + _separator, this);
			layout->addWidget(_title);
			// 检查类型是否受 QVariant 支持
			QVariant variant = QVariant::fromValue(value);
			if (variant.isValid()) {
				if (variant.canConvert<float>() || variant.canConvert<double>())
				{
					double number = variant.toDouble();
					_value = new ElaText(QString::number(number, 'f', 2), this); // 显示小数点后三位
				}
				else
				{
					_value = new ElaText(variant.toString(), this);
				}
				layout->addStretch();
				layout->addWidget(_value);
			}
			else {
				throw UnsupportedTypeException("The provided type is not supported for QVariant conversion.");
			}
			if (!unitStr.isEmpty())
			{
				_unit = new ElaText(unitStr, this);
				layout->addWidget(_unit);
			}
		}
		rectWidget->update();
	};
	~CellDataFrame() {};

	void setTitleTextSize(int size) {
		if (_title)
			_title->setTextPixelSize(size);
	};
	void setValueTextSize(int size) {
		if (_value)
			_value->setTextPixelSize(size);
		if (_unit)
			_unit->setTextPixelSize(size);
	};
	// 设置值
	void setCurrentText(const QString& text) {
		_value->setText(text);
	}
	// 获取标题
	QString getTitleString() {
		return _title->text().remove(_separator);
	}
	// 获取标题
	const QList<QString>& getRegisterNameList() const{
		return _regNameList;
	}
	// 获取字节大小
	int getSize() {
		return _valSize;
	};

private:
	ElaText* _title{ nullptr };
	ElaText* _value{ nullptr };
	ElaText* _unit{ nullptr };
	QChar _separator;

	int _valSize;		// 字节大小
	QList<QString> _regNameList;		// 对应寄存器名称列表

	DisplayStyle _style;
};

#endif // !CELL_DATA_FRAME_H
