// TimerManager.h
#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H

#include "Logger.h"

class Logger;
class LoggerManager {
public:
    static LoggerManager& instance() {
        static LoggerManager instance;
        return instance;
    }

    void log(QString log) {
        logger.log(log);
    }

    QWidget* widget() {
        return &logger;
    }

private:
    LoggerManager() {}  // 私有化构造函数
    Logger logger;
};

#endif // TIMERMANAGER_H
