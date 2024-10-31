#ifndef SERIAL_SETTING_H
#define SERIAL_SETTING_H

#include "AbstractCommsSetting.h"

class SerialSetting : public AbstractCommsSetting
{
public:
	explicit SerialSetting(AbstractCommsSetting* parenet = nullptr);
	~SerialSetting();

	CommunicationType getCommsType() const override;			//��ȡͨѶ����
	void applyWidget(QWidget* w) override;				//�õ����ý���
	virtual void apply() override;						//Ӧ������
};

#endif // !SERIAL_SETTING_H
