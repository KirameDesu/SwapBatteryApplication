#ifndef SETTING_BACKGROUND_H
#define SETTING_BACKGROUND_H

#include <QWidget>
#include <QPainter>
#include "ElaTheme.h"

class SettingsBackgroundArea : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(int BorderRadius READ borderRadius WRITE setBorderRadius)

public:
    explicit SettingsBackgroundArea(QWidget* parent = nullptr);
    ~SettingsBackgroundArea();

    // 获取边框圆角半径
    int borderRadius() const { return m_borderRadius; }

    // 设置边框圆角半径
    void setBorderRadius(int radius) { m_borderRadius = radius; }

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent* event) override;

private:
    int m_borderRadius;  // 边框圆角半径
    ElaThemeType::ThemeMode m_themeMode;  // 主题模式
};

#endif // ELASCROLLPAGEAREA_H
