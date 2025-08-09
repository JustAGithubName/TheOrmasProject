#ifndef GENERATEEXPMNHREPDLG_H
#define GENERATEEXPMNHREPDLG_H

#include "ui_GenerateExpMnhRepDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
/*
class GenerateExpMnhRep : public QDialog, public Ui::GenerateExpMnhReport
{
	Q_OBJECT
public:
	GenerateExpMnhRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~GenerateExpMnhRep();
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
	std::map<int, std::string> accMap;
	std::string prevFromMonth;
	std::string prevTillMonth;
};
*/
#endif //GENERATEExpMnhRepDLG_H