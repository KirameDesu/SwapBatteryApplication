#ifndef SERIAL_CTL_H
#define SERIAL_CTL_H

#include <QtSerialPort/QSerialPort>

#include "AbstractCommunication.h"

struct SerialSettings {
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    bool localEchoEnabled;
};

class SerialCtl : public AbstractCommunication
{
public:
    explicit SerialCtl(QObject* parent = nullptr);
    ~SerialCtl();
    bool open() override;
    bool isOpen() override;
    bool isConnected() override;
    void close() override;
    QByteArray readAll() override;
    qint64 write(const QByteArray& byteArray) const override;
    QString settingsText() const override;
    void setSerialSettings(SerialSettings serialSettings);

private:
    SerialSettings settings;
    QSerialPort* serial{ nullptr };
};

#endif