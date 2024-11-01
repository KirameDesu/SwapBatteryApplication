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

    // ���캯��
    SerialSettings()
        : name("Default"),         // Ĭ������
        baudRate(9600),         // Ĭ�ϲ�����
        dataBits(QSerialPort::Data8), // Ĭ������λ
        parity(QSerialPort::NoParity), // Ĭ������żУ��
        stopBits(QSerialPort::OneStop), // Ĭ��һ��ֹͣλ
        flowControl(QSerialPort::NoFlowControl), // Ĭ����������
        localEchoEnabled(false)  // Ĭ�Ϲرձ��ػ���
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
    void apply() override;
    void setSerialSettings(SerialSettings serialSettings);

private:
    SerialSettings settings;
    QSerialPort* serial{ nullptr };
};

#endif