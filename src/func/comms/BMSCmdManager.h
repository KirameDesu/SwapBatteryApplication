// BMSCmdManager.h 此类用于管理所有报文何时发送以及是否发送成功，主要维护了一个队列
#ifndef BMS_CMD_MANAGER_H
#define BMS_CMD_MANAGER_H

#include <QQueue>
#include <QPair>
#include <QByteArray>

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
	int dataLen;
	QByteArray data;		// 写操作才会用到

	DataTime time;
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

	// 设置寄存器管理类
	//void setupRegisterManager(const RDManager* rd);

	void read(QSet<QString> groupName);
protected:
	// 通讯拓展
	ModbusMaster* _modbusMaster{ nullptr };
	CustomModbusMaster* _customModbusMaster{ nullptr };

private:
	int _lastComunicationResult = 0;

	// CONNECT BASE
	std::shared_ptr<AbstractCommunication> _communication{ nullptr };

	// 寄存器管理类

	// 寄存器操作队列
	//QQueue<QPair<ModbusRequest, RegisterData>> _requestQueue;
	QQueue<ModbusRequest> _requestQueue;

	// 发送报文入队	
	void _enqueueReadRequest(qint16 startAddr, qint16 readLen);
	// 发送报文出队
	void dequeueMessage();
//signals:
	//void read(QList<QString> gourpName);
};


#endif