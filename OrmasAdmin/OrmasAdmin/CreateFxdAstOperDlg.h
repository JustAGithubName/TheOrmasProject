#ifndef CREATEFxdAstOperDLG_H
#define CREATEFxdAstOperDLG_H
#include "ui_CreateFxdAstOperDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateFxdAstOperDlg : public QDialog, public Ui::CreateFxdAstOper
{
	Q_OBJECT
public:
	CreateFxdAstOperDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateFxdAstOperDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateFixedAssetsOperation();
	void EditFixedAssetsOperation();
	void DeleteFixedAssetsOperation(){};
	void Close();
	void OpenFxdAstDlg();
	void TextEditChanged();
	public slots:
	void SetID(int ID, QString childName);
private:
	BusinessLayer::FixedAssetsOperations *fixedAssetsOperations = new BusinessLayer::FixedAssetsOperations();
	void SetFixedAssetsOperationParams(QString, QString, double, QString, QString, int, QString, int = 0);
	void FillEditElements(QString, QString, double, QString, QString, int, QString);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};

#endif //CREATEFxdAstOperDLG_H