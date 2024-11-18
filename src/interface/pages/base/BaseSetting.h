#ifndef BASE_SETTING_H
#define BASE_SETTING_H

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ElaText.h"
#include "ElaComboBox.h"
#include "ElaToggleSwitch.h"

enum RegisterDataType {
    Semaphore = 0,
    Analog,
};

enum PermissionType {
    ReadOnly,
    WriteOnly,
    ReadAndWrite,
};

enum SettingLayoutPolicy
{
    Horizon,
    Verticle,
};

struct Setting
{
    RegisterDataType dataType;
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
        //initWidget();
    };
    BaseSetting(Setting s, QObject* parent = nullptr)
    {
        _type = s.dataType;
        _title = s.title;
        _unit = s.unit;
        _maxVal = s.maxVal;
        _minVal = s.minVal;

        //initWidget();
    };
    ~BaseSetting() = default;

    void initWidget(QWidget* parent = nullptr) {
        switch(_type)
        {
        case Analog:
            w = new QWidget(parent);
            switch (_layoutPolicy)
            {
            case Verticle:
            case Horizon:
                QHBoxLayout* layout = new QHBoxLayout(w);
                ElaText* titleText = new ElaText(_title, TEXT_SIZE, w);
                titleText->setWordWrap(false);
                layout->addWidget(titleText);
                QString unit('(' + _unit + ')');
                layout->addWidget(new ElaText(unit, TEXT_SIZE, w));
                layout->addStretch();
                ElaComboBox* comboBox = new ElaComboBox(w);
                comboBox->setFixedWidth(160);
                comboBox->setEditable(true);
                //comboBox->setPlaceholderText(QString::number(_minVal) + '~' + QString::number(_maxVal));
                comboBox->addItem("0");
                layout->addWidget(comboBox);
            }
        case Semaphore:
            w = new QWidget(parent);
            switch (_layoutPolicy)
            {
            case Verticle:
            case Horizon:
                QHBoxLayout* layout = new QHBoxLayout(w);
                ElaText* titleText = new ElaText(_title, TEXT_SIZE, w);
                titleText->setWordWrap(false);
                layout->addWidget(titleText);
                //QString unit('(' + _unit + ')');
                //layout->addWidget(new ElaText(unit, TEXT_SIZE, w));
                layout->addStretch();
                ElaToggleSwitch* sw = new ElaToggleSwitch(w);
                layout->addWidget(sw);
            }
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

    RegisterDataType _type;      // 信号量与模拟量

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
