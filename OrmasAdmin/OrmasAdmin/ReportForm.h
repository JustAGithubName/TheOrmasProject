#ifndef REPORTFORM_H
#define REPORTFORM_H

#include "ui_ReportForm.h"
#include "OrmasBL.h"
#include <QStandardItem>
#include <QStringList>
#include <QDialog>


class ReportForm : public QWidget, public Ui::ReportForm
{
	Q_OBJECT
public:
	ReportForm(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~ReportForm(){};
	std::string fromDate = "";
	std::string tillDate = "";
	std::string prevMonthEndDate = "";
	void FillStockTable(std::string, std::string, int, std::string);
	void FillAccCrdTable(std::string, std::string, int, std::string);
	void FillAccListCrdTable(std::string, std::string, std::vector<int>, std::string, int parentAccID);
	void FillSubaccCrdTable(std::string, std::string, std::vector<int>, std::string);
	void FillAccCrdTable(std::string, std::string, std::string);
	std::string warehouseName = "";

	private slots:
	void View();
	void ViewWTBSRaw();
	void ViewWTBSProduct();
	void ViewWTBSProduction();
	void ViewAcc();
	void ViewParentAcc();
	void ViewParentSubAcc();
	void ViewOneAcc();
	void ViewSubacc();
	std::string GenerateDocumentInfo(BusinessLayer::FullExtendedEntryView view);
signals:
	void SendID(std::string, std::string, int, std::string);

public slots:
	void CloseReportForm();
	void GetIDValue(QModelIndex index);
	void GeneratOneAccReport(std::string, std::string, int, std::string);
public:
	BusinessLayer::OrmasBL* reportFormBL;
	QWidget* parentForm;
	QDialog* parentDialog;
	BusinessLayer::User* loggedUser;
	std::string errorMessage = "";
};
#endif //ReportFORM_H

