#include "stdafx.h"

#include "CreatePPlanDlg.h"
#include "DataForm.h"

#include <map>

CreatePPlanDlg::CreatePPlanDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	prodCountEdit->setValidator(vDouble);
	statusEdit->setValidator(vInt);
	sumEdit->setValidator(vDouble);
	sumEdit->setMaxLength(17);
	
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePPlanDlg::EditProductionPlan);
	}
	else
	{
		productionPlan->SetID(dialogBL->GenerateID());
		employeeEdit->setText("0");
		prodCountEdit->setText("0");
		sumEdit->setText("0");
		dateEdit->setDateTime(QDateTime::currentDateTime());

		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("PLANNED");
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

		QObject::connect(okBtn, &QPushButton::released, this, &CreatePPlanDlg::CreateProductionPlan);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePPlanDlg::Close);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreatePPlanDlg::OpenStsDlg);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreatePPlanDlg::OpenEmpDlg);
	QObject::connect(addProdBtn, &QPushButton::released, this, &CreatePPlanDlg::OpenPPlanListDlg);
	QObject::connect(prodCountEdit, &QLineEdit::textChanged, this, &CreatePPlanDlg::TextEditChanged);
	QObject::connect(sumEdit, &QLineEdit::textChanged, this, &CreatePPlanDlg::TextEditChanged);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreatePPlanDlg::~CreatePPlanDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();
	
}

void CreatePPlanDlg::SetProductionPlanParams(QString pDate, int pEmployeeID, double pCount, double pSum, int pStatusID, int pCurrencyID, int id)
{
	productionPlan->SetDate(pDate.toUtf8().constData());
	productionPlan->SetEmployeeID(pEmployeeID);
	productionPlan->SetCount(pCount);
	productionPlan->SetSum(pSum);
	productionPlan->SetStatusID(pStatusID);
	productionPlan->SetCurrencyID(pCurrencyID);
	productionPlan->SetID(id);
}

void CreatePPlanDlg::FillEditElements(QString pDate, int pEmployeeID, double pCount, double pSum, int pStatusID, int pCurrencyID)
{
	dateEdit->setDateTime(QDateTime::fromString(pDate, "dd.MM.yyyy hh:mm"));
	employeeEdit->setText(QString::number(pEmployeeID));
	prodCountEdit->setText(QString::number(pCount, 'f', 3));
	sumEdit->setText(QString::number(pSum, 'f', 3));
	statusEdit->setText(QString::number(pStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(pCurrencyID)));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pEmployeeID, errorMessage))
	{
		empNamePh->setText(user.GetName().c_str());
		empSurnamePh->setText(user.GetSurname().c_str());
		empPhonePh->setText(user.GetPhone().c_str());
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

void CreatePPlanDlg::SetID(int ID, QString childName)
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

bool CreatePPlanDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetProductionPlanParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 10)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 10)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePPlanDlg::CreateProductionPlan()
{
	errorMessage.clear();
	if (!dateEdit->text().isEmpty() && 0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !currencyCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetProductionPlanParams(dateEdit->text(), employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
			sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), productionPlan->GetID());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateProductionPlan(productionPlan, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productionPlan->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productionPlan->GetEmployeeID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productionPlan->GetCurrencyID(), errorMessage))
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

					BusinessLayer::Position *position = new BusinessLayer::Position;
					if (0 != productionPlan->GetEmployeeID())
					{
						if (!position->GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee->GetPositionID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							delete currency;
							delete status;
							delete position;
							return;
						}
					}


					QList<QStandardItem*> productionPlanItem;
					productionPlanItem << new QStandardItem(QString::number(productionPlan->GetID()))
						<< new QStandardItem(productionPlan->GetDate().c_str())
						<< new QStandardItem(QString::number(productionPlan->GetCount(), 'f', 3))
						<< new QStandardItem(QString::number(productionPlan->GetSum(),'f',3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(status->GetName().c_str());

					if (0 != productionPlan->GetEmployeeID())
					{
						productionPlanItem << new QStandardItem(employee->GetName().c_str())
							<< new QStandardItem(employee->GetSurname().c_str())
							<< new QStandardItem(employee->GetPhone().c_str())
							<< new QStandardItem(position->GetName().c_str());
					}
					else
					{
						productionPlanItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}

					productionPlanItem << new QStandardItem(QString::number(productionPlan->GetEmployeeID()))
						<< new QStandardItem(QString::number(productionPlan->GetStatusID()))
						<< new QStandardItem(QString::number(productionPlan->GetCurrencyID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(productionPlanItem);
					delete employee;
					delete currency;
					delete status;
					delete position;
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

void CreatePPlanDlg::EditProductionPlan()
{
	errorMessage.clear();
	if (0 != prodCountEdit->text().toDouble() && 0 != sumEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !currencyCmb->currentText().isEmpty())
	{
		if (QString(productionPlan->GetDate().c_str()) != dateEdit->text() ||
			productionPlan->GetEmployeeID() != employeeEdit->text().toInt() || productionPlan->GetCount() != prodCountEdit->text().toDouble() ||
			productionPlan->GetSum() != sumEdit->text().toDouble()
			|| productionPlan->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetProductionPlanParams(dateEdit->text(), employeeEdit->text().toInt(), prodCountEdit->text().toDouble(),
				sumEdit->text().toDouble(), statusEdit->text().toInt(), currencyCmb->currentData().toInt(), productionPlan->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateProductionPlan(productionPlan, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating ProductionPlan data
						
						itemModel->item(mIndex.row(), 1)->setText(productionPlan->GetDate().c_str());

						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();
						BusinessLayer::Status *status = new BusinessLayer::Status;
						BusinessLayer::Position *position = new BusinessLayer::Position;

						if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productionPlan->GetCurrencyID(), errorMessage)
							|| !status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productionPlan->GetStatusID(), errorMessage)
							|| !employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), productionPlan->GetEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							delete currency;
							delete status;
							delete position;
							return;
						}

						if (0 != productionPlan->GetEmployeeID())
						{
							if (!position->GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee->GetPositionID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								delete employee;
								delete currency;
								delete status;
								delete position;
								return;
							}
						}

						itemModel->item(mIndex.row(), 2)->setText(QString::number(productionPlan->GetCount(), 'f', 3));
						itemModel->item(mIndex.row(), 3)->setText(QString::number(productionPlan->GetSum(),'f',3));
						itemModel->item(mIndex.row(), 4)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(status->GetName().c_str());
						if (productionPlan->GetEmployeeID() > 0)
						{
							itemModel->item(mIndex.row(), 6)->setText(employee->GetName().c_str());
							itemModel->item(mIndex.row(), 7)->setText(employee->GetSurname().c_str());
							itemModel->item(mIndex.row(), 8)->setText(employee->GetPhone().c_str());
							itemModel->item(mIndex.row(), 9)->setText(position->GetName().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 6)->setText("");
							itemModel->item(mIndex.row(), 7)->setText("");
							itemModel->item(mIndex.row(), 8)->setText("");
							itemModel->item(mIndex.row(), 9)->setText("");
						}



						itemModel->item(mIndex.row(), 10)->setText(QString::number(productionPlan->GetEmployeeID()));
						itemModel->item(mIndex.row(), 11)->setText(QString::number(productionPlan->GetStatusID()));
						itemModel->item(mIndex.row(), 12)->setText(QString::number(productionPlan->GetCurrencyID()));

						emit itemModel->dataChanged(mIndex, mIndex);

						delete position;
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

void CreatePPlanDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}


void CreatePPlanDlg::OpenEmpDlg()
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
	role->SetName("PRODUCT MANAGER");
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
		QString message = tr("Sorry could not find employee with \"PRODUCT MANAGER\" role!");
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

void CreatePPlanDlg::OpenStsDlg()
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

void CreatePPlanDlg::OpenPPlanListDlg()
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
	dForm->productionPlanID = productionPlan->GetID();
	BusinessLayer::ProductionPlanList ProductionPlanList;
	ProductionPlanList.SetProductionPlanID(productionPlan->GetID());
	std::string ProductionPlanListFilter = ProductionPlanList.GenerateFilter(dialogBL->GetOrmasDal());
	dForm->FillTable<BusinessLayer::ProductionPlanListView>(errorMessage, ProductionPlanListFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("productionPlanListForm");
		dForm->QtConnect<BusinessLayer::ProductionPlanListView>();
		QMdiSubWindow *productionPlanListWindow = new QMdiSubWindow;
		productionPlanListWindow->setWidget(dForm);
		productionPlanListWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(productionPlanListWindow);
		productionPlanListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreatePPlanDlg::InitComboBox()
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

void CreatePPlanDlg::TextEditChanged()
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
