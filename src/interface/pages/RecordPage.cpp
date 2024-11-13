#include "RecordPage.h"

RecordPage::RecordPage(QWidget* parent)
{
	QWidget* mainWidget = new QWidget(this);

	addCentralWidget(mainWidget);
}

RecordPage::~RecordPage()
{
}
