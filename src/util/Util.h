#ifndef UTIL_H
#define UTIL_H

static unsigned short crc16Tab[256];

namespace Util {

	inline uint16_t getCRC16(const uint8_t* buf, int len)
	{
		int counter;
		uint16_t crc = 0;
		for (counter = 0; counter < len; counter++)
			crc = (crc << 8) ^ crc16Tab[((crc >> 8) ^
				(*(buf++))) & 0x00FF]; return crc;
	}

	inline uint8_t getCheckSum(const uint8_t* addr, uint16_t dataLen)
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

	inline void bitWrite(uint16_t& u8Val, uint8_t bit, bool val)
	{
		u8Val &= ~(1 << bit);  // 将指定的bit位置0

		if (val)
		{
			u8Val |= (1 << bit);  // 如果val为true，设置bit位置1
		}
	}

	inline bool bitRead(uint8_t u8Val, uint8_t bit)
	{
		return (u8Val >> bit) & 1;  // 右移 bit 位，得到目标位，& 1 获得该位的值（0 或 1）
	}

	inline uint16_t word(uint8_t u8Low, uint8_t u8High)
	{
		return (static_cast<uint16_t>(u8High) << 8) | u8Low;  // 高字节左移8位，然后与低字节合并
	}

	inline uint8_t highByte(uint16_t u16Val)
	{
		return static_cast<uint8_t>(u16Val >> 8);  // 右移 8 位，取出高字节
	}

	inline uint8_t lowByte(uint16_t u16Val)
	{
		return static_cast<uint8_t>(u16Val & 0xFF);  // 与 0xFF 按位与，取出低字节
	}
}


#endif // !UTIL_H