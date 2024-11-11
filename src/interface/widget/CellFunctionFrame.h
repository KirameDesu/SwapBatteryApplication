#ifndef CELL_FUNCTION_FRAME_H
#define CELL_FUNCTION_FRAME_H

#include <QWidget>
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
		_value = new ElaRadioButton(this);
		layout->addWidget(_value);
		layout->addStretch();
	};
	~CellFunctionFrame() = default;

	void setTitleTextSize(int size) {
		_title->setTextPixelSize(size);
	};

private:
	ElaText* _title{ nullptr };
	QWidget* _value{ nullptr };
};

#endif // !CELL_DATA_FRAME_H
