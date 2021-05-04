#include "stdafx.h"
#include "CreateBrwDlg.h"
#include "DataForm.h"


CreateBrwDlg::CreateBrwDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateBrwDlg::EditBorrower);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateBrwDlg::CreateBorrower);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateBrwDlg::Close);
	QObject::connect(userBtn, &QPushButton::released, this, &CreateBrwDlg::OpenEmpDlg);
}

CreateBrwDlg::~CreateBrwDlg()
{

}

void CreateBrwDlg::SetID(int ID, QString childName)
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
				userEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					namePh->setText(user.GetName().c_str());
					surnamePh->setText(user.GetSurname().c_str());
					phonePh->setText(user.GetPhone().c_str());
				}
			}
		}
	}
}

void CreateBrwDlg::SetBorrowerParams(QString aComment, int aUserID)
{
	borrower->SetUserID(aUserID);
	borrower->SetComment(aComment.toUtf8().constData());
}

void CreateBrwDlg::FillEditElements(QString aInformation, int aUserID)
{
	userEdit->setText(QString::number(aUserID));
	commnetEdit->setText(aInformation);
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), aUserID, errorMessage))
	{
		namePh->setText(user.GetName().c_str());
		surnamePh->setText(user.GetSurname().c_str());
		phonePh->setText(user.GetPhone().c_str());
	}
}

bool CreateBrwDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetBorrowerParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toDouble());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toDouble());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateBrwDlg::CreateBorrower()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetBorrowerParams(commnetEdit->text(), userEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateBorrower(borrower, errorMessage))
		{
			BusinessLayer::Employee employee;
			if (!employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), borrower->GetUserID(), errorMessage))
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
			BusinessLayer::Role role;
			if (!employee.IsEmpty())
			{
				if (!role.GetRoleByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee.GetRoleID(), errorMessage))
				{
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
			}
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{

					QList<QStandardItem*> BorrowerItem;
					BorrowerItem << new QStandardItem(QString::number(borrower->GetID()))
						<< new QStandardItem(employee.GetName().c_str())
						<< new QStandardItem(employee.GetSurname().c_str())
						<< new QStandardItem(borrower->GetComment().c_str())
						<< new QStandardItem(employee.GetPhone().c_str())
						<< new QStandardItem(employee.GetAddress().c_str())
						<< new QStandardItem(role.GetName().c_str())
						<< new QStandardItem(employee.GetPassword().c_str())
						<< new QStandardItem(employee.GetEmail().c_str())
						<< new QStandardItem(employee.GetActivated() ? "true" : "false")
						<< new QStandardItem(role.GetID());

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(BorrowerItem);
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
			QString(tr("Please fill all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateBrwDlg::EditBorrower()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt())
	{
		if (QString(borrower->GetComment().c_str()) != commnetEdit->text() || borrower->GetUserID() != userEdit->text().toDouble())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetBorrowerParams(commnetEdit->text(), userEdit->text().toInt());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateBorrower(borrower, errorMessage))
			{
				BusinessLayer::Employee employee;
				if (!employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), borrower->GetUserID(), errorMessage))
				{
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				BusinessLayer::Role role;
				if (!employee.IsEmpty())
				{
					if (!role.GetRoleByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employee.GetRoleID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
				}
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(employee.GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(employee.GetSurname().c_str());
						itemModel->item(mIndex.row(), 3)->setText(borrower->GetComment().c_str());
						itemModel->item(mIndex.row(), 4)->setText(employee.GetPhone().c_str());
						itemModel->item(mIndex.row(), 5)->setText(employee.GetAddress().c_str());
						itemModel->item(mIndex.row(), 6)->setText(role.GetName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(employee.GetPassword().c_str());
						itemModel->item(mIndex.row(), 8)->setText(employee.GetEmail().c_str());
						itemModel->item(mIndex.row(), 9)->setText(employee.GetActivated() ? "true" : "false");
						itemModel->item(mIndex.row(), 10)->setText(role.GetName().c_str());
						emit itemModel->dataChanged(mIndex, mIndex);
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
			QString(tr("Please fill all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateBrwDlg::Close()
{
	this->parentWidget()->close();
}

void CreateBrwDlg::OpenEmpDlg()
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

