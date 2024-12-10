#ifndef ABSTRACT_COMMUNICATION_H
#define ABSTRACT_COMMUNICATION_H

#include <QtCore/QObject>
#include <QByteArray>

#include "AbstractCommsSetting.h"


class AbstractCommunication : public QObject {
    Q_OBJECT

public:
    static const qint8 ku8TimeOut = 0x10;
    static const qint8 ku8InvildCRC = 0x20;
    //static const qint8 ku8TimeOut = 0x10;


    explicit AbstractCommunication(QObject* parent = nullptr);
    virtual ~AbstractCommunication() = default;

    virtual bool open() = 0;

    virtual bool isOpen() = 0;

    virtual bool isConnected() = 0;

    virtual bool close() = 0;

    virtual qint64 bytesAvailable() = 0;        // 接收缓冲区剩余数据数量

    virtual bool flush() = 0;

    virtual QByteArray readAll() = 0;

    virtual qint8 readByte() = 0;

    virtual qint64 write(const QByteArray& byteArray) const = 0;

    virtual QString settingsText() const = 0;

    virtual void applySettings() = 0;

    virtual QString errorString() = 0;

    virtual QString getCommTypeString() = 0;

    virtual quint8 sendProcess(const QByteArray& byteArray);

    const QByteArray& getRecvArray() const;

    AbstractCommsSetting* settingWidget{ nullptr };

    // 连接异常
    class ConnectException : public std::runtime_error {
    public:
        explicit ConnectException(const std::string& message)
            : std::runtime_error("ConnectException: " + message) {}
    };

    // 指针异常
    class PointerException : public std::runtime_error {
    public:
        explicit PointerException(const std::string& message)
            : std::runtime_error("PointerException: " + message) {}
    };

private:
    static const int ADU_MAX_SIZE = 2048;
    
    quint8 _u8ADUBuff[ADU_MAX_SIZE];
    QByteArray _recvByteArray;

signals:
    void readyRead();
};


#endif // !ABSTRACT_COMMUNICATION_H