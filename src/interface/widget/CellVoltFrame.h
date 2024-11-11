#ifndef CELL_VOLT_FRAME
#define CELL_VOLT_FRAME

#include <QWidget>
#include <QGridLayout>

#include "ElaText.h"
#include "ElaProgressBar.h"

class CellVoltFrame : public QWidget
{
	Q_OBJECT
public:
	CellVoltFrame(int index, int& volt, QWidget* parent = nullptr)
		: _index(index), _volt(volt)
	{
		QGridLayout* layout = new QGridLayout(this);

		_bar = new ElaProgressBar(this);
		_bar->setMinimum(0);
		_bar->setMaximum(5000);
		_bar->setValue(volt);
		_bar->setTextVisible(false);
		
		ElaText* title = new ElaText("cell" + QString::number(index), this);
		title->setTextPixelSize(14);
		ElaText* voltVal = new ElaText(QString::number(volt), this);
		voltVal->setTextPixelSize(14);
		layout->addWidget(title, 0, 0);
		layout->addWidget(voltVal, 0, 1);
		layout->addWidget(_bar, 1, 0, 1, 2);
	};
	~CellVoltFrame() = default;

private:
	int _index;	// µÁ–æ–Ú∫≈
	int& _volt; // µÁ–æµÁ—π
	ElaProgressBar* _bar{ nullptr };
};

#endif // !CELL_VOLT_FRAME
