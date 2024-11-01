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
	virtual void applyWidget(QWidget* settingsWidget) = 0;					//Ӧ�����ý���

	virtual QWidget* getWidget() = 0;							//���ؽ���ָ��
	virtual QString getSettingsString() = 0;					//���������ַ���

	QWidget* settingsWidget{ nullptr };										//����ָ��
};

#endif // !BASE_COMMS_SETTING_H