#include "stdafx.h"
#include "LowValueStockChangeLogClass.h"
#include <codecvt>

namespace BusinessLayer
{
	LowValueStockChangeLog::LowValueStockChangeLog(DataLayer::lowValueStockChangeLogCollection sCollection)
	{
		id = std::get<0>(sCollection);
		lowValueStockID = std::get<1>(sCollection);
		otherStocksID = std::get<2>(sCollection);
		count = std::get<3>(sCollection);
		sum = std::get<4>(sCollection);
		statusID = std::get<5>(sCollection);
		currencyID = std::get<6>(sCollection);
		warehouseID = std::get<7>(sCollection);
		logDate = std::get<8>(sCollection);
		userID = std::get<9>(sCollection);
		operationID = std::get<10>(sCollection);
	}

	int LowValueStockChangeLog::GetID()
	{
		return id;
	}

	int LowValueStockChangeLog::GetLowValueStockID()
	{
		return lowValueStockID;
	}

	int LowValueStockChangeLog::GetOtherStocksID()
	{
		return otherStocksID;
	}

	double LowValueStockChangeLog::GetCount()
	{
		return count;
	}

	double LowValueStockChangeLog::GetSum()
	{
		return sum;
	}

	int LowValueStockChangeLog::GetStatusID()
	{
		return statusID;
	}

	int LowValueStockChangeLog::GetCurrencyID()
	{
		return currencyID;
	}

	int LowValueStockChangeLog::GetWarehouseID()
	{
		return warehouseID;
	}

	std::string LowValueStockChangeLog::GetLogDate()
	{
		return logDate;
	}

	int LowValueStockChangeLog::GetUserID()
	{
		return userID;
	}

	int LowValueStockChangeLog::GetOperationID()
	{
		return operationID;
	}

	void LowValueStockChangeLog::SetID(int sID)
	{
		id = sID;
	}

	void LowValueStockChangeLog::SetLowValueStockID(int slvID)
	{
		lowValueStockID = slvID;
	}

	void LowValueStockChangeLog::SetOtherStocksID(int sProductID)
	{
		otherStocksID = sProductID;
	}
	void LowValueStockChangeLog::SetCount(double sCount)
	{
		count = sCount;
	}
	void LowValueStockChangeLog::SetSum(double sSum)
	{
		sum = sSum;
	}
	void LowValueStockChangeLog::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void LowValueStockChangeLog::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void LowValueStockChangeLog::SetWarehouseID(int sWarehouseID)
	{
		warehouseID = sWarehouseID;
	}

	void LowValueStockChangeLog::SetLogDate(std::string date)
	{
		logDate = date;
	}

	void LowValueStockChangeLog::SetUserID(int lUserID)
	{
		userID = lUserID;
	}

	void LowValueStockChangeLog::SetOperationID(int lOperationID)
	{
		operationID = lOperationID;
	}

	bool LowValueStockChangeLog::CreateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lvsID, int osID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sLogDate, int lUserID, int lOperationID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		lowValueStockID = lvsID;
		otherStocksID = osID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		logDate = sLogDate;
		userID = lUserID;
		operationID = lOperationID;
		if (0 != id && ormasDal.CreateLowValueStockChangeLog(id, lowValueStockID, otherStocksID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool LowValueStockChangeLog::CreateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateLowValueStockChangeLog(id, lowValueStockID, otherStocksID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool LowValueStockChangeLog::DeleteLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteLowValueStockChangeLog(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool LowValueStockChangeLog::UpdateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lvsID, int osID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sLogDate, int lUserID, int lOperationID, std::string& errorMessage)
	{
		lowValueStockID = lvsID;
		otherStocksID = osID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		logDate = sLogDate;
		userID = lUserID;
		operationID = lOperationID;
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateLowValueStockChangeLog(id, lowValueStockID, otherStocksID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool LowValueStockChangeLog::UpdateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateLowValueStockChangeLog(id, lowValueStockID, otherStocksID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string LowValueStockChangeLog::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != lowValueStockID || 0 != otherStocksID || 0 != count || 0 != sum || 0 != statusID || 0 != warehouseID || !logDate.empty()
			|| 0 != userID || 0 != operationID)
		{
			return ormasDal.GetFilterForLowValueStockChangeLog(id, lowValueStockID, otherStocksID, count, sum, statusID, currencyID, warehouseID, logDate, userID, operationID);
		}
		return "";
	}

	bool LowValueStockChangeLog::GetLowValueStockChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockChangeLogCollection> lowValueStockChangeLogVector = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		if (0 != lowValueStockChangeLogVector.size())
		{
			id = std::get<0>(lowValueStockChangeLogVector.at(0));
			lowValueStockID = std::get<1>(lowValueStockChangeLogVector.at(0));
			otherStocksID = std::get<2>(lowValueStockChangeLogVector.at(0));
			count = std::get<3>(lowValueStockChangeLogVector.at(0));
			sum = std::get<4>(lowValueStockChangeLogVector.at(0));
			statusID = std::get<5>(lowValueStockChangeLogVector.at(0));
			currencyID = std::get<6>(lowValueStockChangeLogVector.at(0));
			warehouseID = std::get<7>(lowValueStockChangeLogVector.at(0));
			logDate = std::get<8>(lowValueStockChangeLogVector.at(0));
			userID = std::get<9>(lowValueStockChangeLogVector.at(0));
			operationID = std::get<10>(lowValueStockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock ChangeLog with this id";
		}
		return false;
	}

	bool LowValueStockChangeLog::GetLowValueStockChangeLogByOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		otherStocksID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockChangeLogCollection> lowValueStockChangeLogVector = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		if (0 != lowValueStockChangeLogVector.size())
		{
			id = std::get<0>(lowValueStockChangeLogVector.at(0));
			lowValueStockID = std::get<1>(lowValueStockChangeLogVector.at(0));
			otherStocksID = std::get<2>(lowValueStockChangeLogVector.at(0));
			count = std::get<3>(lowValueStockChangeLogVector.at(0));
			sum = std::get<4>(lowValueStockChangeLogVector.at(0));
			statusID = std::get<5>(lowValueStockChangeLogVector.at(0));
			currencyID = std::get<6>(lowValueStockChangeLogVector.at(0));
			warehouseID = std::get<7>(lowValueStockChangeLogVector.at(0));
			logDate = std::get<8>(lowValueStockChangeLogVector.at(0));
			userID = std::get<9>(lowValueStockChangeLogVector.at(0));
			operationID = std::get<10>(lowValueStockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock ChangeLog with this id";
		}
		return false;
	}

	bool LowValueStockChangeLog::GetLowValueStockChangeLogByOtherStocksAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		if (wID <= 0)
			return false;
		otherStocksID = pID;
		warehouseID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockChangeLogCollection> lowValueStockChangeLogVector = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		if (0 != lowValueStockChangeLogVector.size())
		{
			id = std::get<0>(lowValueStockChangeLogVector.at(0));
			lowValueStockID = std::get<1>(lowValueStockChangeLogVector.at(0));
			otherStocksID = std::get<2>(lowValueStockChangeLogVector.at(0));
			count = std::get<3>(lowValueStockChangeLogVector.at(0));
			sum = std::get<4>(lowValueStockChangeLogVector.at(0));
			statusID = std::get<5>(lowValueStockChangeLogVector.at(0));
			currencyID = std::get<6>(lowValueStockChangeLogVector.at(0));
			warehouseID = std::get<7>(lowValueStockChangeLogVector.at(0));
			logDate = std::get<8>(lowValueStockChangeLogVector.at(0));
			userID = std::get<9>(lowValueStockChangeLogVector.at(0));
			operationID = std::get<10>(lowValueStockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock ChangeLog with this other stocks ID and warehouse ID";
		}
		return false;
	}

	bool LowValueStockChangeLog::GetLowValueStockChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		userID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockChangeLogCollection> lowValueStockChangeLogVector = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		if (0 != lowValueStockChangeLogVector.size())
		{
			id = std::get<0>(lowValueStockChangeLogVector.at(0));
			lowValueStockID = std::get<1>(lowValueStockChangeLogVector.at(0));
			otherStocksID = std::get<2>(lowValueStockChangeLogVector.at(0));
			count = std::get<3>(lowValueStockChangeLogVector.at(0));
			sum = std::get<4>(lowValueStockChangeLogVector.at(0));
			statusID = std::get<5>(lowValueStockChangeLogVector.at(0));
			currencyID = std::get<6>(lowValueStockChangeLogVector.at(0));
			warehouseID = std::get<7>(lowValueStockChangeLogVector.at(0));
			logDate = std::get<8>(lowValueStockChangeLogVector.at(0));
			userID = std::get<9>(lowValueStockChangeLogVector.at(0));
			operationID = std::get<10>(lowValueStockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock ChangeLog with this id";
		}
		return false;
	}

	bool LowValueStockChangeLog::GetLowValueStockChangeLogByLowValueStockID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lvsID, std::string& errorMessage)
	{
		if (lvsID <= 0)
			return false;
		lowValueStockID = lvsID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockChangeLogCollection> lowValueStockChangeLogVector = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		if (0 != lowValueStockChangeLogVector.size())
		{
			id = std::get<0>(lowValueStockChangeLogVector.at(0));
			lowValueStockID = std::get<1>(lowValueStockChangeLogVector.at(0));
			otherStocksID = std::get<2>(lowValueStockChangeLogVector.at(0));
			count = std::get<3>(lowValueStockChangeLogVector.at(0));
			sum = std::get<4>(lowValueStockChangeLogVector.at(0));
			statusID = std::get<5>(lowValueStockChangeLogVector.at(0));
			currencyID = std::get<6>(lowValueStockChangeLogVector.at(0));
			warehouseID = std::get<7>(lowValueStockChangeLogVector.at(0));
			logDate = std::get<8>(lowValueStockChangeLogVector.at(0));
			userID = std::get<9>(lowValueStockChangeLogVector.at(0));
			operationID = std::get<10>(lowValueStockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock ChangeLog with this id";
		}
		return false;
	}

	bool LowValueStockChangeLog::GetLowValueStockChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		operationID = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockChangeLogCollection> lowValueStockChangeLogVector = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		if (0 != lowValueStockChangeLogVector.size())
		{
			id = std::get<0>(lowValueStockChangeLogVector.at(0));
			lowValueStockID = std::get<1>(lowValueStockChangeLogVector.at(0));
			otherStocksID = std::get<2>(lowValueStockChangeLogVector.at(0));
			count = std::get<3>(lowValueStockChangeLogVector.at(0));
			sum = std::get<4>(lowValueStockChangeLogVector.at(0));
			statusID = std::get<5>(lowValueStockChangeLogVector.at(0));
			currencyID = std::get<6>(lowValueStockChangeLogVector.at(0));
			warehouseID = std::get<7>(lowValueStockChangeLogVector.at(0));
			logDate = std::get<8>(lowValueStockChangeLogVector.at(0));
			userID = std::get<9>(lowValueStockChangeLogVector.at(0));
			operationID = std::get<10>(lowValueStockChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock ChangeLog with this id";
		}
		return false;
	}

	bool LowValueStockChangeLog::IsEmpty()
	{
		if (0 == id && 0 == count && 0 == lowValueStockID && 0 == sum && 0 == otherStocksID && 0 == statusID && 0 == currencyID && 0 == warehouseID && logDate.empty()
			&& 0 ==  userID && 0 == operationID)
			return true;
		return false;
	}

	void LowValueStockChangeLog::Clear()
	{
		id = 0;
		lowValueStockID = 0;
		count = 0;
		sum = 0;
		otherStocksID = 0;
		statusID = 0;
		currencyID = 0;
		warehouseID = 0;
		logDate.empty();
		userID = 0;
		operationID = 0;
	}

	bool LowValueStockChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lvsID, int osID, double sCount, double sSum,
		int sID, int cID, int wID, std::string sLogDate, int lUserID, int lOperationID, std::string& errorMessage)
	{
		LowValueStockChangeLog lowValueStockChangeLog;
		lowValueStockChangeLog.Clear();
		errorMessage.clear();
		lowValueStockChangeLog.SetLowValueStockID(lvsID);
		lowValueStockChangeLog.SetOtherStocksID(osID);
		lowValueStockChangeLog.SetCount(sCount);
		lowValueStockChangeLog.SetSum(sSum);
		lowValueStockChangeLog.SetStatusID(sID);
		lowValueStockChangeLog.SetCurrencyID(cID);
		lowValueStockChangeLog.SetWarehouseID(wID);
		lowValueStockChangeLog.SetLogDate(sLogDate);
		lowValueStockChangeLog.SetUserID(lUserID);
		lowValueStockChangeLog.SetOperationID(lOperationID);
		std::string filter = lowValueStockChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockChangeLogCollection> lowValueStockChangeLogVector = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == lowValueStockChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Low value stock ChangeLog with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool LowValueStockChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		LowValueStockChangeLog lowValueStockChangeLog;
		lowValueStockChangeLog.Clear();
		errorMessage.clear();
		lowValueStockChangeLog.SetLowValueStockID(lowValueStockID);
		lowValueStockChangeLog.SetOtherStocksID(otherStocksID);
		lowValueStockChangeLog.SetCount(count);
		lowValueStockChangeLog.SetSum(sum);
		lowValueStockChangeLog.SetStatusID(statusID);
		lowValueStockChangeLog.SetCurrencyID(currencyID);
		lowValueStockChangeLog.SetWarehouseID(warehouseID);
		lowValueStockChangeLog.SetLogDate(logDate);
		lowValueStockChangeLog.SetUserID(userID);
		lowValueStockChangeLog.SetOperationID(operationID);
		std::string filter = lowValueStockChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockChangeLogCollection> lowValueStockChangeLogVector = ormasDal.GetLowValueStockChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == lowValueStockChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Low value stock ChangeLog with this parameters are already exist! Please avoid the duplication!";
		return true;
	}


}