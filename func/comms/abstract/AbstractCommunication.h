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

    AbstractCommsSetting* settingAction;

signals:
    void readyRead();
};


#endif // !ABSTRACT_COMMUNICATION_H