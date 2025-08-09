#include "stdafx.h"

#include "CreateCurRateDlg.h"
#include "MainForm.h"
#include "DataForm.h"


CreateCurRateDlg::CreateCurRateDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 5, this);
	fromValueEdit->setValidator(vDouble);
	toValueEdit->setValidator(vDouble);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCurRateDlg::EditCurrencyRate);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCurRateDlg::CreateCurrencyRate);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateCurRateDlg::Close);
	QObject::connect(fromValueEdit, &QLineEdit::textChanged, this, &CreateCurRateDlg::TextEditChanged);
	QObject::connect(toValueEdit, &QLineEdit::textChanged, this, &CreateCurRateDlg::TextEditChanged);
	InitComboBox();
}

CreateCurRateDlg::~CreateCurRateDlg()
{
	delete vDouble;
}

void CreateCurRateDlg::SetCurrencyRateParams(int fromID, double fromValue, int toID, double toValue, QString rDate, int id)
{
	currencyRate->SetFromCurrencyID(fromID);
	currencyRate->SetFromValue(fromValue);
	currencyRate->SetToCurrencyID(toID);
	currencyRate->SetToValue(toValue);
	currencyRate->SetChangeDate(rDate.toUtf8().constData());
	currencyRate->SetID(id);
}

void CreateCurRateDlg::FillEditElements(int fromID, double fromValue, int toID, double toValue, QString rDate)
{
	dateEdit->setDate(QDate::fromString(rDate, "dd.MM.yyyy"));
	fromCurrencyCmb->setCurrentIndex(fromCurrencyCmb->findData(QVariant(fromID)));
	fromValueEdit->setText(QString::number(fromValue));
	toCurrencyCmb->setCurrentIndex(toCurrencyCmb->findData(QVariant(toID)));
	toValueEdit->setText(QString::number(toValue));
}

bool CreateCurRateDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetCurrencyRateParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 6)).toString().toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 6)).toString().toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateCurRateDlg::CreateCurrencyRate()
{
	errorMessage.clear();
	if (!dateEdit->text().isEmpty() || 0 != fromCurrencyCmb->currentData().toInt() || 0 != toCurrencyCmb->currentData().toInt() || fromValueEdit->text().isEmpty()
		|| toValueEdit->text().isEmpty())
	{
		if (fromCurrencyCmb->currentData().toInt() == toCurrencyCmb->currentData().toInt())
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("From currency must not be the same as to currency!")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetCurrencyRateParams(fromCurrencyCmb->currentData().toInt(), fromValueEdit->text().toDouble(), toCurrencyCmb->currentData().toInt(), toValueEdit->text().toDouble(),
			dateEdit->text());
		BusinessLayer::Currency fromCur;
		BusinessLayer::Currency toCur;
		

		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateCurrencyRate(currencyRate, errorMessage))
		{
			
			
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					if (!fromCur.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyRate->GetFromCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
					if (!toCur.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyRate->GetToCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
					QList<QStandardItem*> companyItem;
					companyItem << new QStandardItem(QString::number(currencyRate->GetID())) 
						<< new QStandardItem(fromCur.GetShortName().c_str())
						<< new QStandardItem(QString::number(currencyRate->GetFromValue(),'f',3))
						<< new QStandardItem(toCur.GetShortName().c_str())
						<< new QStandardItem(QString::number(currencyRate->GetToValue(), 'f', 3))
						<< new QStandardItem(QString::number(currencyRate->GetFromCurrencyID()))
						<< new QStandardItem(QString::number(currencyRate->GetToCurrencyID()))
						<< new QStandardItem(currencyRate->GetChangeDate().c_str());
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
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please fill code, name and short name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCurRateDlg::EditCurrencyRate()
{
	errorMessage.clear();
	if (!dateEdit->text().isEmpty() || 0 != fromCurrencyCmb->currentData().toInt() || 0 != toCurrencyCmb->currentData().toInt() || fromValueEdit->text().isEmpty()
		|| toValueEdit->text().isEmpty())
	{
		if (fromCurrencyCmb->currentData().toInt() != currencyRate->GetFromCurrencyID() || toCurrencyCmb->currentData().toInt() != currencyRate->GetToCurrencyID()
			|| fromValueEdit->text().toDouble() != currencyRate->GetFromValue() || toValueEdit->text().toDouble() != currencyRate->GetToValue())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetCurrencyRateParams(fromCurrencyCmb->currentData().toInt(), fromValueEdit->text().toDouble(), toCurrencyCmb->currentData().toInt(), toValueEdit->text().isEmpty(),
				dateEdit->text(), currencyRate->GetID());
			BusinessLayer::Currency fromCur;
			BusinessLayer::Currency toCur;

			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateCurrencyRate(currencyRate, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						if (!fromCur.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyRate->GetFromCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
						if (!toCur.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyRate->GetToCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
						itemModel->item(mIndex.row(), 1)->setText(fromCur.GetShortName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(currencyRate->GetFromValue()));
						itemModel->item(mIndex.row(), 3)->setText(toCur.GetShortName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(currencyRate->GetToValue()));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(currencyRate->GetFromCurrencyID()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(currencyRate->GetToCurrencyID()));
						itemModel->item(mIndex.row(), 7)->setText(currencyRate->GetChangeDate().c_str());
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
			QString(tr("Please fill code, name and short name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCurRateDlg::Close()
{
	this->parentWidget()->close();
}

void CreateCurRateDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			if (curVector[i].GetMainTrade() != true)
			{
				fromCurrencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
			}
			else
			{
				toCurrencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
			}
		}
	}

}

void CreateCurRateDlg::TextEditChanged()
{

	if (fromValueEdit->text().contains(","))
	{
		fromValueEdit->setText(fromValueEdit->text().replace(",", "."));
	}
	if (fromValueEdit->text().contains(".."))
	{
		fromValueEdit->setText(fromValueEdit->text().replace("..", "."));
	}
	if (toValueEdit->text().contains(","))
	{
		toValueEdit->setText(toValueEdit->text().replace(",", "."));
	}
	if (toValueEdit->text().contains(".."))
	{
		toValueEdit->setText(toValueEdit->text().replace("..", "."));
	}
}