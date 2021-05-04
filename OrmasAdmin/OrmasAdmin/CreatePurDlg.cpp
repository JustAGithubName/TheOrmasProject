#include "stdafx.h"

#include "CreatePurDlg.h"
#include "DataForm.h"


CreatePurDlg::CreatePurDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	companyEdit->setMaxLength(100);
	passwordEdit->setMaxLength(30);
	vInt = new QIntValidator(0, 1000000000, this);
	roleNamePh->setText("PURVEYOR");
	locationEdit->setValidator(vInt);

	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePurDlg::EditPurveyor);
	}
	else
	{
		locationEdit->setText("0");

		QObject::connect(okBtn, &QPushButton::released, this, &CreatePurDlg::CreatePurveyor);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePurDlg::Close);
	QObject::connect(locationBtn, &QPushButton::released, this, &CreatePurDlg::OpenLcnDlg);
}

CreatePurDlg::~CreatePurDlg()
{
	delete purveyor;
	delete vInt;
}

void CreatePurDlg::SetID(int ID, QString childName)
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

void CreatePurDlg::SetPurveyorParams(QString pEmail, QString pName, QString pSurname, QString pPhone, QString pAddress,
	int pRoleID, QString pPassword, QString pActivated, QString pCompanyName, int pLocationID, int id)
{
	purveyor->SetEmail(pEmail.toUtf8().constData());
	purveyor->SetName(pName.toUtf8().constData());
	purveyor->SetSurname(pSurname.toUtf8().constData());
	purveyor->SetPhone(pPhone.toUtf8().constData());
	purveyor->SetAddress(pAddress.toUtf8().constData());
	purveyor->SetRoleID(pRoleID);
	purveyor->SetPassword(pPassword.toUtf8().constData());
	purveyor->SetActivated(pActivated == "true" ? true : false);
	purveyor->SetCompanyName(pCompanyName.toUtf8().constData());
	purveyor->SetLocationID(pLocationID);
	purveyor->SetID(id);
}

void CreatePurDlg::FillEditElements(QString pEmail, QString pName, QString pSurname, QString pPhone, QString pAddress,
	int pRoleID, QString pPassword, QString pActivated, QString pCompanyName, int pLocationID)
{
	emailEdit->setText(pEmail);
	nameEdit->setText(pName);
	surnameEdit->setText(pSurname);
	phoneEdit->setText(pPhone);
	addressEdit->setText(pAddress);
	passwordEdit->setText(pPassword);
	int index = activatedCmbBox->findText(pActivated);
	activatedCmbBox->setCurrentIndex(index);
	companyEdit->setText(pCompanyName);
	locationEdit->setText(QString::number(pLocationID));
	roleNamePh->setText("PURVEYOR");
}

bool CreatePurDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetPurveyorParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 13)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 8)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 14)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 13)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 8)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 14)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePurDlg::CreatePurveyor()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && !surnameEdit->text().isEmpty() && !phoneEdit->text().isEmpty()
		&& !addressEdit->text().isEmpty() && !companyEdit->text().isEmpty()
		&& !passwordEdit->text().isEmpty() && !activatedCmbBox->currentText().isEmpty() && 0 != locationEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;

		BusinessLayer::Role *role = new BusinessLayer::Role();
		role->SetName("PURVEYOR");
		std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
		std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);
		if (roleVector.size() < 1)
		{
			errorMessage = "Please contact with admin, program have fatal issue, Purveyor role doesn't exist!";
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}

		SetPurveyorParams(emailEdit->text(), nameEdit->text(), surnameEdit->text(), phoneEdit->text(), addressEdit->text(),
			roleVector.at(0).GetID(), passwordEdit->text(), activatedCmbBox->currentText(), companyEdit->text(),
		    locationEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreatePurveyor(purveyor, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Location *location = new BusinessLayer::Location();
					if (roleVector.size() < 1
						|| !location->GetLocationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), purveyor->GetLocationID(), errorMessage))
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
					QList<QStandardItem*> purveyorItem;
					purveyorItem << new QStandardItem(QString::number(purveyor->GetID()))
						<< new QStandardItem(purveyor->GetName().c_str())
						<< new QStandardItem(purveyor->GetSurname().c_str())
						<< new QStandardItem(purveyor->GetPhone().c_str())
						<< new QStandardItem(location->GetCountryName().c_str())
						<< new QStandardItem(location->GetRegionName().c_str())
						<< new QStandardItem(location->GetCityName().c_str())
						<< new QStandardItem(purveyor->GetAddress().c_str())
						<< new QStandardItem(purveyor->GetCompanyName().c_str())
						<< new QStandardItem(roleVector.at(0).GetName().c_str())
						<< new QStandardItem(purveyor->GetPassword().c_str())
						<< new QStandardItem(purveyor->GetEmail().c_str())
						<< new QStandardItem(purveyor->GetActivated() ? "true" : "false")
						<< new QStandardItem(QString::number(purveyor->GetRoleID()))
						<< new QStandardItem(QString::number(purveyor->GetLocationID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(purveyorItem);
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

void CreatePurDlg::EditPurveyor()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && !surnameEdit->text().isEmpty() && !phoneEdit->text().isEmpty()
		&& !addressEdit->text().isEmpty() && !companyEdit->text().isEmpty()
		&& !passwordEdit->text().isEmpty() && !activatedCmbBox->currentText().isEmpty() && 0 != locationEdit->text().toInt())
	{
		if (QString(purveyor->GetEmail().c_str()) != emailEdit->text() || QString(purveyor->GetName().c_str()) != nameEdit->text() ||
			QString(purveyor->GetSurname().c_str()) != surnameEdit->text() || QString(purveyor->GetAddress().c_str()) != addressEdit->text() ||
			QString(purveyor->GetPhone().c_str()) != phoneEdit->text() || QString(purveyor->GetCompanyName().c_str()) != companyEdit->text() ||
			purveyor->GetLocationID() != locationEdit->text().toInt() || QString(purveyor->GetPassword().c_str()) != passwordEdit->text() ||
			QString(purveyor->GetActivated() ? "true" : "false") != activatedCmbBox->currentText())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			BusinessLayer::Role *role = new BusinessLayer::Role();
			role->SetName("PURVEYOR");
			std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
			std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);
			if (roleVector.size() < 1)
			{
				errorMessage = "Please contact with admin, program have fatal issue, Purveyor role doesn't exist!";
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
			SetPurveyorParams(emailEdit->text(), nameEdit->text(), surnameEdit->text(), phoneEdit->text(), addressEdit->text(),
				roleVector.at(0).GetID(), passwordEdit->text(), activatedCmbBox->currentText(), companyEdit->text(),
			    locationEdit->text().toInt(), purveyor->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdatePurveyor(purveyor, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						//updating Pur data
						
						itemModel->item(mIndex.row(), 1)->setText(purveyor->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(purveyor->GetSurname().c_str());
						itemModel->item(mIndex.row(), 3)->setText(purveyor->GetPhone().c_str());

						//if location of Purveyor is changed, then update location data fields
						BusinessLayer::Location *location = new BusinessLayer::Location();

						if (roleVector.size() < 1
							|| !location->GetLocationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), purveyor->GetLocationID(), errorMessage))
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
						itemModel->item(mIndex.row(), 7)->setText(purveyor->GetAddress().c_str());
						itemModel->item(mIndex.row(), 8)->setText(purveyor->GetCompanyName().c_str());
						itemModel->item(mIndex.row(), 9)->setText(roleVector.at(0).GetName().c_str());
						itemModel->item(mIndex.row(), 10)->setText(purveyor->GetPassword().c_str());
						itemModel->item(mIndex.row(), 11)->setText(purveyor->GetEmail().c_str());
						itemModel->item(mIndex.row(), 12)->setText(purveyor->GetActivated() ? "true" : "false");
						itemModel->item(mIndex.row(), 13)->setText(QString::number(purveyor->GetRoleID()));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(purveyor->GetLocationID()));

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

void CreatePurDlg::Close()
{
	this->parentWidget()->close();
}

void CreatePurDlg::OpenLcnDlg()
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

void CreatePurDlg::OpenRoleDlg()
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
