#ifndef CREATEBrSAccDLG_H
#define CREATEBrSAccDLG_H

#include "ui_CreateBrSAccDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateBrSAccDlg : public QDialog, public Ui::CreateBranchSubaccount
{
	Q_OBJECT
public:
	CreateBrSAccDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateBrSAccDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateBranchSubaccount();
	void EditBranchSubaccount();
	void DeleteBranchSubaccount(){};
	void Close();
	void OpenSAccDlg();
	public slots:
	void SetID(int ID, QString childName);
signals:
	void CloseCreatedForms();
private:
	BusinessLayer::BranchSubaccountRelation *branchSubaccount = new BusinessLayer::BranchSubaccountRelation();
	void SetBranchSubaccountParams(int, int,int = 0);
	void FillEditElements(int, int);
	QIntValidator *vInt = nullptr;
	void InitComboBox();
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};
#endif //CREATEBrSAccDLG_H