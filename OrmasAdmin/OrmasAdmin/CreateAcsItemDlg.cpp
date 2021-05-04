#include "stdafx.h"
#include "CreateAcsItemDlg.h"

#include "MainForm.h"
#include "DataForm.h"


CreateAcsItemDlg::CreateAcsItemDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	nameEngEdit->setMaxLength(30);
	nameRuEdit->setMaxLength(30);
	divisionEdit->setMaxLength(20);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAcsItemDlg::EditAccessItem);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAcsItemDlg::CreateAccessItem);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAcsItemDlg::Close);
}


void CreateAcsItemDlg::SetAccessItemParams(QString aiNameEng, QString aiNameRu, QString aiDivision, int id)
{
	accessItem->SetNameEng(aiNameEng.toUtf8().constData());
	accessItem->SetNameRu(aiNameRu.toUtf8().constData());
	accessItem->SetDivision(aiDivision.toUtf8().constData());
	accessItem->SetID(id);
}

void CreateAcsItemDlg::FillEditElements(QString aiNameEng, QString aiNameRu, QString aiDivision)
{
	nameEngEdit->setText(aiNameEng);
	nameRuEdit->setText(aiNameRu);
	divisionEdit->setText(aiDivision);
}

bool CreateAcsItemDlg::FillDlgElements(QTableView* aiTable)
{
	QModelIndex mIndex = aiTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetAccessItemParams(aiTable->model()->data(aiTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			aiTable->model()->data(aiTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			aiTable->model()->data(aiTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			aiTable->model()->data(aiTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(aiTable->model()->data(aiTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			aiTable->model()->data(aiTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			aiTable->model()->data(aiTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateAcsItemDlg::CreateAccessItem()
{
	errorMessage.clear();
	if (!(nameEngEdit->text().isEmpty() || nameRuEdit->text().isEmpty() || divisionEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetAccessItemParams(nameEngEdit->text(), nameRuEdit->text(), divisionEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateAccessItem(accessItem, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> accessListItem;
					accessListItem << new QStandardItem(QString::number(accessItem->GetID())) << new QStandardItem(accessItem->GetNameEng().c_str())
						<< new QStandardItem(accessItem->GetNameRu().c_str()) << new QStandardItem(accessItem->GetDivision().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(accessListItem);
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
			QString(tr("Please fill up name in english and in russia or division!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAcsItemDlg::EditAccessItem()
{
	errorMessage.clear();
	if (!(nameEngEdit->text().isEmpty() || nameRuEdit->text().isEmpty() || divisionEdit->text().isEmpty()))
	{
		if (QString(accessItem->GetNameEng().c_str()) != nameEngEdit->text() || QString(accessItem->GetNameRu().c_str()) != nameRuEdit->text()
			|| QString(accessItem->GetDivision().c_str()) != divisionEdit->text())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetAccessItemParams(nameEngEdit->text(), nameRuEdit->text(), divisionEdit->text(), accessItem->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateAccessItem(accessItem, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(accessItem->GetNameEng().c_str());
						itemModel->item(mIndex.row(), 2)->setText(accessItem->GetNameRu().c_str());
						itemModel->item(mIndex.row(), 3)->setText(accessItem->GetDivision().c_str());
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
			QString(tr("Please fill up name in english and in russia or division!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAcsItemDlg::Close()
{
	this->parentWidget()->close();
}
