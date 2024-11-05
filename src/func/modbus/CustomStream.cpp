#include "util/CustomStream.h"

#include "LoggerManager.h"
#include "TimerManager.h"

CustomStream::CustomStream(QSerialPort* parent)
	: QSerialPort(parent)
{
}

CustomStream::~CustomStream()
{
}

// 接收函数
int8_t CustomStream::read()
{
	if (this->bytesAvailable() > 0) {
		QByteArray data = QSerialPort::read(1); // 读取一个字节
		return data.isEmpty() ? '\0' : data[0]; // 返回读取的字节
	}
	return -1; // 如果没有数据，返回默认值
}

// 发送函数
void CustomStream::write(uint8_t* u8Arr, uint16_t arrLen)
{
	QByteArray byteArray(reinterpret_cast<char*>(u8Arr), arrLen);
	QSerialPort::write(byteArray);

	LoggerManager::instance().log("写入" + byteArray.toHex());
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

bool CustomStream::available()
{
	return this->QSerialPort::isOpen();
}

uint32_t CustomStream::millis()
{
	return (uint32_t)static_cast<quint32>(TimerManager::instance().elapsed());
}
