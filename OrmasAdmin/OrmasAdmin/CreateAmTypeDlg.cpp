#include "stdafx.h"

#include "CreateAmTypeDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateAmTypeDlg::CreateAmTypeDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(100);
	codeEdit->setMaxLength(50);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAmTypeDlg::EditAmortizeType);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAmTypeDlg::CreateAmortizeType);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAmTypeDlg::Close);
}

void CreateAmTypeDlg::SetAmortizeTypeParams(QString aName, QString aCode, int id)
{
	amortizeType->SetName(aName.toUtf8().constData());
	amortizeType->SetCode(aCode.toUtf8().constData());
	amortizeType->SetID(id);
}

void CreateAmTypeDlg::FillEditElements(QString aName, QString aCode)
{
	nameEdit->setText(aName);
	codeEdit->setText(aCode);
}

bool CreateAmTypeDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetAmortizeTypeParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
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

void CreateAmTypeDlg::CreateAmortizeType()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetAmortizeTypeParams(nameEdit->text(),codeEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateAmortizeType(amortizeType, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> amortizeTypeItem;
					amortizeTypeItem << new QStandardItem(QString::number(amortizeType->GetID())) << new QStandardItem(amortizeType->GetName().c_str())
						<< new QStandardItem(amortizeType->GetCode().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(amortizeTypeItem);
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
			QString(tr("Please fill name, phone and address!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAmTypeDlg::EditAmortizeType()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		if (QString(amortizeType->GetName().c_str()) != nameEdit->text() || QString(amortizeType->GetCode().c_str()) != codeEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetAmortizeTypeParams(nameEdit->text(), codeEdit->text(),amortizeType->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateAmortizeType(amortizeType, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(amortizeType->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(amortizeType->GetCode().c_str());
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

void CreateAmTypeDlg::Close()
{
	this->parentWidget()->close();
}
