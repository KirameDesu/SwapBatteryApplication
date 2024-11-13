#include "SettingsPage.h"

#include "ElaPushButton.h"

SettingsPage::SettingsPage(QWidget* parent)
{
	_mainLayout = new QGridLayout(this);
	QHBoxLayout* titleLayout = new QHBoxLayout();
	titleLayout->addStretch();
	titleLayout->addWidget(new ElaPushButton("写入", this));
	_mainLayout->addLayout(titleLayout, 0, 0, 1, MAX_COLUMN);
	_mainLayout->setContentsMargins(30, 30, 30, 30);
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
