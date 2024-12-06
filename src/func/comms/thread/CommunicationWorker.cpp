#include "CommunicationWorker.h"

#include <QDateTime>
#include <QTimer>

#include "LoggerManager.h"


QString CommunicationWorker::getLastComunicationInfo()
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

int CommunicationWorker::_sendModbusRequest(ModbusRequest* r) {
    r->time = QDateTime::currentDateTime().toMSecsSinceEpoch();

    _customModbusMaster->begin(1);
    switch (r->actionType) {
    case CMDRequestType::read:  
        for (int i = 0; i < r->gourpNum; ++i)
            _customModbusMaster->appendReadRegisters(0x0001, r->startAddr[i], r->readDataLen[i]);
        break;
    case CMDRequestType::write:
        for (int i = 0; i < r->gourpNum; ++i)
            _customModbusMaster->appendWriteRegisters(0x0001, r->startAddr[i], reinterpret_cast<unsigned short*>(r->dataArr.data()), r->dataArr.size());
    }
    try {
        return _customModbusMaster->TransactionWithMsgNum();
    } catch (AbstractCommunication::PointerException e) {
        emit errorOccurred(e.what());
        return 0xFFFF;
    }
}

void CommunicationWorker::processRequest(ModbusRequest* request, int retries = 0)
{
    if (request == nullptr)
        return;

    if (retries < MAX_RETRIES) {
        _lastComunicationResult = _sendModbusRequest(request);
        if (_lastComunicationResult == 0) {
            processResponse();
            LoggerManager::logWithTime(getLastComunicationInfo());
            int elapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - request->time;
            LoggerManager::log(QString("*************Communication Elapsed Time: %1ms*************").arg(elapsedTime));
            // 继续处理队列中的下一个请求
            emit SendDequeueMessage();
            // 释放request
            emit deleteRequest(request);

            return;  // 发送成功，结束处理
        }
        // 返回值为0xFFFF则表示通讯未连接，则不重试
        else if (_lastComunicationResult == 0xFFFF)
        {
            processRequest(request, MAX_RETRIES);
        }
        else {
            // 如果发送失败，使用 QTimer 进行延迟重试
            LoggerManager::logWithTime(QString(__FUNCTION__) + ": 发送失败，准备重试 " + QString::number(retries + 1));
            QTimer::singleShot(RETRY_DELAY, this, [this, request, retries]() {
                processRequest(request, retries + 1);
                });
        }
    }
    else {
        // 达到最大重试次数，记录错误
        LoggerManager::logWithTime(QString(__FUNCTION__) + ": 重试次数已达上限，发送失败");

        // 释放request
        emit deleteRequest(request);

        // 继续处理队列中的下一个请求，即使失败也不阻塞后续处理
        emit SendDequeueMessage();
    }
}

void CommunicationWorker::processResponse() {
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
