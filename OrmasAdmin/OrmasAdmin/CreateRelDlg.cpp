#include "stdafx.h"
#include "CreateRelDlg.h"
#include "DataForm.h"



CreateRelDlg::CreateRelDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	user1Edit->setValidator(vInt);
	user2Edit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRelDlg::EditRelation);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRelDlg::CreateRelation);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateRelDlg::Close);
	QObject::connect(user1Btn, &QPushButton::released, this, &CreateRelDlg::OpenUser1Dlg);
	QObject::connect(user2Btn, &QPushButton::released, this, &CreateRelDlg::OpenUser2Dlg);
	InitComboBox();
}

CreateRelDlg::~CreateRelDlg()
{
	delete vInt;
}


void CreateRelDlg::SetID(int ID, QString childName)
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

			if (childName == QString("user1Form"))
			{
				user1Edit->setText(QString::number(ID));
				BusinessLayer::User user1;
				if (user1.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					user1NamePh->setText(user1.GetName().c_str());
					user1SurnamePh->setText(user1.GetSurname().c_str());
					user1PhonePh->setText(user1.GetPhone().c_str());
				}
			}
			if (childName == QString("user2Form"))
			{
				user2Edit->setText(QString::number(ID));
				BusinessLayer::User user2;
				if (user2.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					user2NamePh->setText(user2.GetName().c_str());
					user2SurnamePh->setText(user2.GetSurname().c_str());
					user2PhonePh->setText(user2.GetPhone().c_str());
				}
			}
		}
	}
}

void CreateRelDlg::SetRelationParams(int rUser1ID, int rUser2ID, int rRelTypeID, int id)
{
	relation->SetUser1ID(rUser1ID);
	relation->SetUser2ID(rUser2ID);
	relation->SetRelationTypeID(rRelTypeID);
	relation->SetID(id);
}

void CreateRelDlg::FillEditElements(int rUser1ID, int rUser2ID, int rRelTypeID)
{
	user1Edit->setText(QString::number(rUser1ID));
	user2Edit->setText(QString::number(rUser2ID));
	relTypeCmb->setCurrentIndex(relTypeCmb->findData(QVariant(rRelTypeID)));
	BusinessLayer::User user1;
	if (user1.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), rUser1ID, errorMessage))
	{
		user1NamePh->setText(user1.GetName().c_str());
		user1SurnamePh->setText(user1.GetSurname().c_str());
		user1PhonePh->setText(user1.GetPhone().c_str());
	}
	BusinessLayer::User user2;
	if (user2.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), rUser2ID, errorMessage))
	{
		user2NamePh->setText(user2.GetName().c_str());
		user2SurnamePh->setText(user2.GetSurname().c_str());
		user2PhonePh->setText(user2.GetPhone().c_str());
	}
}

bool CreateRelDlg::FillDlgElements(QTableView* bTable)
{
	QModelIndex mIndex = bTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetRelationParams(bTable->model()->data(bTable->model()->index(mIndex.row(), 8)).toInt(),
			bTable->model()->data(bTable->model()->index(mIndex.row(), 9)).toInt(),
			bTable->model()->data(bTable->model()->index(mIndex.row(), 10)).toInt(),
			bTable->model()->data(bTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(bTable->model()->data(bTable->model()->index(mIndex.row(), 8)).toInt(),
			bTable->model()->data(bTable->model()->index(mIndex.row(), 8)).toInt(),
			bTable->model()->data(bTable->model()->index(mIndex.row(), 10)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateRelDlg::CreateRelation()
{
	errorMessage.clear();
	if (0 != user1Edit->text().toInt() || 0 != user2Edit->text().toInt() || !relTypeCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetRelationParams(user1Edit->text().toInt(), user2Edit->text().toInt(), relTypeCmb->currentData().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateRelation(relation, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::User *user1 = new BusinessLayer::User();
					BusinessLayer::User *user2 = new BusinessLayer::User();
					BusinessLayer::RelationType *rType = new BusinessLayer::RelationType();
					if (!user1->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), relation->GetUser1ID(), errorMessage)
						|| !user2->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), relation->GetUser2ID(), errorMessage)
						|| !rType->GetRelationTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), relation->GetRelationTypeID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete user1;
						delete user2;
						delete rType;
						return;
					}
					QList<QStandardItem*> relationItem;
					relationItem << new QStandardItem(QString::number(relation->GetID()))
						<< new QStandardItem(user1->GetName().c_str())
						<< new QStandardItem(user1->GetSurname().c_str())
						<< new QStandardItem(user1->GetPhone().c_str())
						<< new QStandardItem(rType->GetName().c_str())
						<< new QStandardItem(user2->GetName().c_str())
						<< new QStandardItem(user2->GetSurname().c_str())
						<< new QStandardItem(user2->GetPhone().c_str())
						<< new QStandardItem(QString::number(relation->GetUser1ID()))
						<< new QStandardItem(QString::number(relation->GetUser2ID()))
						<< new QStandardItem(QString::number(relation->GetRelationTypeID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(relationItem);
					delete user1;
					delete user2;
					delete rType;
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
			QString(tr("Please fill user1, user2 and relation type!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateRelDlg::EditRelation()
{
	errorMessage.clear();
	if (0 != user1Edit->text().toInt() || 0 != user2Edit->text().toInt() || !relTypeCmb->currentText().isEmpty())
	{
		if (relation->GetUser1ID() != user1Edit->text().toInt() || relation->GetUser2ID() != user2Edit->text().toInt()
			|| relation->GetRelationTypeID() != relTypeCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetRelationParams(user1Edit->text().toInt(), user2Edit->text().toInt(), relTypeCmb->currentData().toInt(), relation->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateRelation(relation, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::User *user1 = new BusinessLayer::User();
						BusinessLayer::User *user2 = new BusinessLayer::User();
						BusinessLayer::RelationType *rType = new BusinessLayer::RelationType();
						if (!user1->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), relation->GetUser1ID(), errorMessage)
							|| !user2->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), relation->GetUser2ID(), errorMessage)
							|| !rType->GetRelationTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), relation->GetRelationTypeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete user1;
							delete user2;
							delete rType;
							return;
						}
						
						itemModel->item(mIndex.row(), 1)->setText(user1->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(user1->GetSurname().c_str());
						itemModel->item(mIndex.row(), 3)->setText(user1->GetPhone().c_str());
						itemModel->item(mIndex.row(), 4)->setText(rType->GetName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(user2->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(user2->GetSurname().c_str());
						itemModel->item(mIndex.row(), 7)->setText(user2->GetPhone().c_str());
						itemModel->item(mIndex.row(), 8)->setText(QString::number(relation->GetUser1ID()));
						itemModel->item(mIndex.row(), 9)->setText(QString::number(relation->GetUser1ID()));
						itemModel->item(mIndex.row(), 10)->setText(QString::number(relation->GetRelationTypeID()));
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
			QString(tr("Please fill user, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateRelDlg::Close()
{
	this->parentWidget()->close();
}

void CreateRelDlg::OpenUser1Dlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("First user"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::UserView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("user1Form");
		dForm->QtConnect<BusinessLayer::UserView>();
		QMdiSubWindow *userWindow = new QMdiSubWindow;
		userWindow->setWidget(dForm);
		userWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(userWindow);
		userWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
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

void CreateRelDlg::OpenUser2Dlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Second user"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::UserView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("user2Form");
		dForm->QtConnect<BusinessLayer::UserView>();
		QMdiSubWindow *user2Window = new QMdiSubWindow;
		user2Window->setWidget(dForm);
		user2Window->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(user2Window);
		user2Window->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
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

void CreateRelDlg::InitComboBox()
{
	std::vector<BusinessLayer::RelationType> relTypeVector = dialogBL->GetAllDataForClass<BusinessLayer::RelationType>(errorMessage);
	if (!relTypeVector.empty())
	{
		for (unsigned int i = 0; i < relTypeVector.size(); i++)
		{
			relTypeCmb->addItem(relTypeVector[i].GetName().c_str(), QVariant(relTypeVector[i].GetID()));
		}
	}
}
