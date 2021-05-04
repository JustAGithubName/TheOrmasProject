#include "stdafx.h"
#include "PostingFixedAssetsClass.h"

namespace BusinessLayer
{
	PostingFixedAssets::PostingFixedAssets(DataLayer::postingFixedAssetsCollection fCollection)
	{
		id = std::get<0>(fCollection);
		userID = std::get<1>(fCollection);
		subaccountID = std::get<2>(fCollection);
		accountID = std::get<3>(fCollection);
		fixedAssetsID = std::get<4>(fCollection);
		inventoryID = std::get<5>(fCollection);
	}

	int PostingFixedAssets::GetID()
	{
		return id;
	}

	int PostingFixedAssets::GetUserID()
	{
		return userID;
	}

	int PostingFixedAssets::GetSubaccountID()
	{
		return subaccountID;
	}

	int PostingFixedAssets::GetAccountID()
	{
		return accountID;
	}

	int PostingFixedAssets::GetFixedAssetsID()
	{
		return fixedAssetsID;
	}

	int PostingFixedAssets::GetInventoryID()
	{
		return inventoryID;
	}

	void PostingFixedAssets::SetID(int fID)
	{
		id = fID;
	}

	void PostingFixedAssets::SetUserID(int uID)
	{
		userID = uID;
	}

	void PostingFixedAssets::SetSubaccountID(int sID)
	{
		subaccountID = sID;
	}

	void PostingFixedAssets::SetAccountID(int aID)
	{
		accountID = aID;
	}

	void PostingFixedAssets::SetFixedAssetsID(int fID)
	{
		fixedAssetsID = fID;
	}

	void PostingFixedAssets::SetInventoryID(int iID)
	{
		inventoryID = iID;
	}

	bool PostingFixedAssets::CreatePostingFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int sID, int aID, int faID, int iID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, sID, aID, faID, iID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		userID = uID;
		subaccountID = sID;
		accountID = aID;
		fixedAssetsID = faID;
		inventoryID = iID;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreatePostingFixedAssets(id, userID, subaccountID, accountID, fixedAssetsID, inventoryID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool PostingFixedAssets::CreatePostingFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreatePostingFixedAssets(id, userID, subaccountID, accountID, fixedAssetsID, inventoryID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool PostingFixedAssets::DeletePostingFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeletePostingFixedAssets(id, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PostingFixedAssets::UpdatePostingFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int sID, int aID, int faID, int iID, std::string& errorMessage)
	{
		userID = uID;
		subaccountID = sID;
		accountID = aID;
		fixedAssetsID = faID;
		inventoryID = iID;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdatePostingFixedAssets(id, userID, subaccountID, accountID, fixedAssetsID, inventoryID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool PostingFixedAssets::UpdatePostingFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdatePostingFixedAssets(id, userID, subaccountID, accountID, fixedAssetsID, inventoryID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string PostingFixedAssets::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != userID || 0 != subaccountID || 0 != accountID || 0 != fixedAssetsID || 0 != inventoryID)
		{
			return ormasDal.GetFilterForPostingFixedAssets(id, userID, subaccountID, accountID, fixedAssetsID, inventoryID);
		}
		return "";
	}

	bool PostingFixedAssets::GetPostingFixedAssetsByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fID, std::string& errorMessage)
	{
		if (fID <= 0)
			return false;
		id = fID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::postingFixedAssetsViewCollection> postingFixedAssetsVector = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		if (0 != postingFixedAssetsVector.size())
		{
			id = std::get<0>(postingFixedAssetsVector.at(0));
			userID = std::get<3>(postingFixedAssetsVector.at(0));
			subaccountID = std::get<4>(postingFixedAssetsVector.at(0));
			accountID = std::get<5>(postingFixedAssetsVector.at(0));
			fixedAssetsID = std::get<6>(postingFixedAssetsVector.at(0));
			inventoryID = std::get<7>(postingFixedAssetsVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find posting fixed assets with this id";
		}
		return false;
	}

	bool PostingFixedAssets::GetPostingFixedAssetsByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		userID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::postingFixedAssetsViewCollection> postingFixedAssetsVector = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		if (0 != postingFixedAssetsVector.size())
		{
			id = std::get<0>(postingFixedAssetsVector.at(0));
			userID = std::get<3>(postingFixedAssetsVector.at(0));
			subaccountID = std::get<4>(postingFixedAssetsVector.at(0));
			accountID = std::get<5>(postingFixedAssetsVector.at(0));
			fixedAssetsID = std::get<6>(postingFixedAssetsVector.at(0));
			inventoryID = std::get<7>(postingFixedAssetsVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find posting fixed assets with this user id";
		}
		return false;
	}

	bool PostingFixedAssets::GetPostingFixedAssetsByAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		accountID = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::postingFixedAssetsViewCollection> postingFixedAssetsVector = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		if (0 != postingFixedAssetsVector.size())
		{
			id = std::get<0>(postingFixedAssetsVector.at(0));
			userID = std::get<3>(postingFixedAssetsVector.at(0));
			subaccountID = std::get<4>(postingFixedAssetsVector.at(0));
			accountID = std::get<5>(postingFixedAssetsVector.at(0));
			fixedAssetsID = std::get<6>(postingFixedAssetsVector.at(0));
			inventoryID = std::get<7>(postingFixedAssetsVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find posting fixed assets with this account id";
		}
		return false;
	}

	bool PostingFixedAssets::GetPostingFixedAssetsBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		subaccountID = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::postingFixedAssetsViewCollection> postingFixedAssetsVector = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		if (0 != postingFixedAssetsVector.size())
		{
			id = std::get<0>(postingFixedAssetsVector.at(0));
			userID = std::get<3>(postingFixedAssetsVector.at(0));
			subaccountID = std::get<4>(postingFixedAssetsVector.at(0));
			accountID = std::get<5>(postingFixedAssetsVector.at(0));
			fixedAssetsID = std::get<6>(postingFixedAssetsVector.at(0));
			inventoryID = std::get<7>(postingFixedAssetsVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find posting fixed assets with this subaccount id";
		}
		return false;
	}

	bool PostingFixedAssets::GetPostingFixedAssetsByFixedAssetsID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int faID, std::string& errorMessage)
	{
		if (faID <= 0)
			return false;
		fixedAssetsID = faID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::postingFixedAssetsViewCollection> postingFixedAssetsVector = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		if (0 != postingFixedAssetsVector.size())
		{
			id = std::get<0>(postingFixedAssetsVector.at(0));
			userID = std::get<3>(postingFixedAssetsVector.at(0));
			subaccountID = std::get<4>(postingFixedAssetsVector.at(0));
			accountID = std::get<5>(postingFixedAssetsVector.at(0));
			fixedAssetsID = std::get<6>(postingFixedAssetsVector.at(0));
			inventoryID = std::get<7>(postingFixedAssetsVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find posting fixed assets with this fixed assets id";
		}
		return false;
	}

	bool PostingFixedAssets::GetPostingFixedAssetsByInventoryID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage)
	{
		if (iID <= 0)
			return false;
		inventoryID = iID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::postingFixedAssetsViewCollection> postingFixedAssetsVector = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		if (0 != postingFixedAssetsVector.size())
		{
			id = std::get<0>(postingFixedAssetsVector.at(0));
			userID = std::get<3>(postingFixedAssetsVector.at(0));
			subaccountID = std::get<4>(postingFixedAssetsVector.at(0));
			accountID = std::get<5>(postingFixedAssetsVector.at(0));
			fixedAssetsID = std::get<6>(postingFixedAssetsVector.at(0));
			inventoryID = std::get<7>(postingFixedAssetsVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find posting fixed assets with this inventory id";
		}
		return false;
	}

	bool PostingFixedAssets::IsEmpty()
	{
		if (0 == id && 0 == userID && 0 == subaccountID && 0 == accountID && 0 == fixedAssetsID && 0 == inventoryID)
			return true;
		return false;
	}

	void PostingFixedAssets::Clear()
	{
		id = 0;
		userID = 0;
		subaccountID = 0;
		accountID = 0;
		fixedAssetsID = 0;
		inventoryID = 0;
	}

	bool PostingFixedAssets::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int sID, int aID, int fID, int iID, std::string& errorMessage)
	{
		PostingFixedAssets postingFixedAssets;
		postingFixedAssets.Clear();
		errorMessage.clear();
		if (uID > 0)
			postingFixedAssets.SetUserID(uID);
		if (sID > 0)
			postingFixedAssets.SetSubaccountID(sID);
		if (aID > 0)
			postingFixedAssets.SetAccountID(aID);
		if (fID > 0)
			postingFixedAssets.SetFixedAssetsID(fID);
		if (iID > 0)
			postingFixedAssets.SetInventoryID(iID);
		std::string filter = postingFixedAssets.GenerateFilter(ormasDal);
		std::vector<DataLayer::postingFixedAssetsViewCollection> postingFixedAssetsVector = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == postingFixedAssetsVector.size())
		{
			return false;
		}
		errorMessage = "Posting fixed assets with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool PostingFixedAssets::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		PostingFixedAssets postingFixedAssets;
		postingFixedAssets.Clear();
		errorMessage.clear();
		postingFixedAssets.SetUserID(userID);
		postingFixedAssets.SetSubaccountID(subaccountID);
		postingFixedAssets.SetAccountID(accountID);
		postingFixedAssets.SetFixedAssetsID(fixedAssetsID);
		postingFixedAssets.SetInventoryID(inventoryID);
		std::string filter = postingFixedAssets.GenerateFilter(ormasDal);
		std::vector<DataLayer::postingFixedAssetsViewCollection> postingFixedAssetsVector = ormasDal.GetPostingFixedAssets(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == postingFixedAssetsVector.size())
		{
			return false;
		}
		errorMessage = "Posting fixed assets with these parameters are already exist! Please avoid the duplication!";
		return true;
	}
}
