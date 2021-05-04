#include "stdafx.h"
#include "StockTransferListClass.h"
#include "ProductClass.h"
#include "EntryClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyClass.h"


namespace BusinessLayer
{
	StockTransferList::StockTransferList(DataLayer::stockTransferListCollection rListCollection)
	{
		id = std::get<0>(rListCollection);
		stockTransferID = std::get<1>(rListCollection);
		productID = std::get<2>(rListCollection);
		count = std::get<3>(rListCollection);
		sum = std::get<4>(rListCollection);
		statusID = std::get<5>(rListCollection);
		currencyID = std::get<6>(rListCollection);
	}

	int StockTransferList::GetID()
	{
		return id;
	}

	int StockTransferList::GetStockTransferID()
	{
		return stockTransferID;
	}

	int StockTransferList::GetProductID()
	{
		return productID;
	}

	double StockTransferList::GetCount()
	{
		return count;
	}

	double StockTransferList::GetSum()
	{
		return sum;
	}

	int StockTransferList::GetStatusID()
	{
		return statusID;
	}

	int StockTransferList::GetCurrencyID()
	{
		return currencyID;
	}

	void StockTransferList::SetID(int rID)
	{
		id = rID;
	}
	void StockTransferList::SetStockTransferID(int rstockTransferID)
	{
		stockTransferID = rstockTransferID;
	}
	void StockTransferList::SetProductID(int rProductID)
	{
		productID = rProductID;
	}
	void StockTransferList::SetCount(double rCount)
	{
		count = rCount;
	}
	void StockTransferList::SetSum(double rSum)
	{
		sum = rSum;
	}
	void StockTransferList::SetStatusID(int rStatusID)
	{
		statusID = rStatusID;
	}
	void StockTransferList::SetCurrencyID(int rCurrencyID)
	{
		currencyID = rCurrencyID;
	}

	bool StockTransferList::CreateStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		stockTransferID = rID;
		productID = pID;
		count = rlCount;
		sum = rlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateStockTransferList(id, stockTransferID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockTransferList::CreateStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateStockTransferList(id, stockTransferID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockTransferList::DeleteStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInStockTransferList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool StockTransferList::DeleteListByStockTransferID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		stockTransferID = oID;
		if (ormasDal.DeleteListByStockTransferID(stockTransferID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool StockTransferList::UpdateStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
		int sID, int cID, std::string& errorMessage)
	{
		stockTransferID = rID;
		productID = pID;
		count = rlCount;
		sum = rlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateStockTransferList(id, stockTransferID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockTransferList::UpdateStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateStockTransferList(id, stockTransferID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string StockTransferList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != stockTransferID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForStockTransferList(id, stockTransferID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool StockTransferList::GetStockTransferListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> stockTransferListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (0 != stockTransferListVector.size())
		{

			id = std::get<0>(stockTransferListVector.at(0));
			stockTransferID = std::get<1>(stockTransferListVector.at(0));
			count = std::get<7>(stockTransferListVector.at(0));
			sum = std::get<8>(stockTransferListVector.at(0));
			productID = std::get<11>(stockTransferListVector.at(0));
			statusID = std::get<12>(stockTransferListVector.at(0));
			currencyID = std::get<13>(stockTransferListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find stock transfer list with this id";
		}
		return false;
	}

	bool StockTransferList::IsEmpty()
	{
		if (0 == id && 0 == stockTransferID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void StockTransferList::Clear()
	{
		id = 0;
		stockTransferID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool StockTransferList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
		int cID, std::string& errorMessage)
	{
		StockTransferList stockTransferList;
		stockTransferList.Clear();
		errorMessage.clear();
		stockTransferList.SetStockTransferID(rID);
		stockTransferList.SetProductID(pID);
		stockTransferList.SetCount(rlCount);
		stockTransferList.SetSum(rlSum);
		stockTransferList.SetCurrencyID(cID);
		std::string filter = stockTransferList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> StockTransferListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == StockTransferListVector.size())
		{
			return false;
		}
		errorMessage = "Stock transfer list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool StockTransferList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		StockTransferList stockTransferList;
		stockTransferList.Clear();
		errorMessage.clear();
		stockTransferList.SetStockTransferID(stockTransferID);
		stockTransferList.SetProductID(productID);
		stockTransferList.SetCount(count);
		stockTransferList.SetSum(sum);
		stockTransferList.SetCurrencyID(currencyID);
		std::string filter = stockTransferList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> StockTransferListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == StockTransferListVector.size())
		{
			return false;
		}
		errorMessage = "Stack transfer list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}