#include "stdafx.h"

#include "CreateAmGrDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateAmGrDlg::CreateAmGrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	vInt = new QIntValidator(0, 1000000000, this);
	gNumberEdit->setValidator(vInt);
	fromMonthEdit->setValidator(vInt);
	toMonthEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAmGrDlg::EditAmortizeGroup);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAmGrDlg::CreateAmortizeGroup);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAmGrDlg::Close);
}

CreateAmGrDlg::~CreateAmGrDlg()
{
	delete vInt;
}


void CreateAmGrDlg::SetAmortizeGroupParams(int gNumber, int fromMonth, int toMonth, int id)
{
	amortizeGroup->SetGroupNumber(gNumber);
	amortizeGroup->SetFromMonth(fromMonth);
	amortizeGroup->SetToMonth(toMonth);
	amortizeGroup->SetID(id);
}

void CreateAmGrDlg::FillEditElements(int gNumber, int fromMonth, int tillMonth)
{
	gNumberEdit->setText(QString::number(gNumber));
	fromMonthEdit->setText(QString::number(fromMonth));
	toMonthEdit->setText(QString::number(tillMonth));
}

bool CreateAmGrDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetAmortizeGroupParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateAmGrDlg::CreateAmortizeGroup()
{
	errorMessage.clear();
	if (0 != gNumberEdit->text().toInt() && 0 != fromMonthEdit->text().toInt() && 0 != toMonthEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetAmortizeGroupParams(gNumberEdit->text().toInt(), fromMonthEdit->text().toInt(), toMonthEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateAmortizeGroup(amortizeGroup, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> amortizeGroupItem;
					amortizeGroupItem << new QStandardItem(QString::number(amortizeGroup->GetID()))
						<< new QStandardItem(QString::number(amortizeGroup->GetGroupNumber()))
						<< new QStandardItem(QString::number(amortizeGroup->GetFromMonth()))
						<< new QStandardItem(QString::number(amortizeGroup->GetToMonth()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(amortizeGroupItem);
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

void CreateAmGrDlg::EditAmortizeGroup()
{
	errorMessage.clear();
	if (0 != gNumberEdit->text().toInt() && 0 != fromMonthEdit->text().toInt() && 0 != toMonthEdit->text().toInt())
	{
		if (gNumberEdit->text().toInt() != amortizeGroup->GetGroupNumber() || fromMonthEdit->text().toInt() != amortizeGroup->GetFromMonth() 
			|| toMonthEdit->text().toInt() != amortizeGroup->GetToMonth())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetAmortizeGroupParams(gNumberEdit->text().toInt(), fromMonthEdit->text().toInt(), toMonthEdit->text().toInt(), amortizeGroup->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateAmortizeGroup(amortizeGroup, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(QString::number(amortizeGroup->GetGroupNumber()));
						itemModel->item(mIndex.row(), 2)->setText(QString::number(amortizeGroup->GetFromMonth()));
						itemModel->item(mIndex.row(), 3)->setText(QString::number(amortizeGroup->GetToMonth()));
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

void CreateAmGrDlg::Close()
{
	this->parentWidget()->close();
}
