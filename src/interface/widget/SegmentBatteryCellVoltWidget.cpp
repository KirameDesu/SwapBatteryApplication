#include "SegmentBatteryCellVoltWidget.h"


SegmentBatteryCellVoltWidget::SegmentBatteryCellVoltWidget(QWidget* parent)
{
	_mainLayout = new QVBoxLayout(this);

	// 单体概况
	QWidget* cellVoltOverviewWidget = new QWidget(this);
	QHBoxLayout* cellVoltOverviewLayout = new QHBoxLayout(cellVoltOverviewWidget);
	ElaText* maxCellVoltTitleText = new ElaText("最高电压: ", 16, cellVoltOverviewWidget);
	maxCellVoltValText = new ElaText("--", 16, cellVoltOverviewWidget);
	ElaText* minCellVoltTitleText = new ElaText("最低电压: ", 16, cellVoltOverviewWidget);
	minCellVoltValText = new ElaText("--", 16, cellVoltOverviewWidget);
	ElaText* avgCellVoltTitleText = new ElaText("平均电压: ", 16, cellVoltOverviewWidget);
	avgCellVoltValText = new ElaText("--", 16, cellVoltOverviewWidget);
	ElaText* diffCellVoltTitleText = new ElaText("电压压差: ", 16, cellVoltOverviewWidget);
	diffCellVoltValText = new ElaText("--", 16, cellVoltOverviewWidget);
	cellVoltOverviewLayout->addWidget(maxCellVoltTitleText);
	cellVoltOverviewLayout->addWidget(maxCellVoltValText);
	cellVoltOverviewLayout->addSpacing(50);
	cellVoltOverviewLayout->addWidget(minCellVoltTitleText);
	cellVoltOverviewLayout->addWidget(minCellVoltValText);
	cellVoltOverviewLayout->addSpacing(50);
	cellVoltOverviewLayout->addWidget(avgCellVoltTitleText);
	cellVoltOverviewLayout->addWidget(avgCellVoltValText);
	cellVoltOverviewLayout->addSpacing(50);
	cellVoltOverviewLayout->addWidget(diffCellVoltTitleText);
	cellVoltOverviewLayout->addWidget(diffCellVoltValText);
	cellVoltOverviewLayout->addStretch();

	// 单体
	QWidget* cellVoltWidget = new QWidget(this);
	for (int i = 0; i < MAX_CELL_NUM; ++i)
		_cellVoltList.append(new CellVoltFrame(i + 1, 0, cellVoltWidget));
	ElaFlowLayout* cellVoltLayout = new ElaFlowLayout(cellVoltWidget, 0, 5, 5);
	cellVoltLayout->setIsAnimation(true);
	cellVoltLayout->setSpacing(140);

	for (auto& c : _cellVoltList)
	{
		cellVoltLayout->addWidget(c);
	}

	_mainLayout->addWidget(cellVoltOverviewWidget);
	_mainLayout->addSpacing(20);
	_mainLayout->addWidget(cellVoltWidget);
	//_mainLayout->addLayout(cellVoltLayout);
}

SegmentBatteryCellVoltWidget::~SegmentBatteryCellVoltWidget()
{
}

void SegmentBatteryCellVoltWidget::setCellDisplayNum(int num)
{
	_cellNum = num;
	for (auto& c : _cellVoltList)
		c->setVisible(true);
	for (int i = num; i < MAX_CELL_NUM; ++i)
	{
		_cellVoltList.at(i)->hide();
	}
}

void SegmentBatteryCellVoltWidget::setModel(BaseModel* model)
{
	ModelData* m = model->findModelDataFromTitle("最大电芯电压");
	int maxVolt = m->val.toInt();
	if (m->isUpdated)
	{
		maxVolt = m->val.toInt();
		maxCellVoltValText->setText(m->val.toString());
		m->isUpdated = false;
	}
	m = model->findModelDataFromTitle("最小电芯电压");
	int minVolt = m->val.toInt();
	if (m->isUpdated)
	{
		minVolt = m->val.toInt();
		minCellVoltValText->setText(m->val.toString());
		m->isUpdated = false;
	}
	m = model->findModelDataFromTitle("平均电芯电压");
	if (m->isUpdated)
	{
		avgCellVoltValText->setText(m->val.toString());
		diffCellVoltValText->setText(QString::number(maxVolt - minVolt));
		m->isUpdated = false;
	}

	m = model->findModelDataFromTitle("电芯数量");
	int cellNum = m->val.toInt();
	if (m->isUpdated)
	{
		setCellDisplayNum(cellNum);
		m->isUpdated = false;
	}
	for (int i = 0; i < cellNum; ++i)
	{
		m = model->findModelDataFromTitle(QString("电芯电压%1").arg(i + 1));
		if (m->isUpdated)
		{
			_cellVoltList.at(i)->setVolt(m->val.toInt());
			m->isUpdated = false;
		}
	}
}
