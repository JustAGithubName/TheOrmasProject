#include "stdafx.h"
#include "ConsumeProductListClass.h"


namespace BusinessLayer
{
	ConsumeProductList::ConsumeProductList(DataLayer::consumeProductListCollection cListCollection)
	{
		id = std::get<0>(cListCollection);
		consumeProductID = std::get<1>(cListCollection);
		productID = std::get<2>(cListCollection);
		count = std::get<3>(cListCollection);
		sum = std::get<4>(cListCollection);
		statusID = std::get<5>(cListCollection);
		currencyID = std::get<6>(cListCollection);
	}

	int ConsumeProductList::GetID()
	{
		return id;
	}

	int ConsumeProductList::GetConsumeProductID()
	{
		return consumeProductID;
	}

	int ConsumeProductList::GetProductID()
	{
		return productID;
	}

	double ConsumeProductList::GetCount()
	{
		return count;
	}

	double ConsumeProductList::GetSum()
	{
		return sum;
	}

	int ConsumeProductList::GetStatusID()
	{
		return statusID;
	}

	int ConsumeProductList::GetCurrencyID()
	{
		return currencyID;
	}

	void ConsumeProductList::SetID(int cID)
	{
		id = cID;
	}
	void ConsumeProductList::SetConsumeProductID(int cConsumeProductID)
	{
		consumeProductID = cConsumeProductID;
	}
	void ConsumeProductList::SetProductID(int cProductID)
	{
		productID = cProductID;
	}
	void ConsumeProductList::SetCount(double cCount)
	{
		count = cCount;
	}
	void ConsumeProductList::SetSum(double cSum)
	{
		sum = cSum;
	}
	void ConsumeProductList::SetStatusID(int cStatusID)
	{
		statusID = cStatusID;
	}
	void ConsumeProductList::SetCurrencyID(int cCurrencyID)
	{
		currencyID = cCurrencyID;
	}

	bool ConsumeProductList::CreateConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int pID, double cplCount, double cplSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		consumeProductID = cpID;
		productID = pID;
		count = cplCount;
		sum = cplSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateConsumeProductList(id, consumeProductID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeProductList::CreateConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateConsumeProductList(id, consumeProductID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeProductList::DeleteConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInConsumeProductList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ConsumeProductList::DeleteListByConsumeProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		consumeProductID = cpID;
		if (ormasDal.DeleteListByConsumeProductID(consumeProductID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool ConsumeProductList::UpdateConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int pID, double cplCount, double cplSum,
		int sID, int cID, std::string& errorMessage)
	{
		consumeProductID = cpID;
		productID = pID;
		count = cplCount;
		sum = cplSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateConsumeProductList(id, consumeProductID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ConsumeProductList::UpdateConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateConsumeProductList(id, consumeProductID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ConsumeProductList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != consumeProductID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForConsumeProductList(id, consumeProductID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool ConsumeProductList::GetConsumeProductListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeProductListViewCollection> consumeProductListVector = ormasDal.GetConsumeProductList(errorMessage, filter);
		if (0 != consumeProductListVector.size())
		{
			id = std::get<0>(consumeProductListVector.at(0));
			consumeProductID = std::get<1>(consumeProductListVector.at(0));
			count = std::get<7>(consumeProductListVector.at(0));
			sum = std::get<8>(consumeProductListVector.at(0));
			productID = std::get<11>(consumeProductListVector.at(0));
			statusID = std::get<12>(consumeProductListVector.at(0));
			currencyID = std::get<13>(consumeProductListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find consume product list with this id";
		}
		return false;
	}

	bool ConsumeProductList::IsEmpty()
	{
		if (0 == id && 0 == consumeProductID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ConsumeProductList::Clear()
	{
		id = 0;
		consumeProductID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ConsumeProductList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int pID, double cplCount, double cplSum,
		int cID, std::string& errorMessage)
	{
		ConsumeProductList consumeProductList;
		consumeProductList.Clear();
		errorMessage.clear();
		consumeProductList.SetConsumeProductID(cpID);
		consumeProductList.SetProductID(pID);
		consumeProductList.SetCount(cplCount);
		consumeProductList.SetSum(cplSum);
		consumeProductList.SetCurrencyID(cID);
		std::string filter = consumeProductList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeProductListViewCollection> consumeProductListVector = ormasDal.GetConsumeProductList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == consumeProductListVector.size())
		{
			return false;
		}
		errorMessage = "Consume product list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ConsumeProductList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ConsumeProductList consumeProductList;
		consumeProductList.Clear();
		errorMessage.clear();
		consumeProductList.SetConsumeProductID(consumeProductID);
		consumeProductList.SetProductID(productID);
		consumeProductList.SetCount(count);
		consumeProductList.SetSum(sum);
		consumeProductList.SetCurrencyID(currencyID);
		std::string filter = consumeProductList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeProductListViewCollection> consumeProductListVector = ormasDal.GetConsumeProductList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == consumeProductListVector.size())
		{
			return false;
		}
		errorMessage = "Consume product list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}