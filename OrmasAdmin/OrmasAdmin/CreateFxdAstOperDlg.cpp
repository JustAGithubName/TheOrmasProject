#include "stdafx.h"
#include "CreateFxdAstOperDlg.h"
#include "DataForm.h"


CreateFxdAstOperDlg::CreateFxdAstOperDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	valueEdit->setMaxLength(17);
	nameEdit->setMaxLength(200);
	fixedAstEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateFxdAstOperDlg::EditFixedAssetsOperation);
	}
	else
	{
		operDateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateFxdAstOperDlg::CreateFixedAssetsOperation);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateFxdAstOperDlg::Close);
	QObject::connect(fxdAstButton, &QPushButton::released, this, &CreateFxdAstOperDlg::OpenFxdAstDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreateFxdAstOperDlg::TextEditChanged);
}

CreateFxdAstOperDlg::~CreateFxdAstOperDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateFxdAstOperDlg::SetID(int ID, QString childName)
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

			if (childName == QString("fixedAssetsForm"))
			{
				fixedAstEdit->setText(QString::number(ID));
				
			}
		}
	}
}

void CreateFxdAstOperDlg::SetFixedAssetsOperationParams(QString oDate, QString oName, double oValue, QString oInc, QString oDec,
	int fxAssID, int id)
{
	fixedAssetsOperations->SetDate(oDate.toUtf8().constData());
	fixedAssetsOperations->SetName(oName.toUtf8().constData());
	fixedAssetsOperations->SetValue(oValue);
	fixedAssetsOperations->SetIncrement(oInc == "true" ? true : false);
	fixedAssetsOperations->SetDecrement(oDec == "true" ? true : false);
	fixedAssetsOperations->SetFixedAssetsID(fxAssID);
	fixedAssetsOperations->SetID(id);
}

void CreateFxdAstOperDlg::FillEditElements(QString oDate, QString oName, double oValue, QString oInc, QString oDec, int fxAssID)
{
	operDateEdit->setDate(QDate::fromString(oDate, "dd.MM.yyyy"));
	nameEdit->setText(oName);
	valueEdit->setText(QString::number(oValue, 'f', 3));
	fixedAstEdit->setText(QString::number(fxAssID));
	oInc == "true" ? inRdb->setChecked(true) : inRdb->setChecked(false);
	oDec == "true" ? decRdb->setChecked(true) : decRdb->setChecked(false);
}

bool CreateFxdAstOperDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetFixedAssetsOperationParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateFxdAstOperDlg::CreateFixedAssetsOperation()
{
	errorMessage.clear();
	if (0.0 != valueEdit->text().toDouble() && 0 != fixedAstEdit->text().toInt()
		&& !operDateEdit->text().isEmpty() && !nameEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetFixedAssetsOperationParams(operDateEdit->text(), nameEdit->text(), valueEdit->text().toDouble(), inRdb->isChecked()? "true":"false",
			decRdb->isChecked() ? "true" : "false", fixedAstEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateFixedAssetsOperation(fixedAssetsOperations, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> fixedAssetsOperationItem;
					fixedAssetsOperationItem << new QStandardItem(QString::number(fixedAssetsOperations->GetID()))
						<< new QStandardItem(fixedAssetsOperations->GetDate().c_str())
						<< new QStandardItem(fixedAssetsOperations->GetName().c_str())
						<< new QStandardItem(QString::number(fixedAssetsOperations->GetValue(), 'f', 3))
						<< new QStandardItem(inRdb->isChecked() ? "true" : "false")
						<< new QStandardItem(decRdb->isChecked() ? "true" : "false")
						<< new QStandardItem(QString::number(fixedAssetsOperations->GetFixedAssetsID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(fixedAssetsOperationItem);
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
			QString(tr("Please fill employee or subaccout, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateFxdAstOperDlg::EditFixedAssetsOperation()
{
	errorMessage.clear();
	if (0.0 != valueEdit->text().toDouble() && 0 != fixedAstEdit->text().toInt()
		&& !operDateEdit->text().isEmpty() && !nameEdit->text().isEmpty())
	{
		if (QString(fixedAssetsOperations->GetDate().c_str()) != operDateEdit->text() || fixedAssetsOperations->GetFixedAssetsID() != fixedAstEdit->text().toInt()
			|| fixedAssetsOperations->GetValue() != valueEdit->text().toDouble() || QString(fixedAssetsOperations->GetName().c_str()) != nameEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetFixedAssetsOperationParams(operDateEdit->text(), nameEdit->text(), valueEdit->text().toDouble(), inRdb->isChecked() ? "true" : "false",
				decRdb->isChecked() ? "true" : "false", fixedAstEdit->text().toInt(), fixedAssetsOperations->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateFixedAssetsOperation(fixedAssetsOperations, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(fixedAssetsOperations->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(fixedAssetsOperations->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(fixedAssetsOperations->GetValue(), 'f', 3));
						itemModel->item(mIndex.row(), 4)->setText(inRdb->isChecked()?"true":"false");
						itemModel->item(mIndex.row(), 5)->setText(decRdb->isChecked() ? "true" : "false");
						itemModel->item(mIndex.row(), 6)->setText(QString::number(fixedAssetsOperations->GetFixedAssetsID()));
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
			QString(tr("Please fill employee or subaccout, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateFxdAstOperDlg::Close()
{
	this->parentWidget()->close();
}

void CreateFxdAstOperDlg::OpenFxdAstDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Fixed assets"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::FixedAssetsView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("fixedAssetsForm");
		dForm->QtConnect<BusinessLayer::FixedAssetsView>();
		QMdiSubWindow *faWindow = new QMdiSubWindow;
		faWindow->setWidget(dForm);
		faWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(faWindow);
		faWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All fixed assets are shown");
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

void CreateFxdAstOperDlg::TextEditChanged()
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


