#include "stdafx.h"

#include "CreateOthStDlg.h"
#include "DataForm.h"



CreateOthStDlg::CreateOthStDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 5, this);
	vInt = new QIntValidator(0, 1000000000, this);
	companyEdit->setValidator(vInt);
	volumeEdit->setValidator(vDouble);
	volumeEdit->setMaxLength(17);
	priceEdit->setValidator(vDouble);
	priceEdit->setMaxLength(17);
	nameEdit->setMaxLength(50);

	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateOthStDlg::EditOtherStocks);
	}
	else
	{
		companyEdit->setText("0");
		priceEdit->setText("0");
		volumeEdit->setText("0");
		QObject::connect(okBtn, &QPushButton::released, this, &CreateOthStDlg::CreateOtherStocks);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateOthStDlg::Close);
	QObject::connect(companyBtn, &QPushButton::released, this, &CreateOthStDlg::OpenCmpDlg);
	QObject::connect(volumeEdit, &QLineEdit::textChanged, this, &CreateOthStDlg::TextEditChanged);
	QObject::connect(priceEdit, &QLineEdit::textChanged, this, &CreateOthStDlg::TextEditChanged);
	InitComboBox();
}

CreateOthStDlg::~CreateOthStDlg()
{
	delete vDouble;
	delete vInt;
}

void CreateOthStDlg::SetID(int ID, QString childName)
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

			if (childName == QString("companyForm"))
			{
				companyEdit->setText(QString::number(ID));
				BusinessLayer::Company company;
				if (company.GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					companyNamePh->setText(company.GetName().c_str());
				}
			}
		}
	}
}

void CreateOthStDlg::SetOtherStocksParams(int pCountryID, QString pOtherStocksName, double pVolume, int pMeasureID, double pPrice,
	int pCurrencyID, int id)
{
	otherStocks->SetCompanyID(pCountryID);
	otherStocks->SetName(pOtherStocksName.toUtf8().constData());
	otherStocks->SetVolume(pVolume);
	otherStocks->SetMeasureID(pMeasureID);
	otherStocks->SetPrice(pPrice);
	otherStocks->SetCurrencyID(pCurrencyID);
	otherStocks->SetID(id);
}

void CreateOthStDlg::FillEditElements(int pCompanyID, QString pOtherStocksName, double pVolume, int pMeasureID, double pPrice,
	 int pCurrencyID)
{
	companyEdit->setText(QString::number(pCompanyID));
	nameEdit->setText(pOtherStocksName);
	volumeEdit->setText(QString::number(pVolume));
	priceEdit->setText(QString::number(pPrice));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(pCurrencyID)));
	measureCmb->setCurrentIndex(measureCmb->findData(QVariant(pMeasureID)));
	BusinessLayer::Company company;
	if (company.GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pCompanyID, errorMessage))
	{
		companyNamePh->setText(company.GetName().c_str());
	}
}

bool CreateOthStDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetOtherStocksParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateOthStDlg::CreateOtherStocks()
{
	errorMessage.clear();
	if (0 != companyEdit->text().toInt() && !nameEdit->text().isEmpty() && 0 != volumeEdit->text().toInt()
		&& !measureCmb->currentText().isEmpty() && 0 != priceEdit->text())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetOtherStocksParams(companyEdit->text().toInt(), nameEdit->text(), volumeEdit->text().toDouble(), measureCmb->currentData().toInt(),
			priceEdit->text().toDouble(), currencyCmb->currentData().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateOtherStocks(otherStocks, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Company *company = new BusinessLayer::Company();
					BusinessLayer::Measure *measure = new BusinessLayer::Measure();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency();

					if (!company->GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetCompanyID(), errorMessage)
						|| !measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetMeasureID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete company;
						delete measure;
						delete currency;
						return;
					}
					QList<QStandardItem*> otherStocksionItem;
					otherStocksionItem << new QStandardItem(QString::number(otherStocks->GetID()))
						<< new QStandardItem(otherStocks->GetName().c_str())
						<< new QStandardItem(QString::number(otherStocks->GetPrice()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(otherStocks->GetVolume()))
						<< new QStandardItem(measure->GetName().c_str())
						<< new QStandardItem(company->GetName().c_str())
						<< new QStandardItem(QString::number(otherStocks->GetCompanyID()))
						<< new QStandardItem(QString::number(otherStocks->GetMeasureID()))
						<< new QStandardItem(QString::number(otherStocks->GetCurrencyID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(otherStocksionItem);
					delete company;
					delete measure;
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateOthStDlg::EditOtherStocks()
{
	errorMessage.clear();
	if (0 != companyEdit->text().toInt() && !nameEdit->text().isEmpty() && 0 != volumeEdit->text().toInt()
		&& !measureCmb->currentText().isEmpty() && 0 != priceEdit->text()
		&& !currencyCmb->currentText().isEmpty())
	{
		if (otherStocks->GetCompanyID() != companyEdit->text().toInt() || QString(otherStocks->GetName().c_str()) != nameEdit->text() ||
			otherStocks->GetVolume() != volumeEdit->text().toDouble() || otherStocks->GetMeasureID() != measureCmb->currentData().toInt() ||
			otherStocks->GetPrice() != priceEdit->text().toDouble()|| otherStocks->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetOtherStocksParams(companyEdit->text().toInt(), nameEdit->text(), volumeEdit->text().toDouble(), measureCmb->currentData().toInt(),
				priceEdit->text().toDouble(), currencyCmb->currentData().toInt(), otherStocks->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateOtherStocks(otherStocks, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{

						itemModel->item(mIndex.row(), 1)->setText(otherStocks->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(otherStocks->GetPrice()));

						BusinessLayer::Company *company = new BusinessLayer::Company();
						BusinessLayer::Measure *measure = new BusinessLayer::Measure();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency();

						if (!company->GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetCompanyID(), errorMessage)
							|| !measure->GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetMeasureID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), otherStocks->GetCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete company;
							delete measure;
							delete currency;
							return;
						}

						itemModel->item(mIndex.row(), 3)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(otherStocks->GetVolume()));
						itemModel->item(mIndex.row(), 5)->setText(measure->GetName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(company->GetName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(QString::number(otherStocks->GetCompanyID()));
						itemModel->item(mIndex.row(), 8)->setText(QString::number(otherStocks->GetMeasureID()));
						itemModel->item(mIndex.row(), 9)->setText(QString::number(otherStocks->GetCurrencyID()));

						emit itemModel->dataChanged(mIndex, mIndex);

						delete company;
						delete measure;
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateOthStDlg::Close()
{
	this->parentWidget()->close();
}

void CreateOthStDlg::OpenCmpDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Companies"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Company>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("companyForm");
		dForm->QtConnect<BusinessLayer::Company>();
		QMdiSubWindow *companyWindow = new QMdiSubWindow;
		companyWindow->setWidget(dForm);
		companyWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(companyWindow);
		companyWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All companies are shown");
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

void CreateOthStDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
	std::vector<BusinessLayer::Measure> meaVector = dialogBL->GetAllDataForClass<BusinessLayer::Measure>(errorMessage);
	if (!meaVector.empty())
	{
		for (unsigned int i = 0; i < meaVector.size(); i++)
		{
			measureCmb->addItem(meaVector[i].GetShortName().c_str(), QVariant(meaVector[i].GetID()));
		}
	}
}

void CreateOthStDlg::TextEditChanged()
{
	if (priceEdit->text().contains(","))
	{
		priceEdit->setText(priceEdit->text().replace(",", "."));
	}
	if (priceEdit->text().contains(".."))
	{
		priceEdit->setText(priceEdit->text().replace("..", "."));
	}
	if (volumeEdit->text().contains(","))
	{
		volumeEdit->setText(volumeEdit->text().replace(",", "."));
	}
	if (volumeEdit->text().contains(".."))
	{
		volumeEdit->setText(volumeEdit->text().replace("..", "."));
	}
}