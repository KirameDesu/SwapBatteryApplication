#ifndef SEGMENT_BATTERY_OVERVIEW_WIDGET_H
#define SEGMENT_BATTERY_OVERVIEW_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QList>

#include "ElaFlowLayout.h"

#include "CellDataFrame.h"
#include "BaseModel.h"


class SegmentBatteryOverviewWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SegmentBatteryOverviewWidget(QWidget* parent = nullptr);
	~SegmentBatteryOverviewWidget();

	void setTextSize(int size);
	Q_SLOT void updateView();
private:
	ElaFlowLayout* _mainLayout{ nullptr };
	QList<CellDataFrame<float>*> _dataList;

	CellDataFrame<float>* cellPackVolt;
	CellDataFrame<float>* cellPackCurr;
	CellDataFrame<float>* SOH;
	CellDataFrame<float>* remainCap;
	CellDataFrame<float>* fullCap;
	CellDataFrame<float>* designCap;
	CellDataFrame<float>* cycle;
	CellDataFrame<float>* mosTemp;
	CellDataFrame<float>* envTemp;
	CellDataFrame<float>* cellTemp1;
	CellDataFrame<float>* cellTemp2;
	CellDataFrame<float>* cellTemp3;
	CellDataFrame<float>* cellTemp4;
};

#endif // !BATTERY_OVERVIEW_WIDGET_H
