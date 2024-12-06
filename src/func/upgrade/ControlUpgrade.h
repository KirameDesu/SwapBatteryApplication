#ifndef CONTROL_UPGRADE_H
#define CONTROL_UPGRADE_H

#include "BaseUpgrade.h"

class ControlUpgrade : public BaseUpgrade
{
public:
	ControlUpgrade();
	~ControlUpgrade();

	void upgrade() override;
	void setFilePath(const QString& path) override;
private:

};



#endif // !CONTROL_UPGRADE_H
