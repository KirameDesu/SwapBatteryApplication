#include "SegmentBatteryAlarmWidget.h"

#include "ElaText.h"

SegmentBatteryAlarmWidget::SegmentBatteryAlarmWidget(QWidget* parent)
{
	_mainLayout = new ElaFlowLayout(this, 0, 5, 5);
	_mainLayout->addWidget(new ElaText("电池报警: ", 20, this));
	
	_dataList.append(new CellAlarmFrame("单体过压", AlarmColor::red, this));
	_dataList.append(new CellAlarmFrame("单体过流", AlarmColor::origin, this));
	_dataList.append(new CellAlarmFrame("低电量", AlarmColor::yellow, this));

	_mainLayout->setIsAnimation(true);
	_mainLayout->setSpacing(100);
	for (auto& c : _dataList)
	{
		_mainLayout->addWidget(c);
		c->setFixedSize(110, 50);
	}
}

SegmentBatteryAlarmWidget::~SegmentBatteryAlarmWidget()
{
}

void SegmentBatteryAlarmWidget::setModel(BaseModel* model)
{
	//QList<QPair<QString, ModelData>> list = model->getSettings();
	//for (int i = 0; i < _dataList.size() && i < list.size(); ++i)
	//{
	//	// 更新对应标题项的值
	//	QString key = _dataList.at(i)->getTitleString();
	//	// 去掉最后一个字符
	//	try {
	//		ModelData m = model->findModelDataFromTitle(key);
	//		_dataList.at(i)->setCurrentText(m.val.toString());
	//	}
	//	catch (std::runtime_error e) {
	//		// 未找到对于数据项
	//		LoggerManager::logWithTime(QString("%1: %2").arg(__FUNCTION__).arg(e.what()));
	//	}
	//}
}