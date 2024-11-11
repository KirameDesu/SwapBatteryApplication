#ifndef SEGMENT_BATTERY_CELL_VOLT_WIDGET_H
#define SEGMENT_BATTERY_CELL_VOLT_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "ElaFlowLayout.h"

#include "CellVoltFrame.h"


class SegmentBatteryCellVoltWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SegmentBatteryCellVoltWidget(QWidget* parent = nullptr);
	~SegmentBatteryCellVoltWidget();
	
	void setCellDisplayNum(int num);
private:
	QVBoxLayout* _mainLayout{ nullptr };
	QList<CellVoltFrame*> _dataList;

	int _cellNum = 16;

	const static int MAX_CELL_NUM = 32;
};

#endif // !SEGMENT_BATTERY_CELL_VOLT_WIDGET_H
