#include "stdafx.h"

#include "CreateProdnDlg.h"
#include "DataForm.h"



CreateProdnDlg::CreateProdnDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	QDate currentDate = QDate::currentDate();
	int day = currentDate.day();
	int month = currentDate.month();
	int year = currentDate.year();
	std::string nextDay;
	nextDay = std::to_string(year);
	nextDay += ".";
	nextDay += std::to_string(month);
	nextDay += ".";
	nextDay += std::to_string(day);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateProdnDlg::EditProduction);
	}
	else
	{
		production->SetID(dialogBL->GenerateID());
		prdDateEdit->setDate(QDate::currentDate());
		expiryDateEdit->setDate(QDate::currentDate());
		sesStartTimeEdit->setTime(QTime::fromString("00:00","hh:mm"));
		sesEndTimeEdit->setTime(QTime::fromString("23:59", "hh:mm"));
		QObject::connect(okBtn, &QPushButton::released, this, &CreateProdnDlg::CreateProduction);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateProdnDlg::Close);
	QObject::connect(addProdBtn, &QPushButton::released, this, &CreateProdnDlg::OpenProdnListDlg);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateProdnDlg::~CreateProdnDlg()
{
	emit CloseCreatedForms();
}


void CreateProdnDlg::SetProductionParams(QString pProductionDate, QString pExpiryDate, QString pSessionStart, QString pSessionEnd, int id)
{
	production->SetProductionDate(pProductionDate.toUtf8().constData());
	production->SetExpiryDate(pExpiryDate.toUtf8().constData());
	production->SetSessionStart(pSessionStart.toUtf8().constData());
	production->SetSessionEnd(pSessionEnd.toUtf8().constData());
	production->SetID(id);
}

void CreateProdnDlg::FillEditElements(QString pProductionDate, QString pExpiryDate, QString pSessionStart, QString pSessionEnd)
{
	prdDateEdit->setDate(QDate::fromString(pProductionDate, "dd.MM.yyyy"));
	expiryDateEdit->setDate(QDate::fromString(pExpiryDate, "dd.MM.yyyy"));
	sesStartTimeEdit->setTime(QTime::fromString(pSessionStart, "hh:mm"));
	sesEndTimeEdit->setTime(QTime::fromString(pSessionEnd, "hh:mm"));
}


bool CreateProdnDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetProductionParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateProdnDlg::CreateProduction()
{
	errorMessage.clear();
	if (!(prdDateEdit->text().isEmpty() || expiryDateEdit->text().isEmpty() || sesStartTimeEdit->text().isEmpty() ||
		sesEndTimeEdit->text().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetProductionParams(prdDateEdit->text(), expiryDateEdit->text(), sesStartTimeEdit->text(), sesEndTimeEdit->text(), production->GetID());
		production->warehouseID = warehouseCmb->currentData().toInt();
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateProduction(production, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> UserItem;
					UserItem << new QStandardItem(QString::number(production->GetID()))
						<< new QStandardItem(production->GetProductionDate().c_str())
						<< new QStandardItem(production->GetExpiryDate().c_str())
						<< new QStandardItem(production->GetSessionStart().c_str())
						<< new QStandardItem(production->GetSessionEnd().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(UserItem);
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

void CreateProdnDlg::EditProduction()
{
	errorMessage.clear();
	if (!(prdDateEdit->text().isEmpty() || expiryDateEdit->text().isEmpty() || sesStartTimeEdit->text().isEmpty() ||
		sesEndTimeEdit->text().isEmpty()))
	{
		if (prodCountEdit->text().toDouble() > 0)
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetProductionParams(prdDateEdit->text(), expiryDateEdit->text(), sesStartTimeEdit->text(), sesEndTimeEdit->text(), production->GetID());
			production->warehouseID = warehouseCmb->currentData().toInt();
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateProduction(production, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating production data
						
						itemModel->item(mIndex.row(), 1)->setText(production->GetProductionDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(production->GetExpiryDate().c_str());
						itemModel->item(mIndex.row(), 3)->setText(production->GetSessionStart().c_str());
						itemModel->item(mIndex.row(), 4)->setText(production->GetSessionEnd().c_str());
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateProdnDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateProdnDlg::OpenProdnListDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Add product"));
	dForm->hide();
	dForm->productionID = production->GetID();
	BusinessLayer::ProductionList pList;
	pList.SetProductionID(production->GetID());
	production->prodCountMap = pList.GetProductCount(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	std::string filter = pList.GenerateFilter(dialogBL->GetOrmasDal());
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ProductionListView>(errorMessage, filter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("productionListForm");
		dForm->QtConnect<BusinessLayer::ProductionListView>();
		QMdiSubWindow *productionListWindow = new QMdiSubWindow;
		productionListWindow->setWidget(dForm);
		productionListWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(productionListWindow);
		productionListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreateProdnDlg::InitComboBox()
{
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	BusinessLayer::Warehouse warehouse;
	BusinessLayer::WarehouseType warehouseType;
	BusinessLayer::WarehouseEmployeeRelation weRelation;
	std::vector<int> warehouseIDVector = weRelation.GetWarehouseIDListByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), dataFormParent->loggedUser->GetID());
	if (!warehouseType.GetWarehouseTypeByCode(dialogBL->globalVar, dialogBL->GetOrmasDal(), "PRODUCTION", errorMessage))
		return;
	warehouse.SetWarehouseTypeID(warehouseType.GetID());
	std::string filter = warehouse.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::WarehouseView> werVector = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseView>(errorMessage, filter);
	if (!werVector.empty())
	{
		if (warehouseIDVector.size() > 0)
		{
			for (unsigned int j = 0; j < warehouseIDVector.size(); j++)
			{
				for (unsigned int i = 0; i < werVector.size(); i++)
				{
					if (werVector[i].GetID() == warehouseIDVector.at(j))
						warehouseCmb->addItem(werVector[i].GetName().c_str(), QVariant(werVector[i].GetID()));
				}
			}
			if (warehouseCmb->count() == 0)
			{
				for (unsigned int i = 0; i < werVector.size(); i++)
				{
					warehouseCmb->addItem(werVector[i].GetName().c_str(), QVariant(werVector[i].GetID()));
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < werVector.size(); i++)
			{
				warehouseCmb->addItem(werVector[i].GetName().c_str(), QVariant(werVector[i].GetID()));
			}
		}
		
	}
}