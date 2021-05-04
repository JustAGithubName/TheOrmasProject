#include "stdafx.h"

#include "CreatePosDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreatePosDlg::CreatePosDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(20);
	dialogBL = ormasBL;
	parentForm = parent;
	nameEdit->setMaxLength(50);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePosDlg::EditPosition);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePosDlg::CreatePosition);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePosDlg::Close);
}

void CreatePosDlg::SetPositionParams(QString rName, int id)
{
	position->SetName(rName.toUtf8().constData());
	position->SetID(id);
}

void CreatePosDlg::FillEditElements(QString rName)
{
	nameEdit->setText(rName);
}

bool CreatePosDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetPositionParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePosDlg::CreatePosition()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetPositionParams(nameEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreatePosition(position, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> PositionItem;
					PositionItem << new QStandardItem(QString::number(position->GetID())) << new QStandardItem(position->GetName().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(PositionItem);
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
			QString(tr("Please fill the name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePosDlg::EditPosition()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty()))
	{
		if (QString(position->GetName().c_str()) != nameEdit->text())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetPositionParams(nameEdit->text(), position->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdatePosition(position, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						
						itemModel->item(mIndex.row(), 1)->setText(position->GetName().c_str());
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
			QString(tr("Please fill the name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePosDlg::Close()
{
	this->parentWidget()->close();
}
