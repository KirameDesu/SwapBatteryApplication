#include "ControlProtocol.h"

#include <QFile>

ControlProtocol::ControlProtocol()
{
}

ControlProtocol::~ControlProtocol()
{
}

QByteArray ControlProtocol::startUpgradeRawData()
{
	return QByteArray();

}

QByteArray ControlProtocol::UpgradePackRawData(int packNo)
{
	return QByteArray();
}

QByteArray ControlProtocol::endUpgradeRawData()
{
	return QByteArray();
}

void ControlProtocol::setFilePath(const QString& path)
{
	BaseProtocol::setFilePath(path);

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		// 文件无法以只读模式打开
		throw std::runtime_error("无法打开文件: " + path.toStdString());
	}

	// 读取文件内容
	QByteArray fileData = file.readAll();
	int totalSize = fileData.size();


}
