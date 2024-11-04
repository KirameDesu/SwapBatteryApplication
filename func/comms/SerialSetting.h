#ifndef SERIAL_SETTING_H
#define SERIAL_SETTING_H

#include "AbstractCommsSetting.h"

class SerialSetting : public AbstractCommsSetting
{
	Q_OBJECT

public:
	explicit SerialSetting(AbstractCommsSetting* parenet = nullptr);
	~SerialSetting();

	CommunicationType getCommsType() const override;		//��ȡͨѶ����
	void applyWidget(QWidget* settingsWidget) override;		//���ý���

	QWidget* getWidget() override;							//���ؽ���ָ��
	QString getSettingsString() override;					//���������ַ���

	QWidget* getWidgetFromName(QString name);				//ͨ���ؼ����ƻ�ȡ�ؼ�ָ��

	void updateSerialPortNames();							//ˢ�´����б���ѡ��
	QStringList getSerialNameList();						//�õ������б�
};

#endif // !SERIAL_SETTING_H
