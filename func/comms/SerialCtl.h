#ifndef SERIAL_CTL_H
#define SERIAL_CTL_H

#include <QtSerialPort/QSerialPort>

#include "AbstractCommunication.h"
#include "SerialSetting.h"

struct SerialSettings {
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
    bool localEchoEnabled;

    // 构造函数
    SerialSettings()
        : name("Default"),         // 默认名称
        baudRate(9600),         // 默认波特率
        dataBits(QSerialPort::Data8), // 默认数据位
        parity(QSerialPort::NoParity), // 默认无奇偶校验
        stopBits(QSerialPort::OneStop), // 默认一个停止位
        flowControl(QSerialPort::NoFlowControl), // 默认无流控制
        localEchoEnabled(false)  // 默认关闭本地回显
    {}
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