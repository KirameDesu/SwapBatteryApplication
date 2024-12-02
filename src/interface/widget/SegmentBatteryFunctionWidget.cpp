#include "SegmentBatteryFunctionWidget.h"

#include "ElaPlainTextEdit.h"
#include "qnamespace.h"

SegmentBatteryFunctionWidget::SegmentBatteryFunctionWidget(QWidget* parent)
{
	_showingDataList.append(new CellFunctionFrame("充电MOS", this));
	_showingDataList.append(new CellFunctionFrame("放电MOS", this));
	_showingDataList.append(new CellFunctionFrame("充电器插入", this));
	_showingDataList.append(new CellFunctionFrame("负载", this));
	_showingDataList.append(new CellFunctionFrame("充电限流", this));
	_showingDataList.append(new CellFunctionFrame("预放", this));
	_showingDataList.append(new CellFunctionFrame("充满", this));
	_showingDataList.append(new CellFunctionFrame("加热", this));
	_showingDataList.append(new CellFunctionFrame("测试模式", this));

	_mainLayout = new ElaFlowLayout(this, 0, 5, 5);
	_mainLayout->setIsAnimation(true);
	_mainLayout->setSpacing(140);
	for (const auto& c : _showingDataList)
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
	for (auto& c : _showingDataList)
	{
		c->setTitleTextSize(size);
	}
}

QLayout* SegmentBatteryFunctionWidget::getLayout()
{
	return _mainLayout;
}

void SegmentBatteryFunctionWidget::setModel(BaseModel* model)
{
	ModelData* m = model->findModelDataFromTitle("系统功能状态");

	static qint16 cnt = 0;	// 测试用

	if (m->isUpdated)
	{
		//qint16 u16Val = m->val.toUInt();
		qint16 u16Val = cnt;
		//for (int i = 0; i < 16; ++i)
		for (int i = 0; i < 9; ++i)
		{
			if ((u16Val >> i) & 0x01)
			{
				// 对应功能指示灯亮
				_showingDataList.at(i)->setStatus(true);
			}
			else
			{
				_showingDataList.at(i)->setStatus(false);
			}
		}
		cnt++;
		if (cnt == 0x0200)
			cnt = 0;
		//m->isUpdated = false;
	}
}