#ifndef SEGMENT_BATTERY_CELL_VOLT_WIDGET_H
#define SEGMENT_BATTERY_CELL_VOLT_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>

#include "ElaFlowLayout.h"

#include "CellVoltFrame.h"
#include "BaseModel.h"

class SegmentBatteryCellVoltWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SegmentBatteryCellVoltWidget(QWidget* parent = nullptr);
	~SegmentBatteryCellVoltWidget();
	
	void setCellDisplayNum(int num);
	
	void setModel(BaseModel* model);
private:
	QVBoxLayout* _mainLayout{ nullptr };
	QList<CellVoltFrame*> _cellVoltList;

	int _cellNum = 16;
	ElaText* maxCellVoltValText{ nullptr };
	ElaText* minCellVoltValText{ nullptr };
	ElaText* avgCellVoltValText{ nullptr };
	ElaText* diffCellVoltValText{ nullptr };

	const static int MAX_CELL_NUM = 24;
};

#endif // !SEGMENT_BATTERY_CELL_VOLT_WIDGET_H
