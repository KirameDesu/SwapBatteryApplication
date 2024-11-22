// TimerManager.h
#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H

#include <QDateTime>

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

    static void logWithTime(const QString& logMessage) {
        QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

        // 调用实例方法，记录带有时间戳的日志
        instance().appendLogList(QString("[%1] %2").arg(timeStamp, logMessage));
    }

private:
    LoggerManager() = default;
    ~LoggerManager() = default;
    LoggerManager(const LoggerManager& l) = delete;
    const LoggerManager& operator=(const LoggerManager& l) = delete;
};

#endif // TIMERMANAGER_H
