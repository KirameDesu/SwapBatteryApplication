#include "SegmentBatteryOverviewWidget.h"

#include <QGridLayout>

#include "ModelManager.h"

#include "LoggerManager.h"

SegmentBatteryOverviewWidget::SegmentBatteryOverviewWidget(QWidget* parent)
	: QWidget(parent)
{
	cellPackVolt = new CellDataFrame<float>("总电压", "V");
	_dataList.append(cellPackVolt);
	cellPackCurr = new CellDataFrame<float>("平均电流1", "A");
	_dataList.append(cellPackCurr);
#if 0
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
#endif
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
		// 更新对应标题项的值
		QString key = _dataList.at(i)->getTitleString();
		// 去掉最后一个字符
		try {
			ModelData m = model->findModelDataFromTitle(key);
			_dataList.at(i)->setCurrentText(m.val.toString());
		} catch (std::runtime_error e) {
			// 未找到对于数据项
			LoggerManager::logWithTime(QString("%1: %2").arg(__FUNCTION__).arg(e.what()));
		}
	}
}
