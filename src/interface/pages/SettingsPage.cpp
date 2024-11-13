#include "SettingsPage.h"

#include "ElaPushButton.h"
#include "ElaScrollArea.h"

SettingsPage::SettingsPage(QWidget* parent)
{
	setWindowTitle("Home");
	setTitleVisible(false);
	setContentsMargins(2, 2, 0, 0);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

	QWidget* mainArea = new QWidget(this);
	mainArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	_mainLayout = new QGridLayout();
	QVBoxLayout* outerLayout = new QVBoxLayout(mainArea);
	QHBoxLayout* titleLayout = new QHBoxLayout();
	titleLayout->addStretch();
	ElaPushButton* writeBtn = new ElaPushButton("写入", this);
	writeBtn->setFixedSize(90, 45);
	titleLayout->addWidget(writeBtn);
	_mainLayout->addLayout(titleLayout, 0, 0, 1, MAX_COLUMN);
	_mainLayout->setContentsMargins(30, 30, 30, 30);

	outerLayout->addLayout(_mainLayout);
	outerLayout->addStretch();
	addCentralWidget(mainArea);
}

SettingsPage::~SettingsPage()
{
}

void SettingsPage::setSettings(SETTINGS_TYPE settings)
{
	for (const auto& c : settings) {
		CellSettingFrame* cell = new CellSettingFrame(this);
		QList<BaseSetting*> cellList;
		for (const auto& i : c.second) {
			// 取出Setting类
			cellList.append(new BaseSetting(i));
		}
		cell->addSettingList(c.first, cellList);
		_settingList.append(cell);
	}
	// 设置控件
	auto frame = _settingList.begin();
	for (int i = 1; i < MAX_ROW && frame != _settingList.end(); ++i) {
		for (int j = 0; j < MAX_COLUMN && frame != _settingList.end(); ++j) {
			_mainLayout->addWidget(*frame, i, j);
			++frame;
		}
	}
}
