#ifndef CREATESACCLMDLG_H
#define CREATESACCLMDLG_H
#include "ui_CreateSAccLmDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateSAccLmDlg : public QDialog, public Ui::CreateSubaccountLimit
{
	Q_OBJECT
public:
	CreateSAccLmDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateSAccLmDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateSubaccountLimit();
	void EditSubaccountLimit();
	void DeleteSubaccountLimit(){};
	void Close();
	void OpenSAccDlg();
	void TextEditChanged();
	public slots:
	void SetID(int ID, QString childName);
private:
	BusinessLayer::SubaccountLimit *subaccountLimit = new BusinessLayer::SubaccountLimit();
	void SetSubaccountLimitParams(int, double, double, int = 0);
	void FillEditElements(int, double, double);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};

#endif //CREATESAccLmDLG_H