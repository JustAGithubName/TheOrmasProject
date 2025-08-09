#ifndef GENERATECMPBLCDLG_H
#define GENERATECMPBLCDLG_H

#include "ui_GenerateCmpBlcDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"

class GenerateCmpBlc : public QDialog, public Ui::GenerateCompanyBalance
{
	Q_OBJECT
public:
	GenerateCmpBlc(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~GenerateCmpBlc();
	BusinessLayer::OrmasBL *dialogBL;
	std::string errorMessage = "";
	private slots:
	void Generate();
	void Close();
	void ChangeRadio();
private:
	BusinessLayer::AccountHistory *aHistory = new BusinessLayer::AccountHistory();
	QWidget* parentForm;
	MainForm* mainForm;
	std::string prevFromMonth;
	std::string prevTillMonth;
	void CalculatePrevMonth(std::string, std::string, std::string&, std::string&);
	int CalculateMonthCount(std::string, std::string);
};
#endif