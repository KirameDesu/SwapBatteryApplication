#include "BMSCmdManager.h"

#include "LoggerManager.h"

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