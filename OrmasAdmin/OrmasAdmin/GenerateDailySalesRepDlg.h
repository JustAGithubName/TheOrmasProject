#ifndef GENERATEDAILYSALESREPDLG_H
#define GENERATEDAILYSALESREPDLG_H

#include "ui_GenerateDailySalesRepDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"

class GenerateDailySalesRep : public QDialog, public Ui::GenerateDailySalesReport
{
	Q_OBJECT
public:
	GenerateDailySalesRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~GenerateDailySalesRep();
	BusinessLayer::OrmasBL *dialogBL;
	std::string errorMessage = "";
	private slots:
	void Generate();
	void Close();
	void OpenEmpDlg();
	public slots:
	void SetID(int ID, QString childName);
signals:
	void CloseCreatedForms();
private:
	QWidget* parentForm;
	MainForm* mainForm;
	QIntValidator *vInt = nullptr;
};
#endif