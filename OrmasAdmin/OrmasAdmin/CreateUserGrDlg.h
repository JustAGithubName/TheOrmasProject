#ifndef CREATEUSERGRDLG_H
#define CREATEUSERGRDLG_H

#include "ui_CreateUserGrDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateUserGrDlg : public QDialog, public Ui::CreateUserGroup
{
	Q_OBJECT
public:
	CreateUserGrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateUserGrDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateUserGroup();
	void EditUserGroup();
	void DeleteUserGroup(){};
	void Close();
	void OpenUserDlg();
	void OpenGroupDlg();
	public slots:
	void SetID(int ID, QString childName);

private:
	BusinessLayer::UserGroupRelation *userGroup = new BusinessLayer::UserGroupRelation();
	void SetUserGroupParams(int, int, int = 0);
	void FillEditElements(int, int);
	QIntValidator *vInt = nullptr;
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};
#endif //CREATEUserGrDLG_H