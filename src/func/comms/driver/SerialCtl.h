#ifndef SERIAL_CTL_H
#define SERIAL_CTL_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/qserialportinfo.h>

#include "AbstractCommunication.h"
#include "SerialSetting.h"
#include "ModbusMaster.h"

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

class ModbusMaster;
class SerialCtl : public AbstractCommunication
{
    Q_OBJECT

public:
    explicit SerialCtl(QObject* parent = nullptr);
    ~SerialCtl();
    bool open() override;
    bool isOpen() override;
    bool isConnected() override;
    bool close() override;
    QByteArray readAll() override;
    qint8 readByte() override;
    qint64 bytesAvailable() override;
    void flush() override;
    qint64 write(const QByteArray& byteArray) const override;
    QString settingsText() const override;
    void applySettings() override;
    QString errorString() override;
    QString getCommTypeString() override;

    static QString getSerialName();
    static qint32 getSerialbaudRate();

    ModbusMaster* modbusMaster{ nullptr };
private:
    static SerialSettings settings;
    QSerialPort* serial{ nullptr };             // 未连接时为空

    bool isConnPtrNotNull();
    bool isConnPtrNotNullWithExcepte() const;
};

#endif