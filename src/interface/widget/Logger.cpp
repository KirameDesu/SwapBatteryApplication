#include "Logger.h"
#include "LogModel.h"


#include <ElaListView.h>
#include <QVBoxLayout>
#include "ElaLog.h"

#include "LoggerManager.h"

Logger::Logger(QWidget* parent)
    : QWidget{ parent }
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 5, 5, 0);
    ElaListView* logView = new ElaListView(this);
    logView->setIsTransparent(true);
    _logModel = &LoggerManager::instance();
    logView->setModel(_logModel);
    mainLayout->addWidget(logView);
    connect(ElaLog::getInstance(), &ElaLog::logMessage, this, [=](QString log) {
        _logModel->appendLogList(log);
    });
    _logModel->appendLogList("这是日志的开始...");
}

Logger::~Logger()
{
}

//void Logger::log(QString log)
//{
//    _logModel->appendLogList(log);
//}
