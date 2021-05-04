#ifndef GENERATEWrRepRepDLG_H
#define GENERATEWrRepRepDLG_H

#include "ui_GenerateWrRepDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"

class GenerateWrRep : public QDialog, public Ui::GenerateWarehouseReport
{
	Q_OBJECT
public:
	GenerateWrRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~GenerateWrRep();
	BusinessLayer::OrmasBL *dialogBL;
	std::string errorMessage = "";
	private slots:
	void Generate();
	void Close();
	
signals:
	void CloseCreatedForms();
private:
	QWidget* parentForm;
	MainForm* mainForm;
	void InitComboBox();
	std::map<int, std::string> accMap;
};
#endif