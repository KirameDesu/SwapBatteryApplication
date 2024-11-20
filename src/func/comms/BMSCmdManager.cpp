#include "BMSCmdManager.h"

#include <QThread>
#include <QCoreApplication>
#include <QTimer>

#include "LoggerManager.h"
#include "RDManager.h"

BMSCmdManager::BMSCmdManager()
{
	// 初始化通讯为串口
	_communication = Communication::createCommunication(CommunicationType::Serial);
	_modbusMaster = new ModbusMaster(new StreamType(_communication.get()));
	_customModbusMaster = new CustomModbusMaster(new StreamType(_communication.get()));
}

BMSCmdManager::~BMSCmdManager()
{
}

std::shared_ptr<AbstractCommunication> BMSCmdManager::getConnect()
{
	return _communication;
}

void BMSCmdManager::standardModbusTest()
{
	try {
		_modbusMaster->begin(1);

		_modbusMaster->setTransmitBuffer(0, 0xFAFA);
		_modbusMaster->setTransmitBuffer(1, 0x1010);
		_modbusMaster->readWriteMultipleRegisters(0x1011, 2);
	}
	catch (AbstractCommunication::PointerException e) {
		LoggerManager::instance().appendLogList(QString::fromStdString(std::string(e.what()) + " occurred in func" + std::string(__FUNCTION__)));
	}
}

static uint8_t SLAVE_ID = 0x01;
static uint8_t ADDR_START = 0x0040;

void BMSCmdManager::customModbusTest()
{
	QByteArray BYTE_ARRAY("ABCD");

	try {
		_customModbusMaster->begin(1);
		_customModbusMaster->appendWriteRegisters(SLAVE_ID, ADDR_START, reinterpret_cast<unsigned short*>(BYTE_ARRAY.data()), BYTE_ARRAY.size());
		_customModbusMaster->appendReadRegisters(SLAVE_ID, ADDR_START, 4);

		// 开始发送
		_lastComunicationResult = _customModbusMaster->TransactionWithMsgNum();
		LoggerManager::log(getLastComunicationInfo());
	}
	catch (AbstractCommunication::PointerException e) {
		LoggerManager::instance().appendLogList(QString::fromStdString(std::string(e.what()) + " occurred in func" + std::string(__FUNCTION__)));
	}
}

QString BMSCmdManager::getLastComunicationInfo()
{
	QString ret("接收状态: 0x" + QString::number(_lastComunicationResult).toLatin1());
	ret.append('\r');
	int msgNum = _customModbusMaster->getResponseMsgNum();
	ret.append(QString("共响应到%1条Msg报文").arg(msgNum));
	ret.append('\r');
	for (int i = 0; i < msgNum; i++) {
		int funCode = _customModbusMaster->getResponseFuncCode(i);
		bool funRet = _customModbusMaster->getResponseFuncResult(i);
		QByteArray byteArray;
		for (int j = 0; j < _customModbusMaster->getResponseLenth(i); j++) {
			uint16_t data = _customModbusMaster->getResponseBuffer(i, j);
			byteArray.append(static_cast<char>(data >> 8));  // 高字节
			byteArray.append(static_cast<char>(data & 0xFF));  // 低字节
		}
		QString byteArrayStr("\"" + byteArray.toHex(' ') + "\"");

		ret.append(QString("*Msg.%1: action=0x%2, bool=%3, data=%4").arg(i + 1).arg(QString::number(funCode).toLatin1()).arg(funRet).arg(byteArrayStr));
		ret.append('\r');
	}
	return ret;
}

void BMSCmdManager::read(QSet<QString> groupName)
{
	// 根据组名称从RDManager中获取需要操作的寄存器地址
	for (const QString& c : groupName) {
		QPair<qint16, qint16> cell = RDManager::instance().getRegGroupAddrAndLen(c);
		// 操作入队
		_enqueueReadRequest(cell.first, cell.second);
	}
}

void BMSCmdManager::write(QSet<QString> groupName)
{
	// 根据组名称从RDManager中获取需要操作的寄存器地址
	for (const QString& c : groupName) {
		qint16 startAddr = RDManager::instance().getRegGroupAddr(c);
		QByteArray data = RDManager::instance().getDisplayDataArr(c);
		// 操作入队
		_enqueueWriteRequest(startAddr, data);
	}
}

bool BMSCmdManager::event(QEvent* event)
{
	if (event->type() == static_cast<QEvent::Type>(QEvent::User + 1)) {
		ModbusRequestEvent* modbusEvent = static_cast<ModbusRequestEvent*>(event);
		try {
			processRequest(modbusEvent->getRequest(), 0);
		} catch (AbstractCommunication::PointerException e) {
			LoggerManager::instance().appendLogList(QString::fromStdString(std::string(e.what()) + " occurred in func" + std::string(__FUNCTION__)));
			// 清空队列
			_requestQueue.clear();
			_oneShot = false;
		}

		return true;
	}
	return QObject::event(event);
}

void BMSCmdManager::_enqueueReadRequest(qint16 startAddr, qint16 readLen)
{
	ModbusRequest r;
	r.actionType = CMDRequestType::read;
	r.startAddr = startAddr;
	r.readDataLen = readLen;
	_requestQueue.enqueue(r);

	// 如果队列之前是空的，表示这是第一个请求，触发处理
	if (!_oneShot) {
		_oneShot = true;
		_dequeueMessage();
	}
}

void BMSCmdManager::_enqueueWriteRequest(qint16 startAddr, const QByteArray& data)
{
	ModbusRequest r;
	r.actionType = CMDRequestType::write;
	r.startAddr = startAddr;
	r.readDataLen = 0;
	r.dataArr = data;
	_requestQueue.enqueue(r);

	// 如果队列之前是空的，表示这是第一个请求，触发处理
	if (!_oneShot) {
		_oneShot = true;
		_dequeueMessage();
	}
}

void BMSCmdManager::_dequeueMessage()
{
	if (!_requestQueue.isEmpty()) {
		ModbusRequest request = _requestQueue.dequeue();
		QCoreApplication::postEvent(this, new ModbusRequestEvent(request));  // 发送事件
		LoggerManager::log(QString(__FUNCTION__) + QString(": 请求队列出队，队列剩余%1个").arg(_requestQueue.size()));
	} else {
		_oneShot = false;
		LoggerManager::log(QString(__FUNCTION__) + QString(": 请求队列执行完毕"));
	}
}

int BMSCmdManager::_sendModbusRequest(ModbusRequest r) {
	_customModbusMaster->begin(1);
	switch (r.actionType) {
	case CMDRequestType::read:
		_customModbusMaster->appendReadRegisters(SLAVE_ID, r.startAddr, r.readDataLen);
		break;
	case CMDRequestType::write:
		_customModbusMaster->appendWriteRegisters(SLAVE_ID, r.startAddr, reinterpret_cast<unsigned short*>(r.dataArr.data()), r.dataArr.size());
	}

	return _customModbusMaster->TransactionWithMsgNum();
}

void BMSCmdManager::processRequest(ModbusRequest request, int retries = 0)
{
	bool success = false;
	if (retries < MAX_RETRIES) {
		success = _sendModbusRequest(request);
		if (success == 0) {
			LoggerManager::log(QString(__FUNCTION__) + ": 发送成功");
			// 继续处理队列中的下一个请求
			_dequeueMessage();
			return;  // 发送成功，结束处理
		}
		else {
			// 发送失败，计划重试
			LoggerManager::log(QString(__FUNCTION__) + ": 发送失败，准备重试 " + QString::number(retries + 1));
			// 使用 QTimer 延迟重试，并保留当前的重试次数
			QTimer::singleShot(RETRY_DELAY * 1000, this, [this, request, retries]() {
				processRequest(request, retries + 1);
				});
			return;  // 立即返回，让定时器在稍后继续尝试
		}
	}
	else {
		// 达到最大重试次数，记录错误
		LoggerManager::log(QString(__FUNCTION__) + ": 重试次数已达上限，发送失败");
		// 继续处理队列中的下一个请求，即使失败也不阻塞后续处理
		_dequeueMessage();
	}
}
