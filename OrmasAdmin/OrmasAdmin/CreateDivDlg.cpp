#include "stdafx.h"

#include "CreateDivDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateDivDlg::CreateDivDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(100);
	codeEdit->setMaxLength(20);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateDivDlg::EditDivision);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateDivDlg::CreateDivision);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateDivDlg::Close);
}

void CreateDivDlg::SetDivisionParams(QString dName, QString dCode, int id)
{
	division->SetName(dName.toUtf8().constData());
	division->SetCode(dCode.toUtf8().constData());
	division->SetID(id);
}

void CreateDivDlg::FillEditElements(QString dName, QString dCode)
{
	nameEdit->setText(dName);
	codeEdit->setText(dCode);
}

bool CreateDivDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetDivisionParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateDivDlg::CreateDivision()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetDivisionParams(nameEdit->text(), codeEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateDivision(division, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> divisionItem;
					divisionItem << new QStandardItem(QString::number(division->GetID())) << new QStandardItem(division->GetName().c_str())
						<< new QStandardItem(division->GetCode().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(divisionItem);
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
			QString(tr("Please fill name and code!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateDivDlg::EditDivision()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		if (QString(division->GetName().c_str()) != nameEdit->text() || QString(division->GetCode().c_str()) != codeEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetDivisionParams(nameEdit->text(), codeEdit->text(), division->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateDivision(division, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(division->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(division->GetCode().c_str());
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
			QString(tr("Please fill name and code!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateDivDlg::Close()
{
	this->parentWidget()->close();
}
