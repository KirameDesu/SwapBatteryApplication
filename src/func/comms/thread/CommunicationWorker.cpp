#include "CommunicationWorker.h"

#include <QDateTime>
#include <QTimer>
//#include <QMutexLocker>

#include "LoggerManager.h"
#include "ElaMessageBar.h"
#include "TimerManager.h"
#include "ControlProtocol.h"


CommunicationWorker::CommunicationWorker(CustomModbusMaster* customModbusMaster, ModelManager* model)
    : _customModbusMaster(customModbusMaster), _model(model)
{
    if (_customModbusMaster != nullptr)
    {
        _communication = _customModbusMaster->getStream()->getConnect();
    }
}

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

/// 暂时直接实现发送到接收的流程
int CommunicationWorker::_sendRawDataRequest(RawDataRequest* r) {
    r->time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    
    // 临时检查一下能否转换成串口通讯派生类指针
    //dynamic_cast<Derived*>(basePtr)
    try {
        return _communication->sendProcess(r->rawData);
    }
    catch (AbstractCommunication::PointerException e)
    {
        emit errorOccurred(e.what());
        return 0xFFFF;
    }
}


void CommunicationWorker::processRequest(ModbusRequest* request, int retries = 0)
{
    if (request == nullptr)
    {
        emit errorOccurred("Request Pointer is NULL");
        return;
    }

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
            /// 似乎可以直接return
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
        emit errorOccurred("通讯重试超时");

        // 释放request
        emit deleteRequest(request);

        // 继续处理队列中的下一个请求，即使失败也不阻塞后续处理
        emit SendDequeueMessage();
    }
}

void CommunicationWorker::processRawDataRequest(RawDataRequest* request, int retries = 0)
{
    /// 避免多次调用
    //QMutexLocker locker(&mutex);

    if (request == nullptr)
    {
        emit errorOccurred("Request Pointer is NULL");
        return;
    }

    // 解析原始数据
    if (retries < MAX_RETRIES) {
        _lastComunicationResult = _sendRawDataRequest(request);
        if (_lastComunicationResult == 0) {
            processRawData();
            LoggerManager::logWithTime(getLastComunicationInfo());
            int elapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - request->time;
            LoggerManager::log(QString("*************Communication Elapsed Time: %1ms*************").arg(elapsedTime));
            // 继续处理队列中的下一个请求
            //emit SendDequeuRawData();     /// 改为由解析函数中来触发下一段报文
            // 释放request
            emit deleteRawRequest(request);

            return;  // 发送成功，结束处理
        }
        // 返回值为0xFFFF则表示通讯未连接，则不重试
        else if (_lastComunicationResult == 0xFFFF)
        {
            processRawDataRequest(request, MAX_RETRIES);
        }
        else {
            // 如果发送失败，使用 QTimer 进行延迟重试
            LoggerManager::logWithTime(QString(__FUNCTION__) + ": 发送失败，准备重试 " + QString::number(retries + 1));
            QTimer::singleShot(RETRY_DELAY, this, [this, request, retries]() {
                processRawDataRequest(request, retries + 1);
                });
        }
    }
    else {
        // 达到最大重试次数，记录错误
        LoggerManager::logWithTime(QString(__FUNCTION__) + ": 重试次数已达上限，发送失败");
        emit errorOccurred("通讯重试超时");

        // 释放request
        emit deleteRawRequest(request);

        // 继续处理队列中的下一个请求，即使失败也不阻塞后续处理
        emit SendDequeuRawData();
    }
}

void CommunicationWorker::setProtocol(BaseProtocol* protocol)
{
    _protocol = protocol;
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

/// 临时
void CommunicationWorker::processRawData() {
    if (_protocol == nullptr || _communication == nullptr)
        throw std::runtime_error(std::string(__FUNCTION__) + ": _protocol or _communication is nullptr");

    QByteArray rawData = _communication->getRecvArray();
    LoggerManager::logWithTime("接收<--" + rawData.toHex(' '));

    BaseProtocol::parseResult ret;
    ret = _protocol->responseHandle(rawData);
    if (ret != BaseProtocol::parseResult::Success)
    {
        switch (ret)
        {
        case BaseProtocol::parseResult::ArrayIsEmpty:
            emit errorOccurred("接收报文为空");
            break;
        case BaseProtocol::parseResult::InvalidHead:
            emit errorOccurred("接收报文结构无效");
            break;
        case BaseProtocol::parseResult::InvalidLength:
            emit errorOccurred("接收报文结构无效");
            break;
        case BaseProtocol::parseResult::InvalidCRC:
            emit errorOccurred("接收报文校验失败");
            break;
        case BaseProtocol::parseResult::InvalidPackNo:
            emit errorOccurred("应答升级包序号无效");
            break;
        default:
            emit errorOccurred("未知错误");
            break;
        }
    }
}
