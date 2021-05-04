#ifndef CREATEACCBLREPDLG_H
#define CREATEACCBLREPDLG_H

#include "ui_CreateAccblRepDlg.h"
#include "OrmasBL.h"
#include "MainForm.h"
#include <QStandardItemModel>

class CreateAccblRepDlg : public QDialog, public Ui::CreateAccountableRep
{
	Q_OBJECT
public:
	CreateAccblRepDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent = 0);
	~CreateAccblRepDlg();
	BusinessLayer::OrmasBL *dialogBL;
	bool FillDlgElements(QTableView*);

	std::vector<BusinessLayer::AccountableApprovement> approveVec;
	std::vector<BusinessLayer::AccountableDocumentListRelation> docListVec;
	std::vector<BusinessLayer::AccountableEntry> entryVec;
	std::vector<BusinessLayer::AccountablePaymentRelation> paymentVec;
	std::vector<BusinessLayer::AccountableWithdrawalRelation> withdrawalVec;
	std::vector<BusinessLayer::ExpenseDocument> expenseVec;

	QWidget* GetParentForm();

	std::string errorMessage;
	private slots:
	void CreateAccountableDocument();
	void EditAccountableDocument();
	void DeleteAccountableDocument(){};
	void Close();

	void OpenStsDlg();
	void OpenCmpDlg();
	void OpenEmpDlg();
	void OpenEmpAccDlg();
	void OpenAccblDlg();

	void AddPayment();
	void DeletePayment();

	void AddWithdrawal();
	void DeleteWithdrawal();

	void AddEntry();
	void DeleteEntry();

	void AddItem();
	void DeleteItem();

	void TextEditChanged();
	void SumEditChanged();
	void SumEditChangedByDelete();

	void AutoComplitePayment();
	void AutoCompliteWithdrawal();
	

	public slots:
	void SetID(int ID, QString childName);
	
	void DecrementItemSum(double itemSum);
	void DecrementEntrySum(double itemSum);
	void IncrementItemSum(double itemSum);
	void IncrementEntrySum(double itemSum);
signals:
	void CloseCreatedForms();

private:
	
	BusinessLayer::AccountableDocument *accountableDocument = new BusinessLayer::AccountableDocument();
	BusinessLayer::AccountableTransaction *accountableTransaction = new BusinessLayer::AccountableTransaction();
	BusinessLayer::AccountableUnionDocument *accountableUnionDocument = new BusinessLayer::AccountableUnionDocument();
	void SetAccountableUnionDocumentParams(BusinessLayer::AccountableDocument*,	BusinessLayer::AccountableTransaction*,
		std::vector<BusinessLayer::AccountableApprovement>*, std::vector<BusinessLayer::AccountableDocumentListRelation>*, std::vector<BusinessLayer::AccountableEntry>*,
		std::vector<BusinessLayer::AccountablePaymentRelation>*, std::vector<BusinessLayer::AccountableWithdrawalRelation>*, std::vector<BusinessLayer::ExpenseDocument>*);
	void FillEditElements(QString, double, QString, int, int, int);
	void SetAccountableDocumentParams(QString, double, QString, int, int, int = 0);
	void SetAccountableTransactionParams(double, double, double, double, int, int = 0);
	void SetEntryVec(QTableView*);
	void SetExposeVec(QTableView*);
	void SetWithdrawalVec(QTableView*);
	void SetPaymentVec(QTableView*);
	void SetApproveVec(int, int, QString, QString);
	
	void HideSpecButton();
	QDoubleValidator *vDouble = nullptr;
	QIntValidator *vInt = nullptr;
	std::map<std::string, int> statusMap;
	void InitComboBox();
	bool CheckAccess();
	QWidget* parentForm;
	MainForm* mainForm;
	QStandardItemModel *itemModel;
	QModelIndex mIndex;
};
#endif //CREATEACCBLREPDLG_H