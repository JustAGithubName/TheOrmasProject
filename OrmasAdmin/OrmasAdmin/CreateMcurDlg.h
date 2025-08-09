#ifndef CREATEMCURDLG_H
#define CREATEMCURDLG_H
#include "ui_CreateMcurDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateMcurDlg : public QDialog, public Ui::CreateMulticurrency
{
	Q_OBJECT
public:
	CreateMcurDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateMcurDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateMulticurrency();
	//void EditMulticurrency();
	void DeleteMulticurrency(){};
	void Close();
	void OpenStsDlg();
	void OpenSAccDlg();
	void TextEditChanged();
	void GenerateNumber();
	void GenerateTwoNumbers();
	//void ClearTabs();
	void OpenCOADlg();
	public slots:
	void SetID(int ID, QString childName);
private:
	BusinessLayer::Multicurrency *multicurrency = new BusinessLayer::Multicurrency();
	void SetMulticurrencyParams(int, int, QString, int = 0);
	void FillEditElements(int, int, QString);
	int GetParentAccNumber(std::string subNumber);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	void InitComboBox();
	QWidget* parentForm;
	MainForm* mainForm;
	int parentAccID = 0;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
	void SortTable(QTableView *table);
};


#endif