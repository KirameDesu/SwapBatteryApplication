#ifndef FUNC_SETTINGS_MODEL_H
#define FUNC_SETTINGS_MODEL_H

#include "BaseModel.h"

class FunctionSettingsModel : public BaseModel
{
	Q_OBJECT

public:
	explicit FunctionSettingsModel(BaseModel* parent = nullptr);
	~FunctionSettingsModel();

	void emitDataChanged() override;
	//void parse(const QByteArray& rawData) override;
private:

};

#endif // !FUNC_SETTINGS_MODEL_H