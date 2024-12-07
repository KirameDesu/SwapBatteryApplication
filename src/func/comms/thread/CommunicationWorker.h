﻿#ifndef COMMUNICATION_WORKER_H
#define COMMUNICATION_WORKER_H

#include <QObject>

#include "CustomModbusMaster.h"
#include "ModelManager.h"

enum UpgradeStep
{
    prepareUpgrade = 0,
    sendPack,
    checkUpgrade,
    endUpgrade
};

class CommunicationWorker : public QObject
{
    Q_OBJECT
public:
    CommunicationWorker(CustomModbusMaster* customModbusMaster, ModelManager* model)
        : _customModbusMaster(customModbusMaster), _model(model) {}

	void processRequest(ModbusRequest* request, int retries);

private:
    void processResponse();
    void processUpgrade();
	QString getLastComunicationInfo();
	int _sendModbusRequest(ModbusRequest* r);

signals:
    Q_SIGNAL void SendDequeueMessage();
    Q_SIGNAL void errorOccurred(QString errorMessage);
    Q_SIGNAL void deleteRequest(ModbusRequest* r);
    Q_SIGNAL void nextProcess(UpgradeStep step);

private:
    const static int MAX_RETRIES = 2;
    const static int RETRY_DELAY = 500;     // ms

	int _lastComunicationResult = 0;

    CustomModbusMaster* _customModbusMaster;
    ModelManager* _model;
};


#endif // !COMMUNICATION_WORKER_H