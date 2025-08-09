#include "stdafx.h"

#include "CreateFxdAstDlg.h"
#include "DataForm.h"

#include <map>

CreateFxdAstDlg::CreateFxdAstDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	faNameEdit->setMaxLength(200);
	factoryNumEdit->setMaxLength(30);
	developerEdit->setMaxLength(100);
	documentEdit->setMaxLength(200);
	objCharEdit->setMaxLength(400);
	conditionEdit->setMaxLength(100);
	consDateEdit->setDate(QDate::currentDate());

	locationEdit->setMaxLength(200);
	primaryCostEdit->setValidator(vDouble);
	primaryCostEdit->setMaxLength(20);
	amortizeEdit->setValidator(vDouble);
	amortizeEdit->setMaxLength(20);
	statusEdit->setValidator(vInt);
	barcodeEdit->setMaxLength(50);
	amValueEdit->setValidator(vDouble);
	primaryCostEdit->setMaxLength(20);
	
	invNumberEdit->setMaxLength(50);
	primaryEdit->setValidator(vDouble);
	primaryEdit->setMaxLength(20);
	stopEdit->setValidator(vDouble);
	stopEdit->setMaxLength(20);
	serviceLifeEdit->setValidator(vInt);

	
	specBtn->setVisible(false);
	specIDEdit->hide();
	detailsIDEdit->hide();

	accableIDEdit->setValidator(vInt);
	purEditID->setValidator(vInt);
	accIDEdit->setValidator(vInt);

	InitComboBox();
	
	//sourceGbx->hide();

	if (true == updateFlag)
	{
		accableBtn->hide();
		accountBtn->hide();
		purveyorBtn->hide();
		fAstTypeCmb->setAcceptDrops(false);
		//specGrpBox->hide();
		existSpecCxb->hide();
		newFACxb->hide();
		specBtn->hide();
		specIDEdit->hide();
		isAmChx->setEnabled(false);
		factoryNumEdit->setReadOnly(true);
		documentEdit->setReadOnly(true);
		objCharEdit->setReadOnly(true);
		conditionEdit->setReadOnly(true);
		developerEdit->setReadOnly(true);
		consDateEdit->setReadOnly(true);
		amValueEdit->setReadOnly(true);
		amortizeEdit->setReadOnly(true);
		primaryEdit->setReadOnly(true);
		stopEdit->setReadOnly(true);
		serviceLifeEdit->setReadOnly(true);
		amGrpCmb->hide();
		amTypeCmb->hide();
		divisionCmb->hide();
		fAstTypeCmb->hide();
		amGroupLb->hide();
		amTypeLb->hide();
		depLb->hide();
		endDateEdit->setReadOnly(true);
		startDateEdit->setReadOnly(true);
		buyDateEdit->setReadOnly(true);
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateFxdAstDlg::EditFixedAssets);
	}
	else
	{
		buyDateEdit->setDate(QDate::currentDate());
		startDateEdit->setDate(QDate::currentDate());
		GenerateInventoryNumber();
		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("IN STOCK");
		std::string statusFilter = dialogBL->GenerateFilter<BusinessLayer::Status>(status);
		std::vector<BusinessLayer::Status> statusVector = dialogBL->GetAllDataForClass<BusinessLayer::Status>(errorMessage, statusFilter);
		delete status;
		if (statusVector.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Status are empty please contact with Admin")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		statusEdit->setText(QString::number(statusVector.at(0).GetID()));
		QObject::connect(okBtn, &QPushButton::released, this, &CreateFxdAstDlg::CreateFixedAssets);
		QObject::connect(divisionCmb, &QComboBox::currentTextChanged, this, &CreateFxdAstDlg::GenerateInventoryNumber);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateFxdAstDlg::Close);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateFxdAstDlg::OpenStsDlg);
	QObject::connect(accableBtn, &QPushButton::released, this, &CreateFxdAstDlg::OpenActDlg);
	QObject::connect(purveyorBtn, &QPushButton::released, this, &CreateFxdAstDlg::OpenPurDlg);
	QObject::connect(accountBtn, &QPushButton::released, this, &CreateFxdAstDlg::OpenAccDlg);
	QObject::connect(specBtn, &QPushButton::released, this, &CreateFxdAstDlg::OpenSpecDlg);
	QObject::connect(primaryCostEdit, &QLineEdit::textChanged, this, &CreateFxdAstDlg::TextEditChanged);
	QObject::connect(amortizeEdit, &QLineEdit::textChanged, this, &CreateFxdAstDlg::TextEditChanged);
	QObject::connect(primaryEdit, &QLineEdit::textChanged, this, &CreateFxdAstDlg::TextEditChanged);
	QObject::connect(amValueEdit, &QLineEdit::textChanged, this, &CreateFxdAstDlg::CalculateMonthChanged);
	QObject::connect(primaryEdit, &QLineEdit::textChanged, this, &CreateFxdAstDlg::CalculateMonthChanged);
	QObject::connect(existSpecCxb, &QCheckBox::released, this, &CreateFxdAstDlg::HideSpecButton);
	QObject::connect(newFACxb, &QCheckBox::released, this, &CreateFxdAstDlg::HideSpecButton);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	
}

CreateFxdAstDlg::~CreateFxdAstDlg()
{
	delete vDouble;
	delete vInt;
	emit CloseCreatedForms();

}

void CreateFxdAstDlg::SetFixedAssetsSpecificationParams(QString faName, QString factoryNumber, QString fDeveloper, QString fDocument, QString objChar,
	QString fConditionint, QString conDate, int id)
{
	fixedAssetsSpecification->SetName(faName.toUtf8().constData());
	fixedAssetsSpecification->SetFactoryNumber(factoryNumber.toUtf8().constData());
	fixedAssetsSpecification->SetDeveloper(fDeveloper.toUtf8().constData());
	fixedAssetsSpecification->SetDocument(fDocument.toUtf8().constData());
	fixedAssetsSpecification->SetObjectCharacters(objChar.toUtf8().constData());
	fixedAssetsSpecification->SetCondition(fConditionint.toUtf8().constData());
	fixedAssetsSpecification->SetDateOfConstruction(conDate.toUtf8().constData());
	fixedAssetsSpecification->SetID(id);
}

void CreateFxdAstDlg::SetFixedAssetsDetailsParams(int amGroupID, int amTypeID, int depID, QString fLocation, int primID, int amID,
	QString fBarcode, double amotValue, int id)
{
	fixedAssetsDetails->SetAmortizeGroupID(amGroupID);
	fixedAssetsDetails->SetAmortizeTypeID(amTypeID);
	fixedAssetsDetails->SetDepartmentID(depID);
	fixedAssetsDetails->SetFixedAssetsLocation(fLocation.toUtf8().constData());
	fixedAssetsDetails->SetPrimaryCostAccountID(primID);
	fixedAssetsDetails->SetAmortizeAccountID(amID);
	fixedAssetsDetails->SetBarcodeNumber(fBarcode.toUtf8().constData());
	fixedAssetsDetails->SetAmortizeValue(amotValue);
	fixedAssetsDetails->SetID(id);
}

void CreateFxdAstDlg::SetFixedAssetsParams(int specID, QString invNumber, double primCost, double stopCost, int servLife, QString isAmor,
	QString buyDate, QString sartOfOperDate, QString endOfOperDate, int statID, int fxID, int id)
{
	fixedAssets->SetSpecificationID(specID);
	fixedAssets->SetInventoryNumber(invNumber.toUtf8().constData());
	fixedAssets->SetPrimaryCost(primCost);
	fixedAssets->SetStopCost(stopCost);
	fixedAssets->SetServiceLife(servLife);
	fixedAssets->SetIsAmortize(isAmor == "true" ? true : false);
	fixedAssets->SetBuyDate(buyDate.toUtf8().constData());
	fixedAssets->SetStartOfOperationDate(sartOfOperDate.toUtf8().constData());
	fixedAssets->SetEndOfOperationDate(endOfOperDate.toUtf8().constData());
	fixedAssets->SetStatusID(statID);
	fixedAssets->SetFixedAssetsDetailsID(fxID);
	fixedAssets->SetID(id);
}

void CreateFxdAstDlg::SetPostingFixedAssetsParams(int userID, int subaccID, int accID, int fxID, int invID, int id)
{
	postingFixedAssets->SetUserID(userID);
	postingFixedAssets->SetSubaccountID(subaccID);
	postingFixedAssets->SetAccountID(accID);
	postingFixedAssets->SetFixedAssetsID(fxID);
	postingFixedAssets->SetInventoryID(invID);
	postingFixedAssets->SetID(id);
}

void CreateFxdAstDlg::SetFixedAssetsUnionParams(BusinessLayer::FixedAssets* fa, BusinessLayer::FixedAssetsSpecification* fas, BusinessLayer::FixedAssetsDetails* fad, BusinessLayer::PostingFixedAssets* pfa)
{
	fixedAssetsUnion->SetFixedAssets(fa);
	fixedAssetsUnion->SetFixedAssetsSpecification(fas);
	fixedAssetsUnion->SetFixedAssetsDetails(fad);
	fixedAssetsUnion->SetPostingFixedAssets(pfa);
}

void CreateFxdAstDlg::FillEditElements(int specID, QString invNumber, double primCost, double stopCost, int servLife, QString isAmor,
	QString buyDate, QString sartOfOperDate, QString endOfOperDate, int statID, int fxDetID, int faID)
{
	specIDEdit->setText(QString::number(specID));
	if (fixedAssetsSpecification->GetFixedAssetsSpecificationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), specID, errorMessage))
	{
		faNameEdit->setText(fixedAssetsSpecification->GetName().c_str());
		factoryNumEdit->setText(fixedAssetsSpecification->GetFactoryNumber().c_str());
		developerEdit->setText(fixedAssetsSpecification->GetDeveloper().c_str());
		documentEdit->setText(fixedAssetsSpecification->GetDocument().c_str());
		objCharEdit->setText(fixedAssetsSpecification->GetObjectCharacters().c_str());
		conditionEdit->setText(fixedAssetsSpecification->GetCondition().c_str());
		consDateEdit->setDate(QDate::fromString(fixedAssetsSpecification->GetDateOfConstruction().c_str(), "dd.MM.yyyy"));
	}
	detailsIDEdit->setText(QString::number(fxDetID));
	if (fixedAssetsDetails->GetFixedAssetsDetailsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fxDetID, errorMessage))
	{
		amGrpCmb->setCurrentIndex(amGrpCmb->findData(QVariant(fixedAssetsDetails->GetAmortizeGroupID())));
		amTypeCmb->setCurrentIndex(amTypeCmb->findData(QVariant(fixedAssetsDetails->GetAmortizeTypeID())));
		divisionCmb->setCurrentIndex(divisionCmb->findData(QVariant(fixedAssetsDetails->GetDepartmentID())));
		locationEdit->setText(fixedAssetsDetails->GetFixedAssetsLocation().c_str());
		BusinessLayer::Subaccount priSub;
		BusinessLayer::Subaccount amorSub;
		if (priSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssetsDetails->GetPrimaryCostAccountID(), errorMessage))
		{
			primaryCostEdit->setText(QString::number(priSub.GetCurrentBalance(),'f', 3));
			fAstTypeCmb->setCurrentIndex(fAstTypeCmb->findData(QVariant(priSub.GetParentAccountID())));
		}
		if (amorSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssetsDetails->GetAmortizeAccountID(), errorMessage))
		{
			primaryCostEdit->setText(QString::number(amorSub.GetCurrentBalance(), 'f', 3));
		}
		barcodeEdit->setText(fixedAssetsDetails->GetBarcodeNumber().c_str());
		amValueEdit->setText(QString::number(fixedAssetsDetails->GetAmortizeValue(), 'f', 3));
	}

	if (postingFixedAssets->GetPostingFixedAssetsByFixedAssetsID(dialogBL->globalVar, dialogBL->GetOrmasDal(), faID, errorMessage))
	{
		if (postingFixedAssets->GetAccountID() > 0)
		{
			accIDEdit->setText(QString::number(postingFixedAssets->GetAccountID()));
			BusinessLayer::ChartOfAccounts coa;
			BusinessLayer::Account acc;
			if (acc.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), postingFixedAssets->GetAccountID(), errorMessage))
			{
				if (coa.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), acc.GetNumber(), errorMessage))
				{
					surnameLb->setText("");
					accountName->setText(coa.GetName().c_str());
					accableIDEdit->hide();
					accableIDEdit->setText("");
					purEditID->hide();
					purEditID->setText("");
					surLb->hide();
				}
			}
		}
		if (postingFixedAssets->GetUserID() > 0)
		{
			purEditID->setText(QString::number(postingFixedAssets->GetUserID()));
			BusinessLayer::User user;
			if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), postingFixedAssets->GetUserID(), errorMessage))
			{
				surnameLb->setText(user.GetSurname().c_str());
				accableIDEdit->hide();
				accableIDEdit->setText("");
				accLB->hide();
				accountName->hide();
				accIDEdit->hide();
				accIDEdit->setText("");
			}
		}
		if (postingFixedAssets->GetSubaccountID() > 0)
		{
			BusinessLayer::Balance balance;
			if (balance.GetBalanceBySubaccountID(dialogBL->globalVar, dialogBL->GetOrmasDal(), postingFixedAssets->GetSubaccountID(), errorMessage))
			{
				accableIDEdit->setText(QString::number(balance.GetUserID()));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance.GetUserID(), errorMessage))
				{
					surnameLb->setText(user.GetSurname().c_str());
					purEditID->hide();
					purEditID->setText("");
					accLB->hide();
					accountName->hide();
					accIDEdit->hide();
					accIDEdit->setText("");
				}
			}
		}
	}

	invNumberEdit->setText(invNumber);
	primaryEdit->setText(QString::number(primCost, 'f', 3));
	stopEdit->setText(QString::number(stopCost, 'f', 3));
	serviceLifeEdit->setText(QString::number(servLife));
	if (isAmor.toStdString().compare("true") == 0)
	{
		isAmChx->setCheckState(Qt::Checked);
	}
	else
	{
		isAmChx->setCheckState(Qt::Unchecked);
	}
	buyDateEdit->setDate(QDate::fromString(buyDate, "dd.MM.yyyy"));
	startDateEdit->setDate(QDate::fromString(sartOfOperDate, "dd.MM.yyyy"));
	endDateEdit->setDate(QDate::fromString(endOfOperDate, "dd.MM.yyyy"));
	statusEdit->setText(QString::number(statID));
}

void CreateFxdAstDlg::SetID(int ID, QString childName)
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

			if (childName == QString("statusForm"))
			{
				statusEdit->setText(QString::number(ID));
			}
			if (childName == QString("purveyorForm"))
			{
				purEditID->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					accountName->setText("");
					surnameLb->setText(user.GetSurname().c_str());
				}
			}
			if (childName == QString("accountableForm"))
			{
				accableIDEdit->setText(QString::number(ID));
				BusinessLayer::Accountable accountable;
				if (accountable.GetAccountableByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					BusinessLayer::User user;
					if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountable.GetEmployeeID(), errorMessage))
					{
						accountName->setText("");
						surnameLb->setText(user.GetSurname().c_str());
					}
				}
			}
			if (childName == QString("accountForm"))
			{
				accIDEdit->setText(QString::number(ID));
				BusinessLayer::Account account;
				if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					BusinessLayer::ChartOfAccounts coA;
					if (coA.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), account.GetNumber(), errorMessage))
					{
						surnameLb->setText("");
						accountName->setText(coA.GetName().c_str());
					}
				}
			}
			if (childName == QString("specificationForm"))
			{
				specIDEdit->setText(QString::number(ID));
				BusinessLayer::FixedAssetsSpecification spec;
				if (spec.GetFixedAssetsSpecificationByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					faNameEdit->setText(spec.GetName().c_str());
					factoryNumEdit->setText(spec.GetFactoryNumber().c_str());
					documentEdit->setText(spec.GetFactoryNumber().c_str());
					objCharEdit->setText(spec.GetObjectCharacters().c_str());
					conditionEdit->setText(spec.GetCondition().c_str());
					developerEdit->setText(spec.GetDeveloper().c_str());
					consDateEdit->setDate(QDate::fromString(spec.GetDateOfConstruction().c_str(), "dd.MM.yyyy"));
				}
			}
		}
	}
}

bool CreateFxdAstDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetFixedAssetsParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 14)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 9)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 13)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 15)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 16)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 14)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 3)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toDouble(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 9)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 13)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 15)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 16)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateFxdAstDlg::CreateFixedAssets()
{
	errorMessage.clear();
	if (0 == primaryCostEdit->text().toInt())
		primaryCostEdit->setText(primaryEdit->text());
	if (!faNameEdit->text().isEmpty() && !invNumberEdit->text().isEmpty() && !locationEdit->text().isEmpty() && 0 != amValueEdit->text().toDouble() && 0 != primaryEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !amGrpCmb->currentText().isEmpty() && !amTypeCmb->currentText().isEmpty()
		&& !divisionCmb->currentText().isEmpty() && 0 != serviceLifeEdit->text().toInt())
	{
		if (newFACxb->isChecked())
		{
			if (0 == accableIDEdit->text().toInt() && 0 == purEditID->text().toInt() && 0 == accIDEdit->text().toInt())
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Please recheck all fields, accountable ID, purveyor ID or account ID!")),
					QString(tr("Ok")));
				return;
			}
		}
		dialogBL->StartIsolatedTransaction(errorMessage);
		SetFixedAssetsSpecificationParams(faNameEdit->text(), factoryNumEdit->text(), developerEdit->text(), documentEdit->text(),
			objCharEdit->text(), conditionEdit->text(), consDateEdit->text());
		
		SetFixedAssetsDetailsParams(amGrpCmb->currentData().toInt(), amTypeCmb->currentData().toInt(), divisionCmb->currentData().toInt(),
			locationEdit->text(), 0, 0, barcodeEdit->text(),
			amValueEdit->text().toDouble());
		
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetFixedAssetsParams(fixedAssetsSpecification->GetID(), invNumberEdit->text(), primaryEdit->text().toDouble(), stopEdit->text().toDouble(), 
			serviceLifeEdit->text().toInt(), isAmChx->isChecked() ? "true" : "false", buyDateEdit->text(), 
			startDateEdit->text(), "", statusEdit->text().toInt(), fixedAssetsDetails->GetID());
		fixedAssetsUnion->isNewFixedAssets = newFACxb->isChecked();
		fixedAssetsUnion->amortizeValue = amortizeEdit->text().toDouble();
		fixedAssetsUnion->primaryValue = primaryCostEdit->text().toDouble();
		fixedAssetsUnion->fixedAssetsAccountID = fAstTypeCmb->currentData().toInt();
		fixedAssetsUnion->purveyorID = purEditID->text().toInt();
		fixedAssetsUnion->accountableID = accableIDEdit->text().toInt();
		fixedAssetsUnion->accountID = accIDEdit->text().toInt();
		SetFixedAssetsUnionParams(fixedAssets, fixedAssetsSpecification, fixedAssetsDetails, postingFixedAssets);
		if (dialogBL->CreateFixedAssetsUnion(fixedAssetsUnion, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssets->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					BusinessLayer::Subaccount priSub;
					BusinessLayer::Subaccount amorSub;
					if (!priSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssetsDetails->GetPrimaryCostAccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					if (!amorSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssetsDetails->GetAmortizeAccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					BusinessLayer::Division division;
					if (!division.GetDivisionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssetsDetails->GetDepartmentID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete status;
						return;
					}
					QList<QStandardItem*> fixedAssetsItem;
					fixedAssetsItem << new QStandardItem(QString::number(fixedAssets->GetID()))
						<< new QStandardItem(fixedAssetsSpecification->GetName().c_str())
						<< new QStandardItem(fixedAssets->GetInventoryNumber().c_str())
						<< new QStandardItem(QString::number(fixedAssets->GetPrimaryCost(), 'f', 3))
						<< new QStandardItem(QString::number(fixedAssets->GetStopCost(), 'f', 3))
						<< new QStandardItem(QString::number(priSub.GetCurrentBalance(), 'f', 3))
						<< new QStandardItem(QString::number(amorSub.GetCurrentBalance(), 'f', 3))
						<< new QStandardItem(division.GetName().c_str())
						<< new QStandardItem(status->GetName().c_str())
						<< new QStandardItem(QString::number(fixedAssets->GetServiceLife()))
						<< new QStandardItem(fixedAssets->GetIsAmortize() ? "true" : "false")
						<< new QStandardItem(fixedAssets->GetBuyDate().c_str())
						<< new QStandardItem(fixedAssets->GetStartOfOperationDate().c_str())
						<< new QStandardItem(fixedAssets->GetEndOfOperationDate().c_str())
						<< new QStandardItem(QString::number(fixedAssets->GetSpecificationID()))
						<< new QStandardItem(QString::number(fixedAssets->GetStatusID()))
						<< new QStandardItem(QString::number(fixedAssets->GetFixedAssetsDetailsID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(fixedAssetsItem);

					delete status;
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
			QString(tr("Please recheck all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateFxdAstDlg::EditFixedAssets()
{
	errorMessage.clear();
	if (!faNameEdit->text().isEmpty() && !locationEdit->text().isEmpty() && !invNumberEdit->text().isEmpty() && 0 != amValueEdit->text().toDouble() && 0 != primaryEdit->text().toDouble()
		&& 0 != statusEdit->text().toInt() && !amGrpCmb->currentText().isEmpty() && !amTypeCmb->currentText().isEmpty()
		&& !divisionCmb->currentText().isEmpty() && 0 != serviceLifeEdit->text().toInt())
	{
		if (faNameEdit->text() != QString(fixedAssetsSpecification->GetName().c_str()) || barcodeEdit->text() != QString(fixedAssetsDetails->GetBarcodeNumber().c_str())
			|| locationEdit->text() != QString(fixedAssetsDetails->GetFixedAssetsLocation().c_str())
			|| statusEdit->text().toInt() != fixedAssets->GetStatusID())
		{
			dialogBL->StartIsolatedTransaction(errorMessage);
			DataForm *parentDataForm = (DataForm*)parentForm;
			BusinessLayer::Status sts;

			if (faNameEdit->text() != QString(fixedAssetsSpecification->GetName().c_str()))
			{
				fixedAssetsSpecification->SetName(faNameEdit->text().toUtf8().constData());
			}
			if (barcodeEdit->text() != QString(fixedAssetsDetails->GetBarcodeNumber().c_str()) || locationEdit->text() != QString(fixedAssetsDetails->GetFixedAssetsLocation().c_str()))
			{
				fixedAssetsDetails->SetBarcodeNumber(barcodeEdit->text().toUtf8().constData());
				fixedAssetsDetails->SetFixedAssetsLocation(locationEdit->text().toUtf8().constData());
			}
			if (!sts.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "WRITE-OFFED", errorMessage))
			{
				return;
			}
			if (fixedAssets->GetStatusID() == sts.GetID())
			{
				SetFixedAssetsParams(fixedAssetsSpecification->GetID(), invNumberEdit->text(), primaryEdit->text().toDouble(), stopEdit->text().toDouble(),
					serviceLifeEdit->text().toInt(), isAmChx->isChecked() ? "true" : "false", buyDateEdit->text(),
					startDateEdit->text(), dialogBL->GetOrmasDal().GetSystemDate().c_str(), statusEdit->text().toInt(), fixedAssetsDetails->GetID(), fixedAssets->GetID());
			}
			else
			{
				SetFixedAssetsParams(fixedAssetsSpecification->GetID(), invNumberEdit->text(), primaryEdit->text().toDouble(), stopEdit->text().toDouble(),
					serviceLifeEdit->text().toInt(), isAmChx->isChecked() ? "true" : "false", buyDateEdit->text(),
					startDateEdit->text(), "", statusEdit->text().toInt(), fixedAssetsDetails->GetID(), fixedAssets->GetID());
			}
			if (accableIDEdit->text().isEmpty() && purEditID->text().isEmpty() && accIDEdit->text().isEmpty())
			{
				fixedAssetsUnion->isNewFixedAssets = false;
			}
			else
			{
				fixedAssetsUnion->isNewFixedAssets = true;
			}
			fixedAssetsUnion->amortizeValue = amortizeEdit->text().toDouble();
			fixedAssetsUnion->primaryValue = primaryCostEdit->text().toDouble();
			fixedAssetsUnion->fixedAssetsAccountID = fAstTypeCmb->currentData().toInt();
			fixedAssetsUnion->purveyorID = purEditID->text().toInt();
			fixedAssetsUnion->accountableID = accableIDEdit->text().toInt();
			fixedAssetsUnion->accountID = accIDEdit->text().toInt();
			SetFixedAssetsUnionParams(fixedAssets, fixedAssetsSpecification, fixedAssetsDetails, postingFixedAssets);
			if (dialogBL->UpdateFixedAssetsUnion(fixedAssetsUnion, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Status *status = new BusinessLayer::Status;
						if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssets->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete status;
							return;
						}
						BusinessLayer::Subaccount priSub;
						BusinessLayer::Subaccount amorSub;
						if (!priSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssetsDetails->GetPrimaryCostAccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete status;
							return;
						}
						if (!amorSub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssetsDetails->GetAmortizeAccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete status;
							return;
						}
						BusinessLayer::Division division;
						if (!division.GetDivisionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), fixedAssetsDetails->GetDepartmentID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete status;
							return;
						}
						//updating FixedAssets data
						itemModel->item(mIndex.row(), 1)->setText(fixedAssetsSpecification->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(fixedAssets->GetInventoryNumber().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(fixedAssets->GetPrimaryCost(), 'f', 3));
						itemModel->item(mIndex.row(), 4)->setText(QString::number(fixedAssets->GetStopCost(), 'f', 3));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(priSub.GetCurrentBalance(), 'f', 3));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(amorSub.GetCurrentBalance(), 'f', 3));
						itemModel->item(mIndex.row(), 7)->setText(division.GetName().c_str());
						itemModel->item(mIndex.row(), 8)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 9)->setText(QString::number(fixedAssets->GetServiceLife()));
						itemModel->item(mIndex.row(), 10)->setText(fixedAssets->GetIsAmortize()?"true":"false");
						itemModel->item(mIndex.row(), 11)->setText(fixedAssets->GetBuyDate().c_str());
						itemModel->item(mIndex.row(), 12)->setText(fixedAssets->GetStartOfOperationDate().c_str());
						itemModel->item(mIndex.row(), 13)->setText(fixedAssets->GetEndOfOperationDate().c_str());
						itemModel->item(mIndex.row(), 14)->setText(QString::number(fixedAssets->GetSpecificationID()));
						itemModel->item(mIndex.row(), 15)->setText(QString::number(fixedAssets->GetStatusID()));
						itemModel->item(mIndex.row(), 16)->setText(QString::number(fixedAssets->GetFixedAssetsDetailsID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete status;
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

void CreateFxdAstDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateFxdAstDlg::OpenStsDlg()
{
	errorMessage.clear();
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

void CreateFxdAstDlg::OpenSpecDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Fixed assets specification"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::FixedAssetsSpecification>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("specificationForm");
		dForm->QtConnect<BusinessLayer::FixedAssetsSpecification>();
		QMdiSubWindow *specWindow = new QMdiSubWindow;
		specWindow->setWidget(dForm);
		specWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(specWindow);
		specWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All specifications are shown");
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

void CreateFxdAstDlg::OpenAccDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Account"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::Account>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accountForm");
		dForm->QtConnect<BusinessLayer::Account>();
		QMdiSubWindow *accWindow = new QMdiSubWindow;
		accWindow->setWidget(dForm);
		accWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(accWindow);
		accWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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

void CreateFxdAstDlg::OpenPurDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Purveyors"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	BusinessLayer::Role *role = new BusinessLayer::Role();
	role->SetName("PURVEYOR");
	std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
	std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);

	if (roleVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not define the role for this purveyor!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	dForm->FillTable<BusinessLayer::PurveyorView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("purveyorForm");
		dForm->QtConnect<BusinessLayer::PurveyorView>();
		QMdiSubWindow *purveyorWindow = new QMdiSubWindow;
		purveyorWindow->setWidget(dForm);
		purveyorWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(purveyorWindow);
		purveyorWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All purveyors are shown");
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

void CreateFxdAstDlg::OpenActDlg()
{
	errorMessage.clear();
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Accountable"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::AccountableView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accountableForm");
		dForm->QtConnect<BusinessLayer::AccountableView>();
		QMdiSubWindow *accblWindow = new QMdiSubWindow;
		accblWindow->setWidget(dForm);
		accblWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(accblWindow);
		accblWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All accountable are shown");
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

void CreateFxdAstDlg::InitComboBox()
{
	std::vector<BusinessLayer::Division> curDivision = dialogBL->GetAllDataForClass<BusinessLayer::Division>(errorMessage);
	if (!curDivision.empty())
	{
		for (unsigned int i = 0; i < curDivision.size(); i++)
		{
			divisionCmb->addItem(curDivision[i].GetName().c_str(), QVariant(curDivision[i].GetID()));
		}
	}
	std::vector<BusinessLayer::AmortizeType> curAmType = dialogBL->GetAllDataForClass<BusinessLayer::AmortizeType>(errorMessage);
	if (!curAmType.empty())
	{
		for (unsigned int i = 0; i < curAmType.size(); i++)
		{
			amTypeCmb->addItem(curAmType[i].GetName().c_str(), QVariant(curAmType[i].GetID()));
		}
	}
	std::vector<BusinessLayer::AmortizeGroup> curAmGroup = dialogBL->GetAllDataForClass<BusinessLayer::AmortizeGroup>(errorMessage);
	if (!curAmGroup.empty())
	{
		for (unsigned int i = 0; i < curAmGroup.size(); i++)
		{
			amGrpCmb->addItem(QString::number(curAmGroup[i].GetGroupNumber()), QVariant(curAmGroup[i].GetID()));
		}
	}
	std::vector<BusinessLayer::Account> accGroup = dialogBL->GetAllDataForClass<BusinessLayer::Account>(errorMessage);
	if (!accGroup.empty())
	{
		BusinessLayer::ChartOfAccounts coAcc;
		for (unsigned int i = 0; i < accGroup.size(); i++)
		{
			if (accGroup[i].GetNumber().substr(0, 3).compare("110")==0)
			{
				if (accGroup[i].GetNumber().substr(0, 5).compare("11000") != 0)
				{
					coAcc.Clear();
					if (coAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), accGroup[i].GetNumber(), errorMessage))
					{
						fAstTypeCmb->addItem(coAcc.GetName().c_str(), QVariant(accGroup[i].GetID()));
					}
				}
			}
		}
	}
}

void CreateFxdAstDlg::HideSpecButton()
{
	if (existSpecCxb->isChecked())
	{
		specBtn->setVisible(true);
		specIDEdit->show();
	}
	else
	{
		specIDEdit->hide();
		specBtn->setVisible(false);
		specIDEdit->setText("");
	}
	if (newFACxb->isChecked())
	{
		BusinessLayer::Status status;
		if (status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "IN STOCK", errorMessage))
			statusEdit->setText(QString::number(status.GetID()));
		sourceGbx->show();
		amortizeEdit->setText("");
		amortizeEdit->setReadOnly(true);
	}
	else
	{
		BusinessLayer::Status status;
		if (status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "IN USE", errorMessage))
			statusEdit->setText(QString::number(status.GetID()));
		sourceGbx->hide();
		surnameLb->setText("");
		accountName->setText("");
		accableIDEdit->setText("");
		purEditID->setText("");
		accIDEdit->setText("");
		amortizeEdit->setReadOnly(false);
	}
}

void CreateFxdAstDlg::CalculateMonthChanged()
{
	double amValue = amValueEdit->text().toDouble();
	double primeValue = primaryEdit->text().toDouble();
	double monthCount = std::round(100 / amValue * 12);
	serviceLifeEdit->setText(QString::number(monthCount));
	std::vector<BusinessLayer::AmortizeGroup> curAmGroup = dialogBL->GetAllDataForClass<BusinessLayer::AmortizeGroup>(errorMessage);
	if (!curAmGroup.empty())
	{
		for (unsigned int i = 0; i < curAmGroup.size(); i++)
		{
			if (curAmGroup[i].GetFromMonth() <= monthCount || curAmGroup[i].GetToMonth() >= monthCount)
				amGrpCmb->setCurrentIndex(i);
		}
	}
	primaryCostEdit->setText(primaryEdit->text());
}

void CreateFxdAstDlg::TextEditChanged()
{
	if (primaryEdit->text().contains(","))
	{
		primaryEdit->setText(primaryEdit->text().replace(",", "."));
	}
	if (primaryEdit->text().contains(".."))
	{
		primaryEdit->setText(primaryEdit->text().replace("..", "."));
	}
	if (stopEdit->text().contains(","))
	{
		stopEdit->setText(stopEdit->text().replace(",", "."));
	}
	if (stopEdit->text().contains(".."))
	{
		stopEdit->setText(stopEdit->text().replace("..", "."));
	}
	if (amValueEdit->text().contains(","))
	{
		amValueEdit->setText(amValueEdit->text().replace(",", "."));
	}
	if (amValueEdit->text().contains(".."))
	{
		amValueEdit->setText(amValueEdit->text().replace("..", "."));
	}
	if (primaryCostEdit->text().contains(","))
	{
		primaryCostEdit->setText(primaryCostEdit->text().replace(",", "."));
	}
	if (primaryCostEdit->text().contains(".."))
	{
		primaryCostEdit->setText(primaryCostEdit->text().replace("..", "."));
	}
	if (amortizeEdit->text().contains(","))
	{
		amortizeEdit->setText(amortizeEdit->text().replace(",", "."));
	}
	if (amortizeEdit->text().contains(".."))
	{
		amortizeEdit->setText(amortizeEdit->text().replace("..", "."));
	}
}

void CreateFxdAstDlg::GenerateInventoryNumber()
{
	std::string invNumber = "";
	invNumber = fixedAssetsUnion->GenerateInventoryNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), divisionCmb->currentData().toInt());
	invNumberEdit->setText(invNumber.c_str());
}
