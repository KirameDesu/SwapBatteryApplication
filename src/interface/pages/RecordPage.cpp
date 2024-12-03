#include "RecordPage.h"

#include <QFont>
#include <QHeaderView>
#include <QHBoxLayout>

#include "ElaText.h"
#include "ElaToggleButton.h"

#include "ModelManager.h"
#include "TableViewModel.h"

RecordPage::RecordPage(QWidget* parent)
    : BasePage(parent)
{
    setWindowTitle("监控记录");
    setTitleVisible(false);

	QWidget* mainWidget = new QWidget(this);
    _mainLayout = new QVBoxLayout(mainWidget);

    ElaToggleButton* recordSwitch = new ElaToggleButton("记录", this);
    connect(recordSwitch, &ElaToggleButton::toggled, this, [=](bool checked) {
        if (checked) {
            connect(BasePage::_timer, &QTimer::timeout, this, &RecordPage::onRecordStartTimeout);
            _isStart = true;
        }
        else {
            disconnect(BasePage::_timer, &QTimer::timeout, this, &RecordPage::onRecordStartTimeout);
            _isStart = false;
        }
    });
    QHBoxLayout* topLayout = new QHBoxLayout(this);
    topLayout->addStretch();
    topLayout->addWidget(recordSwitch);

    _tableView = new ElaTableView(this);
    QFont tableHeaderFont = _tableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(16);
    _tableView->horizontalHeader()->setFont(tableHeaderFont);
    _tableModel = new TableViewModel(this);
    BatteryOverviewModel* model = ModelManager::getBatteryOverviewModel();
    if (model)
    {
        connect(model, &BatteryOverviewModel::AFEDataChanged, this, [=]() {
            if (_isStart)
                _tableModel->insertOneData(model);
        });
    }
    _tableView->setModel(_tableModel);
    _tableView->setAlternatingRowColors(true);
    _tableView->setIconSize(QSize(38, 38));
    _tableView->verticalHeader()->setHidden(true);
    _tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _tableView->horizontalHeader()->setMinimumSectionSize(60);
    _tableView->verticalHeader()->setMinimumSectionSize(46);
    _tableView->setFixedHeight(600);
    connect(_tableView, &ElaTableView::tableViewShow, this, [=]() {
        _tableView->setColumnWidth(1, 220);
    });
	_mainLayout->addLayout(topLayout);
	_mainLayout->addWidget(_tableView);
    _mainLayout->addStretch();

	addCentralWidget(mainWidget);
}

RecordPage::~RecordPage()
{
}

void RecordPage::onRecordStartTimeout()
{
    emit fetchOneRecord();
}
