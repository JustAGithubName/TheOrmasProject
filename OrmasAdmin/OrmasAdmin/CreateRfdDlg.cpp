#include "stdafx.h"
#include "CreateRfdDlg.h"
#include "DataForm.h"


CreateRfdDlg::CreateRfdDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	userEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble);
	valueEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRfdDlg::EditRefund);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateRfdDlg::CreateRefund);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateRfdDlg::Close);
	QObject::connect(userBtn, &QPushButton::released, this, &CreateRfdDlg::OpenUserDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreateRfdDlg::TextEditChanged);
	InitComboBox();
}

CreateRfdDlg::~CreateRfdDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateRfdDlg::SetID(int ID, QString childName)
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
			}
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

void CreateRfdDlg::SetRefundParams(QString pDate, double pValue, int pUserID, int pCurrencyID, int id)
{
	refund->SetDate(pDate.toUtf8().constData());
	refund->SetValue(pValue);
	refund->SetUserID(pUserID);
	refund->SetCurrencyID(pCurrencyID);
	refund->SetID(id);
}

void CreateRfdDlg::FillEditElements(QString pDate, double pValue, int pUserID, int pCurrencyID)
{
	dateEdit->setDateTime(QDateTime::fromString(pDate, "dd.MM.yyyy hh:mm"));
	valueEdit->setText(QString::number(pValue));
	userEdit->setText(QString::number(pUserID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(pCurrencyID)));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pUserID, errorMessage))
	{
		namePh->setText(user.GetName().c_str());
		surnamePh->setText(user.GetSurname().c_str());
		phonePh->setText(user.GetPhone().c_str());
	}
}

bool CreateRfdDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetRefundParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateRfdDlg::CreateRefund()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetRefundParams(dateEdit->text(), valueEdit->text().toDouble(), userEdit->text().toInt(), currencyCmb->currentData().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateRefund(refund, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), refund->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete currency;
						return;
					}
					QList<QStandardItem*> refundItem;
					refundItem << new QStandardItem(QString::number(refund->GetID()))
						<< new QStandardItem(refund->GetDate().c_str())
						<< new QStandardItem(QString::number(refund->GetValue()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(refund->GetUserID()))
						<< new QStandardItem(QString::number(refund->GetCurrencyID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(refundItem);
					delete currency;
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
			QString(tr("Please fill user, value, date and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateRfdDlg::EditRefund()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty())
	{
		if (QString(refund->GetDate().c_str()) != dateEdit->text() || refund->GetUserID() != userEdit->text().toInt()
			|| refund->GetValue() != valueEdit->text().toDouble() || refund->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetRefundParams(dateEdit->text(), valueEdit->text().toDouble(), userEdit->text().toInt(), currencyCmb->currentData().toInt(), refund->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateRefund(refund, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), refund->GetCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete currency;
							return;
						}
					
						itemModel->item(mIndex.row(), 1)->setText(refund->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(refund->GetValue()));
						itemModel->item(mIndex.row(), 3)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(refund->GetUserID()));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(refund->GetCurrencyID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete currency;
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

void CreateRfdDlg::Close()
{
	this->parentWidget()->close();
}

void CreateRfdDlg::OpenUserDlg()
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

void CreateRfdDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			if (curVector[i].GetMainTrade() == true)
				currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
}

void CreateRfdDlg::TextEditChanged()
{
	if (valueEdit->text().contains(","))
	{
		valueEdit->setText(valueEdit->text().replace(",", "."));
	}
	if (valueEdit->text().contains(".."))
	{
		valueEdit->setText(valueEdit->text().replace("..", "."));
	}
}
