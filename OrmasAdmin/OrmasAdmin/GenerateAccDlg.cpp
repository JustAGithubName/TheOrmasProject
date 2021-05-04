#include "stdafx.h"
#include "GenerateAccDlg.h"
#include "MainForm.h"



GenerateAcc::GenerateAcc(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	InitComboBox();
	
	QObject::connect(generateBtn, &QPushButton::released, this, &GenerateAcc::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateAcc::Close);
}

GenerateAcc::~GenerateAcc()
{
	delete account;
	delete status;
	delete caRelation;
}

void GenerateAcc::Generate()
{
	QProgressDialog progressDialog(this);
	std::vector<BusinessLayer::ChartOfAccountsView> coaVector = dialogBL->GetAllDataForClass<BusinessLayer::ChartOfAccountsView>(errorMessage);
	if (coaVector.size() > 0)
	{
		progressDialog.setRange(0, coaVector.size());
		progressDialog.setWindowFlags(Qt::FramelessWindowHint);
		
		int i = 0;
		std::string number = "";

		dialogBL->GetOrmasDal().StartTransaction(errorMessage);
		for each (auto coaItem in coaVector)
		{
			number = coaItem.GetNumber();
			account->Clear();
			account->SetNumber(number);
			account->SetStartBalance(0.0);
			account->SetCurrentBalance(0.0);

			if (account->CreateAccount(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
			{
				caRelation->Clear();
				caRelation->SetAccountID(account->GetID());
				caRelation->SetCompanyID(companyCmb->currentData().toInt());
				if (!caRelation->CreateCompanyAccountRelation(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
				{
					QMessageBox::information(NULL, QString(tr("Info")),
						QString(tr("Cannot create relation with generated account and company! Please contact with Administrator!")),
						QString(tr("Ok")));
					dialogBL->GetOrmasDal().CancelTransaction(errorMessage);
					Close();
				}
			}
			else
			{
				QMessageBox::information(NULL, QString(tr("Info")),
					QString(tr("Cannot generate account! Please contact with Administrator!")),
					QString(tr("Ok")));
				dialogBL->GetOrmasDal().CancelTransaction(errorMessage);
				Close();
			}

			progressDialog.setValue(i);
			i++;

			number = "";
		}
		dialogBL->GetOrmasDal().CommitTransaction(errorMessage);
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("All accounts were successfully generated!")),
			QString(tr("Ok")));
		Close();
	}
}

void GenerateAcc::Close()
{
	this->parentWidget()->close();
}

void GenerateAcc::InitComboBox()
{
	std::vector<BusinessLayer::Company> comVector = dialogBL->GetAllDataForClass<BusinessLayer::Company>(errorMessage);
	if (!comVector.empty())
	{
		for (unsigned int i = 0; i < comVector.size(); i++)
		{
			companyCmb->addItem(comVector[i].GetName().c_str(), QVariant(comVector[i].GetID()));
		}
	}
}