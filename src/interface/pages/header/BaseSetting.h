#ifndef BASE_SETTING_H
#define BASE_SETTING_H

#include <QWidget>
#include <QString>

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

class BaseSetting
{
    Q_OBJECT
public:
    BaseSetting(QWidget* parent, QString title, int maxVal, int minVal)
        : _title(_title), _maxVal(maxVal), _minVal(minVal)
    {
        initWidget(parent);
    };
    BaseSetting(QWidget* parent, Setting s)
    {
        _title = s.title;
        _unit = s.unit;
        _maxVal = s.maxVal;
        _minVal = s.minVal;

        initWidget(parent);
    };
    ~BaseSetting() = default;

    void initWidget(QWidget* parent = nullptr) {
        w = new QWidget(parent);
        switch (_layoutPolicy)
        {
        case Horizon:
            w->setLayout(new QHBoxLayout(w));
        case Verticle:
            w->setLayout(new QVBoxLayout(w));
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
