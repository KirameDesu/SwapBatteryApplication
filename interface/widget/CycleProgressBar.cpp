#include "CycleProgressBar.h"
#include <QPainter>

CycleProgressBar::CycleProgressBar(QWidget* parent) : QWidget(parent),
m_persent(0)
{
    m_progressbar_background_color = QColor(213, 240, 255);
    m_progressbar_color = QColor(45, 183, 255);
    m_background_color = QColor(255, 255, 255);
    m_font_color = QColor(0, 191, 255);
}

void CycleProgressBar::setColor(QColor pb_bg_color, QColor pg_color, QColor bd_color, QColor ft_color)
{
    m_progressbar_background_color = pb_bg_color;
    m_progressbar_color = pg_color;
    m_background_color = bd_color;
    m_font_color = ft_color;
    this->update();
}

void CycleProgressBar::setPersent(int persent)
{
    if (persent != m_persent)
    {
        m_persent = persent;
        this->update();
    }
}

void CycleProgressBar::setVoltage(int voltage)
{
    if (voltage != m_voltage)
    {
        m_voltage = voltage;
        this->update();
    }
}

void CycleProgressBar::setCurrent(int current)
{
    if (current != m_current)
    {
        m_current = current;
        this->update();
    }
}

void CycleProgressBar::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 计算角度
    int angle = 0;
    if (m_persent > 0)
    {
        angle = 360 * m_persent / 100;
    }
    else
    {
        angle = 0;
    }

    int side = qMin(this->width(), this->height());
    QRectF outRect(0, 0, side, side);
    QRectF inRect(10, 10, side - 20, side - 20);
    QString valueStr = QString("%1 %").arg(QString::number(m_persent));
    QString valueStr2 = QString("%1V").arg(QString::number(m_voltage));          // 总压
    QString valueStr3 = QString("%1A").arg(QString::number(m_current));          // 总电流

    p.setPen(Qt::NoPen);

    // 画底部圆
    p.setBrush(QBrush(m_progressbar_background_color));
    p.drawEllipse(outRect);

    // 画扇形显示进度
    p.setBrush(QBrush(m_progressbar_color));
    p.drawPie(outRect, (90 - angle) * 16, angle * 16);

    // 画中心圆
    p.setBrush(m_background_color);
    p.drawEllipse(inRect);

    // 画文字
    QFont f = QFont("Microsoft YaHei", 24, QFont::Normal);
    p.setFont(f);
    p.setPen(m_font_color);
    QRectF drawRect = inRect;
    drawRect.translate(0, -10);
    p.drawText(drawRect, Qt::AlignCenter, valueStr);
    //    // 写总压
    f.setPointSize(14);
    p.setFont(f);

    drawRect.translate(0, 31);
    p.drawText(drawRect, Qt::AlignCenter, QString("SOC"));

    QWidget::paintEvent(event);
}
