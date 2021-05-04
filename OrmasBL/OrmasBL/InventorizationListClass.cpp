#include "stdafx.h"
#include "InventorizationListClass.h"

namespace BusinessLayer
{
	InventorizationList::InventorizationList(DataLayer::inventorizationListCollection iListCollection)
	{
		id = std::get<0>(iListCollection);
		inventorizationID = std::get<1>(iListCollection);
		productID = std::get<2>(iListCollection);
		count = std::get<3>(iListCollection);
		sum = std::get<4>(iListCollection);
		statusID = std::get<5>(iListCollection);
		currencyID = std::get<6>(iListCollection);
	}

	int InventorizationList::GetID()
	{
		return id;
	}

	int InventorizationList::GetInventorizationID()
	{
		return inventorizationID;
	}

	int InventorizationList::GetProductID()
	{
		return productID;
	}

	double InventorizationList::GetCount()
	{
		return count;
	}

	double InventorizationList::GetSum()
	{
		return sum;
	}

	int InventorizationList::GetStatusID()
	{
		return statusID;
	}

	int InventorizationList::GetCurrencyID()
	{
		return currencyID;
	}

	void InventorizationList::SetID(int iID)
	{
		id = iID;
	}
	void InventorizationList::SetInventorizationID(int iInventorizationID)
	{
		inventorizationID = iInventorizationID;
	}
	void InventorizationList::SetProductID(int iProductID)
	{
		productID = iProductID;
	}
	void InventorizationList::SetCount(double iCount)
	{
		count = iCount;
	}
	void InventorizationList::SetSum(double iSum)
	{
		sum = iSum;
	}
	void InventorizationList::SetStatusID(int iStatusID)
	{
		statusID = iStatusID;
	}
	void InventorizationList::SetCurrencyID(int iCurrencyID)
	{
		currencyID = iCurrencyID;
	}

	bool InventorizationList::CreateInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, int pID, double ilCount, double ilSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		inventorizationID = iID;
		productID = pID;
		count = ilCount;
		sum = ilSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateInventorizationList(id, inventorizationID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool InventorizationList::CreateInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateInventorizationList(id, inventorizationID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool InventorizationList::DeleteInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInInventorizationList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool InventorizationList::DeleteListByInventorizationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage)
	{
		inventorizationID = iID;
		if (ormasDal.DeleteListByInventorizationID(inventorizationID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool InventorizationList::UpdateInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, int pID, double ilCount, double ilSum,
		int sID, int cID, std::string& errorMessage)
	{
		inventorizationID = iID;
		productID = pID;
		count = ilCount;
		sum = ilSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateInventorizationList(id, inventorizationID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool InventorizationList::UpdateInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateInventorizationList(id, inventorizationID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string InventorizationList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != inventorizationID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForInventorizationList(id, inventorizationID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool InventorizationList::GetInventorizationListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage)
	{
		if (iID <= 0)
			return false;
		id = iID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::inventorizationListViewCollection> inventorizationListVector = ormasDal.GetInventorizationList(errorMessage, filter);
		if (0 != inventorizationListVector.size())
		{
			id = std::get<0>(inventorizationListVector.at(0));
			inventorizationID = std::get<1>(inventorizationListVector.at(0));
			count = std::get<7>(inventorizationListVector.at(0));
			sum = std::get<8>(inventorizationListVector.at(0));
			productID = std::get<11>(inventorizationListVector.at(0));
			statusID = std::get<12>(inventorizationListVector.at(0));
			currencyID = std::get<13>(inventorizationListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find inventorization list with this id";
		}
		return false;
	}

	bool InventorizationList::IsEmpty()
	{
		if (0 == id && 0 == inventorizationID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void InventorizationList::Clear()
	{
		id = 0;
		inventorizationID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool InventorizationList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, int pID, double ilCount, double ilSum,
		int cID, std::string& errorMessage)
	{
		InventorizationList inventorizationList;
		inventorizationList.Clear();
		errorMessage.clear();
		inventorizationList.SetInventorizationID(iID);
		inventorizationList.SetProductID(pID);
		inventorizationList.SetCount(ilCount);
		inventorizationList.SetSum(ilSum);
		inventorizationList.SetCurrencyID(cID);
		std::string filter = inventorizationList.GenerateFilter(ormasDal);
		std::vector<DataLayer::inventorizationListViewCollection> inventorizationListVector = ormasDal.GetInventorizationList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == inventorizationListVector.size())
		{
			return false;
		}
		errorMessage = "Inventorization list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool InventorizationList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		InventorizationList inventorizationList;
		inventorizationList.Clear();
		errorMessage.clear();
		inventorizationList.SetInventorizationID(inventorizationID);
		inventorizationList.SetProductID(productID);
		inventorizationList.SetCount(count);
		inventorizationList.SetSum(sum);
		inventorizationList.SetCurrencyID(currencyID);
		std::string filter = inventorizationList.GenerateFilter(ormasDal);
		std::vector<DataLayer::inventorizationListViewCollection> inventorizationListVector = ormasDal.GetInventorizationList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == inventorizationListVector.size())
		{
			return false;
		}
		errorMessage = "Inventorization list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}