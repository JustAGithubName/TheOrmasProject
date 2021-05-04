#include "stdafx.h"
#include "CreateCASHERDlg.h"
#include "DataForm.h"



CreateCASHERDlg::CreateCASHERDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	employeeEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCASHERDlg::EditCashboxEmployee);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCASHERDlg::CreateCashboxEmployee);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateCASHERDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateCASHERDlg::OpenEmpDlg);
	InitComboBox();
}

CreateCASHERDlg::~CreateCASHERDlg()
{
	delete vInt;
}


void CreateCASHERDlg::SetID(int ID, QString childName)
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
			}
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


void CreateCASHERDlg::SetCashboxEmployeeParams(int ceCashboxID, int ceEmployeeID, int id)
{
	cashboxEmployee->SetCashboxID(ceCashboxID);
	cashboxEmployee->SetEmployeeID(ceEmployeeID);
	cashboxEmployee->SetID(id);
}

void CreateCASHERDlg::FillEditElements(int ceCashboxID, int ceEmployeeID)
{
	employeeEdit->setText(QString::number(ceEmployeeID));
	cashboxCmb->setCurrentIndex(cashboxCmb->findData(QVariant(ceCashboxID)));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ceEmployeeID, errorMessage))
	{
		empNamePh->setText(user.GetName().c_str());
		empSurnamePh->setText(user.GetSurname().c_str());
		empPhonePh->setText(user.GetPhone().c_str());
	}
}

bool CreateCASHERDlg::FillDlgElements(QTableView* aTable)
{
	QModelIndex mIndex = aTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetCashboxEmployeeParams(aTable->model()->data(aTable->model()->index(mIndex.row(), 7)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 8)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(aTable->model()->data(aTable->model()->index(mIndex.row(), 7)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 8)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateCASHERDlg::CreateCashboxEmployee()
{
	errorMessage.clear();
	if (!cashboxCmb->currentText().isEmpty() && 0 != employeeEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetCashboxEmployeeParams(cashboxCmb->currentData().toInt(), employeeEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateCashboxEmployeeRelation(cashboxEmployee, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Cashbox *cashbox = new BusinessLayer::Cashbox();
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					if (!cashbox->GetCashboxByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashboxEmployee->GetCashboxID(), errorMessage)
						|| !employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashboxEmployee->GetEmployeeID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete cashbox;
						delete employee;
						return;
					}
					BusinessLayer::Subaccount *subacc = new BusinessLayer::Subaccount();
					if (!subacc->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashbox->GetSubaccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete cashbox;
						delete employee;
						delete subacc;
						return;
					}
					BusinessLayer::Role *role = new BusinessLayer::Role();
					if (!role->GetRoleByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee->GetRoleID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete cashbox;
						delete employee;
						delete subacc;
						delete role;
						return;
					}
					QList<QStandardItem*> CashboxEmployeeItem;
					CashboxEmployeeItem << new QStandardItem(QString::number(cashboxEmployee->GetID()))
						<< new QStandardItem(subacc->GetNumber().c_str())
						<< new QStandardItem(cashbox->GetAddress().c_str())
						<< new QStandardItem(employee->GetName().c_str())
						<< new QStandardItem(employee->GetSurname().c_str())
						<< new QStandardItem(employee->GetPhone().c_str())
						<< new QStandardItem(role->GetName().c_str())
						<< new QStandardItem(QString::number(cashboxEmployee->GetCashboxID()))
						<< new QStandardItem(QString::number(cashboxEmployee->GetEmployeeID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(CashboxEmployeeItem);

					delete cashbox;
					delete employee;
					delete subacc;
					delete role;
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
			QString(tr("Please fill cashbox, employee fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCASHERDlg::EditCashboxEmployee()
{
	errorMessage.clear();
	if (!cashboxCmb->currentText().isEmpty() && 0 != employeeEdit->text().toInt())
	{
		if (cashboxEmployee->GetCashboxID() != cashboxCmb->currentData().toInt() || cashboxEmployee->GetEmployeeID() != employeeEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetCashboxEmployeeParams(cashboxCmb->currentData().toInt(), employeeEdit->text().toInt(), cashboxEmployee->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateCashboxEmployeeRelation(cashboxEmployee, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Cashbox *cashbox = new BusinessLayer::Cashbox();
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						if (!cashbox->GetCashboxByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashboxEmployee->GetCashboxID(), errorMessage)
							|| !employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashboxEmployee->GetEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete cashbox;
							delete employee;
							return;
						}
						BusinessLayer::Subaccount *subacc = new BusinessLayer::Subaccount();
						if (!subacc->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashbox->GetSubaccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete cashbox;
							delete employee;
							delete subacc;
							return;
						}
						BusinessLayer::Role *role = new BusinessLayer::Role();
						if (!role->GetRoleByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee->GetRoleID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete cashbox;
							delete employee;
							delete subacc;
							delete role;
							return;
						}
						
						itemModel->item(mIndex.row(), 1)->setText(subacc->GetNumber().c_str());
						itemModel->item(mIndex.row(), 1)->setText(cashbox->GetAddress().c_str());
						itemModel->item(mIndex.row(), 2)->setText(employee->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(employee->GetSurname().c_str());
						itemModel->item(mIndex.row(), 4)->setText(employee->GetPhone().c_str());
						itemModel->item(mIndex.row(), 4)->setText(role->GetName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(cashboxEmployee->GetCashboxID()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(cashboxEmployee->GetEmployeeID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete cashbox;
						delete employee;
						delete subacc;
						delete role;
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
			QString(tr("Please enter role and CashboxEmployee item!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCASHERDlg::Close()
{
	this->parentWidget()->close();
}

void CreateCASHERDlg::OpenEmpDlg()
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
	role->SetName("CASHIER");
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
		QString message = tr("Sorry could not find employee with \"CASHIER\" role!");
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


void CreateCASHERDlg::InitComboBox()
{
	std::vector<BusinessLayer::CashboxView> cashVector = dialogBL->GetAllDataForClass<BusinessLayer::CashboxView>(errorMessage);
	if (!cashVector.empty())
	{
		for (unsigned int i = 0; i < cashVector.size(); i++)
		{
			cashboxCmb->addItem(cashVector[i].GetAddress().c_str(), QVariant(cashVector[i].GetID()));
		}
	}
}