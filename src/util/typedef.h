﻿#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QByteArray>

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

#define REQUEST_DATA_GROUP_MAX 16
struct ModbusRequest
{
	int id;

	CMDRequestType actionType;

	int gourpNum;
	qint16 startAddr[REQUEST_DATA_GROUP_MAX];
	int readDataLen[REQUEST_DATA_GROUP_MAX];
	QByteArray dataArr;		// 写操作才会用到

	int time;		// 1970年时间戳, ms
};

struct RawDataRequest
{
	int id;
	QByteArray rawData;
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
