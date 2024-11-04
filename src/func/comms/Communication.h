#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "SerialCtl.h"


class Communication
{
public:
    static std::unique_ptr<AbstractCommunication> createCommunication(CommunicationType type) {
        switch (type) {
        //case CommunicationType::Bluetooth:
        //    return std::make_unique<BluetoothCommunication>();
        case CommunicationType::Serial:
            return std::make_unique<SerialCtl>();
        default:
            return nullptr;
        }
    }
};

#endif //