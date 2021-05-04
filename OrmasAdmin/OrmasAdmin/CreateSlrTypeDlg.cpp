#include "stdafx.h"

#include "CreateSlrTypeDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreateSlrTypeDlg::CreateSlrTypeDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	codeEdit->setMaxLength(6);
	nameEdit->setMaxLength(30);
	dialogBL = ormasBL;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateSlrTypeDlg::EditSalaryType);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateSlrTypeDlg::CreateSalaryType);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateSlrTypeDlg::Close);
}

void CreateSlrTypeDlg::SetSalaryTypeParams(QString sCode, QString sName, int id)
{
	salaryType->SetCode(sCode.toUtf8().constData());
	salaryType->SetName(sName.toUtf8().constData());
	salaryType->SetID(id);
}

void CreateSlrTypeDlg::FillEditElements(QString sCode, QString sName)
{
	codeEdit->setText(sCode);
	nameEdit->setText(sName);
}

bool CreateSlrTypeDlg::FillDlgElements(QTableView* sTable)
{
	QModelIndex mIndex = sTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetSalaryTypeParams(sTable->model()->data(sTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(sTable->model()->data(sTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateSlrTypeDlg::CreateSalaryType()
{
	errorMessage.clear();
	if (!(codeEdit->text().isEmpty() || nameEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetSalaryTypeParams(codeEdit->text(), nameEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateSalaryType(salaryType, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> salaryTypeItem;
					salaryTypeItem << new QStandardItem(QString::number(salaryType->GetID())) << new QStandardItem(salaryType->GetCode().c_str())
						<< new QStandardItem(salaryType->GetName().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(salaryTypeItem);
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

void CreateSlrTypeDlg::EditSalaryType()
{
	errorMessage.clear();
	if (!(codeEdit->text().isEmpty() || nameEdit->text().isEmpty()))
	{
		if (QString(salaryType->GetCode().c_str()) != codeEdit->text() || QString(salaryType->GetName().c_str()) != nameEdit->text())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetSalaryTypeParams(codeEdit->text(), nameEdit->text(), salaryType->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateSalaryType(salaryType, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						
						itemModel->item(mIndex.row(), 1)->setText(salaryType->GetCode().c_str());
						itemModel->item(mIndex.row(), 2)->setText(salaryType->GetName().c_str());
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

void CreateSlrTypeDlg::Close()
{
	this->parentWidget()->close();
}
