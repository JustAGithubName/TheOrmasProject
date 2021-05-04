#include "stdafx.h"

#include "CreateWrhTpDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreateWrhTypeDlg::CreateWrhTypeDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	codeEdit->setMaxLength(20);
	nameEdit->setMaxLength(60);
	purposeEdit->setMaxLength(60);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWrhTypeDlg::EditWarehouseType);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWrhTypeDlg::CreateWarehouseType);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateWrhTypeDlg::Close);
}

void CreateWrhTypeDlg::SetWarehouseTypeParams(QString wCode, QString wPurpose, QString wName, int id)
{
	warehouseType->SetCode(wCode.toUtf8().constData());
	warehouseType->SetPurpose(wPurpose.toUtf8().constData());
	warehouseType->SetName(wName.toUtf8().constData());
	warehouseType->SetID(id);
}

void CreateWrhTypeDlg::FillEditElements(QString wCode, QString wPurpose, QString wName)
{
	codeEdit->setText(wCode);
	purposeEdit->setText(wPurpose);
	nameEdit->setText(wName);
}

bool CreateWrhTypeDlg::FillDlgElements(QTableView* sTable)
{
	QModelIndex mIndex = sTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetWarehouseTypeParams(sTable->model()->data(sTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(sTable->model()->data(sTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateWrhTypeDlg::CreateWarehouseType()
{
	errorMessage.clear();
	if (!(codeEdit->text().isEmpty() || nameEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetWarehouseTypeParams(codeEdit->text(), purposeEdit->text() ,nameEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateWarehouseType(warehouseType, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> WarehouseTypeItem;
					WarehouseTypeItem << new QStandardItem(QString::number(warehouseType->GetID())) 
						<< new QStandardItem(warehouseType->GetCode().c_str())
						<< new QStandardItem(warehouseType->GetPurpose().c_str())
						<< new QStandardItem(warehouseType->GetName().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(WarehouseTypeItem);
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
			QString(tr("Please fill code and name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateWrhTypeDlg::EditWarehouseType()
{
	errorMessage.clear();
	if (!(codeEdit->text().isEmpty() || nameEdit->text().isEmpty()))
	{
		if (QString(warehouseType->GetCode().c_str()) != codeEdit->text() || QString(warehouseType->GetName().c_str()) != nameEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetWarehouseTypeParams(codeEdit->text(), purposeEdit->text(), nameEdit->text(), warehouseType->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateWarehouseType(warehouseType, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{

						itemModel->item(mIndex.row(), 1)->setText(warehouseType->GetCode().c_str());
						itemModel->item(mIndex.row(), 2)->setText(warehouseType->GetPurpose().c_str());
						itemModel->item(mIndex.row(), 3)->setText(warehouseType->GetName().c_str());
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
			QString(tr("Please fill code and name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateWrhTypeDlg::Close()
{
	this->parentWidget()->close();
}