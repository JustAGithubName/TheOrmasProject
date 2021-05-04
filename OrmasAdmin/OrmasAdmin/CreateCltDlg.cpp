#include "stdafx.h"

#include "CreateCltDlg.h"
#include "DataForm.h"


CreateCltDlg::CreateCltDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	activatedCmbBox->addItem("false");
	activatedCmbBox->addItem("true");
	locationEdit->setReadOnly(true);
	emailEdit->setMaxLength(30);
	surnameEdit->setMaxLength(50);
	nameEdit->setMaxLength(40);
	phoneEdit->setMaxLength(20);
	addressEdit->setMaxLength(50);
	firmEdit->setMaxLength(50);
	firmNumEdit->setMaxLength(10);
	passwordEdit->setMaxLength(30);
	vInt = new QIntValidator(0, 1000000000, this);
	roleNamePh->setText("CLIENT");
	locationEdit->setValidator(vInt);

	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCltDlg::EditClient);
	}
	else
	{
		locationEdit->setText("0");
		
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCltDlg::CreateClient);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateCltDlg::Close);
	QObject::connect(locationBtn, &QPushButton::released, this, &CreateCltDlg::OpenLcnDlg);
}

CreateCltDlg::~CreateCltDlg()
{
	delete client;
	delete vInt;
}

void CreateCltDlg::SetID(int ID, QString childName)
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

			if (childName == QString("locationForm"))
			{
				locationEdit->setText(QString::number(ID));
			}
		}
	}
}

void CreateCltDlg::SetClientParams(QString cEmail, QString cName, QString cSurname, QString cPhone, QString cAddress, 
	int cRoleID, QString cPassword, QString cActivated, QString cFirm, QString cFirmNumber, int cLocationID, int id)
{
	client->SetEmail(cEmail.toUtf8().constData());
	client->SetName(cName.toUtf8().constData());
	client->SetSurname(cSurname.toUtf8().constData());
	client->SetPhone(cPhone.toUtf8().constData());
	client->SetAddress(cAddress.toUtf8().constData());
	client->SetRoleID(cRoleID);
	client->SetPassword(cPassword.toUtf8().constData());
	client->SetActivated(cActivated == "true" ? true : false);
	client->SetFirm(cFirm.toUtf8().constData());
	client->SetFirmNumber(cFirmNumber.toUtf8().constData());
	client->SetLocationID(cLocationID);
	client->SetID(id);
}

void CreateCltDlg::FillEditElements(QString cEmail, QString cName, QString cSurname, QString cPhone, QString cAddress,
	int cRoleID, QString cPassword, QString cActivated, QString cFirm, QString cFirmNumber, int cLocationID)
{
	emailEdit->setText(cEmail);
	nameEdit->setText(cName);
	surnameEdit->setText(cSurname);
	phoneEdit->setText(cPhone);
	addressEdit->setText(cAddress);
	passwordEdit->setText(cPassword);
	int index = activatedCmbBox->findText(cActivated);
	activatedCmbBox->setCurrentIndex(index);
	firmEdit->setText(cFirm);
	firmNumEdit->setText(cFirmNumber);
	locationEdit->setText(QString::number(cLocationID));
	roleNamePh->setText("CLIENT");
}

bool CreateCltDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetClientParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 14)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 13)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 8)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 9)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 15)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 14)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 13)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 8)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 9)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 15)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateCltDlg::CreateClient()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && !surnameEdit->text().isEmpty() && !phoneEdit->text().isEmpty()
		&& !addressEdit->text().isEmpty() && !firmEdit->text().isEmpty() 
		&& !passwordEdit->text().isEmpty() && !activatedCmbBox->currentText().isEmpty() &&  0 != locationEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		
		BusinessLayer::Role *role = new BusinessLayer::Role();
		role->SetName("CLIENT");
		std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
		std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);
		if (roleVector.size() < 1)
		{
			errorMessage = "Please contact with admin, program have fatal issue, client role doesn't exist!";
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}

		SetClientParams(emailEdit->text(), nameEdit->text(), surnameEdit->text(), phoneEdit->text(), addressEdit->text(),
			roleVector.at(0).GetID(), passwordEdit->text(), activatedCmbBox->currentText(), firmEdit->text(),
			firmNumEdit->text(), locationEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateClient(client, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Location *location = new BusinessLayer::Location();
					if (roleVector.size() < 1
						|| !location->GetLocationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), client->GetLocationID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete location;
						delete role;
						return;
					}
					QList<QStandardItem*> clientItem;
					clientItem << new QStandardItem(QString::number(client->GetID()))
						<< new QStandardItem(client->GetName().c_str())
						<< new QStandardItem(client->GetSurname().c_str())
						<< new QStandardItem(client->GetPhone().c_str())
						<< new QStandardItem(location->GetCountryName().c_str())
						<< new QStandardItem(location->GetRegionName().c_str())
						<< new QStandardItem(location->GetCityName().c_str())
						<< new QStandardItem(client->GetAddress().c_str())
						<< new QStandardItem(client->GetFirm().c_str())
						<< new QStandardItem(client->GetFirmNumber().c_str())
						<< new QStandardItem(roleVector.at(0).GetName().c_str())
						<< new QStandardItem(client->GetPassword().c_str())
						<< new QStandardItem(client->GetEmail().c_str())
						<< new QStandardItem(client->GetActivated() ? "true" : "false")
						<< new QStandardItem(QString::number(client->GetRoleID()))
						<< new QStandardItem(QString::number(client->GetLocationID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(clientItem);

					delete location;
					
				}
			}
			delete role;
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCltDlg::EditClient()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && !surnameEdit->text().isEmpty() && !phoneEdit->text().isEmpty()
		&& !addressEdit->text().isEmpty() && !firmEdit->text().isEmpty() 
		&& !passwordEdit->text().isEmpty() && !activatedCmbBox->currentText().isEmpty() && 0 != locationEdit->text().toInt())
	{
		if (QString(client->GetEmail().c_str()) != emailEdit->text() || QString(client->GetName().c_str()) != nameEdit->text() ||
			QString(client->GetSurname().c_str()) != surnameEdit->text() || QString(client->GetAddress().c_str()) != addressEdit->text() ||
			QString(client->GetPhone().c_str()) != phoneEdit->text() || QString(client->GetFirm().c_str()) != firmEdit->text() ||
			QString(client->GetFirmNumber().c_str()) != firmNumEdit->text() ||
			client->GetLocationID() != locationEdit->text().toInt() || QString(client->GetPassword().c_str()) != passwordEdit->text() ||
			QString(client->GetActivated() ? "true" : "false") != activatedCmbBox->currentText())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			BusinessLayer::Role *role = new BusinessLayer::Role();
			role->SetName("CLIENT");
			std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
			std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);
			if (roleVector.size() < 1)
			{
				errorMessage = "Please contact with admin, program have fatal issue, client role doesn't exist!";
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
			SetClientParams(emailEdit->text(), nameEdit->text(), surnameEdit->text(), phoneEdit->text(), addressEdit->text(),
				roleVector.at(0).GetID(), passwordEdit->text(), activatedCmbBox->currentText(), firmEdit->text(),
				firmNumEdit->text(), locationEdit->text().toInt(), client->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateClient(client, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating Clt data
						
						itemModel->item(mIndex.row(), 1)->setText(client->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(client->GetSurname().c_str());
						itemModel->item(mIndex.row(), 3)->setText(client->GetPhone().c_str());

						//if location of client is changed, then update location data fields
						BusinessLayer::Location *location = new BusinessLayer::Location();

						if (roleVector.size() < 1
							|| !location->GetLocationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), client->GetLocationID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete location;
							delete role;
							return;
						}
						itemModel->item(mIndex.row(), 4)->setText(location->GetCountryName().c_str());
						itemModel->item(mIndex.row(), 5)->setText(location->GetRegionName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(location->GetCityName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(client->GetAddress().c_str());
						itemModel->item(mIndex.row(), 8)->setText(client->GetFirm().c_str());
						itemModel->item(mIndex.row(), 9)->setText(client->GetFirmNumber().c_str());
						itemModel->item(mIndex.row(), 10)->setText(roleVector.at(0).GetName().c_str());
						itemModel->item(mIndex.row(), 11)->setText(client->GetPassword().c_str());
						itemModel->item(mIndex.row(), 12)->setText(client->GetEmail().c_str());
						itemModel->item(mIndex.row(), 13)->setText(client->GetActivated() ? "true" : "false");
						itemModel->item(mIndex.row(), 14)->setText(QString::number(client->GetRoleID()));
						itemModel->item(mIndex.row(), 15)->setText(QString::number(client->GetLocationID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete location;
					}
				}

				
				delete role;
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

void CreateCltDlg::Close()
{
	this->parentWidget()->close();
}

void CreateCltDlg::OpenLcnDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Locations"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Location>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("locationForm");
		dForm->QtConnect<BusinessLayer::Location>();
		QMdiSubWindow *locationWindow = new QMdiSubWindow;
		locationWindow->setWidget(dForm);
		locationWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(locationWindow);
		locationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All locations are shown");
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

void CreateCltDlg::OpenRoleDlg()
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
