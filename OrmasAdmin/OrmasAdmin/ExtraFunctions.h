#ifndef EXTRAFUNCTIONS_H
#define EXTRAFUNCTIONS_H
#include "QTWidgets/QMdiSubWindow"
#include <QString>
#include <QTableView>
#include <QModelIndex>

inline QWidget* IsWindowExist(QList <QMdiSubWindow *> mList, QString formName)
{
	for (auto subWindow : mList)
	{
		if (subWindow->widget()->objectName() == formName)
		{
			return subWindow->widget();
		}
	}
	return nullptr;
}

inline QMdiSubWindow* GetSubWindow(QList <QMdiSubWindow *> mList, QString formName)
{
	for (auto subWindow : mList)
	{
		if (subWindow->widget()->objectName() == formName)
		{
			return subWindow;
		}
	}
	return nullptr;
}

inline int GetIDFromTable(QTableView* table, std::string& errorMessage)
{
	int id = 0;
	QModelIndex mIndex = table->selectionModel()->currentIndex();
	try
	{
		id = table->model()->data(table->model()->index(mIndex.row(), 0)).toInt();
	}
	catch (...)
	{
		errorMessage = "Please select row, deleting is unpossible!";
	}
	return id;
}

inline int GetIDFromTable(QTableView* table, QModelIndex mIndex)
{
	int id = 0;
	try
	{
		id = table->model()->data(table->model()->index(mIndex.row(), 0)).toInt();
	}
	catch (...)
	{
	}
	return id;
}


#endif //EXTRAFUNCTIONS_H