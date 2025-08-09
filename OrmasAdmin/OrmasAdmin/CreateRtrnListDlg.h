#ifndef CREATERTRNLISTDLG_H
#define CREATERTRNLISTDLG_H
#include "ui_CreateRtrnListDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateRtrnListDlg : public QDialog, public Ui::CreateRtrnList
{
	Q_OBJECT
public:
	CreateRtrnListDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateRtrnListDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	int returnID = 0;
	private slots:
	void AddProductToList();
	void EditProductInList();
	void DeleteProduct(){};
	void Close();
	void OpenRtrnDlg();
	void OpenProdDlg();
	void OpenStsDlg();
	void TextEditChanged();
	public slots:
	void SetID(int ID, QString childName);
signals:
	void DataIsChanged();
private:
	BusinessLayer::ReturnList *returnList = new BusinessLayer::ReturnList();
	void SetReturnListParams(int, int, double, double, int, int, int = 0);
	void FillEditElements(int, int, double, double, int, int);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	void InitComboBox();
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
	unsigned int employeeID = 0;
	unsigned int clientID = 0;
};
#endif //CREATEORDLITDLG_H