#include "stdafx.h"
#include "ConsumeOtherStocksListClass.h"

namespace BusinessLayer
{
	ConsumeOtherStocksList::ConsumeOtherStocksList(DataLayer::consumeOtherStocksListCollection cListCollection)
	{
		id = std::get<0>(cListCollection);
		consumeOtherStocksID = std::get<1>(cListCollection);
		otherStocksID = std::get<2>(cListCollection);
		count = std::get<3>(cListCollection);
		sum = std::get<4>(cListCollection);
		statusID = std::get<5>(cListCollection);
		currencyID = std::get<6>(cListCollection);
	}

	int ConsumeOtherStocksList::GetID()
	{
		return id;
	}

	int ConsumeOtherStocksList::GetConsumeOtherStocksID()
	{
		return consumeOtherStocksID;
	}

	int ConsumeOtherStocksList::GetOtherStocksID()
	{
		return otherStocksID;
	}

	double ConsumeOtherStocksList::GetCount()
	{
		return count;
	}

	double ConsumeOtherStocksList::GetSum()
	{
		return sum;
	}

	int ConsumeOtherStocksList::GetStatusID()
	{
		return statusID;
	}

	int ConsumeOtherStocksList::GetCurrencyID()
	{
		return currencyID;
	}

	void ConsumeOtherStocksList::SetID(int cID)
	{
		id = cID;
	}
	void ConsumeOtherStocksList::SetConsumeOtherStocksID(int cConsumeOtherStocksID)
	{
		consumeOtherStocksID = cConsumeOtherStocksID;
	}
	void ConsumeOtherStocksList::SetOtherStocksID(int cProductID)
	{
		otherStocksID = cProductID;
	}
	void ConsumeOtherStocksList::SetCount(double cCount)
	{
		count = cCount;
	}
	void ConsumeOtherStocksList::SetSum(double cSum)
	{
		sum = cSum;
	}
	void ConsumeOtherStocksList::SetStatusID(int cStatusID)
	{
		statusID = cStatusID;
	}
	void ConsumeOtherStocksList::SetCurrencyID(int cCurrencyID)
	{
		currencyID = cCurrencyID;
	}

	bool ConsumeOtherStocksList::CreateConsumeOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int osID, double crlCount, double crlSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		consumeOtherStocksID = crID;
		otherStocksID = osID;
		count = crlCount;
		sum = crlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateConsumeOtherStocksList(id, consumeOtherStocksID, otherStocksID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeOtherStocksList::CreateConsumeOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateConsumeOtherStocksList(id, consumeOtherStocksID, otherStocksID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeOtherStocksList::DeleteConsumeOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInConsumeOtherStocksList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ConsumeOtherStocksList::DeleteListByConsumeOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage)
	{
		consumeOtherStocksID = crID;
		if (ormasDal.DeleteListByConsumeOtherStocksID(consumeOtherStocksID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool ConsumeOtherStocksList::UpdateConsumeOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int osID, double crlCount, double crlSum,
		int sID, int cID, std::string& errorMessage)
	{
		consumeOtherStocksID = crID;
		otherStocksID = osID;
		count = crlCount;
		sum = crlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateConsumeOtherStocksList(id, consumeOtherStocksID, otherStocksID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeOtherStocksList::UpdateConsumeOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateConsumeOtherStocksList(id, consumeOtherStocksID, otherStocksID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ConsumeOtherStocksList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != consumeOtherStocksID || 0 != otherStocksID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForConsumeOtherStocksList(id, consumeOtherStocksID, otherStocksID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool ConsumeOtherStocksList::GetConsumeOtherStocksListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksListViewCollection> consumeOtherStocksListVector = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);
		if (0 != consumeOtherStocksListVector.size())
		{
			id = std::get<0>(consumeOtherStocksListVector.at(0));
			consumeOtherStocksID = std::get<1>(consumeOtherStocksListVector.at(0));
			count = std::get<7>(consumeOtherStocksListVector.at(0));
			sum = std::get<8>(consumeOtherStocksListVector.at(0));
			otherStocksID = std::get<11>(consumeOtherStocksListVector.at(0));
			statusID = std::get<12>(consumeOtherStocksListVector.at(0));
			currencyID = std::get<13>(consumeOtherStocksListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find consume other stocks list with this id";
		}
		return false;
	}

	bool ConsumeOtherStocksList::IsEmpty()
	{
		if (0 == id && 0 == consumeOtherStocksID && 0 == count && 0 == sum && 0 == otherStocksID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ConsumeOtherStocksList::Clear()
	{
		id = 0;
		consumeOtherStocksID = 0;
		count = 0;
		sum = 0;
		otherStocksID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ConsumeOtherStocksList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int osID, double crlCount, double crlSum,
		int cID, std::string& errorMessage)
	{
		ConsumeOtherStocksList consumeOtherStocksList;
		consumeOtherStocksList.Clear();
		errorMessage.clear();
		consumeOtherStocksList.SetConsumeOtherStocksID(crID);
		consumeOtherStocksList.SetOtherStocksID(osID);
		consumeOtherStocksList.SetCount(crlCount);
		consumeOtherStocksList.SetSum(crlSum);
		consumeOtherStocksList.SetCurrencyID(cID);
		std::string filter = consumeOtherStocksList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksListViewCollection> consumeOtherStocksListVector = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == consumeOtherStocksListVector.size())
		{
			return false;
		}
		errorMessage = "Consume other stocks list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ConsumeOtherStocksList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ConsumeOtherStocksList consumeOtherStocksList;
		consumeOtherStocksList.Clear();
		errorMessage.clear();
		consumeOtherStocksList.SetConsumeOtherStocksID(consumeOtherStocksID);
		consumeOtherStocksList.SetOtherStocksID(otherStocksID);
		consumeOtherStocksList.SetCount(count);
		consumeOtherStocksList.SetSum(sum);
		consumeOtherStocksList.SetCurrencyID(currencyID);
		std::string filter = consumeOtherStocksList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksListViewCollection> consumeOtherStocksListVector = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == consumeOtherStocksListVector.size())
		{
			return false;
		}
		errorMessage = "Consume other stocks list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}