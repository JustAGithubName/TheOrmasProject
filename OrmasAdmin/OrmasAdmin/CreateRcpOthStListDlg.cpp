#include "stdafx.h"

#include "CreateRcpOthStListDlg.h"
#include "DataForm.h"


CreateRcpOthStListDlg::CreateRcpOthStListDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	receiptOtherStocksID = ((DataForm*)parent)->receiptOtherStocksID;
	employeeID = ((DataForm*)parent)->employeeID;
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	productEdit->setValidator(vInt);
	countEdit->setValidator(vDouble);
	countEdit->setMaxLength(20);
	receiptOthStEdit->setValidator(vInt);
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		QObject::connect(addBtn, &QPushButton::released, this, &CreateRcpOthStListDlg::EditProductInList);
	}
	else
	{
		statusEdit->setText("0");
		receiptOthStEdit->setText("0");
		countEdit->setText("0");
		productEdit->setText("0");
		sumEdit->setText("0");
		editSectionWgt->hide();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateRcpOthStListDlg::AddProductToList);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateRcpOthStListDlg::Close);
	QObject::connect(receiptOthStBtn, &QPushButton::released, this, &CreateRcpOthStListDlg::OpenRcpOthStDlg);
	QObject::connect(otherStocksBtn, &QPushButton::released, this, &CreateRcpOthStListDlg::OpenOthStDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateRcpOthStListDlg::OpenStsDlg);
	QObject::connect(countEdit, &QLineEdit::textChanged, this, &CreateRcpOthStListDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateRcpOthStListDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(DataIsChanged()), ((DataForm*)parent), SLOT(OnRowsNumberChanged()));
	InitComboBox();
}

CreateRcpOthStListDlg::~CreateRcpOthStListDlg()
{
	delete vDouble;
	delete vInt;
}

void CreateRcpOthStListDlg::SetProductData(int productID)
{
	productEdit->setText(QString::number(productID));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productID, errorMessage))
	{
		othStNamePh->setText(product.GetName().c_str());
		volumePh->setText(QString::number(product.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetName().c_str());
		}
		oldPriceLb->setText(QString::number(product.GetPrice()));
	}
}

void CreateRcpOthStListDlg::SetID(int ID, QString childName)
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

			if (childName == QString("othserStocksForm"))
			{
				productEdit->setText(QString::number(ID));
				BusinessLayer::OtherStocks otherStocks;
				if (otherStocks.GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					othStNamePh->setText(otherStocks.GetName().c_str());
					volumePh->setText(QString::number(otherStocks.GetVolume()));
					BusinessLayer::Measure measure;
					if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks.GetMeasureID(), errorMessage))
					{
						measurePh->setText(measure.GetName().c_str());
					}
					oldPriceLb->setText(QString::number(otherStocks.GetPrice()));
				}
			}
			if (childName == QString("receiptOthStForm"))
			{
				receiptOthStEdit->setText(QString::number(ID));
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

void CreateRcpOthStListDlg::SetRcpOthStListParams(int oReceiptOtherStocksID, int oOtherStocksID, double oCount, double oSum, int oStatusID, int oCurrencyID, int id)
{
	receiptOtherStocksList->SetReceiptOtherStocksID(oReceiptOtherStocksID);
	receiptOtherStocksList->SetOtherStocksID(oOtherStocksID);
	receiptOtherStocksList->SetCount(oCount);
	receiptOtherStocksList->SetSum(oSum);
	receiptOtherStocksList->SetStatusID(oStatusID);
	receiptOtherStocksList->SetCurrencyID(oCurrencyID);
	receiptOtherStocksList->SetID(id);
}

void CreateRcpOthStListDlg::FillEditElements(int oReceiptOtherStocksID, int oOtherStocksID, double oCount, double oSum, int oStatusID, int oCurrencyID)
{
	receiptOthStEdit->setText(QString::number(oReceiptOtherStocksID));
	productEdit->setText(QString::number(oOtherStocksID));
	countEdit->setText(QString::number(oCount, 'f', 3));
	sumEdit->setText(QString::number(oSum, 'f', 3));
	statusEdit->setText(QString::number(oStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(oCurrencyID)));
	BusinessLayer::OtherStocks otherStocks;
	if (otherStocks.GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oOtherStocksID, errorMessage))
	{
		othStNamePh->setText(otherStocks.GetName().c_str());
		volumePh->setText(QString::number(otherStocks.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetName().c_str());
		}
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

bool CreateRcpOthStListDlg::FillDlgElements(QTableView* oTable)
{
	QModelIndex mIndex = oTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetRcpOthStListParams(oTable->model()->data(oTable->model()->index(mIndex.row(), 1)).toInt(),
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

void CreateRcpOthStListDlg::AddProductToList()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		if (!BlockWrongPrice(newPriceLb->text(), oldPriceLb->text()))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("A new price of product is too height or low, please check count and sum fields! Or contact with accountant!")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		DataForm *parentDataForm = (DataForm*)parentForm;
		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("ORDERED");
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
		BusinessLayer::OtherStocks *otherStocks = new BusinessLayer::OtherStocks();
		//product->SetID(productEdit->text().toInt());
		//std::string productFilter = dialogBL->GenerateFilter<BusinessLayer::Product>(product);
		//std::vector<BusinessLayer::ProductView> productVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductView>(errorMessage, productFilter);

		BusinessLayer::Measure *measure = new BusinessLayer::Measure();

		BusinessLayer::Currency *currency = new BusinessLayer::Currency();
		BusinessLayer::Currency *sumCurrency = new BusinessLayer::Currency();

		if (!otherStocks->GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productEdit->text().toInt(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			delete otherStocks;
			delete measure;
			delete currency;
			return;
		}
		else
		{
			if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetMeasureID(), errorMessage)
				|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetCurrencyID(), errorMessage)
				|| !sumCurrency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetCurrencyID(), errorMessage))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				delete otherStocks;
				delete measure;
				delete currency;
				return;
			}
		}

		if (sumEdit->text().toDouble() == 0 || sumEdit->text().isEmpty())
		{
			SetRcpOthStListParams(receiptOtherStocksID, productEdit->text().toInt(),
				countEdit->text().toDouble(), (countEdit->text().toDouble() * otherStocks->GetPrice()),
				statusVector.at(0).GetID(), otherStocks->GetCurrencyID());
		}
		else
		{
			SetRcpOthStListParams(receiptOtherStocksID, productEdit->text().toInt(),
				countEdit->text().toDouble(), sumEdit->text().toDouble(),
				statusVector.at(0).GetID(), otherStocks->GetCurrencyID());
		}
		receiptOtherStocksList->employeeID = employeeID;
		if (dialogBL->CreateReceiptOtherStocksList(receiptOtherStocksList, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> productListItem;
					productListItem << new QStandardItem(QString::number(receiptOtherStocksList->GetID()));
					if (0 != receiptOtherStocksList)
					{
						productListItem << new QStandardItem(QString::number(receiptOtherStocksID));
					}
					else
					{
						productListItem << new QStandardItem(QString::number(0));
					}
					productListItem << new QStandardItem(otherStocks->GetName().c_str())
						<< new QStandardItem(QString::number(otherStocks->GetPrice()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(otherStocks->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(QString::number(receiptOtherStocksList->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(receiptOtherStocksList->GetSum(), 'f', 3))
						<< new QStandardItem(sumCurrency->GetShortName().c_str())
						<< new QStandardItem(statusVector.at(0).GetName().c_str())
						<< new QStandardItem(QString::number(receiptOtherStocksList->GetOtherStocksID()))
						<< new QStandardItem(QString::number(receiptOtherStocksList->GetStatusID()))
						<< new QStandardItem(QString::number(receiptOtherStocksList->GetCurrencyID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(productListItem);
				}
			}
			delete measure;
			delete otherStocks;
			delete currency;
			Close();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This other stocks is not valid! Please delete it!")),
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

void CreateRcpOthStListDlg::EditProductInList()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		if (productEdit->text().toInt() != receiptOtherStocksList->GetOtherStocksID() || countEdit->text().toDouble() != receiptOtherStocksList->GetCount()
			|| receiptOthStEdit->text().toInt() != receiptOtherStocksList->GetReceiptOtherStocksID() || sumEdit->text().toDouble() != receiptOtherStocksList->GetSum()
			|| statusEdit->text().toInt() != receiptOtherStocksList->GetStatusID() || currencyCmb->currentData().toInt() != receiptOtherStocksList->GetCurrencyID())
		{
			if (!BlockWrongPrice(newPriceLb->text(), oldPriceLb->text()))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("A new price of other stocks is too height, please check count and sum fields! Or contact with accountant!")),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
			BusinessLayer::OtherStocks *otherStocks = new BusinessLayer::OtherStocks();
			if (!otherStocks->GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productEdit->text().toInt(), errorMessage))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				delete otherStocks;
				return;
			}
			if (countEdit->text().toDouble() != receiptOtherStocksList->GetCount() ||
				productEdit->text().toInt() != receiptOtherStocksList->GetOtherStocksID())
			{
				sumEdit->setText(QString::number(countEdit->text().toDouble() * otherStocks->GetPrice()));
			}
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetRcpOthStListParams(receiptOthStEdit->text().toInt(),
				productEdit->text().toInt(), countEdit->text().toDouble(), sumEdit->text().toDouble(), statusEdit->text().toInt(),
				receiptOtherStocksList->GetCurrencyID(), receiptOtherStocksList->GetID());
			receiptOtherStocksList->employeeID = employeeID;
			if (dialogBL->UpdateReceiptOtherStocksList(receiptOtherStocksList, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Measure *measure = new BusinessLayer::Measure();
						BusinessLayer::Status *status = new BusinessLayer::Status();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();
						BusinessLayer::Currency *sumCurrency = new BusinessLayer::Currency();
						if (!measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetMeasureID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetCurrencyID(), errorMessage)
							|| !sumCurrency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyCmb->currentData().toInt(), errorMessage)
							|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), statusEdit->text().toInt(), errorMessage))
						{
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete otherStocks;
							delete measure;
							delete status;
							delete currency;
							return;
						}

						QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
						QModelIndex mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
						itemModel->item(mIndex.row(), 1)->setText(QString::number(receiptOtherStocksList->GetReceiptOtherStocksID()));
						itemModel->item(mIndex.row(), 2)->setText(otherStocks->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(otherStocks->GetPrice()));
						itemModel->item(mIndex.row(), 4)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(otherStocks->GetVolume()));
						itemModel->item(mIndex.row(), 6)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(QString::number(receiptOtherStocksList->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(receiptOtherStocksList->GetSum(), 'f', 3));
						itemModel->item(mIndex.row(), 9)->setText(sumCurrency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 10)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 11)->setText(QString::number(receiptOtherStocksList->GetOtherStocksID()));
						itemModel->item(mIndex.row(), 12)->setText(QString::number(receiptOtherStocksList->GetStatusID()));
						itemModel->item(mIndex.row(), 13)->setText(QString::number(receiptOtherStocksList->GetCurrencyID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						emit DataIsChanged();
						delete measure;
						delete status;
						delete currency;
					}
				}
				delete otherStocks;

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

void CreateRcpOthStListDlg::Close()
{
	this->parentWidget()->close();
}

void CreateRcpOthStListDlg::OpenStsDlg()
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

void CreateRcpOthStListDlg::OpenOthStDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Other stocks"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	/*BusinessLayer::ProductType *pType = new BusinessLayer::ProductType();
	pType->SetCode("RAW");
	std::string pTypeFilter = dialogBL->GenerateFilter<BusinessLayer::ProductType>(pType);
	std::vector<BusinessLayer::ProductType> pTypeVector = dialogBL->GetAllDataForClass<BusinessLayer::ProductType>(errorMessage, pTypeFilter);
	if (pTypeVector.size() == 0)
	{
		delete pType;
		QString message = tr("Sorry could not find product type with \"Raw\" code!");
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
		QString message = tr("Sorry could not find product with \"Raw\" code!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}*/

	dForm->FillTable<BusinessLayer::ProductView>(errorMessage);//, productFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("otherStockForm");
		dForm->QtConnect<BusinessLayer::OtherStocksView>();
		QMdiSubWindow *othStWindow = new QMdiSubWindow;
		othStWindow->setWidget(dForm);
		othStWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(othStWindow);
		othStWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All other stocks are shown");
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


void CreateRcpOthStListDlg::OpenRcpOthStDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Receipt other stocks"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ReceiptOtherStocksView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("ReceiptOthStForm");
		dForm->QtConnect<BusinessLayer::ReceiptOtherStocksView>();
		QMdiSubWindow *receiptOthStWindow = new QMdiSubWindow;
		receiptOthStWindow->setWidget(dForm);
		receiptOthStWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(receiptOthStWindow);
		receiptOthStWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All receipt other stocks are shown");
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

void CreateRcpOthStListDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
}

void CreateRcpOthStListDlg::TextEditChanged()
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
	if (!countEdit->text().isEmpty() && !countEdit->text().isEmpty())
		InspectPrice();
}

void CreateRcpOthStListDlg::InspectPrice()
{
	if (sumEdit->text().toDouble() > 0 && countEdit->text().toDouble() > 0)
		newPriceLb->setText(QString::number(sumEdit->text().toDouble() / countEdit->text().toDouble(), 'f', 3));
}

bool CreateRcpOthStListDlg::BlockWrongPrice(QString newPrice, QString oldPrice)
{
	if (newPrice.toDouble() >= oldPrice.toDouble() / 1.25 && newPrice.toDouble() <= oldPrice.toDouble()*1.25)
		return true;
	return false;
}

