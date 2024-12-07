#include "ControllerMaster.h"

uint8_t ControllerMaster::ModbusMasterTransaction(uint8_t u8CMD)
{
    uint8_t u8ModbusADU[2048];
    uint8_t u8ADUSize = 0;
    uint8_t i, u8Qty;
    uint8_t u8CheckSum;
    uint32_t u32StartTime;
    uint8_t u8BytesLeft = 8;
    uint8_t u8MBStatus = ku8MBSuccess;

    // assemble Modbus Request Application Data Unit
    u8ModbusADU[u8ADUSize++] = StreamType::highByte(_u16Head);
    u8ModbusADU[u8ADUSize++] = StreamType::lowByte(_u16Head);
    u8ModbusADU[u8ADUSize++] =_u8SlaveDeviceID;
    u8ModbusADU[u8ADUSize++] = u8CMD;

    switch (u8CMD)
    {
    case ku8CMDUpgradeStart:
        memcpy(u8ModbusADU + u8ADUSize, _u8TransmitBuffer, _u8TransmitBufferIndex);
        u8ADUSize += _u8TransmitBufferIndex;
    case ku8CMDSendUpgradeData:
    case ku8CMDEndUpgrade:
    default:
        break;
    }

    u8CheckSum = _getCheckSum(u8ModbusADU + 2, u8ADUSize - 2);
    u8ModbusADU[u8ADUSize++] = u8CheckSum;

    // 发送

    // 阻塞接收

    // 解析应答

	return 0;
}

uint8_t ControllerMaster::_getCheckSum(const uint8_t* addr, uint16_t dataLen)
{
    int i;
    uint16_t iSum = 0;
    for (i = 0; i < dataLen; ++i)
    {
        iSum += addr[i];
    }
    iSum %= 0x0100;
    return (uint8_t)(iSum & 0x00FF);
}
