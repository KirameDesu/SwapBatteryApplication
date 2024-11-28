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
	//QList<QPair<QString, ModelData>> list = model->getSettings();
	//for (int i = 0; i < _showingDataList.size() && i < list.size(); ++i)
	//{
	//	// 更新对应标题项的值
	//	QString key = _showingDataList.at(i)->getTitleString();
	//	// 去掉最后一个字符
	//	try {
	//		ModelData m = model->findModelDataFromTitle(key);
	//		_dataList.at(i)->setCurrentText(m.val.toString());
	//	}
	//	catch (std::runtime_error e) {
	//		// 未找到对于数据项
	//		LoggerManager::logWithTime(QString("%1: %2").arg(__FUNCTION__).arg(e.what()));
	//	}
	//}
}