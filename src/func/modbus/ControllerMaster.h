#ifndef CONTROLLER_MASTER_H
#define CONTROLLER_MASTER_H

#include "StreamType.h"
#include "typedef.h"

class StreamType;
using Stream = StreamType;
class ControllerMaster
{
public:
    // 开始升级操作码
    static const uint8_t ku8CMDUpgradeStart = 0x9A;
    // 发送升级数据操作码
    static const uint8_t ku8CMDSendUpgradeData = 0x9B;
    // 结束升级操作码
    static const uint8_t ku8CMDEndUpgrade = 0x9C;

    static const uint8_t ku8MBSuccess = 0x00;

    void begin(uint8_t);
    void preTransmission(void (*)());
    void postTransmission(void (*)());

    uint16_t getResponseBuffer(uint8_t);
    void     clearResponseBuffer();
    uint8_t  setTransmitBuffer(uint8_t, uint16_t);
    void     clearTransmitBuffer();

    uint8_t ModbusMasterTransaction(uint8_t u8CMD);
private:
    uint8_t _u8SlaveDeviceID = 0x02;        // 报文从机设备ID

    static const uint16_t _u16Head = 0xEB90;
#if 0
    static const uint8_t ku8MaxBufferSize = 1024;   ///< size of response/transmit buffers    
    uint8_t _funcode = 0;                                   ///< slave register to which to write
    uint8_t _u8ResponseBuffer[ku8MaxBufferSize] = { 0 };               ///< buffer to store Modbus slave response; read via GetResponseBuffer()
    uint16_t _u16WriteQty = 0;                                       ///< quantity of words to write
    uint8_t _u8TransmitBuffer[ku8MaxBufferSize] = { 0 };               ///< buffer containing data to transmit to Modbus slave; set via SetTransmitBuffer()
    uint8_t _u8TransmitBufferIndex = 0;
    uint8_t _u8ResponseBufferIndex = 0;
#endif
    Stream* _streamHandle{ nullptr };

    uint8_t _getCheckSum(const uint8_t* addr, uint16_t dataLen);
};

#endif // !CONTROLLER_MASTER_H
