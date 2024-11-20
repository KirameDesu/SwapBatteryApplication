// BMSCmdManager.h 此类用于管理所有报文何时发送以及是否发送成功，主要维护了一个队列
#ifndef BMS_CMD_MANAGER_H
#define BMS_CMD_MANAGER_H

#include <QQueue>
#include <QPair>
#include <QByteArray>
#include <QEvent>

#include "AbstractCommunication.h"
#include "Communication.h"
#include "CustomModbusMaster.h"
#include "TimerManager.h"

enum CMDRequestType
{
	read,
	write
};

struct ModbusRequest
{
	CMDRequestType actionType;

	qint16 startAddr;
	int readDataLen;
	QByteArray dataArr;		// 写操作才会用到

	DataTime time;
};


// 自定义事件
class ModbusRequestEvent : public QEvent
{
public:
	ModbusRequestEvent(ModbusRequest request)
		: QEvent(static_cast<QEvent::Type>(QEvent::User + 1)), // 使用 QEvent::User + 1 来确保自定义事件的类型
		m_request(request) {}

	ModbusRequest getRequest() const { return m_request; }

private:
	ModbusRequest m_request;
};

class BMSCmdManager : QObject
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

protected:
	// 通讯拓展
	ModbusMaster* _modbusMaster{ nullptr };
	CustomModbusMaster* _customModbusMaster{ nullptr };

	bool event(QEvent* event) override;
private:
	// CONNECT BASE
	std::shared_ptr<AbstractCommunication> _communication{ nullptr };

	// 寄存器操作请求队列
	QQueue<ModbusRequest> _requestQueue;

	int _lastComunicationResult = 0;
	static const int MAX_RETRIES = 3;
	static const int RETRY_DELAY = 1;

	bool _oneShot = false;

	// 发送报文入队	
	void _enqueueReadRequest(qint16 startAddr, qint16 readLen);
	void _enqueueWriteRequest(qint16 startAddr, const QByteArray& data);
	// 发送报文出队
	Q_SLOT void _dequeueMessage();

	int _sendModbusRequest(ModbusRequest r);

	void processRequest(ModbusRequest, int);

};


#endif