#ifndef COMMUNICATION_WORKER_H
#define COMMUNICATION_WORKER_H

#include <QObject>
#include <QByteArray>

#include "CustomModbusMaster.h"
#include "AbstractCommunication.h"
#include "BaseProtocol.h"
#include "ModelManager.h"

class CommunicationWorker : public QObject
{
    Q_OBJECT
public:
    CommunicationWorker(CustomModbusMaster* customModbusMaster, ModelManager* model);
    ~CommunicationWorker() = default;

	void processRequest(ModbusRequest* request, int retries);
    // 对于原始数组
    void processRawDataRequest(RawDataRequest* request, int retries);

    void setProtocol(BaseProtocol* protocol);

private:
    void processResponse();
    void processRawData();
	QString getLastComunicationInfo();
	int _sendModbusRequest(ModbusRequest* r);

    int _sendRawDataRequest(RawDataRequest* r);

    //QMutex mutex;  // 声明一个互斥量
signals:
    Q_SIGNAL void SendDequeueMessage();
    Q_SIGNAL void SendDequeuRawData();
    Q_SIGNAL void errorOccurred(QString errorMessage);
    Q_SIGNAL void deleteRequest(ModbusRequest* r);
    Q_SIGNAL void deleteRawRequest(RawDataRequest* r);

private:
    const static int MAX_RETRIES = 2;
    const static int RETRY_DELAY = 500;     // ms

	int _lastComunicationResult = 0;

    // 通讯类
    CustomModbusMaster* _customModbusMaster;
    AbstractCommunication* _communication;

    // 协议类
    BaseProtocol* _protocol;

    ModelManager* _model;
};


#endif // !COMMUNICATION_WORKER_H