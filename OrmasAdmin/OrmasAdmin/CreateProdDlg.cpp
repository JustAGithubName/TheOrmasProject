#include "stdafx.h"

#include "CreateProdDlg.h"
#include "DataForm.h"



CreateProdDlg::CreateProdDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 5, this);
	vInt = new QIntValidator(0, 1000000000, this);
	companyEdit->setValidator(vInt);
	shelfLifeEdit->setValidator(vInt);
	volumeEdit->setValidator(vDouble);
	volumeEdit->setMaxLength(17);
	priceEdit->setValidator(vDouble);
	priceEdit->setMaxLength(17);
	nameEdit->setMaxLength(50);
	
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateProdDlg::EditProduct);
	}
	else
	{
		companyEdit->setText("0");
		shelfLifeEdit->setText("0");
		priceEdit->setText("0");
		volumeEdit->setText("0");
		QObject::connect(okBtn, &QPushButton::released, this, &CreateProdDlg::CreateProduct);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateProdDlg::Close);
	QObject::connect(companyBtn, &QPushButton::released, this, &CreateProdDlg::OpenCmpDlg);
	QObject::connect(volumeEdit, &QLineEdit::textChanged, this, &CreateProdDlg::TextEditChanged);
	QObject::connect(priceEdit, &QLineEdit::textChanged, this, &CreateProdDlg::TextEditChanged);
	InitComboBox();
}

CreateProdDlg::~CreateProdDlg()
{
	delete vDouble;
	delete vInt;
}

void CreateProdDlg::SetID(int ID, QString childName)
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

			if (childName == QString("companyForm"))
			{
				companyEdit->setText(QString::number(ID));
				BusinessLayer::Company company;
				if (company.GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					companyNamePh->setText(company.GetName().c_str());
				}
			}
		}
	}
}

void CreateProdDlg::SetProductParams(int pCountryID, QString pProductName, double pVolume, int pMeasureID, double pPrice, 
	int pProductTypeID, int pShelfLife, int pCurrencyID, int id)
{
	product->SetCompanyID(pCountryID);
	product->SetName(pProductName.toUtf8().constData());
	product->SetVolume(pVolume);
	product->SetMeasureID(pMeasureID);
	product->SetPrice(pPrice);
	product->SetProductTypeID(pProductTypeID);
	product->SetShelfLife(pShelfLife);
	product->SetCurrencyID(pCurrencyID);
	product->SetID(id);
}

void CreateProdDlg::FillEditElements(int pCompanyID, QString pProductName, double pVolume, int pMeasureID, double pPrice,
	int pProductTypeID, int pShelfLife, int pCurrencyID)
{
	companyEdit->setText(QString::number(pCompanyID));
	nameEdit->setText(pProductName);
	volumeEdit->setText(QString::number(pVolume));
	priceEdit->setText(QString::number(pPrice));
	prodTypeCmb->setCurrentIndex(prodTypeCmb->findData(QVariant(pProductTypeID)));
	shelfLifeEdit->setText(QString::number(pShelfLife));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(pCurrencyID)));
	measureCmb->setCurrentIndex(measureCmb->findData(QVariant(pMeasureID)));
	BusinessLayer::Company company;
	if (company.GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pCompanyID, errorMessage))
	{
		companyNamePh->setText(company.GetName().c_str());
	}
}

bool CreateProdDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetProductParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateProdDlg::CreateProduct()
{
	errorMessage.clear();
	if (0 != companyEdit->text().toInt() && !nameEdit->text().isEmpty() && 0 != volumeEdit->text().toInt()
		&& !measureCmb->currentText().isEmpty() && 0 != priceEdit->text()
		&& !prodTypeCmb->currentText().isEmpty() && 0 != shelfLifeEdit->text().toInt() && !currencyCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetProductParams(companyEdit->text().toInt(), nameEdit->text(), volumeEdit->text().toDouble(), measureCmb->currentData().toInt(),
			priceEdit->text().toDouble(), prodTypeCmb->currentData().toInt(), shelfLifeEdit->text().toInt(), currencyCmb->currentData().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateProduct(product, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Company *company = new BusinessLayer::Company();
					BusinessLayer::Measure *measure = new BusinessLayer::Measure();
					BusinessLayer::ProductType *prodType = new BusinessLayer::ProductType();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency();

					if (!company->GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetCompanyID(), errorMessage)
						|| !measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage)
						|| !prodType->GetProductTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetProductTypeID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete company;
						delete measure;
						delete prodType;
						delete currency;
						return;
					}
					QList<QStandardItem*> ProductionItem;
					ProductionItem << new QStandardItem(QString::number(product->GetID()))
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(product->GetPrice()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(product->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(prodType->GetShortName().c_str())
						<< new QStandardItem(QString::number(product->GetShelfLife()))
						<< new QStandardItem(company->GetName().c_str())
						<< new QStandardItem(QString::number(product->GetCompanyID()))
						<< new QStandardItem(QString::number(product->GetMeasureID()))
						<< new QStandardItem(QString::number(product->GetProductTypeID()))
						<< new QStandardItem(QString::number(product->GetCurrencyID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(ProductionItem);
					delete company;
					delete measure;
					delete prodType;
					delete currency;
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateProdDlg::EditProduct()
{
	errorMessage.clear();
	if (0 != companyEdit->text().toInt() && !nameEdit->text().isEmpty() && 0 != volumeEdit->text().toInt()
		&& !measureCmb->currentText().isEmpty() && 0 != priceEdit->text()
		&& !prodTypeCmb->currentText().isEmpty() && 0 != shelfLifeEdit->text().toInt() && !currencyCmb->currentText().isEmpty())
	{
		if (product->GetCompanyID() != companyEdit->text().toInt() || QString(product->GetName().c_str()) != nameEdit->text() || 
			product->GetVolume() != volumeEdit->text().toDouble() || product->GetMeasureID() != measureCmb->currentData().toInt() ||
			product->GetPrice() != priceEdit->text().toDouble() || product->GetProductTypeID() != prodTypeCmb->currentData().toInt() ||
			product->GetShelfLife() != shelfLifeEdit->text().toInt() || product->GetCurrencyID() != currencyCmb->currentData().toInt())
			{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetProductParams(companyEdit->text().toInt(), nameEdit->text(), volumeEdit->text().toDouble(), measureCmb->currentData().toInt(),
				priceEdit->text().toDouble(), prodTypeCmb->currentData().toInt(), shelfLifeEdit->text().toInt(), currencyCmb->currentData().toInt(),
				product->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateProduct(product, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						
						itemModel->item(mIndex.row(), 1)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(product->GetPrice()));

						BusinessLayer::Company *company = new BusinessLayer::Company();
						BusinessLayer::Measure *measure = new BusinessLayer::Measure();
						BusinessLayer::ProductType *prodType = new BusinessLayer::ProductType();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();

						if (!company->GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetCompanyID(), errorMessage)
							|| !measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage)
							|| !prodType->GetProductTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetProductTypeID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete company;
							delete measure;
							delete prodType;
							delete currency;
							return;
						}

						itemModel->item(mIndex.row(), 3)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(product->GetVolume()));
						itemModel->item(mIndex.row(), 5)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(prodType->GetShortName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(shelfLifeEdit->text());
						itemModel->item(mIndex.row(), 8)->setText(company->GetName().c_str());
						itemModel->item(mIndex.row(), 9)->setText(QString::number(product->GetCompanyID()));
						itemModel->item(mIndex.row(), 10)->setText(QString::number(product->GetMeasureID()));
						itemModel->item(mIndex.row(), 11)->setText(QString::number(product->GetProductTypeID()));
						itemModel->item(mIndex.row(), 12)->setText(QString::number(product->GetCurrencyID()));

						emit itemModel->dataChanged(mIndex, mIndex);

						delete company;
						delete measure;
						delete prodType;
						delete currency;
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateProdDlg::Close()
{
	this->parentWidget()->close();
}

void CreateProdDlg::OpenCmpDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Companies"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Company>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("companyForm");
		dForm->QtConnect<BusinessLayer::Company>();
		QMdiSubWindow *companyWindow = new QMdiSubWindow;
		companyWindow->setWidget(dForm);
		companyWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(companyWindow);
		companyWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All companies are shown");
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

void CreateProdDlg::InitComboBox()
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
	std::vector<BusinessLayer::Measure> meaVector = dialogBL->GetAllDataForClass<BusinessLayer::Measure>(errorMessage);
	if (!meaVector.empty())
	{
		for (unsigned int i = 0; i < meaVector.size(); i++)
		{
			measureCmb->addItem(meaVector[i].GetShortName().c_str(), QVariant(meaVector[i].GetID()));
		}
	}
	std::vector<BusinessLayer::ProductType> ptVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductType>(errorMessage);
	if (!ptVector.empty())
	{
		for (unsigned int i = 0; i < ptVector.size(); i++)
		{
			prodTypeCmb->addItem(ptVector[i].GetShortName().c_str(), QVariant(ptVector[i].GetID()));
		}
	}
}

void CreateProdDlg::TextEditChanged()
{
	if (priceEdit->text().contains(","))
	{
		priceEdit->setText(priceEdit->text().replace(",", "."));
	}
	if (priceEdit->text().contains(".."))
	{
		priceEdit->setText(priceEdit->text().replace("..", "."));
	}
	if (volumeEdit->text().contains(","))
	{
		volumeEdit->setText(volumeEdit->text().replace(",", "."));
	}
	if (volumeEdit->text().contains(".."))
	{
		volumeEdit->setText(volumeEdit->text().replace("..", "."));
	}
}