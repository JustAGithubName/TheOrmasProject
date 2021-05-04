#include "stdafx.h"
#include "CreatePhtDlg.h"
#include "DataForm.h"



CreatePhtDlg::CreatePhtDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	productEdit->setValidator(vInt);
	userEdit->setValidator(vInt);
	sourceEdit->setMaxLength(100);
	if (parent->windowTitle().compare(tr("User photo")) == 0)
	{
		productEdit->setVisible(false);
		productBtn->setVisible(false);
		prodNameLb->setVisible(false);
		volumeLb->setVisible(false);
		measureLb->setVisible(false);
		prodNamePh->setVisible(false);
		volumePh->setVisible(false);
		measurePh->setVisible(false);
		userEdit->setVisible(true);
		userBtn->setVisible(true);
	}
	else
	{
		userEdit->setVisible(false);
		userBtn->setVisible(false);
		nameLb->setVisible(false);
		surnameLb->setVisible(false);
		phoneLb->setVisible(false);
		namePh->setVisible(false);
		surnamePh->setVisible(false);
		phonePh->setVisible(false);
		productEdit->setVisible(true);
		productBtn->setVisible(true);
	}
	if (true == updateFlag)
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePhtDlg::EditPhoto);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePhtDlg::CreatePhoto);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePhtDlg::Close);
	QObject::connect(userBtn, &QPushButton::released, this, &CreatePhtDlg::OpenUserDlg);
	QObject::connect(productBtn, &QPushButton::released, this, &CreatePhtDlg::OpenPrdDlg);
}

CreatePhtDlg::~CreatePhtDlg()
{
	delete vInt;
}

void CreatePhtDlg::SetID(int ID, QString childName)
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
					namePh->setText(user.GetName().c_str());
					surnamePh->setText(user.GetSurname().c_str());
					phonePh->setText(user.GetPhone().c_str());
				}
			}
			if (childName == QString("productForm"))
			{
				productEdit->setText(QString::number(ID));
				BusinessLayer::Product product;
				if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					prodNamePh->setText(product.GetName().c_str());
					volumePh->setText(QString::number(product.GetVolume()));
					BusinessLayer::Measure measure;
					if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
					{
						measurePh->setText(measure.GetShortName().c_str());
					}
				}
			}
		}
	}
}

void CreatePhtDlg::SetPhotoParams(int pUserID, int pProduct, QString pSource, int id)
{
	photo->SetUserID(pUserID);
	photo->SetProductID(pProduct);
	photo->SetSource(pSource.toUtf8().constData());
	photo->SetID(id);
}

void CreatePhtDlg::FillEditElements(int pUserID, int pProduct, QString pSource)
{
	userEdit->setText(QString::number(pUserID));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pUserID, errorMessage))
	{
		namePh->setText(user.GetName().c_str());
		surnamePh->setText(user.GetSurname().c_str());
		phonePh->setText(user.GetPhone().c_str());
	}
	productEdit->setText(QString::number(pProduct));
	BusinessLayer::Product product;
	if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pProduct, errorMessage))
	{
		prodNamePh->setText(product.GetName().c_str());
		volumePh->setText(QString::number(product.GetVolume()));
		BusinessLayer::Measure measure;
		if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
		{
			measurePh->setText(measure.GetShortName().c_str());
		}
	}
	sourceEdit->setText(pSource);
}

bool CreatePhtDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetPhotoParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePhtDlg::CreatePhoto()
{
	errorMessage.clear();
	if (!sourceEdit->text().isEmpty() && (0 != userEdit->text().toInt() || 0 != productEdit->text().toInt()))
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetPhotoParams(userEdit->text().toInt(), productEdit->text().toInt(), sourceEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreatePhoto(photo, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> photoItem;
					photoItem << new QStandardItem(QString::number(photo->GetID())) << new QStandardItem(QString::number(photo->GetUserID()))
						<< new QStandardItem(QString::number(photo->GetProductID())) << new QStandardItem(photo->GetSource().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(photoItem);
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
			QString(tr("Please fill user, product and source!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePhtDlg::EditPhoto()
{
	errorMessage.clear();
	if (!sourceEdit->text().isEmpty() && (0 != userEdit->text().toInt() || 0 != productEdit->text().toInt()))
	{
		if (photo->GetUserID() != userEdit->text().toInt() || photo->GetProductID() != productEdit->text().toInt()
			|| QString(photo->GetSource().c_str()) != sourceEdit->text())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetPhotoParams(userEdit->text().toInt(), productEdit->text().toInt(), sourceEdit->text(), photo->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdatePhoto(photo, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
						QModelIndex mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
						itemModel->item(mIndex.row(), 1)->setText(QString::number(photo->GetUserID()));
						itemModel->item(mIndex.row(), 2)->setText(QString::number(photo->GetProductID()));
						itemModel->item(mIndex.row(), 3)->setText(photo->GetSource().c_str());
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
			QString(tr("Please fill user, product and source!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePhtDlg::Close()
{
	this->parentWidget()->close();
}

void CreatePhtDlg::OpenUserDlg()
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

void CreatePhtDlg::OpenPrdDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Products"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ProductView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("productForm");
		dForm->QtConnect<BusinessLayer::ProductView>();
		QMdiSubWindow *productWindow = new QMdiSubWindow;
		productWindow->setWidget(dForm);
		productWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(productWindow);
		productWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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