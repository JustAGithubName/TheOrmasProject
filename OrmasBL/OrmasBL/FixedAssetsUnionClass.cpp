#include "stdafx.h"
#include "FixedAssetsUnionClass.h"
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
	FixedAssetsUnion::FixedAssetsUnion(DataLayer::fixedAssetsUnionCollection fCollection)
	{
		fixedAssets->SetID(std::get<0>(fCollection));
		fixedAssets->SetSpecificationID(std::get<22>(fCollection));
		fixedAssets->SetInventoryNumber(std::get<6>(fCollection));
		fixedAssets->SetPrimaryCost(std::get<3>(fCollection));
		fixedAssets->SetStopCost(std::get<4>(fCollection));
		fixedAssets->SetServiceLife(std::get<8>(fCollection));
		fixedAssets->SetIsAmortize(std::get<9>(fCollection));
		fixedAssets->SetBuyDate(std::get<11>(fCollection));
		fixedAssets->SetStartOfOperationDate(std::get<12>(fCollection));
		fixedAssets->SetEndOfOperationDate(std::get<13>(fCollection));
		fixedAssets->SetStatusID(std::get<23>(fCollection));
		fixedAssets->SetFixedAssetsDetailsID(std::get<24>(fCollection));
		
		fixedAssetsSpecification->SetID(std::get<22>(fCollection));
		fixedAssetsSpecification->SetName(std::get<1>(fCollection));
		fixedAssetsSpecification->SetFactoryNumber(std::get<16>(fCollection));
		fixedAssetsSpecification->SetDeveloper(std::get<17>(fCollection));
		fixedAssetsSpecification->SetDocument(std::get<18>(fCollection));
		fixedAssetsSpecification->SetObjectCharacters(std::get<19>(fCollection));
		fixedAssetsSpecification->SetCondition(std::get<20>(fCollection));
		fixedAssetsSpecification->SetDateOfConstruction(std::get<21>(fCollection));
		
		fixedAssetsDetails->SetID(std::get<24>(fCollection));
		fixedAssetsDetails->SetAmortizeGroupID(std::get<25>(fCollection));
		fixedAssetsDetails->SetAmortizeTypeID(std::get<26>(fCollection));
		fixedAssetsDetails->SetDepartmentID(std::get<27>(fCollection));
		fixedAssetsDetails->SetFixedAssetsLocation(std::get<14>(fCollection));
		fixedAssetsDetails->SetPrimaryCostAccountID(std::get<28>(fCollection));
		fixedAssetsDetails->SetAmortizeAccountID(std::get<29>(fCollection));
		fixedAssetsDetails->SetBarcodeNumber(std::get<15>(fCollection));
		fixedAssetsDetails->SetAmortizeValue(std::get<7>(fCollection));

		postingFixedAssets->SetID(std::get<30>(fCollection));
		postingFixedAssets->SetUserID(std::get<31>(fCollection));
		postingFixedAssets->SetSubaccountID(std::get<32>(fCollection));
		postingFixedAssets->SetAccountID(std::get<33>(fCollection));
	}

	FixedAssets* FixedAssetsUnion::GetFixedAssets()
	{
		return fixedAssets;
	}

	FixedAssetsDetails* FixedAssetsUnion::GetFixedAssetsDetails()
	{
		return fixedAssetsDetails;
	}

	FixedAssetsSpecification* FixedAssetsUnion::GetFixedAssetsSpecification()
	{
		return fixedAssetsSpecification;
	}

	PostingFixedAssets* FixedAssetsUnion::GetPostingFixedAssets()
	{
		return postingFixedAssets;
	}

	void FixedAssetsUnion::SetFixedAssets(FixedAssets* fs)
	{
		fixedAssets = fs;
	}

	void FixedAssetsUnion::SetFixedAssetsDetails(FixedAssetsDetails* faD)
	{
		fixedAssetsDetails = faD;
	}

	void FixedAssetsUnion::SetFixedAssetsSpecification(FixedAssetsSpecification* faS)
	{
		fixedAssetsSpecification = faS;
	}

	void FixedAssetsUnion::SetPostingFixedAssets(PostingFixedAssets* pfa)
	{
		postingFixedAssets = pfa;
	}

	bool FixedAssetsUnion::CreateFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, FixedAssets* fAssets, FixedAssetsDetails* faDetails, FixedAssetsSpecification* faSpecification, PostingFixedAssets* pfAssets, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		fixedAssets = fAssets;
		fixedAssetsDetails = faDetails;
		fixedAssetsSpecification = faSpecification;
		postingFixedAssets = pfAssets;
		//ormasDal.StartTransaction(errorMessage);
		if (fixedAssetsSpecification->CreateFixedAssetsSpecification(globalVar, ormasDal, errorMessage))
		{
			fixedAssetsDetails->fixedAssetsAccountID = fixedAssetsAccountID;
			int primAccID = 0;
			int amoAccID = 0;
			if (isNewFixedAssets)
			{
				primAccID = fixedAssetsDetails->GeneratePrimeSubaccount(globalVar, ormasDal, 0, errorMessage);
				amoAccID = fixedAssetsDetails->GenerateAmortizeSubaccount(globalVar, ormasDal, 0, errorMessage);
			}
			else
			{
				primAccID = fixedAssetsDetails->GeneratePrimeSubaccount(globalVar, ormasDal, primaryValue, errorMessage);
				amoAccID = fixedAssetsDetails->GenerateAmortizeSubaccount(globalVar, ormasDal, amortizeValue, errorMessage);
			}
			fixedAssetsDetails->SetPrimaryCostAccountID(primAccID);
			fixedAssetsDetails->SetAmortizeAccountID(amoAccID);
			if (fixedAssetsDetails->CreateFixedAssetsDetails(globalVar, ormasDal, errorMessage))
			{
				fixedAssets->SetFixedAssetsDetailsID(fixedAssetsDetails->GetID());
				fixedAssets->SetSpecificationID(fixedAssetsSpecification->GetID());
				if (fixedAssets->CreateFixedAssets(globalVar, ormasDal, errorMessage))
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
						postingFixedAssets->SetFixedAssetsID(fixedAssets->GetID());
						if (!postingFixedAssets->CreatePostingFixedAssets(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
					}
					if (isNewFixedAssets == false)
						return true;
					if (fixedAssets->GetStatusID() == statusMap.find("IN USE")->second)
					{
						if (fixedAssets->CreatePostingFixedAssetsEntry(globalVar, ormasDal, accountableID, purveyorID, accountID, fixedAssetsDetails->GetPrimaryCostAccountID(), fixedAssets->GetPrimaryCost(), fixedAssets->GetStartOfOperationDate(), errorMessage))
						{
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					if (fixedAssets->GetStatusID() == statusMap.find("WRITE-OFFED")->second || fixedAssets->GetStatusID() == statusMap.find("ERROR")->second)
					{
						errorMessage = "Cannot change status of this to \"WRITE-OFFED\" or \"ERROR\".";
						return false;
					}
					else
					{
						return true;
					}
				}
			}
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool FixedAssetsUnion::CreateFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		if (fixedAssetsSpecification->CreateFixedAssetsSpecification(globalVar, ormasDal, errorMessage))
		{
			fixedAssetsDetails->fixedAssetsAccountID = fixedAssetsAccountID;
			int primAccID = 0;
			int amoAccID = 0;
			if (isNewFixedAssets)
			{
				primAccID = fixedAssetsDetails->GeneratePrimeSubaccount(globalVar, ormasDal, 0, errorMessage);
				amoAccID = fixedAssetsDetails->GenerateAmortizeSubaccount(globalVar, ormasDal, 0, errorMessage);
			}
			else
			{
				primAccID = fixedAssetsDetails->GeneratePrimeSubaccount(globalVar, ormasDal, primaryValue, errorMessage);
				amoAccID = fixedAssetsDetails->GenerateAmortizeSubaccount(globalVar, ormasDal, amortizeValue, errorMessage);
			}
			fixedAssetsDetails->SetPrimaryCostAccountID(primAccID);
			fixedAssetsDetails->SetAmortizeAccountID(amoAccID);
			if (fixedAssetsDetails->CreateFixedAssetsDetails(globalVar, ormasDal, errorMessage))
			{
				fixedAssets->SetFixedAssetsDetailsID(fixedAssetsDetails->GetID());
				fixedAssets->SetSpecificationID(fixedAssetsSpecification->GetID());
				if (fixedAssets->CreateFixedAssets(globalVar, ormasDal, errorMessage))
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
						postingFixedAssets->SetFixedAssetsID(fixedAssets->GetID());
						if (!postingFixedAssets->CreatePostingFixedAssets(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
					}
					if (isNewFixedAssets == false)
						return true;
					if (fixedAssets->GetStatusID() == statusMap.find("IN USE")->second)
					{
						if (fixedAssets->CreatePostingFixedAssetsEntry(globalVar, ormasDal, accountableID, purveyorID, accountID, fixedAssetsDetails->GetPrimaryCostAccountID(), fixedAssets->GetPrimaryCost(), fixedAssets->GetStartOfOperationDate(), errorMessage))
						{
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					if (fixedAssets->GetStatusID() == statusMap.find("WRITE-OFFED")->second || fixedAssets->GetStatusID() == statusMap.find("ERROR")->second)
					{
						errorMessage = "Cannot change status of this to \"WRITE-OFFED\" or \"ERROR\".";
						return false;
					}
					else
					{
						return true;
					}
				}
			}
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool FixedAssetsUnion::DeleteFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (fixedAssets->GetStatusID() == statusMap.find("WRITE-OFF")->second || fixedAssets->GetStatusID() == statusMap.find("ERROR")->second)
		{
			if (!fixedAssets->DeleteFixedAssets(globalVar, ormasDal, errorMessage))
				return false;
			if (!fixedAssetsDetails->DeleteFixedAssetsDetails(globalVar, ormasDal, errorMessage))
				return false;
			if (!postingFixedAssets->DeletePostingFixedAssets(globalVar, ormasDal, errorMessage))
				return false;
			return true;
		}
		return false;
	}
	bool FixedAssetsUnion::UpdateFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, FixedAssets* fAssets, FixedAssetsDetails* faDetails, FixedAssetsSpecification* faSpecification, PostingFixedAssets* pfAssets, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		fixedAssets = fAssets;
		fixedAssetsDetails = faDetails;
		fixedAssetsSpecification = faSpecification;
		postingFixedAssets = pfAssets;

		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, fixedAssets->GetID(), errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		if (fixedAssetsSpecification->UpdateFixedAssetsSpecification(globalVar, ormasDal, errorMessage))
		{
			if (fixedAssetsDetails->UpdateFixedAssetsDetails(globalVar, ormasDal, errorMessage))
			{
				if (previousStatusID == statusMap.find("IN USE")->second && fixedAssets->GetStatusID() == statusMap.find("IN USE")->second)
				{
					return true;
				}
				if (previousStatusID != statusMap.find("IN USE")->second && fixedAssets->GetStatusID() == statusMap.find("WRITE-OFFED")->second)
				{
					errorMessage = "Cannot update the document, because \"WRITE-OFFED\" status is unchangeable state";
					return false;
				}
				if (previousStatusID == statusMap.find("IN USE")->second)
				{
					if (fixedAssets->GetStatusID() != statusMap.find("WRITE-OFFED")->second && fixedAssets->GetStatusID() != statusMap.find("ERROR")->second)
					{
						errorMessage = "Cannot update the document, because \"IN USE\" status could be changed to \"WRITE-OFFED\" or \"ERROR\"";
						return false;
					}
				}
				if (fixedAssets->UpdateFixedAssets(globalVar, ormasDal, errorMessage))
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
						postingFixedAssets->SetFixedAssetsID(fixedAssets->GetID());
						if (!postingFixedAssets->UpdatePostingFixedAssets(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
					}
					if (fixedAssets->GetStatusID() == statusMap.find("IN USE")->second && isNewFixedAssets == true)
					{
						if (fixedAssets->CreatePostingFixedAssetsEntry(globalVar, ormasDal, accountableID, purveyorID, accountID, fixedAssetsDetails->GetPrimaryCostAccountID(), fixedAssets->GetPrimaryCost(), fixedAssets->GetStartOfOperationDate(), errorMessage))
						{
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					if (previousStatusID == statusMap.find("IN USE")->second && fixedAssets->GetStatusID() == statusMap.find("ERROR")->second)
					{
						Subaccount sub;
						if (!sub.GetSubaccountByID(globalVar, ormasDal, fixedAssetsDetails->GetAmortizeAccountID(), errorMessage))
							return false;
						if (sub.GetCurrentBalance() != 0)
						{
							errorMessage = "Cannot set status to \"ERROR\", amortize account value does not equal to 0";
							return false;
						}
						if (fixedAssets->CreatePostingFixedAssetsEntryReverce(globalVar, ormasDal, accountableID, purveyorID, accountID, fixedAssetsDetails->GetPrimaryCostAccountID(), fixedAssets->GetPrimaryCost(), fixedAssets->GetStartOfOperationDate(), errorMessage))
						{
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					if (previousStatusID == statusMap.find("IN USE")->second && fixedAssets->GetStatusID() == statusMap.find("WRITE-OFFED")->second)
					{
						if (fixedAssets->CreatePostingFixedAssetsEntryWriteOFF(globalVar, ormasDal, fixedAssets->GetID(), errorMessage))
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
			}
			else
			{
				return false;
			}
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string FixedAssetsUnion::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		/*fixedAssets->SetID(std::get<0>(fCollection));
		fixedAssets->SetSpecificationID(std::get<22>(fCollection));
		fixedAssets->SetInventoryNumber(std::get<6>(fCollection));
		fixedAssets->SetPrimaryCost(std::get<3>(fCollection));
		fixedAssets->SetStopCost(std::get<4>(fCollection));
		fixedAssets->SetServiceLife(std::get<8>(fCollection));
		fixedAssets->SetIsAmortize(std::get<9>(fCollection));
		fixedAssets->SetBuyDate(std::get<11>(fCollection));
		fixedAssets->SetStartOfOperationDate(std::get<12>(fCollection));
		fixedAssets->SetEndOfOperationDate(std::get<13>(fCollection));
		fixedAssets->SetStatusID(std::get<23>(fCollection));
		fixedAssets->SetFixedAssetsDetailsID(std::get<24>(fCollection));

		fixedAssetsSpecification->SetID(std::get<22>(fCollection));
		fixedAssetsSpecification->SetName(std::get<1>(fCollection));
		fixedAssetsSpecification->SetFactoryNumber(std::get<16>(fCollection));
		fixedAssetsSpecification->SetDeveloper(std::get<17>(fCollection));
		fixedAssetsSpecification->SetDocument(std::get<18>(fCollection));
		fixedAssetsSpecification->SetObjectCharacters(std::get<19>(fCollection));
		fixedAssetsSpecification->SetCondition(std::get<20>(fCollection));
		fixedAssetsSpecification->SetDateOfConstruction(std::get<21>(fCollection));

		fixedAssetsDetails->SetID(std::get<24>(fCollection));
		fixedAssetsDetails->SetAmortizeGroupID(std::get<25>(fCollection));
		fixedAssetsDetails->SetAmortizeTypeID(std::get<26>(fCollection));
		fixedAssetsDetails->SetDepartmentID(std::get<27>(fCollection));
		fixedAssetsDetails->SetFixedAssetsLocation(std::get<14>(fCollection));
		fixedAssetsDetails->SetPrimaryCostAccountID(std::get<28>(fCollection));
		fixedAssetsDetails->SetAmortizeAccountID(std::get<29>(fCollection));
		fixedAssetsDetails->SetBarcodeNumber(std::get<15>(fCollection));
		fixedAssetsDetails->SetAmortizeValue(std::get<7>(fCollection));

		postingFixedAssets->SetID(std::get<30>(fCollection));
		postingFixedAssets->SetUserID(std::get<31>(fCollection));
		postingFixedAssets->SetSubaccountID(std::get<32>(fCollection));
		postingFixedAssets->SetAccountID(std::get<33>(fCollection));
		if (!fixedAssets->IsEmpty() || !fixedAssetsSpecification->IsEmpty() || !fixedAssetsDetails->IsEmpty() || !postingFixedAssets->IsEmpty())
		{
			return ormasDal.GetFilterForFixedAssUnionView(fixedAssets->GetID(), fixedAssetsSpecification->GetName(), fixedAssetsDetails->GetDepartmentID(),
				fixedAssets->GetInventoryNumber(), fixedAssets->GetPrimaryCost(),
				fixedAssets->GetStopCost(), fixedAssets->GetServiceLife(), fixedAssets->GetIsAmortize(), fixedAssets->GetBuyDate(), fixedAssets->SetStartOfOperationDate(),inventoryNumber, primaryCost, stopCost, serviceLife,
				isAmortize, buyDate, startOfOperationDate, endOfOperationDate, fixedAssetsSpecification->GetID(), statusID, fixedAssetsDetailsID);
		}*/
		return "";
	}

	bool FixedAssetsUnion::UpdateFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, fixedAssets->GetID(), errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		if (fixedAssetsSpecification->UpdateFixedAssetsSpecification(globalVar, ormasDal, errorMessage))
		{
			if (fixedAssetsDetails->UpdateFixedAssetsDetails(globalVar, ormasDal, errorMessage))
			{
				if (previousStatusID == statusMap.find("IN USE")->second && fixedAssets->GetStatusID() == statusMap.find("IN USE")->second)
				{
					return true;
				}
				if (previousStatusID != statusMap.find("IN USE")->second && fixedAssets->GetStatusID() == statusMap.find("WRITE-OFFED")->second)
				{
					errorMessage = "Cannot update the document, because \"WRITE-OFFED\" status is unchangeable state";
					return false;
				}
				if (previousStatusID == statusMap.find("IN USE")->second)
				{
					if (fixedAssets->GetStatusID() != statusMap.find("WRITE-OFFED")->second && fixedAssets->GetStatusID() != statusMap.find("ERROR")->second)
					{
						errorMessage = "Cannot update the document, because \"IN USE\" status could be changed to \"WRITE-OFFED\" or \"ERROR\"";
						return false;
					}
				}
				if (fixedAssets->UpdateFixedAssets(globalVar, ormasDal, errorMessage))
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
						postingFixedAssets->SetFixedAssetsID(fixedAssets->GetID());
						if (!postingFixedAssets->UpdatePostingFixedAssets(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
					}
					if (fixedAssets->GetStatusID() == statusMap.find("IN USE")->second && isNewFixedAssets == true)
					{
						if (fixedAssets->CreatePostingFixedAssetsEntry(globalVar, ormasDal, accountableID, purveyorID, accountID, fixedAssetsDetails->GetPrimaryCostAccountID(), fixedAssets->GetPrimaryCost(), ormasDal.GetSystemDate(), errorMessage))
						{
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					if (previousStatusID == statusMap.find("IN USE")->second && fixedAssets->GetStatusID() == statusMap.find("ERROR")->second)
					{
						Subaccount sub;
						if (!sub.GetSubaccountByID(globalVar, ormasDal, fixedAssetsDetails->GetAmortizeAccountID(), errorMessage))
							return false;
						if (sub.GetCurrentBalance() != 0)
						{
							errorMessage = "Cannot set status to \"ERROR\", amortize account value does not equal to 0";
							return false;
						}
						if (fixedAssets->CreatePostingFixedAssetsEntryReverce(globalVar, ormasDal, accountableID, purveyorID, accountID, fixedAssetsDetails->GetPrimaryCostAccountID(), fixedAssets->GetPrimaryCost(), ormasDal.GetSystemDate(), errorMessage))
						{
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					if (previousStatusID == statusMap.find("IN USE")->second && fixedAssets->GetStatusID() == statusMap.find("WRITE-OFFED")->second)
					{
						if (fixedAssets->CreatePostingFixedAssetsEntryWriteOFF(globalVar, ormasDal, fixedAssets->GetID(), errorMessage))
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
			}
			else
			{
				return false;
			}
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool FixedAssetsUnion::IsEmpty()
	{
		if (fixedAssets->IsEmpty() && fixedAssetsDetails->IsEmpty() && fixedAssetsSpecification->IsEmpty() && postingFixedAssets->IsEmpty())
			return true;
		return false;
	}

	void FixedAssetsUnion::Clear()
	{
		fixedAssets->Clear();
		fixedAssetsDetails->Clear();
		fixedAssetsSpecification->Clear();
		postingFixedAssets->Clear();
	}

	std::string FixedAssetsUnion::GenerateInventoryNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int divID)
	{
		std::string errorMessage="";
		std::string invNumber="";
		invNumber += "F";
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

	std::string FixedAssetsUnion::GenerateInvRawNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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

	int FixedAssetsUnion::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fxID, std::string& errorMessage)
	{
		FixedAssets fixedAssets;
		if (fixedAssets.GetFixedAssetsByID(globalVar, ormasDal, fxID, errorMessage))
			return fixedAssets.GetStatusID();
		return 0;
	}
}
