#include "stdafx.h"

#include "CreateOrdDlg.h"
#include "DataForm.h"

#include <map>

CreateOrdDlg::CreateOrdDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);
	
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateOrdDlg::EditOrder);
	}
	else
	{
		order->SetID(dialogBL->GenerateID());
		execDateWidget->setVisible(false);
		execDateEdit->setDateTime(QDateTime::currentDateTime());
		clientEdit->setText("0");
		employeeEdit->setText("0");
		prodCountEdit->setText("0");
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

		QObject::connect(okBtn, &QPushButton::released, this, &CreateOrdDlg::CreateOrder);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateOrdDlg::Close);
	QObject::connect(clientBtn, &QPushButton::released, this, &CreateOrdDlg::OpenCltDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateOrdDlg::OpenStsDlg);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateOrdDlg::OpenEmpDlg);
	QObject::connect(addProdBtn, &QPushButton::released, this, &CreateOrdDlg::OpenOrdListDlg);
	QObject::connect(statusEdit, &QLineEdit::textChanged, this, &CreateOrdDlg::StatusWasChenged);
	QObject::connect(prodCountEdit, &QLineEdit::textChanged, this, &CreateOrdDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateOrdDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateOrdDlg::~CreateOrdDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();
}

void CreateOrdDlg::SetOrderParams(int oClientID, QString oDate, QString oExecDate, int oEmployeeID, double oCount, double oSum, int oStatusID, int oCurrencyID, int id)
{
	order->SetClientID(oClientID);
	order->SetDate(oDate.toUtf8().constData());
	order->SetExecutionDate(oExecDate.toUtf8().constData());
	order->SetEmployeeID(oEmployeeID);
	order->SetCount(oCount);
	order->SetSum(oSum);
	order->SetStatusID(oStatusID);
	order->SetCurrencyID(oCurrencyID);
	order->SetID(id);
}

void CreateOrdDlg::FillEditElements(int oClientID, QString oDate, QString oExecDate, int oEmployeeID, double oCount, double oSum, int oStatusID, int oCurrencyID)
{
	clientEdit->setText(QString::number(oClientID));
	dateEdit->setDateTime(QDateTime::fromString(oDate, "dd.MM.yyyy hh:mm"));
	if (!oExecDate.isEmpty())
	{
		execDateEdit->setDateTime(QDateTime::fromString(oExecDate, "dd.MM.yyyy hh:mm"));
	}
	employeeEdit->setText(QString::number(oEmployeeID));
	prodCountEdit->setText(QString::number(oCount, 'f', 3));
	sumEdit->setText(QString::number(oSum,'f',3));
	statusEdit->setText(QString::number(oStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(oCurrencyID)));
	BusinessLayer::User user1;
	if (user1.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oClientID, errorMessage))
	{
		clNamePh->setText(user1.GetName().c_str());
		clSurnamePh->setText(user1.GetSurname().c_str());
		clPhonePh->setText(user1.GetPhone().c_str());
	}
	BusinessLayer::User user2;
	if (user2.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oEmployeeID, errorMessage))
	{
		empNamePh->setText(user2.GetName().c_str());
		empSurnamePh->setText(user2.GetSurname().c_str());
		empPhonePh->setText(user2.GetPhone().c_str());
		productIDlist.clear();
		BusinessLayer::EmployeeProductRelation epRelation;
		productIDlist = epRelation.GetAllProductByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oEmployeeID, errorMessage);
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), oStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

void CreateOrdDlg::SetID(int ID, QString childName)
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
				BusinessLayer::User user1;
				if (user1.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					clNamePh->setText(user1.GetName().c_str());
					clSurnamePh->setText(user1.GetSurname().c_str());
					clPhonePh->setText(user1.GetPhone().c_str());
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
				BusinessLayer::User user2;
				if (user2.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					empNamePh->setText(user2.GetName().c_str());
					empSurnamePh->setText(user2.GetSurname().c_str());
					empPhonePh->setText(user2.GetPhone().c_str());
				}
			}
		}
	}
}

bool CreateOrdDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetOrderParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 17)).toInt(),
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

void CreateOrdDlg::CreateOrder()
{
	errorMessage.clear();
	if (0 != clientEdit->text().toInt()
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && 0 != currencyCmb->currentData().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		std::string temp = execDateEdit->text().toStdString();
		if (!execDateWidget->isVisible())
		{
			SetOrderParams(clientEdit->text().toInt(), dateEdit->text(), "", employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), order->GetID());
		}
		else
		{
			SetOrderParams(clientEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), order->GetID());
		}
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateOrder(order, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					QList<QStandardItem*> orderItem;
					orderItem << new QStandardItem(QString::number(order->GetID()))
						<< new QStandardItem(order->GetDate().c_str())
						<< new QStandardItem(order->GetExecutionDate().c_str())
						<< new QStandardItem(status->GetCode().c_str())
						<< new QStandardItem(status->GetName().c_str());

					BusinessLayer::Client *client = new BusinessLayer::Client();
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;

					if (!client->GetClientByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetClientID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete client;
						delete currency;
						delete status;
						return;
					}

					if (order->GetEmployeeID() > 0)
					{
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetEmployeeID(), errorMessage))
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

					if (0 != order->GetClientID())
					{
						orderItem << new QStandardItem(client->GetName().c_str())
							<< new QStandardItem(client->GetSurname().c_str())
							<< new QStandardItem(client->GetPhone().c_str())
							<< new QStandardItem(client->GetAddress().c_str())
							<< new QStandardItem(client->GetFirm().c_str());
					}
					else
					{
						orderItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}
					if (0 != order->GetEmployeeID())
					{
						orderItem << new QStandardItem(employee->GetName().c_str())
							<< new QStandardItem(employee->GetSurname().c_str())
							<< new QStandardItem(employee->GetPhone().c_str());
					}
					else
					{
						orderItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}

					orderItem << new QStandardItem(QString::number(order->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(order->GetSum(),'f',3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(order->GetEmployeeID()))
						<< new QStandardItem(QString::number(order->GetClientID()))
						<< new QStandardItem(QString::number(order->GetStatusID()))
						<< new QStandardItem(QString::number(order->GetCurrencyID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(orderItem);

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

void CreateOrdDlg::EditOrder()
{
	errorMessage.clear();
	if (0 != clientEdit->text().toInt()
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && 0 != currencyCmb->currentData().toInt())
	{
		if (order->GetClientID() != clientEdit->text().toInt() || QString(order->GetDate().c_str()) != dateEdit->text() ||
			QString(order->GetExecutionDate().c_str()) != execDateEdit->text() ||
			order->GetEmployeeID() != employeeEdit->text().toInt() || order->GetCount() != prodCountEdit->text().toDouble() ||
			order->GetSum() != sumEdit->text().toDouble()
			 || order->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			
			if (!execDateWidget->isVisible())
			{
				SetOrderParams(clientEdit->text().toInt(), dateEdit->text(), "", employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), order->GetID());
			}
			else
			{
				SetOrderParams(clientEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), order->GetID());
			}
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateOrder(order, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating order data
						itemModel->item(mIndex.row(), 1)->setText(order->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(order->GetExecutionDate().c_str());


						BusinessLayer::Client *client = new BusinessLayer::Client();
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();
						BusinessLayer::Status *status = new BusinessLayer::Status;

						if (!client->GetClientByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetClientID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetCurrencyID(), errorMessage)
							|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetStatusID(), errorMessage))
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
						if (order->GetEmployeeID() > 0)
						{
							if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetEmployeeID(), errorMessage))
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
						if (order->GetEmployeeID() > 0)
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

						itemModel->item(mIndex.row(), 13)->setText(QString::number(order->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(order->GetSum(), 'f', 3));
						itemModel->item(mIndex.row(), 15)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 16)->setText(QString::number(order->GetEmployeeID()));
						itemModel->item(mIndex.row(), 17)->setText(QString::number(order->GetClientID()));
						itemModel->item(mIndex.row(), 18)->setText(QString::number(order->GetStatusID()));
						itemModel->item(mIndex.row(), 19)->setText(QString::number(order->GetCurrencyID()));

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

void CreateOrdDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateOrdDlg::OpenCltDlg()
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

	dForm->FillTable<BusinessLayer::ClientView>(errorMessage,clientFilter);
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

void CreateOrdDlg::OpenEmpDlg()
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

void CreateOrdDlg::OpenStsDlg()
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

void CreateOrdDlg::OpenOrdListDlg()
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
	dForm->orderID = order->GetID();
	dForm->employeeID = order->GetEmployeeID();
	BusinessLayer::OrderList orderList;
	orderList.SetOrderID(order->GetID());
	std::string orderListFilter = orderList.GenerateFilter(dialogBL->GetOrmasDal());
	dForm->FillTable<BusinessLayer::OrderListView>(errorMessage, orderListFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("orderListForm");
		dForm->QtConnect<BusinessLayer::OrderListView>();
		QMdiSubWindow *orderListWindow = new QMdiSubWindow;
		orderListWindow->setWidget(dForm);
		orderListWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(orderListWindow);
		orderListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreateOrdDlg::StatusWasChenged()
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

void CreateOrdDlg::InitComboBox()
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

void CreateOrdDlg::TextEditChanged()
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

bool CreateOrdDlg::CheckAccess()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return false;
	BusinessLayer::Status *status = new BusinessLayer::Status;
	if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), order->GetStatusID(), errorMessage))
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
