#ifndef RECORD_PAGE_H
#define RECORD_PAGE_H

#include <QVBoxLayout>
#include <QList>

#include "ElaTableView.h"
#include "CellRecordFrame.h"
#include "BasePage.h"


class RecordPage : public BasePage
{
	Q_OBJECT
public:
	explicit RecordPage(QWidget* parent = nullptr);
	~RecordPage();

	//void setSettings(SETTINGS_TYPE settings);
private:
	//static const int MAX_COLUMN = 2;
	//static const int MAX_ROW = 5;

	QList<CellRecordFrame*> _recordList;
	QVBoxLayout* _mainLayout{ nullptr };
	ElaTableView* listView{ nullptr };
};

#endif // !RECORD_PAGE_H
