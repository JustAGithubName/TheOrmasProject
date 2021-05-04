// OrmasBL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "OrmasBL.h"
#include <typeinfo>
#include <math.h>
#include <algorithm>
#include <codecvt>
namespace BusinessLayer{
	
	OrmasBL::OrmasBL()
	{
	}
	
	OrmasBL::OrmasBL(const OrmasBL &oBL)
	{ 
		ormasDal = oBL.ormasDal; 
	}
	
	OrmasBL::~OrmasBL()
	{
		delete loggedUser;
		delete globalVar;
	}

	void OrmasBL::SetGlobalVariables(BusinessLayer::GlobalVariable* glVar)
	{
		globalVar = glVar;
	}

	bool OrmasBL::ConnectToDB(std::string dbname, std::string username, std::string password, std::string host, int port)
	{
		if (ormasDal.ConnectToDB(dbname, username, password, host, port))
			return true;
		return false;
	}

	bool OrmasBL::IsConnected()
	{
		if (ormasDal.IsConnectionStillALive())
			return true;
		return false;
	}
	
	DataLayer::OrmasDal& OrmasBL::GetOrmasDal()
	{
		return ormasDal;
	}

	int OrmasBL::GenerateID()
	{
		return ormasDal.GenerateID();
	}

	int OrmasBL::GenerateInventoryNumber()
	{
		return ormasDal.GenerateInventoryNumber();
	}

	bool OrmasBL::StartTransaction(std::string& errorMessage)
	{
		return ormasDal.StartTransaction(errorMessage);
	}
	bool OrmasBL::StartIsolatedTransaction(std::string& errorMessage)
	{
		return ormasDal.StartIsolatedTransaction(errorMessage);
	}
	bool OrmasBL::CommitTransaction(std::string& errorMessage)
	{
		return ormasDal.CommitTransaction(errorMessage);
	}
	bool OrmasBL::CancelTransaction(std::string& errorMessage)
	{
		return ormasDal.CancelTransaction(errorMessage);
	}

	std::string OrmasBL::ConcatenateFilters(std::vector<std::string> filterList)
	{
		return ormasDal.ConcatenateFilters(filterList);
	}

	template<>
	std::vector<AccessView> OrmasBL::GetAllDataForClass<AccessView>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccessView> vecForAccess;
		std::vector<DataLayer::accessesViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccesses(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccesses(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccess.push_back(AccessView(data));
			}
		}
		return vecForAccess;
	}

	template<>
	std::vector<AccessItem> OrmasBL::GetAllDataForClass<AccessItem>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccessItem> vecForAccessItems;
		std::vector<DataLayer::accessItemsCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccessItems(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccessItems(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccessItems.push_back(AccessItem(data));
			}
		}
		return vecForAccessItems;
	}

	template<>
	std::vector<Account> OrmasBL::GetAllDataForClass<Account>(std::string& errorMessage, std::string filter)
	{
		std::vector<Account> vecForAccount;
		std::vector<DataLayer::accountsCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccounts(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccounts(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccount.push_back(Account(data));
			}
		}
		return vecForAccount;
	}

	template<>
	std::vector<AccountableView> OrmasBL::GetAllDataForClass<AccountableView>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccountableView> vecForAccountable;
		std::vector<DataLayer::accountableViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccountable(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccountable(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccountable.push_back(AccountableView(data));
			}
		}
		return vecForAccountable;
	}

	template<>
	std::vector<AccountableDocument> OrmasBL::GetAllDataForClass<AccountableDocument>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccountableDocument> vecForAccountableDoc;
		std::vector<DataLayer::accountableDocumentCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccountableDocument(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccountableDocument(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccountableDoc.push_back(AccountableDocument(data));
			}
		}
		return vecForAccountableDoc;
	}

	template<>
	std::vector<AccountableEntry> OrmasBL::GetAllDataForClass<AccountableEntry>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccountableEntry> vecForAccountableEtr;
		std::vector<DataLayer::accountableEntryCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccountableEntry(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccountableEntry(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccountableEtr.push_back(AccountableEntry(data));
			}
		}
		return vecForAccountableEtr;
	}

	template<>
	std::vector<AccountablePaymentRelation> OrmasBL::GetAllDataForClass<AccountablePaymentRelation>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccountablePaymentRelation> vecForAccountablePay;
		std::vector<DataLayer::accountablePaymentCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccountablePayment(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccountablePayment(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccountablePay.push_back(AccountablePaymentRelation(data));
			}
		}
		return vecForAccountablePay;
	}

	template<>
	std::vector<AccountableWithdrawalRelation> OrmasBL::GetAllDataForClass<AccountableWithdrawalRelation>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccountableWithdrawalRelation> vecForAccountableWith;
		std::vector<DataLayer::accountableWithdrawalCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccountableWithdrawal(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccountableWithdrawal(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccountableWith.push_back(AccountableWithdrawalRelation(data));
			}
		}
		return vecForAccountableWith;
	}

	template<>
	std::vector<AccountHistory> OrmasBL::GetAllDataForClass<AccountHistory>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccountHistory> vecForAccountHis;
		std::vector<DataLayer::accountHistoryCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccountHistory(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccountHistory(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccountHis.push_back(AccountHistory(data));
			}
		}
		return vecForAccountHis;
	}

	template<>
	std::vector<AccountChangeLog> OrmasBL::GetAllDataForClass<AccountChangeLog>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccountChangeLog> vecForAccountLog;
		std::vector<DataLayer::accountChangeLogCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccountChangeLog(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccountChangeLog(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccountLog.push_back(AccountChangeLog(data));
			}
		}
		return vecForAccountLog;
	}


	template<>
	std::vector<AccountType> OrmasBL::GetAllDataForClass<AccountType>(std::string& errorMessage, std::string filter)
	{
		std::vector<AccountType> vecForAccountType;
		std::vector<DataLayer::accountTypeCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAccountType(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAccountType(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAccountType.push_back(AccountType(data));
			}
		}
		return vecForAccountType;
	}

	template<>
	std::vector<AmortizeGroup> OrmasBL::GetAllDataForClass<AmortizeGroup>(std::string& errorMessage, std::string filter)
	{
		std::vector<AmortizeGroup> vecForAmortizeGroup;
		std::vector<DataLayer::amortizeGroupCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAmortizeGroup(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAmortizeGroup(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAmortizeGroup.push_back(AmortizeGroup(data));
			}
		}
		return vecForAmortizeGroup;
	}

	template<>
	std::vector<AmortizeType> OrmasBL::GetAllDataForClass<AmortizeType>(std::string& errorMessage, std::string filter)
	{
		std::vector<AmortizeType> vecForAmortizeType;
		std::vector<DataLayer::amortizeTypeCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetAmortizeType(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetAmortizeType(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForAmortizeType.push_back(AmortizeType(data));
			}
		}
		return vecForAmortizeType;
	}

	template<>
	std::vector<BalanceView> OrmasBL::GetAllDataForClass<BalanceView>(std::string& errorMessage, std::string filter)
	{
		std::vector<BalanceView> vecForBalance;
		std::vector<DataLayer::balancesViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetBalances(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetBalances(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForBalance.push_back(BalanceView(data));
			}
		}
		return vecForBalance;
	}

	template<>
	std::vector<Branch> OrmasBL::GetAllDataForClass<Branch>(std::string& errorMessage, std::string filter)
	{
		std::vector<Branch> vecForBranch;
		std::vector<DataLayer::branchesCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetBranches(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetBranches(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForBranch.push_back(Branch(data));
			}
		}
		return vecForBranch;
	}

	template<>
	std::vector<BranchSubaccountRelationView> OrmasBL::GetAllDataForClass<BranchSubaccountRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<BranchSubaccountRelationView> vecForBranchSub;
		std::vector<DataLayer::branchSubaccountViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetBranchSubaccount(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetBranchSubaccount(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForBranchSub.push_back(BranchSubaccountRelationView(data));
			}
		}
		return vecForBranchSub;
	}

	template<>
	std::vector<BorrowerView> OrmasBL::GetAllDataForClass<BorrowerView>(std::string& errorMessage, std::string filter)
	{
		std::vector<BorrowerView> vecForBorrower;
		std::vector<DataLayer::borrowersViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetBorrowers(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetBorrowers(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForBorrower.push_back(BorrowerView(data));
			}
		}
		return vecForBorrower;
	}

	template<>
	std::vector<CashboxView> OrmasBL::GetAllDataForClass<CashboxView>(std::string& errorMessage, std::string filter)
	{
		std::vector<CashboxView> vecForCashbox;
		std::vector<DataLayer::cashboxViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetCashbox(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetCashbox(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForCashbox.push_back(CashboxView(data));
			}
		}
		return vecForCashbox;
	}

	template<>
	std::vector<CashboxTransaction> OrmasBL::GetAllDataForClass<CashboxTransaction>(std::string& errorMessage, std::string filter)
	{
		std::vector<CashboxTransaction> vecForCashboxTr;
		std::vector<DataLayer::cashboxTransactionCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetCashboxTransaction(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetCashboxTransaction(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForCashboxTr.push_back(CashboxTransaction(data));
			}
		}
		return vecForCashboxTr;
	}

	template<>
	std::vector<CashboxEmployeeRelationView> OrmasBL::GetAllDataForClass<CashboxEmployeeRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<CashboxEmployeeRelationView> vecForCashboxEmployee;
		std::vector<DataLayer::cashboxEmployeeViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetCashboxEmployee(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetCashboxEmployee(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForCashboxEmployee.push_back(CashboxEmployeeRelationView(data));
			}
		}
		return vecForCashboxEmployee;
	}

	template<>
	std::vector<ChartOfAccountsView> OrmasBL::GetAllDataForClass<ChartOfAccountsView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ChartOfAccountsView> vecForChartOfAccount;
		std::vector<DataLayer::chartOfAccountsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetChartOfAccounts(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetChartOfAccounts(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForChartOfAccount.push_back(ChartOfAccountsView(data));
			}
		}
		return vecForChartOfAccount;
	}

	template<>
	std::vector<ClientView> OrmasBL::GetAllDataForClass<ClientView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ClientView> vecForClient;
		std::vector<DataLayer::clientsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetClients(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetClients(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForClient.push_back(ClientView(data));
			}
		}
		return vecForClient;
	}

	template<>
	std::vector<CompanyAccountRelationView> OrmasBL::GetAllDataForClass<CompanyAccountRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<CompanyAccountRelationView> vecForComAccRel;
		std::vector<DataLayer::companyAccountViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetCompanyAccount(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetCompanyAccount(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForComAccRel.push_back(CompanyAccountRelationView(data));
			}
		}
		return vecForComAccRel;
	}

	template<>
	std::vector<CompanyEmployeeRelationView> OrmasBL::GetAllDataForClass<CompanyEmployeeRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<CompanyEmployeeRelationView> vecForComEmpRel;
		std::vector<DataLayer::companyEmployeeViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetCompanyEmployee(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetCompanyEmployee(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForComEmpRel.push_back(CompanyEmployeeRelationView(data));
			}
		}
		return vecForComEmpRel;
	}

	template<>
	std::vector<Company> OrmasBL::GetAllDataForClass<Company>(std::string& errorMessage, std::string filter)
	{
		std::vector<Company> vecForCompany;
		std::vector<DataLayer::companiesCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetCompanies(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetCompanies(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForCompany.push_back(Company(data));
			}
		}
		return vecForCompany;
	}

	template<>
	std::vector<ConsumeProductView> OrmasBL::GetAllDataForClass<ConsumeProductView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ConsumeProductView> vecForConsumeProduct;
		std::vector<DataLayer::consumeProductsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetConsumeProducts(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetConsumeProducts(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForConsumeProduct.push_back(ConsumeProductView(data));
			}
		}
		return vecForConsumeProduct;
	}

	template<>
	std::vector<ConsumeProductListView> OrmasBL::GetAllDataForClass<ConsumeProductListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ConsumeProductListView> vecForConsumeProductList;
		std::vector<DataLayer::consumeProductListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetConsumeProductList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetConsumeProductList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForConsumeProductList.push_back(ConsumeProductListView(data));
			}
		}
		return vecForConsumeProductList;
	}

	template<>
	std::vector<ConsumeRawView> OrmasBL::GetAllDataForClass<ConsumeRawView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ConsumeRawView> vecForConsumeRaw;
		std::vector<DataLayer::consumeRawsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetConsumeRaws(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetConsumeRaws(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForConsumeRaw.push_back(ConsumeRawView(data));
			}
		}
		return vecForConsumeRaw;
	}

	template<>
	std::vector<ConsumeRawListView> OrmasBL::GetAllDataForClass<ConsumeRawListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ConsumeRawListView> vecForConsumeRawList;
		std::vector<DataLayer::consumeRawListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetConsumeRawList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetConsumeRawList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForConsumeRawList.push_back(ConsumeRawListView(data));
			}
		}
		return vecForConsumeRawList;
	}

	template<>
	std::vector<ConsumeOtherStocksView> OrmasBL::GetAllDataForClass<ConsumeOtherStocksView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ConsumeOtherStocksView> vecForConsumeOthS;
		std::vector<DataLayer::consumeOtherStocksViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetConsumeOtherStocks(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetConsumeOtherStocks(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForConsumeOthS.push_back(ConsumeOtherStocksView(data));
			}
		}
		return vecForConsumeOthS;
	}

	template<>
	std::vector<ConsumeOtherStocksListView> OrmasBL::GetAllDataForClass<ConsumeOtherStocksListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ConsumeOtherStocksListView> vecForConsumeOthSList;
		std::vector<DataLayer::consumeOtherStocksListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetConsumeOtherStocksList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForConsumeOthSList.push_back(ConsumeOtherStocksListView(data));
			}
		}
		return vecForConsumeOthSList;
	}

	template<>
	std::vector<Currency> OrmasBL::GetAllDataForClass<Currency>(std::string& errorMessage, std::string filter)
	{
		std::vector<Currency> vecForCurrency;
		std::vector<DataLayer::currenciesCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetCurrencies(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetCurrencies(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForCurrency.push_back(Currency(data));
			}
		}
		return vecForCurrency;
	}

	template<>
	std::vector<Creditor> OrmasBL::GetAllDataForClass<Creditor>(std::string& errorMessage, std::string filter)
	{
		std::vector<Creditor> vecForCreditor;
		std::vector<DataLayer::creditorsCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetCreditors(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetCreditors(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForCreditor.push_back(Creditor(data));
			}
		}
		return vecForCreditor;
	}

	template<>
	std::vector<DivisionAccountRelationView> OrmasBL::GetAllDataForClass<DivisionAccountRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<DivisionAccountRelationView> vecForDivisionAccount;
		std::vector<DataLayer::divisionAccountViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetDivisionAccount(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetDivisionAccount(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForDivisionAccount.push_back(DivisionAccountRelationView(data));
			}
		}
		return vecForDivisionAccount;
	}

	template<>
	std::vector<DivisionEmployeeRelation> OrmasBL::GetAllDataForClass<DivisionEmployeeRelation>(std::string& errorMessage, std::string filter)
	{
		std::vector<DivisionEmployeeRelation> vecForDivisionEmployee;
		std::vector<DataLayer::divisionEmployeeCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetDivisionEmployee(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetDivisionEmployee(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForDivisionEmployee.push_back(DivisionEmployeeRelation(data));
			}
		}
		return vecForDivisionEmployee;
	}

	template<>
	std::vector<Division> OrmasBL::GetAllDataForClass<Division>(std::string& errorMessage, std::string filter)
	{
		std::vector<Division> vecForDivision;
		std::vector<DataLayer::divisionsCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetDivisions(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetDivisions(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForDivision.push_back(Division(data));
			}
		}
		return vecForDivision;
	}

	template<>
	std::vector<EmployeeView> OrmasBL::GetAllDataForClass<EmployeeView>(std::string& errorMessage, std::string filter)
	{
		std::vector<EmployeeView> vecForEmployee;
		std::vector<DataLayer::employeesViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetEmployees(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetEmployees(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForEmployee.push_back(EmployeeView(data));
			}
		}
		return vecForEmployee;
	}

	template<>
	std::vector<EmployeeProductRelationView> OrmasBL::GetAllDataForClass<EmployeeProductRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<EmployeeProductRelationView> vecForEmplProd;
		std::vector<DataLayer::employeeProductViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetEmployeeProduct(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetEmployeeProduct(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForEmplProd.push_back(EmployeeProductRelationView(data));
			}
		}
		return vecForEmplProd;
	}


	template<>
	std::vector<EntryView> OrmasBL::GetAllDataForClass<EntryView>(std::string& errorMessage, std::string filter)
	{
		std::vector<EntryView> vecForEntry;
		std::vector<DataLayer::entriesViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetEntries(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetEntries(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForEntry.push_back(EntryView(data));
			}
		}
		return vecForEntry;
	}

	template<>
	std::vector<ExtendedEntryView> OrmasBL::GetAllDataForClass<ExtendedEntryView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ExtendedEntryView> vecForEntry;
		std::vector<DataLayer::entriesFullViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetExtendedEntries(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetExtendedEntries(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForEntry.push_back(ExtendedEntryView(data));
			}
		}
		return vecForEntry;
	}

	template<>
	std::vector<FullExtendedEntryView> OrmasBL::GetAllDataForClass<FullExtendedEntryView>(std::string& errorMessage, std::string filter)
	{
		std::vector<FullExtendedEntryView> vecForEntry;
		std::vector<DataLayer::entriesFullJoinViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetFullExtendedEntries(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetFullExtendedEntries(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForEntry.push_back(FullExtendedEntryView(data));
			}
		}
		return vecForEntry;
	}

	template<>
	std::vector<EntryRouting> OrmasBL::GetAllDataForClass<EntryRouting>(std::string& errorMessage, std::string filter)
	{
		std::vector<EntryRouting> vecForEntryRouting;
		std::vector<DataLayer::entryRoutingCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetEntryRouting(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetEntryRouting(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForEntryRouting.push_back(EntryRouting(data));
			}
		}
		return vecForEntryRouting;
	}

	template<>
	std::vector<ExpenseDocument> OrmasBL::GetAllDataForClass<ExpenseDocument>(std::string& errorMessage, std::string filter)
	{
		std::vector<ExpenseDocument> vecForExpenseDoc;
		std::vector<DataLayer::expenseDocumentCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetExpenseDocument(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetExpenseDocument(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForExpenseDoc.push_back(ExpenseDocument(data));
			}
		}
		return vecForExpenseDoc;
	}

	template<>
	std::vector<EntrySubaccountRelation> OrmasBL::GetAllDataForClass<EntrySubaccountRelation>(std::string& errorMessage, std::string filter)
	{
		std::vector<EntrySubaccountRelation> vecForEntrySubaccount;
		std::vector<DataLayer::entrySubaccountCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetEntrySubaccount(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetEntrySubaccount(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForEntrySubaccount.push_back(EntrySubaccountRelation(data));
			}
		}
		return vecForEntrySubaccount;
	}

	template<>
	std::vector<FinancialReport> OrmasBL::GetAllDataForClass<FinancialReport>(std::string& errorMessage, std::string filter)
	{
		std::vector<FinancialReport> vecForFinRep;
		std::vector<DataLayer::financialReportCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetFinancialReport(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetFinancialReport(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForFinRep.push_back(FinancialReport(data));
			}
		}
		return vecForFinRep;
	}

	template<>
	std::vector<FixedAssetsView> OrmasBL::GetAllDataForClass<FixedAssetsView>(std::string& errorMessage, std::string filter)
	{
		std::vector<FixedAssetsView> vecFixedAssRep;
		std::vector<DataLayer::fixedAssetsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetFixedAssets(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetFixedAssets(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecFixedAssRep.push_back(FixedAssetsView(data));
			}
		}
		return vecFixedAssRep;
	}

	template<>
	std::vector<FixedAssetsUnion> OrmasBL::GetAllDataForClass<FixedAssetsUnion>(std::string& errorMessage, std::string filter)
	{
		std::vector<FixedAssetsUnion> vecFixedAssUnionRep;
		std::vector<DataLayer::fixedAssetsUnionCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetFixedAssetsUnion(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetFixedAssetsUnion(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecFixedAssUnionRep.push_back(FixedAssetsUnion(data));
			}
		}
		return vecFixedAssUnionRep;
	}

	template<>
	std::vector<FixedAssetsDetailsView> OrmasBL::GetAllDataForClass<FixedAssetsDetailsView>(std::string& errorMessage, std::string filter)
	{
		std::vector<FixedAssetsDetailsView> vecFixedAssDetailsRep;
		std::vector<DataLayer::fixedAssetsDetailsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetFixedAssetsDetails(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetFixedAssetsDetails(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecFixedAssDetailsRep.push_back(FixedAssetsDetailsView(data));
			}
		}
		return vecFixedAssDetailsRep;
	}

	template<>
	std::vector<FixedAssetsOperations> OrmasBL::GetAllDataForClass<FixedAssetsOperations>(std::string& errorMessage, std::string filter)
	{
		std::vector<FixedAssetsOperations> vecFixedAssOperRep;
		std::vector<DataLayer::fixedAssetsOperationsCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetFixedAssetsOperation(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetFixedAssetsOperation(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecFixedAssOperRep.push_back(FixedAssetsOperations(data));
			}
		}
		return vecFixedAssOperRep;
	}

	template<>
	std::vector<FixedAssetsSpecification> OrmasBL::GetAllDataForClass<FixedAssetsSpecification>(std::string& errorMessage, std::string filter)
	{
		std::vector<FixedAssetsSpecification> vecFixedAssSpecRep;
		std::vector<DataLayer::fixedAssetsSpecificationCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetFixedAssetsSpecification(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetFixedAssetsSpecification(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecFixedAssSpecRep.push_back(FixedAssetsSpecification(data));
			}
		}
		return vecFixedAssSpecRep;
	}

	template<>
	std::vector<Group> OrmasBL::GetAllDataForClass<Group>(std::string& errorMessage, std::string filter)
	{
		std::vector<Group> vecGroup;
		std::vector<DataLayer::groupsCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetGroups(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetGroups(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecGroup.push_back(Group(data));
			}
		}
		return vecGroup;
	}

	template<>
	std::vector<InventorizationView> OrmasBL::GetAllDataForClass<InventorizationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<InventorizationView> vecForInventorization;
		std::vector<DataLayer::inventorizationsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetInventorizations(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetInventorizations(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForInventorization.push_back(InventorizationView(data));
			}
		}
		return vecForInventorization;
	}

	template<>
	std::vector<InventorizationListView> OrmasBL::GetAllDataForClass<InventorizationListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<InventorizationListView> vecForInventorizationList;
		std::vector<DataLayer::inventorizationListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetInventorizationList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetInventorizationList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForInventorizationList.push_back(InventorizationListView(data));
			}
		}
		return vecForInventorizationList;
	}

	template<>
	std::vector<InventoryView> OrmasBL::GetAllDataForClass<InventoryView>(std::string& errorMessage, std::string filter)
	{
		std::vector<InventoryView> vecForInventory;
		std::vector<DataLayer::inventoryViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetInventory(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetInventory(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForInventory.push_back(InventoryView(data));
			}
		}
		return vecForInventory;
	}

	template<>
	std::vector<InventoryUnion> OrmasBL::GetAllDataForClass<InventoryUnion>(std::string& errorMessage, std::string filter)
	{
		std::vector<InventoryUnion> vecForInventoryUn;
		std::vector<DataLayer::inventoryUnionViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetInventoryUnion(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetInventoryUnion(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForInventoryUn.push_back(InventoryUnion(data));
			}
		}
		return vecForInventoryUn;
	}

	template<>
	std::vector<InventoryHistory> OrmasBL::GetAllDataForClass<InventoryHistory>(std::string& errorMessage, std::string filter)
	{
		std::vector<InventoryHistory> vecForInventoryHist;
		std::vector<DataLayer::inventoryHistoryCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetInventoryHistory(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetInventoryHistory(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForInventoryHist.push_back(InventoryHistory(data));
			}
		}
		return vecForInventoryHist;
	}

	template<>
	std::vector<JobpriceView> OrmasBL::GetAllDataForClass<JobpriceView>(std::string& errorMessage, std::string filter)
	{
		std::vector<JobpriceView> vecForJobprice;
		std::vector<DataLayer::jobpriceViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetJobprice(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetJobprice(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForJobprice.push_back(JobpriceView(data));
			}
		}
		return vecForJobprice;
	}

	template<>
	std::vector<JobsheetView> OrmasBL::GetAllDataForClass<JobsheetView>(std::string& errorMessage, std::string filter)
	{
		std::vector<JobsheetView> vecForJobsheet;
		std::vector<DataLayer::jobsheetViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetJobsheet(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetJobsheet(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForJobsheet.push_back(JobsheetView(data));
			}
		}
		return vecForJobsheet;
	}

	template<>
	std::vector<LowValueStockView> OrmasBL::GetAllDataForClass<LowValueStockView>(std::string& errorMessage, std::string filter)
	{
		std::vector<LowValueStockView> vecForLVStock;
		std::vector<DataLayer::lowValueStockViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetLowValueStock(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetLowValueStock(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForLVStock.push_back(LowValueStockView(data));
			}
		}
		return vecForLVStock;
	}

	template<>
	std::vector<LowValueStockHistoryView> OrmasBL::GetAllDataForClass<LowValueStockHistoryView>(std::string& errorMessage, std::string filter)
	{
		std::vector<LowValueStockHistoryView> vecForLVStockHistory;
		std::vector<DataLayer::lowValueStockHistoryViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetLowValueStockHistory(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetLowValueStockHistory(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForLVStockHistory.push_back(LowValueStockHistoryView(data));
			}
		}
		return vecForLVStockHistory;
	}

	template<>
	std::vector<LowValueStockChangeLog> OrmasBL::GetAllDataForClass<LowValueStockChangeLog>(std::string& errorMessage, std::string filter)
	{
		std::vector<LowValueStockChangeLog> vecForLVStockLog;
		std::vector<DataLayer::lowValueStockChangeLogCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetLowValueStockChangeLog(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForLVStockLog.push_back(LowValueStockChangeLog(data));
			}
		}
		return vecForLVStockLog;
	}

	template<>
	std::vector<Location> OrmasBL::GetAllDataForClass<Location>(std::string& errorMessage, std::string filter)
	{
		std::vector<Location> vecForLocation;
		std::vector<DataLayer::locationsCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetLocations(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetLocations(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForLocation.push_back(Location(data));
			}
		}
		return vecForLocation;
	}

	template<>
	std::vector<Measure> OrmasBL::GetAllDataForClass<Measure>(std::string& errorMessage, std::string filter)
	{
		std::vector<Measure> vecForMeasure;
		std::vector<DataLayer::measuresCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetMeasures(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetMeasures(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForMeasure.push_back(Measure(data));
			}
		}
		return vecForMeasure;
	}

	template<>
	std::vector<NetCostView> OrmasBL::GetAllDataForClass<NetCostView>(std::string& errorMessage, std::string filter)
	{
		std::vector<NetCostView> vecFornetCost;
		std::vector<DataLayer::netCostViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetNetCost(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetNetCost(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecFornetCost.push_back(NetCostView(data));
			}
		}
		return vecFornetCost;
	}

	template<>
	std::vector<OrderView> OrmasBL::GetAllDataForClass<OrderView>(std::string& errorMessage, std::string filter)
	{
		std::vector<OrderView> vecForOrder;
		std::vector<DataLayer::ordersViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetOrders(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetOrders(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForOrder.push_back(OrderView(data));
			}
		}
		return vecForOrder;
	}

	template<>
	std::vector<OrderListView> OrmasBL::GetAllDataForClass<OrderListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<OrderListView> vecForOrderList;
		std::vector<DataLayer::orderListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetOrderList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetOrderList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForOrderList.push_back(OrderListView(data));
			}
		}
		return vecForOrderList;
	}

	template<>
	std::vector<OrderRawView> OrmasBL::GetAllDataForClass<OrderRawView>(std::string& errorMessage, std::string filter)
	{
		std::vector<OrderRawView> vecForOrderRaw;
		std::vector<DataLayer::orderRawsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetOrderRaws(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetOrderRaws(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForOrderRaw.push_back(OrderRawView(data));
			}
		}
		return vecForOrderRaw;
	}

	template<>
	std::vector<OrderRawListView> OrmasBL::GetAllDataForClass<OrderRawListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<OrderRawListView> vecForOrderRawList;
		std::vector<DataLayer::orderListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetOrderRawList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetOrderRawList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForOrderRawList.push_back(OrderRawListView(data));
			}
		}
		return vecForOrderRawList;
	}

	template<>
	std::vector<OtherStocksView> OrmasBL::GetAllDataForClass<OtherStocksView>(std::string& errorMessage, std::string filter)
	{
		std::vector<OtherStocksView> vecForOtherStockst;
		std::vector<DataLayer::otherStocksViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetOtherStocks(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetOtherStocks(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForOtherStockst.push_back(OtherStocksView(data));
			}
		}
		return vecForOtherStockst;
	}

	template<>
	std::vector<OtherStocksType> OrmasBL::GetAllDataForClass<OtherStocksType>(std::string& errorMessage, std::string filter)
	{
		std::vector<OtherStocksType> vecForOtherStockst;
		std::vector<DataLayer::otherStocksTypeCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetOtherStocksType(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetOtherStocksType(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForOtherStockst.push_back(OtherStocksType(data));
			}
		}
		return vecForOtherStockst;
	}

	template<>
	std::vector<PaymentView> OrmasBL::GetAllDataForClass<PaymentView>(std::string& errorMessage, std::string filter)
	{
		std::vector<PaymentView> vecForPayment;
		std::vector<DataLayer::paymentsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetPayments(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetPayments(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForPayment.push_back(PaymentView(data));
			}
		}
		return vecForPayment;
	}

	template<>
	std::vector<PayslipView> OrmasBL::GetAllDataForClass<PayslipView>(std::string& errorMessage, std::string filter)
	{
		std::vector<PayslipView> vecForPayslip;
		std::vector<DataLayer::payslipsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetPayslips(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetPayslips(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForPayslip.push_back(PayslipView(data));
			}
		}
		return vecForPayslip;
	}

	template<>
	std::vector<PercentRate> OrmasBL::GetAllDataForClass<PercentRate>(std::string& errorMessage, std::string filter)
	{
		std::vector<PercentRate> vecForPercentRate;
		std::vector<DataLayer::percentRateCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetPercentRate(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetPercentRate(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForPercentRate.push_back(PercentRate(data));
			}
		}
		return vecForPercentRate;
	}

	template<>
	std::vector<Photo> OrmasBL::GetAllDataForClass<Photo>(std::string& errorMessage, std::string filter)
	{
		std::vector<Photo> vecForPhoto;
		std::vector<DataLayer::photosCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetPhotos(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetPhotos(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForPhoto.push_back(Photo(data));
			}
		}
		return vecForPhoto;
	}

	template<>
	std::vector<PostingFixedAssetsView> OrmasBL::GetAllDataForClass<PostingFixedAssetsView>(std::string& errorMessage, std::string filter)
	{
		std::vector<PostingFixedAssetsView> vecForPosFX;
		std::vector<DataLayer::postingFixedAssetsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetPostingFixedAssets(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForPosFX.push_back(PostingFixedAssetsView(data));
			}
		}
		return vecForPosFX;
	}

	template<>
	std::vector<Position> OrmasBL::GetAllDataForClass<Position>(std::string& errorMessage, std::string filter)
	{
		std::vector<Position> vecForPosition;
		std::vector<DataLayer::positionsCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetPositions(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetPositions(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForPosition.push_back(Position(data));
			}
		}
		return vecForPosition;
	}

	template<>
	std::vector<PriceView> OrmasBL::GetAllDataForClass<PriceView>(std::string& errorMessage, std::string filter)
	{
		std::vector<PriceView> vecForPrices;
		std::vector<DataLayer::pricesViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetPrices(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetPrices(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForPrices.push_back(PriceView(data));
			}
		}
		return vecForPrices;
	}

	template<>
	std::vector<ProductView> OrmasBL::GetAllDataForClass<ProductView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductView> vecForProduct;
		std::vector<DataLayer::productsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProducts(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProducts(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProduct.push_back(ProductView(data));
			}
		}
		return vecForProduct;
	}

	
	template<>
	std::vector<Production> OrmasBL::GetAllDataForClass<Production>(std::string& errorMessage, std::string filter)
	{
		std::vector<Production> vecForProduction;
		std::vector<DataLayer::productionCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProduction(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProduction(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProduction.push_back(Production(data));
			}
		}
		return vecForProduction;
	}

	template<>
	std::vector<ProductionListView> OrmasBL::GetAllDataForClass<ProductionListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductionListView> vecForProductionList;
		std::vector<DataLayer::productionListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProductionList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProductionList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProductionList.push_back(ProductionListView(data));
			}
		}
		return vecForProductionList;
	}

	template<>
	std::vector<ProductionConsumeRawView> OrmasBL::GetAllDataForClass<ProductionConsumeRawView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductionConsumeRawView> vecForProdConsumeRaw;
		std::vector<DataLayer::productionConsumeRawsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProductionConsumeRaws(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProductionConsumeRaws(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProdConsumeRaw.push_back(ProductionConsumeRawView(data));
			}
		}
		return vecForProdConsumeRaw;
	}

	template<>
	std::vector<ProductionConsumeRawListView> OrmasBL::GetAllDataForClass<ProductionConsumeRawListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductionConsumeRawListView> vecForProdConsumeRawList;
		std::vector<DataLayer::productionConsumeRawListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProductionConsumeRawList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProductionConsumeRawList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProdConsumeRawList.push_back(ProductionConsumeRawListView(data));
			}
		}
		return vecForProdConsumeRawList;
	}

	template<>
	std::vector<ProductionPlanView> OrmasBL::GetAllDataForClass<ProductionPlanView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductionPlanView> vecForProductionPlan;
		std::vector<DataLayer::productionPlanViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProductionPlan(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProductionPlan(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProductionPlan.push_back(ProductionPlanView(data));
			}
		}
		return vecForProductionPlan;
	}

	template<>
	std::vector<ProductionPlanListView> OrmasBL::GetAllDataForClass<ProductionPlanListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductionPlanListView> vecForProductionPlanList;
		std::vector<DataLayer::productionPlanListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProductionPlanList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProductionPlanList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProductionPlanList.push_back(ProductionPlanListView(data));
			}
		}
		return vecForProductionPlanList;
	}


	template<>
	std::vector<ProductionStockView> OrmasBL::GetAllDataForClass<ProductionStockView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductionStockView> vecForProductionStock;
		std::vector<DataLayer::productionStockViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProductionStock(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProductionStock(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProductionStock.push_back(ProductionStockView(data));
			}
		}
		return vecForProductionStock;
	}


	template<>
	std::vector<ProductType> OrmasBL::GetAllDataForClass<ProductType>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductType> vecForProductType;
		std::vector<DataLayer::productTypeCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProductTypes(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProductTypes(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProductType.push_back(ProductType(data));
			}
		}
		return vecForProductType;
	}

	template<>
	std::vector<ProductBranchRelationView> OrmasBL::GetAllDataForClass<ProductBranchRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ProductBranchRelationView> vecForProductBranch;
		std::vector<DataLayer::productBranchViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetProductBranch(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetProductBranch(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProductBranch.push_back(ProductBranchRelationView(data));
			}
		}
		return vecForProductBranch;
	}

	template<>
	std::vector<PurveyorView> OrmasBL::GetAllDataForClass<PurveyorView>(std::string& errorMessage, std::string filter)
	{
		std::vector<PurveyorView> vecForProductType;
		std::vector<DataLayer::purveyorsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetPurveyors(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetPurveyors(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForProductType.push_back(PurveyorView(data));
			}
		}
		return vecForProductType;
	}

	template<>
	std::vector<ReceiptOtherStocksView> OrmasBL::GetAllDataForClass<ReceiptOtherStocksView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ReceiptOtherStocksView> vecForReceiptOthS;
		std::vector<DataLayer::receiptOtherStocksViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetReceiptOtherStocks(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetReceiptOtherStocks(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForReceiptOthS.push_back(ReceiptOtherStocksView(data));
			}
		}
		return vecForReceiptOthS;
	}

	template<>
	std::vector<ReceiptOtherStocksListView> OrmasBL::GetAllDataForClass<ReceiptOtherStocksListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ReceiptOtherStocksListView> vecForReceiptOthSList;
		std::vector<DataLayer::receiptProductListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetReceiptOtherStocksList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForReceiptOthSList.push_back(ReceiptOtherStocksListView(data));
			}
		}
		return vecForReceiptOthSList;
	}

	template<>
	std::vector<ReceiptProductView> OrmasBL::GetAllDataForClass<ReceiptProductView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ReceiptProductView> vecForReceiptProduct;
		std::vector<DataLayer::receiptProductsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetReceiptProducts(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetReceiptProducts(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForReceiptProduct.push_back(ReceiptProductView(data));
			}
		}
		return vecForReceiptProduct;
	}

	template<>
	std::vector<ReceiptProductListView> OrmasBL::GetAllDataForClass<ReceiptProductListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ReceiptProductListView> vecForReceiptProducList;
		std::vector<DataLayer::receiptProductListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetReceiptProductList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetReceiptProductList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForReceiptProducList.push_back(ReceiptProductListView(data));
			}
		}
		return vecForReceiptProducList;
	}

	template<>
	std::vector<StockTransferView> OrmasBL::GetAllDataForClass<StockTransferView>(std::string& errorMessage, std::string filter)
	{
		std::vector<StockTransferView> vecForStockTransfer;
		std::vector<DataLayer::stockTransferViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetStockTransfer(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetStockTransfer(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStockTransfer.push_back(StockTransferView(data));
			}
		}
		return vecForStockTransfer;
	}

	template<>
	std::vector<StockTransferListView> OrmasBL::GetAllDataForClass<StockTransferListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<StockTransferListView> vecForStockTransferList;
		std::vector<DataLayer::stockTransferListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetStockTransferList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetStockTransferList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStockTransferList.push_back(StockTransferListView(data));
			}
		}
		return vecForStockTransferList;
	}

	template<>
	std::vector<RefundView> OrmasBL::GetAllDataForClass<RefundView>(std::string& errorMessage, std::string filter)
	{
		std::vector<RefundView> vecForRefund;
		std::vector<DataLayer::refundsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetRefunds(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetRefunds(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForRefund.push_back(RefundView(data));
			}
		}
		return vecForRefund;
	}

	template<>
	std::vector<RelationView> OrmasBL::GetAllDataForClass<RelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<RelationView> vecForRelation;
		std::vector<DataLayer::relationsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetRelations(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetRelations(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForRelation.push_back(RelationView(data));
			}
		}
		return vecForRelation;
	}

	template<>
	std::vector<RelationType> OrmasBL::GetAllDataForClass<RelationType>(std::string& errorMessage, std::string filter)
	{
		std::vector<RelationType> vecForRelationType;
		std::vector<DataLayer::relationTypeCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetRelationType(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetRelationType(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForRelationType.push_back(RelationType(data));
			}
		}
		return vecForRelationType;
	}


	template<>
	std::vector<ReturnView> OrmasBL::GetAllDataForClass<ReturnView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ReturnView> vecForReturn;
		std::vector<DataLayer::returnsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetReturns(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetReturns(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForReturn.push_back(ReturnView(data));
			}
		}
		return vecForReturn;
	}

	template<>
	std::vector<ReturnListView> OrmasBL::GetAllDataForClass<ReturnListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ReturnListView> vecForReturnList;
		std::vector<DataLayer::returnListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetReturnList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetReturnList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForReturnList.push_back(ReturnListView(data));
			}
		}
		return vecForReturnList;
	}

	template<>
	std::vector<Role> OrmasBL::GetAllDataForClass<Role>(std::string& errorMessage, std::string filter)
	{
		std::vector<Role> vecForRole;
		std::vector<DataLayer::rolesCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetRoles(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetRoles(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForRole.push_back(Role(data));
			}
		}
		return vecForRole;
	}

	template<>
	std::vector<SalaryView> OrmasBL::GetAllDataForClass<SalaryView>(std::string& errorMessage, std::string filter)
	{
		std::vector<SalaryView> vecForSalary;
		std::vector<DataLayer::salariesViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSalaries(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSalaries(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSalary.push_back(SalaryView(data));
			}
		}
		return vecForSalary;
	}

	template<>
	std::vector<ShareholderView> OrmasBL::GetAllDataForClass<ShareholderView>(std::string& errorMessage, std::string filter)
	{
		std::vector<ShareholderView> vecForSareholder;
		std::vector<DataLayer::shareholdersViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetShareholders(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetShareholders(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSareholder.push_back(ShareholderView(data));
			}
		}
		return vecForSareholder;
	}

	template<>
	std::vector<SalaryType> OrmasBL::GetAllDataForClass<SalaryType>(std::string& errorMessage, std::string filter)
	{
		std::vector<SalaryType> vecForSalaryType;
		std::vector<DataLayer::salaryTypeCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSalaryType(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSalaryType(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSalaryType.push_back(SalaryType(data));
			}
		}
		return vecForSalaryType;
	}

	template<>
	std::vector<SpecificationListView> OrmasBL::GetAllDataForClass<SpecificationListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<SpecificationListView> vecForSpecificationList;
		std::vector<DataLayer::specificationListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSpecificationList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSpecificationList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSpecificationList.push_back(SpecificationListView(data));
			}
		}
		return vecForSpecificationList;
	}

	template<>
	std::vector<SpecificationChangeLog> OrmasBL::GetAllDataForClass<SpecificationChangeLog>(std::string& errorMessage, std::string filter)
	{
		std::vector<SpecificationChangeLog> vecForSpecificationLog;
		std::vector<DataLayer::specificationChangeLogCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSpecificationChangeLog(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSpecificationChangeLog(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSpecificationLog.push_back(SpecificationChangeLog(data));
			}
		}
		return vecForSpecificationLog;
	}

	template<>
	std::vector<SpecificationView> OrmasBL::GetAllDataForClass<SpecificationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<SpecificationView> vecForSpecification;
		std::vector<DataLayer::specificationsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSpecifications(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSpecifications(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSpecification.push_back(SpecificationView(data));
			}
		}
		return vecForSpecification;
	}

	template<>
	std::vector<SpoilageListView> OrmasBL::GetAllDataForClass<SpoilageListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<SpoilageListView> vecForSpoilageList;
		std::vector<DataLayer::spoilageListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSpoilageList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSpoilageList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSpoilageList.push_back(SpoilageListView(data));
			}
		}
		return vecForSpoilageList;
	}

	template<>
	std::vector<SpoilageView> OrmasBL::GetAllDataForClass<SpoilageView>(std::string& errorMessage, std::string filter)
	{
		std::vector<SpoilageView> vecForSpoilage;
		std::vector<DataLayer::spoilageViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSpoilage(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSpoilage(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSpoilage.push_back(SpoilageView(data));
			}
		}
		return vecForSpoilage;
	}

	template<>
	std::vector<State> OrmasBL::GetAllDataForClass<State>(std::string& errorMessage, std::string filter)
	{
		std::vector<State> vecForState;
		std::vector<DataLayer::stateCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetState(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetState(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForState.push_back(State(data));
			}
		}
		return vecForState;
	}

	template<>
	std::vector<Status> OrmasBL::GetAllDataForClass<Status>(std::string& errorMessage, std::string filter)
	{
		std::vector<Status> vecForStatus;
		std::vector<DataLayer::statusCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetStatus(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetStatus(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStatus.push_back(Status(data));
			}
		}
		return vecForStatus;
	}

	template<>
	std::vector<StatusRuleView> OrmasBL::GetAllDataForClass<StatusRuleView>(std::string& errorMessage, std::string filter)
	{
		std::vector<StatusRuleView> vecForStatusRule;
		std::vector<DataLayer::statusRuleViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetStatusRule(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetStatusRule(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStatusRule.push_back(StatusRuleView(data));
			}
		}
		return vecForStatusRule;
	}

	template<>
	std::vector<StockView> OrmasBL::GetAllDataForClass<StockView>(std::string& errorMessage, std::string filter)
	{
		std::vector<StockView> vecForStock;
		std::vector<DataLayer::stockViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetStock(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetStock(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStock.push_back(StockView(data));
			}
		}
		return vecForStock;
	}

	template<>
	std::vector<StockLimitView> OrmasBL::GetAllDataForClass<StockLimitView>(std::string& errorMessage, std::string filter)
	{
		std::vector<StockLimitView> vecForStockLimit;
		std::vector<DataLayer::stockLimitViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetStockLimit(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetStockLimit(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStockLimit.push_back(StockLimitView(data));
			}
		}
		return vecForStockLimit;
	}

	template<>
	std::vector<StockHistoryView> OrmasBL::GetAllDataForClass<StockHistoryView>(std::string& errorMessage, std::string filter)
	{
		std::vector<StockHistoryView> vecForStockHistory;
		std::vector<DataLayer::stockHistoryViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetStockHistory(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetStockHistory(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStockHistory.push_back(StockHistoryView(data));
			}
		}
		return vecForStockHistory;
	}

	template<>
	std::vector<StockChangeLog> OrmasBL::GetAllDataForClass<StockChangeLog>(std::string& errorMessage, std::string filter)
	{
		std::vector<StockChangeLog> vecForStockLog;
		std::vector<DataLayer::stockChangeLogCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetStockChangeLog(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetStockChangeLog(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStockLog.push_back(StockChangeLog(data));
			}
		}
		return vecForStockLog;
	}

	template<>
	std::vector<SubaccountView> OrmasBL::GetAllDataForClass<SubaccountView>(std::string& errorMessage, std::string filter)
	{
		std::vector<SubaccountView> vecForSubaccount;
		std::vector<DataLayer::subaccountsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSubaccounts(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSubaccounts(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSubaccount.push_back(SubaccountView(data));
			}
		}
		return vecForSubaccount;
	}

	template<>
	std::vector<SubaccountLimitView> OrmasBL::GetAllDataForClass<SubaccountLimitView>(std::string& errorMessage, std::string filter)
	{
		std::vector<SubaccountLimitView> vecForSubaccountLimit;
		std::vector<DataLayer::subaccountLimitViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSubaccountLimit(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSubaccountLimit(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSubaccountLimit.push_back(SubaccountLimitView(data));
			}
		}
		return vecForSubaccountLimit;
	}

	template<>
	std::vector<SubaccountChangeLog> OrmasBL::GetAllDataForClass<SubaccountChangeLog>(std::string& errorMessage, std::string filter)
	{
		std::vector<SubaccountChangeLog> vecForSubaccountLog;
		std::vector<DataLayer::subaccountChangeLogCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSubaccountChangeLog(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSubaccountChangeLog(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSubaccountLog.push_back(SubaccountChangeLog(data));
			}
		}
		return vecForSubaccountLog;
	}

	template<>
	std::vector<SubaccountHistory> OrmasBL::GetAllDataForClass<SubaccountHistory>(std::string& errorMessage, std::string filter)
	{
		std::vector<SubaccountHistory> vecForSubaccountHis;
		std::vector<DataLayer::subaccountHistoryCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetSubaccountHistory(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetSubaccountHistory(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForSubaccountHis.push_back(SubaccountHistory(data));
			}
		}
		return vecForSubaccountHis;
	}

	template<>
	std::vector<Tax> OrmasBL::GetAllDataForClass<Tax>(std::string& errorMessage, std::string filter)
	{
		std::vector<Tax> vecForTax;
		std::vector<DataLayer::taxesCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetTaxes(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetTaxes(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForTax.push_back(Tax(data));
			}
		}
		return vecForTax;
	}


	template<>
	std::vector<TimesheetView> OrmasBL::GetAllDataForClass<TimesheetView>(std::string& errorMessage, std::string filter)
	{
		std::vector<TimesheetView> vecForStock;
		std::vector<DataLayer::timesheetViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetTimesheet(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetTimesheet(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForStock.push_back(TimesheetView(data));
			}
		}
		return vecForStock;
	}

	template<>
	std::vector<TransportView> OrmasBL::GetAllDataForClass<TransportView>(std::string& errorMessage, std::string filter)
	{
		std::vector<TransportView> vecForTransport;
		std::vector<DataLayer::transportsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetTransports(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetTransports(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForTransport.push_back(TransportView(data));
			}
		}
		return vecForTransport;
	}
	
	template<>
	std::vector<TransportHistory> OrmasBL::GetAllDataForClass<TransportHistory>(std::string& errorMessage, std::string filter)
	{
		std::vector<TransportHistory> vecForTransport;
		std::vector<DataLayer::transportHistoryCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetTransportHistory(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetTransportHistory(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForTransport.push_back(TransportHistory(data));
			}
		}
		return vecForTransport;
	}

	template<>
	std::vector<TransportChangeLog> OrmasBL::GetAllDataForClass<TransportChangeLog>(std::string& errorMessage, std::string filter)
	{
		std::vector<TransportChangeLog> vecForTransportLog;
		std::vector<DataLayer::transportChangeLogCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetTransportChangeLog(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetTransportChangeLog(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForTransportLog.push_back(TransportChangeLog(data));
			}
		}
		return vecForTransportLog;
	}

	template<>
	std::vector<TransportListView> OrmasBL::GetAllDataForClass<TransportListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<TransportListView> vecForTransportList;
		std::vector<DataLayer::transportListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetTransportList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetTransportList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForTransportList.push_back(TransportListView(data));
			}
		}
		return vecForTransportList;
	}

	template<>
	std::vector<UserView> OrmasBL::GetAllDataForClass<UserView>(std::string& errorMessage, std::string filter)
	{
		std::vector<UserView> vecForUser;
		std::vector<DataLayer::usersViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetUsers(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetUsers(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForUser.push_back(UserView(data));
			}
		}
		return vecForUser;
	}

	template<>
	std::vector<UserExtendedView> OrmasBL::GetAllDataForClass<UserExtendedView>(std::string& errorMessage, std::string filter)
	{
		std::vector<UserExtendedView> vecForUser;
		std::vector<DataLayer::userExtendedViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetUserExtended(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetUserExtended(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForUser.push_back(UserExtendedView(data));
			}
		}
		return vecForUser;
	}

	template<>
	std::vector<UserGroupRelationView> OrmasBL::GetAllDataForClass<UserGroupRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<UserGroupRelationView> vecForUserGroup;
		std::vector<DataLayer::userGroupViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetUserGroup(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetUserGroup(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForUserGroup.push_back(UserGroupRelationView(data));
			}
		}
		return vecForUserGroup;
	}
	
	template<>
	std::vector<WarehouseView> OrmasBL::GetAllDataForClass<WarehouseView>(std::string& errorMessage, std::string filter)
	{
		std::vector<WarehouseView> vecForWarehouse;
		std::vector<DataLayer::warehouseViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetWarehouse(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetWarehouse(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForWarehouse.push_back(WarehouseView(data));
			}
		}
		return vecForWarehouse;
	}

	template<>
	std::vector<WarehouseType> OrmasBL::GetAllDataForClass<WarehouseType>(std::string& errorMessage, std::string filter)
	{
		std::vector<WarehouseType> vecForWarehouseType;
		std::vector<DataLayer::warehouseTypeCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetWarehouseType(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetWarehouseType(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForWarehouseType.push_back(WarehouseType(data));
			}
		}
		return vecForWarehouseType;
	}

	template<>
	std::vector<WarehouseEmployeeRelationView> OrmasBL::GetAllDataForClass<WarehouseEmployeeRelationView>(std::string& errorMessage, std::string filter)
	{
		std::vector<WarehouseEmployeeRelationView> vecForWarehouseRel;
		std::vector<DataLayer::warehouseEmployeeViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetWarehouseEmployee(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForWarehouseRel.push_back(WarehouseEmployeeRelationView(data));
			}
		}
		return vecForWarehouseRel;
	}
	
	template<>
	std::vector<WithdrawalView> OrmasBL::GetAllDataForClass<WithdrawalView>(std::string& errorMessage, std::string filter)
	{
		std::vector<WithdrawalView> vecForWithdrawal;
		std::vector<DataLayer::withdrawalsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetWithdrawals(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetWithdrawals(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForWithdrawal.push_back(WithdrawalView(data));
			}
		}
		return vecForWithdrawal;
	}

	template<>
	std::vector<WriteOffView> OrmasBL::GetAllDataForClass<WriteOffView>(std::string& errorMessage, std::string filter)
	{
		std::vector<WriteOffView> vecForWriteOff;
		std::vector<DataLayer::writeOffsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetWriteOffs(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetWriteOffs(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForWriteOff.push_back(WriteOffView(data));
			}
		}
		return vecForWriteOff;
	}

	template<>
	std::vector<WriteOffListView> OrmasBL::GetAllDataForClass<WriteOffListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<WriteOffListView> vecForWriteOffList;
		std::vector<DataLayer::writeOffListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetWriteOffList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetWriteOffList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForWriteOffList.push_back(WriteOffListView(data));
			}
		}
		return vecForWriteOffList;
	}

	template<>
	std::vector<WriteOffRawView> OrmasBL::GetAllDataForClass<WriteOffRawView>(std::string& errorMessage, std::string filter)
	{
		std::vector<WriteOffRawView> vecForWriteOffRaw;
		std::vector<DataLayer::writeOffRawsViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetWriteOffRaws(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetWriteOffRaws(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForWriteOffRaw.push_back(WriteOffRawView(data));
			}
		}
		return vecForWriteOffRaw;
	}

	template<>
	std::vector<WriteOffRawListView> OrmasBL::GetAllDataForClass<WriteOffRawListView>(std::string& errorMessage, std::string filter)
	{
		std::vector<WriteOffRawListView> vecForWriteOffRawList;
		std::vector<DataLayer::writeOffListViewCollection> dataCollection;
		if (filter.empty())
		{
			dataCollection = ormasDal.GetWriteOffRawList(errorMessage);
		}
		else
		{
			dataCollection = ormasDal.GetWriteOffRawList(errorMessage, filter);
		}
		if (!dataCollection.empty()){
			for (auto data : dataCollection)
			{
				vecForWriteOffRawList.push_back(WriteOffRawListView(data));
			}
		}
		return vecForWriteOffRawList;
	}

	/// \brief	Creates the access.///
	///
	/// \param [in,out] access			If non-null, the access.
	/// \param [in,out] errorMessage	Message describing the error.
	///
	/// \return	true if it succeeds, false if it fails.
	
	bool OrmasBL::CreateAccess(BusinessLayer::Access* access, std::string& errorMessage)
	{
		try
		{
			if (0 != access->GetRoleID() && 0 != access->GetAccessItemID())
			{
				return access->CreateAccess(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Access item or role must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccess(BusinessLayer::Access* access, std::string& errorMessage)
	{
		try
		{
			if (0 != access->GetRoleID() && 0 != access->GetAccessItemID())
			{
				return access->UpdateAccess(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Access item or role must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccess(BusinessLayer::Access* access, std::string& errorMessage)
	{
		try
		{
			if (0 != access->GetID())
			{
				return access->DeleteAccess(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Access ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}
	
	bool OrmasBL::CreateAccessItem(BusinessLayer::AccessItem* accessItem, std::string& errorMessage)
	{
		try
		{
			if (!accessItem->GetNameEng().empty() && !accessItem->GetNameRu().empty() && !accessItem->GetDivision().empty())
			{
				return accessItem->CreateAccessItem(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! English item name or Russiam item name also division must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccessItem(BusinessLayer::AccessItem* accessItem, std::string& errorMessage)
	{
		try
		{
			if (!accessItem->GetNameEng().empty() && !accessItem->GetNameRu().empty() && !accessItem->GetDivision().empty())
			{
				return accessItem->UpdateAccessItem(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! English item name or Russiam item name also division must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccessItem(BusinessLayer::AccessItem* accessItem, std::string& errorMessage)
	{
		try
		{
			if (0 != accessItem->GetID())
			{
				return accessItem->DeleteAccessItem(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Access item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateAccount(BusinessLayer::Account* account, std::string& errorMessage)
	{
		try
		{
			if (!account->GetNumber().empty())
			{
				return account->CreateAccount(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccount(BusinessLayer::Account* account, std::string& errorMessage)
	{
		try
		{
			if (!account->GetNumber().empty())
			{
				return account->UpdateAccount(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccount(BusinessLayer::Account* account, std::string& errorMessage)
	{
		try
		{
			if (0 != account->GetID())
			{
				return account->DeleteAccount(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Account item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateAccountable(BusinessLayer::Accountable* accountable, std::string& errorMessage)
	{
		try
		{
			if (0 != accountable->GetEmployeeID())
			{
				return accountable->CreateAccountable(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccountable(BusinessLayer::Accountable* accountable, std::string& errorMessage)
	{
		try
		{
			if (0 != accountable->GetEmployeeID())
			{
				return accountable->UpdateAccountable(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccountable(BusinessLayer::Accountable* accountable, std::string& errorMessage)
	{
		try
		{
			if (0 != accountable->GetID())
			{
				return accountable->DeleteAccountable(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Accountable item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}


	bool OrmasBL::CreateAccountableUnionDocument(BusinessLayer::AccountableUnionDocument* aUnionDoc, std::string& errorMessage)
	{
		try
		{
			if (!aUnionDoc->IsEmpty())
			{
				return aUnionDoc->CreateAccountableUnionDocument(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccountableUnionDocument(BusinessLayer::AccountableUnionDocument* aUnionDoc, std::string& errorMessage)
	{
		try
		{
			if (!aUnionDoc->IsEmpty())
			{
				return aUnionDoc->UpdateAccountableUnionDocument(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccountableUnionDocument(BusinessLayer::AccountableUnionDocument* aUnionDoc, std::string& errorMessage)
	{
		try
		{
			if (0 != aUnionDoc->GetAccountableDocument()->GetID())
			{
				return aUnionDoc->DeleteAccountableUnionDocument(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Accountable item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	/*bool OrmasBL::CreateAccountableTransaction(BusinessLayer::AccountableTransaction* accountableTransaction, std::string& errorMessage)
	{
		try
		{
			if (0 != accountableTransaction->GetAccountableID() && 0 != accountableTransaction->GetStartValue() &&
				accountableTransaction->GetEndValue() && 0 != accountableTransaction->GetOperationID())
			{
				return accountableTransaction->CreateAccountableTransaction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccountableTransaction(BusinessLayer::AccountableTransaction* accountableTransaction, std::string& errorMessage)
	{
		try
		{
			if (0 != accountableTransaction->GetAccountableID() && 0 != accountableTransaction->GetStartValue() &&
				accountableTransaction->GetEndValue() && 0 != accountableTransaction->GetOperationID())
			{
				return accountableTransaction->UpdateAccountableTransaction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccountableTransaction(BusinessLayer::AccountableTransaction* accountableTransaction, std::string& errorMessage)
	{
		try
		{
			if (0 != accountableTransaction->GetID())
			{
				return accountableTransaction->DeleteAccountableTransaction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Accountable transaction item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}*/

	bool OrmasBL::CreateAccountHistory(BusinessLayer::AccountHistory* accountHis, std::string& errorMessage)
	{
		try
		{
			if (!accountHis->GetNumber().empty() && !accountHis->GetFromDate().empty()
				&& !accountHis->GetTillDate().empty())
			{
				return accountHis->CreateAccountHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccountHistory(BusinessLayer::AccountHistory* accountHis, std::string& errorMessage)
	{
		try
		{
			if (!accountHis->GetNumber().empty() && !accountHis->GetFromDate().empty()
				&& !accountHis->GetTillDate().empty())
			{
				return accountHis->UpdateAccountHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccountHistory(BusinessLayer::AccountHistory* accountHis, std::string& errorMessage)
	{
		try
		{
			if (0 != accountHis->GetID())
			{
				return accountHis->DeleteAccountHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Account history item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateAccountChangeLog(BusinessLayer::AccountChangeLog* accountLog, std::string& errorMessage)
	{
		try
		{
			if (!accountLog->GetAccountID() != 0 && !accountLog->GetLogDate().empty())
			{
				return accountLog->CreateAccountChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccountChangeLog(BusinessLayer::AccountChangeLog* accountLog, std::string& errorMessage)
	{
		try
		{
			if (!accountLog->GetAccountID() != 0 && !accountLog->GetLogDate().empty())
			{
				return accountLog->UpdateAccountChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccountChangeLog(BusinessLayer::AccountChangeLog* accountLog, std::string& errorMessage)
	{
		try
		{
			if (0 != accountLog->GetID())
			{
				return accountLog->DeleteAccountChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Account change log item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateAccountType(BusinessLayer::AccountType* accountType, std::string& errorMessage)
	{
		try
		{
			if (!accountType->GetName().empty() && 0 != accountType->GetNumber())
			{
				return accountType->CreateAccountType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name and number fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAccountType(BusinessLayer::AccountType* accountType, std::string& errorMessage)
	{
		try
		{
			if (!accountType->GetName().empty() && 0 != accountType->GetNumber())
			{
				return accountType->UpdateAccountType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name and number fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAccountType(BusinessLayer::AccountType* accountType, std::string& errorMessage)
	{
		try
		{
			if (0 != accountType->GetID())
			{
				return accountType->DeleteAccountType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Account type item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateAmortizeGroup(BusinessLayer::AmortizeGroup* amortizeGroup, std::string& errorMessage)
	{
		try
		{
			if (0 != amortizeGroup->GetGroupNumber() && 0 != amortizeGroup->GetFromMonth() && 0 != amortizeGroup->GetToMonth())
			{
				return amortizeGroup->CreateAmortizeGroup(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Group number and month count fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAmortizeGroup(BusinessLayer::AmortizeGroup* amortizeGroup, std::string& errorMessage)
	{
		try
		{
			if (0 != amortizeGroup->GetGroupNumber() && 0 != amortizeGroup->GetFromMonth() && 0 != amortizeGroup->GetToMonth())
			{
				return amortizeGroup->UpdateAmortizeGroup(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Group number and month count fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAmortizeGroup(BusinessLayer::AmortizeGroup* amortizeGroup, std::string& errorMessage)
	{
		try
		{
			if (0 != amortizeGroup->GetID())
			{
				return amortizeGroup->DeleteAmortizeGroup(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Amortize group item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateAmortizeType(BusinessLayer::AmortizeType* amortizeType, std::string& errorMessage)
	{
		try
		{
			if (!amortizeType->GetName().empty() && !amortizeType->GetCode().empty())
			{
				return amortizeType->CreateAmortizeType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Amortize type name and code fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateAmortizeType(BusinessLayer::AmortizeType* amortizeType, std::string& errorMessage)
	{
		try
		{
			if (!amortizeType->GetName().empty() && !amortizeType->GetCode().empty())
			{
				return amortizeType->UpdateAmortizeType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Amortize type name and code fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteAmortizeType(BusinessLayer::AmortizeType* amortizeType, std::string& errorMessage)
	{
		try
		{
			if (0 != amortizeType->GetID())
			{
				return amortizeType->DeleteAmortizeType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Amortize type item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateBalance(BusinessLayer::Balance* balance, std::string& errorMessage)
	{
		try
		{
			if (0 != balance->GetUserID() && 0 != balance->GetSubaccountID())
			{
				return balance->CreateBalance(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User, account and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateBalance(BusinessLayer::Balance* balance, std::string& errorMessage)
	{
		try
		{
			if (0 != balance->GetUserID() && 0 != balance->GetSubaccountID())
			{
				return balance->UpdateBalance(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User, account and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteBalance(BusinessLayer::Balance* balance, std::string& errorMessage)
	{
		try
		{
			if (0 != balance->GetID())
			{
				return balance->DeleteBalance(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Balance ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateBranch(BusinessLayer::Branch* branch, std::string& errorMessage)
	{
		try
		{
			if (!branch->GetName().empty() && !branch->GetAddress().empty() && !branch->GetPhone().empty())
			{
				return branch->CreateBranch(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name, address and phone must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateBranch(BusinessLayer::Branch* branch, std::string& errorMessage)
	{
		try
		{
			if (!branch->GetName().empty() && !branch->GetAddress().empty() && !branch->GetPhone().empty())
			{
				return branch->UpdateBranch(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error!  Name, address and phone must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteBranch(BusinessLayer::Branch* branch, std::string& errorMessage)
	{
		try
		{
			if (0 != branch->GetID())
			{
				return branch->DeleteBranch(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Branch ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateBranchSubaccount(BusinessLayer::BranchSubaccountRelation* branchSubaccount, std::string& errorMessage)
	{
		try
		{
			if (0 != branchSubaccount->GetBranchID() && 0 != branchSubaccount->GetSubaccountID())
			{
				return branchSubaccount->CreateBranchSubaccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Branch-Subaccount relation branch ID and subaccount ID  must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateBranchSubaccount(BusinessLayer::BranchSubaccountRelation* branchSubaccount, std::string& errorMessage)
	{
		try
		{
			if (0 != branchSubaccount->GetBranchID() && 0 != branchSubaccount->GetSubaccountID())
			{
				return branchSubaccount->UpdateBranchSubaccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Branch-Subaccount relation branch ID and subaccount ID  must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteBranchSubaccount(BusinessLayer::BranchSubaccountRelation* branchSubaccount, std::string& errorMessage)
	{
		try
		{
			if (0 != branchSubaccount->GetID())
			{
				return branchSubaccount->DeleteBranchSubaccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Branch-Subaccount  relation ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateBorrower(BusinessLayer::Borrower* borrower, std::string& errorMessage)
	{
		try
		{
			if (0 != borrower->GetUserID() || (!borrower->GetName().empty() && !borrower->GetAddress().empty() && !borrower->GetPhone().empty()))
			{
				return borrower->CreateBorrower(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name, address and phone must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateBorrower(BusinessLayer::Borrower* borrower, std::string& errorMessage)
	{
		try
		{
			if (0 != borrower->GetUserID() || (!borrower->GetName().empty() && !borrower->GetAddress().empty() && !borrower->GetPhone().empty()))
			{
				return borrower->UpdateBorrower(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error!  Name, address and phone must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteBorrower(BusinessLayer::Borrower* borrower, std::string& errorMessage)
	{
		try
		{
			if (0 != borrower->GetID())
			{
				return borrower->DeleteBorrower(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Borrower ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateCashbox(BusinessLayer::Cashbox* cashbox, std::string& errorMessage)
	{
		try
		{
			if (0 != cashbox->GetSubaccountID() && !cashbox->GetAddress().empty())
			{
				return cashbox->CreateCashbox(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Subaccount, address must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateCashbox(BusinessLayer::Cashbox* cashbox, std::string& errorMessage)
	{
		try
		{
			if (0 != cashbox->GetSubaccountID() && !cashbox->GetAddress().empty())
			{
				return cashbox->UpdateCashbox(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Subaccount, address must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteCashbox(BusinessLayer::Cashbox* cashbox, std::string& errorMessage)
	{
		try
		{
			if (0 != cashbox->GetID())
			{
				return cashbox->DeleteCashbox(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Cashbox ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateCashboxTransaction(BusinessLayer::CashboxTransaction* cashboxTransaction, std::string& errorMessage)
	{
		try
		{
			if (0 != cashboxTransaction->GetAccountantID() && 0 != cashboxTransaction->GetCashboxID()
				&& 0 != cashboxTransaction->GetCashierID() && 0 != cashboxTransaction->GetOwnerID())
			{
				return cashboxTransaction->CreateCashboxTransaction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Cashier ID, cahbox ID, accountant ID and owner ID  must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateCashboxTransaction(BusinessLayer::CashboxTransaction* cashboxTransaction, std::string& errorMessage)
	{
		try
		{
			if (0 != cashboxTransaction->GetAccountantID() && 0 != cashboxTransaction->GetCashboxID()
				&& 0 != cashboxTransaction->GetCashierID() && 0 != cashboxTransaction->GetOwnerID())
			{
				return cashboxTransaction->UpdateCashboxTransaction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Cashier ID, cahbox ID, accountant ID and owner ID  must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteCashboxTransaction(BusinessLayer::CashboxTransaction* cashboxTransaction, std::string& errorMessage)
	{
		try
		{
			if (0 != cashboxTransaction->GetID())
			{
				return cashboxTransaction->DeleteCashboxTransaction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Cashbox transaction ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateCashboxEmployeeRelation(BusinessLayer::CashboxEmployeeRelation* ceRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != ceRelation->GetCashboxID() && 0 != ceRelation->GetEmployeeID())
			{
				return ceRelation->CreateCashboxEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Cashbox and employee must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateCashboxEmployeeRelation(BusinessLayer::CashboxEmployeeRelation* ceRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != ceRelation->GetCashboxID() && 0 != ceRelation->GetEmployeeID())
			{
				return ceRelation->UpdateCashboxEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Cashbox and employee must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteCashboxEmployeeRelation(BusinessLayer::CashboxEmployeeRelation* ceRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != ceRelation->GetCashboxID() && 0 != ceRelation->GetEmployeeID())
			{
				return ceRelation->DeleteCashboxEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company account relation ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateChartOfAccounts(BusinessLayer::ChartOfAccounts* chartOfAccounts, std::string& errorMessage)
	{
		try
		{
			if (!chartOfAccounts->GetNumber().empty() && 0 != chartOfAccounts->GetAccountTypeID() && !chartOfAccounts->GetName().empty())
			{
				return chartOfAccounts->CreateChartOfAccounts(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name, number and account type ID must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateChartOfAccounts(BusinessLayer::ChartOfAccounts* chartOfAccounts, std::string& errorMessage)
	{
		try
		{
			if (!chartOfAccounts->GetNumber().empty() && 0 != chartOfAccounts->GetAccountTypeID() && !chartOfAccounts->GetName().empty())
			{
				return chartOfAccounts->UpdateChartOfAccounts(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name, number and account type ID must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteChartOfAccounts(BusinessLayer::ChartOfAccounts* chartOfAccounts, std::string& errorMessage)
	{
		try
		{
			if (0 != chartOfAccounts->GetID())
			{
				return chartOfAccounts->DeleteChartOfAccounts(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Chart of accounts ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateClient(BusinessLayer::Client* client, std::string& errorMessage)
	{
		try
		{
			if (!client->GetName().empty() && !client->GetSurname().empty() && !client->GetPhone().empty()
				&& !client->GetAddress().empty() && !client->GetPassword().empty() && 0 != client->GetRoleID() && !client->GetFirm().empty()
				&& 0 != client->GetLocationID())
			{
				return client->CreateClient(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateClient(BusinessLayer::Client* client, std::string& errorMessage)
	{
		try
		{
			if (!client->GetName().empty() && !client->GetSurname().empty() && !client->GetPhone().empty()
				&& !client->GetAddress().empty() && !client->GetPassword().empty() && 0 != client->GetRoleID() && !client->GetFirm().empty()
				&& 0 != client->GetLocationID())
			{
				return client->UpdateClient(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteClient(BusinessLayer::Client* client, std::string& errorMessage)
	{
		try
		{
			if (0 != client->GetID())
			{
				return client->DeleteClient(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Client ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateCompanyAccountRelation(BusinessLayer::CompanyAccountRelation* caRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != caRelation->GetCompanyID() && 0 != caRelation->GetAccountID())
			{
				return caRelation->CreateCompanyAccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company and account must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateCompanyAccountRelation(BusinessLayer::CompanyAccountRelation* caRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != caRelation->GetAccountID() && 0 != caRelation->GetCompanyID())
			{
				return caRelation->UpdateCompanyAccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company and account must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteCompanyAccountRelation(BusinessLayer::CompanyAccountRelation* caRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != caRelation->GetCompanyID() && 0 != caRelation->GetAccountID())
			{
				return caRelation->DeleteCompanyAccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company account relation ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	/// \brief	Creates a company. Creation section
	///
	/// \param [in,out] company			If non-null, the company.
	/// \param [in,out] errorMessage	Message describing the error.
	///
	/// \return	true if it succeeds, false if it fails.

	bool OrmasBL::CreateCompany(BusinessLayer::Company* company, std::string& errorMessage)
	{
		try
		{
			if (!company->GetName().empty() && !company->GetAddress().empty() && !company->GetPhone().empty())
			{
				return company->CreateCompany(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company name, address and phone must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateCompany(BusinessLayer::Company* company, std::string& errorMessage)
	{
		try
		{
			if (!company->GetName().empty() && !company->GetAddress().empty() && !company->GetPhone().empty())
			{
				return company->UpdateCompany(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company name, address and phone must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteCompany(BusinessLayer::Company* company, std::string& errorMessage)
	{
		try
		{
			if (0 != company->GetID())
			{
				return company->DeleteCompany(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateCompanyEmployeeRelation(BusinessLayer::CompanyEmployeeRelation* ceRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != ceRelation->GetEmployeeID() && 0 != ceRelation->GetCompanyID())
			{
				return ceRelation->CreateCompanyEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company and employee must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateCompanyEmployeeRelation(BusinessLayer::CompanyEmployeeRelation* ceRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != ceRelation->GetEmployeeID() && 0 != ceRelation->GetCompanyID())
			{
				return ceRelation->UpdateCompanyEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company and employee must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteCompanyEmployeeRelation(BusinessLayer::CompanyEmployeeRelation* ceRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != ceRelation->GetEmployeeID() && 0 != ceRelation->GetCompanyID())
			{
				return ceRelation->DeleteCompanyEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Company id or employee id is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateConsumeProduct(BusinessLayer::ConsumeProduct* consumeProduct, std::string& errorMessage)
	{
		try
		{
			if (!consumeProduct->GetDate().empty() && 0 != consumeProduct->GetEmployeeID() && 0 != consumeProduct->GetCount()
				&& 0 != consumeProduct->GetSum() && 0 != consumeProduct->GetStatusID() && 0 != consumeProduct->GetCurrencyID()
				&& 0 != consumeProduct->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, consumeProduct->GetCurrencyID(), errorMessage))
				{
					roundSum = round(consumeProduct->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				consumeProduct->SetSum(roundSum);
				return consumeProduct->CreateConsumeProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateConsumeProduct(BusinessLayer::ConsumeProduct* consumeProduct, std::string& errorMessage)
	{
		try
		{
			if (!consumeProduct->GetDate().empty() && 0 != consumeProduct->GetEmployeeID() && 0 != consumeProduct->GetCount()
				&& 0 != consumeProduct->GetSum() && 0 != consumeProduct->GetStatusID() && 0 != consumeProduct->GetCurrencyID()
				&& 0 != consumeProduct->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, consumeProduct->GetCurrencyID(), errorMessage))
				{
					roundSum = round(consumeProduct->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				consumeProduct->SetSum(roundSum);
				return consumeProduct->UpdateConsumeProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteConsumeProduct(BusinessLayer::ConsumeProduct* consumeProduct, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeProduct->GetID())
			{
				return consumeProduct->DeleteConsumeProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Consume product ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateConsumeProductList(BusinessLayer::ConsumeProductList* consumeProductList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeProductList->GetConsumeProductID() && 0 != consumeProductList->GetProductID()
				&& 0 != consumeProductList->GetCount() && 0 != consumeProductList->GetSum() && 0 != consumeProductList->GetStatusID()
				&& 0 != consumeProductList->GetCurrencyID())
			{
				return consumeProductList->CreateConsumeProductList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateConsumeProductList(BusinessLayer::ConsumeProductList* consumeProductList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeProductList->GetConsumeProductID() && 0 != consumeProductList->GetProductID()
				&& 0 != consumeProductList->GetCount() && 0 != consumeProductList->GetSum() && 0 != consumeProductList->GetStatusID()
				&& 0 != consumeProductList->GetCurrencyID())
			{
				return consumeProductList->UpdateConsumeProductList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteConsumeProductList(BusinessLayer::ConsumeProductList* consumeProductList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeProductList->GetID())
			{
				return consumeProductList->DeleteConsumeProductList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Consume product list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateConsumeRaw(BusinessLayer::ConsumeRaw* consumeRaw, std::string& errorMessage)
	{
		try
		{
			if (!consumeRaw->GetDate().empty() && 0 != consumeRaw->GetEmployeeID() && 0 != consumeRaw->GetCount()
				&& 0 != consumeRaw->GetSum() && 0 != consumeRaw->GetStatusID() && 0 != consumeRaw->GetCurrencyID()
				&& 0 != consumeRaw->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, consumeRaw->GetCurrencyID(), errorMessage))
				{
					roundSum = round(consumeRaw->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				consumeRaw->SetSum(roundSum);
				return consumeRaw->CreateConsumeRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateConsumeRaw(BusinessLayer::ConsumeRaw* consumeRaw, std::string& errorMessage)
	{
		try
		{
			if (!consumeRaw->GetDate().empty() && 0 != consumeRaw->GetEmployeeID() && 0 != consumeRaw->GetCount()
				&& 0 != consumeRaw->GetSum() && 0 != consumeRaw->GetStatusID() && 0 != consumeRaw->GetCurrencyID()
				&& 0 != consumeRaw->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, consumeRaw->GetCurrencyID(), errorMessage))
				{
					roundSum = round(consumeRaw->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				consumeRaw->SetSum(roundSum);
				return consumeRaw->UpdateConsumeRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteConsumeRaw(BusinessLayer::ConsumeRaw* consumeRaw, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeRaw->GetID())
			{
				return consumeRaw->DeleteConsumeRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Consume raw ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateConsumeRawList(BusinessLayer::ConsumeRawList* consumeRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeRawList->GetConsumeRawID() && 0 != consumeRawList->GetProductID()
				&& 0 != consumeRawList->GetCount() && 0 != consumeRawList->GetSum() && 0 != consumeRawList->GetStatusID()
				&& 0 != consumeRawList->GetCurrencyID())
			{
				return consumeRawList->CreateConsumeRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateConsumeRawList(BusinessLayer::ConsumeRawList* consumeRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeRawList->GetConsumeRawID() && 0 != consumeRawList->GetProductID()
				&& 0 != consumeRawList->GetCount() && 0 != consumeRawList->GetSum() && 0 != consumeRawList->GetStatusID()
				&& 0 != consumeRawList->GetCurrencyID())
			{
				return consumeRawList->UpdateConsumeRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteConsumeRawList(BusinessLayer::ConsumeRawList* consumeRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeRawList->GetID())
			{
				return consumeRawList->DeleteConsumeRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Consume raw list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateCurrency(BusinessLayer::Currency* currency, std::string& errorMessage)
	{
		try
		{
			if (0 != currency->GetCode() && !currency->GetName().empty() && !currency->GetShortName().empty() && 0 != currency->GetUnit())
			{
				return currency->CreateCurrency(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Currency code, name and short name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateConsumeOtherStocks(BusinessLayer::ConsumeOtherStocks* consumeOthS, std::string& errorMessage)
	{
		try
		{
			if (!consumeOthS->GetDate().empty() && 0 != consumeOthS->GetEmployeeID() && 0 != consumeOthS->GetCount()
				&& 0 != consumeOthS->GetSum() && 0 != consumeOthS->GetStatusID() && 0 != consumeOthS->GetCurrencyID()
				&& 0 != consumeOthS->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, consumeOthS->GetCurrencyID(), errorMessage))
				{
					roundSum = round(consumeOthS->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				consumeOthS->SetSum(roundSum);
				return consumeOthS->CreateConsumeOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateConsumeOtherStocks(BusinessLayer::ConsumeOtherStocks* consumeOthS, std::string& errorMessage)
	{
		try
		{
			if (!consumeOthS->GetDate().empty() && 0 != consumeOthS->GetEmployeeID() && 0 != consumeOthS->GetCount()
				&& 0 != consumeOthS->GetSum() && 0 != consumeOthS->GetStatusID() && 0 != consumeOthS->GetCurrencyID()
				&& 0 != consumeOthS->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, consumeOthS->GetCurrencyID(), errorMessage))
				{
					roundSum = round(consumeOthS->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				consumeOthS->SetSum(roundSum);
				return consumeOthS->UpdateConsumeOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteConsumeOtherStocks(BusinessLayer::ConsumeOtherStocks* consumeOthS, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeOthS->GetID())
			{
				return consumeOthS->DeleteConsumeOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Consume other stocks ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateConsumeOtherStocksList(BusinessLayer::ConsumeOtherStocksList* consumeOthSList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeOthSList->GetConsumeOtherStocksID() && 0 != consumeOthSList->GetOtherStocksID()
				&& 0 != consumeOthSList->GetCount() && 0 != consumeOthSList->GetSum() && 0 != consumeOthSList->GetStatusID()
				&& 0 != consumeOthSList->GetCurrencyID())
			{
				return consumeOthSList->CreateConsumeOtherStocksList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateConsumeOtherStocksList(BusinessLayer::ConsumeOtherStocksList* consumeOthSList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeOthSList->GetConsumeOtherStocksID() && 0 != consumeOthSList->GetOtherStocksID()
				&& 0 != consumeOthSList->GetCount() && 0 != consumeOthSList->GetSum() && 0 != consumeOthSList->GetStatusID()
				&& 0 != consumeOthSList->GetCurrencyID())
			{
				return consumeOthSList->UpdateConsumeOtherStocksList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteConsumeOtherStocksList(BusinessLayer::ConsumeOtherStocksList* consumeOthSList, std::string& errorMessage)
	{
		try
		{
			if (0 != consumeOthSList->GetID())
			{
				return consumeOthSList->DeleteConsumeOtherStocksList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Consume other stocks list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	
	bool OrmasBL::UpdateCurrency(BusinessLayer::Currency* currency, std::string& errorMessage)
	{
		try
		{
			if (0 != currency->GetCode() && !currency->GetName().empty() && !currency->GetShortName().empty() && 0 != currency->GetUnit())
			{
				return currency->UpdateCurrency(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Currency code, name and short name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteCurrency(BusinessLayer::Currency* currency, std::string& errorMessage)
	{
		try
		{
			if (0 != currency->GetID())
			{
				return currency->DeleteCurrency(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Currency ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateCreditor(BusinessLayer::Creditor* creditor, std::string& errorMessage)
	{
		try
		{
			if (!creditor->GetName().empty() && !creditor->GetAddress().empty() && !creditor->GetPhone().empty())
			{
				return creditor->CreateCreditor(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Creditor name, phone and address must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateCreditor(BusinessLayer::Creditor* creditor, std::string& errorMessage)
	{
		try
		{
			if (!creditor->GetName().empty() && !creditor->GetAddress().empty() && !creditor->GetPhone().empty())
			{
				return creditor->UpdateCreditor(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Creditor name, phone and address must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteCreditor(BusinessLayer::Creditor* creditor, std::string& errorMessage)
	{
		try
		{
			if (0 != creditor->GetID())
			{
				return creditor->DeleteCreditor(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Creditor ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateDivisionAccountRelation(BusinessLayer::DivisionAccountRelation* divisionAccountReletion, std::string& errorMessage)
	{
		try
		{
			if (0 != divisionAccountReletion->GetDivisionID() && 0 != divisionAccountReletion->GetAccountID() && !divisionAccountReletion->GetCode().empty())
			{
				return divisionAccountReletion->CreateDivisionAccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division-Account relation division ID, account ID and code name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateDivisionAccountRelation(BusinessLayer::DivisionAccountRelation* divisionAccountReletion, std::string& errorMessage)
	{
		try
		{
			if (0 != divisionAccountReletion->GetDivisionID() && 0 != divisionAccountReletion->GetAccountID() && !divisionAccountReletion->GetCode().empty())
			{
				return divisionAccountReletion->UpdateDivisionAccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division-Account relation division ID, account ID and code name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteDivisionAccountRelation(BusinessLayer::DivisionAccountRelation* divisionAccountReletion, std::string& errorMessage)
	{
		try
		{
			if (0 != divisionAccountReletion->GetID())
			{
				return divisionAccountReletion->DeleteDivisionAccountRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division-Account relation ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateDivisionEmployeeRelation(BusinessLayer::DivisionEmployeeRelation* divisionEmployeeRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != divisionEmployeeRelation->GetDivisionID() && 0 != divisionEmployeeRelation->GetEmployeeID())
			{
				return divisionEmployeeRelation->CreateDivisionEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division-Employee relation division ID, employee ID and code name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateDivisionEmployeeRelation(BusinessLayer::DivisionEmployeeRelation* divisionEmployeeRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != divisionEmployeeRelation->GetDivisionID() && 0 != divisionEmployeeRelation->GetEmployeeID())
			{
				return divisionEmployeeRelation->UpdateDivisionEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division-Account relation division ID, employee ID and code name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteDivisionEmployeeRelation(BusinessLayer::DivisionEmployeeRelation* divisionEmployeeReletion, std::string& errorMessage)
	{
		try
		{
			if (0 != divisionEmployeeReletion->GetID())
			{
				return divisionEmployeeReletion->DeleteDivisionEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division-Account relation ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateDivision(BusinessLayer::Division* division, std::string& errorMessage)
	{
		try
		{
			if (!division->GetCode().empty() && !division->GetName().empty())
			{
				return division->CreateDivision(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateDivision(BusinessLayer::Division* division, std::string& errorMessage)
	{
		try
		{
			if (!division->GetCode().empty() && !division->GetName().empty())
			{
				return division->UpdateDivision(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteDivision(BusinessLayer::Division* division, std::string& errorMessage)
	{
		try
		{
			if (0 != division->GetID())
			{
				return division->DeleteDivision(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Division ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}
    
	bool OrmasBL::CreateEmployee(BusinessLayer::Employee* employee, std::string& errorMessage)
	{
		try
		{
			if (!employee->GetName().empty() && !employee->GetSurname().empty() && !employee->GetPhone().empty()
				&& !employee->GetAddress().empty() && !employee->GetPassword().empty() && 0 != employee->GetRoleID() 
				&& !employee->GetBirthDate().empty() && !employee->GetHireDate().empty() && 0 != employee->GetPositionID())
			{
				return employee->CreateEmployee(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateEmployee(BusinessLayer::Employee* employee, std::string& errorMessage)
	{
		try
		{
			if (!employee->GetName().empty() && !employee->GetSurname().empty() && !employee->GetPhone().empty()
				&& !employee->GetAddress().empty() && !employee->GetPassword().empty() && 0 != employee->GetRoleID()
				&& !employee->GetBirthDate().empty() && !employee->GetHireDate().empty() && 0 != employee->GetPositionID())
			{
				return employee->UpdateEmployee(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteEmployee(BusinessLayer::Employee* employee, std::string& errorMessage)
	{
		try
		{
			if (0 != employee->GetID())
			{
				return employee->DeleteEmployee(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Employee ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateEmployeeProductRelation(BusinessLayer::EmployeeProductRelation* employeeProduct, std::string& errorMessage)
	{
		try
		{
			if (0 != employeeProduct->GetEmployeeID() && 0 != employeeProduct->GetProductID())
			{
				return employeeProduct->CreateEmployeeProductRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateEmployeeProductRelation(BusinessLayer::EmployeeProductRelation* employeeProduct, std::string& errorMessage)
	{
		try
		{
			if (0 != employeeProduct->GetEmployeeID() && 0 != employeeProduct->GetProductID())
			{
				return employeeProduct->UpdateEmployeeProductRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteEmployeeProductRelation(BusinessLayer::EmployeeProductRelation* employeeProduct, std::string& errorMessage)
	{
		try
		{
			if (0 != employeeProduct->GetID())
			{
				return employeeProduct->DeleteEmployeeProductRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Employee-product ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateEntry(BusinessLayer::Entry* entry, std::string& errorMessage)
	{
		try
		{
			if (0 != entry->GetCreditingAccountID() && 0 != entry->GetDebitingAccountID() && !entry->GetDate().empty() 
				&& 0 != entry->GetValue())
			{
				return entry->CreateEntry(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateEntry(BusinessLayer::Entry* entry, std::string& errorMessage)
	{
		try
		{
			if (0 != entry->GetCreditingAccountID() && 0 != entry->GetDebitingAccountID() && !entry->GetDate().empty()
				&& 0 != entry->GetValue())
			{
				return entry->UpdateEntry(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteEntry(BusinessLayer::Entry* entry, std::string& errorMessage)
	{
		try
		{
			if (0 != entry->GetID())
			{
				return entry->DeleteEntry(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Entry ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateEntryRouting(BusinessLayer::EntryRouting* entryRouting, std::string& errorMessage)
	{
		try
		{
			if (0 != entryRouting->GetCreditAccountID() && 0 != entryRouting->GetDebitAccountID() && !entryRouting->GetOperation().empty())
			{
				return entryRouting->CreateEntryRouting(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateEntryRouting(BusinessLayer::EntryRouting* entryRouting, std::string& errorMessage)
	{
		try
		{
			if (0 != entryRouting->GetCreditAccountID() && 0 != entryRouting->GetDebitAccountID() && !entryRouting->GetOperation().empty())
			{
				return entryRouting->UpdateEntryRouting(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteEntryRouting(BusinessLayer::EntryRouting* entryRouting, std::string& errorMessage)
	{
		try
		{
			if (0 != entryRouting->GetID())
			{
				return entryRouting->DeleteEntryRouting(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Entry routing ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateFinancialReport(BusinessLayer::FinancialReport* finRep, std::string& errorMessage)
	{
		try
		{
			if (0 != finRep->GetAccount44010() && 0 != finRep->GetAccount55010() && !finRep->GetFromDate().empty()
				&& !finRep->GetTillDate().empty())
			{
				return finRep->CreateFinancialReport(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateFinancialReport(BusinessLayer::FinancialReport* finRep, std::string& errorMessage)
	{
		try
		{
			if (0 != finRep->GetAccount44010() && 0 != finRep->GetAccount55010() && !finRep->GetFromDate().empty()
				&& !finRep->GetTillDate().empty())
			{
				return finRep->UpdateFinancialReport(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteFinancialReport(BusinessLayer::FinancialReport* finRep, std::string& errorMessage)
	{
		try
		{
			if (0 != finRep->GetID())
			{
				return finRep->DeleteFinancialReport(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Financial report ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateFixedAssets(BusinessLayer::FixedAssets* fixedAssets, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssets->GetSpecificationID() && 0 != fixedAssets->GetPrimaryCost() && !fixedAssets->GetBuyDate().empty()
				&& 0 != fixedAssets->GetServiceLife() && 0 != fixedAssets->GetStatusID())
			{
				return fixedAssets->CreateFixedAssets(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateFixedAssets(BusinessLayer::FixedAssets* fixedAssets, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssets->GetSpecificationID() && 0 != fixedAssets->GetPrimaryCost() && !fixedAssets->GetBuyDate().empty()
				&& 0 != fixedAssets->GetServiceLife() && 0 != fixedAssets->GetStatusID())
			{
				return fixedAssets->UpdateFixedAssets(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteFixedAssets(BusinessLayer::FixedAssets* fixedAssets, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssets->GetID())
			{
				return fixedAssets->DeleteFixedAssets(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Fixed assets ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateFixedAssetsUnion(BusinessLayer::FixedAssetsUnion* fixedAssetsUnion, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssetsUnion->GetFixedAssets()->GetPrimaryCost() && 0 != fixedAssetsUnion->GetFixedAssetsDetails()->GetAmortizeValue() &&
				!fixedAssetsUnion->GetFixedAssetsSpecification()->GetName().empty())
			{
				return fixedAssetsUnion->CreateFixedAssetsUnion(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateFixedAssetsUnion(BusinessLayer::FixedAssetsUnion* fixedAssetsUnion, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssetsUnion->GetFixedAssets()->GetPrimaryCost() && 0 != fixedAssetsUnion->GetFixedAssetsDetails()->GetAmortizeValue() &&
				!fixedAssetsUnion->GetFixedAssetsSpecification()->GetName().empty())
			{
				return fixedAssetsUnion->UpdateFixedAssetsUnion(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteFixedAssetsUnion(BusinessLayer::FixedAssetsUnion* fixedAssetsUnion, std::string& errorMessage)
	{
		try
		{
			if (!fixedAssetsUnion->GetFixedAssets()->IsEmpty() && !fixedAssetsUnion->GetFixedAssetsDetails()->IsEmpty() &&
				!fixedAssetsUnion->GetFixedAssetsSpecification()->IsEmpty())
			{
				return fixedAssetsUnion->DeleteFixedAssetsUnion(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateGroup(BusinessLayer::Group* group, std::string& errorMessage)
	{
		try
		{
			if (!group->GetName().empty() && !group->GetDefenition().empty())
			{
				return group->CreateGroup(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateGroup(BusinessLayer::Group* group, std::string& errorMessage)
	{
		try
		{
			if (!group->GetName().empty() && !group->GetDefenition().empty())
			{
				return group->UpdateGroup(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteGroup(BusinessLayer::Group* group, std::string& errorMessage)
	{
		try
		{
			if (0 != group->GetID())
			{
				return group->DeleteGroup(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateFixedAssetsDetails(BusinessLayer::FixedAssetsDetails* fixedAssetsDetails, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssetsDetails->GetAmortizeGroupID() && 0 != fixedAssetsDetails->GetAmortizeAccountID()
				&& 0 != fixedAssetsDetails->GetDepartmentID() && 0 != fixedAssetsDetails->GetPrimaryCostAccountID() && 0 != fixedAssetsDetails->GetAmortizeAccountID())
			{
				return fixedAssetsDetails->CreateFixedAssetsDetails(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateFixedAssetsDetails(BusinessLayer::FixedAssetsDetails* fixedAssetsDetails, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssetsDetails->GetID() && 0 != fixedAssetsDetails->GetAmortizeValue() && 0 != fixedAssetsDetails->GetAmortizeGroupID() &&
				0 != fixedAssetsDetails->GetAmortizeTypeID() && 0 != fixedAssetsDetails->GetDepartmentID() &&
				0 != fixedAssetsDetails->GetPrimaryCostAccountID() && 0 != fixedAssetsDetails->GetAmortizeAccountID())
			{
				return fixedAssetsDetails->UpdateFixedAssetsDetails(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteFixedAssetsDetails(BusinessLayer::FixedAssetsDetails* fixedAssetsDetails, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssetsDetails->GetID() && 0 != fixedAssetsDetails->GetAmortizeValue() && 0 != fixedAssetsDetails->GetAmortizeGroupID() && 
				0 != fixedAssetsDetails->GetAmortizeTypeID() && 0 != fixedAssetsDetails->GetDepartmentID() &&
				0 != fixedAssetsDetails->GetPrimaryCostAccountID() && 0 != fixedAssetsDetails->GetAmortizeAccountID())
			{
				return fixedAssetsDetails->DeleteFixedAssetsDetails(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Fixed assets details ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateFixedAssetsOperation(BusinessLayer::FixedAssetsOperations* fixedAssetsOperation, std::string& errorMessage)
	{
		try
		{
			if (!fixedAssetsOperation->GetDate().empty() && !fixedAssetsOperation->GetName().empty() 
				&& 0 != fixedAssetsOperation->GetValue() && 0 != fixedAssetsOperation->GetFixedAssetsID())
			{
				return fixedAssetsOperation->CreateFixedAssetsOperations(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateFixedAssetsOperation(BusinessLayer::FixedAssetsOperations* fixedAssetsOperation, std::string& errorMessage)
	{
		try
		{
			if (!fixedAssetsOperation->GetDate().empty() && !fixedAssetsOperation->GetName().empty()
				&& 0 != fixedAssetsOperation->GetValue() && 0 != fixedAssetsOperation->GetFixedAssetsID())
			{
				return fixedAssetsOperation->UpdateFixedAssetsOperations(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteFixedAssetsOperation(BusinessLayer::FixedAssetsOperations* fixedAssetsOperation, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssetsOperation->GetID())
			{
				return fixedAssetsOperation->DeleteFixedAssetsOperations(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Fixed assets operation ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateFixedAssetsSpecification(BusinessLayer::FixedAssetsSpecification* fixedAssetsSpecification, std::string& errorMessage)
	{
		try
		{
			if (!fixedAssetsSpecification->GetName().empty())
			{
				return fixedAssetsSpecification->CreateFixedAssetsSpecification(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateFixedAssetsSpecification(BusinessLayer::FixedAssetsSpecification* fixedAssetsSpecification, std::string& errorMessage)
	{
		try
		{
			if (!fixedAssetsSpecification->GetName().empty())
			{
				return fixedAssetsSpecification->UpdateFixedAssetsSpecification(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteFixedAssetsSpecification(BusinessLayer::FixedAssetsSpecification* fixedAssetsSpecification, std::string& errorMessage)
	{
		try
		{
			if (0 != fixedAssetsSpecification->GetID())
			{
				return fixedAssetsSpecification->DeleteFixedAssetsSpecification(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Fixed assets specification ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateInventorization(BusinessLayer::Inventorization* inventorization, std::string& errorMessage)
	{
		try
		{
			if (!inventorization->GetDate().empty() && 0 != inventorization->GetEmployeeID() && 0 != inventorization->GetCount()
				&& 0 != inventorization->GetSum() && 0 != inventorization->GetStatusID() && 0 != inventorization->GetCurrencyID()
				&& 0 != inventorization->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, inventorization->GetCurrencyID(), errorMessage))
				{
					roundSum = round(inventorization->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				inventorization->SetSum(roundSum);
				return inventorization->CreateInventorization(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateInventorization(BusinessLayer::Inventorization* inventorization, std::string& errorMessage)
	{
		try
		{
			if (!inventorization->GetDate().empty() && 0 != inventorization->GetEmployeeID() && 0 != inventorization->GetCount()
				&& 0 != inventorization->GetSum() && 0 != inventorization->GetStatusID() && 0 != inventorization->GetCurrencyID()
				&& 0 != inventorization->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, inventorization->GetCurrencyID(), errorMessage))
				{
					roundSum = round(inventorization->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				inventorization->SetSum(roundSum);
				return inventorization->UpdateInventorization(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteInventorization(BusinessLayer::Inventorization* inventorization, std::string& errorMessage)
	{
		try
		{
			if (0 != inventorization->GetID())
			{
				return inventorization->DeleteInventorization(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Inventorization ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateInventorizationList(BusinessLayer::InventorizationList* inventorizationList, std::string& errorMessage)
	{
		try
		{
			if (0 != inventorizationList->GetInventorizationID() && 0 != inventorizationList->GetProductID()
				&& 0 != inventorizationList->GetCount() && 0 != inventorizationList->GetSum() && 0 != inventorizationList->GetStatusID()
				&& 0 != inventorizationList->GetCurrencyID())
			{
				return inventorizationList->CreateInventorizationList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateInventorizationList(BusinessLayer::InventorizationList* inventorizationList, std::string& errorMessage)
	{
		try
		{
			if (0 != inventorizationList->GetInventorizationID() && 0 != inventorizationList->GetProductID()
				&& 0 != inventorizationList->GetCount() && 0 != inventorizationList->GetSum() && 0 != inventorizationList->GetStatusID()
				&& 0 != inventorizationList->GetCurrencyID())
			{
				return inventorizationList->UpdateInventorizationList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteInventorizationList(BusinessLayer::InventorizationList* inventorizationList, std::string& errorMessage)
	{
		try
		{
			if (0 != inventorizationList->GetID())
			{
				return inventorizationList->DeleteInventorizationList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Inventorization list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateInventory(BusinessLayer::Inventory* inventory, std::string& errorMessage)
	{
		try
		{
			if (!inventory->GetName().empty() && 0 != inventory->GetCost() && 0 != inventory->GetDepartmentID()
				&& 0 != inventory->GetStatusID())
			{
				return inventory->CreateInventory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateInventory(BusinessLayer::Inventory* inventory, std::string& errorMessage)
	{
		try
		{
			if (!inventory->GetName().empty() && 0 != inventory->GetCost() && 0 != inventory->GetDepartmentID()
				&& 0 != inventory->GetStatusID())
			{
				return inventory->UpdateInventory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteInventory(BusinessLayer::Inventory* inventory, std::string& errorMessage)
	{
		try
		{
			if (0 != inventory->GetID())
			{
				return inventory->DeleteInventory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Inventory list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateInventoryUnion(BusinessLayer::InventoryUnion* inventoryUnion, std::string& errorMessage)
	{
		try
		{
			if (0 != inventoryUnion->GetInventory()->GetCost() && 
				!inventoryUnion->GetInventory()->GetName().empty())
			{
				return inventoryUnion->CreateInventoryUnion(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateInventoryUnion(BusinessLayer::InventoryUnion* inventoryUnion, std::string& errorMessage)
	{
		try
		{
			if (0 != inventoryUnion->GetInventory()->GetCost() &&
				!inventoryUnion->GetInventory()->GetName().empty())
			{

				return inventoryUnion->UpdateInventoryUnion(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteInventoryUnion(BusinessLayer::InventoryUnion* inventoryUnion, std::string& errorMessage)
	{
		try
		{
			if (!inventoryUnion->GetInventory()->IsEmpty())
			{
				return inventoryUnion->DeleteInventoryUnion(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fienlds name must not be empty. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}


	bool OrmasBL::CreateInventoryHistory(BusinessLayer::InventoryHistory* inventoryHistory, std::string& errorMessage)
	{
		try
		{
			if (!inventoryHistory->GetChangeDate().empty() && 0 != inventoryHistory->GetInventoryID())
			{
				return inventoryHistory->CreateInventoryHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateInventoryHistory(BusinessLayer::InventoryHistory* inventoryHistory, std::string& errorMessage)
	{
		try
		{
			if (!inventoryHistory->GetChangeDate().empty() && 0 != inventoryHistory->GetInventoryID())
			{
				return inventoryHistory->UpdateInventoryHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteInventoryHistory(BusinessLayer::InventoryHistory* inventoryHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != inventoryHistory->GetID())
			{
				return inventoryHistory->DeleteInventoryHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Inventory history ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateJobprice(BusinessLayer::Jobprice* jobprice, std::string& errorMessage)
	{
		try
		{
			if (0 != jobprice->GetProductID() && 0.0 != jobprice->GetValue() && 0 != jobprice->GetCurrencyID() && 
				0.0 != jobprice->GetVolume() && 0 != jobprice->GetMeasureID() && 0 != jobprice->GetPositionID())
			{
				return jobprice->CreateJobprice(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Jobprice code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateJobprice(BusinessLayer::Jobprice* jobprice, std::string& errorMessage)
	{
		try
		{
			if (0 != jobprice->GetProductID() && 0.0 != jobprice->GetValue() && 0 != jobprice->GetCurrencyID() &&
				0.0 != jobprice->GetVolume() && 0 != jobprice->GetMeasureID() && 0 != jobprice->GetPositionID())
			{
				return jobprice->UpdateJobprice(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Jobprice code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteJobprice(BusinessLayer::Jobprice* jobprice, std::string& errorMessage)
	{
		try
		{
			if (0 != jobprice->GetID())
			{
				return jobprice->DeleteJobprice(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Jobprice ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateJobsheet(BusinessLayer::Jobsheet* jobsheet, std::string& errorMessage)
	{
		try
		{
			if (!jobsheet->GetDate().empty() && 0.0 != jobsheet->GetCount() && 0 != jobsheet->GetProductID() && 0 != jobsheet->GetEmployeeID())
			{
				return jobsheet->CreateJobsheet(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Jobsheet code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateJobsheet(BusinessLayer::Jobsheet* jobsheet, std::string& errorMessage)
	{
		try
		{
			if (!jobsheet->GetDate().empty() && 0.0 != jobsheet->GetCount() && 0 != jobsheet->GetProductID() && 0 != jobsheet->GetEmployeeID())
			{
				return jobsheet->UpdateJobsheet(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Jobsheet code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteJobsheet(BusinessLayer::Jobsheet* jobsheet, std::string& errorMessage)
	{
		try
		{
			if (0 != jobsheet->GetID())
			{
				return jobsheet->DeleteJobsheet(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Jobsheet ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateLocation(BusinessLayer::Location* location, std::string& errorMessage)
	{
		try
		{
			if (!location->GetCountryName().empty() && !location->GetCountryCode().empty() && !location->GetRegionName().empty()
				&& !location->GetCityName().empty())
			{
				return location->CreateLocation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Location code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateLocation(BusinessLayer::Location* location, std::string& errorMessage)
	{
		try
		{
			if (!location->GetCountryName().empty() && !location->GetCountryCode().empty() && !location->GetRegionName().empty()
				&& !location->GetCityName().empty())
			{
				return location->UpdateLocation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Location code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteLocation(BusinessLayer::Location* location, std::string& errorMessage)
	{
		try
		{
			if (0 != location->GetID())
			{
				return location->DeleteLocation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Location ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateMeasure(BusinessLayer::Measure* measure, std::string& errorMessage)
	{
		try
		{
			if (!measure->GetName().empty() && !measure->GetShortName().empty() && 0 != measure->GetUnit())
			{
				return measure->CreateMeasure(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Measure name and short name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateMeasure(BusinessLayer::Measure* measure, std::string& errorMessage)
	{
		try
		{
			if (!measure->GetName().empty() && !measure->GetShortName().empty() && 0 != measure->GetUnit())
			{
				return measure->UpdateMeasure(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Measure name and short name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateLowValueStock(BusinessLayer::LowValueStock* stock, std::string& errorMessage)
	{
		try
		{
			if (0 != stock->GetOtherStocksID() && 0 != stock->GetCount() &&
				0 != stock->GetSum() && 0 != stock->GetStatusID() && 0 != stock->GetCurrencyID())
			{
				return stock->CreateLowValueStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateLowValueStock(BusinessLayer::LowValueStock* stock, std::string& errorMessage)
	{
		try
		{
			if (0 != stock->GetOtherStocksID() && 0 != stock->GetCount() &&
				0 != stock->GetSum() && 0 != stock->GetStatusID() && 0 != stock->GetCurrencyID())
			{
				return stock->UpdateLowValueStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteLowValueStock(BusinessLayer::LowValueStock* stock, std::string& errorMessage)
	{
		try
		{
			if (0 != stock->GetID())
			{
				return stock->DeleteLowValueStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error!Low value stock ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateLowValueStockHistory(BusinessLayer::LowValueStockHistory* stockHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != stockHistory->GetOtherStocksID() && 0 != stockHistory->GetCount() &&
				0 != stockHistory->GetSum() && 0 != stockHistory->GetStatusID() && 0 != stockHistory->GetCurrencyID()
				&& !stockHistory->GetHistoryDate().empty())
			{
				return stockHistory->CreateLowValueStockHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateLowValueStockHistory(BusinessLayer::LowValueStockHistory* stockHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != stockHistory->GetOtherStocksID() && 0 != stockHistory->GetCount() &&
				0 != stockHistory->GetSum() && 0 != stockHistory->GetStatusID() && 0 != stockHistory->GetCurrencyID()
				&& !stockHistory->GetHistoryDate().empty())
			{
				return stockHistory->UpdateLowValueStockHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteLowValueStockHistory(BusinessLayer::LowValueStockHistory* stockHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != stockHistory->GetID())
			{
				return stockHistory->DeleteLowValueStockHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error!Low value stock history ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateLowValueStockChangeLog(BusinessLayer::LowValueStockChangeLog* stockChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != stockChangeLog->GetLowValueStockID() && !stockChangeLog->GetLogDate().empty())
			{
				return stockChangeLog->CreateLowValueStockChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateLowValueStockChangeLog(BusinessLayer::LowValueStockChangeLog* stockChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != stockChangeLog->GetLowValueStockID() && !stockChangeLog->GetLogDate().empty())
			{
				return stockChangeLog->UpdateLowValueStockChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteLowValueStockChangeLog(BusinessLayer::LowValueStockChangeLog* stockChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != stockChangeLog->GetID())
			{
				return stockChangeLog->DeleteLowValueStockChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error!Low value stock change log ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteMeasure(BusinessLayer::Measure* measure, std::string& errorMessage)
	{
		try
		{
			if (0 != measure->GetID())
			{
				return measure->DeleteMeasure(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Measure ID is 0. Some thing goes wrong!";
			}			
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider."; 
		}
		return false;
	}

	bool OrmasBL::CreateNetCost(BusinessLayer::NetCost* netCost, std::string& errorMessage)
	{
		try
		{
			if (0 != netCost->GetProductID() && 0.0 != netCost->GetValue() && 0 != netCost->GetCurrencyID() && !netCost->GetDate().empty())
			{
				return netCost->CreateNetCost(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product , currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateNetCost(BusinessLayer::NetCost* netCost, std::string& errorMessage)
	{
		try
		{
			if (0 != netCost->GetProductID() && 0.0 != netCost->GetValue() && 0 != netCost->GetCurrencyID() && !netCost->GetDate().empty())
			{
				return netCost->UpdateNetCost(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product, currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteNetCost(BusinessLayer::NetCost* netCost, std::string& errorMessage)
	{
		try
		{
			if (0 != netCost->GetID())
			{
				return netCost->DeleteNetCost(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Price ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateOrder(BusinessLayer::Order* order, std::string& errorMessage)
	{
		try
		{
			if (!order->GetDate().empty() &&  0 != order->GetClientID() && 0 != order->GetCount()
				&& 0 != order->GetSum() && 0 != order->GetStatusID() && 0 != order->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, order->GetCurrencyID(), errorMessage))
				{
					roundSum = round(order->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				order->SetSum(order->GetSum());
				return order->CreateOrder(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateOrder(BusinessLayer::Order* order, std::string& errorMessage)
	{
		try
		{
			if (!order->GetDate().empty() && 0 != order->GetClientID() && 0 != order->GetCount()
				&& 0 != order->GetSum() && 0 != order->GetStatusID() && 0 != order->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, order->GetCurrencyID(), errorMessage))
				{
					roundSum = round(order->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				order->SetSum(order->GetSum());
				return order->UpdateOrder(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteOrder(BusinessLayer::Order* order, std::string& errorMessage)
	{
		try
		{
			if (0 != order->GetID())
			{
				return order->DeleteOrder(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Order ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}


	bool OrmasBL::CreateOrderList(BusinessLayer::OrderList* orderList, std::string& errorMessage)
	{
		try
		{
			if (0 != orderList->GetOrderID() && 0 != orderList->GetProductID()
				&& 0 != orderList->GetCount() && 0 != orderList->GetSum() && 0 != orderList->GetStatusID()
				&& 0 != orderList->GetCurrencyID())
			{
				return orderList->CreateOrderList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateOrderList(BusinessLayer::OrderList* orderList, std::string& errorMessage)
	{
		try
		{
			if (0 != orderList->GetOrderID() && 0 != orderList->GetProductID()
				&& 0 != orderList->GetCount() && 0 != orderList->GetSum() && 0 != orderList->GetStatusID()
				&& 0 != orderList->GetCurrencyID())
			{
				return orderList->UpdateOrderList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteOrderList(BusinessLayer::OrderList* orderList, std::string& errorMessage)
	{
		try
		{
			if (0 != orderList->GetID())
			{
				return orderList->DeleteOrderList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Order list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateOrderRaw(BusinessLayer::OrderRaw* orderRaw, std::string& errorMessage)
	{
		try
		{
			if (!orderRaw->GetDate().empty() && 0 != orderRaw->GetPurveyorID() && 0 != orderRaw->GetCount()
				&& 0 != orderRaw->GetSum() && 0 != orderRaw->GetStatusID() && 0 != orderRaw->GetCurrencyID()
				&& 0 != orderRaw->GetEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, orderRaw->GetCurrencyID(), errorMessage))
				{
					roundSum = round(orderRaw->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				orderRaw->SetSum(roundSum);
				return orderRaw->CreateOrderRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateOrderRaw(BusinessLayer::OrderRaw* orderRaw, std::string& errorMessage)
	{
		try
		{
			if (!orderRaw->GetDate().empty() && 0 != orderRaw->GetPurveyorID() && 0 != orderRaw->GetCount()
				&& 0 != orderRaw->GetSum() && 0 != orderRaw->GetStatusID() && 0 != orderRaw->GetCurrencyID()
				&& 0 != orderRaw->GetEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, orderRaw->GetCurrencyID(), errorMessage))
				{
					roundSum = round(orderRaw->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				orderRaw->SetSum(roundSum);
				return orderRaw->UpdateOrderRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteOrderRaw(BusinessLayer::OrderRaw* orderRaw, std::string& errorMessage)
	{
		try
		{
			if (0 != orderRaw->GetID())
			{
				return orderRaw->DeleteOrderRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Order raw ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateOrderRawList(BusinessLayer::OrderRawList* orderRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != orderRawList->GetOrderRawID() && 0 != orderRawList->GetProductID()
				&& 0 != orderRawList->GetCount() && 0 != orderRawList->GetSum() && 0 != orderRawList->GetStatusID()
				&& 0 != orderRawList->GetCurrencyID())
			{
				return orderRawList->CreateOrderRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateOrderRawList(BusinessLayer::OrderRawList* orderRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != orderRawList->GetOrderRawID() && 0 != orderRawList->GetProductID()
				&& 0 != orderRawList->GetCount() && 0 != orderRawList->GetSum() && 0 != orderRawList->GetStatusID()
				&& 0 != orderRawList->GetCurrencyID())
			{
				return orderRawList->UpdateOrderRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteOrderRawList(BusinessLayer::OrderRawList* orderRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != orderRawList->GetID())
			{
				return orderRawList->DeleteOrderRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Order Raw list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreatePayment(BusinessLayer::Payment* payment, std::string& errorMessage)
	{
		payment->loggedUserID = loggedUser->GetID();
		try
		{
			if (0.0 != payment->GetValue() && 0 != payment->GetCurrencyID() && !payment->GetDate().empty() && !payment->GetWho().empty()
				&& 0 != payment->GetStatusID())
			{
				return payment->CreatePayment(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateOtherStocks(BusinessLayer::OtherStocks* otherStocks, std::string& errorMessage)
	{
		try
		{
			if (0 != otherStocks->GetCompanyID() && !otherStocks->GetName().empty() && 0 != otherStocks->GetVolume() && 0 != otherStocks->GetMeasureID()
				&& 0 != otherStocks->GetPrice() && 0 != otherStocks->GetCurrencyID() && 0 != otherStocks->GetOtherStocksTypeID())
			{
				return otherStocks->CreateOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateOtherStocks(BusinessLayer::OtherStocks* otherStocks, std::string& errorMessage)
	{
		try
		{
			if (0 != otherStocks->GetCompanyID() && !otherStocks->GetName().empty() && 0 != otherStocks->GetVolume() && 0 != otherStocks->GetMeasureID()
				&& 0 != otherStocks->GetPrice() && 0 != otherStocks->GetCurrencyID() && 0 != otherStocks->GetOtherStocksTypeID())
			{
				return otherStocks->UpdateOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteOtherStocks(BusinessLayer::OtherStocks* otherStocks, std::string& errorMessage)
	{
		try
		{
			if (0 != otherStocks->GetID())
			{
				return otherStocks->DeleteOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Other stocks ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}


	bool OrmasBL::CreateOtherStocksType(BusinessLayer::OtherStocksType* otherStocksType, std::string& errorMessage)
	{
		try
		{
			if (0 != otherStocksType->GetID() && !otherStocksType->GetName().empty() && !otherStocksType->GetCode().empty()
				&& !otherStocksType->GetShortName().empty())
			{
				return otherStocksType->CreateOtherStocksType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateOtherStocksType(BusinessLayer::OtherStocksType* otherStocksType, std::string& errorMessage)
	{
		try
		{
			if (0 != otherStocksType->GetID() && !otherStocksType->GetName().empty() && !otherStocksType->GetCode().empty()
				&& !otherStocksType->GetShortName().empty())
			{
				return otherStocksType->UpdateOtherStocksType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteOtherStocksType(BusinessLayer::OtherStocksType* otherStocksType, std::string& errorMessage)
	{
		try
		{
			if (0 != otherStocksType->GetID())
			{
				return otherStocksType->DeleteOtherStocksType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Other stocks ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdatePayment(BusinessLayer::Payment* payment, std::string& errorMessage)
	{
		payment->loggedUserID = loggedUser->GetID();
		try
		{
			if (0.0 != payment->GetValue() && 0 != payment->GetCurrencyID() && !payment->GetDate().empty() && !payment->GetWho().empty()
				&& 0 != payment->GetStatusID())
			{
				return payment->UpdatePayment(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeletePayment(BusinessLayer::Payment* payment, std::string& errorMessage)
	{
		payment->loggedUserID = loggedUser->GetID();
		try
		{
			if (0 != payment->GetID())
			{
				return payment->DeletePayment(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Payment ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreatePayslip(BusinessLayer::Payslip* payslip, std::string& errorMessage)
	{
		try
		{
			if (0 != payslip->GetSalaryID() && 0.0 != payslip->GetValue() && 0 != payslip->GetCurrencyID() && !payslip->GetDate().empty())
			{
				return payslip->CreatePayslip(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Salary, currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdatePayslip(BusinessLayer::Payslip* payslip, std::string& errorMessage)
	{
		try
		{
			if (0 != payslip->GetSalaryID() && 0.0 != payslip->GetValue() && 0 != payslip->GetCurrencyID() && !payslip->GetDate().empty())
			{
				return payslip->UpdatePayslip(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Salary, currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeletePayslip(BusinessLayer::Payslip* payslip, std::string& errorMessage)
	{
		try
		{
			if (0 != payslip->GetID())
			{
				return payslip->DeletePayslip(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Payslip ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreatePercentRate(BusinessLayer::PercentRate* percentRate, std::string& errorMessage)
	{
		try
		{
			if ((0.0 != percentRate->GetValue() || 0 != percentRate->GetPositionID()) && !percentRate->GetCondition().empty())
			{
				return percentRate->CreatePercentRate(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Value, postion and condition must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdatePercentRate(BusinessLayer::PercentRate* percentRate, std::string& errorMessage)
	{
		try
		{
			if ((0.0 != percentRate->GetValue() || 0 != percentRate->GetPositionID()) && !percentRate->GetCondition().empty())
			{
				return percentRate->UpdatePercentRate(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Value, postion and condition must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeletePercentRate(BusinessLayer::PercentRate* percentRate, std::string& errorMessage)
	{
		try
		{
			if (0 != percentRate->GetID())
			{
				return percentRate->DeletePercentRate(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Percent rate ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreatePhoto(BusinessLayer::Photo* photo, std::string& errorMessage)
	{
		try
		{
			if ((0 != photo->GetUserID() || 0 != photo->GetProductID()) && !photo->GetSource().empty())
			{
				return photo->CreatePhoto(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User, product and source must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdatePhoto(BusinessLayer::Photo* photo, std::string& errorMessage)
	{
		try
		{
			if ((0 != photo->GetUserID() || 0 != photo->GetProductID()) && !photo->GetSource().empty())
			{
				return photo->UpdatePhoto(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User, product and source must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeletePhoto(BusinessLayer::Photo* photo, std::string& errorMessage)
	{
		try
		{
			if (0 != photo->GetID())
			{
				return photo->DeletePhoto(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Photo ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreatePostingFixedAssets(BusinessLayer::PostingFixedAssets* pfAssets, std::string& errorMessage)
	{
		try
		{
			if (0 != pfAssets->GetFixedAssetsID() || 0 != pfAssets->GetInventoryID())
			{
				return pfAssets->CreatePostingFixedAssets(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Posting fixed assets or inventory must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdatePostingFixedAssets(BusinessLayer::PostingFixedAssets* pfAssets, std::string& errorMessage)
	{
		try
		{
			if (0 != pfAssets->GetFixedAssetsID() || 0 != pfAssets->GetInventoryID())
			{
				return pfAssets->UpdatePostingFixedAssets(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! osting fixed assets or inventory must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeletePostingFixedAssets(BusinessLayer::PostingFixedAssets* pfAssets, std::string& errorMessage)
	{
		try
		{
			if (0 != pfAssets->GetID())
			{
				return pfAssets->DeletePostingFixedAssets(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Posting fixed assets ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreatePosition(BusinessLayer::Position* position, std::string& errorMessage)
	{
		try
		{
			if (!position->GetName().empty())
			{
				return position->CreatePosition(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdatePosition(BusinessLayer::Position* position, std::string& errorMessage)
	{
		try
		{
			if (!position->GetName().empty())
			{
				return position->UpdatePosition(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeletePosition(BusinessLayer::Position* position, std::string& errorMessage)
	{
		try
		{
			if (0 != position->GetID())
			{
				return position->DeletePosition(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Position ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreatePrice(BusinessLayer::Price* price, std::string& errorMessage)
	{
		try
		{
			if (0 != price->GetProductID() && 0.0 != price->GetValue() && 0 != price->GetCurrencyID() && !price->GetDate().empty())
			{
				return price->CreatePrice(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product , currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdatePrice(BusinessLayer::Price* price, std::string& errorMessage)
	{
		try
		{
			if (0 != price->GetProductID() && 0.0 != price->GetValue() && 0 != price->GetCurrencyID() && !price->GetDate().empty())
			{
				return price->UpdatePrice(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product, currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeletePrice(BusinessLayer::Price* price, std::string& errorMessage)
	{
		try
		{
			if (0 != price->GetID())
			{
				return price->DeletePrice(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Price ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateProduct(BusinessLayer::Product* product, std::string& errorMessage)
	{
		try
		{
			if (0 != product->GetCompanyID() && !product->GetName().empty() && 0 != product->GetVolume() && 0 != product->GetMeasureID()
				&& 0 != product->GetPrice() && 0 != product->GetProductTypeID() && 0 != product->GetShelfLife() && 0 != product->GetCurrencyID())
			{
				return product->CreateProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProduct(BusinessLayer::Product* product, std::string& errorMessage)
	{
		try
		{
			if (0 != product->GetCompanyID() && !product->GetName().empty() && 0 != product->GetVolume() && 0 != product->GetMeasureID()
				&& 0 != product->GetPrice() && 0 != product->GetProductTypeID() && 0 != product->GetShelfLife() && 0 != product->GetCurrencyID())
			{
				return product->UpdateProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProduct(BusinessLayer::Product* product, std::string& errorMessage)
	{
		try
		{
			if (0 != product->GetID())
			{
				return product->DeleteProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateProductBranchRelation(BusinessLayer::ProductBranchRelation* prodcutBranch, std::string& errorMessage)
	{
		try
		{
			if (0 != prodcutBranch->GetBranchID() && 0 != prodcutBranch->GetProductID())
			{
				return prodcutBranch->CreateProductBranchRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProductBranchRelation(BusinessLayer::ProductBranchRelation* employeeProduct, std::string& errorMessage)
	{
		try
		{
			if (0 != employeeProduct->GetBranchID() && 0 != employeeProduct->GetProductID())
			{
				return employeeProduct->UpdateProductBranchRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProductBranchRelation(BusinessLayer::ProductBranchRelation* employeeProduct, std::string& errorMessage)
	{
		try
		{
			if (0 != employeeProduct->GetID())
			{
				return employeeProduct->DeleteProductBranchRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Employee-product ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateProduction(BusinessLayer::Production* production, std::string& errorMessage)
	{
		try
		{
			if (!production->GetProductionDate().empty() && !production->GetExpiryDate().empty() && !production->GetSessionStart().empty()
				&& !production->GetSessionEnd().empty())
			{
				return production->CreateProduction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProduction(BusinessLayer::Production* production, std::string& errorMessage)
	{
		try
		{
			if (!production->GetProductionDate().empty() && !production->GetExpiryDate().empty() && !production->GetSessionStart().empty()
				&& !production->GetSessionEnd().empty())
			{
				return production->UpdateProduction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProduction(BusinessLayer::Production* production, std::string& errorMessage)
	{
		try
		{
			if (0 != production->GetID())
			{
				return production->DeleteProduction(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Production ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;

	}

	bool OrmasBL::CreateProductionList(BusinessLayer::ProductionList* productionList, std::string& errorMessage)
	{
		try
		{
			if (0 != productionList->GetProductionID() && 0 != productionList->GetProductID()
				&& 0 != productionList->GetCount() && 0 != productionList->GetSum() && 0 != productionList->GetStatusID()
				&& 0 != productionList->GetCurrencyID())
			{
				return productionList->CreateProductionList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProductionList(BusinessLayer::ProductionList* productionList, std::string& errorMessage)
	{
		try
		{
			if (0 != productionList->GetProductionID() && 0 != productionList->GetProductID()
				&& 0 != productionList->GetCount() && 0 != productionList->GetSum() && 0 != productionList->GetStatusID()
				&& 0 != productionList->GetCurrencyID())
			{
				return productionList->UpdateProductionList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProductionList(BusinessLayer::ProductionList* productionList, std::string& errorMessage)
	{
		try
		{
			if (0 != productionList->GetID())
			{
				return productionList->DeleteProductionList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Production list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateProductionConsumeRaw(BusinessLayer::ProductionConsumeRaw* pConsumeRaw, std::string& errorMessage)
	{
		try
		{
			if (!pConsumeRaw->GetDate().empty() && 0 != pConsumeRaw->GetCount()
				&& 0 != pConsumeRaw->GetSum() && 0 != pConsumeRaw->GetStatusID() && 0 != pConsumeRaw->GetCurrencyID()
				&& 0 != pConsumeRaw->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, pConsumeRaw->GetCurrencyID(), errorMessage))
				{
					roundSum = round(pConsumeRaw->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				pConsumeRaw->SetSum(roundSum);
				return pConsumeRaw->CreateProductionConsumeRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProductionConsumeRaw(BusinessLayer::ProductionConsumeRaw* pConsumeRaw, std::string& errorMessage)
	{
		try
		{
			if (!pConsumeRaw->GetDate().empty() && 0 != pConsumeRaw->GetCount()
				&& 0 != pConsumeRaw->GetSum() && 0 != pConsumeRaw->GetStatusID() && 0 != pConsumeRaw->GetCurrencyID()
				&& 0 != pConsumeRaw->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, pConsumeRaw->GetCurrencyID(), errorMessage))
				{
					roundSum = round(pConsumeRaw->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				pConsumeRaw->SetSum(roundSum);
				return pConsumeRaw->UpdateProductionConsumeRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProductionConsumeRaw(BusinessLayer::ProductionConsumeRaw* pConsumeRaw, std::string& errorMessage)
	{
		try
		{
			if (0 != pConsumeRaw->GetID())
			{
				return pConsumeRaw->DeleteProductionConsumeRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Consume raw ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateProductionConsumeRawList(BusinessLayer::ProductionConsumeRawList* pConsumeRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != pConsumeRawList->GetProductionConsumeRawID() && 0 != pConsumeRawList->GetProductID()
				&& 0 != pConsumeRawList->GetCount() && 0 != pConsumeRawList->GetSum() && 0 != pConsumeRawList->GetStatusID()
				&& 0 != pConsumeRawList->GetCurrencyID())
			{
				return pConsumeRawList->CreateProductionConsumeRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProductionConsumeRawList(BusinessLayer::ProductionConsumeRawList* pConsumeRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != pConsumeRawList->GetProductionConsumeRawID() && 0 != pConsumeRawList->GetProductID()
				&& 0 != pConsumeRawList->GetCount() && 0 != pConsumeRawList->GetSum() && 0 != pConsumeRawList->GetStatusID()
				&& 0 != pConsumeRawList->GetCurrencyID())
			{
				return pConsumeRawList->UpdateProductionConsumeRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProductionConsumeRawList(BusinessLayer::ProductionConsumeRawList* pConsumeRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != pConsumeRawList->GetID())
			{
				return pConsumeRawList->DeleteProductionConsumeRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Consume raw list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateProductionPlan(BusinessLayer::ProductionPlan* pPlan, std::string& errorMessage)
	{
		try
		{
			if (!pPlan->GetDate().empty() && 0 != pPlan->GetCount()
				&& 0 != pPlan->GetSum() && 0 != pPlan->GetStatusID() && 0 != pPlan->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, pPlan->GetCurrencyID(), errorMessage))
				{
					roundSum = round(pPlan->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				pPlan->SetSum(roundSum);
				return pPlan->CreateProductionPlan(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProductionPlan(BusinessLayer::ProductionPlan* pPlan, std::string& errorMessage)
	{
		try
		{
			if (!pPlan->GetDate().empty() && 0 != pPlan->GetCount()
				&& 0 != pPlan->GetSum() && 0 != pPlan->GetStatusID() && 0 != pPlan->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, pPlan->GetCurrencyID(), errorMessage))
				{
					roundSum = round(pPlan->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				pPlan->SetSum(roundSum);
				return pPlan->UpdateProductionPlan(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProductionPlan(BusinessLayer::ProductionPlan* pPlan, std::string& errorMessage)
	{
		try
		{
			if (0 != pPlan->GetID())
			{
				return pPlan->DeleteProductionPlan(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Production plan ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}


	bool OrmasBL::CreateProductionPlanList(BusinessLayer::ProductionPlanList* pPlanList, std::string& errorMessage)
	{
		try
		{
			if (0 != pPlanList->GetProductionPlanID() && 0 != pPlanList->GetProductID()
				&& 0 != pPlanList->GetCount() && 0 != pPlanList->GetSum() && 0 != pPlanList->GetStatusID()
				&& 0 != pPlanList->GetCurrencyID())
			{
				return pPlanList->CreateProductionPlanList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProductionPlanList(BusinessLayer::ProductionPlanList* pPlanList, std::string& errorMessage)
	{
		try
		{
			if (0 != pPlanList->GetProductionPlanID() && 0 != pPlanList->GetProductID()
				&& 0 != pPlanList->GetCount() && 0 != pPlanList->GetSum() && 0 != pPlanList->GetStatusID()
				&& 0 != pPlanList->GetCurrencyID())
			{
				return pPlanList->UpdateProductionPlanList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProductionPlanList(BusinessLayer::ProductionPlanList* pPlanList, std::string& errorMessage)
	{
		try
		{
			if (0 != pPlanList->GetID())
			{
				return pPlanList->DeleteProductionPlanList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Production plan list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateProductionStock(BusinessLayer::ProductionStock* pStock, std::string& errorMessage)
	{
		try
		{
			if (0 != pStock->GetProductID() && 0 != pStock->GetCount() &&
				0 != pStock->GetSum() && 0 != pStock->GetStatusID() && 0 != pStock->GetCurrencyID())
			{
				return pStock->CreateProductionStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProductionStock(BusinessLayer::ProductionStock* pStock, std::string& errorMessage)
	{
		try
		{
			if (0 != pStock->GetProductID() && 0 != pStock->GetCount() &&
				0 != pStock->GetSum() && 0 != pStock->GetStatusID() && 0 != pStock->GetCurrencyID())
			{
				return pStock->UpdateProductionStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProductionStock(BusinessLayer::ProductionStock* pStock, std::string& errorMessage)
	{
		try
		{
			if (0 != pStock->GetID())
			{
				return pStock->DeleteProductionStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Production stock ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateProductType(BusinessLayer::ProductType* pType, std::string& errorMessage)
	{
		try
		{
			if (!pType->GetName().empty() && !pType->GetShortName().empty() && !pType->GetCode().empty())
			{
				return pType->CreateProductType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product type name, code and short name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateProductType(BusinessLayer::ProductType* pType, std::string& errorMessage)
	{
		try
		{
			if (!pType->GetName().empty() && !pType->GetShortName().empty() && !pType->GetCode().empty())
			{
				return pType->UpdateProductType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product type name, code and short name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteProductType(BusinessLayer::ProductType* pType, std::string& errorMessage)
	{
		try
		{
			if (0 != pType->GetID())
			{
				return pType->DeleteProductType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product type ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreatePurveyor(BusinessLayer::Purveyor* purveyor, std::string& errorMessage)
	{
		try
		{
			if (!purveyor->GetName().empty() && !purveyor->GetSurname().empty() && !purveyor->GetPhone().empty()
				&& !purveyor->GetAddress().empty() && !purveyor->GetPassword().empty() && 0 != purveyor->GetRoleID()
				&& !purveyor->GetCompanyName().empty() && 0 != purveyor->GetLocationID())
			{
				return purveyor->CreatePurveyor(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdatePurveyor(BusinessLayer::Purveyor* purveyor, std::string& errorMessage)
	{
		try
		{
			if (!purveyor->GetName().empty() && !purveyor->GetSurname().empty() && !purveyor->GetPhone().empty()
				&& !purveyor->GetAddress().empty() && !purveyor->GetPassword().empty() && 0 != purveyor->GetRoleID()
				&& !purveyor->GetCompanyName().empty() && 0 != purveyor->GetLocationID())
			{
				return purveyor->UpdatePurveyor(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeletePurveyor(BusinessLayer::Purveyor* purveyor, std::string& errorMessage)
	{
		try
		{
			if (0 != purveyor->GetID())
			{
				return purveyor->DeletePurveyor(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Purveyor ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateReceiptProduct(BusinessLayer::ReceiptProduct* receiptProduct, std::string& errorMessage)
	{
		try
		{
			if (!receiptProduct->GetDate().empty() && 0 != receiptProduct->GetEmployeeID() && 0 != receiptProduct->GetCount()
				&& 0 != receiptProduct->GetSum() && 0 != receiptProduct->GetStatusID() && 0 != receiptProduct->GetCurrencyID()
				&& 0 != receiptProduct->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, receiptProduct->GetCurrencyID(), errorMessage))
				{
					roundSum = round(receiptProduct->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				receiptProduct->SetSum(roundSum);
				return receiptProduct->CreateReceiptProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateReceiptProduct(BusinessLayer::ReceiptProduct* receiptProduct, std::string& errorMessage)
	{
		try
		{
			if (!receiptProduct->GetDate().empty() && 0 != receiptProduct->GetEmployeeID() && 0 != receiptProduct->GetCount()
				&& 0 != receiptProduct->GetSum() && 0 != receiptProduct->GetStatusID() && 0 != receiptProduct->GetCurrencyID()
				&& 0 != receiptProduct->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, receiptProduct->GetCurrencyID(), errorMessage))
				{
					roundSum = round(receiptProduct->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				receiptProduct->SetSum(roundSum);
				return receiptProduct->UpdateReceiptProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteReceiptProduct(BusinessLayer::ReceiptProduct* receiptProduct, std::string& errorMessage)
	{
		try
		{
			if (0 != receiptProduct->GetID())
			{
				return receiptProduct->DeleteReceiptProduct(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Reciept product ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateReceiptProductList(BusinessLayer::ReceiptProductList* receiptProductList, std::string& errorMessage)
	{
		try
		{
			if (0 != receiptProductList->GetReceiptProductID() && 0 != receiptProductList->GetProductID()
				&& 0 != receiptProductList->GetCount() && 0 != receiptProductList->GetSum() && 0 != receiptProductList->GetStatusID()
				&& 0 != receiptProductList->GetCurrencyID())
			{
				return receiptProductList->CreateReceiptProductList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateReceiptProductList(BusinessLayer::ReceiptProductList* receiptProductList, std::string& errorMessage)
	{
		try
		{
			if (0 != receiptProductList->GetReceiptProductID() && 0 != receiptProductList->GetProductID()
				&& 0 != receiptProductList->GetCount() && 0 != receiptProductList->GetSum() && 0 != receiptProductList->GetStatusID()
				&& 0 != receiptProductList->GetCurrencyID())
			{
				return receiptProductList->UpdateReceiptProductList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteReceiptProductList(BusinessLayer::ReceiptProductList* receiptProductList, std::string& errorMessage)
	{
		try
		{
			if (0 != receiptProductList->GetID())
			{
				return receiptProductList->DeleteReceiptProductList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Receipt product list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateReceiptOtherStocks(BusinessLayer::ReceiptOtherStocks* receiptOthS, std::string& errorMessage)
	{
		try
		{
			if (!receiptOthS->GetDate().empty() && 0 != receiptOthS->GetEmployeeID() && 0 != receiptOthS->GetCount()
				&& 0 != receiptOthS->GetSum() && 0 != receiptOthS->GetStatusID() && 0 != receiptOthS->GetCurrencyID()
				&& 0 != receiptOthS->GetPurveyorID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, receiptOthS->GetCurrencyID(), errorMessage))
				{
					roundSum = round(receiptOthS->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				receiptOthS->SetSum(roundSum);
				return receiptOthS->CreateReceiptOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateReceiptOtherStocks(BusinessLayer::ReceiptOtherStocks* receiptOthS, std::string& errorMessage)
	{
		try
		{
			if (!receiptOthS->GetDate().empty() && 0 != receiptOthS->GetEmployeeID() && 0 != receiptOthS->GetCount()
				&& 0 != receiptOthS->GetSum() && 0 != receiptOthS->GetStatusID() && 0 != receiptOthS->GetCurrencyID()
				&& 0 != receiptOthS->GetPurveyorID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, receiptOthS->GetCurrencyID(), errorMessage))
				{
					roundSum = round(receiptOthS->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				receiptOthS->SetSum(roundSum);
				return receiptOthS->UpdateReceiptOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteReceiptOtherStocks(BusinessLayer::ReceiptOtherStocks* receiptOthS, std::string& errorMessage)
	{
		try
		{
			if (0 != receiptOthS->GetID())
			{
				return receiptOthS->DeleteReceiptOtherStocks(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Reciept other stock ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateReceiptOtherStocksList(BusinessLayer::ReceiptOtherStocksList* receiptOthSList, std::string& errorMessage)
	{
		try
		{
			if (0 != receiptOthSList->GetReceiptOtherStocksID() && 0 != receiptOthSList->GetOtherStocksID()
				&& 0 != receiptOthSList->GetCount() && 0 != receiptOthSList->GetSum() && 0 != receiptOthSList->GetStatusID()
				&& 0 != receiptOthSList->GetCurrencyID())
			{
				return receiptOthSList->CreateReceiptOtherStocksList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateReceiptOtherStocksList(BusinessLayer::ReceiptOtherStocksList* receiptOthSList, std::string& errorMessage)
	{
		try
		{
			if (0 != receiptOthSList->GetReceiptOtherStocksID() && 0 != receiptOthSList->GetOtherStocksID()
				&& 0 != receiptOthSList->GetCount() && 0 != receiptOthSList->GetSum() && 0 != receiptOthSList->GetStatusID()
				&& 0 != receiptOthSList->GetCurrencyID())
			{
				return receiptOthSList->UpdateReceiptOtherStocksList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteReceiptOtherStocksList(BusinessLayer::ReceiptOtherStocksList* receiptOthSList, std::string& errorMessage)
	{
		try
		{
			if (0 != receiptOthSList->GetID())
			{
				return receiptOthSList->DeleteReceiptOtherStocksList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Receipt product list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateStockTransfer(BusinessLayer::StockTransfer* stockTransfer, std::string& errorMessage)
	{
		try
		{
			if (!stockTransfer->GetDate().empty() && 0 != stockTransfer->GetEmployeeID() && 0 != stockTransfer->GetCount()
				&& 0 != stockTransfer->GetSum() && 0 != stockTransfer->GetStatusID() && 0 != stockTransfer->GetCurrencyID()
				&& 0 != stockTransfer->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, stockTransfer->GetCurrencyID(), errorMessage))
				{
					roundSum = round(stockTransfer->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				stockTransfer->SetSum(roundSum);
				return stockTransfer->CreateStockTransfer(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateStockTransfer(BusinessLayer::StockTransfer* stockTransfer, std::string& errorMessage)
	{
		try
		{
			if (!stockTransfer->GetDate().empty() && 0 != stockTransfer->GetEmployeeID() && 0 != stockTransfer->GetCount()
				&& 0 != stockTransfer->GetSum() && 0 != stockTransfer->GetStatusID() && 0 != stockTransfer->GetCurrencyID()
				&& 0 != stockTransfer->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, stockTransfer->GetCurrencyID(), errorMessage))
				{
					roundSum = round(stockTransfer->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				stockTransfer->SetSum(roundSum);
				return stockTransfer->UpdateStockTransfer(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteStockTransfer(BusinessLayer::StockTransfer* stockTransfer, std::string& errorMessage)
	{
		try
		{
			if (0 != stockTransfer->GetID())
			{
				return stockTransfer->DeleteStockTransfer(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Stock transfer ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateStockTransferList(BusinessLayer::StockTransferList* stockTransferList, std::string& errorMessage)
	{
		try
		{
			if (0 != stockTransferList->GetStockTransferID() && 0 != stockTransferList->GetProductID()
				&& 0 != stockTransferList->GetCount() && 0 != stockTransferList->GetSum() && 0 != stockTransferList->GetStatusID()
				&& 0 != stockTransferList->GetCurrencyID())
			{
				return stockTransferList->CreateStockTransferList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateStockTransferList(BusinessLayer::StockTransferList* stockTransferList, std::string& errorMessage)
	{
		try
		{
			if (0 != stockTransferList->GetStockTransferID() && 0 != stockTransferList->GetProductID()
				&& 0 != stockTransferList->GetCount() && 0 != stockTransferList->GetSum() && 0 != stockTransferList->GetStatusID()
				&& 0 != stockTransferList->GetCurrencyID())
			{
				return stockTransferList->UpdateStockTransferList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteStockTransferList(BusinessLayer::StockTransferList* stockTransferList, std::string& errorMessage)
	{
		try
		{
			if (0 != stockTransferList->GetID())
			{
				return stockTransferList->DeleteStockTransferList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Stock transfer list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateRefund(BusinessLayer::Refund* refund, std::string& errorMessage)
	{
		refund->loggedUserID = loggedUser->GetID();
		try
		{
			if (0 != refund->GetUserID() && 0.0 != refund->GetValue() && 0 != refund->GetCurrencyID() && !refund->GetDate().empty())
			{
				return refund->CreateRefund(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User, currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}


	bool OrmasBL::UpdateRefund(BusinessLayer::Refund* refund, std::string& errorMessage)
	{
		refund->loggedUserID = loggedUser->GetID();
		try
		{
			if (0 != refund->GetUserID() && 0.0 != refund->GetValue() && 0 != refund->GetCurrencyID() && !refund->GetDate().empty())
			{
				return refund->UpdateRefund(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User, currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteRefund(BusinessLayer::Refund* refund, std::string& errorMessage)
	{
		refund->loggedUserID = loggedUser->GetID();
		try
		{
			if (0 != refund->GetID())
			{
				return refund->DeleteRefund(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Refund ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateRelation(BusinessLayer::Relation* relation, std::string& errorMessage)
	{
		try
		{
			if (0 != relation->GetUser1ID() && 0.0 != relation->GetUser2ID() && 0 != relation->GetRelationTypeID())
			{
				return relation->CreateRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User 1, user 2 and relation type must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateRelation(BusinessLayer::Relation* relation, std::string& errorMessage)
	{
		try
		{
			if (0 != relation->GetUser1ID() && 0.0 != relation->GetUser2ID() && 0 != relation->GetRelationTypeID())
			{
				return relation->UpdateRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User 1, user 2 and relation type must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteRelation(BusinessLayer::Relation* relation, std::string& errorMessage)
	{
		try
		{
			if (0 != relation->GetID())
			{
				return relation->DeleteRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Relation ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateRelationType(BusinessLayer::RelationType* relationType, std::string& errorMessage)
	{
		try
		{
			if (!relationType->GetName().empty())
			{
				return relationType->CreateRelationType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Relation type name must not be empty. Please fill up it!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateRelationType(BusinessLayer::RelationType* relationType, std::string& errorMessage)
	{
		try
		{
			if (!relationType->GetName().empty())
			{
				return relationType->UpdateRelationType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Relation type name must not be empty. Please fill up it!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteRelationType(BusinessLayer::RelationType* relationType, std::string& errorMessage)
	{
		try
		{
			if (0 != relationType->GetID())
			{
				return relationType->DeleteRelationType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Relation type ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateReturn(BusinessLayer::Return* ret, std::string& errorMessage)
	{
		try
		{
			if (!ret->GetDate().empty() && 0 != ret->GetClientID() && 0 != ret->GetCount()
				&& 0 != ret->GetSum() && 0 != ret->GetStatusID() && 0 != ret->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, ret->GetCurrencyID(), errorMessage))
				{
					roundSum = round(ret->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				ret->SetSum(roundSum);
				return ret->CreateReturn(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateReturn(BusinessLayer::Return* ret, std::string& errorMessage)
	{
		try
		{
			if (!ret->GetDate().empty() && 0 != ret->GetClientID() && 0 != ret->GetCount()
				&& 0 != ret->GetSum() && 0 != ret->GetStatusID() && 0 != ret->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, ret->GetCurrencyID(), errorMessage))
				{
					roundSum = round(ret->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				ret->SetSum(roundSum);
				return ret->UpdateReturn(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteReturn(BusinessLayer::Return* ret, std::string& errorMessage)
	{
		try
		{
			if (0 != ret->GetID())
			{
				return ret->DeleteReturn(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Return ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}
	
	bool OrmasBL::CreateReturnList(BusinessLayer::ReturnList* returnList, std::string& errorMessage)
	{
		try
		{
			if (0 != returnList->GetReturnID() && 0 != returnList->GetProductID()
				&& 0 != returnList->GetCount() && 0 != returnList->GetSum() && 0 != returnList->GetStatusID()
				&& 0 != returnList->GetCurrencyID())
			{
				return returnList->CreateReturnList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateReturnList(BusinessLayer::ReturnList* returnList, std::string& errorMessage)
	{
		try
		{
			if (0 != returnList->GetReturnID() && 0 != returnList->GetProductID()
				&& 0 != returnList->GetCount() && 0 != returnList->GetSum() && 0 != returnList->GetStatusID()
				&& 0 != returnList->GetCurrencyID())
			{
				return returnList->UpdateReturnList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteReturnList(BusinessLayer::ReturnList* returnList, std::string& errorMessage)
	{
		try
		{
			if (0 != returnList->GetID())
			{
				return returnList->DeleteReturnList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Return list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateRole(BusinessLayer::Role* role, std::string& errorMessage)
	{
		try
		{
			if (!role->GetCode().empty() && !role->GetName().empty())
			{
				return role->CreateRole(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Role name and code must not be empty. Please fill up it!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateRole(BusinessLayer::Role* role, std::string& errorMessage)
	{
		try
		{
			if (!role->GetCode().empty() && !role->GetName().empty())
			{
				return role->UpdateRole(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Role name and code must not be empty. Please fill up it!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteRole(BusinessLayer::Role* role, std::string& errorMessage)
	{
		try
		{
			if (0 != role->GetID())
			{
				return role->DeleteRole(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Role ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSalary(BusinessLayer::Salary* salary, std::string& errorMessage)
	{
		try
		{
			if (0 != salary->GetEmployeeID() && 0.0 != salary->GetValue() && 0 != salary->GetCurrencyID() && 0 != salary->GetSalaryTypeID()
				&& !salary->GetDate().empty())
			{
				return salary->CreateSalary(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product , currency, date, salary type and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSalary(BusinessLayer::Salary* salary, std::string& errorMessage)
	{
		try
		{
			if (0 != salary->GetEmployeeID() && 0.0 != salary->GetValue() && 0 != salary->GetCurrencyID() && 0 != salary->GetSalaryTypeID()
				&& !salary->GetDate().empty())
			{
				return salary->UpdateSalary(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Product , currency, date, salary type and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSalary(BusinessLayer::Salary* salary, std::string& errorMessage)
	{
		try
		{
			if (0 != salary->GetID())
			{
				return salary->DeleteSalary(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Salary ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSalaryType(BusinessLayer::SalaryType* salaryType, std::string& errorMessage)
	{
		try
		{
			if (!salaryType->GetCode().empty() && !salaryType->GetName().empty())
			{
				return salaryType->CreateSalaryType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Salary type code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSalaryType(BusinessLayer::SalaryType* salaryType, std::string& errorMessage)
	{
		try
		{
			if (!salaryType->GetCode().empty() && !salaryType->GetName().empty())
			{
				return salaryType->UpdateSalaryType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Salary type code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSalaryType(BusinessLayer::SalaryType* salaryType, std::string& errorMessage)
	{
		try
		{
			if (0 != salaryType->GetID())
			{
				return salaryType->DeleteSalaryType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Salary type ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateShareholder(BusinessLayer::Shareholder* shareholder, std::string& errorMessage)
	{
		try
		{
			if (0 != shareholder->GetUserID() || (!shareholder->GetName().empty() && !shareholder->GetAddress().empty() && !shareholder->GetPhone().empty()))
			{
				return shareholder->CreateShareholder(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Name, address and phone must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateShareholder(BusinessLayer::Shareholder* shareholder, std::string& errorMessage)
	{
		try
		{
			if (0 != shareholder->GetUserID() || (!shareholder->GetName().empty() && !shareholder->GetAddress().empty() && !shareholder->GetPhone().empty()))
			{
				return shareholder->UpdateShareholder(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error!  Name, address and phone must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteShareholder(BusinessLayer::Shareholder* shareholder, std::string& errorMessage)
	{
		try
		{
			if (0 != shareholder->GetID())
			{
				return shareholder->DeleteShareholder(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Shareholder ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSpecification(BusinessLayer::Specification* specification, std::string& errorMessage)
	{
		try
		{
			if (0 != specification->GetProductID() && 0 != specification->GetSum() && 0 != specification->GetCurrencyID()
				&& 0 != specification->GetEmployeeID() && !specification->GetDate().empty())
			{
				return specification->CreateSpecification(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSpecification(BusinessLayer::Specification* specification, std::string& errorMessage)
	{
		try
		{
			if (0 != specification->GetProductID() && 0 != specification->GetSum() && 0 != specification->GetCurrencyID()
				&& 0 != specification->GetEmployeeID() && !specification->GetDate().empty())
			{
				return specification->UpdateSpecification(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSpecification(BusinessLayer::Specification* specification, std::string& errorMessage)
	{
		try
		{
			if (0 != specification->GetID())
			{
				return specification->DeleteSpecification(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Specification raw ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSpecificationList(BusinessLayer::SpecificationList* specificationList, std::string& errorMessage)
	{
		try
		{
			if (0 != specificationList->GetSpecificationID() && 0 != specificationList->GetProductID()
				&& 0 != specificationList->GetCount())
			{
				return specificationList->CreateSpecificationList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSpecificationList(BusinessLayer::SpecificationList* specificationList, std::string& errorMessage)
	{
		try
		{
			if (0 != specificationList->GetSpecificationID() && 0 != specificationList->GetProductID()
				&& 0.0 != specificationList->GetCount())
			{
				return specificationList->UpdateSpecificationList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSpecificationList(BusinessLayer::SpecificationList* specificationList, std::string& errorMessage)
	{
		try
		{
			if (0 != specificationList->GetID())
			{
				return specificationList->DeleteSpecificationList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Specification list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSpecificationChangeLog(BusinessLayer::SpecificationChangeLog* specificationChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != specificationChangeLog->GetSpecificationID() && !specificationChangeLog->GetLogDate().empty())
			{
				return specificationChangeLog->CreateSpecificationChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSpecificationChangeLog(BusinessLayer::SpecificationChangeLog* specificationChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != specificationChangeLog->GetSpecificationID() && !specificationChangeLog->GetLogDate().empty())
			{
				return specificationChangeLog->UpdateSpecificationChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSpecificationChangeLog(BusinessLayer::SpecificationChangeLog* specificationChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != specificationChangeLog->GetID())
			{
				return specificationChangeLog->DeleteSpecificationChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Specification change log ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSpoilage(BusinessLayer::Spoilage* spoilage, std::string& errorMessage)
	{
		try
		{
			if (!spoilage->GetDate().empty() && 0 != spoilage->GetCount()
				&& 0 != spoilage->GetSum() && 0 != spoilage->GetStatusID() && 0 != spoilage->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, spoilage->GetCurrencyID(), errorMessage))
				{
					roundSum = round(spoilage->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				spoilage->SetSum(roundSum);
				return spoilage->CreateSpoilage(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSpoilage(BusinessLayer::Spoilage* spoilage, std::string& errorMessage)
	{
		try
		{
			if (!spoilage->GetDate().empty() && 0 != spoilage->GetCount()
				&& 0 != spoilage->GetSum() && 0 != spoilage->GetStatusID() && 0 != spoilage->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, spoilage->GetCurrencyID(), errorMessage))
				{
					roundSum = round(spoilage->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				spoilage->SetSum(roundSum);
				return spoilage->UpdateSpoilage(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSpoilage(BusinessLayer::Spoilage* spoilage, std::string& errorMessage)
	{
		try
		{
			if (0 != spoilage->GetID())
			{
				return spoilage->DeleteSpoilage(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Spoilage ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}


	bool OrmasBL::CreateSpoilageList(BusinessLayer::SpoilageList* spoilageList, std::string& errorMessage)
	{
		try
		{
			if (0 != spoilageList->GetSpoilageID() && 0 != spoilageList->GetProductID()
				&& 0 != spoilageList->GetCount() && 0 != spoilageList->GetSum() && 0 != spoilageList->GetStatusID()
				&& 0 != spoilageList->GetCurrencyID())
			{
				return spoilageList->CreateSpoilageList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSpoilageList(BusinessLayer::SpoilageList* spoilageList, std::string& errorMessage)
	{
		try
		{
			if (0 != spoilageList->GetSpoilageID() && 0 != spoilageList->GetProductID()
				&& 0 != spoilageList->GetCount() && 0 != spoilageList->GetSum() && 0 != spoilageList->GetStatusID()
				&& 0 != spoilageList->GetCurrencyID())
			{
				return spoilageList->UpdateSpoilageList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSpoilageList(BusinessLayer::SpoilageList* spoilageList, std::string& errorMessage)
	{
		try
		{
			if (0 != spoilageList->GetID())
			{
				return spoilageList->DeleteSpoilageList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Spoilage list list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateState(BusinessLayer::State* state, std::string& errorMessage)
	{
		try
		{
			if (0 != state->GetUniversalID() && 0 != state->GetStatusID() && !state->GetLastChange().empty())
			{
				return state->CreateState(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! State last change, universal ID and status ID must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateState(BusinessLayer::State* state, std::string& errorMessage)
	{
		try
		{
			if (0 != state->GetUniversalID() && 0 != state->GetStatusID() && !state->GetLastChange().empty())
			{
				return state->UpdateState(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! State last change, universal ID and status ID must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteState(BusinessLayer::State* state, std::string& errorMessage)
	{
		try
		{
			if (0 != state->GetID())
			{
				return state->DeleteState(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! State ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateStatus(BusinessLayer::Status* status, std::string& errorMessage)
	{
		try
		{
			if (!status->GetCode().empty() && !status->GetName().empty())
			{
				return status->CreateStatus(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Status code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateStatus(BusinessLayer::Status* status, std::string& errorMessage)
	{
		try
		{
			if (!status->GetCode().empty() && !status->GetName().empty())
			{
				return status->UpdateStatus(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Status code and name must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteStatus(BusinessLayer::Status* status, std::string& errorMessage)
	{
		try
		{
			if (0 != status->GetID())
			{
				return status->DeleteStatus(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Status ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateStatusRule(BusinessLayer::StatusRule* statusRule, std::string& errorMessage)
	{
		try
		{
			if (!statusRule->GetOperation().empty() && 0 != statusRule->GetStatusID())
			{
				return statusRule->CreateStatusRule(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Status rule operation and status ID must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateStatusRule(BusinessLayer::StatusRule* statusRule, std::string& errorMessage)
	{
		try
		{
			if (!statusRule->GetOperation().empty() && 0 != statusRule->GetStatusID())
			{
				return statusRule->UpdateStatusRule(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Status rule operation and status ID must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteStatusRule(BusinessLayer::StatusRule* statusRule, std::string& errorMessage)
	{
		try
		{
			if (0 != statusRule->GetID())
			{
				return statusRule->DeleteStatusRule(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Status ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateStock(BusinessLayer::Stock* stock, std::string& errorMessage)
	{
		try
		{
			if (0 != stock->GetProductID() && 0 != stock->GetCount() &&
				0 != stock->GetSum() && 0 != stock->GetStatusID() && 0 != stock->GetCurrencyID())
			{
				return stock->CreateStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateStock(BusinessLayer::Stock* stock, std::string& errorMessage)
	{
		try
		{
			if (0 != stock->GetProductID() && 0 != stock->GetCount() &&
				0 != stock->GetSum() && 0 != stock->GetStatusID() && 0 != stock->GetCurrencyID())
			{
				return stock->UpdateStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteStock(BusinessLayer::Stock* stock, std::string& errorMessage)
	{
		try
		{
			if (0 != stock->GetID())
			{
				return stock->DeleteStock(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Stock ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateStockLimit(BusinessLayer::StockLimit* stockLimit, std::string& errorMessage)
	{
		try
		{
			if (0 != stockLimit->GetProductID() && 0 <= stockLimit->GetMinValue() &&
				0 <= stockLimit->GetMaxValue() && 0 != stockLimit->GetStockID())
			{
				return stockLimit->CreateStockLimit(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateStockLimit(BusinessLayer::StockLimit* stockLimit, std::string& errorMessage)
	{
		try
		{
			if (0 != stockLimit->GetProductID() && 0 <= stockLimit->GetMinValue() &&
				0 <= stockLimit->GetMaxValue() && 0 != stockLimit->GetStockID())
			{
				return stockLimit->UpdateStockLimit(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteStockLimit(BusinessLayer::StockLimit* stockLimit, std::string& errorMessage)
	{
		try
		{
			if (0 != stockLimit->GetID())
			{
				return stockLimit->DeleteStockLimit(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Stock ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateStockHistory(BusinessLayer::StockHistory* stockHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != stockHistory->GetProductID() && 0 != stockHistory->GetCount() &&
				0 != stockHistory->GetSum() && 0 != stockHistory->GetStatusID() && 0 != stockHistory->GetCurrencyID()
				&& !stockHistory->GetHistoryDate().empty())
			{
				return stockHistory->CreateStockHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateStockHistory(BusinessLayer::StockHistory* stockHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != stockHistory->GetProductID() && 0 != stockHistory->GetCount() &&
				0 != stockHistory->GetSum() && 0 != stockHistory->GetStatusID() && 0 != stockHistory->GetCurrencyID()
				&& !stockHistory->GetHistoryDate().empty())
			{
				return stockHistory->UpdateStockHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteStockHistory(BusinessLayer::StockHistory* stockHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != stockHistory->GetID())
			{
				return stockHistory->DeleteStockHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Stock history ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateStockChangeLog(BusinessLayer::StockChangeLog* stockChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != stockChangeLog->GetStockID() && !stockChangeLog->GetLogDate().empty())
			{
				return stockChangeLog->CreateStockChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateStockChangeLog(BusinessLayer::StockChangeLog* stockChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != stockChangeLog->GetStockID() && !stockChangeLog->GetLogDate().empty())
			{
				return stockChangeLog->UpdateStockChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteStockChangeLog(BusinessLayer::StockChangeLog* stockChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != stockChangeLog->GetID())
			{
				return stockChangeLog->DeleteStockChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Stock change log ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSubaccount(BusinessLayer::Subaccount* subaccount, std::string& errorMessage)
	{
		try
		{
			if (0 != subaccount->GetParentAccountID() && !subaccount->GetNumber().empty() && 0 != subaccount->GetCurrencyID() 
				&& !subaccount->GetOpenedDate().empty() && 0 != subaccount->GetStatusID())
			{
				return subaccount->CreateSubaccount(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSubaccount(BusinessLayer::Subaccount* subaccount, std::string& errorMessage)
	{
		try
		{
			if (0 != subaccount->GetParentAccountID() && !subaccount->GetNumber().empty() && 0 != subaccount->GetCurrencyID()
				&& !subaccount->GetOpenedDate().empty() && 0 != subaccount->GetStatusID())
			{
				return subaccount->UpdateSubaccount(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSubaccount(BusinessLayer::Subaccount* subaccount, std::string& errorMessage)
	{
		try
		{
			if (0 != subaccount->GetID())
			{
				return subaccount->DeleteSubaccount(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Subaccount item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSubaccountLimit(BusinessLayer::SubaccountLimit* subaccountLimit, std::string& errorMessage)
	{
		try
		{
			if (0 != subaccountLimit->GetSubaccountID())
			{
				return subaccountLimit->CreateSubaccountLimit(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSubaccountLimit(BusinessLayer::SubaccountLimit* subaccountLimit, std::string& errorMessage)
	{
		try
		{
			if (0 != subaccountLimit->GetSubaccountID())
			{
				return subaccountLimit->UpdateSubaccountLimit(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSubaccountLimit(BusinessLayer::SubaccountLimit* subaccountLimit, std::string& errorMessage)
	{
		try
		{
			if (0 != subaccountLimit->GetID())
			{
				return subaccountLimit->DeleteSubaccountLimit(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Subaccount item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSubaccountHistory(BusinessLayer::SubaccountHistory* subaccountHis, std::string& errorMessage)
	{
		try
		{
			if (!subaccountHis->GetFromDate().empty() && !subaccountHis->GetTillDate().empty())
			{
				return subaccountHis->CreateSubaccountHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSubaccountHistory(BusinessLayer::SubaccountHistory* subaccountHis, std::string& errorMessage)
	{
		try
		{
			if (!subaccountHis->GetFromDate().empty() && !subaccountHis->GetTillDate().empty())
			{
				return subaccountHis->UpdateSubaccountHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSubaccountHistory(BusinessLayer::SubaccountHistory* subaccountHis, std::string& errorMessage)
	{
		try
		{
			if (0 != subaccountHis->GetID())
			{
				return subaccountHis->DeleteSubaccountHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Subaccount history item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateSubaccountChangeLog(BusinessLayer::SubaccountChangeLog* subaccountChangeLog, std::string& errorMessage)
	{
		try
		{
			if (!subaccountChangeLog->GetLogDate().empty() && 0 != subaccountChangeLog->GetSubaccountID())
			{
				return subaccountChangeLog->CreateSubaccountChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateSubaccountChangeLog(BusinessLayer::SubaccountChangeLog* subaccountChangeLog, std::string& errorMessage)
	{
		try
		{
			if (!subaccountChangeLog->GetLogDate().empty() && 0 != subaccountChangeLog->GetSubaccountID())
			{
				return subaccountChangeLog->UpdateSubaccountChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteSubaccountChangeLog(BusinessLayer::SubaccountChangeLog* subaccountChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != subaccountChangeLog->GetID())
			{
				return subaccountChangeLog->DeleteSubaccountChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Subaccount change log item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateTax(BusinessLayer::Tax* tax, std::string& errorMessage)
	{
		try
		{
			if (!tax->GetName().empty() && !tax->GetCode().empty())
			{
				return tax->CreateTax(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateTax(BusinessLayer::Tax* tax, std::string& errorMessage)
	{
		try
		{
			if (!tax->GetName().empty() && !tax->GetCode().empty())
			{
				return tax->UpdateTax(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteTax(BusinessLayer::Tax* tax, std::string& errorMessage)
	{
		try
		{
			if (0 != tax->GetID())
			{
				return tax->DeleteTax(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Tax item ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateTimesheet(BusinessLayer::Timesheet* timesheet, std::string& errorMessage)
	{
		try
		{
			if (0 != timesheet->GetSalaryID() && 0 != timesheet->GetWorkedTime() && !timesheet->GetDate().empty())
			{
				return timesheet->CreateTimesheet(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateTimesheet(BusinessLayer::Timesheet* timesheet, std::string& errorMessage)
	{
		try
		{
			if (0 != timesheet->GetSalaryID() && 0 != timesheet->GetWorkedTime() && !timesheet->GetDate().empty())
			{
				return timesheet->UpdateTimesheet(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteTimesheet(BusinessLayer::Timesheet* timesheet, std::string& errorMessage)
	{
		try
		{
			if (0 != timesheet->GetID())
			{
				return timesheet->DeleteTimesheet(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Timesheet ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateTransport(BusinessLayer::Transport* transport, std::string& errorMessage)
	{
		try
		{
			if (!transport->GetDate().empty() && 0 != transport->GetUserID() && 0 != transport->GetCount()
				&& 0 != transport->GetSum() && 0 != transport->GetStatusID() && 0 != transport->GetCurrencyID()
				&& 0 != transport->GetEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, transport->GetCurrencyID(), errorMessage))
				{
					roundSum = round(transport->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				transport->SetSum(roundSum);
				return transport->CreateTransport(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateTransport(BusinessLayer::Transport* transport, std::string& errorMessage)
	{
		try
		{
			if (!transport->GetDate().empty() && 0 != transport->GetUserID() && 0 != transport->GetCount()
				&& 0 != transport->GetSum() && 0 != transport->GetStatusID() && 0 != transport->GetCurrencyID()
				&& 0 != transport->GetEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, transport->GetCurrencyID(), errorMessage))
				{
					roundSum = round(transport->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				transport->SetSum(roundSum);
				return transport->UpdateTransport(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteTransport(BusinessLayer::Transport* transport, std::string& errorMessage)
	{
		try
		{
			if (0 != transport->GetID())
			{
				return transport->DeleteTransport(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Transport ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateTransportHistory(BusinessLayer::TransportHistory* transportHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != transportHistory->GetTransportID() && 0 != transportHistory->GetProductID()
				&& 0 != transportHistory->GetCount() && 0 != transportHistory->GetSum() && 0 != transportHistory->GetStatusID()
				&& 0 != transportHistory->GetCurrencyID())
			{
				return transportHistory->CreateTransportHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateTransportHistory(BusinessLayer::TransportHistory* transportHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != transportHistory->GetTransportID() && 0 != transportHistory->GetProductID()
				&& 0 != transportHistory->GetCount() && 0 != transportHistory->GetSum() && 0 != transportHistory->GetStatusID()
				&& 0 != transportHistory->GetCurrencyID())
			{
				return transportHistory->UpdateTransportHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteTransportHistory(BusinessLayer::TransportHistory* transportHistory, std::string& errorMessage)
	{
		try
		{
			if (0 != transportHistory->GetID())
			{
				return transportHistory->DeleteTransportHistory(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Stock transfer list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateTransportChangeLog(BusinessLayer::TransportChangeLog* transportChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != transportChangeLog->GetTransportID() && !transportChangeLog->GetLogDate().empty())
			{
				return transportChangeLog->CreateTransportChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateTransportChangeLog(BusinessLayer::TransportChangeLog* transportChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != transportChangeLog->GetTransportID() && !transportChangeLog->GetLogDate().empty())
			{
				return transportChangeLog->UpdateTransportChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteTransportChangeLog(BusinessLayer::TransportChangeLog* transportChangeLog, std::string& errorMessage)
	{
		try
		{
			if (0 != transportChangeLog->GetID())
			{
				return transportChangeLog->DeleteTransportChangeLog(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Stock transfer change log ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateTransportList(BusinessLayer::TransportList* transportList, std::string& errorMessage)
	{
		try
		{
			if (0 != transportList->GetTransportID() && 0 != transportList->GetProductID()
				&& 0 != transportList->GetCount() && 0 != transportList->GetSum() && 0 != transportList->GetStatusID()
				&& 0 != transportList->GetCurrencyID())
			{
				return transportList->CreateTransportList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateTransportList(BusinessLayer::TransportList* transportList, std::string& errorMessage)
	{
		try
		{
			if (0 != transportList->GetTransportID() && 0 != transportList->GetProductID()
				&& 0 != transportList->GetCount() && 0 != transportList->GetSum() && 0 != transportList->GetStatusID()
				&& 0 != transportList->GetCurrencyID())
			{
				return transportList->UpdateTransportList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteTransportList(BusinessLayer::TransportList* transportList, std::string& errorMessage)
	{
		try
		{
			if (0 != transportList->GetID())
			{
				return transportList->DeleteTransportList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Transport list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateUser(BusinessLayer::User* user, std::string& errorMessage)
	{
		try
		{
			if (!user->GetName().empty() && !user->GetSurname().empty() && !user->GetPhone().empty() && !user->GetAddress().empty()
				&& !user->GetPassword().empty() && 0 != user->GetRoleID())
			{
				return user->CreateUser(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateUser(BusinessLayer::User* user, std::string& errorMessage)
	{
		try
		{
			if (!user->GetName().empty() && !user->GetSurname().empty() && !user->GetPhone().empty() && !user->GetAddress().empty()
				&& !user->GetPassword().empty()  && 0 != user->GetRoleID())
			{
				return user->UpdateUser(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteUser(BusinessLayer::User* user, std::string& errorMessage)
	{
		try
		{
			if (0 != user->GetID())
			{
				return user->DeleteUser(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateUserGroupRelation(BusinessLayer::UserGroupRelation* userGroup, std::string& errorMessage)
	{
		try
		{
			if (0 != userGroup->GetGroupID() && 0 != userGroup->GetUserID())
			{
				return userGroup->CreateUserGroupRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateUserGroupRelation(BusinessLayer::UserGroupRelation* userGroup, std::string& errorMessage)
	{
		try
		{
			if (0 != userGroup->GetGroupID() && 0 != userGroup->GetUserID())
			{
				return userGroup->UpdateUserGroupRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteUserGroupRelation(BusinessLayer::UserGroupRelation* userGroup, std::string& errorMessage)
	{
		try
		{
			if (0 != userGroup->GetID())
			{
				return userGroup->DeleteUserGroupRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateWarehouse(BusinessLayer::Warehouse* warehouse, std::string& errorMessage)
	{
		try
		{
			if (0 != warehouse->GetSubaccountID() && 0 != warehouse->GetWarehouseTypeID() && !warehouse->GetName().empty() 
				&& !warehouse->GetAddress().empty() && !warehouse->GetPhone().empty())
			{
				return warehouse->CreateWarehouse(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields of warehouse must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateWarehouse(BusinessLayer::Warehouse* warehouse, std::string& errorMessage)
	{
		try
		{
			if (0 != warehouse->GetSubaccountID() && 0 != warehouse->GetWarehouseTypeID() && !warehouse->GetName().empty()
				&& !warehouse->GetAddress().empty() && !warehouse->GetPhone().empty())
			{
				return warehouse->UpdateWarehouse(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields of warehouse must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteWarehouse(BusinessLayer::Warehouse* warehouse, std::string& errorMessage)
	{
		try
		{
			if (0 != warehouse->GetID())
			{
				return warehouse->DeleteWarehouse(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Warehouse ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateWarehouseType(BusinessLayer::WarehouseType* warehouseType, std::string& errorMessage)
	{
		try
		{
			if (!warehouseType->GetName().empty() && !warehouseType->GetCode().empty() && !warehouseType->GetPurpose().empty())
			{
				return warehouseType->CreateWarehouseType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields of warehouse type must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateWarehouseType(BusinessLayer::WarehouseType* warehouseType, std::string& errorMessage)
	{
		try
		{
			if (!warehouseType->GetName().empty() && !warehouseType->GetCode().empty() && !warehouseType->GetPurpose().empty())
			{
				return warehouseType->UpdateWarehouseType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! All fields of warehouse type must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteWarehouseType(BusinessLayer::WarehouseType* warehouseType, std::string& errorMessage)
	{
		try
		{
			if (0 != warehouseType->GetID())
			{
				return warehouseType->DeleteWarehouseType(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Warehouse Type ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}
	
	bool OrmasBL::CreateWarehouseEmployeeRelation(BusinessLayer::WarehouseEmployeeRelation* weRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != weRelation->GetWarehouseID() && 0 != weRelation->GetEmployeeID())
			{
				return weRelation->CreateWarehouseEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Cashbox and employee must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateWarehouseEmployeeRelation(BusinessLayer::WarehouseEmployeeRelation* weRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != weRelation->GetWarehouseID() && 0 != weRelation->GetEmployeeID())
			{
				return weRelation->UpdateWarehouseEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Warehouse and employee must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteWarehouseEmployeeRelation(BusinessLayer::WarehouseEmployeeRelation* weRelation, std::string& errorMessage)
	{
		try
		{
			if (0 != weRelation->GetWarehouseID() && 0 != weRelation->GetEmployeeID())
			{
				return weRelation->DeleteWarehouseEmployeeRelation(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Warehouse employee relation ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateWithdrawal(BusinessLayer::Withdrawal* withdrawal, std::string& errorMessage)
	{
		withdrawal->loggedUserID = loggedUser->GetID();
		try
		{
			if (0.0 != withdrawal->GetValue() && 0 != withdrawal->GetCurrencyID() && !withdrawal->GetDate().empty() && !withdrawal->GetWho().empty())
			{
				return withdrawal->CreateWithdrawal(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User, currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateWithdrawal(BusinessLayer::Withdrawal* withdrawal, std::string& errorMessage)
	{
		withdrawal->loggedUserID = loggedUser->GetID();
		try
		{
			if (0.0 != withdrawal->GetValue() && 0 != withdrawal->GetCurrencyID() && !withdrawal->GetDate().empty() && !withdrawal->GetWho().empty())
			{
				return withdrawal->UpdateWithdrawal(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! User, currency, date and value must not be empty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteWithdrawal(BusinessLayer::Withdrawal* withdrawal, std::string& errorMessage)
	{
		withdrawal->loggedUserID = loggedUser->GetID();
		try
		{
			if (0 != withdrawal->GetID())
			{
				return withdrawal->DeleteWithdrawal(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Withdrawal ID is 0. Some thing goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateWriteOff(BusinessLayer::WriteOff* writeOff, std::string& errorMessage)
	{
		try
		{
			if (!writeOff->GetDate().empty()  && 0 != writeOff->GetCount()
				&& 0 != writeOff->GetSum() && 0 != writeOff->GetStatusID() && 0 != writeOff->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, writeOff->GetCurrencyID(), errorMessage))
				{
					roundSum = round(writeOff->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				writeOff->SetSum(roundSum);
				return writeOff->CreateWriteOff(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateWriteOff(BusinessLayer::WriteOff* writeOff, std::string& errorMessage)
	{
		try
		{
			if (!writeOff->GetDate().empty() && 0 != writeOff->GetCount()
				&& 0 != writeOff->GetSum() && 0 != writeOff->GetStatusID() && 0 != writeOff->GetCurrencyID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, writeOff->GetCurrencyID(), errorMessage))
				{
					roundSum = round(writeOff->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				writeOff->SetSum(roundSum);
				return writeOff->UpdateWriteOff(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteWriteOff(BusinessLayer::WriteOff* writeOff, std::string& errorMessage)
	{
		try
		{
			if (0 != writeOff->GetID())
			{
				return writeOff->DeleteWriteOff(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Write-off ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateWriteOffList(BusinessLayer::WriteOffList* writeOffList, std::string& errorMessage)
	{
		try
		{
			if (0 != writeOffList->GetWriteOffID() && 0 != writeOffList->GetProductID()
				&& 0 != writeOffList->GetCount() && 0 != writeOffList->GetSum() && 0 != writeOffList->GetStatusID()
				&& 0 != writeOffList->GetCurrencyID())
			{
				return writeOffList->CreateWriteOffList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateWriteOffList(BusinessLayer::WriteOffList* writeOffList, std::string& errorMessage)
	{
		try
		{
			if (0 != writeOffList->GetWriteOffID() && 0 != writeOffList->GetProductID()
				&& 0 != writeOffList->GetCount() && 0 != writeOffList->GetSum() && 0 != writeOffList->GetStatusID()
				&& 0 != writeOffList->GetCurrencyID())
			{
				return writeOffList->UpdateWriteOffList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteWriteOffList(BusinessLayer::WriteOffList* writeOffList, std::string& errorMessage)
	{
		try
		{
			if (0 != writeOffList->GetID())
			{
				return writeOffList->DeleteWriteOffList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Write-off list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::CreateWriteOffRaw(BusinessLayer::WriteOffRaw* writeOffRaw, std::string& errorMessage)
	{
		try
		{
			if (!writeOffRaw->GetDate().empty() &&  0 != writeOffRaw->GetCount()
				&& 0 != writeOffRaw->GetSum() && 0 != writeOffRaw->GetStatusID() && 0 != writeOffRaw->GetCurrencyID()
				&& 0 != writeOffRaw->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, writeOffRaw->GetCurrencyID(), errorMessage))
				{
					roundSum = round(writeOffRaw->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				writeOffRaw->SetSum(roundSum);
				return writeOffRaw->CreateWriteOffRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateWriteOffRaw(BusinessLayer::WriteOffRaw* writeOffRaw, std::string& errorMessage)
	{
		try
		{
			if (!writeOffRaw->GetDate().empty()  && 0 != writeOffRaw->GetCount()
				&& 0 != writeOffRaw->GetSum() && 0 != writeOffRaw->GetStatusID() && 0 != writeOffRaw->GetCurrencyID()
				&& 0 != writeOffRaw->GetStockEmployeeID())
			{
				double roundSum = 0;
				Currency *cur = new Currency();
				if (cur->GetCurrencyByID(globalVar, ormasDal, writeOffRaw->GetCurrencyID(), errorMessage))
				{
					roundSum = round(writeOffRaw->GetSum() * cur->GetUnit()) / cur->GetUnit();
				}
				else
				{
					return false;
				}
				delete cur;
				writeOffRaw->SetSum(roundSum);
				return writeOffRaw->UpdateWriteOffRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteWriteOffRaw(BusinessLayer::WriteOffRaw* writeOffRaw, std::string& errorMessage)
	{
		try
		{
			if (0 != writeOffRaw->GetID())
			{
				return writeOffRaw->DeleteWriteOffRaw(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Write-off raw ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}
	
	bool OrmasBL::CreateWriteOffRawList(BusinessLayer::WriteOffRawList* writeOffRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != writeOffRawList->GetWriteOffRawID() && 0 != writeOffRawList->GetProductID()
				&& 0 != writeOffRawList->GetCount() && 0 != writeOffRawList->GetSum() && 0 != writeOffRawList->GetStatusID()
				&& 0 != writeOffRawList->GetCurrencyID())
			{
				return writeOffRawList->CreateWriteOffRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One or several feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::UpdateWriteOffRawList(BusinessLayer::WriteOffRawList* writeOffRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != writeOffRawList->GetWriteOffRawID() && 0 != writeOffRawList->GetProductID()
				&& 0 != writeOffRawList->GetCount() && 0 != writeOffRawList->GetSum() && 0 != writeOffRawList->GetStatusID()
				&& 0 != writeOffRawList->GetCurrencyID())
			{
				return writeOffRawList->UpdateWriteOffRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! One of feilds are emplty. Please fill up them!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}

	bool OrmasBL::DeleteWriteOffRawList(BusinessLayer::WriteOffRawList* writeOffRawList, std::string& errorMessage)
	{
		try
		{
			if (0 != writeOffRawList->GetID())
			{
				return writeOffRawList->DeleteWriteOffRawList(globalVar, ormasDal, errorMessage);
			}
			else
			{
				errorMessage = "Error! Write-off raw  list ID is 0. Something goes wrong!";
			}
		}
		catch (...)
		{
			errorMessage = "Fatal error! Please contact with application provider.";
		}
		return false;
	}


	//Close of month functions
	//Close of month
	bool OrmasBL::CloseOfMonth(std::string fromDate, std::string tillDate)
	{
		std::string errorMessage = "";
		//ormasDal.StartTransaction(errorMessage);
		if (CalculateEmployeeSalary(fromDate, tillDate))
		{
			//ormasDal.CommitTransaction(errorMessage);
		}
		else
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		//ormasDal.StartTransaction(errorMessage);
		if (!SaveAccountState(fromDate, ""))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!CalculateTax(fromDate, tillDate))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!CalculateAmortization(fromDate, tillDate))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!RecalculateNetCost(fromDate, tillDate))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!CorrectingNetCostInStock())
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!CorrectingNetCostInTransport())
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!CorrectingEntries())
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!GenerateReports(fromDate, tillDate))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!CalculateCloseOfMonth(fromDate, tillDate))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		//ormasDal.CommitTransaction(errorMessage);
		CloseOfAccount70000();
		if (!SaveAccountState("", tillDate))
		{
			return false;
		}
		if (!SaveStockState("", tillDate))
		{
			return false;
		}
		if (!SaveTransportState("", tillDate))
		{
			return false;
		}
		if (!CorrectDates(tillDate))
		{
			return false;
		}
		return true;
	}

	bool OrmasBL::SaveAccountState(std::string fromDate, std::string tillDate)
	{
		std::string errorMessage = "";
		if (tillDate.empty())
		{
			//save state of accounts
			std::vector<Account> vecForAccount;
			std::vector<DataLayer::accountsCollection> accCollection;
			accCollection = ormasDal.GetAccounts(errorMessage);
			if (!accCollection.empty()){
				for (auto data : accCollection)
				{
					vecForAccount.push_back(Account(data));
				}
			}
			AccountHistory accHis;
			for each (auto item in vecForAccount)
			{
				accHis.Clear();
				accHis.SetID(ormasDal.GenerateID());
				accHis.SetAccountID(item.GetID());
				accHis.SetNumber(item.GetNumber());
				accHis.SetStartBalance(item.GetStartBalance());
				accHis.SetCurrentBalance(item.GetCurrentBalance());
				accHis.SetFromDate(fromDate);
				accHis.SetTillDate(fromDate);
				if (!accHis.CreateAccountHistory(globalVar, ormasDal, errorMessage))
					return false;
			}

			//save state of subaccounts
			std::vector<SubaccountView> vecForSubaccountHis;
			std::vector<DataLayer::subaccountsViewCollection> subaccCollection;
			subaccCollection = ormasDal.GetSubaccounts(errorMessage);
			if (!subaccCollection.empty()){
				for (auto data : subaccCollection)
				{
					vecForSubaccountHis.push_back(SubaccountView(data));
				}
			}
			SubaccountHistory saccHis;
			for each (auto item in vecForSubaccountHis)
			{
				saccHis.Clear();
				saccHis.SetID(ormasDal.GenerateID());
				saccHis.SetSubaccountID(item.GetID());
				saccHis.SetStartBalance(item.GetStartBalance());
				saccHis.SetCurrentBalance(item.GetCurrentBalance());
				saccHis.SetFromDate(fromDate);
				saccHis.SetTillDate(fromDate);
				if (!saccHis.CreateSubaccountHistory(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		if (fromDate.empty())
		{
			//save state of accounts
			std::vector<Account> vecForAccount;
			std::vector<DataLayer::accountsCollection> accCollection;
			accCollection = ormasDal.GetAccounts(errorMessage);
			if (!accCollection.empty()){
				for (auto data : accCollection)
				{
					vecForAccount.push_back(Account(data));
				}
			}
			AccountHistory accHis;
			for each (auto item in vecForAccount)
			{
				accHis.Clear();
				accHis.SetID(ormasDal.GenerateID());
				accHis.SetAccountID(item.GetID());
				accHis.SetNumber(item.GetNumber());
				accHis.SetStartBalance(item.GetStartBalance());
				accHis.SetCurrentBalance(item.GetCurrentBalance());
				accHis.SetFromDate(tillDate);
				accHis.SetTillDate(tillDate);
				if (!accHis.CreateAccountHistory(globalVar, ormasDal, errorMessage))
					return false;
			}

			//save state of subaccounts
			std::vector<SubaccountView> vecForSubaccountHis;
			std::vector<DataLayer::subaccountsViewCollection> subaccCollection;
			subaccCollection = ormasDal.GetSubaccounts(errorMessage);
			if (!subaccCollection.empty()){
				for (auto data : subaccCollection)
				{
					vecForSubaccountHis.push_back(SubaccountView(data));
				}
			}
			SubaccountHistory saccHis;
			for each (auto item in vecForSubaccountHis)
			{
				saccHis.Clear();
				saccHis.SetID(ormasDal.GenerateID());
				saccHis.SetSubaccountID(item.GetID());
				saccHis.SetStartBalance(item.GetStartBalance());
				saccHis.SetCurrentBalance(item.GetCurrentBalance());
				saccHis.SetFromDate(tillDate);
				saccHis.SetTillDate(tillDate);
				if (!saccHis.CreateSubaccountHistory(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		return true;
	}

	bool OrmasBL::SaveStockState(std::string fromDate, std::string tillDate)
	{
		std::string errorMessage = "";
		//save state of accounts
		std::vector<StockView> vecForStock;
		std::vector<DataLayer::stockViewCollection> stockCollection;
		stockCollection = ormasDal.GetStock(errorMessage);
		if (!stockCollection.empty()){
			for (auto data : stockCollection)
			{
				vecForStock.push_back(StockView(data));
			}
		}
		StockHistory stockHis;
		for each (auto item in vecForStock)
		{
			stockHis.Clear();
			stockHis.SetID(ormasDal.GenerateID());
			stockHis.SetProductID(item.GetProductID());
			stockHis.SetCount(item.GetCount());
			stockHis.SetSum(item.GetSum());
			stockHis.SetCurrencyID(item.GetCurrencyID());
			stockHis.SetWarehouseID(item.GetWarehouseID());
			stockHis.SetHistoryDate(tillDate);
			if (!stockHis.CreateStockHistory(globalVar, ormasDal, errorMessage))
				return false;
		}
		return true;
	}

	bool OrmasBL::SaveTransportState(std::string fromDate, std::string tillDate)
	{
		std::string errorMessage = "";
		//save state of accounts
		std::vector<TransportListView> vecForTransportList;
		std::vector<DataLayer::transportListViewCollection> transportListCollection;
		transportListCollection = ormasDal.GetTransportList(errorMessage);
		if (!transportListCollection.empty())
		{
			for each (auto data in transportListCollection)
			{
				vecForTransportList.push_back(TransportListView(data));
			}
		}
		TransportHistory tranHis;
		for each (auto item in vecForTransportList)
		{
			tranHis.Clear();
			tranHis.SetID(ormasDal.GenerateID());
			tranHis.SetProductID(item.GetProductID());
			tranHis.SetCount(item.GetCount());
			tranHis.SetSum(item.GetSum());
			tranHis.SetCurrencyID(item.GetCurrencyID());
			tranHis.SetTransportID(item.GetTransportID());
			tranHis.SetFromDate(tillDate);
			tranHis.SetTillDate(tillDate);
			if (!tranHis.CreateTransportHistory(globalVar, ormasDal, errorMessage))
				return false;
		}
		return true;
	}

	bool OrmasBL::CalculateEmployeeSalary(std::string fromDate, std::string tillDate)
	{
		std::string errorMessage = "";
		double sum = 0;
		double count = 0;
		std::vector<EmployeeView> employeeVector = this->GetAllDataForClass<EmployeeView>(errorMessage);
		if (employeeVector.size() > 0)
		{
			Salary salary;
			std::string salaryFilter;
			std::vector<SalaryView> salaryVector;
			std::map<std::string, int> salaryTypeMap = SalaryType::GetSalaryTypesAsMap(globalVar, ormasDal, errorMessage);
			std::map<std::string, int> statusMap = Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
			Payslip payslip;
			Order order;
			Timesheet timesheet;
			Jobsheet jobsheet;
			Jobprice jobprice;
			std::string orderFilter;
			std::string timesheetFilter;
			std::string jobsheetFilter;
			std::vector<OrderView> orderVector;
			std::vector<TimesheetView> timesheetVector;
			std::vector<JobsheetView> jobsheetVector;
			std::map<int, double> workedPieceMap;

			for each (auto employeeItem in employeeVector)
			{
				if (!employeeItem.IsEmpty())
				{
					errorMessage = "";
					salary.Clear();
					salary.SetEmployeeID(employeeItem.GetID());
					salaryFilter = salary.GenerateFilter(ormasDal);
					salaryVector.clear();
					salaryVector = this->GetAllDataForClass<SalaryView>(errorMessage, salaryFilter);
					if (errorMessage.empty())
					{
						if (1 <= salaryVector.size())
						{
							if (salaryTypeMap.size() > 0 && statusMap.size() > 0)
							{
								for each (auto salaryItem in salaryVector)
								{
									try
									{
										if (salaryItem.GetValue() > 0)
										{
											if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("FIXED")->second)
											{
												payslip.Clear();
												payslip.SetDate(ormasDal.GetSystemDateTime());
												payslip.SetSalaryID(salaryItem.GetID());
												payslip.SetCurrencyID(salaryItem.GetCurrencyID());
												payslip.SetValue(salaryItem.GetValue());

												if (!payslip.CreatePayslip(globalVar, ormasDal, errorMessage))
													return false;
											}
											if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("PERCENT")->second)
											{
												order.Clear();
												order.SetEmployeeID(salary.GetEmployeeID());
												order.SetStatusID(statusMap.find("EXECUTED")->second);
												orderFilter.clear();
												orderFilter = order.GenerateFilterForPeriod(globalVar, ormasDal, fromDate, tillDate);
												orderVector.clear();
												orderVector = this->GetAllDataForClass<OrderView>(errorMessage, orderFilter);
												sum = 0;
												if (orderVector.size() > 0)
												{
													for each (auto orderItem in orderVector)
													{
														sum += orderItem.GetSum();
													}
												}
												if (sum > 0)
												{
													payslip.Clear();
													payslip.SetDate(ormasDal.GetSystemDateTime());
													payslip.SetSalaryID(salaryItem.GetID());
													payslip.SetCurrencyID(salaryItem.GetCurrencyID());
													payslip.SetValue(sum * salaryItem.GetValue() / 1000);
													if (!payslip.CreatePayslip(globalVar, ormasDal, errorMessage))
														return false;
												}
											}
											if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("HOURLY")->second)
											{
												timesheet.Clear();
												timesheet.SetSalaryID(salary.GetID());
												timesheetFilter.clear();
												timesheetFilter = timesheet.GenerateFilterForPeriod(globalVar, ormasDal, fromDate, tillDate);
												timesheetVector.clear();
												timesheetVector = this->GetAllDataForClass<TimesheetView>(errorMessage, timesheetFilter);
												count = 0;
												if (timesheetVector.size() > 0)
												{
													for each (auto timesheetItem in timesheetVector)
													{
														count += timesheetItem.GetWorkedTime();
													}
												}
												if (count > 0)
												{
													payslip.Clear();
													payslip.SetDate(ormasDal.GetSystemDateTime());
													payslip.SetSalaryID(salaryItem.GetID());
													payslip.SetCurrencyID(salaryItem.GetCurrencyID());
													payslip.SetValue(std::round(salaryItem.GetValue()* count * 100) / 100);
													if (!payslip.CreatePayslip(globalVar, ormasDal, errorMessage))
														return false;
												}
											}
											if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("SHIFT")->second)
											{
												/*payslip.Clear();
												payslip.SetDate(ormasDal.GetSystemDateTime());
												payslip.SetSalaryID(salaryItem.GetID());
												payslip.SetCurrencyID(salaryItem.GetCurrencyID());
												payslip.SetValue(salaryItem.GetValue());
												if (!payslip.CreatePayslip(globalVar, ormasDal, errorMessage))
												return false;*/
											}
											if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("PIECE")->second)
											{
												jobsheet.Clear();
												jobsheet.SetEmployeeID(salary.GetEmployeeID());
												jobsheetFilter.clear();
												jobsheetFilter = jobsheet.GenerateFilterForPeriod(globalVar, ormasDal, fromDate, tillDate);
												jobsheetVector.clear();
												jobsheetVector = this->GetAllDataForClass<JobsheetView>(errorMessage, timesheetFilter);
												if (jobsheetVector.size() > 0)
												{
													for each (auto jobsheetItem in jobsheetVector)
													{
														if (workedPieceMap.find(jobsheetItem.GetProductID()) == workedPieceMap.end())
														{
															workedPieceMap.insert(std::make_pair(jobsheetItem.GetProductID(), jobsheetItem.GetCount()));
														}
														else
														{
															workedPieceMap.find(jobsheetItem.GetProductID())->second = workedPieceMap.find(jobsheetItem.GetProductID())->second + jobsheetItem.GetCount();
														}
													}
												}
												if (workedPieceMap.size() > 0)
												{
													sum = 0;
													for each (auto workedPieceItem in workedPieceMap)
													{
														jobprice.Clear();
														if (!jobprice.GetJobpriceByID(globalVar, ormasDal, workedPieceItem.first, errorMessage))
															return false;
														sum += std::round(jobprice.GetValue() * workedPieceItem.second * 100) / 100;
													}
												}
												payslip.Clear();
												payslip.SetDate(ormasDal.GetSystemDateTime());
												payslip.SetSalaryID(salaryItem.GetID());
												payslip.SetCurrencyID(salaryItem.GetCurrencyID());
												payslip.SetValue(sum);
												if (!payslip.CreatePayslip(globalVar, ormasDal, errorMessage))
													return false;
											}
										}
									}
									catch (...)
									{
										return false;
									}
								}
							}
							else
							{
								return false;
							}
						}
					}
					else
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}

	bool OrmasBL::CorrectingEntries()
	{
		std::string errorMessage;
		Account account10730;
		Account account55020;
		if (!account10730.GetAccountByNumber(globalVar, ormasDal, "10730", errorMessage))
			return false;
		if (!account55020.GetAccountByNumber(globalVar, ormasDal, "55020", errorMessage))
			return false;
		double correctingValue = 0;
		double correctingStockValue = 0;
		double temp = account10730.GetCurrentBalance();
		correctingValue = std::round((account10730.GetCurrentBalance()) * 10000)/10000;
		
		Entry entry;
		CompanyAccountRelation cAccRel;
		Company company;
		int companyID = company.GetCompanyID(globalVar, ormasDal, errorMessage);
		int acc55010 = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55010", errorMessage);
		int acc55020 = account55020.GetID();

		if (correctingValue > 0)
		{
			entry.Clear();
			entry.SetID(ormasDal.GenerateID());
			entry.SetDebitingAccountID(acc55020);
			entry.SetValue(correctingValue);
			entry.SetCreditingAccountID(account10730.GetID());
			entry.SetDate(ormasDal.GetSystemDateTime());
			entry.SetDescription(wstring_to_utf8(L"Обнуление счета расходы 10730 через счет 55020"));
			if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
				return false;
		}
		else if (correctingValue < 0)
		{
			entry.Clear();
			entry.SetID(ormasDal.GenerateID());
			entry.SetDebitingAccountID(account10730.GetID());
			entry.SetValue(correctingValue * (-1));
			entry.SetCreditingAccountID(acc55020);
			entry.SetDate(ormasDal.GetSystemDateTime());
			entry.SetDescription(wstring_to_utf8(L"Обнуление счета расходы 10730 через счет 55020"));
			if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
				return false;
		}
		account55020.Clear();
		if (!account55020.GetAccountByNumber(globalVar, ormasDal, "55020", errorMessage))
			return false;
		correctingStockValue = account55020.GetCurrentBalance();
		if (correctingStockValue > 0)
		{
			entry.Clear();
			entry.SetID(ormasDal.GenerateID());
			entry.SetDebitingAccountID(acc55010);
			entry.SetValue(correctingStockValue);
			entry.SetCreditingAccountID(account55020.GetID());
			entry.SetDate(ormasDal.GetSystemDateTime());
			entry.SetDescription(wstring_to_utf8(L"Коррекция счета 55010 при закрытии месяца, счет 55020 корректирует переоценку"));
			if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
				return false;
		}
		else if (correctingStockValue < 0)
		{
			entry.Clear();
			entry.SetID(ormasDal.GenerateID());
			entry.SetDebitingAccountID(account55020.GetID());
			entry.SetValue(correctingStockValue * (-1));
			entry.SetCreditingAccountID(acc55010);
			entry.SetDate(ormasDal.GetSystemDateTime());
			entry.SetDescription(wstring_to_utf8(L"Коррекция счета 55010 при закрытии месяца, счет 55020 корректирует переоценку"));
			if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
				return false;
		}
		return true;
	}

	bool OrmasBL::CalculateAmortization(std::string fromDate, std::string tillDate)
	{
		std::string errorMessage = "";
		FixedAssets fixedAst;
		FixedAssetsDetails faDetails;
		Subaccount primeAcc;
		Subaccount amortizeAcc;
		ChartOfAccounts cao;
		Account account;
		Account debitAcc;
		Account creditAcc;
		double amortizeValue = 0;
		std::string entryText="";
		Entry entry;
		Division division;
		std::vector<FixedAssetsView> astVect = this->GetAllDataForClass<FixedAssetsView>(errorMessage);
		for each (auto fa in astVect)
		{
			if (fa.GetIsAmortize() == true)
			{
				cao.Clear();
				account.Clear();
				faDetails.Clear();
				primeAcc.Clear();
				amortizeAcc.Clear();
				amortizeValue = 0;
				entry.Clear(); 
				division.Clear();
				debitAcc.Clear();
				creditAcc.Clear();
				if (!faDetails.GetFixedAssetsDetailsByID(globalVar, ormasDal, fa.GetFixedAssetsDetailsID(), errorMessage))
					return false;
				if (!primeAcc.GetSubaccountByID(globalVar, ormasDal, faDetails.GetPrimaryCostAccountID(), errorMessage))
					return false;
				if (!amortizeAcc.GetSubaccountByID(globalVar, ormasDal, faDetails.GetAmortizeAccountID(), errorMessage))
					return false;
				if (amortizeAcc.GetCurrentBalance() == primeAcc.GetCurrentBalance())
					continue;
				amortizeValue = (primeAcc.GetCurrentBalance() * faDetails.GetAmortizeValue()) / 12 / 100;
				if (primeAcc.GetCurrentBalance() + amortizeAcc.GetCurrentBalance() < amortizeValue)
					amortizeValue = primeAcc.GetCurrentBalance() + amortizeAcc.GetCurrentBalance();
				amortizeValue = std::round(amortizeValue * 1000) / 1000;
				if (!account.GetAccountByID(globalVar, ormasDal, primeAcc.GetParentAccountID(), errorMessage))
					return false;
				if (!cao.GetChartOfAccountsByNumber(globalVar, ormasDal, account.GetNumber(), errorMessage))
					return false;
				if (!division.GetDivisionByID(globalVar, ormasDal, faDetails.GetDepartmentID(), errorMessage))
					return false;
				entryText = wstring_to_utf8(L"Начисление амортизации ");
				entryText += cao.GetName();
				entryText += wstring_to_utf8(L", ID = ");
				entryText += std::to_string(fa.GetID());

				entry.SetDate(ormasDal.GetSystemDateTime());
				entry.SetDescription(entryText);
				entry.SetValue(amortizeValue);
				if (amortizeValue > 0)
				{
					if (division.GetCode() == "PRODUCTION")
					{
						if (!debitAcc.GetAccountByNumber(globalVar, ormasDal, "10730", errorMessage))
							return false;
						entry.SetDebitingAccountID(debitAcc.GetID());
					}
					if (division.GetCode() == "RELEASE")
					{
						if (!debitAcc.GetAccountByNumber(globalVar, ormasDal, "55270", errorMessage))
							return false;
						entry.SetDebitingAccountID(debitAcc.GetID());
					}
					if (division.GetCode() == "ADMINISTRATION")
					{
						if (!debitAcc.GetAccountByNumber(globalVar, ormasDal, "55321", errorMessage))
							return false;
						entry.SetDebitingAccountID(debitAcc.GetID());
					}
					if (entry.GetDebitingAccountID() == 0)
						return false;
					entry.SetCreditingAccountID(amortizeAcc.GetID());
				}
				else
				{
					entry.SetDebitingAccountID(amortizeAcc.GetID());
					if (division.GetCode() == "PRODUCTION")
					{
						if (!creditAcc.GetAccountByNumber(globalVar, ormasDal, "10730", errorMessage))
							return false;
						entry.SetCreditingAccountID(creditAcc.GetID());
					}
					if (division.GetCode() == "RELEASE")
					{
						if (!creditAcc.GetAccountByNumber(globalVar, ormasDal, "55270", errorMessage))
							return false;
						entry.SetCreditingAccountID(creditAcc.GetID());
					}
					if (division.GetCode() == "ADMINISTRATION")
					{
						if (!creditAcc.GetAccountByNumber(globalVar, ormasDal, "55321", errorMessage))
							return false;
						entry.SetCreditingAccountID(creditAcc.GetID());
					}
					
					if (entry.GetCreditingAccountID() == 0)
						return false;
				}
				if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
					return false;
			}

		}
		return true;
	}

	bool OrmasBL::CalculateTax(std::string fromDate, std::string tillDate)
	{
		//to do list
		return true;
	}

	bool OrmasBL::RecalculateNetCost(std::string fromDate, std::string tillDate)
	{
		//Get all produced products ID  as vector<int productionID>
		std::string errorMessage = "";
		std::vector<Production> vecForProd;
		std::vector<DataLayer::productionCollection> pCollection;
		Production production;
		std::string filter = production.GenerateFilterForPeriod(globalVar, ormasDal, fromDate, tillDate);
		pCollection = ormasDal.GetProduction(errorMessage, filter);
		if (!pCollection.empty()){
			for (auto data : pCollection)
			{
				vecForProd.push_back(Production(data));
			}
		}
		std::vector<int> vecProductionID;
		for each (auto item in vecForProd)
		{
			vecProductionID.push_back(item.GetID());
		}

		if (vecProductionID.size() == 0)
			return false;

		//Get all produced products ID  as map<int productID, double count>
		ProductionList pList;
		std::string pListFilter;
		std::vector<ProductionListView> vecForProdList;
		std::vector<DataLayer::productionListViewCollection> pListCollection;
		for each (auto prodID in vecProductionID)
		{
			pList.Clear();
			pListFilter.clear();
			pListCollection.clear();
			pList.SetProductionID(prodID);
			pListFilter = pList.GenerateFilter(ormasDal);
			pListCollection = ormasDal.GetProductionList(errorMessage, pListFilter);
			if (!pListCollection.empty()){
				for (auto data : pListCollection)
				{
					vecForProdList.push_back(ProductionListView(data));
				}
			}
		}
		
		std::map<int, double> mapProducedProducts;
		double totalSum = 0;
		NetCost nCost;
		for each (auto item in vecForProdList)
		{
			nCost.Clear();
			std::map<int, double>::iterator it = mapProducedProducts.find(item.GetProductID());
			if (it != mapProducedProducts.end())
			{
				if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
					return false;
				it->second += item.GetCount();
				totalSum += item.GetCount()*nCost.GetValue();
			}
			else
			{
				if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
					return false;
				mapProducedProducts.insert(std::make_pair(item.GetProductID(), item.GetCount()));
				totalSum += item.GetCount()*nCost.GetValue();
			}
		}

		//Get pure net cost from specification list as map<int productID, double netCost>
		std::vector<SpecificationView> vecForSpec;
		std::vector<DataLayer::specificationsViewCollection> pSpecCollection;
		pSpecCollection = ormasDal.GetSpecifications(errorMessage);
		if (!pSpecCollection.empty()){
			for (auto data : pSpecCollection)
			{
				vecForSpec.push_back(SpecificationView(data));
			}
		}
		std::multimap<double, int> mapNetCost;
		for(unsigned int i = 0; i < vecForSpec.size(); i++)
		{
			mapNetCost.insert(std::make_pair(vecForSpec[i].GetSum(), vecForSpec[i].GetProductID()));
		}

		//Calculate product coificient
		std::map<int, double> coif;

		int i = 0;
		double divide = 0;
		divide = mapNetCost.begin()->first;
		for each (auto item in mapNetCost)
		{
			if (i == 0)
				coif.insert(std::make_pair(item.second, 1));
			coif.insert(std::make_pair(item.second, (item.first / divide)));
			i++;
		}


		//Calculate tolal count
		double totalCount = 0;
		for each (auto item in mapProducedProducts)
		{
			if (coif.find(item.first) != coif.end())
			{
				totalCount += item.second * coif.find(item.first)->second;
			}
			else
			{
				return false;
			}
		}

		Account account10730;
		if (!account10730.GetAccountByNumber(globalVar, ormasDal, "10730", errorMessage))
			return false;

		double totalConsumptionSum = 0;
		totalConsumptionSum = account10730.GetCurrentBalance() + totalSum;
		if (0 == totalConsumptionSum)
			return false;
		double totalNetCost = 0;
		//totalNetCost = account10730.GetCurrentBalance() / totalCount;
		totalNetCost = totalConsumptionSum / totalCount;

		NetCost netCost;
		for each (auto item in mapProducedProducts)
		{
			netCost.Clear();
			if (!netCost.GetNetCostByProductID(globalVar, ormasDal, item.first, errorMessage))
				return false;
			if (coif.find(item.first) != coif.end())
				netCost.SetValue(std::round(totalNetCost * coif.find(item.first)->second * 100) / 100);
			if (!netCost.UpdateNetCost(globalVar, ormasDal, errorMessage))
				return false;
		}

		return true;
	}

	bool OrmasBL::CorrectingNetCostInStock()
	{
		std::string errorMessage = "";
		std::vector<StockView> stockVector = this->GetAllDataForClass<StockView>(errorMessage);
		if (stockVector.size() > 0)
		{
			Account account;
			if (!account.GetAccountByNumber(globalVar, ormasDal, "10740", errorMessage))
				return false;
			Product product;
			Warehouse warehouse;
			ProductType pType;
			NetCost nCost;
			Subaccount subaccount;
			int companyID = 0;
			double difference = 0;
			for each (auto stockItem in stockVector)
			{
				product.Clear();
				pType.Clear();
				nCost.Clear();
				warehouse.Clear();
				subaccount.Clear();
				difference = 0;
				if (!stockItem.IsEmpty())
				{
					errorMessage = "";
					if (0 == stockItem.GetCount())
					{
						continue;
					}
					else
					{
						if (!product.GetProductByID(globalVar, ormasDal, stockItem.GetProductID(), errorMessage))
							return false;
						if (!pType.GetProductTypeByCode(globalVar, ormasDal, "PRODUCT", errorMessage))
							return false;
						if (product.GetProductTypeID() == pType.GetID())
						{
							if (!nCost.GetNetCostByProductID(globalVar, ormasDal, stockItem.GetProductID(), errorMessage))
								return false;
							if (!warehouse.GetWarehouseByID(globalVar, ormasDal, stockItem.GetWarehouseID(), errorMessage))
								return false;
							if (!subaccount.GetSubaccountByID(globalVar, ormasDal, warehouse.GetSubaccountID(), errorMessage))
								return false;
							if (subaccount.GetParentAccountID() == account.GetID())
							{

								companyID = product.GetCompanyID();
								difference = stockItem.GetCount()*nCost.GetValue() - stockItem.GetSum();
								if (difference > 0 && difference != 0)
								{
									CompanyAccountRelation caRel;
									int debAccID = warehouse.GetSubaccountID();
									int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
									if (0 == debAccID || 0 == credAccID)
									{
										return false;
									}
									if (!stockItem.CreateCorrectongEntry(globalVar, ormasDal, product.GetID(), debAccID, difference, credAccID, errorMessage))
									{
										return false;
									}
								}
								if (difference < 0 && difference != 0)
								{
									CompanyAccountRelation caRel;
									int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
									int credAccID = warehouse.GetSubaccountID();
									if (0 == debAccID || 0 == credAccID)
									{
										return false;
									}
									if (!stockItem.CreateCorrectongEntry(globalVar, ormasDal, product.GetID(), debAccID, difference * (-1), credAccID, errorMessage))
									{
										return false;
									}
								}
								stockItem.SetSum(stockItem.GetCount()*nCost.GetValue());
								if (!stockItem.UpdateStock(globalVar, ormasDal, errorMessage))
									return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	bool OrmasBL::CorrectingNetCostInTransport()
	{
		std::string errorMessage = "";
		std::vector<TransportListView> transporListVector = this->GetAllDataForClass<TransportListView>(errorMessage);
		if (transporListVector.size() > 0)
		{
			Product product;
			ProductType pType;
			NetCost nCost;
			int companyID = 0;
			double difference = 0;
			for each (auto listItem in transporListVector)
			{
				product.Clear();
				pType.Clear();
				nCost.Clear();
				difference = 0;
				if (!listItem.IsEmpty())
				{
					errorMessage = "";
					if (0 == listItem.GetCount())
					{
						continue;
					}
					else
					{
						if (!product.GetProductByID(globalVar, ormasDal, listItem.GetProductID(), errorMessage))
							return false;
						if (!pType.GetProductTypeByCode(globalVar, ormasDal, "PRODUCT", errorMessage))
							return false;
						if (product.GetProductTypeID() == pType.GetID())
						{
							if (!nCost.GetNetCostByProductID(globalVar, ormasDal, listItem.GetProductID(), errorMessage))
								return false;
							companyID = product.GetCompanyID();
							difference = listItem.GetCount()*nCost.GetValue() - listItem.GetSum();
							if (difference > 0 && difference != 0)
							{
								CompanyAccountRelation caRel;
								int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10742", errorMessage);
								int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
								if (0 == debAccID || 0 == credAccID)
								{
									return false;
								}
								if (!listItem.CreateEntry(globalVar, ormasDal, debAccID, difference, credAccID, errorMessage))
								{
									return false;
								}
							}
							if (difference < 0 && difference != 0)
							{
								CompanyAccountRelation caRel;
								int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
								int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10742", errorMessage);
								if (0 == debAccID || 0 == credAccID)
								{
									return false;
								}
								if (!listItem.CreateEntry(globalVar, ormasDal, debAccID, difference * (-1), credAccID, errorMessage))
								{
									return false;
								}
							}
							listItem.SetSum(listItem.GetCount()*nCost.GetValue());
							if (!listItem.UpdateTransportList(globalVar, ormasDal, errorMessage))
								return false;
						}

					}
				}
			}
		}
		return true;
	}

	bool OrmasBL::GenerateReports(std::string fromDate, std::string tillDate)
	{
		std::string errorMessage = "";
		FinancialReport fReport;
		Company company;
		Account account44010;
		Account account55010;
		Account account55200;
		Account account55300;
		Account account55270;
		Account account55321;
		Account account44020;
		Account account44090;
		double account66010 = 0;
		double account66020 = 0;
		double account66040 = 0;
		double account66050 = 0;
		double account66060 = 0;
		double account66070 = 0;
		double account66110 = 0;
		double account66120 = 0;
		double account66140 = 0;
		double account66150 = 0;
		double account66160 = 0;
		double account66170 = 0;
		double account66130 = 0;
		int companyID = company.GetCompanyID(globalVar, ormasDal, errorMessage);
		account44010.Clear();
		if (!account44010.GetAccountByNumber(globalVar, ormasDal, "44010", errorMessage))
			return false;
		account55010.Clear();
		if (!account55010.GetAccountByNumber(globalVar, ormasDal, "55010", errorMessage))
			return false;
		account55200.Clear();
		if (!account55200.GetAccountByNumber(globalVar, ormasDal, "55200", errorMessage))
			return false;
		account55300.Clear();
		if (!account55300.GetAccountByNumber(globalVar, ormasDal, "55300", errorMessage))
			return false;
		account55270.Clear();
		if (!account55270.GetAccountByNumber(globalVar, ormasDal, "55270", errorMessage))
			return false;
		account55321.Clear();
		if (!account55321.GetAccountByNumber(globalVar, ormasDal, "55321", errorMessage))
			return false;
		account44020.Clear();
		if (!account44020.GetAccountByNumber(globalVar, ormasDal, "44020", errorMessage))
			return false;
		account44090.Clear();
		if (!account44090.GetAccountByNumber(globalVar, ormasDal, "44090", errorMessage))
			return false;

		std::vector<Account> vecForAccount;
		std::vector<DataLayer::accountsCollection> accCollection;
		accCollection = ormasDal.GetAccounts(errorMessage);
		if (!accCollection.empty()){
			for (auto data : accCollection)
			{
				vecForAccount.push_back(Account(data));
			}
		}
		for each (auto item in vecForAccount)
		{
			if (0 == item.GetNumber().substr(0, 1).compare("6"))
			{
				if (0 == item.GetNumber().compare("66010"))
					account66010 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66020"))
					account66020 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66040"))
					account66040 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66050"))
					account66050 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66060"))
					account66060 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66070"))
					account66070 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66110"))
					account66110 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66120"))
					account66120 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66140"))
					account66140 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66150"))
					account66150 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66160"))
					account66160 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66170"))
					account66170 = item.GetCurrentBalance();
				if (0 == item.GetNumber().compare("66130"))
					account66130 = item.GetCurrentBalance();
			}
		}

		fReport.SetAccount44010(std::round(account44010.GetCurrentBalance() * 1000) / 1000);
		fReport.SetAccount55010(std::round(account55010.GetCurrentBalance() * 1000) / 1000);
		fReport.SetAccount552(std::round(account55200.GetCurrentBalance() * 1000) / 1000);
		fReport.SetAccount55270(std::round(account55270.GetCurrentBalance() * 1000) / 1000);
		fReport.SetAccount553(std::round(account55300.GetCurrentBalance() * 1000) / 1000);
		fReport.SetAccount55321(std::round(account55321.GetCurrentBalance() * 1000) / 1000);
		fReport.SetAccount44020_90(std::round((account44020.GetCurrentBalance() + account44090.GetCurrentBalance()) * 1000) / 1000);
		fReport.SetAccount66010_66110(std::round((account66010 + account66110) * 1000) / 1000);
		fReport.SetAccount66020_66120(std::round((account66020 + account66120) * 1000) / 1000);
		fReport.SetAccount66040_66140(std::round((account66040 + account66140) * 1000) / 1000);
		fReport.SetAccount66050_66150(std::round((account66050 + account66150) * 1000) / 1000);
		fReport.SetAccount66060_66160(std::round((account66060 + account66160) * 1000) / 1000);
		fReport.SetAccount66130(std::round((account66130) * 1000) / 1000);
		fReport.SetAccount66070_66170(std::round((account66070 + account66170) * 1000) / 1000);
		fReport.SetFromDate(fromDate);
		fReport.SetTillDate(tillDate);
		if (!fReport.CreateFinancialReport(globalVar, ormasDal, errorMessage))
			return false;
		return true;
	}

	bool OrmasBL::CalculateCloseOfMonth(std::string fromDate, std::string tillDate)
	{
		//save state of accounts
		std::string errorMessage = "";
		std::vector<Account> vecForAccount;
		std::vector<DataLayer::accountsCollection> accCollection;
		accCollection = ormasDal.GetAccounts(errorMessage);
		Entry entry;
		CompanyAccountRelation cAccRel;
		Company company;
		int companyID = company.GetCompanyID(globalVar, ormasDal, errorMessage);
		int acc70000 = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "70000", errorMessage);
		if (!accCollection.empty()){
			for (auto data : accCollection)
			{
				vecForAccount.push_back(Account(data));
			}
		}
		for each (auto item in vecForAccount)
		{
			if (0 == item.GetNumber().substr(0, 1).compare("4") || 0 == item.GetNumber().substr(0, 1).compare("5")
				|| 0 == item.GetNumber().substr(0, 1).compare("6"))
			{
				if (0 == acc70000)
					return false;
				if (0 == item.GetNumber().compare("44000") || 0 == item.GetNumber().compare("55000") || 0 == item.GetNumber().compare("55200")
					|| 0 == item.GetNumber().compare("55300") || 0 == item.GetNumber().compare("66000") || 0 == item.GetNumber().compare("66100"))
				{					
				}
				else
				{
					if (item.GetCurrentBalance() > 0)
					{
						entry.Clear();
						entry.SetID(ormasDal.GenerateID());
						entry.SetDebitingAccountID(acc70000);
						entry.SetValue(item.GetCurrentBalance());
						entry.SetCreditingAccountID(item.GetID());
						entry.SetDate(ormasDal.GetSystemDateTime());
						entry.SetDescription(wstring_to_utf8(L"Закрытие счетов на конец месяца"));
						if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
							return false;
					}
					else if (item.GetCurrentBalance() < 0)
					{
						entry.Clear();
						entry.SetID(ormasDal.GenerateID());
						entry.SetDebitingAccountID(item.GetID());
						entry.SetValue(item.GetCurrentBalance() * (-1));
						entry.SetCreditingAccountID(acc70000);
						entry.SetDate(ormasDal.GetSystemDateTime());
						entry.SetDescription(wstring_to_utf8(L"Закрытие счетов на конец месяца"));
						if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
							return false;
					}
				}
			}
			else
			{
				if (0 == item.GetNumber().substr(0, 1).compare("7"))
				{
				}
				else
				{
					item.SetStartBalance(item.GetCurrentBalance());
					if (!item.UpdateAccount(globalVar, ormasDal, errorMessage))
						return false;
				}
			}
		}

		std::vector<SubaccountView> vecForSubaccountHis;
		std::vector<DataLayer::subaccountsViewCollection> subaccCollection;
		subaccCollection = ormasDal.GetSubaccounts(errorMessage);
		if (!subaccCollection.empty()){
			for (auto data : subaccCollection)
			{
				vecForSubaccountHis.push_back(SubaccountView(data));
			}
		}
		for each (auto item in vecForSubaccountHis)
		{
			item.SetStartBalance(item.GetCurrentBalance());
			if (!item.UpdateSubaccount(globalVar, ormasDal, errorMessage))
				return false;
		}
		return true;
	}

	bool OrmasBL::CloseOfAccount70000()
	{
		std::string errorMessage = "";
		Account account70000;
		if (!account70000.GetAccountByNumber(globalVar, ormasDal, "70000", errorMessage))
			return false;
		Account account33210;
		if (!account33210.GetAccountByNumber(globalVar, ormasDal, "33210", errorMessage))
			return false;
		
		account33210.SetStartBalance(account33210.GetCurrentBalance());
		if (!account33210.UpdateAccount(globalVar, ormasDal, errorMessage))
			return false;
		
		double correctingValue = 0;
		correctingValue = account70000.GetCurrentBalance()*(-1);

		Entry entry;
		CompanyAccountRelation cAccRel;
		Company company;
		int companyID = company.GetCompanyID(globalVar, ormasDal, errorMessage);
		
		if (correctingValue > 0)
		{
			entry.Clear();
			entry.SetID(ormasDal.GenerateID());
			entry.SetDebitingAccountID(account70000.GetID());
			entry.SetValue(correctingValue);
			entry.SetCreditingAccountID(account33210.GetID());
			entry.SetDate(ormasDal.GetSystemDateTime());
			entry.SetDescription(wstring_to_utf8(L"Операция закрытие счета 70000"));
			if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
				return false;
		}
		else if (correctingValue < 0)
		{
			entry.Clear();
			entry.SetID(ormasDal.GenerateID());
			entry.SetDebitingAccountID(account33210.GetID());
			entry.SetValue(correctingValue * (-1));
			entry.SetCreditingAccountID(account70000.GetID());
			entry.SetDate(ormasDal.GetSystemDateTime());
			entry.SetDescription(wstring_to_utf8(L"Операция закрытие счета 70000"));
			if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
				return false;
		}
		return true;
	}

	bool OrmasBL::CorrectDates(std::string tillDate)
	{
		//save state of accounts
		if (ormasDal.CloseOfMonthDateCorrection(tillDate))
			return true;
		return false;
	}

	std::string OrmasBL::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}