#ifndef CREATEACCBLEXPDLG_H
#define CREATEACCBLEXPDLG_H
#include "ui_CreateAccblExpDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include "CreateAccblRepDlg.h"
#include <QStandardItemModel>

class CreateAccblExpDlg : public QDialog, public Ui::CreateAccblExp
{
	Q_OBJECT
public:
	CreateAccblExpDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateAccblExpDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);
	std::string errorMessage;
	private slots:
	void CreateExpose();
	void DeleteExpose();
	void Close();
	void TextEditChanged();
public slots:
	
signals:
	void IncrementItemEditChanged(double);
	 void DecrementItemEditChanged(double);
private:
	BusinessLayer::ExpenseDocument *eDoc = new BusinessLayer::ExpenseDocument();
	void SetExposeParams(QString, double, double, int, int, int = 0);
	void FillEditElements(QString, double, double, int, int);
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
	void InitComboBox();
};

#endif //CreateAccblExpDLG_H