#ifndef SEGMENT_BATTERY_ALARM_WIDGET_H
#define SEGMENT_BATTERY_ALARM_WIDGET_H

#include <QWidget>

#include "ElaFlowLayout.h"
#include "CellAlarmFrame.h"

class SegmentBatteryAlarmWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SegmentBatteryAlarmWidget(QWidget* parent = nullptr);
	~SegmentBatteryAlarmWidget();

	//void setTextSize(int size);
private:
	ElaFlowLayout* _mainLayout{ nullptr };
	QList<CellAlarmFrame*> _dataList;
};

#endif // !SEGMENT_BATTERY_ALARM_WIDGET_H