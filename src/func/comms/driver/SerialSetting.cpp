﻿#include "SerialSetting.h"

#include <stdexcept>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/qserialportinfo.h>

#include "ElaText.h"
#include "ElaComboBox.h"
#include "ElaIconButton.h"
#include "ElaScrollPageArea.h"
#include "ElaIconButton.h"
#include "ElaMessageBar.h"

#include "SerialCtl.h"


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

	//---端口号复选框
	ElaText* portTitle = new ElaText("端口号", w);
	portTitle->setWordWrap(false);
	portTitle->setTextPixelSize(14);
	ElaComboBox* portComboBox = new ElaComboBox(w);
	portComboBox->setObjectName("com");
	ElaIconButton* refreshButton = new ElaIconButton(ElaIconType::Recycle, w);
	connect(refreshButton, &QPushButton::clicked, this, [=] {
		updateSerialPortNamesToComboBox(portComboBox);
	});
	//---波特率复选框
	ElaText* baudTitle = new ElaText("波特率", w);
	baudTitle->setWordWrap(false);
	baudTitle->setTextPixelSize(14);
	ElaComboBox* baudComboBox = new ElaComboBox(w);
	baudComboBox->setObjectName("baud");
	baudComboBox->addItems(QStringList({ "9600", "19200", "38400", "57600", "115200" }));

	//第一行
	QWidget* tw1 = new QWidget(w);
	QHBoxLayout* tHLyout1 = new QHBoxLayout(tw1);
	tHLyout1->addWidget(portTitle);
	tHLyout1->addWidget(portComboBox);
	tHLyout1->addWidget(refreshButton);
	tHLyout1->addStretch();
	tHLyout1->addWidget(baudTitle);
	tHLyout1->addWidget(baudComboBox);

	//第二行
	//QWidget* tw2 = new QWidget(w);
	//QHBoxLayout* tHLyout2 = new QHBoxLayout(tw2);

	if (auto* vLayout = qobject_cast<QVBoxLayout*>(l)) {
		vLayout->addWidget(tw1);
	}

	// 刷新一下串口列表
	refreshButton->click();

	// 根据设置填充设置项
	portComboBox->setCurrentText(SerialCtl::getSerialName());
	baudComboBox->setCurrentText(QString::number(SerialCtl::getSerialbaudRate()));

	settingsWidget = w;
}

QWidget* SerialSetting::getWidget()
{
	if (!settingsWidget)
		throw std::runtime_error("Communication Settings Page Widget is null");
	return settingsWidget;
}

QString SerialSetting::getSettingsString()
{
	QString comStr(""), baudStr("");

	QComboBox* com = getWidget()->findChild<QComboBox*>("com");
	QComboBox* baud = getWidget()->findChild<QComboBox*>("baud");
	if (com)
		comStr = com->currentText();
	if (baud)
		baudStr = baud->currentText();

	return QString("com: " + comStr + " baud: " + baudStr);
}

QWidget* SerialSetting::getWidgetFromName(QString name)
{
	QWidget* w = nullptr;
	w = getWidget()->findChild<QWidget*>(name);

	return w;
}

void SerialSetting::updateSerialPortNamesToComboBox(QComboBox* cb)
{
	// 使用 serialComboBox
	auto serialPortNameList = getSerialNameList();
	cb->clear();
	cb->addItems(serialPortNameList);
}

QStringList SerialSetting::getSerialNameList() {
	auto serialPortInfoList = QSerialPortInfo::availablePorts();
	QStringList l;
	for (auto& s : serialPortInfoList) {
		l.append(s.portName());
	}
	return l;
}