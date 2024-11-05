/*
filename:CustomStream.h
describe:用于适配QT框架
*/

#ifndef CUSTOM_STREAM_H
#define CUSTOM_STREAM_H

#include <QtSerialPort/QSerialPort>

//#include "TimerManager.h"

class CustomStream : public QSerialPort
{
public:
	explicit CustomStream(QSerialPort* parent = nullptr);
	~CustomStream();

	int8_t read();
	void write(uint8_t* u8Arr, uint16_t arrLen);
	bool available();

	static void bitWrite(uint16_t& u8Val, uint8_t bit, bool val);
	static bool bitRead(uint8_t u8Val, uint8_t bit);
	static uint16_t word(uint8_t u8Low, uint8_t u8High);
	static uint8_t highByte(uint16_t u16Val);
	static uint8_t lowByte(uint16_t u16Val);

	static uint32_t millis();
};


#endif // !CUSTOM_STREAM_H
