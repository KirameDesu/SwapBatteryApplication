#ifndef SEGMENT_BATTERY_FUNCTION_WIDGET_H
#define SEGMENT_BATTERY_FUNCTION_WIDGET_H

#include <QWidget>

#include "ElaFlowLayout.h"

#include "CellFunctionFrame.h"

class SegmentBatteryFunctionWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SegmentBatteryFunctionWidget(QWidget* parent = nullptr);
	~SegmentBatteryFunctionWidget();

	void setTextSize(int size);
	QLayout* getLayout();
private:
	ElaFlowLayout* _mainLayout{ nullptr };
	QList<CellFunctionFrame*> _dataList;
};

#endif // !SEGMENT_BATTERY_FUNCTION_WIDGET_H
