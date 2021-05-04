#include "stdafx.h"

#include "CreateGrpDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateGrpDlg::CreateGrpDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(80);
	defenitionEdit->setMaxLength(80);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateGrpDlg::EditGroup);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateGrpDlg::CreateGroup);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateGrpDlg::Close);
}

void CreateGrpDlg::SetGroupParams(QString cName, QString cDefinition, int id)
{
	group->SetName(cName.toUtf8().constData());
	group->SetDefenition(cDefinition.toUtf8().constData());
	group->SetID(id);
}

void CreateGrpDlg::FillEditElements(QString cName, QString cDefinition)
{
	nameEdit->setText(cName);
	defenitionEdit->setText(cDefinition);
}

bool CreateGrpDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetGroupParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
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

void CreateGrpDlg::CreateGroup()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || defenitionEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetGroupParams(nameEdit->text(), defenitionEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateGroup(group, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> groupItem;
					groupItem << new QStandardItem(QString::number(group->GetID())) << new QStandardItem(group->GetName().c_str())
						<< new QStandardItem(group->GetDefenition().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(groupItem);
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
			QString(tr("Please fill name and definition!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateGrpDlg::EditGroup()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || defenitionEdit->text().isEmpty()))
	{
		if (QString(group->GetName().c_str()) != nameEdit->text() || QString(group->GetDefenition().c_str()) != defenitionEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetGroupParams(nameEdit->text(), defenitionEdit->text(), group->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateGroup(group, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(group->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(group->GetDefenition().c_str());
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

void CreateGrpDlg::Close()
{
	this->parentWidget()->close();
}