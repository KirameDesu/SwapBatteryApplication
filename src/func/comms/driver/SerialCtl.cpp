﻿#include "SerialCtl.h"

#include <QDebug>
#include <QComboBox>
#include <QPushButton>
#include <LoggerManager.h>

SerialSettings SerialCtl::settings;

SerialCtl::SerialCtl(QObject* parent)
{
    this->settingWidget = new SerialSetting();
}

SerialCtl::~SerialCtl()
{
    delete settingWidget;
    settingWidget = nullptr;
}

bool SerialCtl::open() {
    close();

    serial = new QSerialPort(this);
    //modbusMaster = new ModbusMaster(new CustomStream(serial));
    serial->setPortName(settings.name);
    serial->setBaudRate(settings.baudRate);
    serial->setDataBits(settings.dataBits);
    serial->setParity(settings.parity);
    serial->setStopBits(settings.stopBits);
    serial->setFlowControl(settings.flowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        connect(serial, &QSerialPort::readyRead, this, &SerialCtl::readyRead);
        return true;
    }
    else {
        return false;
    }
}

bool SerialCtl::isOpen() {
    return serial != nullptr && serial->isOpen();
}

QByteArray SerialCtl::readAll() {
    if (!isConnPtrNotNullWithExcepte() || !serial->isOpen())
        return QByteArray();

    QByteArray arr(serial->readAll());
    LoggerManager::instance().appendLogList("读取" + arr.toHex());
    return arr;
}

qint8 SerialCtl::readByte()
{
    if (!isConnPtrNotNullWithExcepte())
        return 0xFF;

    QByteArray ba = serial->read(1);
    return ba.isEmpty() ? 0xFF : ba[0];
}

qint64 SerialCtl::bytesAvailable() {
    if (!isConnPtrNotNullWithExcepte())
        return -1;

    return serial->bytesAvailable();
}

void SerialCtl::flush()
{
    if (!isConnPtrNotNullWithExcepte())
        return;

    serial->flush();
}

qint64 SerialCtl::write(const QByteArray& byteArray) const {
    if (!isConnPtrNotNullWithExcepte() || !serial->isOpen())
        return -1;

    LoggerManager::logWithTime("发送-->" + byteArray.toHex(' '));
    return serial->write(byteArray);
}

bool SerialCtl::close() {
    if (serial != nullptr) {
        serial->close();
        delete serial;
        serial = nullptr;
        return true;
    }
    return false;
}

QString SerialCtl::settingsText() const {
    return QString("%1 %2 %3 %4 %5").arg(settings.name).arg(settings.baudRate).arg(settings.dataBits).arg(
        settings.stopBits).arg(settings.parity);
}

void SerialCtl::applySettings()
{
    // 返回widget上的设置项
    QWidget* settingsWidget = this->settingWidget->getWidget();
    settings.name = settingsWidget->findChild<QComboBox*>("com")->currentText();
    settings.baudRate = settingsWidget->findChild<QComboBox*>("baud")->currentText().toInt();
}

QString SerialCtl::errorString()
{
    if (!isConnPtrNotNullWithExcepte())
        return QString("");

    return serial->errorString();
}

QString SerialCtl::getCommTypeString()
{
    return QString("Serial");
}

QString SerialCtl::getSerialName()
{
    return settings.name == "Default" ? QString("") : settings.name;
}

qint32 SerialCtl::getSerialbaudRate()
{
    return settings.baudRate;
}

bool SerialCtl::isConnected() {
    return serial != nullptr && serial->isOpen();
}

bool SerialCtl::isConnPtrNotNull() {
    return serial != nullptr ? true : false;
}

bool SerialCtl::isConnPtrNotNullWithExcepte() const {
    if (serial == nullptr) {
        throw PointerException("Connect Pointer is NULL");
    }
    return true;
}