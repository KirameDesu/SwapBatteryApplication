#ifndef COMMUNICATION_WORKER_H
#define COMMUNICATION_WORKER_H

#include <QObject>

#include "CustomModbusMaster.h"
#include "ModelManager.h"

enum CMDRequestType
{
    read,
    write
};

struct ModbusRequest
{
	int id;

	CMDRequestType actionType;

	qint16 startAddr;
	int readDataLen;
	QByteArray dataArr;		// 写操作才会用到

	int time;		// 1970年时间戳, ms
};

struct ModbusResponse
{
	int id;

	int resultCode;

	qint16 startAddr;
	QByteArray responseData;
	int responseLen;

	int time;		// 1970年时间戳
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