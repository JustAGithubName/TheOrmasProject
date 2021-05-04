#include "stdafx.h"
#include "ConsumeRawListClass.h"

namespace BusinessLayer
{
	ConsumeRawList::ConsumeRawList(DataLayer::consumeRawListCollection cListCollection)
	{
		id = std::get<0>(cListCollection);
		consumeRawID = std::get<1>(cListCollection);
		productID = std::get<2>(cListCollection);
		count = std::get<3>(cListCollection);
		sum = std::get<4>(cListCollection);
		statusID = std::get<5>(cListCollection);
		currencyID = std::get<6>(cListCollection);
	}

	int ConsumeRawList::GetID()
	{
		return id;
	}

	int ConsumeRawList::GetConsumeRawID()
	{
		return consumeRawID;
	}

	int ConsumeRawList::GetProductID()
	{
		return productID;
	}

	double ConsumeRawList::GetCount()
	{
		return count;
	}

	double ConsumeRawList::GetSum()
	{
		return sum;
	}

	int ConsumeRawList::GetStatusID()
	{
		return statusID;
	}

	int ConsumeRawList::GetCurrencyID()
	{
		return currencyID;
	}

	void ConsumeRawList::SetID(int cID)
	{
		id = cID;
	}
	void ConsumeRawList::SetConsumeRawID(int cConsumeRawID)
	{
		consumeRawID = cConsumeRawID;
	}
	void ConsumeRawList::SetProductID(int cProductID)
	{
		productID = cProductID;
	}
	void ConsumeRawList::SetCount(double cCount)
	{
		count = cCount;
	}
	void ConsumeRawList::SetSum(double cSum)
	{
		sum = cSum;
	}
	void ConsumeRawList::SetStatusID(int cStatusID)
	{
		statusID = cStatusID;
	}
	void ConsumeRawList::SetCurrencyID(int cCurrencyID)
	{
		currencyID = cCurrencyID;
	}

	bool ConsumeRawList::CreateConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int pID, double crlCount, double crlSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		consumeRawID = crID;
		productID = pID;
		count = crlCount;
		sum = crlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateConsumeRawList(id, consumeRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeRawList::CreateConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateConsumeRawList(id, consumeRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeRawList::DeleteConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInConsumeRawList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ConsumeRawList::DeleteListByConsumeRawID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage)
	{
		consumeRawID = crID;
		if (ormasDal.DeleteListByConsumeRawID(consumeRawID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool ConsumeRawList::UpdateConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int pID, double crlCount, double crlSum,
		int sID, int cID, std::string& errorMessage)
	{
		consumeRawID = crID;
		productID = pID;
		count = crlCount;
		sum = crlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateConsumeRawList(id, consumeRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeRawList::UpdateConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateConsumeRawList(id, consumeRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ConsumeRawList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != consumeRawID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForConsumeRawList(id, consumeRawID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool ConsumeRawList::GetConsumeRawListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> consumeRawListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (0 != consumeRawListVector.size())
		{
			id = std::get<0>(consumeRawListVector.at(0));
			consumeRawID = std::get<1>(consumeRawListVector.at(0));
			count = std::get<7>(consumeRawListVector.at(0));
			sum = std::get<8>(consumeRawListVector.at(0));
			productID = std::get<11>(consumeRawListVector.at(0));
			statusID = std::get<12>(consumeRawListVector.at(0));
			currencyID = std::get<13>(consumeRawListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find consume raw list with this id";
		}
		return false;
	}

	bool ConsumeRawList::IsEmpty()
	{
		if (0 == id && 0 == consumeRawID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ConsumeRawList::Clear()
	{
		id = 0;
		consumeRawID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ConsumeRawList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int pID, double crlCount, double crlSum,
		int cID, std::string& errorMessage)
	{
		ConsumeRawList consumeRawList;
		consumeRawList.Clear();
		errorMessage.clear();
		consumeRawList.SetConsumeRawID(crID);
		consumeRawList.SetProductID(pID);
		consumeRawList.SetCount(crlCount);
		consumeRawList.SetSum(crlSum);
		consumeRawList.SetCurrencyID(cID);
		std::string filter = consumeRawList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> consumeRawListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == consumeRawListVector.size())
		{
			return false;
		}
		errorMessage = "Consume raw list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ConsumeRawList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ConsumeRawList consumeRawList;
		consumeRawList.Clear();
		errorMessage.clear();
		consumeRawList.SetConsumeRawID(consumeRawID);
		consumeRawList.SetProductID(productID);
		consumeRawList.SetCount(count);
		consumeRawList.SetSum(sum);
		consumeRawList.SetCurrencyID(currencyID);
		std::string filter = consumeRawList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> consumeRawListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == consumeRawListVector.size())
		{
			return false;
		}
		errorMessage = "Consume raw list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}