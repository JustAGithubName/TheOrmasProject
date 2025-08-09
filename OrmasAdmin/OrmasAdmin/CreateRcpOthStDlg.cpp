#include "stdafx.h"

#include "CreateRcpOthStDlg.h"
#include "DataForm.h"

#include <map>

CreateRcpOthStDlg::CreateRcpOthStDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	
	//setModal(true);
	dialogBL = ormasBL;
	
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	purveyorEdit->setValidator(vInt);
	employeeEdit->setValidator(vInt);
	othStCountEdit->setValidator(vDouble);
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);

	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRcpOthStDlg::EditReceiptOtherStocks);
	}
	else
	{
		receiptOtherStocks->SetID(dialogBL->GenerateID());
		execDateWidget->setVisible(false);
		execDateEdit->setDateTime(QDateTime::currentDateTime());
		employeeEdit->setText("0");
		purveyorEdit->setText("0");
		othStCountEdit->setText("0");
		statusEdit->setText("0");
		sumEdit->setText("0");
		dateEdit->setDateTime(QDateTime::currentDateTime());

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
		statusEdit->setText(QString::number(statusVector.at(0).GetID()));
		statusPh->setText(statusVector.at(0).GetName().c_str());

		QObject::connect(okBtn, &QPushButton::released, this, &CreateRcpOthStDlg::CreateReceiptOtherStocks);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateRcpOthStDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateRcpOthStDlg::OpenEmpDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateRcpOthStDlg::OpenStsDlg);
	QObject::connect(purveyorBtn, &QPushButton::released, this, &CreateRcpOthStDlg::OpenPurDlg);
	QObject::connect(addOthStBtn, &QPushButton::released, this, &CreateRcpOthStDlg::OpenRcpOthStListDlg);
	QObject::connect(statusEdit, &QLineEdit::textChanged, this, &CreateRcpOthStDlg::StatusWasChenged);
	QObject::connect(othStCountEdit, &QLineEdit::textChanged, this, &CreateRcpOthStDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateRcpOthStDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateRcpOthStDlg::~CreateRcpOthStDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();

}

void CreateRcpOthStDlg::SetReceiptOtherStocksParams(int oPurveyorID, QString oDate, QString oExecDate, int oEmployeeID, double oCount,
	double oSum, int oStatusID, int oCurrencyID, int id)
{
	receiptOtherStocks->SetPurveyorID(oPurveyorID);
	receiptOtherStocks->SetDate(oDate.toUtf8().constData());
	receiptOtherStocks->SetExecutionDate(oExecDate.toUtf8().constData());
	receiptOtherStocks->SetEmployeeID(oEmployeeID);
	receiptOtherStocks->SetCount(oCount);
	receiptOtherStocks->SetSum(oSum);
	receiptOtherStocks->SetStatusID(oStatusID);
	receiptOtherStocks->SetCurrencyID(oCurrencyID);
	receiptOtherStocks->SetID(id);
}

void CreateRcpOthStDlg::FillEditElements(int oPurveyorID, QString oDate, QString oExecDate, int oEmployeeID, double oCount,
	double oSum, int oStatusID, int oCurrencyID)
{
	purveyorEdit->setText(QString::number(oPurveyorID));
	dateEdit->setDateTime(QDateTime::fromString(oDate, "dd.MM.yyyy hh:mm"));
	if (!oExecDate.isEmpty())
	{
		execDateEdit->setDateTime(QDateTime::fromString(oExecDate, "dd.MM.yyyy hh:mm"));
	}
	employeeEdit->setText(QString::number(oEmployeeID));
	othStCountEdit->setText(QString::number(oCount, 'f', 3));
	sumEdit->setText(QString::number(oSum, 'f', 3));
	statusEdit->setText(QString::number(oStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(oCurrencyID)));
	BusinessLayer::User user1;
	if (user1.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oPurveyorID, errorMessage))
	{
		prNamePh->setText(user1.GetName().c_str());
		prSurnamePh->setText(user1.GetSurname().c_str());
		prPhonePh->setText(user1.GetPhone().c_str());
	}
	BusinessLayer::User user2;
	if (user2.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oEmployeeID, errorMessage))
	{
		empNamePh->setText(user2.GetName().c_str());
		empSurnamePh->setText(user2.GetSurname().c_str());
		empPhonePh->setText(user2.GetPhone().c_str());
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

void CreateRcpOthStDlg::SetID(int ID, QString childName)
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

			if (childName == QString("purveyorForm"))
			{
				purveyorEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					prNamePh->setText(user.GetName().c_str());
					prSurnamePh->setText(user.GetSurname().c_str());
					prPhonePh->setText(user.GetPhone().c_str());
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
			if (childName == QString("employeeForm"))
			{
				BusinessLayer::WarehouseEmployeeRelation weRel;
				if (!weRel.GetWarehouseEmployeeByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr("This user isn't warehouse employee!")),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				BusinessLayer::Warehouse warehouse;
				if (!warehouse.GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), weRel.GetWarehouseID(), errorMessage))
				{
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr("Cannot find warehouse!")),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				BusinessLayer::WarehouseType warehouseType;
				if (!warehouseType.GetWarehouseTypeByCode(dialogBL->globalVar, dialogBL->GetOrmasDal(), "RAW", errorMessage))
				{
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr("Cannot find warehouse type!")),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				if (warehouseType.GetID() != warehouse.GetWarehouseTypeID())
				{
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr("This user isn't raw warehouse employee!")),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				employeeEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					empNamePh->setText(user.GetName().c_str());
					empSurnamePh->setText(user.GetSurname().c_str());
					empPhonePh->setText(user.GetPhone().c_str());
				}
			}
		}
	}
}

bool CreateRcpOthStDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetReceiptOtherStocksParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 17)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 16)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 13)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 14)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 18)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 19)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 17)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 16)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 13)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 14)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 18)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 19)).toInt());

		return CheckAccess();
	}
	else
	{
		return false;
	}
}

void CreateRcpOthStDlg::CreateReceiptOtherStocks()
{
	errorMessage.clear();
	if (0 != purveyorEdit->text().toInt() && 0 != employeeEdit->text().toInt()
		&& 0 != othStCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && 0 != currencyCmb->currentData().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		if (!execDateWidget->isVisible())
		{
			SetReceiptOtherStocksParams(purveyorEdit->text().toInt(), dateEdit->text(), "", employeeEdit->text().toInt(), othStCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), receiptOtherStocks->GetID());
		}
		else
		{
			SetReceiptOtherStocksParams(purveyorEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), employeeEdit->text().toInt(), othStCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), receiptOtherStocks->GetID());
		}

		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateReceiptOtherStocks(receiptOtherStocks, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					QList<QStandardItem*> receiptOtherStocksItem;
					receiptOtherStocksItem << new QStandardItem(QString::number(receiptOtherStocks->GetID()))
						<< new QStandardItem(receiptOtherStocks->GetDate().c_str())
						<< new QStandardItem(receiptOtherStocks->GetExecutionDate().c_str())
						<< new QStandardItem(status->GetCode().c_str())
						<< new QStandardItem(status->GetName().c_str());

					BusinessLayer::Purveyor *purveyor = new BusinessLayer::Purveyor();
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;

					if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetEmployeeID(), errorMessage)
						|| !purveyor->GetPurveyorByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetPurveyorID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete employee;
						delete purveyor;
						delete currency;
						delete status;
						return;
					}

					if (0 != receiptOtherStocks->GetPurveyorID())
					{
						receiptOtherStocksItem << new QStandardItem(purveyor->GetName().c_str())
							<< new QStandardItem(purveyor->GetSurname().c_str())
							<< new QStandardItem(purveyor->GetPhone().c_str())
							<< new QStandardItem(purveyor->GetCompanyName().c_str());
					}
					else
					{
						receiptOtherStocksItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}

					if (0 != receiptOtherStocks->GetEmployeeID())
					{
						BusinessLayer::Position *ePosition = new BusinessLayer::Position();
						if (!ePosition->GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee->GetPositionID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete ePosition;
							return;
						}
						receiptOtherStocksItem << new QStandardItem(employee->GetName().c_str())
							<< new QStandardItem(employee->GetSurname().c_str())
							<< new QStandardItem(employee->GetPhone().c_str())
							<< new QStandardItem(ePosition->GetName().c_str());
					}
					else
					{
						receiptOtherStocksItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}


					receiptOtherStocksItem << new QStandardItem(QString::number(receiptOtherStocks->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(receiptOtherStocks->GetSum(), 'f', 3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(receiptOtherStocks->GetEmployeeID()))
						<< new QStandardItem(QString::number(receiptOtherStocks->GetPurveyorID()))
						<< new QStandardItem(QString::number(receiptOtherStocks->GetStatusID()))
						<< new QStandardItem(QString::number(receiptOtherStocks->GetCurrencyID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(receiptOtherStocksItem);

					delete employee;
					delete purveyor;
					delete currency;
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

void CreateRcpOthStDlg::EditReceiptOtherStocks()
{
	errorMessage.clear();
	if (0 != purveyorEdit->text().toInt() && 0 != employeeEdit->text().toInt()
		&& 0 != othStCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && 0 != currencyCmb->currentData().toInt())
	{
		if (receiptOtherStocks->GetEmployeeID() != employeeEdit->text().toInt() || QString(receiptOtherStocks->GetDate().c_str()) != dateEdit->text() ||
			receiptOtherStocks->GetPurveyorID() != purveyorEdit->text().toInt() || QString(receiptOtherStocks->GetExecutionDate().c_str()) != execDateEdit->text() ||
			receiptOtherStocks->GetEmployeeID() != employeeEdit->text().toInt() || receiptOtherStocks->GetCount() != othStCountEdit->text().toDouble() ||
			receiptOtherStocks->GetSum() != sumEdit->text().toDouble()
			|| receiptOtherStocks->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			if (!execDateWidget->isVisible())
			{
				SetReceiptOtherStocksParams(purveyorEdit->text().toInt(), dateEdit->text(), "", employeeEdit->text().toInt(), othStCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), receiptOtherStocks->GetID());
			}
			else
			{
				SetReceiptOtherStocksParams(purveyorEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), employeeEdit->text().toInt(), othStCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), receiptOtherStocks->GetID());
			}
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateReceiptOtherStocks(receiptOtherStocks, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating ReceiptOtherStocks data
						itemModel->item(mIndex.row(), 1)->setText(receiptOtherStocks->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(receiptOtherStocks->GetExecutionDate().c_str());


						BusinessLayer::Purveyor *purveyor = new BusinessLayer::Purveyor();
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						BusinessLayer::Status *status = new BusinessLayer::Status;
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetEmployeeID(), errorMessage)
							|| !purveyor->GetPurveyorByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetPurveyorID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetCurrencyID(), errorMessage)
							|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							delete purveyor;
							delete currency;
							delete status;
							return;
						}

						itemModel->item(mIndex.row(), 3)->setText(status->GetCode().c_str());
						itemModel->item(mIndex.row(), 4)->setText(status->GetName().c_str());

						if (receiptOtherStocks->GetPurveyorID() > 0)
						{
							itemModel->item(mIndex.row(), 5)->setText(purveyor->GetName().c_str());
							itemModel->item(mIndex.row(), 6)->setText(purveyor->GetSurname().c_str());
							itemModel->item(mIndex.row(), 7)->setText(purveyor->GetPhone().c_str());
							itemModel->item(mIndex.row(), 8)->setText(purveyor->GetCompanyName().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 5)->setText("");
							itemModel->item(mIndex.row(), 6)->setText("");
							itemModel->item(mIndex.row(), 7)->setText("");
							itemModel->item(mIndex.row(), 8)->setText("");
						}

						if (receiptOtherStocks->GetEmployeeID() > 0)
						{
							BusinessLayer::Position *ePosition = new BusinessLayer::Position();
							if (!ePosition->GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee->GetPositionID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								delete ePosition;
								return;
							}
							itemModel->item(mIndex.row(), 9)->setText(employee->GetName().c_str());
							itemModel->item(mIndex.row(), 10)->setText(employee->GetSurname().c_str());
							itemModel->item(mIndex.row(), 11)->setText(employee->GetPhone().c_str());
							itemModel->item(mIndex.row(), 12)->setText(ePosition->GetName().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 9)->setText("");
							itemModel->item(mIndex.row(), 10)->setText("");
							itemModel->item(mIndex.row(), 11)->setText("");
							itemModel->item(mIndex.row(), 12)->setText("");
						}


						itemModel->item(mIndex.row(), 13)->setText(QString::number(receiptOtherStocks->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(receiptOtherStocks->GetSum(), 'f', 3));
						itemModel->item(mIndex.row(), 15)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 16)->setText(QString::number(receiptOtherStocks->GetEmployeeID()));
						itemModel->item(mIndex.row(), 17)->setText(QString::number(receiptOtherStocks->GetPurveyorID()));
						itemModel->item(mIndex.row(), 18)->setText(QString::number(receiptOtherStocks->GetStatusID()));
						itemModel->item(mIndex.row(), 19)->setText(QString::number(receiptOtherStocks->GetCurrencyID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete employee;
						delete purveyor;
						delete currency;
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

void CreateRcpOthStDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateRcpOthStDlg::OpenPurDlg()
{
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

void CreateRcpOthStDlg::OpenEmpDlg()
{
	if (othStCountEdit->text().toInt() > 0)
	{
		QString message = tr("Cannot change employee!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Cannot change stock employee after adding product!")),
			QString(tr("Ok")));
		return;
	}
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
	role->SetName("STOCK MANAGER");
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
		QString message = tr("Sorry could not find employee with \"stock employee\" role!");
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

void CreateRcpOthStDlg::OpenStsDlg()
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


void CreateRcpOthStDlg::OpenRcpOthStListDlg()
{
	if (employeeEdit->text().toInt() == 0 || employeeEdit->text().toInt() < 0)
	{
		QString message = tr("Enter stock employee before!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Enter stock employee before!")),
			QString(tr("Ok")));
		return;
	}
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Add product"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->receiptOtherStocksID = receiptOtherStocks->GetID();
	dForm->employeeID = employeeEdit->text().toInt();
	BusinessLayer::ReceiptOtherStocksList receiptOtherStocksList;
	receiptOtherStocksList.SetReceiptOtherStocksID(receiptOtherStocks->GetID());
	std::string receiptOtherStocksListFilter = receiptOtherStocksList.GenerateFilter(dialogBL->GetOrmasDal());
	dForm->FillTable<BusinessLayer::ReceiptOtherStocksListView>(errorMessage, receiptOtherStocksListFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("receiptOtherStocksListForm");
		dForm->QtConnect<BusinessLayer::ReceiptOtherStocksListView>();
		QMdiSubWindow *receiptOtherStocksWindow = new QMdiSubWindow;
		receiptOtherStocksWindow->setWidget(dForm);
		receiptOtherStocksWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(receiptOtherStocksWindow);
		receiptOtherStocksWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreateRcpOthStDlg::StatusWasChenged()
{
	errorMessage = "";
	statusMap = BusinessLayer::Status::GetStatusesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (statusEdit->text().toInt() == statusMap.find("EXECUTED")->second
		|| statusEdit->text().toInt() == statusMap.find("RETURN")->second
		|| statusEdit->text().toInt() == statusMap.find("ERROR")->second)
	{
		execDateWidget->setVisible(true);
		execDateEdit->setDateTime(QDateTime::currentDateTime());
	}
	else
	{
		execDateWidget->setVisible(false);
		execDateEdit->setDateTime(QDateTime::fromString("01.01.2000", "dd.mm.yyyy"));
	}
}

void CreateRcpOthStDlg::InitComboBox()
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

void CreateRcpOthStDlg::TextEditChanged()
{
	if (othStCountEdit->text().contains(","))
	{
		othStCountEdit->setText(othStCountEdit->text().replace(",", "."));
	}
	if (othStCountEdit->text().contains(".."))
	{
		othStCountEdit->setText(othStCountEdit->text().replace("..", "."));
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

bool CreateRcpOthStDlg::CheckAccess()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return false;
	BusinessLayer::Status *status = new BusinessLayer::Status;
	if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), receiptOtherStocks->GetStatusID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		delete status;
		return false;
	}

	if (0 == status->GetName().compare("EXECUTED"))
	{
		if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
			mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
		{
			return true;
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This document have an \"EXECUTED\" status. The document with \"EXECUTED\" status cannot be changed!")),
				QString(tr("Ok")));
			errorMessage.clear();
			delete status;
			return false;
		}
	}

	if (0 == status->GetName().compare("RETURN"))
	{
		if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
			mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
		{
			return true;
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This document have an \"RETURN\" status. The document with \"EXECUTED\" status cannot be changed!")),
				QString(tr("Ok")));
			errorMessage.clear();
			delete status;
			return false;
		}
	}

	if (0 == status->GetName().compare("ERROR"))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("This document have an \"ERROR\" status. The document with \"ERROR\" status cannot be changed!")),
			QString(tr("Ok")));
		errorMessage.clear();
		delete status;
		return false;
	}

	return true;
}
