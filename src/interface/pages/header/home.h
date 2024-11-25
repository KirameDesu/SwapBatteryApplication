#ifndef T_HOME_H
#define T_HOME_H

#include "BasePage.h"

#include "SegmentBatteryOverviewWidget.h"
#include "SegmentBatteryFunctionWidget.h"
#include "SegmentBatteryCellVoltWidget.h"
#include "SegmentBatteryAlarmWidget.h"

class ElaMenu;
class MonitorPage : public BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MonitorPage(QWidget* parent = nullptr);
    ~MonitorPage();

    // 添加监控项
    void setMonitorItems(SETTINGS_CLASS settings);

Q_SIGNALS:
    Q_SIGNAL void elaScreenNavigation();
    Q_SIGNAL void elaBaseComponentNavigation();
    Q_SIGNAL void elaSceneNavigation();
    Q_SIGNAL void elaCardNavigation();
    Q_SIGNAL void elaIconNavigation();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
private:
    // 右键菜单
    ElaMenu* _homeMenu{ nullptr };

    SegmentBatteryOverviewWidget* segmentBattOverview{ nullptr };
    SegmentBatteryAlarmWidget* segmentBattAlarm{ nullptr };
    SegmentBatteryFunctionWidget* segmentBatteryFunction{ nullptr };
    SegmentBatteryCellVoltWidget* segmentCellVolt{ nullptr };

};

#endif // T_HOME_H
