#ifndef BMS_CMD_MANAGER_H
#define BMS_CMD_MANAGER_H

#include "AbstractCommunication.h"
#include "Communication.h"

class BMSCmdManager
{
public:
	BMSCmdManager();
	~BMSCmdManager();
	
	std::shared_ptr<AbstractCommunication> getConnect();
	void test();
private:
	std::shared_ptr<AbstractCommunication> _communication{ nullptr };
	ModbusMaster* _modbusMaster{ nullptr };
};


#endif