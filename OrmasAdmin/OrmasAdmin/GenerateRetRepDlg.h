#ifndef GENERATERETREPDLG_H
#define GENERATERETREPDLG_H

#include "ui_GenerateRetRepDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"

class GenerateRetRep : public QDialog, public Ui::GenerateReturnReport
{
	Q_OBJECT
public:
	GenerateRetRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~GenerateRetRep();
	BusinessLayer::OrmasBL *dialogBL;
	std::string errorMessage = "";
	private slots:
	void Generate();
	void Close();
	void OpenEmpDlg();
	void CheckBoxChanged();
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
#endif //GENERATERETREPDLG_H