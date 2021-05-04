#include "stdafx.h"

#include "CreateWrhDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateWrhDlg::CreateWrhDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(60);
	addressEdit->setMaxLength(60);
	phoneEdit->setMaxLength(15);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWrhDlg::EditWarehouse);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWrhDlg::CreateWarehouse);
		QObject::connect(wTypeCmb, &QComboBox::currentTextChanged, this, &CreateWrhDlg::GenerateSubaccount);
		InitComboBox();
		GenerateSubaccount();
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateWrhDlg::Close);
	
}

void CreateWrhDlg::SetWarehouseParams(QString wName, QString wAddress, QString wPhone, int wtID, int subID, int id)
{
	warehouse->SetName(wName.toUtf8().constData());
	warehouse->SetAddress(wAddress.toUtf8().constData());
	warehouse->SetPhone(wPhone.toUtf8().constData());
	warehouse->SetWarehouseTypeID(wtID);
	warehouse->SetSubaccountID(subID);
	warehouse->SetID(id);
}

void CreateWrhDlg::FillEditElements(QString wName, QString wAddress, QString wPhone, int wtID, int subID)
{
	nameEdit->setText(wName);
	addressEdit->setText(wAddress);
	phoneEdit->setText(wPhone);
	wTypeCmb->setCurrentIndex(wTypeCmb->findData(QVariant(wtID)));
	BusinessLayer::Subaccount subacc;
	if (subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subID, errorMessage))
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
	InitComboBox(wtID);
}

bool CreateWrhDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetWarehouseParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 6)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 6)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateWrhDlg::CreateWarehouse()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || addressEdit->text().isEmpty() || phoneEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;

		dialogBL->StartIsolatedTransaction(errorMessage);
		//create subacc section
		BusinessLayer::Currency curr;
		std::string filter;
		curr.SetShortName("TJS");
		filter = curr.GenerateFilter(dialogBL->GetOrmasDal());
		std::vector<BusinessLayer::Currency> curVec = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage, filter);
		if (curVec.size() == 0)
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Cannot find currency!")),
				QString(tr("Ok")));

			errorMessage.clear();
		}
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
		subaccount->SetCurrencyID(curVec.at(0).GetID());
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
		SetWarehouseParams(nameEdit->text(), addressEdit->text(), phoneEdit->text(), wTypeCmb->currentData().toInt(), subaccount->GetID());
		if (dialogBL->CreateWarehouse(warehouse, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> WarehouseItem;
					WarehouseItem << new QStandardItem(QString::number(warehouse->GetID()))
						<< new QStandardItem(warehouse->GetName().c_str())
						<< new QStandardItem(subaccount->GetNumber().c_str())
						<< new QStandardItem(wTypeCmb->currentText())
						<< new QStandardItem(warehouse->GetAddress().c_str())
						<< new QStandardItem(warehouse->GetPhone().c_str())
						<< new QStandardItem(QString::number(warehouse->GetWarehouseTypeID()))
						<< new QStandardItem(QString::number(subaccount->GetID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(WarehouseItem);
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

void CreateWrhDlg::EditWarehouse()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || addressEdit->text().isEmpty() || phoneEdit->text().isEmpty()))
	{
		if (QString(warehouse->GetName().c_str()) != nameEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetWarehouseParams(nameEdit->text(), addressEdit->text(), phoneEdit->text(), wTypeCmb->currentData().toInt(), warehouse->GetSubaccountID(), warehouse->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (!subaccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouse->GetSubaccountID(), errorMessage))
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));

				errorMessage.clear();
				return;
			}
			if (dialogBL->UpdateWarehouse(warehouse, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						
						itemModel->item(mIndex.row(), 1)->setText(warehouse->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(subaccount->GetNumber().c_str());
						itemModel->item(mIndex.row(), 3)->setText(wTypeCmb->currentText());
						itemModel->item(mIndex.row(), 4)->setText(warehouse->GetAddress().c_str());
						itemModel->item(mIndex.row(), 5)->setText(warehouse->GetPhone().c_str());
						itemModel->item(mIndex.row(), 6)->setText(QString::number(warehouse->GetWarehouseTypeID()));
						itemModel->item(mIndex.row(), 7)->setText(QString::number(warehouse->GetSubaccountID()));
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

void CreateWrhDlg::Close()
{
	this->parentWidget()->close();
}

void CreateWrhDlg::InitComboBox()
{
	std::vector<BusinessLayer::WarehouseType> wtVector = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseType>(errorMessage);
	if (!wtVector.empty())
	{
		for (unsigned int i = 0; i < wtVector.size(); i++)
		{
			wTypeCmb->addItem(wtVector[i].GetName().c_str(), QVariant(wtVector[i].GetID()));
		}
	}
}

void CreateWrhDlg::InitComboBox(int wTypeID)
{
	BusinessLayer::WarehouseType wType;
	wType.SetID(wTypeID);
	std::string filter = wType.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::WarehouseType> wtVector = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseType>(errorMessage, filter);
	if (!wtVector.empty())
	{
		for (unsigned int i = 0; i < wtVector.size(); i++)
		{
			wTypeCmb->addItem(wtVector[i].GetName().c_str(), QVariant(wtVector[i].GetID()));
		}
	}
}

void CreateWrhDlg::GenerateSubaccount()
{
	BusinessLayer::Account acc;
	BusinessLayer::ChartOfAccounts aoSAcc;
	BusinessLayer::Currency curr;
	BusinessLayer::WarehouseType wType;
	wType.SetCode("PRODUCT");
	int wTypeID = wType.GetWarehouseTypeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	std::string filter;
	curr.SetShortName("TJS");
	filter = curr.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::Currency> curVec = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage, filter);
	if (curVec.size()>0)
	{
		std::string number = "";
		if (wTypeCmb->currentData().toInt() == wTypeID)
		{
			number += "10740";
			number += std::to_string(curVec.at(0).GetCode());
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
			if (acc.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10740", errorMessage))
			{
				if (aoSAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10740", errorMessage))
				{
					accNamePh->setText(aoSAcc.GetName().c_str());
				}
			}
			subaccount->SetParentAccountID(acc.GetID());
		}
		else
		{
			number += "10720";
			number += std::to_string(curVec.at(0).GetCode());
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
			if (acc.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10720", errorMessage))
			{
				if (aoSAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10720", errorMessage))
				{
					accNamePh->setText(aoSAcc.GetName().c_str());
				}
			}
			subaccount->SetParentAccountID(acc.GetID());
		}
	}
}