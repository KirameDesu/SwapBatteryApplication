// TimerManager.h
#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H

#include "LogModel.h"

class LogModel;
class LoggerManager {
public:
    static LogModel& instance() {
        static LogModel instance;
        return instance;
    }

    static void log(const QString& logMessage) {
        instance().appendLogList(logMessage);
    }


private:
    LoggerManager() = default;
    ~LoggerManager() = default;
    LoggerManager(const LoggerManager& l) = delete;
    const LoggerManager& operator=(const LoggerManager& l) = delete;
};

#endif // TIMERMANAGER_H
