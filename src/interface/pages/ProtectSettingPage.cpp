#include "ProtectSettingPage.h"

#include <QHBoxLayout>

#include "ElaScrollPageArea.h"
#include "ElaWindow.h"
#include "ElaText.h"
#include "ElaPushButton.h"

#include "BaseSetting.h"
#include "ProtectSettings.h"

ProtectSettingPage::ProtectSettingPage(QWidget* parent)
{
    // Ԥ�����ڱ���
    ElaWindow* window = dynamic_cast<ElaWindow*>(parent);
    setWindowTitle("ProtectSetting");

    // д�밴ť
    ElaPushButton* saveBtn = new ElaPushButton(this);
    connect(saveBtn, &QPushButton::clicked, this, [=] {
        for (auto c : _allSettings) {
            // �����Ҫ���ã�������
            if (c->needToSave())
            {
                // �ж�����ֵ�Ƿ����
                if (c->isVaild()) {
                    emit saveSetting(c->getStartAddr);
                }
                else {
                    // ��ʾ
                }
            }
        }
    });

    ElaText* themeText = new ElaText("�����ѹ", this);
    themeText->setWordWrap(false);
    themeText->setTextPixelSize(18);
#if 0
    _themeComboBox = new ElaComboBox(this);
    _themeComboBox->addItem("�ռ�ģʽ");
    _themeComboBox->addItem("ҹ��ģʽ");
    ElaScrollPageArea* themeSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* themeSwitchLayout = new QHBoxLayout(themeSwitchArea)

    ElaText* themeSwitchText = new ElaText("�����ѹ()", this);
    themeSwitchText->setWordWrap(false);
    themeSwitchText->setTextPixelSize(15);
    themeSwitchLayout->addWidget(themeSwitchText);
    themeSwitchLayout->addStretch();
    themeSwitchLayout->addWidget(_themeComboBox);

    connect(_themeComboBox, QOverload<int>::of(&ElaComboBox::currentIndexChanged), this, [=](int index) {
        if (index == 0)
        {
            eTheme->setThemeMode(ElaThemeType::Light);
        }
        else
        {
            eTheme->setThemeMode(ElaThemeType::Dark);
        }
        });
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeComboBox->blockSignals(true);
        if (themeMode == ElaThemeType::Light)
        {
            _themeComboBox->setCurrentIndex(0);
        }
        else
        {
            _themeComboBox->setCurrentIndex(1);
        }
        _themeComboBox->blockSignals(false);
        });
#else
    for (auto c : CELL_OV)
    {
        BaseSetting* set = new 
        _allSettings.append(c);
        QHBoxLayout* themeSwitchLayout = new QHBoxLayout(new BaseSetting(c));
    }
#endif


    ElaText* helperText = new ElaText("Ӧ�ó�������", this);
    helperText->setWordWrap(false);
    helperText->setTextPixelSize(18);

    _micaSwitchButton = new ElaToggleSwitch(this);
    ElaScrollPageArea* micaSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* micaSwitchLayout = new QHBoxLayout(micaSwitchArea);
    ElaText* micaSwitchText = new ElaText("������ĸЧ��(��ƽ̨)", this);
    micaSwitchText->setWordWrap(false);
    micaSwitchText->setTextPixelSize(15);
    micaSwitchLayout->addWidget(micaSwitchText);
    micaSwitchLayout->addStretch();
    micaSwitchLayout->addWidget(_micaSwitchButton);
    connect(_micaSwitchButton, &ElaToggleSwitch::toggled, this, [=](bool checked) {
        eApp->setIsEnableMica(checked);
        });

    _logSwitchButton = new ElaToggleSwitch(this);
    ElaScrollPageArea* logSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* logSwitchLayout = new QHBoxLayout(logSwitchArea);
    ElaText* logSwitchText = new ElaText("������־����", this);
    logSwitchText->setWordWrap(false);
    logSwitchText->setTextPixelSize(15);
    logSwitchLayout->addWidget(logSwitchText);
    logSwitchLayout->addStretch();
    logSwitchLayout->addWidget(_logSwitchButton);
    connect(_logSwitchButton, &ElaToggleSwitch::toggled, this, [=](bool checked) {
        ElaLog::getInstance()->initMessageLog(checked);
        if (checked)
        {
            qDebug() << "��־������!";
        }
        else
        {
            qDebug() << "��־�ѹر�!";
        }
        });

    _minimumButton = new ElaRadioButton("Minimum", this);
    _compactButton = new ElaRadioButton("Compact", this);
    _maximumButton = new ElaRadioButton("Maximum", this);
    _autoButton = new ElaRadioButton("Auto", this);
    _autoButton->setChecked(true);
    ElaScrollPageArea* displayModeArea = new ElaScrollPageArea(this);
    QHBoxLayout* displayModeLayout = new QHBoxLayout(displayModeArea);
    ElaText* displayModeText = new ElaText("������ģʽѡ��", this);
    displayModeText->setWordWrap(false);
    displayModeText->setTextPixelSize(15);
    displayModeLayout->addWidget(displayModeText);
    displayModeLayout->addStretch();
    displayModeLayout->addWidget(_minimumButton);
    displayModeLayout->addWidget(_compactButton);
    displayModeLayout->addWidget(_maximumButton);
    displayModeLayout->addWidget(_autoButton);
    connect(_minimumButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked)
        {
            window->setNavigationBarDisplayMode(ElaNavigationType::Minimal);
        }
        });
    connect(_compactButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked)
        {
            window->setNavigationBarDisplayMode(ElaNavigationType::Compact);
        }
        });
    connect(_maximumButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked)
        {
            window->setNavigationBarDisplayMode(ElaNavigationType::Maximal);
        }
        });
    connect(_autoButton, &ElaRadioButton::toggled, this, [=](bool checked) {
        if (checked)
        {
            window->setNavigationBarDisplayMode(ElaNavigationType::Auto);
        }
        });

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Setting");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addSpacing(30);
    centerLayout->addWidget(themeText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(themeSwitchArea);
    centerLayout->addSpacing(15);
    centerLayout->addWidget(helperText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(logSwitchArea);
    centerLayout->addWidget(micaSwitchArea);
    centerLayout->addWidget(displayModeArea);
    centerLayout->addStretch();
    centerLayout->setContentsMargins(0, 0, 0, 0);
    addCentralWidget(centralWidget, true, true, 0);
}

ProtectSettingPage::~ProtectSettingPage()
{
}
