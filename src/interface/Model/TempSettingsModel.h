#ifndef TEMP_SETTINGS_MODEL_H
#define TEMP_SETTINGS_MODEL_H

#include "BaseModel.h"

class TempSettingsModel : public BaseModel
{
	Q_OBJECT

public:
	explicit TempSettingsModel(BaseModel* parent = nullptr);
	~TempSettingsModel();
	 
	void parse(const QByteArray& rawData) override;
private:

};

#endif // !VOLTAGE_PROTECT_MODEL_H
