#ifndef LOW_SOC_SETTINGS_MODEL_H
#define LOW_SOC_SETTINGS_MODEL_H

#include "BaseModel.h"

class LowSOCSettingsModel : public BaseModel
{
	Q_OBJECT

public:
	explicit LowSOCSettingsModel(BaseModel* parent = nullptr);
	~LowSOCSettingsModel();

	void emitDataChanged() override;
	//void parse(const QByteArray& rawData) override;
private:

};

#endif // !LOW_SOC_SETTINGS_MODEL_H
