#include "stdafx.h"
#include "LoginForm.h"

LoginForm::LoginForm(BusinessLayer::OrmasBL *ormasBL, BusinessLayer::User* user)
{
	setupUi(this);
	messageLb->setStyleSheet("color : red");
	//iconLb->setStyleSheet("background-image: url(:/images/lock.png);");
	iconLb->setPixmap(QString::fromUtf8(":/images/lock.png"));
	loggedUser = user;
	oBL = ormasBL;
	CreateConnections(); 
}

void LoginForm::CreateConnections()
{
	QObject::connect(cancelBtn, &QPushButton::released, this, &LoginForm::Close);
	QObject::connect(okBtn, &QPushButton::released, this, &LoginForm::CheckCredentials);
}

void LoginForm::CheckCredentials()
{
	if (!oBL->IsConnected())
		Close();
	std::string errorMessage = "";
	if (userEdit->text().isEmpty() && passwordEdit->text().isEmpty())
	{
		messageLb->setText(tr("Please fill up phone and password fields!"));
	}
	if (loggedUser->GetUserByCredentials(oBL->globalVar, oBL->GetOrmasDal(), userEdit->text().toUtf8().constData(), passwordEdit->text().toUtf8().constData()))
	{
		BusinessLayer::Role *userRole = new BusinessLayer::Role();
		if (!userRole->GetRoleByID(oBL->globalVar, oBL->GetOrmasDal(), loggedUser->GetRoleID(), errorMessage))
		{
			userEdit->setText("");
			passwordEdit->setText("");
			messageLb->setText(tr("Wrong phone or password!"));
			loggedUser->Clear();
			return;
		}
		if (userRole->GetName() == "CLIENT")
		{
			userEdit->setText("");
			passwordEdit->setText("");
			messageLb->setText(tr("Wrong phone or password!"));
			loggedUser->Clear();
			return;
		}
		this->close();
	}
	else
	{
		userEdit->setText("");
		passwordEdit->setText("");
		messageLb->setText(tr("Wrong phone or password!"));
		loggedUser->Clear();
	}
}

void LoginForm::Close()
{
	this->close();
}