#include "ProductSettingPage.h"

#include <QHBoxLayout>

#include "ElaText.h"
#include "ElaScrollPageArea.h"
#include "ElaLineEdit.h"
#include "ElaPushButton.h"

ProductSettingPage::ProductSettingPage(QWidget* parent)
	: BasePage(parent)
{
	setWindowTitle("ProductSetting");
	setTitleVisible(false);
	setContentsMargins(2, 2, 0, 0);

	ElaText* title = new ElaText("生产参数设置", 28, this);

	// BMS序列号读取写入
	ElaScrollPageArea* bmsSNArea = new ElaScrollPageArea(this);
	bmsSNArea->setContentsMargins(20, 0, 20, 0);
	QHBoxLayout* bmsSNLayout = new QHBoxLayout(bmsSNArea);
	ElaText* bmsSNTitle = new ElaText("BMS序列号: ", 16, bmsSNArea);
	bmsSNTitle->setFixedWidth(110);
	bmsSNTitle->setWordWrap(false);
	bmsSNLayout->addWidget(bmsSNTitle);
	bmsSNLayout->addSpacing(30);
	ElaLineEdit* bmsSNLineEdit = new ElaLineEdit(bmsSNArea);
	bmsSNLineEdit->setFixedHeight(35);
	bmsSNLayout->addWidget(bmsSNLineEdit);
	bmsSNLayout->addWidget(new ElaPushButton("读", bmsSNArea));
	bmsSNLayout->addWidget(new ElaPushButton("写", bmsSNArea));

	// PACK序列号读取写入
	ElaScrollPageArea* packSNArea = new ElaScrollPageArea(this);
	packSNArea->setContentsMargins(20, 0, 20, 0);
	QHBoxLayout* packSNLayout = new QHBoxLayout(packSNArea);
	ElaText* packSNTitle = new ElaText("PACK序列号: ", 16, packSNArea);
	packSNTitle->setFixedWidth(110);
	packSNTitle->setWordWrap(false);
	packSNLayout->addWidget(packSNTitle);
	packSNLayout->addSpacing(30);
	ElaLineEdit* packSNAreaLineEdit = new ElaLineEdit(packSNArea);
	packSNAreaLineEdit->setFixedHeight(35);
	packSNLayout->addWidget(packSNAreaLineEdit);
	packSNLayout->addWidget(new ElaPushButton("读", packSNArea));
	packSNLayout->addWidget(new ElaPushButton("写", packSNArea));

	// 软件版本读取写入
	ElaScrollPageArea* softwareVersionArea = new ElaScrollPageArea(this);
	softwareVersionArea->setContentsMargins(20, 0, 20, 0);
	QHBoxLayout* softwareVersionLayout = new QHBoxLayout(softwareVersionArea);
	ElaText* softwareVersionTitle = new ElaText("软件版本: ", 16, softwareVersionArea);
	softwareVersionTitle->setFixedWidth(110);
	softwareVersionTitle->setWordWrap(false);
	softwareVersionLayout->addWidget(softwareVersionTitle);
	softwareVersionLayout->addSpacing(30);
	ElaLineEdit* softwareVersionLineEdit = new ElaLineEdit(softwareVersionArea);
	softwareVersionLineEdit->setFixedHeight(35);
	softwareVersionLayout->addWidget(softwareVersionLineEdit);
	softwareVersionLayout->addWidget(new ElaPushButton("读", softwareVersionArea));
	softwareVersionLayout->addWidget(new ElaPushButton("写", softwareVersionArea));

	QWidget* mainWidget = new QWidget(this);
	mainWidget->setContentsMargins(30, 30, 30, 30);
	_mainLayout = new QVBoxLayout(mainWidget);
	_mainLayout->addWidget(title);
	_mainLayout->addSpacing(30);
	_mainLayout->addWidget(bmsSNArea);
	_mainLayout->addWidget(packSNArea);
	_mainLayout->addWidget(softwareVersionArea);
	_mainLayout->addWidget(softwareVersionArea);
	_mainLayout->addStretch();

	addCentralWidget(mainWidget);
}

ProductSettingPage::~ProductSettingPage()
{
}
