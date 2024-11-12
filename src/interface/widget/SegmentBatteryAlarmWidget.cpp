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
