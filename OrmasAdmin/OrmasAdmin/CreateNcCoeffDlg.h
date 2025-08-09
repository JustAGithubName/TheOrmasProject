#ifndef CREATENCCOEFFDLG_H
#define CREATENCCOEFFDLG_H
#include "ui_CreateNcCoeffDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateNcCoeffDlg : public QDialog, public Ui::CreateNetCostCoefficient
{
	Q_OBJECT
public:
	CreateNcCoeffDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateNcCoeffDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateNetCostCoefficient();
	void EditNetCostCoefficient();
	void DeleteNetCostCoefficient(){};
	void Close();
	void OpenPrdDlg();
	public slots:
	void SetID(int ID, QString childName);
private:
	BusinessLayer::NetCostCoefficient *netCostCoefficient = new BusinessLayer::NetCostCoefficient();
	void SetNetCostCoefficientParams(double, int, QString, int = 0);
	void FillEditElements(double, int, QString);
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};

#endif //CREATENCCOEFFDLG_H