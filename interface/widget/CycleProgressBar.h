#ifndef _CYCLE_PROGRESS_BAR_H_
#define _CYCLE_PROGRESS_BAR_H_


#include <QWidget>
#include <QColor>

class CycleProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit CycleProgressBar(QWidget* parent = 0);

    void    setColor(QColor pb_bg_color, QColor pg_color, QColor bd_color, QColor ft_color);
    void    setPersent(int persent);
    void    setVoltage(int voltage);
    void    setCurrent(int current);

protected:
    void    paintEvent(QPaintEvent* event);

private:
    QColor  m_progressbar_background_color;     // 进度条底色
    QColor  m_progressbar_color;                // 进度条颜色
    QColor  m_background_color;                 // 背景颜色
    QColor  m_font_color;                       // 字体颜色
    int     m_persent;                          // SOC百分比
    float   m_voltage;                          // 总压
    float   m_current;                          // 总电流
};


#endif // !_CYCLE_PROGRESS_BAR_H_
