#include "LogModel.h"

LogModel::LogModel(QObject* parent)
	: QAbstractListModel{parent}
{
}

LogModel::~LogModel()
{
}

int LogModel::rowCount(const QModelIndex& parent) const
{
    return this->_logList.count();
}

QVariant LogModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return _logList[index.row()];
    }
    return QVariant();
}

void LogModel::setLogList(QStringList list)
{
    beginResetModel();
    this->_logList = list;
    endResetModel();
}

void LogModel::appendLogList(QString log)
{
    beginResetModel();
    this->_logList.append(log);
    endResetModel();
}

QStringList LogModel::getLogList() const
{
    return this->_logList;
}
