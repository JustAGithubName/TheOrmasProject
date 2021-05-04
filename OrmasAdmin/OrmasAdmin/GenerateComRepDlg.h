#ifndef GENERATECOMREPDLG_H
#define GENERATECOMREPDLG_H

#include "ui_GenerateComRepDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"

class GenerateComRep : public QDialog, public Ui::GenerateCommonReport
{
	Q_OBJECT
public:
	GenerateComRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~GenerateComRep();
	BusinessLayer::OrmasBL *dialogBL;
	std::string errorMessage = "";
	private slots:
	void Generate();
	void Close();
private:
	QWidget* parentForm;
	MainForm* mainForm;
	std::string prevFromMonth;
	std::string prevTillMonth;
};
#endif