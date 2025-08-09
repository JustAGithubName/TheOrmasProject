#include "stdafx.h"
#include "CreateRtrnDlg.h"
#include "DataForm.h"
#include <map>

CreateRtrnDlg::CreateRtrnDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	
	//setModal(true);
	dialogBL = ormasBL;
	
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();

	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	clientEdit->setValidator(vInt);
	employeeEdit->setValidator(vInt);
	prodCountEdit->setValidator(vDouble);
	clientEdit->setValidator(vInt);
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRtrnDlg::EditReturn);
	}
	else
	{
		ret->SetID(dialogBL->GenerateID());
		execDateWidget->setVisible(false);
		execDateEdit->setDateTime(QDateTime::currentDateTime());
		clientEdit->setText("0");
		employeeEdit->setText("0");
		prodCountEdit->setText("0");
		clientEdit->setText("0");
		statusEdit->setText("0");
		sumEdit->setText("0");
		dateEdit->setDateTime(QDateTime::currentDateTime());

		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("TO RETURN");
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

		QObject::connect(okBtn, &QPushButton::released, this, &CreateRtrnDlg::CreateReturn);
	}

	

	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateRtrnDlg::Close);
	QObject::connect(clientBtn, &QPushButton::released, this, &CreateRtrnDlg::OpenCltDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateRtrnDlg::OpenStsDlg);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateRtrnDlg::OpenEmpDlg);
	QObject::connect(addProdBtn, &QPushButton::released, this, &CreateRtrnDlg::OpenRtrnListDlg);
	QObject::connect(statusEdit, &QLineEdit::textChanged, this, &CreateRtrnDlg::StatusWasChenged);
	QObject::connect(prodCountEdit, &QLineEdit::textChanged, this, &CreateRtrnDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateRtrnDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateRtrnDlg::~CreateRtrnDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();

}

void CreateRtrnDlg::SetReturnParams(int rClientID, QString rDate, QString rExecDate, int rEmployeeID, double rCount, double rSum, int rStatusID, int rCurrencyID, int id)
{
	ret->SetClientID(rClientID);
	ret->SetDate(rDate.toUtf8().constData());
	ret->SetExecutionDate(rExecDate.toUtf8().constData());
	ret->SetEmployeeID(rEmployeeID);
	ret->SetCount(rCount);
	ret->SetSum(rSum);
	ret->SetStatusID(rStatusID);
	ret->SetCurrencyID(rCurrencyID);
	ret->SetID(id);
}

void CreateRtrnDlg::FillEditElements(int rClientID, QString rDate, QString rExecDate, int rEmployeeID, double rCount, double rSum, int rStatusID, int rCurrencyID)
{
	clientEdit->setText(QString::number(rClientID));
	dateEdit->setDateTime(QDateTime::fromString(rDate, "dd.MM.yyyy hh:mm"));
	if (!rExecDate.isEmpty())
	{
		execDateEdit->setDateTime(QDateTime::fromString(rExecDate, "dd.MM.yyyy hh:mm"));
	}
	employeeEdit->setText(QString::number(rEmployeeID));
	prodCountEdit->setText(QString::number(rCount, 'f', 3));
	sumEdit->setText(QString::number(rSum, 'f', 3));
	statusEdit->setText(QString::number(rStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(rCurrencyID)));
	BusinessLayer::User user1;
	if (user1.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), rClientID, errorMessage))
	{
		clNamePh->setText(user1.GetName().c_str());
		clSurnamePh->setText(user1.GetSurname().c_str());
		clPhonePh->setText(user1.GetPhone().c_str());
	}
	BusinessLayer::User user2;
	if (user2.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), rEmployeeID, errorMessage))
	{
		empNamePh->setText(user2.GetName().c_str());
		empSurnamePh->setText(user2.GetSurname().c_str());
		empPhonePh->setText(user2.GetPhone().c_str());
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), rStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

void CreateRtrnDlg::SetID(int ID, QString childName)
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

			if (childName == QString("clientForm"))
			{
				clientEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					clNamePh->setText(user.GetName().c_str());
					clSurnamePh->setText(user.GetSurname().c_str());
					clPhonePh->setText(user.GetPhone().c_str());
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

bool CreateRtrnDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetReturnParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 17)).toInt(),
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

void CreateRtrnDlg::CreateReturn()
{
	errorMessage.clear();
	if (0 != clientEdit->text().toInt() 
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && 0 != currencyCmb->currentData().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		if (!execDateWidget->isVisible())
		{
			SetReturnParams(clientEdit->text().toInt(), dateEdit->text(), "", employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), ret->GetID());
		}
		else
		{
			SetReturnParams(clientEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), ret->GetID());
		}
		ret->warehouseID = warehouseCmb->currentData().toInt();
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateReturn(ret, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}

					QList<QStandardItem*> returnItem;
					returnItem << new QStandardItem(QString::number(ret->GetID()))
						<< new QStandardItem(ret->GetDate().c_str())
						<< new QStandardItem(ret->GetExecutionDate().c_str())
						<< new QStandardItem(status->GetCode().c_str())
						<< new QStandardItem(status->GetName().c_str());

					BusinessLayer::Client *client = new BusinessLayer::Client();
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;

					if (!client->GetClientByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetClientID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete client;
						delete currency;
						return;
					}

					if (ret->GetEmployeeID() > 0)
					{
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetEmployeeID(), errorMessage))
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

					if (0 != ret->GetClientID())
					{
						returnItem << new QStandardItem(client->GetName().c_str())
							<< new QStandardItem(client->GetSurname().c_str())
							<< new QStandardItem(client->GetPhone().c_str())
							<< new QStandardItem(client->GetAddress().c_str())
							<< new QStandardItem(client->GetFirm().c_str());
					}
					else
					{
						returnItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}

					if (0 != ret->GetEmployeeID())
					{
						returnItem << new QStandardItem(employee->GetName().c_str())
							<< new QStandardItem(employee->GetSurname().c_str())
							<< new QStandardItem(employee->GetPhone().c_str());
					}
					else
					{
						returnItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}

					returnItem << new QStandardItem(QString::number(ret->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(ret->GetSum(),'f',3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(ret->GetEmployeeID()))
						<< new QStandardItem(QString::number(ret->GetClientID()))
						<< new QStandardItem(QString::number(ret->GetStatusID()))
						<< new QStandardItem(QString::number(ret->GetCurrencyID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(returnItem);
					delete client;
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
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields, especially product list!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateRtrnDlg::EditReturn()
{
	errorMessage.clear();
	if (0 != clientEdit->text().toInt()
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && 0 != currencyCmb->currentData().toInt())
	{
		if (ret->GetClientID() != clientEdit->text().toInt() || QString(ret->GetDate().c_str()) != dateEdit->text() ||
			QString(ret->GetExecutionDate().c_str()) != execDateEdit->text() ||
			ret->GetEmployeeID() != employeeEdit->text().toInt() || ret->GetCount() != prodCountEdit->text().toDouble() ||
			ret->GetSum() != sumEdit->text().toDouble()
			|| ret->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			if (!execDateWidget->isVisible())
			{
				SetReturnParams(clientEdit->text().toInt(), dateEdit->text(), "", employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), ret->GetID());
			}
			else
			{
				SetReturnParams(clientEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), ret->GetID());
			}
			ret->warehouseID = warehouseCmb->currentData().toInt();
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateReturn(ret, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating ret data
						itemModel->item(mIndex.row(), 1)->setText(ret->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(ret->GetExecutionDate().c_str());


						BusinessLayer::Client *client = new BusinessLayer::Client();
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();
						BusinessLayer::Status *status = new BusinessLayer::Status;

						if (!client->GetClientByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetClientID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetCurrencyID(), errorMessage)
							|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							delete currency;
							delete client;
							delete status;
							return;
						}
						if (ret->GetEmployeeID() > 0)
						{
							if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetEmployeeID(), errorMessage))
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
						itemModel->item(mIndex.row(), 5)->setText(client->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(client->GetSurname().c_str());
						itemModel->item(mIndex.row(), 7)->setText(client->GetPhone().c_str());
						itemModel->item(mIndex.row(), 8)->setText(client->GetAddress().c_str());
						itemModel->item(mIndex.row(), 9)->setText(client->GetFirm().c_str());
						if (ret->GetEmployeeID() > 0)
						{
							itemModel->item(mIndex.row(), 10)->setText(employee->GetName().c_str());
							itemModel->item(mIndex.row(), 11)->setText(employee->GetSurname().c_str());
							itemModel->item(mIndex.row(), 12)->setText(employee->GetPhone().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 10)->setText("");
							itemModel->item(mIndex.row(), 11)->setText("");
							itemModel->item(mIndex.row(), 12)->setText("");
						}
						itemModel->item(mIndex.row(), 13)->setText(QString::number(ret->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(ret->GetSum(),'f',3));
						itemModel->item(mIndex.row(), 15)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 16)->setText(QString::number(ret->GetEmployeeID()));
						itemModel->item(mIndex.row(), 17)->setText(QString::number(ret->GetClientID()));
						itemModel->item(mIndex.row(), 18)->setText(QString::number(ret->GetStatusID()));
						itemModel->item(mIndex.row(), 19)->setText(QString::number(ret->GetCurrencyID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete client;
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

void CreateRtrnDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateRtrnDlg::OpenCltDlg()
{
	if (employeeEdit->text().toInt() == 0 || employeeEdit->text().toInt() < 0)
	{
		QString message = tr("Enter employee before!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Enter employee before!")),
			QString(tr("Ok")));
		return;
	}
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Clients"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	BusinessLayer::Role *role = new BusinessLayer::Role();
	role->SetName("CLIENT");
	std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
	std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);
	if (roleVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not define the role for this client!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}
	BusinessLayer::Client *client = new BusinessLayer::Client();
	client->SetRoleID(roleVector.at(0).GetID());
	std::string clientFilter = dialogBL->GenerateFilter<BusinessLayer::Client>(client);
	std::vector<BusinessLayer::ClientView> clientVector = dialogBL->GetAllDataForClass<BusinessLayer::ClientView>(errorMessage, clientFilter);
	if (clientVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not find client!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	dForm->FillTable<BusinessLayer::ClientView>(errorMessage, clientFilter);
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
		dForm->HideSomeRow();
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

void CreateRtrnDlg::OpenEmpDlg()
{
	if (prodCountEdit->text().toInt() > 0)
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

void CreateRtrnDlg::OpenStsDlg()
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

void CreateRtrnDlg::OpenRtrnListDlg()
{
	if (employeeEdit->text().toInt() == 0 || employeeEdit->text().toInt() < 0)
	{
		QString message = tr("Enter employee before!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Enter employee before!")),
			QString(tr("Ok")));
		return;
	}
	if (clientEdit->text().toInt() == 0 || clientEdit->text().toInt() < 0)
	{
		QString message = tr("Enter client before!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Enter client before!")),
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
	dForm->returnID = ret->GetID();
	dForm->employeeID = employeeEdit->text().toInt();
	dForm->clientID = clientEdit->text().toInt();
	BusinessLayer::ReturnList returnList;
	returnList.SetReturnID(ret->GetID());
	std::string returnListFilter = returnList.GenerateFilter(dialogBL->GetOrmasDal());
	dForm->FillTable<BusinessLayer::ReturnListView>(errorMessage, returnListFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("returnListForm");
		dForm->QtConnect<BusinessLayer::ReturnListView>();
		QMdiSubWindow *returnListWindow = new QMdiSubWindow;
		returnListWindow->setWidget(dForm);
		returnListWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(returnListWindow);
		returnListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreateRtrnDlg::StatusWasChenged()
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

void CreateRtrnDlg::InitComboBox()
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


	//Auto select a warehouse
	int warehouseID = 0;
	BusinessLayer::WarehouseEmployeeRelation wReleation;
	if (wReleation.GetWarehouseEmployeeByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), dialogBL->loggedUser->GetID(), errorMessage))
	{
		warehouseID = wReleation.GetWarehouseID();
	}

	if (warehouseID > 0)
	{
		BusinessLayer::Warehouse warehouse;
		if (!warehouse.GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseID, errorMessage))
			return;
		warehouseCmb->addItem(warehouse.GetName().c_str(), warehouseID);
	}
	else
	{

		BusinessLayer::Warehouse warehouse;
		BusinessLayer::WarehouseType warehouseType;
		if (!warehouseType.GetWarehouseTypeByCode(dialogBL->globalVar, dialogBL->GetOrmasDal(), "PRODUCT", errorMessage))
			return;
		warehouse.SetWarehouseTypeID(warehouseType.GetID());
		std::string filter = warehouse.GenerateFilter(dialogBL->GetOrmasDal());
		std::vector<BusinessLayer::WarehouseView> werVector = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseView>(errorMessage, filter);
		if (!werVector.empty())
		{
			for (unsigned int i = 0; i < werVector.size(); i++)
			{
				warehouseCmb->addItem(werVector[i].GetName().c_str(), QVariant(werVector[i].GetID()));
			}
		}
	}
}

void CreateRtrnDlg::TextEditChanged()
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

bool CreateRtrnDlg::CheckAccess()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return false;
	BusinessLayer::Status *status = new BusinessLayer::Status;
	if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ret->GetStatusID(), errorMessage))
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
