#ifndef RECORD_PAGE_H
#define RECORD_PAGE_H

#include <QVBoxLayout>
#include <QList>

#include "ElaTableView.h"
#include "CellRecordFrame.h"
#include "BasePage.h"
#include "TableViewModel.h"

class RecordPage : public BasePage
{
	Q_OBJECT
public:
	explicit RecordPage(QWidget* parent = nullptr);
	~RecordPage();

protected:
	
private:
	QList<CellRecordFrame*> _recordList;
	QVBoxLayout* _mainLayout{ nullptr };
	ElaTableView* _tableView{ nullptr };
	TableViewModel* _tableModel{ nullptr };

	bool _isStart = false;

	Q_SLOT void onRecordStartTimeout();

signals:
	Q_SIGNAL void fetchOneRecord();
};

#endif // !RECORD_PAGE_H
