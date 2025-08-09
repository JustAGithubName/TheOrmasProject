#include "stdafx.h"
#include "CreateJbpDlg.h"
#include "DataForm.h"


CreateJbpDlg::CreateJbpDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	positionEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble);
	volumeEdit->setValidator(vDouble);
	valueEdit->setMaxLength(17);
	volumeEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateJbpDlg::EditJobprice);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateJbpDlg::CreateJobprice);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateJbpDlg::Close);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateJbpDlg::OpenProdDlg);
	QObject::connect(positionBtn, &QPushButton::released, this, &CreateJbpDlg::OpenPosDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreateJbpDlg::TextEditChanged);
	QObject::connect(volumeEdit, &QLineEdit::textChanged, this, &CreateJbpDlg::TextEditChanged);
	InitComboBox();
}

CreateJbpDlg::~CreateJbpDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateJbpDlg::SetID(int ID, QString childName)
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
						measurePh->setText(measure.GetName().c_str());
					}
				}
			}
			if (childName == QString("positionForm"))
			{
				positionEdit->setText(QString::number(ID));
				BusinessLayer::Position position;
				if (position.GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					positionPh->setText(position.GetName().c_str());
				}
			}
		}
	}
}

void CreateJbpDlg::SetJobpriceParams(int pID, double jValue, int cID, double jVolume, int mID, int posID,  int id)
{
	jobprice->SetProductID(pID);
	jobprice->SetValue(jValue);
	jobprice->SetCurrencyID(cID);
	jobprice->SetVolume(jVolume);
	jobprice->SetMeasureID(mID);
	jobprice->SetPositionID(posID);
	jobprice->SetID(id);
}

void CreateJbpDlg::FillEditElements(int pID, double jValue, int cID, double jVolume, int mID, int posID)
{
	productEdit->setText(QString::number(pID));
	valueEdit->setText(QString::number(jValue));
	volumeEdit->setText(QString::number(jVolume));
	positionEdit->setText(QString::number(posID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(cID)));
	measureCmb->setCurrentIndex(measureCmb->findData(QVariant(mID)));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pID, errorMessage))
	{
		prodNamePh->setText(product.GetName().c_str());
		volumePh->setText(QString::number(product.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetName().c_str());
		}
	}
	BusinessLayer::Position position;
	if (position.GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), posID, errorMessage))
	{
		prodNamePh->setText(position.GetName().c_str());
	}
}

bool CreateJbpDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetJobpriceParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateJbpDlg::CreateJobprice()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& 0.0 != volumeEdit->text().toDouble() && !measureCmb->currentText().isEmpty() && 0 != positionEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetJobpriceParams(productEdit->text().toInt(), valueEdit->text().toDouble(), currencyCmb->currentData().toInt(),
			volumeEdit->text().toDouble(), measureCmb->currentData().toInt(), positionEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateJobprice(jobprice, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Product *product = new BusinessLayer::Product;
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					BusinessLayer::Measure *measure = new BusinessLayer::Measure;
					BusinessLayer::Position *position = new BusinessLayer::Position;
					if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobprice->GetProductID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobprice->GetCurrencyID(), errorMessage)
						|| !measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobprice->GetMeasureID(), errorMessage)
						|| !position->GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobprice->GetPositionID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete product;
						delete currency;
						delete measure;
						delete position;
						return;
					}
					QList<QStandardItem*> jobpriceItem;
					jobpriceItem << new QStandardItem(QString::number(jobprice->GetID()))
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(jobprice->GetValue()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(jobprice->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(position->GetName().c_str())
						<< new QStandardItem(QString::number(jobprice->GetProductID()))
						<< new QStandardItem(QString::number(jobprice->GetCurrencyID()))
						<< new QStandardItem(QString::number(jobprice->GetMeasureID()))
						<< new QStandardItem(QString::number(jobprice->GetPositionID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(jobpriceItem);
					delete product;
					delete currency;
					delete measure;
					delete position;
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
			QString(tr("Please fill all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateJbpDlg::EditJobprice()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& 0.0 != volumeEdit->text().toDouble() && !measureCmb->currentText().isEmpty() && 0 != positionEdit->text().toInt())
	{
		if (jobprice->GetProductID() != productEdit->text().toInt() || jobprice->GetValue() != valueEdit->text().toDouble() 
			|| jobprice->GetCurrencyID() != currencyCmb->currentData().toInt() || jobprice->GetValue() != valueEdit->text().toDouble()
			|| jobprice->GetMeasureID() != measureCmb->currentData().toInt() || jobprice->GetPositionID() != positionEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetJobpriceParams(productEdit->text().toInt(), valueEdit->text().toDouble(), currencyCmb->currentData().toInt(),
				volumeEdit->text().toDouble(), measureCmb->currentData().toInt(), positionEdit->text().toInt(), jobprice->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateJobprice(jobprice, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Product *product = new BusinessLayer::Product;
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						BusinessLayer::Measure *measure = new BusinessLayer::Measure;
						BusinessLayer::Position *position = new BusinessLayer::Position;
						if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobprice->GetProductID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobprice->GetCurrencyID(), errorMessage)
							|| !measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobprice->GetMeasureID(), errorMessage)
							|| !position->GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), jobprice->GetPositionID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete product;
							delete currency;
							delete measure;
							delete position;
							return;
						}
						
						itemModel->item(mIndex.row(), 1)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(jobprice->GetValue()));
						itemModel->item(mIndex.row(), 3)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(jobprice->GetVolume()));
						itemModel->item(mIndex.row(), 5)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(position->GetName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(QString::number(jobprice->GetProductID()));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(jobprice->GetCurrencyID()));
						itemModel->item(mIndex.row(), 9)->setText(QString::number(jobprice->GetMeasureID()));
						itemModel->item(mIndex.row(), 10)->setText(QString::number(jobprice->GetPositionID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete product;
						delete currency;
						delete measure;
						delete position;
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
			QString(tr("Please fill all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateJbpDlg::Close()
{
	this->parentWidget()->close();
}

void CreateJbpDlg::OpenProdDlg()
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

void CreateJbpDlg::OpenPosDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Positions"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Position>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("positionForm");
		dForm->QtConnect<BusinessLayer::Position>();
		QMdiSubWindow *positionWindow = new QMdiSubWindow;
		positionWindow->setWidget(dForm);
		positionWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(positionWindow);
		positionWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All positions are shown");
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

void CreateJbpDlg::InitComboBox()
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
}

void CreateJbpDlg::TextEditChanged()
{
	if (valueEdit->text().contains(","))
	{
		valueEdit->setText(valueEdit->text().replace(",", "."));
	}
	if (valueEdit->text().contains(".."))
	{
		valueEdit->setText(valueEdit->text().replace("..", "."));
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