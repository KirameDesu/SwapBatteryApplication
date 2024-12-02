#ifndef CELL_FUNCTION_FRAME_H
#define CELL_FUNCTION_FRAME_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "ElaText.h"
#include "ElaRadioButton.h"

class CellFunctionFrame : public QWidget
{
	Q_OBJECT
public:
	CellFunctionFrame(QString title, QWidget* parent = nullptr) {
		QHBoxLayout* layout = new QHBoxLayout(this);
		_title = new ElaText(title, this);
		layout->addWidget(_title);
		_value = new QLabel(this);
		//_value->setFixedSize(30, 30);
		layout->addWidget(_value);
		layout->addStretch();

		setStatus(false);
	};
	~CellFunctionFrame() = default;

	void setTitleTextSize(int size) {
		_title->setTextPixelSize(size);
	};

	void setStatus(bool status) {
		if (status) {
			_value->setPixmap(QPixmap(":/src/image/func_on.png").scaled(25, 25));
		}
		else {
			_value->setPixmap(QPixmap(":/src/image/func_off.png").scaled(25, 25));
		}
	};
private:
	ElaText* _title{ nullptr };
	QLabel* _value{ nullptr };
};

#endif // !CELL_DATA_FRAME_H
