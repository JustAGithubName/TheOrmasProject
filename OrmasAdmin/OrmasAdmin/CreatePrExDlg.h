#ifndef CREATEPREXDLG_H
#define CREATEPREXDLG_H
#include "ui_CreatePrExDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreatePrExDlg : public QDialog, public Ui::CreatePriceExtension
{
	Q_OBJECT
public:
	CreatePrExDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreatePrExDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreatePriceExtension();
	void EditPriceExtension();
	void DeletePriceExtension(){};
	void Close();
	void OpenPrdDlg();
	void OpenBrhDlg();
	void OpenLcnDlg();
	void OpenCltDlg();
	void OpenEmpDlg();
	void TextEditChanged();
	public slots:
	void SetID(int ID, QString childName);
private:
	BusinessLayer::PriceExtension *priceExtension = new BusinessLayer::PriceExtension();
	void SetPriceExtensionParams(int, double, QString, int, int, int, int, int, int = 0);
	void FillEditElements(int, double, QString, int, int, int, int, int);
	QDoubleValidator *vDouble = nullptr;
	QDoubleValidator *vDouble2 = nullptr;
	QIntValidator *vInt = nullptr;
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};

#endif //CREATEPREXDLG_H