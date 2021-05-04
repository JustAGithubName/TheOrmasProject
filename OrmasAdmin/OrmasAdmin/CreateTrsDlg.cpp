#include "stdafx.h"

#include "CreateTrsDlg.h"
#include "DataForm.h"
#include <map>

CreateTrsDlg::CreateTrsDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	employeeEdit->setValidator(vInt);
	stockEmployeeEdit->setValidator(vInt);
	prodCountEdit->setValidator(vDouble);
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);
	

	//hide employee, because it's not needed
	empNamePh->setVisible(false);
	empSurnamePh->setVisible(false);
	empPhonePh->setVisible(false);
	empNameLb->setVisible(false);
	empSurnameLb->setVisible(false);
	empPhoneLb->setVisible(false);
	employeeBtn->setVisible(false);
	employeeEdit->setVisible(false);
	//
	 
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateTrsDlg::EditTransport);
	}
	else
	{
		transport->SetID(dialogBL->GenerateID());
		execDateWidget->setVisible(false);
		execDateEdit->setDateTime(QDateTime::currentDateTime());
		employeeEdit->setText("0");
		stockEmployeeEdit->setText("0");
		prodCountEdit->setText("0");
		sumEdit->setText("0");
		dateEdit->setDateTime(QDateTime::currentDateTime());

		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("TRANSPORTING");
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

		QObject::connect(okBtn, &QPushButton::released, this, &CreateTrsDlg::CreateTransport);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateTrsDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateTrsDlg::OpenEmpDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateTrsDlg::OpenStsDlg);
	QObject::connect(stockEmployeeBtn, &QPushButton::released, this, &CreateTrsDlg::OpenUserDlg);
	QObject::connect(addProdBtn, &QPushButton::released, this, &CreateTrsDlg::OpenTrsListDlg);
	QObject::connect(statusEdit, &QLineEdit::textChanged, this, &CreateTrsDlg::StatusWasChenged);
	QObject::connect(prodCountEdit, &QLineEdit::textChanged, this, &CreateTrsDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateTrsDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateTrsDlg::~CreateTrsDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();
	
}

void CreateTrsDlg::SetTransportParams(int tUserID, QString tDate, QString tExecDate, int tEmployeeID, double tCount,
	double tSum, int tStatusID, int tCurrencyID, int id)
{
	transport->SetUserID(tUserID);
	transport->SetDate(tDate.toUtf8().constData());
	transport->SetExecutionDate(tExecDate.toUtf8().constData());
	transport->SetEmployeeID(tEmployeeID);
	transport->SetCount(tCount);
	transport->SetSum(tSum);
	transport->SetStatusID(tStatusID);
	transport->SetCurrencyID(tCurrencyID);
	transport->SetID(id);
}

void CreateTrsDlg::FillEditElements(int tUserID, QString tDate, QString tExecDate, int tEmployeeID, double tCount,
	double tSum, int tStatusID, int tCurrencyID)
{
	employeeEdit->setText(QString::number(tUserID));
	dateEdit->setDateTime(QDateTime::fromString(tDate, "dd.MM.yyyy hh:mm"));
	if (!tExecDate.isEmpty())
	{
		execDateEdit->setDateTime(QDateTime::fromString(tExecDate, "dd.MM.yyyy hh:mm"));
	}
	stockEmployeeEdit->setText(QString::number(tEmployeeID));
	prodCountEdit->setText(QString::number(tCount, 'f', 3));
	sumEdit->setText(QString::number(tSum, 'f', 3));
	statusEdit->setText(QString::number(tStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(tCurrencyID)));
	BusinessLayer::User user1;
	if (user1.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), tUserID, errorMessage))
	{
		empNamePh->setText(user1.GetName().c_str());
		empSurnamePh->setText(user1.GetSurname().c_str());
		empPhonePh->setText(user1.GetPhone().c_str());
	}
	BusinessLayer::User user2;
	if (user2.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), tEmployeeID, errorMessage))
	{
		empStockNamePh->setText(user2.GetName().c_str());
		empStockSurnamePh->setText(user2.GetSurname().c_str());
		empStockPhonePh->setText(user2.GetPhone().c_str());
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), tStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

void CreateTrsDlg::SetID(int ID, QString childName)
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

			if (childName == QString("userForm"))
			{
				employeeEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					empNamePh->setText(user.GetName().c_str());
					empSurnamePh->setText(user.GetSurname().c_str());
					empPhonePh->setText(user.GetPhone().c_str());
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
				stockEmployeeEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					empStockNamePh->setText(user.GetName().c_str());
					empStockSurnamePh->setText(user.GetSurname().c_str());
					empStockPhonePh->setText(user.GetPhone().c_str());
				}
			}
		}
	}
}

bool CreateTrsDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetTransportParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 17)).toInt(),
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
		BusinessLayer::Status *status = new BusinessLayer::Status;
		if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetStatusID(), errorMessage))
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
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This document have an \"EXECUTED\" status. The document with \"EXECUTED\" status cannot be changed!")),
				QString(tr("Ok")));
			errorMessage.clear();
			delete status;
			return false;
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
	else
	{
		return false;
	}
}

void CreateTrsDlg::CreateTransport()
{
	errorMessage.clear();
	if (0 != stockEmployeeEdit->text().toInt() 
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && 0 != currencyCmb->currentData().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		if (!execDateWidget->isVisible())
		{
			SetTransportParams(employeeEdit->text().toInt(), dateEdit->text(), "", stockEmployeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), transport->GetID());
		}
		else
		{
			SetTransportParams(employeeEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), stockEmployeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), transport->GetID());
		}
		
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateTransport(transport, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					QList<QStandardItem*> transportItem;
					transportItem << new QStandardItem(QString::number(transport->GetID()))
						<< new QStandardItem(transport->GetDate().c_str())
						<< new QStandardItem(transport->GetExecutionDate().c_str())
						<< new QStandardItem(status->GetCode().c_str())
						<< new QStandardItem(status->GetName().c_str());

					BusinessLayer::Employee *user = new BusinessLayer::Employee();
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;

					if (!user->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetEmployeeID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete employee;
						delete currency;
						delete status;
						return;
					}

					if (transport->GetEmployeeID() > 0)
					{
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							return;
						}
					}

					if (0 != transport->GetUserID())
					{
						BusinessLayer::Position *ePosition = new BusinessLayer::Position();
						if (!user->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetUserID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete ePosition;
							return;
						}
						transportItem << new QStandardItem(user->GetName().c_str())
							<< new QStandardItem(user->GetSurname().c_str())
							<< new QStandardItem(user->GetPhone().c_str())
							<< new QStandardItem(ePosition->GetName().c_str());
					}
					else
					{
						transportItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}
					if (0 != transport->GetEmployeeID())
					{
						BusinessLayer::Position *sePosition = new BusinessLayer::Position();
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete sePosition;
							return;
						}
						transportItem << new QStandardItem(employee->GetName().c_str())
							<< new QStandardItem(employee->GetSurname().c_str())
							<< new QStandardItem(employee->GetPhone().c_str())
							<< new QStandardItem(sePosition->GetName().c_str());
					}
					else
					{
						transportItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}
					transportItem << new QStandardItem(QString::number(transport->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(transport->GetSum(),'f',3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(transport->GetEmployeeID()))
						<< new QStandardItem(QString::number(transport->GetUserID()))
						<< new QStandardItem(QString::number(transport->GetStatusID()))
						<< new QStandardItem(QString::number(transport->GetCurrencyID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(transportItem);
					delete employee;
					delete user;
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

void CreateTrsDlg::EditTransport()
{
	errorMessage.clear();
	if (0 != stockEmployeeEdit->text().toInt()
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && 0 != currencyCmb->currentData().toInt())
	{
		if (transport->GetEmployeeID() != stockEmployeeEdit->text().toInt() || QString(transport->GetDate().c_str()) != dateEdit->text() ||
			QString(transport->GetExecutionDate().c_str()) != execDateEdit->text() ||
			transport->GetUserID() != employeeEdit->text().toInt() || transport->GetCount() != prodCountEdit->text().toDouble() ||
			transport->GetSum() != sumEdit->text().toDouble()
			|| transport->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			if (!execDateWidget->isVisible())
			{
				SetTransportParams(employeeEdit->text().toInt(), dateEdit->text(), "", stockEmployeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), transport->GetID());
			}
			else
			{
				SetTransportParams(employeeEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), stockEmployeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), transport->GetID());
			}
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateTransport(transport, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating Transport data
						
						itemModel->item(mIndex.row(), 1)->setText(transport->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(transport->GetExecutionDate().c_str());


						BusinessLayer::Employee *user = new BusinessLayer::Employee();
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();
						BusinessLayer::Status *status = new BusinessLayer::Status;

						if (!user->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetUserID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetCurrencyID(), errorMessage)
							|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							delete currency;
							delete user;
							delete status;
							return;
						}
						if (transport->GetEmployeeID() > 0)
						{
							if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetEmployeeID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								delete employee;
								return;
							}
						}
						itemModel->item(mIndex.row(), 3)->setText(status->GetCode().c_str());
						itemModel->item(mIndex.row(), 4)->setText(status->GetName().c_str());
						if (transport->GetUserID() > 0)
						{
							BusinessLayer::Position *ePosition = new BusinessLayer::Position();
							if (!user->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetUserID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								delete ePosition;
								return;
							}
							itemModel->item(mIndex.row(), 5)->setText(user->GetName().c_str());
							itemModel->item(mIndex.row(), 6)->setText(user->GetSurname().c_str());
							itemModel->item(mIndex.row(), 7)->setText(user->GetPhone().c_str());
							itemModel->item(mIndex.row(), 8)->setText(ePosition->GetName().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 5)->setText("");
							itemModel->item(mIndex.row(), 6)->setText("");
							itemModel->item(mIndex.row(), 7)->setText("");
							itemModel->item(mIndex.row(), 8)->setText("");
						}
						if (transport->GetEmployeeID() > 0)
						{
							BusinessLayer::Position *sePosition = new BusinessLayer::Position();
							if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transport->GetEmployeeID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								delete sePosition;
								return;
							}
							itemModel->item(mIndex.row(), 9)->setText(employee->GetName().c_str());
							itemModel->item(mIndex.row(), 10)->setText(employee->GetSurname().c_str());
							itemModel->item(mIndex.row(), 11)->setText(employee->GetPhone().c_str());
							itemModel->item(mIndex.row(), 12)->setText(sePosition->GetName().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 9)->setText("");
							itemModel->item(mIndex.row(), 10)->setText("");
							itemModel->item(mIndex.row(), 11)->setText("");
							itemModel->item(mIndex.row(), 12)->setText("");
						}

						itemModel->item(mIndex.row(), 13)->setText(QString::number(transport->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(transport->GetSum(),'f',3));
						itemModel->item(mIndex.row(), 15)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 16)->setText(QString::number(transport->GetEmployeeID()));
						itemModel->item(mIndex.row(), 17)->setText(QString::number(transport->GetUserID()));
						itemModel->item(mIndex.row(), 18)->setText(QString::number(transport->GetStatusID()));
						itemModel->item(mIndex.row(), 19)->setText(QString::number(transport->GetCurrencyID()));

						emit itemModel->dataChanged(mIndex, mIndex);

						delete user;
						delete employee;
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

void CreateTrsDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateTrsDlg::OpenEmpDlg()
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

void CreateTrsDlg::OpenUserDlg()
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
		dForm->setObjectName("userForm");
		dForm->QtConnect<BusinessLayer::EmployeeView>();
		QMdiSubWindow *stockEmployeeWindow = new QMdiSubWindow;
		stockEmployeeWindow->setWidget(dForm);
		stockEmployeeWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(stockEmployeeWindow);
		stockEmployeeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All stock employees are shown");
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

void CreateTrsDlg::OpenStsDlg()
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

void CreateTrsDlg::OpenTrsListDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Add product"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->transportID = transport->GetID();
	BusinessLayer::TransportList transportList;
	transportList.SetTransportID(transport->GetID());
	std::string transportListFilter = transportList.GenerateFilter(dialogBL->GetOrmasDal());
	dForm->FillTable<BusinessLayer::TransportListView>(errorMessage, transportListFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("transportListForm");
		dForm->QtConnect<BusinessLayer::TransportListView>();
		QMdiSubWindow *transportWindow = new QMdiSubWindow;
		transportWindow->setWidget(dForm);
		transportWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(transportWindow);
		transportWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreateTrsDlg::StatusWasChenged()
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

void CreateTrsDlg::InitComboBox()
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

void CreateTrsDlg::TextEditChanged()
{
	if (prodCountEdit->text().contains(","))
	{
		prodCountEdit->setText(prodCountEdit->text().replace(",", "."));
	}
	if (prodCountEdit->text().contains(".."))
	{
		prodCountEdit->setText(prodCountEdit->text().replace("..", "."));
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