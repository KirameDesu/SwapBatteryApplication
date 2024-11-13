#include "SettingsBackgroundArea.h"
#include <QGraphicsDropShadowEffect>

SettingsBackgroundArea::SettingsBackgroundArea(QWidget* parent)
    : QWidget(parent), m_borderRadius(6), m_themeMode(ElaThemeType::Light) // 默认圆角半径和主题模式
{
    //setFixedHeight(75);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

    // 获取当前的主题模式
    m_themeMode = eTheme->getThemeMode();

    // 连接信号，当主题模式变化时更新主题模式
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        m_themeMode = themeMode;
        update();  // 更新界面，重新绘制
        });
}

SettingsBackgroundArea::~SettingsBackgroundArea()
{
}

void SettingsBackgroundArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.save();

    // 设置主题颜色
    painter.setPen(ElaThemeColor(m_themeMode, BasicBorder));
    painter.setBrush(ElaThemeColor(m_themeMode, BasicBaseAlpha));

    // 绘制圆角矩形
    QRect foregroundRect(1, 1, width() - 2, height() - 2);
    painter.drawRoundedRect(foregroundRect, m_borderRadius, m_borderRadius);

    painter.restore();
}
