#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <QByteArray>

#include "VoltageProtectModel.h"

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	bool parseHandle(int startAddr, QByteArray rawData);
private:
	VoltageProtectModel* _voltProtModel{ nullptr };
};

#endif // !MODEL_MANAGER_H
