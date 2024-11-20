#include "SettingsPage.h"

#include "ElaPushButton.h"
#include "ElaScrollArea.h"

#include "RDManager.h"

SettingsPage::SettingsPage(QWidget* parent)
	: BasePage(nullptr)
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

	// 逻辑行为初始化
	// 初始化定时获取报文
	//BasePage::setTimedMessageSending(_registerList);
	//BasePage::setTimerStatus(false);
}

SettingsPage::~SettingsPage()
{
	// 释放设置框架内存
	if (!_settingList.isEmpty()) {
		for (auto c : _settingList)
			delete c;
	}
	// 释放寄存器类内存
	//if (!_registerList.isEmpty()) {
	//	for (auto c : _registerList)
	//		delete c;
	//}
}

void SettingsPage::setSettings(SETTINGS_CLASS settings)
{
	QList<RegisterData*> regList;
	for (const auto& c : settings) {
		CellSettingFrame* cell = new CellSettingFrame(this);
		QList<BaseSetting*> cellList;
		for (const auto& i : c.setList) {
			// 取出Setting类
			BaseSetting* baseSet = new BaseSetting(i);
			cellList.append(baseSet);
			// 创建寄存器子类
			RegisterData* regData = new RegisterData(c.regStart, i);
			regData->setDispalyWidget(baseSet->getWidget());
			regList.append(regData);
		}
		cell->addSettingList(c.title, cellList);
		_settingList.append(cell);
		
		// 基类列表赋值
		_DataGroupNameList.insert(c.title);
		// 设置寄存器列表
		REGISTERS_GROUP pr;
		pr.first = c.title;
		pr.second = regList;
		//_registerList.append(pr);
		RDManager::instance().addRegisterGroup(pr);
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

void SettingsPage::showEvent(QShowEvent* event)
{
	BasePage::showEvent(event);

	// 连接定时器与槽
	connect(BasePage::_timer, &QTimer::timeout, this, &SettingsPage::readDataTiming);
}

void SettingsPage::hideEvent(QHideEvent* event)
{
	BasePage::hideEvent(event);

	// 断开定时器与槽
	disconnect(BasePage::_timer, &QTimer::timeout, this, &SettingsPage::readDataTiming);
}

