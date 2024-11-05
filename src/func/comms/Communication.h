#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "SerialCtl.h"

class SerialCtl;
class Communication
{
public:
    static std::shared_ptr<AbstractCommunication> createCommunication(CommunicationType type) {
        switch (type) {
        //case CommunicationType::Bluetooth:
        //    return std::make_unique<BluetoothCommunication>();
        case CommunicationType::Serial:
            return std::make_shared<SerialCtl>();
        default:
            return nullptr;
        }
    }
};

#endif //