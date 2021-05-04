#ifndef CREATEGRPDLG_H
#define CREATEGRPDLG_H
#include "ui_CreateGrpDlg.h"
#include "OrmasBL.h"
#include <QStandardItemModel>

class CreateGrpDlg : public QDialog, public Ui::CreateGroup
{
	Q_OBJECT
public:
	CreateGrpDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateGrpDlg(){};
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateGroup();
	void EditGroup();
	void DeleteGroup(){};
	void Close();
private:
	BusinessLayer::Group *group = new BusinessLayer::Group();
	void SetGroupParams(QString, QString, int = 0);
	void FillEditElements(QString, QString);
	QWidget* parentForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};

#endif //CREATEGrpDLG_H