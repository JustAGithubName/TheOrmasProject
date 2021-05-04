#include "stdafx.h"
#include "CashInfoDlg.h"

CashInfoDlg::CashInfoDlg(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	mainForm = (MainForm *)this->parent();

	BusinessLayer::CashboxEmployeeRelation ceRel;
	BusinessLayer::Cashbox cashbox;
	BusinessLayer::Subaccount subacc;
	if (ceRel.GetCashboxEmployeeByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainForm->GetLoggedUser()->GetID(), errorMessage))
	{
		if (cashbox.GetCashboxByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ceRel.GetCashboxID(), errorMessage))
		{
			if (subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashbox.GetSubaccountID(), errorMessage))
			{
				cashValueLb->setText(QString::number(subacc.GetCurrentBalance(), 'f', 3));
				cashCurLb->setText("TJS");
			}
		}
	}
	
	QObject::connect(okBtn, &QPushButton::released, this, &CashInfoDlg::Close);
	QObject::connect(cancelBtn, &QPushButton::released, this, &CashInfoDlg::Close);
}

CashInfoDlg::~CashInfoDlg()
{

}

void CashInfoDlg::Close()
{
	this->parentWidget()->close();
}

