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
		// �ļ��޷���ֻ��ģʽ��
		throw std::runtime_error("�޷����ļ�: " + path.toStdString());
	}

	// ��ȡ�ļ�����
	QByteArray fileData = file.readAll();
	int totalSize = fileData.size();


}
