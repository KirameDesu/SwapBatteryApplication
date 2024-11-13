#ifndef BASE_SETTING_H
#define BASE_SETTING_H

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaText.h"
#include "ElaComboBox.h"

enum SettingLayoutPolicy
{
    Horizon,
    Verticle,
};

struct Setting
{
    QString title;
    QString unit;
    int maxVal;
    int minVal;
};

class BaseSetting : public QObject
{
    Q_OBJECT
public:
    const static int TEXT_SIZE = 16;

    BaseSetting(QString title, int maxVal, int minVal, QObject* parent = nullptr)
        : _title(_title), _maxVal(maxVal), _minVal(minVal)
    {
        initWidget();
    };
    BaseSetting(Setting s, QObject* parent = nullptr)
    {
        _title = s.title;
        _unit = s.unit;
        _maxVal = s.maxVal;
        _minVal = s.minVal;

        initWidget();
    };
    ~BaseSetting() = default;

    void initWidget() {
        w = new QWidget();
        switch (_layoutPolicy)
        {
        case Verticle:
        case Horizon:
            QHBoxLayout* layout = new QHBoxLayout(w);
            layout->addWidget(new ElaText(_title, TEXT_SIZE, w));
            QString unit('(' + _unit + ')');
            layout->addWidget(new ElaText(unit, TEXT_SIZE, w));
            layout->addStretch();
            ElaComboBox* comboBox = new ElaComboBox(w);
            comboBox->setFixedWidth(160);
            //comboBox->setPlaceholderText(QString::number(_minVal) + '~' + QString::number(_maxVal));
            comboBox->addItem("0");
            layout->addWidget(comboBox);
        }
    }

    QWidget* getWidget() {
        return w;
    }

    bool needToSave()
    {
        return _needSave;
    }

    virtual bool isVaild() {
        return _settingVal >= _minVal && _settingVal <= _maxVal ? true : false;
    }

    /*virtual bool saveSetting() {
        
    };*/

    uint16_t getStartAddr() {
    
    };
signals:
    void getSetting(uint16_t);
    void saveSetting(uint16_t);

private:
    QWidget* w{ nullptr };
    QString _title;
    QString _unit;
    int _currentval = 0;        // 当前值
    int _settingVal = 0;        // 设置值
    int _minVal = 0;
    int _maxVal = 0;
    
    bool _needSave = false;      // 是否需要设置

    SettingLayoutPolicy _layoutPolicy = Horizon;
};

#endif // !BASE_SETTING_H
