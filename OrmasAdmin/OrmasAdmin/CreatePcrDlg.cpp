#include "stdafx.h"
#include "CreatePcrDlg.h"

#include "MainForm.h"
#include "DataForm.h"



CreatePcrDlg::CreatePcrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	valueEdit->setValidator(vDouble);
	positionEdit->setValidator(vInt);
	valueEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePcrDlg::EditPercentRate);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePcrDlg::CreatePercentRate);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePcrDlg::Close);
	QObject::connect(positionBtn, &QPushButton::released, this, &CreatePcrDlg::OpenPosDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreatePcrDlg::TextEditChanged);
}

CreatePcrDlg::~CreatePcrDlg()
{
	delete vInt;
	delete vDouble;
}

void CreatePcrDlg::SetID(int ID, QString childName)
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

			if (childName == QString("positionForm"))
			{
				positionEdit->setText(QString::number(ID));
				BusinessLayer::Position position;
				if (position.GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					positionPh->setText(position.GetName().c_str());
				}
			}
		}
	}
}

void CreatePcrDlg::SetPercentRateParams(double pValue, QString pCondition, int posID, int id)
{
	percentRate->SetValue(pValue);
	percentRate->SetCondition(pCondition.toUtf8().constData());
	percentRate->SetPositionID(posID);
	percentRate->SetID(id);
}

void CreatePcrDlg::FillEditElements(double pValue, QString pCondition, int posID)
{
	valueEdit->setText(QString::number(pValue));
	conditionEdit->setText(pCondition);
	positionEdit->setText(QString::number(posID));
	BusinessLayer::Position position;
	if (position.GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), posID, errorMessage))
	{
		positionPh->setText(position.GetName().c_str());
	}
}

bool CreatePcrDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetPercentRateParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePcrDlg::CreatePercentRate()
{
	errorMessage.clear();
	if (0.0 != valueEdit->text().toDouble() && 0 != positionEdit->text().toInt()
		&& !conditionEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetPercentRateParams(valueEdit->text().toDouble(), conditionEdit->text(), positionEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreatePercentRate(percentRate, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Position *position = new BusinessLayer::Position;
					if (!position->GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), percentRate->GetPositionID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete position;
						return;
					}
					QList<QStandardItem*> PercentRateItem;
					PercentRateItem << new QStandardItem(QString::number(percentRate->GetID()))
						<< new QStandardItem(QString::number(percentRate->GetValue()))
						<< new QStandardItem(percentRate->GetCondition().c_str())
						<< new QStandardItem(QString::number(percentRate->GetPositionID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(PercentRateItem);
					delete position;
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
			QString(tr("Please fill position, condition and value!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePcrDlg::EditPercentRate()
{
	errorMessage.clear();
	if (0.0 != valueEdit->text().toDouble() && 0 != positionEdit->text().toInt()
		&& !conditionEdit->text().isEmpty())
	{
		if (percentRate->GetValue() != valueEdit->text().toDouble() || QString(percentRate->GetCondition().c_str()) != conditionEdit->text() ||
			percentRate->GetPositionID() != positionEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetPercentRateParams(valueEdit->text().toDouble(), conditionEdit->text(), positionEdit->text().toInt(), percentRate->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdatePercentRate(percentRate, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Position *position = new BusinessLayer::Position;
						if (!position->GetPositionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), percentRate->GetPositionID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete position;
							return;
						}
						QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
						QModelIndex mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
						itemModel->item(mIndex.row(), 1)->setText(QString::number(percentRate->GetValue()));
						itemModel->item(mIndex.row(), 2)->setText(percentRate->GetCondition().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(percentRate->GetPositionID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete position;
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
			QString(tr("Please fill position, condition and value!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePcrDlg::Close()
{
	this->parentWidget()->close();
}

void CreatePcrDlg::OpenPosDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("positions"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Position>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("positionForm");
		dForm->QtConnect<BusinessLayer::Position>();
		QMdiSubWindow *currencyWindow = new QMdiSubWindow;
		currencyWindow->setWidget(dForm);
		currencyWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(currencyWindow);
		currencyWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All positions are shown");
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

void CreatePcrDlg::TextEditChanged()
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
