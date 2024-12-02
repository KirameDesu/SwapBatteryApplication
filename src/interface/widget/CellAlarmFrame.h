#ifndef CELL_ALARM_WIDGET_H
#define CELL_ALARM_WIDGET_H

#include <QWidget>
#include <QPainter>

class AlarmColor {
public:
    inline static const QColor red = QColor(255, 0, 0, 127);
    inline static const QColor yellow = QColor(200, 200, 10, 200);
    inline static const QColor origin = QColor(255, 165, 30, 200);
};

class CellAlarmFrame : public QWidget
{
public:
    explicit CellAlarmFrame(const QString& message, const QColor color, QWidget* parent = nullptr)
        : QWidget(parent), _message(message), _color(color)
    {
        this->setFixedSize(110, 50);
    }

    //void setMessage(const QString& message) {
    //    _message = message;
    //    update();
    //}
	
protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);

        // 设置抗锯齿
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制圆角矩形
        QRect rect(0, 0, width() - 20, height() - 20);
        painter.setBrush(_color);  // 半透明红色背景
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect, 15, 15);  // 圆角半径为10

        // 设置警告文字样式
        painter.setPen(Qt::white);
        painter.setFont(QFont("思源黑体 CN Regular", 12, QFont::Bold));
        painter.drawText(rect, Qt::AlignCenter, _message);
    }

private:
    QString _message;  // 警告信息
    QColor _color;
};

#endif // !CELL_ALARM_WIDGET_H
