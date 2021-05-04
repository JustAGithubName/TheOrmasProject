#include "stdafx.h"

#include "CreateCmpDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateCmpDlg::CreateCmpDlg(BusinessLayer::OrmasBL *ormasBL,bool updateFlag ,QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(40);
	addressEdit->setMaxLength(40);
	phoneEdit->setMaxLength(20);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCmpDlg::EditCompany);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCmpDlg::CreateCompany);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateCmpDlg::Close);
	QObject::connect(commentTextEdit, &QTextEdit::textChanged, this, &CreateCmpDlg::TextEditChanged);
}

void CreateCmpDlg::SetCompanyParams(QString cName, QString cAddress, QString cPhone, QString cComment, int id)
{
	company->SetName(cName.toUtf8().constData());
	company->SetAddress(cAddress.toUtf8().constData());
	company->SetPhone(cPhone.toUtf8().constData());
	company->SetComment(cComment.toUtf8().constData());
	company->SetID(id);
}

void CreateCmpDlg::FillEditElements(QString cName, QString cAddress, QString cPhone, QString cComment)
{
	nameEdit->setText(cName);
	addressEdit->setText(cAddress);
	phoneEdit->setText(cPhone);
	commentTextEdit->setText(cComment);
}

bool CreateCmpDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetCompanyParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
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

void CreateCmpDlg::CreateCompany()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || phoneEdit->text().isEmpty() || addressEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetCompanyParams(nameEdit->text(), addressEdit->text(), phoneEdit->text(), commentTextEdit->toPlainText());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateCompany(company,errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> companyItem;
					companyItem << new QStandardItem(QString::number(company->GetID())) << new QStandardItem(company->GetName().c_str())
						<< new QStandardItem(company->GetAddress().c_str()) << new QStandardItem(company->GetPhone().c_str())
						<< new QStandardItem(company->GetComment().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(companyItem);
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

void CreateCmpDlg::EditCompany()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || phoneEdit->text().isEmpty() || addressEdit->text().isEmpty()))
	{
		if (QString(company->GetName().c_str()) != nameEdit->text() || QString(company->GetAddress().c_str()) != addressEdit->text()
			|| QString(company->GetPhone().c_str()) != phoneEdit->text()
			|| QString(company->GetComment().c_str()) != commentTextEdit->toPlainText())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetCompanyParams(nameEdit->text(), addressEdit->text(), phoneEdit->text(), commentTextEdit->toPlainText(), company->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateCompany(company, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(company->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(company->GetAddress().c_str());
						itemModel->item(mIndex.row(), 3)->setText(company->GetPhone().c_str());
						itemModel->item(mIndex.row(), 4)->setText(company->GetComment().c_str());
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

void CreateCmpDlg::Close()
{
	this->parentWidget()->close();
}

void CreateCmpDlg::TextEditChanged()
{
	if (commentTextEdit->toPlainText().length()> 100) {
		commentTextEdit->setPlainText(commentTextEdit->toPlainText().left(commentTextEdit->toPlainText().length() - 1));
		commentTextEdit->moveCursor(QTextCursor::End);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Warning: no more then ")) + QString::number(100) + QString(tr(" characters in this field")),
			QString(tr("Ok")));
	}
}
