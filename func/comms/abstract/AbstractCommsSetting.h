#ifndef BASE_COMMS_SETTING_H
#define BASE_COMMS_SETTING_H

#include <QWidget>

enum class CommunicationType {
	Bluetooth,
	Serial,
	TCP,
	UDP,
};

class AbstractCommsSetting
{
public:
	virtual ~AbstractCommsSetting() = default;
	virtual CommunicationType getCommsType() const = 0;			//��ȡͨѶ����
	virtual void applyWidget(QWidget* w) = 0;					//Ӧ�����ý���
	virtual void apply() = 0;									//Ӧ������
};

#endif // !BASE_COMMS_SETTING_H