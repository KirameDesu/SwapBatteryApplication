#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

enum CMDRequestType
{
	read,
	write
};

struct ModbusRequest
{
	int id;

	CMDRequestType actionType;

	qint16 startAddr;
	int readDataLen;
	QByteArray dataArr;		// 写操作才会用到

	int time;		// 1970年时间戳, ms
};

struct ModbusResponse
{
	int id;

	int resultCode;

	qint16 startAddr;
	QByteArray responseData;
	int responseLen;

	int time;		// 1970年时间戳
};

#endif // !TYPEDEF_H
