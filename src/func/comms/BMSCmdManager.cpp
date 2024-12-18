﻿#include "BMSCmdManager.h"

#include <QThread>
#include <QCoreApplication>
#include <QTimer>

#include "ElaMessageBar.h"

#include "LoggerManager.h"
#include "RDManager.h"
#include "VoltageProtectModel.h"

BMSCmdManager::BMSCmdManager()
{
	_model = new ModelManager();

	// 初始化通讯为串口, 使用工厂方法模式, 根据选项设置具体通讯方法
	_communication = Communication::createCommunication(CommunicationType::Serial);
	_modbusMaster = new ModbusMaster(new StreamType(_communication.get()));
	_customModbusMaster = new CustomModbusMaster(new StreamType(_communication.get()));
	
	_upgradeStep = UpgradeStep::prepareUpgrade;
}

BMSCmdManager::~BMSCmdManager()
{
	// 终止和清理线程
	waitThreadEnd();
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

static uint8_t SLAVE_ID = 0x0101;
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
		LoggerManager::logWithTime(getLastComunicationInfo());
	}
	catch (AbstractCommunication::PointerException e) {
		LoggerManager::instance().appendLogList(QString::fromStdString(std::string(e.what()) + " occurred in func" + std::string(__FUNCTION__)));
	}
}

QString BMSCmdManager::getLastComunicationInfo()
{
	QString ret("接收状态: 0x" + QString("%1").arg(_lastComunicationResult, 2, 16, QChar('0')).toUpper());
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

		uint16_t regStart = _customModbusMaster->getRegisterStartAddr(i);
		ret.append(QString("*Msg.%1: action=0x%2, ResponseState=%3, RegStart=0X%4, data=%5")
			.arg(i + 1)
			.arg(QString("%1").arg(funCode, 2, 16, QChar('0')).toUpper())
			.arg(funRet)
			.arg(QString("%1").arg(regStart, 4, 16, QChar('0')).toUpper())
			.arg(byteArrayStr));
		ret.append('\r');
	}
	return ret;
}

void BMSCmdManager::read(QSet<QString> groupName)
{
	// 根据组名称从RDManager中获取需要操作的寄存器地址
	QList<QPair<qint16, qint16>> list;
#if 0			/// 暂时改为只让第一个group去发送页面所有的
	for (const QString& c : groupName) {
		QPair<qint16, qint16> cell = RDManager::instance().getRegGroupAddrAndLen(c);
		// 操作入队
		//list.append(cell);
		_enqueueReadRequest(cell.first, cell.second);
	}
#else
	quint16 startAddr = 0xFFFF;
	int totalSize = 0;
	for (const QString& c : groupName) {
		QPair<quint16, quint16> cell = RDManager::instance().getRegGroupAddrAndLen(c);
		totalSize += cell.second;
		if (startAddr > cell.first)
			startAddr = cell.first;
	}
	_enqueueReadRequest(startAddr, totalSize);
#endif
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

void BMSCmdManager::startUpgrade(QString protString, QString filePath)
{
	if (_workerThread == nullptr || _commuWorker == nullptr)
	{
		_commuError("Worker or Thread is NULL");
		return;
	}

	if (!_protocol)
	{
		ElaMessageBar::error(ElaMessageBarType::BottomRight, "Error", "升级指针为空!", 2000);
	}
	_protocol->setFilePath(filePath);
	// 确保升级为初始状态
	if (_upgradeStep == UpgradeStep::prepareUpgrade)
	{
		_upgradeProcess();
		ElaMessageBar::information(ElaMessageBarType::BottomRight, "INFO:", "开始升级...", 2000);
	}
	else
		_commuError("Upgrade is processing!");
		//throw std::runtime_error("Upgrade is processing!");
}

/// 这个函数将为被信号一直触发，根据_upgradeStep 
void BMSCmdManager::_upgradeProcess()
{
	static int currentPackNo = 0;
	float upgradeProcessPercent = 0;

	if (_upgradeStep == UpgradeStep::endUpgrade)
	{
		// 结束升级
		_upgradeStep = UpgradeStep::prepareUpgrade;
		currentPackNo = 0;
		_protocol->resetUpgradeState();
		emit upgradeEnd();
		return;
	}

	//request.time = QDateTime::currentDateTime().toMSecsSinceEpoch();
	RawDataRequest* request = nullptr;
	switch (_upgradeStep)
	{
	case UpgradeStep::prepareUpgrade:
		request = new RawDataRequest();
		request->rawData = _protocol->startUpgradeRawData();
		_rawDataSendQueue.enqueue(request);
		_dequeueRawData();
		break;
	case UpgradeStep::sendPack:				/// 只执行一次
#if 1
		// 由于有队列，可以考虑一次性把所有的报文逐个添加到队列
		for (int i = 1; i <= _protocol->getUpgradeTotalPackNum(); ++i)
		{
			request = new RawDataRequest();
			request->rawData = _protocol->UpgradePackRawData(i);
			_rawDataSendQueue.enqueue(request);
		}
		upgradeProcessPercent = _protocol->getUpgradeProcessPercent();
		emit upgradeProcess(upgradeProcessPercent);
		_dequeueRawData();

#else 
		rawData = _protocol->UpgradePackRawData(currentPackNo);
		_rawDataSendQueue.enqueue(std::make_shared<QByteArray>(rawData));
#endif
		break;
	case UpgradeStep::checkUpgrade:
		// 发送切换IAP报文
		request = new RawDataRequest();
		request->rawData = _protocol->endUpgradeRawData();
		_rawDataSendQueue.enqueue(request);
		_dequeueRawData();
		break;
	}
}

void BMSCmdManager::startThread()
{
	if (_workerThread != nullptr)
	{
		qDebug() << "通讯线程已存在";
		return;
	}

	// 工作线程类
	_commuWorker = new CommunicationWorker(_customModbusMaster, _model);
	// 创建升级实例
	_protocol = ProtocolFactory::createProtocol("Controller");
	_commuWorker->setProtocol(_protocol);
	// 创建线程和Worker
	_workerThread = new QThread;
	_commuWorker->moveToThread(_workerThread);
	// 连接信号和槽
	connect(this, &BMSCmdManager::sendModbusRequest, _commuWorker, &CommunicationWorker::processRequest);
	connect(this, &BMSCmdManager::sendRawDataRequest, _commuWorker, &CommunicationWorker::processRawDataRequest);
	connect(_commuWorker, &CommunicationWorker::errorOccurred, this, &BMSCmdManager::_commuError);
	connect(_commuWorker, &CommunicationWorker::SendDequeueMessage, this, &BMSCmdManager::_dequeueMessage);
	connect(_commuWorker, &CommunicationWorker::SendDequeuRawData, this, &BMSCmdManager::_dequeueRawData);
	connect(_commuWorker, &CommunicationWorker::deleteRequest, this, [=](ModbusRequest* r) {
		delete r;
		r = nullptr;
		});	
	connect(_commuWorker, &CommunicationWorker::deleteRawRequest, this, [=](RawDataRequest* r) {
		delete r;
		r = nullptr;
		});
	// 升级相关
	connect(_protocol, &BaseProtocol::nextProcess, this, [=](UpgradeStep step) {
		_upgradeStep = step;
		_upgradeProcess();
		});
	connect(_workerThread, &QThread::finished, this, &BMSCmdManager::_resetQueue);

	
	// 启动线程
	_workerThread->start();
	//qDebug() << "WORKER THEAD : " << _workerThread->currentThreadId();
}

void BMSCmdManager::_commuError(QString errMsg)
{
	ElaMessageBar::error(ElaMessageBarType::BottomRight, "通讯异常", errMsg, 2000);
	LoggerManager::instance().appendLogList(QString(errMsg + " occurred in func" + QString(__FUNCTION__)));
	_resetQueue();
	// 重置升级标志
	_protocol->resetUpgradeState();
}

void BMSCmdManager::waitThreadEnd()
{
	if (_workerThread != nullptr)
	{
		auto id = _workerThread->currentThreadId();
		_workerThread->quit();
		_workerThread->wait();
		delete _workerThread;
		_workerThread = nullptr;
		delete _commuWorker;
		_commuWorker = nullptr;
		//qDebug() << "通讯线程: " << id << "已经退出";
	}
}

bool BMSCmdManager::event(QEvent* event)
{
#if defined __NOT_THREAD__
	if (event->type() == static_cast<QEvent::Type>(QEvent::User + 1)) {
		ModbusRequestEvent* modbusEvent = static_cast<ModbusRequestEvent*>(event);
		try {
			processRequest(modbusEvent->getRequest(), 0);
		} catch (AbstractCommunication::PointerException e) {
			LoggerManager::instance().appendLogList(QString::fromStdString(std::string(e.what()) + " occurred in func" + std::string(__FUNCTION__)));
			// 清空队列
			_sendQueue.clear();
			_oneShot = false;
		}

		return true;
	}
#endif
	return QObject::event(event);
}

void BMSCmdManager::_resetQueue()
{
	// 清空队列
	_sendQueue.clear();
	_recvQueue.clear();
	_rawDataSendQueue.clear();

	// 重置状态
	_oneShot = false;		// modbus
	_upgradeStep = UpgradeStep::prepareUpgrade;			/// 所有通讯失败都会刷新升级标志，要考虑会不会导致其他问题		
}

void BMSCmdManager::_enqueueReadRequest(qint16 startAddr, qint16 readLen)
{
	if (_workerThread == nullptr || _commuWorker == nullptr)
	{
		_commuError("Worker or Thread is NULL");
		return;
	}

	ModbusRequest* r = new ModbusRequest;
	r->actionType = CMDRequestType::read;
	r->gourpNum = 1;
	r->startAddr[0] = startAddr;
	r->readDataLen[0] = readLen;
	//r->time = QDateTime::currentDateTime().toMSecsSinceEpoch();
	_sendQueue.enqueue(r);

	// 如果队列之前是空的，表示这是第一个请求，触发处理
	if (!_oneShot) {
		_oneShot = true;
		_dequeueMessage();
	}
}

void BMSCmdManager::_enqueueReadMutiRequest(const QList<QPair<qint16, qint16>>& l)
{
	if (_workerThread == nullptr || _commuWorker == nullptr)
	{
		_commuError("Worker or Thread is NULL");
		return;
	}

	int i;

	ModbusRequest* r = new ModbusRequest;
	r->actionType = CMDRequestType::read;
	for (i = 0; i < l.size(); ++i)
	{
		r->startAddr[i] = l.at(i).first;
		r->readDataLen[i] = l.at(i).second;
	}
	r->gourpNum = i;
	//r->time = QDateTime::currentDateTime().toMSecsSinceEpoch();
	_sendQueue.enqueue(r);

	// 如果队列之前是空的，表示这是第一个请求，触发处理
	if (!_oneShot) {
		_oneShot = true;
		_dequeueMessage();
	}
}

void BMSCmdManager::_enqueueWriteRequest(qint16 startAddr, const QByteArray& data)
{
	if (_workerThread == nullptr || _commuWorker == nullptr)
	{
		_commuError("Worker or Thread is NULL");
		return;
	}

	ModbusRequest* r = new ModbusRequest;
	r->actionType = CMDRequestType::write;
	r->gourpNum = 1;	// 一次写一组
	r->startAddr[0] = startAddr;
	r->readDataLen[0] = 0;
	r->dataArr = data;
	_sendQueue.enqueue(r);

	// 如果队列之前是空的，表示这是第一个请求，触发处理
	if (!_oneShot) {
		_oneShot = true;
		_dequeueMessage();
	}
}

void BMSCmdManager::_dequeueMessage()
{
	if (!_sendQueue.isEmpty()) {
		ModbusRequest* request = _sendQueue.dequeue();  // 使用 std::move 获取智能指针
#if defined __NOT_THREAD__
		QCoreApplication::postEvent(this, new ModbusRequestEvent(request));  // 传递对象的副本
		LoggerManager::logWithTime(QString(__FUNCTION__) + QString(": 请求队列出队，队列剩余%1个").arg(_sendQueue.size()));
#else
		emit sendModbusRequest(request, 0);  // 发送信号给Worker线程处理
#endif
		/// 出队可以考虑是否要保存成历史记录等...
	}
	else {
		_oneShot = false;
		LoggerManager::logWithTime(QString(__FUNCTION__) + QString(": 请求队列执行完毕"));
	}
}

void BMSCmdManager::_dequeueRawData()
{
	if (!_rawDataSendQueue.isEmpty()) {
		//std::shared_ptr<RawDataRequest> request = _rawDataSendQueue.dequeue();  // 使用 std::move 获取智能指针
		RawDataRequest* request = _rawDataSendQueue.dequeue();
#if defined __NOT_THREAD__
		QCoreApplication::postEvent(this, new ModbusRequestEvent(request));  // 传递对象的副本
		LoggerManager::logWithTime(QString(__FUNCTION__) + QString(": 请求队列出队，队列剩余%1个").arg(_sendQueue.size()));
#else
		emit sendRawDataRequest(request, 0);  // 发送信号给Worker线程处理
#endif
		/// 出队可以考虑是否要保存成历史记录等...
	}
	else {
		LoggerManager::logWithTime(QString(__FUNCTION__) + QString(": 请求队列执行完毕"));
	}
}

#if defined __NOT_THREAD__
int BMSCmdManager::_sendModbusRequest(ModbusRequest* r) {
	r->time = QDateTime::currentDateTime().toMSecsSinceEpoch();

	_customModbusMaster->begin(1);
	switch (r->actionType) {
	case CMDRequestType::read:
		_customModbusMaster->appendReadRegisters(SLAVE_ID, r->startAddr, r->readDataLen);
		break;
	case CMDRequestType::write:
		_customModbusMaster->appendWriteRegisters(SLAVE_ID, r->startAddr, reinterpret_cast<unsigned short*>(r->dataArr.data()), r->dataArr.size());
	}

	return _customModbusMaster->TransactionWithMsgNum();
}

void BMSCmdManager::processRequest(ModbusRequest* request, int retries = 0)
{
	//int success = -1;
	if (retries < MAX_RETRIES) {
		_lastComunicationResult = _sendModbusRequest(request);
		if (_lastComunicationResult == 0) {
			//LoggerManager::log(QString(__FUNCTION__) + ": 发送成功");
			processResponse();
			LoggerManager::logWithTime(getLastComunicationInfo());
			int elapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - request->time;
			LoggerManager::log(QString("*************Communication Elapsed Time: %1ms*************").arg(elapsedTime));
			// 继续处理队列中的下一个请求
			_dequeueMessage();

			// 释放request
			delete request;
			request = nullptr;

			return;  // 发送成功，结束处理
		}
		else {
			// 发送失败，计划重试
			LoggerManager::logWithTime(QString(__FUNCTION__) + ": 发送失败，准备重试 " + QString::number(retries + 1));
			// 使用 QTimer 延迟重试，并保留当前的重试次数
			QTimer::singleShot(RETRY_DELAY * 500, this, [this, request, retries]() {
				processRequest(request, retries + 1);  // 使用指针传递对象
				});
			return;  // 立即返回，让定时器在稍后继续尝试
		}
	}
	else {
		// 达到最大重试次数，记录错误
		LoggerManager::logWithTime(QString(__FUNCTION__) + ": 重试次数已达上限，发送失败");

		// 释放request
		delete request;
		request = nullptr;

		// 继续处理队列中的下一个请求，即使失败也不阻塞后续处理
		_dequeueMessage();
	}
}

void BMSCmdManager::processResponse() {
	/// 应答结构体入队
	//_enqueueRespnse();

	int msgNum = _customModbusMaster->getResponseMsgNum();

	for (int i = 0; i < msgNum; i++) {
		int funCode = _customModbusMaster->getResponseFuncCode(i);
		bool funRet = _customModbusMaster->getResponseFuncResult(i);
		QByteArray rawData;
		for (int j = 0; j < _customModbusMaster->getResponseLenth(i); j++) {
			uint16_t data = _customModbusMaster->getResponseBuffer(i, j);
			rawData.append(static_cast<char>(data >> 8));  // 高字节
			rawData.append(static_cast<char>(data & 0xFF));  // 低字节
		}
		// 将数据传递给Model，也就是数据结构体
		uint16_t startAddr = _customModbusMaster->getRegisterStartAddr(i);
		_model->parseHandle(startAddr, rawData);
	}
}
#endif