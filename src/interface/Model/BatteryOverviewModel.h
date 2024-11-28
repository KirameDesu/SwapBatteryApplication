#ifndef BATTERY_OVERVIEW_MODEL_H
#define BATTERY_OVERVIEW_MODEL_H

#include "BaseModel.h"

class BatteryOverviewModel : public BaseModel
{
	Q_OBJECT

public:
	explicit BatteryOverviewModel(BaseModel* parent = nullptr);
	~BatteryOverviewModel();

	void parseFromRegAddr(int addrStart, const QByteArray& rawData);

	void emitDataChanged() override;
private:

signals:
	Q_SIGNAL void AFEDataChanged();
	Q_SIGNAL void SOCDataChanged();
};

#endif // !BATTERY_OVERVIEW_MODEL_H
