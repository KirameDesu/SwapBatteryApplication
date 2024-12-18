#ifndef CELL_VOLT_FRAME
#define CELL_VOLT_FRAME

#include <QWidget>
#include <QGridLayout>

#include "ElaText.h"
#include "ElaProgressBar.h"

class CellVoltFrame : public QWidget
{
	//Q_OBJECT
public:
	CellVoltFrame(int index, int volt, QWidget* parent = nullptr)
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
		_voltVal = new ElaText(QString::number(volt), this);
		_voltVal->setTextPixelSize(14);
		layout->addWidget(title, 0, 0);
		layout->addWidget(_voltVal, 0, 1);
		layout->addWidget(_bar, 1, 0, 1, 2);
	};
	~CellVoltFrame() = default;

	void setVolt(int volt)
	{
		_volt = volt;
		_voltVal->setText(QString::number(volt));
		if (_bar)
			_bar->setValue(volt);
	}
private:
	int _index;	// 电芯序号
	int _volt; // 电芯电压
	ElaProgressBar* _bar{ nullptr };
	ElaText* _voltVal{ nullptr };
};

#endif // !CELL_VOLT_FRAME
