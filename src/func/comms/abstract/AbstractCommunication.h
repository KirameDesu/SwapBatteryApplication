#ifndef ABSTRACT_COMMUNICATION_H
#define ABSTRACT_COMMUNICATION_H

#include <QtCore/QObject>

#include "AbstractCommsSetting.h"


class AbstractCommunication : public QObject {
    Q_OBJECT

public:
    explicit AbstractCommunication(QObject* parent = nullptr);

    virtual bool open() = 0;

    virtual bool isOpen() = 0;

    virtual bool isConnected() = 0;

    virtual void close() = 0;

    virtual QByteArray readAll() = 0;

    virtual qint64 write(const QByteArray& byteArray) const = 0;

    virtual QString settingsText() const = 0;

    virtual void applySettings() = 0;

    virtual QString errorString() = 0;

    AbstractCommsSetting* settingWidget;

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

signals:
    void readyRead();
};


#endif // !ABSTRACT_COMMUNICATION_H