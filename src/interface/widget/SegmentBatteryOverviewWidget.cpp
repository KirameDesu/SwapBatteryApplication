#include "SegmentBatteryOverviewWidget.h"

#include <QGridLayout>

SegmentBatteryOverviewWidget::SegmentBatteryOverviewWidget(QWidget* parent)
	: QWidget(parent)
{
	float T_PackVolt = 56.312;
	CellDataFrame<float>* cellPackVolt = new CellDataFrame<float>("总电压", T_PackVolt, "V");
	_dataList.append(cellPackVolt);
	float T_PackCurr = 1.21;
	CellDataFrame<float>* cellPackCurr = new CellDataFrame<float>("总电流", T_PackCurr, "A");
	_dataList.append(cellPackCurr);
	float T_remainCap = 100.00;
	CellDataFrame<float>* remainCap = new CellDataFrame<float>("剩余容量", T_remainCap, "AH");
	_dataList.append(remainCap);
	float T_fullCap = 100.00;
	CellDataFrame<float>* fullCap = new CellDataFrame<float>("充满容量", T_fullCap, "AH");
	_dataList.append(fullCap);
	float T_designCap = 100.00;
	CellDataFrame<float>* designCap = new CellDataFrame<float>("设计容量", T_designCap, "AH");
	_dataList.append(designCap);
	float T_temp = 24.10;
	_dataList.append(new CellDataFrame<float>("循环次数", T_temp, "℃"));
	_dataList.append(new CellDataFrame<float>("MOS温度", T_temp, "℃"));
	_dataList.append(new CellDataFrame<float>("环境温度", T_temp, "℃"));
	_dataList.append(new CellDataFrame<float>("电芯温度1", T_temp, "℃"));
	_dataList.append(new CellDataFrame<float>("电芯温度2", T_temp, "℃"));
	_dataList.append(new CellDataFrame<float>("电芯温度3", T_temp, "℃"));
	_dataList.append(new CellDataFrame<float>("电芯温度4", T_temp, "℃"));

	// 填充栅格布局
	_mainLayout = new ElaFlowLayout(this, 0, 5, 5);
	_mainLayout->setIsAnimation(true);
	_mainLayout->setSpacing(100);
	//_mainLayout->addWidget(cellPackVolt);
	//_mainLayout->addWidget(cellPackCurr);
	//_mainLayout->addWidget(remainCap);
	//_mainLayout->addWidget(fullCap);
	//_mainLayout->addWidget(designCap);
	for (auto& c : _dataList)
		_mainLayout->addWidget(c);

	this->setLayout(_mainLayout);
}


SegmentBatteryOverviewWidget::~SegmentBatteryOverviewWidget()
{
}

void SegmentBatteryOverviewWidget::setTextSize(int size)
{
	for (auto& c : _dataList)
	{	
		if (c)
		{
			c->setTitleTextSize(size);
			c->setValueTextSize(size);
		}
	}
}
