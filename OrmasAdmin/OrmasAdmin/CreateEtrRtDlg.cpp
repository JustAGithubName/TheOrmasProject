#include "stdafx.h"
#include "CreateEtrRtDlg.h"

#include "MainForm.h"
#include "DataForm.h"



CreateEtrRtDlg::CreateEtrRtDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateEtrRtDlg::EditEntryRouting);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateEtrRtDlg::CreateEntryRouting);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateEtrRtDlg::Close);
	InitComboBox();
}

CreateEtrRtDlg::~CreateEtrRtDlg()
{

}

void CreateEtrRtDlg::SetEntryRoutingParams(QString eOperation, int eDebit, int eCredit, int id)
{
	entryRouting->SetOperation(eOperation.toUtf8().constData());
	entryRouting->SetDebitAccountID(eDebit);
	entryRouting->SetCreditAccountID(eCredit);
	entryRouting->SetID(id);
}

void CreateEtrRtDlg::FillEditElements(QString eOperation, int eDebit, int eCredit)
{
	operationEdit->setText(eOperation);
	dAccCmb->setCurrentIndex(dAccCmb->findData(QVariant(eDebit)));
	cAccCmb->setCurrentIndex(cAccCmb->findData(QVariant(eCredit)));
}

bool CreateEtrRtDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetEntryRoutingParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateEtrRtDlg::CreateEntryRouting()
{
	errorMessage.clear();
	if (0 != dAccCmb->currentData().toInt() && 0 != cAccCmb->currentData().toInt() && !operationEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetEntryRoutingParams(operationEdit->text(), dAccCmb->currentData().toInt(), cAccCmb->currentData().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateEntryRouting(entryRouting, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> entryRoutingItem;
					entryRoutingItem << new QStandardItem(QString::number(entryRouting->GetID()))
						<< new QStandardItem(entryRouting->GetOperation().c_str())
						<< new QStandardItem(QString::number(entryRouting->GetDebitAccountID()))
						<< new QStandardItem(QString::number(entryRouting->GetCreditAccountID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(entryRoutingItem);
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
			QString(tr("Please fill operation, debit and credit!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateEtrRtDlg::EditEntryRouting()
{
	errorMessage.clear();
	if (0 != dAccCmb->currentData().toInt() && 0 != cAccCmb->currentData().toInt() && !operationEdit->text().isEmpty())
	{
		if (QString(entryRouting->GetOperation().c_str()) != operationEdit->text() || entryRouting->GetDebitAccountID() != cAccCmb->currentData().toInt()
			|| entryRouting->GetCreditAccountID() != dAccCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetEntryRoutingParams(operationEdit->text(), dAccCmb->currentData().toInt(), cAccCmb->currentData().toInt(), entryRouting->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateEntryRouting(entryRouting, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(entryRouting->GetOperation().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(entryRouting->GetDebitAccountID()));
						itemModel->item(mIndex.row(), 3)->setText(QString::number(entryRouting->GetCreditAccountID()));
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
			QString(tr("Please fill operation, debit and credit!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateEtrRtDlg::Close()
{
	this->parentWidget()->close();
}

void CreateEtrRtDlg::InitComboBox()
{
	BusinessLayer::ChartOfAccounts coAcc;
	std::string comboText = "";
	std::vector<BusinessLayer::Account> accountVec = dialogBL->GetAllDataForClass<BusinessLayer::Account>(errorMessage);
	if (!accountVec.empty())
	{
		for (unsigned int i = 0; i < accountVec.size(); i++)
		{
			coAcc.Clear();
			if (!coAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountVec[i].GetNumber(), errorMessage))
				continue;
			comboText = "";
			comboText += accountVec[i].GetNumber();
			comboText += " - ";
			comboText += coAcc.GetName();
			dAccCmb->addItem(comboText.c_str(), QVariant(accountVec[i].GetID()));
			cAccCmb->addItem(comboText.c_str(), QVariant(accountVec[i].GetID()));
		}
	}
}
