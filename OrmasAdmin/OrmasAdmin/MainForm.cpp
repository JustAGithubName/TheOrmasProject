#include "stdafx.h"
#include "MainForm.h"
#include "DataForm.h"
#include "GenerateAccDlg.h"
#include "GenerateOneAccDlg.h"
#include "ClcWagesDlg.h"
#include "InfoForm.h"
#include "ReworkRawDlg.h"
#include "CloseOfMonthDlg.h"
#include "GenerateFinRepDlg.h"
#include "GenerateCmpBlcDlg.h"
#include "GenerateAccRepDlg.h"
#include "GenerateProfRepDlg.h"
#include "GenerateAgentRepDlg.h"
#include "GenerateComRepDlg.h"
#include "GenerateSalesRepDlg.h"
#include "GenerateSpecRepDlg.h"
#include "GenerateWrRepDlg.h"
#include "GenerateFxAstRepDlg.h"
#include "GenerateDailySalesRepDlg.h"
#include "GenerateWTBSDlg.h"
#include "CashInfoDlg.h"
#include "CashBookListDlg.h"
#include "WarehouseEmployeeRelationClass.h"
#include "WarehouseTypeClass.h"


MainForm::MainForm(BusinessLayer::OrmasBL *ormasBL, BusinessLayer::User* user)
{
	setupUi(this);
	mdiArea->cascadeSubWindows();
	QString message = tr("Ready");
	statusBar()->showMessage(message);
	oBL = ormasBL;
	userAccess = new BusinessLayer::Access();
	loggedUser = user;
	oBL->loggedUser = loggedUser;
	CreateConnections();
	rights = userAccess->GetRightsList(oBL->globalVar, &oBL->GetOrmasDal(), user);
	this->setWindowTitle("Ormas Admin Panel");
	this->setWindowTitle(this->windowTitle() + " (" + user->GetName().c_str() + "." + user->GetSurname().c_str()+ ")");
	SetMenuItemsByAccess(rights);
	//connect(mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::updateMenus);
}

BusinessLayer::User* MainForm::GetLoggedUser()
{
	return loggedUser;
}

void MainForm::SetMenuItemsByAccess(std::vector<int> rights)
{
	SetAllMenuInvisible();
	if (1 == rights.size())
	{
		if (userAccess->CheckAccess(oBL->globalVar, &oBL->GetOrmasDal(), rights.at(0), "ALL"))
		{
			SetAllMenuVisible();
			return;
		}
	}
	if (0 < rights.size())
	{
		std::string errorMessage= "";
		BusinessLayer::AccessItem item;
		for each (auto id in rights)
		{
			if (userAccess->CheckAccess(oBL->globalVar, &oBL->GetOrmasDal(), id, "MENU"))
			{
				item.Clear();
				item.GetAccessItemByID(oBL->globalVar, oBL->GetOrmasDal(), id, errorMessage);
				if (errorMessage.empty())
				{
					if(0 != this->findChild<QMenu*>(QString(item.GetNameEng().c_str())))
						this->findChild<QMenu*>(QString(item.GetNameEng().c_str()))->setEnabled(true);
				}
			}
			if (userAccess->CheckAccess(oBL->globalVar, &oBL->GetOrmasDal(), id, "MENUITEM"))
			{
				item.Clear();
				item.GetAccessItemByID(oBL->globalVar, oBL->GetOrmasDal(), id, errorMessage);
				if (errorMessage.empty())
				{
					if(0 != this->findChild<QAction*>(QString(item.GetNameEng().c_str())))
						this->findChild<QAction*>(QString(item.GetNameEng().c_str()))->setVisible(true);
					if (0 != this->findChild<QAction*>(QString(item.GetNameEng().c_str())))
					{
						QList<QWidget *> widgetList = this->findChild<QAction*>(QString(item.GetNameEng().c_str()))->associatedWidgets();
						if (widgetList.size() == 1)
							widgetList.at(0)->setEnabled(true);
					}
						
				}
			}
		}
	}
}

void MainForm::SetAllMenuInvisible()
{
	menuUsers->setEnabled(false);
	menuProducts->setEnabled(false);
	menuOrders->setEnabled(false);
	menuReturns->setEnabled(false);
	menuWriteOffs->setEnabled(false);
	menuProductions->setEnabled(false);
	menuAccountings->setEnabled(false);
	menuFixedAssets->setEnabled(false);
	menuCash->setEnabled(false);
	menuStock->setEnabled(false);
	menuReports->setEnabled(false);
	menuReferences->setEnabled(false);
	menuHelp->setEnabled(true);
	
	//actions in menu users
	actionAllUsers->setVisible(false);
	actionClients->setVisible(false);
	actionEmployees->setVisible(false);
	actionPurveyors->setVisible(false);
	actionAccountables->setVisible(false);
	actionBorrowers->setVisible(false);
	actionCreditors->setVisible(false);
	actionShareholders->setVisible(false);
	actionGroup->setVisible(false);
	actionUserGroup->setVisible(false);
	actionCompanyEmployees->setVisible(false);
	actionCashboxEmployees->setVisible(false);
	actionWarehouseEmployees->setVisible(false);
	actionAccess->setVisible(false);
	actionAccessItems->setVisible(false);
	actionUserPhoto->setVisible(false);
	actionPosition->setVisible(false);

	//actions in product menu
	actionProducts->setVisible(false);
	actionProductType->setVisible(false);
	actionProductPhoto->setVisible(false);
	actionSpecifications->setVisible(false);
	actionSpecificationList->setVisible(false);
	actionPrices->setVisible(false);
	actionNetCost->setVisible(false);
	actionEmployeeProducts->setVisible(false);
	actionBranchProducts->setVisible(false);
	actionOtherStocks->setVisible(false);
	
	//actions in menu order
	actionOrders->setVisible(false);
	actionOrderList->setVisible(false);

	//actions in menu return
 	actionReturns->setVisible(false);
	actionReturnList->setVisible(false);

	//actions in menu write-off
	actionWriteOffs->setVisible(false);
	actionWriteOffList->setVisible(false);

	//actions in menu production
	actionProduction->setVisible(false);
	actionProductionList->setVisible(false);
	actionProductionStock->setVisible(false);
	actionProductionConsumeRaws->setVisible(false);
	actionProductionPlan->setVisible(false);
	actionProductionPlanList->setVisible(false);
	actionJobprice->setVisible(false);
	actionJobsheet->setVisible(false);
	actionPercentRate->setVisible(false);
	actionTimesheet->setVisible(false);
	actionSpoilage->setVisible(false);
	actionSpoilageList->setVisible(false);
	actionReworkRaws->setVisible(false);
		
	//actions in menu fixed assets
	actionFixedAssets->setVisible(false);
	actionFixedAssetsOperation->setVisible(false);
	actionInventory->setVisible(false);
	actionAmortizeGroup->setVisible(false);
	actionAmortizeType->setVisible(false);

	//actions in menu accounting
	actionBalances->setVisible(false);
	actionAccounts->setVisible(false);
	actionSubaccounts->setVisible(false); 
	actionSubaccountLimit->setVisible(false);
	actionGenerateOneAccount->setVisible(false);
	actionGenerateAccounts->setVisible(false);
	actionSalary->setVisible(false);
	actionSalaryType->setVisible(false);
	actionPayroll->setVisible(false);
	actionAccountType->setVisible(false);
	actionBranchSubaccounts->setVisible(false);
	actionDivisionAccounts->setVisible(false);
	actionChartOfAccounts->setVisible(false);
	actionCompanyAccounts->setVisible(false);
	actionEntry->setVisible(false);
	actionEntryRouting->setVisible(false);
	actionAccountableReport->setVisible(false);
	actionCloseOfMonth->setVisible(false);
	actionWarehouse->setVisible(false);
	actionCashbox->setVisible(false);

		
	//actions in menu cash
	actionCash->setVisible(false);
	actionPayments->setVisible(false);
	actionRefund->setVisible(false);
	actionWithdrawal->setVisible(false);
	actionPayslip->setVisible(false);
	actionCashBookList->setVisible(false);

	//actions in menu stock
	actionStock->setVisible(false);
	actionStockLimit->setVisible(false);
	actionRawStock->setVisible(false);
	actionProductStock->setVisible(false);
	actionOrderRaws->setVisible(false);
	actionStockTransfers->setVisible(false);
	actionConsumptionRaws->setVisible(false);
	actionWriteOffRaws->setVisible(false);
	actionTransports->setVisible(false);
	actionReceiptProducts->setVisible(false);
	actionConsumptionProducts->setVisible(false);
	actionInventorization->setVisible(false);
	actionLowValueStock->setVisible(false);
	actionConsumeOthSt->setVisible(false);
	actionReceiptOthSt->setVisible(false);
	
	//actions in menu reports
	actionCompanyBalanceInfo->setVisible(false);
	actionFinancialReport->setVisible(false);
	actionCompanyBalance->setVisible(false);
	actionSpecificationReport->setVisible(false);
	actionProfitability->setVisible(false);
	actionSalesReport->setVisible(false);
	actionAccountCard->setVisible(false);
	actionWarehouseTurnover->setVisible(false);
	actionDailySalesReport->setVisible(false);
	actionCommonReport->setVisible(false);
	actionAgentReport->setVisible(false);
	actionFixedAssetsReport->setVisible(false);
	actionWarehouseReport->setVisible(false);

	//actions in menu reference
	actionCompany->setVisible(false);
	actionCurrency->setVisible(false);
	actionMeasure->setVisible(false);
	actionLocation->setVisible(false);
	actionRoles->setVisible(false);
	actionStatus->setVisible(false);
	actionStatusRule->setVisible(false);
	actionRelation->setVisible(false);
	actionRelationType->setVisible(false);
	actionDivision->setVisible(false);
	actionWarehouseType->setVisible(false);
	actionBranch->setVisible(false);

	//actions in menu about
	actionAbout->setVisible(true);
}

void MainForm::SetAllMenuVisible()
{
	menuUsers->setEnabled(true);
	menuProducts->setEnabled(true);
	menuOrders->setEnabled(true);
	menuReturns->setEnabled(true);
	menuWriteOffs->setEnabled(true);
	menuProductions->setEnabled(true);
	menuAccountings->setEnabled(true);
	menuFixedAssets->setEnabled(true);
	menuCash->setEnabled(true);
	menuStock->setEnabled(true);
	menuReports->setEnabled(true);
	menuReferences->setEnabled(true);
	menuHelp->setEnabled(true);

	//actions in menu users
	actionAllUsers->setVisible(true);
	actionClients->setVisible(true);
	actionEmployees->setVisible(true);
	actionPurveyors->setVisible(true);
	actionAccountables->setVisible(true);
	actionBorrowers->setVisible(true);
	actionCreditors->setVisible(true);
	actionShareholders->setVisible(true);
	actionGroup->setVisible(true);
	actionUserGroup->setVisible(true);
	actionCompanyEmployees->setVisible(true);
	actionCashboxEmployees->setVisible(true);
	actionWarehouseEmployees->setVisible(true);
	actionAccess->setVisible(true);
	actionAccessItems->setVisible(true);
	actionUserPhoto->setVisible(true);
	actionPosition->setVisible(true);

	//actions in product menu
	actionProducts->setVisible(true);
	actionProductType->setVisible(true);
	actionProductPhoto->setVisible(true);
	actionSpecifications->setVisible(true);
	actionSpecificationList->setVisible(true);
	actionPrices->setVisible(true);
	actionNetCost->setVisible(true);
	actionEmployeeProducts->setVisible(true);
	actionBranchProducts->setVisible(true);
	actionOtherStocks->setVisible(true);

	//actions in menu order
	actionOrders->setVisible(true);
	actionOrderList->setVisible(true);

	//actions in menu return
	actionReturns->setVisible(true);
	actionReturnList->setVisible(true);

	//actions in menu write-off
	actionWriteOffs->setVisible(true);
	actionWriteOffList->setVisible(true);

	//actions in menu production
	actionProduction->setVisible(true);
	actionProductionList->setVisible(true);
	actionProductionStock->setVisible(true);
	actionProductionConsumeRaws->setVisible(true);
	actionProductionPlan->setVisible(true);
	actionProductionPlanList->setVisible(true);
	actionJobprice->setVisible(true);
	actionJobsheet->setVisible(true);
	actionPercentRate->setVisible(true);
	actionTimesheet->setVisible(true);
	actionSpoilage->setVisible(true);
	actionSpoilageList->setVisible(true);
	actionReworkRaws->setVisible(true);

	//actions in menu accounting
	actionBalances->setVisible(true);
	actionAccounts->setVisible(true);
	actionSubaccounts->setVisible(true);
	actionSubaccountLimit->setVisible(true);
	actionGenerateOneAccount->setVisible(true);
	actionGenerateAccounts->setVisible(true);
	actionSalary->setVisible(true);
	actionSalaryType->setVisible(true);
	actionPayroll->setVisible(true);
	actionAccountType->setVisible(true);
	actionBranchSubaccounts->setVisible(true);
	actionDivisionAccounts->setVisible(true);
	actionChartOfAccounts->setVisible(true);
	actionCompanyAccounts->setVisible(true);
	actionEntry->setVisible(true);
	actionEntryRouting->setVisible(true);
	actionAccountableReport->setVisible(true);
	actionCloseOfMonth->setVisible(true);
	actionWarehouse->setVisible(true);
	actionCashbox->setVisible(true);

	//actions in menu fixed assets
	actionFixedAssets->setVisible(true);
	actionFixedAssetsOperation->setVisible(true);
	actionInventory->setVisible(true);
	actionAmortizeGroup->setVisible(true);
	actionAmortizeType->setVisible(true);

	//actions in menu cash
	actionCash->setVisible(true);
	actionPayments->setVisible(true);
	actionRefund->setVisible(true);
	actionWithdrawal->setVisible(true);
	actionPayslip->setVisible(true);
	actionCashBookList->setVisible(true);

	//actions in menu stock
	actionStock->setVisible(true);
	actionStockLimit->setVisible(true);
	actionRawStock->setVisible(true);
	actionProductStock->setVisible(true);
	actionOrderRaws->setVisible(true);
	actionStockTransfers->setVisible(true);
	actionConsumptionRaws->setVisible(true);
	actionWriteOffRaws->setVisible(true);
	actionTransports->setVisible(true);
	actionReceiptProducts->setVisible(true);
	actionConsumptionProducts->setVisible(true);
	actionInventorization->setVisible(true);
	actionReceiptOthSt->setVisible(true);
	actionConsumeOthSt->setVisible(true);
	actionLowValueStock->setVisible(true);

	//actions in menu reports
	actionCompanyBalanceInfo->setVisible(true);
	actionFinancialReport->setVisible(true);
	actionCompanyBalance->setVisible(true);
	actionSpecificationReport->setVisible(true);
	actionProfitability->setVisible(true);
	actionSalesReport->setVisible(true);
	actionAccountCard->setVisible(true);
	actionWarehouseTurnover->setVisible(true);
	actionDailySalesReport->setVisible(true);
	actionCommonReport->setVisible(true);
	actionAgentReport->setVisible(true);
	actionFixedAssetsReport->setVisible(true);
	actionWarehouseReport->setVisible(true);

	//actions in menu reference
	actionCompany->setVisible(true);
	actionCurrency->setVisible(true);
	actionMeasure->setVisible(true);
	actionLocation->setVisible(true);
	actionRoles->setVisible(true);
	actionStatus->setVisible(true);
	actionStatusRule->setVisible(true);
	actionRelation->setVisible(true);
	actionRelationType->setVisible(true);
	actionDivision->setVisible(true);
	actionWarehouseType->setVisible(true);
	actionBranch->setVisible(true);

	//actions in menu about
	actionAbout->setVisible(true);
}

MainForm::~MainForm()
{
	delete loggedUser;
	delete userAccess;
}

void MainForm::CloseChildsByName()
{
	if (0 != this->findChild<QWidget*>("consumeProductListForm"))
		((DataForm*)this->findChild<QWidget*>("consumeProductListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("consumeRawListForm"))
		((DataForm*)this->findChild<QWidget*>("consumeRawListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("inventorizationListForm"))
		((DataForm*)this->findChild<QWidget*>("inventorizationListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("orderListForm"))
		((DataForm*)this->findChild<QWidget*>("orderListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("orderRawListForm"))
		((DataForm*)this->findChild<QWidget*>("orderRawListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("productionPlanListForm"))
		((DataForm*)this->findChild<QWidget*>("productionPlanListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("receiptProductListForm"))
		((DataForm*)this->findChild<QWidget*>("receiptProductListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("StockTransferListForm"))
		((DataForm*)this->findChild<QWidget*>("StockTransferListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("returnListForm"))
		((DataForm*)this->findChild<QWidget*>("returnListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("specificationListForm"))
		((DataForm*)this->findChild<QWidget*>("specificationListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("spoilageListForm"))
		((DataForm*)this->findChild<QWidget*>("spoilageListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("transportListForm"))
		((DataForm*)this->findChild<QWidget*>("transportListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("productionConsumeRawListForm"))
		((DataForm*)this->findChild<QWidget*>("productionConsumeRawListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("productionListForm"))
		((DataForm*)this->findChild<QWidget*>("productionListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("writeOffListForm"))
		((DataForm*)this->findChild<QWidget*>("writeOffListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("writeOffRawListForm"))
		((DataForm*)this->findChild<QWidget*>("writeOffRawListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("consumeOthStListForm"))
		((DataForm*)this->findChild<QWidget*>("consumeOthStListForm"))->CloseDataForm();
	if (0 != this->findChild<QWidget*>("receiptOthStListForm"))
		((DataForm*)this->findChild<QWidget*>("receiptOthStListForm"))->CloseDataForm();
}

void MainForm::CreateConnections()
{
	QObject::connect(actionAllUsers, &QAction::triggered, this, &MainForm::OpenUserForm);
	QObject::connect(actionClients, &QAction::triggered, this, &MainForm::OpenClientForm);
	QObject::connect(actionEmployees, &QAction::triggered, this, &MainForm::OpenEmployeeForm);
	QObject::connect(actionPurveyors, &QAction::triggered, this, &MainForm::OpenPurveyorForm);
	QObject::connect(actionAccountables, &QAction::triggered, this, &MainForm::OpenAccountableForm);
	QObject::connect(actionBorrowers, &QAction::triggered, this, &MainForm::OpenBorrowerForm);
	QObject::connect(actionCreditors, &QAction::triggered, this, &MainForm::OpenCreditorForm);
	QObject::connect(actionShareholders, &QAction::triggered, this, &MainForm::OpenShareholderForm);
	QObject::connect(actionGroup, &QAction::triggered, this, &MainForm::OpenGroupForm);
	QObject::connect(actionUserGroup, &QAction::triggered, this, &MainForm::OpenUserGroupForm);
	QObject::connect(actionCompanyEmployees, &QAction::triggered, this, &MainForm::OpenCompanyEmployeeForm);
	QObject::connect(actionCashboxEmployees, &QAction::triggered, this, &MainForm::OpenCashboxEmployeeForm);
	QObject::connect(actionWarehouseEmployees, &QAction::triggered, this, &MainForm::OpenWarehouseEmployeeForm);
	QObject::connect(actionAccess, &QAction::triggered, this, &MainForm::OpenAccessForm);
	QObject::connect(actionAccessItems, &QAction::triggered, this, &MainForm::OpenAccessItemForm);
	QObject::connect(actionUserPhoto, &QAction::triggered, this, &MainForm::OpenUserPhotoForm);
	QObject::connect(actionPosition, &QAction::triggered, this, &MainForm::OpenPositionForm);
	

	QObject::connect(actionProductType, &QAction::triggered, this, &MainForm::OpenProductTypeForm);
	QObject::connect(actionProducts, &QAction::triggered, this, &MainForm::OpenProductForm);
	QObject::connect(actionProductPhoto, &QAction::triggered, this, &MainForm::OpenProductPhotoForm);
	QObject::connect(actionSpecifications, &QAction::triggered, this, &MainForm::OpenSpecificationForm);
	QObject::connect(actionSpecificationList, &QAction::triggered, this, &MainForm::OpenSpecificationListForm);
	QObject::connect(actionPrices, &QAction::triggered, this, &MainForm::OpenPriceForm);
	QObject::connect(actionNetCost, &QAction::triggered, this, &MainForm::OpenNetCostForm);
	QObject::connect(actionEmployeeProducts, &QAction::triggered, this, &MainForm::OpenEmployeeProductForm);
	QObject::connect(actionBranchProducts, &QAction::triggered, this, &MainForm::OpenBranchProductForm);
	QObject::connect(actionOtherStocks, &QAction::triggered, this, &MainForm::OpenOtherStocksForm);
	

	QObject::connect(actionOrders, &QAction::triggered, this, &MainForm::OpenOrderForm);
	QObject::connect(actionOrderList, &QAction::triggered, this, &MainForm::OpenOrderListForm);

	QObject::connect(actionReturns, &QAction::triggered, this, &MainForm::OpenReturnForm);
	QObject::connect(actionReturnList, &QAction::triggered, this, &MainForm::OpenReturnListForm);

	QObject::connect(actionProduction, &QAction::triggered, this, &MainForm::OpenProductionForm);
	QObject::connect(actionProductionList, &QAction::triggered, this, &MainForm::OpenProductionListForm);
	QObject::connect(actionProductionStock, &QAction::triggered, this, &MainForm::OpenProductionStockForm);
	QObject::connect(actionProductionConsumeRaws, &QAction::triggered, this, &MainForm::OpenProductionConsumeRawForm);
	QObject::connect(actionProductionPlan, &QAction::triggered, this, &MainForm::OpenProductionPlanForm);
	QObject::connect(actionProductionPlanList, &QAction::triggered, this, &MainForm::OpenProductionPlanListForm);
	QObject::connect(actionJobprice, &QAction::triggered, this, &MainForm::OpenJobpriceForm);
	QObject::connect(actionJobsheet, &QAction::triggered, this, &MainForm::OpenJobsheetForm);
	QObject::connect(actionPercentRate, &QAction::triggered, this, &MainForm::OpenPercentRateForm);
	QObject::connect(actionTimesheet, &QAction::triggered, this, &MainForm::OpenTimesheetForm);
	QObject::connect(actionSpoilage, &QAction::triggered, this, &MainForm::OpenSpoilageForm);
	QObject::connect(actionSpoilageList, &QAction::triggered, this, &MainForm::OpenSpoilageListForm);
	QObject::connect(actionReworkRaws, &QAction::triggered, this, &MainForm::ReworkRawForm);

	QObject::connect(actionWriteOffs, &QAction::triggered, this, &MainForm::OpenWriteOffForm);
	QObject::connect(actionWriteOffList, &QAction::triggered, this, &MainForm::OpenWriteOffListForm);

	QObject::connect(actionBalances, &QAction::triggered, this, &MainForm::OpenBalanceForm);
	QObject::connect(actionAccounts, &QAction::triggered, this, &MainForm::OpenAccountForm);
	QObject::connect(actionSubaccounts, &QAction::triggered, this, &MainForm::OpenSubaccountForm);
	QObject::connect(actionSubaccountLimit, &QAction::triggered, this, &MainForm::OpenSubaccountLimitForm);
	QObject::connect(actionGenerateAccounts, &QAction::triggered, this, &MainForm::GenerateAccountsForm);
	QObject::connect(actionGenerateOneAccount, &QAction::triggered, this, &MainForm::GenerateOneAccountForm);
	QObject::connect(actionSalary, &QAction::triggered, this, &MainForm::OpenSalaryForm);
	QObject::connect(actionSalaryType, &QAction::triggered, this, &MainForm::OpenSalaryTypeForm);
	QObject::connect(actionPayroll, &QAction::triggered, this, &MainForm::OpenPayrollForm);	
	QObject::connect(actionAccountType, &QAction::triggered, this, &MainForm::OpenAccountTypeForm);
	QObject::connect(actionBranchSubaccounts, &QAction::triggered, this, &MainForm::OpenBranchSubaccountForm);
	QObject::connect(actionDivisionAccounts, &QAction::triggered, this, &MainForm::OpenDivisionAccountsForm);
	QObject::connect(actionChartOfAccounts, &QAction::triggered, this, &MainForm::OpenChartOfAccountsForm);
	QObject::connect(actionCompanyAccounts, &QAction::triggered, this, &MainForm::OpenCompanyAccountForm);
	QObject::connect(actionEntry, &QAction::triggered, this, &MainForm::OpenEntryForm);
	QObject::connect(actionEntryRouting, &QAction::triggered, this, &MainForm::OpenEntryRoutingForm);
	QObject::connect(actionAccountableReport, &QAction::triggered, this, &MainForm::OpenAccountableDocumentForm);
	QObject::connect(actionCloseOfMonth, &QAction::triggered, this, &MainForm::OpenCloseOfMonthForm);
	QObject::connect(actionWarehouse, &QAction::triggered, this, &MainForm::OpenWarehouseForm);
	QObject::connect(actionCashbox, &QAction::triggered, this, &MainForm::OpenCashboxForm);
		
	QObject::connect(actionFixedAssets, &QAction::triggered, this, &MainForm::OpenFixedAssetsForm);
	QObject::connect(actionFixedAssetsOperation, &QAction::triggered, this, &MainForm::OpenFixedAssetsOperationForm);
	QObject::connect(actionInventory, &QAction::triggered, this, &MainForm::OpenInventoryForm);
	QObject::connect(actionAmortizeGroup, &QAction::triggered, this, &MainForm::OpenAmortizeGroupForm);
	QObject::connect(actionAmortizeType, &QAction::triggered, this, &MainForm::OpenAmortizeTypeForm);

	QObject::connect(actionCash, &QAction::triggered, this, &MainForm::OpenCashForm);
	QObject::connect(actionPayments, &QAction::triggered, this, &MainForm::OpenPaymentForm);
	QObject::connect(actionRefund, &QAction::triggered, this, &MainForm::OpenRefundForm);
	QObject::connect(actionPayslip, &QAction::triggered, this, &MainForm::OpenPayslipForm);
	QObject::connect(actionWithdrawal, &QAction::triggered, this, &MainForm::OpenWithdrawalForm);
	QObject::connect(actionCashBookList, &QAction::triggered, this, &MainForm::OpenCashBookListForm);

	QObject::connect(actionStock, &QAction::triggered, this, &MainForm::OpenStockForm);
	QObject::connect(actionStockLimit, &QAction::triggered, this, &MainForm::OpenStockLimitForm);
	QObject::connect(actionRawStock, &QAction::triggered, this, &MainForm::OpenStockRawForm);
	QObject::connect(actionProductStock, &QAction::triggered, this, &MainForm::OpenStockProductForm);
	QObject::connect(actionOrderRaws, &QAction::triggered, this, &MainForm::OpenOrderRawForm);
	QObject::connect(actionStockTransfers, &QAction::triggered, this, &MainForm::OpenStockTransferForm);
	QObject::connect(actionConsumptionRaws, &QAction::triggered, this, &MainForm::OpenConsumeRawForm);
	QObject::connect(actionWriteOffRaws, &QAction::triggered, this, &MainForm::OpenWriteOffRawForm);
	QObject::connect(actionTransports, &QAction::triggered, this, &MainForm::OpenTransportForm);
	QObject::connect(actionReceiptProducts, &QAction::triggered, this, &MainForm::OpenReceiptProductForm);
	QObject::connect(actionConsumptionProducts, &QAction::triggered, this, &MainForm::OpenConsumeProductForm);
	QObject::connect(actionInventorization, &QAction::triggered, this, &MainForm::OpenInventorizationForm);
	QObject::connect(actionLowValueStock, &QAction::triggered, this, &MainForm::OpenLowValueStockForm);
	QObject::connect(actionReceiptOthSt, &QAction::triggered, this, &MainForm::OpenReceiptOthStForm);
	QObject::connect(actionConsumeOthSt, &QAction::triggered, this, &MainForm::OpenConsumeOthStForm);

	QObject::connect(actionCompanyBalanceInfo, &QAction::triggered, this, &MainForm::CompanyBalanceInfo);
	QObject::connect(actionFinancialReport, &QAction::triggered, this, &MainForm::FinancialReportForm);
	QObject::connect(actionCompanyBalance, &QAction::triggered, this, &MainForm::CompanyBalanceForm);
	QObject::connect(actionSpecificationReport, &QAction::triggered, this, &MainForm::SpecificationReportForm);
	QObject::connect(actionProfitability, &QAction::triggered, this, &MainForm::ProfitabilityReportForm);
	QObject::connect(actionSalesReport, &QAction::triggered, this, &MainForm::SalesReportForm);
	QObject::connect(actionAccountCard, &QAction::triggered, this, &MainForm::AccountCardForm);
	QObject::connect(actionWarehouseTurnover, &QAction::triggered, this, &MainForm::WarehouseTurnoverForm);
	QObject::connect(actionDailySalesReport, &QAction::triggered, this, &MainForm::DailySalesReportForm);
	QObject::connect(actionCommonReport, &QAction::triggered, this, &MainForm::CommonReportForm);
	QObject::connect(actionAgentReport, &QAction::triggered, this, &MainForm::AgentReportForm);
	QObject::connect(actionFixedAssetsReport, &QAction::triggered, this, &MainForm::FixedAssetsForm);
	QObject::connect(actionWarehouseReport, &QAction::triggered, this, &MainForm::WarehouseReportForm);
	
	QObject::connect(actionCompany, &QAction::triggered, this, &MainForm::OpenCompanyForm);
	QObject::connect(actionCurrency, &QAction::triggered, this, &MainForm::OpenCurrencyForm);
	QObject::connect(actionMeasure, &QAction::triggered, this, &MainForm::OpenMeasureForm);
	QObject::connect(actionLocation, &QAction::triggered, this, &MainForm::OpenLocationForm);
	QObject::connect(actionRoles, &QAction::triggered, this, &MainForm::OpenRoleForm);
	QObject::connect(actionStatus, &QAction::triggered, this, &MainForm::OpenStatusForm);
	QObject::connect(actionStatusRule, &QAction::triggered, this, &MainForm::OpenStatusRuleForm);
	QObject::connect(actionRelation, &QAction::triggered, this, &MainForm::OpenRelationForm);
	QObject::connect(actionRelationType, &QAction::triggered, this, &MainForm::OpenRelationTypeForm);
	QObject::connect(actionDivision, &QAction::triggered, this, &MainForm::OpenDivisionForm);
	QObject::connect(actionWarehouseType, &QAction::triggered, this, &MainForm::OpenWarehouseTypeForm);
	QObject::connect(actionBranch, &QAction::triggered, this, &MainForm::OpenBranchForm);

	QObject::connect(actionAbout, &QAction::triggered, this, &MainForm::OpenAboutForm);
}

QMdiSubWindow* MainForm::GetWindowByName(QString name)
{
	return GetSubWindow(mdiArea->subWindowList(), name);
}

void MainForm::OpenUserForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("userForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Users"));
		dForm->FillTable<BusinessLayer::UserView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::UserView>();
			dForm->setObjectName("userForm");
			QMdiSubWindow *userWindow = new QMdiSubWindow;
			userWindow->setWidget(dForm);
			userWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(userWindow);
			userWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All users are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All users are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenUserGroupForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("userGroupForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("User group"));
		dForm->FillTable<BusinessLayer::UserGroupRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::UserGroupRelationView>();
			dForm->setObjectName("userGroupForm");
			QMdiSubWindow *userGrWindow = new QMdiSubWindow;
			userGrWindow->setWidget(dForm);
			userGrWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(userGrWindow);
			userGrWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All user groups are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All user grous are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenClientForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("clientForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Clients"));
		dForm->FillTable<BusinessLayer::ClientView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ClientView>();
			dForm->setObjectName("clientForm");
			QMdiSubWindow *clientWindow = new QMdiSubWindow;
			clientWindow->setWidget(dForm);
			clientWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(clientWindow);
			clientWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All clients are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All clients are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenEmployeeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("employeeForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Employees"));
		dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::EmployeeView>();
			dForm->setObjectName("employeeForm");
			QMdiSubWindow *employeeWindow = new QMdiSubWindow;
			employeeWindow->setWidget(dForm);
			employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(employeeWindow);
			employeeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All employees are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All employees are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenPurveyorForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("purveyorForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Purveyors"));
		dForm->FillTable<BusinessLayer::PurveyorView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::PurveyorView>();
			dForm->setObjectName("purveyorForm");
			QMdiSubWindow *purveyorWindow = new QMdiSubWindow;
			purveyorWindow->setWidget(dForm);
			purveyorWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(purveyorWindow);
			purveyorWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All purveyors are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All purveyors are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenAccountableForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("accountableForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Accountables"));
		dForm->FillTable<BusinessLayer::AccountableView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::AccountableView>();
			dForm->setObjectName("accountableForm");
			QMdiSubWindow *accountableWindow = new QMdiSubWindow;
			accountableWindow->setWidget(dForm);
			accountableWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(accountableWindow);
			accountableWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All accountables are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All accountables are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenBorrowerForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("borrowerForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Borrowers"));
		dForm->FillTable<BusinessLayer::BorrowerView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::BorrowerView>();
			dForm->setObjectName("borrowerForm");
			QMdiSubWindow *borrowerWindow = new QMdiSubWindow;
			borrowerWindow->setWidget(dForm);
			borrowerWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(borrowerWindow);
			borrowerWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All borrowers are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All borrowers are shown");
		statusBar()->showMessage(message);
	}
}


/*void MainForm::OpenCreditorForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("creditorForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Creditors"));
		dForm->FillTable<BusinessLayer::Creditor>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Creditor>();
			dForm->setObjectName("creditorForm");
			QMdiSubWindow *creditorWindow = new QMdiSubWindow;
			creditorWindow->setWidget(dForm);
			creditorWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(creditorWindow);
			creditorWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All creditors are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All creditors are shown");
		statusBar()->showMessage(message);
	}
}*/

/*void MainForm::OpenShareholderForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("shareholderForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Shareholders"));
		dForm->FillTable<BusinessLayer::Shareholder>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Shareholder>();
			dForm->setObjectName("shareholderForm");
			QMdiSubWindow *shareholderWindow = new QMdiSubWindow;
			shareholderWindow->setWidget(dForm);
			shareholderWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(shareholderWindow);
			shareholderWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All shareholders are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All shareholders are shown");
		statusBar()->showMessage(message);
	}
}*/

void MainForm::OpenGroupForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("groupForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Groups"));
		dForm->FillTable<BusinessLayer::Group>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Group>();
			dForm->setObjectName("groupForm");
			QMdiSubWindow *groupWindow = new QMdiSubWindow;
			groupWindow->setWidget(dForm);
			groupWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(groupWindow);
			groupWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->HideSomeRow();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All groups are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All groups are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenCompanyEmployeeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("companyEmployeeForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Company-employee relation"));
		dForm->FillTable<BusinessLayer::CompanyEmployeeRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::CompanyEmployeeRelationView>();
			dForm->setObjectName("companyEmployeeForm");
			QMdiSubWindow *comEmpWindow = new QMdiSubWindow;
			comEmpWindow->setWidget(dForm);
			comEmpWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(comEmpWindow);
			comEmpWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All company-employee relations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All company-employee relations are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenCashboxEmployeeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("cashboxEmployeeForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Cashbox-employee relation"));
		dForm->FillTable<BusinessLayer::CashboxEmployeeRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::CashboxEmployeeRelationView>();
			dForm->setObjectName("cashboxEmployeeForm");
			QMdiSubWindow *cashEmpWindow = new QMdiSubWindow;
			cashEmpWindow->setWidget(dForm);
			cashEmpWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(cashEmpWindow);
			cashEmpWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All cashbox-employee relations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All cashbox-employee relations are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenWarehouseEmployeeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("warehouseEmployeeForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Warehouse-employee relation"));
		dForm->FillTable<BusinessLayer::WarehouseEmployeeRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::WarehouseEmployeeRelationView>();
			dForm->setObjectName("warehouseEmployeeForm");
			QMdiSubWindow *werEmpWindow = new QMdiSubWindow;
			werEmpWindow->setWidget(dForm);
			werEmpWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(werEmpWindow);
			werEmpWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All warehouse-employee relations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All warehouse-employee relations are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenAccessForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("accessForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Accesses"));
		dForm->FillTable<BusinessLayer::AccessView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::AccessView>();
			dForm->setObjectName("accessForm");
			QMdiSubWindow *accessWindow = new QMdiSubWindow;
			accessWindow->setWidget(dForm);
			accessWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(accessWindow);
			accessWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All accesses are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All accesses are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenAccessItemForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("accessItemForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Access items"));
		dForm->FillTable<BusinessLayer::AccessItem>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::AccessItem>();
			dForm->setObjectName("accessItemForm");
			QMdiSubWindow *accessItemWindow = new QMdiSubWindow;
			accessItemWindow->setWidget(dForm);
			accessItemWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(accessItemWindow);
			accessItemWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All access items are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All access items are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenUserPhotoForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("userPhotoForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("User photo"));
		dForm->FillTable<BusinessLayer::Photo>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Photo>();
			dForm->setObjectName("userPhotoForm");
			QMdiSubWindow *userPhotoWindow = new QMdiSubWindow;
			userPhotoWindow->setWidget(dForm);
			userPhotoWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(userPhotoWindow);
			userPhotoWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All user photos are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All user photos are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenPositionForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("positionForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Position"));
		dForm->FillTable<BusinessLayer::Position>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Position>();
			dForm->setObjectName("positionForm");
			QMdiSubWindow *positionWindow = new QMdiSubWindow;
			positionWindow->setWidget(dForm);
			positionWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(positionWindow);
			positionWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All position are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All position are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenProductForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Products"));
		dForm->FillTable<BusinessLayer::ProductView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductView>();
			dForm->setObjectName("productForm");
			QMdiSubWindow *productWindow = new QMdiSubWindow;
			productWindow->setWidget(dForm);
			productWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(productWindow);
			productWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenProductTypeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Product types"));
		dForm->FillTable<BusinessLayer::ProductType>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductType>();
			dForm->setObjectName("productTypeForm");
			QMdiSubWindow *prodTypeWindow = new QMdiSubWindow;
			prodTypeWindow->setWidget(dForm);
			prodTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(prodTypeWindow);
			prodTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All product types are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All product types are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenProductPhotoForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productPhotoForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Product photo"));
		dForm->FillTable<BusinessLayer::Photo>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Photo>();
			dForm->setObjectName("productPhotoForm");
			QMdiSubWindow *prodPhotoWindow = new QMdiSubWindow;
			prodPhotoWindow->setWidget(dForm);
			prodPhotoWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(prodPhotoWindow);
			prodPhotoWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All product photos are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All product photos are shown");
		statusBar()->showMessage(message);
	}

}
void MainForm::OpenSpecificationForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("specificationForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Specifications"));
		dForm->FillTable<BusinessLayer::SpecificationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::SpecificationView>();
			dForm->setObjectName("specificationForm");
			QMdiSubWindow *specWindow = new QMdiSubWindow;
			specWindow->setWidget(dForm);
			specWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(specWindow);
			specWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All specifications are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All specifications are shown");
		statusBar()->showMessage(message);
	}

}
void MainForm::OpenSpecificationListForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("specificationListForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Spesicfication list"));
		dForm->FillTable<BusinessLayer::SpecificationListView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::SpecificationListView>();
			dForm->setObjectName("specificationListForm");
			QMdiSubWindow *specListWindow = new QMdiSubWindow;
			specListWindow->setWidget(dForm);
			specListWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(specListWindow);
			specListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products in the specification list are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products in the specification list are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenPriceForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("priceForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Price"));
		dForm->FillTable<BusinessLayer::PriceView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("priceForm");
			dForm->QtConnect<BusinessLayer::PriceView>();
			QMdiSubWindow *priceWindow = new QMdiSubWindow;
			priceWindow->setWidget(dForm);
			priceWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(priceWindow);
			priceWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All prices are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All prices are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenNetCostForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("netCostForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Net cost"));
		dForm->FillTable<BusinessLayer::NetCostView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("netCostForm");
			dForm->QtConnect<BusinessLayer::NetCostView>();
			QMdiSubWindow *netCostWindow = new QMdiSubWindow;
			netCostWindow->setWidget(dForm);
			netCostWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(netCostWindow);
			netCostWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All net cost are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All net cost are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenEmployeeProductForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("employeeProductForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Employee-product relation"));
		dForm->FillTable<BusinessLayer::EmployeeProductRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::EmployeeProductRelationView>();
			dForm->setObjectName("employeeProductForm");
			QMdiSubWindow *empPrdWindow = new QMdiSubWindow;
			empPrdWindow->setWidget(dForm);
			empPrdWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(empPrdWindow);
			empPrdWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All employee-product relations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All employee-product relations are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenBranchProductForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("branchProductForm"));
	if (checkedWidget == nullptr)
	{
		errorMessage = "";
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Branch-product relation"));
		dForm->FillTable<BusinessLayer::ProductBranchRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductBranchRelationView>();
			dForm->setObjectName("branchProductForm");
			QMdiSubWindow *brnPrdWindow = new QMdiSubWindow;
			brnPrdWindow->setWidget(dForm);
			brnPrdWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(brnPrdWindow);
			brnPrdWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All branch-product relations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All branch-product relations are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenOrderForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("orderForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Orders"));
		dForm->FillTable<BusinessLayer::OrderView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::OrderView>();
			dForm->setObjectName("orderForm");
			QMdiSubWindow *orderWindow = new QMdiSubWindow;
			orderWindow->setWidget(dForm);
			orderWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(orderWindow);
			orderWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All orders are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All orders are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenOrderListForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("orderListForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Products in order list"));
		dForm->FillTable<BusinessLayer::OrderListView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::OrderListView>();
			dForm->setObjectName("orderListForm");
			QMdiSubWindow *orderListWindow = new QMdiSubWindow;
			orderListWindow->setWidget(dForm);
			orderListWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(orderListWindow);
			orderListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products in order list are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products in order list are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenReturnForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("returnForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Returns"));
		dForm->FillTable<BusinessLayer::ReturnView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ReturnView>();
			dForm->setObjectName("returnForm");
			QMdiSubWindow *returnWindow = new QMdiSubWindow;
			returnWindow->setWidget(dForm);
			returnWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(returnWindow);
			returnWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All returns are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All returns are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenReturnListForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("returnListForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Products in return list"));
		dForm->FillTable<BusinessLayer::ReturnListView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ReturnListView>();
			dForm->setObjectName("returnListForm");
			QMdiSubWindow *returnListWindow = new QMdiSubWindow;
			returnListWindow->setWidget(dForm);
			returnListWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(returnListWindow);
			returnListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products in return list are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products in return list are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenWriteOffForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("writeOffForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Write-off"));
		dForm->FillTable<BusinessLayer::WriteOffView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::WriteOffView>();
			dForm->setObjectName("writeOffForm");
			QMdiSubWindow *writeOfftWindow = new QMdiSubWindow;
			writeOfftWindow->setWidget(dForm);
			writeOfftWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(writeOfftWindow);
			writeOfftWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All write-off are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All write-off are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenWriteOffListForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("writeOffListForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Products in write-off list"));
		dForm->FillTable<BusinessLayer::WriteOffListView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::WriteOffListView>();
			dForm->setObjectName("writeOffListForm");
			QMdiSubWindow *writeOffListWindow = new QMdiSubWindow;
			writeOffListWindow->setWidget(dForm);
			writeOffListWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(writeOffListWindow);
			writeOffListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products in write-off list are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products in write-off list are shown");
		statusBar()->showMessage(message);
	}

}


void MainForm::OpenProductionForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productionForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Production"));
		dForm->FillTable<BusinessLayer::Production>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::Production>();
			dForm->setObjectName("productionForm");
			QMdiSubWindow *productionWindow = new QMdiSubWindow;
			productionWindow->setWidget(dForm);
			productionWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(productionWindow);
			productionWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All production are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All production are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenProductionStockForm()
{
	BusinessLayer::WarehouseEmployeeRelation reRel;
	BusinessLayer::Warehouse warehouse;
	BusinessLayer::WarehouseType wType;
	if (!reRel.GetWarehouseEmployeeByEmployeeID(oBL->globalVar, oBL->GetOrmasDal(), loggedUser->GetID(), errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (!warehouse.GetWarehouseByID(oBL->globalVar, oBL->GetOrmasDal(), reRel.GetWarehouseID(), errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (!wType.GetWarehouseTypeByCode(oBL->globalVar, oBL->GetOrmasDal(), "PRODUCTION", errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (wType.GetID() != warehouse.GetWarehouseTypeID())
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::Stock stock;
	stock.SetWarehouseID(reRel.GetWarehouseID());
	std::string filter = stock.GenerateFilter(oBL->GetOrmasDal());
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productionStockForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Production stock"));
		dForm->FillTable<BusinessLayer::StockView>(errorMessage, filter);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::StockView>();
			dForm->setObjectName("productionStockForm");
			QMdiSubWindow *stockWindow = new QMdiSubWindow;
			stockWindow->setWidget(dForm);
			stockWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(stockWindow);
			stockWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->SetDecoration();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in production stock");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in production stock");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenProductionListForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productionListForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Products in production list"));
		dForm->FillTable<BusinessLayer::ProductionListView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductionListView>();
			dForm->setObjectName("productionListForm");
			QMdiSubWindow *productionListWindow = new QMdiSubWindow;
			productionListWindow->setWidget(dForm);
			productionListWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(productionListWindow);
			productionListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products in production list are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products in production list are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenProductionConsumeRawForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productionCnsumeRawForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Production consume raw"));
		dForm->FillTable<BusinessLayer::ProductionConsumeRawView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("productionCnsumeRawForm");
			dForm->QtConnect<BusinessLayer::ProductionConsumeRawView>();
			QMdiSubWindow *pConsumeRawWindow = new QMdiSubWindow;
			pConsumeRawWindow->setWidget(dForm);
			pConsumeRawWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(pConsumeRawWindow);
			pConsumeRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raws are shown in consume");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raws are shown in consume");
		statusBar()->showMessage(message);
	}

}


void MainForm::OpenProductionPlanForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productionPlanForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Production plan"));
		dForm->FillTable<BusinessLayer::ProductionPlanView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductionPlanView>();
			dForm->setObjectName("productionPlanForm");
			QMdiSubWindow *productionPlanWindow = new QMdiSubWindow;
			productionPlanWindow->setWidget(dForm);
			productionPlanWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(productionPlanWindow);
			productionPlanWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All production plans are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All production plan are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenProductionPlanListForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productionPlanListForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Products in production plan list"));
		dForm->FillTable<BusinessLayer::ProductionPlanListView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::ProductionPlanListView>();
			dForm->setObjectName("productionPlanListForm");
			QMdiSubWindow *productionPlanListWindow = new QMdiSubWindow;
			productionPlanListWindow->setWidget(dForm);
			productionPlanListWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(productionPlanListWindow);
			productionPlanListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products in production plan list are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products in production plan list are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenJobpriceForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("jobpriceForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Jobprice"));
		dForm->FillTable<BusinessLayer::JobpriceView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::JobpriceView>();
			dForm->setObjectName("jobpriceForm");
			QMdiSubWindow *jobpriceWindow = new QMdiSubWindow;
			jobpriceWindow->setWidget(dForm);
			jobpriceWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(jobpriceWindow);
			jobpriceWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All jobprices are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();

		QString message = tr("All jobprices are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenJobsheetForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("jobsheetForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Jobsheet"));
		dForm->FillTable<BusinessLayer::JobsheetView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::JobsheetView>();
			dForm->setObjectName("jobsheetForm");
			QMdiSubWindow *jobsheetWindow = new QMdiSubWindow;
			jobsheetWindow->setWidget(dForm);
			jobsheetWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(jobsheetWindow);
			jobsheetWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All jobsheets are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All jobsheets are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenPercentRateForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("percentRateForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Percent rate"));
		dForm->FillTable<BusinessLayer::PercentRate>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::PercentRate>();
			dForm->setObjectName("percentRateForm");
			QMdiSubWindow *percentRateWindow = new QMdiSubWindow;
			percentRateWindow->setWidget(dForm);
			percentRateWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(percentRateWindow);
			percentRateWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All percent rates are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All percent rates are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenTimesheetForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("timesheetForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Timesheet"));
		dForm->FillTable<BusinessLayer::TimesheetView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::TimesheetView>();
			dForm->setObjectName("timesheetForm");
			QMdiSubWindow *timesheetWindow = new QMdiSubWindow;
			timesheetWindow->setWidget(dForm);
			timesheetWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(timesheetWindow);
			timesheetWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All timesheets are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All timesheets are shown");
		statusBar()->showMessage(message);
	}

}



void MainForm::OpenSpoilageForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("spoilageForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Spoilage"));
		dForm->FillTable<BusinessLayer::SpoilageView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::SpoilageView>();
			dForm->setObjectName("spoilageForm");
			QMdiSubWindow *spoilageWindow = new QMdiSubWindow;
			spoilageWindow->setWidget(dForm);
			spoilageWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(spoilageWindow);
			spoilageWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All spoilage are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All spoilage are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenSpoilageListForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("spoilageListForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Products in spoilage list"));
		dForm->FillTable<BusinessLayer::SpoilageListView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::SpoilageListView>();
			dForm->setObjectName("spoilageListForm");
			QMdiSubWindow *spoilageListWindow = new QMdiSubWindow;
			spoilageListWindow->setWidget(dForm);
			spoilageListWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(spoilageListWindow);
			spoilageListWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products in spoilage list are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products in spoilage list are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::ReworkRawForm()
{
	ReworkRawDlg *reworkRawDlg = new ReworkRawDlg(oBL, this);
	reworkRawDlg->setAttribute(Qt::WA_DeleteOnClose);
	reworkRawDlg->setWindowTitle(tr("Rework raws"));
	QMdiSubWindow *reworkRawWindow = new QMdiSubWindow;
	reworkRawWindow->setWidget(reworkRawDlg);
	reworkRawWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(reworkRawWindow);
	reworkRawDlg->show();
}

void MainForm::OpenBalanceForm()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(oBL->globalVar, oBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return;

	std::string filter = "";

	if (GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
		GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
	{
		
		filter = "";
	}
	else
	{
		BusinessLayer::Employee emp;
		BusinessLayer::CompanyEmployeeRelation ceRel;
		int branchID = ceRel.GetBranchByEmployeeID(oBL->globalVar, oBL->GetOrmasDal(), GetLoggedUser()->GetID(), errorMessage);
		if (0 < branchID)
		{
			//get list of employees in branch
			ceRel.Clear();
			std::vector<int> empIDVec = ceRel.GetAllEmployeeIDByBranchID(oBL->globalVar, oBL->GetOrmasDal(), branchID, errorMessage);
			filter = emp.GenerateINFilter(oBL->globalVar, oBL->GetOrmasDal(), empIDVec);
		}
	}

	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("balanceForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Balances"));
		dForm->FillTable<BusinessLayer::BalanceView>(errorMessage, filter);
		if (errorMessage.empty())
		{
			dForm->setObjectName("balanceForm");
			dForm->QtConnect<BusinessLayer::BalanceView>();
			QMdiSubWindow *balanceWindow = new QMdiSubWindow;
			balanceWindow->setWidget(dForm);
			balanceWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(balanceWindow);
			balanceWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All balances are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All balances are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenAccountForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("accountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Accounts"));
		dForm->FillTable<BusinessLayer::Account>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("accountForm");
			dForm->QtConnect<BusinessLayer::Account>();
			QMdiSubWindow *accountWindow = new QMdiSubWindow;
			accountWindow->setWidget(dForm);
			accountWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(accountWindow);
			accountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All accounts are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All accounts are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenSubaccountForm()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(oBL->globalVar, oBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return;

	std::string filter = "";
	
	if (this->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
		this->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
	{
		filter = "";
	}
	else
	{
		BusinessLayer::Subaccount subaccount;
		BusinessLayer::BranchSubaccountRelation bsRel;
		BusinessLayer::CompanyEmployeeRelation ceRel;
		int branchID = ceRel.GetBranchByEmployeeID(oBL->globalVar, oBL->GetOrmasDal(), this->GetLoggedUser()->GetID(), errorMessage);
		if (0 < branchID)
		{
			std::vector<int> subaccountIDVec = bsRel.GetSubaccountIDsbyBranchID(oBL->globalVar, oBL->GetOrmasDal(), branchID, errorMessage);
			if (subaccountIDVec.size() > 0)
			{
				filter = subaccount.GenerateINFilter(oBL->globalVar, oBL->GetOrmasDal(), subaccountIDVec);
			}
		}
	}
	errorMessage.clear();
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("subaccountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Subaccounts"));
		dForm->FillTable<BusinessLayer::SubaccountView>(errorMessage, filter);
		if (errorMessage.empty())
		{
			dForm->setObjectName("subaccountForm");
			dForm->QtConnect<BusinessLayer::SubaccountView>();
			QMdiSubWindow *subaccountWindow = new QMdiSubWindow;
			subaccountWindow->setWidget(dForm);
			subaccountWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(subaccountWindow);
			subaccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->SetDecoration();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All subaccounts are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All subaccounts are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenSubaccountLimitForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("subaccountLimitForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Subaccount limit"));
		dForm->FillTable<BusinessLayer::SubaccountLimitView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("subaccountLimitForm");
			dForm->QtConnect<BusinessLayer::SubaccountLimitView>();
			QMdiSubWindow *subaccountLmWindow = new QMdiSubWindow;
			subaccountLmWindow->setWidget(dForm);
			subaccountLmWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(subaccountLmWindow);
			subaccountLmWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All subaccount limits are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All subaccount limits are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::GenerateAccountsForm()
{
	GenerateAcc *generateAccDlg = new GenerateAcc(oBL, this);
	generateAccDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateAccDlg->setWindowTitle(tr("Generate accounts"));
	QMdiSubWindow *generateAccWindow = new QMdiSubWindow;
	generateAccWindow->setWidget(generateAccDlg);
	generateAccWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateAccWindow);
	generateAccDlg->show();
}

void MainForm::GenerateOneAccountForm(){
	GenerateOneAcc *generateOneAccDlg = new GenerateOneAcc(oBL, this);
	generateOneAccDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateOneAccDlg->setWindowTitle(tr("Generate one account"));
	QMdiSubWindow *generateOneAccWindow = new QMdiSubWindow;
	generateOneAccWindow->setWidget(generateOneAccDlg);
	generateOneAccWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateOneAccWindow);
	generateOneAccDlg->show();
}

void MainForm::FixedAssetsForm()
{
	GenerateFxAstRep *generateFxAstDlg = new GenerateFxAstRep(oBL, this);
	generateFxAstDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateFxAstDlg->setWindowTitle(tr("Generate fixed assets report"));
	QMdiSubWindow *generateFxAstWindow = new QMdiSubWindow;
	generateFxAstWindow->setWidget(generateFxAstDlg);
	generateFxAstWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateFxAstWindow);
	generateFxAstDlg->show();
}


void MainForm::WarehouseReportForm()
{
	GenerateWrRep *generateWRDlg = new GenerateWrRep(oBL, this);
	generateWRDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateWRDlg->setWindowTitle(tr("Generate warehosue report"));
	QMdiSubWindow *generateWRWindow = new QMdiSubWindow;
	generateWRWindow->setWidget(generateWRDlg);
	generateWRWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateWRWindow);
	generateWRDlg->show();
}

void MainForm::OpenSalaryForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("salaryForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Salary"));
		dForm->FillTable<BusinessLayer::SalaryView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("salaryForm");
			dForm->QtConnect<BusinessLayer::SalaryView>();
			QMdiSubWindow *salaryWindow = new QMdiSubWindow;
			salaryWindow->setWidget(dForm);
			salaryWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(salaryWindow);
			salaryWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All salary are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All salary are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenSalaryTypeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("salaryTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Salary types"));
		dForm->FillTable<BusinessLayer::SalaryType>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("salaryTypeForm");
			dForm->QtConnect<BusinessLayer::SalaryType>();
			QMdiSubWindow *salaryTypeWindow = new QMdiSubWindow;
			salaryTypeWindow->setWidget(dForm);
			salaryTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(salaryTypeWindow);
			salaryTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All salary types are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All salary types are shown");
		statusBar()->showMessage(message);
	}

}


void MainForm::OpenPayrollForm()
{
	ClcWagesDlg *wagesDlg = new ClcWagesDlg(oBL, this);
	wagesDlg->setAttribute(Qt::WA_DeleteOnClose);
	wagesDlg->setWindowTitle(tr("Calculate salary"));
	QMdiSubWindow *wagesWindow = new QMdiSubWindow;
	wagesWindow->setWidget(wagesDlg);
	wagesWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(wagesWindow);
	wagesDlg->show();
}

void MainForm::OpenAccountTypeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("accountTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Account type"));
		dForm->FillTable<BusinessLayer::AccountType>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("accountTypeForm");
			dForm->QtConnect<BusinessLayer::AccountType>();
			QMdiSubWindow *accountTypeWindow = new QMdiSubWindow;
			accountTypeWindow->setWidget(dForm);
			accountTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(accountTypeWindow);
			accountTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All account type are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All account type are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenChartOfAccountsForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("chartOffAccountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Chart of account"));
		dForm->FillTable<BusinessLayer::ChartOfAccountsView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("chartOffAccountForm");
			dForm->QtConnect<BusinessLayer::ChartOfAccountsView>();
			QMdiSubWindow *chartOfAccountWindow = new QMdiSubWindow;
			chartOfAccountWindow->setWidget(dForm);
			chartOfAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(chartOfAccountWindow);
			chartOfAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Chart of accounts are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Chart of accounts are showns");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenCompanyAccountForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("companyAccountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Company account relation"));
		dForm->FillTable<BusinessLayer::CompanyAccountRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("companyAccountForm");
			dForm->QtConnect<BusinessLayer::CompanyAccountRelationView>();
			QMdiSubWindow *companyAccountWindow = new QMdiSubWindow;
			companyAccountWindow->setWidget(dForm);
			companyAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(companyAccountWindow);
			companyAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Company-account relations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Company-account relations are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenEntryForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("entryForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Entries"));
		dForm->FillTable<BusinessLayer::EntryView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("entryForm");
			dForm->QtConnect<BusinessLayer::EntryView>();
			QMdiSubWindow *entryWindow = new QMdiSubWindow;
			entryWindow->setWidget(dForm);
			entryWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(entryWindow);
			entryWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All entries are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All entries are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenAccountableDocumentForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("acctbDocForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Accountable documents"));
		dForm->FillTable<BusinessLayer::AccountableDocument>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("accblDocForm");
			dForm->QtConnect<BusinessLayer::AccountableDocument>();
			QMdiSubWindow *accblDocWindow = new QMdiSubWindow;
			accblDocWindow->setWidget(dForm);
			accblDocWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(accblDocWindow);
			accblDocWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All documents are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All documents are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenEntryRoutingForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("entryRoutingForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Entry routing"));
		dForm->FillTable<BusinessLayer::EntryRouting>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("entryRoutingForm");
			dForm->QtConnect<BusinessLayer::EntryRouting>();
			QMdiSubWindow *entryRoutingWindow = new QMdiSubWindow;
			entryRoutingWindow->setWidget(dForm);
			entryRoutingWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(entryRoutingWindow);
			entryRoutingWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Entry routing are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Entry routing are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenCloseOfMonthForm()
{
	CloseOfMonthDlg *closeOfMonthDlg = new CloseOfMonthDlg(oBL, this);
	closeOfMonthDlg->setAttribute(Qt::WA_DeleteOnClose);
	closeOfMonthDlg->setWindowTitle(tr("Close of month"));
	QMdiSubWindow *closeOfMonthWindow = new QMdiSubWindow;
	closeOfMonthWindow->setWidget(closeOfMonthDlg);
	closeOfMonthWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(closeOfMonthWindow);
	closeOfMonthDlg->show();
}

void MainForm::OpenWarehouseForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("warehouseForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Warehouse"));
		dForm->FillTable<BusinessLayer::WarehouseView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("warehouseForm");
			dForm->QtConnect<BusinessLayer::WarehouseView>();
			QMdiSubWindow *wareWindow = new QMdiSubWindow;
			wareWindow->setWidget(dForm);
			wareWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(wareWindow);
			wareWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Warehouse are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Warehouse are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenFixedAssetsForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("fixedAstForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Fixed assets"));
		dForm->FillTable<BusinessLayer::FixedAssetsView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("fixedAstForm");
			dForm->QtConnect<BusinessLayer::FixedAssetsView>();
			QMdiSubWindow *faWindow = new QMdiSubWindow;
			faWindow->setWidget(dForm);
			faWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(faWindow);
			faWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Fixed assets are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Fixed assets are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenFixedAssetsOperationForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("fixedAstOperForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Fixed assets operation"));
		dForm->FillTable<BusinessLayer::FixedAssetsOperations>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("fixedAstOperForm");
			dForm->QtConnect<BusinessLayer::FixedAssetsOperations>();
			QMdiSubWindow *faoWindow = new QMdiSubWindow;
			faoWindow->setWidget(dForm);
			faoWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(faoWindow);
			faoWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Fixed assets operation are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Fixed assets operation are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenInventoryForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("inventoryForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Fixed assets operation"));
		dForm->FillTable<BusinessLayer::InventoryView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("inventoryForm");
			dForm->QtConnect<BusinessLayer::InventoryView>();
			QMdiSubWindow *inveWindow = new QMdiSubWindow;
			inveWindow->setWidget(dForm);
			inveWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(inveWindow);
			inveWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Inventory are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Inventory are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenAmortizeGroupForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("amGroupForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Amortize group"));
		dForm->FillTable<BusinessLayer::AmortizeGroup>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("amGroupForm");
			dForm->QtConnect<BusinessLayer::AmortizeGroup>();
			QMdiSubWindow *amGrWindow = new QMdiSubWindow;
			amGrWindow->setWidget(dForm);
			amGrWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(amGrWindow);
			amGrWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Amortize group are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Amortize group are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenAmortizeTypeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("amTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Amortize type"));
		dForm->FillTable<BusinessLayer::AmortizeType>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("amTypeForm");
			dForm->QtConnect<BusinessLayer::AmortizeType>();
			QMdiSubWindow *amTypeWindow = new QMdiSubWindow;
			amTypeWindow->setWidget(dForm);
			amTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(amTypeWindow);
			amTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Amortize type are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Amortize type are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenCashboxForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("cashboxForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Cashbox"));
		dForm->FillTable<BusinessLayer::CashboxView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("cashboxForm");
			dForm->QtConnect<BusinessLayer::CashboxView>();
			QMdiSubWindow *caWindow = new QMdiSubWindow;
			caWindow->setWidget(dForm);
			caWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(caWindow);
			caWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("Cashbox are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("Cashbox are shown");
		statusBar()->showMessage(message);
	}

}



void MainForm::OpenCashForm()
{
	CashInfoDlg *cashInfoDlg = new CashInfoDlg(oBL, this);
	cashInfoDlg->setAttribute(Qt::WA_DeleteOnClose);
	cashInfoDlg->setWindowTitle(tr("Cash"));
	QMdiSubWindow *cashInfoWindow = new QMdiSubWindow;
	cashInfoWindow->setWidget(cashInfoDlg);
	cashInfoWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(cashInfoWindow);
	cashInfoDlg->show();
}

void MainForm::OpenOtherStocksForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("otherStocksForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Other stocks"));
		dForm->FillTable<BusinessLayer::OtherStocksView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::OtherStocksView>();
			dForm->setObjectName("otherStocksForm");
			QMdiSubWindow *otherStocksWindow = new QMdiSubWindow;
			otherStocksWindow->setWidget(dForm);
			otherStocksWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(otherStocksWindow);
			otherStocksWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All other stocks are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All other stocks are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenPaymentForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("paymentForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Payments"));
		std::string filter = "";
		BusinessLayer::Cashbox cashbox;
		BusinessLayer::CashboxEmployeeRelation ceRelation;
		if (ceRelation.GetCashboxEmployeeByEmployeeID(oBL->globalVar, oBL->GetOrmasDal(), oBL->loggedUser->GetID(), errorMessage))
		{
			if (cashbox.GetCashboxByID(oBL->globalVar, oBL->GetOrmasDal(), ceRelation.GetCashboxID(), errorMessage))
			{
				BusinessLayer::Payment payment;
				payment.SetCashboxAccountID(cashbox.GetSubaccountID());
				filter = payment.GenerateFilter(oBL->GetOrmasDal());
			}
		}
		dForm->FillTable<BusinessLayer::PaymentView>(errorMessage, filter);
		if (errorMessage.empty())
		{
			dForm->setObjectName("paymentForm");
			dForm->QtConnect<BusinessLayer::PaymentView>();
			QMdiSubWindow *paymentWindow = new QMdiSubWindow;
			paymentWindow->setWidget(dForm);
			paymentWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(paymentWindow);
			paymentWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All payments are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All payments are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenRefundForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("refundForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Refunds"));
		dForm->FillTable<BusinessLayer::RefundView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("refundForm");
			dForm->QtConnect<BusinessLayer::RefundView>();
			QMdiSubWindow *refundWindow = new QMdiSubWindow;
			refundWindow->setWidget(dForm);
			refundWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(refundWindow);
			refundWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All refunds are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All payments are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenPayslipForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("payslipForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Payslips"));
		dForm->FillTable<BusinessLayer::PayslipView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("payslipForm");
			dForm->QtConnect<BusinessLayer::PayslipView>();
			QMdiSubWindow *payslipWindow = new QMdiSubWindow;
			payslipWindow->setWidget(dForm);
			payslipWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(payslipWindow);
			payslipWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All payslips are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All withdrawals are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenWithdrawalForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("withdrawalForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Withdrawals"));
		std::string filter = "";
		BusinessLayer::Cashbox cashbox;
		BusinessLayer::CashboxEmployeeRelation ceRelation;
		if (ceRelation.GetCashboxEmployeeByEmployeeID(oBL->globalVar, oBL->GetOrmasDal(), oBL->loggedUser->GetID(), errorMessage))
		{
			if (cashbox.GetCashboxByID(oBL->globalVar, oBL->GetOrmasDal(), ceRelation.GetCashboxID(), errorMessage))
			{
				BusinessLayer::Withdrawal withdrawal;
				withdrawal.SetCashboxAccountID(cashbox.GetSubaccountID());
				filter = withdrawal.GenerateFilter(oBL->GetOrmasDal());
			}
		}
		dForm->FillTable<BusinessLayer::WithdrawalView>(errorMessage, filter);
		if (errorMessage.empty())
		{
			dForm->setObjectName("withdrawalForm");
			dForm->QtConnect<BusinessLayer::WithdrawalView>();
			QMdiSubWindow *withdrawalWindow = new QMdiSubWindow;
			withdrawalWindow->setWidget(dForm);
			withdrawalWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(withdrawalWindow);
			withdrawalWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All withdrawal are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All withdrawals are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenCashBookListForm()
{
	CashBookListDlg *cashBookListDlg = new CashBookListDlg(oBL, this);
	cashBookListDlg->setAttribute(Qt::WA_DeleteOnClose);
	cashBookListDlg->setWindowTitle(tr("Cash book list"));
	QMdiSubWindow *cashBookListWindow = new QMdiSubWindow;
	cashBookListWindow->setWidget(cashBookListDlg);
	cashBookListWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(cashBookListWindow);
	cashBookListDlg->show();
}

void MainForm::OpenStockForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("stockForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Stock"));
		dForm->FillTable<BusinessLayer::StockView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("stockForm");
			dForm->QtConnect<BusinessLayer::StockView>();
			QMdiSubWindow *stockWindow = new QMdiSubWindow;
			stockWindow->setWidget(dForm);
			stockWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(stockWindow);
			stockWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->SetDecoration();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in the stock");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in the stock");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenStockLimitForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("stockLimitForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Stock limit"));
		dForm->FillTable<BusinessLayer::StockLimitView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("stockLimitForm");
			dForm->QtConnect<BusinessLayer::StockLimitView>();
			QMdiSubWindow *stockLmWindow = new QMdiSubWindow;
			stockLmWindow->setWidget(dForm);
			stockLmWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(stockLmWindow);
			stockLmWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All ilimits are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All ilimits are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenStockRawForm()
{
	BusinessLayer::WarehouseEmployeeRelation reRel;
	BusinessLayer::Warehouse warehouse;
	BusinessLayer::WarehouseType wType;
	if (!reRel.GetWarehouseEmployeeByEmployeeID(oBL->globalVar, oBL->GetOrmasDal(), loggedUser->GetID(), errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (!warehouse.GetWarehouseByID(oBL->globalVar, oBL->GetOrmasDal(), reRel.GetWarehouseID(), errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (!wType.GetWarehouseTypeByCode(oBL->globalVar, oBL->GetOrmasDal(), "RAW", errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (wType.GetID() != warehouse.GetWarehouseTypeID())
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::Stock stock;
	stock.SetWarehouseID(reRel.GetWarehouseID());
	std::string filter = stock.GenerateFilter(oBL->GetOrmasDal());
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("rewStockForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Raw stock"));
		dForm->FillTable<BusinessLayer::StockView>(errorMessage, filter);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::StockView>();
			dForm->setObjectName("rawStockForm");
			QMdiSubWindow *stockWindow = new QMdiSubWindow;
			stockWindow->setWidget(dForm);
			stockWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(stockWindow);
			stockWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->SetDecoration();
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in raw stock");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in raw stock");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenStockProductForm()
{
	BusinessLayer::WarehouseEmployeeRelation reRel;
	BusinessLayer::Warehouse warehouse;
	BusinessLayer::WarehouseType wType;
	if (!reRel.GetWarehouseEmployeeByEmployeeID(oBL->globalVar, oBL->GetOrmasDal(), loggedUser->GetID(), errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (!warehouse.GetWarehouseByID(oBL->globalVar, oBL->GetOrmasDal(), reRel.GetWarehouseID(), errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (!wType.GetWarehouseTypeByCode(oBL->globalVar, oBL->GetOrmasDal(), "PRODUCT", errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (wType.GetID() != warehouse.GetWarehouseTypeID())
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::Stock stock;
	stock.SetWarehouseID(reRel.GetWarehouseID());
	std::string filter = stock.GenerateFilter(oBL->GetOrmasDal());
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("productStockForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Product stock"));
		dForm->FillTable<BusinessLayer::StockView>(errorMessage, filter);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::StockView>();
			dForm->setObjectName("productStockForm");
			QMdiSubWindow *stockWindow = new QMdiSubWindow;
			stockWindow->setWidget(dForm);
			stockWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(stockWindow);
			stockWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in product stock");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in product stock");
		statusBar()->showMessage(message);
	}

}


void MainForm::OpenOrderRawForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("orderRawForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Order raw"));
		dForm->FillTable<BusinessLayer::OrderRawView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("orderRawForm");
			dForm->QtConnect<BusinessLayer::OrderRawView>();
			QMdiSubWindow *orderRawWindow = new QMdiSubWindow;
			orderRawWindow->setWidget(dForm);
			orderRawWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(orderRawWindow);
			orderRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raws are shown in orders");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raws are shown in orders");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenStockTransferForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("stockTransferForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Receipt raw"));
		dForm->FillTable<BusinessLayer::StockTransferView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("StockTransferForm");
			dForm->QtConnect<BusinessLayer::StockTransferView>();
			QMdiSubWindow *StockTransferWindow = new QMdiSubWindow;
			StockTransferWindow->setWidget(dForm);
			StockTransferWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(StockTransferWindow);
			StockTransferWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raws are shown in receipt");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raws are shown in receipt");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenConsumeRawForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("consumeRawForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Consume raw"));
		dForm->FillTable<BusinessLayer::ConsumeRawView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("consumeRawForm");
			dForm->QtConnect<BusinessLayer::ConsumeRawView>();
			QMdiSubWindow *consumeRawWindow = new QMdiSubWindow;
			consumeRawWindow->setWidget(dForm);
			consumeRawWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(consumeRawWindow);
			consumeRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raws are shown in consume");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raws are shown in consume");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenConsumeOthStForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("consumeOthStForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Consume other stocks"));
		dForm->FillTable<BusinessLayer::ConsumeOtherStocksView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("consumeOthStForm");
			dForm->QtConnect<BusinessLayer::ConsumeOtherStocksView>();
			QMdiSubWindow *consumeOthStWindow = new QMdiSubWindow;
			consumeOthStWindow->setWidget(dForm);
			consumeOthStWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(consumeOthStWindow);
			consumeOthStWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All other stocks are shown in consume");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All other stocks are shown in consume");
		statusBar()->showMessage(message);
	}

}


void MainForm::OpenWriteOffRawForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("writeOffRawForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Write-off raw"));
		dForm->FillTable<BusinessLayer::WriteOffRawView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("writeOffRawForm");
			dForm->QtConnect<BusinessLayer::WriteOffRawView>();
			QMdiSubWindow *writeOffRawWindow = new QMdiSubWindow;
			writeOffRawWindow->setWidget(dForm);
			writeOffRawWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(writeOffRawWindow);
			writeOffRawWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All raw are shown in write-off");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All raw are shown in write-off");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenTransportForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("transportForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Transports"));
		dForm->FillTable<BusinessLayer::TransportView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("transportForm");
			dForm->QtConnect<BusinessLayer::TransportView>();
			QMdiSubWindow *transportWindow = new QMdiSubWindow;
			transportWindow->setWidget(dForm);
			transportWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(transportWindow);
			transportWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All transports are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All transports are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenReceiptOthStForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("receiptOthStForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Receipt other stocks"));
		dForm->FillTable<BusinessLayer::ReceiptOtherStocksView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("receiptOthStForm");
			dForm->QtConnect<BusinessLayer::ReceiptOtherStocksView>();
			QMdiSubWindow *rosWindow = new QMdiSubWindow;
			rosWindow->setWidget(dForm);
			rosWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(rosWindow);
			rosWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All other stocks are shown in receipts");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All other stocks are shown in receipts");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenReceiptProductForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("receiptProductForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Receipt product"));
		dForm->FillTable<BusinessLayer::ReceiptProductView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("receiptProductForm");
			dForm->QtConnect<BusinessLayer::ReceiptProductView>();
			QMdiSubWindow *receiptProductWindow = new QMdiSubWindow;
			receiptProductWindow->setWidget(dForm);
			receiptProductWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(receiptProductWindow);
			receiptProductWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in receipt");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in receipt");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenConsumeProductForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("consumeProductForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Consume product"));
		dForm->FillTable<BusinessLayer::ConsumeProductView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("consumeProductForm");
			dForm->QtConnect<BusinessLayer::ConsumeProductView>();
			QMdiSubWindow *consumeProductWindow = new QMdiSubWindow;
			consumeProductWindow->setWidget(dForm);
			consumeProductWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(consumeProductWindow);
			consumeProductWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All products are shown in consume");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All products are shown in consume");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenInventorizationForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("inventorizationForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Inventorization"));
		dForm->FillTable<BusinessLayer::InventorizationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("inventorizationForm");
			dForm->QtConnect<BusinessLayer::InventorizationView>();
			QMdiSubWindow *inventorizationWindow = new QMdiSubWindow;
			inventorizationWindow->setWidget(dForm);
			inventorizationWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(inventorizationWindow);
			inventorizationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All inventorizations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All inventorizations are shown");
		statusBar()->showMessage(message);
	}

}

void MainForm::CompanyBalanceInfo()
{
	double active = 0;
	double passive = 0;
	BusinessLayer::Account acc;
	acc.BalanceShortInfo(oBL->globalVar, oBL->GetOrmasDal(), active, passive, errorMessage);
	QString message = tr("Balance info!");
	statusBar()->showMessage(message);
	if (errorMessage.empty())
	{
		QString message = "Actives = " + QString::number(active, 'f', 3) + " / Passives = " + QString::number(passive, 'f', 3);
		QMessageBox::information(NULL, QString(tr("Warning")),
			message,
			QString(tr("Ok")));
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
	}
	errorMessage = "";
}

void MainForm::FinancialReportForm()
{
	GenerateFinRep *generateFinRepDlg = new GenerateFinRep(oBL, this);
	generateFinRepDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateFinRepDlg->setWindowTitle(tr("Generate financial report"));
	QMdiSubWindow *generateFinRepWindow = new QMdiSubWindow;
	generateFinRepWindow->setWidget(generateFinRepDlg);
	generateFinRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateFinRepWindow);
	generateFinRepDlg->show();
}

void MainForm::CompanyBalanceForm()
{
	GenerateCmpBlc *generateFinCmpBlc = new GenerateCmpBlc(oBL, this);
	generateFinCmpBlc->setAttribute(Qt::WA_DeleteOnClose);
	generateFinCmpBlc->setWindowTitle(tr("Generate financial report"));
	QMdiSubWindow *generateCmpBlcWindow = new QMdiSubWindow;
	generateCmpBlcWindow->setWidget(generateFinCmpBlc);
	generateCmpBlcWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateCmpBlcWindow);
	generateFinCmpBlc->show();
}

void MainForm::SpecificationReportForm()
{
	GenerateSpecRep *generateSpecRepDlg = new GenerateSpecRep(oBL, this);
	generateSpecRepDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateSpecRepDlg->setWindowTitle(tr("Generate specification report"));
	QMdiSubWindow *generateSpecRepWindow = new QMdiSubWindow;
	generateSpecRepWindow->setWidget(generateSpecRepDlg);
	generateSpecRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateSpecRepWindow);
	generateSpecRepDlg->show();
}

void MainForm::ProfitabilityReportForm()
{
	GenerateProfRep *generateProfRepDlg = new GenerateProfRep(oBL, this);
	generateProfRepDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateProfRepDlg->setWindowTitle(tr("Generate profitability report"));
	QMdiSubWindow *generateProfRepWindow = new QMdiSubWindow;
	generateProfRepWindow->setWidget(generateProfRepDlg);
	generateProfRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateProfRepWindow);
	generateProfRepDlg->show();
}

void MainForm::SalesReportForm()
{
	GenerateSalesRep *generateSalesRepDlg = new GenerateSalesRep(oBL, this);
	generateSalesRepDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateSalesRepDlg->setWindowTitle(tr("Generate sales report"));
	QMdiSubWindow *generateSalesRepWindow = new QMdiSubWindow;
	generateSalesRepWindow->setWidget(generateSalesRepDlg);
	generateSalesRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateSalesRepWindow);
	generateSalesRepDlg->show();
}

void MainForm::AccountCardForm()
{
	GenerateAccCardRep *generateAccRepDlg = new GenerateAccCardRep(oBL, this);
	generateAccRepDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateAccRepDlg->setWindowTitle(tr("Generate account card report"));
	QMdiSubWindow *generateAccRepWindow = new QMdiSubWindow;
	generateAccRepWindow->setWidget(generateAccRepDlg);
	generateAccRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateAccRepWindow);
	generateAccRepDlg->show();
}

void MainForm::WarehouseTurnoverForm()
{
	GenerateWTBS *generateWTBSDlg = new GenerateWTBS(oBL, this);
	generateWTBSDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateWTBSDlg->setWindowTitle(tr("Generate warehouse turnover balance sheet report"));
	QMdiSubWindow *generateWTBSWindow = new QMdiSubWindow;
	generateWTBSWindow->setWidget(generateWTBSDlg);
	generateWTBSWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateWTBSWindow);
	generateWTBSDlg->show();
}

void MainForm::DailySalesReportForm()
{
	GenerateDailySalesRep *generateDailySalesRepDlg = new GenerateDailySalesRep(oBL, this);
	generateDailySalesRepDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateDailySalesRepDlg->setWindowTitle(tr("Generate daily sales report"));
	QMdiSubWindow *generateDailySalesRepWindow = new QMdiSubWindow;
	generateDailySalesRepWindow->setWidget(generateDailySalesRepDlg);
	generateDailySalesRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generateDailySalesRepWindow);
	generateDailySalesRepDlg->show();
}

void MainForm::AgentReportForm()
{
	GenerateAgentRep *generateAgentRepDlg = new GenerateAgentRep(oBL, this);
	generateAgentRepDlg->setAttribute(Qt::WA_DeleteOnClose);
	generateAgentRepDlg->setWindowTitle(tr("Generate agent report"));
	QMdiSubWindow *generatAgentRepWindow = new QMdiSubWindow;
	generatAgentRepWindow->setWidget(generateAgentRepDlg);
	generatAgentRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(generatAgentRepWindow);
	generateAgentRepDlg->show();
}

void MainForm::CommonReportForm()
{
	GenerateComRep *commonRepDlg = new GenerateComRep(oBL, this);
	commonRepDlg->setAttribute(Qt::WA_DeleteOnClose);
	commonRepDlg->setWindowTitle(tr("Generate common report"));
	QMdiSubWindow *commonRepDlgRepWindow = new QMdiSubWindow;
	commonRepDlgRepWindow->setWidget(commonRepDlg);
	commonRepDlgRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(commonRepDlgRepWindow);
	commonRepDlg->show();
}



void MainForm::OpenCompanyForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("companyForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Companies"));
		dForm->FillTable<BusinessLayer::Company>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("companyForm");
			dForm->QtConnect<BusinessLayer::Company>();
			QMdiSubWindow *companyWindow = new QMdiSubWindow;
			companyWindow->setWidget(dForm);
			companyWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(companyWindow);
			companyWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All companies are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All companies are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenCurrencyForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("currencyForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Currencies"));
		dForm->FillTable<BusinessLayer::Currency>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("currencyForm");
			dForm->QtConnect<BusinessLayer::Currency>();
			QMdiSubWindow *currencyWindow = new QMdiSubWindow;
			currencyWindow->setWidget(dForm);
			currencyWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(currencyWindow);
			currencyWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All currencies are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All currencies are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenMeasureForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("measureForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Measures"));
		dForm->FillTable<BusinessLayer::Measure>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("measureForm");
			dForm->QtConnect<BusinessLayer::Measure>();
			QMdiSubWindow *measureWindow = new QMdiSubWindow;
			measureWindow->setWidget(dForm);
			measureWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(measureWindow);
			measureWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All measures are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All measures are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenLocationForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("locationForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Locations"));
		dForm->FillTable<BusinessLayer::Location>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("locationForm");
			dForm->QtConnect<BusinessLayer::Location>();
			QMdiSubWindow *locationWindow = new QMdiSubWindow;
			locationWindow->setWidget(dForm);
			locationWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(locationWindow);
			locationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All locations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All locations are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenLowValueStockForm()
{
	BusinessLayer::WarehouseEmployeeRelation reRel;
	BusinessLayer::Warehouse warehouse;
	BusinessLayer::WarehouseType wType;
	if (!reRel.GetWarehouseEmployeeByEmployeeID(oBL->globalVar, oBL->GetOrmasDal(), loggedUser->GetID(), errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (!warehouse.GetWarehouseByID(oBL->globalVar, oBL->GetOrmasDal(), reRel.GetWarehouseID(), errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (!wType.GetWarehouseTypeByCode(oBL->globalVar, oBL->GetOrmasDal(), "LOW VALUE", errorMessage))
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	if (wType.GetID() != warehouse.GetWarehouseTypeID())
	{
		QString message = tr("Access denied!");
		statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Access denied!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::LowValueStock lowValStock;
	lowValStock.SetWarehouseID(reRel.GetWarehouseID());
	std::string filter = lowValStock.GenerateFilter(oBL->GetOrmasDal());
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("lowValueStockForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Low valuw stock"));
		dForm->FillTable<BusinessLayer::LowValueStockView>(errorMessage, filter);
		if (errorMessage.empty())
		{
			dForm->QtConnect<BusinessLayer::LowValueStockView>();
			dForm->setObjectName("lowValueStockForm");
			QMdiSubWindow *lvStockWindow = new QMdiSubWindow;
			lvStockWindow->setWidget(dForm);
			lvStockWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(lvStockWindow);
			lvStockWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All other stocsk are shown in low value stock");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All other stocsk are shown in low value stock");
		statusBar()->showMessage(message);
	}

}

void MainForm::OpenRoleForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("roleForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Roles"));
		dForm->FillTable<BusinessLayer::Role>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("roleForm");
			dForm->QtConnect<BusinessLayer::Role>();
			QMdiSubWindow *roleWindow = new QMdiSubWindow;
			roleWindow->setWidget(dForm);
			roleWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(roleWindow);
			roleWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All roles are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All roles are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenStatusForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("statusForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL,this);
		dForm->setWindowTitle(tr("Statuses"));
		dForm->FillTable<BusinessLayer::Status>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("statusForm");
			dForm->QtConnect<BusinessLayer::Status>();
			QMdiSubWindow *statusWindow = new QMdiSubWindow;
			statusWindow->setWidget(dForm);
			statusWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(statusWindow);
			statusWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All statuses are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All statuses are shown");
		statusBar()->showMessage(message);
	}
	
}

void MainForm::OpenStatusRuleForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("statusRuleForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Status rule"));
		dForm->FillTable<BusinessLayer::StatusRuleView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("statusRuleForm");
			dForm->QtConnect<BusinessLayer::StatusRuleView>();
			QMdiSubWindow *statusRuleWindow = new QMdiSubWindow;
			statusRuleWindow->setWidget(dForm);
			statusRuleWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(statusRuleWindow);
			statusRuleWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All status rules are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All status rules are shown");
		statusBar()->showMessage(message);
	}

}


void MainForm::OpenRelationForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("relationForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Relations"));
		dForm->FillTable<BusinessLayer::RelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("relationForm");
			dForm->QtConnect<BusinessLayer::RelationView>();
			QMdiSubWindow *relationWindow = new QMdiSubWindow;
			relationWindow->setWidget(dForm);
			relationWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(relationWindow);
			relationWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All relations are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All relations are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenRelationTypeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("relationTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Relation types"));
		dForm->FillTable<BusinessLayer::RelationType>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("relationTypeForm");
			dForm->QtConnect<BusinessLayer::RelationType>();
			QMdiSubWindow *relationtypeWindow = new QMdiSubWindow;
			relationtypeWindow->setWidget(dForm);
			relationtypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(relationtypeWindow);
			relationtypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All relation types are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All relation types are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenDivisionForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("divisionForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Divisions"));
		dForm->FillTable<BusinessLayer::Division>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("divisionForm");
			dForm->QtConnect<BusinessLayer::Division>();
			QMdiSubWindow *divisionWindow = new QMdiSubWindow;
			divisionWindow->setWidget(dForm);
			divisionWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(divisionWindow);
			divisionWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All divisions are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All divisions are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenDivisionAccountsForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("divisionAccForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Division account"));
		dForm->FillTable<BusinessLayer::DivisionAccountRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("divisionAccountForm");
			dForm->QtConnect<BusinessLayer::DivisionAccountRelationView>();
			QMdiSubWindow *divisionAccWindow = new QMdiSubWindow;
			divisionAccWindow->setWidget(dForm);
			divisionAccWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(divisionAccWindow);
			divisionAccWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All division account are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All division account are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenBranchForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("branchForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Branches"));
		dForm->FillTable<BusinessLayer::Branch>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("branchForm");
			dForm->QtConnect<BusinessLayer::Branch>();
			QMdiSubWindow *branchWindow = new QMdiSubWindow;
			branchWindow->setWidget(dForm);
			branchWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(branchWindow);
			branchWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All branches are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All branches are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenBranchSubaccountForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("branchSubaccountForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Branch subaccount"));
		dForm->FillTable<BusinessLayer::BranchSubaccountRelationView>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("branchSubaccountForm");
			dForm->QtConnect<BusinessLayer::BranchSubaccountRelationView>();
			QMdiSubWindow *branchSAccWindow = new QMdiSubWindow;
			branchSAccWindow->setWidget(dForm);
			branchSAccWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(branchSAccWindow);
			branchSAccWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All branch subaccount relation are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All branch subaccount relation are shown");
		statusBar()->showMessage(message);
	}
}


void MainForm::OpenWarehouseTypeForm()
{
	QString message = tr("Loading...");
	statusBar()->showMessage(message);
	QWidget* checkedWidget = IsWindowExist(mdiArea->subWindowList(), QString("warehouseTypeForm"));
	if (checkedWidget == nullptr)
	{
		DataForm *dForm = new DataForm(oBL, this);
		dForm->setWindowTitle(tr("Warehouse type"));
		dForm->FillTable<BusinessLayer::WarehouseType>(errorMessage);
		if (errorMessage.empty())
		{
			dForm->setObjectName("warehouseTypeForm");
			dForm->QtConnect<BusinessLayer::WarehouseType>();
			QMdiSubWindow *wTypeWindow = new QMdiSubWindow;
			wTypeWindow->setWidget(dForm);
			wTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
			mdiArea->addSubWindow(wTypeWindow);
			wTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
			dForm->show();
			dForm->topLevelWidget();
			dForm->activateWindow();
			dForm->raise();
			dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
			QString message = tr("All warehouse types are shown");
			statusBar()->showMessage(message);
		}
		else
		{
			delete dForm;
			QString message = tr("End with error!");
			statusBar()->showMessage(message);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			QMessageBox msgBox;
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
		QString message = tr("All warehouse types are shown");
		statusBar()->showMessage(message);
	}
}

void MainForm::OpenAboutForm()
{
	InfoForm *infoDlg = new InfoForm(oBL);
	infoDlg->setAttribute(Qt::WA_DeleteOnClose);
	infoDlg->setWindowTitle(tr("About"));
	infoDlg->show();
}