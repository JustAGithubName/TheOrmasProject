#ifndef GENERATEAGENTREPDLG_H
#define GENERATEAGENTREPDLG_H

#include "ui_GenerateAgentRepDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"

class GenerateAgentRep : public QDialog, public Ui::GenerateAgentReport
{
	Q_OBJECT
public:
	GenerateAgentRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~GenerateAgentRep();
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
	std::string prevFromMonth;
	std::string prevTillMonth;
	QIntValidator *vInt = nullptr;
	void CalculatePrevMonth(std::string, std::string, std::string&, std::string&);

	 
};
#endif