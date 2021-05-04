#include "stdafx.h"
#include "CreateStockDlg.h"
#include "DataForm.h"

CreateStockDlg::CreateStockDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	productEdit->setValidator(vInt);
	countEdit->setValidator(vDouble);
	countEdit->setMaxLength(20);
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateStockDlg::EditProduct);
	}
	else
	{
		statusEdit->setText("0");
		countEdit->setText("0");
		productEdit->setText("0");
		sumEdit->setText("0");
		editSectionWgt->hide();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateStockDlg::AddProduct);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateStockDlg::Close);
	QObject::connect(productBtn, &QPushButton::released, this, &CreateStockDlg::OpenProdDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateStockDlg::OpenStsDlg);
	QObject::connect(countEdit, &QLineEdit::textChanged, this, &CreateStockDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateStockDlg::TextEditChanged);
	InitComboBox();
}

CreateStockDlg::~CreateStockDlg()
{
	delete vDouble;
	delete vInt;
}

void CreateStockDlg::SetID(int ID, QString childName)
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

void CreateStockDlg::SetStockParams(int sProductID, double sCount, double sSum, int sStatusID, int sCurrencyID, int sWarehouseID, int id)
{
	stock->SetProductID(sProductID);
	stock->SetCount(sCount);
	stock->SetSum(sSum);
	stock->SetStatusID(sStatusID);
	stock->SetCurrencyID(sCurrencyID);
	stock->SetWarehouseID(sWarehouseID);
	stock->SetID(id);
}

void CreateStockDlg::FillEditElements(int sProductID, double sCount, double sSum, int sStatusID, int sCurrencyID, int sWarehouseID)
{
	productEdit->setText(QString::number(sProductID));
	countEdit->setText(QString::number(sCount, 'f', 3));
	sumEdit->setText(QString::number(sSum, 'f', 3));
	statusEdit->setText(QString::number(sStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(sCurrencyID)));
	warehouseCmb->setCurrentIndex(warehouseCmb->findData(QVariant(sWarehouseID)));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sProductID, errorMessage))
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
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

bool CreateStockDlg::FillDlgElements(QTableView* oTable)
{
	QModelIndex mIndex = oTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetStockParams(oTable->model()->data(oTable->model()->index(mIndex.row(), 12)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 6)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 7)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 13)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 14)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 15)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(oTable->model()->data(oTable->model()->index(mIndex.row(), 12)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 6)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 7)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 13)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 14)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 15)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateStockDlg::AddProduct()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("IN STOCK");
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

		BusinessLayer::Subaccount subacc;
		BusinessLayer::Warehouse warehouse;
		if (warehouseCmb->currentData().toInt() != 0)
		{
			if (warehouse.GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseCmb->currentData().toInt(), errorMessage))
			{
				if (!subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouse.GetSubaccountID(), errorMessage))
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
			else
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
		SetStockParams(productEdit->text().toInt(),
			countEdit->text().toDouble(), (countEdit->text().toDouble() * product->GetPrice()),
			statusVector.at(0).GetID(), product->GetCurrencyID(), warehouseCmb->currentData().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateStock(stock, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> productListItem;
					productListItem << new QStandardItem(QString::number(stock->GetID()))
						<< new QStandardItem(product->GetName().c_str())
						<< new QStandardItem(QString::number(product->GetPrice()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(product->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(QString::number(stock->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(stock->GetSum(),'f',3))
						<< new QStandardItem(sumCurrency->GetShortName().c_str())
						<< new QStandardItem(warehouseCmb->currentText())
						<< new QStandardItem(subacc.GetNumber().c_str())
						<< new QStandardItem(statusVector.at(0).GetName().c_str())
						<< new QStandardItem(QString::number(stock->GetProductID()))
						<< new QStandardItem(QString::number(stock->GetStatusID()))
						<< new QStandardItem(QString::number(stock->GetCurrencyID()))
						<< new QStandardItem(QString::number(warehouseCmb->currentData().toInt()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(productListItem);
				}
			}
			delete measure;
			delete product;
			delete currency;
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
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This product is not valid! Please delete it!")),
				QString(tr("Ok")));
			dialogBL->CancelTransaction(errorMessage);
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
		dialogBL->CancelTransaction(errorMessage);
	}
	errorMessage.clear();
}

void CreateStockDlg::EditProduct()
{
	errorMessage.clear();
	if (0 != productEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		if (productEdit->text().toInt() != stock->GetProductID() || countEdit->text().toDouble() != stock->GetCount()
			|| sumEdit->text().toDouble() != stock->GetSum()
			|| statusEdit->text().toInt() != stock->GetStatusID() || currencyCmb->currentData().toInt() != stock->GetCurrencyID())
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
			if (countEdit->text().toDouble() != stock->GetCount() ||
				productEdit->text().toInt() != stock->GetProductID())
			{
				sumEdit->setText(QString::number(countEdit->text().toDouble() * product->GetPrice()));
			}
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetStockParams(productEdit->text().toInt(), countEdit->text().toDouble(), sumEdit->text().toDouble(), statusEdit->text().toInt(),
				stock->GetCurrencyID(), warehouseCmb->currentData().toInt(), stock->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateStock(stock, errorMessage))
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

						BusinessLayer::Subaccount subacc;
						BusinessLayer::Warehouse warehouse;
						if (warehouseCmb->currentData().toInt() != 0)
						{
							if (warehouse.GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseCmb->currentData().toInt(), errorMessage))
							{
								if (!subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouse.GetSubaccountID(), errorMessage))
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
							else
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

						
						itemModel->item(mIndex.row(), 1)->setText(product->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(product->GetPrice()));
						itemModel->item(mIndex.row(), 3)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(product->GetVolume()));
						itemModel->item(mIndex.row(), 5)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(QString::number(stock->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 7)->setText(QString::number(stock->GetSum(),'f',3));
						itemModel->item(mIndex.row(), 8)->setText(sumCurrency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 9)->setText(warehouseCmb->currentText());
						itemModel->item(mIndex.row(), 10)->setText(subacc.GetNumber().c_str());
						itemModel->item(mIndex.row(), 11)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 12)->setText(QString::number(product->GetID()));
						itemModel->item(mIndex.row(), 13)->setText(QString::number(stock->GetStatusID()));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(stock->GetCurrencyID()));
						itemModel->item(mIndex.row(), 15)->setText(QString::number(warehouseCmb->currentData().toInt()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete product;
						delete measure;
						delete status;
						delete currency;
						if (!dialogBL->CommitTransaction(errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
						}
					}
				}
				
				Close();
			}
			else
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				dialogBL->CancelTransaction(errorMessage);
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
		dialogBL->CancelTransaction(errorMessage);
	}
	errorMessage.clear();
}

void CreateStockDlg::Close()
{
	this->parentWidget()->close();
}

void CreateStockDlg::OpenStsDlg()
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
		dForm->QtConnect<BusinessLayer::Status>();
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
		QString message = tr("All stocks are shown");
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

void CreateStockDlg::OpenProdDlg()
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

void CreateStockDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
	std::vector<BusinessLayer::WarehouseView> werVector = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseView>(errorMessage);
	if (!werVector.empty())
	{
		for (unsigned int i = 0; i < werVector.size(); i++)
		{
			warehouseCmb->addItem(werVector[i].GetName().c_str(), QVariant(werVector[i].GetID()));
		}
	}
}

void CreateStockDlg::TextEditChanged()
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
