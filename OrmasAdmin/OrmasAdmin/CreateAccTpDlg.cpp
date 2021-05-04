#include "stdafx.h"
#include "CreateAccTpDlg.h"

#include "MainForm.h"
#include "DataForm.h"



CreateAccTpDlg::CreateAccTpDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	vInt = new QIntValidator(0, 1000000000, this);
	numberEdit->setValidator(vInt);
	commentEdit->setMaxLength(100);
	nameEdit->setMaxLength(50);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAccTpDlg::EditAccountType);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAccTpDlg::CreateAccountType);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAccTpDlg::Close);
}

CreateAccTpDlg::~CreateAccTpDlg()
{
	delete vInt;
}

void CreateAccTpDlg::SetAccountTypeParams(QString aName, int aNumber, QString aComment, int id)
{
	accountType->SetName(aName.toUtf8().constData());
	accountType->SetNumber(aNumber);
	accountType->SetComment(aComment.toUtf8().constData());
	accountType->SetID(id);
}

void CreateAccTpDlg::FillEditElements(QString aName, int aNumber, QString aComment)
{
	nameEdit->setText(aName);
	numberEdit->setText(QString::number(aNumber));
	commentEdit->setText(aComment);
}

bool CreateAccTpDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetAccountTypeParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateAccTpDlg::CreateAccountType()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && 0 != numberEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetAccountTypeParams(nameEdit->text(), numberEdit->text().toInt(), commentEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);

		if (dialogBL->CreateAccountType(accountType, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> accountTypeItem;
					accountTypeItem << new QStandardItem(QString::number(accountType->GetID()))
						<< new QStandardItem(accountType->GetName().c_str())
						<< new QStandardItem(QString::number(accountType->GetNumber()))
						<< new QStandardItem(accountType->GetComment().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(accountTypeItem);
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
			QString(tr("Please fill name and number!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAccTpDlg::EditAccountType()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty()  && 0 != numberEdit->text().toInt())
	{
		if (QString(accountType->GetName().c_str()) != nameEdit->text() || accountType->GetNumber() != numberEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetAccountTypeParams(nameEdit->text(), numberEdit->text().toInt(), commentEdit->text(), accountType->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateAccountType(accountType, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(accountType->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(numberEdit->text().toInt()));
						itemModel->item(mIndex.row(), 3)->setText(commentEdit->text());
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
			QString(tr("Please fill name and number!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAccTpDlg::Close()
{
	this->parentWidget()->close();
}
