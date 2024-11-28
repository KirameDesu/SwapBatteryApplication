#ifndef SEGMENT_BATTERY_FUNCTION_WIDGET_H
#define SEGMENT_BATTERY_FUNCTION_WIDGET_H

#include <QWidget>

#include "ElaFlowLayout.h"

#include "CellFunctionFrame.h"
#include "BaseModel.h"

class SegmentBatteryFunctionWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SegmentBatteryFunctionWidget(QWidget* parent = nullptr);
	~SegmentBatteryFunctionWidget();

	void setTextSize(int size);
	QLayout* getLayout();

	void setModel(BaseModel* model);
private:
	ElaFlowLayout* _mainLayout{ nullptr };
	QList<CellFunctionFrame*> _showingDataList;
};

#endif // !SEGMENT_BATTERY_FUNCTION_WIDGET_H
