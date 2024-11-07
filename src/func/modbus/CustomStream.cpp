#include "util/CustomStream.h"

#include "LoggerManager.h"
#include "TimerManager.h"

CustomStream::CustomStream(AbstractCommunication* c)
	: _con(c)
{
}

CustomStream::~CustomStream()
{
}

// 发送函数
void CustomStream::dataWrite(uint8_t* u8Arr, uint16_t arrLen)
{
	QByteArray byteArray(reinterpret_cast<char*>(u8Arr), arrLen);
	_con->write(byteArray);
}

void CustomStream::bitWrite(uint16_t& u8Val, uint8_t bit, bool val)
{
	u8Val &= ~(1 << bit);  // 将指定的bit位置0

	if (val)
	{
		u8Val |= (1 << bit);  // 如果val为true，设置bit位置1
	}
}

bool CustomStream::bitRead(uint8_t u8Val, uint8_t bit)
{
	return (u8Val >> bit) & 1;  // 右移 bit 位，得到目标位，& 1 获得该位的值（0 或 1）
}

uint16_t CustomStream::word(uint8_t u8Low, uint8_t u8High)
{
	return (static_cast<uint16_t>(u8High) << 8) | u8Low;  // 高字节左移8位，然后与低字节合并
}

uint8_t CustomStream::highByte(uint16_t u16Val)
{
	return static_cast<uint8_t>(u16Val >> 8);  // 右移 8 位，取出高字节
}

uint8_t CustomStream::lowByte(uint16_t u16Val)
{
	return static_cast<uint8_t>(u16Val & 0xFF);  // 与 0xFF 按位与，取出低字节
}

int32_t CustomStream::available()
{
	return _con->bytesAvailable();
}

uint32_t CustomStream::millis()
{
	return (uint32_t)static_cast<quint32>(TimerManager::instance().elapsed());
}

AbstractCommunication* CustomStream::getConnect()
{
	return _con;
}
