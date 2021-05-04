#include "stdafx.h"
#include "CreateAcsDlg.h"
#include "DataForm.h"



CreateAcsDlg::CreateAcsDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	roleEdit->setValidator(vInt);
	acsItemEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAcsDlg::EditAccess);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAcsDlg::CreateAccess);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAcsDlg::Close);
	QObject::connect(roleBtn, &QPushButton::released, this, &CreateAcsDlg::OpenRoleDlg);
	QObject::connect(acsItemBtn, &QPushButton::released, this, &CreateAcsDlg::OpenAcsItemDlg);
}

CreateAcsDlg::~CreateAcsDlg()
{
	delete vInt;
}


void CreateAcsDlg::SetID(int ID, QString childName)
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

			if (childName == QString("roleForm"))
			{
				roleEdit->setText(QString::number(ID));
			}
			if (childName == QString("accessItemForm"))
			{
				acsItemEdit->setText(QString::number(ID));
			}
		}
	}
}


void CreateAcsDlg::SetAccessParams(int aRoleID, int aAccessTypeID, int id)
{
	access->SetRoleID(aRoleID);
	access->SetAccessItemID(aAccessTypeID);
	access->SetID(id);
}

void CreateAcsDlg::FillEditElements(int aRoleID, int aAccessTypeID)
{
	roleEdit->setText(QString::number(aRoleID));
	acsItemEdit->setText(QString::number(aAccessTypeID));
}

bool CreateAcsDlg::FillDlgElements(QTableView* aTable)
{
	QModelIndex mIndex = aTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetAccessParams(aTable->model()->data(aTable->model()->index(mIndex.row(), 5)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 6)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(aTable->model()->data(aTable->model()->index(mIndex.row(), 5)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 6)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateAcsDlg::CreateAccess()
{
	errorMessage.clear();
	if (!roleEdit->text().isEmpty() && !acsItemEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetAccessParams(roleEdit->text().toInt(), acsItemEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateAccess(access, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Role *role = new BusinessLayer::Role();
					BusinessLayer::AccessItem *acItem = new BusinessLayer::AccessItem();
					if (!role->GetRoleByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), access->GetRoleID(), errorMessage)
						|| !acItem->GetAccessItemByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), access->GetAccessItemID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete role;
						delete acItem;
						return;
					}

					QList<QStandardItem*> accessItem;
					accessItem << new QStandardItem(QString::number(access->GetID()))
						<< new QStandardItem(role->GetName().c_str())
						<< new QStandardItem(acItem->GetNameEng().c_str())
						<< new QStandardItem(acItem->GetNameRu().c_str())
						<< new QStandardItem(acItem->GetDivision().c_str())
						<< new QStandardItem(QString::number(access->GetRoleID()))
						<< new QStandardItem(QString::number(access->GetAccessItemID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(accessItem);
					delete role;
					delete acItem;

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
			QString(tr("Please fill role, access item!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAcsDlg::EditAccess()
{
	errorMessage.clear();
	if (!roleEdit->text().isEmpty() && !acsItemEdit->text().isEmpty())
	{
		if (access->GetRoleID() != roleEdit->text().toInt() || access->GetAccessItemID() != acsItemEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetAccessParams(roleEdit->text().toInt(), acsItemEdit->text().toInt(), access->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateAccess(access, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Role *role = new BusinessLayer::Role();
						BusinessLayer::AccessItem *acItem = new BusinessLayer::AccessItem();
						if (!role->GetRoleByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), access->GetRoleID(), errorMessage)
							|| !acItem->GetAccessItemByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), access->GetAccessItemID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete role;
							delete acItem;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(role->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(acItem->GetNameEng().c_str());
						itemModel->item(mIndex.row(), 3)->setText(acItem->GetNameRu().c_str());
						itemModel->item(mIndex.row(), 4)->setText(acItem->GetDivision().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(access->GetRoleID()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(access->GetAccessItemID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete role;
						delete acItem;
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
			QString(tr("Please enter role and access item!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAcsDlg::Close()
{
	this->parentWidget()->close();
}

void CreateAcsDlg::OpenRoleDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Roles"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Role>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("roleForm");
		dForm->QtConnect<BusinessLayer::Role>();
		QMdiSubWindow *roleWindow = new QMdiSubWindow;
		roleWindow->setWidget(dForm);
		roleWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(roleWindow);
		roleWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All roles are shown");
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


void CreateAcsDlg::OpenAcsItemDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Access Item"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::AccessItem>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accessItemForm");
		dForm->QtConnect<BusinessLayer::AccessItem>();
		QMdiSubWindow *acsItemWindow = new QMdiSubWindow;
		acsItemWindow->setWidget(dForm);
		acsItemWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(acsItemWindow);
		acsItemWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All access items are shown");
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
