#include "stdafx.h"
#include "CreatePrcDlg.h"
#include "DataForm.h"



CreatePrcDlg::CreatePrcDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 5, this);
	vInt = new QIntValidator(0, 1000000000, this);
	productEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble);
	valueEdit->setMaxLength(17);
	isOutdatedCmb->addItem("false");
	isOutdatedCmb->addItem("true");
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePrcDlg::EditPrice);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePrcDlg::CreatePrice);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePrcDlg::Close);
	QObject::connect(productBtn, &QPushButton::released, this, &CreatePrcDlg::OpenPrdDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreatePrcDlg::TextEditChanged);
	
	InitComboBox();
}

CreatePrcDlg::~CreatePrcDlg()
{
	delete vDouble;
	delete vInt;
}


void CreatePrcDlg::SetID(int ID, QString childName)
{
	if (0 != ID)
	{
		if (0 != childName.length())
		{
			this->hide();
			this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
			this->show();
			this->raise();
			this->activateWindow();
			QApplication::setActiveWindow(this);

			if (childName == QString("productForm"))
			{
				productEdit->setText(QString::number(ID));
				BusinessLayer::Product product;
				if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					prodNamePh->setText(product.GetName().c_str());
					volumePh->setText(QString::number(product.GetVolume()));
					BusinessLayer::Measure measure;
					if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
					{
						measurePh->setText(measure.GetShortName().c_str());
					}
				}
			}
		}
	}
}

void CreatePrcDlg::SetPriceParams(QString pDate, double pValue, int pProductID, int pCurrencyID, QString pIsOutdated, int id)
{
	price->SetDate(pDate.toUtf8().constData());
	price->SetValue(pValue);
	price->SetProductID(pProductID);
	price->SetCurrencyID(pCurrencyID);
	price->SetIsOutdated(pIsOutdated == "true" ? true : false);
	price->SetID(id);
}

void CreatePrcDlg::FillEditElements(QString pDate, double pValue, int pProductID, int pCurrencyID, QString pIsOutdated)
{
	dateEdit->setDateTime(QDateTime::fromString(pDate, "dd.MM.yyyy hh:mm"));
	valueEdit->setText(QString::number(pValue));
	productEdit->setText(QString::number(pProductID));
	int index = isOutdatedCmb->findText(pIsOutdated);
	isOutdatedCmb->setCurrentIndex(index);
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(pCurrencyID)));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pProductID, errorMessage))
	{
		prodNamePh->setText(product.GetName().c_str());
		volumePh->setText(QString::number(product.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetShortName().c_str());
		}
	}
}

bool CreatePrcDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetPriceParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePrcDlg::CreatePrice()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetPriceParams(dateEdit->text(), valueEdit->text().toDouble(), productEdit->text().toInt(), 
			currencyCmb->currentData().toInt(), isOutdatedCmb->currentText());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreatePrice(price, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Product *product = new BusinessLayer::Product;
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), price->GetProductID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), price->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete product;
						delete currency;

						return;
					}
					BusinessLayer::Measure *measure = new BusinessLayer::Measure();
					if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete measure;
					}
					QList<QStandardItem*> PriceItem;
					PriceItem << new QStandardItem(QString::number(price->GetID()))
						<< new QStandardItem(price->GetDate().c_str())
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(product->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(QString::number(price->GetValue()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(price->GetCurrencyID()))
						<< new QStandardItem(QString::number(price->GetProductID()))
						<< new QStandardItem(price->GetIsOutdated() ? "true" : "false");;
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(PriceItem);
					delete product;
					delete currency;
					delete measure;
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
			QString(tr("Please fill user, value, date and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePrcDlg::EditPrice()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty())
	{
		if (QString(price->GetDate().c_str()) != dateEdit->text() || price->GetProductID() != productEdit->text().toInt()
			|| price->GetValue() != valueEdit->text().toDouble() || price->GetCurrencyID() != currencyCmb->currentData().toInt()
			|| QString(price->GetIsOutdated() ? "true" : "false") != isOutdatedCmb->currentText())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetPriceParams(dateEdit->text(), valueEdit->text().toDouble(), productEdit->text().toInt(), 
				currencyCmb->currentData().toInt(), isOutdatedCmb->currentText(), price->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdatePrice(price, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Product *product = new BusinessLayer::Product;
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), price->GetProductID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), price->GetCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete product;
							delete currency;

							return;
						}
						BusinessLayer::Measure *measure = new BusinessLayer::Measure();
						if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete measure;
						}
						
						itemModel->item(mIndex.row(), 1)->setText(price->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(product->GetVolume()));
						itemModel->item(mIndex.row(), 4)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(price->GetValue()));
						itemModel->item(mIndex.row(), 6)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(QString::number(price->GetCurrencyID()));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(price->GetProductID()));
						itemModel->item(mIndex.row(), 9)->setText(price->GetIsOutdated() ? "true" : "false");
						emit itemModel->dataChanged(mIndex, mIndex);
						delete product;
						delete currency;
						delete measure;
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
			QString(tr("Please fill user, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePrcDlg::Close()
{
	this->parentWidget()->close();
}

void CreatePrcDlg::OpenPrdDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Products"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ProductView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("productForm");
		dForm->QtConnect<BusinessLayer::ProductView>();
		QMdiSubWindow *productWindow = new QMdiSubWindow;
		productWindow->setWidget(dForm);
		productWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(productWindow);
		productWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All products are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreatePrcDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			if (curVector[i].GetMainTrade() == true)
				currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
}

void CreatePrcDlg::TextEditChanged()
{
	if (valueEdit->text().contains(","))
	{
		valueEdit->setText(valueEdit->text().replace(",", "."));
	}
	if (valueEdit->text().contains(".."))
	{
		valueEdit->setText(valueEdit->text().replace("..", "."));
	}
}
