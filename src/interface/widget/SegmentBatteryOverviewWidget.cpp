#include "SegmentBatteryOverviewWidget.h"

#include <QGridLayout>

#include "ModelManager.h"

SegmentBatteryOverviewWidget::SegmentBatteryOverviewWidget(QWidget* parent)
	: QWidget(parent)
{
	cellPackVolt = new CellDataFrame<float>("总电压", "V");
	_dataList.append(cellPackVolt);
	cellPackCurr = new CellDataFrame<float>("总电流", "A");
	_dataList.append(cellPackCurr);
	SOH = new CellDataFrame<float>("SOH", "%");
	_dataList.append(SOH);
	remainCap = new CellDataFrame<float>("剩余容量", "AH");
	_dataList.append(remainCap);
	fullCap = new CellDataFrame<float>("充满容量", "AH");
	_dataList.append(fullCap);
	designCap = new CellDataFrame<float>("设计容量", "AH");
	_dataList.append(designCap);
	cycle = new CellDataFrame<float>("循环次数");
	_dataList.append(cycle);
	mosTemp = new CellDataFrame<float>("MOS温度", "℃");
	_dataList.append(mosTemp);
	envTemp = new CellDataFrame<float>("环境温度", "℃");
	_dataList.append(envTemp);
	cellTemp1 = new CellDataFrame<float>("电芯温度1", "℃");
	_dataList.append(cellTemp1);
	cellTemp2 = new CellDataFrame<float>("电芯温度2", "℃");
	_dataList.append(cellTemp2);
	cellTemp3 = new CellDataFrame<float>("电芯温度3", "℃");
	_dataList.append(cellTemp3);
	cellTemp4 = new CellDataFrame<float>("电芯温度4", "℃");
	_dataList.append(cellTemp4);

	// 填充栅格布局
	_mainLayout = new ElaFlowLayout(this, 0, 5, 5);
	_mainLayout->setIsAnimation(true);
	_mainLayout->setSpacing(100);

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

void SegmentBatteryOverviewWidget::updateView()
{
	BatteryOverviewModel* model = ModelManager::getBatteryOverviewModel();

	QList<QPair<QString, ModelData>> list = model->getSettings();
	for (int i = 0; i < _dataList.size() && i < list.size(); ++i)
	{
		QVariant var = list.at(i).second.val;
		_dataList.at(i)->setCurrentText(var.toString());
	}
}
