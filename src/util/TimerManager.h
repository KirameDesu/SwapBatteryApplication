// TimerManager.h 用于全局定时
#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <QElapsedTimer>
#include <QDateTime>

using DataTime = QDateTime;

class QElapsedTimer;
class TimerManager {
public:
    static TimerManager& instance() {
        static TimerManager instance;
        return instance;
    }

    void start() {
        timer.start();
    }

    qint64 elapsed() {
        return timer.elapsed();
    }

    QDateTime getCurrentDataTime() {
        QDateTime::currentDateTime();
    }

private:
    TimerManager() {}  // 私有化构造函数
    QElapsedTimer timer;
};

#endif // TIMERMANAGER_H
