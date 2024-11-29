#ifndef INVERTER_SETTINGS_MODEL_H
#define INVERTER_SETTINGS_MODEL_H

#include "BaseModel.h"

class InverterSettingsModel : public BaseModel
{
	Q_OBJECT

public:
	explicit InverterSettingsModel(BaseModel* parent = nullptr);
	~InverterSettingsModel();

	void emitDataChanged() override;
	//void parse(const QByteArray& rawData) override;
private:

};

#endif // !INVERTER_SETTINGS_MODEL_H