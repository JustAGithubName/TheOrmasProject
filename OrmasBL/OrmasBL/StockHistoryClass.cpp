#include "stdafx.h"
#include "StockHistoryClass.h"
#include <codecvt>

namespace BusinessLayer
{
	StockHistory::StockHistory(DataLayer::stockHistoryCollection sCollection)
	{
		id = std::get<0>(sCollection);
		productID = std::get<1>(sCollection);
		count = std::get<2>(sCollection);
		sum = std::get<3>(sCollection);
		statusID = std::get<4>(sCollection);
		currencyID = std::get<5>(sCollection);
		warehouseID = std::get<6>(sCollection);
		historyDate = std::get<7>(sCollection);
	}

	int StockHistory::GetID()
	{
		return id;
	}

	int StockHistory::GetProductID()
	{
		return productID;
	}

	double StockHistory::GetCount()
	{
		return count;
	}

	double StockHistory::GetSum()
	{
		return sum;
	}

	int StockHistory::GetStatusID()
	{
		return statusID;
	}

	int StockHistory::GetCurrencyID()
	{
		return currencyID;
	}

	int StockHistory::GetWarehouseID()
	{
		return warehouseID;
	}

	std::string StockHistory::GetHistoryDate()
	{
		return historyDate;
	}

	void StockHistory::SetID(int sID)
	{
		id = sID;
	}

	void StockHistory::SetProductID(int sProductID)
	{
		productID = sProductID;
	}
	void StockHistory::SetCount(double sCount)
	{
		count = sCount;
	}
	void StockHistory::SetSum(double sSum)
	{
		sum = sSum;
	}
	void StockHistory::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void StockHistory::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void StockHistory::SetWarehouseID(int sWarehouseID)
	{
		warehouseID = sWarehouseID;
	}

	void StockHistory::SetHistoryDate(std::string date)
	{
		historyDate = date;
	}

	bool StockHistory::CreateStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sHistoryDate, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		historyDate = sHistoryDate;
		if (0 != id && ormasDal.CreateStockHistory(id, productID, count, sum, statusID, currencyID, warehouseID, historyDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockHistory::CreateStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateStockHistory(id, productID, count, sum, statusID, currencyID, warehouseID, historyDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockHistory::DeleteStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteStockHistory(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool StockHistory::UpdateStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sHistoryDate, std::string& errorMessage)
	{
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		historyDate = sHistoryDate;
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateStockHistory(id, productID, count, sum, statusID, currencyID, warehouseID, historyDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockHistory::UpdateStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateStockHistory(id, productID, count, sum, statusID, currencyID, warehouseID, historyDate, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string StockHistory::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != count || 0 != sum || 0 != statusID || 0 != warehouseID || !historyDate.empty()) 
		{
			return ormasDal.GetFilterForStockHistory(id, productID, count, sum, statusID, currencyID, warehouseID, historyDate);
		}
		return "";
	}

	bool StockHistory::GetStockHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockHistoryViewCollection> StockHistoryVector = ormasDal.GetStockHistory(errorMessage, filter);
		if (0 != StockHistoryVector.size())
		{
			id = std::get<0>(StockHistoryVector.at(0));
			count = std::get<6>(StockHistoryVector.at(0));
			sum = std::get<7>(StockHistoryVector.at(0));
			productID = std::get<12>(StockHistoryVector.at(0));
			statusID = std::get<13>(StockHistoryVector.at(0));
			currencyID = std::get<14>(StockHistoryVector.at(0));
			warehouseID = std::get<15>(StockHistoryVector.at(0));
			historyDate = std::get<16>(StockHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find StockHistory with this id";
		}
		return false;
	}

	bool StockHistory::GetStockHistoryByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockHistoryViewCollection> StockHistoryVector = ormasDal.GetStockHistory(errorMessage, filter);
		if (0 != StockHistoryVector.size())
		{
			id = std::get<0>(StockHistoryVector.at(0));
			count = std::get<6>(StockHistoryVector.at(0));
			sum = std::get<7>(StockHistoryVector.at(0));
			productID = std::get<12>(StockHistoryVector.at(0));
			statusID = std::get<13>(StockHistoryVector.at(0));
			currencyID = std::get<14>(StockHistoryVector.at(0));
			warehouseID = std::get<15>(StockHistoryVector.at(0));
			historyDate = std::get<16>(StockHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find StockHistory with this id";
		}
		return false;
	}

	bool StockHistory::GetStockHistoryByProductAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		if (wID <= 0)
			return false;
		productID = pID;
		warehouseID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockHistoryViewCollection> StockHistoryVector = ormasDal.GetStockHistory(errorMessage, filter);
		if (0 != StockHistoryVector.size())
		{
			id = std::get<0>(StockHistoryVector.at(0));
			count = std::get<6>(StockHistoryVector.at(0));
			sum = std::get<7>(StockHistoryVector.at(0));
			productID = std::get<12>(StockHistoryVector.at(0));
			statusID = std::get<13>(StockHistoryVector.at(0));
			currencyID = std::get<14>(StockHistoryVector.at(0));
			warehouseID = std::get<15>(StockHistoryVector.at(0));
			historyDate = std::get<16>(StockHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find StockHistory with this product ID and warehouse ID";
		}
		return false;
	}

	bool StockHistory::IsEmpty()
	{
		if (0 == id && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID && 0 == warehouseID && historyDate.empty())
			return true;
		return false;
	}

	void StockHistory::Clear()
	{
		id = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
		warehouseID = 0;
		historyDate.empty();
	}

	bool StockHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		StockHistory StockHistory;
		StockHistory.Clear();
		errorMessage.clear();
		StockHistory.SetProductID(pID);
		StockHistory.SetWarehouseID(wID);
		std::string filter = StockHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockHistoryViewCollection> StockHistoryVector = ormasDal.GetStockHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == StockHistoryVector.size())
		{
			return false;
		}
		errorMessage = "StockHistory with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool StockHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		StockHistory StockHistory;
		StockHistory.Clear();
		errorMessage.clear();
		StockHistory.SetProductID(productID);
		StockHistory.SetWarehouseID(warehouseID);
		std::string filter = StockHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockHistoryViewCollection> StockHistoryVector = ormasDal.GetStockHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == StockHistoryVector.size())
		{
			return false;
		}
		errorMessage = "StockHistory with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	
}