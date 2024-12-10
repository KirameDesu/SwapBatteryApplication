// BMSCmdManager.h 此类用于管理所有报文何时发送以及是否发送成功，主要维护了一个队列
#ifndef BMS_CMD_MANAGER_H
#define BMS_CMD_MANAGER_H

#include <memory>

#include <QQueue>
#include <QList>
#include <QPair>
#include <QByteArray>
#include <QEvent>
#include <QThread>

#include "AbstractCommunication.h"
#include "BaseProtocol.h"
#include "Communication.h"
#include "CustomModbusMaster.h"
#include "ControllerMaster.h"
#include "TimerManager.h"
#include "ModelManager.h"
#include "CommunicationWorker.h"

#include "ProtocolFactory.h"


// 自定义事件
class ModbusRequestEvent : public QEvent
{
public:
	ModbusRequestEvent(ModbusRequest* request)
		: QEvent(static_cast<QEvent::Type>(QEvent::User + 1)),  // 使用 QEvent::User + 1 来确保自定义事件的类型
		m_request(std::move(request)) {}  // 使用 std::move

	ModbusRequest* getRequest() const { return m_request; }

private:
	ModbusRequest* m_request;  // 保存智能指针
};

class BMSCmdManager : public QObject
{	
	Q_OBJECT
public:
	BMSCmdManager();
	~BMSCmdManager();
	
	std::shared_ptr<AbstractCommunication> getConnect();
	void standardModbusTest();
	void customModbusTest();
	QString getLastComunicationInfo();

	void read(QSet<QString> groupName);

	void write(QSet<QString> groupName);

	void startUpgrade(QString protString, QString filePath);

	void startThread();

	void waitThreadEnd();

	//LowSOCSettingsModel* getLowSOCSettingsModel() {
	//	return _model->getLowSOCSettingsModel();
	//}
protected:
	// 通讯拓展
	ModbusMaster* _modbusMaster{ nullptr };
	CustomModbusMaster* _customModbusMaster{ nullptr };
	ControllerMaster* _controllerMastar{ nullptr };

	bool event(QEvent* event) override;

private:
	int _lastComunicationResult = 0;
	static const int MAX_RETRIES = 3;
	static const int RETRY_DELAY = 1;

	// CONNECT BASE
	std::shared_ptr<AbstractCommunication> _communication{ nullptr };
	// UPGRADE BASE
	BaseProtocol* _protocol{ nullptr };

	// 寄存器操作请求队列
	QQueue<ModbusRequest*> _sendQueue;
	QQueue<ModbusResponse*> _recvQueue;
	// Model类
	ModelManager* _model{ nullptr };
	// 线程类
	CommunicationWorker* _commuWorker{ nullptr };
	QThread* _workerThread{ nullptr };

	bool _oneShot = false;

	//====*hex数组待发送队列====
	QQueue<RawDataRequest*> _rawDataSendQueue;

	// 发送报文入队	
	void _enqueueReadRequest(qint16 startAddr, qint16 readLen);
	void _enqueueReadMutiRequest(const QList<QPair<qint16, qint16>>& l);
	void _enqueueWriteRequest(qint16 startAddr, const QByteArray& data);
	// 发送报文出队
	Q_SLOT void _dequeueMessage();
	Q_SLOT void _dequeueRawData();
	// 重置队列以及标志
	void _resetQueue();
	void _commuError(QString errMsg);

	UpgradeStep _upgradeStep;

	void _upgradeProcess();

#if defined __NOT_THREAD__
	int _sendModbusRequest(ModbusRequest* r);
	void processRequest(ModbusRequest* request, int retries);
	void processResponse();
#endif

signals:
	Q_SIGNAL void sendModbusRequest(ModbusRequest* r, int retries);
	Q_SIGNAL void sendRawDataRequest(RawDataRequest* r, int retries);

	Q_SIGNAL void upgradeReady();
	Q_SIGNAL void upgradePackSendOver();
	Q_SIGNAL void upgradeEnd();

	Q_SIGNAL void upgradeProcess(float percent);
};


#endif