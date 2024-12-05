#ifndef BASE_UPGRADE_H
#define BASE_UPGRADE_H

#include "AbstractCommunication.h"

class BaseUpgrade {

public:
	virtual void upgrade() = 0;
	virtual ~BaseUpgrade() {
		delete commu;
	}

protected:
	AbstractCommunication* commu;

private:

};

#endif // !BASE_UPGRADE_H
