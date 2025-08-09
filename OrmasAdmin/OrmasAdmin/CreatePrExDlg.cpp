#include "stdafx.h"
#include "CreatePrExDlg.h"
#include "DataForm.h"



CreatePrExDlg::CreatePrExDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 5, this);
	vDouble2 = new QDoubleValidator(-500000000.00, 500000000.00, 5, this);
	vInt = new QIntValidator(0, 1000000000, this);
	productEdit->setValidator(vInt);
	branchEdit->setValidator(vInt);
	branchBtn->setEnabled(false);
	locationEdit->setValidator(vInt);
	locationBtn->setEnabled(false);
	clientEdit->setValidator(vInt);
	clientBtn->setEnabled(false);
	expeditorEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble2);
	valueEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePrExDlg::EditPriceExtension);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePrExDlg::CreatePriceExtension);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePrExDlg::Close);
	QObject::connect(branchBtn, &QPushButton::released, this, &CreatePrExDlg::OpenBrhDlg);
	QObject::connect(productBtn, &QPushButton::released, this, &CreatePrExDlg::OpenPrdDlg);
	QObject::connect(locationBtn, &QPushButton::released, this, &CreatePrExDlg::OpenLcnDlg);
	QObject::connect(clientBtn, &QPushButton::released, this, &CreatePrExDlg::OpenCltDlg);
	QObject::connect(expeditorBtn, &QPushButton::released, this, &CreatePrExDlg::OpenEmpDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreatePrExDlg::TextEditChanged);
}

CreatePrExDlg::~CreatePrExDlg()
{
	delete vDouble;
	delete vInt;
}


void CreatePrExDlg::SetID(int ID, QString childName)
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
						prNamePh->setText(product.GetName().c_str());
						prPricePh->setText(QString::number(product.GetPrice()));
				}
			}
			if (childName == QString("branchForm"))
			{
				branchEdit->setText(QString::number(ID));
				clientEdit->setText("");
				expeditorEdit->setText("");
				locationEdit->setText("");
				BusinessLayer::Branch branch;
				if (branch.GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					brNamePh->setText(branch.GetName().c_str());
				}
			}
			if (childName == QString("locationForm"))
			{
				locationEdit->setText(QString::number(ID));
				clientEdit->setText("");
				branchEdit->setText("");
				expeditorEdit->setText("");
				BusinessLayer::Location location;
				if (location.GetLocationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					regionNamePh->setText(location.GetRegionName().c_str());
					cityNamePh->setText(location.GetCityName().c_str());
				}
			}
			if (childName == QString("clientForm"))
			{
				clientEdit->setText(QString::number(ID));
				expeditorEdit->setText("");
				branchEdit->setText("");
				locationEdit->setText("");
				BusinessLayer::User client;
				if (client.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					clientNamePh->setText(client.GetName().c_str());
					clientSurnamePh->setText(client.GetSurname().c_str());
					clientPhonePh->setText(client.GetPhone().c_str());
				}
			}
			if (childName == QString("employeeForm"))
			{
				expeditorEdit->setText(QString::number(ID));
				clientEdit->setText("");
				branchEdit->setText("");
				locationEdit->setText("");
				BusinessLayer::User expeditor;
				if (expeditor.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					expeditorNamePh->setText(expeditor.GetName().c_str());
					expeditorSurnamePh->setText(expeditor.GetSurname().c_str());
					expeditorPhonePh->setText(expeditor.GetPhone().c_str());
				}
			}
		}
	}
}

void CreatePrExDlg::SetPriceExtensionParams(int productID, double pValue, QString pDate, int pDayCount, int lID, int eID, int bID, int cID, int id)
{
	priceExtension->SetProductID(productID);
	priceExtension->SetValue(pValue);
	priceExtension->SetDate(pDate.toUtf8().constData());
	priceExtension->SetDayCount(pDayCount);
	priceExtension->SetLocationID(lID);
	priceExtension->SetExpeditorID(eID);
	priceExtension->SetBranchID(bID);
	priceExtension->SetClientID(cID);
	priceExtension->SetID(id);
}

void CreatePrExDlg::FillEditElements(int productID, double pValue, QString pDate, int pDayCount, int lID, int eID, int bID, int cID)
{
	productEdit->setText(QString::number(productID));
	valueEdit->setText(QString::number(pValue));
	dateEdit->setDateTime(QDateTime::fromString(pDate, "dd.MM.yyyy"));
	daySpb->setValue(pDayCount);
	locationEdit->setText(QString::number(lID));
	expeditorEdit->setText(QString::number(eID));
	branchEdit->setText(QString::number(bID));
	clientEdit->setText(QString::number(cID));
	
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productID, errorMessage))
		{
			prNamePh->setText(product.GetName().c_str());
			prPricePh->setText(QString::number(product.GetPrice()));
		}
	

	BusinessLayer::Branch branch;
	if (branch.GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), bID, errorMessage))
	{
		brNamePh->setText(branch.GetName().c_str());
	}

	BusinessLayer::Location location;
	if (location.GetLocationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), lID, errorMessage))
	{
		regionNamePh->setText(location.GetRegionName().c_str());
		cityNamePh->setText(location.GetCityName().c_str());
	}

	BusinessLayer::User client;
	if (client.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cID, errorMessage))
	{
		clientNamePh->setText(client.GetName().c_str());
		clientSurnamePh->setText(client.GetSurname().c_str());
		clientPhonePh->setText(client.GetPhone().c_str());
	}

	BusinessLayer::User expeditor;
	if (expeditor.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), eID, errorMessage))
	{
		expeditorNamePh->setText(expeditor.GetName().c_str());
		expeditorSurnamePh->setText(expeditor.GetSurname().c_str());
		expeditorPhonePh->setText(expeditor.GetPhone().c_str());
	}
}

bool CreatePrExDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetPriceExtensionParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 13)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());

		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 13)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePrExDlg::CreatePriceExtension()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() 
		&& !dateEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetPriceExtensionParams(productEdit->text().toInt(), valueEdit->text().toDouble(), dateEdit->text(), daySpb->text().toInt(), locationEdit->text().toInt(), 
			expeditorEdit->text().toInt(), branchEdit->text().toInt(), clientEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreatePriceExtension(priceExtension, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					
					BusinessLayer::Product *product = new BusinessLayer::Product();
					BusinessLayer::Branch *branch = new BusinessLayer::Branch();
					BusinessLayer::User *client = new BusinessLayer::User();
					BusinessLayer::User *expeditor = new BusinessLayer::User();
					BusinessLayer::Location *location = new BusinessLayer::Location();
					if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetProductID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete product;
						
						delete branch;
						delete client;
						delete expeditor;
						delete location;
						return;
					}

					if (!branch->GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetBranchID(), errorMessage)
						&& !client->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetClientID(), errorMessage)
						&& !location->GetLocationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetLocationID(), errorMessage)
						&& !expeditor->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetExpeditorID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete product;
						
						delete branch;
						delete client;
						delete expeditor;
						delete location;
						return;
					}
		
					QList<QStandardItem*> priceExtensionItem;

					QString lPh = "";
					if (!location->IsEmpty())
					{
						lPh = location->GetCountryName().c_str() + QString(" ") + location->GetRegionName().c_str() + QString(" ") + location->GetCityName().c_str();
					}
					
					QString expPh = "";
					if (!expeditor->IsEmpty())
					{
						QString expPh = expeditor->GetName().c_str() + QString(" ") + expeditor->GetSurname().c_str() + QString(" ") + expeditor->GetPhone().c_str();
					}

					QString clPh = "";
					if (!client->IsEmpty())
					{
						clPh = client->GetName().c_str() + QString(" ") + client->GetSurname().c_str() + QString(" ") + client->GetPhone().c_str();
					}

					QString bPh = "";
					if (!branch->IsEmpty())
					{
						bPh = branch->GetName().c_str();
					}


					priceExtensionItem << new QStandardItem(QString::number(priceExtension->GetID()))
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(priceExtension->GetValue()))
						<< new QStandardItem(priceExtension->GetDate().c_str())
						<< new QStandardItem(QString::number(priceExtension->GetDayCount()))
						<< new QStandardItem(lPh)
						<< new QStandardItem(expPh)
						<< new QStandardItem(bPh)
						<< new QStandardItem(clPh)
						<< new QStandardItem(QString::number(priceExtension->GetProductID()))
						<< new QStandardItem(QString::number(priceExtension->GetLocationID()))
						<< new QStandardItem(QString::number(priceExtension->GetExpeditorID()))
						<< new QStandardItem(QString::number(priceExtension->GetBranchID()))
						<< new QStandardItem(QString::number(priceExtension->GetClientID()));
					
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(priceExtensionItem);
					
					delete product;
					delete branch;
					delete client;
					delete expeditor;
					delete location;
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

void CreatePrExDlg::EditPriceExtension()
{
	errorMessage.clear();
	if (0 !=productEdit->text().toInt() 
		&& !dateEdit->text().isEmpty())
	{
		if (QString(priceExtension->GetDate().c_str()) != dateEdit->text() || priceExtension->GetProductID() !=productEdit->text().toInt()
			|| priceExtension->GetValue() != valueEdit->text().toDouble())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetPriceExtensionParams(productEdit->text().toInt(), valueEdit->text().toDouble(), dateEdit->text(), daySpb->text().toInt(), locationEdit->text().toInt(),
				expeditorEdit->text().toInt(), branchEdit->text().toInt(), clientEdit->text().toInt(), priceExtension->GetID());
	
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdatePriceExtension(priceExtension, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Product *product = new BusinessLayer::Product();
						BusinessLayer::Branch *branch = new BusinessLayer::Branch();
						BusinessLayer::User *client = new BusinessLayer::User();
						BusinessLayer::Location *location = new BusinessLayer::Location();
						BusinessLayer::User *expeditor = new BusinessLayer::User();

						if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetProductID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete product;
							
							delete branch;
							delete client;
							delete expeditor;
							delete location;
							return;
						}

						if (!branch->GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetBranchID(), errorMessage)
							&& !client->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetClientID(), errorMessage)
							&& !location->GetLocationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetLocationID(), errorMessage)
							&& !expeditor->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), priceExtension->GetExpeditorID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete product;
							
							delete branch;
							delete client;
							delete expeditor;
							delete location;
							return;
						}

						QString lPh = "";
						if (!location->IsEmpty())
						{
							lPh = location->GetCountryName().c_str() + QString(" ") + location->GetRegionName().c_str() + QString(" ") + location->GetCityName().c_str();
						}

						QString expPh = "";
						if (!expeditor->IsEmpty())
						{
							QString expPh = expeditor->GetName().c_str() + QString(" ") + expeditor->GetSurname().c_str() + QString(" ") + expeditor->GetPhone().c_str();
						}

						QString clPh = "";
						if (!client->IsEmpty())
						{
							clPh = client->GetName().c_str() + QString(" ") + client->GetSurname().c_str() + QString(" ") + client->GetPhone().c_str();
						}

						QString bPh = "";
						if (!branch->IsEmpty())
						{
							bPh = branch->GetName().c_str();
						}

						
						itemModel->item(mIndex.row(), 1)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(priceExtension->GetValue()));
						itemModel->item(mIndex.row(), 3)->setText(priceExtension->GetDate().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(priceExtension->GetDayCount()));
						itemModel->item(mIndex.row(), 5)->setText(lPh);
						itemModel->item(mIndex.row(), 6)->setText(expPh);
						itemModel->item(mIndex.row(), 7)->setText(bPh);
						itemModel->item(mIndex.row(), 8)->setText(clPh);
						itemModel->item(mIndex.row(), 9)->setText(QString::number(priceExtension->GetProductID()));
						itemModel->item(mIndex.row(), 10)->setText(QString::number(priceExtension->GetLocationID()));
						itemModel->item(mIndex.row(), 11)->setText(QString::number(priceExtension->GetExpeditorID()));
						itemModel->item(mIndex.row(), 12)->setText(QString::number(priceExtension->GetBranchID()));
						itemModel->item(mIndex.row(), 13)->setText(QString::number(priceExtension->GetClientID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						
						delete product;
						delete branch;
						delete client;
						delete expeditor;
						delete location;
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

void CreatePrExDlg::Close()
{
	this->parentWidget()->close();
}

void CreatePrExDlg::OpenPrdDlg()
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
		QString message = tr("Sorry could not find product with \"Product\" code!");
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

void CreatePrExDlg::OpenBrhDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Branches"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Branch>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("branchForm");
		dForm->QtConnect<BusinessLayer::Branch>();
		QMdiSubWindow *branchWindow = new QMdiSubWindow;
		branchWindow->setWidget(dForm);
		branchWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(branchWindow);
		branchWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All branches are shown");
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

void CreatePrExDlg::OpenCltDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Clients"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ClientView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("clientForm");
		dForm->QtConnect<BusinessLayer::ClientView>();
		QMdiSubWindow *clientWindow = new QMdiSubWindow;
		clientWindow->setWidget(dForm);
		clientWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(clientWindow);
		clientWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All clients are shown");
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

void CreatePrExDlg::OpenEmpDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Employees"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	BusinessLayer::Role *role = new BusinessLayer::Role();
	role->SetName("EXPEDITOR");
	std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
	std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);

	if (roleVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not define the role for this employee!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	BusinessLayer::Employee *employee = new BusinessLayer::Employee();
	employee->SetRoleID(roleVector.at(0).GetID());
	std::string employeeFilter = dialogBL->GenerateFilter<BusinessLayer::Employee>(employee);
	std::vector<BusinessLayer::EmployeeView> employeeVector = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
	if (employeeVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not find employee with \"expeditor\" role!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("employeeForm");
		dForm->QtConnect<BusinessLayer::EmployeeView>();
		QMdiSubWindow *employeeWindow = new QMdiSubWindow;
		employeeWindow->setWidget(dForm);
		employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(employeeWindow);
		employeeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All employees are shown");
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

void CreatePrExDlg::OpenLcnDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Locations"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Location>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("loactionForm");
		dForm->QtConnect<BusinessLayer::Location>();
		QMdiSubWindow *loactionWindow = new QMdiSubWindow;
		loactionWindow->setWidget(dForm);
		loactionWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(loactionWindow);
		loactionWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All loaction are shown");
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

void CreatePrExDlg::TextEditChanged()
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