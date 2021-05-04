#include "stdafx.h"
#include "CreateWOffDlg.h"
#include "DataForm.h"

CreateWOffDlg::CreateWOffDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	sumEdit->setVisible(false);
	sumLb->setVisible(false);


	//hide employee, because it's not needed
	clNamePh->setVisible(false);
	clSurnamePh->setVisible(false);
	clPhonePh->setVisible(false);
	clNameLb->setVisible(false);
	clSurnameLb->setVisible(false);
	clPhoneLb->setVisible(false);
	clientBtn->setVisible(false);
	clientEdit->setVisible(false);
	//
	
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWOffDlg::EditWriteOff);
	}
	else
	{
		writeOff->SetID(dialogBL->GenerateID());
		execDateWidget->setVisible(false);
		execDateEdit->setDateTime(QDateTime::currentDateTime());
		clientEdit->setText("0");
		employeeEdit->setText("0");
		prodCountEdit->setText("0");
		clientEdit->setText("0");
		sumEdit->setText("0");
		dateEdit->setDateTime(QDateTime::currentDateTime());

		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("WRITE-OFFED");
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

		QObject::connect(okBtn, &QPushButton::released, this, &CreateWOffDlg::CreateWriteOff);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateWOffDlg::Close);
	QObject::connect(clientBtn, &QPushButton::released, this, &CreateWOffDlg::OpenCltDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateWOffDlg::OpenStsDlg);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateWOffDlg::OpenEmpDlg);
	QObject::connect(addProdBtn, &QPushButton::released, this, &CreateWOffDlg::OpenWOffListDlg);
	QObject::connect(prodCountEdit, &QLineEdit::textChanged, this, &CreateWOffDlg::TextEditChanged);
	QObject::connect(statusEdit, &QLineEdit::textChanged, this, &CreateWOffDlg::StatusWasChenged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateWOffDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateWOffDlg::~CreateWOffDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();
	
}

void CreateWOffDlg::SetWriteOffParams(int wClientID, QString wDate, QString wExecDate,  int wEmployeeID, double wCount, double wSum, int wStatusID, int wCurrencyID, int id)
{
	writeOff->SetClientID(wClientID);
	writeOff->SetDate(wDate.toUtf8().constData());
	QDateTime execDate;
	execDate.fromString(wExecDate, "dd.mm.yyyy");
	if (execDate != QDateTime::fromString("01.01.2000", "dd.mm.yyyy"))
	{
		writeOff->SetExecutionDate(wExecDate.toUtf8().constData());
	}
	writeOff->SetEmployeeID(wEmployeeID);
	writeOff->SetCount(wCount);
	writeOff->SetSum(wSum);
	writeOff->SetStatusID(wStatusID);
	writeOff->SetCurrencyID(wCurrencyID);
	writeOff->SetID(id);
}

void CreateWOffDlg::FillEditElements(int wClientID, QString wDate, QString wExecDate, int wEmployeeID, double wCount, double wSum, int wStatusID, int wCurrencyID)
{
	clientEdit->setText(QString::number(wClientID));
	dateEdit->setDateTime(QDateTime::fromString(wDate, "dd.MM.yyyy hh:mm"));
	if (!wExecDate.isEmpty())
	{
		execDateEdit->setDateTime(QDateTime::fromString(wExecDate, "dd.MM.yyyy hh:mm"));
	}
	employeeEdit->setText(QString::number(wEmployeeID));
	prodCountEdit->setText(QString::number(wCount, 'f', 3));
	sumEdit->setText(QString::number(wSum, 'f', 3));
	statusEdit->setText(QString::number(wStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(wCurrencyID)));
	BusinessLayer::User employee;
	if (employee.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wEmployeeID, errorMessage))
	{
		empNamePh->setText(employee.GetName().c_str());
		empSurnamePh->setText(employee.GetSurname().c_str());
		empPhonePh->setText(employee.GetPhone().c_str());
	}
	BusinessLayer::User client;
	if (client.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wClientID, errorMessage))
	{
		clNamePh->setText(client.GetName().c_str());
		clSurnamePh->setText(client.GetSurname().c_str());
		clPhonePh->setText(client.GetPhone().c_str());
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

void CreateWOffDlg::SetID(int ID, QString childName)
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
				BusinessLayer::User client;
				if (client.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					clNamePh->setText(client.GetName().c_str());
					clSurnamePh->setText(client.GetSurname().c_str());
					clPhonePh->setText(client.GetPhone().c_str());
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
				BusinessLayer::User employee;
				if (employee.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					empNamePh->setText(employee.GetName().c_str());
					empSurnamePh->setText(employee.GetSurname().c_str());
					empPhonePh->setText(employee.GetPhone().c_str());
				}
			}
		}
	}
}

bool CreateWOffDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetWriteOffParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 17)).toInt(),
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

void CreateWOffDlg::CreateWriteOff()
{
	errorMessage.clear();
	if (!dateEdit->text().isEmpty()
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !currencyCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		if (!execDateWidget->isVisible())
		{
			SetWriteOffParams(clientEdit->text().toInt(), dateEdit->text(), "", employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), writeOff->GetID());
		}
		else
		{
			SetWriteOffParams(clientEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), writeOff->GetID());
		}

		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateWriteOff(writeOff, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> writeOffItem;
					writeOffItem << new QStandardItem(QString::number(writeOff->GetID()))
						<< new QStandardItem(writeOff->GetDate().c_str())
						<< new QStandardItem(writeOff->GetExecutionDate().c_str());

					BusinessLayer::Client *client = new BusinessLayer::Client();
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOff->GetCurrencyID(), errorMessage)
						|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOff->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete currency;
						delete status;
						return;
					}

					writeOffItem << new QStandardItem(status->GetCode().c_str())
						<< new QStandardItem(status->GetName().c_str());


					if (writeOff->GetEmployeeID() > 0)
					{
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOff->GetEmployeeID(), errorMessage))
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


					if (0 != writeOff->GetClientID())
					{
						writeOffItem << new QStandardItem(client->GetName().c_str())
							<< new QStandardItem(client->GetSurname().c_str())
							<< new QStandardItem(client->GetPhone().c_str())
							<< new QStandardItem(client->GetAddress().c_str())
							<< new QStandardItem(client->GetFirm().c_str());
					}
					else
					{
						writeOffItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}
					if (0 != writeOff->GetEmployeeID())
					{
						writeOffItem << new QStandardItem(employee->GetName().c_str())
							<< new QStandardItem(employee->GetSurname().c_str())
							<< new QStandardItem(employee->GetPhone().c_str());
					}
					else
					{
						writeOffItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}

					writeOffItem << new QStandardItem(QString::number(writeOff->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(writeOff->GetSum(),'f',3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(writeOff->GetEmployeeID()))
						<< new QStandardItem(QString::number(writeOff->GetClientID()))
						<< new QStandardItem(QString::number(writeOff->GetStatusID()))
						<< new QStandardItem(QString::number(writeOff->GetCurrencyID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(writeOffItem);
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

void CreateWOffDlg::EditWriteOff()
{
	errorMessage.clear();
	if (0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !currencyCmb->currentText().isEmpty())
	{
		if (QString(writeOff->GetDate().c_str()) != dateEdit->text() ||
			writeOff->GetEmployeeID() != employeeEdit->text().toInt() || writeOff->GetCount() != prodCountEdit->text().toDouble() ||
			writeOff->GetSum() != sumEdit->text().toDouble() || writeOff->GetCurrencyID() != currencyCmb->currentData().toInt()
			|| writeOff->GetStatusID() != statusEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			if (!execDateWidget->isVisible())
			{
				SetWriteOffParams(clientEdit->text().toInt(), dateEdit->text(), "", employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), writeOff->GetID());
			}
			else
			{
				SetWriteOffParams(clientEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), writeOff->GetID());
			}
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateWriteOff(writeOff, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating WriteOff data
					
						itemModel->item(mIndex.row(), 1)->setText(writeOff->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(writeOff->GetDate().c_str());

						BusinessLayer::Status *status = new BusinessLayer::Status();
						status->SetID(statusEdit->text().toInt());
						std::string statusFilter = dialogBL->GenerateFilter<BusinessLayer::Status>(status);
						std::vector<BusinessLayer::Status> statusVector = dialogBL->GetAllDataForClass<BusinessLayer::Status>(errorMessage, statusFilter);
						if (statusVector.size() > 0)
						{
							itemModel->item(mIndex.row(), 3)->setText(statusVector.at(0).GetCode().c_str());
							itemModel->item(mIndex.row(), 4)->setText(statusVector.at(0).GetName().c_str());
						}
						else
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr("This status does not valid, cannot create WriteOff!")),
								QString(tr("Ok")));
							return;
						}

						BusinessLayer::Client *client = new BusinessLayer::Client();
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();

						BusinessLayer::Currency *currency = new BusinessLayer::Currency();

						if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOff->GetCurrencyID(), errorMessage))
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

						if (writeOff->GetEmployeeID() > 0)
						{
							if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOff->GetEmployeeID(), errorMessage))
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

						if (0 != writeOff->GetClientID())
						{
							itemModel->item(mIndex.row(), 5)->setText(client->GetName().c_str());
							itemModel->item(mIndex.row(), 6)->setText(client->GetSurname().c_str());
							itemModel->item(mIndex.row(), 7)->setText(client->GetPhone().c_str());
							itemModel->item(mIndex.row(), 8)->setText(client->GetAddress().c_str());
							itemModel->item(mIndex.row(), 9)->setText(client->GetFirm().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 5)->setText("");
							itemModel->item(mIndex.row(), 6)->setText("");
							itemModel->item(mIndex.row(), 7)->setText("");
							itemModel->item(mIndex.row(), 8)->setText("");
							itemModel->item(mIndex.row(), 9)->setText("");
						}
						if (writeOff->GetEmployeeID() > 0)
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

						itemModel->item(mIndex.row(), 13)->setText(QString::number(writeOff->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(writeOff->GetSum(),'f',3));
						itemModel->item(mIndex.row(), 15)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 16)->setText(QString::number(writeOff->GetEmployeeID()));
						itemModel->item(mIndex.row(), 17)->setText(QString::number(writeOff->GetClientID()));
						itemModel->item(mIndex.row(), 18)->setText(QString::number(writeOff->GetStatusID()));
						itemModel->item(mIndex.row(), 19)->setText(QString::number(writeOff->GetCurrencyID()));

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

void CreateWOffDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateWOffDlg::OpenCltDlg()
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

void CreateWOffDlg::OpenEmpDlg()
{
	if (prodCountEdit->text().toInt() > 0)
	{
		QString message = tr("Cannot change employee!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Cannot change production employee after adding product!")),
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
		QString message = tr("Sorry could not find employee with \"Stock manager\" role!");
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

void CreateWOffDlg::OpenStsDlg()
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

void CreateWOffDlg::OpenWOffListDlg()
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
	dForm->writeOffID = writeOff->GetID();
	BusinessLayer::WriteOffList writeOffList;
	writeOffList.SetWriteOffID(writeOff->GetID());
	std::string writeOffListFilter = writeOffList.GenerateFilter(dialogBL->GetOrmasDal());
	dForm->FillTable<BusinessLayer::WriteOffListView>(errorMessage, writeOffListFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("writeOffListForm");
		dForm->QtConnect<BusinessLayer::WriteOffListView>();
		QMdiSubWindow *writeOffListWindow = new QMdiSubWindow;
		writeOffListWindow->setWidget(dForm);
		writeOffListWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(writeOffListWindow);
		writeOffListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreateWOffDlg::InitComboBox()
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

void CreateWOffDlg::TextEditChanged()
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

void CreateWOffDlg::StatusWasChenged()
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

bool CreateWOffDlg::CheckAccess()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return false;
	BusinessLayer::Status *status = new BusinessLayer::Status;
	if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOff->GetStatusID(), errorMessage))
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
