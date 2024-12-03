#include "TableViewModel.h"

#include <QIcon>
#include <QDateTime>

TableViewModel::TableViewModel(QObject* parent)
    : QAbstractTableModel{ parent }
{
    _header << "序号"
        << "时间"
        << "电池电压"
        << "总电流"
        << "剩余容量"
        << "满充容量"
        << "最大电芯电压"
        << "最小电芯电压"
        << "平均电芯电压"
        << "保护状态"
        << "故障状态"
        << "电芯电压1"
        << "电芯电压2"
        << "电芯电压3"
        << "电芯电压4"
        << "电芯电压5"
        << "电芯电压6"
        << "电芯电压7"
        << "电芯电压8"
        << "电芯电压9"
        << "电芯电压10"
        << "电芯电压11"
        << "电芯电压12"
        << "电芯电压13"
        << "电芯电压14"
        << "电芯电压15"
        << "电芯电压16"
        << "电芯电压17"
        << "电芯电压18"
        << "电芯电压19"
        << "电芯电压20"
        << "电芯电压21"
        << "电芯电压22"
        << "电芯电压23"
        << "电芯电压24"
        << "电芯温度1"
        << "电芯温度2"
        << "电芯温度3"
        << "电芯温度4"
        << "MOS温度"
        << "环境温度";

    //QStringList data0;
    //QStringList data1;
    //QStringList data2;
    //QStringList data3;
    //QStringList data4;
    //QStringList data5;
    //QStringList data6;
    //QStringList data7;
    //QStringList data8;
    //data0 << "夜航星(Night Voyager)"
    //    << "不才/三体宇宙"
    //    << "我的三体之章北海传"
    //    << "05:03";
    //data1 << "玫瑰少年"
    //    << "五月天"
    //    << "玫瑰少年"
    //    << "03:55";
    //data2 << "Collapsing World(Original Mix)"
    //    << "Lightscape"
    //    << "Collapsing World"
    //    << "03:10";
    //data3 << "RAIN MAN (雨人)"
    //    << "AKIHIDE (佐藤彰秀)"
    //    << "RAIN STORY"
    //    << "05:37";
    //data4 << "黑暗森林"
    //    << "雲翼星辰"
    //    << "黑暗森林"
    //    << "05:47";
    //data5 << "轻(我的三体第四季主题曲)"
    //    << "刘雪茗"
    //    << "我的三体第四季"
    //    << "01:59";
    //data6 << "STYX HELIX"
    //    << "MYTH & ROID"
    //    << "STYX HELIX"
    //    << "04:51";
    //data7 << "LAST STARDUST"
    //    << "Aimer"
    //    << "DAWN"
    //    << "05:18";
    //data8 << "Running In The Dark"
    //    << "MONKEY MAJIK/塞壬唱片"
    //    << "Running In The Dark"
    //    << "03:40";
    //_dataList.append(data0);
    //_dataList.append(data1);
    //_dataList.append(data2);
    //_dataList.append(data3);
    //_dataList.append(data4);
    //_dataList.append(data5);
    //_dataList.append(data6);
    //_dataList.append(data7);
    //_dataList.append(data8);
}

TableViewModel::~TableViewModel()
{
}

int TableViewModel::rowCount(const QModelIndex& parent) const
{
    return _dataList.size();
}

int TableViewModel::columnCount(const QModelIndex& parent) const
{
    return _header.count();
}

QVariant TableViewModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return _dataList[index.row()][index.column()];
    }
    //else if (role == Qt::DecorationRole && index.column() == 0)
    //{
    //    return _iconList[index.row() % 9];
    //}
    //else if (role == Qt::DecorationPropertyRole)
    //{
    //    return Qt::AlignCenter;
    //}
    //else if (role == Qt::TextAlignmentRole && index.column() == 4)
    //{
    //    return Qt::AlignCenter;
    //}
    return QVariant();
}

QVariant TableViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return _header[section];
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

// 在模型中插入数据
void TableViewModel::insertRow(int row, const QStringList& newRow) {
    beginInsertRows(QModelIndex(), row, row);
    _dataList.insert(row, newRow);
    endInsertRows();
}

void TableViewModel::insertOneData(BaseModel* dataModel)
{
    QStringList l;

    for (const auto& headTitle : _header)
    {
        if (headTitle == "序号")
        {
            l << QString::number(_dataList.size() + 1);
        }
        else if (headTitle == "时间")
        {
            l << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        }
        else
        {
            try {
                ModelData* m = dataModel->findModelDataFromTitle(headTitle);
                l << m->val.toString();
            } catch (const std::runtime_error& e) {
                l << "UNDEFINED";
            }
        }
    }
    insertRow(rowCount(), l);
}
