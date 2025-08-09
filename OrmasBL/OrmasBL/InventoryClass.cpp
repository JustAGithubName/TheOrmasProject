#include "stdafx.h"
#include "InventoryClass.h"
#include "InventoryHistoryClass.h"
#include "DivisionClass.h"
#include "BalanceClass.h"
#include "UserClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "SubaccountClass.h"
#include "AccountClass.h"
#include "StatusClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyEmployeeRelationClass.h"
#include "CompanyClass.h"
#include "CurrencyClass.h"
#include "DivisionAccountRelationClass.h"
#include <codecvt>

namespace BusinessLayer
{
	Inventory::Inventory(DataLayer::inventoryCollection iCollection)
	{
		id = std::get<0>(iCollection);
		name = std::get<1>(iCollection);
		cost = std::get<2>(iCollection);
		departmentID = std::get<3>(iCollection);
		location = std::get<4>(iCollection);
		statusID = std::get<5>(iCollection);
		startOfOperationDate = std::get<6>(iCollection);
		endOfOperationDate = std::get<7>(iCollection);
		inventoryNumber = std::get<8>(iCollection);
		barcodeNumber = std::get<9>(iCollection);
		subaccountID = std::get<10>(iCollection);
	}

	int Inventory::GetID()
	{
		return id;
	}

	std::string Inventory::GetName()
	{
		return name;
	}

	double Inventory::GetCost()
	{
		return cost;
	}

	int Inventory::GetDepartmentID()
	{
		return departmentID;
	}

	std::string Inventory::GetLocation()
	{
		return location;
	}

	int Inventory::GetStatusID()
	{
		return statusID;
	}

	std::string Inventory::GetStartOfOperationDate()
	{
		return startOfOperationDate;
	}
	
	std::string Inventory::GetEndOfOperationDate()
	{
		return endOfOperationDate;
	}

	std::string Inventory::GetInventoryNumber()
	{
		return inventoryNumber;
	}
	
	std::string Inventory::GetBarcodeNumber()
	{
		return barcodeNumber;
	}

	int Inventory::GetSubaccountID()
	{
		return subaccountID;
	}

	void Inventory::SetID(int iID)
	{
		id = iID;
	}

	void Inventory::SetName(std::string iName)
	{
		name = iName;
	}

	void Inventory::SetCost(double iCost)
	{
		cost = iCost;
	}

	void Inventory::SetDepartmentID(int iDepID)
	{
		departmentID = iDepID;
	}

	void Inventory::SetLocation(std::string iLocation)
	{
		location = iLocation;
	}

	void Inventory::SetStatusID(int statID)
	{
		statusID = statID;
	}

	void Inventory::SetStartOfOperationDate(std::string sooDate)
	{
		startOfOperationDate = sooDate;
	}

	void Inventory::SetEndOfOperationDate(std::string eooDate)
	{
		endOfOperationDate = eooDate;
	}

	void Inventory::SetInventoryNumber(std::string iNumber)
	{
		inventoryNumber = iNumber;
	}

	void Inventory::SetBarcodeNumber(std::string bNumber)
	{
		barcodeNumber = bNumber;
	}

	void Inventory::SetSubaccountID(int subID)
	{
		subaccountID = subID;
	}

	bool Inventory::CreateInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string iName, double iCost, int depID, std::string iLocation, 
		int sID, std::string sooDate, std::string eooDate, std::string iNumber, std::string bNumber, int subID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, iName, iNumber, bNumber, iCost, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		name = iName;
		cost = iCost;
		departmentID = depID;
		location = iLocation;
		statusID = sID;
		startOfOperationDate = sooDate;
		endOfOperationDate = eooDate;
		inventoryNumber = iNumber;
		barcodeNumber = bNumber;
		subaccountID = subID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateInventory(id, name, cost, departmentID, location, statusID, startOfOperationDate,
			endOfOperationDate, inventoryNumber, barcodeNumber, subaccountID, errorMessage))
		{
			Status sts;
			if (!sts.GetStatusByID(globalVar, ormasDal, statusID, errorMessage))
				return false;
			InventoryHistory iHis;
			if (!iHis.CreateInventoryHistory(globalVar, ormasDal, id, sts.GetName(), ormasDal.GetSystemDate(), errorMessage))
				return false;
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool Inventory::CreateInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateInventory(id, name, cost, departmentID, location, statusID, startOfOperationDate,
			endOfOperationDate, inventoryNumber, barcodeNumber, subaccountID, errorMessage))
		{
			Status sts;
			if (!sts.GetStatusByID(globalVar, ormasDal, statusID, errorMessage))
				return false;
			InventoryHistory iHis;
			if (!iHis.CreateInventoryHistory(globalVar, ormasDal, id, sts.GetName(), ormasDal.GetSystemDate(), errorMessage))
				return false;
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Inventory::DeleteInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeleteFixedAssetsOperation(id, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Inventory::UpdateInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string iName, double iCost, int depID, std::string iLocation, 
		int sID, std::string sooDate, std::string eooDate, std::string iNumber, std::string bNumber, int subID, std::string& errorMessage)
	{
		name = iName;
		cost = iCost;
		departmentID = depID;
		location = iLocation;
		statusID = sID;
		startOfOperationDate = sooDate;
		endOfOperationDate = eooDate;
		inventoryNumber = iNumber;
		barcodeNumber = bNumber;
		subaccountID = subID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateInventory(id, name, cost, departmentID, location, statusID, startOfOperationDate,
			endOfOperationDate, inventoryNumber, barcodeNumber, subaccountID, errorMessage))
		{
			Status sts;
			if (!sts.GetStatusByID(globalVar, ormasDal, statusID, errorMessage))
				return false;
			InventoryHistory iHis;
			if (!iHis.CreateInventoryHistory(globalVar, ormasDal, id, sts.GetName(), ormasDal.GetSystemDate(), errorMessage))
				return false;
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Inventory::UpdateInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;		
		if (0 != id && ormasDal.UpdateInventory(id, name, cost, departmentID, location, statusID, startOfOperationDate,
			endOfOperationDate, inventoryNumber, barcodeNumber, subaccountID, errorMessage))
		{
			Status sts;
			if (!sts.GetStatusByID(globalVar, ormasDal, statusID, errorMessage))
				return false;
			InventoryHistory iHis;
			if (!iHis.CreateInventoryHistory(globalVar, ormasDal, id, sts.GetName(), ormasDal.GetSystemDate(), errorMessage))
				return false;
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string Inventory::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || 0 != cost || 0 != departmentID || !location.empty() || 0 != statusID || !startOfOperationDate.empty()
			|| !endOfOperationDate.empty() || !inventoryNumber.empty() || !barcodeNumber.empty() || 0 != subaccountID)
		{
			return ormasDal.GetFilterForInventory(id, name, cost, departmentID, location, statusID, startOfOperationDate,
				endOfOperationDate, inventoryNumber, barcodeNumber, subaccountID);
		}
		return "";
	}

	bool Inventory::GetInventoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage)
	{
		if (iID <= 0)
			return false;
		id = iID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::inventoryViewCollection> inventoryVector = ormasDal.GetInventory(errorMessage, filter);
		if (0 != inventoryVector.size())
		{
			id = std::get<0>(inventoryVector.at(0));
			name = std::get<1>(inventoryVector.at(0));
			cost = std::get<2>(inventoryVector.at(0));
			departmentID = std::get<11>(inventoryVector.at(0));
			location = std::get<7>(inventoryVector.at(0));
			statusID = std::get<10>(inventoryVector.at(0));
			startOfOperationDate = std::get<8>(inventoryVector.at(0));
			endOfOperationDate = std::get<9>(inventoryVector.at(0));
			inventoryNumber = std::get<3>(inventoryVector.at(0));
			barcodeNumber = std::get<4>(inventoryVector.at(0));
			subaccountID = std::get<12>(inventoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find inventry with this id";
		}
		return false;
	}

	bool Inventory::IsEmpty()
	{
		if (0 == id && name == "" && 0.0 == cost && 0 == departmentID && location == "" && 0 == statusID
			&& startOfOperationDate == "" && endOfOperationDate == "" && inventoryNumber == "" && barcodeNumber == ""
			&& 0 == subaccountID)
			return true;
		return false;
	}

	void Inventory::Clear()
	{
		id = 0;
		name = "";
		cost = 0.0;
		departmentID = 0;
		location = "";
		statusID = 0;
		startOfOperationDate = "";
		endOfOperationDate = "";
		inventoryNumber = "";
		barcodeNumber = "";
		subaccountID = 0;
	}

	bool Inventory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string iName, std::string iNumber, std::string bNumber, double iCost, std::string& errorMessage)
	{
		Inventory inventory;
		inventory.Clear();
		errorMessage.clear();
		inventory.SetName(iName);
		inventory.SetInventoryNumber(iNumber);
		inventory.SetBarcodeNumber(bNumber);
		inventory.SetCost(iCost);
		std::string filter = inventory.GenerateFilter(ormasDal);
		std::vector<DataLayer::inventoryViewCollection> inventoryVector = ormasDal.GetInventory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == inventoryVector.size())
		{
			return false;
		}
		errorMessage = "inventory with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Inventory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Inventory inventory;
		inventory.Clear();
		errorMessage.clear();
		inventory.SetName(name);
		inventory.SetInventoryNumber(inventoryNumber);
		inventory.SetBarcodeNumber(barcodeNumber);
		inventory.SetCost(cost);
		std::string filter = inventory.GenerateFilter(ormasDal);
		std::vector<DataLayer::inventoryViewCollection> inventoryVector = ormasDal.GetInventory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == inventoryVector.size())
		{
			return false;
		}
		errorMessage = "inventory with these parameters are already exist! Please avoid the duplication!";
		return true;
	}
	
	bool Inventory::CreateInventoryEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int acctbID, int purID, int accID, int debitingAccID, double value, std::string execDate, std::string& errorMessage)
	{
		if (purID > 0)
		{
			Balance balance;
			if (balance.GetBalanceByUserID(globalVar, ormasDal, purID, errorMessage))
			{
				int debAccID = 0;
				int credAccID = 0;
				debAccID = debitingAccID;
				credAccID = balance.GetSubaccountID();
				if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, execDate, errorMessage))
				{
					return true;
				}
			}
			return false;
		}
		if (acctbID > 0)
		{
			Balance balance;
			Balance tempBalance;
			Subaccount sub;
			Account account;
			if (!account.GetAccountByNumber(globalVar, ormasDal, "10520", errorMessage))
				return false;
			balance.SetUserID(acctbID);
			std::string filter = balance.GenerateFilter(ormasDal);
			std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
			if (0 < balanceVector.size())
			{
				balance.Clear();
				for each (auto item in balanceVector)
				{
					sub.Clear();
					tempBalance.Clear();
					if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
						return false;
					if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
					{
						if (sub.GetParentAccountID() == account.GetID())
						{
							balance.SetSubaccountID(sub.GetID());
						}
					}
				}
			}
			else
			{
				return false;
			}
			if (balance.GetSubaccountID() <= 0)
				return false;
			if (balance.GetBalanceBySubaccountID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			{
				int debAccID = debitingAccID;
				int credAccID = balance.GetSubaccountID();
				if (0 == debAccID || 0 == credAccID)
				{
					return false;
				}
				if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, execDate, errorMessage))
				{
					return true;
				}
			}
		}
		else if (accID > 0)
		{
			int debAccID = debitingAccID;
			int credAccID = accID;
			if (0 == debAccID || 0 == credAccID)
			{
				return false;
			}
			if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, execDate, errorMessage))
			{
				return true;
			}
		}
		return false;
	}

	bool Inventory::CreateInventoryEntryReverce(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int acctbID, int purID, int accID, int debitingAccID, double value, std::string execDate, std::string& errorMessage)
	{
		if (purID > 0)
		{
			Balance balance;
			if (balance.GetBalanceByUserID(globalVar, ormasDal, purID, errorMessage))
			{
				int debAccID = 0;
				int credAccID = 0;
				debAccID = balance.GetSubaccountID();
				credAccID = debitingAccID;
				if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, execDate, errorMessage))
				{
					return true;
				}
			}
			return false;
		}
		if (acctbID > 0)
		{
			Balance balance;
			Balance tempBalance;
			Subaccount sub;
			Account account;
			if (!account.GetAccountByNumber(globalVar, ormasDal, "10520", errorMessage))
				return false;
			balance.SetUserID(acctbID);
			std::string filter = balance.GenerateFilter(ormasDal);
			std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
			if (0 < balanceVector.size())
			{
				balance.Clear();
				for each (auto item in balanceVector)
				{
					sub.Clear();
					tempBalance.Clear();
					if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
						return false;
					if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
					{
						if (sub.GetParentAccountID() == account.GetID())
						{
							balance.SetSubaccountID(sub.GetID());
						}
					}
				}
			}
			else
			{
				return false;
			}
			if (balance.GetSubaccountID() <= 0)
				return false;
			if (balance.GetBalanceBySubaccountID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			{
				int debAccID = balance.GetSubaccountID();
				int credAccID = debitingAccID;
				if (0 == debAccID || 0 == credAccID)
				{
					return false;
				}
				if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, execDate, errorMessage))
				{
					return true;
				}
			}
		}
		else if (accID > 0)
		{
			int debAccID = accID;
			int credAccID = debitingAccID;
			if (0 == debAccID || 0 == credAccID)
			{
				return false;
			}
			if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, execDate, errorMessage))
			{
				return true;
			}
		}
		return false;
	}

	bool Inventory::CreateInventoryEntryWriteOFF(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int inventoryID, std::string& errorMessage)
	{
		Inventory inv;
		DivisionAccountRelation daRel;
		if (!inv.GetInventoryByID(globalVar, ormasDal, inventoryID, errorMessage))
			return false;
		
		Subaccount subAcc;
		if (!subAcc.GetSubaccountByID(globalVar, ormasDal, inv.GetSubaccountID(), errorMessage))
			return false;
		if (!daRel.GetDARelationByDivisionIDAndCode(globalVar, ormasDal, inv.GetDepartmentID(), "FIXED ASSETS WRITE-OFF", errorMessage))
			return false;
		int debAccID = daRel.GetAccountID();
		int credAccID = inv.GetSubaccountID();
		if (0 == debAccID || 0 == credAccID)
		{
			return false;
		}
		if (this->CreateEntryWriteOFF(globalVar, ormasDal, debAccID, subAcc.GetCurrentBalance(), credAccID, ormasDal.GetSystemDate(), errorMessage))
		{
			return true;
		}
		return false;
	}

	bool Inventory::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Покупака инвентаря!"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	bool Inventory::CreateEntryCancel(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена покупки инвентаря"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	bool Inventory::CreateEntryWriteOFF(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Списание инвентаря"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	std::string Inventory::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}

	int Inventory::GenerateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double currentValue, std::string& errorMessage)
	{
		Account account;
		Subaccount subaccount;
		if (!account.GetAccountByNumber(globalVar, ormasDal, "10730", errorMessage))
			return 0;
		Currency currency;
		std::string number = "";
		std::string genAccRawNumber = "";
		int currID = currency.GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (0 != currID)
		{
			Status status;
			if (!status.GetStatusByName(globalVar, ormasDal, "OPEN", errorMessage))
				return false;
			if (!currency.GetCurrencyByID(globalVar, ormasDal, currID, errorMessage))
				return false;
			number = account.GetNumber();
			number.append(std::to_string(currency.GetCode()));
			genAccRawNumber = subaccount.GenerateRawNumber(globalVar, ormasDal, errorMessage);
			if (genAccRawNumber.empty())
				return false;
			number.append(genAccRawNumber);
			subaccount.SetParentAccountID(account.GetID());
			subaccount.SetNumber(number);
			subaccount.SetStartBalance(currentValue);
			subaccount.SetCurrentBalance(currentValue);
			subaccount.SetCurrencyID(currID);
			subaccount.SetStatusID(status.GetID());
			subaccount.SetOpenedDate(ormasDal.GetSystemDate());
			subaccount.SetClosedDate("");
			subaccount.SetDetails("Generated by system");
			if (!subaccount.CreateSubaccount(globalVar, ormasDal, errorMessage))
				return 0;
			return subaccount.GetID();
		}
		return 0;
	}
}
