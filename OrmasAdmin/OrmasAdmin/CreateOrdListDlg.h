#ifndef CREATEORDLISTDLG_H
#define CREATEORDLISTDLG_H
#include "ui_CreateOrdListDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"

class CreateOrdListDlg : public QDialog, public Ui::CreateOrdList
{
	Q_OBJECT
public:
	CreateOrdListDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateOrdListDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	int orderID = 0;
	private slots:
	void AddProductToList();
	void EditProductInList();
	void DeleteProduct(){};
	void Close();
	void OpenOrdDlg();
	void OpenProdDlg();
	void OpenStsDlg();
	void TextEditChanged();
	public slots:
	void SetID(int ID, QString childName);
signals:
	void DataIsChanged();
private:
	BusinessLayer::OrderList *orderList = new BusinessLayer::OrderList();
	void SetOrderListParams(int, int, double, double, int, int, int = 0);
	void FillEditElements(int, int, double, double, int, int);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	void InitComboBox();
	QWidget* parentForm;
	MainForm* mainForm;
	unsigned int employeeID = 0;
	unsigned int clientID = 0;
};
#endif //CREATEORDLITDLG_H