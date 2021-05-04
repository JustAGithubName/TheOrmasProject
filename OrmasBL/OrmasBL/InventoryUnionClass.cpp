#include "stdafx.h"
#include "InventoryUnionClass.h"
#include "BalanceClass.h"
#include "UserClass.h"
#include "EntryClass.h"
#include "SubaccountClass.h"
#include "AccountClass.h"
#include "EntryOperationRelationClass.h"
#include "StatusClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyEmployeeRelationClass.h"
#include "CompanyClass.h"
#include "DivisionClass.h"
#include <codecvt>


namespace BusinessLayer
{
	InventoryUnion::InventoryUnion(DataLayer::inventoryUnionViewCollection fCollection)
	{
		inventory->SetID(std::get<0>(fCollection));
		inventory->SetName(std::get<1>(fCollection));
		inventory->SetCost(std::get<2>(fCollection));
		inventory->SetInventoryNumber(std::get<3>(fCollection));
		inventory->SetBarcodeNumber(std::get<4>(fCollection));
		inventory->SetLocation(std::get<5>(fCollection));
		inventory->SetStartOfOperationDate(std::get<8>(fCollection));
		inventory->SetEndOfOperationDate(std::get<9>(fCollection));
		inventory->SetStatusID(std::get<10>(fCollection));
		inventory->SetDepartmentID(std::get<11>(fCollection));
		
		postingFixedAssets->SetID(std::get<12>(fCollection));
		postingFixedAssets->SetUserID(std::get<13>(fCollection));
		postingFixedAssets->SetSubaccountID(std::get<14>(fCollection));
		postingFixedAssets->SetAccountID(std::get<15>(fCollection));
	}

	Inventory* InventoryUnion::GetInventory()
	{
		return inventory;
	}

	PostingFixedAssets* InventoryUnion::GetPostingFixedAssets()
	{
		return postingFixedAssets;
	}

	void InventoryUnion::SetInventory(Inventory* fs)
	{
		inventory = fs;
	}

	void InventoryUnion::SetPostingFixedAssets(PostingFixedAssets* pfa)
	{
		postingFixedAssets = pfa;
	}

	bool InventoryUnion::CreateInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, Inventory* fInven, PostingFixedAssets* pfAssets, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		inventory = fInven;
		postingFixedAssets = pfAssets;
		//ormasDal.StartTransaction(errorMessage);
		inventory->inventoryAccountID = inventoryAccountID;
		int subAccID = 0;
		if (isNewInventory)
		{
			subAccID = inventory->GenerateSubaccount(globalVar, ormasDal, 0, errorMessage);
		}
		else
		{
			subAccID = inventory->GenerateSubaccount(globalVar, ormasDal, subaccValue, errorMessage);
		}
		inventory->SetSubaccountID(subAccID);
		if (inventory->CreateInventory(globalVar, ormasDal, errorMessage))
		{
			if (0 != purveyorID || 0 != accountableID || 0 != accountID)
			{
				postingFixedAssets->SetAccountID(accountID);
				if (accountableID > 0)
				{
					Balance balance;
					Balance tempBalance;
					Subaccount sub;
					Account acc;
					if (!acc.GetAccountByNumber(globalVar, ormasDal, "10520", errorMessage))
					{
						return false;
					}
					PostingFixedAssets pFixedAssets;
					pFixedAssets.SetUserID(accountableID);
					std::string filter = pFixedAssets.GenerateFilter(ormasDal);
					std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
					if (0 < balanceVector.size())
					{
						for each (auto item in balanceVector)
						{
							sub.Clear();
							tempBalance.Clear();
							if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
								return false;
							if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
							{
								if (sub.GetParentAccountID() == acc.GetID())
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
						postingFixedAssets->SetSubaccountID(balance.GetSubaccountID());
					}
				}
				if (purveyorID > 0)
				{
					postingFixedAssets->SetUserID(purveyorID);
				}
				postingFixedAssets->SetInventoryID(inventory->GetID());
				if (!postingFixedAssets->CreatePostingFixedAssets(globalVar, ormasDal, errorMessage))
				{
							return false;
				}
			}
			if (isNewInventory == false)
				return true;
			if (inventory->GetStatusID() == statusMap.find("IN USE")->second)
			{
				if (inventory->CreateInventoryEntry(globalVar, ormasDal, accountableID, purveyorID, accountID, inventory->GetSubaccountID(), inventory->GetCost(), inventory->GetStartOfOperationDate(), errorMessage))
				{
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (inventory->GetStatusID() == statusMap.find("WRITE-OFFED")->second || inventory->GetStatusID() == statusMap.find("ERROR")->second)
			{
				errorMessage = "Cannot change status of this to \"WRITE-OFFED\" or \"ERROR\".";
				return false;
			}
			else
			{
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool InventoryUnion::CreateInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		inventory->inventoryAccountID = inventoryAccountID;
		int subAccID = 0;
		if (isNewInventory)
		{
			subAccID = inventory->GenerateSubaccount(globalVar, ormasDal, 0, errorMessage);
		}
		else
		{
			subAccID = inventory->GenerateSubaccount(globalVar, ormasDal, subaccValue, errorMessage);
		}
		inventory->SetSubaccountID(subAccID);
		if (inventory->CreateInventory(globalVar, ormasDal, errorMessage))
		{
			if (0 != purveyorID || 0 != accountableID || 0 != accountID)
			{
				postingFixedAssets->SetAccountID(accountID);
				if (accountableID > 0)
				{
					Balance balance;
					Balance tempBalance;
					Subaccount sub;
					Account acc;
					if (!acc.GetAccountByNumber(globalVar, ormasDal, "10520", errorMessage))
					{
						return false;
					}
					PostingFixedAssets pFixedAssets;
					pFixedAssets.SetUserID(accountableID);
					std::string filter = pFixedAssets.GenerateFilter(ormasDal);
					std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
					if (0 < balanceVector.size())
					{
						for each (auto item in balanceVector)
						{
							sub.Clear();
							tempBalance.Clear();
							if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
								return false;
							if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
							{
								if (sub.GetParentAccountID() == acc.GetID())
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
						postingFixedAssets->SetSubaccountID(balance.GetSubaccountID());
					}
				}
				if (purveyorID > 0)
				{
					postingFixedAssets->SetUserID(purveyorID);
				}
				postingFixedAssets->SetInventoryID(inventory->GetID());
				if (!postingFixedAssets->CreatePostingFixedAssets(globalVar, ormasDal, errorMessage))
				{
					return false;
				}
			}
			if (isNewInventory == false)
				return true;
			if (inventory->GetStatusID() == statusMap.find("IN USE")->second)
			{
				if (inventory->CreateInventoryEntry(globalVar, ormasDal, accountableID, purveyorID, accountID, inventory->GetSubaccountID(), inventory->GetCost(), inventory->GetStartOfOperationDate(), errorMessage))
				{
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (inventory->GetStatusID() == statusMap.find("WRITE-OFFED")->second || inventory->GetStatusID() == statusMap.find("ERROR")->second)
			{
				errorMessage = "Cannot change status of this to \"WRITE-OFFED\" or \"ERROR\".";
				return false;
			}
			else
			{
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool InventoryUnion::DeleteInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (inventory->GetStatusID() == statusMap.find("WRITE-OFF")->second || inventory->GetStatusID() == statusMap.find("ERROR")->second)
		{
			if (!inventory->DeleteInventory(globalVar, ormasDal, errorMessage))
				return false;
			if (!postingFixedAssets->DeletePostingFixedAssets(globalVar, ormasDal, errorMessage))
				return false;
			return true;
		}
		return false;
	}
	bool InventoryUnion::UpdateInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, Inventory* inv, PostingFixedAssets* pfAssets, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		inventory = inv;
		postingFixedAssets = pfAssets;

		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, inventory->GetID(), errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		if (previousStatusID == statusMap.find("IN USE")->second && inventory->GetStatusID() == statusMap.find("IN USE")->second)
		{
			return true;
		}
		if (previousStatusID != statusMap.find("IN USE")->second && inventory->GetStatusID() == statusMap.find("WRITE-OFFED")->second)
		{
			errorMessage = "Cannot update the document, because \"WRITE-OFFED\" status is unchangeable state";
			return false;
		}
		if (previousStatusID == statusMap.find("IN USE")->second)
		{
			if (inventory->GetStatusID() != statusMap.find("WRITE-OFFED")->second && inventory->GetStatusID() != statusMap.find("ERROR")->second)
			{
				errorMessage = "Cannot update the document, because \"IN USE\" status could be changed to \"WRITE-OFFED\" or \"ERROR\"";
				return false;
			}
		}
		if (inventory->UpdateInventory(globalVar, ormasDal, errorMessage))
		{
			if (0 != purveyorID || 0 != accountableID || 0 != accountID)
			{
				postingFixedAssets->SetAccountID(accountID);
				if (accountableID > 0)
				{
					Balance balance;
					Balance tempBalance;
					Subaccount sub;
					Account acc;
					if (!acc.GetAccountByNumber(globalVar, ormasDal, "10520", errorMessage))
					{
						return false;
					}
					PostingFixedAssets pFixedAssets;
					pFixedAssets.SetUserID(accountableID);
					std::string filter = pFixedAssets.GenerateFilter(ormasDal);
					std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
					if (0 < balanceVector.size())
					{
						for each (auto item in balanceVector)
						{
							sub.Clear();
							tempBalance.Clear();
							if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
								return false;
							if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
							{
								if (sub.GetParentAccountID() == acc.GetID())
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
						postingFixedAssets->SetSubaccountID(balance.GetSubaccountID());
					}
				}
				if (purveyorID > 0)
				{
					postingFixedAssets->SetUserID(purveyorID);
				}
				postingFixedAssets->SetInventoryID(inventory->GetID());
				if (!postingFixedAssets->UpdatePostingFixedAssets(globalVar, ormasDal, errorMessage))
				{
					return false;
				}
			}
			if (inventory->GetStatusID() == statusMap.find("IN USE")->second && isNewInventory == true)
			{
				if (inventory->CreateInventoryEntry(globalVar, ormasDal, accountableID, purveyorID, accountID, inventory->GetSubaccountID(), inventory->GetCost(), inventory->GetStartOfOperationDate(), errorMessage))
				{
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (previousStatusID == statusMap.find("IN USE")->second && inventory->GetStatusID() == statusMap.find("ERROR")->second)
			{
				Subaccount sub;
				if (!sub.GetSubaccountByID(globalVar, ormasDal, inventory->GetSubaccountID(), errorMessage))
					return false;
				if (sub.GetCurrentBalance() <= 0 && sub.GetCurrentBalance()< inventory->GetCost())
				{
					errorMessage = "Cannot set status to \"ERROR\", inventory account value must be equal to cost or more";
					return false;
				}
				if (inventory->CreateInventoryEntryReverce(globalVar, ormasDal, accountableID, purveyorID, accountID, inventory->GetSubaccountID(), inventory->GetCost(), inventory->GetStartOfOperationDate(), errorMessage))
				{
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (previousStatusID == statusMap.find("IN USE")->second && inventory->GetStatusID() == statusMap.find("WRITE-OFFED")->second)
			{
				if (inventory->CreateInventoryEntryWriteOFF(globalVar, ormasDal, inventory->GetID(), errorMessage))
				{
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			else
			{
				errorMessage = "Cannot change status to \"WRITE-OFFED\", fixed assets must be in \"IN USE\" state";
				return false;
			}
			return true;
		}
		else
		{
			return false;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool InventoryUnion::UpdateInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);

		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, inventory->GetID(), errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		if (previousStatusID == statusMap.find("IN USE")->second && inventory->GetStatusID() == statusMap.find("IN USE")->second)
		{
			return true;
		}
		if (previousStatusID != statusMap.find("IN USE")->second && inventory->GetStatusID() == statusMap.find("WRITE-OFFED")->second)
		{
			errorMessage = "Cannot update the document, because \"WRITE-OFFED\" status is unchangeable state";
			return false;
		}
		if (previousStatusID == statusMap.find("IN USE")->second)
		{
			if (inventory->GetStatusID() != statusMap.find("WRITE-OFFED")->second && inventory->GetStatusID() != statusMap.find("ERROR")->second)
			{
				errorMessage = "Cannot update the document, because \"IN USE\" status could be changed to \"WRITE-OFFED\" or \"ERROR\"";
				return false;
			}
		}
		if (inventory->UpdateInventory(globalVar, ormasDal, errorMessage))
		{
			if (0 != purveyorID || 0 != accountableID || 0 != accountID)
			{
				postingFixedAssets->SetAccountID(accountID);
				if (accountableID > 0)
				{
					Balance balance;
					Balance tempBalance;
					Subaccount sub;
					Account acc;
					if (!acc.GetAccountByNumber(globalVar, ormasDal, "10520", errorMessage))
					{
						return false;
					}
					PostingFixedAssets pFixedAssets;
					pFixedAssets.SetUserID(accountableID);
					std::string filter = pFixedAssets.GenerateFilter(ormasDal);
					std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
					if (0 < balanceVector.size())
					{
						for each (auto item in balanceVector)
						{
							sub.Clear();
							tempBalance.Clear();
							if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
								return false;
							if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
							{
								if (sub.GetParentAccountID() == acc.GetID())
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
						postingFixedAssets->SetSubaccountID(balance.GetSubaccountID());
					}
				}
				if (purveyorID > 0)
				{
					postingFixedAssets->SetUserID(purveyorID);
				}
				postingFixedAssets->SetInventoryID(inventory->GetID());
				if (!postingFixedAssets->UpdatePostingFixedAssets(globalVar, ormasDal, errorMessage))
				{
					return false;
				}
			}
			if (inventory->GetStatusID() == statusMap.find("IN USE")->second && isNewInventory == true)
			{
				if (inventory->CreateInventoryEntry(globalVar, ormasDal, accountableID, purveyorID, accountID, inventory->GetSubaccountID(), inventory->GetCost(), inventory->GetStartOfOperationDate(), errorMessage))
				{
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (previousStatusID == statusMap.find("IN USE")->second && inventory->GetStatusID() == statusMap.find("ERROR")->second)
			{
				Subaccount sub;
				if (!sub.GetSubaccountByID(globalVar, ormasDal, inventory->GetSubaccountID(), errorMessage))
					return false;
				if (sub.GetCurrentBalance() <= 0 && sub.GetCurrentBalance()< inventory->GetCost())
				{
					errorMessage = "Cannot set status to \"ERROR\", inventory account value must be equal to cost or more";
					return false;
				}
				if (inventory->CreateInventoryEntryReverce(globalVar, ormasDal, accountableID, purveyorID, accountID, inventory->GetSubaccountID(), inventory->GetCost(), inventory->GetStartOfOperationDate(), errorMessage))
				{
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (previousStatusID == statusMap.find("IN USE")->second && inventory->GetStatusID() == statusMap.find("WRITE-OFFED")->second)
			{
				if (inventory->CreateInventoryEntryWriteOFF(globalVar, ormasDal, inventory->GetID(), errorMessage))
				{
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			else
			{
				errorMessage = "Cannot change status to \"WRITE-OFFED\", fixed assets must be in \"IN USE\" state";
				return false;
			}
			return true;
		}
		else
		{
			return false;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool InventoryUnion::IsEmpty()
	{
		if (inventory->IsEmpty() && postingFixedAssets->IsEmpty())
			return true;
		return false;
	}

	void InventoryUnion::Clear()
	{
		inventory->Clear();
		postingFixedAssets->Clear();
	}

	std::string InventoryUnion::GenerateInventoryNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int divID)
	{
		std::string errorMessage = "";
		std::string invNumber = "";
		invNumber += "I";
		Division div;
		if (!div.GetDivisionByID(globalVar, ormasDal, divID, errorMessage))
			return "";
		if (0 == div.GetCode().compare("PRODUCTION"))
		{
			invNumber += "P";
		}
		if (0 == div.GetCode().compare("RELEASE"))
		{
			invNumber += "R";
		}
		if (0 == div.GetCode().compare("ADMINISTRATION"))
		{
			invNumber += "A";
		}
		std::string rawNumber = GenerateInvRawNumber(globalVar, ormasDal, errorMessage);
		invNumber += rawNumber;
		if (invNumber.size() < 9)
			return "";
		return invNumber;
	}

	std::string InventoryUnion::GenerateInvRawNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		int countOfNulls;
		int genNumber = ormasDal.GenerateInventoryNumber();
		std::string invNumber = "";
		std::string genNumberStr = std::to_string(genNumber);
		if (genNumberStr.length() < 9)
		{
			countOfNulls = 9 - genNumberStr.length();
			for (int i = 0; i < countOfNulls; i++)
			{
				invNumber.append("0");
			}
			invNumber.append(genNumberStr);
			return invNumber;
		}
		return "";
	}

	int InventoryUnion::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fxID, std::string& errorMessage)
	{
		Inventory Inventory;
		if (Inventory.GetInventoryByID(globalVar, ormasDal, fxID, errorMessage))
			return Inventory.GetStatusID();
		return 0;
	}
}
