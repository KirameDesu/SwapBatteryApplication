#ifndef COMMUNICATION_WORKER_H
#define COMMUNICATION_WORKER_H

#include <QObject>

#include "CustomModbusMaster.h"
#include "ModelManager.h"

class CommunicationWorker : public QObject
{
    Q_OBJECT
public:
    CommunicationWorker(CustomModbusMaster* customModbusMaster, ModelManager* model)
        : _customModbusMaster(customModbusMaster), _model(model) {}

	void processRequest(ModbusRequest* request, int retries);

private:
    void processResponse();
	QString getLastComunicationInfo();
	int _sendModbusRequest(ModbusRequest* r);

signals:
    Q_SIGNAL void SendDequeueMessage();

private:
    const static int MAX_RETRIES = 3;
    const static int RETRY_DELAY = 1;

	int _lastComunicationResult = 0;

    CustomModbusMaster* _customModbusMaster;
    ModelManager* _model;
};


#endif // !COMMUNICATION_WORKER_H