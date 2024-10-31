#include "SerialSetting.h"

#include <QHBoxLayout>
#include <QWidget>

#include "ElaText.h"
#include "ElaComboBox.h"
#include "ElaIconButton.h"
#include "ElaScrollPageArea.h"
#include "ElaIconButton.h"


SerialSetting::SerialSetting(AbstractCommsSetting* parenet)
{
}

SerialSetting::~SerialSetting()
{
}

CommunicationType SerialSetting::getCommsType() const
{
	return CommunicationType::Serial;
}

void SerialSetting::applyWidget(QWidget* w)
{
	QLayout* l = w->layout();
	if (l)
	{
		while (QLayoutItem* item = l->takeAt(0)) {  // 循环直到没有控件
			QWidget* widget = item->widget();  // 获取QWidget
			if (widget) {
				widget->deleteLater();  // 安全删除QWidget
			}
			delete item;  // 删除布局项
		}
	}

	//QWidget* tw = new QWidget();
	//QWidget* tw = w;

	//多选框
	ElaText* portTitle = new ElaText("端口号", w);
	portTitle->setWordWrap(false);
	portTitle->setTextPixelSize(14);
	ElaComboBox* portComboBox = new ElaComboBox(w);
	ElaIconButton* refreshButton = new ElaIconButton(ElaIconType::Recycle, w);
	//---波特率复选框
	ElaText* baudTitle = new ElaText("波特率", w);
	baudTitle->setWordWrap(false);
	baudTitle->setTextPixelSize(14);
	ElaComboBox* baudComboBox = new ElaComboBox(w);
	baudComboBox->addItems(QStringList({ "9600", "19200", "38400", "57600", "115200" }));
	//---背景
	ElaScrollPageArea* settingArea = new ElaScrollPageArea(w);
	QHBoxLayout* portLayout = new QHBoxLayout(settingArea);
	portLayout->addWidget(portTitle);
	portLayout->addWidget(portComboBox);
	portLayout->addWidget(refreshButton);
	portLayout->addStretch();
	portLayout->addWidget(baudTitle);
	portLayout->addWidget(baudComboBox);

	l->addWidget(settingArea);
}

void SerialSetting::apply()
{
	// 返回widget上的设置项
}
