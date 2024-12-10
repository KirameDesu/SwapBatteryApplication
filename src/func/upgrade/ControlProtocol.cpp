#include "ControlProtocol.h"

#include <QFile>
#include <QThread>
#include <QDebug>

#include "Util.h"

ControlProtocol::ControlProtocol()
{
}

ControlProtocol::~ControlProtocol()
{
}

QByteArray ControlProtocol::startUpgradeRawData()
{
	QByteArray arr;
	arr.reserve(6 + 5);

	arr.append(0xEB);
	arr.append(0x90);
	arr.append(0x02);
	arr.append(0x9A);
	// 长度 5byte
	arr.append(0x05);
	// 软件版本 1byte
	arr.append(0x01);
	// 升级包大小 4byte
	quint32 size = upgradeTotalSize;
	for (int i = 3; i >= 0; i--)
	//for (int i = 4; i > 0; i--)
	{
		arr.append(static_cast<char>((size >> (i * 8)) & 0xFF));  // 逐字节添加
	}

	// 尾部CRC8
	quint8 crc8 = Util::getCheckSum(reinterpret_cast<const uint8_t*>(arr.data() + 2), arr.size() - 2);
	arr.append(crc8);

	return arr;
}

QByteArray ControlProtocol::UpgradePackRawData(int packNo)
{
	QByteArray arr;
	arr.reserve(8 + upgradePackSize);

	arr.append(0xEB);
	arr.append(0x90);
	arr.append(0x02);
	arr.append(0x9B);

	// 包序号 16bit
	quint16 no = packNo;
	for (int i = 1; i >= 0; i--) {
		arr.append(static_cast<char>((no >> (i * 8)) & 0xFF));  // 逐字节添加
	}

	// 数据段
	int currPackStartIndex = (packNo - 1) * upgradePackSize;
	int packDataSize = (packNo == totalPackNum)
		? upgradeTotalSize - currPackStartIndex  // 最后一包可能不足一个完整的包
		: upgradePackSize;
	arr.append(upgradeFileRawData.mid(currPackStartIndex, packDataSize));

	// 长度 5byte
	char dataLen = 2 + packDataSize;
		arr.insert(4, dataLen);

	// 尾部CRC8
	quint8 crc8 = Util::getCheckSum(reinterpret_cast<const uint8_t*>(arr.data() + 2), arr.size() - 2);
	arr.append(crc8);

	return arr;
}

QByteArray ControlProtocol::endUpgradeRawData()
{
	QByteArray arr;
	arr.reserve(6 + 4);

	arr.append(0xEB);
	arr.append(0x90);
	arr.append(0x02);
	arr.append(0x9C);

	// 长度 5byte
	arr.append(0x04);

	// CRC32 32bit
	quint32 crc32 = u32UgradeTotalCRC;
	for (int i = 0; i < 4; ++i) {
		arr.append(static_cast<char>((crc32 >> (i * 8)) & 0xFF));  // 逐字节添加
	}

	// 尾部CRC8
	quint8 crc8 = Util::getCheckSum(reinterpret_cast<const uint8_t*>(arr.data() + 2), arr.size() - 2);
	arr.append(crc8);

	return arr;
}

void ControlProtocol::setFilePath(const QString& path)
{
	BaseProtocol::setFilePath(path);
	QByteArray arr;

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		// 文件无法以只读模式打开
		throw std::runtime_error("无法打开文件: " + path.toStdString());
	}

	// 读取文件内容
	arr = file.readAll();
	upgradeFileRawData.clear();
	upgradeFileRawData.append(arr);
	upgradeTotalSize = arr.size();

	// 计算CRC32
	qint16 crc16 = Util::getCRC16(reinterpret_cast<const uint8_t*>(arr.data()), arr.size());
	u32UgradeTotalCRC = crc16;
}

BaseProtocol::parseResult ControlProtocol::responseHandle(const QByteArray& rawData)
{
	qDebug() << "ResponseHandle Running in " << QThread::currentThreadId;

	quint8 CMDCode;
	const uint8_t* pDataInfoStart = nullptr;
	UpgradeStep step;
	int responsePackNo;

	if (rawData.isEmpty())
		return parseResult::ArrayIsEmpty;

	// 判断头
	if (rawData.at(0) != (char)0xEB || rawData.at(1) != (char)0x90)
		return parseResult::InvalidHead;

	// 判断长度
	if (rawData.at(4) + 6 != rawData.size())
		return parseResult::InvalidLength;

	// 判断CRC
	quint8 crc = Util::getCheckSum(reinterpret_cast<const uint8_t*>(rawData.data() + 2), rawData.size() - 3);
	if ((char)crc != rawData.at(rawData.size() - 1))
		return parseResult::InvalidCRC;

	/// 判断应答是否成功

	// 报文有效
	CMDCode = rawData.at(3);
	// 去掉应答标志
	CMDCode -= 0x40;
	pDataInfoStart = reinterpret_cast<const uint8_t*>(rawData.data()) + 5;
	switch (CMDCode)
	{
	case 0x9A:
		// uint8 返回码, 0x00表示可以升级

		// uint16 分段大小
		upgradePackSize = Util::word(pDataInfoStart[2], pDataInfoStart[1]);
		// 计算分包数量
		totalPackNum = upgradeTotalSize / upgradePackSize;
		if (upgradeTotalSize % upgradePackSize != 0)
			totalPackNum += 1;
		step = UpgradeStep::sendPack;
		emit nextProcess(step);
		break;
	case 0x9B:
		// uint16 包序号, 为0则表示出错, 结束升级流程
		responsePackNo = Util::word(pDataInfoStart[1], pDataInfoStart[0]);
		if (responsePackNo != currentPackNo + 1)
		{
			return parseResult::InvalidPackNo;
		}
		currentPackNo = responsePackNo;
		// 当前接收包序号等于总包序号, 表示传输完成
		if (currentPackNo == totalPackNum)
		{
			step = UpgradeStep::checkUpgrade;
		}
		else
		{
			step = UpgradeStep::sendPack;
		}
		emit nextProcess(step);

		break;
	case 0x9C:
		// uint8 返回码, 为0x00表示升级校验成功

		step = UpgradeStep::endUpgrade;
		emit nextProcess(step);
		break;
	default:
		break;
	}


	return parseResult::Success;
}
