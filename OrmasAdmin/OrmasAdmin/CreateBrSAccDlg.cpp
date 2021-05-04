#include "stdafx.h"

#include "CreateBrSAccDlg.h"
#include "DataForm.h"

#include <map>

CreateBrSAccDlg::CreateBrSAccDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
		QObject::connect(okBtn, &QPushButton::released, this, &CreateBrSAccDlg::EditBranchSubaccount);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateBrSAccDlg::CreateBranchSubaccount);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateBrSAccDlg::Close);
	QObject::connect(subaccountBtn, &QPushButton::released, this, &CreateBrSAccDlg::OpenSAccDlg);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateBrSAccDlg::~CreateBrSAccDlg()
{
	delete vInt;
	emit CloseCreatedForms();

}

void CreateBrSAccDlg::SetBranchSubaccountParams(int braID, int subaccID, int id)
{
	branchSubaccount->SetBranchID(braID);
	branchSubaccount->SetSubaccountID(subaccID);
	branchSubaccount->SetID(id);
}

void CreateBrSAccDlg::FillEditElements(int braID, int subaccID)
{
	branchCmb->setCurrentIndex(branchCmb->findData(QVariant(braID)));
	subaccountEdit->setText(QString::number(subaccID));
}

void CreateBrSAccDlg::SetID(int ID, QString childName)
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
				subaccountEdit->setText(QString::number(ID));
			}
		}
	}
}

bool CreateBrSAccDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetBranchSubaccountParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateBrSAccDlg::CreateBranchSubaccount()
{
	errorMessage.clear();
	if (0 != subaccountEdit->text().toInt() && !branchCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetBranchSubaccountParams(branchCmb->currentData().toInt(), subaccountEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateBranchSubaccount(branchSubaccount, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Subaccount *subaccount = new BusinessLayer::Subaccount;
					if (!subaccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), branchSubaccount->GetSubaccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete subaccount;
						return;
					}
					
					BusinessLayer::Branch *branch = new BusinessLayer::Branch;
					if (!branch->GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), branchSubaccount->GetBranchID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete subaccount;
						delete branch;
						return;
					}
					QList<QStandardItem*> BranchSubaccountItem;
					BranchSubaccountItem << new QStandardItem(QString::number(branchSubaccount->GetID()))
						<< new QStandardItem(branch->GetName().c_str())
						<< new QStandardItem(subaccount->GetNumber().c_str())
						<< new QStandardItem(QString::number(branchSubaccount->GetBranchID()))
						<< new QStandardItem(QString::number(branchSubaccount->GetSubaccountID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(BranchSubaccountItem);

					delete branch;
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
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields, especially product list!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateBrSAccDlg::EditBranchSubaccount()
{
	errorMessage.clear();
	if (0 != subaccountEdit->text().toInt() && !branchCmb->currentText().isEmpty())
	{
		if (branchSubaccount->GetBranchID() != subaccountEdit->text().toInt() ||
			branchSubaccount->GetSubaccountID() != branchCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetBranchSubaccountParams(branchCmb->currentData().toInt(), subaccountEdit->text().toInt(), branchSubaccount->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateBranchSubaccount(branchSubaccount, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Subaccount *subaccount = new BusinessLayer::Subaccount;
						if (!subaccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), branchSubaccount->GetSubaccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete subaccount;
							return;
						}
						BusinessLayer::Branch *branch = new BusinessLayer::Branch;
						if (!branch->GetBranchByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), branchSubaccount->GetBranchID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete subaccount;
							delete branch;
							return;
						}
						//updating BranchSubaccount data
						itemModel->item(mIndex.row(), 1)->setText(branch->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(subaccount->GetNumber().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(branchSubaccount->GetBranchID()));
						itemModel->item(mIndex.row(), 4)->setText(QString::number(branchSubaccount->GetSubaccountID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete branch;
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateBrSAccDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateBrSAccDlg::OpenSAccDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Subaccounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::SubaccountView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("subaccountForm");
		dForm->QtConnect<BusinessLayer::SubaccountView>();
		QMdiSubWindow *cAccountWindow = new QMdiSubWindow;
		cAccountWindow->setWidget(dForm);
		cAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(cAccountWindow);
		cAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All accounts are shown");
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

void CreateBrSAccDlg::InitComboBox()
{
	std::vector<BusinessLayer::Branch> curBranch = dialogBL->GetAllDataForClass<BusinessLayer::Branch>(errorMessage);
	if (!curBranch.empty())
	{
		for (unsigned int i = 0; i < curBranch.size(); i++)
		{
			branchCmb->addItem(curBranch[i].GetName().c_str(), QVariant(curBranch[i].GetID()));
		}
	}
}

