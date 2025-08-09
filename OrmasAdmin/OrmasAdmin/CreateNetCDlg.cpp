#include "stdafx.h"
#include "CreateNetCDlg.h"
#include "DataForm.h"



CreateNetCDlg::CreateNetCDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
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
		QObject::connect(okBtn, &QPushButton::released, this, &CreateNetCDlg::EditNetCost);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateNetCDlg::CreateNetCost);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateNetCDlg::Close);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateNetCDlg::OpenPrdDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreateNetCDlg::TextEditChanged);
	InitComboBox();
}

CreateNetCDlg::~CreateNetCDlg()
{
	delete vDouble;
	delete vInt;
}


void CreateNetCDlg::SetID(int ID, QString childName)
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
					currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(product.GetCompanyID())));
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

void CreateNetCDlg::SetNetCostParams(QString nDate, double nValue, int nProductID, int nCurrencyID, QString nIsOutdated, int id)
{
	netCost->SetDate(nDate.toUtf8().constData());
	netCost->SetValue(nValue);
	netCost->SetProductID(nProductID);
	netCost->SetCurrencyID(nCurrencyID);
	netCost->SetIsOutdated(nIsOutdated == "true" ? true : false);
	netCost->SetID(id);
}

void CreateNetCDlg::FillEditElements(QString nDate, double nValue, int nProductID, int nCurrencyID, QString nIsOutdated)
{
	dateEdit->setDateTime(QDateTime::fromString(nDate, "dd.MM.yyyy hh:mm"));
	valueEdit->setText(QString::number(nValue));
	productEdit->setText(QString::number(nProductID));
	int index = isOutdatedCmb->findText(nIsOutdated);
	isOutdatedCmb->setCurrentIndex(index);
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(nCurrencyID)));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), nProductID, errorMessage))
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

bool CreateNetCDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetNetCostParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
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

void CreateNetCDlg::CreateNetCost()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetNetCostParams(dateEdit->text(), valueEdit->text().toDouble(), productEdit->text().toInt(),
			currencyCmb->currentData().toInt(), isOutdatedCmb->currentText());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateNetCost(netCost, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Product *product = new BusinessLayer::Product;
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), netCost->GetProductID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), netCost->GetCurrencyID(), errorMessage))
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
					QList<QStandardItem*> NetCostItem;
					NetCostItem << new QStandardItem(QString::number(netCost->GetID()))
						<< new QStandardItem(netCost->GetDate().c_str())
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(product->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(QString::number(netCost->GetValue()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(netCost->GetCurrencyID()))
						<< new QStandardItem(QString::number(netCost->GetProductID()))
						<< new QStandardItem(netCost->GetIsOutdated() ? "true" : "false");;
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(NetCostItem);

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

void CreateNetCDlg::EditNetCost()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty())
	{
		if (QString(netCost->GetDate().c_str()) != dateEdit->text() || netCost->GetProductID() != productEdit->text().toInt()
			|| netCost->GetValue() != valueEdit->text().toDouble() || netCost->GetCurrencyID() != currencyCmb->currentData().toInt()
			|| QString(netCost->GetIsOutdated() ? "true" : "false") != isOutdatedCmb->currentText())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetNetCostParams(dateEdit->text(), valueEdit->text().toDouble(), productEdit->text().toInt(),
				currencyCmb->currentData().toInt(), isOutdatedCmb->currentText(), netCost->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateNetCost(netCost, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Product *product = new BusinessLayer::Product;
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), netCost->GetProductID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), netCost->GetCurrencyID(), errorMessage))
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
						
						itemModel->item(mIndex.row(), 1)->setText(netCost->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(product->GetVolume()));
						itemModel->item(mIndex.row(), 4)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(netCost->GetValue()));
						itemModel->item(mIndex.row(), 6)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(QString::number(netCost->GetCurrencyID()));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(netCost->GetProductID()));
						itemModel->item(mIndex.row(), 9)->setText(netCost->GetIsOutdated() ? "true" : "false");
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

void CreateNetCDlg::Close()
{
	this->parentWidget()->close();
}

void CreateNetCDlg::OpenPrdDlg()
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
	BusinessLayer::ProductType *pType = new BusinessLayer::ProductType();
	pType->SetCode("PRODUCT");
	std::string pTypeFilter = dialogBL->GenerateFilter<BusinessLayer::ProductType>(pType);
	std::vector<BusinessLayer::ProductType> pTypeVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductType>(errorMessage, pTypeFilter);
	if (pTypeVector.size() == 0)
	{
		delete pType;
		QString message = tr("Sorry could not find product type with \"Product\" code!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	BusinessLayer::Product *product = new BusinessLayer::Product();
	product->SetProductTypeID(pTypeVector.at(0).GetID());
	std::string productFilter = dialogBL->GenerateFilter<BusinessLayer::Product>(product);
	std::vector<BusinessLayer::ProductView> productVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductView>(errorMessage, productFilter);
	if (productVector.size() == 0)
	{
		delete product;
		QString message = tr("Sorry could not find product with \"product\" code!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	dForm->FillTable<BusinessLayer::ProductView>(errorMessage, productFilter);
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

void CreateNetCDlg::InitComboBox()
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

void CreateNetCDlg::TextEditChanged()
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
