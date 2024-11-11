#include "SegmentBatteryFunctionWidget.h"

#include "ElaPlainTextEdit.h"
#include "qnamespace.h"

SegmentBatteryFunctionWidget::SegmentBatteryFunctionWidget(QWidget* parent)
{
	_dataList.append(new CellFunctionFrame("充电MOS", this));
	_dataList.append(new CellFunctionFrame("放电MOS", this));
	_dataList.append(new CellFunctionFrame("充电器插入", this));
	_dataList.append(new CellFunctionFrame("负载", this));
	_dataList.append(new CellFunctionFrame("充电限流", this));
	_dataList.append(new CellFunctionFrame("预放", this));
	_dataList.append(new CellFunctionFrame("充满", this));
	_dataList.append(new CellFunctionFrame("加热", this));
	_dataList.append(new CellFunctionFrame("测试模式", this));

	_mainLayout = new ElaFlowLayout(this, 0, 5, 5);
	_mainLayout->setIsAnimation(true);
	_mainLayout->setSpacing(140);
	for (const auto& c : _dataList)
	{
		_mainLayout->addWidget(c);
	}
	this->setLayout(_mainLayout);
}

SegmentBatteryFunctionWidget::~SegmentBatteryFunctionWidget()
{
}

void SegmentBatteryFunctionWidget::setTextSize(int size)
{
	for (auto& c : _dataList)
	{
		c->setTitleTextSize(size);
	}
}

QLayout* SegmentBatteryFunctionWidget::getLayout()
{
	return _mainLayout;
}
