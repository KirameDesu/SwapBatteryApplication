#ifndef UPGRADE_FACTORY_H
#define UPGRADE_FACTORY_H

#include <QString>

#include "ControlProtocol.h"

// 工厂类，用来选择具体的协议
class ProtocolFactory {
public:
    static BaseProtocol* createProtocol(const QString& upgradeType) {
        if (upgradeType == "rfn") {
            //return new SerialUpgrade();
        }
        else if (upgradeType == "Controller") {
            return new ControlProtocol();
        }
        return nullptr;
    }
};

#endif // !UPGRADE_FACTORY_H
