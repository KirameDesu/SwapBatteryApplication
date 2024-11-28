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
	//Q_SLOT void updateView();

	void setModel(BaseModel* model);
private:
	ElaFlowLayout* _mainLayout{ nullptr };
	QList<CellDataFrame<float>*> _showingDataList;

	CellDataFrame<float>* SOC;
	CellDataFrame<float>* SOH;
	CellDataFrame<float>* cellPackVolt;
	CellDataFrame<float>* cellPackCurr;
	CellDataFrame<float>* remainCap;
	CellDataFrame<float>* fullCap;
	CellDataFrame<float>* designCap;
	CellDataFrame<float>* cycle;
	CellDataFrame<float>* mosTemp;
	CellDataFrame<float>* envTemp;

	//CellDataFrame<float>* cellTempNum;		// 电芯温度数量
	//QList<CellDataFrame<float>*> cellTempList;

	CellDataFrame<float>* maxVolt;
	CellDataFrame<float>* minVolt;
	CellDataFrame<float>* avgVolt;

	CellDataFrame<float>* cellNum;			// 电芯数量
	QList<CellDataFrame<float>*> _cellTempList;
};

#endif // !BATTERY_OVERVIEW_WIDGET_H
