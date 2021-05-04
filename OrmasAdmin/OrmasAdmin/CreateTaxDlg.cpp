#include "stdafx.h"

#include "CreateTaxDlg.h"
#include "MainForm.h"
#include "DataForm.h"



CreateTaxDlg::CreateTaxDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	nameEdit->setMaxLength(100);
	codeEdit->setMaxLength(15);
	formulaEdit->setMaxLength(100);
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	fixedEdit->setValidator(vDouble);
	percentEdit->setValidator(vInt);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateTaxDlg::EditTax);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateTaxDlg::CreateTax);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateTaxDlg::Close);
}

CreateTaxDlg::~CreateTaxDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateTaxDlg::SetTaxParams(QString tName, QString tCode, double tFixed, int tPercent, QString tFormula, int id)
{
	tax->SetName(tName.toUtf8().constData());
	tax->SetCode(tCode.toUtf8().constData());
	tax->SetFixedValue(tFixed);
	tax->SetPercentValue(tPercent);
	tax->SetFormulaValue(tFormula.toUtf8().constData());
	tax->SetID(id);
}

void CreateTaxDlg::FillEditElements(QString tName, QString tCode, double tFixed, int tPercent, QString tFormula)
{
	nameEdit->setText(tName);
	codeEdit->setText(tCode);
	fixedEdit->setText(QString::number(tFixed));
	percentEdit->setText(QString::number(tPercent));
	formulaEdit->setText(tFormula);
}

bool CreateTaxDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetTaxParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateTaxDlg::CreateTax()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetTaxParams(nameEdit->text(), codeEdit->text(), fixedEdit->text().toDouble(), percentEdit->text().toInt(), formulaEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateTax(tax, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> TaxItem;
					TaxItem << new QStandardItem(QString::number(tax->GetID())) 
						<< new QStandardItem(tax->GetName().c_str())
						<< new QStandardItem(tax->GetCode().c_str())
						<< new QStandardItem(QString::number(tax->GetFixedValue()))
						<< new QStandardItem(QString::number(tax->GetPercentValue()))
						<< new QStandardItem(tax->GetFormulaValue().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(TaxItem);
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
			QString(tr("Please fill name, code and one of values!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateTaxDlg::EditTax()
{
	errorMessage.clear();
	if (!(nameEdit->text().isEmpty() || codeEdit->text().isEmpty()))
	{
		if (QString(tax->GetName().c_str()) != nameEdit->text() || QString(tax->GetCode().c_str()) != codeEdit->text()
			|| QString(tax->GetFormulaValue().c_str()) != formulaEdit->text()
			|| tax->GetFixedValue() != fixedEdit->text().toDouble() || tax->GetPercentValue() != percentEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetTaxParams(nameEdit->text(), codeEdit->text(), fixedEdit->text().toDouble(), percentEdit->text().toInt(), formulaEdit->text(), tax->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateTax(tax, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						
						itemModel->item(mIndex.row(), 1)->setText(tax->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(tax->GetCode().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(tax->GetFixedValue()));
						itemModel->item(mIndex.row(), 4)->setText(QString::number(tax->GetPercentValue()));
						itemModel->item(mIndex.row(), 5)->setText(tax->GetFormulaValue().c_str());
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
			QString(tr("Please fill name, code and one of values!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateTaxDlg::Close()
{
	this->parentWidget()->close();
}
