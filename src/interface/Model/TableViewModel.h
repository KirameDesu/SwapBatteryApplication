#ifndef TABLE_VIEW_MODEL_H
#define TABLE_VIEW_MODEL_H

#include <QAbstractTableModel>

#include "BaseModel.h"


class TableViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableViewModel(QObject* parent = nullptr);
    ~TableViewModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void insertRow(int row, const QStringList& newRow);
    // 根据传入Model插入一条数据
    void insertOneData(BaseModel* dataModel);

private:
    QStringList _header;
    QList<QStringList> _dataList;
    QList<QIcon> _iconList;
};

#endif // !TABLE_VIEW_MODEL_H