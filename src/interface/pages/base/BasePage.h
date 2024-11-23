#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QSet>
#include <QObject>
#include <QTimer>

#include "ElaScrollPage.h"

#include "RegisterData.h"
#include "BMSCmdManager.h"
#include "BaseModel.h"
#include "CellSettingFrame.h"

class BMSCmdManager;
class BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit BasePage(QWidget* parent = nullptr);
    ~BasePage();

    // 指针异常
    class PointerException : public std::runtime_error {
    public:
        explicit PointerException(const std::string& message)
            : std::runtime_error("PointerException: " + message) {}
    };

    // 设置指令管理器指针
    void setCmdManager(BMSCmdManager* m);

    // 设置定时器状态
    static void setTimerStatus(bool status);

    void setModel(BaseModel* m);

    // 获取数据组名称列表
    const QSet<QString>& getAllDataGourpName() const;

    BMSCmdManager* getPageCMDManager();

protected:
    void createCustomWidget(QString desText);
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;

    void writeData();

    void readDataTiming();

    // 页面所有数据组名字
    QSet<QString> _dataGroupNameList;

    // 设置组指针
    void updateUI(QList<CellSettingFrame*>* _settingsGroup);

    // 所有子类共用一个定时器
    static QTimer* _timer;

protected:
    BaseModel* _model{ nullptr };

private:
    BMSCmdManager* _cmdManager{ nullptr };



    // 更新页面数据组
    Q_SLOT virtual void updatePageData();
    //bool _timedRead = false;
    // 定时发送数组
    //QList<REGISTERS_GROUP*> _timedReadRegGroup;


};

#endif // BASEPAGE_H
