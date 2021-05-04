#ifndef CREATESTOCKLIMITDLG_H
#define CREATESTOCKLIMITDLG_H
#include "ui_CreateStockLmDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateStockLimitDlg : public QDialog, public Ui::CreateStockLimit
{
	Q_OBJECT
public:
	CreateStockLimitDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateStockLimitDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void AddStockLimit();
	void EditStockLimit();
	void DeleteStockLimit(){};
	void Close();
	void OpenProdDlg();
	void OpenStockDlg();
	void TextEditChanged();
	public slots:
	void SetID(int ID, QString childName);
private:
	BusinessLayer::StockLimit *stockLimit = new BusinessLayer::StockLimit();
	void SetStockLimitParams(int, int, double, double, int = 0);
	void FillEditElements(int, int, double, double);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};
#endif //CREATEStockLimitDLG_H