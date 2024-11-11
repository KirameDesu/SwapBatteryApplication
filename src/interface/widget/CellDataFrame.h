#ifndef CELL_DATA_FRAME_H
#define CELL_DATA_FRAME_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMetaType>
#include <QVariant>
#include <QString>

#include "ElaText.h"


//using INT_CellDataFrame = CellDataFrame<int>;
//using FLOAT_CellDataFrame = CellDataFrame<float>;
//using Double_CellDataFrame = CellDataFrame<double>;

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

template <typename T>
class CellDataFrame : public QWidget
{
public:
	CellDataFrame(QString title, const T& value, QString unitStr = "", QChar separator = ':', DisplayStyle style = DisplayByHorizon, QWidget* parent = nullptr) {
		_style = style;
		_separator = separator;
		switch (_style)
		{
		case DisplayByHorizon:
		case DisplayByVertical:
			QHBoxLayout* layout = new QHBoxLayout(this);
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
	};
	~CellDataFrame() = default;

	void setTitleTextSize(int size) {
		_title->setTextPixelSize(size);
	};
	void setValueTextSize(int size) {
		_title->setTextPixelSize(size);
		_unit->setTextPixelSize(size);
	};

private:
	ElaText* _title{ nullptr };
	ElaText* _value{ nullptr };
	ElaText* _unit{ nullptr };
	QChar _separator;

	DisplayStyle _style;
};

#endif // !CELL_DATA_FRAME_H
