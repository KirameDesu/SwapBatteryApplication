#include "SegmentBatteryAlarmWidget.h"

#include "ElaText.h"

SegmentBatteryAlarmWidget::SegmentBatteryAlarmWidget(QWidget* parent)
{
	_mainLayout = new ElaFlowLayout(this, 0, 5, 5);
#if defined(TEST_MODE)
	_mainLayout->addWidget(new ElaText("电池报警: ", TEXT_SIZE, this));
#else
	_mainLayout->addWidget(new ElaText("电池报警: 未定义", TEXT_SIZE, this));
#endif
	_mainLayout->setIsAnimation(true);
	_mainLayout->setSpacing(100);

	for (auto& c : _dataList)
	{
		_mainLayout->addWidget(c);
	}
	this->setFixedHeight(100);
}

SegmentBatteryAlarmWidget::~SegmentBatteryAlarmWidget()
{
}

void SegmentBatteryAlarmWidget::setModel(BaseModel* model)
{
	ModelData* protModel = nullptr;
	ModelData* faultModel = nullptr;
	qint16 u16Val = 0;
	
	static qint16 cnt = 0;

	protModel = model->findModelDataFromTitle("保护状态");
	faultModel = model->findModelDataFromTitle("故障状态");
	
	if (protModel && faultModel)
	{
		if (protModel->isUpdated || faultModel->isUpdated)
		{
			// 移除现有的
			while (!_dataList.isEmpty())
			{
				CellAlarmFrame* f = _dataList.takeFirst();
				_mainLayout->removeWidget(f);
				// 释放内存
				delete(f);
				f = nullptr;
			}
			//u16Val = protModel->val.toUInt();
			u16Val = cnt;
			for (int i = 0; i < 16; ++i) {
				// 通过位运算检查每一位
				if ((u16Val >> i) & 0x01)
				{
					_dataList.append(new CellAlarmFrame(QString("保护状态%1").arg(i), AlarmColor::origin, this));
				}
			}
			//u16Val = faultModel->val.toUInt();
			u16Val = cnt;
			for (int i = 0; i < 16; ++i) {
				// 通过位运算检查每一位
				if ((u16Val >> i) & 0x01)
				{
					_dataList.append(new CellAlarmFrame(QString("故障状态%1").arg(i), AlarmColor::red, this));
				}
			}
			if (_dataList.isEmpty())
			{
				_normalText = new ElaText("正常", TEXT_SIZE, this);
				_mainLayout->addWidget(_normalText);
			}
			else
			{
				if (_normalText)
				{
					_mainLayout->removeWidget(_normalText);
					delete _normalText;
					_normalText = nullptr;
				}
				for (auto& c : _dataList)
				{
					_mainLayout->addWidget(c);
				}
			}
			
			//protModel->isUpdated = false;
			//faultModel->isUpdated = false;
			cnt++;
		}
	}
}