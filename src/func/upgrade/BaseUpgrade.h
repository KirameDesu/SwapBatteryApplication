#ifndef BASE_UPGRADE_H
#define BASE_UPGRADE_H

#include "AbstractCommunication.h"

class BaseUpgrade {

public:
	virtual ~BaseUpgrade() {
		delete commu;
	}
	virtual void upgrade() = 0;
	virtual void setFilePath(const QString& path) = 0;

protected:
	AbstractCommunication* commu;

private:

};

#endif // !BASE_UPGRADE_H
