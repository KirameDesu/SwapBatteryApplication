#include "AbstractCommunication.h"

#include "TimerManager.h"
#include "Util.h"

AbstractCommunication::AbstractCommunication(QObject* parent)
	: QObject(parent), settingWidget(nullptr)
{
}

quint8 AbstractCommunication::sendProcess(const QByteArray& rawData)
{
    int ADUSize = 0;
    int startTime;
    quint8 processStatus = 0x00;        // 为0表示正常
    bool isRecvEnd = false;
    int bytesLeft = 0;
    quint8 u8CheckSum;

    // 发送前清空下缓冲区
    if (bytesAvailable() > 0)
    {
        readAll();
    }
    // 发送数据
    write(rawData);
    // 强制写缓冲区
    if (!flush())
    {
        qDebug() << "[ERROR]flush() called failed...";
        throw std::runtime_error("flush() called failed");
    }

    startTime = TimerManager::instance().elapsed();
    bytesLeft = 6;
    while (bytesLeft && !processStatus)
    {
        if (bytesAvailable() > 0)
        {
            _u8ADUBuff[ADUSize++] = readByte();
            bytesLeft--;
        }

        // 接收到第6个字节
        if (ADUSize == 6)
            bytesLeft = _u8ADUBuff[4];  // 更新剩余接收字节数

        // 超时时间2s
        if ((TimerManager::instance().elapsed() - startTime) > 2000)
        {
            processStatus = ku8TimeOut;
        }
    }

    // 检查CRC
    if (!processStatus)
    {
        u8CheckSum = Util::getCheckSum(_u8ADUBuff + 2, ADUSize - 3);
        if (u8CheckSum != _u8ADUBuff[ADUSize - 1])
        {
            processStatus = ku8InvildCRC;
        }
    }

    // 接收成功, 将接收原始数组放入QByteArray
    if (!processStatus)
    {
        _recvByteArray.clear();
        _recvByteArray.append(reinterpret_cast<char*>(_u8ADUBuff), static_cast<int>(ADUSize));
    }

	return processStatus;
}

const QByteArray& AbstractCommunication::getRecvArray() const
{
    return _recvByteArray;
}

