#include "stdafx.h"
#include "CreateRoleDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreateRoleDlg::CreateRoleDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(50);
	codeEdit->setMaxLength(20);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRoleDlg::EditRole);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRoleDlg::CreateRole);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateRoleDlg::Close);
	QObject::connect(commentTextEdit, &QTextEdit::textChanged, this, &CreateRoleDlg::TextEditChanged);
}

void CreateRoleDlg::SetRoleParams(QString rCode, QString rName, QString rComment, int id)
{
	role->SetCode(rCode.toUtf8().constData());
	role->SetName(rName.toUtf8().constData());
	role->SetComment(rComment.toUtf8().constData());
	role->SetID(id);
}

void CreateRoleDlg::FillEditElements(QString rCode, QString rName, QString rComment)
{
	codeEdit->setText(rCode);
	nameEdit->setText(rName);
	commentTextEdit->setText(rComment);
}

bool CreateRoleDlg::FillDlgElements(QTableView* rTable)
{
	QModelIndex mIndex = rTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetRoleParams(rTable->model()->data(rTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			rTable->model()->data(rTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			rTable->model()->data(rTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			rTable->model()->data(rTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(rTable->model()->data(rTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			rTable->model()->data(rTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			rTable->model()->data(rTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateRoleDlg::CreateRole()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetRoleParams(codeEdit->text(), nameEdit->text(), commentTextEdit->toPlainText());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateRole(role, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> roleItem;
					roleItem << new QStandardItem(QString::number(role->GetID()))
						<< new QStandardItem(role->GetCode().c_str())
						<< new QStandardItem(role->GetName().c_str())
						<< new QStandardItem(role->GetComment().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(roleItem);
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
			QString(tr("Please fill the name and code!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateRoleDlg::EditRole()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		if (QString(role->GetCode().c_str()) != codeEdit->text() || QString(role->GetName().c_str()) != nameEdit->text() ||
			QString(role->GetComment().c_str()) != commentTextEdit->toPlainText())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetRoleParams(codeEdit->text(), nameEdit->text(), commentTextEdit->toPlainText(), role->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateRole(role, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						
						itemModel->item(mIndex.row(), 1)->setText(role->GetCode().c_str());
						itemModel->item(mIndex.row(), 2)->setText(role->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(role->GetComment().c_str());
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
			QString(tr("Please fill the name and code!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateRoleDlg::Close()
{
	this->parentWidget()->close();
}

void CreateRoleDlg::TextEditChanged()
{
	if (commentTextEdit->toPlainText().length()> 50) {
		commentTextEdit->setPlainText(commentTextEdit->toPlainText().left(commentTextEdit->toPlainText().length() - 1));
		commentTextEdit->moveCursor(QTextCursor::End);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Warning: no more then ")) + QString::number(100) + QString(tr(" characters in this field")),
			QString(tr("Ok")));
	}
}