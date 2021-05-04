#include "stdafx.h"

#include "CreateOthSTypeDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreateOthSTypeDlg::CreateOthSTypeDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(50);
	shortNameEdit->setMaxLength(10);
	codeEdit->setMaxLength(15);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateOthSTypeDlg::EditOtherStocksType);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateOthSTypeDlg::CreateOtherStocksType);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateOthSTypeDlg::Close);
}

void CreateOthSTypeDlg::SetOthSTypeParams(QString pName, QString pShortName, QString pCode, int id)
{
	othSType->SetName(pName.toUtf8().constData());
	othSType->SetShortName(pShortName.toUtf8().constData());
	othSType->SetCode(pShortName.toUtf8().constData());
	othSType->SetID(id);
}

void CreateOthSTypeDlg::FillEditElements(QString pName, QString pShortName, QString pCode)
{
	nameEdit->setText(pName);
	shortNameEdit->setText(pShortName);
	codeEdit->setText(pCode);
}

bool CreateOthSTypeDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetOthSTypeParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateOthSTypeDlg::CreateOtherStocksType()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || shortNameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetOthSTypeParams(nameEdit->text(), shortNameEdit->text(), codeEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateOtherStocksType(othSType, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> prodTypeItem;
					prodTypeItem << new QStandardItem(QString::number(othSType->GetID())) << new QStandardItem(othSType->GetName().c_str())
						<< new QStandardItem(othSType->GetShortName().c_str()) << new QStandardItem(othSType->GetCode().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(prodTypeItem);
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
			QString(tr("Please fill name, code and short name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateOthSTypeDlg::EditOtherStocksType()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || shortNameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		if (QString(othSType->GetName().c_str()) != nameEdit->text() || QString(othSType->GetShortName().c_str()) != shortNameEdit->text()
			|| QString(othSType->GetCode().c_str()) != codeEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetOthSTypeParams(nameEdit->text(), shortNameEdit->text(), codeEdit->text(), othSType->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateOtherStocksType(othSType, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{

						itemModel->item(mIndex.row(), 1)->setText(othSType->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(othSType->GetShortName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(othSType->GetCode().c_str());
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
			QString(tr("Please fill name, code and short name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateOthSTypeDlg::Close()
{
	this->parentWidget()->close();
}

