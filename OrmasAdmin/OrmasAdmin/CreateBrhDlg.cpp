#include "stdafx.h"

#include "CreateBrhDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateBrhDlg::CreateBrhDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(60);
	addressEdit->setMaxLength(60);
	phoneEdit->setMaxLength(15);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateBrhDlg::EditBranch);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateBrhDlg::CreateBranch);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateBrhDlg::Close);
}

void CreateBrhDlg::SetBranchParams(QString cName, QString cAddress, QString cPhone, QString cComment, int id)
{
	branch->SetName(cName.toUtf8().constData());
	branch->SetAddress(cAddress.toUtf8().constData());
	branch->SetPhone(cPhone.toUtf8().constData());
	branch->SetComment(cComment.toUtf8().constData());
	branch->SetID(id);
}

void CreateBrhDlg::FillEditElements(QString cName, QString cAddress, QString cPhone, QString cComment)
{
	nameEdit->setText(cName);
	addressEdit->setText(cAddress);
	phoneEdit->setText(cPhone);
	commentTextEdit->setText(cComment);
}

bool CreateBrhDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetBranchParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateBrhDlg::CreateBranch()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || phoneEdit->text().isEmpty() || addressEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetBranchParams(nameEdit->text(), addressEdit->text(), phoneEdit->text(), commentTextEdit->toPlainText());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateBranch(branch, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> BranchItem;
					BranchItem << new QStandardItem(QString::number(branch->GetID())) << new QStandardItem(branch->GetName().c_str())
						<< new QStandardItem(branch->GetAddress().c_str()) << new QStandardItem(branch->GetPhone().c_str())
						<< new QStandardItem(branch->GetComment().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(BranchItem);
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

void CreateBrhDlg::EditBranch()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || phoneEdit->text().isEmpty() || addressEdit->text().isEmpty()))
	{
		if (QString(branch->GetName().c_str()) != nameEdit->text() || QString(branch->GetAddress().c_str()) != addressEdit->text()
			|| QString(branch->GetPhone().c_str()) != phoneEdit->text()
			|| QString(branch->GetComment().c_str()) != commentTextEdit->toPlainText())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetBranchParams(nameEdit->text(), addressEdit->text(), phoneEdit->text(), commentTextEdit->toPlainText(), branch->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateBranch(branch, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(branch->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(branch->GetAddress().c_str());
						itemModel->item(mIndex.row(), 3)->setText(branch->GetPhone().c_str());
						itemModel->item(mIndex.row(), 4)->setText(branch->GetComment().c_str());
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

void CreateBrhDlg::Close()
{
	this->parentWidget()->close();
}

