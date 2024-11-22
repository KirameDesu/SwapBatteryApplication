/**
@file
Arduino library for communicating with Modbus slaves over RS232/485 (via RTU protocol).

@defgroup setup CustomModbusMaster Object Instantiation/Initialization
@defgroup buffer CustomModbusMaster Buffer Management
@defgroup discrete Modbus Function Codes for Discrete Coils/Inputs
@defgroup register Modbus Function Codes for Holding/Input Registers
@defgroup constant Modbus Function Codes, Exception Codes
*/
/*

  CustomModbusMaster.h - Arduino library for communicating with Modbus slaves
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


#ifndef CustomModbusMaster_h
#define CustomModbusMaster_h


/**
@def __MODBUSMASTER_DEBUG__ (0)
Set to 1 to enable debugging features within class:
  - PIN A cycles for each byte read in the Modbus response
  - PIN B cycles for each millisecond timeout during the Modbus response
*/
#define __MODBUSMASTER_DEBUG__ (0)
#define __MODBUSMASTER_DEBUG_PIN_A__ 4
#define __MODBUSMASTER_DEBUG_PIN_B__ 5


/* _____STANDARD INCLUDES____________________________________________________ */
// include types & constants of Wiring core API
//#include "Arduino.h"
#include "StreamType.h"

/* _____UTILITY MACROS_______________________________________________________ */

//typedef CustomStream Stream;
//#define Stream CustomStream

/* _____PROJECT INCLUDES_____________________________________________________ */
// functions to calculate Modbus Application Data Unit CRC
#include "util/crc16.h"

// functions to manipulate words
#include "util/word.h"

#include "typedef.h"

/* _____CLASS DEFINITIONS____________________________________________________ */
/**
Arduino class library for communicating with Modbus slaves over
RS232/485 (via RTU protocol).
*/
struct MassageSegment {
    uint8_t _u8MsgNo = 0;                  // 消息段序号
    uint16_t _u16SlaveDeviceID = 0;        // 报文接收设备ID
    uint8_t _u8FunCode = 0;
    uint16_t _u16MsgLen = 0;                // 消息段总字节数
    uint16_t _u16ReadAddress = 0;                                    ///< slave register from which to read
    uint16_t _u16ReadQty = 0;                                        ///< quantity of words to read
    uint16_t _u16WriteAddress = 0;                                   ///< slave register to which to write
    uint16_t _u16WriteQty = 0;                                       ///< quantity of words to write

    static const uint8_t ku8MaxBufferSize = 64;   ///< size of response/transmit buffers
    uint16_t _u16TransmitBuffer[ku8MaxBufferSize] = { 0 };               ///< buffer containing data to transmit to Modbus slave; set via SetTransmitBuffer()
    uint8_t _u8TransmitBufferIndex = 0;
    uint16_t u16TransmitBufferLength = 0;
    uint16_t _u16ResponseBuffer[ku8MaxBufferSize] = { 0 };               ///< buffer to store Modbus slave response; read via GetResponseBuffer()
    uint8_t _u8ResponseBufferIndex = 0;
    uint8_t _u8ResponseBufferLength = 0;
    bool _boolResponseState = false;
};

class StreamType;
using Stream = StreamType;
class CustomModbusMaster
{
public:
    CustomModbusMaster(Stream* serial);
    ~CustomModbusMaster();

    void begin(uint8_t);
    void idle(void (*)());
    void preTransmission(void (*)());
    void postTransmission(void (*)());
    uint8_t getResponseMsgNum();

    static const uint16_t ku16MaxADUSize = 1024;

    // Modbus exception codes
    /**
    Modbus protocol illegal function exception.

    The function code received in the query is not an allowable action for
    the server (or slave). This may be because the function code is only
    applicable to newer devices, and was not implemented in the unit
    selected. It could also indicate that the server (or slave) is in the
    wrong state to process a request of this type, for example because it is
    unconfigured and is being asked to return register values.

    @ingroup constant
    */
    static const uint8_t ku8MBIllegalFunction = 0x01;

    /**
    Modbus protocol illegal data address exception.

    The data address received in the query is not an allowable address for
    the server (or slave). More specifically, the combination of reference
    number and transfer length is invalid. For a controller with 100
    registers, the ADU addresses the first register as 0, and the last one
    as 99. If a request is submitted with a starting register address of 96
    and a quantity of registers of 4, then this request will successfully
    operate (address-wise at least) on registers 96, 97, 98, 99. If a
    request is submitted with a starting register address of 96 and a
    quantity of registers of 5, then this request will fail with Exception
    Code 0x02 "Illegal Data Address" since it attempts to operate on
    registers 96, 97, 98, 99 and 100, and there is no register with address
    100.

    @ingroup constant
    */
    static const uint8_t ku8MBIllegalDataAddress = 0x02;

    /**
    Modbus protocol illegal data value exception.

    A value contained in the query data field is not an allowable value for
    server (or slave). This indicates a fault in the structure of the
    remainder of a complex request, such as that the implied length is
    incorrect. It specifically does NOT mean that a data item submitted for
    storage in a register has a value outside the expectation of the
    application program, since the MODBUS protocol is unaware of the
    significance of any particular value of any particular register.

    @ingroup constant
    */
    static const uint8_t ku8MBIllegalDataValue = 0x03;

    /**
    Modbus protocol slave device failure exception.

    An unrecoverable error occurred while the server (or slave) was
    attempting to perform the requested action.

    @ingroup constant
    */
    static const uint8_t ku8MBSlaveDeviceFailure = 0x04;

    // Class-defined success/exception codes
    /**
    CustomModbusMaster success.

    Modbus transaction was successful; the following checks were valid:
      - slave ID
      - function code
      - response code
      - data
      - CRC

    @ingroup constant
    */
    static const uint8_t ku8MBSuccess = 0x00;

    /**
    CustomModbusMaster invalid response slave ID exception.

    The slave ID in the response does not match that of the request.

    @ingroup constant
    */
    static const uint8_t ku8MBInvalidSlaveID = 0xE0;

    /**
    CustomModbusMaster invalid response function exception.

    The function code in the response does not match that of the request.

    @ingroup constant
    */
    static const uint8_t ku8MBInvalidFunction = 0xE1;

    /**
    CustomModbusMaster response timed out exception.

    The entire response was not received within the timeout period,
    CustomModbusMaster::ku8MBResponseTimeout.

    @ingroup constant
    */
    static const uint8_t ku8MBResponseTimedOut = 0xE2;

    /**
    CustomModbusMaster invalid response CRC exception.

    The CRC in the response does not match the one calculated.

    @ingroup constant
    */
    static const uint8_t ku8MBInvalidCRC = 0xE3;

    // 非法报文结构
    static const uint8_t ku8MBInvalidFrame = 0xE4;

    uint16_t getResponseBuffer(uint8_t, uint8_t);
    uint8_t getResponseLenth(uint8_t);
    bool getResponseFuncResult(uint8_t);
    uint8_t getResponseFuncCode(uint8_t);
    uint16_t getRegisterStartAddr(uint8_t index);
    void     clearResponseBuffer(uint8_t);
    uint8_t  setTransmitBuffer(uint8_t, uint16_t);
    void     clearTransmitBuffer(uint8_t);

    void beginTransmission(uint16_t);
    //uint8_t requestFrom(uint16_t, uint16_t);
    //void sendBit(bool);
    //void send(uint8_t);
    //void send(uint16_t);
    //void send(uint32_t);
    //uint8_t available(void);
    //uint16_t receive(void);


    uint8_t  readCoils(uint16_t, uint16_t);
    bool appendWriteRegisters(uint16_t slave_id, uint16_t addr_start, uint16_t* write_arr, uint16_t write_len);
    bool appendReadRegisters(uint16_t slave_id, uint16_t addr_start, uint16_t read_num);
    uint8_t  readDiscreteInputs(uint16_t, uint16_t);
    uint8_t  readHoldingRegisters(uint16_t, uint16_t, uint16_t);
    uint8_t  readInputRegisters(uint16_t, uint8_t);
    uint8_t  writeSingleCoil(uint16_t, uint8_t);
    uint8_t  writeSingleRegister(uint16_t, uint16_t);
    uint8_t  writeMultipleCoils(uint16_t, uint16_t);
    uint8_t  writeMultipleCoils();
    uint8_t  writeMultipleRegisters(uint16_t, uint16_t, uint16_t);
    //uint8_t  writeMultipleRegisters();
    uint8_t  maskWriteRegister(uint16_t, uint16_t, uint16_t);
    uint8_t  readWriteMultipleRegisters(uint16_t, uint16_t, uint16_t, uint16_t);
    uint8_t  readWriteMultipleRegisters(uint16_t, uint16_t);

    uint8_t TransactionWithMsgNum();


private:
    Stream* _serial{ nullptr };                                             ///< reference to serial port object
    //uint8_t  _u8MBSlave=0;                                         ///< Modbus slave (1..255) initialized in begin()
    
    uint16_t* txBuffer{ nullptr }; // from Wire.h -- need to clean this up Rx
    uint16_t* rxBuffer{ nullptr }; // from Wire.h -- need to clean this up Rx

    /* 消息段外 */
    uint16_t _u16MasterDeviceID = 0x0001;        // 报文发起设备ID
    uint8_t _u8SendMsgNum = 0;          // 待发送报文消息段数量
    uint8_t _u8ResponseMsgNum = 0;          // 接收报文消息段数
    uint16_t _u16MsgCnt = 0;                // 消息段总字节数
    
    /* 消息段内 */
    static const uint8_t ku8MaxMsgBuffSize = 32;
    MassageSegment msgBuffer[ku8MaxMsgBuffSize];

    //Custom Modbus Protocol
    static const uint8_t ku8MBHead = 0x69;      // 报文头
    static const uint8_t ku8MBTail = 0xC3;      // 报文尾

    // Modbus function codes for bit access
    static const uint8_t ku8MBReadCoils = 0x01; ///< Modbus function 0x01 Read Coils
    static const uint8_t ku8MBReadDiscreteInputs = 0x02; ///< Modbus function 0x02 Read Discrete Inputs
    static const uint8_t ku8MBWriteSingleCoil = 0x05; ///< Modbus function 0x05 Write Single Coil
    static const uint8_t ku8MBWriteMultipleCoils = 0x0F; ///< Modbus function 0x0F Write Multiple Coils

    // Modbus function codes for 16 bit access
    static const uint8_t ku8MBReadHoldingRegisters = 0x03; ///< Modbus function 0x03 Read Holding Registers
    static const uint8_t ku8MBReadInputRegisters = 0x04; ///< Modbus function 0x04 Read Input Registers
    static const uint8_t ku8MBWriteSingleRegister = 0x06; ///< Modbus function 0x06 Write Single Register
    static const uint8_t ku8MBWriteMultipleRegisters = 0x10; ///< Modbus function 0x10 Write Multiple Registers
    static const uint8_t ku8MBMaskWriteRegister = 0x16; ///< Modbus function 0x16 Mask Write Register
    static const uint8_t ku8MBReadWriteMultipleRegisters = 0x17; ///< Modbus function 0x17 Read Write Multiple Registers

    // Modbus timeout [milliseconds]
    static const uint16_t ku16MBResponseTimeout = 5000; ///< Modbus timeout [milliseconds]

    // master function that conducts Modbus transactions
    uint8_t ModbusMasterTransaction();

    uint8_t ModbusMasterTransaction(uint8_t func);

    bool getResponseNextMsgStartIndex(uint8_t* msgArrStart, uint8_t& msgStartIndex);

    // idle callback function; gets called during idle time between TX and RX
    void (*_idle)();
    // preTransmission callback function; gets called before writing a Modbus message
    void (*_preTransmission)();
    // postTransmission callback function; gets called after a Modbus message has been sent
    void (*_postTransmission)();
};
#endif

/**
@example examples/Basic/Basic.pde
@example examples/PhoenixContact_nanoLC/PhoenixContact_nanoLC.pde
@example examples/RS485_HalfDuplex/RS485_HalfDuplex.ino
*/
