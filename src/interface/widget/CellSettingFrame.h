#ifndef CELL_SETTING_FRAME
#define CELL_SETTING_FRAME

#include "ElaScrollPageArea.h"

#include <QList>

#include "BaseSetting.h"

class CellSettingFrame : public QWidget
{
public:
	explicit CellSettingFrame(QWidget* parent = nullptr)
		: QWidget(parent)
	{
		// 设置为垂直布局
		this->setLayout(new QVBoxLayout());
	};
	~CellSettingFrame() = default;

	void addSetting(BaseSetting* set) {
		_cellSettingList.append(set);
		this->layout()->addWidget(set->getWidget());
	}

	void setSettingsTitle(const QString& str)
	{
		_settingsTitle = str;
	}

	void addSettingList(QList<BaseSetting*> setList) {
		_cellSettingList = setList;
		QVBoxLayout* l = qobject_cast<QVBoxLayout*>(this->layout());
		if (l) {
			// 设置标题
			l->addWidget(new ElaText(_settingsTitle, 20, this));
			// 设置项
			for (auto& c : _cellSettingList)
				l->addWidget(c->getWidget());
			// 底部添加伸缩因子
			l->addStretch();
		}
	}

	void addSettingList(QString title, QList<BaseSetting*> setList) {
		_cellSettingList = setList;
		_settingsTitle = title;
		QVBoxLayout* l = qobject_cast<QVBoxLayout*>(this->layout());
		if (l) {
			// 设置标题
			l->addWidget(new ElaText(_settingsTitle, 20, this));
			// 设置项
			for (auto& c : _cellSettingList)
				l->addWidget(c->getWidget());
			// 底部添加伸缩因子
			l->addStretch();
		}
	}
private:
	QList<BaseSetting*> _cellSettingList;
	QString _settingsTitle = "设置";
};

#endif // !CELL_SETTING_FRAME
