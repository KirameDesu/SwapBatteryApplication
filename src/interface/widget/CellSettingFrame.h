#ifndef CELL_SETTING_FRAME
#define CELL_SETTING_FRAME

#include "ElaScrollPageArea.h"
#include "ElaScrollArea.h"

#include <QList>

#include "BaseSetting.h"
#include "SettingsBackgroundArea.h"

class CellSettingFrame : public SettingsBackgroundArea
{
public:
	explicit CellSettingFrame(QWidget* parent = nullptr)
		: SettingsBackgroundArea(parent)
	{
		this->setContentsMargins(30, 30, 30, 30);
	};
	~CellSettingFrame()
	{
		if (_cellSettingList.isEmpty())
			for (auto c : _cellSettingList)
				delete c->getWidget();
	}

	void addSetting(BaseSettingView* set) {
		_cellSettingList.append(set);
		this->layout()->addWidget(set->getWidget());
	}

	void setSettingsTitle(const QString& str)
	{
		_settingsTitle = str;
	}

	void addSettingList(QList<BaseSettingView*> setList) {
		_cellSettingList = setList;
		QVBoxLayout* l = qobject_cast<QVBoxLayout*>(this->layout());
		if (l) {
			// 设置标题
			l->addWidget(new ElaText(_settingsTitle, 20, this));
			l->addSpacing(20);
			// 设置项
			for (auto& c : _cellSettingList)
				l->addWidget(c->getWidget());
			// 底部添加伸缩因子
			l->addStretch();
			l->setSpacing(0);
		}
	}

	void addSettingList(QString title, QList<BaseSettingView*> setList) {
		_cellSettingList = setList;
		_settingsTitle = title;
		//ElaScrollPageArea* area = new ElaScrollPageArea(this);
		QVBoxLayout* l = new QVBoxLayout(this);
		if (l) {
			// 设置标题
			l->addWidget(new ElaText(_settingsTitle, 20, this));
			// 设置项
			for (auto& c : _cellSettingList) {
				//c->initWidget(this);
				l->addWidget(c->getWidget());
			}
			// 底部添加伸缩因子
			l->addStretch();
		}
	}

	void updateWidgetValue(QList<QVariant> valList) {
		for (int i = 0; i < valList.size() && i < _cellSettingList.size(); ++i) {
			/// 判断是整型还是bool
			QLineEdit* l = qobject_cast<QComboBox*>(_cellSettingList.at(i)->getValWidget())->lineEdit();
			if (l) {
				l->setText(valList.at(i).toString());
			}
		}
	}
private:
	QList<BaseSettingView*> _cellSettingList;
	QString _settingsTitle = "设置";
};

#endif // !CELL_SETTING_FRAME
