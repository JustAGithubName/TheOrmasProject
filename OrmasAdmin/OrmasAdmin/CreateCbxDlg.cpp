#include "stdafx.h"

#include "CreateCbxDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateCbxDlg::CreateCbxDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	informationEdit->setMaxLength(60);
	addressEdit->setMaxLength(60);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCbxDlg::EditCashbox);
		
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCbxDlg::CreateCashbox);
		QObject::connect(currencyCmb, &QComboBox::currentTextChanged, this, &CreateCbxDlg::GenerateSubaccount);
		InitComboBox();
		GenerateSubaccount();
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateCbxDlg::Close);
}

void CreateCbxDlg::SetCashboxParams(int subID, QString cInfo, QString cAddress, int id)
{
	cashbox->SetSubaccountID(subID);
	cashbox->SetInformation(cInfo.toUtf8().constData());
	cashbox->SetAddress(cAddress.toUtf8().constData());
	cashbox->SetID(id);
}

void CreateCbxDlg::FillEditElements(int subID, QString cInfo, QString cAddress)
{
	informationEdit->setText(cInfo);
	addressEdit->setText(cAddress);
	BusinessLayer::Subaccount subacc;
	if(subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subID, errorMessage))
	{
		numberEdit->setText(subacc.GetNumber().c_str());
	}
	BusinessLayer::Account acc;
	BusinessLayer::ChartOfAccounts aoSAcc;
	if (acc.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subacc.GetParentAccountID(), errorMessage))
	{
		if (aoSAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), acc.GetNumber(), errorMessage))
		{
			accNamePh->setText(aoSAcc.GetName().c_str());
		}
	}
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(subacc.GetCurrencyID())));
	InitComboBox(subacc.GetCurrencyID());
}

bool CreateCbxDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetCashboxParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateCbxDlg::CreateCashbox()
{
	errorMessage.clear();
	if (!(informationEdit->text().isEmpty() || addressEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		
		dialogBL->StartIsolatedTransaction(errorMessage);
		//create subacc section
		BusinessLayer::Status status;
		if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "OPEN", errorMessage))
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));

			errorMessage.clear();
			return;
		}
		subaccount->SetOpenedDate(dialogBL->GetOrmasDal().GetSystemDateTime());
		subaccount->SetCurrentBalance(0);
		subaccount->SetStartBalance(0);
		subaccount->SetCurrencyID(currencyCmb->currentData().toInt());
		subaccount->SetStatusID(status.GetID());
		if (!subaccount->CreateSubaccount(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));

			errorMessage.clear();
			return;
		}
		//end of subacc creation
		SetCashboxParams(subaccount->GetID(), informationEdit->text(), addressEdit->text());
		if (dialogBL->CreateCashbox(cashbox, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> CashboxItem;
					CashboxItem << new QStandardItem(QString::number(cashbox->GetID())) 
						<< new QStandardItem(subaccount->GetNumber().c_str())
						<< new QStandardItem(cashbox->GetInformation().c_str())
						<< new QStandardItem(cashbox->GetAddress().c_str())
						<< new QStandardItem(QString::number(subaccount->GetID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(CashboxItem);
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

			errorMessage.clear();
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please fill name, phone and address!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCbxDlg::EditCashbox()
{
	errorMessage.clear();
	if (!(informationEdit->text().isEmpty() || addressEdit->text().isEmpty()))
	{
		if (QString(cashbox->GetInformation().c_str()) != informationEdit->text() || QString(cashbox->GetAddress().c_str()) != addressEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetCashboxParams(cashbox->GetSubaccountID(), informationEdit->text(), addressEdit->text(), cashbox->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if(!subaccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashbox->GetSubaccountID(), errorMessage))
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));

				errorMessage.clear();
				return;
			}
			if (dialogBL->UpdateCashbox(cashbox, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(subaccount->GetNumber().c_str());
						itemModel->item(mIndex.row(), 2)->setText(cashbox->GetInformation().c_str());
						itemModel->item(mIndex.row(), 3)->setText(cashbox->GetAddress().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(cashbox->GetSubaccountID()));
						emit itemModel->dataChanged(mIndex, mIndex);
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
			QString(tr("Please fill name, phone and address!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCbxDlg::Close()
{
	this->parentWidget()->close();
}

void CreateCbxDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
}

void CreateCbxDlg::InitComboBox(int curID)
{
	BusinessLayer::Currency cur;
	cur.SetID(curID);
	std::string filter = cur.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage, filter);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
}

void CreateCbxDlg::GenerateSubaccount()
{
	BusinessLayer::Account acc;
	BusinessLayer::ChartOfAccounts aoSAcc;
	BusinessLayer::Currency curr;
	if (curr.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyCmb->currentData().toInt(), errorMessage))
	{
		std::string number = "";
		if (curr.GetShortName().compare("TJS") == 0)
		{
			number += "10110";
			number += std::to_string(curr.GetCode());
			std::string genNumber = std::to_string(dialogBL->GetOrmasDal().GenerateAccountID());
			std::string prefix = "";
			unsigned int additionalZero = 7 - genNumber.length();
			while (prefix.length() < additionalZero)
			{
				prefix += "0";
			}
			number += prefix;
			number += genNumber;
			subaccount->SetNumber(number);
			numberEdit->setText(subaccount->GetNumber().c_str());
			if (acc.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10110", errorMessage))
			{
				if (aoSAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10110", errorMessage))
				{
					accNamePh->setText(aoSAcc.GetName().c_str());
				}
			}
			subaccount->SetParentAccountID(acc.GetID());
		}
		else
		{
			number += "10120";
			number += std::to_string(curr.GetCode());
			std::string genNumber = std::to_string(dialogBL->GetOrmasDal().GenerateAccountID());
			std::string prefix = "";
			unsigned int additionalZero = 7 - genNumber.length();
			while (prefix.length() < additionalZero)
			{
				prefix += "0";
			}
			number += prefix;
			number += genNumber;
			subaccount->SetNumber(number);
			numberEdit->setText(subaccount->GetNumber().c_str());
			if (acc.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10120", errorMessage))
			{
				if (aoSAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10120", errorMessage))
				{
					accNamePh->setText(aoSAcc.GetName().c_str());
				}
			}
			subaccount->SetParentAccountID(acc.GetID());
		}

	}
}
