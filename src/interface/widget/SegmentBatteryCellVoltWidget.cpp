#include "SegmentBatteryCellVoltWidget.h"


SegmentBatteryCellVoltWidget::SegmentBatteryCellVoltWidget(QWidget* parent)
{
	_mainLayout = new QVBoxLayout(this);

	// 单体概况
	QWidget* cellVoltOverviewWidget = new QWidget(this);
	QHBoxLayout* cellVoltOverviewLayout = new QHBoxLayout(cellVoltOverviewWidget);
	ElaText* maxCellVoltTitleText = new ElaText("最高电压: ", 16, cellVoltOverviewWidget);
	int maxCellVolt = 3460;
	ElaText* maxCellVoltValText = new ElaText(QString::number(maxCellVolt), 16, cellVoltOverviewWidget);
	ElaText* minCellVoltTitleText = new ElaText("最低电压: ", 16, cellVoltOverviewWidget);
	int minCellVolt = 3240;
	ElaText* minCellVoltValText = new ElaText(QString::number(minCellVolt), 16, cellVoltOverviewWidget);
	ElaText* avgCellVoltTitleText = new ElaText("平均电压: ", 16, cellVoltOverviewWidget);
	ElaText* avgCellVoltValText = new ElaText(QString::number((minCellVolt + maxCellVolt) / 2), 16, cellVoltOverviewWidget);
	ElaText* diffCellVoltTitleText = new ElaText("电压压差: ", 16, cellVoltOverviewWidget);
	ElaText* diffCellVoltValText = new ElaText(QString::number(maxCellVolt - minCellVolt), 16, cellVoltOverviewWidget);
	cellVoltOverviewLayout->addWidget(maxCellVoltTitleText);
	cellVoltOverviewLayout->addWidget(maxCellVoltValText);
	cellVoltOverviewLayout->addWidget(minCellVoltTitleText);
	cellVoltOverviewLayout->addWidget(minCellVoltValText);
	cellVoltOverviewLayout->addWidget(avgCellVoltTitleText);
	cellVoltOverviewLayout->addWidget(avgCellVoltValText);
	cellVoltOverviewLayout->addWidget(diffCellVoltTitleText);
	cellVoltOverviewLayout->addWidget(diffCellVoltValText);

	// 单体
	QWidget* cellVoltWidget = new QWidget(this);
	int volt = 3400;
	for (int i = 0; i < MAX_CELL_NUM; ++i)
		_dataList.append(new CellVoltFrame(i + 1, volt, cellVoltWidget));
	ElaFlowLayout* cellVoltLayout = new ElaFlowLayout(cellVoltWidget, 0, 5, 5);
	cellVoltLayout->setIsAnimation(true);
	cellVoltLayout->setSpacing(140);

	for (auto& c : _dataList)
	{
		cellVoltLayout->addWidget(c);
	}

	_mainLayout->addWidget(cellVoltOverviewWidget);
	_mainLayout->addSpacing(30);
	_mainLayout->addWidget(cellVoltWidget);
	//_mainLayout->addLayout(cellVoltLayout);
}

SegmentBatteryCellVoltWidget::~SegmentBatteryCellVoltWidget()
{
}

void SegmentBatteryCellVoltWidget::setCellDisplayNum(int num)
{
	_cellNum = num;
	for (int i = num; i < MAX_CELL_NUM; ++i)
	{
		_dataList.at(i)->hide();
	}
}
