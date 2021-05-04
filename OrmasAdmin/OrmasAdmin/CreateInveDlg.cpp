#include "stdafx.h"

#include "CreateInveDlg.h"
#include "DataForm.h"

#include <map>

CreateInveDlg::CreateInveDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	nameEdit->setMaxLength(200);
	locationEdit->setMaxLength(200);
	numberEdit->setMaxLength(50);
	barcodeEdit->setMaxLength(50);
	costEdit->setValidator(vDouble);
	statusEdit->setValidator(vInt);
	costEdit->setMaxLength(20);
	startDateEdit->setDateTime(QDateTime::currentDateTime());
	endDateEdit->setDateTime(QDateTime::currentDateTime());


	accableIDEdit->setValidator(vInt);
	purEditID->setValidator(vInt);
	accID->setValidator(vInt);
	//sourceGbx->hide();
	InitComboBox();

	if (true == updateFlag)
	{
		newInvCxb->hide();
		accableBtn->hide();
		accountBtn->hide();
		purveyorBtn->hide();
		divisionCmb->hide();
		label_5->hide();
		endDateEdit->setReadOnly(true);
		startDateEdit->setReadOnly(true);
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateInveDlg::EditInventory);
	}
	else
	{
		startDateEdit->setDate(QDate::currentDate());
		endDateEdit->setReadOnly(true);
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
		GenerateInventoryNumber();
		statusEdit->setText(QString::number(statusVector.at(0).GetID()));
		QObject::connect(okBtn, &QPushButton::released, this, &CreateInveDlg::CreateInventory);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateInveDlg::Close);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateInveDlg::OpenStsDlg);
	QObject::connect(accableBtn, &QPushButton::released, this, &CreateInveDlg::OpenActDlg);
	QObject::connect(purveyorBtn, &QPushButton::released, this, &CreateInveDlg::OpenPurDlg);
	QObject::connect(accountBtn, &QPushButton::released, this, &CreateInveDlg::OpenAccDlg);
	QObject::connect(newInvCxb, &QCheckBox::released, this, &CreateInveDlg::HideSpecButton);
	QObject::connect(costEdit, &QLineEdit::textChanged, this, &CreateInveDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	//QObject::connect(divisionCmb, &QComboBox::currentTextChanged, this, &CreateInveDlg::GenerateInventoryNumber);
}

CreateInveDlg::~CreateInveDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();

}

void CreateInveDlg::SetInventoryParams(QString iName, double iCost, QString iLocation, QString iInvNumber, int iDivID, QString iBarcode,
	QString iStartO, QString iEndO, int iStatusID, int subAccID, int id)
{
	inventory->SetName(iName.toUtf8().constData());
	inventory->SetCost(iCost);
	inventory->SetLocation(iLocation.toUtf8().constData());
	inventory->SetInventoryNumber(iInvNumber.toUtf8().constData());
	inventory->SetDepartmentID(iDivID);
	inventory->SetBarcodeNumber(iBarcode.toUtf8().constData());
	inventory->SetStartOfOperationDate(iStartO.toUtf8().constData());
	inventory->SetEndOfOperationDate(iEndO.toUtf8().constData());
	inventory->SetStatusID(iStatusID);
	inventory->SetSubaccountID(subAccID);
	inventory->SetID(id);
}

void CreateInveDlg::SetPostingFixedAssetsParams(int userID, int subaccID, int accID, int fxID, int invID, int id)
{
	postingFixedAssets->SetUserID(userID);
	postingFixedAssets->SetSubaccountID(subaccID);
	postingFixedAssets->SetAccountID(accID);
	postingFixedAssets->SetFixedAssetsID(fxID);
	postingFixedAssets->SetInventoryID(invID);
	postingFixedAssets->SetID(id);
}

void CreateInveDlg::SetInventoryUnionParams(BusinessLayer::Inventory* inv, BusinessLayer::PostingFixedAssets* pfa)
{
	inventoryUnion->SetInventory(inv);
	inventoryUnion->SetPostingFixedAssets(pfa);
}

void CreateInveDlg::FillEditElements(QString iName, double iCost, QString iLocation, QString iInvNumber, int iDivID, QString iBarcode,
	QString iStartO, QString iEndO, int iStatusID, int subAccID, int iID)
{
	if (postingFixedAssets->GetPostingFixedAssetsByInventoryID(dialogBL->globalVar, dialogBL->GetOrmasDal(), iID, errorMessage))
	{
		if (postingFixedAssets->GetAccountID() > 0)
		{
			accableIDEdit->setText(QString::number(postingFixedAssets->GetAccountID()));
			BusinessLayer::ChartOfAccounts coa;
			BusinessLayer::Account acc;
			if (acc.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), postingFixedAssets->GetAccountID(), errorMessage))
			{
				if (coa.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), acc.GetNumber(), errorMessage))
				{
					surnameLb->setText("");
					accountName->setText(coa.GetName().c_str());
					accableIDEdit->hide();
					accableIDEdit->setText("");
					purEditID->hide();
					purEditID->setText("");
					surLb->hide();
				}
			}
		}
		if (postingFixedAssets->GetUserID() > 0)
		{
			purEditID->setText(QString::number(postingFixedAssets->GetUserID()));
			BusinessLayer::User user;
			if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), postingFixedAssets->GetUserID(), errorMessage))
			{
				surnameLb->setText(user.GetSurname().c_str());
				accableIDEdit->hide();
				accableIDEdit->setText("");
				accLB->hide();
				accountName->hide();
				accID->hide();
				accID->setText("");
			}
		}
		if (postingFixedAssets->GetSubaccountID() > 0)
		{
			BusinessLayer::Balance balance;
			if (balance.GetBalanceBySubaccountID(dialogBL->globalVar, dialogBL->GetOrmasDal(), postingFixedAssets->GetSubaccountID(), errorMessage))
			{
				accableIDEdit->setText(QString::number(balance.GetUserID()));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance.GetUserID(), errorMessage))
				{
					surnameLb->setText(user.GetSurname().c_str());
					purEditID->hide();
					purEditID->setText("");
					accLB->hide();
					accountName->hide();
					accID->hide();
					accID->setText("");
				}
			}
		}
	}
	nameEdit->setText(iName);
	costEdit->setText(QString::number(iCost, 'f', 3));
	locationEdit->setText(iLocation);
	numberEdit->setText(iInvNumber);
	divisionCmb->setCurrentIndex(divisionCmb->findData(QVariant(inventory->GetDepartmentID())));
	barcodeEdit->setText(iBarcode);
	startDateEdit->setDate(QDate::fromString(iStartO, "dd.MM.yyyy"));
	endDateEdit->setDate(QDate::fromString(iEndO, "dd.MM.yyyy"));
	statusEdit->setText(QString::number(iStatusID));
}

void CreateInveDlg::SetID(int ID, QString childName)
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

			if (childName == QString("statusForm"))
			{
				statusEdit->setText(QString::number(ID));
			}
			if (childName == QString("purveyorForm"))
			{
				purEditID->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					surnameLb->setText(user.GetSurname().c_str());
				}
			}
			if (childName == QString("accountableForm"))
			{
				accableIDEdit->setText(QString::number(ID));
				BusinessLayer::Accountable accountable;
				if (accountable.GetAccountableByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					BusinessLayer::User user;
					if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage))
					{
						surnameLb->setText(user.GetSurname().c_str());
					}
				}
			}
			if (childName == QString("accountForm"))
			{
				accID->setText(QString::number(ID));
				BusinessLayer::Account account;
				if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					BusinessLayer::ChartOfAccounts coA;
					if (coA.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), account.GetNumber(), errorMessage))
					{
						surnameLb->setText(coA.GetName().c_str());
					}
				}
			}
		}
	}
}

bool CreateInveDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetInventoryParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 8)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 9)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 10)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 8)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 9)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 10)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateInveDlg::CreateInventory()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && !numberEdit->text().isEmpty() && 0 != costEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !divisionCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetInventoryParams(nameEdit->text(), costEdit->text().toDouble(), locationEdit->text(), numberEdit->text(), divisionCmb->currentData().toInt(),
			barcodeEdit->text(), startDateEdit->text(), "", statusEdit->text().toInt(), 0);
		inventoryUnion->isNewInventory = newInvCxb->isChecked();
		//inventoryUnion->inventoryAccountID = fInvCmb->currentData().toInt();
		inventoryUnion->purveyorID = purEditID->text().toInt();
		inventoryUnion->accountableID = accableIDEdit->text().toInt();
		inventoryUnion->accountID = accID->text().toInt();
		SetInventoryUnionParams(inventory, postingFixedAssets);
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateInventoryUnion(inventoryUnion, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), inventory->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					BusinessLayer::Division *division = new BusinessLayer::Division;
					if (!division->GetDivisionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), inventory->GetDepartmentID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						delete division;
						return;
					}
					QList<QStandardItem*> InventoryItem;
					InventoryItem << new QStandardItem(QString::number(inventory->GetID()))
						<< new QStandardItem(inventory->GetName().c_str())
						<< new QStandardItem(QString::number(inventory->GetCost(), 'f', 3))
						<< new QStandardItem(inventory->GetInventoryNumber().c_str())
						<< new QStandardItem(inventory->GetBarcodeNumber().c_str())
						<< new QStandardItem(division->GetName().c_str())
						<< new QStandardItem(status->GetName().c_str())
						<< new QStandardItem(inventory->GetLocation().c_str())
						<< new QStandardItem(inventory->GetStartOfOperationDate().c_str())
						<< new QStandardItem(inventory->GetEndOfOperationDate().c_str())
						<< new QStandardItem(QString::number(inventory->GetStatusID()))
						<< new QStandardItem(QString::number(inventory->GetDepartmentID()))
						<< new QStandardItem(QString::number(inventory->GetSubaccountID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(InventoryItem);

					delete division;
					delete status;
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
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields, especially product list!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateInveDlg::EditInventory()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && !numberEdit->text().isEmpty() && 0 != costEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !divisionCmb->currentText().isEmpty())
	{
		if (QString(inventory->GetName().c_str()) != nameEdit->text() ||
			inventory->GetCost() != costEdit->text().toDouble() ||
			inventory->GetStatusID() != statusEdit->text().toInt()
			|| inventory->GetDepartmentID() != divisionCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			BusinessLayer::Status sts;
			if (!sts.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "WRITE-OFFED", errorMessage))
			{
				return;
			}
			if (inventory->GetStatusID() == sts.GetID())
			{
				SetInventoryParams(nameEdit->text(), costEdit->text().toDouble(), locationEdit->text(), numberEdit->text(), divisionCmb->currentData().toInt(),
					barcodeEdit->text(), startDateEdit->text(), dialogBL->GetOrmasDal().GetSystemDate().c_str(), statusEdit->text().toInt(), inventory->GetSubaccountID(), inventory->GetID());
			}
			else
			{
				SetInventoryParams(nameEdit->text(), costEdit->text().toDouble(), locationEdit->text(), numberEdit->text(), divisionCmb->currentData().toInt(),
					barcodeEdit->text(), startDateEdit->text(), "", statusEdit->text().toInt(), inventory->GetSubaccountID(), inventory->GetID());
			}
			inventoryUnion->isNewInventory = newInvCxb->isChecked();
			//inventoryUnion->inventoryAccountID = fInvCmb->currentData().toInt();
			inventoryUnion->purveyorID = purEditID->text().toInt();
			inventoryUnion->accountableID = accableIDEdit->text().toInt();
			inventoryUnion->accountID = accID->text().toInt();
			SetInventoryUnionParams(inventory, postingFixedAssets);
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateInventoryUnion(inventoryUnion, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Status *status = new BusinessLayer::Status;
						if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), inventory->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete status;
							return;
						}
						BusinessLayer::Division *division = new BusinessLayer::Division;
						if (!division->GetDivisionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), inventory->GetDepartmentID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete status;
							delete division;
							return;
						}
						//updating Inventory data
						itemModel->item(mIndex.row(), 1)->setText(inventory->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(inventory->GetCost(), 'f', 3));
						itemModel->item(mIndex.row(), 3)->setText(inventory->GetInventoryNumber().c_str());
						itemModel->item(mIndex.row(), 4)->setText(inventory->GetBarcodeNumber().c_str());
						itemModel->item(mIndex.row(), 5)->setText(division->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(inventory->GetLocation().c_str());
						itemModel->item(mIndex.row(), 8)->setText(inventory->GetStartOfOperationDate().c_str());
						itemModel->item(mIndex.row(), 9)->setText(inventory->GetEndOfOperationDate().c_str());
						itemModel->item(mIndex.row(), 10)->setText(QString::number(inventory->GetStatusID()));
						itemModel->item(mIndex.row(), 11)->setText(QString::number(inventory->GetDepartmentID()));
						itemModel->item(mIndex.row(), 12)->setText(QString::number(inventory->GetSubaccountID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete division;
						delete status;
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

void CreateInveDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateInveDlg::OpenStsDlg()
{
	errorMessage.clear();
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
		QString message = tr("All statuses are shown");
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

void CreateInveDlg::OpenAccDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Account"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::Account>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accountForm");
		dForm->QtConnect<BusinessLayer::Account>();
		QMdiSubWindow *accWindow = new QMdiSubWindow;
		accWindow->setWidget(dForm);
		accWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(accWindow);
		accWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All accounts are shown");
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

void CreateInveDlg::OpenPurDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Purveyors"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	BusinessLayer::Role *role = new BusinessLayer::Role();
	role->SetName("PURVEYOR");
	std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
	std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);

	if (roleVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not define the role for this purveyor!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	dForm->FillTable<BusinessLayer::PurveyorView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("purveyorForm");
		dForm->QtConnect<BusinessLayer::PurveyorView>();
		QMdiSubWindow *purveyorWindow = new QMdiSubWindow;
		purveyorWindow->setWidget(dForm);
		purveyorWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(purveyorWindow);
		purveyorWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All purveyors are shown");
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

void CreateInveDlg::OpenActDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Accountable"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::AccountableView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accountableForm");
		dForm->QtConnect<BusinessLayer::AccountableView>();
		QMdiSubWindow *accblWindow = new QMdiSubWindow;
		accblWindow->setWidget(dForm);
		accblWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(accblWindow);
		accblWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All accountable are shown");
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

void CreateInveDlg::InitComboBox()
{
	std::vector<BusinessLayer::Division> curDivision = dialogBL->GetAllDataForClass<BusinessLayer::Division>(errorMessage);
	if (!curDivision.empty())
	{
		for (unsigned int i = 0; i < curDivision.size(); i++)
		{
			divisionCmb->addItem(curDivision[i].GetName().c_str(), QVariant(curDivision[i].GetID()));
		}
	}
}

void CreateInveDlg::HideSpecButton()
{
	if (newInvCxb->isChecked())
	{
		sourceGbx->show();
	}
	else
	{
		sourceGbx->hide();
		surnameLb->setText("");
		accountName->setText("");
		accableIDEdit->setText("");
		purEditID->setText("");
		accID->setText("");
	}
}

void CreateInveDlg::TextEditChanged()
{
	if (costEdit->text().contains(","))
	{
		costEdit->setText(costEdit->text().replace(",", "."));
	}
	if (costEdit->text().contains(".."))
	{
		costEdit->setText(costEdit->text().replace("..", "."));
	}
}

void CreateInveDlg::GenerateInventoryNumber()
{
	std::string invNumber = "";
	invNumber =  inventoryUnion->GenerateInventoryNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), divisionCmb->currentData().toInt());
	numberEdit->setText(invNumber.c_str());
}


