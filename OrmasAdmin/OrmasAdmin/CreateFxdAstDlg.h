#ifndef CREATEFXDASTDLG_H
#define CREATEFXDASTDLG_H

#include "ui_CreateFxdAstDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateFxdAstDlg : public QDialog, public Ui::CreateFxdAst
{
	Q_OBJECT
public:
	CreateFxdAstDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateFxdAstDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateFixedAssets();
	void EditFixedAssets();
	void DeleteFixedAssets(){};
	void Close();
	void OpenStsDlg();
	void OpenAccDlg();
	void OpenPurDlg();
	void OpenActDlg();
	void OpenSpecDlg();
	void TextEditChanged();
	void CalculateMonthChanged();
	public slots:
	void SetID(int ID, QString childName);
signals:
	void CloseCreatedForms();
private:
	BusinessLayer::FixedAssetsUnion *fixedAssetsUnion = new BusinessLayer::FixedAssetsUnion();
	BusinessLayer::FixedAssets *fixedAssets = new BusinessLayer::FixedAssets();
	BusinessLayer::FixedAssetsSpecification *fixedAssetsSpecification = new BusinessLayer::FixedAssetsSpecification();
	BusinessLayer::FixedAssetsDetails *fixedAssetsDetails = new BusinessLayer::FixedAssetsDetails();
	BusinessLayer::PostingFixedAssets *postingFixedAssets = new BusinessLayer::PostingFixedAssets();
	void SetFixedAssetsUnionParams(BusinessLayer::FixedAssets*, BusinessLayer::FixedAssetsSpecification*, BusinessLayer::FixedAssetsDetails*, BusinessLayer::PostingFixedAssets*);
	void SetFixedAssetsParams(int, QString, double, double, int, QString, QString, QString, QString, int, int, int = 0);
	void FillEditElements(int, QString, double, double, int, QString, QString, QString, QString, int, int, int);
	void SetFixedAssetsSpecificationParams(QString, QString, QString, QString, QString, QString, QString, int = 0);
	void SetFixedAssetsDetailsParams(int, int, int, QString, int, int, QString, double, int = 0);
	void SetPostingFixedAssetsParams(int, int, int, int, int, int = 0);
	void HideSpecButton();
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	std::map<std::string, int> statusMap;
	void InitComboBox();
	void GenerateInventoryNumber();
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};
#endif //CREATEFxdAstDLG_H