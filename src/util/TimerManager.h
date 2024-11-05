// TimerManager.h
#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <QElapsedTimer>

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

private:
    TimerManager() {}  // 私有化构造函数
    QElapsedTimer timer;
};

#endif // TIMERMANAGER_H
