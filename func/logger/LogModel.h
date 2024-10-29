#ifndef LOG_MODEL_H
#define LOG_MODEL_H 

#include <QAbstractListModel>
#include <QStringList>
#include <QObject>


class LogModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit LogModel(QObject* parent = nullptr);
	~LogModel();
	void setLogList(QStringList list);
	void appendLogList(QString log);
	QStringList getLogList() const;

protected:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role) const override;

private:
	QStringList _logList;
};

#endif