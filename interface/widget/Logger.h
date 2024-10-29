#ifndef LOGGER_H
#define LOGGER_H

#include <QWidget>


class LogModel;
class Logger : public QWidget
{
	Q_OBJECT
public:
	explicit Logger(QWidget* parent = nullptr);
	~Logger();
	void log(QString log);

private:
	LogModel* _logModel{ nullptr };
};

#endif // !LOGGER_H
