#include "stdafx.h"

#include "CreateMcurDlg.h"

#include "DataForm.h"


CreateMcurDlg::CreateMcurDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(-1000000000.00, 1000000000.00, 2, this);
	vInt = new QIntValidator(0, 1000000000, this);
	mianNumberEdit->setMaxLength(20);
	subNumberEdit->setMaxLength(20);
	newNumberEdit->setMaxLength(20);
	statusEdit->setValidator(vInt);
	startBalanceEdit->setValidator(vDouble);
	currentBalanceEdit->setValidator(vDouble);
	newStartBalanceEdit->setValidator(vDouble);
	newCurrentBalanceEdit->setValidator(vDouble);
	commonStartBalanceEdit->setValidator(vDouble);
	commonEndBalanceEdit->setValidator(vDouble);
	startBalanceEdit->setMaxLength(17);
	currentBalanceEdit->setMaxLength(17);
	newStartBalanceEdit->setMaxLength(17);
	newCurrentBalanceEdit->setMaxLength(17);
	openedDateEdit->setDate(QDate::currentDate());
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		//QObject::connect(okBtn, &QPushButton::released, this, &CreateMcurDlg::EditMulticurrency);
	}
	else
	{
		openedDateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateMcurDlg::CreateMulticurrency);
	}
	InitComboBox();
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateMcurDlg::Close);
	QObject::connect(chartOfAccBtn, &QPushButton::released, this, &CreateMcurDlg::OpenCOADlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateMcurDlg::OpenStsDlg);
	QObject::connect(startBalanceEdit, &QLineEdit::textChanged, this, &CreateMcurDlg::TextEditChanged);
	QObject::connect(currentBalanceEdit, &QLineEdit::textChanged, this, &CreateMcurDlg::TextEditChanged);
	QObject::connect(chartOfAccEdit, &QLineEdit::textChanged, this, &CreateMcurDlg::GenerateTwoNumbers);
	QObject::connect(subCurrencyCmb, &QComboBox::currentTextChanged, this, &CreateMcurDlg::GenerateTwoNumbers);
	QObject::connect(currencyCmb, &QComboBox::currentTextChanged, this, &CreateMcurDlg::GenerateNumber); 
	QObject::connect(mainSubaccEdit, &QLineEdit::textChanged, this, &CreateMcurDlg::GenerateNumber);
	QObject::connect(selectMainSubaccount, &QPushButton::released, this, &CreateMcurDlg::OpenSAccDlg);
	QObject::connect(newCurrentBalanceEdit, &QLineEdit::textChanged, this, &CreateMcurDlg::TextEditChanged);
	QObject::connect(newStartBalanceEdit, &QLineEdit::textChanged, this, &CreateMcurDlg::TextEditChanged);
	
}

CreateMcurDlg::~CreateMcurDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateMcurDlg::SetID(int ID, QString childName)
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

			if (childName == QString("chartOfAccountForm"))
			{
				chartOfAccEdit->setText(QString::number(ID));
				BusinessLayer::ChartOfAccounts coMcur;
				if (coMcur.GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					accNamePh->setText(coMcur.GetName().c_str());
				}
				mainSubaccEdit->setText("");
			}
			if (childName == QString("statusForm"))
			{
				statusEdit->setText(QString::number(ID));
				BusinessLayer::Status status;
				if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					statusPh->setText(status.GetName().c_str());
				}
			}
			if (childName == QString("subaccountForm"))
			{
				mainSubaccEdit->setText(QString::number(ID));
				BusinessLayer::Subaccount subaccount;
				if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					mainSubaccNumberEdit->setText(subaccount.GetNumber().c_str());
					commonStartBalanceEdit->setText(QString::number(subaccount.GetStartBalance(), 'f',3));
					commonEndBalanceEdit->setText(QString::number(subaccount.GetCurrentBalance(),'f',3));
					GenerateNumber();
				}
				chartOfAccEdit->setText("");
			}
		}
	}
}

void CreateMcurDlg::SetMulticurrencyParams(int scID, int mcID, QString sCommnet, int id)
{
	multicurrency->SetSubaccountCurrencyID(scID);
	multicurrency->SetSubaccountMainCurrencyID(mcID);
	multicurrency->SetComment(sCommnet.toUtf8().constData());
	multicurrency->SetID(id);

	BusinessLayer::Subaccount exchangeSub;
	if (exchangeSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), scID, errorMessage))
	{
		multicurrency->SetExchangeSubaccount(exchangeSub);
	}

	BusinessLayer::Subaccount mainSub;
	if (mainSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mcID, errorMessage))
	{
		multicurrency->SetMainSubaccount(mainSub);
	}
}

void CreateMcurDlg::FillEditElements(int cID, int sID, QString aComment)
{
	/*numberEdit->setText(aNumber);
	startBalanceEdit->setText(QString::number(aStartBalance));
	currentBalanceEdit->setText(QString::number(aCurrentBalance));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(cID)));
	statusEdit->setText(QString::number(sID));
	openedDateEdit->setDate(QDate::fromString(aOpenedDate, "dd.MM.yyyy"));
	detailsEdit->setText(aDetails);
	BusinessLayer::ChartOfAccounts aoMcur;
	BusinessLayer::Status status;
	if (aoMcur.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), aNumber.left(5).toUtf8().constData(), errorMessage))
	{
		chartOfAccEdit->setText(QString::number(aoMcur.GetID()));
		accNamePh->setText(aoMcur.GetName().c_str());
	}
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}*/
}

bool CreateMcurDlg::FillDlgElements(QTableView* pTable)
{
	/*QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetMulticurrencyParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}*/
	return true;
}

void CreateMcurDlg::CreateMulticurrency()
{
	errorMessage.clear();
	if (!(chartOfAccEdit->text().isEmpty() && mainSubaccEdit->text().isEmpty()) && !(currencyCmb->currentText().isEmpty() && subCurrencyCmb->currentText().isEmpty()))
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		BusinessLayer::Subaccount exchangeSub;
		BusinessLayer::Subaccount mainSub;

		if (!mainSubaccEdit->text().isEmpty() || mainSubaccEdit->text().toInt() > 0)
		{
			if (mainSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainSubaccEdit->text().toInt(), errorMessage))
			{
				if (newNumberEdit->text().isEmpty())
				{
					errorMessage = "Number is empty! Please contact with administrator!";
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Error")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				if ((mainSub.GetCurrentBalance() < 0 && newCurrentBalanceEdit->text().toDouble()>0)
					|| (mainSub.GetStartBalance() <0 && newStartBalanceEdit->text().toDouble()>0)
					|| (mainSub.GetCurrentBalance() > 0 && newCurrentBalanceEdit->text().toDouble()<0)
					|| (mainSub.GetStartBalance() >0 && newStartBalanceEdit->text().toDouble() < 0))
				{
					errorMessage = "If value is negative/positive in main subaccount, then in exchange subaccount must be the same!";
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Error")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				exchangeSub.SetClosedDate(mainSub.GetClosedDate());
				exchangeSub.SetCurrencyID(currencyCmb->currentData().toInt());
				exchangeSub.SetCurrentBalance(newCurrentBalanceEdit->text().toDouble());
				exchangeSub.SetStartBalance(newStartBalanceEdit->text().toDouble());
				exchangeSub.SetDetails(newDetailsEdit->text().toUtf8().constData());
				exchangeSub.SetNumber(newNumberEdit->text().toUtf8().constData());
				exchangeSub.SetOpenedDate(mainSub.GetOpenedDate());
				exchangeSub.SetParentAccountID(mainSub.GetParentAccountID());
				exchangeSub.SetStatusID(mainSub.GetStatusID());
				if (!exchangeSub.CreateSubaccount(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
				{
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Error")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
			}
			else
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Error")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
		}
		else if (!chartOfAccEdit->text().isEmpty() && 0 != statusEdit->text().toInt())
		{
			BusinessLayer::Currency mainCur;
			int mainCurID = mainCur.GetMainTradeCurrencyID(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
			if (mainCurID <= 0)
			{
				errorMessage = "Number is empty! Please contact with administrator!";
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Error")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
			mainSub.SetClosedDate("");
			mainSub.SetCurrencyID(mainCurID);
			mainSub.SetCurrentBalance(startBalanceEdit->text().toDouble());
			mainSub.SetStartBalance(currentBalanceEdit->text().toDouble());
			mainSub.SetDetails(detailsEdit->text().toUtf8().constData());
			mainSub.SetNumber(mianNumberEdit->text().toUtf8().constData());
			mainSub.SetOpenedDate(openedDateEdit->text().toUtf8().constData());
			mainSub.SetParentAccountID(parentAccID);
			mainSub.SetStatusID(statusEdit->text().toInt());
			if (mainSub.CreateSubaccount(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
			{
				if (subNumberEdit->text().isEmpty())
				{
					errorMessage = "Number is empty! Please contact with administrator!";
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Error")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
				exchangeSub.SetClosedDate(mainSub.GetClosedDate());
				exchangeSub.SetCurrencyID(currencyCmb->currentData().toInt());
				exchangeSub.SetCurrentBalance(newCurrentBalanceEdit->text().toDouble());
				exchangeSub.SetStartBalance(newStartBalanceEdit->text().toDouble());
				exchangeSub.SetDetails(newDetailsEdit->text().toUtf8().constData());
				exchangeSub.SetNumber(subNumberEdit->text().toUtf8().constData());
				exchangeSub.SetOpenedDate(mainSub.GetOpenedDate());
				exchangeSub.SetParentAccountID(mainSub.GetParentAccountID());
				exchangeSub.SetStatusID(mainSub.GetStatusID());
				if (!exchangeSub.CreateSubaccount(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
				{
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Error")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
					errorMessage.clear();
					return;
				}
			}
			else
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Error")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
		}
		else
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Error")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}

		SetMulticurrencyParams(exchangeSub.GetID(), mainSub.GetID(), "");
		
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateMulticurrency(multicurrency, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Currency exhCur;
					BusinessLayer::Currency mainCur;
					exhCur.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), exchangeSub.GetCurrencyID(), errorMessage);
					mainCur.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainSub.GetCurrencyID(), errorMessage);
					QList<QStandardItem*> McurountItem;
					McurountItem << new QStandardItem(QString::number(multicurrency->GetID()))
						<< new QStandardItem(exchangeSub.GetNumber().c_str())
						<< new QStandardItem(QString::number(exchangeSub.GetCurrentBalance(), 'f', 3))
						<< new QStandardItem(exhCur.IsEmpty() ? "" : exhCur.GetShortName().c_str())
						<< new QStandardItem(mainSub.GetNumber().c_str())
						<< new QStandardItem(QString::number(mainSub.GetCurrentBalance(), 'f', 3))
						<< new QStandardItem(mainCur.IsEmpty() ? "" : mainCur.GetShortName().c_str())
						<< new QStandardItem(QString::number(exchangeSub.GetID()))
						<< new QStandardItem(QString::number(mainSub.GetID()))
						<< new QStandardItem("");
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(McurountItem);
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

/*void CreateMcurDlg::EditMulticurrency()
{
	errorMessage.clear();
	if (!numberEdit->text().isEmpty() && !currencyCmb->currentText().isEmpty() &&
		!openedDateEdit->text().isEmpty() && 0 != statusEdit->text().toInt())
	{
		if (QString(Multicurrency->GetNumber().c_str()) != numberEdit->text() || Multicurrency->GetStartBalance() != startBalanceEdit->text().toDouble()
			|| Multicurrency->GetCurrentBalance() != currentBalanceEdit->text().toDouble() || Multicurrency->GetCurrencyID() != currencyCmb->currentData().toInt()
			|| Multicurrency->GetStatusID() != statusEdit->text().toInt() || QString(Multicurrency->GetOpenedDate().c_str()) != openedDateEdit->text()
			|| QString(Multicurrency->GetDetails().c_str()) != detailsEdit->text())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetMulticurrencyParams(numberEdit->text(), startBalanceEdit->text().toDouble(), currentBalanceEdit->text().toDouble(),
				currencyCmb->currentData().toInt(), statusEdit->text().toInt(),
				openedDateEdit->text(), "", detailsEdit->text(), Multicurrency->GetID());
			int parAccID = GetParentAccNumber(numberEdit->text().toStdString());
			if (0 == parAccID)
				return;
			Multicurrency->SetParentAccountID(parAccID);
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateMulticurrency(Multicurrency, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::ChartOfAccounts *coMcur = new BusinessLayer::ChartOfAccounts;
						if (!coMcur->GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), chartOfAccEdit->text().toInt(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete coMcur;
							return;
						}

						BusinessLayer::Status *status = new BusinessLayer::Status;
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						BusinessLayer::Account *account = new BusinessLayer::Account;
						if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), Multicurrency->GetStatusID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), Multicurrency->GetCurrencyID(), errorMessage)
							|| !account->GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), coMcur->GetNumber(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete currency;
							delete status;
							delete account;
							delete coMcur;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(QString::number(account->GetID()));
						itemModel->item(mIndex.row(), 2)->setText(account->GetNumber().c_str());
						itemModel->item(mIndex.row(), 3)->setText(Multicurrency->GetNumber().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(Multicurrency->GetStartBalance()));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(Multicurrency->GetCurrentBalance()));
						itemModel->item(mIndex.row(), 6)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 8)->setText(QString::number(Multicurrency->GetCurrencyID()));
						itemModel->item(mIndex.row(), 9)->setText(QString::number(Multicurrency->GetStatusID()));
						itemModel->item(mIndex.row(), 10)->setText(Multicurrency->GetOpenedDate().c_str());
						itemModel->item(mIndex.row(), 11)->setText(Multicurrency->GetClosedDate().c_str());
						itemModel->item(mIndex.row(), 12)->setText(Multicurrency->GetDetails().c_str());
						emit itemModel->dataChanged(mIndex, mIndex);
						delete currency;
						delete status;
						delete account;
						delete coMcur;
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
}*/

void CreateMcurDlg::Close()
{
	this->parentWidget()->close();
}

void CreateMcurDlg::OpenStsDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
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
		QString message = tr("All status are shown");
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

void CreateMcurDlg::OpenCOADlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Chart of Accounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ChartOfAccountsView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("chartOfAccountForm");
		dForm->QtConnect<BusinessLayer::ChartOfAccountsView>();
		QMdiSubWindow *coMcurWindow = new QMdiSubWindow;
		coMcurWindow->setWidget(dForm);
		coMcurWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(coMcurWindow);
		coMcurWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("Chart of Accounts are shown");
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

void CreateMcurDlg::SortTable(QTableView *table)
{
	BusinessLayer::Currency currency;
	int mainTraeID = currency.GetMainTradeCurrencyID(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	currency.Clear();
	if (!currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainTraeID, errorMessage))
		return;
	for (int i = 0; i < table->model()->rowCount(); i++)
	{
		QModelIndex index = table->model()->index(i, 3);
		if (QString(index.data().toString().toStdString().substr(5, 3).c_str()) == QString::number(currency.GetCode()))
		{
			table->showRow(i);
			continue;
		}
		else
		{
			table->hideRow(i);
		}
	}
	errorMessage = "";
}


void CreateMcurDlg::OpenSAccDlg()
{
	BusinessLayer::Multicurrency mult;
	std::vector<int> exchSubID = mult.GetAllExchSubaccountID(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	mult.Clear();
	std::vector<int> mainSubID = mult.GetAllMainSubaccountID(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (mainSubID.size()>0)
		exchSubID.insert(exchSubID.end(), mainSubID.begin(), mainSubID.end());
	BusinessLayer::Subaccount subacc;
	std::string filter = "";
	filter = subacc.GenerateNotINFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), exchSubID);

	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Subccounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::SubaccountView>(errorMessage, filter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("subaccountForm");
		dForm->QtConnect<BusinessLayer::SubaccountView>();
		QMdiSubWindow *dSAccountWindow = new QMdiSubWindow;
		dSAccountWindow->setWidget(dForm);
		dSAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(dSAccountWindow);
		dSAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		SortTable(dForm->tableView);
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

void CreateMcurDlg::InitComboBox()
{
	BusinessLayer::Currency mainCur;
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
		if (!curVector.empty())
		{
			for (unsigned int i = 0; i < curVector.size(); i++)
			{
				if (curVector[i].GetMainTrade() != true)
				{
					subCurrencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
					currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
				}
			}
		}
	
}

void CreateMcurDlg::TextEditChanged()
{
	if (startBalanceEdit->text().contains(","))
	{
		startBalanceEdit->setText(startBalanceEdit->text().replace(",", "."));
	}
	if (startBalanceEdit->text().contains(".."))
	{
		startBalanceEdit->setText(startBalanceEdit->text().replace("..", "."));
	}
	if (currentBalanceEdit->text().contains(","))
	{
		currentBalanceEdit->setText(currentBalanceEdit->text().replace(",", "."));
	}
	if (currentBalanceEdit->text().contains(".."))
	{
		currentBalanceEdit->setText(currentBalanceEdit->text().replace("..", "."));
	}
	if (newStartBalanceEdit->text().contains(","))
	{
		newStartBalanceEdit->setText(newStartBalanceEdit->text().replace(",", "."));
	}
	if (newStartBalanceEdit->text().contains(".."))
	{
		newStartBalanceEdit->setText(newStartBalanceEdit->text().replace("..", "."));
	}
	if (newCurrentBalanceEdit->text().contains(","))
	{
		newCurrentBalanceEdit->setText(newCurrentBalanceEdit->text().replace(",", "."));
	}
	if (newCurrentBalanceEdit->text().contains(".."))
	{
		newCurrentBalanceEdit->setText(newCurrentBalanceEdit->text().replace("..", "."));
	}
}

void CreateMcurDlg::GenerateTwoNumbers()
{
	BusinessLayer::ChartOfAccounts coAcc;
	BusinessLayer::Account account;
	BusinessLayer::Currency currency;
	BusinessLayer::Currency mainCurrency;
	if (chartOfAccEdit->text().toInt() == 0 || chartOfAccEdit->text().isEmpty())
		return;
	if (!coAcc.GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), chartOfAccEdit->text().toInt(), errorMessage))
		return;
	std::string number = coAcc.GetNumber();
	std::string numberMain = coAcc.GetNumber();

	if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), coAcc.GetNumber(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	if (!currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subCurrencyCmb->currentData().toInt(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	int mainCurID = mainCurrency.GetMainTradeCurrencyID(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	mainCurrency.Clear();
	if (mainCurID <= 0)
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	if (!mainCurrency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainCurID, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	mainCurShortNamePh->setText(mainCurrency.GetShortName().c_str());
	mainCurEdit->setText(QString::number(mainCurrency.GetID()));
	number.append(std::to_string(currency.GetCode()));
	numberMain.append(std::to_string(mainCurrency.GetCode()));
	BusinessLayer::Subaccount exchangeSub;
	BusinessLayer::Subaccount mainSub;
	std::string genAccRawNumberExch = exchangeSub.GenerateRawNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	std::string genAccRawNumberMain = mainSub.GenerateRawNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (genAccRawNumberExch.empty() || genAccRawNumberMain.empty())
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot generate account number! Please contact with Administrator!")),
			QString(tr("Ok")));
		Close();
	}
	number.append(genAccRawNumberExch);
	numberMain.append(genAccRawNumberMain);
	parentAccID = account.GetID();
	mianNumberEdit->setText(numberMain.c_str());
	subNumberEdit->setText(number.c_str());
}

void CreateMcurDlg::GenerateNumber()
{
	if (mainSubaccEdit->text().isEmpty())
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select subaccount first!")),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	BusinessLayer::Subaccount mainSub;
	if (!mainSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainSubaccEdit->text().toInt(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please select subaccount first!")),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	
	BusinessLayer::Account account;
	BusinessLayer::Currency currency;
	
	
	std::string number = mainSub.GetNumber().substr(0,5);

	if (!account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainSub.GetParentAccountID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	if (!currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyCmb->currentData().toInt(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	number.append(std::to_string(currency.GetCode()));
	std::string genAccRawNumber = mainSub.GenerateRawNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (genAccRawNumber.empty())
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot generate account number! Please contact with Administrator!")),
			QString(tr("Ok")));
		Close();
	}
	number.append(genAccRawNumber);
	parentAccID = account.GetID();
	newNumberEdit->setText(number.c_str());
}

int CreateMcurDlg::GetParentAccNumber(std::string subNumber)
{
	std::string parentNumber = subNumber.substr(0, 5);
	BusinessLayer::Account account;
	if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), parentNumber, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return 0;
	}
	return account.GetID();
}


