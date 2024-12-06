#ifndef UPGRADE_FACTORY_H
#define UPGRADE_FACTORY_H

#include <QString>

#include "ControlUpgrade.h"
#include "BaseUpgrade.h"

// 工厂类，用来选择具体的升级方式和协议
class UpgradeFactory {
public:
    static BaseUpgrade* createUpgrade(const QString& upgradeType) {
        if (upgradeType == "rfn") {
            //return new SerialUpgrade();
        }
        else if (upgradeType == "controller") {
            return new ControlUpgrade();
        }
        return nullptr;
    }
};

#endif // !UPGRADE_FACTORY_H
