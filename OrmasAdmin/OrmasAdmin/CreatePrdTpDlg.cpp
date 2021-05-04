#include "stdafx.h"

#include "CreatePrdTpDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreatePrdTpDlg::CreatePrdTpDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePrdTpDlg::EditProductType);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePrdTpDlg::CreateProductType);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePrdTpDlg::Close);
}

void CreatePrdTpDlg::SetProdTypeParams(QString pName, QString pShortName, QString pCode, int id)
{
	prodType->SetName(pName.toUtf8().constData());
	prodType->SetShortName(pShortName.toUtf8().constData());
	prodType->SetCode(pShortName.toUtf8().constData());
	prodType->SetID(id);
}

void CreatePrdTpDlg::FillEditElements(QString pName, QString pShortName, QString pCode)
{
	nameEdit->setText(pName);
	shortNameEdit->setText(pShortName);
	codeEdit->setText(pCode);
}

bool CreatePrdTpDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetProdTypeParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
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

void CreatePrdTpDlg::CreateProductType()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || shortNameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetProdTypeParams(nameEdit->text(), shortNameEdit->text(), codeEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateProductType(prodType, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> prodTypeItem;
					prodTypeItem << new QStandardItem(QString::number(prodType->GetID())) << new QStandardItem(prodType->GetName().c_str())
						<< new QStandardItem(prodType->GetShortName().c_str()) << new QStandardItem(prodType->GetCode().c_str());
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

void CreatePrdTpDlg::EditProductType()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || shortNameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		if (QString(prodType->GetName().c_str()) != nameEdit->text() || QString(prodType->GetShortName().c_str()) != shortNameEdit->text()
			|| QString(prodType->GetCode().c_str()) != codeEdit->text())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetProdTypeParams(nameEdit->text(), shortNameEdit->text(), codeEdit->text(), prodType->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateProductType(prodType, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						
						itemModel->item(mIndex.row(), 1)->setText(prodType->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(prodType->GetShortName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(prodType->GetCode().c_str());
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

void CreatePrdTpDlg::Close()
{
	this->parentWidget()->close();
}

