#include "stdafx.h"
#include "CreateWOffRDlg.h"
#include "DataForm.h"
#include <map>

CreateWOffRDlg::CreateWOffRDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	
	//setModal(true);
	dialogBL = ormasBL;
	
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
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
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWOffRDlg::EditWriteOffRaw);
	}
	else
	{
		writeOffRaw->SetID(dialogBL->GenerateID());
		execDateWidget->setVisible(false);
		execDateEdit->setDateTime(QDateTime::currentDateTime());
		employeeEdit->setText("0");
		stockEmployeeEdit->setText("0");
		prodCountEdit->setText("0");
		statusEdit->setText("0");
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

		QObject::connect(okBtn, &QPushButton::released, this, &CreateWOffRDlg::CreateWriteOffRaw);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateWOffRDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateWOffRDlg::OpenEmpDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateWOffRDlg::OpenStsDlg);
	QObject::connect(stockEmployeeBtn, &QPushButton::released, this, &CreateWOffRDlg::OpenSkEmpDlg);
	QObject::connect(addProdBtn, &QPushButton::released, this, &CreateWOffRDlg::OpenWOffRListDlg);
	QObject::connect(prodCountEdit, &QLineEdit::textChanged, this, &CreateWOffRDlg::TextEditChanged);
	QObject::connect(statusEdit, &QLineEdit::textChanged, this, &CreateWOffRDlg::StatusWasChenged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreateWOffRDlg::TextEditChanged);

	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateWOffRDlg::~CreateWOffRDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();
	
}

void CreateWOffRDlg::SetWriteOffRawParams(int wEmployeeID, QString wDate, QString wExecDate, int wStockEmployeeID, double wCount,
	double wSum, int wStatusID, int wCurrencyID, int id)
{
	writeOffRaw->SetEmployeeID(wEmployeeID);
	writeOffRaw->SetDate(wDate.toUtf8().constData());
	QDateTime execDate;
	execDate.fromString(wExecDate, "dd.mm.yyyy");
	if (execDate != QDateTime::fromString("01.01.2000", "dd.mm.yyyy"))
	{
		writeOffRaw->SetExecutionDate(wExecDate.toUtf8().constData());
	}	
	writeOffRaw->SetStockEmployeeID(wStockEmployeeID);
	writeOffRaw->SetCount(wCount);
	writeOffRaw->SetSum(wSum);
	writeOffRaw->SetStatusID(wStatusID);
	writeOffRaw->SetCurrencyID(wCurrencyID);
	writeOffRaw->SetID(id);
}

void CreateWOffRDlg::FillEditElements(int wEmployeeID, QString wDate, QString wExecDate, int wStockEmployeeID, double wCount,
	double wSum, int wStatusID, int wCurrencyID)
{
	employeeEdit->setText(QString::number(wEmployeeID));
	dateEdit->setDateTime(QDateTime::fromString(wDate, "dd.MM.yyyy hh:mm"));
	if (!wExecDate.isEmpty())
	{
		execDateEdit->setDateTime(QDateTime::fromString(wExecDate, "dd.MM.yyyy hh:mm"));
	}
	stockEmployeeEdit->setText(QString::number(wStockEmployeeID));
	prodCountEdit->setText(QString::number(wCount, 'f', 3));
	sumEdit->setText(QString::number(wSum, 'f', 3));
	statusEdit->setText(QString::number(wStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(wCurrencyID)));
	BusinessLayer::User user1;
	if (user1.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wEmployeeID, errorMessage))
	{
		empNamePh->setText(user1.GetName().c_str());
		empSurnamePh->setText(user1.GetSurname().c_str());
		empPhonePh->setText(user1.GetPhone().c_str());
	}
	BusinessLayer::User user2;
	if (user2.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wStockEmployeeID, errorMessage))
	{
		empStockNamePh->setText(user2.GetName().c_str());
		empStockSurnamePh->setText(user2.GetSurname().c_str());
		empStockPhonePh->setText(user2.GetPhone().c_str());
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

void CreateWOffRDlg::SetID(int ID, QString childName)
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
			if (childName == QString("statusForm"))
			{
				statusEdit->setText(QString::number(ID));
				BusinessLayer::Status status;
				if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					statusPh->setText(status.GetName().c_str());
				}
			}
			if (childName == QString("stockEmployeeForm"))
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

bool CreateWOffRDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetWriteOffRawParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 17)).toInt(),
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

void CreateWOffRDlg::CreateWriteOffRaw()
{
	errorMessage.clear();
	if (0 != stockEmployeeEdit->text().toInt() && !dateEdit->text().isEmpty()
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !currencyCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		if (!execDateWidget->isVisible())
		{
			SetWriteOffRawParams(employeeEdit->text().toInt(), dateEdit->text(),"", stockEmployeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), writeOffRaw->GetID());
		}
		else
		{
			SetWriteOffRawParams(employeeEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), stockEmployeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), writeOffRaw->GetID());
		}
		
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateWriteOffRaw(writeOffRaw, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					QList<QStandardItem*> writeOffRawItem;
					writeOffRawItem << new QStandardItem(QString::number(writeOffRaw->GetID()))
						<< new QStandardItem(writeOffRaw->GetDate().c_str())
						<< new QStandardItem(writeOffRaw->GetExecutionDate().c_str())
						<< new QStandardItem(status->GetCode().c_str())
						<< new QStandardItem(status->GetName().c_str());

					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Employee *stockEmployee = new BusinessLayer::Employee();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;

					if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetCurrencyID(), errorMessage))
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

					if (writeOffRaw->GetStockEmployeeID() > 0)
					{
						if (!stockEmployee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetStockEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete stockEmployee;
							return;
						}
					}

					if (0 != writeOffRaw->GetEmployeeID())
					{
						BusinessLayer::Position *ePosition = new BusinessLayer::Position();
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete ePosition;
							return;
						}
						writeOffRawItem << new QStandardItem(employee->GetName().c_str())
							<< new QStandardItem(employee->GetSurname().c_str())
							<< new QStandardItem(employee->GetPhone().c_str())
							<< new QStandardItem(ePosition->GetName().c_str());
					}
					else
					{
						writeOffRawItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}
					if (0 != writeOffRaw->GetStockEmployeeID())
					{
						BusinessLayer::Position *sePosition = new BusinessLayer::Position();
						if (!stockEmployee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetStockEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete sePosition;
							return;
						}
						writeOffRawItem << new QStandardItem(stockEmployee->GetName().c_str())
							<< new QStandardItem(stockEmployee->GetSurname().c_str())
							<< new QStandardItem(stockEmployee->GetPhone().c_str())
							<< new QStandardItem(sePosition->GetName().c_str());
					}
					else
					{
						writeOffRawItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}

					writeOffRawItem << new QStandardItem(QString::number(writeOffRaw->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(writeOffRaw->GetSum(),'f',3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(writeOffRaw->GetStockEmployeeID()))
						<< new QStandardItem(QString::number(writeOffRaw->GetEmployeeID()))
						<< new QStandardItem(QString::number(writeOffRaw->GetStatusID()))
						<< new QStandardItem(QString::number(writeOffRaw->GetCurrencyID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(writeOffRawItem);
					delete stockEmployee;
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

void CreateWOffRDlg::EditWriteOffRaw()
{
	errorMessage.clear();
	if (0 != stockEmployeeEdit->text().toInt() && !dateEdit->text().isEmpty()
		&& 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !currencyCmb->currentText().isEmpty())
	{
		if (writeOffRaw->GetStockEmployeeID() != stockEmployeeEdit->text().toInt() || QString(writeOffRaw->GetDate().c_str()) != dateEdit->text() ||
			writeOffRaw->GetEmployeeID() != employeeEdit->text().toInt() || writeOffRaw->GetCount() != prodCountEdit->text().toDouble() ||
			writeOffRaw->GetSum() != sumEdit->text().toDouble() || writeOffRaw->GetStatusID() != statusEdit->text().toInt()
			|| writeOffRaw->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			if (!execDateWidget->isVisible())
			{
				SetWriteOffRawParams(employeeEdit->text().toInt(), dateEdit->text(), "", stockEmployeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), writeOffRaw->GetID());
			}
			else
			{
				SetWriteOffRawParams(employeeEdit->text().toInt(), dateEdit->text(), execDateEdit->text(), stockEmployeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
					sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), writeOffRaw->GetID());
			}
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateWriteOffRaw(writeOffRaw, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating WriteOffRaw data

						itemModel->item(mIndex.row(), 1)->setText(writeOffRaw->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(writeOffRaw->GetExecutionDate().c_str());

						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Employee *stockEmployee = new BusinessLayer::Employee();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();
						BusinessLayer::Status *status = new BusinessLayer::Status;

						if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetCurrencyID(), errorMessage)
							|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete stockEmployee;
							delete currency;
							delete employee;
							delete status;
							return;
						}
						if (writeOffRaw->GetStockEmployeeID() > 0)
						{
							if (!stockEmployee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetStockEmployeeID(), errorMessage))
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
						if (writeOffRaw->GetEmployeeID() > 0)
						{
							BusinessLayer::Position *ePosition = new BusinessLayer::Position();
							if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetEmployeeID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								delete ePosition;
								return;
							}
							itemModel->item(mIndex.row(), 5)->setText(employee->GetName().c_str());
							itemModel->item(mIndex.row(), 6)->setText(employee->GetSurname().c_str());
							itemModel->item(mIndex.row(), 7)->setText(employee->GetPhone().c_str());
							itemModel->item(mIndex.row(), 8)->setText(ePosition->GetName().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 5)->setText("");
							itemModel->item(mIndex.row(), 6)->setText("");
							itemModel->item(mIndex.row(), 7)->setText("");
							itemModel->item(mIndex.row(), 8)->setText("");
						}
						if (writeOffRaw->GetStockEmployeeID() > 0)
						{
							BusinessLayer::Position *sePosition = new BusinessLayer::Position();
							if (!stockEmployee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetStockEmployeeID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								delete sePosition;
								return;
							}
							itemModel->item(mIndex.row(), 9)->setText(stockEmployee->GetName().c_str());
							itemModel->item(mIndex.row(), 10)->setText(stockEmployee->GetSurname().c_str());
							itemModel->item(mIndex.row(), 11)->setText(stockEmployee->GetPhone().c_str());
							itemModel->item(mIndex.row(), 12)->setText(sePosition->GetName().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 9)->setText("");
							itemModel->item(mIndex.row(), 10)->setText("");
							itemModel->item(mIndex.row(), 11)->setText("");
							itemModel->item(mIndex.row(), 12)->setText("");
						}

						itemModel->item(mIndex.row(), 13)->setText(QString::number(writeOffRaw->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(writeOffRaw->GetSum(),'f',3));
						itemModel->item(mIndex.row(), 15)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 16)->setText(QString::number(writeOffRaw->GetStockEmployeeID()));
						itemModel->item(mIndex.row(), 17)->setText(QString::number(writeOffRaw->GetEmployeeID()));
						itemModel->item(mIndex.row(), 18)->setText(QString::number(writeOffRaw->GetStatusID()));
						itemModel->item(mIndex.row(), 19)->setText(QString::number(writeOffRaw->GetCurrencyID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete employee;
						delete stockEmployee;
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

void CreateWOffRDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateWOffRDlg::OpenEmpDlg()
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

void CreateWOffRDlg::OpenSkEmpDlg()
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
		dForm->setObjectName("stockEmployeeForm");
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

void CreateWOffRDlg::OpenStsDlg()
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

void CreateWOffRDlg::OpenWOffRListDlg()
{
	if (stockEmployeeEdit->text().toInt() == 0 || stockEmployeeEdit->text().toInt() < 0)
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
	dForm->writeOffRawID = writeOffRaw->GetID();
	BusinessLayer::WriteOffRawList writeOffRawList;
	writeOffRawList.SetWriteOffRawID(writeOffRaw->GetID());
	std::string writeOffRawListFilter = writeOffRawList.GenerateFilter(dialogBL->GetOrmasDal());
	dForm->FillTable<BusinessLayer::WriteOffRawListView>(errorMessage, writeOffRawListFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("writeOffRawListForm");
		dForm->QtConnect<BusinessLayer::WriteOffRawListView>();
		QMdiSubWindow *writeOffRawWindow = new QMdiSubWindow;
		writeOffRawWindow->setWidget(dForm);
		writeOffRawWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(writeOffRawWindow);
		writeOffRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreateWOffRDlg::InitComboBox()
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

void CreateWOffRDlg::TextEditChanged()
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

void CreateWOffRDlg::StatusWasChenged()
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

bool CreateWOffRDlg::CheckAccess()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return false;
	BusinessLayer::Status *status = new BusinessLayer::Status;
	if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), writeOffRaw->GetStatusID(), errorMessage))
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
