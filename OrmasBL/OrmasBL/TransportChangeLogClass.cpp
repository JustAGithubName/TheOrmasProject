#include "stdafx.h"
#include "TransportChangeLogClass.h"
#include <codecvt>

namespace BusinessLayer
{
	TransportChangeLog::TransportChangeLog(DataLayer::transportChangeLogCollection sCollection)
	{
		id = std::get<0>(sCollection);
		transportID = std::get<1>(sCollection);
		productID = std::get<2>(sCollection);
		count = std::get<3>(sCollection);
		sum = std::get<4>(sCollection);
		statusID = std::get<5>(sCollection);
		currencyID = std::get<6>(sCollection);
		logDate = std::get<7>(sCollection);
		userID = std::get<8>(sCollection);
		operationID = std::get<9>(sCollection);
	}

	int TransportChangeLog::GetID()
	{
		return id;
	}

	int TransportChangeLog::GetProductID()
	{
		return productID;
	}

	double TransportChangeLog::GetCount()
	{
		return count;
	}

	double TransportChangeLog::GetSum()
	{
		return sum;
	}

	int TransportChangeLog::GetStatusID()
	{
		return statusID;
	}

	int TransportChangeLog::GetCurrencyID()
	{
		return currencyID;
	}

	int TransportChangeLog::GetTransportID()
	{
		return transportID;
	}

	std::string TransportChangeLog::GetLogDate()
	{
		return logDate;
	}

	int TransportChangeLog::GetUserID()
	{
		return userID;
	}

	int TransportChangeLog::GetOperationID()
	{
		return operationID;
	}

	void TransportChangeLog::SetID(int sID)
	{
		id = sID;
	}

	void TransportChangeLog::SetProductID(int sProductID)
	{
		productID = sProductID;
	}
	void TransportChangeLog::SetCount(double sCount)
	{
		count = sCount;
	}
	void TransportChangeLog::SetSum(double sSum)
	{
		sum = sSum;
	}
	void TransportChangeLog::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void TransportChangeLog::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void TransportChangeLog::SetTransportID(int stransportID)
	{
		transportID = stransportID;
	}

	void TransportChangeLog::SetLogDate(std::string fDate)
	{
		logDate = fDate;
	}

	void TransportChangeLog::SetUserID(int tUserID)
	{
		userID = tUserID;
	}

	void TransportChangeLog::SetOperationID(int tOperationID)
	{
		operationID = tOperationID;
	}

	bool TransportChangeLog::CreateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
		int sID, int cID, std::string sLogDate, int tUserID, int tOperationID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		transportID = tID;
		logDate = sLogDate;
		userID = tUserID;
		operationID = tOperationID;
		if (0 != id && ormasDal.CreateTransportChangeLog(id, transportID, productID, count, sum, statusID, currencyID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool TransportChangeLog::CreateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateTransportChangeLog(id, transportID, productID, count, sum, statusID, currencyID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool TransportChangeLog::DeleteTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteTransportChangeLog(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool TransportChangeLog::UpdateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
		int sID, int cID, std::string sLogDate, int tUserID, int tOperationID, std::string& errorMessage)
	{
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		transportID = tID;
		logDate = sLogDate;
		userID = tUserID;
		operationID = tOperationID;
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateTransportChangeLog(id, transportID, productID, count, sum, statusID, currencyID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool TransportChangeLog::UpdateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateTransportChangeLog(id, transportID, productID, count, sum, statusID, currencyID, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string TransportChangeLog::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != count || 0 != sum || 0 != statusID || 0 != transportID || !logDate.empty() 
			|| 0 != userID || 0 != operationID)
		{
			return ormasDal.GetFilterForTransportChangeLog(id, transportID, productID, count, sum, statusID, currencyID, logDate, 
				userID, operationID);
		}
		return "";
	}

	std::string TransportChangeLog::GenerateFilterForDateLess(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != count || 0 != sum || 0 != statusID || 0 != transportID || !logDate.empty()
			|| 0 != userID || 0 != operationID)
		{
			return ormasDal.GetFilterForTransportChangeLogForDateLess(id, transportID, productID, count, sum, statusID, currencyID, logDate,
				userID, operationID);
		}
		return "";
	}

	std::string TransportChangeLog::GenerateFilterForPeriod(DataLayer::OrmasDal& ormasDal, std::string fromDate, std::string tillDate)
	{
		if (0 != id || 0 != productID || 0 != count || 0 != sum || 0 != statusID || 0 != transportID || !logDate.empty()
			|| 0 != userID || 0 != operationID)
		{
			return ormasDal.GetFilterForTransportChangeLogForPeriod(id, transportID, productID, count, sum, statusID, currencyID, logDate,
				userID, operationID, fromDate, tillDate);
		}
		return "";
	}

	bool TransportChangeLog::GetTransportChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportChangeLogCollection> transportChangeLogVector = ormasDal.GetTransportChangeLog(errorMessage, filter);
		if (0 != transportChangeLogVector.size())
		{
			id = std::get<0>(transportChangeLogVector.at(0));
			transportID = std::get<1>(transportChangeLogVector.at(0));
			productID = std::get<2>(transportChangeLogVector.at(0));
			count = std::get<3>(transportChangeLogVector.at(0));
			sum = std::get<4>(transportChangeLogVector.at(0));
			statusID = std::get<5>(transportChangeLogVector.at(0));
			currencyID = std::get<6>(transportChangeLogVector.at(0));
			logDate = std::get<7>(transportChangeLogVector.at(0));
			userID = std::get<8>(transportChangeLogVector.at(0));
			operationID = std::get<9>(transportChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find TransportChangeLog with this id";
		}
		return false;
	}

	bool TransportChangeLog::GetTransportChangeLogByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportChangeLogCollection> transportChangeLogVector = ormasDal.GetTransportChangeLog(errorMessage, filter);
		if (0 != transportChangeLogVector.size())
		{
			id = std::get<0>(transportChangeLogVector.at(0));
			transportID = std::get<1>(transportChangeLogVector.at(0));
			productID = std::get<2>(transportChangeLogVector.at(0));
			count = std::get<3>(transportChangeLogVector.at(0));
			sum = std::get<4>(transportChangeLogVector.at(0));
			statusID = std::get<5>(transportChangeLogVector.at(0));
			currencyID = std::get<6>(transportChangeLogVector.at(0));
			logDate = std::get<7>(transportChangeLogVector.at(0));
			userID = std::get<8>(transportChangeLogVector.at(0));
			operationID = std::get<9>(transportChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find TransportChangeLog with this id";
		}
		return false;;
	}

	bool TransportChangeLog::GetTransportChangeLogByProductAndtransportID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		if (wID <= 0)
			return false;
		productID = pID;
		transportID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportChangeLogCollection> transportChangeLogVector = ormasDal.GetTransportChangeLog(errorMessage, filter);
		if (0 != transportChangeLogVector.size())
		{
			id = std::get<0>(transportChangeLogVector.at(0));
			transportID = std::get<1>(transportChangeLogVector.at(0));
			productID = std::get<2>(transportChangeLogVector.at(0));
			count = std::get<3>(transportChangeLogVector.at(0));
			sum = std::get<4>(transportChangeLogVector.at(0));
			statusID = std::get<5>(transportChangeLogVector.at(0));
			currencyID = std::get<6>(transportChangeLogVector.at(0));
			logDate = std::get<7>(transportChangeLogVector.at(0));
			userID = std::get<8>(transportChangeLogVector.at(0));
			operationID = std::get<9>(transportChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find TransportChangeLog with this id";
		}
		return false;
	}

	bool TransportChangeLog::GetTransportChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		userID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportChangeLogCollection> transportChangeLogVector = ormasDal.GetTransportChangeLog(errorMessage, filter);
		if (0 != transportChangeLogVector.size())
		{
			id = std::get<0>(transportChangeLogVector.at(0));
			transportID = std::get<1>(transportChangeLogVector.at(0));
			productID = std::get<2>(transportChangeLogVector.at(0));
			count = std::get<3>(transportChangeLogVector.at(0));
			sum = std::get<4>(transportChangeLogVector.at(0));
			statusID = std::get<5>(transportChangeLogVector.at(0));
			currencyID = std::get<6>(transportChangeLogVector.at(0));
			logDate = std::get<7>(transportChangeLogVector.at(0));
			userID = std::get<8>(transportChangeLogVector.at(0));
			operationID = std::get<9>(transportChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find TransportChangeLog with this id";
		}
		return false;;
	}

	bool TransportChangeLog::GetTransportChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		operationID = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportChangeLogCollection> transportChangeLogVector = ormasDal.GetTransportChangeLog(errorMessage, filter);
		if (0 != transportChangeLogVector.size())
		{
			id = std::get<0>(transportChangeLogVector.at(0));
			transportID = std::get<1>(transportChangeLogVector.at(0));
			productID = std::get<2>(transportChangeLogVector.at(0));
			count = std::get<3>(transportChangeLogVector.at(0));
			sum = std::get<4>(transportChangeLogVector.at(0));
			statusID = std::get<5>(transportChangeLogVector.at(0));
			currencyID = std::get<6>(transportChangeLogVector.at(0));
			logDate = std::get<7>(transportChangeLogVector.at(0));
			userID = std::get<8>(transportChangeLogVector.at(0));
			operationID = std::get<9>(transportChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find TransportChangeLog with this id";
		}
		return false;;
	}

	bool TransportChangeLog::IsEmpty()
	{
		if (0 == id && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID && 0 == transportID 
			&& logDate.empty() && 0== userID && 0 == operationID)
			return true;
		return false;
	}

	void TransportChangeLog::Clear()
	{
		id = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
		transportID = 0;
		logDate.empty();
		userID = 0;
		operationID = 0;
	}

	bool TransportChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
		int sID, int cID, std::string sLogDate, int tUserID, int tOperationID, std::string& errorMessage)
	{
		TransportChangeLog transportChangeLog;
		transportChangeLog.Clear();
		errorMessage.clear();
		transportChangeLog.SetTransportID(tID);
		transportChangeLog.SetProductID(pID);
		transportChangeLog.SetCount(sCount);
		transportChangeLog.SetSum(sSum);
		transportChangeLog.SetStatusID(sID);
		transportChangeLog.SetCurrencyID(cID);
		transportChangeLog.SetLogDate(sLogDate);
		transportChangeLog.SetUserID(tUserID);
		transportChangeLog.SetOperationID(tOperationID);
		std::string filter = transportChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::transportChangeLogCollection> transportChangeLogVector = ormasDal.GetTransportChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == transportChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Transport change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool TransportChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		TransportChangeLog transportChangeLog;
		transportChangeLog.Clear();
		errorMessage.clear();
		transportChangeLog.SetTransportID(transportID);
		transportChangeLog.SetProductID(productID);
		transportChangeLog.SetCount(count);
		transportChangeLog.SetSum(sum);
		transportChangeLog.SetStatusID(statusID);
		transportChangeLog.SetCurrencyID(currencyID);
		transportChangeLog.SetLogDate(logDate);
		transportChangeLog.SetUserID(userID);
		transportChangeLog.SetOperationID(operationID);
		std::string filter = transportChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::transportChangeLogCollection> transportChangeLogVector = ormasDal.GetTransportChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == transportChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Transport change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}


}