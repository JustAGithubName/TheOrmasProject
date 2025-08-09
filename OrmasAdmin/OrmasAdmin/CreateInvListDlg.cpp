#include "stdafx.h"

#include "CreateInvListDlg.h"
#include "DataForm.h"


CreateInvListDlg::CreateInvListDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	inventorizationID = ((DataForm*)parent)->inventorizationID;
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	productEdit->setValidator(vInt);
	countEdit->setValidator(vDouble);
	countEdit->setMaxLength(20);
	inventorizationEdit->setValidator(vInt);
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateInvListDlg::EditProductInList);
	}
	else
	{
		statusEdit->setText("0");
		inventorizationEdit->setText("0");
		countEdit->setText("0");
		productEdit->setText("0");
		sumEdit->setText("0");
		editSectionWgt->hide();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateInvListDlg::AddProductToList);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateInvListDlg::Close);
	QObject::connect(inventorizationBtn, &QPushButton::released, this, &CreateInvListDlg::OpenInvDlg);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateInvListDlg::OpenProdDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateInvListDlg::OpenStsDlg);
	QObject::connect(this, SIGNAL(DataIsChanged()), ((DataForm*)parent), SLOT(OnRowsNumberChanged()));
	QObject::connect(countEdit, &QLineEdit::textChanged, this, &CreateInvListDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateInvListDlg::TextEditChanged);
	InitComboBox();
}

CreateInvListDlg::~CreateInvListDlg()
{
	delete vDouble;
	delete vInt;
}

void CreateInvListDlg::SetID(int ID, QString childName)
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
			if (childName == QString("inventorizationForm"))
			{
				inventorizationEdit->setText(QString::number(ID));
			}
			if (childName == QString("statusForm"))
			{
				statusEdit->setText(QString::number(ID));
				BusinessLayer::Status status;
				if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					statusPh->setText(status.GetName().c_str());
				}
			}
		}
	}
}

void CreateInvListDlg::SetInvListParams(int iInventorizationID, int iProductID, double iCount, double iSum, int iStatusID, int iCurrencyID, int id)
{
	inventorizationList->SetInventorizationID(iInventorizationID);
	inventorizationList->SetProductID(iProductID);
	inventorizationList->SetCount(iCount);
	inventorizationList->SetSum(iSum);
	inventorizationList->SetStatusID(iStatusID);
	inventorizationList->SetCurrencyID(iCurrencyID);
	inventorizationList->SetID(id);
}

void CreateInvListDlg::FillEditElements(int iInventorizationID, int iProductID, double iCount, double iSum, int iStatusID, int iCurrencyID)
{
	inventorizationEdit->setText(QString::number(iInventorizationID));
	productEdit->setText(QString::number(iProductID));
	countEdit->setText(QString::number(iCount, 'f', 3));
	sumEdit->setText(QString::number(iSum, 'f', 3));
	statusEdit->setText(QString::number(iStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(iCurrencyID)));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), iProductID, errorMessage))
	{
		prodNamePh->setText(product.GetName().c_str());
		volumePh->setText(QString::number(product.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetName().c_str());
		}
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), iStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

bool CreateInvListDlg::FillDlgElements(QTableView* oTable)
{
	QModelIndex mIndex = oTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetInvListParams(oTable->model()->data(oTable->model()->index(mIndex.row(), 1)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 11)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 7)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 8)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 12)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 13)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(oTable->model()->data(oTable->model()->index(mIndex.row(), 1)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 11)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 7)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 8)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 12)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 13)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateInvListDlg::AddProductToList()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("INVENTORIZED");
		std::string statusFilter = dialogBL->GenerateFilter<BusinessLayer::Status>(status);
		std::vector<BusinessLayer::Status> statusVector = dialogBL->GetAllDataForClass<BusinessLayer::Status>(errorMessage, statusFilter);
		delete status;
		if (statusVector.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Status are empty please contact with Admin")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		BusinessLayer::Product *product = new BusinessLayer::Product();
		//product->SetID(productEdit->text().toInt());
		//std::string productFilter = dialogBL->GenerateFilter<BusinessLayer::Product>(product);
		//std::vector<BusinessLayer::ProductView> productVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductView>(errorMessage, productFilter);

		BusinessLayer::Measure *measure = new BusinessLayer::Measure();

		BusinessLayer::Currency *currency = new BusinessLayer::Currency();
		BusinessLayer::Currency *sumCurrency = new BusinessLayer::Currency();

		if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productEdit->text().toInt(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			delete product;
			delete measure;
			delete currency;
			return;
		}
		else
		{
			if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage)
				|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetCurrencyID(), errorMessage)
				|| !sumCurrency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetCurrencyID(), errorMessage))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				delete product;
				delete measure;
				delete currency;
				return;
			}
		}

		SetInvListParams(inventorizationID, productEdit->text().toInt(),
			countEdit->text().toDouble(), (countEdit->text().toDouble() * product->GetPrice()),
			statusVector.at(0).GetID(), product->GetCurrencyID());

		if (dialogBL->CreateInventorizationList(inventorizationList, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> productListItem;
					productListItem << new QStandardItem(QString::number(inventorizationList->GetID()));
					if (0 != inventorizationID)
					{
						productListItem << new QStandardItem(QString::number(inventorizationID));
					}
					else
					{
						productListItem << new QStandardItem(QString::number(0));
					}
					productListItem << new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(product->GetPrice()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(product->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(QString::number(inventorizationList->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(inventorizationList->GetSum(),'f',3))
						<< new QStandardItem(sumCurrency->GetShortName().c_str())
						<< new QStandardItem(statusVector.at(0).GetName().c_str())
						<< new QStandardItem(QString::number(inventorizationList->GetProductID()))
						<< new QStandardItem(QString::number(inventorizationList->GetStatusID()))
						<< new QStandardItem(QString::number(inventorizationList->GetCurrencyID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(productListItem);
				}
			}
			delete measure;
			delete product;
			delete currency;

			Close();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This product is not valid! Please delete it!")),
				QString(tr("Ok")));
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

void CreateInvListDlg::EditProductInList()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		if (productEdit->text().toInt() != inventorizationList->GetProductID() || countEdit->text().toDouble() != inventorizationList->GetCount()
			|| inventorizationEdit->text().toInt() != inventorizationList->GetInventorizationID() || sumEdit->text().toDouble() != inventorizationList->GetSum()
			|| statusEdit->text().toInt() != inventorizationList->GetStatusID() || currencyCmb->currentData().toInt() != inventorizationList->GetCurrencyID())
		{
			BusinessLayer::Product *product = new BusinessLayer::Product();
			if (!product->GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productEdit->text().toInt(), errorMessage))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				delete product;
				return;
			}
			if (countEdit->text().toDouble() != inventorizationList->GetCount() ||
				productEdit->text().toInt() != inventorizationList->GetProductID())
			{
				sumEdit->setText(QString::number(countEdit->text().toDouble() * product->GetPrice()));
			}
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetInvListParams(inventorizationEdit->text().toInt(),
				productEdit->text().toInt(), countEdit->text().toDouble(), sumEdit->text().toDouble(), statusEdit->text().toInt(),
				inventorizationList->GetCurrencyID(), inventorizationList->GetID());
			if (dialogBL->UpdateInventorizationList(inventorizationList, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Measure *measure = new BusinessLayer::Measure();
						BusinessLayer::Status *status = new BusinessLayer::Status();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();
						BusinessLayer::Currency *sumCurrency = new BusinessLayer::Currency();
						if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetMeasureID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product->GetCurrencyID(), errorMessage)
							|| !sumCurrency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyCmb->currentData().toInt(), errorMessage)
							|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), statusEdit->text().toInt(), errorMessage))
						{
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete product;
							delete measure;
							delete status;
							delete currency;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(QString::number(inventorizationList->GetInventorizationID()));
						itemModel->item(mIndex.row(), 2)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(product->GetPrice()));
						itemModel->item(mIndex.row(), 4)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(product->GetVolume()));
						itemModel->item(mIndex.row(), 6)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(QString::number(inventorizationList->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(inventorizationList->GetSum(),'f',3));
						itemModel->item(mIndex.row(), 9)->setText(sumCurrency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 10)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 11)->setText(QString::number(inventorizationList->GetProductID()));
						itemModel->item(mIndex.row(), 12)->setText(QString::number(inventorizationList->GetStatusID()));
						itemModel->item(mIndex.row(), 13)->setText(QString::number(inventorizationList->GetCurrencyID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete measure;
						delete status;
						delete currency;
					}
				}
				delete product;
				Close();			
			}
			else
			{
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

void CreateInvListDlg::Close()
{
	this->parentWidget()->close();
}

void CreateInvListDlg::OpenStsDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Status"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Status>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("statusForm");
		dForm->QtConnect<BusinessLayer::Measure>();
		QMdiSubWindow *statusWindow = new QMdiSubWindow;
		statusWindow->setWidget(dForm);
		statusWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(statusWindow);
		statusWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All measures are shown");
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

void CreateInvListDlg::OpenProdDlg()
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


void CreateInvListDlg::OpenInvDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Inventorization"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::InventorizationView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("inventorizationForm");
		dForm->QtConnect<BusinessLayer::InventorizationView>();
		QMdiSubWindow *inventorizationWindow = new QMdiSubWindow;
		inventorizationWindow->setWidget(dForm);
		inventorizationWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(inventorizationWindow);
		inventorizationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All inventorization products are shown");
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

void CreateInvListDlg::InitComboBox()
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

void CreateInvListDlg::TextEditChanged()
{
	if (countEdit->text().contains(","))
	{
		countEdit->setText(countEdit->text().replace(",", "."));
	}
	if (countEdit->text().contains(".."))
	{
		countEdit->setText(countEdit->text().replace("..", "."));
	}
	if (sumEdit->text().contains(","))
	{
		sumEdit->setText(sumEdit->text().replace(",", "."));
	}
	if (sumEdit->text().contains(".."))
	{
		sumEdit->setText(sumEdit->text().replace("..", "."));
	}
}