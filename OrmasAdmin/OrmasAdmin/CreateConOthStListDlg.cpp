#include "stdafx.h"

#include "CreateConOthStListDlg.h"
#include "DataForm.h"


CreateConOthStListDlg::CreateConOthStListDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	consumeOtherStocksID = ((DataForm*)parent)->consumeOtherStocksID;
	employeeID = ((DataForm*)parent)->stockEmployeeID;
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	otherStocksEdit->setValidator(vInt);
	countEdit->setValidator(vDouble);
	countEdit->setMaxLength(20);
	consumeOthStEdit->setValidator(vInt);
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateConOthStListDlg::EditOtherStocksInList);
	}
	else
	{
		statusEdit->setText("0");
		consumeOthStEdit->setText("0");
		countEdit->setText("0");
		otherStocksEdit->setText("0");
		sumEdit->setText("0");
		editSectionWgt->hide();
		QObject::connect(addBtn, &QPushButton::released, this, &CreateConOthStListDlg::AddOtherStocksToList);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateConOthStListDlg::Close);
	QObject::connect(consumeOthStBtn, &QPushButton::released, this, &CreateConOthStListDlg::OpenConOthStDlg);
	QObject::connect(otherStocksBtn, &QPushButton::released, this, &CreateConOthStListDlg::OpenOthStDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateConOthStListDlg::OpenStsDlg);
	QObject::connect(countEdit, &QLineEdit::textChanged, this, &CreateConOthStListDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateConOthStListDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(DataIsChanged()), ((DataForm*)parent), SLOT(OnRowsNumberChanged()));
	InitComboBox();
}

CreateConOthStListDlg::~CreateConOthStListDlg()
{
	delete vDouble;
	delete vInt;
}

/*void CreateConOthStListDlg::SetOtherStocksData(int OtherStocksID)
{
	OtherStocksEdit->setText(QString::number(OtherStocksID));
	BusinessLayer::OtherStocks OtherStocks;
	if (OtherStocks.GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), OtherStocksID, errorMessage))
	{
		prodNamePh->setText(OtherStocks.GetName().c_str());
		volumePh->setText(QString::number(OtherStocks.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), OtherStocks.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetName().c_str());
		}
	}
}*/


void CreateConOthStListDlg::SetID(int ID, QString childName)
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

			if (childName == QString("otherStocksForm"))
			{
				otherStocksEdit->setText(QString::number(ID));
				BusinessLayer::OtherStocks OtherStocks;
				if (OtherStocks.GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					othStNamePh->setText(OtherStocks.GetName().c_str());
					volumePh->setText(QString::number(OtherStocks.GetVolume()));
					BusinessLayer::Measure measure;
					if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), OtherStocks.GetMeasureID(), errorMessage))
					{
						measurePh->setText(measure.GetName().c_str());
					}
				}
			}
			if (childName == QString("consumeOthStForm"))
			{
				consumeOthStEdit->setText(QString::number(ID));
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

void CreateConOthStListDlg::SetConOthStListParams(int cConsumeOtherStocksID, int cOtherStocksID, double cCount, double cSum, int cStatusID, int cCurrencyID, int id)
{
	consumeOtherStocksList->SetConsumeOtherStocksID(cConsumeOtherStocksID);
	consumeOtherStocksList->SetOtherStocksID(cOtherStocksID);
	consumeOtherStocksList->SetCount(cCount);
	consumeOtherStocksList->SetSum(cSum);
	consumeOtherStocksList->SetStatusID(cStatusID);
	consumeOtherStocksList->SetCurrencyID(cCurrencyID);
	consumeOtherStocksList->SetID(id);
}

void CreateConOthStListDlg::FillEditElements(int cConsumeOtherStocksID, int cOtherStocksID, double cCount, double cSum, int cStatusID, int cCurrencyID)
{
	consumeOthStEdit->setText(QString::number(cConsumeOtherStocksID));
	otherStocksEdit->setText(QString::number(cOtherStocksID));
	countEdit->setText(QString::number(cCount, 'f', 3));
	sumEdit->setText(QString::number(cSum, 'f', 3));
	statusEdit->setText(QString::number(cStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(cCurrencyID)));
	BusinessLayer::OtherStocks OtherStocks;
	if (OtherStocks.GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cOtherStocksID, errorMessage))
	{
		othStNamePh->setText(OtherStocks.GetName().c_str());
		volumePh->setText(QString::number(OtherStocks.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), OtherStocks.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetName().c_str());
		}
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

bool CreateConOthStListDlg::FillDlgElements(QTableView* oTable)
{
	QModelIndex mIndex = oTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetConOthStListParams(oTable->model()->data(oTable->model()->index(mIndex.row(), 1)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 11)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 7)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 8)).toDouble(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 12)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 13)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(oTable->model()->data(oTable->model()->index(mIndex.row(), 1)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 11)).toInt(),
			oTable->model()->data(oTable->model()->index(mIndex.row(), 7)).toInt(),
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

void CreateConOthStListDlg::AddOtherStocksToList()
{
	errorMessage.clear();
	if (0 != otherStocksEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("CONSUMED");
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
		//OtherStocks->SetID(OtherStocksEdit->text().toInt());
		//std::string OtherStocksFilter = dialogBL->GenerateFilter<BusinessLayer::OtherStocks>(OtherStocks);
		//std::vector<BusinessLayer::OtherStocksView> OtherStocksVector = dialogBL->GetAllDataForClass<BusinessLayer::OtherStocksView>(errorMessage, OtherStocksFilter);

		BusinessLayer::Measure *measure = new BusinessLayer::Measure();

		BusinessLayer::Currency *currency = new BusinessLayer::Currency();
		BusinessLayer::Currency *sumCurrency = new BusinessLayer::Currency();

		if (!otherStocks->GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocksEdit->text().toInt(), errorMessage))
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

		SetConOthStListParams(consumeOtherStocksID, otherStocksEdit->text().toInt(),
			countEdit->text().toDouble(), (countEdit->text().toDouble() * otherStocks->GetPrice()),
			statusVector.at(0).GetID(), otherStocks->GetCurrencyID());
		consumeOtherStocksList->stockEmployeeID = employeeID;
		if (dialogBL->CreateConsumeOtherStocksList(consumeOtherStocksList, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> otherStocksListItem;
					otherStocksListItem << new QStandardItem(QString::number(consumeOtherStocksList->GetID()));
					if (0 != consumeOtherStocksID)
					{
						otherStocksListItem << new QStandardItem(QString::number(consumeOtherStocksID));
					}
					else
					{
						otherStocksListItem << new QStandardItem(QString::number(0));
					}
					otherStocksListItem << new QStandardItem(otherStocks->GetName().c_str())
						<< new QStandardItem(QString::number(consumeOtherStocksList->GetSum() / consumeOtherStocksList->GetCount(), 'f', 3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(otherStocks->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(QString::number(consumeOtherStocksList->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(consumeOtherStocksList->GetSum(), 'f', 3))
						<< new QStandardItem(sumCurrency->GetShortName().c_str())
						<< new QStandardItem(statusVector.at(0).GetName().c_str())
						<< new QStandardItem(QString::number(consumeOtherStocksList->GetOtherStocksID()))
						<< new QStandardItem(QString::number(consumeOtherStocksList->GetStatusID()))
						<< new QStandardItem(QString::number(consumeOtherStocksList->GetCurrencyID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(otherStocksListItem);
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
				QString(tr("This OtherStocks is not valid! Please delete it!")),
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

void CreateConOthStListDlg::EditOtherStocksInList()
{
	errorMessage.clear();
	if (0 != otherStocksEdit->text().toInt() || 0 != countEdit->text().toDouble())
	{
		if (otherStocksEdit->text().toInt() != consumeOtherStocksList->GetOtherStocksID() || countEdit->text().toDouble() != consumeOtherStocksList->GetCount()
			|| consumeOthStEdit->text().toInt() != consumeOtherStocksList->GetConsumeOtherStocksID() || sumEdit->text().toDouble() != consumeOtherStocksList->GetSum()
			|| statusEdit->text().toInt() != consumeOtherStocksList->GetStatusID() || currencyCmb->currentData().toInt() != consumeOtherStocksList->GetCurrencyID())
		{
			BusinessLayer::OtherStocks *otherStocks = new BusinessLayer::OtherStocks();
			if (!otherStocks->GetOtherStocksByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocksEdit->text().toInt(), errorMessage))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				delete otherStocks;
				return;
			}
			if (countEdit->text().toDouble() != consumeOtherStocksList->GetCount() ||
				otherStocksEdit->text().toInt() != consumeOtherStocksList->GetOtherStocksID())
			{
				sumEdit->setText(QString::number(countEdit->text().toDouble() * otherStocks->GetPrice()));
			}
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetConOthStListParams(consumeOthStEdit->text().toInt(),
				otherStocksEdit->text().toInt(), countEdit->text().toDouble(), sumEdit->text().toDouble(), statusEdit->text().toInt(),
				consumeOtherStocksList->GetCurrencyID(), consumeOtherStocksList->GetID());
			consumeOtherStocksList->stockEmployeeID = employeeID;
			if (dialogBL->UpdateConsumeOtherStocksList(consumeOtherStocksList, errorMessage))
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


						itemModel->item(mIndex.row(), 1)->setText(QString::number(consumeOtherStocksList->GetConsumeOtherStocksID()));
						itemModel->item(mIndex.row(), 2)->setText(otherStocks->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(consumeOtherStocksList->GetSum() / consumeOtherStocksList->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 4)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(otherStocks->GetVolume()));
						itemModel->item(mIndex.row(), 6)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(QString::number(consumeOtherStocksList->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(consumeOtherStocksList->GetSum(), 'f', 3));
						itemModel->item(mIndex.row(), 9)->setText(sumCurrency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 10)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 11)->setText(QString::number(consumeOtherStocksList->GetOtherStocksID()));
						itemModel->item(mIndex.row(), 12)->setText(QString::number(consumeOtherStocksList->GetStatusID()));
						itemModel->item(mIndex.row(), 13)->setText(QString::number(consumeOtherStocksList->GetCurrencyID()));

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

void CreateConOthStListDlg::Close()
{
	this->parentWidget()->close();
}

void CreateConOthStListDlg::OpenStsDlg()
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

void CreateConOthStListDlg::OpenOthStDlg()
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

	BusinessLayer::WarehouseEmployeeRelation weRelation;
	weRelation.GetWarehouseEmployeeByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeID, errorMessage);
	std::vector<int> othStIDList;
	BusinessLayer::LowValueStock stock;
	othStIDList = stock.GetAllOtherStocksIDByWarehouseID(dialogBL->globalVar, dialogBL->GetOrmasDal(), weRelation.GetWarehouseID(), errorMessage);
	std::string filterIN = "";
	if (othStIDList.size() > 0)
	{
		std::vector<std::string> filterList;
	//	filterIN = otherStocks->GenerateINFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), othStIDList);
		//filterList.push_back(otherStocksFilter);
	//	filterList.push_back(filterIN);
		//OtherStocksFilter = dialogBL->ConcatenateFilters(filterList);
	}


	dForm->FillTable<BusinessLayer::OtherStocksView>(errorMessage);//, otherStocksFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("otherStocksForm");
		dForm->QtConnect<BusinessLayer::OtherStocksView>();
		QMdiSubWindow *otherStocksWindow = new QMdiSubWindow;
		otherStocksWindow->setWidget(dForm);
		otherStocksWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(otherStocksWindow);
		otherStocksWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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


void CreateConOthStListDlg::OpenConOthStDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Consume other stocks"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ConsumeOtherStocksView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("consumeOthStForm");
		dForm->QtConnect<BusinessLayer::ConsumeOtherStocksView>();
		QMdiSubWindow *consumeOtherStocksWindow = new QMdiSubWindow;
		consumeOtherStocksWindow->setWidget(dForm);
		consumeOtherStocksWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(consumeOtherStocksWindow);
		consumeOtherStocksWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All consume OtherStockss are shown");
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


void CreateConOthStListDlg::InitComboBox()
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

void CreateConOthStListDlg::TextEditChanged()
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

