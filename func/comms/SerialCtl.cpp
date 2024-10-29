#include "SerialCtl.h"

#include <QDebug>

SerialCtl::SerialCtl(QObject* parent)
{
}

SerialCtl::~SerialCtl()
{
}

bool SerialCtl::open() {
    close();

    serial = new QSerialPort(this);
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
    if (serial != nullptr && serial->isOpen()) {
        return serial->readAll();
    }
    qDebug() << "SerialReadWriter readAll() _serial == nullptr or not open";
    return QByteArray();
}

qint64 SerialCtl::write(const QByteArray& byteArray) const {
    if (serial != nullptr && serial->isOpen()) {
        return serial->write(byteArray);
    }
    qDebug() << "SerialReadWriter readAll() _serial == nullptr or not open";
    return 0;
}

void SerialCtl::setSerialSettings(SerialSettings serialSettings) {
    this->settings = std::move(serialSettings);
}

void SerialCtl::close() {
    if (serial != nullptr) {
        serial->close();
        delete serial;
        serial = nullptr;
    }
}

QString SerialCtl::settingsText() const {
    return QString("%1 %2 %3 %4 %5").arg(settings.name).arg(settings.baudRate).arg(settings.dataBits).arg(
        settings.stopBits).arg(settings.parity);
}

bool SerialCtl::isConnected() {
    return serial != nullptr && serial->isOpen();
}
