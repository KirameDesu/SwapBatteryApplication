#include "BMSUpdatePage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

#include "ElaPushButton.h"
#include "ElaToggleButton.h"
#include "ElaScrollPageArea.h"
#include "ElaMessageBar.h"

#include "LoggerManager.h"


BMSUpdatePage::BMSUpdatePage(QWidget* parent)
	: _percentage(0), BasePage(parent)
{
	// 预览窗口标题
	setWindowTitle("BMSUpdate");
	setTitleVisible(false);
	setContentsMargins(2, 2, 0, 0);

	// 标题
	ElaText* titleText = new ElaText("BMS固件升级", this);
	titleText->setTextPixelSize(26);
	ElaPushButton* selectPathBtn = new ElaPushButton("选择文件", this);
	connect(selectPathBtn, &ElaPushButton::clicked, this, &BMSUpdatePage::_browseFile);
	_updateBtn = new ElaPushButton("升级", this);
	connect(_updateBtn, &ElaPushButton::clicked, this, &BMSUpdatePage::_upgradeProcess);
	_updateBtn->setEnabled(false);
	connect(_updateBtn, &ElaPushButton::clicked, this, [=](bool sw) {
			LoggerManager::logWithTime("开始升级");
	});
	QHBoxLayout* titleLayout = new QHBoxLayout(this);
	titleLayout->addWidget(titleText);
	titleLayout->addStretch();
	titleLayout->addWidget(selectPathBtn);
	titleLayout->addWidget(_updateBtn);

	// 协议选择
	ElaScrollPageArea* protArea = new ElaScrollPageArea(this);
	protArea->setContentsMargins(18, 0, 18, 0);
	_protComboBox = new ElaComboBox(this);
	_protComboBox->addItems({"Default", "Controller"});
	// 默认Controller协议
	_protComboBox->setCurrentText("Controller");
	//IAPVerText->setPlaceholderText("请选择升级文件");
	//IAPVerText->setReadOnly(true);
	//IAPVerText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QHBoxLayout* protLayout = new QHBoxLayout(protArea);
	protLayout->addWidget(new ElaText("升级协议", 18, this));
	protLayout->addStretch();
	protLayout->addWidget(_protComboBox);

	// IAP版本
	ElaScrollPageArea* IAPVerArea = new ElaScrollPageArea(this);
	IAPVerArea->setContentsMargins(18, 0, 18, 0);
	_IAPVerText = new ElaText("", 18, this);
	_IAPVerText->setWordWrap(false);
	//IAPVerText->setPlaceholderText("请选择升级文件");
	//IAPVerText->setReadOnly(true);
	//IAPVerText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QHBoxLayout* IAPVerLayout = new QHBoxLayout(IAPVerArea);
	IAPVerLayout->addWidget(new ElaText("IAP版本:", 18, this));
	IAPVerLayout->addStretch();
	IAPVerLayout->addWidget(_IAPVerText);

	// 文件选择
	ElaScrollPageArea* pathArea = new ElaScrollPageArea(this);
	pathArea->setContentsMargins(18, 0, 18, 0);
	ElaText* pathTitle = new ElaText("文件路径:", 18, this);
	_filePathText = new ElaText("--", 18, this);
	_filePathText->setWordWrap(false);
	//pathTextEdit->setPlaceholderText("请选择升级文件");
	//pathTextEdit->setReadOnly(true);
	//pathTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	//pathTextEdit->setFixedHeight(selectPathBtn->sizeHint().height() + 10);
	QHBoxLayout* pathLayout = new QHBoxLayout(pathArea);
	pathLayout->addWidget(pathTitle);
	pathLayout->addStretch();
	pathLayout->addWidget(_filePathText);

	// 进度条
	ElaText* progressTitle = new ElaText("升级进度", 20, this);
	//ElaText* progressDetail = new ElaText("120/400", 20, this);
	QHBoxLayout* progressTitleLayout = new QHBoxLayout(this);
	progressTitleLayout->addWidget(progressTitle);
	progressTitleLayout->addStretch();
	//progressTitleLayout->addWidget(progressDetail);
	_updateProgressBar = new ElaProgressBar(this);
	_updateProgressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	_updateProgressBar->setMinimum(0);
	_updateProgressBar->setMaximum(100);
	_updateProgressBar->setFixedHeight(50);
	QVBoxLayout* progressLayout = new QVBoxLayout(this);
	progressLayout->addWidget(_updateProgressBar);

	QWidget* centralWidget = new QWidget(this);
	centralWidget->setContentsMargins(30, 30, 30, 30);
	QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
	centerVLayout->addLayout(titleLayout);
	centerVLayout->addSpacing(30);
	centerVLayout->addWidget(protArea);
	centerVLayout->addSpacing(5);
	centerVLayout->addWidget(IAPVerArea);
	centerVLayout->addSpacing(5);
	centerVLayout->addWidget(pathArea);
	centerVLayout->addSpacing(120);
	centerVLayout->addLayout(progressTitleLayout);
	centerVLayout->addSpacing(5);
	centerVLayout->addWidget(_updateProgressBar);
	centerVLayout->addStretch();
	addCentralWidget(centralWidget);
}

BMSUpdatePage::~BMSUpdatePage()
{
}

void BMSUpdatePage::setIAPVer(const QString& ver)
{
	_IAPVerText->setText(ver);
}

void BMSUpdatePage::setFilePath(const QString& path)
{
	_filePathText->setText(path);
}

void BMSUpdatePage::setPercentage(int p)
{
	_updateProgressBar->setValue(p);
}

void BMSUpdatePage::_browseFile()
{
	// 打开文件选择对话框
	QString selectedPath = QFileDialog::getOpenFileName(this, "选择升级文件", "", "Binary Files (*.bin)");

	if (!selectedPath.isEmpty()) {
		// 如果选择了路径，则保存到变量 path 中
		_filePath = selectedPath;
		// 显示路径
		_filePathText->setText(_filePath);
		LoggerManager::logWithTime("UPGRADE FILE: " + _filePath);
		
		_updateBtn->setEnabled(true);
	}
	else {
		// 用户取消了选择
		ElaMessageBar::error(ElaMessageBarType::BottomRight, "Error", "升级文件无效!", 2000);
	}
}

void BMSUpdatePage::_upgradeProcess() {
	// 创建升级实例
	_upgrade = UpgradeFactory::createUpgrade(_protComboBox->currentText());
	if (!_upgrade)
	{
		ElaMessageBar::error(ElaMessageBarType::BottomRight, "Error", "升级指针为空!", 2000);
	}

	_upgrade->setFilePath(_filePath);
}