#include "stdafx.h"
#include "CreateSAccLmDlg.h"
#include "DataForm.h"


CreateSAccLmDlg::CreateSAccLmDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(-1000000000.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	sAccEdit->setValidator(vInt);
	minValueEdit->setValidator(vDouble);
	maxValueEdit->setValidator(vDouble);
	minValueEdit->setMaxLength(20);
	maxValueEdit->setMaxLength(20);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateSAccLmDlg::EditSubaccountLimit);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateSAccLmDlg::CreateSubaccountLimit);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateSAccLmDlg::Close);
	QObject::connect(sAccBtn, &QPushButton::released, this, &CreateSAccLmDlg::OpenSAccDlg);
	QObject::connect(minValueEdit, &QLineEdit::textChanged, this, &CreateSAccLmDlg::TextEditChanged);
	QObject::connect(maxValueEdit, &QLineEdit::textChanged, this, &CreateSAccLmDlg::TextEditChanged);
}

CreateSAccLmDlg::~CreateSAccLmDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateSAccLmDlg::SetID(int ID, QString childName)
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

			if (childName == QString("subaccountForm"))
			{
				sAccEdit->setText(QString::number(ID));
				BusinessLayer::Subaccount sAcc;
				if (sAcc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					numberEdit->setText(sAcc.GetNumber().c_str());
				}
			}
		}
	}
}

void CreateSAccLmDlg::SetSubaccountLimitParams(int sAccID, double sMinValue, double sMaxValue, int id)
{
	subaccountLimit->SetSubaccountID(sAccID);
	subaccountLimit->SetMinValue(sMinValue);
	subaccountLimit->SetMaxValue(sMaxValue);
	subaccountLimit->SetID(id);
}

void CreateSAccLmDlg::FillEditElements(int sAccID, double sMinValue, double sMaxValue)
{
	minValueEdit->setText(QString::number(sMinValue));
	maxValueEdit->setText(QString::number(sMaxValue));
	sAccEdit->setText(QString::number(sAccID));
	BusinessLayer::Subaccount subaccount;
	if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sAccID, errorMessage))
	{
		numberEdit->setText(subaccount.GetNumber().c_str());
	}
}

bool CreateSAccLmDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetSubaccountLimitParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateSAccLmDlg::CreateSubaccountLimit()
{
	errorMessage.clear();
	if (0 != sAccEdit->text().toInt())
	{
		if (minValueEdit->text().toDouble() > maxValueEdit->text().toDouble())
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Minimum value must be litte than maximum value!")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		DataForm *parentDataForm = (DataForm*)parentForm;

		SetSubaccountLimitParams(sAccEdit->text().toInt(), minValueEdit->text().toDouble(), maxValueEdit->text().toDouble());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateSubaccountLimit(subaccountLimit, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Subaccount *subaccount = new BusinessLayer::Subaccount;
					if (!subaccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccountLimit->GetSubaccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete subaccount;
						return;
					}
					QList<QStandardItem*> sAccLmountItem;
					sAccLmountItem << new QStandardItem(QString::number(subaccountLimit->GetID()))
						<< new QStandardItem(subaccount->GetNumber().c_str())
						<< new QStandardItem(QString::number(subaccountLimit->GetSubaccountID()))
						<< new QStandardItem(QString::number(subaccountLimit->GetMinValue()))
						<< new QStandardItem(QString::number(subaccountLimit->GetMaxValue()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(sAccLmountItem);
					delete subaccount;
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

void CreateSAccLmDlg::EditSubaccountLimit()
{
	errorMessage.clear();
	if (0 != sAccEdit->text().toInt())
	{
		if (subaccountLimit->GetSubaccountID() != sAccEdit->text().toInt() || subaccountLimit->GetMinValue() != minValueEdit->text().toDouble() ||
			subaccountLimit->GetMaxValue() != maxValueEdit->text().toDouble())
		{
			if (minValueEdit->text().toDouble() > maxValueEdit->text().toDouble())
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Minimum value must be litte than maximum value!")),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetSubaccountLimitParams(sAccEdit->text().toInt(), minValueEdit->text().toDouble(), maxValueEdit->text().toDouble(), subaccountLimit->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateSubaccountLimit(subaccountLimit, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Subaccount *subaccount = new BusinessLayer::Subaccount;
						if (!subaccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccountLimit->GetSubaccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete subaccount;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(subaccount->GetNumber().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(subaccountLimit->GetSubaccountID()));
						itemModel->item(mIndex.row(), 3)->setText(QString::number(subaccountLimit->GetMinValue()));
						itemModel->item(mIndex.row(), 4)->setText(QString::number(subaccountLimit->GetMaxValue()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete subaccount;
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

void CreateSAccLmDlg::Close()
{
	this->parentWidget()->close();
}

void CreateSAccLmDlg::OpenSAccDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Suaccount"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::SubaccountView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("subaccountForm");
		dForm->QtConnect<BusinessLayer::SubaccountView>();
		QMdiSubWindow *sAccWindow = new QMdiSubWindow;
		sAccWindow->setWidget(dForm);
		sAccWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(sAccWindow);
		sAccWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->SetDecoration();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All subaccounts are shown");
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


void CreateSAccLmDlg::TextEditChanged()
{
	if (minValueEdit->text().contains(","))
	{
		minValueEdit->setText(minValueEdit->text().replace(",", "."));
	}
	if (minValueEdit->text().contains(".."))
	{
		minValueEdit->setText(minValueEdit->text().replace("..", "."));
	}
	if (maxValueEdit->text().contains(","))
	{
		maxValueEdit->setText(maxValueEdit->text().replace(",", "."));
	}
	if (maxValueEdit->text().contains(".."))
	{
		maxValueEdit->setText(maxValueEdit->text().replace("..", "."));
	}
}

