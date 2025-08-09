#ifndef CREATEPRODCONRDLG_H
#define CREATEPRODCONRDLG_H

#include "ui_CreateProdConRDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>
 
class CreateProdConRDlg : public QDialog, public Ui::CreateProductionConsumeRaw
{
	Q_OBJECT
public:
	CreateProdConRDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateProdConRDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateConsumeRaw();
	void EditConsumeRaw();
	void DeleteConsumeRaw(){};
	void Close();
	void OpenEmpDlg();
	void OpenSkEmpDlg();
	void OpenStsDlg();
	void OpenProdConRListDlg();
	void StatusWasChenged();
	void TextEditChanged();
	public slots:
	void SetID(int ID, QString childName);
signals:
	void CloseCreatedForms();
private:
	BusinessLayer::ProductionConsumeRaw *pConsumeRaw = new BusinessLayer::ProductionConsumeRaw();
	void SetConsumeRawParams(int, QString, QString, int, double, double, int, int, int = 0);
	void FillEditElements(int, QString, QString, int, double, double, int, int);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	std::map<std::string, int> statusMap;
	void InitComboBox();
	QWidget* parentForm;
	MainForm* mainForm;
	bool CheckAccess();
	void AutoSelectUser();
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};
#endif //CreateProdConRDLG_H