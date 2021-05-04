#include "stdafx.h"
#include "GenerateOneAccDlg.h"
#include "DataForm.h"

GenerateOneAcc::GenerateOneAcc(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	MainForm *mainForm = (MainForm *)this->parent();
	InitComboBox();
	vInt = new QIntValidator(0, 1000000000, this);
	chartOfAccEdit->setValidator(vInt);
	QObject::connect(generateBtn, &QPushButton::released, this, &GenerateOneAcc::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateOneAcc::Close);
	QObject::connect(chartOfAccBtn, &QPushButton::released, this, &GenerateOneAcc::OpenCOADlg);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
}

GenerateOneAcc::~GenerateOneAcc()
{
	delete subaccount;
	delete status;
	delete caRelation;
	emit CloseCreatedForms();
}

void GenerateOneAcc::SetID(int ID, QString childName)
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
				BusinessLayer::ChartOfAccounts coAcc;
				if (coAcc.GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					accNamePh->setText(coAcc.GetName().c_str());
				}
			}
		}
	}
}

void GenerateOneAcc::Generate()
{
	BusinessLayer::Currency currency;
	BusinessLayer::Account account;
	std::string number = "";
	std::string genAccRawNumber = "";

	if (!currencyCmb->currentText().isEmpty() && !currencyCmb->currentText().isEmpty() && 0 != chartOfAccEdit->text().toInt())
	{
		status->SetName("OPEN");
		std::string statusFilter = dialogBL->GenerateFilter<BusinessLayer::Status>(status);
		std::vector<BusinessLayer::Status> statusVector = dialogBL->GetAllDataForClass<BusinessLayer::Status>(errorMessage, statusFilter);
		if (0 == statusVector.size())
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Status is empty please contact with Administrator")),
				QString(tr("Ok")));
			errorMessage.clear();
			Close();
		}
		status->SetID(statusVector.at(0).GetID());

		BusinessLayer::ChartOfAccounts coAcc;
		if (!coAcc.GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), chartOfAccEdit->text().toInt(), errorMessage))
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		if (!currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyCmb->currentData().toInt(), errorMessage))
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}

		number = coAcc.GetNumber();
		
		if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), coAcc.GetNumber(), errorMessage))
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}

		number.append(std::to_string(currency.GetCode()));
		genAccRawNumber = subaccount->GenerateRawNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
		if (genAccRawNumber.empty())
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot generate account number! Please contact with Administrator!")),
				QString(tr("Ok")));
			Close();
		}
		number.append(genAccRawNumber);
		subaccount->Clear();
		subaccount->SetParentAccountID(account.GetID());
		subaccount->SetNumber(number);
		subaccount->SetStartBalance(0.0);
		subaccount->SetCurrentBalance(0.0);
		subaccount->SetCurrencyID(currencyCmb->currentData().toInt());
		subaccount->SetStatusID(status->GetID());
		subaccount->SetOpenedDate(dialogBL->GetOrmasDal().GetSystemDate());
		subaccount->SetClosedDate("");
		subaccount->SetDetails("");

		if (subaccount->CreateSubaccount(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
		{
			Close();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot generate account! Please contact with Administrator!")),
				QString(tr("Ok")));
			Close();
		}
		number = "";
		genAccRawNumber = "";
	}
	Close();
}

void GenerateOneAcc::Close()
{
	this->parentWidget()->close();
}

void GenerateOneAcc::OpenCOADlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Chart of accounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::ChartOfAccountsView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("chartOfAccountForm");
		dForm->QtConnect<BusinessLayer::ChartOfAccountsView>();
		QMdiSubWindow *coAccWindow = new QMdiSubWindow;
		coAccWindow->setWidget(dForm);
		coAccWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(coAccWindow);
		coAccWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void GenerateOneAcc::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}

	std::vector<BusinessLayer::Company> comVector = dialogBL->GetAllDataForClass<BusinessLayer::Company>(errorMessage);
	if (!comVector.empty())
	{
		for (unsigned int i = 0; i < comVector.size(); i++)
		{
			companyCmb->addItem(comVector[i].GetName().c_str(), QVariant(comVector[i].GetID()));
		}
	}
}