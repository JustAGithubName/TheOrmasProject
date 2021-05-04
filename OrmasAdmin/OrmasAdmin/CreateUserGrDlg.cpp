#include "stdafx.h"

#include "CreateUserGrDlg.h"
#include "DataForm.h"

#include <map>

CreateUserGrDlg::CreateUserGrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateUserGrDlg::EditUserGroup);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateUserGrDlg::CreateUserGroup);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateUserGrDlg::Close);
	QObject::connect(userBtn, &QPushButton::released, this, &CreateUserGrDlg::OpenUserDlg);
	QObject::connect(groupBtn, &QPushButton::released, this, &CreateUserGrDlg::OpenGroupDlg);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
}

CreateUserGrDlg::~CreateUserGrDlg()
{
	delete vInt;
}

void CreateUserGrDlg::SetUserGroupParams(int uID, int gID, int id)
{
	userGroup->SetUserID(uID);
	userGroup->SetGroupID(gID);
	userGroup->SetID(id);
}

void CreateUserGrDlg::FillEditElements(int uID, int gID)
{
	userEdit->setText(QString::number(uID));
	groupEdit->setText(QString::number(gID));
	BusinessLayer::User user;
	BusinessLayer::Group group;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), userGroup->GetUserID(), errorMessage))
	{
		userSurnameLb->setText(user.GetSurname().c_str());
		userNameLB->setText(user.GetName().c_str());
	}
	if (group.GetGroupByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), userGroup->GetGroupID(), errorMessage))
	{
		groupNameLb->setText(group.GetName().c_str());
	}

}

void CreateUserGrDlg::SetID(int ID, QString childName)
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

			if (childName == QString("userForm"))
			{
				userEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					userSurnameLb->setText(user.GetSurname().c_str());
					userNameLB->setText(user.GetName().c_str());
				}
			}
			if (childName == QString("groupForm"))
			{
				groupEdit->setText(QString::number(ID));
				BusinessLayer::Group group;
				if (group.GetGroupByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					groupNameLb->setText(group.GetName().c_str());
				}
			}
		}
	}
}

bool CreateUserGrDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetUserGroupParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 6)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 6)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateUserGrDlg::CreateUserGroup()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt()
		&& 0 != groupEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetUserGroupParams(userEdit->text().toInt(), groupEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateUserGroupRelation(userGroup, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::User *user = new BusinessLayer::User;
					if (!user->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), userGroup->GetUserID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete user;
						return;
					}
					BusinessLayer::Group *group = new BusinessLayer::Group;
					if (!group->GetGroupByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), userGroup->GetGroupID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete user;
						delete group;
						return;
					}
					QList<QStandardItem*> userGroupItem;
					userGroupItem << new QStandardItem(QString::number(userGroup->GetID()))
						<< new QStandardItem(group->GetName().c_str())
						<< new QStandardItem(user->GetSurname().c_str())
						<< new QStandardItem(user->GetName().c_str())
						<< new QStandardItem(QString::number(user->GetRoleID()))
						<< new QStandardItem(QString::number(userGroup->GetGroupID()))
						<< new QStandardItem(QString::number(userGroup->GetUserID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(userGroupItem);

					delete user;
					delete group;
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

void CreateUserGrDlg::EditUserGroup()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt()
		&& 0 != groupEdit->text().toInt())
	{
		if (userGroup->GetUserID() != userEdit->text().toInt() ||
			userGroup->GetGroupID() != groupEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetUserGroupParams(userEdit->text().toInt(), groupEdit->text().toInt(), userGroup->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateUserGroupRelation(userGroup, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::User *user = new BusinessLayer::User;
						if (!user->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), userGroup->GetUserID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete user;
							return;
						}
						BusinessLayer::Group *group = new BusinessLayer::Group;
						if (!group->GetGroupByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), userGroup->GetGroupID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete user;
							delete group;
							return;
						}
						//updating UserGroup data
						itemModel->item(mIndex.row(), 1)->setText(group->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(user->GetSurname().c_str());
						itemModel->item(mIndex.row(), 3)->setText(user->GetName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(user->GetRoleID()));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(userGroup->GetGroupID()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(userGroup->GetUserID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete user;
						delete group;
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

void CreateUserGrDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateUserGrDlg::OpenUserDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Users"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::UserView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("userForm");
		dForm->QtConnect<BusinessLayer::UserView>();
		QMdiSubWindow *userWindow = new QMdiSubWindow;
		userWindow->setWidget(dForm);
		userWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(userWindow);
		userWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		//SortTable(dForm->tableView);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All users are shown");
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

void CreateUserGrDlg::OpenGroupDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Groups"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Group>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("groupForm");
		dForm->QtConnect<BusinessLayer::Group>();
		QMdiSubWindow *groupWindow = new QMdiSubWindow;
		groupWindow->setWidget(dForm);
		groupWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(groupWindow);
		groupWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All groups are shown");
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

