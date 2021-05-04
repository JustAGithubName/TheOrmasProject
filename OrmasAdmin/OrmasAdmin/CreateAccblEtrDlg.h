#ifndef CREATEACCBLETRDLG_H
#define CREATEACCBLETRDLG_H
#include "ui_CreateAccblEtrDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include "CreateAccblRepDlg.h"
#include <QStandardItemModel>

class CreateAccblEtrDlg : public QDialog, public Ui::CreateAccblEntry
{
	Q_OBJECT
public:
	CreateAccblEtrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateAccblEtrDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	int accountableID = 0;
	private slots:
	void CreateEntry();
	void DeleteEntry();
	void Close();
	void OpenDAccDlg();
	void OpenCAccDlg();
	void OpenDSAccDlg();
	void OpenCSAccDlg();
	void DATextChanged();
	void CATextChanged();
	void TextEditChanged();
	public slots:
	void SetID(int ID, QString childName);
signals:
	void IncrementEntryEditChanged(double);
	void DecrementEntryEditChanged(double);
private:
	BusinessLayer::AccountableEntry *entry = new BusinessLayer::AccountableEntry();
	void SetEntryParams(int, int, double, int, int, int, int = 0);
	void FillEditElements(int, int, double, int, int, int);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
	void InitComboBox();
	void AccountIsChenged();
};

#endif //CreateAccblEtrDLG_H