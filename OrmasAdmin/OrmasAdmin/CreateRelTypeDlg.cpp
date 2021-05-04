#include "stdafx.h"

#include "CreateRelTypeDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreateRelTypeDlg::CreateRelTypeDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(20);
	dialogBL = ormasBL;
	parentForm = parent;
	nameEdit->setMaxLength(30);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRelTypeDlg::EditRelationType);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRelTypeDlg::CreateRelationType);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateRelTypeDlg::Close);
	QObject::connect(commentTextEdit, &QTextEdit::textChanged, this, &CreateRelTypeDlg::TextEditChanged);
}

void CreateRelTypeDlg::SetRelationTypeParams(QString rName, QString rComment, int id)
{
	relationType->SetName(rName.toUtf8().constData());
	relationType->SetComment(rComment.toUtf8().constData());
	relationType->SetID(id);
}

void CreateRelTypeDlg::FillEditElements(QString rName, QString rComment)
{
	nameEdit->setText(rName);
	commentTextEdit->setText(rComment);
}

bool CreateRelTypeDlg::FillDlgElements(QTableView* rTable)
{
	QModelIndex mIndex = rTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetRelationTypeParams(rTable->model()->data(rTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			rTable->model()->data(rTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			rTable->model()->data(rTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(rTable->model()->data(rTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			rTable->model()->data(rTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateRelTypeDlg::CreateRelationType()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetRelationTypeParams(nameEdit->text(), commentTextEdit->toPlainText());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateRelationType(relationType, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> relationTypeItem;
					relationTypeItem << new QStandardItem(QString::number(relationType->GetID())) << new QStandardItem(relationType->GetName().c_str())
						<< new QStandardItem(relationType->GetComment().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(relationTypeItem);
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

void CreateRelTypeDlg::EditRelationType()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty()))
	{
		if (QString(relationType->GetName().c_str()) != nameEdit->text() || QString(relationType->GetComment().c_str()) != commentTextEdit->toPlainText())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetRelationTypeParams(nameEdit->text(), commentTextEdit->toPlainText(), relationType->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateRelationType(relationType, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						
						itemModel->item(mIndex.row(), 1)->setText(relationType->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(relationType->GetComment().c_str());
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

void CreateRelTypeDlg::Close()
{
	this->parentWidget()->close();
}

void CreateRelTypeDlg::TextEditChanged()
{
	if (commentTextEdit->toPlainText().length()> 50) {
		commentTextEdit->setPlainText(commentTextEdit->toPlainText().left(commentTextEdit->toPlainText().length() - 1));
		commentTextEdit->moveCursor(QTextCursor::End);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Warning: no more then ")) + QString::number(100) + QString(tr(" characters in this field")),
			QString(tr("Ok")));
	}
}