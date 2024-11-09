#ifndef BMS_CMD_MANAGER_H
#define BMS_CMD_MANAGER_H

#include "AbstractCommunication.h"
#include "Communication.h"
#include "CustomModbusMaster.h"

class BMSCmdManager
{
public:
	BMSCmdManager();
	~BMSCmdManager();
	
	std::shared_ptr<AbstractCommunication> getConnect();
	void standardModbusTest();
	void customModbusTest();
	QString getLastComunicationInfo();
private:
	int _lastComunicationResult = 0;

	std::shared_ptr<AbstractCommunication> _communication{ nullptr };
	ModbusMaster* _modbusMaster{ nullptr };
	CustomModbusMaster* _customModbusMaster{ nullptr };
};


#endif