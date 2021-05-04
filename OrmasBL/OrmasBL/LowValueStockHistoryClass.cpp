#include "stdafx.h"
#include "LowValueStockHistoryClass.h"
#include <codecvt>

namespace BusinessLayer
{
	LowValueStockHistory::LowValueStockHistory(DataLayer::lowValueStockHistoryCollection sCollection)
	{
		id = std::get<0>(sCollection);
		otherStocksID = std::get<1>(sCollection);
		count = std::get<2>(sCollection);
		sum = std::get<3>(sCollection);
		statusID = std::get<4>(sCollection);
		currencyID = std::get<5>(sCollection);
		warehouseID = std::get<6>(sCollection);
		historyDate = std::get<7>(sCollection);
	}

	int LowValueStockHistory::GetID()
	{
		return id;
	}

	int LowValueStockHistory::GetOtherStocksID()
	{
		return otherStocksID;
	}

	double LowValueStockHistory::GetCount()
	{
		return count;
	}

	double LowValueStockHistory::GetSum()
	{
		return sum;
	}

	int LowValueStockHistory::GetStatusID()
	{
		return statusID;
	}

	int LowValueStockHistory::GetCurrencyID()
	{
		return currencyID;
	}

	int LowValueStockHistory::GetWarehouseID()
	{
		return warehouseID;
	}

	std::string LowValueStockHistory::GetHistoryDate()
	{
		return historyDate;
	}

	void LowValueStockHistory::SetID(int sID)
	{
		id = sID;
	}

	void LowValueStockHistory::SetOtherStocksID(int sProductID)
	{
		otherStocksID = sProductID;
	}
	void LowValueStockHistory::SetCount(double sCount)
	{
		count = sCount;
	}
	void LowValueStockHistory::SetSum(double sSum)
	{
		sum = sSum;
	}
	void LowValueStockHistory::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void LowValueStockHistory::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void LowValueStockHistory::SetWarehouseID(int sWarehouseID)
	{
		warehouseID = sWarehouseID;
	}

	void LowValueStockHistory::SetHistoryDate(std::string date)
	{
		historyDate = date;
	}

	bool LowValueStockHistory::CreateLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sHistoryDate, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		otherStocksID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		historyDate = sHistoryDate;
		if (0 != id && ormasDal.CreateLowValueStockHistory(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, historyDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool LowValueStockHistory::CreateLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateLowValueStockHistory(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, historyDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool LowValueStockHistory::DeleteLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteLowValueStockHistory(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool LowValueStockHistory::UpdateLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sHistoryDate, std::string& errorMessage)
	{
		otherStocksID = pID;
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
		if (0 != id && ormasDal.UpdateLowValueStockHistory(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, historyDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool LowValueStockHistory::UpdateLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateLowValueStockHistory(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, historyDate, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string LowValueStockHistory::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != otherStocksID || 0 != count || 0 != sum || 0 != statusID || 0 != warehouseID || !historyDate.empty())
		{
			return ormasDal.GetFilterForLowValueStockHistory(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, historyDate);
		}
		return "";
	}

	bool LowValueStockHistory::GetLowValueStockHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockHistoryViewCollection> lowValueStockHistoryVector = ormasDal.GetLowValueStockHistory(errorMessage, filter);
		if (0 != lowValueStockHistoryVector.size())
		{
			id = std::get<0>(lowValueStockHistoryVector.at(0));
			count = std::get<6>(lowValueStockHistoryVector.at(0));
			sum = std::get<7>(lowValueStockHistoryVector.at(0));
			otherStocksID = std::get<12>(lowValueStockHistoryVector.at(0));
			statusID = std::get<13>(lowValueStockHistoryVector.at(0));
			currencyID = std::get<14>(lowValueStockHistoryVector.at(0));
			warehouseID = std::get<15>(lowValueStockHistoryVector.at(0));
			historyDate = std::get<16>(lowValueStockHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock history with this id";
		}
		return false;
	}

	bool LowValueStockHistory::GetLowValueStockHistoryByOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		otherStocksID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockHistoryViewCollection> lowValueStockHistoryVector = ormasDal.GetLowValueStockHistory(errorMessage, filter);
		if (0 != lowValueStockHistoryVector.size())
		{
			id = std::get<0>(lowValueStockHistoryVector.at(0));
			count = std::get<6>(lowValueStockHistoryVector.at(0));
			sum = std::get<7>(lowValueStockHistoryVector.at(0));
			otherStocksID = std::get<12>(lowValueStockHistoryVector.at(0));
			statusID = std::get<13>(lowValueStockHistoryVector.at(0));
			currencyID = std::get<14>(lowValueStockHistoryVector.at(0));
			warehouseID = std::get<15>(lowValueStockHistoryVector.at(0));
			historyDate = std::get<16>(lowValueStockHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock history with this id";
		}
		return false;
	}

	bool LowValueStockHistory::GetLowValueStockHistoryByOtherStocksAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		if (wID <= 0)
			return false;
		otherStocksID = pID;
		warehouseID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockHistoryViewCollection> lowValueStockHistoryVector = ormasDal.GetLowValueStockHistory(errorMessage, filter);
		if (0 != lowValueStockHistoryVector.size())
		{
			id = std::get<0>(lowValueStockHistoryVector.at(0));
			count = std::get<6>(lowValueStockHistoryVector.at(0));
			sum = std::get<7>(lowValueStockHistoryVector.at(0));
			otherStocksID = std::get<12>(lowValueStockHistoryVector.at(0));
			statusID = std::get<13>(lowValueStockHistoryVector.at(0));
			currencyID = std::get<14>(lowValueStockHistoryVector.at(0));
			warehouseID = std::get<15>(lowValueStockHistoryVector.at(0));
			historyDate = std::get<16>(lowValueStockHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock history with this other stocks ID and warehouse ID";
		}
		return false;
	}

	bool LowValueStockHistory::IsEmpty()
	{
		if (0 == id && 0 == count && 0 == sum && 0 == otherStocksID && 0 == statusID && 0 == currencyID && 0 == warehouseID && historyDate.empty())
			return true;
		return false;
	}

	void LowValueStockHistory::Clear()
	{
		id = 0;
		count = 0;
		sum = 0;
		otherStocksID = 0;
		statusID = 0;
		currencyID = 0;
		warehouseID = 0;
		historyDate.empty();
	}

	bool LowValueStockHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		LowValueStockHistory lowValueStockHistory;
		lowValueStockHistory.Clear();
		errorMessage.clear();
		lowValueStockHistory.SetOtherStocksID(pID);
		lowValueStockHistory.SetWarehouseID(wID);
		std::string filter = lowValueStockHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockHistoryViewCollection> lowValueStockHistoryVector = ormasDal.GetLowValueStockHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == lowValueStockHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Low value stock history with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool LowValueStockHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		LowValueStockHistory lowValueStockHistory;
		lowValueStockHistory.Clear();
		errorMessage.clear();
		lowValueStockHistory.SetOtherStocksID(otherStocksID);
		lowValueStockHistory.SetWarehouseID(warehouseID);
		std::string filter = lowValueStockHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockHistoryViewCollection> lowValueStockHistoryVector = ormasDal.GetLowValueStockHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == lowValueStockHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Low value stock history with this parameters are already exist! Please avoid the duplication!";
		return true;
	}


}