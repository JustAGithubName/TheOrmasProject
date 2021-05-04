#include "stdafx.h"
#include "StockChangeLogClass.h"
#include <codecvt>

namespace BusinessLayer
{
	StockChangeLog::StockChangeLog(DataLayer::stockChangeLogCollection sCollection)
	{
		id = std::get<0>(sCollection);
		stockID = std::get<1>(sCollection);
		productID = std::get<2>(sCollection);
		count = std::get<3>(sCollection);
		sum = std::get<4>(sCollection);
		statusID = std::get<5>(sCollection);
		currencyID = std::get<6>(sCollection);
		warehouseID = std::get<7>(sCollection);
		logDate = std::get<8>(sCollection);
		userID = std::get<9>(sCollection);
		operationID = std::get<10>(sCollection);
	}

	int StockChangeLog::GetID()
	{
		return id;
	}
	int StockChangeLog::GetStockID()
	{
		return stockID;
	}

	int StockChangeLog::GetProductID()
	{
		return productID;
	}

	double StockChangeLog::GetCount()
	{
		return count;
	}

	double StockChangeLog::GetSum()
	{
		return sum;
	}

	int StockChangeLog::GetStatusID()
	{
		return statusID;
	}

	int StockChangeLog::GetCurrencyID()
	{
		return currencyID;
	}

	int StockChangeLog::GetWarehouseID()
	{
		return warehouseID;
	}

	std::string StockChangeLog::GetLogDate()
	{
		return logDate;
	}
	int StockChangeLog::GetUserID()
	{
		return userID;
	}
	int StockChangeLog::GetOperationID()
	{
		return operationID;
	}

	void StockChangeLog::SetID(int sID)
	{
		id = sID;
	}
	void StockChangeLog::SetStockID(int sStockID)
	{
		stockID = sStockID;
	}
	void StockChangeLog::SetProductID(int sProductID)
	{
		productID = sProductID;
	}
	void StockChangeLog::SetCount(double sCount)
	{
		count = sCount;
	}
	void StockChangeLog::SetSum(double sSum)
	{
		sum = sSum;
	}
	void StockChangeLog::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void StockChangeLog::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void StockChangeLog::SetWarehouseID(int sWarehouseID)
	{
		warehouseID = sWarehouseID;
	}

	void StockChangeLog::SetUserID(int sUserID)
	{
		userID = sUserID;
	}

	void StockChangeLog::SetLogDate(std::string lDate)
	{
		logDate = lDate;
	}

	void StockChangeLog::SetOperationID(int sOperationID)
	{
		operationID = sOperationID;
	}

	bool StockChangeLog::CreateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sStockID, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sLogDate, int sUserID, int sOperationID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		stockID = sStockID;
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		logDate = sLogDate;
		userID = sUserID;
		operationID = sOperationID;
		if (0 != id && ormasDal.CreateStockChangeLog(id, stockID, productID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockChangeLog::CreateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateStockChangeLog(id, stockID, productID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockChangeLog::DeleteStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteStockChangeLog(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool StockChangeLog::UpdateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sStockID, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sLogDate, int sUserID, int sOperationID, std::string& errorMessage)
	{
		stockID = sStockID;
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		logDate = sLogDate;
		userID = sUserID;
		operationID = sOperationID;
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateStockChangeLog(id, stockID, productID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockChangeLog::UpdateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateStockChangeLog(id, stockID, productID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string StockChangeLog::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != stockID || 0 != productID || 0 != count || 0 != sum || 0 != statusID || 0 != warehouseID 
			|| !logDate.empty() || 0 != userID || 0 != operationID)
		{
			return ormasDal.GetFilterForStockChangeLog(id,stockID, productID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID);
		}
		return "";
	}

	bool StockChangeLog::GetStockChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockChangeLogCollection> stockChangeLogVector = ormasDal.GetStockChangeLog(errorMessage, filter);
		if (0 != stockChangeLogVector.size())
		{
			id = std::get<0>(stockChangeLogVector.at(0));
			stockID = std::get<1>(stockChangeLogVector.at(0));
			productID = std::get<2>(stockChangeLogVector.at(0));
			count = std::get<3>(stockChangeLogVector.at(0));
			sum = std::get<4>(stockChangeLogVector.at(0));
			statusID = std::get<5>(stockChangeLogVector.at(0));
			currencyID = std::get<6>(stockChangeLogVector.at(0));
			warehouseID = std::get<7>(stockChangeLogVector.at(0));
			logDate = std::get<8>(stockChangeLogVector.at(0));
			userID = std::get<9>(stockChangeLogVector.at(0));
			operationID = std::get<10>(stockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Stock change log with this id";
		}
		return false;
	}

	bool StockChangeLog::GetStockChangeLogByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockChangeLogCollection> stockChangeLogVector = ormasDal.GetStockChangeLog(errorMessage, filter);
		if (0 != stockChangeLogVector.size())
		{
			id = std::get<0>(stockChangeLogVector.at(0));
			stockID = std::get<1>(stockChangeLogVector.at(0));
			productID = std::get<2>(stockChangeLogVector.at(0));
			count = std::get<3>(stockChangeLogVector.at(0));
			sum = std::get<4>(stockChangeLogVector.at(0));
			statusID = std::get<5>(stockChangeLogVector.at(0));
			currencyID = std::get<6>(stockChangeLogVector.at(0));
			warehouseID = std::get<7>(stockChangeLogVector.at(0));
			logDate = std::get<8>(stockChangeLogVector.at(0));
			userID = std::get<9>(stockChangeLogVector.at(0));
			operationID = std::get<10>(stockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Stock change log with this id";
		}
		return false;
	}

	bool StockChangeLog::GetStockChangeLogByProductAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		if (wID <= 0)
			return false;
		productID = pID;
		warehouseID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockChangeLogCollection> stockChangeLogVector = ormasDal.GetStockChangeLog(errorMessage, filter);
		if (0 != stockChangeLogVector.size())
		{
			id = std::get<0>(stockChangeLogVector.at(0));
			stockID = std::get<1>(stockChangeLogVector.at(0));
			productID = std::get<2>(stockChangeLogVector.at(0));
			count = std::get<3>(stockChangeLogVector.at(0));
			sum = std::get<4>(stockChangeLogVector.at(0));
			statusID = std::get<5>(stockChangeLogVector.at(0));
			currencyID = std::get<6>(stockChangeLogVector.at(0));
			warehouseID = std::get<7>(stockChangeLogVector.at(0));
			logDate = std::get<8>(stockChangeLogVector.at(0));
			userID = std::get<9>(stockChangeLogVector.at(0));
			operationID = std::get<10>(stockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Stock change log with this id";
		}
		return false;
	}

	bool StockChangeLog::GetStockChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		userID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockChangeLogCollection> stockChangeLogVector = ormasDal.GetStockChangeLog(errorMessage, filter);
		if (0 != stockChangeLogVector.size())
		{
			id = std::get<0>(stockChangeLogVector.at(0));
			stockID = std::get<1>(stockChangeLogVector.at(0));
			productID = std::get<2>(stockChangeLogVector.at(0));
			count = std::get<3>(stockChangeLogVector.at(0));
			sum = std::get<4>(stockChangeLogVector.at(0));
			statusID = std::get<5>(stockChangeLogVector.at(0));
			currencyID = std::get<6>(stockChangeLogVector.at(0));
			warehouseID = std::get<7>(stockChangeLogVector.at(0));
			logDate = std::get<8>(stockChangeLogVector.at(0));
			userID = std::get<9>(stockChangeLogVector.at(0));
			operationID = std::get<10>(stockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Stock change log with this id";
		}
		return false;
	}

	bool StockChangeLog::GetStockChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		operationID = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockChangeLogCollection> stockChangeLogVector = ormasDal.GetStockChangeLog(errorMessage, filter);
		if (0 != stockChangeLogVector.size())
		{
			id = std::get<0>(stockChangeLogVector.at(0));
			stockID = std::get<1>(stockChangeLogVector.at(0));
			productID = std::get<2>(stockChangeLogVector.at(0));
			count = std::get<3>(stockChangeLogVector.at(0));
			sum = std::get<4>(stockChangeLogVector.at(0));
			statusID = std::get<5>(stockChangeLogVector.at(0));
			currencyID = std::get<6>(stockChangeLogVector.at(0));
			warehouseID = std::get<7>(stockChangeLogVector.at(0));
			logDate = std::get<8>(stockChangeLogVector.at(0));
			userID = std::get<9>(stockChangeLogVector.at(0));
			operationID = std::get<10>(stockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Stock change log with this id";
		}
		return false;
	}

	bool StockChangeLog::GetStockChangeLogByStockID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		stockID = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockChangeLogCollection> stockChangeLogVector = ormasDal.GetStockChangeLog(errorMessage, filter);
		if (0 != stockChangeLogVector.size())
		{
			id = std::get<0>(stockChangeLogVector.at(0));
			stockID = std::get<1>(stockChangeLogVector.at(0));
			productID = std::get<2>(stockChangeLogVector.at(0));
			count = std::get<3>(stockChangeLogVector.at(0));
			sum = std::get<4>(stockChangeLogVector.at(0));
			statusID = std::get<5>(stockChangeLogVector.at(0));
			currencyID = std::get<6>(stockChangeLogVector.at(0));
			warehouseID = std::get<7>(stockChangeLogVector.at(0));
			logDate = std::get<8>(stockChangeLogVector.at(0));
			userID = std::get<9>(stockChangeLogVector.at(0));
			operationID = std::get<10>(stockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Stock change log with this id";
		}
		return false;
	}


	bool StockChangeLog::IsEmpty()
	{
		if (0 == id && 0 == stockID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID && 
			0 == warehouseID && logDate.empty() && 0== userID && 0==operationID)
			return true;
		return false;
	}

	void StockChangeLog::Clear()
	{
		id = 0;
		stockID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
		warehouseID = 0;
		logDate.empty();
		userID = 0;
		operationID = 0;
	}

	bool StockChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sStockID, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sLogDate, int sUserID, int sOperationID, std::string& errorMessage)
	{
		StockChangeLog stockChangeLog;
		stockChangeLog.Clear();
		errorMessage.clear();
		stockChangeLog.SetStockID(sStockID);
		stockChangeLog.SetProductID(pID);
		stockChangeLog.SetCount(sCount);
		stockChangeLog.SetSum(sSum);
		stockChangeLog.SetStatusID(sID);
		stockChangeLog.SetCurrencyID(cID);
		stockChangeLog.SetWarehouseID(wID);
		stockChangeLog.SetLogDate(sLogDate);
		stockChangeLog.SetUserID(sUserID);
		stockChangeLog.SetOperationID(sOperationID);
		std::string filter = stockChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockChangeLogCollection> stockChangeLogVector = ormasDal.GetStockChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == stockChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Stock change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool StockChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		StockChangeLog stockChangeLog;
		stockChangeLog.Clear();
		errorMessage.clear();
		stockChangeLog.SetStockID(stockID);
		stockChangeLog.SetProductID(productID);
		stockChangeLog.SetCount(count);
		stockChangeLog.SetSum(sum);
		stockChangeLog.SetStatusID(statusID);
		stockChangeLog.SetCurrencyID(currencyID);
		stockChangeLog.SetWarehouseID(warehouseID);
		stockChangeLog.SetLogDate(logDate);
		stockChangeLog.SetUserID(userID);
		stockChangeLog.SetOperationID(operationID);
		std::string filter = stockChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockChangeLogCollection> stockChangeLogVector = ormasDal.GetStockChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == stockChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Stock change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}


}