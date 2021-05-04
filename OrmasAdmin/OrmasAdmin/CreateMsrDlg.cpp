#include "stdafx.h"

#include "CreateMsrDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreateMsrDlg::CreateMsrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	shortNameEdit->setMaxLength(4);
	nameEdit->setMaxLength(15);
	dialogBL = ormasBL;
	parentForm = parent;
	vInt = new QIntValidator(0, 1000000000, this);
	unitEdit->setValidator(vInt);
	unitEdit->setMaxLength(10);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateMsrDlg::EditMeasure);
	}
	else
	{
		unitEdit->setText("0");
		QObject::connect(okBtn, &QPushButton::released, this, &CreateMsrDlg::CreateMeasure);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateMsrDlg::Close);
}

CreateMsrDlg::~CreateMsrDlg()
{
	delete vInt;
}

void CreateMsrDlg::SetMeasureParams(QString mName, QString mShortName, int mUnit, int id)
{
	measure->SetName(mName.toUtf8().constData());
	measure->SetShortName(mShortName.toUtf8().constData());
	measure->SetUnit(mUnit);
	measure->SetID(id);
}

void CreateMsrDlg::FillEditElements(QString mName, QString mShortName, int mUnit)
{
	nameEdit->setText(mName);
	shortNameEdit->setText(mShortName);
	unitEdit->setText(QString::number(mUnit));
}

bool CreateMsrDlg::FillDlgElements(QTableView* mTable)
{
	QModelIndex mIndex = mTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetMeasureParams(mTable->model()->data(mTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			mTable->model()->data(mTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			mTable->model()->data(mTable->model()->index(mIndex.row(), 3)).toInt(),
			mTable->model()->data(mTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(mTable->model()->data(mTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			mTable->model()->data(mTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			mTable->model()->data(mTable->model()->index(mIndex.row(), 3)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateMsrDlg::CreateMeasure()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || shortNameEdit->text().isEmpty()) && 0 != unitEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetMeasureParams(nameEdit->text(), shortNameEdit->text(), unitEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateMeasure(measure,errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> measureItem;
					measureItem << new QStandardItem(QString::number(measure->GetID())) << new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(measure->GetShortName().c_str()) << new QStandardItem(QString::number(measure->GetUnit()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(measureItem);
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
			QString(tr("Please fill name and short name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateMsrDlg::EditMeasure()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || shortNameEdit->text().isEmpty()) || 0 != unitEdit->text().toInt())
	{
		if (QString(measure->GetName().c_str()) != nameEdit->text() || QString(measure->GetShortName().c_str()) != shortNameEdit->text()
			|| measure->GetUnit() != unitEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetMeasureParams(nameEdit->text(), shortNameEdit->text(), unitEdit->text().toInt(), measure->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateMeasure(measure,errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(shortNameEdit->text());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(unitEdit->text().toInt()));
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
			QString(tr("Please fill name and short name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateMsrDlg::Close()
{
	this->parentWidget()->close();
}
