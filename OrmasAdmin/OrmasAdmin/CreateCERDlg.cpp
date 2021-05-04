#include "stdafx.h"
#include "CreateCERDlg.h"
#include "DataForm.h"



CreateCERDlg::CreateCERDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCERDlg::EditCompanyEmployee);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCERDlg::CreateCompanyEmployee);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateCERDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateCERDlg::OpenEmpDlg);
	InitComboBox();
}

CreateCERDlg::~CreateCERDlg()
{
	delete vInt;
}


void CreateCERDlg::SetID(int ID, QString childName)
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


void CreateCERDlg::SetCompanyEmployeeParams(int ceCompenyID, int ceEmployeeID, int ceBranchID, int id)
{
	companyEmployee->SetCompanyID(ceCompenyID);
	companyEmployee->SetEmployeeID(ceEmployeeID);
	companyEmployee->SetBranchID(ceBranchID);
	companyEmployee->SetID(id);
}

void CreateCERDlg::FillEditElements(int ceCompenyID, int ceEmployeeID, int ceBranchID)
{
	employeeEdit->setText(QString::number(ceEmployeeID));
	companyCmb->setCurrentIndex(companyCmb->findData(QVariant(ceCompenyID)));
	branchCmb->setCurrentIndex(branchCmb->findData(QVariant(ceBranchID)));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ceEmployeeID, errorMessage))
	{
		empNamePh->setText(user.GetName().c_str());
		empSurnamePh->setText(user.GetSurname().c_str());
		empPhonePh->setText(user.GetPhone().c_str());
	}
}

bool CreateCERDlg::FillDlgElements(QTableView* aTable)
{
	QModelIndex mIndex = aTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetCompanyEmployeeParams(aTable->model()->data(aTable->model()->index(mIndex.row(), 6)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 7)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 8)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(aTable->model()->data(aTable->model()->index(mIndex.row(), 6)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 7)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 8)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateCERDlg::CreateCompanyEmployee()
{
	errorMessage.clear();
	if (!companyCmb->currentText().isEmpty() && 0 != employeeEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetCompanyEmployeeParams(companyCmb->currentData().toInt(), employeeEdit->text().toInt(), branchCmb->currentData().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateCompanyEmployeeRelation(companyEmployee, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Company *company = new BusinessLayer::Company();
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Branch *branch = new BusinessLayer::Branch();
					if (!company->GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyEmployee->GetCompanyID(), errorMessage)
						|| !employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyEmployee->GetEmployeeID(), errorMessage)
						|| !branch->GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyEmployee->GetBranchID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete company;
						delete employee;
						delete branch;
						return;
					}
					QList<QStandardItem*> companyEmployeeItem;
					companyEmployeeItem << new QStandardItem(QString::number(companyEmployee->GetID()))
						<< new QStandardItem(company->GetName().c_str())
						<< new QStandardItem(branch->GetName().c_str())
						<< new QStandardItem(employee->GetName().c_str())
						<< new QStandardItem(employee->GetSurname().c_str())
						<< new QStandardItem(employee->GetPhone().c_str())
						<< new QStandardItem(QString::number(companyEmployee->GetCompanyID()))
						<< new QStandardItem(QString::number(companyEmployee->GetEmployeeID()))
						<< new QStandardItem(QString::number(companyEmployee->GetBranchID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(companyEmployeeItem);
					
					delete company;
					delete employee;
					delete branch;
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
			QString(tr("Please fill company, employee fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCERDlg::EditCompanyEmployee()
{
	errorMessage.clear();
	if (!companyCmb->currentText().isEmpty() && 0 != employeeEdit->text().toInt())
	{
		if (companyEmployee->GetCompanyID() != companyCmb->currentData().toInt() || companyEmployee->GetEmployeeID() != employeeEdit->text().toInt()
			|| companyEmployee->GetBranchID() != branchCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetCompanyEmployeeParams(companyCmb->currentData().toInt(), employeeEdit->text().toInt(), branchCmb->currentData().toInt(), companyEmployee->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateCompanyEmployeeRelation(companyEmployee, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Company *company = new BusinessLayer::Company();
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Branch *branch = new BusinessLayer::Branch();
						if (!company->GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyEmployee->GetCompanyID(), errorMessage)
							|| !employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyEmployee->GetEmployeeID(), errorMessage)
							|| !branch->GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyEmployee->GetBranchID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete company;
							delete employee;
							delete branch;
							return;
						}

						
						itemModel->item(mIndex.row(), 1)->setText(company->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(branch->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(employee->GetName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(employee->GetSurname().c_str());
						itemModel->item(mIndex.row(), 5)->setText(employee->GetPhone().c_str());
						itemModel->item(mIndex.row(), 6)->setText(QString::number(companyEmployee->GetCompanyID()));
						itemModel->item(mIndex.row(), 7)->setText(QString::number(companyEmployee->GetEmployeeID()));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(companyEmployee->GetBranchID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete company;
						delete employee;
						delete branch;
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
			QString(tr("Please enter employee and company item!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCERDlg::Close()
{
	this->parentWidget()->close();
}

void CreateCERDlg::OpenEmpDlg()
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


void CreateCERDlg::InitComboBox()
{
	std::vector<BusinessLayer::Company> comVector = dialogBL->GetAllDataForClass<BusinessLayer::Company>(errorMessage);
	if (!comVector.empty())
	{
		for (unsigned int i = 0; i < comVector.size(); i++)
		{
			companyCmb->addItem(comVector[i].GetName().c_str(), QVariant(comVector[i].GetID()));
		}
	}
	std::vector<BusinessLayer::Branch> brVector = dialogBL->GetAllDataForClass<BusinessLayer::Branch>(errorMessage);
	if (!brVector.empty())
	{
		for (unsigned int i = 0; i < brVector.size(); i++)
		{
			branchCmb->addItem(brVector[i].GetName().c_str(), QVariant(brVector[i].GetID()));
		}
	}
}