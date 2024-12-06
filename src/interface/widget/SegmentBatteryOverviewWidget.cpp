#include "SegmentBatteryOverviewWidget.h"

#include <QGridLayout>

#include "LoggerManager.h"

SegmentBatteryOverviewWidget::SegmentBatteryOverviewWidget(QWidget* parent)
	: QWidget(parent)
{
	cellPackVolt = new CellDataFrame<float>("电池电压", "V");
	_showingDataList.append(cellPackVolt);
	QList<QString> l = { "实时电流1", "实时电流2" };
	cellPackCurr = new CellDataFrame<float>("电流", "A", 2, l);
	_showingDataList.append(cellPackCurr);
#if 0
	SOH = new CellDataFrame<float>("SOH", "%");
	_dataList.append(SOH);
	remainCap = new CellDataFrame<float>("剩余容量", "AH");
	_dataList.append(remainCap);
	fullCap = new CellDataFrame<float>("充满容量", "AH");
	_dataList.append(fullCap);
	designCap = new CellDataFrame<float>("设计容量", "AH");
	_dataList.append(designCap);
	cycle = new CellDataFrame<float>("循环次数");
	_dataList.append(cycle);
#endif
	mosTemp = new CellDataFrame<float>("MOS温度", "℃");
	_showingDataList.append(mosTemp);
	envTemp = new CellDataFrame<float>("环境温度", "℃");
	_showingDataList.append(envTemp);
	CellDataFrame<float>* cellTemp1 = new CellDataFrame<float>("电芯温度1", "℃");
	_cellTempList.append(cellTemp1);
	CellDataFrame<float>* cellTemp2 = new CellDataFrame<float>("电芯温度2", "℃");
	_cellTempList.append(cellTemp2);
	CellDataFrame<float>* cellTemp3 = new CellDataFrame<float>("电芯温度3", "℃");
	_cellTempList.append(cellTemp3);
	CellDataFrame<float>* cellTemp4 = new CellDataFrame<float>("电芯温度4", "℃");
	_cellTempList.append(cellTemp4);

	// 填充栅格布局
	_mainLayout = new ElaFlowLayout(this, 0, 5, 5);
	_mainLayout->setIsAnimation(true);
	_mainLayout->setSpacing(100);

	for (auto& c : _showingDataList)
		_mainLayout->addWidget(c);

	for (auto& c : _cellTempList)
		_mainLayout->addWidget(c);

	this->setLayout(_mainLayout);
	this->setFixedHeight(100);
}


SegmentBatteryOverviewWidget::~SegmentBatteryOverviewWidget()
{
}

void SegmentBatteryOverviewWidget::setTextSize(int size)
{
	for (auto& c : _showingDataList)
	{	
		if (c)
		{
			c->setTitleTextSize(size);
			c->setValueTextSize(size);
		}
	}
	for (auto& c : _cellTempList)
	{
		if (c)
		{
			c->setTitleTextSize(size);
			c->setValueTextSize(size);
		}
	}
}

void SegmentBatteryOverviewWidget::setModel(BaseModel* model)
{
	ModelData* m = nullptr;

	QList<QPair<QString, ModelData>> list = model->getSettings();
	for (int i = 0; i < _showingDataList.size() && i < list.size(); ++i)
	{
		CellDataFrame<float>* cellData = _showingDataList.at(i);
		if (cellData->getSize() == 1)
		{
			// 更新对应标题项的值
			QString key = cellData->getTitleString();
			// 去掉最后一个字符
			try {
				m = model->findModelDataFromTitle(key);
				if (m->isUpdated)
				{
					if (key == "电池电压")
					{
						float f = (m->val.toInt()) / 100.00;
						cellData->setCurrentText(QString::number(f, 'f', 2));
					}
					else if (key == "MOS温度")
					{
						float f = (m->val.toInt() - 2730) / 10.0;
						cellData->setCurrentText(QString::number(f, 'f', 1));
					}
					else
						cellData->setCurrentText(m->val.toString());
					m->isUpdated = false;
				}
			}
			catch (std::runtime_error e) {
				// 未找到对于数据项
				LoggerManager::logWithTime(QString("%1: %2").arg(__FUNCTION__).arg(e.what()));
			}
		}
		else if (cellData->getSize() == 2)
		{
			ModelData* m1 = nullptr;
			ModelData* m2 = nullptr;
			// 更新对应标题项的值
			QList<QString> l = cellData->getRegisterNameList();
			QString reg1 = l.at(0);
			QString reg2 = l.at(1);

			// 去掉最后一个字符
			try {
				m1 = model->findModelDataFromTitle(reg1);
				m2 = model->findModelDataFromTitle(reg2);
				uint32_t combined = (static_cast<uint32_t>(m2->val.toUInt()) << 16) | static_cast<uint32_t>(m1->val.toUInt());
				if (m1->isUpdated || m2->isUpdated)
				{
					if (cellData->getTitleString() == "电流")
					{
						float* f = reinterpret_cast<float*>(&combined);
						float val = *f / 100.0;
						cellData->setCurrentText(QString::number(val, 'f', 2));
					}
					else
					{
						cellData->setCurrentText(QString::number(combined, 'f', 2));
					}
					m1->isUpdated = false;
					m2->isUpdated = false;
				}
			}
			catch (std::runtime_error e) {
				// 未找到对于数据项
				LoggerManager::logWithTime(QString("%1: %2").arg(__FUNCTION__).arg(e.what()));
			}
		}
	}
	// 电芯温度特殊处理
	m = model->findModelDataFromTitle("温度采集点数量");
	int tempNum = m->val.toInt();
	if (m->isUpdated)
	{
		// 移除现有
		for (auto& c : _cellTempList)
		{
			c->setVisible(false);
		}
		for (int i = 0; i < tempNum; ++i)
		{
			_cellTempList.at(i)->setVisible(true);
		}
		m->isUpdated = false;
	}
	for (int i = 0; i < tempNum; ++i)
	{
		m = model->findModelDataFromTitle(QString("电芯温度%1").arg(i + 1));
		if (m->isUpdated)
		{
			float f = (m->val.toInt() - 2730) / 10.0;
			_cellTempList.at(i)->setCurrentText(QString::number(f, 'f', 1));
			m->isUpdated = false;
		}
	}
}

/*
void SegmentBatteryOverviewWidget::updateView()
{
	BatteryOverviewModel* model = ModelManager::getBatteryOverviewModel();

	QList<QPair<QString, ModelData>> list = model->getSettings();
	for (int i = 0; i < _dataList.size() && i < list.size(); ++i)
	{
		// 更新对应标题项的值
		QString key = _dataList.at(i)->getTitleString();
		// 去掉最后一个字符
		try {
			ModelData m = model->findModelDataFromTitle(key);
			_dataList.at(i)->setCurrentText(m.val.toString());
		} catch (std::runtime_error e) {
			// 未找到对于数据项
			LoggerManager::logWithTime(QString("%1: %2").arg(__FUNCTION__).arg(e.what()));
		}
	}
}
*/