#include "stdafx.h"
#include "CreateWERDlg.h"
#include "DataForm.h"



CreateWERDlg::CreateWERDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWERDlg::EditWarehouseEmployee);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWERDlg::CreateWarehouseEmployee);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateWERDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateWERDlg::OpenEmpDlg);
	InitComboBox();
}

CreateWERDlg::~CreateWERDlg()
{
	delete vInt;
}


void CreateWERDlg::SetID(int ID, QString childName)
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


void CreateWERDlg::SetWarehouseEmployeeParams(int ceWarehouseID, int ceEmployeeID, int id)
{
	warehouseEmployee->SetWarehouseID(ceWarehouseID);
	warehouseEmployee->SetEmployeeID(ceEmployeeID);
	warehouseEmployee->SetID(id);
}

void CreateWERDlg::FillEditElements(int ceWarehouseID, int ceEmployeeID)
{
	employeeEdit->setText(QString::number(ceEmployeeID));
	warehouseCmb->setCurrentIndex(warehouseCmb->findData(QVariant(ceWarehouseID)));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ceEmployeeID, errorMessage))
	{
		empNamePh->setText(user.GetName().c_str());
		empSurnamePh->setText(user.GetSurname().c_str());
		empPhonePh->setText(user.GetPhone().c_str());
	}
}

bool CreateWERDlg::FillDlgElements(QTableView* aTable)
{
	QModelIndex mIndex = aTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetWarehouseEmployeeParams(aTable->model()->data(aTable->model()->index(mIndex.row(), 7)).toInt(),
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

void CreateWERDlg::CreateWarehouseEmployee()
{
	errorMessage.clear();
	if (!warehouseCmb->currentText().isEmpty() && 0 != employeeEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetWarehouseEmployeeParams(warehouseCmb->currentData().toInt(), employeeEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateWarehouseEmployeeRelation(warehouseEmployee, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Warehouse *warehouse = new BusinessLayer::Warehouse();
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					if (!warehouse->GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseEmployee->GetWarehouseID(), errorMessage)
						|| !employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseEmployee->GetEmployeeID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete warehouse;
						delete employee;
						return;
					}
					BusinessLayer::Subaccount *subacc = new BusinessLayer::Subaccount();
					if (!subacc->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouse->GetSubaccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete warehouse;
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
						delete warehouse;
						delete employee;
						delete subacc;
						delete role;
						return;
					}
					QList<QStandardItem*> WarehouseEmployeeItem;
					WarehouseEmployeeItem << new QStandardItem(QString::number(warehouseEmployee->GetID()))
						<< new QStandardItem(employee->GetName().c_str())
						<< new QStandardItem(employee->GetSurname().c_str())
						<< new QStandardItem(employee->GetPhone().c_str())
						<< new QStandardItem(role->GetName().c_str())
						<< new QStandardItem(warehouse->GetName().c_str())
						<< new QStandardItem(subacc->GetNumber().c_str())
						<< new QStandardItem(QString::number(warehouseEmployee->GetWarehouseID()))
						<< new QStandardItem(QString::number(warehouseEmployee->GetEmployeeID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(WarehouseEmployeeItem);

					delete warehouse;
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
			QString(tr("Please fill Warehouse, employee fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateWERDlg::EditWarehouseEmployee()
{
	errorMessage.clear();
	if (!warehouseCmb->currentText().isEmpty() && 0 != employeeEdit->text().toInt())
	{
		if (warehouseEmployee->GetWarehouseID() != warehouseCmb->currentData().toInt() || warehouseEmployee->GetEmployeeID() != employeeEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetWarehouseEmployeeParams(warehouseCmb->currentData().toInt(), employeeEdit->text().toInt(), warehouseEmployee->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateWarehouseEmployeeRelation(warehouseEmployee, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Warehouse *warehouse = new BusinessLayer::Warehouse();
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						if (!warehouse->GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseEmployee->GetWarehouseID(), errorMessage)
							|| !employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseEmployee->GetEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete warehouse;
							delete employee;
							return;
						}
						BusinessLayer::Subaccount *subacc = new BusinessLayer::Subaccount();
						if (!subacc->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouse->GetSubaccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete warehouse;
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
							delete warehouse;
							delete employee;
							delete subacc;
							delete role;
							return;
						}
						
						itemModel->item(mIndex.row(), 1)->setText(employee->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(employee->GetSurname().c_str());
						itemModel->item(mIndex.row(), 3)->setText(employee->GetPhone().c_str());
						itemModel->item(mIndex.row(), 4)->setText(role->GetName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(warehouse->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(subacc->GetNumber().c_str());
						itemModel->item(mIndex.row(), 7)->setText(QString::number(warehouseEmployee->GetWarehouseID()));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(warehouseEmployee->GetEmployeeID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete warehouse;
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
			QString(tr("Please enter role and warehouse-mployee item!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateWERDlg::Close()
{
	this->parentWidget()->close();
}

void CreateWERDlg::OpenEmpDlg()
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
	dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage);
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


void CreateWERDlg::InitComboBox()
{
	std::vector<BusinessLayer::WarehouseView> werVector = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseView>(errorMessage);
	if (!werVector.empty())
	{
		for (unsigned int i = 0; i < werVector.size(); i++)
		{
			warehouseCmb->addItem(werVector[i].GetName().c_str(), QVariant(werVector[i].GetID()));
		}
	}
}