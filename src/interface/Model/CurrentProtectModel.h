#ifndef CURRENT_PROTECT_MODEL_H
#define CURRENT_PROTECT_MODEL_H

#include "BaseModel.h"

class CurrentProtectModel : public BaseModel
{
	Q_OBJECT

public:
	explicit CurrentProtectModel(BaseModel* parent = nullptr);
	~CurrentProtectModel();
	 
	void parse(const QByteArray& rawData) override;
private:

};

#endif // !CURRENT_PROTECT_MODEL_H
