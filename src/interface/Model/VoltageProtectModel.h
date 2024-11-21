#ifndef VOLTAGE_PROTECT_MODEL_H
#define VOLTAGE_PROTECT_MODEL_H

#include "BaseModel.h"

class VoltageProtectModel : public BaseModel
{
	Q_OBJECT

public:
	explicit VoltageProtectModel(BaseModel* parent = nullptr);
	~VoltageProtectModel();
	 
	void parse(const QByteArray& rawData) override;
private:

};

#endif // !VOLTAGE_PROTECT_MODEL_H
