#include "stdafx.h"
#include "SpoilageListClass.h"

namespace BusinessLayer
{
	SpoilageList::SpoilageList(DataLayer::spoilageListCollection sListCollection)
	{
		id = std::get<0>(sListCollection);
		spoilageID = std::get<1>(sListCollection);
		productID = std::get<2>(sListCollection);
		count = std::get<3>(sListCollection);
		sum = std::get<4>(sListCollection);
		statusID = std::get<5>(sListCollection);
		currencyID = std::get<6>(sListCollection);
	}

	int SpoilageList::GetID()
	{
		return id;
	}

	int SpoilageList::GetSpoilageID()
	{
		return spoilageID;
	}

	int SpoilageList::GetProductID()
	{
		return productID;
	}

	double SpoilageList::GetCount()
	{
		return count;
	}

	double SpoilageList::GetSum()
	{
		return sum;
	}

	int SpoilageList::GetStatusID()
	{
		return statusID;
	}

	int SpoilageList::GetCurrencyID()
	{
		return currencyID;
	}

	void SpoilageList::SetID(int sID)
	{
		id = sID;
	}
	void SpoilageList::SetSpoilageID(int sSpoilageID)
	{
		spoilageID = sSpoilageID;
	}
	void SpoilageList::SetProductID(int sProductID)
	{
		productID = sProductID;
	}
	void SpoilageList::SetCount(double sCount)
	{
		count = sCount;
	}
	void SpoilageList::SetSum(double sSum)
	{
		sum = sSum;
	}
	void SpoilageList::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void SpoilageList::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}

	bool SpoilageList::CreateSpoilageList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, double slCount, double slSum,
		int stsID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		spoilageID = sID;
		productID = pID;
		count = slCount;
		sum = slSum;
		statusID = stsID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateSpoilageList(id, spoilageID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool SpoilageList::CreateSpoilageList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateSpoilageList(id, spoilageID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool SpoilageList::DeleteSpoilageList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInSpoilageList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool SpoilageList::DeleteListBySpoilageID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		spoilageID = sID;
		if (ormasDal.DeleteListBySpoilageID(spoilageID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool SpoilageList::UpdateSpoilageList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, double slCount, double slSum,
		int stsID, int cID, std::string& errorMessage)
	{
		spoilageID = sID;
		productID = pID;
		count = slCount;
		sum = slSum;
		statusID = stsID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateSpoilageList(id, spoilageID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool SpoilageList::UpdateSpoilageList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateSpoilageList(id, spoilageID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string SpoilageList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != spoilageID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForSpoilageList(id, spoilageID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool SpoilageList::GetSpoilageListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::spoilageListViewCollection> spoilageListVector = ormasDal.GetSpoilageList(errorMessage, filter);
		if (0 != spoilageListVector.size())
		{
			id = std::get<0>(spoilageListVector.at(0));
			spoilageID = std::get<1>(spoilageListVector.at(0));
			count = std::get<7>(spoilageListVector.at(0));
			sum = std::get<8>(spoilageListVector.at(0));
			productID = std::get<11>(spoilageListVector.at(0));
			statusID = std::get<12>(spoilageListVector.at(0));
			currencyID = std::get<13>(spoilageListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find spoilage list with this id";
		}
		return false;
	}

	bool SpoilageList::IsEmpty()
	{
		if (0 == id && 0 == spoilageID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void SpoilageList::Clear()
	{
		id = 0;
		spoilageID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool SpoilageList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, int slCount, double slSum,
		int cID, std::string& errorMessage)
	{
		SpoilageList spoilageList;
		spoilageList.Clear();
		errorMessage.clear();
		spoilageList.SetSpoilageID(sID);
		spoilageList.SetProductID(pID);
		spoilageList.SetCount(slCount);
		spoilageList.SetSum(slSum);
		spoilageList.SetCurrencyID(cID);
		std::string filter = spoilageList.GenerateFilter(ormasDal);
		std::vector<DataLayer::spoilageListViewCollection> spoilageListVector = ormasDal.GetSpoilageList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == spoilageListVector.size())
		{
			return false;
		}
		errorMessage = "Spoilage list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool SpoilageList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		SpoilageList spoilageList;
		spoilageList.Clear();
		errorMessage.clear();
		spoilageList.SetSpoilageID(spoilageID);
		spoilageList.SetProductID(productID);
		spoilageList.SetCount(count);
		spoilageList.SetSum(sum);
		spoilageList.SetCurrencyID(currencyID);
		std::string filter = spoilageList.GenerateFilter(ormasDal);
		std::vector<DataLayer::spoilageListViewCollection> spoilageListVector = ormasDal.GetSpoilageList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == spoilageListVector.size())
		{
			return false;
		}
		errorMessage = "Spoilage list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}