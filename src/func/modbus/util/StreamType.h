﻿/*
filename:StreamType.h
describe:用于适配QT框架
*/

#ifndef STREAM_TYPE_H
#define STREAM_TYPE_H

#include "AbstractCommunication.h"

//#include "TimerManager.h"

class StreamType
{
public:
	explicit StreamType(AbstractCommunication* parent = nullptr);
	~StreamType();

	//int8_t read();
	void dataWrite(uint8_t* u8Arr, uint16_t arrLen);
	int32_t available();

	static void bitWrite(uint16_t& u8Val, uint8_t bit, bool val);
	static bool bitRead(uint8_t u8Val, uint8_t bit);
	static uint16_t word(uint8_t u8Low, uint8_t u8High);
	static uint8_t highByte(uint16_t u16Val);
	static uint8_t lowByte(uint16_t u16Val);

	static uint32_t millis();

	AbstractCommunication* getConnect();
private:
	AbstractCommunication* _con;
};


#endif // !CUSTOM_STREAM_H
