#include "stdafx.h"

#include "CreateAccblRepDlg.h"
#include "CreateAccblEtrDlg.h"
#include "CreateAccblExpDlg.h"
#include "DataForm.h"

#include <map>

CreateAccblRepDlg::CreateAccblRepDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);

	paymentTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	paymentTableView->verticalHeader()->hide();
	paymentTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	paymentTableView->setSelectionMode(QAbstractItemView::SingleSelection);


	withdrawalTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	withdrawalTableView->verticalHeader()->hide();
	withdrawalTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	withdrawalTableView->setSelectionMode(QAbstractItemView::SingleSelection);


	entryTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	entryTableView->verticalHeader()->hide();
	entryTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	entryTableView->setSelectionMode(QAbstractItemView::SingleSelection);


	itemTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	itemTableView->verticalHeader()->hide();
	itemTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	itemTableView->setSelectionMode(QAbstractItemView::SingleSelection);



	
	//setModal(true);
	dialogBL = ormasBL;
	
	
	
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);

	QStandardItemModel *itemModelDoc = new QStandardItemModel(dataFormParent);
	QStringList headerDoc;
	headerDoc << QObject::tr("ID") << QObject::tr("Expense name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Measure ID") << QObject::tr("Currency ID");
	itemModelDoc->setHorizontalHeaderLabels(headerDoc);
	itemTableView->setModel(itemModelDoc);

	QStandardItemModel* itemModelEntry = new QStandardItemModel(dataFormParent);
	QStringList headerEntry;
	headerEntry << QObject::tr("ID") << QObject::tr("Debit account ID") << QObject::tr("Debit subaccount ID")
		<< QObject::tr("Value") << QObject::tr("Credit account ID") << QObject::tr("Credit subaccount ID") << QObject::tr("Accountable document ID");
	itemModelEntry->setHorizontalHeaderLabels(headerEntry);
	entryTableView->setModel(itemModelEntry);

	QStandardItemModel *itemModelPayment = new QStandardItemModel(dataFormParent);
	QStringList headerPayment;
	headerPayment << QObject::tr("ID") << QObject::tr("Accountable document ID") << QObject::tr("Payment ID");
	itemModelPayment->setHorizontalHeaderLabels(headerPayment);
	paymentTableView->setModel(itemModelPayment);

	QStandardItemModel *itemModelWithdsrawal = new QStandardItemModel(dataFormParent);
	QStringList headerWithdrawal;
	headerWithdrawal << QObject::tr("ID") << QObject::tr("Accountable document ID") << QObject::tr("Withdrawal ID");
	itemModelWithdsrawal->setHorizontalHeaderLabels(headerWithdrawal);
	withdrawalTableView->setModel(itemModelWithdsrawal);

	
	appointmentEdit->setMaxLength(300);
	
	
	prevRemainderEdit->setValidator(vDouble);
	prevRemainderEdit->setMaxLength(20);
	prevOverrunEdit->setValidator(vDouble);
	prevOverrunEdit->setMaxLength(20);

	totalEdit->setValidator(vDouble);
	totalEdit->setMaxLength(20);
	spentEdit->setValidator(vDouble);
	spentEdit->setMaxLength(20);
	remainderEdit->setValidator(vDouble);
	remainderEdit->setMaxLength(20);
	overrunEdit->setValidator(vDouble);
	overrunEdit->setMaxLength(20);
	
	entryTotalSumEdit->setValidator(vDouble);
	entryTotalSumEdit->setMaxLength(20);

	itemSumEdit->setValidator(vDouble);
	itemSumEdit->setMaxLength(20);


	companyEdit->setValidator(vInt);
	directorEdit->setValidator(vInt);
	employeeEdit->setValidator(vInt);
	accountantEdit->setValidator(vInt);
	statusEdit->setValidator(vInt);


	InitComboBox();

	//sourceGbx->hide();

	if (true == updateFlag)
	{
		tab->setDisabled(true);
		severalDocTab->setDisabled(true);
		cmpBtn->setDisabled(true);
		empBtn->setDisabled(true);
		directorBtn->setDisabled(true);
		accontantBtn->setDisabled(true);
		reprotDateEdit->setDisabled(true);
		approveDateEdit->setDisabled(true);
		appointmentEdit->setDisabled(true);
		addPaymentBtn->setDisabled(true);
		deletePaymentBtn->setDisabled(true);
		addWithdrawalBtn->setDisabled(true);
		deleteWithdrawalBtn->setDisabled(true);
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAccblRepDlg::EditAccountableDocument);
	}
	else
	{
		reprotDateEdit->setDateTime(QDateTime::currentDateTime());
		approveDateEdit->setDateTime(QDateTime::currentDateTime());
		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("OPEN");
		std::string statusFilter = dialogBL->GenerateFilter<BusinessLayer::Status>(status);
		std::vector<BusinessLayer::Status> statusVector = dialogBL->GetAllDataForClass<BusinessLayer::Status>(errorMessage, statusFilter);
		delete status;
		if (statusVector.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Status are empty please contact with Admin")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		statusEdit->setText(QString::number(statusVector.at(0).GetID()));
		statusPh->setText(statusVector.at(0).GetName().c_str()); 

		BusinessLayer::User director;
		BusinessLayer::User accountant;
		BusinessLayer::Company company;
		BusinessLayer::Role role;

		if (role.GetRoleIDByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "DIRECTOR", errorMessage))
		{
			director.SetRoleID(role.GetID());
			std::string roleIDFilter = director.GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::UserView> userVector = dialogBL->GetAllDataForClass<BusinessLayer::UserView>(errorMessage, roleIDFilter);
			if (userVector.size() > 0)
			{
				directorPh->setText(userVector.at(0).GetSurname().c_str() + QString(" ") + userVector.at(0).GetName().c_str());
				directorEdit->setText(QString::number(userVector.at(0).GetID()));
			}
		}

		if (accountant.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), dialogBL->loggedUser->GetID(), errorMessage))
		{
			accountantPh->setText(accountant.GetSurname().c_str() + QString(" ") + accountant.GetName().c_str());
			accountantEdit->setText(QString::number(accountant.GetID()));
		}

		std::vector<BusinessLayer::Company> companyVector = dialogBL->GetAllDataForClass<BusinessLayer::Company>(errorMessage);
		if (companyVector.size())
		{
			companyEdit->setText(QString::number(companyVector.at(0).GetID()));
			companyPh->setText(companyVector.at(0).GetName().c_str());
		}

		QObject::connect(okBtn, &QPushButton::released, this, &CreateAccblRepDlg::CreateAccountableDocument);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAccblRepDlg::Close);
	QObject::connect(stsBtn, &QPushButton::released, this, &CreateAccblRepDlg::OpenStsDlg);
	QObject::connect(cmpBtn, &QPushButton::released, this, &CreateAccblRepDlg::OpenCmpDlg);
	QObject::connect(directorBtn, &QPushButton::released, this, &CreateAccblRepDlg::OpenEmpDlg);
	QObject::connect(empBtn, &QPushButton::released, this, &CreateAccblRepDlg::OpenAccblDlg);
	QObject::connect(accontantBtn, &QPushButton::released, this, &CreateAccblRepDlg::OpenEmpAccDlg);

	QObject::connect(addPaymentBtn, &QPushButton::released, this, &CreateAccblRepDlg::AddPayment);
	QObject::connect(deletePaymentBtn, &QPushButton::released, this, &CreateAccblRepDlg::DeletePayment);

	QObject::connect(addWithdrawalBtn, &QPushButton::released, this, &CreateAccblRepDlg::AddWithdrawal);
	QObject::connect(deleteWithdrawalBtn, &QPushButton::released, this, &CreateAccblRepDlg::DeleteWithdrawal);

	QObject::connect(addEntryBtn, &QPushButton::released, this, &CreateAccblRepDlg::AddEntry);
	QObject::connect(deleteEntryBtn, &QPushButton::released, this, &CreateAccblRepDlg::DeleteEntry);

	QObject::connect(addItemBtn, &QPushButton::released, this, &CreateAccblRepDlg::AddItem);
	QObject::connect(deleteItemBtn, &QPushButton::released, this, &CreateAccblRepDlg::DeleteItem);

	QObject::connect(itemSumEdit, &QLineEdit::textChanged, this, &CreateAccblRepDlg::SumEditChanged);
	QObject::connect(totalEdit, &QLineEdit::textChanged, this, &CreateAccblRepDlg::SumEditChangedByDelete);


	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	
}

CreateAccblRepDlg::~CreateAccblRepDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();

}

QWidget* CreateAccblRepDlg::GetParentForm()
{
	return parentForm;
}


void CreateAccblRepDlg::SetAccountableDocumentParams(QString dDate, double dValue, QString expAssignment, int accountableID, int statusID, int id)
{
	accountableDocument->SetDate(dDate.toUtf8().constData());
	accountableDocument->SetValue(dValue);
	accountableDocument->SetExpenseAssignment(expAssignment.toUtf8().constData());
	accountableDocument->SetAccountableID(accountableID);
	accountableDocument->SetStatusID(statusID);
	accountableDocument->SetID(id);

}


void CreateAccblRepDlg::SetAccountableTransactionParams(double residualValue, double totalValue, double spentValue, double diffValue, int accblDocID, int id)
{
	accountableTransaction->SetResidualValue(residualValue);
	accountableTransaction->SetTotalValue(totalValue);
	accountableTransaction->SetSpentValue(spentValue);
	accountableTransaction->SetDifferenceValue(diffValue);
	accountableTransaction->SetAccountableDocumentID(accblDocID);
	accountableTransaction->SetID(id);
}

void CreateAccblRepDlg::SetEntryVec(QTableView* entryTable)
{
	int id = 0;
	int dAccID = 0;
	int dSAccID = 0;
	double value = 0;
	int cAccID = 0;
	int cSAccID = 0;
	int aDocID = 0;
	BusinessLayer::AccountableEntry aEntry;
	if (entryTable->model()->rowCount() > 0)
	{
		for (int i = 0; i < entryTable->model()->rowCount(); i++)
		{
			id = 0;
			dAccID = 0;
			dSAccID = 0;
			value = 0;
			cAccID = 0;
			cSAccID = 0;
			aDocID = 0;
			id = (entryTable->model()->index(i, 0)).data().toInt();
			dAccID = (entryTable->model()->index(i, 1)).data().toInt();
			dSAccID = (entryTable->model()->index(i, 2)).data().toInt();
			value = (entryTable->model()->index(i, 3)).data().toDouble();
			cAccID = (entryTable->model()->index(i, 4)).data().toInt();
			cSAccID = (entryTable->model()->index(i, 5)).data().toInt();
			aDocID = (entryTable->model()->index(i, 6)).data().toInt();
			aEntry.SetID(id);
			aEntry.SetDebitAccountID(dAccID);
			aEntry.SetDebitSubaccountID(dSAccID);
			aEntry.SetValue(value);
			aEntry.SetCreditAccountID(cAccID);
			aEntry.SetCreditSubaccountID(cSAccID);
			aEntry.SetAccountableDocumentID(aDocID);
			entryVec.push_back(aEntry);
		}
	}
}

void CreateAccblRepDlg::SetExposeVec(QTableView* exposeTable)
{
	int id = 0;
	std::string name = "";
	double count = 0;
	double sum = 0;
	int mID = 0;
	int cID = 0;
	
	BusinessLayer::ExpenseDocument aExpose;
	if (exposeTable->model()->rowCount() > 0)
	{
		for (int i = 0; i < exposeTable->model()->rowCount(); i++)
		{
			id = 0;
			name = "";
			count = 0;
			sum = 0;
			mID = 0;
			cID = 0;

			id = (exposeTable->model()->index(i, 0)).data().toInt();
			name = (exposeTable->model()->index(i, 1)).data().toString().toStdString();
			count = (exposeTable->model()->index(i, 2)).data().toDouble();
			sum = (exposeTable->model()->index(i, 3)).data().toDouble();
			mID = (exposeTable->model()->index(i, 4)).data().toInt();
			cID = (exposeTable->model()->index(i, 5)).data().toInt();
			
			aExpose.SetID(id);
			aExpose.SetExpenseName(name);
			aExpose.SetCount(count);
			aExpose.SetSum(sum);
			aExpose.SetMeasureID(mID);
			aExpose.SetCurrencyID(cID);
			
			expenseVec.push_back(aExpose);
		}
	}
}

void CreateAccblRepDlg::SetPaymentVec(QTableView* withdrawalTable)
{
	int id = 0;
	int docID = 0;
	int paymentID = 0;
	BusinessLayer::AccountablePaymentRelation pr;
	if (withdrawalTable->model()->rowCount() > 0)
	{
		for (int i = 0; i < withdrawalTable->model()->rowCount(); i++)
		{
			id = 0;
			docID = 0;
			paymentID = 0;
			id = (withdrawalTable->model()->index(i, 0)).data().toInt();
			docID = (withdrawalTable->model()->index(i, 1)).data().toInt();
			paymentID = (withdrawalTable->model()->index(i, 2)).data().toInt();
			if (paymentID > 0)
			{
				pr.Clear();
				pr.SetID(id);
				pr.SetAccountableDocumentID(docID);
				pr.SetPaymentID(paymentID);
				paymentVec.push_back(pr);
			}
		}
	}
}

void CreateAccblRepDlg::SetWithdrawalVec(QTableView* paymentTable)
{
	int id = 0;
	int docID = 0;
	int withdrawalID = 0;
	BusinessLayer::AccountableWithdrawalRelation wr;
	if (paymentTable->model()->rowCount() > 0)
	{
		for (int i = 0; i < paymentTable->model()->rowCount(); i++)
		{
			id = 0;
			docID = 0;
			withdrawalID = 0;
			id = (paymentTable->model()->index(i, 0)).data().toInt();
			docID = (paymentTable->model()->index(i, 1)).data().toInt();
			withdrawalID = (paymentTable->model()->index(i, 2)).data().toInt();
			if (withdrawalID > 0)
			{
				wr.Clear();
				wr.SetID(id);
				wr.SetAccountableDocumentID(docID);
				wr.SetWithdrawalID(withdrawalID);
				withdrawalVec.push_back(wr);
			}
		}
	}
}

void CreateAccblRepDlg::SetApproveVec(int dirID, int accoID, QString dDate, QString expDate)
{
	BusinessLayer::AccountableApprovement aAppr;
	if (dirID > 0)
	{
		aAppr.SetDirectorID(dirID);
		aAppr.SetApproveDate(expDate.toStdString());
		approveVec.push_back(aAppr);
	}
	aAppr.Clear();
	if (accoID > 0)
	{
		aAppr.SetAccounantID(accoID);
		aAppr.SetApproveDate(dDate.toStdString());
		approveVec.push_back(aAppr);
	}
}

void CreateAccblRepDlg::SetAccountableUnionDocumentParams(BusinessLayer::AccountableDocument* aDocument, BusinessLayer::AccountableTransaction* aTransaction,
	std::vector<BusinessLayer::AccountableApprovement>* aApprovement, std::vector<BusinessLayer::AccountableDocumentListRelation>* aDocumentList, 
	std::vector<BusinessLayer::AccountableEntry>* aEntry,
	std::vector<BusinessLayer::AccountablePaymentRelation>* aPayment, std::vector<BusinessLayer::AccountableWithdrawalRelation>* aWithdrawal, 
	std::vector<BusinessLayer::ExpenseDocument>* eDocument)
{
	accountableUnionDocument->SetAccountableDocument(aDocument);
	accountableUnionDocument->SetAccountableTransaction(aTransaction);
	accountableUnionDocument->SetAccountableApprovementVector(aApprovement);
	accountableUnionDocument->SetAccountableDocumentListVector(aDocumentList);
	accountableUnionDocument->SetAccountableEntryVector(aEntry);
	accountableUnionDocument->SetAccountablePaymentVector(aPayment);
	accountableUnionDocument->SetAccountableWithdrawalVector(aWithdrawal);
	accountableUnionDocument->SetExpenseDocumentVector(eDocument);
}

void CreateAccblRepDlg::FillEditElements(QString aDate, double aValue, QString epAssignment, int accID, int statusID, int id)
{
	BusinessLayer::AccountableApprovement accountableApprovement;
	BusinessLayer::AccountableDocumentListRelation accountableDocumentList;
	BusinessLayer::AccountableEntry accountableEntry;
	BusinessLayer::AccountablePaymentRelation accountablePayment;
	BusinessLayer::AccountableWithdrawalRelation accountableWithdrawal;
	BusinessLayer::ExpenseDocument expenseDoc;

	std::vector<int> approvementIDVector;
	approvementIDVector = accountableApprovement.GetAllApprovementByAccountableDocumentID(dialogBL->globalVar, dialogBL->GetOrmasDal(), id, errorMessage);
	if (approvementIDVector.size() > 0)
	{
		BusinessLayer::AccountableApprovement approvement;
		BusinessLayer::User user;
		for each (auto approveID in approvementIDVector)
		{
			approvement.Clear();
			if (approvement.GetAccountableApprovementByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), approveID, errorMessage))
			{
				approveVec.push_back(approvement);
				if (approvement.GetDirectorID() > 0)
				{
					user.Clear();
					if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), approvement.GetDirectorID(), errorMessage))
					{
						directorPh->setText(user.GetSurname().c_str() + QString(" ") + user.GetName().c_str());
						directorEdit->setText(QString::number(user.GetID()));
					}
				}
				if (approvement.GetAccountantID() > 0)
				{
					user.Clear();
					if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), approvement.GetAccountantID(), errorMessage))
					{
						accountantPh->setText(user.GetSurname().c_str() + QString(" ") + user.GetName().c_str());
						accountantEdit->setText(QString::number(user.GetID()));
					}
				}
				approveDateEdit->setDateTime(QDateTime::fromString(approvement.GetApproveDate().c_str(), "dd.MM.yyyy hh:mm"));
			}
		}
	}

	std::vector<int> docListIDVector;
	docListIDVector = accountableDocumentList.GetAllListByAccountableDocumentID(dialogBL->globalVar, dialogBL->GetOrmasDal(), id, errorMessage);
	if (docListIDVector.size() > 0)
	{
		BusinessLayer::AccountableDocumentListRelation docList;
		BusinessLayer::ExpenseDocument eDocument;
		QStandardItemModel *itemModelDoc;
		itemModelDoc = (QStandardItemModel *)itemTableView->model();
		QList<QStandardItem*> itemDoc;
		QStringList headerDoc;
		headerDoc << QObject::tr("ID") << QObject::tr("Expense name") << QObject::tr("Count")
			<< QObject::tr("Sum") << QObject::tr("Measure ID") << QObject::tr("Currency ID");
		itemModelDoc->setHorizontalHeaderLabels(headerDoc);
		double sum = 0;
		for each (auto listID in docListIDVector)
		{
			docList.Clear();
			eDocument.Clear();
			if (docList.GetDocumentListByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), listID, errorMessage))
			{
				docListVec.push_back(docList);
				if (eDocument.GetExpenseDocumentByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), docList.GetExpenseDocumentID(), errorMessage))
				{
					expenseVec.push_back(eDocument);
					itemDoc << new QStandardItem(QString::number(eDocument.GetID()))
						<< new QStandardItem(eDocument.GetExpenseName().c_str())
						<< new QStandardItem(QString::number(eDocument.GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(eDocument.GetSum(), 'f', 3))
						<< new QStandardItem(QString::number(eDocument.GetMeasureID()))
						<< new QStandardItem(QString::number(eDocument.GetCurrencyID()));
					currCmb->setCurrentIndex(currCmb->findData(QVariant(eDocument.GetCurrencyID())));
					sum += eDocument.GetSum();
					itemModelDoc->appendRow(itemDoc);
					itemDoc.clear();
				}
			}
			
		}
		
		itemSumEdit->setText(QString::number(sum, 'f', 3));
	}

	std::vector<int> entryIDVector;
	entryIDVector = accountableEntry.GetAllEntryByAccountableDocumentID(dialogBL->globalVar, dialogBL->GetOrmasDal(), id, errorMessage);
	if (entryIDVector.size() > 0)
	{
		BusinessLayer::AccountableEntry eEntry;
		QStandardItemModel *itemModelEntry;
		itemModelEntry = (QStandardItemModel *)entryTableView->model();
		QList<QStandardItem*> itemEntry;
		QStringList headerEntry;
		headerEntry << QObject::tr("ID") << QObject::tr("Debit account ID") << QObject::tr("Debit subaccount ID")
			<< QObject::tr("Value") << QObject::tr("Credit account ID") << QObject::tr("Credit subaccount ID") << QObject::tr("Accountable document ID");
		itemModelEntry->setHorizontalHeaderLabels(headerEntry);
		double sum = 0;
		for each (auto entryID in entryIDVector)
		{
			eEntry.Clear();
			if (eEntry.GetAccountableEntryByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entryID, errorMessage))
			{
				entryVec.push_back(eEntry);
				itemEntry << new QStandardItem(QString::number(eEntry.GetID()))
					<< new QStandardItem(QString::number(eEntry.GetDebitAccountID()))
					<< new QStandardItem(QString::number(eEntry.GetDebitSubaccountID()))
					<< new QStandardItem(QString::number(eEntry.GetValue(), 'f', 3))
					<< new QStandardItem(QString::number(eEntry.GetCreditAccountID()))
					<< new QStandardItem(QString::number(eEntry.GetCreditSubaccountID()))
					<< new QStandardItem(QString::number(eEntry.GetAccountableDocumentID()));
				sum += eEntry.GetValue();
				itemModelEntry->appendRow(itemEntry);
				itemEntry.clear();
			}
		}
		entryTotalSumEdit->setText(QString::number(sum, 'f', 3));
	}

	double withSum = 0;
	std::vector<int> paymentIDVector;
	paymentIDVector = accountablePayment.GetAllPaymentByAccountableDocumentID(dialogBL->globalVar, dialogBL->GetOrmasDal(), id, errorMessage);
	if (paymentIDVector.size() > 0)
	{
		BusinessLayer::AccountablePaymentRelation ePayment;
		BusinessLayer::Withdrawal withdrawal;
		QStandardItemModel *itemModelPayment;
		itemModelPayment = (QStandardItemModel *)paymentTableView->model();
		QList<QStandardItem*> itemPayment;
		QStringList headerPayment;
		headerPayment << QObject::tr("ID") << QObject::tr("Accountable document ID") << QObject::tr("Payment ID");
		itemModelPayment->setHorizontalHeaderLabels(headerPayment);
		for each (auto paymentID in paymentIDVector)
		{
			ePayment.Clear();
			if (ePayment.GetAccountablePaymentByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), paymentID, errorMessage))
			{
				paymentVec.push_back(ePayment);
				itemPayment << new QStandardItem(QString::number(ePayment.GetID()))
					<< new QStandardItem(QString::number(ePayment.GetAccountableDocumentID()))
					<< new QStandardItem(QString::number(ePayment.GetPaymentID()));
				withdrawal.Clear();
				if (withdrawal.GetWithdrawalByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ePayment.GetPaymentID(), errorMessage))
					withSum += withdrawal.GetValue();
				itemModelPayment->appendRow(itemPayment);
				itemPayment.clear();
			}
		}
	}

	double paySum = 0;
	std::vector<int> withdrawalIDVector;
	withdrawalIDVector = accountableWithdrawal.GetAllWithdrawalByAccountableDocumentID(dialogBL->globalVar, dialogBL->GetOrmasDal(), id, errorMessage);
	if (withdrawalIDVector.size() > 0)
	{
		BusinessLayer::AccountableWithdrawalRelation eWithdrawal;
		BusinessLayer::Payment payment;
		QStandardItemModel *itemModelWithdrawal;
		itemModelWithdrawal = (QStandardItemModel *)withdrawalTableView->model();
		QList<QStandardItem*> itemWithdrawal;
		QStringList headerWithdrawal;
		headerWithdrawal << QObject::tr("ID") << QObject::tr("Accountable document ID") << QObject::tr("Withdrawal ID");
		itemModelWithdrawal->setHorizontalHeaderLabels(headerWithdrawal);
		for each (auto withdrawalID in withdrawalIDVector)
		{
			eWithdrawal.Clear();
			if (eWithdrawal.GetAccountableWithdrawalByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawalID, errorMessage))
			{
				withdrawalVec.push_back(eWithdrawal);
				itemWithdrawal << new QStandardItem(QString::number(eWithdrawal.GetID()))
					<< new QStandardItem(QString::number(eWithdrawal.GetAccountableDocumentID()))
					<< new QStandardItem(QString::number(eWithdrawal.GetWithdrawalID()));
				if (payment.GetPaymentByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), eWithdrawal.GetWithdrawalID(), errorMessage))
					paySum += payment.GetValue();
				itemModelWithdrawal->appendRow(itemWithdrawal);
				itemWithdrawal.clear();
			}
		}
	}

	if (accountableTransaction->GetAccountableTransactionByAccountableDocumentID(dialogBL->globalVar, dialogBL->GetOrmasDal(), id, errorMessage))
	{
		totalEdit->setText(QString::number(accountableTransaction->GetTotalValue()));
		spentEdit->setText(QString::number(accountableTransaction->GetSpentValue()));
		remainderEdit->setText(QString::number(accountableTransaction->GetResidualValue()));
		overrunEdit->setText(QString::number(accountableTransaction->GetDifferenceValue()));
		if (accountableTransaction->GetTotalValue()-withSum+paySum >= 0)
		{
			prevRemainderEdit->setText(QString::number(accountableTransaction->GetTotalValue() - withSum + paySum,'f',3));
			prevOverrunEdit->setText(QString::number(0));
		}
		else
		{
			prevRemainderEdit->setText(QString::number(0));
			prevOverrunEdit->setText(QString::number(accountableTransaction->GetTotalValue() - withSum + paySum, 'f', 3));
		}
		
	}


	BusinessLayer::Accountable accountable;
	if (accountable.GetAccountableByUserID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accID, errorMessage))
	{
		
		BusinessLayer::User user;
		BusinessLayer::CompanyEmployeeRelation comEmp;
		BusinessLayer::Branch branch;
		BusinessLayer::Position position;
		BusinessLayer::Role role;
		BusinessLayer::Employee employee;
		BusinessLayer::Company company;
		if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage))
		{
			employeePh->setText(user.GetSurname().c_str() + QString(" ") + user.GetName().c_str());
			employeeEdit->setText(QString::number(user.GetID()));
			int branchid = 0;
			int companyID = 0;
			branchid = comEmp.GetBranchByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage);
			companyID = comEmp.GetCompanyByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage);
			if (companyID>0)
			{
				if (company.GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyID, errorMessage))
				{
					companyEdit->setText(QString::number(company.GetID()));
					companyPh->setText(company.GetName().c_str());
				}
			}
			comEmp.Clear();
			if (branchid>0)
			{
				if (branch.GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), branchid, errorMessage))
				{
					branchPh->setText(branch.GetName().c_str());
				}
				if (role.GetRoleByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), user.GetRoleID(), errorMessage))
				{
					rolePh->setText(role.GetName().c_str());
				}
				if (employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), user.GetID(), errorMessage))
				{
					if (position.GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee.GetPositionID(), errorMessage))
					{
						positionPh->setText(position.GetName().c_str());
					}
				}
			}
		}
	}

	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), statusID, errorMessage))
	{
		statusEdit->setText(QString::number(statusID));
		statusPh->setText(status.GetName().c_str());
	}

	std::string temp = aDate.toStdString();
	reprotDateEdit->setDateTime(QDateTime::fromString(aDate, "dd.MM.yyyy hh:mm"));
	appointmentEdit->setText(epAssignment);
}

void CreateAccblRepDlg::SetID(int ID, QString childName)
{
	if (0 != ID)
	{
		if (0 != childName.length())
		{
			this->hide();
			this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
			this->show();
			this->raise();
			this->activateWindow();
			QApplication::setActiveWindow(this);

			if (childName == QString("statusForm"))
			{
				statusEdit->setText(QString::number(ID));
				BusinessLayer::Status status;
				if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					statusPh->setText(status.GetName().c_str());
				}
			}
			if (childName == QString("employeeForm"))
			{
				directorEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					directorPh->setText(user.GetSurname().c_str() + QString(" ") + user.GetName().c_str());
				}
			}
			if (childName == QString("employee2Form"))
			{
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					BusinessLayer::Role accountant;
					BusinessLayer::Role cheffAccountant;
					if (accountant.GetRoleIDByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "ACCOUNTANT", errorMessage)
						&& cheffAccountant.GetRoleIDByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "CHIEF ACCOUNTANT", errorMessage))
					{
						if (user.GetRoleID() != accountant.GetID() && user.GetRoleID() != cheffAccountant.GetID())
						{
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr("Employee role must be an 'Accountant' or 'Chief accountnat'!")),
								QString(tr("Ok")));
							return;
						}
						else
						{
							accountantEdit->setText(QString::number(ID));
							accountantPh->setText(user.GetSurname().c_str() + QString(" ") + user.GetName().c_str());
						}
					}
					
				}
			}
			if (childName == QString("accountableForm"))
			{
				BusinessLayer::Accountable accountable;
				if (accountable.GetAccountableByUserID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{

				

					BusinessLayer::AccountableDocument acDoc;
					acDoc.SetAccountableID(accountable.GetEmployeeID());
					std::string docFilter = acDoc.GenerateFilter(dialogBL->GetOrmasDal());
					std::vector<BusinessLayer::AccountableDocument> acDocVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountableDocument>(errorMessage, docFilter);
					if (acDocVec.size() > 0)
					{
						BusinessLayer::Status statusOpen;
						if (!statusOpen.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "OPEN", errorMessage))
							return;
						BusinessLayer::Status statusError;
						if (!statusError.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "ERROR", errorMessage))
							return;
						BusinessLayer::Status statusExecute;
						if (!statusExecute.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
							return;

						int stopCounter = 0;
						for each (auto docItem in acDocVec)
						{
							if (stopCounter == 10)
								break;
							if (docItem.GetStatusID() == statusOpen.GetID())
							{
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr("Error! This accountable allready have one or more current ongoing document with \"OPEN\" status. Please close that document at first.")),
									QString(tr("Ok")));
								return;
							}
							if (docItem.GetStatusID() != statusOpen.GetID() && docItem.GetStatusID() != statusError.GetID() && docItem.GetStatusID() != statusExecute.GetID())
							{
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr("Error! This accountable allready have one or more document with unacceptible status. Please change that document status to correct.")),
									QString(tr("Ok")));
								return;
							}
							stopCounter++;
						}
					}
					employeeEdit->setText(QString::number(ID));
					employeeEdit->setDisabled(true);
					BusinessLayer::User user;
					BusinessLayer::CompanyEmployeeRelation comEmp;
					BusinessLayer::Branch branch;
					BusinessLayer::Position position;
					BusinessLayer::Role role;
					BusinessLayer::Employee employee;
					if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage))
					{
						employeePh->setText(user.GetSurname().c_str() + QString(" ") + user.GetName().c_str());
						int branchID = 0;
						branchID = comEmp.GetBranchByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage);
						if (branchID>0)
						{
							if (branch.GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), branchID, errorMessage))
							{
								branchPh->setText(branch.GetName().c_str()); 
							}
							if (role.GetRoleByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), user.GetRoleID(), errorMessage))
							{
								rolePh->setText(role.GetName().c_str());
							}
							if (employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), user.GetID(), errorMessage))
							{
								if (position.GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee.GetPositionID(), errorMessage))
								{
									positionPh->setText(position.GetName().c_str());
								}
							}
						}


						BusinessLayer::AccountableDocument accDoc;
						BusinessLayer::AccountableTransaction accTran;

						accDoc.SetAccountableID(ID);
						std::string filterDoc = accDoc.GenerateFilter(dialogBL->GetOrmasDal());
						std::vector<BusinessLayer::AccountableDocument> docVector = dialogBL->GetAllDataForClass<BusinessLayer::AccountableDocument>(errorMessage, filterDoc);
						if (docVector.size() == 0)
						{
							prevRemainderEdit->setText(QString::number(0));
							prevOverrunEdit->setText(QString::number(0));
						}
						else
						{
							if (accTran.GetAccountableTransactionByAccountableDocumentID(dialogBL->globalVar, dialogBL->GetOrmasDal(), docVector.at(0).GetID(), errorMessage))
							{
								if (accTran.GetDifferenceValue()>=0)
								{
									prevRemainderEdit->setText(QString::number(accTran.GetResidualValue()));
									prevOverrunEdit->setText(QString::number(0));
									totalEdit->setText(QString::number(accTran.GetResidualValue()));
								}
								else
								{
									prevRemainderEdit->setText(QString::number(0));
									prevOverrunEdit->setText(QString::number(accTran.GetDifferenceValue()));
									totalEdit->setText(QString::number(accTran.GetDifferenceValue()));
								}
							}
							else
							{
								prevRemainderEdit->setText(QString::number(0));
								prevOverrunEdit->setText(QString::number(0));
							}
						}
					}
					AutoComplitePayment();
					AutoCompliteWithdrawal();
				}
			}
			if (childName == QString("companyForm"))
			{
				companyEdit->setText(QString::number(ID));
				BusinessLayer::Company company;
				if (company.GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					companyPh->setText(company.GetName().c_str());
				}
			}
			if (childName == QString("paymentForm"))
			{
				BusinessLayer::Payment payment;
				if (payment.GetPaymentByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					QList<QStandardItem*> paymentItem;
					paymentItem << new QStandardItem(QString::number(0))
						 << new QStandardItem(QString::number(0))
						 << new QStandardItem(QString::number(payment.GetID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)withdrawalTableView->model();
					itemModel->appendRow(paymentItem);

					
					if (totalEdit->text().toDouble() == 0)
						totalEdit->setText(QString::number(prevRemainderEdit->text().toDouble() - payment.GetValue(), 'f', 3));
					else
						totalEdit->setText(QString::number(totalEdit->text().toDouble() - payment.GetValue(), 'f', 3));
				}
			}
			if (childName == QString("withdrawalForm"))
			{
				BusinessLayer::Withdrawal withdrawal;
				if (withdrawal.GetWithdrawalByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					QList<QStandardItem*> withdrawalItem;
					withdrawalItem << new QStandardItem(QString::number(0))
						<< new QStandardItem(QString::number(0))
						<< new QStandardItem(QString::number(withdrawal.GetID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)paymentTableView->model();
					itemModel->appendRow(withdrawalItem);

					if (totalEdit->text().toDouble() == 0)
						totalEdit->setText(QString::number(prevRemainderEdit->text().toDouble() + withdrawal.GetValue(), 'f', 3));
					else
						totalEdit->setText(QString::number(totalEdit->text().toDouble() + withdrawal.GetValue(), 'f', 3));
				}
			}
		}
	}
}

bool CreateAccblRepDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetAccountableDocumentParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		return CheckAccess();
	}
	else
	{
		return false;
	}
}

void CreateAccblRepDlg::CreateAccountableDocument()
{
	errorMessage.clear();
	if (!companyEdit->text().isEmpty() && !directorEdit->text().isEmpty() && !employeeEdit->text().isEmpty() && 0 != statusEdit->text().toInt() &&
		0 != spentEdit->text().toDouble() && 0 != accountantEdit->text().toDouble()
		&& 0 != entryTotalSumEdit->text().toDouble()
		&& 0 != itemSumEdit->text().toDouble() && !appointmentEdit->text().isEmpty())
	{
		if (itemSumEdit->text().toDouble() != entryTotalSumEdit->text().toDouble())
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Please check the documen, sums are not equal!")),
					QString(tr("Ok")));
			return;
		}
		dialogBL->StartIsolatedTransaction(errorMessage);
		this->approveVec.clear();
		this->docListVec.clear();
		this->entryVec.clear();
		this->paymentVec.clear();
		this->withdrawalVec.clear();
		this->expenseVec.clear();
		this->SetAccountableDocumentParams(reprotDateEdit->text(), spentEdit->text().toDouble(), appointmentEdit->text(), employeeEdit->text().toInt(), statusEdit->text().toInt());
		this->SetAccountableTransactionParams(remainderEdit->text().toDouble(), totalEdit->text().toDouble(), spentEdit->text().toDouble(), overrunEdit->text().toDouble(), 0);
		this->SetEntryVec(entryTableView);
		this->SetExposeVec(itemTableView);
		this->SetWithdrawalVec(withdrawalTableView);
		this->SetPaymentVec(paymentTableView);
		this->SetApproveVec(directorEdit->text().toInt(), accountantEdit->text().toInt(), reprotDateEdit->text(), approveDateEdit->text());

		DataForm *parentDataForm = (DataForm*)parentForm;
	
		SetAccountableUnionDocumentParams(accountableDocument, accountableTransaction, &approveVec, &docListVec, &entryVec, &paymentVec, &withdrawalVec, &expenseVec);
		if (dialogBL->CreateAccountableUnionDocument(accountableUnionDocument, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountableUnionDocument->GetAccountableDocument()->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					
					QList<QStandardItem*> accountableDocItem;
					int docID = accountableUnionDocument->GetAccountableDocument()->GetID();
					std::string docDate = accountableUnionDocument->GetAccountableDocument()->GetDate();
					std::string expAss = accountableUnionDocument->GetAccountableDocument()->GetExpenseAssignment();
					int accblID = accountableUnionDocument->GetAccountableDocument()->GetAccountableID();
					int stsID = accountableUnionDocument->GetAccountableDocument()->GetStatusID();
					accountableDocItem << new QStandardItem(QString::number(docID))
						<< new QStandardItem(docDate.c_str())
						<< new QStandardItem(QString::number(accountableUnionDocument->GetAccountableDocument()->GetValue(), 'f', 3))
						<< new QStandardItem(expAss.c_str())
						<< new QStandardItem(QString::number(accblID))
						<< new QStandardItem(QString::number(stsID));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(accountableDocItem);

					delete status;
				}
			}
			if (!dialogBL->CommitTransaction(errorMessage))
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
			}

			Close();
		}
		else
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAccblRepDlg::EditAccountableDocument()
{
	errorMessage.clear();
	if (!companyEdit->text().isEmpty() && !directorEdit->text().isEmpty() && !employeeEdit->text().isEmpty() && 0 != statusEdit->text().toInt() &&
		0 != spentEdit->text().toDouble() && 0 != accountantEdit->text().toDouble()
		&& 0 != entryTotalSumEdit->text().toDouble()
		&& 0 != itemSumEdit->text().toDouble() && !appointmentEdit->text().isEmpty())
	{
		dialogBL->StartIsolatedTransaction(errorMessage);
		BusinessLayer::AccountableTransaction aTrans;
		if (!aTrans.GetAccountableTransactionByAccountableDocumentID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountableDocument->GetID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Please recheck all fields!")),
				QString(tr("Ok")));
		}
		if (itemSumEdit->text().toDouble() != aTrans.GetSpentValue() || statusEdit->text().toInt() != accountableDocument->GetStatusID())
		{
			this->SetAccountableDocumentParams(reprotDateEdit->text(), spentEdit->text().toDouble(), appointmentEdit->text(), employeeEdit->text().toInt(), statusEdit->text().toInt(), accountableDocument->GetID());
			this->SetAccountableTransactionParams(remainderEdit->text().toDouble(), totalEdit->text().toDouble(), spentEdit->text().toDouble(), overrunEdit->text().toDouble(), accountableDocument->GetID(), aTrans.GetID());
			//this->SetEntryVec(entryTableView);
			//this->SetExposeVec(itemTableView);
			//this->SetWithdrawalVec(withdrawalTableView);
			//this->SetPaymentVec(paymentTableView);
			//this->SetApproveVec(directorEdit->text().toInt(), accountantEdit->text().toInt(), reprotDateEdit->text(), approveDateEdit->text());

			DataForm *parentDataForm = (DataForm*)parentForm;

			SetAccountableUnionDocumentParams(accountableDocument, accountableTransaction, &approveVec, &docListVec, &entryVec, &paymentVec, &withdrawalVec, &expenseVec);
			if (dialogBL->UpdateAccountableUnionDocument(accountableUnionDocument, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Status *status = new BusinessLayer::Status;
						if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountableUnionDocument->GetAccountableDocument()->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete status;
							return;
						}

						std::string docDate = accountableUnionDocument->GetAccountableDocument()->GetDate();
						std::string expAss = accountableUnionDocument->GetAccountableDocument()->GetExpenseAssignment();
						int accblID = accountableUnionDocument->GetAccountableDocument()->GetAccountableID();
						int stsID = accountableUnionDocument->GetAccountableDocument()->GetStatusID();
						//updating Accountable data
						itemModel->item(mIndex.row(), 1)->setText(docDate.c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(accountableUnionDocument->GetAccountableDocument()->GetValue(), 'f', 3));
						itemModel->item(mIndex.row(), 3)->setText(expAss.c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(accblID));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(stsID));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete status;
					}
				}
				if (!dialogBL->CommitTransaction(errorMessage))
				{
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
				}


				Close();
			}
			else
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
			}
		}
		else
		{
			Close();
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAccblRepDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateAccblRepDlg::OpenStsDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Status"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::Status>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("statusForm");
		dForm->QtConnect<BusinessLayer::Status>();
		QMdiSubWindow *statusWindow = new QMdiSubWindow;
		statusWindow->setWidget(dForm);
		statusWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(statusWindow);
		statusWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All statuses are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}


void CreateAccblRepDlg::OpenCmpDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Company"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::Company>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("companyForm");
		dForm->QtConnect<BusinessLayer::Company>();
		QMdiSubWindow *copmWindow = new QMdiSubWindow;
		copmWindow->setWidget(dForm);
		copmWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(copmWindow);
		copmWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All company are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateAccblRepDlg::OpenEmpDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Employees"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	BusinessLayer::Role *role = new BusinessLayer::Role();
	role->SetName("DIRECTOR");
	std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
	std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);

	if (roleVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not define the role!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	
	BusinessLayer::Employee *employee = new BusinessLayer::Employee();
	employee->SetRoleID(roleVector.at(0).GetID());
	std::string employeeFilter = dialogBL->GenerateFilter<BusinessLayer::Employee>(employee);
	std::vector<BusinessLayer::EmployeeView> employeeVector = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
	if (employeeVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not find employee with \"director\" role!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("employeeForm");
		dForm->QtConnect<BusinessLayer::EmployeeView>();
		QMdiSubWindow *employeeWindow = new QMdiSubWindow;
		employeeWindow->setWidget(dForm);
		employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(employeeWindow);
		employeeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All employees are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateAccblRepDlg::OpenEmpAccDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Employees"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	/*BusinessLayer::Role *role = new BusinessLayer::Role();
	role->SetName("DIRECTOR");
	std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
	std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);

	if (roleVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not define the role!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	BusinessLayer::Employee *employee = new BusinessLayer::Employee();
	employee->SetRoleID(roleVector.at(0).GetID());
	std::string employeeFilter = dialogBL->GenerateFilter<BusinessLayer::Employee>(employee);
	std::vector<BusinessLayer::EmployeeView> employeeVector = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
	if (employeeVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not find employee with \"director\" role!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}*/

	dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage);// , employeeFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("employee2Form");
		dForm->QtConnect<BusinessLayer::EmployeeView>();
		QMdiSubWindow *employeeWindow = new QMdiSubWindow;
		employeeWindow->setWidget(dForm);
		employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(employeeWindow);
		employeeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All employees are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateAccblRepDlg::OpenAccblDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Accountable"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::AccountableView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accountableForm");
		dForm->QtConnect<BusinessLayer::AccountableView>();
		QMdiSubWindow *accblWindow = new QMdiSubWindow;
		accblWindow->setWidget(dForm);
		accblWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(accblWindow);
		accblWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All accountable are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateAccblRepDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curDivision = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curDivision.empty())
	{
		for (unsigned int i = 0; i < curDivision.size(); i++)
		{
			currCmb->addItem(curDivision[i].GetShortName().c_str(), QVariant(curDivision[i].GetID()));
		}
	}
	

}


void CreateAccblRepDlg::SumEditChanged()
{
	spentEdit->setText(QString::number(itemSumEdit->text().toDouble(), 'f', 3));
	SumEditChangedByDelete();
}

void CreateAccblRepDlg::SumEditChangedByDelete()
{
	if ((totalEdit->text().toDouble() - spentEdit->text().toDouble()) > 0)
	{
		remainderEdit->setText(QString::number(totalEdit->text().toDouble() - spentEdit->text().toDouble()));
		overrunEdit->setText(QString::number(0));
	}
	else
	{
		overrunEdit->setText(QString::number(totalEdit->text().toDouble() - spentEdit->text().toDouble(), 'f', 3));
		remainderEdit->setText(QString::number(0));
	}
}

void CreateAccblRepDlg::DecrementItemSum(double itemSum)
{
	itemSumEdit->setText(QString::number(itemSumEdit->text().toDouble() - itemSum, 'f', 3));
}

void CreateAccblRepDlg::DecrementEntrySum(double itemSum)
{
	entryTotalSumEdit->setText(QString::number(entryTotalSumEdit->text().toDouble() - itemSum, 'f', 3));
}

void CreateAccblRepDlg::IncrementItemSum(double itemSum)
{
	itemSumEdit->setText(QString::number(itemSumEdit->text().toDouble() + itemSum, 'f', 3));
}

void CreateAccblRepDlg::IncrementEntrySum(double itemSum)
{
	entryTotalSumEdit->setText(QString::number(entryTotalSumEdit->text().toDouble() + itemSum, 'f', 3));
}

void CreateAccblRepDlg::TextEditChanged()
{
	
}

void CreateAccblRepDlg::AddWithdrawal()
{
	if (employeeEdit->text().isEmpty())
	{
		QString message = tr("Please select accountable first!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	BusinessLayer::Account account;
	if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10520", errorMessage))
		return;
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Payments"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	BusinessLayer::AccountableDocument *aDoc = new BusinessLayer::AccountableDocument();
	aDoc->SetAccountableID(employeeEdit->text().toInt());
	std::string docFilter = dialogBL->GenerateFilter<BusinessLayer::AccountableDocument>(aDoc);
	std::vector<BusinessLayer::AccountableDocument> docVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountableDocument>(errorMessage, docFilter);
	
	BusinessLayer::Payment *payment = new BusinessLayer::Payment();
	payment->SetUserID(employeeEdit->text().toInt());
	payment->SetAccountID(account.GetID());
	if (employeeEdit->text().isEmpty())
	{
		QString message = tr("Please select accountable first!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	std::string paymentFilter;
	paymentFilter = dialogBL->GenerateFilter<BusinessLayer::Payment>(payment);
	
	std::string paymentMoreFilter;
	if (docVec.size() > 0)
	{
		BusinessLayer::AccountablePaymentRelation *aPay = new BusinessLayer::AccountablePaymentRelation();
		std::string docPayFilter="";
		std::vector<BusinessLayer::AccountablePaymentRelation> docPayVec;
		BusinessLayer::Payment pay;
		for each (auto payItem in docVec)
		{
			aPay->Clear();
			aPay->SetAccountableDocumentID(payItem.GetID());
			docPayFilter = dialogBL->GenerateFilter<BusinessLayer::AccountablePaymentRelation>(aPay);
			docPayVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountablePaymentRelation>(errorMessage, docPayFilter);
			if (docPayVec.size() > 0)
			{
				pay.Clear();
				pay.SetID(docPayVec.at(0).GetPaymentID());
				paymentMoreFilter = pay.GenerateFilterFieldBiggerThen(dialogBL->GetOrmasDal());
				break;
			}
		}
	}
	
	
	if (!paymentMoreFilter.empty())
	{
		std::vector<std::string> filterVec;
		filterVec.push_back(paymentFilter);
		filterVec.push_back(paymentMoreFilter);
		paymentFilter.clear();
		paymentFilter = dialogBL->ConcatenateFilters(filterVec);
	}
	
	dForm->FillTable<BusinessLayer::PaymentView>(errorMessage, paymentFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("paymentForm");
		dForm->QtConnect<BusinessLayer::PaymentView>();
		QMdiSubWindow *paymentWindow = new QMdiSubWindow;
		paymentWindow->setWidget(dForm);
		paymentWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(paymentWindow);
		paymentWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideAllButtons();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All payments are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateAccblRepDlg::DeleteWithdrawal()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = (withdrawalTableView->model()->index(withdrawalTableView->selectionModel()->currentIndex().row(), 2)).data().toInt();
	BusinessLayer::Payment pay;
	if (!pay.GetPaymentByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), id, errorMessage))
		return;

	totalEdit->setText(QString::number(totalEdit->text().toDouble() + pay.GetValue(), 'f', 3));
	

	withdrawalTableView->model()->removeRow(withdrawalTableView->selectionModel()->currentIndex().row());
}


void CreateAccblRepDlg::AddPayment()
{
	if (employeeEdit->text().isEmpty())
	{
		QString message = tr("Please select accountable first!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	BusinessLayer::Account account;
	if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10520", errorMessage))
		return;
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Withdrawals"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	BusinessLayer::Withdrawal *withdrawal = new BusinessLayer::Withdrawal();
	withdrawal->SetUserID(employeeEdit->text().toInt());
	withdrawal->SetAccountID(account.GetID());
	if (employeeEdit->text().isEmpty())
	{
		QString message = tr("Please select accountable first!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	
	BusinessLayer::AccountableDocument *aDoc = new BusinessLayer::AccountableDocument();
	aDoc->SetAccountableID(employeeEdit->text().toInt());
	std::string docFilter = dialogBL->GenerateFilter<BusinessLayer::AccountableDocument>(aDoc);
	std::vector<BusinessLayer::AccountableDocument> docVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountableDocument>(errorMessage, docFilter);

	
	std::string withdrawalFilter;
	withdrawalFilter = dialogBL->GenerateFilter<BusinessLayer::Withdrawal>(withdrawal);

	std::string withMoreFilter;
	if (docVec.size() > 0)
	{
		BusinessLayer::AccountableWithdrawalRelation *aWith = new BusinessLayer::AccountableWithdrawalRelation();
		std::string docWithFilter = "";
		std::vector<BusinessLayer::AccountableWithdrawalRelation> docWithVec;
		BusinessLayer::Withdrawal with;
		for each (auto withItem in docVec)
		{
			aWith->Clear();
			aWith->SetAccountableDocumentID(docVec.at(0).GetID());
			docWithFilter = dialogBL->GenerateFilter<BusinessLayer::AccountableWithdrawalRelation>(aWith);
			docWithVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountableWithdrawalRelation>(errorMessage, docWithFilter);
			if (docWithVec.size() > 0)
			{
				with.Clear();
				with.SetID(docWithVec.at(0).GetWithdrawalID());
				withMoreFilter = with.GenerateFilterFieldBiggerThen(dialogBL->GetOrmasDal());
			}
		}
		
	}

	if (!withMoreFilter.empty())
	{
		std::vector<std::string> filterVec;
		filterVec.push_back(withdrawalFilter);
		filterVec.push_back(withMoreFilter);
		withdrawalFilter.clear();
		withdrawalFilter = dialogBL->ConcatenateFilters(filterVec);
	}

	dForm->FillTable<BusinessLayer::WithdrawalView>(errorMessage, withdrawalFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("withdrawalForm");
		dForm->QtConnect<BusinessLayer::WithdrawalView>();
		QMdiSubWindow *withdrawalWindow = new QMdiSubWindow;
		withdrawalWindow->setWidget(dForm);
		withdrawalWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(withdrawalWindow);
		withdrawalWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideAllButtons();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All withdrawal are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateAccblRepDlg::AutoComplitePayment()
{
	BusinessLayer::Account account;
	if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10520", errorMessage))
		return;
	BusinessLayer::Withdrawal *withdrawal = new BusinessLayer::Withdrawal();
	withdrawal->SetUserID(employeeEdit->text().toInt());
	withdrawal->SetAccountID(account.GetID());
	if (employeeEdit->text().isEmpty())
	{
		return;
	}
	BusinessLayer::AccountableDocument *aDoc = new BusinessLayer::AccountableDocument();
	aDoc->SetAccountableID(employeeEdit->text().toInt());
	std::string docFilter = dialogBL->GenerateFilter<BusinessLayer::AccountableDocument>(aDoc);
	std::vector<BusinessLayer::AccountableDocument> docVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountableDocument>(errorMessage, docFilter);


	std::string withdrawalFilter;
	withdrawalFilter = dialogBL->GenerateFilter<BusinessLayer::Withdrawal>(withdrawal);

	std::string withMoreFilter;
	if (docVec.size() > 0)
	{
		BusinessLayer::AccountablePaymentRelation *aPay = new BusinessLayer::AccountablePaymentRelation();
		std::string docWithFilter = "";
		std::vector<BusinessLayer::AccountablePaymentRelation> docWithVec;
		BusinessLayer::Withdrawal with;
		bool exitState = false;
		for each (auto docItem in docVec)
		{
			aPay->Clear();
			aPay->SetAccountableDocumentID(docItem.GetID());
			docWithFilter = dialogBL->GenerateFilter<BusinessLayer::AccountablePaymentRelation>(aPay);
			docWithVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountablePaymentRelation>(errorMessage, docWithFilter);
			if (docWithVec.size() > 0)
			{
				for each (auto withItem in docWithVec)
				{
					with.Clear();
					with.SetID(withItem.GetPaymentID());
					withMoreFilter = with.GenerateFilterFieldBiggerThen(dialogBL->GetOrmasDal());
					exitState = true;
				}
			}
			if (exitState)
				break;
		}



		if (!withMoreFilter.empty())
		{
			std::vector<std::string> filterVec;
			filterVec.push_back(withdrawalFilter);
			filterVec.push_back(withMoreFilter);
			withdrawalFilter.clear();
			withdrawalFilter = dialogBL->ConcatenateFilters(filterVec);
		}


		std::vector<BusinessLayer::WithdrawalView> withdrawalVec = dialogBL->GetAllDataForClass<BusinessLayer::WithdrawalView>(errorMessage, withdrawalFilter);
		if (withdrawalVec.size() > 0)
		{

			BusinessLayer::Withdrawal withdrawal;
			QList<QStandardItem*> withdrawalItem;
			QStandardItemModel *itemModel;
			for each (auto withItem in withdrawalVec)
			{
				withdrawal.Clear();
				withdrawalItem.clear();
				if (withdrawal.GetWithdrawalByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withItem.GetID(), errorMessage))
				{

					withdrawalItem << new QStandardItem(QString::number(0))
						<< new QStandardItem(QString::number(0))
						<< new QStandardItem(QString::number(withdrawal.GetID()));

					itemModel = (QStandardItemModel *)paymentTableView->model();
					itemModel->appendRow(withdrawalItem);

					if (totalEdit->text().toDouble() == 0)
						totalEdit->setText(QString::number(prevRemainderEdit->text().toDouble() + withdrawal.GetValue(), 'f', 3));
					else
						totalEdit->setText(QString::number(totalEdit->text().toDouble() + withdrawal.GetValue(), 'f', 3));
				}
			}
			addPaymentBtn->setDisabled(true);
			deletePaymentBtn->setDisabled(true);
		}
	}
}

void CreateAccblRepDlg::AutoCompliteWithdrawal()
{
	BusinessLayer::Account account;
	if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10520", errorMessage))
		return;
	BusinessLayer::AccountableDocument *aDoc = new BusinessLayer::AccountableDocument();
	aDoc->SetAccountableID(employeeEdit->text().toInt());
	std::string docFilter = dialogBL->GenerateFilter<BusinessLayer::AccountableDocument>(aDoc);
	std::vector<BusinessLayer::AccountableDocument> docVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountableDocument>(errorMessage, docFilter);

	BusinessLayer::Payment *payment = new BusinessLayer::Payment();
	payment->SetUserID(employeeEdit->text().toInt());
	payment->SetAccountID(account.GetID());
	if (employeeEdit->text().isEmpty())
	{
		QString message = tr("Please select accountable first!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	std::string paymentFilter;
	paymentFilter = dialogBL->GenerateFilter<BusinessLayer::Payment>(payment);

	std::string paymentMoreFilter;
	if (docVec.size() > 0)
	{
		BusinessLayer::AccountableWithdrawalRelation *aWith = new BusinessLayer::AccountableWithdrawalRelation();
		std::string docPayFilter = "";
		std::vector<BusinessLayer::AccountableWithdrawalRelation> docPayVec;
		BusinessLayer::Payment pay;
		bool exitState = false;
		for each (auto docItem in docVec)
		{
			aWith->Clear();
			aWith->SetAccountableDocumentID(docItem.GetID());
			docPayFilter = dialogBL->GenerateFilter<BusinessLayer::AccountableWithdrawalRelation>(aWith);
			docPayVec = dialogBL->GetAllDataForClass<BusinessLayer::AccountableWithdrawalRelation>(errorMessage, docPayFilter);
			if (docPayVec.size() > 0)
			{
				for each (auto payItem in docPayVec)
				{
					pay.Clear();
					pay.SetID(payItem.GetWithdrawalID());
					paymentMoreFilter = pay.GenerateFilterFieldBiggerThen(dialogBL->GetOrmasDal());
					exitState = true;
				}
			}
			if (exitState)
				break;
		}


		if (!paymentMoreFilter.empty())
		{
			std::vector<std::string> filterVec;
			filterVec.push_back(paymentFilter);
			filterVec.push_back(paymentMoreFilter);
			paymentFilter.clear();
			paymentFilter = dialogBL->ConcatenateFilters(filterVec);
		}

		std::vector<BusinessLayer::PaymentView> paymentVec = dialogBL->GetAllDataForClass<BusinessLayer::PaymentView>(errorMessage, paymentFilter);

		if (paymentVec.size() > 0)
		{
			BusinessLayer::Payment payment;
			QList<QStandardItem*> paymentItem;
			QStandardItemModel *itemModel;

			for each (auto payItem in paymentVec)
			{
				payment.Clear();
				paymentItem.clear();
				if (payment.GetPaymentByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payItem.GetID(), errorMessage))
				{

					paymentItem << new QStandardItem(QString::number(0))
						<< new QStandardItem(QString::number(0))
						<< new QStandardItem(QString::number(payment.GetID()));

					itemModel = (QStandardItemModel *)withdrawalTableView->model();
					itemModel->appendRow(paymentItem);


					if (totalEdit->text().toDouble() == 0)
						totalEdit->setText(QString::number(prevRemainderEdit->text().toDouble() - payment.GetValue(), 'f', 3));
					else
						totalEdit->setText(QString::number(totalEdit->text().toDouble() - payment.GetValue(), 'f', 3));
				}
			}
			addWithdrawalBtn->setDisabled(true);
			deleteWithdrawalBtn->setDisabled(true);
		}
	}
	
}

void CreateAccblRepDlg::DeletePayment()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	
	int id = (paymentTableView->model()->index(paymentTableView->selectionModel()->currentIndex().row(), 2)).data().toInt();
	BusinessLayer::Withdrawal withd;
	if (!withd.GetWithdrawalByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), id, errorMessage))
		return;

	totalEdit->setText(QString::number(totalEdit->text().toDouble() - withd.GetValue(), 'f', 3));

	paymentTableView->model()->removeRow(paymentTableView->selectionModel()->currentIndex().row());
}

void CreateAccblRepDlg::AddEntry()
{
	if (employeeEdit->text().isEmpty())
	{
		QString message = tr("Please select accountable first!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	CreateAccblEtrDlg *entDlg = new CreateAccblEtrDlg(dialogBL, false, this);
	entDlg->setAttribute(Qt::WA_DeleteOnClose);
	entDlg->setWindowTitle(tr("Add entry to accountable document"));
	QMdiSubWindow *etrWindow = new QMdiSubWindow;
	etrWindow->setWidget(entDlg);
	etrWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)((DataForm*)parentForm)->GetParent())->mdiArea->addSubWindow(etrWindow);
	entDlg->show();
}

void CreateAccblRepDlg::DeleteEntry()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	
	double value = (entryTableView->model()->index(entryTableView->selectionModel()->currentIndex().row(), 3)).data().toDouble();
	DecrementEntrySum(value);
	entryTableView->model()->removeRow(entryTableView->selectionModel()->currentIndex().row());
}

void CreateAccblRepDlg::AddItem()
{
	if (employeeEdit->text().isEmpty())
	{
		QString message = tr("Please select accountable first!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	CreateAccblExpDlg *expDlg = new CreateAccblExpDlg(dialogBL, false, this);
	expDlg->setAttribute(Qt::WA_DeleteOnClose);
	expDlg->setWindowTitle(tr("Add expense to document"));
	QMdiSubWindow *expWindow = new QMdiSubWindow;
	expWindow->setWidget(expDlg);
	expWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)((DataForm*)parentForm)->GetParent())->mdiArea->addSubWindow(expWindow);
	expDlg->show();
}

void CreateAccblRepDlg::DeleteItem()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	
	double value = (itemTableView->model()->index(itemTableView->selectionModel()->currentIndex().row(), 3)).data().toDouble();
	DecrementItemSum(value);
	itemTableView->model()->removeRow(itemTableView->selectionModel()->currentIndex().row());
}

bool CreateAccblRepDlg::CheckAccess()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return false;
	BusinessLayer::Status *status = new BusinessLayer::Status;
	if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountableDocument->GetStatusID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		delete status;
		return false;
	}

	if (0 == status->GetName().compare("EXECUTED"))
	{
		if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
			mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
		{
			return true;
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This document have an \"EXECUTED\" status. The document with \"EXECUTED\" status cannot be changed!")),
				QString(tr("Ok")));
			errorMessage.clear();
			delete status;
			return false;
		}
	}

	if (0 == status->GetName().compare("RETURN"))
	{
		if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
			mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
		{
			return true;
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This document have an \"RETURN\" status. The document with \"EXECUTED\" status cannot be changed!")),
				QString(tr("Ok")));
			errorMessage.clear();
			delete status;
			return false;
		}
	}

	if (0 == status->GetName().compare("ERROR"))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("This document have an \"ERROR\" status. The document with \"ERROR\" status cannot be changed!")),
			QString(tr("Ok")));
		errorMessage.clear();
		delete status;
		return false;
	}

	return true;
}


