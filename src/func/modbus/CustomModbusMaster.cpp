/**
@file
Arduino library for communicating with Modbus slaves over RS232/485 (via RTU protocol).
*/
/*

  CustomModbusMaster.cpp - Arduino library for communicating with Modbus slaves
  over RS232/485 (via RTU protocol).

  Library:: CustomModbusMaster

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/


/* _____PROJECT INCLUDES_____________________________________________________ */
#include "CustomModbusMaster.h"

#include "LoggerManager.h"
#include <qcoreapplication.h>
/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____PUBLIC FUNCTIONS_____________________________________________________ */
/**
Constructor.

Creates class object; initialize it using CustomModbusMaster::begin().

@ingroup setup
*/
CustomModbusMaster::CustomModbusMaster(Stream* serial)
{
    _idle = 0;
    _preTransmission = 0;
    _postTransmission = 0;
    _serial = serial;
}

CustomModbusMaster::~CustomModbusMaster()
{
}

/**
Initialize class object.

Assigns the Modbus slave ID and serial port.
Call once class has been instantiated, typically within setup().

@param slave Modbus slave ID (1..255)
@param &serial reference to serial port object (Serial, Serial1, ... Serial3)
@ingroup setup
*/
void CustomModbusMaster::begin(uint8_t slave)
{
    //  txBuffer = (uint16_t*) calloc(ku8MaxBufferSize, sizeof(uint16_t));
    _u8MBSlave = slave;
    _u8TransmitBufferIndex = 0;
    u16TransmitBufferLength = 0;

    LoggerManager::log("CustomModbus begin");

#if __MODBUSMASTER_DEBUG__
    pinMode(__MODBUSMASTER_DEBUG_PIN_A__, OUTPUT);
    pinMode(__MODBUSMASTER_DEBUG_PIN_B__, OUTPUT);
#endif
}


void CustomModbusMaster::beginTransmission(uint16_t u16Address)
{
    _u16WriteAddress = u16Address;
    _u8TransmitBufferIndex = 0;
    u16TransmitBufferLength = 0;
}

// eliminate this function in favor of using existing MB request functions
//uint8_t CustomModbusMaster::requestFrom(uint16_t address, uint16_t quantity)
//{
//    uint8_t read;
//    // clamp to buffer length
//    if (quantity > ku8MaxBufferSize)
//    {
//        quantity = ku8MaxBufferSize;
//    }
//    // set rx buffer iterator vars
//    _u8ResponseBufferIndex = 0;
//    _u8ResponseBufferLength = read;
//
//    return read;
//}


void CustomModbusMaster::sendBit(bool data)
{
    uint8_t txBitIndex = u16TransmitBufferLength % 16;
    if ((u16TransmitBufferLength >> 4) < ku8MaxBufferSize)
    {
        if (0 == txBitIndex)
        {
            _u16TransmitBuffer[_u8TransmitBufferIndex] = 0;
        }
        StreamType::bitWrite(_u16TransmitBuffer[_u8TransmitBufferIndex], txBitIndex, data);
        u16TransmitBufferLength++;
        _u8TransmitBufferIndex = u16TransmitBufferLength >> 4;
    }
}


void CustomModbusMaster::send(uint16_t data)
{
    if (_u8TransmitBufferIndex < ku8MaxBufferSize)
    {
        _u16TransmitBuffer[_u8TransmitBufferIndex++] = data;
        u16TransmitBufferLength = _u8TransmitBufferIndex << 4;
    }
}


void CustomModbusMaster::send(uint32_t data)
{
    send(lowWord(data));
    send(highWord(data));
}


void CustomModbusMaster::send(uint8_t data)
{
    // ��ȷ��������
    send(StreamType::word(data, 0));
}









uint8_t CustomModbusMaster::available(void)
{
    return _u8ResponseBufferLength - _u8ResponseBufferIndex;
}


uint16_t CustomModbusMaster::receive(void)
{
    if (_u8ResponseBufferIndex < _u8ResponseBufferLength)
    {
        return _u16ResponseBuffer[_u8ResponseBufferIndex++];
    }
    else
    {
        return 0xFFFF;
    }
}








/**
Set idle time callback function (cooperative multitasking).

This function gets called in the idle time between transmission of data
and response from slave. Do not call functions that read from the serial
buffer that is used by CustomModbusMaster. Use of i2c/TWI, 1-Wire, other
serial ports, etc. is permitted within callback function.

@see CustomModbusMaster::ModbusMasterTransaction()
*/
void CustomModbusMaster::idle(void (*idle)())
{
    _idle = idle;
}

/**
Set pre-transmission callback function.

This function gets called just before a Modbus message is sent over serial.
Typical usage of this callback is to enable an RS485 transceiver's
Driver Enable pin, and optionally disable its Receiver Enable pin.

@see CustomModbusMaster::ModbusMasterTransaction()
@see CustomModbusMaster::postTransmission()
*/
void CustomModbusMaster::preTransmission(void (*preTransmission)())
{
    _preTransmission = preTransmission;
}

/**
Set post-transmission callback function.

This function gets called after a Modbus message has finished sending
(i.e. after all data has been physically transmitted onto the serial
bus).

Typical usage of this callback is to enable an RS485 transceiver's
Receiver Enable pin, and disable its Driver Enable pin.

@see CustomModbusMaster::ModbusMasterTransaction()
@see CustomModbusMaster::preTransmission()
*/
void CustomModbusMaster::postTransmission(void (*postTransmission)())
{
    _postTransmission = postTransmission;
}


/**
Retrieve data from response buffer.

@see CustomModbusMaster::clearResponseBuffer()
@param u8Index index of response buffer array (0x00..0x3F)
@return value in position u8Index of response buffer (0x0000..0xFFFF)
@ingroup buffer
*/
uint16_t CustomModbusMaster::getResponseBuffer(uint8_t u8Index)
{
    if (u8Index < ku8MaxBufferSize)
    {
        return _u16ResponseBuffer[u8Index];
    }
    else
    {
        return 0xFFFF;
    }
}


/**
Clear Modbus response buffer.

@see CustomModbusMaster::getResponseBuffer(uint8_t u8Index)
@ingroup buffer
*/
void CustomModbusMaster::clearResponseBuffer()
{
    uint8_t i;

    for (i = 0; i < ku8MaxBufferSize; i++)
    {
        _u16ResponseBuffer[i] = 0;
    }
}


/**
Place data in transmit buffer.

@see CustomModbusMaster::clearTransmitBuffer()
@param u8Index index of transmit buffer array (0x00..0x3F)
@param u16Value value to place in position u8Index of transmit buffer (0x0000..0xFFFF)
@return 0 on success; exception number on failure
@ingroup buffer
*/
uint8_t CustomModbusMaster::setTransmitBuffer(uint8_t u8Index, uint16_t u16Value)
{
    if (u8Index < ku8MaxBufferSize)
    {
        _u16TransmitBuffer[u8Index] = u16Value;
        return ku8MBSuccess;
    }
    else
    {
        return ku8MBIllegalDataAddress;
    }
}


/**
Clear Modbus transmit buffer.

@see CustomModbusMaster::setTransmitBuffer(uint8_t u8Index, uint16_t u16Value)
@ingroup buffer
*/
void CustomModbusMaster::clearTransmitBuffer()
{
    uint8_t i;

    for (i = 0; i < ku8MaxBufferSize; i++)
    {
        _u16TransmitBuffer[i] = 0;
    }
}


/**
Modbus function 0x01 Read Coils.

This function code is used to read from 1 to 2000 contiguous status of
coils in a remote device. The request specifies the starting address,
i.e. the address of the first coil specified, and the number of coils.
Coils are addressed starting at zero.

The coils in the response buffer are packed as one coil per bit of the
data field. Status is indicated as 1=ON and 0=OFF. The LSB of the first
data word contains the output addressed in the query. The other coils
follow toward the high order end of this word and from low order to high
order in subsequent words.

If the returned quantity is not a multiple of sixteen, the remaining
bits in the final data word will be padded with zeros (toward the high
order end of the word).

@param u16ReadAddress address of first coil (0x0000..0xFFFF)
@param u16BitQty quantity of coils to read (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t CustomModbusMaster::readCoils(uint16_t u16ReadAddress, uint16_t u16BitQty)
{
    _u16ReadAddress = u16ReadAddress;
    _u16ReadQty = u16BitQty;
    return ModbusMasterTransaction(ku8MBReadCoils);
}


/**
Modbus function 0x02 Read Discrete Inputs.

This function code is used to read from 1 to 2000 contiguous status of
discrete inputs in a remote device. The request specifies the starting
address, i.e. the address of the first input specified, and the number
of inputs. Discrete inputs are addressed starting at zero.

The discrete inputs in the response buffer are packed as one input per
bit of the data field. Status is indicated as 1=ON; 0=OFF. The LSB of
the first data word contains the input addressed in the query. The other
inputs follow toward the high order end of this word, and from low order
to high order in subsequent words.

If the returned quantity is not a multiple of sixteen, the remaining
bits in the final data word will be padded with zeros (toward the high
order end of the word).

@param u16ReadAddress address of first discrete input (0x0000..0xFFFF)
@param u16BitQty quantity of discrete inputs to read (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t CustomModbusMaster::readDiscreteInputs(uint16_t u16ReadAddress,
    uint16_t u16BitQty)
{
    _u16ReadAddress = u16ReadAddress;
    _u16ReadQty = u16BitQty;
    return ModbusMasterTransaction(ku8MBReadDiscreteInputs);
}


/**
Modbus function 0x03 Read Holding Registers.

This function code is used to read the contents of a contiguous block of
holding registers in a remote device. The request specifies the starting
register address and the number of registers. Registers are addressed
starting at zero.

The register data in the response buffer is packed as one word per
register.

@param u16ReadAddress address of the first holding register (0x0000..0xFFFF)
@param u16ReadQty quantity of holding registers to read (1..125, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t CustomModbusMaster::readHoldingRegisters(uint16_t u16ReadAddress,
    uint16_t u16ReadQty)
{
    _u16ReadAddress = u16ReadAddress;
    _u16ReadQty = u16ReadQty;
    return ModbusMasterTransaction(ku8MBReadHoldingRegisters);
}


/**
Modbus function 0x04 Read Input Registers.

This function code is used to read from 1 to 125 contiguous input
registers in a remote device. The request specifies the starting
register address and the number of registers. Registers are addressed
starting at zero.

The register data in the response buffer is packed as one word per
register.

@param u16ReadAddress address of the first input register (0x0000..0xFFFF)
@param u16ReadQty quantity of input registers to read (1..125, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t CustomModbusMaster::readInputRegisters(uint16_t u16ReadAddress,
    uint8_t u16ReadQty)
{
    _u16ReadAddress = u16ReadAddress;
    _u16ReadQty = u16ReadQty;
    return ModbusMasterTransaction(ku8MBReadInputRegisters);
}


/**
Modbus function 0x05 Write Single Coil.

This function code is used to write a single output to either ON or OFF
in a remote device. The requested ON/OFF state is specified by a
constant in the state field. A non-zero value requests the output to be
ON and a value of 0 requests it to be OFF. The request specifies the
address of the coil to be forced. Coils are addressed starting at zero.

@param u16WriteAddress address of the coil (0x0000..0xFFFF)
@param u8State 0=OFF, non-zero=ON (0x00..0xFF)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t CustomModbusMaster::writeSingleCoil(uint16_t u16WriteAddress, uint8_t u8State)
{
    _u16WriteAddress = u16WriteAddress;
    _u16WriteQty = (u8State ? 0xFF00 : 0x0000);
    return ModbusMasterTransaction(ku8MBWriteSingleCoil);
}


/**
Modbus function 0x06 Write Single Register.

This function code is used to write a single holding register in a
remote device. The request specifies the address of the register to be
written. Registers are addressed starting at zero.

@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16WriteValue value to be written to holding register (0x0000..0xFFFF)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t CustomModbusMaster::writeSingleRegister(uint16_t u16WriteAddress,
    uint16_t u16WriteValue)
{
    _u16WriteAddress = u16WriteAddress;
    _u16WriteQty = 0;
    _u16TransmitBuffer[0] = u16WriteValue;
    return ModbusMasterTransaction(ku8MBWriteSingleRegister);
}


/**
Modbus function 0x0F Write Multiple Coils.

This function code is used to force each coil in a sequence of coils to
either ON or OFF in a remote device. The request specifies the coil
references to be forced. Coils are addressed starting at zero.

The requested ON/OFF states are specified by contents of the transmit
buffer. A logical '1' in a bit position of the buffer requests the
corresponding output to be ON. A logical '0' requests it to be OFF.

@param u16WriteAddress address of the first coil (0x0000..0xFFFF)
@param u16BitQty quantity of coils to write (1..2000, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup discrete
*/
uint8_t CustomModbusMaster::writeMultipleCoils(uint16_t u16WriteAddress,
    uint16_t u16BitQty)
{
    _u16WriteAddress = u16WriteAddress;
    _u16WriteQty = u16BitQty;
    return ModbusMasterTransaction(ku8MBWriteMultipleCoils);
}
uint8_t CustomModbusMaster::writeMultipleCoils()
{
    _u16WriteQty = u16TransmitBufferLength;
    return ModbusMasterTransaction(ku8MBWriteMultipleCoils);
}


/**
Modbus function 0x10 Write Multiple Registers.

This function code is used to write a block of contiguous registers (1
to 123 registers) in a remote device.

The requested written values are specified in the transmit buffer. Data
is packed as one word per register.

@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16WriteQty quantity of holding registers to write (1..123, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t CustomModbusMaster::writeMultipleRegisters(uint16_t u16WriteAddress,
    uint16_t u16WriteQty)
{
    _u16WriteAddress = u16WriteAddress;
    _u16WriteQty = u16WriteQty;
    return ModbusMasterTransaction(ku8MBWriteMultipleRegisters);
}

// new version based on Wire.h
uint8_t CustomModbusMaster::writeMultipleRegisters()
{
    _u16WriteQty = _u8TransmitBufferIndex;
    return ModbusMasterTransaction(ku8MBWriteMultipleRegisters);
}


/**
Modbus function 0x16 Mask Write Register.

This function code is used to modify the contents of a specified holding
register using a combination of an AND mask, an OR mask, and the
register's current contents. The function can be used to set or clear
individual bits in the register.

The request specifies the holding register to be written, the data to be
used as the AND mask, and the data to be used as the OR mask. Registers
are addressed starting at zero.

The function's algorithm is:

Result = (Current Contents && And_Mask) || (Or_Mask && (~And_Mask))

@param u16WriteAddress address of the holding register (0x0000..0xFFFF)
@param u16AndMask AND mask (0x0000..0xFFFF)
@param u16OrMask OR mask (0x0000..0xFFFF)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t CustomModbusMaster::maskWriteRegister(uint16_t u16WriteAddress,
    uint16_t u16AndMask, uint16_t u16OrMask)
{
    _u16WriteAddress = u16WriteAddress;
    _u16TransmitBuffer[0] = u16AndMask;
    _u16TransmitBuffer[1] = u16OrMask;
    return ModbusMasterTransaction(ku8MBMaskWriteRegister);
}


/**
Modbus function 0x17 Read Write Multiple Registers.

This function code performs a combination of one read operation and one
write operation in a single MODBUS transaction. The write operation is
performed before the read. Holding registers are addressed starting at
zero.

The request specifies the starting address and number of holding
registers to be read as well as the starting address, and the number of
holding registers. The data to be written is specified in the transmit
buffer.

@param u16ReadAddress address of the first holding register (0x0000..0xFFFF)
@param u16ReadQty quantity of holding registers to read (1..125, enforced by remote device)
@param u16WriteAddress address of the first holding register (0x0000..0xFFFF)
@param u16WriteQty quantity of holding registers to write (1..121, enforced by remote device)
@return 0 on success; exception number on failure
@ingroup register
*/
uint8_t CustomModbusMaster::readWriteMultipleRegisters(uint16_t u16ReadAddress,
    uint16_t u16ReadQty, uint16_t u16WriteAddress, uint16_t u16WriteQty)
{
    _u16ReadAddress = u16ReadAddress;
    _u16ReadQty = u16ReadQty;
    _u16WriteAddress = u16WriteAddress;
    _u16WriteQty = u16WriteQty;
    return ModbusMasterTransaction(ku8MBReadWriteMultipleRegisters);
}
uint8_t CustomModbusMaster::readWriteMultipleRegisters(uint16_t u16ReadAddress,
    uint16_t u16ReadQty)
{
    _u16ReadAddress = u16ReadAddress;
    _u16ReadQty = u16ReadQty;
    _u16WriteQty = _u8TransmitBufferIndex;
    return ModbusMasterTransaction(ku8MBReadWriteMultipleRegisters);
}


/* _____PRIVATE FUNCTIONS____________________________________________________ */
/**
Modbus transaction engine.
Sequence:
  - assemble Modbus Request Application Data Unit (ADU),
    based on particular function called
  - transmit request over selected serial port
  - wait for/retrieve response
  - evaluate/disassemble response
  - return status (success/exception)

@param u8MBFunction Modbus function (0x01..0xFF)
@return 0 on success; exception number on failure
*/
uint8_t CustomModbusMaster::ModbusMasterTransaction(uint8_t u8MBFunction)
{
    uint8_t u8ModbusADU[1024];
    uint8_t u8ModbusADUSize = 0;
    uint8_t i, u8Qty;
    uint16_t u16CRC;
    uint32_t u32StartTime;
    uint8_t u8BytesLeft = 9;
    uint8_t u8MsgsLeft = 1;         // ��ʣ���ٸ���Ϣ����Ҫ����
    uint8_t u8MBStatus = ku8MBSuccess;
    
    // ��֯ͷ��
    u8ModbusADU[u8ModbusADUSize++] = ku8MBHead;
    u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(_u16MasterDeviceID);
    u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(_u16MasterDeviceID);
    u8ModbusADU[u8ModbusADUSize++] = _u8MsgNum;
    u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(_u16MsgLen);
    u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(_u16MsgLen);

    // ������Ϣ��


    //// assemble Modbus Request Application Data Unit
    //u8ModbusADU[u8ModbusADUSize++] = _u8MBSlave;
    //u8ModbusADU[u8ModbusADUSize++] = u8MBFunction;
    for (int u8Tmp1 = 0; u8Tmp1 < _u8MsgNum; ++u8Tmp1) {
        switch (u8MBFunction)
        {
            case ku8MBReadCoils:
            case ku8MBReadDiscreteInputs:
            case ku8MBReadInputRegisters:
            case ku8MBReadHoldingRegisters:
            case ku8MBReadWriteMultipleRegisters:
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16ReadAddress);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16ReadAddress);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16ReadQty);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16ReadQty);
                break;
        }

        switch (u8MBFunction)
        {
            case ku8MBWriteSingleCoil:
            case ku8MBMaskWriteRegister:
            case ku8MBWriteMultipleCoils:
            case ku8MBWriteSingleRegister:
            case ku8MBWriteMultipleRegisters:
            case ku8MBReadWriteMultipleRegisters:
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16WriteAddress);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16WriteAddress);
                break;
        }

        switch (u8MBFunction)
        {
            case ku8MBWriteSingleCoil:
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16WriteQty);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16WriteQty);
                break;

            case ku8MBWriteSingleRegister:
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[0]);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[0]);
                break;

            case ku8MBWriteMultipleCoils:
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16WriteQty);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16WriteQty);
                u8Qty = (msgBuffer[u8Tmp1]._u16WriteQty % 8) ? ((msgBuffer[u8Tmp1]._u16WriteQty >> 3) + 1) : (msgBuffer[u8Tmp1]._u16WriteQty >> 3);
                u8ModbusADU[u8ModbusADUSize++] = u8Qty;
                for (i = 0; i < u8Qty; i++)
                {
                    switch (i % 2)
                    {
                    case 0: // i is even
                        u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[i >> 1]);
                        break;

                    case 1: // i is odd
                        u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[i >> 1]);
                        break;
                    }
                }
                break;

            case ku8MBWriteMultipleRegisters:
            case ku8MBReadWriteMultipleRegisters:
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16WriteQty);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16WriteQty);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16WriteQty << 1);

                for (i = 0; i < StreamType::lowByte(msgBuffer[u8Tmp1]._u16WriteQty); i++)
                {
                    u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[i]);
                    u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[i]);
                }
                break;

            case ku8MBMaskWriteRegister:
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[0]);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[0]);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[1]);
                u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(msgBuffer[u8Tmp1]._u16TransmitBuffer[1]);
                break;
        }

        // append CRC
        u16CRC = 0xFFFF;
        for (i = 0; i < u8ModbusADUSize; i++)
        {
            u16CRC = crc16_update(u16CRC, u8ModbusADU[i]);
        }
        u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(u16CRC);
        u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(u16CRC);
    }

    // ����β��CRC�ͽ�����
    for (i = 0; i < u8ModbusADUSize; i++)
    {
        u16CRC = crc16_update(u16CRC, u8ModbusADU[i]);
    }
    u8ModbusADU[u8ModbusADUSize++] = StreamType::lowByte(u16CRC);
    u8ModbusADU[u8ModbusADUSize++] = StreamType::highByte(u16CRC);
    u8ModbusADU[u8ModbusADUSize++] = ku8MBTail;


    // flush receive buffer before transmitting request
#if 0
    while (_serial->read() != -1);
#else
    if (_serial->getConnect()->bytesAvailable() > 0)
        _serial->getConnect()->readAll();
#endif

    // transmit request
    if (_preTransmission)
    {
        _preTransmission();
    }

    _serial->dataWrite(u8ModbusADU, u8ModbusADUSize);

    u8ModbusADUSize = 0;
    _serial->getConnect()->flush();    // flush transmit buffer
    if (_postTransmission)
    {
        _postTransmission();
    }

    uint8_t delta = 0;
    uint16_t msgByteNum = 0;
    // loop until we run out of time or bytes, or an error occurs
    u32StartTime = StreamType::millis();
    while (u8BytesLeft && u8MsgsLeft && !u8MBStatus)
    {
        QCoreApplication::processEvents();  // �����¼�ѭ�����������¼�
        // TODO: �����������
        if (_serial->getConnect()->bytesAvailable() > 0)
        {
#if __MODBUSMASTER_DEBUG__
            digitalWrite(__MODBUSMASTER_DEBUG_PIN_A__, true);
#endif
            u8ModbusADU[u8ModbusADUSize++] = _serial->getConnect()->readByte();
            u8BytesLeft--;
#if __MODBUSMASTER_DEBUG__
            digitalWrite(__MODBUSMASTER_DEBUG_PIN_A__, false);
#endif
#if 0       // �Ƿ������н���ģʽ
            if (u8ModbusADU[u8ModbusADUSize++] != ku8MBHead)
            {
                u8ModbusADUSize = 0;
                u8BytesLeft = 9;
            }
#endif
        }
        else
        {
#if __MODBUSMASTER_DEBUG__
            digitalWrite(__MODBUSMASTER_DEBUG_PIN_B__, true);
#endif
            if (_idle)
            {
                _idle();
            }
#if __MODBUSMASTER_DEBUG__
            digitalWrite(__MODBUSMASTER_DEBUG_PIN_B__, false);
#endif
        }

        // ���յ���6���ֽ�ʱ
        if (u8ModbusADUSize == 6)
        {
            // ���ͷ
            if (u8ModbusADU[0] != ku8MBHead)
            {
                u8MBStatus = ku8MBInvalidFrame;
                break;
            }
            /// ��鷢���豸 (�Ƿ���Ҫ???)

            // ��ֵ��Ϣ
            u8MsgsLeft = u8ModbusADU[3];
            msgByteNum = StreamType::word(u8ModbusADU[4], u8ModbusADU[5]);
            u8BytesLeft = (msgByteNum + 3);
        }
        
        // ����MsgN��Data lenΪֹ
        if (u8ModbusADUSize == 6 + 8 + delta)
        {
            // Msg����Ƿ���ȷ
            if (msgByteNum - u8MsgsLeft != u8ModbusADU[5 + 1 + delta] - 1)
            {
                u8MBStatus = ku8MBInvalidFrame;
                break;
            }

            u8MsgsLeft--;       /// ���ܲ�����Ҫ,��Ϊ�ܽ��ܸ����Ѿ�ȷ��
            // ��������
            delta += StreamType::word(u8ModbusADU[5 + 7 + delta], u8ModbusADU[5 + 7 + delta]);
        }

        /// �Ƿ���Ҫ�ڳ�ʱʱ���ڽ��������з��͵Ĳ�����???

        if ((StreamType::millis() - u32StartTime) > ku16MBResponseTimeout)
        {
            u8MBStatus = ku8MBResponseTimedOut;
            LoggerManager::log("Ӧ��ʱ");
        }
    }


    // �������CRC
    if (!u8MBStatus && u8ModbusADUSize >= 9)
    {
        // calculate CRC
        u16CRC = 0xFFFF;
        for (i = 0; i < (u8ModbusADUSize - 4); i++)
        {
            u16CRC = crc16_update(u16CRC, u8ModbusADU[1 + i]);
        }

        // verify CRC
        if (!u8MBStatus && (StreamType::lowByte(u16CRC) != u8ModbusADU[u8ModbusADUSize - 3] ||
            StreamType::highByte(u16CRC) != u8ModbusADU[u8ModbusADUSize - 2]))
        {
            u8MBStatus = ku8MBInvalidCRC;
        }
    }

    // disassemble ADU into words
    if (!u8MBStatus)
    {
        delta = 0;
        while (msgByteNum--)
        {
            // �����ΪӦ���ΪĿ���豸
            if (!StreamType::bitRead(u8ModbusADU[5 + 4 + delta], 6) || _u16MasterDeviceID != StreamType::word(u8ModbusADU[5 + 5 + delta], u8ModbusADU[5 + 6 + delta]))
            {
                continue;
            }

            // ���msg��CRC

            // evaluate returned Modbus function code
            switch (u8ModbusADU[5 + 4 + delta])
            {
                case ku8MBReadCoils:
                case ku8MBReadDiscreteInputs:
                    // ���Ӧ��ɹ�
                    if (StreamType::bitRead(u8ModbusADU[5 + 4 + delta], 7)) {
                        // load bytes into word; response bytes are ordered L, H, L, H, ...
                        for (i = 0; i < StreamType::word(u8ModbusADU[5 + 7 + delta], u8ModbusADU[5 + 8 + delta]) >> 1; i++)
                        {
                            /// ���ձ����Ƿ���Ҫ��Ӧ���ѷ��͹�����
                            if (i < msgBuffer[msgByteNum].ku8MaxBufferSize)
                            {
                                msgBuffer[msgByteNum]._u16ResponseBuffer[i] = StreamType::word(u8ModbusADU[5 + 9 + 2 * i + delta], u8ModbusADU[5 + 10 + 2 * i + delta]);
                            }

                            msgBuffer[msgByteNum]._u8ResponseBufferLength = i;
                        }

                        // ����ֽ�����Ϊż��
                        if (StreamType::word(u8ModbusADU[5 + 7 + delta], u8ModbusADU[5 + 8 + delta] % 2))
                        {
                            if (i < msgBuffer[msgByteNum].ku8MaxBufferSize)
                            {
                                msgBuffer[msgByteNum]._u16ResponseBuffer[i] = StreamType::word(u8ModbusADU[2 * i + 3], 0);
                            }

                            msgBuffer[msgByteNum]._u8ResponseBufferLength = i + 1;
                        }
                        break;
                    }
                    

                case ku8MBReadInputRegisters:
                case ku8MBReadHoldingRegisters:
                case ku8MBReadWriteMultipleRegisters:
                    if (StreamType::bitRead(u8ModbusADU[5 + 4 + delta], 7)) {
                        // load bytes into word; response bytes are ordered H, L, H, L, ...
                        for (i = 0; i < StreamType::word(u8ModbusADU[5 + 7 + delta], u8ModbusADU[5 + 8 + delta]) >> 1; i++)
                        {
                            if (i < msgBuffer[msgByteNum].ku8MaxBufferSize)
                            {
                                msgBuffer[msgByteNum]._u16ResponseBuffer[i] = StreamType::word(u8ModbusADU[2 * i + 3], u8ModbusADU[2 * i + 4]);
                            }

                            msgBuffer[msgByteNum]._u8ResponseBufferLength = i;
                        }
                        break;
                    }
                    else {
                        
                    }
            }
            // ��������
            delta += StreamType::word(u8ModbusADU[5 + 7 + delta], u8ModbusADU[5 + 7 + delta]);
            /// ����״̬
            msgBuffer[msgByteNum]._u8TransmitBufferIndex = 0;
            msgBuffer[msgByteNum].u16TransmitBufferLength = 0;
            msgBuffer[msgByteNum]._u8ResponseBufferIndex = 0;
        }
    }


    /// �Ƴ��Ѿ����յ�Ӧ��ı��Ķ���???


    return u8MBStatus;
}