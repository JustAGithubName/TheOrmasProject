#include "stdafx.h"
#include "CreateStsRuleDlg.h"
#include "MainForm.h"
#include "DataForm.h"

CreateStsRuleDlg::CreateStsRuleDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	vInt = new QIntValidator(0, 1000000000, this);
	statusEdit->setValidator(vInt);
	operationEdit->setMaxLength(50);
	dialogBL = ormasBL;
	parentForm = parent;
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateStsRuleDlg::EditStatusRule);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateStsRuleDlg::CreateStatusRule);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateStsRuleDlg::Close);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateStsRuleDlg::OpenStsDlg);
}

void CreateStsRuleDlg::SetStatusRuleParams(QString sOperation, int sID, int id)
{
	statusRule->SetOperation(sOperation.toUtf8().constData());
	statusRule->SetStatusID(sID);
	statusRule->SetID(id);
}

void CreateStsRuleDlg::FillEditElements(QString sOperation, int sID)
{
	operationEdit->setText(sOperation);
	statusEdit->setText(QString::number(sID));
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

bool CreateStsRuleDlg::FillDlgElements(QTableView* sTable)
{
	QModelIndex mIndex = sTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetStatusRuleParams(sTable->model()->data(sTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 3)).toInt(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(sTable->model()->data(sTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 3)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateStsRuleDlg::CreateStatusRule()
{
	errorMessage.clear();
	if ( 0 != statusEdit->text().toInt() && operationEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetStatusRuleParams(operationEdit->text(), statusEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateStatusRule(statusRule, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), statusRule->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					QList<QStandardItem*> StatusRuleItem;
					StatusRuleItem << new QStandardItem(QString::number(statusRule->GetID()))
						<< new QStandardItem(statusRule->GetOperation().c_str())
						<< new QStandardItem(status->GetName().c_str())
						<< new QStandardItem(QString::number(statusRule->GetStatusID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(StatusRuleItem);
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
			QString(tr("Please fill code and name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateStsRuleDlg::EditStatusRule()
{
	errorMessage.clear();
	if (0 != statusEdit->text().toInt() && operationEdit->text().isEmpty())
	{
		if (QString(statusRule->GetOperation().c_str()) != operationEdit->text()
			|| statusRule->GetStatusID() != statusEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetStatusRuleParams(operationEdit->text(), statusEdit->text().toInt(), statusRule->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateStatusRule(statusRule, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Status *status = new BusinessLayer::Status;
						if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), statusRule->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete status;
							return;
						}
						
						itemModel->item(mIndex.row(), 1)->setText(statusRule->GetOperation().c_str());
						itemModel->item(mIndex.row(), 2)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(statusRule->GetStatusID()));
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
			QString(tr("Please fill code and name!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateStsRuleDlg::Close()
{
	this->parentWidget()->close();
}

void CreateStsRuleDlg::OpenStsDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	DataForm *userParent = (DataForm *)this->parentForm;
	MainForm *mainForm = (MainForm *)userParent->GetParent();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Status"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::Status>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("statusForm");
		dForm->QtConnect<BusinessLayer::Status>();
		QMdiSubWindow *statusWindow = new QMdiSubWindow;
		statusWindow->setWidget(dForm);
		statusWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(statusWindow);
		statusWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All statuses are shown");
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