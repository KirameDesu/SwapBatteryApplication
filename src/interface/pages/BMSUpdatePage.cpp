#include "BMSUpdatePage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaPushButton.h"
#include "ElaToggleButton.h"
#include "ElaScrollPageArea.h"

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
	ElaPushButton* updateBtn = new ElaPushButton("升级", this);
	updateBtn->setEnabled(false);
	connect(updateBtn, &ElaPushButton::clicked, this, [=](bool sw) {
			LoggerManager::log("开始升级");
	});
	QHBoxLayout* titleLayout = new QHBoxLayout(this);
	titleLayout->addWidget(titleText);
	titleLayout->addStretch();
	titleLayout->addWidget(selectPathBtn);
	titleLayout->addWidget(updateBtn);

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
	_filePathText = new ElaText("", 18, this);
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
