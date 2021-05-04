#include "stdafx.h"
#include "ReturnListClass.h"

namespace BusinessLayer
{
	ReturnList::ReturnList(DataLayer::returnListCollection rListCollection)
	{
		id = std::get<0>(rListCollection);
		returnID = std::get<1>(rListCollection);
		productID = std::get<2>(rListCollection);
		count = std::get<3>(rListCollection);
		sum = std::get<4>(rListCollection);
		statusID = std::get<5>(rListCollection);
		currencyID = std::get<6>(rListCollection);
	}

	int ReturnList::GetID()
	{
		return id;
	}

	int ReturnList::GetReturnID()
	{
		return returnID;
	}

	int ReturnList::GetProductID()
	{
		return productID;
	}

	double ReturnList::GetCount()
	{
		return count;
	}

	double ReturnList::GetSum()
	{
		return sum;
	}

	int ReturnList::GetStatusID()
	{
		return statusID;
	}

	int ReturnList::GetCurrencyID()
	{
		return currencyID;
	}

	void ReturnList::SetID(int rID)
	{
		id = rID;
	}
	void ReturnList::SetReturnID(int rReturnID)
	{
		returnID = rReturnID;
	}
	void ReturnList::SetProductID(int rProductID)
	{
		productID = rProductID;
	}
	void ReturnList::SetCount(double rCount)
	{
		count = rCount;
	}
	void ReturnList::SetSum(double rSum)
	{
		sum = rSum;
	}
	void ReturnList::SetStatusID(int rStatusID)
	{
		statusID = rStatusID;
	}
	void ReturnList::SetCurrencyID(int rCurrencyID)
	{
		currencyID = rCurrencyID;
	}

	bool ReturnList::CreateReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rCount, double rSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		returnID = rID;
		productID = pID;
		count = rCount;
		sum = rSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateReturnList(id, returnID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReturnList::CreateReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateReturnList(id, returnID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReturnList::DeleteReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInReturnList(id, errorMessage))
		{
			Clear();
			id = 0;
			return true;
		}
		return false;
	}
	bool ReturnList::DeleteListByReturnID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage)
	{
		returnID = rID;
		if (ormasDal.DeleteListByReturnID(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ReturnList::UpdateReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rCount, double rSum,
		int sID, int cID, std::string& errorMessage)
	{
		returnID = rID;
		productID = pID;
		count = rCount;
		sum = rSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateReturnList(id, returnID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReturnList::UpdateReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateReturnList(id, returnID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ReturnList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != returnID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForReturnList(id, returnID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool ReturnList::GetReturnListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::returnListViewCollection> returnListVector = ormasDal.GetReturnList(errorMessage, filter);
		if (0 != returnListVector.size())
		{
			id = std::get<0>(returnListVector.at(0));
			returnID = std::get<1>(returnListVector.at(0));
			count = std::get<7>(returnListVector.at(0));
			sum = std::get<8>(returnListVector.at(0));
			productID = std::get<11>(returnListVector.at(0));
			statusID = std::get<12>(returnListVector.at(0));
			currencyID = std::get<13>(returnListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Return list with this id";
		}
		return false;
	}
	
	bool ReturnList::IsEmpty()
	{
		if (0 == id && 0 == returnID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ReturnList::Clear()
	{
		id = 0;
		returnID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ReturnList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
		int cID, std::string& errorMessage)
	{
		ReturnList returnList;
		returnList.Clear();
		errorMessage.clear();
		returnList.SetReturnID(rID);
		returnList.SetProductID(pID);
		returnList.SetCount(rlCount);
		returnList.SetSum(rlSum);
		returnList.SetCurrencyID(cID);
		std::string filter = returnList.GenerateFilter(ormasDal);
		std::vector<DataLayer::returnListViewCollection> returnListVector = ormasDal.GetReturnList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == returnListVector.size())
		{
			return false;
		}
		errorMessage = "Return list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ReturnList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ReturnList returnList;
		returnList.Clear();
		errorMessage.clear();
		returnList.SetReturnID(returnID);
		returnList.SetProductID(productID);
		returnList.SetCount(count);
		returnList.SetSum(sum);
		returnList.SetCurrencyID(currencyID);
		std::string filter = returnList.GenerateFilter(ormasDal);
		std::vector<DataLayer::returnListViewCollection> returnListVector = ormasDal.GetReturnList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == returnListVector.size())
		{
			return false;
		}
		errorMessage = "Return list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}