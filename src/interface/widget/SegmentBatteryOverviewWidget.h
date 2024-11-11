﻿#ifndef SEGMENT_BATTERY_OVERVIEW_WIDGET_H
#define SEGMENT_BATTERY_OVERVIEW_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QList>

#include "ElaFlowLayout.h"

#include "CellDataFrame.h"


class SegmentBatteryOverviewWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SegmentBatteryOverviewWidget(QWidget* parent = nullptr);
	~SegmentBatteryOverviewWidget();

	void setTextSize(int size);
private:
	ElaFlowLayout* _mainLayout{ nullptr };
	QList<CellDataFrame<float>*> _dataList;
};

#endif // !BATTERY_OVERVIEW_WIDGET_H