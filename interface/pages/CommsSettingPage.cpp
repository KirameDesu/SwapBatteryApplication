#include "CommsSettingPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ElaComboBox.h"
#include "ElaCheckBox.h"
#include "ElaText.h"
#include "ElaIconButton.h"
#include "ElaScrollPageArea.h"
#include "ElaPushButton.h"


CommsSettingPage::CommsSettingPage(QWidget* parent)
{
	setWindowTitle(tr("通讯设置"));
	this->setIsFixedSize(true);
	setWindowModality(Qt::ApplicationModal);
	setWindowButtonFlags(ElaAppBarType::CloseButtonHint);

	ElaScrollPageArea* protocolArea = new ElaScrollPageArea(this);
	QHBoxLayout* protocolLayout = new QHBoxLayout(protocolArea);
	ElaComboBox* protocolComboBox = new ElaComboBox(protocolArea);
	protocolComboBox->addItems({ tr("串口"), tr("TCP") });
	ElaText* textWidget = new ElaText("通讯方式", protocolArea);
	textWidget->setTextPixelSize(14);
	protocolLayout->addWidget(textWidget);
	protocolLayout->addStretch();
	protocolLayout->addWidget(protocolComboBox);

#if 0
	//多选框
	ElaText* portTitle = new ElaText("端口号", this);
	portTitle->setWordWrap(false);
	portTitle->setTextPixelSize(14);
	ElaComboBox* portComboBox = new ElaComboBox(this);
	ElaIconButton* refreshButton = new ElaIconButton(ElaIconType::Recycle, this);
	//---波特率复选框
	ElaText* baudTitle = new ElaText("波特率", this);
	baudTitle->setWordWrap(false);
	baudTitle->setTextPixelSize(14);
	ElaComboBox* baudComboBox = new ElaComboBox(this);
	baudComboBox->addItems(QStringList({ "9600", "19200", "38400", "57600", "115200"}));
	//---背景
	ElaScrollPageArea* settingArea = new ElaScrollPageArea(this);
	QHBoxLayout* portLayout = new QHBoxLayout(settingArea);
	portLayout->addWidget(portTitle);
	portLayout->addWidget(portComboBox);
	portLayout->addWidget(refreshButton);
	portLayout->addStretch();
	portLayout->addWidget(baudTitle);
	portLayout->addWidget(baudComboBox);
#else
	//通讯设置框
	_settingsWidget = new ElaScrollPageArea(this);
	_settingsWidget->setLayout(new QHBoxLayout());
#endif

	//按钮
	ElaPushButton* confirmButton = new ElaPushButton(tr("确定"), this);
	connect(confirmButton, &ElaPushButton::click, this, [=]() {
		emit confirm();
		});
	ElaPushButton* cancelButton = new ElaPushButton(tr("取消"), this);
	connect(cancelButton, &ElaPushButton::click, this, &CommsSettingPage::hide);
	QWidget* buttonWidget = new QWidget(this);
	QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
	buttonLayout->addWidget(confirmButton);
	buttonLayout->addWidget(cancelButton);

	QVBoxLayout* centerLayout = new QVBoxLayout(this);
	//centerLayout->setContentsMargins(20, 10, 20, 10);
	centerLayout->addWidget(protocolArea);
	centerLayout->addSpacing(20);
	centerLayout->addWidget(_settingsWidget);
	centerLayout->addStretch();
	centerLayout->addWidget(buttonWidget);
}

CommsSettingPage::~CommsSettingPage()
{
}

QWidget* CommsSettingPage::getSettingsWidget()
{
	return _settingsWidget;
}
