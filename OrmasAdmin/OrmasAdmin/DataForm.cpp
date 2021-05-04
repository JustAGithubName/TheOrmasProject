#include "stdafx.h"
#include "DataForm.h"
#include "MainForm.h"
#include "DocForm.h"
#include "AllDlgHeaders.h"



DataForm::DataForm(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QWidget(parent)
{
	setupUi(this);
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableView->verticalHeader()->hide();
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	filterWidget->hide();
	editBtn->setDisabled(true);
	deleteBtn->setDisabled(true);
	dataFormBL = ormasBL;
	parentForm = parent;
	loggedUser = ((MainForm*)parentForm)->GetLoggedUser();
	if (objectName() == "orderForm" || objectName() == "returnForm" || objectName() == "productionForm" || objectName() == "writeOffForm" ||
		objectName() == "consumeProductForm" || objectName() == "consumeRawForm" || objectName() == "inventorizationForm" ||
		objectName() == "orderRawForm" || objectName() == "receiptProductForm" || objectName() == "stockTransferForm" ||
		objectName() == "productionPlanForm" || objectName() == "spoilageForm" || objectName() == "productionConsumeRawForm" ||
		objectName() == "specificationForm" || objectName() == "transportForm" || objectName() == "writeOffRawForm"
		|| objectName() == "consumeOtherStocksForm" || objectName() == "receiptOtherStocksForm")
	{
		connect(tableView, SIGNAL(cellClicked(int, int)), this, SLOT(OpenList(int, int)));
	}
	connect(filterBtn, &QPushButton::released, this, &DataForm::Filter);
	connect(refreshBtn, &QPushButton::released, this, &DataForm::Refresh);
	connect(searchBtn, &QPushButton::released, this, &DataForm::FilterSearchInBase);
	connect(clearBtn, &QPushButton::released, this, &DataForm::ClearFilter);
	HideSomeRow();
	this->setWindowIcon(QIcon("./images/ormas.png"));


}

// All Slots ----------------------------------------------------------------------------
void DataForm::CloseDataForm()
{
	QMdiSubWindow *dataFromWindow = ((MainForm*)parentForm)->GetWindowByName(this->objectName());
	if (dataFromWindow != nullptr)
		dataFromWindow->close();
}

void DataForm::Search(QString searchText)
{
	if (!searchText.isEmpty())
	{
		for (int i = 0; i < tableView->model()->columnCount(); i++)
		{
			for (int j = 0; j < tableView->model()->rowCount(); j++)
			{
				QModelIndex index = tableView->model()->index(j, i);
				if (index.data().toString().compare(searchText, Qt::CaseInsensitive) == 0
					|| index.data().toString().contains(searchText))
				{
					tableView->setCurrentIndex(index);
					((QStandardItemModel *)tableView->model())->item(j,i)->setBackground(Qt::yellow);
				}
			}
		}
	}
}

void DataForm::ClearFilter()
{
	for (int i = 0; i < tableView->model()->rowCount(); i++)
	{
		tableView->showRow(i);
	}
	filterWidget->hide();
	filterTextLb->setText("");
}

void DataForm::Filter()
{
	QString filterText = valueEdit->text();
	if (!filterText.isEmpty())
	{
		for (int i = 0; i < tableView->model()->rowCount(); i++)
		{
			QModelIndex index = tableView->model()->index(i, columnCmb->currentData().toInt());
			if (0 == typeCmb->currentData().toInt())
			{
				if (index.data().toString().contains(filterText))
				{
					tableView->showRow(i);
				}
				else
				{
					tableView->hideRow(i);
				}
			}
			if (1 == typeCmb->currentData().toInt())
			{
				if (index.data().toString().compare(filterText, Qt::CaseInsensitive) < 0)
				{
					tableView->showRow(i);
				}
				else
				{
					tableView->hideRow(i);
				}
			}
			if (2 == typeCmb->currentData().toInt())
			{
				std::string test = index.data().toString().toStdString();
				if (index.data().toString().compare(filterText, Qt::CaseInsensitive) == 0 )
				{
					tableView->showRow(i);
				}
				else
				{
					tableView->hideRow(i);
				}
			}
			if (3 == typeCmb->currentData().toInt())
			{
				if (index.data().toString().compare(filterText, Qt::CaseInsensitive) > 0)
				{
					tableView->showRow(i);
				}
				else
				{
					tableView->hideRow(i);
				}
			}
		}
	}
	QString filterTextRow = columnCmb->currentText() + " " + typeCmb->currentText() + " " + filterText;
	filterTextLb->setText(filterTextRow);
	filterWidget->show();
}

void DataForm::FilterSearchInBase()
{
	QString filterText = valueSearchEdit->text();
	std::string filter="";
	if (!filterText.isEmpty())
	{
		if (objectName() == "accountForm")
		{
			BusinessLayer::Account account;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				account.SetID(filterText.toInt());
				break;
			case 1:
				account.SetNumber(filterText.toStdString());
				break;
			case 2:
				account.SetStartBalance(filterText.toDouble());
				break;
			case 3:
				account.SetCurrentBalance(filterText.toDouble());
				break;
		
			}
			filter = account.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAccForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "acctbDocForm")
		{
			BusinessLayer::AccountableDocument acctbDoc;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				acctbDoc.SetID(filterText.toInt());
				break;
			case 1:
				acctbDoc.SetDate(filterText.toStdString());
				break;
			case 2:
				acctbDoc.SetValue(filterText.toDouble());
				break;
			case 3:
				acctbDoc.SetExpenseAssignment(filterText.toStdString());
				break;
			case 4:
				acctbDoc.SetAccountableID(filterText.toInt());
				break;
			case 5:
				acctbDoc.SetStatusID(filterText.toInt());
				break;
			}
			filter = acctbDoc.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAccblDocForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "accountTypeForm")
		{
			BusinessLayer::AccountType accType;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				accType.SetID(filterText.toInt());
				break;
			case 1:
				accType.SetName(filterText.toStdString());
				break;
			case 2:
				accType.SetNumber(filterText.toInt());
				break;
			case 3:
				accType.SetComment(filterText.toStdString());
				break;
			}
			filter = accType.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAcsItemForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "accessItemForm")
		{
			BusinessLayer::AccessItem accessItem;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				accessItem.SetID(filterText.toInt());
				break;
			case 1:
				accessItem.SetNameEng(filterText.toStdString());
				break;
			case 2:
				accessItem.SetNameRu(filterText.toStdString());
				break;
			case 3:
				accessItem.SetDivision(filterText.toStdString());
				break;
			}
			filter = accessItem.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAcsItemForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "accessForm")
		{
			BusinessLayer::AccessView accessView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				accessView.SetID(filterText.toInt());
				break;
			case 1:
				accessView.SetRoleName(filterText.toStdString());
				break;
			case 2:
				accessView.SetAccessItemEng(filterText.toStdString());
				break;
			case 3:
				accessView.SetAccessItemRu(filterText.toStdString());
				break;
			case 4:
				accessView.SetDivision(filterText.toStdString());
				break;
			case 5:
				accessView.SetRoleID(filterText.toInt());
				break;
			case 6:
				accessView.SetAccessItemID(filterText.toInt());
				break;
			}
			filter = accessView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAccessForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "accountableForm")
		{
			BusinessLayer::AccountableView accountbleView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				accountbleView.SetID(filterText.toInt());
				break;
			case 1:
				accountbleView.SetName(filterText.toStdString());
				break;
			case 2:
				accountbleView.SetSurname(filterText.toStdString());
				break;
			case 3:
				accountbleView.SetInformation(filterText.toStdString());
				break;
			case 4:
				accountbleView.SetPhone(filterText.toStdString());
				break;
			case 5:
				accountbleView.SetAddress(filterText.toStdString());
				break;
			case 6:
				accountbleView.SetRoleName(filterText.toStdString());
				break;
			}
			filter = accountbleView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAcctblForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "amGroupForm")
		{
			BusinessLayer::AmortizeGroup amGroup;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				amGroup.SetID(filterText.toInt());
				break;
			case 1:
				amGroup.SetGroupNumber(filterText.toInt());
				break;
			case 2:
				amGroup.SetFromMonth(filterText.toInt());
				break;
			case 3:
				amGroup.SetToMonth(filterText.toInt());
				break;
			}
			filter = amGroup.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAmGrForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "amTypeForm")
		{
			BusinessLayer::AmortizeType amType;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				amType.SetID(filterText.toInt());
				break;
			case 1:
				amType.SetName(filterText.toStdString());
				break;
			case 2:
				amType.SetCode(filterText.toStdString());
				break;
			}
			filter = amType.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAmTypeForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "balanceForm")
		{
			BusinessLayer::BalanceView balanceView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				balanceView.SetID(filterText.toInt());
				break;
			case 1:
				balanceView.SetUsername(filterText.toStdString());
				break;
			case 2:
				balanceView.SetUserSurname(filterText.toStdString());
				break;
			case 3:
				balanceView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 4:
				balanceView.SetCurrentBalance(filterText.toDouble());
				break;
			case 5:
				balanceView.SetCurrencyName(filterText.toStdString());
				break;
			case 6:
				balanceView.SetUserID(filterText.toInt());
				break;
			case 7:
				balanceView.SetSubaccountID(filterText.toInt());
				break;
			}
			filter = balanceView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInBlcForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "branchForm")
		{
			BusinessLayer::Branch branch;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				branch.SetID(filterText.toInt());
				break;
			case 1:
				branch.SetName(filterText.toStdString());
				break;
			case 2:
				branch.SetAddress(filterText.toStdString());
				break;
			case 3:
				branch.SetPhone(filterText.toStdString());
				break;
			case 4:
				branch.SetComment(filterText.toStdString());
				break;
			}
			filter = branch.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInBrhForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "borrowerForm")
		{
			BusinessLayer::BorrowerView borrowerView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				borrowerView.SetID(filterText.toInt());
				break;
			case 1:
				borrowerView.SetName(filterText.toStdString());
				break;
			case 2:
				borrowerView.SetSurname(filterText.toStdString());
				break;
			case 3:
				borrowerView.SetComment(filterText.toStdString());
				break;
			case 4:
				borrowerView.SetPhone(filterText.toStdString());
				break;
			case 5:
				borrowerView.SetAddress(filterText.toStdString());
				break;
			case 6:
				borrowerView.SetRoleName(filterText.toStdString());
				break;
			case 7:
				borrowerView.SetPassword(filterText.toStdString());
				break;
			case 8:
				borrowerView.SetEmail(filterText.toStdString());
				break;
			case 10:
				borrowerView.SetRoleID(filterText.toInt());
				break;
			}

			filter = borrowerView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInBrwForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "branchSubaccountForm")
		{
			BusinessLayer::BranchSubaccountRelationView brSAccView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				brSAccView.SetID(filterText.toInt());
				break;
			case 1:
				brSAccView.SetBranchName(filterText.toStdString());
				break;
			case 2:
				brSAccView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 3:
				brSAccView.SetBranchID(filterText.toInt());
				break;
			case 4:
				brSAccView.SetSubaccountID(filterText.toInt());
				break;
			}

			filter = brSAccView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInBrSAccForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "cashboxEmployeeForm")
		{
			BusinessLayer::CashboxEmployeeRelationView cashERView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				cashERView.SetID(filterText.toInt());
				break;
			case 1:
				cashERView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 2:
				cashERView.SetCashboxAddress(filterText.toStdString());
				break;
			case 3:
				cashERView.SetUsername(filterText.toStdString());
				break;
			case 4:
				cashERView.SetUserSurname(filterText.toStdString());
				break;
			case 5:
				cashERView.SetUserPhone(filterText.toStdString());
				break;
			case 6:
				cashERView.SetRoleName(filterText.toStdString());
				break;
			case 7:
				cashERView.SetCashboxID(filterText.toInt());
				break;
			case 8:
				cashERView.SetEmployeeID(filterText.toInt());
				break;
			}

			filter = cashERView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInCASHERForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "cashboxForm")
		{
			BusinessLayer::CashboxView cashboxView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				cashboxView.SetID(filterText.toInt());
				break;
			case 1:
				cashboxView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 2:
				cashboxView.SetInformation(filterText.toStdString());
				break;
			case 3:
				cashboxView.SetAddress(filterText.toStdString());
				break;
			case 4:
				cashboxView.SetSubaccountID(filterText.toInt());
				break;
			}

			filter = cashboxView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInCbxForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "chartOffAccountForm")
		{
			BusinessLayer::ChartOfAccountsView caoView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				caoView.SetID(filterText.toInt());
				break;
			case 1:
				caoView.SetNumber(filterText.toStdString());
				break;
			case 2:
				caoView.SetName(filterText.toStdString());
				break;
			case 3:
				caoView.SetAccountTypeName(filterText.toStdString());
				break;
			case 4:
				caoView.SetAccountTypeID(filterText.toInt());
				break;
			}

			filter = caoView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInCOADForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "clientForm")
		{
			BusinessLayer::ClientView clientView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				clientView.SetID(filterText.toInt());
				break;
			case 1:
				clientView.SetName(filterText.toStdString());
				break;
			case 2:
				clientView.SetSurname(filterText.toStdString());
				break;
			case 3:
				clientView.SetPhone(filterText.toStdString());
				break;
			case 4:
				clientView.SetCountryName(filterText.toStdString());
				break;
			case 5:
				clientView.SetRegionName(filterText.toStdString());
				break;
			case 6:
				clientView.SetCityName(filterText.toStdString());
				break;
			case 7:
				clientView.SetAddress(filterText.toStdString());
				break;
			case 8:
				clientView.SetFirm(filterText.toStdString());
				break;
			case 9:
				clientView.SetFirmNumber(filterText.toStdString());
				break;
			case 10:
				clientView.SetRoleName(filterText.toStdString());
				break;
			case 11:
				clientView.SetPassword(filterText.toStdString());
				break;
			case 12:
				clientView.SetEmail(filterText.toStdString());
				break;
			case 14:
				clientView.SetRoleID(filterText.toInt());
				break;
			case 15:
				clientView.SetLocationID(filterText.toInt());
				break;
			}
			filter = clientView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInCltForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "companyAccountForm")
		{
			BusinessLayer::CompanyAccountRelationView carView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				carView.SetID(filterText.toInt());
				break;
			case 1:
				carView.SetCompanyName(filterText.toStdString());
				break;
			case 2:
				carView.SetAccountNumber(filterText.toStdString());
				break;
			case 3:
				carView.SetCompanyID(filterText.toInt());
				break;
			case 4:
				carView.SetAccountID(filterText.toInt());
				break;
			}

			filter = carView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInCARForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "companyForm")
		{
			BusinessLayer::Company company;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				company.SetID(filterText.toInt());
				break;
			case 1:
				company.SetName(filterText.toStdString());
				break;
			case 2:
				company.SetAddress(filterText.toStdString());
				break;
			case 3:
				company.SetPhone(filterText.toStdString());
				break;
			case 4:
				company.SetComment(filterText.toStdString());
				break;
			}

			filter = company.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInCmpForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "companyEmployeeForm")
		{
			BusinessLayer::CompanyEmployeeRelationView cerEmpView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				cerEmpView.SetID(filterText.toInt());
				break;
			case 1:
				cerEmpView.SetCompanyName(filterText.toStdString());
				break;
			case 2:
				cerEmpView.SetBranchName(filterText.toStdString());
				break;
			case 3:
				cerEmpView.SetUsername(filterText.toStdString());
				break;
			case 4:
				cerEmpView.SetUserSurname(filterText.toStdString());
				break;
			case 5:
				cerEmpView.SetUserPhone(filterText.toStdString());
				break;
			case 6:
				cerEmpView.SetCompanyID(filterText.toInt());
				break;
			case 7:
				cerEmpView.SetEmployeeID(filterText.toInt());
				break;
			case 8:
				cerEmpView.SetBranchID(filterText.toInt());
				break;
			}

			filter = cerEmpView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInCERForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "consumeProductForm")
		{
			BusinessLayer::ConsumeProductView conPView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				conPView.SetID(filterText.toInt());
				break;
			case 1:
				conPView.SetDate(filterText.toStdString());
				break;
			case 2:
				conPView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				conPView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				conPView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				conPView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				conPView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				conPView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				conPView.SetEmployeePosition(filterText.toStdString());
				break;
			case 9:
				conPView.SetStockEmployeeName(filterText.toStdString());
				break;
			case 10:
				conPView.SetStockEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				conPView.SetStockEmployeePhone(filterText.toStdString());
				break;
			case 12:
				conPView.SetStockEmployeePosition(filterText.toStdString());
				break;
			case 13:
				conPView.SetCount(filterText.toDouble());
				break;
			case 14:
				conPView.SetSum(filterText.toDouble());
				break;
			case 15:
				conPView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				conPView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				conPView.SetStockEmployeeID(filterText.toInt());
				break;
			case 18:
				conPView.SetStatusID(filterText.toInt());
				break;
			case 19:
				conPView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = conPView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInConPForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "consumeOthStForm")
		{
			BusinessLayer::ConsumeOtherStocksView conOthView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				conOthView.SetID(filterText.toInt());
				break;
			case 1:
				conOthView.SetDate(filterText.toStdString());
				break;
			case 2:
				conOthView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				conOthView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				conOthView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				conOthView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				conOthView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				conOthView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				conOthView.SetEmployeePosition(filterText.toStdString());
				break;
			case 9:
				conOthView.SetStockEmployeeName(filterText.toStdString());
				break;
			case 10:
				conOthView.SetStockEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				conOthView.SetStockEmployeePhone(filterText.toStdString());
				break;
			case 12:
				conOthView.SetStockEmployeePosition(filterText.toStdString());
				break;
			case 13:
				conOthView.SetCount(filterText.toDouble());
				break;
			case 14:
				conOthView.SetSum(filterText.toDouble());
				break;
			case 15:
				conOthView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				conOthView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				conOthView.SetStockEmployeeID(filterText.toInt());
				break;
			case 18:
				conOthView.SetStatusID(filterText.toInt());
				break;
			case 19:
				conOthView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = conOthView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInConOthForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "consumeRawForm")
		{
			BusinessLayer::ConsumeRawView conRawView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				conRawView.SetID(filterText.toInt());
				break;
			case 1:
				conRawView.SetDate(filterText.toStdString());
				break;
			case 2:
				conRawView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				conRawView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				conRawView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				conRawView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				conRawView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				conRawView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				conRawView.SetEmployeePosition(filterText.toStdString());
				break;
			case 9:
				conRawView.SetStockEmployeeName(filterText.toStdString());
				break;
			case 10:
				conRawView.SetStockEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				conRawView.SetStockEmployeePhone(filterText.toStdString());
				break;
			case 12:
				conRawView.SetStockEmployeePosition(filterText.toStdString());
				break;
			case 13:
				conRawView.SetCount(filterText.toDouble());
				break;
			case 14:
				conRawView.SetSum(filterText.toDouble());
				break;
			case 15:
				conRawView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				conRawView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				conRawView.SetStockEmployeeID(filterText.toInt());
				break;
			case 18:
				conRawView.SetStatusID(filterText.toInt());
				break;
			case 19:
				conRawView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = conRawView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInConRForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "currencyForm")
		{
			BusinessLayer::Currency currency;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				currency.SetID(filterText.toInt());
				break;
			case 1:
				currency.SetCode(filterText.toInt());
				break;
			case 2:
				currency.SetShortName(filterText.toStdString());
				break;
			case 3:
				currency.SetName(filterText.toStdString());
				break;
			case 4:
				currency.SetUnit(filterText.toInt());
				break;
			}

			filter = currency.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInCurForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "divisionForm")
		{
			BusinessLayer::Division div;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				div.SetID(filterText.toInt());
				break;
			case 1:
				div.SetName(filterText.toStdString());
				break;
			case 2:
				div.SetCode(filterText.toStdString());
				break;
			}

			filter = div.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInDivForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "divisionAccForm")
		{
			BusinessLayer::DivisionAccountRelationView divAccView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				divAccView.SetID(filterText.toInt());
				break;
			case 1:
				divAccView.SetDivisionName(filterText.toStdString());
				break;
			case 2:
				divAccView.SetAccountNumber(filterText.toStdString());
				break;
			case 3:
				divAccView.SetAccountName(filterText.toStdString());
				break;
			case 4:
				divAccView.SetCode(filterText.toStdString());
				break;
			case 5:
				divAccView.SetAccountID(filterText.toInt());
				break;
			}

			filter = divAccView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInDivAccForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "employeeForm")
		{
			BusinessLayer::EmployeeView employeeView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				employeeView.SetID(filterText.toInt());
				break;
			case 1:
				employeeView.SetName(filterText.toStdString());
				break;
			case 2:
				employeeView.SetSurname(filterText.toStdString());
				break;
			case 3:
				employeeView.SetPositionName(filterText.toStdString());
				break;
			case 4:
				employeeView.SetPhone(filterText.toStdString());
				break;
			case 5:
				employeeView.SetAddress(filterText.toStdString());
				break;
			case 6:
				employeeView.SetBirthDate(filterText.toStdString());
				break;
			case 7:
				employeeView.SetRoleName(filterText.toStdString());
				break;
			case 8:
				employeeView.SetHireDate(filterText.toStdString());
				break;
			case 9:
				employeeView.SetPassword(filterText.toStdString());
				break;
			case 10:
				employeeView.SetEmail(filterText.toStdString());
				break;
			case 12:
				employeeView.SetRoleID(filterText.toInt());
				break;
			case 13:
				employeeView.SetPositionID(filterText.toInt());
				break;
			case 14:
				employeeView.SetDivisionEmployeeID(filterText.toInt());
				break;
			case 15:
				employeeView.SetDivisionID(filterText.toInt());
				break;
			}

			filter = employeeView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInEmpForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "employeeProductForm")
		{
			BusinessLayer::EmployeeProductRelationView employeeProdView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				employeeProdView.SetID(filterText.toInt());
				break;
			case 1:
				employeeProdView.SetUsername(filterText.toStdString());
				break;
			case 2:
				employeeProdView.SetUserSurname(filterText.toStdString());
				break;
			case 3:
				employeeProdView.SetUserPhone(filterText.toStdString());
				break;
			case 4:
				employeeProdView.SetProductName(filterText.toStdString());
				break;
			case 5:
				employeeProdView.SetPrice(filterText.toDouble());
				break;
			case 6:
				employeeProdView.SetEmployeeID(filterText.toInt());
				break;
			case 7:
				employeeProdView.SetProductID(filterText.toInt());
				break;
			}

			filter = employeeProdView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInEmpPrdForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "entryForm")
		{
			BusinessLayer::EntryView entryView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				entryView.SetID(filterText.toInt());
				break;
			case 1:
				entryView.SetDate(filterText.toStdString());
				break;
			case 2:
				entryView.SetDebitingAccountNumber(filterText.toStdString());
				break;
			case 3:
				entryView.SetValue(filterText.toDouble());
				break;
			case 4:
				entryView.SetCreditingAccountNumber(filterText.toStdString());
				break;
			case 5:
				entryView.SetDebitingAccountID(filterText.toInt());
				break;
			case 6:
				entryView.SetCreditingAccountID(filterText.toInt());
				break;
			case 7:
				entryView.SetDescription(filterText.toStdString());
				break;
			}

			filter = entryView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInEtrForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "entryRoutingForm")
		{
			BusinessLayer::EntryRouting entryRt;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				entryRt.SetID(filterText.toInt());
				break;
			case 1:
				entryRt.SetOperation(filterText.toStdString());
				break;
			case 2:
				entryRt.SetDebitAccountID(filterText.toInt());
				break;
			case 3:
				entryRt.SetCreditAccountID(filterText.toInt());
				break;
			}

			filter = entryRt.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInEtrRtForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "fixedAstForm")
		{
			BusinessLayer::FixedAssetsView fxView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				fxView.SetID(filterText.toInt());
				break;
			case 1:
				fxView.SetName(filterText.toStdString());
				break;
			case 2:
				fxView.SetInventoryNumber(filterText.toStdString());
				break;
			case 3:
				fxView.SetPrimaryCost(filterText.toDouble());
				break;
			case 4:
				fxView.SetStopCost(filterText.toDouble());
				break;
			case 5:
				fxView.SetPrimaryCostValue(filterText.toDouble());
				break;
			case 6:
				fxView.SetAmortizeValue(filterText.toDouble());
				break;
			case 7:
				fxView.SetDivisionName(filterText.toStdString());
				break;
			case 8:
				fxView.SetStatusName(filterText.toStdString());
				break;
			case 9:
				fxView.SetServiceLife(filterText.toInt());
				break;
			case 11:
				fxView.SetBuyDate(filterText.toStdString());
				break;
			case 12:
				fxView.SetStartOfOperationDate(filterText.toStdString());
				break;
			case 13:
				fxView.SetEndOfOperationDate(filterText.toStdString());
				break;
			case 14:
				fxView.SetSpecificationID(filterText.toInt());
				break;
			case 15:
				fxView.SetStatusID(filterText.toInt());
				break;
			case 16:
				fxView.SetFixedAssetsDetailsID(filterText.toInt());
				break;
			}
			filter = fxView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInFxdAstForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "fixedAstOperForm")
		{
			BusinessLayer::FixedAssetsOperations fxOper;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				fxOper.SetID(filterText.toInt());
				break;
			case 1:
				fxOper.SetDate(filterText.toStdString());
				break;
			case 2:
				fxOper.SetName(filterText.toStdString());
				break;
			case 3:
				fxOper.SetValue(filterText.toDouble());
				break;
			case 4:
				fxOper.SetIncrement(filterText.toInt());
				break;
			case 5:
				fxOper.SetDecrement(filterText.toInt());
				break;
			case 6:
				fxOper.SetFixedAssetsID(filterText.toInt());
				break;
			}
			filter = fxOper.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInAstOperForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "inventoryForm")
		{
			BusinessLayer::InventoryView invView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				invView.SetID(filterText.toInt());
				break;
			case 1:
				invView.SetName(filterText.toStdString());
				break;
			case 2:
				invView.SetCost(filterText.toDouble());
				break;
			case 3:
				invView.SetInventoryNumber(filterText.toStdString());
				break;
			case 4:
				invView.SetBarcodeNumber(filterText.toStdString());
				break;
			case 5:
				invView.SetDivisionName(filterText.toStdString());
				break;
			case 6:
				invView.SetStatusName(filterText.toStdString());
				break;
			case 7:
				invView.SetLocation(filterText.toStdString());
				break;
			case 8:
				invView.SetStartOfOperationDate(filterText.toStdString());
				break;
			case 9:
				invView.SetEndOfOperationDate(filterText.toStdString());
				break;
			case 10:
				invView.SetStatusID(filterText.toInt());
				break;
			case 11:
				invView.SetDepartmentID(filterText.toInt());
				break;
			case 12:
				invView.SetSubaccountID(filterText.toInt());
				break;
			}
			filter = invView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInInveForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "inventorizationForm")
		{
			BusinessLayer::InventorizationView invView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				invView.SetID(filterText.toInt());
				break;
			case 1:
				invView.SetDate(filterText.toStdString());
				break;
			case 2:
				invView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				invView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				invView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				invView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				invView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				invView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				invView.SetEmployeePosition(filterText.toStdString());
				break;
			case 9:
				invView.SetStockEmployeeName(filterText.toStdString());
				break;
			case 10:
				invView.SetStockEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				invView.SetStockEmployeePhone(filterText.toStdString());
				break;
			case 12:
				invView.SetStockEmployeePosition(filterText.toStdString());
				break;
			case 13:
				invView.SetCount(filterText.toDouble());
				break;
			case 14:
				invView.SetSum(filterText.toDouble());
				break;
			case 15:
				invView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				invView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				invView.SetStockEmployeeID(filterText.toInt());
				break;
			case 18:
				invView.SetStatusID(filterText.toInt());
				break;
			case 19:
				invView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = invView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInInvForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "groupForm")
		{
			BusinessLayer::Group group;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				group.SetID(filterText.toInt());
				break;
			case 1:
				group.SetName(filterText.toStdString());
				break;
			case 2:
				group.SetDefenition(filterText.toStdString());
				break;
			}
			filter = group.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInGroupForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "jobpriceForm")
		{
			BusinessLayer::JobpriceView jobView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				jobView.SetID(filterText.toInt());
				break;
			case 1:
				jobView.SetProductName(filterText.toStdString());
				break;
			case 2:
				jobView.SetValue(filterText.toDouble());
				break;
			case 3:
				jobView.SetCurrencyName(filterText.toStdString());
				break;
			case 4:
				jobView.SetVolume(filterText.toDouble());
				break;
			case 5:
				jobView.SetMeasureName(filterText.toStdString());
				break;
			case 6:
				jobView.SetPositionName(filterText.toStdString());
				break;
			case 7:
				jobView.SetProductID(filterText.toInt());
				break;
			case 8:
				jobView.SetCurrencyID(filterText.toInt());
				break;
			case 9:
				jobView.SetMeasureID(filterText.toInt());
				break;
			case 10:
				jobView.SetPositionID(filterText.toInt());
				break;
			}
			filter = jobView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInJbpForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "jobsheetForm")
		{
			BusinessLayer::JobsheetView jobsheetView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				jobsheetView.SetID(filterText.toInt());
				break;
			case 1:
				jobsheetView.SetDate(filterText.toStdString());
				break;
			case 2:
				jobsheetView.SetEmployeeName(filterText.toStdString());
				break;
			case 3:
				jobsheetView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 4:
				jobsheetView.SetEmployeePhone(filterText.toStdString());
				break;
			case 5:
				jobsheetView.SetProductName(filterText.toStdString());
				break;
			case 6:
				jobsheetView.SetCount(filterText.toDouble());
				break;
			case 7:
				jobsheetView.SetProductID(filterText.toInt());
				break;
			case 8:
				jobsheetView.SetMeasureName(filterText.toStdString());
				break;
			case 9:
				jobsheetView.SetProductID(filterText.toInt());
				break;
			case 10:
				jobsheetView.SetEmployeeID(filterText.toInt());
				break;
			}
			filter = jobsheetView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInJbsForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "lowValueStockForm")
		{

			BusinessLayer::LowValueStockView lwstockView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				lwstockView.SetID(filterText.toInt());
				break;
			case 1:
				lwstockView.SetOtherStocksName(filterText.toStdString());
				break;
			case 2:
				lwstockView.SetPrice(filterText.toDouble());
				break;
			case 3:
				lwstockView.SetCurrencyName(filterText.toStdString());
				break;
			case 4:
				lwstockView.SetVolume(filterText.toDouble());
				break;
			case 5:
				lwstockView.SetMeasureName(filterText.toStdString());
				break;
			case 6:
				lwstockView.SetCount(filterText.toDouble());
				break;
			case 7:
				lwstockView.SetSum(filterText.toDouble());
				break;
			case 8:
				lwstockView.SetSumCurrencyName(filterText.toStdString());
				break;
			case 9:
				lwstockView.SetWarehouseName(filterText.toStdString());
				break;
			case 10:
				lwstockView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 11:
				lwstockView.SetStatusName(filterText.toStdString());
				break;
			case 12:
				lwstockView.SetOtherStocksID(filterText.toInt());
				break;
			case 13:
				lwstockView.SetStatusID(filterText.toInt());
				break;
			case 14:
				lwstockView.SetCurrencyID(filterText.toInt());
				break;
			case 15:
				lwstockView.SetWarehouseID(filterText.toInt());
				break;
			}
			filter = lwstockView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInLowValStockForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "locationForm")
		{
			BusinessLayer::Location location;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				location.SetID(filterText.toInt());
				break;
			case 1:
				location.SetCountryName(filterText.toStdString());
				break;
			case 2:
				location.SetCountryCode(filterText.toStdString());
				break;
			case 3:
				location.SetRegionName(filterText.toStdString());
				break;
			case 4:
				location.SetCityName(filterText.toStdString());
				break;
			}
			filter = location.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInLcnForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "measureForm")
		{
			BusinessLayer::Measure measuer;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				measuer.SetID(filterText.toInt());
				break;
			case 1:
				measuer.SetName(filterText.toStdString());
				break;
			case 2:
				measuer.SetShortName(filterText.toStdString());
				break;
			case 3:
				measuer.SetUnit(filterText.toInt());
				break;
			}
			filter = measuer.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInMsrForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "netCostForm")
		{
			BusinessLayer::NetCostView nckView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				nckView.SetID(filterText.toInt());
				break;
			case 1:
				nckView.SetDate(filterText.toStdString());
				break;
			case 2:
				nckView.SetProductName(filterText.toStdString());
				break;
			case 3:
				nckView.SetVolume(filterText.toDouble());
				break;
			case 4:
				nckView.SetMeasureName(filterText.toStdString());
				break;
			case 5:
				nckView.SetValue(filterText.toDouble());
				break;
			case 6:
				nckView.SetCurrencyName(filterText.toStdString());
				break;
			case 7:
				nckView.SetCurrencyID(filterText.toInt());
				break;
			case 8:
				nckView.SetProductID(filterText.toInt());
				break;
			}
			filter = nckView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInNetCForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "orderForm")
		{
			BusinessLayer::OrderView orderView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				orderView.SetID(filterText.toInt());
				break;
			case 1:
				orderView.SetDate(filterText.toStdString());
				break;
			case 2:
				orderView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				orderView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				orderView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				orderView.SetClientName(filterText.toStdString());
				break;
			case 6:
				orderView.SetClientSurname(filterText.toStdString());
				break;
			case 7:
				orderView.SetClientPhone(filterText.toStdString());
				break;
			case 8:
				orderView.SetClientAddress(filterText.toStdString());
				break;
			case 9:
				orderView.SetClientFirm(filterText.toStdString());
				break;
			case 10:
				orderView.SetEmployeeName(filterText.toStdString());
				break;
			case 11:
				orderView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 12:
				orderView.SetEmployeePhone(filterText.toStdString());
				break;
			case 13:
				orderView.SetCount(filterText.toDouble());
				break;
			case 14:
				orderView.SetSum(filterText.toDouble());
				break;
			case 15:
				orderView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				orderView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				orderView.SetClientID(filterText.toInt());
				break;
			case 18:
				orderView.SetStatusID(filterText.toInt());
				break;
			case 19:
				orderView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = orderView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInOrderForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "orderRawForm")
		{
			BusinessLayer::OrderRawView orderRawView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				orderRawView.SetID(filterText.toInt());
				break;
			case 1:
				orderRawView.SetDate(filterText.toStdString());
				break;
			case 2:
				orderRawView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				orderRawView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				orderRawView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				orderRawView.SetPurveyorName(filterText.toStdString());
				break;
			case 6:
				orderRawView.SetPurveyorSurname(filterText.toStdString());
				break;
			case 7:
				orderRawView.SetPurveyorPhone(filterText.toStdString());
				break;
			case 8:
				orderRawView.SetPurveyorCompanyName(filterText.toStdString());
				break;
			case 9:
				orderRawView.SetEmployeeName(filterText.toStdString());
				break;
			case 10:
				orderRawView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				orderRawView.SetEmployeePhone(filterText.toStdString());
				break;
			case 12:
				orderRawView.SetEmployeePosition(filterText.toStdString());
				break;
			case 13:
				orderRawView.SetCount(filterText.toDouble());
				break;
			case 14:
				orderRawView.SetSum(filterText.toDouble());
				break;
			case 15:
				orderRawView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				orderRawView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				orderRawView.SetPurveyorID(filterText.toInt());
				break;
			case 18:
				orderRawView.SetStatusID(filterText.toInt());
				break;
			case 19:
				orderRawView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = orderRawView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInOrdRForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "otherStocksForm")
		{
			BusinessLayer::OtherStocksView othStView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				othStView.SetID(filterText.toInt());
				break;
			case 1:
				othStView.SetName(filterText.toStdString());
				break;
			case 2:
				othStView.SetPrice(filterText.toDouble());
				break;
			case 3:
				othStView.SetCurrencyName(filterText.toStdString());
				break;
			case 4:
				othStView.SetVolume(filterText.toDouble());
				break;
			case 5:
				othStView.SetMeasureName(filterText.toStdString());
				break;
			case 6:
				othStView.SetCompanyName(filterText.toStdString());
				break;
			case 7:
				othStView.SetCompanyID(filterText.toInt());
				break;
			case 8:
				othStView.SetMeasureID(filterText.toInt());
				break;
			case 9:
				othStView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = othStView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInOthStForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "percentRateForm")
		{
			BusinessLayer::PercentRate pRate;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				pRate.SetID(filterText.toInt());
				break;
			case 1:
				pRate.SetValue(filterText.toDouble());
				break;
			case 2:
				pRate.SetCondition(filterText.toStdString());
				break;
			case 3:
				pRate.SetPositionID(filterText.toInt());
				break;
			}
			filter = pRate.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInPcrForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "paymentForm")
		{
			BusinessLayer::PaymentView paymentView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				paymentView.SetID(filterText.toInt());
				break;
			case 1:
				paymentView.SetDate(filterText.toStdString());
				break;
			case 2:
				paymentView.SetUsername(filterText.toStdString());
				break;
			case 3:
				paymentView.SetUserSurname(filterText.toStdString());
				break;
			case 4:
				paymentView.SetUserPhone(filterText.toStdString());
				break;
			case 5:
				paymentView.SetValue(filterText.toDouble());
				break;
			case 6:
				paymentView.SetCurrencyName(filterText.toStdString());
				break;
			case 7:
				paymentView.SetTarget(filterText.toStdString());
				break;
			case 8:
				paymentView.SetAccountNumber(filterText.toStdString());
				break;
			case 9:
				paymentView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 10:
				paymentView.SetWho(filterText.toStdString());
				break;
			case 11:
				paymentView.SetStatusName(filterText.toStdString());
				break;
			case 12:
				paymentView.SetUserID(filterText.toInt());
				break;
			case 13:
				paymentView.SetCurrencyID(filterText.toInt());
				break;
			case 14:
				paymentView.SetStatusID(filterText.toInt());
				break;
			case 15:
				paymentView.SetAccountID(filterText.toInt());
				break;
			case 16:
				paymentView.SetSubaccountID(filterText.toInt());
				break;
			case 17:
				paymentView.SetCashboxAccountID(filterText.toInt());
				break;
			}
			filter = paymentView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInPmtForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "positionForm")
		{
			BusinessLayer::Position posirion;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				posirion.SetID(filterText.toInt());
				break;
			case 1:
				posirion.SetName(filterText.toStdString());
				break;
			}
			filter = posirion.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInPosForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "priceForm")
		{
			BusinessLayer::PriceView priceView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				priceView.SetID(filterText.toInt());
				break;
			case 1:
				priceView.SetDate(filterText.toStdString());
				break;
			case 2:
				priceView.SetProductName(filterText.toStdString());
				break;
			case 3:
				priceView.SetVolume(filterText.toDouble());
				break;
			case 4:
				priceView.SetMeasureName(filterText.toStdString());
				break;
			case 5:
				priceView.SetValue(filterText.toDouble());
				break;
			case 6:
				priceView.SetCurrencyName(filterText.toStdString());
				break;
			case 7:
				priceView.SetCurrencyID(filterText.toInt());
				break;
			case 8:
				priceView.SetProductID(filterText.toInt());
				break;
			}
			filter = priceView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInPrcForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "productTypeForm")
		{
			BusinessLayer::ProductType prodType;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				prodType.SetID(filterText.toInt());
				break;
			case 1:
				prodType.SetName(filterText.toStdString());
				break;
			case 2:
				prodType.SetShortName(filterText.toStdString());
				break;
			case 3:
				prodType.SetCode(filterText.toStdString());
				break;
			}
			filter = prodType.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInProdTpForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "branchProductForm")
		{
			BusinessLayer::ProductBranchRelationView prodBranchView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				prodBranchView.SetID(filterText.toInt());
				break;
			case 1:
				prodBranchView.SetBranchName(filterText.toStdString());
				break;
			case 2:
				prodBranchView.SetBranchAddress(filterText.toStdString());
				break;
			case 3:
				prodBranchView.SetProductName(filterText.toStdString());
				break;
			case 4:
				prodBranchView.SetPrice(filterText.toDouble());
				break;
			case 5:
				prodBranchView.SetProductID(filterText.toInt());
				break;
			case 6:
				prodBranchView.SetBranchID(filterText.toInt());
				break;
			
			}
			filter = prodBranchView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInPrdBrnForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "productForm")
		{
			BusinessLayer::ProductView productView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				productView.SetID(filterText.toInt());
				break;
			case 1:
				productView.SetName(filterText.toStdString());
				break;
			case 2:
				productView.SetPrice(filterText.toDouble());
				break;
			case 3:
				productView.SetCurrencyName(filterText.toStdString());
				break;
			case 4:
				productView.SetVolume(filterText.toDouble());
				break;
			case 5:
				productView.SetMeasureName(filterText.toStdString());
				break;
			case 6:
				productView.SetProductTypeName(filterText.toStdString());
				break;
			case 7:
				productView.SetShelfLife(filterText.toInt());
				break;
			case 8:
				productView.SetCompanyName(filterText.toStdString());
				break;
			case 9:
				productView.SetCompanyID(filterText.toInt());
				break;
			case 10:
				productView.SetMeasureID(filterText.toInt());
				break;
			case 11:
				productView.SetProductTypeID(filterText.toInt());
				break;
			case 12:
				productView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = productView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInProdForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "productionForm")
		{
			BusinessLayer::Production prod;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				prod.SetID(filterText.toInt());
				break;
			case 1:
				prod.SetProductionDate(filterText.toStdString());
				break;
			case 2:
				prod.SetExpiryDate(filterText.toStdString());
				break;
			case 3:
				prod.SetSessionStart(filterText.toStdString());
				break;
			case 4:
				prod.SetSessionEnd(filterText.toStdString());
				break;
			
			}
			filter = prod.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInProdnForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "productionCnsumeRawForm")
		{
			BusinessLayer::ProductionConsumeRawView pconRawView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				pconRawView.SetID(filterText.toInt());
				break;
			case 1:
				pconRawView.SetDate(filterText.toStdString());
				break;
			case 2:
				pconRawView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				pconRawView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				pconRawView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				pconRawView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				pconRawView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				pconRawView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				pconRawView.SetEmployeePosition(filterText.toStdString());
				break;
			case 9:
				pconRawView.SetStockEmployeeName(filterText.toStdString());
				break;
			case 10:
				pconRawView.SetStockEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				pconRawView.SetStockEmployeePhone(filterText.toStdString());
				break;
			case 12:
				pconRawView.SetStockEmployeePosition(filterText.toStdString());
				break;
			case 13:
				pconRawView.SetCount(filterText.toDouble());
				break;
			case 14:
				pconRawView.SetSum(filterText.toDouble());
				break;
			case 15:
				pconRawView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				pconRawView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				pconRawView.SetStockEmployeeID(filterText.toInt());
				break;
			case 18:
				pconRawView.SetStatusID(filterText.toInt());
				break;
			case 19:
				pconRawView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = pconRawView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInProdConRForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "productionPlanForm")
		{
			BusinessLayer::ProductionPlanView pPlanView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				pPlanView.SetID(filterText.toInt());
				break;
			case 1:
				pPlanView.SetDate(filterText.toStdString());
				break;
			case 2:
				pPlanView.SetCount(filterText.toDouble());
				break;
			case 3:
				pPlanView.SetSum(filterText.toDouble());
				break;
			case 4:
				pPlanView.SetCurrencyName(filterText.toStdString());
				break;
			case 5:
				pPlanView.SetStatusName(filterText.toStdString());
				break;
			case 6:
				pPlanView.SetEmployeeName(filterText.toStdString());
				break;
			case 7:
				pPlanView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 8:
				pPlanView.SetEmployeePhone(filterText.toStdString());
				break;
			case 9:
				pPlanView.SetEmployeePosition(filterText.toStdString());
				break;
			case 10:
				pPlanView.SetEmployeeID(filterText.toInt());
				break;
			case 11:
				pPlanView.SetStatusID(filterText.toInt());
				break;
			case 12:
				pPlanView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = pPlanView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInPPlanConRForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "payslipForm")
		{
			BusinessLayer::PayslipView payslipView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				payslipView.SetID(filterText.toInt());
				break;
			case 1:
				payslipView.SetDate(filterText.toStdString());
				break;
			case 2:
				payslipView.SetValue(filterText.toDouble());
				break;
			case 3:
				payslipView.SetCurrencyName(filterText.toStdString());
				break;
			case 4:
				payslipView.SetSalaryID(filterText.toDouble());
				break;
			case 5:
				payslipView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = payslipView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInPspForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "purveyorForm")
		{
			BusinessLayer::PurveyorView purveyorView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				purveyorView.SetID(filterText.toInt());
				break;
			case 1:
				purveyorView.SetName(filterText.toStdString());
				break;
			case 2:
				purveyorView.SetSurname(filterText.toStdString());
				break;
			case 3:
				purveyorView.SetPhone(filterText.toStdString());
				break;
			case 4:
				purveyorView.SetCountryName(filterText.toStdString());
				break;
			case 5:
				purveyorView.SetRegionName(filterText.toStdString());
				break;
			case 6:
				purveyorView.SetCityName(filterText.toStdString());
				break;
			case 7:
				purveyorView.SetAddress(filterText.toStdString());
				break;
			case 8:
				purveyorView.SetCompanyName(filterText.toStdString());
				break;
			case 9:
				purveyorView.SetRoleName(filterText.toStdString());
				break;
			case 10:
				purveyorView.SetPassword(filterText.toStdString());
				break;
			case 11:
				purveyorView.SetEmail(filterText.toStdString());
				break;
			case 13:
				purveyorView.SetRoleID(filterText.toInt());
				break;
			case 14:
				purveyorView.SetLocationID(filterText.toInt());
				break;
			}

			filter = purveyorView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInPurForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "relationForm")
		{
			BusinessLayer::RelationView relationView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				relationView.SetID(filterText.toInt());
				break;
			case 1:
				relationView.SetEmployeeName(filterText.toStdString());
				break;
			case 2:
				relationView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 3:
				relationView.SetEmployeePhone(filterText.toStdString());
				break;
			case 4:
				relationView.SetRelationName(filterText.toStdString());
				break;
			case 5:
				relationView.SetUsername(filterText.toStdString());
				break;
			case 6:
				relationView.SetUserSurname(filterText.toStdString());
				break;
			case 7:
				relationView.SetUserPhone(filterText.toStdString());
				break;
			case 8:
				relationView.SetUser1ID(filterText.toInt());
				break;
			case 9:
				relationView.SetUser2ID(filterText.toInt());
				break;
			case 10:
				relationView.SetRelationTypeID(filterText.toInt());
				break;
			}

			filter = relationView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRelForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "relationTypeForm")
		{
			BusinessLayer::RelationType relationType;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				relationType.SetID(filterText.toInt());
				break;
			case 1:
				relationType.SetName(filterText.toStdString());
				break;
			case 2:
				relationType.SetComment(filterText.toStdString());
				break;
			}

			filter = relationType.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRelTypeForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "roleForm")
		{
			BusinessLayer::Role role;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				role.SetID(filterText.toInt());
				break;
			case 1:
				role.SetCode(filterText.toStdString());
				break;
			case 2:
				role.SetName(filterText.toStdString());
				break;
			case 3:
				role.SetComment(filterText.toStdString());
				break;
			}

			filter = role.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRoleForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "receiptOthStForm")
		{
			BusinessLayer::ReceiptOtherStocksView othStView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				othStView.SetID(filterText.toInt());
				break;
			case 1:
				othStView.SetDate(filterText.toStdString());
				break;
			case 2:
				othStView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				othStView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				othStView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				othStView.SetPurveyorName(filterText.toStdString());
				break;
			case 6:
				othStView.SetPurveyorSurname(filterText.toStdString());
				break;
			case 7:
				othStView.SetPurveyorPhone(filterText.toStdString());
				break;
			case 8:
				othStView.SetPurveyorCompanyName(filterText.toStdString());
				break;
			case 9:
				othStView.SetEmployeeName(filterText.toStdString());
				break;
			case 10:
				othStView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				othStView.SetEmployeePhone(filterText.toStdString());
				break;
			case 12:
				othStView.SetEmployeePosition(filterText.toStdString());
				break;
			case 13:
				othStView.SetCount(filterText.toDouble());
				break;
			case 14:
				othStView.SetSum(filterText.toDouble());
				break;
			case 15:
				othStView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				othStView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				othStView.SetPurveyorID(filterText.toInt());
				break;
			case 18:
				othStView.SetStatusID(filterText.toInt());
				break;
			case 19:
				othStView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = othStView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRcpOthStForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "receiptProductForm")
		{
			BusinessLayer::ReceiptProductView rcpProdView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				rcpProdView.SetID(filterText.toInt());
				break;
			case 1:
				rcpProdView.SetDate(filterText.toStdString());
				break;
			case 2:
				rcpProdView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				rcpProdView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				rcpProdView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				rcpProdView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				rcpProdView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				rcpProdView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				rcpProdView.SetEmployeePosition(filterText.toStdString());
				break;
			case 9:
				rcpProdView.SetStockEmployeeName(filterText.toStdString());
				break;
			case 10:
				rcpProdView.SetStockEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				rcpProdView.SetStockEmployeePhone(filterText.toStdString());
				break;
			case 12:
				rcpProdView.SetStockEmployeePosition(filterText.toStdString());
				break;
			case 13:
				rcpProdView.SetCount(filterText.toDouble());
				break;
			case 14:
				rcpProdView.SetSum(filterText.toDouble());
				break;
			case 15:
				rcpProdView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				rcpProdView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				rcpProdView.SetStockEmployeeID(filterText.toInt());
				break;
			case 18:
				rcpProdView.SetStatusID(filterText.toInt());
				break;
			case 19:
				rcpProdView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = rcpProdView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRcpPForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "stockTransferForm")
		{
			BusinessLayer::StockTransferView stockTrView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				stockTrView.SetID(filterText.toInt());
				break;
			case 1:
				stockTrView.SetDate(filterText.toStdString());
				break;
			case 2:
				stockTrView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				stockTrView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				stockTrView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				stockTrView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				stockTrView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				stockTrView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				stockTrView.SetEmployeePosition(filterText.toStdString());
				break;
			case 9:
				stockTrView.SetStockEmployeeName(filterText.toStdString());
				break;
			case 10:
				stockTrView.SetStockEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				stockTrView.SetStockEmployeePhone(filterText.toStdString());
				break;
			case 12:
				stockTrView.SetStockEmployeePosition(filterText.toStdString());
				break;
			case 13:
				stockTrView.SetCount(filterText.toDouble());
				break;
			case 14:
				stockTrView.SetSum(filterText.toDouble());
				break;
			case 15:
				stockTrView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				stockTrView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				stockTrView.SetStockEmployeeID(filterText.toInt());
				break;
			case 18:
				stockTrView.SetStatusID(filterText.toInt());
				break;
			case 19:
				stockTrView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = stockTrView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInStockTrForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "refundForm")
		{
			BusinessLayer::RefundView refunView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				refunView.SetID(filterText.toInt());
				break;
			case 1:
				refunView.SetDate(filterText.toStdString());
				break;
			case 2:
				refunView.SetValue(filterText.toDouble());
				break;
			case 3:
				refunView.SetCurrencyName(filterText.toStdString());
				break;
			case 4:
				refunView.SetUserID(filterText.toInt());
				break;
			case 5:
				refunView.SetCurrencyID(filterText.toInt());
				break;
			}

			filter = refunView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRfdForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "returnForm")
		{
			BusinessLayer::ReturnView returnView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				returnView.SetID(filterText.toInt());
				break;
			case 1:
				returnView.SetDate(filterText.toStdString());
				break;
			case 2:
				returnView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				returnView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				returnView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				returnView.SetClientName(filterText.toStdString());
				break;
			case 6:
				returnView.SetClientSurname(filterText.toStdString());
				break;
			case 7:
				returnView.SetClientPhone(filterText.toStdString());
				break;
			case 8:
				returnView.SetClientAddress(filterText.toStdString());
				break;
			case 9:
				returnView.SetClientFirm(filterText.toStdString());
				break;
			case 10:
				returnView.SetEmployeeName(filterText.toStdString());
				break;
			case 11:
				returnView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 12:
				returnView.SetEmployeePhone(filterText.toStdString());
				break;
			case 13:
				returnView.SetCount(filterText.toDouble());
				break;
			case 14:
				returnView.SetSum(filterText.toDouble());
				break;
			case 15:
				returnView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				returnView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				returnView.SetClientID(filterText.toInt());
				break;
			case 18:
				returnView.SetStatusID(filterText.toInt());
				break;
			case 19:
				returnView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = returnView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRtrnForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "salaryForm")
		{
			BusinessLayer::SalaryView salaryView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				salaryView.SetID(filterText.toInt());
				break;
			case 1:
				salaryView.SetEmployeeID(filterText.toInt());
				break;
			case 2:
				salaryView.SetEmployeeName(filterText.toStdString());
				break;
			case 3:
				salaryView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 4:
				salaryView.SetEmployeePhone(filterText.toStdString());
				break;
			case 5:
				salaryView.SetDate(filterText.toStdString());
				break;
			case 6:
				salaryView.SetValue(filterText.toDouble());
				break;
			case 7:
				salaryView.SetCurrencyName(filterText.toStdString());
				break;
			case 8:
				salaryView.SetSalaryTypeName(filterText.toStdString());
				break;
			case 9:
				salaryView.SetCurrencyID(filterText.toInt());
				break;
			case 10:
				salaryView.SetSalaryTypeID(filterText.toInt());
				break;
			}
			filter = salaryView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInSlrForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "salaryTypeForm")
		{
			BusinessLayer::SalaryType sType;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				sType.SetID(filterText.toInt());
				break;
			case 1:
				sType.SetCode(filterText.toStdString());
				break;
			case 2:
				sType.SetName(filterText.toStdString());
				break;
			}
			filter = sType.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInSlrTypeForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "statusForm")
		{
			BusinessLayer::Status status;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				status.SetID(filterText.toInt());
				break;
			case 1:
				status.SetCode(filterText.toStdString());
				break;
			case 2:
				status.SetName(filterText.toStdString());
				break;
			case 3:
				status.SetComment(filterText.toStdString());
				break;
			}
			filter = status.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInStsForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "statusRuleForm")
		{
			BusinessLayer::StatusRuleView statusRuleView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				statusRuleView.SetID(filterText.toInt());
				break;
			case 1:
				statusRuleView.SetOperation(filterText.toStdString());
				break;
			case 2:
				statusRuleView.SetStatusName(filterText.toStdString());
				break;
			case 3:
				statusRuleView.SetStatusID(filterText.toInt());
				break;
			}
			filter = statusRuleView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInStsRuleForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "specificationForm")
		{
			BusinessLayer::SpecificationView specView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				specView.SetID(filterText.toInt());
				break;
			case 1:
				specView.SetDate(filterText.toStdString());
				break;
			case 2:
				specView.SetProductName(filterText.toStdString());
				break;
			case 3:
				specView.SetSum(filterText.toDouble());
				break;
			case 4:
				specView.SetCurrencyName(filterText.toStdString());
				break;
			case 5:
				specView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				specView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				specView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				specView.SetEmployeePositionName(filterText.toStdString());
				break;
			case 9:
				specView.SetProductID(filterText.toInt());
				break;
			case 10:
				specView.SetCurrencyID(filterText.toInt());
				break;
			case 11:
				specView.SetEmployeeID(filterText.toInt());
				break;
			}
			filter = specView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInSpecForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "spoilageForm")
		{
			
			BusinessLayer::SpoilageView spoView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				spoView.SetID(filterText.toInt());
				break;
			case 1:
				spoView.SetDate(filterText.toStdString());
				break;
			case 2:
				spoView.SetCount(filterText.toDouble());
				break;
			case 3:
				spoView.SetSum(filterText.toDouble());
				break;
			case 4:
				spoView.SetCurrencyName(filterText.toStdString());
				break;
			case 5:
				spoView.SetStatusName(filterText.toStdString());
				break;
			case 6:
				spoView.SetEmployeeName(filterText.toStdString());
				break;
			case 7:
				spoView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 8:
				spoView.SetEmployeePhone(filterText.toStdString());
				break;
			case 9:
				spoView.SetEmployeeID(filterText.toInt());
				break;
			case 10:
				spoView.SetStatusID(filterText.toInt());
				break;
			case 11:
				spoView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = spoView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInSplForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "subaccountForm")
		{
			BusinessLayer::SubaccountView subView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				subView.SetID(filterText.toInt());
				break;
			case 1:
				subView.SetParentAccountID(filterText.toInt());
				break;
			case 2:
				subView.SetParentAccountNumber(filterText.toStdString());
				break;
			case 3:
				subView.SetNumber(filterText.toStdString());
				break;
			case 4:
				subView.SetStartBalance(filterText.toDouble());
				break;
			case 5:
				subView.SetCurrentBalance(filterText.toDouble());
				break;
			case 6:
				subView.SetCurrencyName(filterText.toStdString());
				break;
			case 7:
				subView.SetStatusName(filterText.toStdString());
				break;
			case 8:
				subView.SetCurrencyID(filterText.toInt());
				break;
			case 9:
				subView.SetStatusID(filterText.toInt());
				break;
			case 10:
				subView.SetOpenedDate(filterText.toStdString());
				break;
			case 11:
				subView.SetClosedDate(filterText.toStdString());
				break;
			case 12:
				subView.SetDetails(filterText.toStdString());
				break;
			}
			filter = subView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRtrnForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "subaccountLimitForm")
		{
			BusinessLayer::SubaccountLimitView subLimitView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				subLimitView.SetID(filterText.toInt());
				break;
			case 1:
				subLimitView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 2:
				subLimitView.SetSubaccountID(filterText.toInt());
				break;
			case 3:
				subLimitView.SetMinValue(filterText.toDouble());
				break;
			case 4:
				subLimitView.SetMaxValue(filterText.toDouble());
				break;
			}
			filter = subLimitView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInRtrnForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "stockForm")
		{
			
			BusinessLayer::StockView stockView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				stockView.SetID(filterText.toInt());
				break;
			case 1:
				stockView.SetProductName(filterText.toStdString());
				break;
			case 2:
				stockView.SetPrice(filterText.toDouble());
				break;
			case 3:
				stockView.SetCurrencyName(filterText.toStdString());
				break;
			case 4:
				stockView.SetVolume(filterText.toDouble());
				break;
			case 5:
				stockView.SetMeasureName(filterText.toStdString());
				break;
			case 6:
				stockView.SetCount(filterText.toDouble());
				break;
			case 7:
				stockView.SetSum(filterText.toDouble());
				break;
			case 8:
				stockView.SetSumCurrencyName(filterText.toStdString());
				break;
			case 9:
				stockView.SetWarehouseName(filterText.toStdString());
				break;
			case 10:
				stockView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 11:
				stockView.SetStatusName(filterText.toStdString());
				break;
			case 12:
				stockView.SetProductID(filterText.toInt());
				break;
			case 13:
				stockView.SetStatusID(filterText.toInt());
				break;
			case 14:
				stockView.SetCurrencyID(filterText.toInt());
				break;
			case 15:
				stockView.SetWarehouseID(filterText.toInt());
				break;
			}
			filter = stockView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if(SearchInRtrnForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "stockLimitForm")
		{
			BusinessLayer::StockLimitView stockLimitView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				stockLimitView.SetID(filterText.toInt());
				break;
			case 1:
				stockLimitView.SetWarehouseName(filterText.toStdString());
				break;
			case 2:
				stockLimitView.SetProductName(filterText.toStdString());
				break;
			case 3:
				stockLimitView.SetMinValue(filterText.toDouble());
				break;
			case 4:
				stockLimitView.SetMaxValue(filterText.toDouble());
				break;
			case 5:
				stockLimitView.SetStockID(filterText.toInt());
				break;
			case 6:
				stockLimitView.SetProductID(filterText.toInt());
				break;
			}
			filter = stockLimitView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInStockLmForm(filter))
				this->CloseDataForm();
		}

		if (objectName() == "timesheetForm")
		{
			BusinessLayer::TimesheetView timeVIew;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				timeVIew.SetID(filterText.toInt());
				break;
			case 1:
				timeVIew.SetUsername(filterText.toStdString());
				break;
			case 2:
				timeVIew.SetUserSurname(filterText.toStdString());
				break;
			case 3:
				timeVIew.SetUserPhone(filterText.toStdString());
				break;
			case 4:
				timeVIew.SetDate(filterText.toStdString());
				break;
			case 5:
				timeVIew.SetWorkedTime(filterText.toInt());
				break;
			case 6:
				timeVIew.SetSalaryID(filterText.toInt());
				break;
			}
			filter = timeVIew.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInStockLmForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "transportForm")
		{
			BusinessLayer::TransportView transportView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				transportView.SetID(filterText.toInt());
				break;
			case 1:
				transportView.SetDate(filterText.toStdString());
				break;
			case 2:
				transportView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				transportView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				transportView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				transportView.SetUserName(filterText.toStdString());
				break;
			case 6:
				transportView.SetUserSurname(filterText.toStdString());
				break;
			case 7:
				transportView.SetUserPhone(filterText.toStdString());
				break;
			case 8:
				transportView.SetUserPosition(filterText.toStdString());
				break;
			case 9:
				transportView.SetEmployeeName(filterText.toStdString());
				break;
			case 10:
				transportView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				transportView.SetEmployeePhone(filterText.toStdString());
				break;
			case 12:
				transportView.SetEmployeePosition(filterText.toStdString());
				break;
			case 13:
				transportView.SetCount(filterText.toDouble());
				break;
			case 14:
				transportView.SetSum(filterText.toDouble());
				break;
			case 15:
				transportView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				transportView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				transportView.SetUserID(filterText.toInt());
				break;
			case 18:
				transportView.SetStatusID(filterText.toInt());
				break;
			case 19:
				transportView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = transportView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInTrsForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "userForm")
		{
			BusinessLayer::UserView userView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				userView.SetID(filterText.toInt());
				break;
			case 1:
				userView.SetEmail(filterText.toStdString());
				break;
			case 2:
				userView.SetName(filterText.toStdString());
				break;
			case 3:
				userView.SetSurname(filterText.toStdString());
				break;
			case 4:
				userView.SetPhone(filterText.toStdString());
				break;
			case 5:
				userView.SetAddress(filterText.toStdString());
				break;
			case 6:
				userView.SetRoleName(filterText.toStdString());
				break;
			case 7:
				userView.SetPassword(filterText.toStdString());
				break;
			case 9:
				userView.SetRoleID(filterText.toInt());
				break;
			}
			filter = userView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInUserForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "userGroupForm")
		{
			BusinessLayer::UserGroupRelationView userGroupView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				userGroupView.SetID(filterText.toInt());
				break;
			case 1:
				userGroupView.SetGroupName(filterText.toStdString());
				break;
			case 2:
				userGroupView.SetUsername(filterText.toStdString());
				break;
			case 3:
				userGroupView.SetUserSurname(filterText.toStdString());
				break;
			case 4:
				userGroupView.SetRoleID(filterText.toInt());
				break;
			case 5:
				userGroupView.SetGroupID(filterText.toInt());
				break;
			case 6:
				userGroupView.SetUserID(filterText.toInt());
				break;
			case 7:
				userGroupView.SetRoleID(filterText.toInt());
				break;
			}
			filter = userGroupView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInUserGrForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "warehouseForm")
		{
			BusinessLayer::WarehouseView wareView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				wareView.SetID(filterText.toInt());
				break;
			case 1:
				wareView.SetName(filterText.toStdString());
				break;
			case 2:
				wareView.SetSubaccountNumber(filterText.toStdString());
				break;
			case 3:
				wareView.SetWarehouseTypeName(filterText.toStdString());
				break;
			case 4:
				wareView.SetAddress(filterText.toStdString());
				break;
			case 5:
				wareView.SetPhone(filterText.toStdString());
				break;
			case 6:
				wareView.SetWarehouseTypeID(filterText.toInt());
				break;
			case 7:
				wareView.SetSubaccountID(filterText.toInt());
				break;
			}
			filter = wareView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInWrhForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "warehouseTypeForm")
		{
			BusinessLayer::WarehouseType wType;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				wType.SetID(filterText.toInt());
				break;
			case 1:
				wType.SetCode(filterText.toStdString());
				break;
			case 2:
				wType.SetPurpose(filterText.toStdString());
				break;
			case 3:
				wType.SetName(filterText.toStdString());
				break;
			}
			filter = wType.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInWrhTpForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "warehouseEmployeeForm")
		{
			BusinessLayer::WarehouseEmployeeRelationView werType;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				werType.SetID(filterText.toInt());
				break;
			case 1:
				werType.SetUsername(filterText.toStdString());
				break;
			case 2:
				werType.SetUserSurname(filterText.toStdString());
				break;
			case 3:
				werType.SetUserPhone(filterText.toStdString());
				break;
			case 4:
				werType.SetRoleName(filterText.toStdString());
				break;
			case 5:
				werType.SetWarehouseName(filterText.toStdString());
				break;
			case 6:
				werType.SetSubaccountNumber(filterText.toStdString());
				break;
			case 7:
				werType.SetWarehouseID(filterText.toInt());
				break;
			case 8:
				werType.SetEmployeeID(filterText.toInt());
				break;
			}
			filter = werType.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInWERForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "withdrawalForm")
		{
			BusinessLayer::WithdrawalView wdwType;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				wdwType.SetID(filterText.toInt());
				break;
			case 1:
				wdwType.SetDate(filterText.toStdString());
				break;
			case 2:
				wdwType.SetValue(filterText.toDouble());
				break;
			case 3:
				wdwType.SetCurrencyName(filterText.toStdString());
				break;
			case 4:
				wdwType.SetUsername(filterText.toStdString());
				break;
			case 5:
				wdwType.SetUserSurname(filterText.toStdString());
				break;
			case 6:
				wdwType.SetUserPhone(filterText.toStdString());
				break;
			case 7:
				wdwType.SetStatusName(filterText.toStdString());
				break;
			case 8:
				wdwType.SetAccountNumber(filterText.toStdString());
				break;
			case 9:
				wdwType.SetSubaccountNumber(filterText.toStdString());
				break;
			case 10:
				wdwType.SetWho(filterText.toStdString());
				break;
			case 11:
				wdwType.SetTarget(filterText.toStdString());
				break;
			case 12:
				wdwType.SetUserID(filterText.toInt());
				break;
			case 13:
				wdwType.SetCurrencyID(filterText.toInt());
				break;
			case 14:
				wdwType.SetSubaccountID(filterText.toInt());
				break;
			case 15:
				wdwType.SetStatusID(filterText.toInt());
				break;
			case 16:
				wdwType.SetAccountID(filterText.toInt());
				break;
			case 17:
				wdwType.SetCashboxAccountID(filterText.toInt());
				break;
			}
			filter = wdwType.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInwWdwForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "writeOffForm")
		{
			BusinessLayer::WriteOffView wView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				wView.SetID(filterText.toInt());
				break;
			case 1:
				wView.SetDate(filterText.toStdString());
				break;
			case 2:
				wView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				wView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				wView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				wView.SetClientName(filterText.toStdString());
				break;
			case 6:
				wView.SetClientSurname(filterText.toStdString());
				break;
			case 7:
				wView.SetClientPhone(filterText.toStdString());
				break;
			case 8:
				wView.SetClientAddress(filterText.toStdString());
				break;
			case 9:
				wView.SetClientFirm(filterText.toStdString());
				break;
			case 10:
				wView.SetEmployeeName(filterText.toStdString());
				break;
			case 11:
				wView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 12:
				wView.SetEmployeePhone(filterText.toStdString());
				break;
			case 13:
				wView.SetCount(filterText.toDouble());
				break;
			case 14:
				wView.SetSum(filterText.toDouble());
				break;
			case 15:
				wView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				wView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				wView.SetClientID(filterText.toInt());
				break;
			case 18:
				wView.SetStatusID(filterText.toInt());
				break;
			case 19:
				wView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = wView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInWOffForm(filter))
				this->CloseDataForm();
		}
		if (objectName() == "writeOffRawForm")
		{
			BusinessLayer::WriteOffRawView wRawView;
			switch (columnSearchCmb->currentData().toInt())
			{
			case 0:
				wRawView.SetID(filterText.toInt());
				break;
			case 1:
				wRawView.SetDate(filterText.toStdString());
				break;
			case 2:
				wRawView.SetExecutionDate(filterText.toStdString());
				break;
			case 3:
				wRawView.SetStatusCode(filterText.toStdString());
				break;
			case 4:
				wRawView.SetStatusName(filterText.toStdString());
				break;
			case 5:
				wRawView.SetEmployeeName(filterText.toStdString());
				break;
			case 6:
				wRawView.SetEmployeeSurname(filterText.toStdString());
				break;
			case 7:
				wRawView.SetEmployeePhone(filterText.toStdString());
				break;
			case 8:
				wRawView.SetEmployeePosition(filterText.toStdString());
				break;
			case 9:
				wRawView.SetStockEmployeeName(filterText.toStdString());
				break;
			case 10:
				wRawView.SetStockEmployeeSurname(filterText.toStdString());
				break;
			case 11:
				wRawView.SetStockEmployeePhone(filterText.toStdString());
				break;
			case 12:
				wRawView.SetStockEmployeePosition(filterText.toStdString());
				break;
			case 13:
				wRawView.SetCount(filterText.toDouble());
				break;
			case 14:
				wRawView.SetSum(filterText.toDouble());
				break;
			case 15:
				wRawView.SetCurrencyName(filterText.toStdString());
				break;
			case 16:
				wRawView.SetEmployeeID(filterText.toInt());
				break;
			case 17:
				wRawView.SetStockEmployeeID(filterText.toInt());
				break;
			case 18:
				wRawView.SetStatusID(filterText.toInt());
				break;
			case 19:
				wRawView.SetCurrencyID(filterText.toInt());
				break;
			}
			filter = wRawView.GenerateFilter(dataFormBL->GetOrmasDal());
			if (filter.empty())
				return;
			this->setObjectName("");
			if (SearchInWOffRawForm(filter))
				this->CloseDataForm();
		}
	}
}

void DataForm::Refresh()
{
	if (objectName() == "accountForm")
	{
		this->setObjectName("");
		SearchInAccForm("");
		this->CloseDataForm();
	}
	if (objectName() == "acctbDocForm")
	{
		this->setObjectName("");
		SearchInAccblDocForm("");
		this->CloseDataForm();
	}
	if (objectName() == "accountTypeForm")
	{
		this->setObjectName("");
		SearchInAccTpForm("");
		this->CloseDataForm();
	}
	if (objectName() == "accessItemForm")
	{
		this->setObjectName("");
		SearchInAcsItemForm("");
		this->CloseDataForm();
	}
	if (objectName() == "accessForm")
	{
		this->setObjectName("");
		SearchInAccessForm("");
		this->CloseDataForm();
	}
	if (objectName() == "accountableForm")
	{
		this->setObjectName("");
		SearchInAcctblForm("");
		this->CloseDataForm();
	}
	if (objectName() == "amGroupForm")
	{
		this->setObjectName("");
		SearchInAmGrForm("");
		this->CloseDataForm();
	}
	if (objectName() == "amTypeForm")
	{
		this->setObjectName("");
		SearchInAmTypeForm("");
		this->CloseDataForm();
	}
	if (objectName() == "balanceForm")
	{
		this->setObjectName("");
		SearchInBlcForm("");
		this->CloseDataForm();
	}
	if (objectName() == "branchForm")
	{
		this->setObjectName("");
		SearchInBrhForm("");
		this->CloseDataForm();
	}
	if (objectName() == "borrowerForm")
	{
		this->setObjectName("");
		SearchInBrwForm("");
		this->CloseDataForm();
	}
	if (objectName() == "branchSubaccountForm")
	{
		this->setObjectName("");
		SearchInBrSAccForm("");
		this->CloseDataForm();
	}
	if (objectName() == "cashboxEmployeeForm")
	{
		this->setObjectName("");
		SearchInCASHERForm("");
		this->CloseDataForm();
	}
	if (objectName() == "cashboxForm")
	{
		this->setObjectName("");
		SearchInCbxForm("");
		this->CloseDataForm();
	}
	if (objectName() == "chartOffAccountForm")
	{
		this->setObjectName("");
		SearchInCOADForm("");
		this->CloseDataForm();
	}
	if (objectName() == "clientForm")
	{
		this->setObjectName("");
		SearchInCltForm("");
		this->CloseDataForm();
	}
	if (objectName() == "companyAccountForm")
	{
		this->setObjectName("");
		SearchInCARForm("");
		this->CloseDataForm();
	}
	if (objectName() == "companyForm")
	{
		this->setObjectName("");
		SearchInCmpForm("");
		this->CloseDataForm();
	}
	if (objectName() == "companyEmployeeForm")
	{
		this->setObjectName("");
		SearchInCERForm("");
		this->CloseDataForm();
	}
	if (objectName() == "consumeProductForm")
	{
		this->setObjectName("");
		SearchInConPForm("");
		this->CloseDataForm();
	}
	if (objectName() == "consumeOthStForm")
	{
		this->setObjectName("");
		SearchInConOthForm("");
		this->CloseDataForm();
	}
	if (objectName() == "consumeRawForm")
	{
		this->setObjectName("");
		SearchInConRForm("");
		this->CloseDataForm();
	}
	if (objectName() == "currencyForm")
	{
		this->setObjectName("");
		SearchInCurForm("");
		this->CloseDataForm();
	}
	if (objectName() == "divisionForm")
	{
		this->setObjectName("");
		SearchInDivForm("");
		this->CloseDataForm();
	}
	if (objectName() == "divisionAccForm")
	{
		this->setObjectName("");
		SearchInDivAccForm("");
		this->CloseDataForm();
	}
	if (objectName() == "employeeForm")
	{
		this->setObjectName("");
		SearchInEmpForm("");
		this->CloseDataForm();
	}
	if (objectName() == "employeeProductForm")
	{
		this->setObjectName("");
		SearchInEmpPrdForm("");
		this->CloseDataForm();
	}
	if (objectName() == "entryForm")
	{
		this->setObjectName("");
		SearchInEtrForm("");
		this->CloseDataForm();
	}
	if (objectName() == "entryRoutingForm")
	{
		this->setObjectName("");
		SearchInEtrRtForm("");
		this->CloseDataForm();
	}
	if (objectName() == "fixedAstForm")
	{
		this->setObjectName("");
		SearchInFxdAstForm("");
		this->CloseDataForm();
	}
	if (objectName() == "fixedAstOperForm")
	{
		this->setObjectName("");
		SearchInAstOperForm("");
		this->CloseDataForm();
	}
	if (objectName() == "inventoryForm")
	{
		this->setObjectName("");
		SearchInInveForm("");
		this->CloseDataForm();
	}
	if (objectName() == "inventorizationForm")
	{
		this->setObjectName("");
		SearchInInvForm("");
		this->CloseDataForm();
	}
	if (objectName() == "groupForm")
	{
		this->setObjectName("");
		SearchInGroupForm("");
		this->CloseDataForm();
	}
	if (objectName() == "jobpriceForm")
	{
		this->setObjectName("");
		SearchInJbpForm("");
		this->CloseDataForm();
	}
	if (objectName() == "jobsheetForm")
	{
		this->setObjectName("");
		SearchInJbsForm("");
		this->CloseDataForm();
	}
	if (objectName() == "lowValueStockForm")
	{
		this->setObjectName("");
		SearchInLowValStockForm("");
		this->CloseDataForm();
	}
	if (objectName() == "locationForm")
	{
		this->setObjectName("");
		SearchInLcnForm("");
		this->CloseDataForm();
	}
	if (objectName() == "measureForm")
	{
		this->setObjectName("");
		SearchInMsrForm("");
		this->CloseDataForm();
	}
	if (objectName() == "netCostForm")
	{
		this->setObjectName("");
		SearchInNetCForm("");
		this->CloseDataForm();
	}
	if (objectName() == "orderForm")
	{
		this->setObjectName("");
		SearchInOrderForm("");
		this->CloseDataForm();
	}
	if (objectName() == "orderRawForm")
	{
		this->setObjectName("");
		SearchInOrdRForm("");
		this->CloseDataForm();
	}
	if (objectName() == "otherStocksForm")
	{
		this->setObjectName("");
		SearchInOthStForm("");
		this->CloseDataForm();
	}
	if (objectName() == "percentRateForm")
	{
		this->setObjectName("");
		SearchInPcrForm("");
		this->CloseDataForm();
	}
	if (objectName() == "paymentForm")
	{
		this->setObjectName("");
		SearchInPmtForm("");
		this->CloseDataForm();
	}
	if (objectName() == "positionForm")
	{
		this->setObjectName("");
		SearchInPosForm("");
		this->CloseDataForm();
	}
	if (objectName() == "priceForm")
	{
		this->setObjectName("");
		SearchInPrcForm("");
		this->CloseDataForm();
	}
	if (objectName() == "productTypeForm")
	{
		this->setObjectName("");
		SearchInProdTpForm("");
		this->CloseDataForm();
	}
	if (objectName() == "branchProductForm")
	{
		this->setObjectName("");
		SearchInPrdBrnForm("");
		this->CloseDataForm();
	}
	if (objectName() == "productForm")
	{
		this->setObjectName("");
		SearchInProdForm("");
		this->CloseDataForm();
	}
	if (objectName() == "productionForm")
	{
		this->setObjectName("");
		SearchInProdnForm("");
		this->CloseDataForm();
	}
	if (objectName() == "productionCnsumeRawForm")
	{
		this->setObjectName("");
		SearchInProdConRForm("");
		this->CloseDataForm();
	}
	if (objectName() == "productionPlanForm")
	{
		this->setObjectName("");
		SearchInPPlanConRForm("");
		this->CloseDataForm();
	}
	if (objectName() == "payslipForm")
	{
		this->setObjectName("");
		SearchInPspForm("");
		this->CloseDataForm();
	}
	if (objectName() == "purveyorForm")
	{
		this->setObjectName("");
		SearchInPurForm("");
		this->CloseDataForm();
	}
	if (objectName() == "relationForm")
	{
		this->setObjectName("");
		SearchInRelForm("");
		this->CloseDataForm();
	}
	if (objectName() == "relationTypeForm")
	{
		this->setObjectName("");
		SearchInRelForm("");
		this->CloseDataForm();
	}
	if (objectName() == "roleForm")
	{
		this->setObjectName("");
		SearchInRoleForm("");
		this->CloseDataForm();
	}
	if (objectName() == "receiptOthStForm")
	{
		this->setObjectName("");
		SearchInRcpOthStForm("");
		this->CloseDataForm();
	}
	if (objectName() == "receiptProductForm")
	{
		this->setObjectName("");
		SearchInRcpPForm("");
		this->CloseDataForm();
	}
	if (objectName() == "stockTransferForm")
	{
		this->setObjectName("");
		SearchInStockTrForm("");
		this->CloseDataForm();
	}
	if (objectName() == "refundForm")
	{
		this->setObjectName("");
		SearchInRfdForm("");
		this->CloseDataForm();
	}
	if (objectName() == "returnForm")
	{
		this->setObjectName("");
		SearchInRtrnForm("");
		this->CloseDataForm();
	}
	if (objectName() == "salaryForm")
	{
		this->setObjectName("");
		SearchInSlrForm("");
		this->CloseDataForm();
	}
	if (objectName() == "salaryTypeForm")
	{
		this->setObjectName("");
		SearchInSlrTypeForm("");
		this->CloseDataForm();
	}
	if (objectName() == "statusForm")
	{
		this->setObjectName("");
		SearchInStsForm("");
		this->CloseDataForm();
	}
	if (objectName() == "statusRuleForm")
	{
		this->setObjectName("");
		SearchInStsRuleForm("");
		this->CloseDataForm();
	}
	if (objectName() == "specificationForm")
	{
		this->setObjectName("");
		SearchInSpecForm("");
		this->CloseDataForm();
	}
	if (objectName() == "spoilageForm")
	{
		this->setObjectName("");
		SearchInSplForm("");
		this->CloseDataForm();
	}
	if (objectName() == "subaccountForm")
	{
		this->setObjectName("");
		SearchInSAccForm("");
		this->CloseDataForm();
	}
	if (objectName() == "subaccountLimitForm")
	{
		this->setObjectName("");
		SearchInSAccLmForm("");
		this->CloseDataForm();
	}
	if (objectName() == "stockForm")
	{
		this->setObjectName("");
		SearchInStockForm("");
		this->CloseDataForm();
	}
	if (objectName() == "stockLimitForm")
	{
		this->setObjectName("");
		SearchInStockLmForm("");
		this->CloseDataForm();
	}
	if (objectName() == "timesheetForm")
	{
		this->setObjectName("");
		SearchInTmsForm("");
		this->CloseDataForm();
	}
	if (objectName() == "transportForm")
	{
		this->setObjectName("");
		SearchInTrsForm("");
		this->CloseDataForm();
	}
	if (objectName() == "userForm")
	{
		this->setObjectName("");
		SearchInUserForm("");
		this->CloseDataForm();
	}
	if (objectName() == "userGroupForm")
	{
		this->setObjectName("");
		SearchInUserGrForm("");
		this->CloseDataForm();
	}
	if (objectName() == "warehouseForm")
	{
		this->setObjectName("");
		SearchInWrhForm("");
		this->CloseDataForm();
	}
	if (objectName() == "warehouseTypeForm")
	{
		this->setObjectName("");
		SearchInWrhTpForm("");
		this->CloseDataForm();
	}
	if (objectName() == "warehouseEmployeeForm")
	{
		this->setObjectName("");
		SearchInWERForm("");
		this->CloseDataForm();
	}
	if (objectName() == "withdrawalForm")
	{
		this->setObjectName("");
		SearchInwWdwForm("");
		this->CloseDataForm();
	}
	if (objectName() == "withdrawalForm")
	{
		this->setObjectName("");
		SearchInwWdwForm("");
		this->CloseDataForm();
	}
	if (objectName() == "writeOffForm")
	{
		this->setObjectName("");
		SearchInWOffForm("");
		this->CloseDataForm();
	}
	if (objectName() == "SearchInWOffForm")
	{
		this->setObjectName("");
		SearchInWOffRawForm("");
		this->CloseDataForm();
	}
}

void DataForm::SetDecoration()
{
	std::string errorMassage = "";
	if (objectName() == "stockForm" || objectName() == "rawStockForm" || objectName() == "productionStockForm")
	{
		BusinessLayer::StockLimit stockLimit;
		BusinessLayer::Stock stock;
		QModelIndex indexID;
		QModelIndex indexWhole;
		for (int i = 0; i < tableView->model()->rowCount(); i++)
		{
			indexID = tableView->model()->index(i, 0);
			stockLimit.Clear();
			stock.Clear();
			if (stockLimit.GetStockLimitByStockID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), indexID.data().toInt(), errorMassage))
			{
				if (stock.GetStockByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), indexID.data().toInt(), errorMassage))
				{
					for (int j = 0; j < tableView->model()->columnCount(); j++)
					{
						indexWhole = tableView->model()->index(i, j);
						if (stock.GetCount() <= stockLimit.GetMinValue())
						{
							((QStandardItemModel *)tableView->model())->item(i, j)->setBackground(QColor(255, 153, 153));
						}
						if (stock.GetCount() >= stockLimit.GetMaxValue())
						{
							((QStandardItemModel *)tableView->model())->item(i, j)->setBackground(QColor(144, 199, 255));
						}
					}
				}
			}
		}
	}
	else if (objectName() == "otherStockForm")
	{

	}
	else if (objectName() == "subaccountForm")
	{
		BusinessLayer::SubaccountLimit sAccLimit;
		BusinessLayer::Subaccount sAcc;
		QModelIndex indexID;
		QModelIndex indexWhole;
		for (int i = 0; i < tableView->model()->rowCount(); i++)
		{
			indexID = tableView->model()->index(i, 0);
			sAccLimit.Clear();
			sAcc.Clear();
			if (sAccLimit.GetSubaccountLimitBySubaccountID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), indexID.data().toInt(), errorMassage))
			{
				if (sAcc.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), indexID.data().toInt(), errorMassage))
				{
					for (int j = 0; j < tableView->model()->columnCount(); j++)
					{
						indexWhole = tableView->model()->index(i, j);
						if (sAcc.GetCurrentBalance() <= sAccLimit.GetMinValue())
						{
							((QStandardItemModel *)tableView->model())->item(i, j)->setBackground(QColor(255, 153, 153));
						}
						if (sAcc.GetCurrentBalance() >= sAccLimit.GetMaxValue())
						{
							((QStandardItemModel *)tableView->model())->item(i, j)->setBackground(QColor(144, 199, 255));
						}
					}
				}
			}
		}
	}
}

void DataForm::SetColumnFilter(QStringList header)
{
	for (int i = 0; i < header.size(); i++)
	{
		columnCmb->addItem(header.at(i), i);
		columnSearchCmb->addItem(header.at(i), i);
	}
}

void DataForm::SetTypeFilter()
{
	typeCmb->addItem(tr("LIKE"), 0);
	typeCmb->addItem(tr("EQUAL(=)"), 1);
	typeCmb->addItem(tr("MORE(>)"), 2);
	typeCmb->addItem(tr("LESS(<)"), 3);
}

bool DataForm::IsClosed()
{
	//This is wrong method, please reimplement it!
	if (orderID != 0 && productionID != 0 && writeOffID != 0 && consumeProductID != 0 && consumeRawID != 0 && inventorizationID != 0 && 
		productionPlanID != 0 && receiptProductID != 0 && stockTransferID != 0 && specificationID != 0 && spoilageID != 0 &&
		transportID != 0 && writeOffRawID != 0)
	{
		return true;
	}
	return false;
}

void DataForm::ChangeBtnState()
{
	if (0 < tableView->model()->rowCount())
	{
		EnableButtons();
	}
	else
	{
		DisableButtons();
	}
}
void DataForm::DisableButtons()
{
	editBtn->setDisabled(true);
	deleteBtn->setDisabled(true);
}
void DataForm::EnableButtons()
{
	editBtn->setDisabled(false);
	deleteBtn->setDisabled(false);
}

void DataForm::HideAllButtons()
{
	editBtn->hide();
	deleteBtn->hide();
	viewBtn->hide();
	createBtn->hide();
}

void DataForm::HideSomeRow()
{
	BusinessLayer::Access access;
	if (objectName() == "userForm")
	{
		std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAllUsers");
		std::size_t pos = crud.find("CRUD");
		if (pos == std::string::npos)
		{
			tableView->setColumnHidden(7, true);
		}
	}
	if (objectName() == "clientForm")
	{
		std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionClients");
		std::size_t pos = crud.find("CRUD");
		if (pos == std::string::npos)
		{
			tableView->setColumnHidden(11, true);
		}
	}
	if (objectName() == "employeeForm" || objectName() == "stockEmployeeForm")
	{
		std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionEmployees");
		std::size_t pos = crud.find("CRUD");
		if (pos == std::string::npos)
		{
			tableView->setColumnHidden(9, true);
		}
	}
	if (objectName() == "purveyorForm")
	{
		std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionPurveyors");
		std::size_t pos = crud.find("CRUD");
		if (pos == std::string::npos)
		{
			tableView->setColumnHidden(10, true);
		}
	}
	if (objectName() == "borrowerForm")
	{
		std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionBorrowers");
		std::size_t pos = crud.find("CRUD");
		if (pos == std::string::npos)
		{
			tableView->setColumnHidden(7, true);
		}
	}
}

QWidget* DataForm::GetParent()
{
	return parentForm;
}

void DataForm::GetIDValue(QModelIndex index)
{
	int id = GetIDFromTable(tableView, index);
	emit SendID(id, objectName());
	CloseDataForm();
}

void DataForm::AcsDenied()
{
	QString message = tr("Access denied!");
	QMessageBox::information(NULL, QString(tr("Warning")),
		QString(tr("Access denied, contact with Administrator!")),
		QString(tr("Ok")));
}

void DataForm::OpenList(int row, int column)
{
	if (column == tableView->model()->columnCount() - 1 && row > 0)
	{
		std::string errorMessage = "";
		std::string filterString = "";
		int id = 0;
		QString message = tr("Loading...");
		((MainForm*)parentWidget())->statusBar()->showMessage(message);
		QWidget* checkedWidget = nullptr;
		if (objectName() == "orderForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				orderID = id;
			BusinessLayer::OrderList *orderList = new BusinessLayer::OrderList();
			orderList->SetOrderID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::OrderList>(orderList);
			delete orderList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("orderListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Order list products"));
					dForm->FillTable<BusinessLayer::OrderListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("orderListForm");
						QMdiSubWindow *prodListWindow = new QMdiSubWindow;
						prodListWindow->setWidget(dForm);
						prodListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(prodListWindow);
						prodListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for order list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for order list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "conusmeProductForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				consumeProductID = id;
			BusinessLayer::ConsumeProductList *consumeProductList = new BusinessLayer::ConsumeProductList();
			consumeProductList->SetConsumeProductID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ConsumeProductList>(consumeProductList);
			delete consumeProductList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("conusmeProductListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Consume product list"));
					dForm->FillTable<BusinessLayer::ConsumeProductListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("conusmeProductListForm");
						QMdiSubWindow *conProdListWindow = new QMdiSubWindow;
						conProdListWindow->setWidget(dForm);
						conProdListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(conProdListWindow);
						conProdListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for consume product list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for consume product list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "conusmeRawForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				consumeRawID = id;
			BusinessLayer::ConsumeRawList *consumeRawList = new BusinessLayer::ConsumeRawList();
			consumeRawList->SetConsumeRawID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ConsumeRawList>(consumeRawList);
			delete consumeRawList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("conusmeRawListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Consume raw list"));
					dForm->FillTable<BusinessLayer::ConsumeRawListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("conusmeRawListForm");
						QMdiSubWindow *conRawListWindow = new QMdiSubWindow;
						conRawListWindow->setWidget(dForm);
						conRawListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(conRawListWindow);
						conRawListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All raws for consume product list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All raws for consume product list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "inventorizationForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				inventorizationID = id;
			BusinessLayer::InventorizationList *inventorizationList = new BusinessLayer::InventorizationList();
			inventorizationList->SetInventorizationID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::InventorizationList>(inventorizationList);
			delete inventorizationList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("inventorizationListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Inventorization list"));
					dForm->FillTable<BusinessLayer::InventorizationListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("inventorizationListForm");
						QMdiSubWindow *invListWindow = new QMdiSubWindow;
						invListWindow->setWidget(dForm);
						invListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(invListWindow);
						invListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for inventorization list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for inventorization list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "orderRawForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				orderRawID = id;
			BusinessLayer::OrderRawList *orderRawList = new BusinessLayer::OrderRawList();
			orderRawList->SetOrderRawID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::OrderRawList>(orderRawList);
			delete orderRawList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("orderRawListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Order raw list"));
					dForm->FillTable<BusinessLayer::OrderRawListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("orderRawListForm");
						QMdiSubWindow *orderRawListWindow = new QMdiSubWindow;
						orderRawListWindow->setWidget(dForm);
						orderRawListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(orderRawListWindow);
						orderRawListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All raws for order list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All raws for order list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "productionForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				productionID = id;
			BusinessLayer::ProductionList *productionList = new BusinessLayer::ProductionList();
			productionList->SetProductionID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ProductionList>(productionList);
			delete productionList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("productionListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Production list products"));
					dForm->FillTable<BusinessLayer::ProductionListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("productionListForm");
						QMdiSubWindow *prodListWindow = new QMdiSubWindow;
						prodListWindow->setWidget(dForm);
						prodListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(prodListWindow);
						prodListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for production list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for production list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "productionConusmeRawForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				consumeRawID = id;
			BusinessLayer::ProductionConsumeRawList *pConsumeRawList = new BusinessLayer::ProductionConsumeRawList();
			pConsumeRawList->SetProductionConsumeRawID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ProductionConsumeRawList>(pConsumeRawList);
			delete pConsumeRawList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("productionConusmeRawListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Production consume raw list"));
					dForm->FillTable<BusinessLayer::ProductionConsumeRawListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("productionConusmeRawForm");
						QMdiSubWindow *pconRawListWindow = new QMdiSubWindow;
						pconRawListWindow->setWidget(dForm);
						pconRawListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(pconRawListWindow);
						pconRawListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All raws for  production consume product list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All raws for production consume product list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "productionPlanForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				productionID = id;
			BusinessLayer::ProductionPlanList *productionPlanList = new BusinessLayer::ProductionPlanList();
			productionPlanList->SetProductionPlanID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ProductionPlanList>(productionPlanList);
			delete productionPlanList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("productionPlanListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Production plan list products"));
					dForm->FillTable<BusinessLayer::ProductionPlanListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("productionPlanListForm");
						QMdiSubWindow *prodPlanListWindow = new QMdiSubWindow;
						prodPlanListWindow->setWidget(dForm);
						prodPlanListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(prodPlanListWindow);
						prodPlanListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for production plan list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for production list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "receiptProductForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				receiptProductID = id;
			BusinessLayer::ReceiptProductList *receiptProductList = new BusinessLayer::ReceiptProductList();
			receiptProductList->SetReceiptProductID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ReceiptProductList>(receiptProductList);
			delete receiptProductList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("receiptProductListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Receipt product list"));
					dForm->FillTable<BusinessLayer::ReceiptProductListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("receiptProductListForm");
						QMdiSubWindow *recProdListWindow = new QMdiSubWindow;
						recProdListWindow->setWidget(dForm);
						recProdListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(recProdListWindow);
						recProdListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for receipt product list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for receipt product list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "stockTransferForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				stockTransferID = id;
			BusinessLayer::StockTransferList *stockTransferList = new BusinessLayer::StockTransferList();
			stockTransferList->SetStockTransferID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::StockTransferList>(stockTransferList);
			delete stockTransferList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("stockTransferListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Receipt raw list"));
					dForm->FillTable<BusinessLayer::StockTransferListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("stockTransferListForm");
						QMdiSubWindow *stockTrListWindow = new QMdiSubWindow;
						stockTrListWindow->setWidget(dForm);
						stockTrListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(stockTrListWindow);
						stockTrListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for stock transfer list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All raws for receipt product list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if(objectName() == "returnForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				returnID = id;
			BusinessLayer::ReturnList *returnList = new BusinessLayer::ReturnList();
			returnList->SetReturnID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ReturnList>(returnList);
			delete returnList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("returnListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Return list products"));
					dForm->FillTable<BusinessLayer::ReturnListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("returnListForm");
						QMdiSubWindow *retListWindow = new QMdiSubWindow;
						retListWindow->setWidget(dForm);
						retListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(retListWindow);
						retListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for return list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for return list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "specificationForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				transportID = id;
			BusinessLayer::SpecificationList *specificationList = new BusinessLayer::SpecificationList();
			specificationList->SetSpecificationID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::SpecificationList>(specificationList);
			delete specificationList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("specificationListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Specification list products"));
					dForm->FillTable<BusinessLayer::SpecificationListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("specificationListForm");
						QMdiSubWindow *specListWindow = new QMdiSubWindow;
						specListWindow->setWidget(dForm);
						specListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(specListWindow);
						specListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for specification list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for specification list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "spoilageForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				transportID = id;
			BusinessLayer::SpoilageList *spoilageList = new BusinessLayer::SpoilageList();
			spoilageList->SetSpoilageID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::SpoilageList>(spoilageList);
			delete spoilageList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("spoilageListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Spoilage list products"));
					dForm->FillTable<BusinessLayer::SpoilageListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("spoilageListForm");
						QMdiSubWindow *spoListWindow = new QMdiSubWindow;
						spoListWindow->setWidget(dForm);
						spoListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(spoListWindow);
						spoListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for spoilage list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for spoilage list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "transportForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				transportID = id;
			BusinessLayer::TransportList *transportList = new BusinessLayer::TransportList();
			transportList->SetTransportID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::TransportList>(transportList);
			delete transportList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("transportListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Transport list products"));
					dForm->FillTable<BusinessLayer::TransportListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("transportListForm");
						QMdiSubWindow *tranListWindow = new QMdiSubWindow;
						tranListWindow->setWidget(dForm);
						tranListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(tranListWindow);
						tranListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for transport list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for transport list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "writeOffForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				productionID = id;
			BusinessLayer::WriteOffList *writeOffList = new BusinessLayer::WriteOffList();
			writeOffList->SetWriteOffID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::WriteOffList>(writeOffList);
			delete writeOffList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("writeOffListForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Write-off list products"));
					dForm->FillTable<BusinessLayer::WriteOffListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("writeOffListForm");
						QMdiSubWindow *wListWindow = new QMdiSubWindow;
						wListWindow->setWidget(dForm);
						wListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(wListWindow);
						wListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All products for write-off list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All products for write-off list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "writeOffRawForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				writeOffRawID = id;
			BusinessLayer::WriteOffRawList *writeOffRawList = new BusinessLayer::WriteOffRawList();
			writeOffRawList->SetWriteOffRawID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::WriteOffRawList>(writeOffRawList);
			delete writeOffRawList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("writeOffRawListForm")); 
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Write-off raw list products"));
					dForm->FillTable<BusinessLayer::WriteOffRawListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("writeOffRawListForm");
						QMdiSubWindow *rawListWindow = new QMdiSubWindow;
						rawListWindow->setWidget(dForm);
						rawListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(rawListWindow);
						rawListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All raws for write-off raw list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All raws for write-off raw list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "consumeOtherStocksForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				consumeOtherStocksID = id;
			BusinessLayer::ConsumeOtherStocksList *conOthStList = new BusinessLayer::ConsumeOtherStocksList();
			conOthStList->SetConsumeOtherStocksID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ConsumeOtherStocksList>(conOthStList);
			delete conOthStList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("consumeOtherStocksForm"));
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Consume other stocks list"));
					dForm->FillTable<BusinessLayer::ConsumeOtherStocksListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("consumeOtherStocksForm");
						QMdiSubWindow *cosListWindow = new QMdiSubWindow;
						cosListWindow->setWidget(dForm);
						cosListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(cosListWindow);
						cosListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All other stocks for consume list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All other stocks for consume list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else if (objectName() == "receiptOtherStocksForm")
		{
			id = GetIDFromTable(tableView, errorMessage);
			if (0 != id)
				receiptOtherStocksID = id;
			BusinessLayer::ReceiptOtherStocksList *receiptOtherStocksList = new BusinessLayer::ReceiptOtherStocksList();
			receiptOtherStocksList->SetReceiptOtherStocksID(id);
			filterString = dataFormBL->GenerateFilter<BusinessLayer::ReceiptOtherStocksList>(receiptOtherStocksList);
			delete receiptOtherStocksList;
			checkedWidget = IsWindowExist(((MainForm*)parentWidget())->mdiArea->subWindowList(), QString("receiptOtherStocksListForm")); 
			if (errorMessage.empty())
			{
				if (checkedWidget == nullptr)
				{
					DataForm *dForm = new DataForm(dataFormBL, this);
					dForm->setWindowTitle(tr("Receipt other stocks list"));
					dForm->FillTable<BusinessLayer::ReceiptOtherStocksListView>(errorMessage, filterString);
					if (errorMessage.empty())
					{
						dForm->setObjectName("receiptOtherStocksListForm");
						QMdiSubWindow *rawListWindow = new QMdiSubWindow;
						rawListWindow->setWidget(dForm);
						rawListWindow->setAttribute(Qt::WA_DeleteOnClose);
						((MainForm*)parentWidget())->mdiArea->addSubWindow(rawListWindow);
						rawListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
						dForm->setWindowModality(Qt::WindowModal);
						dForm->show();
						dForm->topLevelWidget();
						dForm->activateWindow();
						QString message = tr("All other stocks for receipt list are shown");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
					}
					else
					{
						delete dForm;
						QString message = tr("End with error!");
						((MainForm*)parentWidget())->statusBar()->showMessage(message);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage = "";
					}
				}
				else
				{
					checkedWidget->topLevelWidget();
					checkedWidget->activateWindow();
					QString message = tr("All other stocks for receipt list are shown");
					((MainForm*)parentWidget())->statusBar()->showMessage(message);
				}
			}
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
}

void DataForm::OnRowsNumberChanged()
{
	if (parentDialog != nullptr)
	{
		std::string errorMessage = "";
		double sum = 0;
		double priceSum = 0;
		double count = 0;
		int currencyID = 0;
		if (parentDialog->objectName() == "CreateSpecification")
		{
			if (tableView->model()->rowCount() > 0)
			{
				BusinessLayer::Product product;
				for (int i = 0; i < tableView->model()->rowCount(); i++)
				{
					product.Clear();
					product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), tableView->model()->data(tableView->model()->index(i, 5)).toInt(), errorMessage);
					count = count + tableView->model()->data(tableView->model()->index(i, 3)).toDouble();
					sum = sum + (tableView->model()->data(tableView->model()->index(i, 3)).toDouble() * product.GetPrice());
				}
				currencyID = product.GetCurrencyID();
			}
		}
		else if (parentDialog->objectName() == "CreateConsumeProduct" || parentDialog->objectName() == "CreateReceiptProduct"
			|| parentDialog->objectName() == "CreateStockTransfer")
		{
			if (tableView->model()->rowCount() > 0)
			{
				BusinessLayer::Product product;
				BusinessLayer::NetCost nCost;
				for (int i = 0; i < tableView->model()->rowCount(); i++)
				{
					product.Clear();
					product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), tableView->model()->data(tableView->model()->index(i, 11)).toInt(), errorMessage);
					nCost.Clear();
					nCost.GetNetCostByProductID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetID(), errorMessage);
					count = count + tableView->model()->data(tableView->model()->index(i, 7)).toDouble();
					sum = sum + (tableView->model()->data(tableView->model()->index(i, 7)).toDouble() * nCost.GetValue());
					priceSum = priceSum + (tableView->model()->data(tableView->model()->index(i, 7)).toDouble() * product.GetPrice());
				}
				currencyID = product.GetCurrencyID();
			}
		}
		else if (parentDialog->objectName() == "CreateRecieptProduct" || parentDialog->objectName() == "CreateRecieptProduct")
		{
			if (tableView->model()->rowCount() > 0)
			{
				BusinessLayer::Product product;
				BusinessLayer::NetCost nCost;
				for (int i = 0; i < tableView->model()->rowCount(); i++)
				{
					product.Clear();
					product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), tableView->model()->data(tableView->model()->index(i, 11)).toInt(), errorMessage);
					nCost.Clear();
					nCost.GetNetCostByProductID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetID(), errorMessage);
					count = count + tableView->model()->data(tableView->model()->index(i, 7)).toDouble();
					sum = sum + (tableView->model()->data(tableView->model()->index(i, 7)).toDouble() * nCost.GetValue());
					priceSum = priceSum + (tableView->model()->data(tableView->model()->index(i, 7)).toDouble() * product.GetPrice());
				}
				currencyID = product.GetCurrencyID();
			}
		}
		else if (parentDialog->objectName() == "CreateWriteOff" || parentDialog->objectName() == "CreateWriteOff")
		{
			if (tableView->model()->rowCount() > 0)
			{
				BusinessLayer::Product product;
				BusinessLayer::NetCost nCost;
				for (int i = 0; i < tableView->model()->rowCount(); i++)
				{
					product.Clear();
					product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), tableView->model()->data(tableView->model()->index(i, 11)).toInt(), errorMessage);
					nCost.Clear();
					nCost.GetNetCostByProductID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetID(), errorMessage);
					count = count + tableView->model()->data(tableView->model()->index(i, 7)).toDouble();
					sum = sum + (tableView->model()->data(tableView->model()->index(i, 7)).toDouble() * nCost.GetValue());
					priceSum = priceSum + (tableView->model()->data(tableView->model()->index(i, 7)).toDouble() * product.GetPrice());
				}
				currencyID = product.GetCurrencyID();
			}
		}
		else
		{
			if (tableView->model()->rowCount() > 0)
			{
				for (int i = 0; i < tableView->model()->rowCount(); i++)
				{
					sum = sum + tableView->model()->data(tableView->model()->index(i, 8)).toDouble();
					count = count + tableView->model()->data(tableView->model()->index(i, 7)).toDouble();
				}
				currencyID = tableView->model()->data(tableView->model()->index(0, 13)).toInt();
			}
		}
		
		if (parentDialog->objectName() == "CreateConsumeProduct")
		{
			((CreateConPDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateConPDlg*)parentDialog)->sumEdit->setText(QString::number(sum,'f',3));
			((CreateConPDlg*)parentDialog)->priceSumLb->setText(QString::number(priceSum, 'f', 3));
			((CreateConPDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateConPDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateConsumeRaw")
		{
			((CreateConRDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateConRDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateConRDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateConRDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateConsumeOthSt")
		{
			((CreateConOthStDlg*)parentDialog)->othStCountEdit->setText(QString::number(count, 'f', 3));
			((CreateConOthStDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateConOthStDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateConOthStDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateInventorization")
		{
			((CreateInvDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateInvDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateInvDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateInvDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateOrder")
		{
			((CreateOrdDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateOrdDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateOrdDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateOrdDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateOrderRaw")
		{
			((CreateOrdRDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateOrdRDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateOrdRDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateOrdRDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateReceiptOthSt")
		{
			((CreateRcpOthStDlg*)parentDialog)->othStCountEdit->setText(QString::number(count, 'f', 3));
			((CreateRcpOthStDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateRcpOthStDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateRcpOthStDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateReceiptProduct")
		{
			((CreateRcpPDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateRcpPDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateConPDlg*)parentDialog)->priceSumLb->setText(QString::number(priceSum, 'f', 3));
			((CreateRcpPDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateRcpPDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateStockTransfer")
		{
			((CreateStockTrDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateStockTrDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateStockTrDlg*)parentDialog)->priceSumLb->setText(QString::number(priceSum, 'f', 3));
			((CreateStockTrDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateStockTrDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateProductionConsumeRaw")
		{
			((CreateProdConRDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateProdConRDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateProdConRDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateProdConRDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateProductionPlan")
		{
			((CreatePPlanDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreatePPlanDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreatePPlanDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreatePPlanDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateTransport")
		{
			((CreateTrsDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateTrsDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateTrsDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateTrsDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateReturn")
		{
			((CreateRtrnDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateRtrnDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateRtrnDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateRtrnDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateSpecification")
		{
			((CreateSpecDlg*)parentDialog)->prodCountPh->setText(QString::number(count, 'f', 3));
			((CreateSpecDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateSpecDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateSpecDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateSpoilage")
		{
			((CreateSplDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateSplDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateSplDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateSplDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateWriteOff")
		{
			((CreateWOffDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateWOffDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateWOffDlg*)parentDialog)->priceSumLb->setText(QString::number(priceSum, 'f', 3));
			((CreateWOffDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateWOffDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
		else if (parentDialog->objectName() == "CreateWriteOffR")
		{
			((CreateWOffRDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
			((CreateWOffRDlg*)parentDialog)->sumEdit->setText(QString::number(sum, 'f', 3));
			((CreateWOffRDlg*)parentDialog)->currencyCmb->setCurrentIndex(((CreateWOffRDlg*)parentDialog)->currencyCmb->findData(QVariant(currencyID)));
		}
	}
	if (parentDialog->objectName() == "CreateProduction")
	{
		int count = 0;
		if (tableView->model()->rowCount() > 0)
		{
			for (int i = 0; i < tableView->model()->rowCount(); i++)
			{
				count = count + tableView->model()->data(tableView->model()->index(i, 7)).toDouble();
			}
		}
		((CreateProdnDlg*)parentDialog)->prodCountEdit->setText(QString::number(count, 'f', 3));
	}
}

void DataForm::CrtAccDlg()
{
	CreateAccDlg *accountDlg = new CreateAccDlg(dataFormBL, false, this);
	accountDlg->setAttribute(Qt::WA_DeleteOnClose);
	accountDlg->setWindowTitle(tr("Create account"));
	QMdiSubWindow *accountWindow = new QMdiSubWindow;
	accountWindow->setWidget(accountDlg);
	accountWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accountWindow);
	accountDlg->show();
}
void DataForm::UdpAccDlg()
{
	CreateAccDlg *accountDlg = new CreateAccDlg(dataFormBL, true, this);
	accountDlg->setAttribute(Qt::WA_DeleteOnClose);
	accountDlg->setWindowTitle(tr("Update account"));
	QMdiSubWindow *accountWindow = new QMdiSubWindow;
	accountWindow->setWidget(accountDlg);
	accountWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accountWindow);
	if (accountDlg->FillDlgElements(tableView))
	{
		accountDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelAccDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Account account;
	account.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteAccount(&account, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Account with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtAcctblDlg()
{
	CreateAcctbDlg *accountableDlg = new CreateAcctbDlg(dataFormBL, false, this);
	accountableDlg->setAttribute(Qt::WA_DeleteOnClose);
	accountableDlg->setWindowTitle(tr("Create accountable"));
	QMdiSubWindow *accountableWindow = new QMdiSubWindow;
	accountableWindow->setWidget(accountableDlg);
	accountableWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accountableWindow);
	accountableDlg->show();
}
void DataForm::UdpAcctblDlg()
{
	CreateAcctbDlg *accountableDlg = new CreateAcctbDlg(dataFormBL, true, this);
	accountableDlg->setAttribute(Qt::WA_DeleteOnClose);
	accountableDlg->setWindowTitle(tr("Update accountable"));
	QMdiSubWindow *accountableWindow = new QMdiSubWindow;
	accountableWindow->setWidget(accountableDlg);
	accountableWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accountableWindow);
	if (accountableDlg->FillDlgElements(tableView))
	{
		accountableDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelAcctblDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Accountable accountable;
	accountable.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteAccountable(&accountable, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Accountable with this id does not exist!")),
			QString(tr("Ok")));
	}
}


void DataForm::CrtAccblDocDlg()
{
	CreateAccblRepDlg *repDlg = new CreateAccblRepDlg(dataFormBL, false, this);
	repDlg->setAttribute(Qt::WA_DeleteOnClose);
	repDlg->setWindowTitle(tr("Create accountable document"));
	QMdiSubWindow *repWindow = new QMdiSubWindow;
	repWindow->setWidget(repDlg);
	repWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(repWindow);
	repDlg->show();
}
void DataForm::UdpAccblDocDlg()
{
	CreateAccblRepDlg *repDlg = new CreateAccblRepDlg(dataFormBL, true, this);
	repDlg->setAttribute(Qt::WA_DeleteOnClose);
	repDlg->setWindowTitle(tr("Update accountable document"));
	QMdiSubWindow *repWindow = new QMdiSubWindow;
	repWindow->setWidget(repDlg);
	repWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(repWindow);
	if (repDlg->FillDlgElements(tableView))
	{
		repDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelAccblDocDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::AccountableUnionDocument accountableUnionDoc;
	BusinessLayer::AccountableDocument *accountableDoc = new BusinessLayer::AccountableDocument();
	accountableDoc->SetID(id);
	accountableUnionDoc.SetAccountableDocument(accountableDoc);
	
	if (0 != id)
	{
		if (dataFormBL->DeleteAccountableUnionDocument(&accountableUnionDoc, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Accountable document with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewAccblDocDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	
	BusinessLayer::AccountableDocument aDoc;
	BusinessLayer::AccountableTransaction aTransaction;
	
	std::vector<BusinessLayer::AccountableApprovement> approveVec;
	std::vector<BusinessLayer::AccountableDocumentListRelation> docListVec;
	std::vector<BusinessLayer::AccountableEntry> entryVec;
	std::vector<BusinessLayer::AccountablePaymentRelation> paymentVec;
	std::vector<BusinessLayer::AccountableWithdrawalRelation> withdrawalVec;
	std::vector<BusinessLayer::ExpenseDocument> expenseVec;

	BusinessLayer::AccountableApprovement aAapprove;
	BusinessLayer::AccountableDocumentListRelation aDocList;
	BusinessLayer::AccountableEntry aEntry;
	BusinessLayer::AccountablePaymentRelation aPayment;
	BusinessLayer::AccountableWithdrawalRelation aWithdrawal;
	BusinessLayer::ExpenseDocument aExpense;


	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Income chash order"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/accountable.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();

	BusinessLayer::CompanyEmployeeRelation ceRel;
	BusinessLayer::Company company;
	BusinessLayer::Status status;
	int companyID = 0;
	

	if (aDoc.GetAccountableDocumentByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		reportText.replace(QString("DocumentNumberPh"), QString(QString::number(aDoc.GetID())), Qt::CaseInsensitive);
		reportText.replace(QString("DocumentDatePh"), QString(aDoc.GetDate().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("AppointmentPh"), QString(aDoc.GetExpenseAssignment().c_str()), Qt::CaseInsensitive);
		
		companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), aDoc.GetAccountableID(), errorMessage);
		if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot show information for this row!")),
				QString(tr("Ok")));
			return;
		}
		reportText.replace(QString("ComNamePh"), company.GetName().c_str(), Qt::CaseInsensitive);

		if (!status.GetStatusByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), aDoc.GetStatusID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot show information for this row!")),
				QString(tr("Ok")));
			return;
		}
		reportText.replace(QString("UserIDPh"), QString::number(aDoc.GetAccountableID()), Qt::CaseInsensitive);
		reportText.replace(QString("StatusPh"), status.GetName().c_str(), Qt::CaseInsensitive);

		if (!aTransaction.GetAccountableTransactionByAccountableDocumentID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), aDoc.GetID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find transaction for this document!")),
				QString(tr("Ok")));
			return;
		}
		double prevRet = 0;
		double revOver = 0;

		reportText.replace(QString("TotalSumPh"), QString::number(aTransaction.GetTotalValue(),'f',3), Qt::CaseInsensitive);
		reportText.replace(QString("SpentSumPh"), QString::number(aTransaction.GetSpentValue(),'f',3), Qt::CaseInsensitive);
		reportText.replace(QString("RepSumPh"), QString::number(aTransaction.GetResidualValue(),'f',3), Qt::CaseInsensitive);
		reportText.replace(QString("OverSumPh"), QString::number(aTransaction.GetDifferenceValue(),'f',3), Qt::CaseInsensitive);
		

		std::vector<int> approvementIDVector;
		approvementIDVector = aAapprove.GetAllApprovementByAccountableDocumentID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), aDoc.GetID(), errorMessage);
		if (approvementIDVector.size() > 0)
		{
			BusinessLayer::AccountableApprovement approvement;
			BusinessLayer::User user;
			for each (auto approveID in approvementIDVector)
			{
				approvement.Clear();
				if (approvement.GetAccountableApprovementByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), approveID, errorMessage))
				{
					approveVec.push_back(approvement);
					if (approvement.GetDirectorID() > 0)
					{
						user.Clear();
						if (user.GetUserByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), approvement.GetDirectorID(), errorMessage))
						{
							reportText.replace(QString("DirectorPh"), QString(user.GetSurname().c_str() + QString(" ") + user.GetSurname().c_str()), Qt::CaseInsensitive);
						}
					}
					if (approvement.GetAccountantID() > 0)
					{
						user.Clear();
						if (user.GetUserByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), approvement.GetAccountantID(), errorMessage))
						{
							reportText.replace(QString("AccounantNamePh"), QString(user.GetSurname().c_str() + QString(" ") + user.GetSurname().c_str()), Qt::CaseInsensitive);
						}
					}
					reportText.replace(QString("ApproveDatePh"), QString(approvement.GetApproveDate().c_str()), Qt::CaseInsensitive);
				}
			}
		}

		BusinessLayer::Accountable accountable;
		if (accountable.GetAccountableByUserID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), aDoc.GetAccountableID(), errorMessage))
		{
			
			BusinessLayer::User user;
			BusinessLayer::CompanyEmployeeRelation comEmp;
			BusinessLayer::Branch branch;
			BusinessLayer::Position position;
			BusinessLayer::Role role;
			BusinessLayer::Employee employee;
			BusinessLayer::Company company;
			user.Clear();
			if (user.GetUserByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage))
			{

				reportText.replace(QString("AccountableDataPh"), QString(user.GetSurname().c_str() + QString(" ") + user.GetSurname().c_str()), Qt::CaseInsensitive);
				int branchid = 0;
				int companyID = 0;
				branchid = comEmp.GetBranchByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage);
				companyID = comEmp.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage);
				if (companyID > 0)
				{
					if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage))
					{
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr("Connot find company for this employee!")),
							QString(tr("Ok")));
						return;
					}
				}
				comEmp.Clear();
				if (branchid > 0)
				{
					if (branch.GetBranchByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), branchid, errorMessage))
					{
						reportText.replace(QString("DivisionPh"), QString(branch.GetName().c_str()), Qt::CaseInsensitive);
					}
					if (employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), user.GetID(), errorMessage))
					{
						if (position.GetPositionByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), employee.GetPositionID(), errorMessage))
						{
							reportText.replace(QString("PositionPh"), QString(position.GetName().c_str()), Qt::CaseInsensitive);
						}
					}
				}
			}
		}

		std::vector<int> docListIDVector;
		double totalExpenseSum = 0;
		QString tableBody;
		QString currencyShortName;;
		docListIDVector = aDocList.GetAllListByAccountableDocumentID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), aDoc.GetID(), errorMessage);
		if (docListIDVector.size() > 0)
		{
			BusinessLayer::AccountableDocumentListRelation docList;
			BusinessLayer::ExpenseDocument eDocument;
			BusinessLayer::Measure measure;
			BusinessLayer::Currency currency;
			for each (auto listID in docListIDVector)
			{
				docList.Clear();
				eDocument.Clear();
				if (docList.GetDocumentListByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), listID, errorMessage))
				{
					docListVec.push_back(docList);
					if (eDocument.GetExpenseDocumentByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), docList.GetExpenseDocumentID(), errorMessage))
					{
						measure.Clear();
						currency.Clear();
						if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), eDocument.GetMeasureID(), errorMessage))
							continue;
						if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), eDocument.GetCurrencyID(), errorMessage))
							continue;
						tableBody += "<tr>";
						tableBody += "<td>" + QString::number(eDocument.GetID()) + "</td>";
						tableBody += "<td>" + QString(eDocument.GetExpenseName().c_str()) + "</td>";
						tableBody += "<td>" + QString::number(eDocument.GetCount()) + "</td>";
						tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
						tableBody += "<td>" + QString::number(eDocument.GetSum()) + "</td>";
						tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
						tableBody += "</tr>";
						totalExpenseSum += eDocument.GetSum();
						currencyShortName = currency.GetShortName().c_str();
					}
				}
			}
			reportText.replace(QString("TableBodyPh"), QString(tableBody), Qt::CaseInsensitive);
			reportText.replace(QString("SpentSumPh"), QString::number(totalExpenseSum,'f',3), Qt::CaseInsensitive);
			reportText.replace(QString("CurrencyPh"), QString(currencyShortName), Qt::CaseInsensitive);
		}

	

		std::vector<int> entryIDVector;
		double totalEntrySum = 0;
		QString eTableBody;
		entryIDVector = aEntry.GetAllEntryByAccountableDocumentID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), aDoc.GetID(), errorMessage);
		if (entryIDVector.size() > 0)
		{
			BusinessLayer::AccountableEntry  enEntry;
			BusinessLayer::Account  debAcc;
			BusinessLayer::Account  credAcc;
			for each (auto entryID in entryIDVector)
			{
				enEntry.Clear();
				if (enEntry.GetAccountableEntryByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), entryID, errorMessage))
				{
					debAcc.Clear();
					credAcc.Clear();
					if (!debAcc.GetAccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), enEntry.GetDebitAccountID(), errorMessage))
						continue;
					if (!credAcc.GetAccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), enEntry.GetCreditAccountID(), errorMessage))
						continue;
					eTableBody += "<tr style = 'width:100%; border: 0px solid black; text-align: center; '>";
					eTableBody += "<td style = 'width:30% ; border: 1px solid black; text-align: center; '>" + QString(debAcc.GetNumber().c_str()) + "</td>";
					eTableBody += "<td style = 'width:20% ; border: 1px solid black; text-align: center; '>" + QString::number(enEntry.GetValue()) + "</td>";
					eTableBody += "<td style = 'width:30% ; border: 1px solid black; text-align: center; '>" + QString(credAcc.GetNumber().c_str()) + "</td>";
					eTableBody += "<td style = 'width:20% ; border: 1px solid black; text-align: center; '>" + QString::number(enEntry.GetValue()) + "</td>";
					eTableBody += "<tr>";
					totalEntrySum += enEntry.GetValue();
				}
			}
			reportText.replace(QString("EntriesPh"), QString(eTableBody), Qt::CaseInsensitive);
			reportText.replace(QString("TotalEntryPh"), QString::number(totalEntrySum, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("CurrencyPh"), QString(currencyShortName), Qt::CaseInsensitive);
		}

		double paySum = 0;
		std::vector<int> paymentIDVector;
		QString pTableBody;
		paymentIDVector = aPayment.GetAllPaymentByAccountableDocumentID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), aDoc.GetID(), errorMessage);
		if (paymentIDVector.size() > 0)
		{
			BusinessLayer::AccountablePaymentRelation ePayment;
			BusinessLayer::Payment payment;
			QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
			for each (auto paymentID in paymentIDVector)
			{
				ePayment.Clear();
				payment.Clear();
				if (ePayment.GetAccountablePaymentByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), paymentID, errorMessage))
				{
					if (payment.GetPaymentByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), ePayment.GetPaymentID(), errorMessage))
					{
						pTableBody += "<tr style = 'width:100% ; border: 0px solid black; text - align: center; '>";
						pTableBody += "<td style = 'width:45% ; border: 1px solid black; text - align: center; '>" + QString::fromLocal8Bit("Возврат подотчетной суммы <b>ПКО №") + QString::number(payment.GetID()) + "</b></td>";

						pTableBody += "<td style = 'width:45% ; border: 1px solid black; text - align: center; <b>'>" + QString::number(payment.GetValue()) + "</b></td>";

						pTableBody += "</tr>";
						paySum += payment.GetValue();
					}
				}
			}
			reportText.replace(QString("WithdrawalPh"), QString(pTableBody), Qt::CaseInsensitive);
		}

		double withSum = 0;
		std::vector<int> withdrawalIDVector;
		QString wTableBody;
		withdrawalIDVector = aWithdrawal.GetAllWithdrawalByAccountableDocumentID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage);
		if (withdrawalIDVector.size() > 0)
		{
			BusinessLayer::AccountableWithdrawalRelation eWithdrawal;
			BusinessLayer::Withdrawal withdrawal;
			QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
			for each (auto withdrawalID in withdrawalIDVector)
			{
				eWithdrawal.Clear();
				withdrawal.Clear();
				if (eWithdrawal.GetAccountableWithdrawalByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), withdrawalID, errorMessage))
				{
					if (withdrawal.GetWithdrawalByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), eWithdrawal.GetWithdrawalID(), errorMessage))
					{
						wTableBody += "<tr style = 'width:100% ; border: 0px solid black; text - align: center; '>";
						wTableBody += "<td style = 'width:45% ; border: 1px solid black; text - align: center; '>" + QString::fromLocal8Bit("Получен аванс <b>РКО №") + QString::number(withdrawal.GetID()) + "</b></td>";

						wTableBody += "<td style = 'width:45% ; border: 1px solid black; text - align: center; <b>'>" + QString::number(withdrawal.GetValue()) + "</b></td>";

						wTableBody += "</tr>";
						withSum += withdrawal.GetValue();
					}
				}
			}
			reportText.replace(QString("PaymentPh"), QString(wTableBody), Qt::CaseInsensitive);
		}

		if (aTransaction.GetTotalValue() - withSum + paySum >= 0)
		{
			reportText.replace(QString("PrevRemPh"), QString::number(aTransaction.GetTotalValue() - withSum + paySum, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("PrevOverPh"), QString::number(0), Qt::CaseInsensitive);
		}
		else
		{
			reportText.replace(QString("PrevRemPh"), QString::number(0), Qt::CaseInsensitive);
			reportText.replace(QString("PrevOverPh"), QString::number(aTransaction.GetTotalValue() - withSum + paySum, 'f', 3), Qt::CaseInsensitive);
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot find document!")),
			QString(tr("Ok")));
		return;
	}

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}


void DataForm::CrtAccTpDlg()
{
	CreateAccTpDlg *accountTpDlg = new CreateAccTpDlg(dataFormBL, false, this);
	accountTpDlg->setAttribute(Qt::WA_DeleteOnClose);
	accountTpDlg->setWindowTitle(tr("Create account type"));
	QMdiSubWindow *accountTpWindow = new QMdiSubWindow;
	accountTpWindow->setWidget(accountTpDlg);
	accountTpWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accountTpWindow);
	accountTpDlg->show();
}
void DataForm::UdpAccTpDlg()
{
	CreateAccTpDlg *accountTpDlg = new CreateAccTpDlg(dataFormBL, true, this);
	accountTpDlg->setAttribute(Qt::WA_DeleteOnClose);
	accountTpDlg->setWindowTitle(tr("Update account type"));
	QMdiSubWindow *accountTpWindow = new QMdiSubWindow;
	accountTpWindow->setWidget(accountTpDlg);
	accountTpWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accountTpWindow);
	if (accountTpDlg->FillDlgElements(tableView))
	{
		accountTpDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelAccTpDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::AccountType accountType;
	accountType.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteAccountType(&accountType, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Account type with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtAcsDlg()
{
	CreateAcsDlg *accessDlg = new CreateAcsDlg(dataFormBL, false, this);
	accessDlg->setAttribute(Qt::WA_DeleteOnClose);
	accessDlg->setWindowTitle(tr("Create access"));
	QMdiSubWindow *accessWindow = new QMdiSubWindow;
	accessWindow->setWidget(accessDlg);
	accessWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accessWindow);
	accessDlg->show();
}
void DataForm::UdpAcsDlg()
{
	CreateAcsDlg *accessDlg = new CreateAcsDlg(dataFormBL, true, this);
	accessDlg->setAttribute(Qt::WA_DeleteOnClose);
	accessDlg->setWindowTitle(tr("Update access"));
	QMdiSubWindow *accessWindow = new QMdiSubWindow;
	accessWindow->setWidget(accessDlg);
	accessWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accessWindow);
	if (accessDlg->FillDlgElements(tableView))
	{
		accessDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelAcsDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Access access;
	access.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteAccess(&access, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtAcsItemDlg()
{
	CreateAcsItemDlg *accessItemDlg = new CreateAcsItemDlg(dataFormBL, false, this);
	accessItemDlg->setAttribute(Qt::WA_DeleteOnClose);
	accessItemDlg->setWindowTitle(tr("Create access item"));
	QMdiSubWindow *accessItemWindow = new QMdiSubWindow;
	accessItemWindow->setWidget(accessItemDlg);
	accessItemWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accessItemWindow);
	accessItemDlg->show();
}
void DataForm::UdpAcsItemDlg()
{
	CreateAcsItemDlg *accessItemDlg = new CreateAcsItemDlg(dataFormBL, true, this);
	accessItemDlg->setAttribute(Qt::WA_DeleteOnClose);
	accessItemDlg->setWindowTitle(tr("Update access item"));
	QMdiSubWindow *accessItemWindow = new QMdiSubWindow;
	accessItemWindow->setWidget(accessItemDlg);
	accessItemWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(accessItemWindow);
	if (accessItemDlg->FillDlgElements(tableView))
	{
		accessItemDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelAcsItemDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::AccessItem accessItem;
	accessItem.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteAccessItem(&accessItem, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access item with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtAmGrDlg()
{
	CreateAmGrDlg *amGrDlg = new CreateAmGrDlg(dataFormBL, false, this);
	amGrDlg->setAttribute(Qt::WA_DeleteOnClose);
	amGrDlg->setWindowTitle(tr("Create amortime group"));
	QMdiSubWindow *amGrWindow = new QMdiSubWindow;
	amGrWindow->setWidget(amGrDlg);
	amGrWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(amGrWindow);
	amGrDlg->show();
}
void DataForm::UdpAmGrDlg()
{
	CreateAmGrDlg *amGrDlg = new CreateAmGrDlg(dataFormBL, true, this);
	amGrDlg->setAttribute(Qt::WA_DeleteOnClose);
	amGrDlg->setWindowTitle(tr("Update amortime group"));
	QMdiSubWindow *amGrWindow = new QMdiSubWindow;
	amGrWindow->setWidget(amGrDlg);
	amGrWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(amGrWindow);
	if (amGrDlg->FillDlgElements(tableView))
	{
		amGrDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelAmGrDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::AmortizeGroup amGr;
	amGr.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteAmortizeGroup(&amGr, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Amortize group with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtAmTypeDlg()
{
	CreateAmTypeDlg *amTypeDlg = new CreateAmTypeDlg(dataFormBL, false, this);
	amTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	amTypeDlg->setWindowTitle(tr("Create amortime type"));
	QMdiSubWindow *amTypeWindow = new QMdiSubWindow;
	amTypeWindow->setWidget(amTypeDlg);
	amTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(amTypeWindow);
	amTypeDlg->show();
}
void DataForm::UdpAmTypeDlg()
{
	CreateAmTypeDlg *amTypeDlg = new CreateAmTypeDlg(dataFormBL, true, this);
	amTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	amTypeDlg->setWindowTitle(tr("Update amortime type"));
	QMdiSubWindow *amTypeWindow = new QMdiSubWindow;
	amTypeWindow->setWidget(amTypeDlg);
	amTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(amTypeWindow);
	if (amTypeDlg->FillDlgElements(tableView))
	{
		amTypeDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelAmTypeDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::AmortizeType amType;
	amType.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteAmortizeType(&amType, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Amortize type with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtBlcDlg()
{
	CreateBlcDlg *balanceDlg = new CreateBlcDlg(dataFormBL, false, this);
	balanceDlg->setAttribute(Qt::WA_DeleteOnClose);
	balanceDlg->setWindowTitle(tr("Create balance"));
	QMdiSubWindow *balanceWindow = new QMdiSubWindow;
	balanceWindow->setWidget(balanceDlg);
	balanceWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(balanceWindow);
	balanceDlg->show();
}
void DataForm::UdpBlcDlg()
{
	CreateBlcDlg *balanceDlg = new CreateBlcDlg(dataFormBL, true, this);
	balanceDlg->setAttribute(Qt::WA_DeleteOnClose);
	balanceDlg->setWindowTitle(tr("Update balance"));
	QMdiSubWindow *balanceWindow = new QMdiSubWindow;
	balanceWindow->setWidget(balanceDlg);
	balanceWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(balanceWindow);
	if (balanceDlg->FillDlgElements(tableView))
	{
		balanceDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelBlcDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Balance balance;
	balance.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteBalance(&balance, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Balance with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtBrhDlg()
{
	CreateBrhDlg *branchDlg = new CreateBrhDlg(dataFormBL, false, this);
	branchDlg->setAttribute(Qt::WA_DeleteOnClose);
	branchDlg->setWindowTitle(tr("Create branch"));
	QMdiSubWindow *branchWindow = new QMdiSubWindow;
	branchWindow->setWidget(branchDlg);
	branchWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(branchWindow);
	branchDlg->show();
}
void DataForm::UdpBrhDlg()
{
	CreateBrhDlg *branchDlg = new CreateBrhDlg(dataFormBL, true, this);
	branchDlg->setAttribute(Qt::WA_DeleteOnClose);
	branchDlg->setWindowTitle(tr("Update branch"));
	QMdiSubWindow *branchWindow = new QMdiSubWindow;
	branchWindow->setWidget(branchDlg);
	branchWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(branchWindow);
	if (branchDlg->FillDlgElements(tableView))
	{
		branchDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelBrhDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Branch branch;
	branch.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteBranch(&branch, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Branch with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtBrSAccDlg()
{
	CreateBrSAccDlg *branchSAccDlg = new CreateBrSAccDlg(dataFormBL, false, this);
	branchSAccDlg->setAttribute(Qt::WA_DeleteOnClose);
	branchSAccDlg->setWindowTitle(tr("Create branch subaccount"));
	QMdiSubWindow *branchSAccWindow = new QMdiSubWindow;
	branchSAccWindow->setWidget(branchSAccDlg);
	branchSAccWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(branchSAccWindow);
	branchSAccDlg->show();
}
void DataForm::UdpBrSAccDlg()
{
	CreateBrSAccDlg *branchSAccDlg = new CreateBrSAccDlg(dataFormBL, true, this);
	branchSAccDlg->setAttribute(Qt::WA_DeleteOnClose);
	branchSAccDlg->setWindowTitle(tr("Update branch subaccount"));
	QMdiSubWindow *branchSAccWindow = new QMdiSubWindow;
	branchSAccWindow->setWidget(branchSAccDlg);
	branchSAccWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(branchSAccWindow);
	if (branchSAccDlg->FillDlgElements(tableView))
	{
		branchSAccDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelBrSAccDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::BranchSubaccountRelation branchSub;
	branchSub.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteBranchSubaccount(&branchSub, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Branch subaccount with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtBrwDlg()
{
	CreateBrwDlg *borroweDlg = new CreateBrwDlg(dataFormBL, false, this);
	borroweDlg->setAttribute(Qt::WA_DeleteOnClose);
	borroweDlg->setWindowTitle(tr("Create borrower"));
	QMdiSubWindow *borrowerWindow = new QMdiSubWindow;
	borrowerWindow->setWidget(borroweDlg);
	borrowerWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(borrowerWindow);
	borroweDlg->show();
}
void DataForm::UdpBrwDlg()
{
	CreateBrwDlg *borroweDlg = new CreateBrwDlg(dataFormBL, true, this);
	borroweDlg->setAttribute(Qt::WA_DeleteOnClose);
	borroweDlg->setWindowTitle(tr("Update borrower"));
	QMdiSubWindow *borrowerWindow = new QMdiSubWindow;
	borrowerWindow->setWidget(borroweDlg);
	borrowerWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(borrowerWindow);
	if (borroweDlg->FillDlgElements(tableView))
	{
		borrowerWindow->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelBrwDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Borrower borrower;
	borrower.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteBorrower(&borrower, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Borrower with this id does not exist!")),
			QString(tr("Ok")));
	}
}


void DataForm::CrtCbxDlg()
{
	CreateCbxDlg *cashboxDlg = new CreateCbxDlg(dataFormBL, false, this);
	cashboxDlg->setAttribute(Qt::WA_DeleteOnClose);
	cashboxDlg->setWindowTitle(tr("Create cashbox"));
	QMdiSubWindow *cashboxWindow = new QMdiSubWindow;
	cashboxWindow->setWidget(cashboxDlg);
	cashboxWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(cashboxWindow);
	cashboxDlg->show();
}
void DataForm::UdpCbxDlg()
{
	CreateCbxDlg *cashboxDlg = new CreateCbxDlg(dataFormBL, true, this);
	cashboxDlg->setAttribute(Qt::WA_DeleteOnClose);
	cashboxDlg->setWindowTitle(tr("Update cashbox"));
	QMdiSubWindow *cashboxWindow = new QMdiSubWindow;
	cashboxWindow->setWidget(cashboxDlg);
	cashboxWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(cashboxWindow);
	if (cashboxDlg->FillDlgElements(tableView))
	{
		cashboxDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelCbxDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Cashbox cashbox;
	cashbox.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteCashbox(&cashbox, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Cashbox with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtCASHERDlg()
{
	CreateCASHERDlg *cashRelDlg = new CreateCASHERDlg(dataFormBL, false, this);
	cashRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	cashRelDlg->setWindowTitle(tr("Create cashbox-employee relation"));
	QMdiSubWindow *cashRelWindow = new QMdiSubWindow;
	cashRelWindow->setWidget(cashRelDlg);
	cashRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(cashRelWindow);
	cashRelDlg->show();
}
void DataForm::UdpCASHERDlg()
{
	CreateCASHERDlg *cashRelDlg = new CreateCASHERDlg(dataFormBL, true, this);
	cashRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	cashRelDlg->setWindowTitle(tr("Update cashbox-employee relation"));
	QMdiSubWindow *cashRelWindow = new QMdiSubWindow;
	cashRelWindow->setWidget(cashRelDlg);
	cashRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(cashRelWindow);
	if (cashRelDlg->FillDlgElements(tableView))
	{
		cashRelDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelCASHERDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::CashboxEmployeeRelation cashRel;

	if (0 != id && cashRel.GetCashboxEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		if (dataFormBL->DeleteCashboxEmployeeRelation(&cashRel, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Cashbox-employee relation with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtCltDlg()
{
	CreateCltDlg *clientDlg = new CreateCltDlg(dataFormBL, false, this);
	clientDlg->setAttribute(Qt::WA_DeleteOnClose);
	clientDlg->setWindowTitle(tr("Create client"));
	QMdiSubWindow *clientWindow = new QMdiSubWindow;
	clientWindow->setWidget(clientDlg);
	clientWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(clientWindow);
	clientDlg->show();
}
void DataForm::UdpCltDlg()
{
	CreateCltDlg *clientDlg = new CreateCltDlg(dataFormBL, true, this);
	clientDlg->setAttribute(Qt::WA_DeleteOnClose);
	clientDlg->setWindowTitle(tr("Update client"));
	QMdiSubWindow *clientWindow = new QMdiSubWindow;
	clientWindow->setWidget(clientDlg);
	clientWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(clientWindow);
	if (clientDlg->FillDlgElements(tableView))
	{
		clientDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelCltDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Client client;
	client.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteClient(&client, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Client with this id does not exist!")),
			QString(tr("Ok")));
	}
}


void DataForm::CrtCmpDlg()
{
	CreateCmpDlg *companyDlg = new CreateCmpDlg(dataFormBL,false,this);
	companyDlg->setAttribute(Qt::WA_DeleteOnClose);
	companyDlg->setWindowTitle(tr("Create company"));
	QMdiSubWindow *companyWindow = new QMdiSubWindow;
	companyWindow->setWidget(companyDlg);
	companyWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(companyWindow);
	companyDlg->show();
}
void DataForm::UdpCmpDlg()
{
	CreateCmpDlg *companyDlg = new CreateCmpDlg(dataFormBL,true, this);
	companyDlg->setAttribute(Qt::WA_DeleteOnClose);
	companyDlg->setWindowTitle(tr("Update company"));
	QMdiSubWindow *companyWindow = new QMdiSubWindow;
	companyWindow->setWidget(companyDlg);
	companyWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(companyWindow);
	if (companyDlg->FillDlgElements(tableView))
	{
		companyDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelCmpDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Company company;
	company.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteCompany(&company, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Company with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtCERDlg()
{
	CreateCERDlg *ceRelDlg = new CreateCERDlg(dataFormBL, false, this);
	ceRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	ceRelDlg->setWindowTitle(tr("Create company-employee relation"));
	QMdiSubWindow *ceRelWindow = new QMdiSubWindow;
	ceRelWindow->setWidget(ceRelDlg);
	ceRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(ceRelWindow);
	ceRelDlg->show();
}
void DataForm::UdpCERDlg()
{
	CreateCERDlg *ceRelDlg = new CreateCERDlg(dataFormBL, true, this);
	ceRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	ceRelDlg->setWindowTitle(tr("Update company-employee relation"));
	QMdiSubWindow *ceRelWindow = new QMdiSubWindow;
	ceRelWindow->setWidget(ceRelDlg);
	ceRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(ceRelWindow);
	if (ceRelDlg->FillDlgElements(tableView))
	{
		ceRelDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelCERDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::CompanyEmployeeRelation ceRel;
	
	if (0 != id && ceRel.GetCompanyEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		if (dataFormBL->DeleteCompanyEmployeeRelation(&ceRel, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Company-employee relation with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtCARDlg()
{
	CreateCARDlg *caRelDlg = new CreateCARDlg(dataFormBL, false, this);
	caRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	caRelDlg->setWindowTitle(tr("Create company-account relation"));
	QMdiSubWindow *caRelWindow = new QMdiSubWindow;
	caRelWindow->setWidget(caRelDlg);
	caRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(caRelWindow);
	caRelDlg->show();
}
void DataForm::UdpCARDlg()
{
	CreateCARDlg *caRelDlg = new CreateCARDlg(dataFormBL, true, this);
	caRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	caRelDlg->setWindowTitle(tr("Update company-account relation"));
	QMdiSubWindow *caRelWindow = new QMdiSubWindow;
	caRelWindow->setWidget(caRelDlg);
	caRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(caRelWindow);
	if (caRelDlg->FillDlgElements(tableView))
	{
		caRelDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelCARDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::CompanyAccountRelation caRel;

	if (0 != id && caRel.GetCompanyAccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		if (dataFormBL->DeleteCompanyAccountRelation(&caRel, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Company-account relation with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtCOADlg()
{
	CreateCOADlg *coAccDlg = new CreateCOADlg(dataFormBL, false, this);
	coAccDlg->setAttribute(Qt::WA_DeleteOnClose);
	coAccDlg->setWindowTitle(tr("Create chart of account"));
	QMdiSubWindow *coAccWindow = new QMdiSubWindow;
	coAccWindow->setWidget(coAccDlg);
	coAccWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(coAccWindow);
	coAccDlg->show();
}
void DataForm::UdpCOADlg()
{
	CreateCOADlg *coAccDlg = new CreateCOADlg(dataFormBL, true, this);
	coAccDlg->setAttribute(Qt::WA_DeleteOnClose);
	coAccDlg->setWindowTitle(tr("Update chart of account"));
	QMdiSubWindow *coAccWindow = new QMdiSubWindow;
	coAccWindow->setWidget(coAccDlg);
	coAccWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(coAccWindow);
	if (coAccDlg->FillDlgElements(tableView))
	{
		coAccDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelCOADlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ChartOfAccounts coAcc;
	coAcc.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteChartOfAccounts(&coAcc, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Chart of account with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtConPDlg()
{
	CreateConPDlg *conPDlg = new CreateConPDlg(dataFormBL, false, this);
	conPDlg->setAttribute(Qt::WA_DeleteOnClose);
	conPDlg->setWindowTitle(tr("Create consume product"));
	QMdiSubWindow *conPWindow = new QMdiSubWindow;
	conPWindow->setWidget(conPDlg);
	conPWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(conPWindow);
	conPDlg->show();
}
void DataForm::UdpConPDlg()
{
	CreateConPDlg *conPDlg = new CreateConPDlg(dataFormBL, true, this);
	conPDlg->setAttribute(Qt::WA_DeleteOnClose);
	conPDlg->setWindowTitle(tr("Update consume product"));
	QMdiSubWindow *conPWindow = new QMdiSubWindow;
	conPWindow->setWidget(conPDlg);
	conPWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(conPWindow);
	if (conPDlg->FillDlgElements(tableView))
	{
		conPDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelConPDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeProduct consumeProdcut;
	consumeProdcut.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteConsumeProduct(&consumeProdcut, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Consume product with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewConPDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeProduct consumeProdcut;
	if (!consumeProdcut.GetConsumeProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ConsumeProductList consumeProdcutList;
	BusinessLayer::Employee employee;
	BusinessLayer::Employee stockEmployee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeProdcut.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeProdcut.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!stockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeProdcut.GetStockEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	
	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);
	
	QFile file;
	file.setFileName(":/docs/invoice.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	consumeProdcutList.SetConsumeProductID(consumeProdcut.GetID());
	std::string filter = consumeProdcutList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ConsumeProductListView> vecConProdList = dataFormBL->GetAllDataForClass<BusinessLayer::ConsumeProductListView>(errorMessage, filter);
	if (vecConProdList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(consumeProdcut.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(consumeProdcut.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(stockEmployee.GetSurname().c_str()) + " " + QString(stockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	BusinessLayer::NetCost netCost;
	QString tableBody;
	double sum = 0;
	for each (auto item in vecConProdList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		netCost.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!netCost.GetNetCostByProductID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()*product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		sum += item.GetCount()*product.GetPrice();
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(sum), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtConPListDlg()
{
	CreateConPListDlg *craeteConPListDlg = new CreateConPListDlg(dataFormBL, false, this);
	if (0 != consumeProductID)
	{
		craeteConPListDlg->consumeProductID = consumeProductID;
	}
	craeteConPListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteConPListDlg->setWindowTitle(tr("Add product to consume product list"));
	QMdiSubWindow *craeteConPListWindow = new QMdiSubWindow;
	craeteConPListWindow->setWidget(craeteConPListDlg);
	craeteConPListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteConPListWindow);
	craeteConPListDlg->show();
}
void DataForm::UdpConPListDlg()
{
	CreateConPListDlg *craeteConPListDlg = new CreateConPListDlg(dataFormBL, true, this);
	craeteConPListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteConPListDlg->setWindowTitle(tr("Update product in consume product list"));
	QMdiSubWindow *craeteConPListWindow = new QMdiSubWindow;
	craeteConPListWindow->setWidget(craeteConPListDlg);
	craeteConPListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteConPListWindow);
	if (craeteConPListDlg->FillDlgElements(tableView))
	{
		craeteConPListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelConPListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeProductList consumeProductList;
	consumeProductList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteConsumeProductList(&consumeProductList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtConOthStDlg()
{
	CreateConOthStDlg *conOthStDlg = new CreateConOthStDlg(dataFormBL, false, this);
	conOthStDlg->setAttribute(Qt::WA_DeleteOnClose);
	conOthStDlg->setWindowTitle(tr("Create consume other stocks"));
	QMdiSubWindow *cosRWindow = new QMdiSubWindow;
	cosRWindow->setWidget(conOthStDlg);
	cosRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(cosRWindow);
	conOthStDlg->show();
}
void DataForm::UdpConOthStDlg()
{
	CreateConOthStDlg *conOthStDlg = new CreateConOthStDlg(dataFormBL, true, this);
	conOthStDlg->setAttribute(Qt::WA_DeleteOnClose);
	conOthStDlg->setWindowTitle(tr("Update consume other stocks"));
	QMdiSubWindow *cosRWindow = new QMdiSubWindow;
	cosRWindow->setWidget(conOthStDlg);
	cosRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(cosRWindow);
	if (conOthStDlg->FillDlgElements(tableView))
	{
		conOthStDlg->show();
	}
	/*else
	{
	QMessageBox::information(NULL, QString(tr("Warning")),
	QString(tr("Please select one row at first!")),
	QString(tr("Ok")));
	}*/
}
void DataForm::DelConOthStDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeOtherStocks consumeOtherStocks;
	consumeOtherStocks.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteConsumeOtherStocks(&consumeOtherStocks, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Consume other stocks with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewConOthStDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeOtherStocks consumeOtherStocks;
	if (!consumeOtherStocks.GetConsumeOtherStocksByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ConsumeOtherStocksList consumeOtherStocksList;
	BusinessLayer::Employee employee;
	BusinessLayer::Employee stockEmployee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeOtherStocks.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeOtherStocks.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!stockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeOtherStocks.GetStockEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/invoice.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	consumeOtherStocksList.SetConsumeOtherStocksID(consumeOtherStocks.GetID());
	std::string filter = consumeOtherStocksList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ConsumeOtherStocksListView> vecConOthStList = dataFormBL->GetAllDataForClass<BusinessLayer::ConsumeOtherStocksListView>(errorMessage, filter);
	if (vecConOthStList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(consumeOtherStocks.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(consumeOtherStocks.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(stockEmployee.GetSurname().c_str()) + " " + QString(stockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::OtherStocks otherStocks;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	for each (auto item in vecConOthStList)
	{
		otherStocks.Clear();
		measure.Clear();
		currency.Clear();
		if (!otherStocks.GetOtherStocksByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetOtherStocksID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Other stocks is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), otherStocks.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), otherStocks.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(otherStocks.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(consumeOtherStocks.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtConOthStListDlg()
{
	CreateConOthStListDlg *craeteConOthStListDlg = new CreateConOthStListDlg(dataFormBL, false, this);
	if (0 != consumeOtherStocksID)
	{
		craeteConOthStListDlg->consumeOtherStocksID = consumeOtherStocksID;
	}
	craeteConOthStListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteConOthStListDlg->setWindowTitle(tr("Add other stocks to consume list"));
	QMdiSubWindow *craeteConOthStListWindow = new QMdiSubWindow;
	craeteConOthStListWindow->setWidget(craeteConOthStListDlg);
	craeteConOthStListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteConOthStListWindow);
	craeteConOthStListDlg->show();
}
void DataForm::UdpConOthStListDlg()
{
	CreateConOthStListDlg *craeteConOthStListDlg = new CreateConOthStListDlg(dataFormBL, true, this);
	craeteConOthStListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteConOthStListDlg->setWindowTitle(tr("Update product in consume product list"));
	QMdiSubWindow *craeteConOthStListWindow = new QMdiSubWindow;
	craeteConOthStListWindow->setWidget(craeteConOthStListDlg);
	craeteConOthStListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteConOthStListWindow);
	if (craeteConOthStListDlg->FillDlgElements(tableView))
	{
		craeteConOthStListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelConOthStListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeOtherStocksList consumeOtherStocksList;
	consumeOtherStocksList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteConsumeOtherStocksList(&consumeOtherStocksList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtConRDlg()
{
	CreateConRDlg *conRDlg = new CreateConRDlg(dataFormBL, false, this);
	conRDlg->setAttribute(Qt::WA_DeleteOnClose);
	conRDlg->setWindowTitle(tr("Create consume raw"));
	QMdiSubWindow *conRWindow = new QMdiSubWindow;
	conRWindow->setWidget(conRDlg);
	conRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(conRWindow);
	conRDlg->show();
}
void DataForm::UdpConRDlg()
{
	CreateConRDlg *conRDlg = new CreateConRDlg(dataFormBL, true, this);
	conRDlg->setAttribute(Qt::WA_DeleteOnClose);
	conRDlg->setWindowTitle(tr("Update consume raw"));
	QMdiSubWindow *conRWindow = new QMdiSubWindow;
	conRWindow->setWidget(conRDlg);
	conRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(conRWindow);
	if (conRDlg->FillDlgElements(tableView))
	{
		conRDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelConRDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeRaw consumeRaw;
	consumeRaw.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteConsumeRaw(&consumeRaw, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Consume raw with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewConRDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeRaw consumeRaw;
	if (!consumeRaw.GetConsumeRawByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ConsumeRawList consumeRawList;
	BusinessLayer::Employee employee;
	BusinessLayer::Employee stockEmployee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeRaw.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeRaw.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!stockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), consumeRaw.GetStockEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/invoice.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	consumeRawList.SetConsumeRawID(consumeRaw.GetID());
	std::string filter = consumeRawList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ConsumeRawListView> vecConRawList = dataFormBL->GetAllDataForClass<BusinessLayer::ConsumeRawListView>(errorMessage, filter);
	if (vecConRawList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(consumeRaw.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(consumeRaw.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(stockEmployee.GetSurname().c_str()) + " " + QString(stockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	for each (auto item in vecConRawList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(consumeRaw.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtConRListDlg()
{
	CreateConRListDlg *craeteConRListDlg = new CreateConRListDlg(dataFormBL, false, this);
	if (0 != consumeRawID)
	{
		craeteConRListDlg->consumeRawID = consumeRawID;
	}
	craeteConRListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteConRListDlg->setWindowTitle(tr("Add raw to consume raw list"));
	QMdiSubWindow *craeteConRListWindow = new QMdiSubWindow;
	craeteConRListWindow->setWidget(craeteConRListDlg);
	craeteConRListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteConRListWindow);
	craeteConRListDlg->show();
}
void DataForm::UdpConRListDlg()
{
	CreateConRListDlg *craeteConRListDlg = new CreateConRListDlg(dataFormBL, true, this);
	craeteConRListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteConRListDlg->setWindowTitle(tr("Update raw in consume raw list"));
	QMdiSubWindow *craeteConRListWindow = new QMdiSubWindow;
	craeteConRListWindow->setWidget(craeteConRListDlg);
	craeteConRListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteConRListWindow);
	if (craeteConRListDlg->FillDlgElements(tableView))
	{
		craeteConRListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelConRListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ConsumeRawList consumeRawList;
	consumeRawList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteConsumeRawList(&consumeRawList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtCurDlg()
{
	CreateCurDlg *currencyDlg = new CreateCurDlg(dataFormBL, false, this);
	currencyDlg->setAttribute(Qt::WA_DeleteOnClose);
	currencyDlg->setWindowTitle(tr("Create currency"));
	QMdiSubWindow *currencyWindow = new QMdiSubWindow;
	currencyWindow->setWidget(currencyDlg);
	currencyWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(currencyWindow);
	currencyDlg->show();
}
void DataForm::UdpCurDlg()
{
	CreateCurDlg *currencyDlg = new CreateCurDlg(dataFormBL, true, this);
	currencyDlg->setAttribute(Qt::WA_DeleteOnClose);
	currencyDlg->setWindowTitle(tr("Update currency"));
	QMdiSubWindow *currencyWindow = new QMdiSubWindow;
	currencyWindow->setWidget(currencyDlg);
	currencyWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(currencyWindow);
	if (currencyDlg->FillDlgElements(tableView))
	{
		currencyDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelCurDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Currency currency;
	currency.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteCurrency(&currency,errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Currency with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtDivDlg()
{
	CreateDivDlg *divisionDlg = new CreateDivDlg(dataFormBL, false, this);
	divisionDlg->setAttribute(Qt::WA_DeleteOnClose);
	divisionDlg->setWindowTitle(tr("Create division"));
	QMdiSubWindow *divisionWindow = new QMdiSubWindow;
	divisionWindow->setWidget(divisionDlg);
	divisionWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(divisionWindow);
	divisionDlg->show();
}
void DataForm::UdpDivDlg()
{
	CreateDivDlg *divisionDlg = new CreateDivDlg(dataFormBL, true, this);
	divisionDlg->setAttribute(Qt::WA_DeleteOnClose);
	divisionDlg->setWindowTitle(tr("Update division"));
	QMdiSubWindow *divisionWindow = new QMdiSubWindow;
	divisionWindow->setWidget(divisionDlg);
	divisionWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(divisionWindow);
	if (divisionDlg->FillDlgElements(tableView))
	{
		divisionDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelDivDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Division division;
	division.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteDivision(&division, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Division with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtDivAccDlg()
{
	CreateDivAccDlg *divisionAccDlg = new CreateDivAccDlg(dataFormBL, false, this);
	divisionAccDlg->setAttribute(Qt::WA_DeleteOnClose);
	divisionAccDlg->setWindowTitle(tr("Create division account"));
	QMdiSubWindow *divisionAccWindow = new QMdiSubWindow;
	divisionAccWindow->setWidget(divisionAccDlg);
	divisionAccWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(divisionAccWindow);
	divisionAccDlg->show();
}
void DataForm::UdpDivAccDlg()
{
	CreateDivAccDlg *divisionAccDlg = new CreateDivAccDlg(dataFormBL, true, this);
	divisionAccDlg->setAttribute(Qt::WA_DeleteOnClose);
	divisionAccDlg->setWindowTitle(tr("Update division account"));
	QMdiSubWindow *divisionAccWindow = new QMdiSubWindow;
	divisionAccWindow->setWidget(divisionAccDlg);
	divisionAccWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(divisionAccWindow);
	if (divisionAccDlg->FillDlgElements(tableView))
	{
		divisionAccDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelDivAccDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::DivisionAccountRelation divisionAcc;
	divisionAcc.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteDivisionAccountRelation(&divisionAcc, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Division account with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtEmpDlg()
{
	CreateEmpDlg *employeeDlg = new CreateEmpDlg(dataFormBL, false, this);
	employeeDlg->setAttribute(Qt::WA_DeleteOnClose);
	employeeDlg->setWindowTitle(tr("Create employee"));
	QMdiSubWindow *employeeWindow = new QMdiSubWindow;
	employeeWindow->setWidget(employeeDlg);
	employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(employeeWindow);
	employeeDlg->show();
}
void DataForm::UdpEmpDlg()
{
	CreateEmpDlg *employeeDlg = new CreateEmpDlg(dataFormBL, true, this);
	employeeDlg->setAttribute(Qt::WA_DeleteOnClose);
	employeeDlg->setWindowTitle(tr("Update employee"));
	QMdiSubWindow *employeeWindow = new QMdiSubWindow;
	employeeWindow->setWidget(employeeDlg);
	employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(employeeWindow);
	if (employeeDlg->FillDlgElements(tableView))
	{
		employeeDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelEmpDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Employee employee;
	employee.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteEmployee(&employee, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Employee with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtEmpPrdDlg()
{
	CreateEmpPrdDlg *epRelDlg = new CreateEmpPrdDlg(dataFormBL, false, this);
	epRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	epRelDlg->setWindowTitle(tr("Create employee-product relation"));
	QMdiSubWindow *epRelWindow = new QMdiSubWindow;
	epRelWindow->setWidget(epRelDlg);
	epRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(epRelWindow);
	epRelWindow->show();
}
void DataForm::UdpEmpPrdDlg()
{
	CreateEmpPrdDlg *epRelDlg = new CreateEmpPrdDlg(dataFormBL, true, this);
	epRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	epRelDlg->setWindowTitle(tr("Update employee-product relation"));
	QMdiSubWindow *epRelWindow = new QMdiSubWindow;
	epRelWindow->setWidget(epRelDlg);
	epRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(epRelWindow);
	if (epRelDlg->FillDlgElements(tableView))
	{
		epRelDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelEmpPrdDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::EmployeeProductRelation epRel;

	if (0 != id && epRel.GetEmployeeProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		if (dataFormBL->DeleteEmployeeProductRelation(&epRel, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Employee-product relation with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtEtrDlg()
{
	CreateEtrDlg *entryDlg = new CreateEtrDlg(dataFormBL, false, this);
	entryDlg->setAttribute(Qt::WA_DeleteOnClose);
	entryDlg->setWindowTitle(tr("Create entry"));
	QMdiSubWindow *entryWindow = new QMdiSubWindow;
	entryWindow->setWidget(entryDlg);
	entryWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(entryWindow);
	entryDlg->show();
}
void DataForm::UdpEtrDlg()
{
	CreateEtrDlg *entryDlg = new CreateEtrDlg(dataFormBL, true, this);
	entryDlg->setAttribute(Qt::WA_DeleteOnClose);
	entryDlg->setWindowTitle(tr("Update entry"));
	QMdiSubWindow *entryWindow = new QMdiSubWindow;
	entryWindow->setWidget(entryDlg);
	entryWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(entryWindow);
	if (entryDlg->FillDlgElements(tableView))
	{
		entryDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelEtrDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Entry entry;
	entry.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteEntry(&entry, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Entry with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtEtrRtDlg()
{
	CreateEtrRtDlg *entryRtDlg = new CreateEtrRtDlg(dataFormBL, false, this);
	entryRtDlg->setAttribute(Qt::WA_DeleteOnClose);
	entryRtDlg->setWindowTitle(tr("Create entry routing"));
	QMdiSubWindow *entryRtWindow = new QMdiSubWindow;
	entryRtWindow->setWidget(entryRtDlg);
	entryRtWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(entryRtWindow);
	entryRtDlg->show();
}
void DataForm::UdpEtrRtDlg()
{
	CreateEtrRtDlg *entryRtDlg = new CreateEtrRtDlg(dataFormBL, true, this);
	entryRtDlg->setAttribute(Qt::WA_DeleteOnClose);
	entryRtDlg->setWindowTitle(tr("Update entry routing"));
	QMdiSubWindow *entryRtWindow = new QMdiSubWindow;
	entryRtWindow->setWidget(entryRtDlg);
	entryRtWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(entryRtWindow);
	if (entryRtDlg->FillDlgElements(tableView))
	{
		entryRtDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelEtrRtDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::EntryRouting entryRouting;
	entryRouting.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteEntryRouting(&entryRouting, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Entry routing with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtFxdAstDlg()
{
	CreateFxdAstDlg *fxdAstDlg = new CreateFxdAstDlg(dataFormBL, false, this);
	fxdAstDlg->setAttribute(Qt::WA_DeleteOnClose);
	fxdAstDlg->setWindowTitle(tr("Create fixed assets"));
	QMdiSubWindow *fxdAstWindow = new QMdiSubWindow;
	fxdAstWindow->setWidget(fxdAstDlg);
	fxdAstWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(fxdAstWindow);
	fxdAstDlg->show();
}
void DataForm::UdpFxdAstDlg()
{
	CreateFxdAstDlg *fxdAstDlg = new CreateFxdAstDlg(dataFormBL, true, this);
	fxdAstDlg->setAttribute(Qt::WA_DeleteOnClose);
	fxdAstDlg->setWindowTitle(tr("Update fixed assets"));
	QMdiSubWindow *fxdAstWindow = new QMdiSubWindow;
	fxdAstWindow->setWidget(fxdAstDlg);
	fxdAstWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(fxdAstWindow);
	if (fxdAstDlg->FillDlgElements(tableView))
	{
		fxdAstDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelFxdAstDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::FixedAssets fxdAst;
	fxdAst.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteFixedAssets(&fxdAst, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Fixed assets with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewFxdAstDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::FixedAssets fixAst;
	if (!fixAst.GetFixedAssetsByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::FixedAssetsDetails faDetails;
	BusinessLayer::FixedAssetsSpecification faSpec;
	BusinessLayer::FixedAssetsOperations faOper;
	std::vector<BusinessLayer::FixedAssetsOperations> faOperVec;
	BusinessLayer::Subaccount primeSub;
	BusinessLayer::Subaccount amSub;
	BusinessLayer::Division division;
	BusinessLayer::AmortizeGroup amGroup;
	BusinessLayer::Account account;
	
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), dataFormBL->loggedUser->GetID(), errorMessage);
	company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage);

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/fixed_asset.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	
	if (!faDetails.GetFixedAssetsDetailsByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), fixAst.GetFixedAssetsDetailsID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	if (!faSpec.GetFixedAssetsSpecificationByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), fixAst.GetSpecificationID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	if (!primeSub.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), faDetails.GetPrimaryCostAccountID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	if (!amSub.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), faDetails.GetAmortizeAccountID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	if (!division.GetDivisionByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), faDetails.GetDepartmentID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	if (!amGroup.GetAmortizeGroupByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), faDetails.GetAmortizeGroupID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	
	if (!account.GetAccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), primeSub.GetParentAccountID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	faOper.SetFixedAssetsID(fixAst.GetID());
	std::string filter = faOper.GenerateFilter(dataFormBL->GetOrmasDal());
	faOperVec = dataFormBL->GetAllDataForClass<BusinessLayer::FixedAssetsOperations>(errorMessage, filter);
	

	//generating report
	if (!fixAst.IsEmpty())
	{
		reportText.replace(QString("DocumentNumberPh"), QString(QString::number(fixAst.GetID())), Qt::CaseInsensitive);
		if(!company.IsEmpty())
			reportText.replace(QString("ComNamePh"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("DivisionNamePh"), QString(division.GetName().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("DocumentDatePh"), QString(fixAst.GetBuyDate().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("FixedAssetNamePh"), QString(faSpec.GetName().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("GroupPh"), QString(QString::number(amGroup.GetGroupNumber())), Qt::CaseInsensitive);
		reportText.replace(QString("PassportPh"), QString(faSpec.GetDocument().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("FactoryPh"), QString(faSpec.GetFactoryNumber().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("InventoryPh"), QString(fixAst.GetInventoryNumber().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("DateOfInPh"), QString(fixAst.GetStartOfOperationDate().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("DateOfOutPh"), QString(fixAst.GetEndOfOperationDate().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("AccountPh"), QString(account.GetNumber().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("LocationPh"), QString(faDetails.GetFixedAssetsLocation().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("DeveloperPh"), QString(faSpec.GetDeveloper().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("OutPh"), QString(fixAst.GetBuyDate().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("ReconsPh"), QString("-"), Qt::CaseInsensitive);
		reportText.replace(QString("ReconsPh"), QString("-"), Qt::CaseInsensitive);
		reportText.replace(QString("NamePh"), QString("-"), Qt::CaseInsensitive);
		reportText.replace(QString("NumberPh"), QString("-"), Qt::CaseInsensitive);
		reportText.replace(QString("DatePh"), QString(fixAst.GetStartOfOperationDate().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("InUsePh"), QString::number(std::round((-1)*amSub.GetCurrentBalance() / (primeSub.GetCurrentBalance()*faDetails.GetAmortizeValue() / 12 / 100))), Qt::CaseInsensitive);
		reportText.replace(QString("AmorSumPh"), QString::number((-1)*amSub.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
		reportText.replace(QString("LastPh"), QString::number(primeSub.GetCurrentBalance() + amSub.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
		reportText.replace(QString("PricePh"), QString::number(primeSub.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
		reportText.replace(QString("UsePh"), QString::number(100 / faDetails.GetAmortizeValue() * 12, 'f', 3), Qt::CaseInsensitive);
		QString table1="";
		if (faOperVec.size() > 0)
		{
			
			for each (auto oper in faOperVec)
			{
				table1 += "<tr width = '100%'>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>< / td>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>2< / td>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>3< / td>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>1< / td>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>2< / td>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>3< / td>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>1< / td>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>2< / td>";
				table1 += "<td style = 'height:20px; border: 1px solid black; text - align: center; font - size:12px; '>3< / td>";
				table1 += "</tr>";
			}
		}

		reportText.replace(QString("Table1Ph"), table1, Qt::CaseInsensitive);
		reportText.replace(QString("Table2Ph"), "", Qt::CaseInsensitive);
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot find document!")),
			QString(tr("Ok")));
		return;
	}

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}



void DataForm::CrtFxdAstOperDlg()
{
	CreateFxdAstOperDlg *fxdAstOperDlg = new CreateFxdAstOperDlg(dataFormBL, false, this);
	fxdAstOperDlg->setAttribute(Qt::WA_DeleteOnClose);
	fxdAstOperDlg->setWindowTitle(tr("Create fixed assets operation"));
	QMdiSubWindow *fxdAstOperWindow = new QMdiSubWindow;
	fxdAstOperWindow->setWidget(fxdAstOperDlg);
	fxdAstOperWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(fxdAstOperWindow);
	fxdAstOperDlg->show();
}
void DataForm::UdpFxdAstOperDlg()
{
	CreateFxdAstOperDlg *fxdAstOperDlg = new CreateFxdAstOperDlg(dataFormBL, true, this);
	fxdAstOperDlg->setAttribute(Qt::WA_DeleteOnClose);
	fxdAstOperDlg->setWindowTitle(tr("Update fixed assets operation"));
	QMdiSubWindow *fxdAstOperWindow = new QMdiSubWindow;
	fxdAstOperWindow->setWidget(fxdAstOperDlg);
	fxdAstOperWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(fxdAstOperWindow);
	if (fxdAstOperDlg->FillDlgElements(tableView))
	{
		fxdAstOperDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelFxdAstOperDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::FixedAssetsOperations fxdAstOper;
	fxdAstOper.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteFixedAssetsOperation(&fxdAstOper, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Fixed assets operation with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtInveDlg()
{
	CreateInveDlg *inveDlg = new CreateInveDlg(dataFormBL, false, this);
	inveDlg->setAttribute(Qt::WA_DeleteOnClose);
	inveDlg->setWindowTitle(tr("Create inventory"));
	QMdiSubWindow *inveWindow = new QMdiSubWindow;
	inveWindow->setWidget(inveDlg);
	inveWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(inveWindow);
	inveDlg->show();
}
void DataForm::UdpInveDlg()
{
	CreateInveDlg *inveDlg = new CreateInveDlg(dataFormBL, true, this);
	inveDlg->setAttribute(Qt::WA_DeleteOnClose);
	inveDlg->setWindowTitle(tr("Update inventory"));
	QMdiSubWindow *inveWindow = new QMdiSubWindow;
	inveWindow->setWidget(inveDlg);
	inveWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(inveWindow);
	if (inveDlg->FillDlgElements(tableView))
	{
		inveDlg->show();
	}
	else
	{
	QMessageBox::information(NULL, QString(tr("Warning")),
	QString(tr("Please select one row at first!")),
	QString(tr("Ok")));
	}
}

void DataForm::DelInveDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Inventory inve;
	inve.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteInventory(&inve, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Inventory with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtInvDlg()
{
	CreateInvDlg *invDlg = new CreateInvDlg(dataFormBL, false, this);
	invDlg->setAttribute(Qt::WA_DeleteOnClose);
	invDlg->setWindowTitle(tr("Create inventorization"));
	QMdiSubWindow *invWindow = new QMdiSubWindow;
	invWindow->setWidget(invDlg);
	invWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(invWindow);
	invDlg->show();
}
void DataForm::UdpInvDlg()
{
	CreateInvDlg *invDlg = new CreateInvDlg(dataFormBL, true, this);
	invDlg->setAttribute(Qt::WA_DeleteOnClose);
	invDlg->setWindowTitle(tr("Update inventorization"));
	QMdiSubWindow *invWindow = new QMdiSubWindow;
	invWindow->setWidget(invDlg);
	invWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(invWindow);
	if (invDlg->FillDlgElements(tableView))
	{
		invDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelInvDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Inventorization inv;
	inv.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteInventorization(&inv, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Inventorization with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewInvDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Inventorization inventorization;
	if (!inventorization.GetInventorizationByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::InventorizationList inventorizationList;
	BusinessLayer::Employee employee;
	BusinessLayer::Employee stockEmployee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), inventorization.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), inventorization.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!stockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), inventorization.GetStockEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/inventarization.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	inventorizationList.SetInventorizationID(inventorization.GetID());
	std::string filter = inventorizationList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::InventorizationListView> vecConRawList = dataFormBL->GetAllDataForClass<BusinessLayer::InventorizationListView>(errorMessage, filter);
	if (vecConRawList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(inventorization.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(inventorization.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(stockEmployee.GetSurname().c_str()) + " " + QString(stockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	for each (auto item in vecConRawList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(inventorization.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtInvListDlg()
{
	CreateInvListDlg *craeteInvListDlg = new CreateInvListDlg(dataFormBL, false, this);
	if (0 != inventorizationID)
	{
		craeteInvListDlg->inventorizationID = inventorizationID;
	}
	craeteInvListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteInvListDlg->setWindowTitle(tr("Add product to inventorization list"));
	QMdiSubWindow *craeteInvListWindow = new QMdiSubWindow;
	craeteInvListWindow->setWidget(craeteInvListDlg);
	craeteInvListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteInvListWindow);
	craeteInvListDlg->show();
}
void DataForm::UdpInvListDlg()
{
	CreateInvListDlg *craeteInvListDlg = new CreateInvListDlg(dataFormBL, true, this);
	craeteInvListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteInvListDlg->setWindowTitle(tr("Update product in inventorization list"));
	QMdiSubWindow *craeteInvListWindow = new QMdiSubWindow;
	craeteInvListWindow->setWidget(craeteInvListDlg);
	craeteInvListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteInvListWindow);
	if (craeteInvListDlg->FillDlgElements(tableView))
	{
		craeteInvListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelInvListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::InventorizationList invList;
	invList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteInventorizationList(&invList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtGroupDlg()
{
	CreateGrpDlg *groupDlg = new CreateGrpDlg(dataFormBL, false, this);
	groupDlg->setAttribute(Qt::WA_DeleteOnClose);
	groupDlg->setWindowTitle(tr("Create group"));
	QMdiSubWindow *groupWindow = new QMdiSubWindow;
	groupWindow->setWidget(groupDlg);
	groupWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(groupWindow);
	groupDlg->show();
}
void DataForm::UdpGroupDlg()
{
	CreateGrpDlg *groupDlg = new CreateGrpDlg(dataFormBL, true, this);
	groupDlg->setAttribute(Qt::WA_DeleteOnClose);
	groupDlg->setWindowTitle(tr("Update group"));
	QMdiSubWindow *groupWindow = new QMdiSubWindow;
	groupWindow->setWidget(groupDlg);
	groupWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(groupWindow);
	if (groupDlg->FillDlgElements(tableView))
	{
		groupDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelGroupDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Group group;
	group.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteGroup(&group, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Group with this id does not exist!")),
			QString(tr("Ok")));

	}
}


void DataForm::CrtJbpDlg()
{
	CreateJbpDlg *jobpriceDlg = new CreateJbpDlg(dataFormBL, false, this);
	jobpriceDlg->setAttribute(Qt::WA_DeleteOnClose);
	jobpriceDlg->setWindowTitle(tr("Create jobprice"));
	QMdiSubWindow *jobpriceWindow = new QMdiSubWindow;
	jobpriceWindow->setWidget(jobpriceDlg);
	jobpriceWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(jobpriceWindow);
	jobpriceDlg->show();
}
void DataForm::UdpJbpDlg()
{
	CreateJbpDlg *jobpriceDlg = new CreateJbpDlg(dataFormBL, true, this);
	jobpriceDlg->setAttribute(Qt::WA_DeleteOnClose);
	jobpriceDlg->setWindowTitle(tr("Update jobprice"));
	QMdiSubWindow *jobpriceWindow = new QMdiSubWindow;
	jobpriceWindow->setWidget(jobpriceDlg);
	jobpriceWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(jobpriceWindow);
	if (jobpriceDlg->FillDlgElements(tableView))
	{
		jobpriceDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelJbpDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Jobprice jobprice;
	jobprice.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteJobprice(&jobprice, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Jobprice with this id does not exist!")),
			QString(tr("Ok")));

	}
}

void DataForm::CrtJbsDlg()
{
	CreateJbsDlg *jobsheetDlg = new CreateJbsDlg(dataFormBL, false, this);
	jobsheetDlg->setAttribute(Qt::WA_DeleteOnClose);
	jobsheetDlg->setWindowTitle(tr("Create jobsheet"));
	QMdiSubWindow *jobsheetWindow = new QMdiSubWindow;
	jobsheetWindow->setWidget(jobsheetDlg);
	jobsheetWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(jobsheetWindow);
	jobsheetDlg->show();
}
void DataForm::UdpJbsDlg()
{
	CreateJbsDlg *jobsheetDlg = new CreateJbsDlg(dataFormBL, true, this);
	jobsheetDlg->setAttribute(Qt::WA_DeleteOnClose);
	jobsheetDlg->setWindowTitle(tr("Update jobsheet"));
	QMdiSubWindow *jobsheetWindow = new QMdiSubWindow;
	jobsheetWindow->setWidget(jobsheetDlg);
	jobsheetWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(jobsheetWindow);
	if (jobsheetDlg->FillDlgElements(tableView))
	{
		jobsheetDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelJbsDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Jobsheet jobsheet;
	jobsheet.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteJobsheet(&jobsheet, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Jobsheet with this id does not exist!")),
			QString(tr("Ok")));

	}
}

void DataForm::CrtLowValStockDlg()
{
	CreateLowValStockDlg *lowValStockDlg = new CreateLowValStockDlg(dataFormBL, false, this);
	lowValStockDlg->setAttribute(Qt::WA_DeleteOnClose);
	lowValStockDlg->setWindowTitle(tr("Create low value stock"));
	QMdiSubWindow *lowValStockWindow = new QMdiSubWindow;
	lowValStockWindow->setWidget(lowValStockDlg);
	lowValStockWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(lowValStockWindow);
	lowValStockDlg->show();
}
void DataForm::UdpLowValStockDlg()
{
	CreateLowValStockDlg *lowValStockDlg = new CreateLowValStockDlg(dataFormBL, true, this);
	lowValStockDlg->setAttribute(Qt::WA_DeleteOnClose);
	lowValStockDlg->setWindowTitle(tr("Update low value stock"));
	QMdiSubWindow *lowValStockWindow = new QMdiSubWindow;
	lowValStockWindow->setWidget(lowValStockDlg);
	lowValStockWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(lowValStockWindow);
	if (lowValStockDlg->FillDlgElements(tableView))
	{
		lowValStockDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelLowValStockDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::LowValueStock lowValStock;
	lowValStock.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteLowValueStock(&lowValStock, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Low value stock with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtLcnDlg()
{
	CreateLcnDlg *locationDlg = new CreateLcnDlg(dataFormBL, false, this);
	locationDlg->setAttribute(Qt::WA_DeleteOnClose);
	locationDlg->setWindowTitle(tr("Create location"));
	QMdiSubWindow *locationWindow = new QMdiSubWindow;
	locationWindow->setWidget(locationDlg);
	locationWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(locationWindow);
	locationDlg->show();
}
void DataForm::UdpLcnDlg()
{
	CreateLcnDlg *locationDlg = new CreateLcnDlg(dataFormBL, true, this);
	locationDlg->setAttribute(Qt::WA_DeleteOnClose);
	locationDlg->setWindowTitle(tr("Update location"));
	QMdiSubWindow *locationWindow = new QMdiSubWindow;
	locationWindow->setWidget(locationDlg);
	locationWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(locationWindow);
	if (locationDlg->FillDlgElements(tableView))
	{
		locationDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelLcnDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Location location;
	location.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteLocation(&location, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Location with this id does not exist!")),
			QString(tr("Ok")));

	}
}


void DataForm::CrtMsrDlg()
{
	CreateMsrDlg *measureDlg = new CreateMsrDlg(dataFormBL, false, this);
	measureDlg->setAttribute(Qt::WA_DeleteOnClose);
	measureDlg->setWindowTitle(tr("Create measure"));
	QMdiSubWindow *measureWindow = new QMdiSubWindow;
	measureWindow->setWidget(measureDlg);
	measureWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(measureWindow);
	measureDlg->show();
}
void DataForm::UdpMsrDlg()
{
	CreateMsrDlg *measureDlg = new CreateMsrDlg(dataFormBL, true, this);
	measureDlg->setAttribute(Qt::WA_DeleteOnClose);
	measureDlg->setWindowTitle(tr("Update currency"));
	QMdiSubWindow *measureWindow = new QMdiSubWindow;
	measureWindow->setWidget(measureDlg);
	measureWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(measureWindow);
	if (measureDlg->FillDlgElements(tableView))
	{
		measureDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelMsrDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Measure measure;
	measure.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteMeasure(&measure,errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Measure with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtNetCDlg()
{
	CreateNetCDlg *netCostDlg = new CreateNetCDlg(dataFormBL, false, this);
	netCostDlg->setAttribute(Qt::WA_DeleteOnClose);
	netCostDlg->setWindowTitle(tr("Create net cost"));
	QMdiSubWindow *netCostWindow = new QMdiSubWindow;
	netCostWindow->setWidget(netCostDlg);
	netCostWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(netCostWindow);
	netCostDlg->show();
}
void DataForm::UdpNetCDlg()
{
	CreateNetCDlg *netCostDlg = new CreateNetCDlg(dataFormBL, true, this);
	netCostDlg->setAttribute(Qt::WA_DeleteOnClose);
	netCostDlg->setWindowTitle(tr("Update net cost"));
	QMdiSubWindow *netCostWindow = new QMdiSubWindow;
	netCostWindow->setWidget(netCostDlg);
	netCostWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(netCostWindow);
	if (netCostDlg->FillDlgElements(tableView))
	{
		netCostDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelNetCDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::NetCost netCost;
	netCost.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteNetCost(&netCost, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Net cost with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtOrdDlg()
{
	CreateOrdDlg *orderDlg = new CreateOrdDlg(dataFormBL, false, this);
	orderDlg->setAttribute(Qt::WA_DeleteOnClose);
	orderDlg->setWindowTitle(tr("Create order"));
	QMdiSubWindow *orderWindow = new QMdiSubWindow;
	orderWindow->setWidget(orderDlg);
	orderWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(orderWindow);
	orderDlg->show();
}
void DataForm::UdpOrdDlg()
{
	CreateOrdDlg *orderDlg = new CreateOrdDlg(dataFormBL, true, this);
	orderDlg->setAttribute(Qt::WA_DeleteOnClose);
	orderDlg->setWindowTitle(tr("Update order"));
	QMdiSubWindow *orderWindow = new QMdiSubWindow;
	orderWindow->setWidget(orderDlg);
	orderWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(orderWindow);
	if (orderDlg->FillDlgElements(tableView))
	{
		orderDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelOrdDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Order order;
	order.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteOrder(&order, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Order with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewOrdDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Order order;
	if (!order.GetOrderByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::OrderList orderList;
	BusinessLayer::Client client;
	BusinessLayer::Employee employee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), order.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!client.GetClientByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), order.GetClientID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), order.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/order.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	orderList.SetOrderID(order.GetID());
	std::string filter = orderList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::OrderListView> vecOrdList = dataFormBL->GetAllDataForClass<BusinessLayer::OrderListView>(errorMessage, filter);
	if (vecOrdList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(order.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(order.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(client.GetFirm().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(client.GetSurname().c_str()) + " " + QString(client.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	BusinessLayer::NetCost netCost;
	QString tableBody;
	for each (auto item in vecOrdList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(order.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtOrdListDlg()
{
	CreateOrdListDlg *craeteOrdListDlg = new CreateOrdListDlg(dataFormBL, false, this);
	if (0 != orderID)
	{
		craeteOrdListDlg->orderID = orderID;
	}
	craeteOrdListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteOrdListDlg->setWindowTitle(tr("Add product to order list"));
	QMdiSubWindow *craeteOrdListWindow = new QMdiSubWindow;
	craeteOrdListWindow->setWidget(craeteOrdListDlg);
	craeteOrdListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteOrdListWindow);
	craeteOrdListDlg->show();
}
void DataForm::UdpOrdListDlg()
{
	CreateOrdListDlg *craeteOrdListDlg = new CreateOrdListDlg(dataFormBL, true, this);
	craeteOrdListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteOrdListDlg->setWindowTitle(tr("Update product in order list"));
	QMdiSubWindow *craeteOrdListWindow = new QMdiSubWindow;
	craeteOrdListWindow->setWidget(craeteOrdListDlg);
	craeteOrdListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteOrdListWindow);
	if (craeteOrdListDlg->FillDlgElements(tableView))
	{
		craeteOrdListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelOrdListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::OrderList orderList;
	orderList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteOrderList(&orderList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product with this id does not exist in order list!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtOrdRDlg()
{
	CreateOrdRDlg *orderRDlg = new CreateOrdRDlg(dataFormBL, false, this);
	orderRDlg->setAttribute(Qt::WA_DeleteOnClose);
	orderRDlg->setWindowTitle(tr("Create order raw"));
	QMdiSubWindow *orderRWindow = new QMdiSubWindow;
	orderRWindow->setWidget(orderRDlg);
	orderRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(orderRWindow);
	orderRDlg->show();
}
void DataForm::UdpOrdRDlg()
{
	CreateOrdRDlg *orderRDlg = new CreateOrdRDlg(dataFormBL, true, this);
	orderRDlg->setAttribute(Qt::WA_DeleteOnClose);
	orderRDlg->setWindowTitle(tr("Update order raw"));
	QMdiSubWindow *orderRWindow = new QMdiSubWindow;
	orderRWindow->setWidget(orderRDlg);
	orderRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(orderRWindow);
	if (orderRDlg->FillDlgElements(tableView))
	{
		orderRDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelOrdRDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::OrderRaw orderRaw;
	orderRaw.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteOrderRaw(&orderRaw, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Order raw with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewOrdRDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::OrderRaw orderRaw;
	if (!orderRaw.GetOrderRawByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::OrderRawList orderRawList;
	BusinessLayer::Purveyor purveyor;
	BusinessLayer::Employee employee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), orderRaw.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!purveyor.GetPurveyorByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), orderRaw.GetPurveyorID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), orderRaw.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/order.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	orderRawList.SetOrderRawID(orderRaw.GetID());
	std::string filter = orderRawList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::OrderRawListView> vecOrdRawList = dataFormBL->GetAllDataForClass<BusinessLayer::OrderRawListView>(errorMessage, filter);
	if (vecOrdRawList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(orderRaw.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(orderRaw.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(purveyor.GetCompanyName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(purveyor.GetSurname().c_str()) + " " + QString(purveyor.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	for each (auto item in vecOrdRawList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(orderRaw.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtOrdRListDlg()
{
	CreateOrdRListDlg *craeteOrdRListDlg = new CreateOrdRListDlg(dataFormBL, false, this);
	if (0 != orderRawID)
	{
		craeteOrdRListDlg->orderRawID = orderRawID;
	}
	craeteOrdRListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteOrdRListDlg->setWindowTitle(tr("Add raw to order list"));
	QMdiSubWindow *craeteOrdRListWindow = new QMdiSubWindow;
	craeteOrdRListWindow->setWidget(craeteOrdRListDlg);
	craeteOrdRListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteOrdRListWindow);
	craeteOrdRListDlg->show();
}
void DataForm::UdpOrdRListDlg()
{
	CreateOrdRListDlg *craeteOrdRListDlg = new CreateOrdRListDlg(dataFormBL, true, this);
	craeteOrdRListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteOrdRListDlg->setWindowTitle(tr("Update raw in order list"));
	QMdiSubWindow *craeteOrdRListWindow = new QMdiSubWindow;
	craeteOrdRListWindow->setWidget(craeteOrdRListDlg);
	craeteOrdRListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteOrdRListWindow);
	if (craeteOrdRListDlg->FillDlgElements(tableView))
	{
		craeteOrdRListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelOrdRListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::OrderRawList orderRawList;
	orderRawList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteOrderRawList(&orderRawList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Raw with this id does not exist in order list!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtPcrDlg()
{
	CreatePcrDlg *percentRateDlg = new CreatePcrDlg(dataFormBL, false, this);
	percentRateDlg->setAttribute(Qt::WA_DeleteOnClose);
	percentRateDlg->setWindowTitle(tr("Create percent rate"));
	QMdiSubWindow *percentRateWindow = new QMdiSubWindow;
	percentRateWindow->setWidget(percentRateDlg);
	percentRateWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(percentRateWindow);
	percentRateDlg->show();
}
void DataForm::UdpPcrDlg()
{
	CreatePcrDlg *percentRateDlg = new CreatePcrDlg(dataFormBL, true, this);
	percentRateDlg->setAttribute(Qt::WA_DeleteOnClose);
	percentRateDlg->setWindowTitle(tr("Update percent rate"));
	QMdiSubWindow *percentRateWindow = new QMdiSubWindow;
	percentRateWindow->setWidget(percentRateDlg);
	percentRateWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(percentRateWindow);
	if (percentRateDlg->FillDlgElements(tableView))
	{
		percentRateDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}

void DataForm::DelPcrDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::PercentRate percentRate;
	percentRate.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeletePercentRate(&percentRate, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Percent rate with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtOthStDlg()
{
	CreateOthStDlg *othStDlg = new CreateOthStDlg(dataFormBL, false, this);
	othStDlg->setAttribute(Qt::WA_DeleteOnClose);
	othStDlg->setWindowTitle(tr("Create other stocks"));
	QMdiSubWindow *othStWindow = new QMdiSubWindow;
	othStWindow->setWidget(othStDlg);
	othStWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(othStWindow);
	othStDlg->show();
}
void DataForm::UdpOthStDlg()
{
	CreateOthStDlg *othStDlg = new CreateOthStDlg(dataFormBL, true, this);
	othStDlg->setAttribute(Qt::WA_DeleteOnClose);
	othStDlg->setWindowTitle(tr("Update other stocks"));
	QMdiSubWindow *othStWindow = new QMdiSubWindow;
	othStWindow->setWidget(othStDlg);
	othStWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(othStWindow);
	if (othStDlg->FillDlgElements(tableView))
	{
		othStDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelOthStDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::OtherStocks otherStocks;
	otherStocks.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteOtherStocks(&otherStocks, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Other stocks with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtOthStTypeDlg()
{
	CreateOthSTypeDlg *othSTypeDlg = new CreateOthSTypeDlg(dataFormBL, false, this);
	othSTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	othSTypeDlg->setWindowTitle(tr("Create other stocks type"));
	QMdiSubWindow *othSTypeWindow = new QMdiSubWindow;
	othSTypeWindow->setWidget(othSTypeDlg);
	othSTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(othSTypeWindow);
	othSTypeDlg->show();
}
void DataForm::UdpOthStTypeDlg()
{
	CreateOthSTypeDlg *othSTypeDlg = new CreateOthSTypeDlg(dataFormBL, true, this);
	othSTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	othSTypeDlg->setWindowTitle(tr("Update other stocks type"));
	QMdiSubWindow *othSTypeWindow = new QMdiSubWindow;
	othSTypeWindow->setWidget(othSTypeDlg);
	othSTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(othSTypeWindow);
	if (othSTypeDlg->FillDlgElements(tableView))
	{
		othSTypeDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelOthStTypeDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::OtherStocksType otherStocksType;
	otherStocksType.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteOtherStocksType(&otherStocksType, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Other stocks with this id does not exist!")),
			QString(tr("Ok")));
	}
}




void DataForm::CrtPhotoDlg()
{
	CreatePhtDlg *photoDlg = new CreatePhtDlg(dataFormBL, false, this);
	photoDlg->setAttribute(Qt::WA_DeleteOnClose);
	photoDlg->setWindowTitle(tr("Create photo"));
	QMdiSubWindow *photoWindow = new QMdiSubWindow;
	photoWindow->setWidget(photoDlg);
	photoWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(photoWindow);
	photoDlg->show();
}
void DataForm::UdpPhotoDlg()
{
	CreatePhtDlg *photoDlg = new CreatePhtDlg(dataFormBL, true, this);
	photoDlg->setAttribute(Qt::WA_DeleteOnClose);
	photoDlg->setWindowTitle(tr("Update photo"));
	QMdiSubWindow *photoWindow = new QMdiSubWindow;
	photoWindow->setWidget(photoDlg);
	photoWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(photoWindow);
	if (photoDlg->FillDlgElements(tableView))
	{
		photoDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPhotoDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Photo photo;
	photo.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeletePhoto(&photo, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Photo with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtPmtDlg()
{
	CreatePmtDlg *paymentDlg = new CreatePmtDlg(dataFormBL, false, this);
	paymentDlg->setAttribute(Qt::WA_DeleteOnClose);
	paymentDlg->setWindowTitle(tr("Create payment"));
	QMdiSubWindow *paymentWindow = new QMdiSubWindow;
	paymentWindow->setWidget(paymentDlg);
	paymentWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(paymentWindow);
	paymentDlg->show();
}
void DataForm::UdpPmtDlg()
{
	CreatePmtDlg *paymentDlg = new CreatePmtDlg(dataFormBL, true, this);
	paymentDlg->setAttribute(Qt::WA_DeleteOnClose);
	paymentDlg->setWindowTitle(tr("Update payment"));
	QMdiSubWindow *paymentWindow = new QMdiSubWindow;
	paymentWindow->setWidget(paymentDlg);
	paymentWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(paymentWindow);
	if (paymentDlg->FillDlgElements(tableView))
	{
		paymentDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPmtDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Payment payment;
	payment.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeletePayment(&payment, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Payment with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewPmtDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Payment payment;
	if (!payment.GetPaymentByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::User user;
	BusinessLayer::Employee cashier;
	BusinessLayer::Employee accountant;
	BusinessLayer::Role role;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	BusinessLayer::CashboxTransaction cTransaction;

	if (cTransaction.GetCashboxTransactionByPaymentID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), payment.GetID(), errorMessage))
	{
		if (!accountant.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), cTransaction.GetAccountantID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CHIEF ACCOUNTANT' employee!")),
				QString(tr("Ok")));
			return;
		}
		if (!cashier.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), cTransaction.GetCashierID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CASHIER' employee!")),
				QString(tr("Ok")));
			return;
		}
	}
	else
	{

		if (0 == role.GetRoleIDByName(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), "CHIEF ACCOUNTANT", errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CHIEF ACCOUNTANT' role!")),
				QString(tr("Ok")));
			return;
		}

		accountant.SetRoleID(role.GetID());
		std::string empFilter = accountant.GenerateFilter(dataFormBL->GetOrmasDal());
		std::vector<BusinessLayer::EmployeeView> vecEmpRep = dataFormBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, empFilter);
		if (vecEmpRep.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CHIEF ACCOUNTANT' employee!")),
				QString(tr("Ok")));
			return;
		}
		else
		{
			accountant.SetName(vecEmpRep.at(0).GetName());
			accountant.SetSurname(vecEmpRep.at(0).GetSurname());
		}

		role.Clear();
		if (0 == role.GetRoleIDByName(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), "CASHIER", errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CASHIER' role!")),
				QString(tr("Ok")));
			return;
		}

		cashier.SetRoleID(role.GetID());
		std::string casFilter = cashier.GenerateFilter(dataFormBL->GetOrmasDal());
		std::vector<BusinessLayer::EmployeeView> vecCasRep = dataFormBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, casFilter);
		if (vecCasRep.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CASHIER' employee!")),
				QString(tr("Ok")));
			return;
		}
		else
		{
			cashier.SetName(vecCasRep.at(0).GetName());
			cashier.SetSurname(vecCasRep.at(0).GetSurname());
		}
	}
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), accountant.GetID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Income chash order"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/income.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();

	BusinessLayer::Account acc;
	if (!acc.GetAccountByNumber(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), "10110", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Can't find account!")),
			QString(tr("Ok")));
		return;
	}


	BusinessLayer::Balance balance;
	BusinessLayer::Subaccount subAcc;
	BusinessLayer::Currency currency;
	BusinessLayer::Account account;
	if (payment.GetUserID() > 0)
	{
		balance.SetUserID(payment.GetUserID());
		std::string filter = balance.GenerateFilter(dataFormBL->GetOrmasDal());
		std::vector<BusinessLayer::BalanceView> balanceVector = dataFormBL->GetAllDataForClass<BusinessLayer::BalanceView>(errorMessage, filter);
		if (0 < balanceVector.size())
		{
			for each (auto item in balanceVector)
			{
				subAcc.Clear();
				if (subAcc.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetSubaccountID(), errorMessage))
				{
					if (subAcc.GetParentAccountID() == payment.GetAccountID())
					{
						balance.SetSubaccountID(subAcc.GetID());
					}
				}
			}
		}
		else
		{
			subAcc.Clear();
		}
		if (balance.GetSubaccountID() <= 0)
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Can't find subaccount for this payment!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), payment.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Can't find currency for this payment!")),
				QString(tr("Ok")));
			return;
		}
		subAcc.Clear();
		if (!subAcc.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), balance.GetSubaccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Can't find subaccount for this user!")),
				QString(tr("Ok")));
			return;
		}
	}
	else if (payment.GetAccountID()>0)
	{
		account.Clear();
		if (!account.GetAccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), payment.GetAccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			return;
		}
	}
	else
	{
		subAcc.Clear();
		if (!subAcc.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), payment.GetSubaccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			return;
		}
		if (!account.GetAccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), subAcc.GetParentAccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			return;
		}
	}
	
	//generating report
	reportText.replace(QString("ComNamePh"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("NumberPh"), QString::number(payment.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(payment.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("DebAccNumPh"), QString(acc.GetNumber().c_str()), Qt::CaseInsensitive);
	if (payment.GetUserID() > 0 )
	{
		reportText.replace(QString("CredAccNumPh"), QString(subAcc.GetNumber().c_str()), Qt::CaseInsensitive);
	}
	else
	{
		reportText.replace(QString("CredAccNumPh"), QString(account.GetNumber().c_str()), Qt::CaseInsensitive);
	}
	reportText.replace(QString("SumPh"), QString::number(payment.GetValue()), Qt::CaseInsensitive);
	reportText.replace(QString("FromWhoPh"), QString(payment.GetWho().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("TargetPh"), QString(payment.GetTarget().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("AccounantNamePh"), QString(accountant.GetSurname().c_str()) + " " + QString(accountant.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("CachierNamePh"), QString(cashier.GetSurname().c_str()) + " " + QString(cashier.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtPosDlg()
{
	CreatePosDlg *positionDlg = new CreatePosDlg(dataFormBL, false, this);
	positionDlg->setAttribute(Qt::WA_DeleteOnClose);
	positionDlg->setWindowTitle(tr("Create position"));
	QMdiSubWindow *positionWindow = new QMdiSubWindow;
	positionWindow->setWidget(positionDlg);
	positionWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(positionWindow);
	positionDlg->show();
}
void DataForm::UdpPosDlg()
{
	CreatePosDlg *positionDlg = new CreatePosDlg(dataFormBL, true, this);
	positionDlg->setAttribute(Qt::WA_DeleteOnClose);
	positionDlg->setWindowTitle(tr("Update position"));
	QMdiSubWindow *positionWindow = new QMdiSubWindow;
	positionWindow->setWidget(positionDlg);
	positionWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(positionWindow);
	if (positionDlg->FillDlgElements(tableView))
	{
		positionDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPosDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Position position;
	position.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeletePosition(&position, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Position with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtPrcDlg()
{
	CreatePrcDlg *priceDlg = new CreatePrcDlg(dataFormBL, false, this);
	priceDlg->setAttribute(Qt::WA_DeleteOnClose);
	priceDlg->setWindowTitle(tr("Create price"));
	QMdiSubWindow *priceWindow = new QMdiSubWindow;
	priceWindow->setWidget(priceDlg);
	priceWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(priceWindow);
	priceDlg->show();
}
void DataForm::UdpPrcDlg()
{
	CreatePrcDlg *priceDlg = new CreatePrcDlg(dataFormBL, true, this);
	priceDlg->setAttribute(Qt::WA_DeleteOnClose);
	priceDlg->setWindowTitle(tr("Update price"));
	QMdiSubWindow *priceWindow = new QMdiSubWindow;
	priceWindow->setWidget(priceDlg);
	priceWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(priceWindow);
	if (priceDlg->FillDlgElements(tableView))
	{
		priceDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPrcDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Price price;
	price.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeletePrice(&price, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Price with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtProdTpDlg()
{
	CreatePrdTpDlg *prodTypeDlg = new CreatePrdTpDlg(dataFormBL, false, this);
	prodTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	prodTypeDlg->setWindowTitle(tr("Create product type"));
	QMdiSubWindow *prodTypeWindow = new QMdiSubWindow;
	prodTypeWindow->setWidget(prodTypeDlg);
	prodTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(prodTypeWindow);
	prodTypeDlg->show();
}
void DataForm::UdpProdTpDlg()
{
	CreatePrdTpDlg *prodTypeDlg = new CreatePrdTpDlg(dataFormBL, true, this);
	prodTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	prodTypeDlg->setWindowTitle(tr("Update product type"));
	QMdiSubWindow *prodTypeWindow = new QMdiSubWindow;
	prodTypeWindow->setWidget(prodTypeDlg);
	prodTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(prodTypeWindow);
	if (prodTypeDlg->FillDlgElements(tableView))
	{
		prodTypeDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelProdTpDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ProductType prodTp;
	prodTp.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteProductType(&prodTp,errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product type with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtPrdBrnDlg()
{
	CreatePrdBrnDlg *pbRelDlg = new CreatePrdBrnDlg(dataFormBL, false, this);
	pbRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	pbRelDlg->setWindowTitle(tr("Create product-branch relation"));
	QMdiSubWindow *pbRelWindow = new QMdiSubWindow;
	pbRelWindow->setWidget(pbRelDlg);
	pbRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(pbRelWindow);
	pbRelWindow->show();
}
void DataForm::UdpPrdBrnDlg()
{
	CreatePrdBrnDlg *pbRelDlg = new CreatePrdBrnDlg(dataFormBL, true, this);
	pbRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	pbRelDlg->setWindowTitle(tr("Update product-branch relation"));
	QMdiSubWindow *pbRelWindow = new QMdiSubWindow;
	pbRelWindow->setWidget(pbRelDlg);
	pbRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(pbRelWindow);
	if (pbRelDlg->FillDlgElements(tableView))
	{
		pbRelDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPrdBrnDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ProductBranchRelation pbRel;

	if (0 != id && pbRel.GetProductBranchByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		if (dataFormBL->DeleteProductBranchRelation(&pbRel, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product-branch relation with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtProdDlg()
{
	CreateProdDlg *prodDlg = new CreateProdDlg(dataFormBL, false, this);
	prodDlg->setAttribute(Qt::WA_DeleteOnClose);
	prodDlg->setWindowTitle(tr("Create product"));
	QMdiSubWindow *prodWindow = new QMdiSubWindow;
	prodWindow->setWidget(prodDlg);
	prodWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(prodWindow);
	prodDlg->show();
}
void DataForm::UdpProdDlg()
{
	CreateProdDlg *prodDlg = new CreateProdDlg(dataFormBL, true, this);
	prodDlg->setAttribute(Qt::WA_DeleteOnClose);
	prodDlg->setWindowTitle(tr("Update product"));
	QMdiSubWindow *prodWindow = new QMdiSubWindow;
	prodWindow->setWidget(prodDlg);
	prodWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(prodWindow);
	if (prodDlg->FillDlgElements(tableView))
	{
		prodDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelProdDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Product prod;
	prod.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteProduct(&prod, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtProdnDlg()
{
	CreateProdnDlg *prodnDlg = new CreateProdnDlg(dataFormBL, false, this);
	prodnDlg->setAttribute(Qt::WA_DeleteOnClose);
	prodnDlg->setWindowTitle(tr("Create production"));
	QMdiSubWindow *prodnWindow = new QMdiSubWindow;
	prodnWindow->setWidget(prodnDlg);
	prodnWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(prodnWindow);
	prodnDlg->show();
}
void DataForm::UdpProdnDlg()
{
	CreateProdnDlg *prodnDlg = new CreateProdnDlg(dataFormBL, true, this);
	prodnDlg->setAttribute(Qt::WA_DeleteOnClose);
	prodnDlg->setWindowTitle(tr("Update production"));
	QMdiSubWindow *prodnWindow = new QMdiSubWindow;
	prodnWindow->setWidget(prodnDlg);
	prodnWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(prodnWindow);
	if (prodnDlg->FillDlgElements(tableView))
	{
		prodnDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelProdnDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Production prodn;
	prodn.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteProduction(&prodn, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Production with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewProdnDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Production production;
	if (!production.GetProductionByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ProductionList productionList;
	
	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/production.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	productionList.SetProductionID(production.GetID());
	std::string filter = productionList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ProductionListView> vecProdnList = dataFormBL->GetAllDataForClass<BusinessLayer::ProductionListView>(errorMessage, filter);
	if (vecProdnList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(production.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(production.GetProductionDate().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	BusinessLayer::NetCost netCost;
	QString tableBody;
	double sum = 0;
	for each (auto item in vecProdnList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		netCost.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!netCost.GetNetCostByProductID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(product.GetPrice()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount() * product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		sum += item.GetCount() * product.GetPrice();
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(sum, 'f', 3), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtProdnListDlg()
{
	CreateProdnListDlg *craeteProdnListDlg = new CreateProdnListDlg(dataFormBL, false, this);
	if (0 != productionID)
	{
		craeteProdnListDlg->productionID = productionID;
	}
	craeteProdnListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteProdnListDlg->setWindowTitle(tr("Add product to production list"));
	QMdiSubWindow *craeteProdnListWindow = new QMdiSubWindow;
	craeteProdnListWindow->setWidget(craeteProdnListDlg);
	craeteProdnListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteProdnListWindow);
	craeteProdnListDlg->show();
}
void DataForm::UdpProdnListDlg()
{
	CreateProdnListDlg *craeteProdnListDlg = new CreateProdnListDlg(dataFormBL, true, this);
	craeteProdnListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteProdnListDlg->setWindowTitle(tr("Update product in production list"));
	QMdiSubWindow *craeteProdnListWindow = new QMdiSubWindow;
	craeteProdnListWindow->setWidget(craeteProdnListDlg);
	craeteProdnListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteProdnListWindow);
	if (craeteProdnListDlg->FillDlgElements(tableView))
	{
		craeteProdnListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelProdnListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ProductionList productionList;
	productionList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteProductionList(&productionList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product with this id does not exist in production list!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtProdConRDlg()
{
	CreateProdConRDlg *pConRDlg = new CreateProdConRDlg(dataFormBL, false, this);
	pConRDlg->setAttribute(Qt::WA_DeleteOnClose);
	pConRDlg->setWindowTitle(tr("Create production consume raw"));
	QMdiSubWindow *pconRWindow = new QMdiSubWindow;
	pconRWindow->setWidget(pConRDlg);
	pconRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(pconRWindow);
	pConRDlg->show();
}
void DataForm::UdpProdConRDlg()
{
	CreateProdConRDlg *pConRDlg = new CreateProdConRDlg(dataFormBL, true, this);
	pConRDlg->setAttribute(Qt::WA_DeleteOnClose);
	pConRDlg->setWindowTitle(tr("Update production consume raw"));
	QMdiSubWindow *pConRWindow = new QMdiSubWindow;
	pConRWindow->setWidget(pConRDlg);
	pConRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(pConRWindow);
	if (pConRDlg->FillDlgElements(tableView))
	{
		pConRDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelProdConRDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ProductionConsumeRaw pConsumeRaw;
	pConsumeRaw.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteProductionConsumeRaw(&pConsumeRaw, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Prodcution consume raw with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewProdConRDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ProductionConsumeRaw pConsumeRaw;
	if (!pConsumeRaw.GetProductionConsumeRawByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ProductionConsumeRawList pConsumeRawList;
	BusinessLayer::Employee employee;
	BusinessLayer::Employee stockEmployee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), pConsumeRaw.GetStockEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	/*if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), pConsumeRaw.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}*/
	if (!stockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), pConsumeRaw.GetStockEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/invoice.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	pConsumeRawList.SetProductionConsumeRawID(pConsumeRaw.GetID());
	std::string filter = pConsumeRawList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ProductionConsumeRawListView> vecConRawList = dataFormBL->GetAllDataForClass<BusinessLayer::ProductionConsumeRawListView>(errorMessage, filter);
	if (vecConRawList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(pConsumeRaw.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(pConsumeRaw.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(stockEmployee.GetSurname().c_str()) + " " + QString(stockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	for each (auto item in vecConRawList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(pConsumeRaw.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtProdConRListDlg()
{
	CreateProdConRListDlg *craeteProdConRListDlg = new CreateProdConRListDlg(dataFormBL, false, this);
	if (0 != pConsumeRawID)
	{
		craeteProdConRListDlg->pConsumeRawID = pConsumeRawID;
	}
	craeteProdConRListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteProdConRListDlg->setWindowTitle(tr("Add raw to production consume raw list"));
	QMdiSubWindow *craeteConRListWindow = new QMdiSubWindow;
	craeteConRListWindow->setWidget(craeteProdConRListDlg);
	craeteConRListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteConRListWindow);
	craeteProdConRListDlg->show();
}
void DataForm::UdpProdConRListDlg()
{
	CreateProdConRListDlg *craeteProdConRListDlg = new CreateProdConRListDlg(dataFormBL, true, this);
	craeteProdConRListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteProdConRListDlg->setWindowTitle(tr("Update raw in production consume raw list"));
	QMdiSubWindow *craeteProdConRListWindow = new QMdiSubWindow;
	craeteProdConRListWindow->setWidget(craeteProdConRListDlg);
	craeteProdConRListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteProdConRListWindow);
	if (craeteProdConRListDlg->FillDlgElements(tableView))
	{
		craeteProdConRListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelProdConRListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ProductionConsumeRawList pConsumeRawList;
	pConsumeRawList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteProductionConsumeRawList(&pConsumeRawList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtPPlanDlg()
{
	CreatePPlanDlg *pPlanDlg = new CreatePPlanDlg(dataFormBL, false, this);
	pPlanDlg->setAttribute(Qt::WA_DeleteOnClose);
	pPlanDlg->setWindowTitle(tr("Create production plan"));
	QMdiSubWindow *pPlanWindow = new QMdiSubWindow;
	pPlanWindow->setWidget(pPlanDlg);
	pPlanWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(pPlanWindow);
	pPlanDlg->show();
}
void DataForm::UdpPPlanDlg()
{
	CreatePPlanDlg *pPlanDlg = new CreatePPlanDlg(dataFormBL, true, this);
	pPlanDlg->setAttribute(Qt::WA_DeleteOnClose);
	pPlanDlg->setWindowTitle(tr("Update production plan"));
	QMdiSubWindow *pPlanWindow = new QMdiSubWindow;
	pPlanWindow->setWidget(pPlanDlg);
	pPlanWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(pPlanWindow);
	if (pPlanDlg->FillDlgElements(tableView))
	{
		pPlanDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPPlanDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ProductionPlan pPlan;
	pPlan.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);

		if (dataFormBL->DeleteProductionPlan(&pPlan, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Production plan with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtPPlanListDlg()
{
	CreatePPlanListDlg *craetePPlanListDlg = new CreatePPlanListDlg(dataFormBL, false, this);
	if (0 != productionPlanID)
	{
		craetePPlanListDlg->productionPlanID = productionPlanID;
	}
	craetePPlanListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craetePPlanListDlg->setWindowTitle(tr("Add product to production plan list"));
	QMdiSubWindow *craetePPlanListWindow = new QMdiSubWindow;
	craetePPlanListWindow->setWidget(craetePPlanListDlg);
	craetePPlanListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craetePPlanListWindow);
	craetePPlanListDlg->show();
}
void DataForm::UdpPPlanListDlg()
{
	CreatePPlanListDlg *craetePPlanListDlg = new CreatePPlanListDlg(dataFormBL, true, this);
	craetePPlanListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craetePPlanListDlg->setWindowTitle(tr("Update product in production plan list"));
	QMdiSubWindow *craetePPlanListWindow = new QMdiSubWindow;
	craetePPlanListWindow->setWidget(craetePPlanListDlg);
	craetePPlanListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craetePPlanListWindow);
	if (craetePPlanListDlg->FillDlgElements(tableView))
	{
		craetePPlanListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPPlanListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ProductionPlanList pPlanList;
	pPlanList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteProductionPlanList(&pPlanList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product with this id does not exist in production paln list!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtPspDlg()
{
	CreatePspDlg *payslipDlg = new CreatePspDlg(dataFormBL, false, this);
	payslipDlg->setAttribute(Qt::WA_DeleteOnClose);
	payslipDlg->setWindowTitle(tr("Create payslip"));
	QMdiSubWindow *payslipWindow = new QMdiSubWindow;
	payslipWindow->setWidget(payslipDlg);
	payslipWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(payslipWindow);
	payslipDlg->show();
}
void DataForm::UdpPspDlg()
{
	CreatePspDlg *payslipDlg = new CreatePspDlg(dataFormBL, true, this);
	payslipDlg->setAttribute(Qt::WA_DeleteOnClose);
	payslipDlg->setWindowTitle(tr("Update payslip"));
	QMdiSubWindow *payslipWindow = new QMdiSubWindow;
	payslipWindow->setWidget(payslipDlg);
	payslipWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(payslipWindow);
	if (payslipDlg->FillDlgElements(tableView))
	{
		payslipDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPspDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Payslip payslip;
	payslip.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeletePayslip(&payslip, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Payslip with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtPurDlg()
{
	CreatePurDlg *purveyorDlg = new CreatePurDlg(dataFormBL, false, this);
	purveyorDlg->setAttribute(Qt::WA_DeleteOnClose);
	purveyorDlg->setWindowTitle(tr("Create purveyor"));
	QMdiSubWindow *purveyorWindow = new QMdiSubWindow;
	purveyorWindow->setWidget(purveyorDlg);
	purveyorWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(purveyorWindow);
	purveyorDlg->show();
}
void DataForm::UdpPurDlg()
{
	CreatePurDlg *purveyorDlg = new CreatePurDlg(dataFormBL, true, this);
	purveyorDlg->setAttribute(Qt::WA_DeleteOnClose);
	purveyorDlg->setWindowTitle(tr("Update purveyor"));
	QMdiSubWindow *purveyorWindow = new QMdiSubWindow;
	purveyorWindow->setWidget(purveyorDlg);
	purveyorWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(purveyorWindow);
	if (purveyorDlg->FillDlgElements(tableView))
	{
		purveyorDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelPurDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Purveyor purveyor;
	purveyor.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeletePurveyor(&purveyor, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Purveyor with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtRelDlg()
{
	CreateRelDlg *relationDlg = new CreateRelDlg(dataFormBL, false, this);
	relationDlg->setAttribute(Qt::WA_DeleteOnClose);
	relationDlg->setWindowTitle(tr("Create relation"));
	QMdiSubWindow *relationWindow = new QMdiSubWindow;
	relationWindow->setWidget(relationDlg);
	relationWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(relationWindow);
	relationDlg->show();
}
void DataForm::UdpRelDlg()
{
	CreateRelDlg *relationDlg = new CreateRelDlg(dataFormBL, true, this);
	relationDlg->setAttribute(Qt::WA_DeleteOnClose);
	relationDlg->setWindowTitle(tr("Update relation"));
	QMdiSubWindow *relationWindow = new QMdiSubWindow;
	relationWindow->setWidget(relationDlg);
	relationWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(relationWindow);
	if (relationDlg->FillDlgElements(tableView))
	{
		relationDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelRelDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Relation relation;
	relation.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteRelation(&relation, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Relation with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtRelTypeDlg()
{
	CreateRelTypeDlg *relationTypeDlg = new CreateRelTypeDlg(dataFormBL, false, this);
	relationTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	relationTypeDlg->setWindowTitle(tr("Create relation type"));
	QMdiSubWindow *relationTypeWindow = new QMdiSubWindow;
	relationTypeWindow->setWidget(relationTypeDlg);
	relationTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(relationTypeWindow);
	relationTypeDlg->show();
}
void DataForm::UdpRelTypeDlg()
{
	CreateRelTypeDlg *relationTypeDlg = new CreateRelTypeDlg(dataFormBL, true, this);
	relationTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	relationTypeDlg->setWindowTitle(tr("Update relation type"));
	QMdiSubWindow *relationTypeWindow = new QMdiSubWindow;
	relationTypeWindow->setWidget(relationTypeDlg);
	relationTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(relationTypeWindow);
	if (relationTypeDlg->FillDlgElements(tableView))
	{
		relationTypeDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelRelTypeDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::RelationType relationType;
	relationType.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteRelationType(&relationType, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Relation type with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtRcpOthStDlg()
{
	CreateRcpOthStDlg *rosDlg = new CreateRcpOthStDlg(dataFormBL, false, this);
	rosDlg->setAttribute(Qt::WA_DeleteOnClose);
	rosDlg->setWindowTitle(tr("Create receipt product"));
	QMdiSubWindow *rosWindow = new QMdiSubWindow;
	rosWindow->setWidget(rosDlg);
	rosWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(rosWindow);
	rosDlg->show();
}
void DataForm::UdpRcpOthStDlg()
{
	CreateRcpOthStDlg *rosDlg = new CreateRcpOthStDlg(dataFormBL, true, this);
	rosDlg->setAttribute(Qt::WA_DeleteOnClose);
	rosDlg->setWindowTitle(tr("Update receipt product"));
	QMdiSubWindow *rosWindow = new QMdiSubWindow;
	rosWindow->setWidget(rosDlg);
	rosWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(rosWindow);
	if (rosDlg->FillDlgElements(tableView))
	{
		rosDlg->show();
	}
	/*else
	{
	QMessageBox::information(NULL, QString(tr("Warning")),
	QString(tr("Please select one row at first!")),
	QString(tr("Ok")));
	}*/
}

void DataForm::DelRcpOthStDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ReceiptOtherStocks receiptOtherStocks;
	receiptOtherStocks.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteReceiptOtherStocks(&receiptOtherStocks, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Receipt other stocks with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewRcpOthStDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ReceiptOtherStocks receiptOtherStocks;
	if (!receiptOtherStocks.GetReceiptOtherStocksByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ReceiptOtherStocksList receiptOtherStocksList;
	BusinessLayer::Employee employee;
	BusinessLayer::Employee stockEmployee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), receiptOtherStocks.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), receiptOtherStocks.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!stockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), receiptOtherStocks.GetPurveyorID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/invoice.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	receiptOtherStocksList.SetReceiptOtherStocksID(receiptOtherStocks.GetID());
	std::string filter = receiptOtherStocksList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ReceiptOtherStocksListView> vecRcpOthStList = dataFormBL->GetAllDataForClass<BusinessLayer::ReceiptOtherStocksListView>(errorMessage, filter);
	if (vecRcpOthStList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(receiptOtherStocks.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(receiptOtherStocks.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(stockEmployee.GetSurname().c_str()) + " " + QString(stockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::OtherStocks otherStocks;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	BusinessLayer::NetCost netCost;
	QString tableBody;
	double sum = 0;
	for each (auto item in vecRcpOthStList)
	{
		otherStocks.Clear();
		measure.Clear();
		currency.Clear();
		netCost.Clear();
		if (!otherStocks.GetOtherStocksByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetOtherStocksID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), otherStocks.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), otherStocks.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(otherStocks.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(otherStocks.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()*otherStocks.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		sum += item.GetCount() * otherStocks.GetPrice();
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(sum, 'f', 3), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtRcpOthStListDlg()
{
	CreateRcpOthStListDlg *craeteRcpOthStListDlg = new CreateRcpOthStListDlg(dataFormBL, false, this);
	if (0 != receiptOtherStocksID)
	{
		craeteRcpOthStListDlg->receiptOtherStocksID = receiptOtherStocksID;
	}
	craeteRcpOthStListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteRcpOthStListDlg->setWindowTitle(tr("Add other stocks to receipt list"));
	QMdiSubWindow *craeteRcpOthStListWindow = new QMdiSubWindow;
	craeteRcpOthStListWindow->setWidget(craeteRcpOthStListDlg);
	craeteRcpOthStListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteRcpOthStListWindow);
	craeteRcpOthStListDlg->show();
}
void DataForm::UdpRcpOthStListDlg()
{
	CreateRcpOthStListDlg *craeteRcpOthStListDlg = new CreateRcpOthStListDlg(dataFormBL, true, this);
	craeteRcpOthStListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteRcpOthStListDlg->setWindowTitle(tr("Update other stocks in receipt list"));
	QMdiSubWindow *craeteRcpOthStListWindow = new QMdiSubWindow;
	craeteRcpOthStListWindow->setWidget(craeteRcpOthStListDlg);
	craeteRcpOthStListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteRcpOthStListWindow);
	if (craeteRcpOthStListDlg->FillDlgElements(tableView))
	{
		craeteRcpOthStListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelRcpOthStListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ReceiptOtherStocksList receiptOtherStocksList;
	receiptOtherStocksList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteReceiptOtherStocksList(&receiptOtherStocksList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtRcpPDlg()
{
	CreateRcpPDlg *rcpPDlg = new CreateRcpPDlg(dataFormBL, false, this);
	rcpPDlg->setAttribute(Qt::WA_DeleteOnClose);
	rcpPDlg->setWindowTitle(tr("Create receipt product"));
	QMdiSubWindow *rcpPWindow = new QMdiSubWindow;
	rcpPWindow->setWidget(rcpPDlg);
	rcpPWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(rcpPWindow);
	rcpPDlg->show();
}
void DataForm::UdpRcpPDlg()
{
	CreateRcpPDlg *rcpPDlg = new CreateRcpPDlg(dataFormBL, true, this);
	rcpPDlg->setAttribute(Qt::WA_DeleteOnClose);
	rcpPDlg->setWindowTitle(tr("Update receipt product"));
	QMdiSubWindow *rcpPWindow = new QMdiSubWindow;
	rcpPWindow->setWidget(rcpPDlg);
	rcpPWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(rcpPWindow);
	if (rcpPDlg->FillDlgElements(tableView))
	{
		rcpPDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}

void DataForm::DelRcpPDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ReceiptProduct receiptProdcut;
	receiptProdcut.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteReceiptProduct(&receiptProdcut, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Receipt product with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewRcpPDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ReceiptProduct receiptProdcut;
	if (!receiptProdcut.GetReceiptProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ReceiptProductList receiptProdcutList;
	BusinessLayer::Employee employee;
	BusinessLayer::Employee stockEmployee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), receiptProdcut.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), receiptProdcut.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!stockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), receiptProdcut.GetStockEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/invoice.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	receiptProdcutList.SetReceiptProductID(receiptProdcut.GetID());
	std::string filter = receiptProdcutList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ReceiptProductListView> vecRcpProdList = dataFormBL->GetAllDataForClass<BusinessLayer::ReceiptProductListView>(errorMessage, filter);
	if (vecRcpProdList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(receiptProdcut.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(receiptProdcut.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(stockEmployee.GetSurname().c_str()) + " " + QString(stockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	BusinessLayer::NetCost netCost;
	QString tableBody;
	double sum = 0;
	for each (auto item in vecRcpProdList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		netCost.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!netCost.GetNetCostByProductID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()*product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		sum += item.GetCount() * product.GetPrice();
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(sum, 'f',3), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtRcpPListDlg()
{
	CreateRcpPListDlg *craeteRcpPListDlg = new CreateRcpPListDlg(dataFormBL, false, this);
	if (0 != receiptProductID)
	{
		craeteRcpPListDlg->receiptProductID = receiptProductID;
	}
	craeteRcpPListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteRcpPListDlg->setWindowTitle(tr("Add product to receipt product list"));
	QMdiSubWindow *craeteRcpPListWindow = new QMdiSubWindow;
	craeteRcpPListWindow->setWidget(craeteRcpPListDlg);
	craeteRcpPListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteRcpPListWindow);
	craeteRcpPListDlg->show();
}
void DataForm::UdpRcpPListDlg()
{
	CreateRcpPListDlg *craeteRcpPListDlg = new CreateRcpPListDlg(dataFormBL, true, this);
	craeteRcpPListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteRcpPListDlg->setWindowTitle(tr("Update product in receipt product list"));
	QMdiSubWindow *craeteRcpPListWindow = new QMdiSubWindow;
	craeteRcpPListWindow->setWidget(craeteRcpPListDlg);
	craeteRcpPListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteRcpPListWindow);
	if (craeteRcpPListDlg->FillDlgElements(tableView))
	{
		craeteRcpPListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelRcpPListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ReceiptProductList receiptProductList;
	receiptProductList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteReceiptProductList(&receiptProductList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtStockTrDlg()
{
	CreateStockTrDlg *StockTrDlg = new CreateStockTrDlg(dataFormBL, false, this);
	StockTrDlg->setAttribute(Qt::WA_DeleteOnClose);
	StockTrDlg->setWindowTitle(tr("Stock transfer"));
	QMdiSubWindow *StockTrWindow = new QMdiSubWindow;
	StockTrWindow->setWidget(StockTrDlg);
	StockTrWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(StockTrWindow);
	StockTrDlg->show();
}
void DataForm::UdpStockTrDlg()
{
	CreateStockTrDlg *StockTrDlg = new CreateStockTrDlg(dataFormBL, true, this);
	StockTrDlg->setAttribute(Qt::WA_DeleteOnClose);
	StockTrDlg->setWindowTitle(tr("Update stock transfer"));
	QMdiSubWindow *StockTrWindow = new QMdiSubWindow;
	StockTrWindow->setWidget(StockTrDlg);
	StockTrWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(StockTrWindow);
	if (StockTrDlg->FillDlgElements(tableView))
	{
		StockTrDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelStockTrDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::StockTransfer stockTransfer;
	stockTransfer.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteStockTransfer(&stockTransfer, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Consume raw with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewStockTrDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::StockTransfer stockTransfer;
	if (!stockTransfer.GetStockTransferByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::StockTransferList stockTransferList;
	BusinessLayer::Employee fromStockEmployee;
	BusinessLayer::Employee toStockEmployee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), stockTransfer.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!fromStockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), stockTransfer.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!toStockEmployee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), stockTransfer.GetStockEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/invoice.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	stockTransferList.SetStockTransferID(stockTransfer.GetID());
	std::string filter = stockTransferList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::StockTransferListView> vecStockTrawList = dataFormBL->GetAllDataForClass<BusinessLayer::StockTransferListView>(errorMessage, filter);
	if (vecStockTrawList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(stockTransfer.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(stockTransfer.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(fromStockEmployee.GetSurname().c_str()) + " " + QString(fromStockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(toStockEmployee.GetSurname().c_str()) + " " + QString(toStockEmployee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	double sum = 0;
	for each (auto item in vecStockTrawList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()*product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		sum += item.GetCount() * product.GetPrice();
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(sum,'f', 3), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtStockTrListDlg()
{
	CreateStockTrListDlg *craeteStockTrListDlg = new CreateStockTrListDlg(dataFormBL, false, this);
	if (0 != stockTransferID)
	{
		craeteStockTrListDlg->stockTransferID = stockTransferID;
	}
	craeteStockTrListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteStockTrListDlg->setWindowTitle(tr("Add product to stock transfer list"));
	QMdiSubWindow *craeteStockTrListWindow = new QMdiSubWindow;
	craeteStockTrListWindow->setWidget(craeteStockTrListDlg);
	craeteStockTrListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteStockTrListWindow);
	craeteStockTrListDlg->show();
}
void DataForm::UdpStockTrListDlg()
{
	CreateStockTrListDlg *craeteStockTrListDlg = new CreateStockTrListDlg(dataFormBL, true, this);
	craeteStockTrListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteStockTrListDlg->setWindowTitle(tr("Update raw in receipt raw list"));
	QMdiSubWindow *craeteStockTrListWindow = new QMdiSubWindow;
	craeteStockTrListWindow->setWidget(craeteStockTrListDlg);
	craeteStockTrListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteStockTrListWindow);
	if (craeteStockTrListDlg->FillDlgElements(tableView))
	{
		craeteStockTrListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelStockTrListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::StockTransferList stockTransferList;
	stockTransferList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteStockTransferList(&stockTransferList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtRfdDlg()
{
	CreateRfdDlg *refundDlg = new CreateRfdDlg(dataFormBL, false, this);
	refundDlg->setAttribute(Qt::WA_DeleteOnClose);
	refundDlg->setWindowTitle(tr("Create refund"));
	QMdiSubWindow *refundWindow = new QMdiSubWindow;
	refundWindow->setWidget(refundDlg);
	refundWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(refundWindow);
	refundDlg->show();
}
void DataForm::UdpRfdDlg()
{
	CreateRfdDlg *refundDlg = new CreateRfdDlg(dataFormBL, true, this);
	refundDlg->setAttribute(Qt::WA_DeleteOnClose);
	refundDlg->setWindowTitle(tr("Update refund"));
	QMdiSubWindow *refundWindow = new QMdiSubWindow;
	refundWindow->setWidget(refundDlg);
	refundWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(refundWindow);
	if (refundDlg->FillDlgElements(tableView))
	{
		refundDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelRfdDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Refund refund;
	refund.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteRefund(&refund, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Refund with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtRoleDlg()
{
	CreateRoleDlg *roleDlg = new CreateRoleDlg(dataFormBL, false, this);
	roleDlg->setAttribute(Qt::WA_DeleteOnClose);
	roleDlg->setWindowTitle(tr("Create role"));
	QMdiSubWindow *roleWindow = new QMdiSubWindow;
	roleWindow->setWidget(roleDlg);
	roleWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(roleWindow);
	roleDlg->show();
}
void DataForm::UdpRoleDlg()
{
	CreateRoleDlg *roleDlg = new CreateRoleDlg(dataFormBL, true, this);
	roleDlg->setAttribute(Qt::WA_DeleteOnClose);
	roleDlg->setWindowTitle(tr("Update role"));
	QMdiSubWindow *roleWindow = new QMdiSubWindow;
	roleWindow->setWidget(roleDlg);
	roleWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(roleWindow);
	if (roleDlg->FillDlgElements(tableView))
	{
		roleDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelRoleDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Role role;
	role.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteRole(&role, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Role with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtRtrnDlg()
{
	CreateRtrnDlg *returnDlg = new CreateRtrnDlg(dataFormBL, false, this);
	returnDlg->setAttribute(Qt::WA_DeleteOnClose);
	returnDlg->setWindowTitle(tr("Create return"));
	QMdiSubWindow *returnWindow = new QMdiSubWindow;
	returnWindow->setWidget(returnDlg);
	returnWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(returnWindow);
	returnDlg->show();
}
void DataForm::UdpRtrnDlg()
{
	CreateRtrnDlg *returnDlg = new CreateRtrnDlg(dataFormBL, true, this);
	returnDlg->setAttribute(Qt::WA_DeleteOnClose);
	returnDlg->setWindowTitle(tr("Update return"));
	QMdiSubWindow *returnWindow = new QMdiSubWindow;
	returnWindow->setWidget(returnDlg);
	returnWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(returnWindow);
	if (returnDlg->FillDlgElements(tableView))
	{
		returnDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelRtrnDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Return ret;
	ret.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteReturn(&ret, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Return with this id does not exist!")),
			QString(tr("Ok")));

	}
}

void DataForm::ViewRtrnDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Return ret;
	if (!ret.GetReturnByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ReturnList returnList;
	BusinessLayer::Client client;
	BusinessLayer::Employee employee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), ret.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!client.GetClientByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), ret.GetClientID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), ret.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/return.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	returnList.SetReturnID(ret.GetID());
	std::string filter = returnList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::ReturnListView> vecRetList = dataFormBL->GetAllDataForClass<BusinessLayer::ReturnListView>(errorMessage, filter);
	if (vecRetList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(ret.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(ret.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName2Ph"), QString(client.GetFirm().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName2Ph"), QString(client.GetSurname().c_str()) + " " + QString(client.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	for each (auto item in vecRetList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(ret.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtRtrnListDlg()
{
	CreateRtrnListDlg *craeteRtrnListDlg = new CreateRtrnListDlg(dataFormBL, false, this);
	if (0 != returnID)
	{
		craeteRtrnListDlg->returnID = returnID;
	}
	craeteRtrnListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteRtrnListDlg->setWindowTitle(tr("Add product to return list"));
	QMdiSubWindow *craeteRtrnListWindow = new QMdiSubWindow;
	craeteRtrnListWindow->setWidget(craeteRtrnListDlg);
	craeteRtrnListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteRtrnListWindow);
	craeteRtrnListDlg->show();
}
void DataForm::UdpRtrnListDlg()
{
	CreateRtrnListDlg *craeteRtrnListDlg = new CreateRtrnListDlg(dataFormBL, true, this);
	craeteRtrnListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteRtrnListDlg->setWindowTitle(tr("Update product in return list"));
	QMdiSubWindow *craeteRtrnListWindow = new QMdiSubWindow;
	craeteRtrnListWindow->setWidget(craeteRtrnListDlg);
	craeteRtrnListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteRtrnListWindow);
	if (craeteRtrnListDlg->FillDlgElements(tableView))
	{
		craeteRtrnListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelRtrnListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::ReturnList returnList;
	returnList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteReturnList(&returnList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product with this id does not exist in return list!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtSlrDlg()
{
	CreateSlrDlg *salaryDlg = new CreateSlrDlg(dataFormBL, false, this);
	salaryDlg->setAttribute(Qt::WA_DeleteOnClose);
	salaryDlg->setWindowTitle(tr("Create salary"));
	QMdiSubWindow *salaryWindow = new QMdiSubWindow;
	salaryWindow->setWidget(salaryDlg);
	salaryWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(salaryWindow);
	salaryDlg->show();
}
void DataForm::UdpSlrDlg()
{
	CreateSlrDlg *salaryDlg = new CreateSlrDlg(dataFormBL, true, this);
	salaryDlg->setAttribute(Qt::WA_DeleteOnClose);
	salaryDlg->setWindowTitle(tr("Update salary"));
	QMdiSubWindow *salaryWindow = new QMdiSubWindow;
	salaryWindow->setWidget(salaryDlg);
	salaryWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(salaryWindow);
	if (salaryDlg->FillDlgElements(tableView))
	{
		salaryDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelSlrDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Salary salary;
	salary.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteSalary(&salary, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Salary with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtSlrTypeDlg()
{
	CreateSlrTypeDlg *salaryTypeDlg = new CreateSlrTypeDlg(dataFormBL, false, this);
	salaryTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	salaryTypeDlg->setWindowTitle(tr("Create salary type" ));
	QMdiSubWindow *salaryTypeWindow = new QMdiSubWindow;
	salaryTypeWindow->setWidget(salaryTypeDlg);
	salaryTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(salaryTypeWindow);
	salaryTypeDlg->show();
}
void DataForm::UdpSlrTypeDlg()
{
	CreateSlrTypeDlg *salaryTypeDlg = new CreateSlrTypeDlg(dataFormBL, true, this);
	salaryTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	salaryTypeDlg->setWindowTitle(tr("Update salary type"));
	QMdiSubWindow *salaryTypeWindow = new QMdiSubWindow;
	salaryTypeWindow->setWidget(salaryTypeDlg);
	salaryTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(salaryTypeWindow);
	if (salaryTypeDlg->FillDlgElements(tableView))
	{
		salaryTypeDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelSlrTypeDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::SalaryType salaryType;
	salaryType.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteSalaryType(&salaryType, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Salary type with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtStsDlg()
{
	CreateStsDlg *statusDlg = new CreateStsDlg(dataFormBL, false, this);
	statusDlg->setAttribute(Qt::WA_DeleteOnClose);
	statusDlg->setWindowTitle(tr("Create status"));
	QMdiSubWindow *statusWindow = new QMdiSubWindow;
	statusWindow->setWidget(statusDlg);
	statusWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(statusWindow);
	statusDlg->show();
}
void DataForm::UdpStsDlg()
{
	CreateStsDlg *statusDlg = new CreateStsDlg(dataFormBL, true, this);
	statusDlg->setAttribute(Qt::WA_DeleteOnClose);
	statusDlg->setWindowTitle(tr("Update status"));
	QMdiSubWindow *statusWindow = new QMdiSubWindow;
	statusWindow->setWidget(statusDlg);
	statusWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(statusWindow);
	if (statusDlg->FillDlgElements(tableView))
	{
		statusDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelStsDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Status status;
	status.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteStatus(&status,errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Status with this id does not exist!")),
			QString(tr("Ok")));
	}
}


void DataForm::CrtStsRuleDlg()
{
	CreateStsRuleDlg *statusRuleDlg = new CreateStsRuleDlg(dataFormBL, false, this);
	statusRuleDlg->setAttribute(Qt::WA_DeleteOnClose);
	statusRuleDlg->setWindowTitle(tr("Create status rule"));
	QMdiSubWindow *statusRuleWindow = new QMdiSubWindow;
	statusRuleWindow->setWidget(statusRuleDlg);
	statusRuleWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(statusRuleWindow);
	statusRuleDlg->show();
}
void DataForm::UdpStsRuleDlg()
{
	CreateStsRuleDlg *statusRuleDlg = new CreateStsRuleDlg(dataFormBL, true, this);
	statusRuleDlg->setAttribute(Qt::WA_DeleteOnClose);
	statusRuleDlg->setWindowTitle(tr("Update status rule"));
	QMdiSubWindow *statusRuleWindow = new QMdiSubWindow;
	statusRuleWindow->setWidget(statusRuleDlg);
	statusRuleWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(statusRuleWindow);
	if (statusRuleDlg->FillDlgElements(tableView))
	{
		statusRuleDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelStsRuleDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::StatusRule statusRule;
	statusRule.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteStatusRule (&statusRule, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Status rule with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtSpecDlg()
{
	CreateSpecDlg *specPDlg = new CreateSpecDlg(dataFormBL, false, this);
	specPDlg->setAttribute(Qt::WA_DeleteOnClose);
	specPDlg->setWindowTitle(tr("Create specification"));
	QMdiSubWindow *specPWindow = new QMdiSubWindow;
	specPWindow->setWidget(specPDlg);
	specPWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(specPWindow);
	specPDlg->show();
}
void DataForm::UdpSpecDlg()
{
	CreateSpecDlg *specPDlg = new CreateSpecDlg(dataFormBL, true, this);
	specPDlg->setAttribute(Qt::WA_DeleteOnClose);
	specPDlg->setWindowTitle(tr("Update specification"));
	QMdiSubWindow *specPWindow = new QMdiSubWindow;
	specPWindow->setWidget(specPDlg);
	specPWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(specPWindow);
	if (specPDlg->FillDlgElements(tableView))
	{
		specPDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelSpecDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Specification specification;
	specification.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteSpecification(&specification, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Specification with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewSpecDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Specification spec;
	if (!spec.GetSpecificationByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::SpecificationList specList;
	BusinessLayer::Employee employee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), spec.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), spec.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/specification.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	specList.SetSpecificationID(spec.GetID());
	std::string filter = specList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::SpecificationListView> vecSpecList = dataFormBL->GetAllDataForClass<BusinessLayer::SpecificationListView>(errorMessage, filter);
	if (vecSpecList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(spec.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(spec.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	for each (auto item in vecSpecList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(product.GetPrice()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()*product.GetPrice(),'f',3) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(spec.GetSum(), 'f',3), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtSpecListDlg()
{
	CreateSpecListDlg *specListDlg = new CreateSpecListDlg(dataFormBL, false, this);
	if (0 != specificationID)
	{
		specListDlg->specificationID = specificationID;
	}
	specListDlg->setAttribute(Qt::WA_DeleteOnClose);
	specListDlg->setWindowTitle(tr("Add product to specification list"));
	QMdiSubWindow *specListWindow = new QMdiSubWindow;
	specListWindow->setWidget(specListDlg);
	specListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(specListWindow);
	specListDlg->show();
}
void DataForm::UdpSpecListDlg()
{
	CreateSpecListDlg *specListDlg = new CreateSpecListDlg(dataFormBL, true, this);
	specListDlg->setAttribute(Qt::WA_DeleteOnClose);
	specListDlg->setWindowTitle(tr("Update product in specification list"));
	QMdiSubWindow *specListWindow = new QMdiSubWindow;
	specListWindow->setWidget(specListDlg);
	specListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(specListWindow);
	if (specListDlg->FillDlgElements(tableView))
	{
		specListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelSpecListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::SpecificationList specificationList;
	specificationList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteSpecificationList(&specificationList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtSplDlg()
{
	CreateSplDlg *spoilageDlg = new CreateSplDlg(dataFormBL, false, this);
	spoilageDlg->setAttribute(Qt::WA_DeleteOnClose);
	spoilageDlg->setWindowTitle(tr("Create spoilage"));
	QMdiSubWindow *spoilageWindow = new QMdiSubWindow;
	spoilageWindow->setWidget(spoilageDlg);
	spoilageWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(spoilageWindow);
	spoilageDlg->show();
}
void DataForm::UdpSplDlg()
{
	CreateSplDlg *spoilageDlg = new CreateSplDlg(dataFormBL, true, this);
	spoilageDlg->setAttribute(Qt::WA_DeleteOnClose);
	spoilageDlg->setWindowTitle(tr("Update spoilage"));
	QMdiSubWindow *spoilageWindow = new QMdiSubWindow;
	spoilageWindow->setWidget(spoilageDlg);
	spoilageWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(spoilageWindow);
	if (spoilageDlg->FillDlgElements(tableView))
	{
		spoilageDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelSplDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Spoilage spoilage;
	spoilage.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteSpoilage(&spoilage, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Spoilage with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewSplDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Spoilage spoilage;
	if (!spoilage.GetSpoilageByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::SpoilageList splList;
	BusinessLayer::Employee employee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), spoilage.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), spoilage.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	
	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/spoilage.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	splList.SetSpoilageID(spoilage.GetID());
	std::string filter = splList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::SpoilageListView> vecSplList = dataFormBL->GetAllDataForClass<BusinessLayer::SpoilageListView>(errorMessage, filter);
	if (vecSplList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(spoilage.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(spoilage.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	BusinessLayer::NetCost netCost;
	QString tableBody;
	for each (auto item in vecSplList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		netCost.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!netCost.GetNetCostByProductID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(spoilage.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtSplListDlg()
{
	CreateSplListDlg *spoilageListDlg = new CreateSplListDlg(dataFormBL, false, this);
	if (0 != spoilageID)
	{
		spoilageListDlg->spoilageID = spoilageID;
	}
	spoilageListDlg->setAttribute(Qt::WA_DeleteOnClose);
	spoilageListDlg->setWindowTitle(tr("Add product to spoilage list"));
	QMdiSubWindow *spoilageListWindow = new QMdiSubWindow;
	spoilageListWindow->setWidget(spoilageListDlg);
	spoilageListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(spoilageListWindow);
	spoilageListDlg->show();
}
void DataForm::UdpSplListDlg()
{
	CreateSplListDlg *spoilageListDlg = new CreateSplListDlg(dataFormBL, true, this);
	spoilageListDlg->setAttribute(Qt::WA_DeleteOnClose);
	spoilageListDlg->setWindowTitle(tr("Update product in spoilage list"));
	QMdiSubWindow *spoilageListWindow = new QMdiSubWindow;
	spoilageListWindow->setWidget(spoilageListDlg);
	spoilageListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(spoilageListWindow);
	if (spoilageListDlg->FillDlgElements(tableView))
	{
		spoilageListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelSplListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::SpoilageList spoilageList;
	spoilageList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteSpoilageList(&spoilageList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product with this id does not exist in spoilage list!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtStockDlg()
{
	CreateStockDlg *stockDlg = new CreateStockDlg(dataFormBL, false, this);
	stockDlg->setAttribute(Qt::WA_DeleteOnClose);
	stockDlg->setWindowTitle(tr("Create stock"));
	QMdiSubWindow *stockWindow = new QMdiSubWindow;
	stockWindow->setWidget(stockDlg);
	stockWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(stockWindow);
	stockDlg->show();
}
void DataForm::UdpStockDlg()
{
	CreateStockDlg *stockDlg = new CreateStockDlg(dataFormBL, true, this);
	stockDlg->setAttribute(Qt::WA_DeleteOnClose);
	stockDlg->setWindowTitle(tr("Update stock"));
	QMdiSubWindow *stockWindow = new QMdiSubWindow;
	stockWindow->setWidget(stockDlg);
	stockWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(stockWindow);
	if (stockDlg->FillDlgElements(tableView))
	{
		stockDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelStockDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Stock stock;
	stock.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteStock(&stock, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Receipt product with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtStockLmDlg()
{
	CreateStockLimitDlg *stockLmDlg = new CreateStockLimitDlg(dataFormBL, false, this);
	stockLmDlg->setAttribute(Qt::WA_DeleteOnClose);
	stockLmDlg->setWindowTitle(tr("Create stock"));
	QMdiSubWindow *stockLmWindow = new QMdiSubWindow;
	stockLmWindow->setWidget(stockLmDlg);
	stockLmWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(stockLmWindow);
	stockLmDlg->show();
}
void DataForm::UdpStockLmDlg()
{
	CreateStockLimitDlg *stockLmDlg = new CreateStockLimitDlg(dataFormBL, true, this);
	stockLmDlg->setAttribute(Qt::WA_DeleteOnClose);
	stockLmDlg->setWindowTitle(tr("Update stock"));
	QMdiSubWindow *stockLmWindow = new QMdiSubWindow;
	stockLmWindow->setWidget(stockLmDlg);
	stockLmWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(stockLmWindow);
	if (stockLmDlg->FillDlgElements(tableView))
	{
		stockLmDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelStockLmDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::StockLimit stockLimit;
	stockLimit.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteStockLimit(&stockLimit, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Stock limit with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtSAccDlg()
{
	CreateSAccDlg *sAccountDlg = new CreateSAccDlg(dataFormBL, false, this);
	sAccountDlg->setAttribute(Qt::WA_DeleteOnClose);
	sAccountDlg->setWindowTitle(tr("Create subaccount"));
	QMdiSubWindow *sAccountWindow = new QMdiSubWindow;
	sAccountWindow->setWidget(sAccountDlg);
	sAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(sAccountWindow);
	sAccountDlg->show();
}
void DataForm::UdpSAccDlg()
{
	CreateSAccDlg *sAccountDlg = new CreateSAccDlg(dataFormBL, true, this);
	sAccountDlg->setAttribute(Qt::WA_DeleteOnClose);
	sAccountDlg->setWindowTitle(tr("Update subaccount"));
	QMdiSubWindow *sAccountWindow = new QMdiSubWindow;
	sAccountWindow->setWidget(sAccountDlg);
	sAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(sAccountWindow);
	if (sAccountDlg->FillDlgElements(tableView))
	{
		sAccountDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelSAccDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Subaccount subaccount;
	subaccount.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteSubaccount(&subaccount, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Subaccount with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtSAccLmDlg()
{
	CreateSAccLmDlg *sAccLmDlg = new CreateSAccLmDlg(dataFormBL, false, this);
	sAccLmDlg->setAttribute(Qt::WA_DeleteOnClose);
	sAccLmDlg->setWindowTitle(tr("Create subaccount limit"));
	QMdiSubWindow *sAccLmWindow = new QMdiSubWindow;
	sAccLmWindow->setWidget(sAccLmDlg);
	sAccLmWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(sAccLmWindow);
	sAccLmDlg->show();
}
void DataForm::UdpSAccLmDlg()
{
	CreateSAccLmDlg *sAccLmDlg = new CreateSAccLmDlg(dataFormBL, true, this);
	sAccLmDlg->setAttribute(Qt::WA_DeleteOnClose);
	sAccLmDlg->setWindowTitle(tr("Update subaccount limit"));
	QMdiSubWindow *sAccLmWindow = new QMdiSubWindow;
	sAccLmWindow->setWidget(sAccLmDlg);
	sAccLmWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(sAccLmWindow);
	if (sAccLmDlg->FillDlgElements(tableView))
	{
		sAccLmDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelSAccLmDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::SubaccountLimit subaccountLimit;
	subaccountLimit.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteSubaccountLimit(&subaccountLimit, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Subaccount limit with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtTmsDlg()
{
	CreateTmsDlg *tmsDlg = new CreateTmsDlg(dataFormBL, false, this);
	tmsDlg->setAttribute(Qt::WA_DeleteOnClose);
	tmsDlg->setWindowTitle(tr("Create timesheet"));
	QMdiSubWindow *tmsWindow = new QMdiSubWindow;
	tmsWindow->setWidget(tmsDlg);
	tmsWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(tmsWindow);
	tmsDlg->show();
}
void DataForm::UdpTmsDlg()
{
	CreateTmsDlg *tmsDlg = new CreateTmsDlg(dataFormBL, true, this);
	tmsDlg->setAttribute(Qt::WA_DeleteOnClose);
	tmsDlg->setWindowTitle(tr("Update timesheet"));
	QMdiSubWindow *tmsWindow = new QMdiSubWindow;
	tmsWindow->setWidget(tmsDlg);
	tmsWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(tmsWindow);
	if (tmsDlg->FillDlgElements(tableView))
	{
		tmsDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelTmsDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Timesheet timesheet;
	timesheet.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteTimesheet(&timesheet, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Timesheet with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtTrsDlg()
{
	CreateTrsDlg *trsDlg = new CreateTrsDlg(dataFormBL, false, this);
	trsDlg->setAttribute(Qt::WA_DeleteOnClose);
	trsDlg->setWindowTitle(tr("Create transport"));
	QMdiSubWindow *trsWindow = new QMdiSubWindow;
	trsWindow->setWidget(trsDlg);
	trsWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(trsWindow);
	trsDlg->show();
}
void DataForm::UdpTrsDlg()
{
	CreateTrsDlg *trsDlg = new CreateTrsDlg(dataFormBL, true, this);
	trsDlg->setAttribute(Qt::WA_DeleteOnClose);
	trsDlg->setWindowTitle(tr("Update transport"));
	QMdiSubWindow *trsWindow = new QMdiSubWindow;
	trsWindow->setWidget(trsDlg);
	trsWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(trsWindow);
	if (trsDlg->FillDlgElements(tableView))
	{
		trsDlg->show();
	}
	/*else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}*/
}
void DataForm::DelTrsDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Transport transport;
	transport.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteTransport(&transport, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Transport with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewTrsDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Transport transport;
	if (!transport.GetTransportByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::TransportList transportList;
	BusinessLayer::Employee employee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), transport.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), transport.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/transport.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	transportList.SetTransportID(transport.GetID());
	std::string filter = transportList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::TransportListView> vecTrsList = dataFormBL->GetAllDataForClass<BusinessLayer::TransportListView>(errorMessage, filter);
	if (vecTrsList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(transport.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(transport.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	double sum = 0;
	for each (auto item in vecTrsList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount() * product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
		sum += item.GetCount() * product.GetPrice();
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(sum, 'f' ,3), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtTrsListDlg()
{
	CreateTrsListDlg *craeteTrsListDlg = new CreateTrsListDlg(dataFormBL, false, this);
	if (0 != transportID)
	{
		craeteTrsListDlg->transportID = transportID;
	}
	craeteTrsListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteTrsListDlg->setWindowTitle(tr("Add product to transport list"));
	QMdiSubWindow *craeteTrsListWindow = new QMdiSubWindow;
	craeteTrsListWindow->setWidget(craeteTrsListDlg);
	craeteTrsListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteTrsListWindow);
	craeteTrsListDlg->show();
}
void DataForm::UdpTrsListDlg()
{
	CreateTrsListDlg *craeteTrsListDlg = new CreateTrsListDlg(dataFormBL, true, this);
	craeteTrsListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteTrsListDlg->setWindowTitle(tr("Update product in transport list"));
	QMdiSubWindow *craeteTrsListWindow = new QMdiSubWindow;
	craeteTrsListWindow->setWidget(craeteTrsListDlg);
	craeteTrsListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteTrsListWindow);
	if (craeteTrsListDlg->FillDlgElements(tableView))
	{
		craeteTrsListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelTrsListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::TransportList transportList;
	transportList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteTransportList(&transportList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtUserDlg()
{
	CreateUserDlg *userDlg = new CreateUserDlg(dataFormBL, false, this);
	userDlg->setAttribute(Qt::WA_DeleteOnClose);
	userDlg->setWindowTitle(tr("Create user"));
	QMdiSubWindow *userWindow = new QMdiSubWindow;
	userWindow->setWidget(userDlg);
	userWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(userWindow);
	userDlg->show();
}
void DataForm::UdpUserDlg()
{
	CreateUserDlg *userDlg = new CreateUserDlg(dataFormBL, true, this);
	userDlg->setAttribute(Qt::WA_DeleteOnClose);
	userDlg->setWindowTitle(tr("Update user"));
	QMdiSubWindow *userWindow = new QMdiSubWindow;
	userWindow->setWidget(userDlg);
	userWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(userWindow);
	if (userDlg->FillDlgElements(tableView))
	{
		userDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelUserDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::User user;
	user.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteUser(&user, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("User with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtUserGrDlg()
{
	CreateUserGrDlg *userGrDlg = new CreateUserGrDlg(dataFormBL, false, this);
	userGrDlg->setAttribute(Qt::WA_DeleteOnClose);
	userGrDlg->setWindowTitle(tr("Create user group"));
	QMdiSubWindow *userGrWindow = new QMdiSubWindow;
	userGrWindow->setWidget(userGrDlg);
	userGrWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(userGrWindow);
	userGrDlg->show();
}
void DataForm::UdpUserGrDlg()
{
	CreateUserGrDlg *userGrDlg = new CreateUserGrDlg(dataFormBL, true, this);
	userGrDlg->setAttribute(Qt::WA_DeleteOnClose);
	userGrDlg->setWindowTitle(tr("Update user"));
	QMdiSubWindow *userGrWindow = new QMdiSubWindow;
	userGrWindow->setWidget(userGrDlg);
	userGrWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(userGrWindow);
	if (userGrDlg->FillDlgElements(tableView))
	{
		userGrDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelUserGrDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::UserGroupRelation userGr;
	userGr.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteUserGroupRelation(&userGr, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("User with this id does not exist!")),
			QString(tr("Ok")));
	}
}


void DataForm::CrtWdwDlg()
{
	CreateWdwDlg *withdrawalDlg = new CreateWdwDlg(dataFormBL, false, this);
	withdrawalDlg->setAttribute(Qt::WA_DeleteOnClose);
	withdrawalDlg->setWindowTitle(tr("Create withdrawal"));
	QMdiSubWindow *withdrawalWindow = new QMdiSubWindow;
	withdrawalWindow->setWidget(withdrawalDlg);
	withdrawalWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(withdrawalWindow);
	withdrawalDlg->show();
}
void DataForm::UdpWdwDlg()
{
	CreateWdwDlg *withdrawalDlg = new CreateWdwDlg(dataFormBL, true, this);
	withdrawalDlg->setAttribute(Qt::WA_DeleteOnClose);
	withdrawalDlg->setWindowTitle(tr("Update withdrawal"));
	QMdiSubWindow *withdrawalWindow = new QMdiSubWindow;
	withdrawalWindow->setWidget(withdrawalDlg);
	withdrawalWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(withdrawalWindow);
	if (withdrawalDlg->FillDlgElements(tableView))
	{
		withdrawalDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelWdwDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Withdrawal withdrawal;
	withdrawal.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteWithdrawal(&withdrawal, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Withdrawal with this id does not exist!")),
			QString(tr("Ok")));
	}
}


void DataForm::CrtWrhDlg()
{
	CreateWrhDlg *warehouseDlg = new CreateWrhDlg(dataFormBL, false, this);
	warehouseDlg->setAttribute(Qt::WA_DeleteOnClose);
	warehouseDlg->setWindowTitle(tr("Create warehouse"));
	QMdiSubWindow *warehouseWindow = new QMdiSubWindow;
	warehouseWindow->setWidget(warehouseDlg);
	warehouseWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(warehouseWindow);
	warehouseDlg->show();
}

void DataForm::UdpWrhDlg()
{
	CreateWrhDlg *warehouseDlg = new CreateWrhDlg(dataFormBL, true, this);
	warehouseDlg->setAttribute(Qt::WA_DeleteOnClose);
	warehouseDlg->setWindowTitle(tr("Update warehouse"));
	QMdiSubWindow *warehouseWindow = new QMdiSubWindow;
	warehouseWindow->setWidget(warehouseDlg);
	warehouseWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(warehouseWindow);
	if (warehouseDlg->FillDlgElements(tableView))
	{
		warehouseDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelWrhDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Warehouse warehouse;
	warehouse.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteWarehouse(&warehouse, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Warehouse with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtWrhTpDlg()
{
	CreateWrhTypeDlg *wTypeDlg = new CreateWrhTypeDlg(dataFormBL, false, this);
	wTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	wTypeDlg->setWindowTitle(tr("Create warehouse type"));
	QMdiSubWindow *wTypeWindow = new QMdiSubWindow;
	wTypeWindow->setWidget(wTypeDlg);
	wTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(wTypeWindow);
	wTypeDlg->show();
}
void DataForm::UdpWrhTpDlg()
{
	CreateWrhTypeDlg *wTypeDlg = new CreateWrhTypeDlg(dataFormBL, true, this);
	wTypeDlg->setAttribute(Qt::WA_DeleteOnClose);
	wTypeDlg->setWindowTitle(tr("Update warehouse type"));
	QMdiSubWindow *wTypeWindow = new QMdiSubWindow;
	wTypeWindow->setWidget(wTypeDlg);
	wTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(wTypeWindow);
	if (wTypeDlg->FillDlgElements(tableView))
	{
		wTypeDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelWrhTpDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::WarehouseType wType;
	wType.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteWarehouseType(&wType, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Warehouse type with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtWERDlg()
{
	CreateWERDlg *wRelDlg = new CreateWERDlg(dataFormBL, false, this);
	wRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	wRelDlg->setWindowTitle(tr("Create warehouse-employee relation"));
	QMdiSubWindow *wRelWindow = new QMdiSubWindow;
	wRelWindow->setWidget(wRelDlg);
	wRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(wRelWindow);
	wRelDlg->show();
}
void DataForm::UdpWERDlg()
{
	CreateWERDlg *wRelDlg = new CreateWERDlg(dataFormBL, true, this);
	wRelDlg->setAttribute(Qt::WA_DeleteOnClose);
	wRelDlg->setWindowTitle(tr("Update warehouse-employee relation"));
	QMdiSubWindow *wRelWindow = new QMdiSubWindow;
	wRelWindow->setWidget(wRelDlg);
	wRelWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(wRelWindow);
	if (wRelDlg->FillDlgElements(tableView))
	{
		wRelDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelWERDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::WarehouseEmployeeRelation wareRel;

	if (0 != id && wareRel.GetWarehouseEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		if (dataFormBL->DeleteWarehouseEmployeeRelation(&wareRel, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Warehouse-employee relation with this id does not exist!")),
			QString(tr("Ok")));
	}
}

void DataForm::ViewWdwDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::Withdrawal withdrawal;
	if (!withdrawal.GetWithdrawalByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::User user;
	BusinessLayer::Employee cashier;
	BusinessLayer::Employee accountant;
	BusinessLayer::Employee owner;
	BusinessLayer::Role role;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	BusinessLayer::CashboxTransaction cTransaction;

	if (cTransaction.GetCashboxTransactionByWithdrawalID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), withdrawal.GetID(), errorMessage))
	{
		if (!accountant.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), cTransaction.GetAccountantID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CHIEF ACCOUNTANT' employee!")),
				QString(tr("Ok")));
			return;
		}
		if (!cashier.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), cTransaction.GetCashierID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CASHIER' employee!")),
				QString(tr("Ok")));
			return;
		}
		if (!owner.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), cTransaction.GetOwnerID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'OWNER' employee!")),
				QString(tr("Ok")));
			return;
		}
	}
	else
	{

		if (0 == role.GetRoleIDByName(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), "CHIEF ACCOUNTANT", errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CHIEF ACCOUNTANT' role!")),
				QString(tr("Ok")));
			return;
		}

		accountant.SetRoleID(role.GetID());
		std::string empFilter = accountant.GenerateFilter(dataFormBL->GetOrmasDal());
		std::vector<BusinessLayer::EmployeeView> vecEmpRep = dataFormBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, empFilter);
		if (vecEmpRep.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CHIEF ACCOUNTANT' employee!")),
				QString(tr("Ok")));
			return;
		}
		else
		{
			accountant.SetName(vecEmpRep.at(0).GetName());
			accountant.SetSurname(vecEmpRep.at(0).GetSurname());
		}

		role.Clear();
		if (0 == role.GetRoleIDByName(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), "CASHIER", errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CASHIER' role!")),
				QString(tr("Ok")));
			return;
		}

		cashier.SetRoleID(role.GetID());
		std::string casFilter = cashier.GenerateFilter(dataFormBL->GetOrmasDal());
		std::vector<BusinessLayer::EmployeeView> vecCasRep = dataFormBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, casFilter);
		if (vecCasRep.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CASHIER' employee!")),
				QString(tr("Ok")));
			return;
		}
		else
		{
			cashier.SetName(vecCasRep.at(0).GetName());
			cashier.SetSurname(vecCasRep.at(0).GetSurname());
		}

		role.Clear();
		if (0 == role.GetRoleIDByName(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), "DIRECTOR", errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'OWNER' role!")),
				QString(tr("Ok")));
			return;
		}

		owner.SetRoleID(role.GetID());
		std::string ownFilter = owner.GenerateFilter(dataFormBL->GetOrmasDal());
		std::vector<BusinessLayer::EmployeeView> vecOwnRep = dataFormBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, ownFilter);
		if (vecOwnRep.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'OWNER' employee!")),
				QString(tr("Ok")));
			return;
		}
		else
		{
			owner.SetName(vecOwnRep.at(0).GetName());
			owner.SetSurname(vecOwnRep.at(0).GetSurname());
		}
	}
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), accountant.GetID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	
	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Consumption chash order"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/consumption.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();

	BusinessLayer::Account acc;
	if (!acc.GetAccountByNumber(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), "10110", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Can't find account!")),
			QString(tr("Ok")));
		return;
	}

	BusinessLayer::Balance balance;
	BusinessLayer::Subaccount subAcc;
	BusinessLayer::Currency currency;
	BusinessLayer::Account account;
	if (withdrawal.GetUserID() > 0)
	{
		balance.SetUserID(withdrawal.GetUserID());
		std::string filter = balance.GenerateFilter(dataFormBL->GetOrmasDal());
		std::vector<BusinessLayer::BalanceView> balanceVector = dataFormBL->GetAllDataForClass<BusinessLayer::BalanceView>(errorMessage, filter);
		if (0 < balanceVector.size())
		{
			for each (auto item in balanceVector)
			{
				subAcc.Clear();
				if (subAcc.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetSubaccountID(), errorMessage))
				{
					if (subAcc.GetParentAccountID() == withdrawal.GetAccountID())
					{
						balance.SetSubaccountID(subAcc.GetID());
					}
				}
			}
		}
		else
		{
			subAcc.Clear();
		}
		if (balance.GetSubaccountID() <= 0)
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Can't find subaccount for this withdrawal!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), withdrawal.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Can't find currency for this withdrawal!")),
				QString(tr("Ok")));
			return;
		}
		subAcc.Clear();
		if (!subAcc.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), balance.GetSubaccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Can't find subaccount for this user!")),
				QString(tr("Ok")));
			return;
		}
	}
	else if (withdrawal.GetAccountID()>0)
	{
		account.Clear();
		if (!account.GetAccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), withdrawal.GetAccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			return;
		}
	}
	else
	{
		subAcc.Clear();
		if (!subAcc.GetSubaccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), withdrawal.GetSubaccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			return;
		}
		if (!account.GetAccountByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), subAcc.GetParentAccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			return;
		}
	}

	//generating report
	reportText.replace(QString("ComNamePh"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("NumberPh"), QString::number(withdrawal.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(withdrawal.GetDate().c_str()), Qt::CaseInsensitive);
	if (withdrawal.GetUserID() > 0)
	{
		reportText.replace(QString("DebAccNumPh"), QString(subAcc.GetNumber().c_str()), Qt::CaseInsensitive);
	}
	else
	{
		reportText.replace(QString("DebAccNumPh"), QString(account.GetNumber().c_str()) , Qt::CaseInsensitive);
	}
	
	reportText.replace(QString("CredAccNumPh"), QString(acc.GetNumber().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(withdrawal.GetValue()), Qt::CaseInsensitive);
	reportText.replace(QString("ToWhoPh"), QString(withdrawal.GetWho().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("TargetPh"), QString(withdrawal.GetTarget().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("OwnerNamePh"), QString(owner.GetSurname().c_str()) + " " + QString(owner.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("AccounantNamePh"), QString(accountant.GetSurname().c_str()) + " " + QString(accountant.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("CashierPh"), QString(cashier.GetSurname().c_str()) + " " + QString(cashier.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtWOffDlg()
{
	CreateWOffDlg *writeOffDlg = new CreateWOffDlg(dataFormBL, false, this);
	writeOffDlg->setAttribute(Qt::WA_DeleteOnClose);
	writeOffDlg->setWindowTitle(tr("Create write-off"));
	QMdiSubWindow *writeOffWindow = new QMdiSubWindow;
	writeOffWindow->setWidget(writeOffDlg);
	writeOffWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(writeOffWindow);
	writeOffDlg->show();
}
void DataForm::UdpWOffDlg()
{
	CreateWOffDlg *writeOffDlg = new CreateWOffDlg(dataFormBL, true, this);
	writeOffDlg->setAttribute(Qt::WA_DeleteOnClose);
	writeOffDlg->setWindowTitle(tr("Update write-off"));
	QMdiSubWindow *writeOffWindow = new QMdiSubWindow;
	writeOffWindow->setWidget(writeOffDlg);
	writeOffWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(writeOffWindow);
	if (writeOffDlg->FillDlgElements(tableView))
	{
		writeOffDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelWOffDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::WriteOff writeOff;
	writeOff.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteWriteOff(&writeOff, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Write-off with this id does not exist!")),
			QString(tr("Ok")));

	}
}

void DataForm::ViewWOffDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::WriteOff wOff;
	if (!wOff.GetWriteOffByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::WriteOffList wOffList;
	BusinessLayer::Employee employee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), wOff.GetEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), wOff.GetEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/write_off.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	wOffList.SetWriteOffID(wOff.GetID());
	std::string filter = wOffList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::WriteOffListView> vecWOffList = dataFormBL->GetAllDataForClass<BusinessLayer::WriteOffListView>(errorMessage, filter);
	if (vecWOffList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(wOff.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(wOff.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	QString tableBody;
	double sum = 0;
	for each (auto item in vecWOffList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount() * product.GetPrice(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
		sum += item.GetCount() * product.GetPrice();
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(sum, 'f',3), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtWOffListDlg()
{
	CreateWOffListDlg *craeteWOffListDlg = new CreateWOffListDlg(dataFormBL, false, this);
	if (0 != writeOffID)
	{
		craeteWOffListDlg->writeOffID = writeOffID;
	}
	craeteWOffListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteWOffListDlg->setWindowTitle(tr("Add product to write-off list"));
	QMdiSubWindow *craeteWOffListWindow = new QMdiSubWindow;
	craeteWOffListWindow->setWidget(craeteWOffListDlg);
	craeteWOffListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteWOffListWindow);
	craeteWOffListDlg->show();
}
void DataForm::UdpWOffListDlg()
{
	CreateWOffListDlg *craeteWOffListDlg = new CreateWOffListDlg(dataFormBL, true, this);
	craeteWOffListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteWOffListDlg->setWindowTitle(tr("Update product in write-off list"));
	QMdiSubWindow *craeteWOffListWindow = new QMdiSubWindow;
	craeteWOffListWindow->setWidget(craeteWOffListDlg);
	craeteWOffListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteWOffListWindow);
	if (craeteWOffListDlg->FillDlgElements(tableView))
	{
		craeteWOffListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelWOffListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::WriteOffList writeOffList;
	writeOffList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteWriteOffList(&writeOffList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Product with this id does not exist in write-off list!")),
			QString(tr("Ok")));
	}
}

void DataForm::CrtWOffRDlg()
{
	CreateWOffRDlg *writeOffRDlg = new CreateWOffRDlg(dataFormBL, false, this);
	writeOffRDlg->setAttribute(Qt::WA_DeleteOnClose);
	writeOffRDlg->setWindowTitle(tr("Create write-off raw"));
	QMdiSubWindow *writeOffRWindow = new QMdiSubWindow;
	writeOffRWindow->setWidget(writeOffRDlg);
	writeOffRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(writeOffRWindow);
	writeOffRDlg->show();
}
void DataForm::UdpWOffRDlg()
{
	CreateWOffRDlg *writeOffRDlg = new CreateWOffRDlg(dataFormBL, true, this);
	writeOffRDlg->setAttribute(Qt::WA_DeleteOnClose);
	writeOffRDlg->setWindowTitle(tr("Update write-off raw"));
	QMdiSubWindow *writeOffRWindow = new QMdiSubWindow;
	writeOffRWindow->setWidget(writeOffRDlg);
	writeOffRWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(writeOffRWindow);
	if (writeOffRDlg->FillDlgElements(tableView))
	{
		writeOffRDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelWOffRDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::WriteOffRaw writeOffRaw;
	writeOffRaw.SetID(id);
	if (0 != id)
	{
		dataFormBL->StartTransaction(errorMessage);
		if (dataFormBL->DeleteWriteOffRaw(&writeOffRaw, errorMessage))
		{
			dataFormBL->CommitTransaction(errorMessage);
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			dataFormBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Write-off raw with this id does not exist!")),
			QString(tr("Ok")));

	}
}

void DataForm::ViewWOffRDlg()
{
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::WriteOffRaw wOffRaw;
	if (!wOffRaw.GetWriteOffRawByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), id, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::WriteOffRawList wOffRawList;
	BusinessLayer::Employee employee;
	BusinessLayer::Company company;
	BusinessLayer::CompanyEmployeeRelation ceRel;
	int companyID = 0;
	companyID = ceRel.GetCompanyByEmployeeID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), wOffRaw.GetStockEmployeeID(), errorMessage);
	if (!company.GetCompanyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), companyID, errorMessage) || 0 == companyID)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}
	if (!employee.GetEmployeeByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), wOffRaw.GetStockEmployeeID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Connot show information for this row!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dataFormBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print report"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/write_off.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	wOffRawList.SetWriteOffRawID(wOffRaw.GetID());
	std::string filter = wOffRawList.GenerateFilter(dataFormBL->GetOrmasDal());
	std::vector<BusinessLayer::WriteOffRawListView> vecWOffRawList = dataFormBL->GetAllDataForClass<BusinessLayer::WriteOffRawListView>(errorMessage, filter);
	if (vecWOffRawList.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("List is empty!")),
			QString(tr("Ok")));
		return;
	}

	//generating report
	reportText.replace(QString("NumberPh"), QString::number(wOffRaw.GetID()), Qt::CaseInsensitive);
	reportText.replace(QString("DatePh"), QString(wOffRaw.GetDate().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("ComName1Ph"), QString(company.GetName().c_str()), Qt::CaseInsensitive);
	reportText.replace(QString("UserName1Ph"), QString(employee.GetSurname().c_str()) + " " + QString(employee.GetName().c_str()), Qt::CaseInsensitive);
	int i = 1;
	BusinessLayer::Product product;
	BusinessLayer::Measure measure;
	BusinessLayer::Currency currency;
	BusinessLayer::NetCost netCost;
	QString tableBody;
	for each (auto item in vecWOffRawList)
	{
		product.Clear();
		measure.Clear();
		currency.Clear();
		netCost.Clear();
		if (!product.GetProductByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), item.GetProductID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Product is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!measure.GetMeasureByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Measure is wrong!")),
				QString(tr("Ok")));
			return;
		}
		if (!currency.GetCurrencyByID(dataFormBL->globalVar, dataFormBL->GetOrmasDal(), product.GetCurrencyID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Currency is wrong!")),
				QString(tr("Ok")));
			return;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(i) + "</td>";
		tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
		tableBody += "<td>" + QString(measure.GetShortName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum() / item.GetCount(), 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(item.GetSum()) + "</td>";
		tableBody += "<td>" + QString(currency.GetShortName().c_str()) + "</td>";
		tableBody += "</tr>";
		i++;
	}
	reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
	reportText.replace(QString("SumPh"), QString::number(wOffRaw.GetSum()), Qt::CaseInsensitive);
	reportText.replace(QString("CurrencyPh"), QString(currency.GetShortName().c_str()), Qt::CaseInsensitive);

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
}

void DataForm::CrtWOffRListDlg()
{
	CreateWOffRListDlg *craeteWOffRListDlg = new CreateWOffRListDlg(dataFormBL, false, this);
	if (0 != writeOffRawID)
	{
		craeteWOffRListDlg->writeOffRawID = writeOffRawID;
	}
	craeteWOffRListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteWOffRListDlg->setWindowTitle(tr("Add raw to write-off list"));
	QMdiSubWindow *craeteWOffRListWindow = new QMdiSubWindow;
	craeteWOffRListWindow->setWidget(craeteWOffRListDlg);
	craeteWOffRListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteWOffRListWindow);
	craeteWOffRListDlg->show();
}
void DataForm::UdpWOffRListDlg()
{
	CreateWOffRListDlg *craeteWOffRListDlg = new CreateWOffRListDlg(dataFormBL, true, this);
	craeteWOffRListDlg->setAttribute(Qt::WA_DeleteOnClose);
	craeteWOffRListDlg->setWindowTitle(tr("Update raw in write-off list"));
	QMdiSubWindow *craeteWOffRListWindow = new QMdiSubWindow;
	craeteWOffRListWindow->setWidget(craeteWOffRListDlg);
	craeteWOffRListWindow->setAttribute(Qt::WA_DeleteOnClose);
	((MainForm*)parentForm)->mdiArea->addSubWindow(craeteWOffRListWindow);
	if (craeteWOffRListDlg->FillDlgElements(tableView))
	{
		craeteWOffRListDlg->show();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select one row at first!")),
			QString(tr("Ok")));
	}
}
void DataForm::DelWOffRListDlg()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	int id = GetIDFromTable(tableView, errorMessage);
	BusinessLayer::WriteOffRawList writeOffRawList;
	writeOffRawList.SetID(id);
	if (0 != id)
	{
		if (dataFormBL->DeleteWriteOffRawList(&writeOffRawList, errorMessage))
		{
			tableView->model()->removeRow(tableView->selectionModel()->currentIndex().row());
			ChangeBtnState();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Wrong id, cannot delete data from this row!")),
			QString(tr("Ok")));
	}
}

// Template specializations for generating headers of table ------------------------------
template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Account>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Number") << QObject::tr("Start balance") << QObject::tr("Current balance")
	 << QObject::tr("Details");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::AccountType>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Type name") << QObject::tr("Type number") << QObject::tr("Comment");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::AccountableView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Information")
		<< QObject::tr("Employee phone") << QObject::tr("Employee address") << QObject::tr("Role name");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::AccountableDocument>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Document date") << QObject::tr("Value") << QObject::tr("Expense assignment")
		<< QObject::tr("Accountable ID") << QObject::tr("Status ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::AccessView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Role name") << QObject::tr("Item english name") << QObject::tr("Item russian name") 
		<< QObject::tr("Division") << QObject::tr("Role ID") << QObject::tr("Access item ID");
	return header;
}
template<>
QStringList DataForm::GetTableHeader<BusinessLayer::AccessItem>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Item english name") << QObject::tr("Item russian name") << QObject::tr("Division");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::AmortizeGroup>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Group number") << QObject::tr("From month") << QObject::tr("To month");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::AmortizeType>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Code");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::BalanceView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("User name") << QObject::tr("User surname") << QObject::tr("Subaccount number")
		<< QObject::tr("Current balance") << QObject::tr("Currency name") << QObject::tr("User ID") << QObject::tr("Account ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Branch>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Branch name") << QObject::tr("Branch address") << QObject::tr("Branch phone")
		<< QObject::tr("Commnet");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::BranchSubaccountRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Branch name") << QObject::tr("Subaccount number") << QObject::tr("Branch ID")
		<< QObject::tr("Subaccount ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::BorrowerView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("User name") << QObject::tr("User surname") << QObject::tr("Comment")
		<< QObject::tr("User phone") << QObject::tr("User address")  << QObject::tr("Role name")
		<< QObject::tr("Password") << QObject::tr("User email") << QObject::tr("Activated") << QObject::tr("Role ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::CashboxView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Subaccount number") << QObject::tr("Information") << QObject::tr("Cashbox address")
		<< QObject::tr("Subaccount ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::CashboxEmployeeRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Subaccount number") << QObject::tr("Cashbox address") << QObject::tr("User name")
		<< QObject::tr("User surname") << QObject::tr("User phone") << QObject::tr("Role name") << QObject::tr("Cashbox ID")
		<< QObject::tr("Employee ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ChartOfAccountsView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Number") << QObject::tr("Name") << QObject::tr("Type name")
		<< QObject::tr("Account type ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ClientView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Surname") << QObject::tr("Phone") << QObject::tr("Country name")
		<< QObject::tr("Region name") << QObject::tr("City name") << QObject::tr("Address") << QObject::tr("Firm") 
		<< QObject::tr("Firm number") << QObject::tr("Role name") << QObject::tr("Password") << QObject::tr("Email")
		<< QObject::tr("Avtivated") << QObject::tr("Role ID") << QObject::tr("Location ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Company>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Address") << QObject::tr("Phone") << QObject::tr("Comment");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::CompanyAccountRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Company name") << QObject::tr("Account number") 
		<< QObject::tr("Company ID") << QObject::tr("Account ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::CompanyEmployeeRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Company name") << QObject::tr("Branch name") << QObject::tr("Employee name") << QObject::tr("Employee surname")
		<< QObject::tr("Employee Phone") << QObject::tr("Company ID") << QObject::tr("Employee ID") << QObject::tr("Branch ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ConsumeProductView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Consume date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ConsumeProductListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Consume ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ConsumeRawView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Consume raw date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ConsumeRawListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Consume raw ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ConsumeOtherStocksView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Consume raw date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ConsumeOtherStocksListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Consume raw ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}


template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Currency>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Code") << QObject::tr("Short name") << QObject::tr("Name") 
		<< QObject::tr("Change unit") << QObject::tr("Main trade currency");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Division>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Code");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::DivisionAccountRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Division name") << QObject::tr("Account number") << QObject::tr("Account name")
		<< QObject::tr("Code") << QObject::tr("Division ID") << QObject::tr("Account ID");
	return header;
}


template<>
QStringList DataForm::GetTableHeader<BusinessLayer::EmployeeView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Surname") << QObject::tr("Position name") 
		<< QObject::tr("Phone") << QObject::tr("Address") << QObject::tr("Birth date") << QObject::tr("Role name") 
		<< QObject::tr("Hire date") << QObject::tr("Password") << QObject::tr("Email")
		<< QObject::tr("Avtivated") << QObject::tr("Role ID") << QObject::tr("Position ID")
		<< QObject::tr("Division-Employee-ID") << QObject::tr("Division ID") << QObject::tr("Is contract?");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::EmployeeProductRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Surname") 
		<< QObject::tr("Phone") << QObject::tr("Product name") << QObject::tr("Price") << QObject::tr("Employee ID")
		<< QObject::tr("Product ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::EntryView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Debiting account number") << QObject::tr("Value")
		<< QObject::tr("Crediting account number") << QObject::tr("Debiting account ID") << QObject::tr("Crediting account ID")
		<< QObject::tr("Description");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::EntryRouting>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Operation") << QObject::tr("Debit") 
		<< QObject::tr("Credit");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::FixedAssetsView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Fixed assets name") << QObject::tr("Inventory number") << QObject::tr("Primary cost")
		<< QObject::tr("Stop cost") << QObject::tr("Start primary value") << QObject::tr("Amortize value") << QObject::tr("Division name")
		<< QObject::tr("Status name") << QObject::tr("Service life") << QObject::tr("Is amortize?") << QObject::tr("Buy date") << QObject::tr("Start of operation date")
		<< QObject::tr("End of operation date") << QObject::tr("Specification ID") << QObject::tr("Status ID") << QObject::tr("Details ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::FixedAssetsSpecification>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Factory number") << QObject::tr("Document")
		<< QObject::tr("Object characters") << QObject::tr("Condition") << QObject::tr("Developer") << QObject::tr("Construction date");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::FixedAssetsOperations>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Name") << QObject::tr("Value")
		<< QObject::tr("Increment") << QObject::tr("Decrement") << QObject::tr("Fixed assets ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::InventoryView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Cost") << QObject::tr("Inventory number")
		<< QObject::tr("Barcode number") << QObject::tr("Division name") << QObject::tr("Staus name")
		<< QObject::tr("Location") << QObject::tr("Start of operation date") << QObject::tr("End of operation date")
		<< QObject::tr("Status ID") << QObject::tr("Department ID") << QObject::tr("Subaccount ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::InventorizationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Inventorization date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::InventorizationListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Inventorization ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Group>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Group name") << QObject::tr("Definition");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::JobpriceView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Product name") << QObject::tr("Value")
		<< QObject::tr("Currnecy name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Position name")
		<< QObject::tr("Product ID") << QObject::tr("Currency ID") << QObject::tr("Measure ID") 
		<< QObject::tr("Position ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::JobsheetView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("User name")
		<< QObject::tr("User surname") << QObject::tr("User phone") << QObject::tr("Product name") << QObject::tr("Count")
		<< QObject::tr("Measure name") << QObject::tr("Product ID") << QObject::tr("Employee ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::LowValueStockView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Warehouse name") << QObject::tr("Subaccount number")
		<< QObject::tr("Status name") << QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Warehouse ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Location>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Country name") << QObject::tr("Country code") 
		<< QObject::tr("Region name") << QObject::tr("City name");
	return header;
}


template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Measure>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Short name") << QObject::tr("Change unit");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::NetCostView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Product name") << QObject::tr("Volume") << QObject::tr("Measure name")
		<< QObject::tr("Value") << QObject::tr("Currency name") << QObject::tr("Currency ID") << QObject::tr("Product ID") << QObject::tr("Is outdated?");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::OrderView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Order date") << QObject::tr("Execution date") << QObject::tr("Status code") 
		<< QObject::tr("Status name") << QObject::tr("Client name") << QObject::tr("Client surname") << QObject::tr("Client phone") 
		<< QObject::tr("Client address") << QObject::tr("Client firm") << QObject::tr("Employee name") << QObject::tr("Employee surname")
		<< QObject::tr("Employee phone") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name") 
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID") 
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::OrderListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Order ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count") 
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::OrderRawView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Order raw date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Purveyor name") << QObject::tr("Purveyor surname") << QObject::tr("Purveyor phone")
		<< QObject::tr("Purveyor company name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Purveyor ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::OrderRawListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Order raw ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::PercentRate>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Value") << QObject::tr("Condition") << QObject::tr("Position ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Photo>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("User ID") << QObject::tr("Product ID") << QObject::tr("Source");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::OtherStocksView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Price") << QObject::tr("Currency name") << QObject::tr("Volume")
		<< QObject::tr("Measure name") << QObject::tr("Company name")
		<< QObject::tr("Company ID") << QObject::tr("Measure ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::OtherStocksType>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Short name") << QObject::tr("Code");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::PaymentView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("User name") << QObject::tr("User surname") 
		<< QObject::tr("User Phone") << QObject::tr("Value") << QObject::tr("Currency name") << QObject::tr("Target")
		<< QObject::tr("Account number") << QObject::tr("Subccount number") << QObject::tr("From who") << QObject::tr("Status name") 
		<< QObject::tr("User ID") << QObject::tr("Currency ID") << QObject::tr("Status ID") << QObject::tr("Account ID") << QObject::tr("Subaccount ID")
		<< QObject::tr("Cashbox account ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Position>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name");
	return header;
}


template<>
QStringList DataForm::GetTableHeader<BusinessLayer::PriceView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Product name") << QObject::tr("Volume") << QObject::tr("Measure name")
		<< QObject::tr("Value") << QObject::tr("Currency name") << QObject::tr("Currency ID") << QObject::tr("Product ID") << QObject::tr("Is outdated?");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ProductType>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Short name") << QObject::tr("Code");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ProductView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Price") << QObject::tr("Currency name") << QObject::tr("Volume") 
		<< QObject::tr("Measure name") << QObject::tr("Product type name") << QObject::tr("Shelf life") << QObject::tr("Company name") 
		<< QObject::tr("Company ID") << QObject::tr("Measure ID") << QObject::tr("Product type ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ProductBranchRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Address") << QObject::tr("Product name") 
		<< QObject::tr("Price") << QObject::tr("Product id") << QObject::tr("Branch ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Production>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Production Date") << QObject::tr("Expiry Date") << QObject::tr("Session start") 
		<< QObject::tr("Session end") << QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ProductionListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Production ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ProductionConsumeRawView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Consume raw date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ProductionConsumeRawListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Consume raw ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ProductionPlanView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname")
		<< QObject::tr("Employee phone") << QObject::tr("Employee position") << QObject::tr("Employee ID") << QObject::tr("Status ID") 
		<< QObject::tr("Currency ID") << QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ProductionPlanListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Production plan ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::PayslipView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Value") << QObject::tr("Currency name") 
		<< QObject::tr("Salary ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::PurveyorView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Surname") << QObject::tr("Phone") << QObject::tr("Country name")
		<< QObject::tr("Region name") << QObject::tr("City name") << QObject::tr("Address") << QObject::tr("Company name")
		<< QObject::tr("Role name") << QObject::tr("Password") << QObject::tr("Email")
		<< QObject::tr("Avtivated") << QObject::tr("Role ID") << QObject::tr("Location ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ReceiptOtherStocksView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Receipt date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ReceiptOtherStocksListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Receipt ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ReceiptProductView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Receipt date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ReceiptProductListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Receipt ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::StockTransferView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Receipt date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::StockTransferListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Receipt raw ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}
template<>
QStringList DataForm::GetTableHeader<BusinessLayer::RelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("User 1 name") << QObject::tr("User 1 surname") << QObject::tr("User 1 Phone") 
		<< QObject::tr("Relation type name") << QObject::tr("User 2 name") << QObject::tr("User 2 surname") 
		<< QObject::tr("User 2 Phone") << QObject::tr("User 1") << QObject::tr("User 2") << QObject::tr("Relation type");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::RelationType>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Comment");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ReturnView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Return date") << QObject::tr("Execution date") << QObject::tr("Status code") 
		<< QObject::tr("Status name") << QObject::tr("Client name") << QObject::tr("Client surname")
		<< QObject::tr("Client phone") << QObject::tr("Client address") << QObject::tr("Client firm") << QObject::tr("Employee name")
		<< QObject::tr("Employee surname") << QObject::tr("Employee phone") << QObject::tr("Product count") << QObject::tr("Sum")
		<< QObject::tr("Currency name") << QObject::tr("Employee ID") << QObject::tr("Client ID")
		<< QObject::tr("Status ID") << QObject::tr("Currency ID") << QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::ReturnListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Return ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count") 
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::RefundView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Value") << QObject::tr("Currency name") << QObject::tr("User ID") 
		<< QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Role>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Code") << QObject::tr("Name") << QObject::tr("Comment");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::SalaryType>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Code") << QObject::tr("Name");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::SalaryView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("User ID") << QObject::tr("Employee name") << QObject::tr("Employee surname") 
		<< QObject::tr("Employee phone") << QObject::tr("Date") << QObject::tr("Value") << QObject::tr("Currency name") 
		<< QObject::tr("Salary type name") << QObject::tr("Currency ID") << QObject::tr("Salary type ID") << QObject::tr("Is bonus?");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::Status>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Code") << QObject::tr("Name") << QObject::tr("Comment");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::StatusRuleView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Operation") << QObject::tr("Status name") << QObject::tr("Status ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::SpecificationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Product name")
		<< QObject::tr("Sum") << QObject::tr("Currnecy name") << QObject::tr("Employee name") << QObject::tr("Employee surname")
		<< QObject::tr("Employee phone") << QObject::tr("Employee position") << QObject::tr("Product ID")
		<< QObject::tr("Currency ID") << QObject::tr("Employee ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::SpecificationListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Specification ID") << QObject::tr("Product name")
		<< QObject::tr("Count") << QObject::tr("Measure name") << QObject::tr("Product ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::SpoilageView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname")
		<< QObject::tr("Employee phone") << QObject::tr("Employee position") << QObject::tr("Employee ID") << QObject::tr("Status ID")
		<< QObject::tr("Currency ID") << QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::SpoilageListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Spoilage ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::StockView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Warehouse name") << QObject::tr("Subaccount number")
		<< QObject::tr("Status name") << QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Warehouse ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::StockLimitView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Warehouse name") << QObject::tr("Product name")
		<< QObject::tr("Minimum value") << QObject::tr("Maximum value") << QObject::tr("Stock ID") << QObject::tr("Product ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::SubaccountView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Parent account ID") << QObject::tr("Parent account Number") << QObject::tr("Number") 
		<< QObject::tr("Start balance") << QObject::tr("Current balance")
		<< QObject::tr("Currency name") << QObject::tr("Status name") << QObject::tr("Currency ID") << QObject::tr("Status ID")
		<< QObject::tr("Opened date") << QObject::tr("Closed date") << QObject::tr("Details");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::SubaccountLimitView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Subaccount number") << QObject::tr("Subaccount ID") << QObject::tr("Minimum value")
		<< QObject::tr("Maximum value");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::TimesheetView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Date") << QObject::tr("Worked time") << QObject::tr("Salary ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::TransportView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Transportation date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("User name") << QObject::tr("User surname") << QObject::tr("User phone")
		<< QObject::tr("Userposition") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::TransportListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Transport ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}


template<>
QStringList DataForm::GetTableHeader<BusinessLayer::UserView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Email") << QObject::tr("Name") << QObject::tr("Surname") << QObject::tr("Phone") 
		<< QObject::tr("Address") << QObject::tr("Role name") << QObject::tr("Password") << QObject::tr("Avtivated") << QObject::tr("Role ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::UserExtendedView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Name") << QObject::tr("Surname") << QObject::tr("Phone") << QObject::tr("Address") << QObject::tr("Company name")
		<< QObject::tr("Branch name") << QObject::tr("Role name") << QObject::tr("Subaccount number") << QObject::tr("Role ID") << QObject::tr("Subaccount ID") 
		<< QObject::tr("Account ID") << QObject::tr("Company ID") << QObject::tr("Branch ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::UserGroupRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Group name") << QObject::tr("User surname") << QObject::tr("User name")
		<< QObject::tr("Role ID") << QObject::tr("Group ID") << QObject::tr("User ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::WarehouseView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Warehouse name") << QObject::tr("Subaccount number") << QObject::tr("Type name")
		<< QObject::tr("Warehouse address") << QObject::tr("Warehouse phone") << QObject::tr("Warehouse type ID") 
		<< QObject::tr("Subaccount ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::WarehouseType>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Type code") << QObject::tr("Type purpose") << QObject::tr("Type name");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::WarehouseEmployeeRelationView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("User name") << QObject::tr("User surname") << QObject::tr("User phone")
		<< QObject::tr("Role name") << QObject::tr("Warehouse name") << QObject::tr("Subaccount number")
		<< QObject::tr("Warehouse ID") << QObject::tr("Employee ID");
	return header;
}


template<>
QStringList DataForm::GetTableHeader<BusinessLayer::WithdrawalView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Date") << QObject::tr("Value") << QObject::tr("Currency name") 
		<< QObject::tr("User name") << QObject::tr("User surname") << QObject::tr("User phone") << QObject::tr("Status name") << QObject::tr("Account number")
		<< QObject::tr("Subaccount number") << QObject::tr("To who") << QObject::tr("Target") << QObject::tr("User ID") << QObject::tr("Currency ID")
		<< QObject::tr("Subaccount ID") << QObject::tr("Status ID") << QObject::tr("Account ID") << QObject::tr("Cashbox account ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::WriteOffView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Write-off date") << QObject::tr("Execution date") << QObject::tr("Status code") << QObject::tr("Status name")
		<< QObject::tr("Client name") << QObject::tr("Client surname") << QObject::tr("Client phone") << QObject::tr("Client address")
		<< QObject::tr("Client firm") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone") 
		<< QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name") << QObject::tr("Employee ID")
		<< QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID") << QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::WriteOffListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Write-off ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count") << QObject::tr("Sum") 
		<< QObject::tr("Sum currency name") << QObject::tr("Status name") << QObject::tr("Product ID") << QObject::tr("Status ID") 
		<< QObject::tr("Currency ID");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::WriteOffRawView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Write-off date") << QObject::tr("Execution date") << QObject::tr("Status code")
		<< QObject::tr("Status name") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Employee name") << QObject::tr("Employee surname") << QObject::tr("Employee phone")
		<< QObject::tr("Employee position") << QObject::tr("Product count") << QObject::tr("Sum") << QObject::tr("Currency name")
		<< QObject::tr("Employee ID") << QObject::tr("Client ID") << QObject::tr("Status ID") << QObject::tr("Currency ID")
		<< QObject::tr("Product list");
	return header;
}

template<>
QStringList DataForm::GetTableHeader<BusinessLayer::WriteOffRawListView>()
{
	QStringList header;
	header << QObject::tr("ID") << QObject::tr("Write-off raw ID") << QObject::tr("Product name") << QObject::tr("Price")
		<< QObject::tr("Currency name") << QObject::tr("Volume") << QObject::tr("Measure name") << QObject::tr("Count")
		<< QObject::tr("Sum") << QObject::tr("Sum currency name") << QObject::tr("Status name")
		<< QObject::tr("Product ID") << QObject::tr("Status ID") << QObject::tr("Currency ID");
	return header;
}


// Template specializations for generating data ---------------------------------------------------------------------------
template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Account>(BusinessLayer::Account& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetNumber().c_str())
		<< new QStandardItem(QString::number(data.GetStartBalance(), 'f', 3))
		<< new QStandardItem(QString::number(data.GetCurrentBalance(), 'f', 3));
	return items;
}

// Template specializations for generating data ---------------------------------------------------------------------------
template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::AccountableView>(BusinessLayer::AccountableView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetSurname().c_str())
		<< new QStandardItem(data.GetInformation().c_str())
		<< new QStandardItem(data.GetPhone().c_str())
		<< new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(data.GetRoleName().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::AccountableDocument>(BusinessLayer::AccountableDocument& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(QString::number(data.GetValue(), 'f', 3))
		<< new QStandardItem(data.GetExpenseAssignment().c_str())
		<< new QStandardItem(QString::number(data.GetAccountableID()))
		<< new QStandardItem(QString::number(data.GetStatusID()));
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::AccountType>(BusinessLayer::AccountType& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(QString::number(data.GetNumber())) << new QStandardItem(data.GetComment().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::AccessView>(BusinessLayer::AccessView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) 
		<< new QStandardItem(data.GetRoleName().c_str())
		<< new QStandardItem(data.GetAccessItemEng().c_str())
		<< new QStandardItem(data.GetAccessItemRu().c_str())
		<< new QStandardItem(data.GetDivision().c_str())
		<< new QStandardItem(QString::number(data.GetRoleID()))
		<< new QStandardItem(QString::number(data.GetAccessItemID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::AccessItem>(BusinessLayer::AccessItem& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetNameEng().c_str())
		<< new QStandardItem(data.GetNameRu().c_str()) << new QStandardItem(data.GetDivision().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::AmortizeGroup>(BusinessLayer::AmortizeGroup& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(QString::number(data.GetGroupNumber()))
		<< new QStandardItem(QString::number(data.GetFromMonth())) << new QStandardItem(QString::number(data.GetToMonth()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::AmortizeType>(BusinessLayer::AmortizeType& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetCode().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::BalanceView>(BusinessLayer::BalanceView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(QString::number(data.GetCurrentBalance(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetUserID()))
		<< new QStandardItem(QString::number(data.GetSubaccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Branch>(BusinessLayer::Branch& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(data.GetPhone().c_str())
		<< new QStandardItem(data.GetComment().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::BranchSubaccountRelationView>(BusinessLayer::BranchSubaccountRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetBranchName().c_str())
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(QString::number(data.GetBranchID()))
		<< new QStandardItem(QString::number(data.GetSubaccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::BorrowerView>(BusinessLayer::BorrowerView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetUserID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetSurname().c_str())
		<< new QStandardItem(data.GetComment().c_str())
		<< new QStandardItem(data.GetPhone().c_str())
		<< new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(data.GetRoleName().c_str())
		<< new QStandardItem(data.GetPassword().c_str())
		<< new QStandardItem(data.GetEmail().c_str())
		<< new QStandardItem(data.GetActivated() ? "true" : "false")
		<< new QStandardItem(QString::number(data.GetRoleID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::CashboxView>(BusinessLayer::CashboxView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(data.GetInformation().c_str())
		<< new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(QString::number(data.GetSubaccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::CashboxEmployeeRelationView>(BusinessLayer::CashboxEmployeeRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(data.GetCashboxAddress().c_str())
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(data.GetRoleName().c_str())
		<< new QStandardItem(QString::number(data.GetCashboxID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ChartOfAccountsView>(BusinessLayer::ChartOfAccountsView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetNumber().c_str())
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetAccountTypeName().c_str())
		<< new QStandardItem(QString::number(data.GetAccountTypeID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ClientView>(BusinessLayer::ClientView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetSurname().c_str())
		<< new QStandardItem(data.GetPhone().c_str())
		<< new QStandardItem(data.GetCountryName().c_str())
		<< new QStandardItem(data.GetRegionName().c_str())
		<< new QStandardItem(data.GetCityName().c_str())
		<< new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(data.GetFirm().c_str())
		<< new QStandardItem(data.GetFirmNumber().c_str())
		<< new QStandardItem(data.GetRoleName().c_str())
		<< new QStandardItem(data.GetPassword().c_str())
		<< new QStandardItem(data.GetEmail().c_str())
		<< new QStandardItem(data.GetActivated() ? "true" : "false")
		<< new QStandardItem(QString::number(data.GetRoleID()))
		<< new QStandardItem(QString::number(data.GetLocationID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Company>(BusinessLayer::Company& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetAddress().c_str()) << new QStandardItem(data.GetPhone().c_str())
		<< new QStandardItem(data.GetComment().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::CompanyAccountRelationView>(BusinessLayer::CompanyAccountRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetCompanyName().c_str())
		<< new QStandardItem(data.GetAccountNumber().c_str())
		<< new QStandardItem(QString::number(data.GetCompanyID())) 
		<< new QStandardItem(QString::number(data.GetAccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::CompanyEmployeeRelationView>(BusinessLayer::CompanyEmployeeRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetCompanyName().c_str())
		<< new QStandardItem(data.GetBranchName().c_str())
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(QString::number(data.GetCompanyID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetBranchID()));
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ConsumeProductView>(BusinessLayer::ConsumeProductView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(data.GetStockEmployeeName().c_str())
		<< new QStandardItem(data.GetStockEmployeeSurname().c_str())
		<< new QStandardItem(data.GetStockEmployeePhone().c_str())
		<< new QStandardItem(data.GetStockEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetStockEmployeeID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ConsumeProductListView>(BusinessLayer::ConsumeProductListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetConsumeProductID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ConsumeRawView>(BusinessLayer::ConsumeRawView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(data.GetStockEmployeeName().c_str())
		<< new QStandardItem(data.GetStockEmployeeSurname().c_str())
		<< new QStandardItem(data.GetStockEmployeePhone().c_str())
		<< new QStandardItem(data.GetStockEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetStockEmployeeID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ConsumeRawListView>(BusinessLayer::ConsumeRawListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetConsumeRawID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ConsumeOtherStocksView>(BusinessLayer::ConsumeOtherStocksView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(data.GetStockEmployeeName().c_str())
		<< new QStandardItem(data.GetStockEmployeeSurname().c_str())
		<< new QStandardItem(data.GetStockEmployeePhone().c_str())
		<< new QStandardItem(data.GetStockEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetStockEmployeeID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ConsumeOtherStocksListView>(BusinessLayer::ConsumeOtherStocksListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetConsumeOtherStocksID()))
		<< new QStandardItem(data.GetOtherStocksName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetOtherStocksID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Currency>(BusinessLayer::Currency& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(QString::number(data.GetCode()))
		<< new QStandardItem(data.GetShortName().c_str()) << new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(QString::number(data.GetUnit())) << new QStandardItem(data.GetMainTrade()?"true":"false");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Division>(BusinessLayer::Division& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str()) << new QStandardItem(data.GetCode().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::DivisionAccountRelationView>(BusinessLayer::DivisionAccountRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDivisionName().c_str()) 
		<< new QStandardItem(data.GetAccountNumber().c_str())
		<< new QStandardItem(data.GetAccountName().c_str())
		<< new QStandardItem(data.GetCode().c_str())
		<< new QStandardItem(QString::number(data.GetDivisionID()))
		<< new QStandardItem(QString::number(data.GetAccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::EmployeeView>(BusinessLayer::EmployeeView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetSurname().c_str())
		<< new QStandardItem(data.GetPositionName().c_str())
		<< new QStandardItem(data.GetPhone().c_str())
		<< new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(data.GetBirthDate().c_str())
		<< new QStandardItem(data.GetRoleName().c_str())
		<< new QStandardItem(data.GetHireDate().c_str())
		<< new QStandardItem(data.GetPassword().c_str())
		<< new QStandardItem(data.GetEmail().c_str())
		<< new QStandardItem(data.GetActivated() ? "true" : "false")
		<< new QStandardItem(QString::number(data.GetRoleID()))
		<< new QStandardItem(QString::number(data.GetPositionID()))
		<< new QStandardItem(QString::number(data.GetDivisionEmployeeID()))
		<< new QStandardItem(QString::number(data.GetDivisionID()))
		<< new QStandardItem(data.GetIsContract() ? "true" : "false");
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::EmployeeProductRelationView>(BusinessLayer::EmployeeProductRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice(), 'f', 2))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetProductID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::EntryView>(BusinessLayer::EntryView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetDebitingAccountNumber().c_str())
		<< new QStandardItem(QString::number(data.GetValue(), 'f', 3))
		<< new QStandardItem(data.GetCreditingAccountNumber().c_str())
		<< new QStandardItem(QString::number(data.GetDebitingAccountID()))
		<< new QStandardItem(QString::number(data.GetCreditingAccountID()))
		<< new QStandardItem(data.GetDescription().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::EntryRouting>(BusinessLayer::EntryRouting& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetOperation().c_str())
		<< new QStandardItem(QString::number(data.GetDebitAccountID()))
		<< new QStandardItem(QString::number(data.GetCreditAccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::FixedAssetsView>(BusinessLayer::FixedAssetsView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetInventoryNumber().c_str())
		<< new QStandardItem(QString::number(data.GetPrimaryCost(), 'f', 3))
		<< new QStandardItem(QString::number(data.GetStopCost(), 'f', 3))
		<< new QStandardItem(QString::number(data.GetPrimaryCostValue(), 'f', 3))
		<< new QStandardItem(QString::number(data.GetAmortizeValue(), 'f', 3))
		<< new QStandardItem(data.GetDivisionName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetServiceLife()))
		<< new QStandardItem(data.GetIsAmortize() ? "true" : "false")
		<< new QStandardItem(data.GetBuyDate().c_str())
		<< new QStandardItem(data.GetStartOfOperationDate().c_str())
		<< new QStandardItem(data.GetEndOfOperationDate().c_str())
		<< new QStandardItem(QString::number(data.GetSpecificationID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetFixedAssetsDetailsID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::FixedAssetsSpecification>(BusinessLayer::FixedAssetsSpecification& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetFactoryNumber().c_str())
		<< new QStandardItem(data.GetDocument().c_str())
		<< new QStandardItem(data.GetObjectCharacters().c_str())
		<< new QStandardItem(data.GetCondition().c_str())
		<< new QStandardItem(data.GetDeveloper().c_str())
		<< new QStandardItem(data.GetDateOfConstruction().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::FixedAssetsOperations>(BusinessLayer::FixedAssetsOperations& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(QString::number(data.GetValue(), 'f', 3))
		<< new QStandardItem(data.GetIncrement()?"true":"false")
		<< new QStandardItem(data.GetDecrement() ? "true" : "false")
		<< new QStandardItem(QString::number(data.GetFixedAssetsID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::InventoryView>(BusinessLayer::InventoryView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(QString::number(data.GetCost(), 'f', 3))
		<< new QStandardItem(data.GetInventoryNumber().c_str())
		<< new QStandardItem(data.GetBarcodeNumber().c_str())
		<< new QStandardItem(data.GetDivisionName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetLocation().c_str())
		<< new QStandardItem(data.GetStartOfOperationDate().c_str())
		<< new QStandardItem(data.GetEndOfOperationDate().c_str())
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetDepartmentID()))
		<< new QStandardItem(QString::number(data.GetSubaccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::InventorizationView>(BusinessLayer::InventorizationView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(data.GetStockEmployeeName().c_str())
		<< new QStandardItem(data.GetStockEmployeeSurname().c_str())
		<< new QStandardItem(data.GetStockEmployeePhone().c_str())
		<< new QStandardItem(data.GetStockEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetStockEmployeeID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::InventorizationListView>(BusinessLayer::InventorizationListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetInventorizationID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Group>(BusinessLayer::Group& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetDefenition().c_str());
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::JobpriceView>(BusinessLayer::JobpriceView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetValue()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(data.GetPositionName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetMeasureID()))
		<< new QStandardItem(QString::number(data.GetPositionID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::JobsheetView>(BusinessLayer::JobsheetView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::LowValueStockView>(BusinessLayer::LowValueStockView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetOtherStocksName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetWarehouseName().c_str())
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetOtherStocksID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetWarehouseID()));
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Location>(BusinessLayer::Location& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetCountryName().c_str())
		<< new QStandardItem(data.GetCountryCode().c_str()) << new QStandardItem(data.GetRegionName().c_str())
		<< new QStandardItem(data.GetCityName().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Measure>(BusinessLayer::Measure& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetShortName().c_str()) << new QStandardItem(QString::number(data.GetUnit()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::NetCostView>(BusinessLayer::NetCostView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetValue()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(data.GetIsOutdated() ? "true" : "false");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::OrderView>(BusinessLayer::OrderView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID())) 
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str()) 
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetClientName().c_str()) 
		<< new QStandardItem(data.GetClientSurname().c_str())
		<< new QStandardItem(data.GetClientPhone().c_str())
		<< new QStandardItem(data.GetClientAddress().c_str()) 
		<< new QStandardItem(data.GetClientFirm().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str()) 
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(QString::number(data.GetCount())) 
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str()) 
		<< new QStandardItem(QString::number(data.GetEmployeeID())) 
		<< new QStandardItem(QString::number(data.GetClientID())) 
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon,"Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::OrderListView>(BusinessLayer::OrderListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetOrderID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::OrderRawView>(BusinessLayer::OrderRawView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetPurveyorName().c_str())
		<< new QStandardItem(data.GetPurveyorSurname().c_str())
		<< new QStandardItem(data.GetPurveyorPhone().c_str())
		<< new QStandardItem(data.GetPurveyorCompanyName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetPurveyorID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::OrderRawListView>(BusinessLayer::OrderRawListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetOrderRawID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::OtherStocksView>(BusinessLayer::OtherStocksView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(QString(QString::number(data.GetPrice())))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString(QString::number(data.GetVolume())))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(data.GetCompanyName().c_str())
		<< new QStandardItem(QString::number(data.GetCompanyID()))
		<< new QStandardItem(QString::number(data.GetMeasureID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::OtherStocksType>(BusinessLayer::OtherStocksType& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetShortName().c_str())
		<< new QStandardItem(data.GetCode().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::PercentRate>(BusinessLayer::PercentRate& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) 
		<< new QStandardItem(QString::number(data.GetValue()))
		<< new QStandardItem(data.GetCondition().c_str()) 
		<< new QStandardItem(QString::number(data.GetPositionID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Photo>(BusinessLayer::Photo& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(QString::number(data.GetUserID()))
		<< new QStandardItem(QString::number(data.GetProductID())) << new QStandardItem(data.GetSource().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::PaymentView>(BusinessLayer::PaymentView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(QString::number(data.GetValue(),'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetTarget().c_str())
		<< new QStandardItem(data.GetAccountNumber().c_str())
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(data.GetWho().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetUserID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetAccountID()))
		<< new QStandardItem(QString::number(data.GetSubaccountID()))
		<< new QStandardItem(QString::number(data.GetCashboxAccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Position>(BusinessLayer::Position& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetName().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::PriceView>(BusinessLayer::PriceView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetValue()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(data.GetIsOutdated() ? "true" : "false");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ProductType>(BusinessLayer::ProductType& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetShortName().c_str()) << new QStandardItem(data.GetCode().c_str());
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ProductView>(BusinessLayer::ProductView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(QString(QString::number(data.GetPrice())))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString(QString::number(data.GetVolume())))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(data.GetProductTypeName().c_str())
		<< new QStandardItem(QString::number(data.GetShelfLife()))
		<< new QStandardItem(data.GetCompanyName().c_str())
		<< new QStandardItem(QString::number(data.GetCompanyID()))
		<< new QStandardItem(QString::number(data.GetMeasureID()))
		<< new QStandardItem(QString::number(data.GetProductTypeID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ProductBranchRelationView>(BusinessLayer::ProductBranchRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetBranchName().c_str())
		<< new QStandardItem(data.GetBranchAddress().c_str())
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString(QString::number(data.GetPrice())))
		<< new QStandardItem(QString(QString::number(data.GetProductID())))
		<< new QStandardItem(QString::number(data.GetBranchID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Production>(BusinessLayer::Production& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetProductionDate().c_str())
		<< new QStandardItem(data.GetExpiryDate().c_str()) << new QStandardItem(data.GetSessionStart().c_str())
		<< new QStandardItem(data.GetSessionEnd().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ProductionListView>(BusinessLayer::ProductionListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetProductionID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ProductionConsumeRawView>(BusinessLayer::ProductionConsumeRawView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(data.GetStockEmployeeName().c_str())
		<< new QStandardItem(data.GetStockEmployeeSurname().c_str())
		<< new QStandardItem(data.GetStockEmployeePhone().c_str())
		<< new QStandardItem(data.GetStockEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetStockEmployeeID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ProductionConsumeRawListView>(BusinessLayer::ProductionConsumeRawListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetProductionConsumeRawID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetSum()/data.GetCount()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ProductionPlanView>(BusinessLayer::ProductionPlanView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ProductionPlanListView>(BusinessLayer::ProductionPlanListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetProductionPlanID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::PayslipView>(BusinessLayer::PayslipView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(QString::number(data.GetValue()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetSalaryID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::PurveyorView>(BusinessLayer::PurveyorView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetSurname().c_str())
		<< new QStandardItem(data.GetPhone().c_str())
		<< new QStandardItem(data.GetCountryName().c_str())
		<< new QStandardItem(data.GetRegionName().c_str())
		<< new QStandardItem(data.GetCityName().c_str())
		<< new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(data.GetCompanyName().c_str())
		<< new QStandardItem(data.GetRoleName().c_str())
		<< new QStandardItem(data.GetPassword().c_str())
		<< new QStandardItem(data.GetEmail().c_str())
		<< new QStandardItem(data.GetActivated() ? "true" : "false")
		<< new QStandardItem(QString::number(data.GetRoleID()))
		<< new QStandardItem(QString::number(data.GetLocationID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::RelationView>(BusinessLayer::RelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetRelationName().c_str())
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(QString::number(data.GetUser1ID()))
		<< new QStandardItem(QString::number(data.GetUser2ID())) 
		<< new QStandardItem(QString::number(data.GetRelationTypeID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::RelationType>(BusinessLayer::RelationType& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetComment().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ReceiptProductView>(BusinessLayer::ReceiptProductView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(data.GetStockEmployeeName().c_str())
		<< new QStandardItem(data.GetStockEmployeeSurname().c_str())
		<< new QStandardItem(data.GetStockEmployeePhone().c_str())
		<< new QStandardItem(data.GetStockEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetStockEmployeeID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ReceiptProductListView>(BusinessLayer::ReceiptProductListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetReceiptProductID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ReceiptOtherStocksView>(BusinessLayer::ReceiptOtherStocksView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetPurveyorName().c_str())
		<< new QStandardItem(data.GetPurveyorSurname().c_str())
		<< new QStandardItem(data.GetPurveyorPhone().c_str())
		<< new QStandardItem(data.GetPurveyorCompanyName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetPurveyorID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ReceiptOtherStocksListView>(BusinessLayer::ReceiptOtherStocksListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetReceiptOtherStocksID()))
		<< new QStandardItem(data.GetOtherStocksName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetOtherStocksID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::StockTransferView>(BusinessLayer::StockTransferView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(data.GetStockEmployeeName().c_str())
		<< new QStandardItem(data.GetStockEmployeeSurname().c_str())
		<< new QStandardItem(data.GetStockEmployeePhone().c_str())
		<< new QStandardItem(data.GetStockEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetStockEmployeeID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::StockTransferListView>(BusinessLayer::StockTransferListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetStockTransferID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::RefundView>(BusinessLayer::RefundView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(QString::number(data.GetValue()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetUserID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Role>(BusinessLayer::Role& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) 
		<< new QStandardItem(data.GetCode().c_str())
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetComment().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ReturnView>(BusinessLayer::ReturnView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetClientName().c_str())
		<< new QStandardItem(data.GetClientSurname().c_str())
		<< new QStandardItem(data.GetClientPhone().c_str())
		<< new QStandardItem(data.GetClientAddress().c_str())
		<< new QStandardItem(data.GetClientFirm().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetClientID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::ReturnListView>(BusinessLayer::ReturnListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetReturnID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::SalaryView>(BusinessLayer::SalaryView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(QString::number(data.GetValue()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetSalaryTypeName().c_str())
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetSalaryTypeID()))
		<< new QStandardItem(data.GetIsBonus() ? "true": "false");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::SalaryType>(BusinessLayer::SalaryType& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetCode().c_str())
		<< new QStandardItem(data.GetName().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::Status>(BusinessLayer::Status& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetCode().c_str())
		<< new QStandardItem(data.GetName().c_str()) << new QStandardItem(data.GetComment().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::StatusRuleView>(BusinessLayer::StatusRuleView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetOperation().c_str())
		<< new QStandardItem(data.GetStatusName().c_str()) << new QStandardItem(QString::number(data.GetStatusID()));
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::SpecificationView>(BusinessLayer::SpecificationView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePositionName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::SpecificationListView>(BusinessLayer::SpecificationListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetSpecificationID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::SpoilageView>(BusinessLayer::SpoilageView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::SpoilageListView>(BusinessLayer::SpoilageListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetSpoilageID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::StockView>(BusinessLayer::StockView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetWarehouseName().c_str())
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetWarehouseID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::StockLimitView>(BusinessLayer::StockLimitView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetWarehouseName().c_str())
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetMinValue()))
		<< new QStandardItem(QString::number(data.GetMaxValue()))
		<< new QStandardItem(QString::number(data.GetStockID()))
		<< new QStandardItem(QString::number(data.GetProductID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::SubaccountView>(BusinessLayer::SubaccountView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetParentAccountID()))
		<< new QStandardItem(data.GetParentAccountNumber().c_str())
		<< new QStandardItem(data.GetNumber().c_str())
		<< new QStandardItem(QString::number(data.GetStartBalance(), 'f', 3))
		<< new QStandardItem(QString::number(data.GetCurrentBalance(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(data.GetOpenedDate().c_str())
		<< new QStandardItem(data.GetClosedDate().c_str())
		<< new QStandardItem(data.GetDetails().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::SubaccountLimitView>(BusinessLayer::SubaccountLimitView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(QString::number(data.GetSubaccountID()))
		<< new QStandardItem(QString::number(data.GetMinValue(), 'f', 3))
		<< new QStandardItem(QString::number(data.GetMaxValue(), 'f', 3));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::TimesheetView>(BusinessLayer::TimesheetView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(QString::number(data.GetWorkedTime()))
		<< new QStandardItem(QString::number(data.GetSalaryID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::TransportView>(BusinessLayer::TransportView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(data.GetUserPosition().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetUserID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::TransportListView>(BusinessLayer::TransportListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetTransportID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::UserView>(BusinessLayer::UserView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetEmail().c_str())
		<< new QStandardItem(data.GetName().c_str()) << new QStandardItem(data.GetSurname().c_str())
		<< new QStandardItem(data.GetPhone().c_str()) << new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(data.GetRoleName().c_str()) << new QStandardItem(data.GetPassword().c_str())
		<< new QStandardItem(data.GetActivated()? "true":"false") << new QStandardItem(QString::number(data.GetRoleID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::UserExtendedView>(BusinessLayer::UserExtendedView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) 
		<< new QStandardItem(data.GetName().c_str()) << new QStandardItem(data.GetSurname().c_str())
		<< new QStandardItem(data.GetPhone().c_str()) << new QStandardItem(data.GetAddress().c_str()) << new QStandardItem(data.GetCompanyName().c_str())
		<< new QStandardItem(data.GetBranchName().c_str()) << new QStandardItem(data.GetRoleName().c_str()) << new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(QString::number(data.GetRoleID())) << new QStandardItem(QString::number(data.GetSubaccountID())) 
		<< new QStandardItem(QString::number(data.GetAccountID())) << new QStandardItem(QString::number(data.GetCompanyID()))
		<< new QStandardItem(QString::number(data.GetBranchID()));
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::UserGroupRelationView>(BusinessLayer::UserGroupRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID())) << new QStandardItem(data.GetGroupName().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str()) << new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(QString::number(data.GetRoleID())) << new QStandardItem(QString::number(data.GetGroupID()))
		<< new QStandardItem(QString::number(data.GetUserID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::WarehouseView>(BusinessLayer::WarehouseView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetName().c_str())
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(data.GetWarehouseTypeName().c_str())
		<< new QStandardItem(data.GetAddress().c_str())
		<< new QStandardItem(data.GetPhone().c_str())
		<< new QStandardItem(QString::number(data.GetWarehouseTypeID()))
		<< new QStandardItem(QString::number(data.GetSubaccountID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::WarehouseType>(BusinessLayer::WarehouseType& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetCode().c_str())
		<< new QStandardItem(data.GetPurpose().c_str())
		<< new QStandardItem(data.GetName().c_str());
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::WarehouseEmployeeRelationView>(BusinessLayer::WarehouseEmployeeRelationView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(data.GetRoleName().c_str())
		<< new QStandardItem(data.GetWarehouseName().c_str())
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(QString::number(data.GetWarehouseID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::WithdrawalView>(BusinessLayer::WithdrawalView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(QString::number(data.GetValue()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetUsername().c_str())
		<< new QStandardItem(data.GetUserSurname().c_str())
		<< new QStandardItem(data.GetUserPhone().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetAccountNumber().c_str())
		<< new QStandardItem(data.GetSubaccountNumber().c_str())
		<< new QStandardItem(data.GetWho().c_str())
		<< new QStandardItem(data.GetTarget().c_str())
		<< new QStandardItem(QString::number(data.GetUserID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(QString::number(data.GetSubaccountID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetAccountID()))
		<< new QStandardItem(QString::number(data.GetCashboxAccountID()));
	return items;
}


template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::WriteOffView>(BusinessLayer::WriteOffView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetClientName().c_str())
		<< new QStandardItem(data.GetClientSurname().c_str())
		<< new QStandardItem(data.GetClientPhone().c_str())
		<< new QStandardItem(data.GetClientAddress().c_str())
		<< new QStandardItem(data.GetClientFirm().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetClientID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::WriteOffListView>(BusinessLayer::WriteOffListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetWriteOffID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::WriteOffRawView>(BusinessLayer::WriteOffRawView& data)
{
	QList<QStandardItem*> items;
	QIcon icon;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(data.GetDate().c_str())
		<< new QStandardItem(data.GetExecutionDate().c_str())
		<< new QStandardItem(data.GetStatusCode().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(data.GetEmployeeName().c_str())
		<< new QStandardItem(data.GetEmployeeSurname().c_str())
		<< new QStandardItem(data.GetEmployeePhone().c_str())
		<< new QStandardItem(data.GetEmployeePosition().c_str())
		<< new QStandardItem(data.GetStockEmployeeName().c_str())
		<< new QStandardItem(data.GetStockEmployeeSurname().c_str())
		<< new QStandardItem(data.GetStockEmployeePhone().c_str())
		<< new QStandardItem(data.GetStockEmployeePosition().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetStockEmployeeID()))
		<< new QStandardItem(QString::number(data.GetEmployeeID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()))
		<< new QStandardItem(icon, "Detail");
	return items;
}

template<>
QList<QStandardItem*> DataForm::GetDataFromClass<BusinessLayer::WriteOffRawListView>(BusinessLayer::WriteOffRawListView& data)
{
	QList<QStandardItem*> items;
	items << new QStandardItem(QString::number(data.GetID()))
		<< new QStandardItem(QString::number(data.GetWriteOffRawID()))
		<< new QStandardItem(data.GetProductName().c_str())
		<< new QStandardItem(QString::number(data.GetPrice()))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(QString::number(data.GetVolume()))
		<< new QStandardItem(data.GetMeasureName().c_str())
		<< new QStandardItem(QString::number(data.GetCount()))
		<< new QStandardItem(QString::number(data.GetSum(), 'f', 3))
		<< new QStandardItem(data.GetCurrencyName().c_str())
		<< new QStandardItem(data.GetStatusName().c_str())
		<< new QStandardItem(QString::number(data.GetProductID()))
		<< new QStandardItem(QString::number(data.GetStatusID()))
		<< new QStandardItem(QString::number(data.GetCurrencyID()));
	return items;
}
// Template specializations for connections ---------------------------------------------------------------------------
template<>
void DataForm::QtConnect<BusinessLayer::Account>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAccounts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtAccDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpAccDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelAccDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateCompanyAccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateCARDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateEntry")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateEtrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePayment")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePmtDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWithdrawal")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWdwDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "GenerateAccountCardReport")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((GenerateAccCardRep*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventory")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInveDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateFxdAst")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateFxdAstDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventory")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInveDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateDivisionAccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateDivAccDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccblEntry")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccblEtrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::AccountableView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAccountables");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtAcctblDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpAcctblDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelAcctblDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}

	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventory")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInveDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateFxdAst")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateFxdAstDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccountableRep")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccblRepDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}


template<>
void DataForm::QtConnect<BusinessLayer::AccountableDocument>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAccountableReport");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtAccblDocDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpAccblDocDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelAccblDocDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}

	
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewAccblDocDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::AccountType>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAccountType");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtAccTpDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpAccTpDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelAccTpDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateChartOfAccounts")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateCOADlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}
template<>
void DataForm::QtConnect<BusinessLayer::AccessView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAccess");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtAcsDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpAcsDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelAcsDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::AccessItem>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAccessItems");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtAcsItemDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpAcsItemDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelAcsItemDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccess")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAcsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::AmortizeGroup>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAmortizeGroup");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtAmGrDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpAmGrDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelAmGrDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}

	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::AmortizeType>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAmortizeType");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtAmTypeDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpAmTypeDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelAmTypeDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}

	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::BalanceView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionBalances");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtBlcDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpBlcDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelBlcDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::Branch>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionBranch");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtBrhDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpBrhDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelBrhDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProductBranch")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePrdBrnDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::BranchSubaccountRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionBranchSubaccounts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtBrSAccDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpBrSAccDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelBrSAccDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	
}

template<>
void DataForm::QtConnect<BusinessLayer::BorrowerView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionBorrowers");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtBrwDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpBrwDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelBrwDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::CashboxView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionCashbox");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtCbxDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpCbxDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelCbxDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::CashboxEmployeeRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionCashboxEmployee");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtCASHERDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpCASHERDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelCASHERDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::ChartOfAccountsView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionChartOfAccounts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtCOADlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpCOADlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelCOADlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "GenerateOneAccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((GenerateOneAcc*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSubaccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ClientView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionClients");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtCltDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpCltDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelCltDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrder")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReturn")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRtrnDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWriteOff")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePayment")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePmtDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::Company>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionCompany");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtCmpDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpCmpDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelCmpDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccountableRep")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccblRepDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::CompanyEmployeeRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionCompanyEmployees");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtCERDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpCERDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelCERDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::CompanyAccountRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionCompanyAccounts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtCARDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpCARDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelCARDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::ConsumeProductView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionConsumptionProducts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtConPDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpConPDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelConPDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewConPDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConPList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConPListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ConsumeProductListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionConsumptionProductsList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtConPListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpConPListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelConPListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConPDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ConsumeRawView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionConsumptionRaws");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtConRDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpConRDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelConRDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewConRDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ConsumeRawListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionConsumptionRawsList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtConRListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpConRListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelConRListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConRDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ConsumeOtherStocksView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionConsumeOthSt");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtConOthStDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpConOthStDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelConOthStDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewConOthStDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConOthStList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConOthStListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ConsumeOtherStocksListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionConsumeOthStList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtConOthStListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpConOthStListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelConOthStListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeOthSt")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConOthStDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}


template<>
void DataForm::QtConnect<BusinessLayer::Currency>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionCurrency");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtCurDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpCurDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelCurDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::Division>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionDivision");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtDivDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpDivDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelDivDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::DivisionAccountRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionDivisionAssounts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtDivAccDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpDivAccDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelDivAccDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}


template<>
void DataForm::QtConnect<BusinessLayer::EmployeeView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionEmployees");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtEmpDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpEmpDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelEmpDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccountable")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAcctbDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateBorrower")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateBrwDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConPDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateCompanyEmployee")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateCERDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventorization")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInvDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateJobsheet")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateJbsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrder")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrderRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReceiptProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpPDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStockTransfer")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockTrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProductionConsumeRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdConRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProductionPlan")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePPlanDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReturn")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRtrnDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpecification")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSpecDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSalary")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSlrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpoilage")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSplDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateTransport")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateTrsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWriteOff")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWriteOffR")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CalcWages")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((ClcWagesDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateCashboxEmployee")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateCASHERDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWarehouseEmployee")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWERDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateEmployeeProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateEmpPrdDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReceiptOthSt")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpOthStDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeOthSt")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConOthStDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccountableRep")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccblRepDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "GenerateDailySalesReport")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((GenerateDailySalesRep*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "GenerateAgentReport")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((GenerateAgentRep*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::EmployeeProductRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionEmployeeProducts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtEmpPrdDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpEmpPrdDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelEmpPrdDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::EntryView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionEntry");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtEtrDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpEtrDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelEtrDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}


template<>
void DataForm::QtConnect<BusinessLayer::EntryRouting>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionEntryRouting");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtEtrRtDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpEtrRtDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelEtrRtDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::FixedAssetsView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionFixedAssets");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtFxdAstDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpFxdAstDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelFxdAstDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewFxdAstDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateFxdAstOper")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateFxdAstOperDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::FixedAssetsSpecification>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionFixedAssetsSpec");
	std::size_t pos = crud.find("C");
	createBtn->setHidden(true);
	editBtn->setHidden(true);
	deleteBtn->setHidden(true);
	/*if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtFxdAstDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpFxdAstDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelFxdAstDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewInvDlg);*/
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateFxdAst")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateFxdAstDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::FixedAssetsOperations>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionFixedAstOper");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtFxdAstOperDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpFxdAstOperDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelFxdAstOperDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewInvDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::InventoryView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionInventory");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtInveDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpInveDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelInveDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewInvDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::InventorizationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionInventorization");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtInvDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpInvDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelInvDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewInvDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInvList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInvListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::InventorizationListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionInventorizationList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtInvListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpInvListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelInvListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventorization")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInvDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::Group>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionGroup");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtGroupDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpGroupDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelGroupDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateUserGroup")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateUserGrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::JobpriceView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionJobprice");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtJbpDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpJbpDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelJbpDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::JobsheetView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionJobsheet");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtJbsDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpJbsDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelJbsDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::Location>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionLocation");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtLcnDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpLcnDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelLcnDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateClient")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateCltDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePurveyor")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePurDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::LowValueStockView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionLowValueStock");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtLowValStockDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpLowValStockDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelLowValStockDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::Measure>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionMeasure");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtMsrDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpMsrDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelMsrDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::NetCostView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionNetCost");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtNetCDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpNetCDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelNetCDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}


template<>
void DataForm::QtConnect<BusinessLayer::OrderView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionOrders");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtOrdDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpOrdDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelOrdDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewOrdDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrdList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::OrderListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionOrderList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtOrdListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpOrdListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelOrdListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrder")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::OrderRawView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionOrderRaws");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtOrdRDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpOrdRDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelOrdRDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewOrdRDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrdRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::OrderRawListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionOrderRawsList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtOrdRListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpOrdRListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelOrdRListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrderRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdRDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::OtherStocksView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionOtherStocks");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtOthStDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpOthStDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelOthStDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConOthStList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConOthStListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRcpOthStList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpOthStListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateLowValueStock")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateLowValStockDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::OtherStocksType>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionOtherStocksType");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtOthStTypeDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpOthStTypeDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelOthStTypeDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::PercentRate>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionPercentRate");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPcrDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPcrDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPcrDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::Photo>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionPhoto");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPhotoDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPhotoDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPhotoDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::PaymentView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionPayments");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPmtDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPmtDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPmtDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewPmtDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccountableRep")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccblRepDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::Position>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionPosition");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPosDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPosDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPosDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateEmployee")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateEmpDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateJobsheet")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateJbsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateJobprice")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateJbpDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePercentRate")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePrcDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateTimesheet")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateTmsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::PriceView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionPrices");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPrcDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPrcDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPrcDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::ProductType>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionProductType");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtProdTpDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpProdTpDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelProdTpDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ProductView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionProducts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtProdDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpProdDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelProdDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConPList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConPListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInvList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInvListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrdList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrdRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePrdnList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdnListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProdConRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdConRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePPlanList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePPlanListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRcpPList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpPListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStockTrList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockTrListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRtrnList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRtrnListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpecList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSpecListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStock")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpecList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSpecListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSplList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSplListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateTrsList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateTrsListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWOffList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWOffRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePhoto")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePhtDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateJobprice")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateJbpDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateJobsheet")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateJbsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePrice")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePrcDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateNetCost")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateNetCDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpecification")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSpecDlg*)parentDialog), SLOT(SetID(int, QString)));
	}	
	if (parentDialog != nullptr && parentDialog->objectName() == "ReworkRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((ReworkRawDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateEmployeeProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateEmpPrdDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProductBranch")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePrdBrnDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ProductBranchRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionBranchProducts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPrdBrnDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPrdBrnDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPrdBrnDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::Production>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionProduction");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtProdnDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpProdnDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelProdnDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewProdnDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePrdnList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdnListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ProductionListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionProductionList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtProdnListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpProdnListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelProdnListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProduction")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdnDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ProductionConsumeRawView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionProductionConsumeRaws");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtProdConRDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpProdConRDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelProdConRDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewProdConRDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProdConRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdConRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ProductionConsumeRawListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionProductionConsumeRawsLis");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtProdConRListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpProdConRListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelProdConRListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProductionConsumeRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdConRDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ProductionPlanView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionProductionPlan");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPPlanDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPPlanDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPPlanDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewPPlanDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePPlanList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePPlanListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ProductionPlanListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionProductionPlanList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPPlanListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPPlanListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPPlanListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProductionPlan")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePPlanDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::PayslipView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionPayslip");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPspDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPspDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPspDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::PurveyorView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionPurveyors");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtPurDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpPurDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelPurDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrderRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventory")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInveDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateFxdAst")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateFxdAstDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReceiptOthSt")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpOthStDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::RelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionRelation");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRelDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRelDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRelDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::RelationType>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionRelationType");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRelTypeDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRelTypeDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRelTypeDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRelation")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRelDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}
template<>
void DataForm::QtConnect<BusinessLayer::ReceiptProductView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionReceiptProducts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRcpPDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRcpPDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRcpPDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewRcpPDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRcpPList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpPListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ReceiptOtherStocksView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionReceiptOtherStocks");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRcpOthStDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRcpOthStDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRcpOthStDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewOrdRDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRcpOthStList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpOthStListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ReceiptOtherStocksListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionReceiptOtherStocksList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRcpOthStListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRcpOthStListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRcpOthStListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReceiptOthSt")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpOthStDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ReceiptProductListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionReceiptProductsList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRcpPListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRcpPListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRcpPListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReceiptProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpPDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::StockTransferView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionStockTransfers");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtStockTrDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpStockTrDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelStockTrDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewStockTrDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStockTrList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockTrListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::StockTransferListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionStockTransfersList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtStockTrListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpStockTrListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelStockTrListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStockTransfer")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockTrDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::RefundView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionRefund");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRfdDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRfdDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRfdDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::Role>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionRoles");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRoleDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRoleDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRoleDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateUser")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateUserDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateClient")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateCltDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateEmployee")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateEmpDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccess")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAcsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ReturnView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionReturns");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRtrnDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRtrnDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRtrnDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewRtrnDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRtrnList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRtrnListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::ReturnListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionReturnList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtRtrnListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpRtrnListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelRtrnListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReturn")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRtrnDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::SalaryView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionSalary");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtSlrDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpSlrDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelSlrDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePayslip")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePspDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateTimesheet")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateTmsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::SalaryType>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionSalaryType");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtSlrTypeDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpSlrTypeDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelSlrTypeDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSalary")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSlrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::Status>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionStatus");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtStsDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpStsDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelStsDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConPDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventorization")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInvDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrder")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrderRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePayment")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePmtDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProduction")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePPlanDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProductionConsumeRaw")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReceiptProduct")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpPDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStockTransfer")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockTrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReturn")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRtrnDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpoilage")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSplDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStock")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStatusRule")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStsRuleDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateTransport")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateTrsDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWithdrawal")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWdwDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWriteOff")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWriteOffR")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffRDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConPList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConPListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInvList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInvListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrdList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateOrdRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateOrdRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePrdnList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdnListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateProdConRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateProdConRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePPlanList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePPlanListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRcpPList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpPListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStockTrList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockTrListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRtrnList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRtrnListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpecList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSpecListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSplList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSplListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateTrsList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateTrsListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWOffList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWOffRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSubaccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventory")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInveDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateFxdAst")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateFxdAstDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateInventory")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateInveDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateDivisionAccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateDivAccDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateConsumeOthSt")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateConOthStDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateReceiptOthSt")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRcpOthStDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccountableRep")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccblRepDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::StatusRuleView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionStatusRule");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtStsRuleDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpStsRuleDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelStsRuleDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::SpecificationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionSpecifications");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtSpecDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpSpecDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelSpecDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewSpecDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpecList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSpecListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::SpecificationListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionSpecificationList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtSpecListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpSpecListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelSpecListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpecification")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSpecDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::SpoilageView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionSpoilage");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtSplDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpSplDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelSplDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewSplDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSplList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePPlanListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::SpoilageListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionSpoilageList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtSplListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpSplListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelSplListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSpoilage")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePPlanDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::StockView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionStock");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtStockDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpStockDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelStockDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateStockLimit")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateStockLimitDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::StockLimitView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionStockLimit");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtStockLmDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpStockLmDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelStockLmDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::SubaccountView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionSubaccounts");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtSAccDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpSAccDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelSAccDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}	
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateCompanyAccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateCARDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateEntry")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateEtrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWithdrawal")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWdwDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePayment")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePmtDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "GenerateAccountCardReport")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((GenerateAccCardRep*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSubaccountLimit")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSAccLmDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccblEntry")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccblEtrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateBranchSubaccount")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateBrSAccDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::SubaccountLimitView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionSubaccountsLimit");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtSAccLmDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpSAccLmDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelSAccLmDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}


template<>
void DataForm::QtConnect<BusinessLayer::TimesheetView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionTimesheet");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtTmsDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpTmsDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelTmsDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::TransportView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionTransports");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtTrsDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpTrsDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelTrsDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewTrsDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateTrsList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateTrsListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::TransportListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionTransportsList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtTrsListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpTrsListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelTrsListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateTransport")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateTrsDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::UserView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionAllUsers");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtUserDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpUserDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelUserDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateBalance")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateBlcDlg*)parentDialog), SLOT(SetID(int, QString)));
	}	
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePhoto")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePhtDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePayment")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePmtDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRefund")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRfdDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRelation")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRelDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSalary")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSlrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWithdrawal")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWdwDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateUserGroup")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateUserGrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::UserExtendedView>()
{
	createBtn->setVisible(false);
	editBtn->setVisible(false);
	deleteBtn->setVisible(false);
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	//connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreatePayment")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreatePmtDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWithdrawal")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWdwDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateSalary")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateSlrDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateRelation")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateRelDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::UserGroupRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionUserGroup");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtUserGrDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpUserGrDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelUserGrDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::WarehouseView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionWarehouse");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtWrhDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpWrhDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelWrhDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::WarehouseType>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionWarehouseType");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtWrhTpDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpWrhTpDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelWrhTpDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::WarehouseEmployeeRelationView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionWarehouseEmployee");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtWERDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpWERDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelWERDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
}

template<>
void DataForm::QtConnect<BusinessLayer::WithdrawalView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionWithdrawal");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtWdwDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpWdwDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelWdwDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewWdwDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateAccountableRep")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateAccblRepDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::WriteOffView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionWriteOffs");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtWOffDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpWOffDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelWOffDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewWOffDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWOffList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::WriteOffListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionWriteOffList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtWOffListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpWOffListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelWOffListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWriteOff")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::WriteOffRawView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionWriteOffRaws");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtWOffRDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpWOffRDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelWOffRDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	connect(viewBtn, &QPushButton::released, this, &DataForm::ViewWOffRDlg);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWOffRList")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffRListDlg*)parentDialog), SLOT(SetID(int, QString)));
	}
}

template<>
void DataForm::QtConnect<BusinessLayer::WriteOffRawListView>()
{
	BusinessLayer::Access access;
	std::string crud = access.GetCRUDAccess(dataFormBL->globalVar, &dataFormBL->GetOrmasDal(), loggedUser, "actionWriteOffRawsList");
	std::size_t pos = crud.find("C");
	if (pos != std::string::npos)
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::CrtWOffRListDlg);
	}
	else
	{
		connect(createBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("U");
	if (pos != std::string::npos)
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::UdpWOffRListDlg);
	}
	else
	{
		connect(editBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	pos = crud.find("D");
	if (pos != std::string::npos)
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::DelWOffRListDlg);
	}
	else
	{
		connect(deleteBtn, &QPushButton::released, this, &DataForm::AcsDenied);
	}
	viewBtn->setVisible(false);
	connect(closeBtn, &QPushButton::released, this, &DataForm::CloseDataForm);
	connect(tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(ChangeBtnState()));
	if (parentDialog != nullptr && parentDialog->objectName() == "CreateWriteOffR")
	{
		connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(GetIDValue(QModelIndex)));
		connect(this, SIGNAL(SendID(int, QString)), ((CreateWOffRDlg*)parentDialog), SLOT(SetID(int, QString)));
		connect(tableView->model(), SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
		connect(tableView->model(), SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(OnRowsNumberChanged()));
	}
}


// Form show 
bool DataForm::SearchInAccForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("accountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Accounts"));
		dForm->FillTable<BusinessLayer::Account>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("accountForm");
			dForm->QtConnect<BusinessLayer::Account>();
			QMdiSubWindow *accountWindow = new QMdiSubWindow;
			accountWindow->setWidget(dForm);
			accountWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(accountWindow);
			accountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All accounts are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All accounts are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInAccblDocForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("acctbDocForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Accountable documents"));
		dForm->FillTable<BusinessLayer::AccountableDocument>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("accblDocForm");
			dForm->QtConnect<BusinessLayer::AccountableDocument>();
			QMdiSubWindow *accblDocWindow = new QMdiSubWindow;
			accblDocWindow->setWidget(dForm);
			accblDocWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(accblDocWindow);
			accblDocWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All documents are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All documents are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}


bool DataForm::SearchInAccTpForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("accountTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Account type"));
		dForm->FillTable<BusinessLayer::AccountType>(currentParent->errorMessage);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("accountTypeForm");
			dForm->QtConnect<BusinessLayer::AccountType>();
			QMdiSubWindow *accountTypeWindow = new QMdiSubWindow;
			accountTypeWindow->setWidget(dForm);
			accountTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(accountTypeWindow);
			accountTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All account type are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All account type are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInAcsItemForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("accessItemForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Access items"));
		dForm->FillTable<BusinessLayer::AccessItem>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::AccessItem>();
			dForm->setObjectName("accessItemForm");
			QMdiSubWindow *accessItemWindow = new QMdiSubWindow;
			accessItemWindow->setWidget(dForm);
			accessItemWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(accessItemWindow);
			accessItemWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All access items are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All access items are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInAccessForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("accessForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Accesses"));
		dForm->FillTable<BusinessLayer::AccessView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::AccessView>();
			dForm->setObjectName("accessForm");
			QMdiSubWindow *accessWindow = new QMdiSubWindow;
			accessWindow->setWidget(dForm);
			accessWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(accessWindow);
			accessWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All accesses are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All accesses are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInAcctblForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("accountableForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Accountables"));
		dForm->FillTable<BusinessLayer::AccountableView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::AccountableView>();
			dForm->setObjectName("accountableForm");
			QMdiSubWindow *accountableWindow = new QMdiSubWindow;
			accountableWindow->setWidget(dForm);
			accountableWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(accountableWindow);
			accountableWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All accountables are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All accountables are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInAmGrForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("amGroupForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Amortize group"));
		dForm->FillTable<BusinessLayer::AmortizeGroup>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("amGroupForm");
			dForm->QtConnect<BusinessLayer::AmortizeGroup>();
			QMdiSubWindow *amGrWindow = new QMdiSubWindow;
			amGrWindow->setWidget(dForm);
			amGrWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(amGrWindow);
			amGrWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Amortize group are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Amortize group are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInAmTypeForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("amTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Amortize type"));
		dForm->FillTable<BusinessLayer::AmortizeType>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("amTypeForm");
			dForm->QtConnect<BusinessLayer::AmortizeType>();
			QMdiSubWindow *amTypeWindow = new QMdiSubWindow;
			amTypeWindow->setWidget(dForm);
			amTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(amTypeWindow);
			amTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Amortize type are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Amortize type are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInBlcForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("balanceForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Balances"));
		dForm->FillTable<BusinessLayer::BalanceView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("balanceForm");
			dForm->QtConnect<BusinessLayer::BalanceView>();
			QMdiSubWindow *balanceWindow = new QMdiSubWindow;
			balanceWindow->setWidget(dForm);
			balanceWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(balanceWindow);
			balanceWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All balances are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All balances are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInBrhForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("branchForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Branches"));
		dForm->FillTable<BusinessLayer::Branch>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("branchForm");
			dForm->QtConnect<BusinessLayer::Branch>();
			QMdiSubWindow *branchWindow = new QMdiSubWindow;
			branchWindow->setWidget(dForm);
			branchWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(branchWindow);
			branchWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All branches are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All branches are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInBrwForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("borrowerForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Borrowers"));
		dForm->FillTable<BusinessLayer::BorrowerView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::BorrowerView>();
			dForm->setObjectName("borrowerForm");
			QMdiSubWindow *borrowerWindow = new QMdiSubWindow;
			borrowerWindow->setWidget(dForm);
			borrowerWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(borrowerWindow);
			borrowerWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All borrowers are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All borrowers are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}


bool DataForm::SearchInBrSAccForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("branchSubaccountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Branch subaccount"));
		dForm->FillTable<BusinessLayer::BranchSubaccountRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("branchSubaccountForm");
			dForm->QtConnect<BusinessLayer::BranchSubaccountRelationView>();
			QMdiSubWindow *branchSAccWindow = new QMdiSubWindow;
			branchSAccWindow->setWidget(dForm);
			branchSAccWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(branchSAccWindow);
			branchSAccWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All branch subaccount relation are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All branch subaccount relation are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInCASHERForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("cashboxEmployeeForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Cashbox-employee relation"));
		dForm->FillTable<BusinessLayer::CashboxEmployeeRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::CashboxEmployeeRelationView>();
			dForm->setObjectName("cashboxEmployeeForm");
			QMdiSubWindow *cashEmpWindow = new QMdiSubWindow;
			cashEmpWindow->setWidget(dForm);
			cashEmpWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(cashEmpWindow);
			cashEmpWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All cashbox-employee relations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All cashbox-employee relations are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}
bool DataForm::SearchInCbxForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("cashboxForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Cashbox"));
		dForm->FillTable<BusinessLayer::CashboxView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("cashboxForm");
			dForm->QtConnect<BusinessLayer::CashboxView>();
			QMdiSubWindow *caWindow = new QMdiSubWindow;
			caWindow->setWidget(dForm);
			caWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(caWindow);
			caWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Cashbox are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Cashbox are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInCOADForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("chartOffAccountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Chart of account"));
		dForm->FillTable<BusinessLayer::ChartOfAccountsView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("chartOffAccountForm");
			dForm->QtConnect<BusinessLayer::ChartOfAccountsView>();
			QMdiSubWindow *chartOfAccountWindow = new QMdiSubWindow;
			chartOfAccountWindow->setWidget(dForm);
			chartOfAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(chartOfAccountWindow);
			chartOfAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Chart of accounts are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Chart of accounts are showns");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInCltForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("clientForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Clients"));
		dForm->FillTable<BusinessLayer::ClientView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ClientView>();
			dForm->setObjectName("clientForm");
			QMdiSubWindow *clientWindow = new QMdiSubWindow;
			clientWindow->setWidget(dForm);
			clientWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(clientWindow);
			clientWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All clients are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All clients are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInCARForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("companyAccountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Company account relation"));
		dForm->FillTable<BusinessLayer::CompanyAccountRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("companyAccountForm");
			dForm->QtConnect<BusinessLayer::CompanyAccountRelationView>();
			QMdiSubWindow *companyAccountWindow = new QMdiSubWindow;
			companyAccountWindow->setWidget(dForm);
			companyAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(companyAccountWindow);
			companyAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Company-account relations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Company-account relations are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInCmpForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("companyForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Companies"));
		dForm->FillTable<BusinessLayer::Company>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("companyForm");
			dForm->QtConnect<BusinessLayer::Company>();
			QMdiSubWindow *companyWindow = new QMdiSubWindow;
			companyWindow->setWidget(dForm);
			companyWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(companyWindow);
			companyWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All companies are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All companies are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInCERForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("companyEmployeeForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Company-employee relation"));
		dForm->FillTable<BusinessLayer::CompanyEmployeeRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::CompanyEmployeeRelationView>();
			dForm->setObjectName("companyEmployeeForm");
			QMdiSubWindow *comEmpWindow = new QMdiSubWindow;
			comEmpWindow->setWidget(dForm);
			comEmpWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(comEmpWindow);
			comEmpWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All company-employee relations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All company-employee relations are shown");
		currentParent->statusBar()->showMessage(message);

		return false;
	}
	return true;
}

bool DataForm::SearchInConPForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("consumeProductForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Consume product"));
		dForm->FillTable<BusinessLayer::ConsumeProductView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("consumeProductForm");
			dForm->QtConnect<BusinessLayer::ConsumeProductView>();
			QMdiSubWindow *consumeProductWindow = new QMdiSubWindow;
			consumeProductWindow->setWidget(dForm);
			consumeProductWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(consumeProductWindow);
			consumeProductWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in consume");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in consume");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInConOthForm(std::string searchFilter)
{

	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("consumeOthStForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Consume other stocks"));
		dForm->FillTable<BusinessLayer::ConsumeOtherStocksView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("consumeOthStForm");
			dForm->QtConnect<BusinessLayer::ConsumeOtherStocksView>();
			QMdiSubWindow *consumeOthStWindow = new QMdiSubWindow;
			consumeOthStWindow->setWidget(dForm);
			consumeOthStWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(consumeOthStWindow);
			consumeOthStWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All other stocks are shown in consume");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All other stocks are shown in consume");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInConRForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("consumeRawForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Consume raw"));
		dForm->FillTable<BusinessLayer::ConsumeRawView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("consumeRawForm");
			dForm->QtConnect<BusinessLayer::ConsumeRawView>();
			QMdiSubWindow *consumeRawWindow = new QMdiSubWindow;
			consumeRawWindow->setWidget(dForm);
			consumeRawWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(consumeRawWindow);
			consumeRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raws are shown in consume");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raws are shown in consume");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInCurForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("currencyForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Currencies"));
		dForm->FillTable<BusinessLayer::Currency>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("currencyForm");
			dForm->QtConnect<BusinessLayer::Currency>();
			QMdiSubWindow *currencyWindow = new QMdiSubWindow;
			currencyWindow->setWidget(dForm);
			currencyWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(currencyWindow);
			currencyWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All currencies are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All currencies are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInDivForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("divisionForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Divisions"));
		dForm->FillTable<BusinessLayer::Division>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("divisionForm");
			dForm->QtConnect<BusinessLayer::Division>();
			QMdiSubWindow *divisionWindow = new QMdiSubWindow;
			divisionWindow->setWidget(dForm);
			divisionWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(divisionWindow);
			divisionWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All divisions are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All divisions are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;

}

bool DataForm::SearchInDivAccForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("divisionAccForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Division account"));
		dForm->FillTable<BusinessLayer::DivisionAccountRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("divisionAccountForm");
			dForm->QtConnect<BusinessLayer::DivisionAccountRelationView>();
			QMdiSubWindow *divisionAccWindow = new QMdiSubWindow;
			divisionAccWindow->setWidget(dForm);
			divisionAccWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(divisionAccWindow);
			divisionAccWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All division account are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All division account are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInEmpForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("employeeForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Employees"));
		dForm->FillTable<BusinessLayer::EmployeeView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::EmployeeView>();
			dForm->setObjectName("employeeForm");
			QMdiSubWindow *employeeWindow = new QMdiSubWindow;
			employeeWindow->setWidget(dForm);
			employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(employeeWindow);
			employeeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All employees are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All employees are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInEmpPrdForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("employeeProductForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Employee-product relation"));
		dForm->FillTable<BusinessLayer::EmployeeProductRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::EmployeeProductRelationView>();
			dForm->setObjectName("employeeProductForm");
			QMdiSubWindow *empPrdWindow = new QMdiSubWindow;
			empPrdWindow->setWidget(dForm);
			empPrdWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(empPrdWindow);
			empPrdWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All employee-product relations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All employee-product relations are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInEtrForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("entryForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Entries"));
		dForm->FillTable<BusinessLayer::EntryView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("entryForm");
			dForm->QtConnect<BusinessLayer::EntryView>();
			QMdiSubWindow *entryWindow = new QMdiSubWindow;
			entryWindow->setWidget(dForm);
			entryWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(entryWindow);
			entryWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All entries are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All entries are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInEtrRtForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("entryRoutingForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Entry routing"));
		dForm->FillTable<BusinessLayer::EntryRouting>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("entryRoutingForm");
			dForm->QtConnect<BusinessLayer::EntryRouting>();
			QMdiSubWindow *entryRoutingWindow = new QMdiSubWindow;
			entryRoutingWindow->setWidget(dForm);
			entryRoutingWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(entryRoutingWindow);
			entryRoutingWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Entry routing are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Entry routing are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInFxdAstForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("fixedAstForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Fixed assets"));
		dForm->FillTable<BusinessLayer::FixedAssetsView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("fixedAstForm");
			dForm->QtConnect<BusinessLayer::FixedAssetsView>();
			QMdiSubWindow *faWindow = new QMdiSubWindow;
			faWindow->setWidget(dForm);
			faWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(faWindow);
			faWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Fixed assets are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Fixed assets are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInAstOperForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("fixedAstOperForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Fixed assets operation"));
		dForm->FillTable<BusinessLayer::FixedAssetsOperations>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("fixedAstOperForm");
			dForm->QtConnect<BusinessLayer::FixedAssetsOperations>();
			QMdiSubWindow *faoWindow = new QMdiSubWindow;
			faoWindow->setWidget(dForm);
			faoWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(faoWindow);
			faoWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Fixed assets operation are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Fixed assets operation are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInInveForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("inventoryForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Fixed assets operation"));
		dForm->FillTable<BusinessLayer::InventoryView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("inventoryForm");
			dForm->QtConnect<BusinessLayer::InventoryView>();
			QMdiSubWindow *inveWindow = new QMdiSubWindow;
			inveWindow->setWidget(dForm);
			inveWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(inveWindow);
			inveWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Inventory are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Inventory are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInInvForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("inventorizationForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Inventorization"));
		dForm->FillTable<BusinessLayer::InventorizationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("inventorizationForm");
			dForm->QtConnect<BusinessLayer::InventorizationView>();
			QMdiSubWindow *inventorizationWindow = new QMdiSubWindow;
			inventorizationWindow->setWidget(dForm);
			inventorizationWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(inventorizationWindow);
			inventorizationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All inventorizations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All inventorizations are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}

	return true;
}

bool DataForm::SearchInGroupForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("groupForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Groups"));
		dForm->FillTable<BusinessLayer::Group>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Group>();
			dForm->setObjectName("groupForm");
			QMdiSubWindow *groupWindow = new QMdiSubWindow;
			groupWindow->setWidget(dForm);
			groupWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(groupWindow);
			groupWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All groups are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All groups are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInJbpForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("jobpriceForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Jobprice"));
		dForm->FillTable<BusinessLayer::JobpriceView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::JobpriceView>();
			dForm->setObjectName("jobpriceForm");
			QMdiSubWindow *jobpriceWindow = new QMdiSubWindow;
			jobpriceWindow->setWidget(dForm);
			jobpriceWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(jobpriceWindow);
			jobpriceWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All jobprices are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();

		QString message = tr("All jobprices are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}


bool DataForm::SearchInJbsForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("jobsheetForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Jobsheet"));
		dForm->FillTable<BusinessLayer::JobsheetView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::JobsheetView>();
			dForm->setObjectName("jobsheetForm");
			QMdiSubWindow *jobsheetWindow = new QMdiSubWindow;
			jobsheetWindow->setWidget(dForm);
			jobsheetWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(jobsheetWindow);
			jobsheetWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All jobsheets are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All jobsheets are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInLowValStockForm(std::string searchFilter)
{

	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	BusinessLayer::WarehouseEmployeeRelation reRel;
	BusinessLayer::Warehouse warehouse;
	BusinessLayer::WarehouseType wType;
	if (!reRel.GetWarehouseEmployeeByEmployeeID(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), loggedUser->GetID(), currentParent->errorMessage))
	{
		QString message = tr("Access denied!");
		currentParent->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return false;
	}
	if (!warehouse.GetWarehouseByID(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), reRel.GetWarehouseID(), currentParent->errorMessage))
	{
		QString message = tr("Access denied!");
		currentParent->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return false;
	}
	if (!wType.GetWarehouseTypeByCode(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), "LOW VALUE", currentParent->errorMessage))
	{
		QString message = tr("Access denied!");
		currentParent->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return false;
	}
	if (wType.GetID() != warehouse.GetWarehouseTypeID())
	{
		QString message = tr("Access denied!");
		currentParent->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return false;
	}
	BusinessLayer::LowValueStock lowValStock;
	lowValStock.SetWarehouseID(reRel.GetWarehouseID());
	std::string filter = lowValStock.GenerateFilter(currentParent->oBL->GetOrmasDal());
	std::vector<std::string> filterList;
	filterList.push_back(searchFilter);
	filterList.push_back(filter);
	filter = currentParent->oBL->ConcatenateFilters(filterList);
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("lowValueStockForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Low valuw stock"));
		dForm->FillTable<BusinessLayer::LowValueStockView>(currentParent->errorMessage, filter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::LowValueStockView>();
			dForm->setObjectName("lowValueStockForm");
			QMdiSubWindow *lvStockWindow = new QMdiSubWindow;
			lvStockWindow->setWidget(dForm);
			lvStockWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(lvStockWindow);
			lvStockWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All other stocsk are shown in low value stock");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All other stocsk are shown in low value stock");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInLcnForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("locationForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Locations"));
		dForm->FillTable<BusinessLayer::Location>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("locationForm");
			dForm->QtConnect<BusinessLayer::Location>();
			QMdiSubWindow *locationWindow = new QMdiSubWindow;
			locationWindow->setWidget(dForm);
			locationWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(locationWindow);
			locationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All locations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All locations are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInMsrForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("measureForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Measures"));
		dForm->FillTable<BusinessLayer::Measure>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("measureForm");
			dForm->QtConnect<BusinessLayer::Measure>();
			QMdiSubWindow *measureWindow = new QMdiSubWindow;
			measureWindow->setWidget(dForm);
			measureWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(measureWindow);
			measureWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All measures are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All measures are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInNetCForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("netCostForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Net cost"));
		dForm->FillTable<BusinessLayer::NetCostView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("netCostForm");
			dForm->QtConnect<BusinessLayer::NetCostView>();
			QMdiSubWindow *netCostWindow = new QMdiSubWindow;
			netCostWindow->setWidget(dForm);
			netCostWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(netCostWindow);
			netCostWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All net cost are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All net cost are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInOrderForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("orderForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Orders"));
		dForm->FillTable<BusinessLayer::OrderView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::OrderView>();
			dForm->setObjectName("orderForm");
			QMdiSubWindow *orderWindow = new QMdiSubWindow;
			orderWindow->setWidget(dForm);
			orderWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(orderWindow);
			orderWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All orders are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All orders are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInOrdRForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("orderRawForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Order raw"));
		dForm->FillTable<BusinessLayer::OrderRawView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("orderRawForm");
			dForm->QtConnect<BusinessLayer::OrderRawView>();
			QMdiSubWindow *orderRawWindow = new QMdiSubWindow;
			orderRawWindow->setWidget(dForm);
			orderRawWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(orderRawWindow);
			orderRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raws are shown in orders");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raws are shown in orders");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInOthStForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("otherStocksForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Other stocks"));
		dForm->FillTable<BusinessLayer::OtherStocksView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::OtherStocksView>();
			dForm->setObjectName("otherStocksForm");
			QMdiSubWindow *otherStocksWindow = new QMdiSubWindow;
			otherStocksWindow->setWidget(dForm);
			otherStocksWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(otherStocksWindow);
			otherStocksWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All other stocks are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All other stocks are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInPcrForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("percentRateForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Percent rate"));
		dForm->FillTable<BusinessLayer::PercentRate>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::PercentRate>();
			dForm->setObjectName("percentRateForm");
			QMdiSubWindow *percentRateWindow = new QMdiSubWindow;
			percentRateWindow->setWidget(dForm);
			percentRateWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(percentRateWindow);
			percentRateWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All percent rates are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All percent rates are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInPmtForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("paymentForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Payments"));
		std::string filter = "";
		BusinessLayer::Cashbox cashbox;
		BusinessLayer::CashboxEmployeeRelation ceRelation;
		if (ceRelation.GetCashboxEmployeeByEmployeeID(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), currentParent->oBL->loggedUser->GetID(), currentParent->errorMessage))
		{
			if (cashbox.GetCashboxByID(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), ceRelation.GetCashboxID(), currentParent->errorMessage))
			{
				BusinessLayer::Payment payment;
				payment.SetCashboxAccountID(cashbox.GetSubaccountID());
				filter = payment.GenerateFilter(currentParent->oBL->GetOrmasDal());
			}
		}
		std::vector<std::string> filterList;
		filterList.push_back(searchFilter);
		filterList.push_back(filter);
		filter = currentParent->oBL->ConcatenateFilters(filterList);
		dForm->FillTable<BusinessLayer::PaymentView>(currentParent->errorMessage, filter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("paymentForm");
			dForm->QtConnect<BusinessLayer::PaymentView>();
			QMdiSubWindow *paymentWindow = new QMdiSubWindow;
			paymentWindow->setWidget(dForm);
			paymentWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(paymentWindow);
			paymentWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All payments are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All payments are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInPosForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("positionForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Position"));
		dForm->FillTable<BusinessLayer::Position>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Position>();
			dForm->setObjectName("positionForm");
			QMdiSubWindow *positionWindow = new QMdiSubWindow;
			positionWindow->setWidget(dForm);
			positionWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(positionWindow);
			positionWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All position are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All position are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInPrcForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("priceForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Price"));
		dForm->FillTable<BusinessLayer::PriceView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("priceForm");
			dForm->QtConnect<BusinessLayer::PriceView>();
			QMdiSubWindow *priceWindow = new QMdiSubWindow;
			priceWindow->setWidget(dForm);
			priceWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(priceWindow);
			priceWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All prices are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All prices are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}


bool DataForm::SearchInProdTpForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("productTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Product types"));
		dForm->FillTable<BusinessLayer::ProductType>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductType>();
			dForm->setObjectName("productTypeForm");
			QMdiSubWindow *prodTypeWindow = new QMdiSubWindow;
			prodTypeWindow->setWidget(dForm);
			prodTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(prodTypeWindow);
			prodTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All product types are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All product types are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInPrdBrnForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("branchProductForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Branch-product relation"));
		dForm->FillTable<BusinessLayer::ProductBranchRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductBranchRelationView>();
			dForm->setObjectName("branchProductForm");
			QMdiSubWindow *brnPrdWindow = new QMdiSubWindow;
			brnPrdWindow->setWidget(dForm);
			brnPrdWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(brnPrdWindow);
			brnPrdWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All branch-product relations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All branch-product relations are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInProdForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("productForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Products"));
		dForm->FillTable<BusinessLayer::ProductView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductView>();
			dForm->setObjectName("productForm");
			QMdiSubWindow *productWindow = new QMdiSubWindow;
			productWindow->setWidget(dForm);
			productWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(productWindow);
			productWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInProdnForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("productionForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Production"));
		dForm->FillTable<BusinessLayer::Production>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Production>();
			dForm->setObjectName("productionForm");
			QMdiSubWindow *productionWindow = new QMdiSubWindow;
			productionWindow->setWidget(dForm);
			productionWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(productionWindow);
			productionWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All production are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All production are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}

	return true;
}

bool DataForm::SearchInProdConRForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("productionCnsumeRawForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Production consume raw"));
		dForm->FillTable<BusinessLayer::ProductionConsumeRawView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("productionCnsumeRawForm");
			dForm->QtConnect<BusinessLayer::ProductionConsumeRawView>();
			QMdiSubWindow *pConsumeRawWindow = new QMdiSubWindow;
			pConsumeRawWindow->setWidget(dForm);
			pConsumeRawWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(pConsumeRawWindow);
			pConsumeRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raws are shown in consume");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raws are shown in consume");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}


bool DataForm::SearchInPPlanConRForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("productionPlanForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Production plan"));
		dForm->FillTable<BusinessLayer::ProductionPlanView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductionPlanView>();
			dForm->setObjectName("productionPlanForm");
			QMdiSubWindow *productionPlanWindow = new QMdiSubWindow;
			productionPlanWindow->setWidget(dForm);
			productionPlanWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(productionPlanWindow);
			productionPlanWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All production plans are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All production plan are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInPurForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("purveyorForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Purveyors"));
		dForm->FillTable<BusinessLayer::PurveyorView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::PurveyorView>();
			dForm->setObjectName("purveyorForm");
			QMdiSubWindow *purveyorWindow = new QMdiSubWindow;
			purveyorWindow->setWidget(dForm);
			purveyorWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(purveyorWindow);
			purveyorWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All purveyors are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All purveyors are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}


bool DataForm::SearchInPspForm(std::string searchFilter)
{

	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("payslipForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Payslips"));
		dForm->FillTable<BusinessLayer::PayslipView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("payslipForm");
			dForm->QtConnect<BusinessLayer::PayslipView>();
			QMdiSubWindow *payslipWindow = new QMdiSubWindow;
			payslipWindow->setWidget(dForm);
			payslipWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(payslipWindow);
			payslipWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All payslips are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All withdrawals are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInRelForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("relationForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Relations"));
		dForm->FillTable<BusinessLayer::RelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("relationForm");
			dForm->QtConnect<BusinessLayer::RelationView>();
			QMdiSubWindow *relationWindow = new QMdiSubWindow;
			relationWindow->setWidget(dForm);
			relationWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(relationWindow);
			relationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All relations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All relations are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInRelTypeForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("relationTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Relation types"));
		dForm->FillTable<BusinessLayer::RelationType>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("relationTypeForm");
			dForm->QtConnect<BusinessLayer::RelationType>();
			QMdiSubWindow *relationtypeWindow = new QMdiSubWindow;
			relationtypeWindow->setWidget(dForm);
			relationtypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(relationtypeWindow);
			relationtypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All relation types are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All relation types are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInRoleForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("roleForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Roles"));
		dForm->FillTable<BusinessLayer::Role>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("roleForm");
			dForm->QtConnect<BusinessLayer::Role>();
			QMdiSubWindow *roleWindow = new QMdiSubWindow;
			roleWindow->setWidget(dForm);
			roleWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(roleWindow);
			roleWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All roles are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All roles are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInRcpOthStForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("receiptOthStForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Receipt other stocks"));
		dForm->FillTable<BusinessLayer::ReceiptOtherStocksView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("receiptOthStForm");
			dForm->QtConnect<BusinessLayer::ReceiptOtherStocksView>();
			QMdiSubWindow *rosWindow = new QMdiSubWindow;
			rosWindow->setWidget(dForm);
			rosWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(rosWindow);
			rosWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All other stocks are shown in receipts");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All other stocks are shown in receipts");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInRcpPForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("receiptProductForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Receipt product"));
		dForm->FillTable<BusinessLayer::ReceiptProductView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("receiptProductForm");
			dForm->QtConnect<BusinessLayer::ReceiptProductView>();
			QMdiSubWindow *receiptProductWindow = new QMdiSubWindow;
			receiptProductWindow->setWidget(dForm);
			receiptProductWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(receiptProductWindow);
			receiptProductWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in receipt");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in receipt");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInStockLmForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("stockLimitForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Stock limit"));
		dForm->FillTable<BusinessLayer::StockLimitView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("stockLimitForm");
			dForm->QtConnect<BusinessLayer::StockLimitView>();
			QMdiSubWindow *stockLmWindow = new QMdiSubWindow;
			stockLmWindow->setWidget(dForm);
			stockLmWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(stockLmWindow);
			stockLmWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All ilimits are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All ilimits are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInStockTrForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("stockTransferForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Receipt raw"));
		dForm->FillTable<BusinessLayer::StockTransferView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("StockTransferForm");
			dForm->QtConnect<BusinessLayer::StockTransferView>();
			QMdiSubWindow *StockTransferWindow = new QMdiSubWindow;
			StockTransferWindow->setWidget(dForm);
			StockTransferWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(StockTransferWindow);
			StockTransferWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raws are shown in receipt");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raws are shown in receipt");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInRfdForm(std::string searchFilter)
{

	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("refundForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Refunds"));
		dForm->FillTable<BusinessLayer::RefundView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("refundForm");
			dForm->QtConnect<BusinessLayer::RefundView>();
			QMdiSubWindow *refundWindow = new QMdiSubWindow;
			refundWindow->setWidget(dForm);
			refundWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(refundWindow);
			refundWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All refunds are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All payments are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInRtrnForm(std::string searchFilter)
{

	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("returnForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Returns"));
		dForm->FillTable<BusinessLayer::ReturnView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ReturnView>();
			dForm->setObjectName("returnForm");
			QMdiSubWindow *returnWindow = new QMdiSubWindow;
			returnWindow->setWidget(dForm);
			returnWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(returnWindow);
			returnWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All returns are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All returns are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInSlrForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("salaryForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Salary"));
		dForm->FillTable<BusinessLayer::SalaryView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("salaryForm");
			dForm->QtConnect<BusinessLayer::SalaryView>();
			QMdiSubWindow *salaryWindow = new QMdiSubWindow;
			salaryWindow->setWidget(dForm);
			salaryWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(salaryWindow);
			salaryWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All salary are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All salary are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInSlrTypeForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("salaryTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Salary types"));
		dForm->FillTable<BusinessLayer::SalaryType>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("salaryTypeForm");
			dForm->QtConnect<BusinessLayer::SalaryType>();
			QMdiSubWindow *salaryTypeWindow = new QMdiSubWindow;
			salaryTypeWindow->setWidget(dForm);
			salaryTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(salaryTypeWindow);
			salaryTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All salary types are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All salary types are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInStsForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("statusForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Statuses"));
		dForm->FillTable<BusinessLayer::Status>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("statusForm");
			dForm->QtConnect<BusinessLayer::Status>();
			QMdiSubWindow *statusWindow = new QMdiSubWindow;
			statusWindow->setWidget(dForm);
			statusWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(statusWindow);
			statusWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All statuses are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All statuses are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInStsRuleForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("statusRuleForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Status rule"));
		dForm->FillTable<BusinessLayer::StatusRuleView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("statusRuleForm");
			dForm->QtConnect<BusinessLayer::StatusRuleView>();
			QMdiSubWindow *statusRuleWindow = new QMdiSubWindow;
			statusRuleWindow->setWidget(dForm);
			statusRuleWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(statusRuleWindow);
			statusRuleWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All status rules are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All status rules are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}

	return true;
}

bool DataForm::SearchInSpecForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("specificationForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Specifications"));
		dForm->FillTable<BusinessLayer::SpecificationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::SpecificationView>();
			dForm->setObjectName("specificationForm");
			QMdiSubWindow *specWindow = new QMdiSubWindow;
			specWindow->setWidget(dForm);
			specWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(specWindow);
			specWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All specifications are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All specifications are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInSplForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("spoilageForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Spoilage"));
		dForm->FillTable<BusinessLayer::SpoilageView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::SpoilageView>();
			dForm->setObjectName("spoilageForm");
			QMdiSubWindow *spoilageWindow = new QMdiSubWindow;
			spoilageWindow->setWidget(dForm);
			spoilageWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(spoilageWindow);
			spoilageWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All spoilage are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All spoilage are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}


bool DataForm::SearchInSAccForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), currentParent->errorMessage);
	if (0 == rolesMap.size())
		return false;

	std::string filter = "";

	if (currentParent->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
		currentParent->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
	{
		filter = "";
	}
	else
	{
		BusinessLayer::Subaccount subaccount;
		BusinessLayer::BranchSubaccountRelation bsRel;
		BusinessLayer::CompanyEmployeeRelation ceRel;
		int branchID = ceRel.GetBranchByEmployeeID(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), currentParent->GetLoggedUser()->GetID(), currentParent->errorMessage);
		if (0 < branchID)
		{
			std::vector<int> subaccountIDVec = bsRel.GetSubaccountIDsbyBranchID(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), branchID, currentParent->errorMessage);
			if (subaccountIDVec.size() > 0)
			{
				filter = subaccount.GenerateINFilter(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), subaccountIDVec);
			}
		}
	}
	std::vector<std::string> filterList;
	filterList.push_back(filter);
	filterList.push_back(searchFilter);
	filter = currentParent->oBL->ConcatenateFilters(filterList);
	currentParent->errorMessage.clear();
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("subaccountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Subaccounts"));
		dForm->FillTable<BusinessLayer::SubaccountView>(currentParent->errorMessage, filter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("subaccountForm");
			dForm->QtConnect<BusinessLayer::SubaccountView>();
			QMdiSubWindow *subaccountWindow = new QMdiSubWindow;
			subaccountWindow->setWidget(dForm);
			subaccountWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(subaccountWindow);
			subaccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->SetDecoration();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All subaccounts are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All subaccounts are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInSAccLmForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("subaccountLimitForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Subaccount limit"));
		dForm->FillTable<BusinessLayer::SubaccountLimitView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("subaccountLimitForm");
			dForm->QtConnect<BusinessLayer::SubaccountLimitView>();
			QMdiSubWindow *subaccountLmWindow = new QMdiSubWindow;
			subaccountLmWindow->setWidget(dForm);
			subaccountLmWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(subaccountLmWindow);
			subaccountLmWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All subaccount limits are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All subaccount limits are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInStockForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("stockForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Stock"));
		dForm->FillTable<BusinessLayer::StockView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("stockForm");
			dForm->QtConnect<BusinessLayer::StockView>();
			QMdiSubWindow *stockWindow = new QMdiSubWindow;
			stockWindow->setWidget(dForm);
			stockWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(stockWindow);
			stockWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->SetDecoration();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in the stock");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in the stock");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInTmsForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("timesheetForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Timesheet"));
		dForm->FillTable<BusinessLayer::TimesheetView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::TimesheetView>();
			dForm->setObjectName("timesheetForm");
			QMdiSubWindow *timesheetWindow = new QMdiSubWindow;
			timesheetWindow->setWidget(dForm);
			timesheetWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(timesheetWindow);
			timesheetWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All timesheets are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All timesheets are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInTrsForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("transportForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Transports"));
		dForm->FillTable<BusinessLayer::TransportView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("transportForm");
			dForm->QtConnect<BusinessLayer::TransportView>();
			QMdiSubWindow *transportWindow = new QMdiSubWindow;
			transportWindow->setWidget(dForm);
			transportWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(transportWindow);
			transportWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All transports are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			return false;
			currentParent->errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All transports are shown");
		currentParent->statusBar()->showMessage(message);

		return false;
	}
	return true;
}

bool DataForm::SearchInUserForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("userForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Users"));
		dForm->FillTable<BusinessLayer::UserView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::UserView>();
			dForm->setObjectName("userForm");
			QMdiSubWindow *userWindow = new QMdiSubWindow;
			userWindow->setWidget(dForm);
			userWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(userWindow);
			userWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All users are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All users are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInUserGrForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("userGroupForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("User group"));
		dForm->FillTable<BusinessLayer::UserGroupRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::UserGroupRelationView>();
			dForm->setObjectName("userGroupForm");
			QMdiSubWindow *userGrWindow = new QMdiSubWindow;
			userGrWindow->setWidget(dForm);
			userGrWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(userGrWindow);
			userGrWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All user groups are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All user grous are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInWrhForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("warehouseForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Warehouse"));
		dForm->FillTable<BusinessLayer::WarehouseView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("warehouseForm");
			dForm->QtConnect<BusinessLayer::WarehouseView>();
			QMdiSubWindow *wareWindow = new QMdiSubWindow;
			wareWindow->setWidget(dForm);
			wareWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(wareWindow);
			wareWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Warehouse are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Warehouse are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInWrhTpForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("warehouseTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Warehouse type"));
		dForm->FillTable<BusinessLayer::WarehouseType>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("warehouseTypeForm");
			dForm->QtConnect<BusinessLayer::WarehouseType>();
			QMdiSubWindow *wTypeWindow = new QMdiSubWindow;
			wTypeWindow->setWidget(dForm);
			wTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(wTypeWindow);
			wTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All warehouse types are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All warehouse types are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInWERForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("warehouseEmployeeForm"));
	if (checkedWidget == nullptr)
	{
		currentParent->errorMessage = "";
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Warehouse-employee relation"));
		dForm->FillTable<BusinessLayer::WarehouseEmployeeRelationView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::WarehouseEmployeeRelationView>();
			dForm->setObjectName("warehouseEmployeeForm");
			QMdiSubWindow *werEmpWindow = new QMdiSubWindow;
			werEmpWindow->setWidget(dForm);
			werEmpWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(werEmpWindow);
			werEmpWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All warehouse-employee relations are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All warehouse-employee relations are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInwWdwForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("withdrawalForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Withdrawals"));
		std::string filter = "";
		BusinessLayer::Cashbox cashbox;
		BusinessLayer::CashboxEmployeeRelation ceRelation;
		if (ceRelation.GetCashboxEmployeeByEmployeeID(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), currentParent->oBL->loggedUser->GetID(), currentParent->errorMessage))
		{
			if (cashbox.GetCashboxByID(currentParent->oBL->globalVar, currentParent->oBL->GetOrmasDal(), ceRelation.GetCashboxID(), currentParent->errorMessage))
			{
				BusinessLayer::Withdrawal withdrawal;
				withdrawal.SetCashboxAccountID(cashbox.GetSubaccountID());
				filter = withdrawal.GenerateFilter(currentParent->oBL->GetOrmasDal());
			}
		}
		std::vector<std::string> filterList;
		filterList.push_back(filter);
		filterList.push_back(searchFilter);
		filter = currentParent->oBL->ConcatenateFilters(filterList);
		dForm->FillTable<BusinessLayer::WithdrawalView>(currentParent->errorMessage, filter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("withdrawalForm");
			dForm->QtConnect<BusinessLayer::WithdrawalView>();
			QMdiSubWindow *withdrawalWindow = new QMdiSubWindow;
			withdrawalWindow->setWidget(dForm);
			withdrawalWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(withdrawalWindow);
			withdrawalWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All withdrawal are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All withdrawals are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}


bool DataForm::SearchInWOffForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("writeOffForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Write-off"));
		dForm->FillTable<BusinessLayer::WriteOffView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::WriteOffView>();
			dForm->setObjectName("writeOffForm");
			QMdiSubWindow *writeOfftWindow = new QMdiSubWindow;
			writeOfftWindow->setWidget(dForm);
			writeOfftWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(writeOfftWindow);
			writeOfftWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All write-off are shown");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All write-off are shown");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

bool DataForm::SearchInWOffRawForm(std::string searchFilter)
{
	MainForm* currentParent = (MainForm*)parentForm;
	QString message = tr("Loading...");
	currentParent->statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(currentParent->mdiArea->subWindowList(), QString("writeOffRawForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(currentParent->oBL, currentParent);
		dForm->setWindowTitle(tr("Write-off raw"));
		dForm->FillTable<BusinessLayer::WriteOffRawView>(currentParent->errorMessage, searchFilter);
		if (currentParent->errorMessage.empty())
		{
			dForm->setObjectName("writeOffRawForm");
			dForm->QtConnect<BusinessLayer::WriteOffRawView>();
			QMdiSubWindow *writeOffRawWindow = new QMdiSubWindow;
			writeOffRawWindow->setWidget(dForm);
			writeOffRawWindow->setAttribute(Qt::WA_DeleteOnClose);
			currentParent->mdiArea->addSubWindow(writeOffRawWindow);
			writeOffRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raw are shown in write-off");
			currentParent->statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			currentParent->statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(currentParent->errorMessage.c_str())),
				QString(tr("Ok")));
			currentParent->errorMessage = "";
			return false;
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raw are shown in write-off");
		currentParent->statusBar()->showMessage(message);
		return false;
	}
	return true;
}

void DataForm::keyPressEvent(QKeyEvent *event) {
	if (QApplication::keyboardModifiers() & Qt::ControlModifier) 
	{
		int key = event->key();
		if (key == Qt::Key::Key_F) 
		{ 
			//event is Ctrl+F, search
			SearchInTableDlg *searchDlg = new SearchInTableDlg(this);
			searchDlg->setAttribute(Qt::WA_DeleteOnClose);
			searchDlg->setWindowTitle(tr("Search in table"));
			QMdiSubWindow *invWindow = new QMdiSubWindow;
			invWindow->setWidget(searchDlg);
			invWindow->setAttribute(Qt::WA_DeleteOnClose);
			((MainForm*)parentForm)->mdiArea->addSubWindow(invWindow);
			searchDlg->show();
		}
	}
}