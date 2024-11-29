#ifndef BMS_CALIBRATE_PAGE_H
#define BMS_CALIBRATE_PAGE_H

#include <QVBoxLayout>
#include <QList>

#include "ElaTableView.h"
#include "CellRecordFrame.h"
#include "BasePage.h"


class BMSCalibratePage : public BasePage
{
	Q_OBJECT
public:
	explicit BMSCalibratePage(QWidget* parent = nullptr);
	~BMSCalibratePage();

	//void setSettings(SETTINGS_CLASS settings);
private:
	//static const int MAX_COLUMN = 2;
	//static const int MAX_ROW = 5;

	QList<CellRecordFrame*> _recordList;
	QVBoxLayout* _mainLayout{ nullptr };
	ElaTableView* listView{ nullptr };
};

#endif // !RECORD_PAGE_H
