#ifndef GENERATEFXASTRepDLG_H
#define GENERATEFXASTRepDLG_H

#include "ui_GenerateFxAstRepDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"

class GenerateFxAstRep : public QDialog, public Ui::GenerateFixedAssetsReport
{
	Q_OBJECT
public:
	GenerateFxAstRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent = 0);
	~GenerateFxAstRep();
	BusinessLayer::OrmasBL *dialogBL;
	std::string errorMessage = "";
	private slots:
	void Generate();
	void Close();
	void CheckBoxChanged();
signals:
	void CloseCreatedForms();
private:
	QWidget* parentForm;
	MainForm* mainForm;
	void InitComboBox();
	std::map<int, std::string> accMap;
};
#endif