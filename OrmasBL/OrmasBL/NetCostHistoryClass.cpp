#include "stdafx.h"
#include "NetCostHistoryClass.h"

namespace BusinessLayer{
	NetCostHistory::NetCostHistory(DataLayer::netCostHistoryCollection nCollection)
	{
		id = std::get<0>(nCollection);
		date = std::get<1>(nCollection);
		value = std::get<2>(nCollection);
		currencyID = std::get<3>(nCollection);
		productID = std::get<4>(nCollection);
		isOutdated = std::get<5>(nCollection);
		historyDate = std::get<6>(nCollection);
	}
	NetCostHistory::NetCostHistory()
	{
		date = "";
		value = 0.0;
		currencyID = 0;
		productID = 0;
		isOutdated = true;
		historyDate = "";
	}
	int NetCostHistory::GetID()
	{
		return id;
	}

	std::string NetCostHistory::GetDate()
	{
		return date;
	}

	double NetCostHistory::GetValue()
	{
		return value;
	}

	int NetCostHistory::GetCurrencyID()
	{
		return currencyID;
	}

	int NetCostHistory::GetProductID()
	{
		return productID;
	}

	bool NetCostHistory::GetIsOutdated()
	{
		return isOutdated;
	}

	std::string NetCostHistory::GetHistoryDate()
	{
		return historyDate;

	}
	void NetCostHistory::SetID(int nID)
	{
		id = nID;
	}

	void NetCostHistory::SetDate(std::string nDate)
	{
		date = nDate;
	}

	void NetCostHistory::SetValue(double nValue)
	{
		value = nValue;
	}

	void NetCostHistory::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}

	void NetCostHistory::SetProductID(int prID)
	{
		productID = prID;
	}

	void NetCostHistory::SetIsOutdated(bool nIsOutdated)
	{
		isOutdated = nIsOutdated;
	}
	
	void NetCostHistory::SetHistoryDate(std::string nHDate)
	{
		historyDate = nHDate;
	}

	bool NetCostHistory::CreateNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID, bool nIsOutdated, std::string hDate,
		std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, nDate, nValue, cID, prID, hDate, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		date = nDate;
		value = nValue;
		currencyID = cID;
		productID = prID;
		isOutdated = nIsOutdated;
		historyDate = hDate;
		if (0 != id && ormasDal.CreateNetCostHistory(id, date, value, currencyID, productID, isOutdated, historyDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCostHistory::CreateNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateNetCostHistory(id, date, value, currencyID, productID, isOutdated, historyDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCostHistory::DeleteNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteNetCostHistory(id, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}

	bool NetCostHistory::UpdateNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID, bool nIsOutdated, std::string hDate,
		std::string& errorMessage)
	{
		date = nDate;
		value = nValue;
		currencyID = cID;
		productID = prID;
		isOutdated = nIsOutdated;
		historyDate = hDate;
		if (0 != id && ormasDal.UpdateNetCostHistory(id, date, value, currencyID, productID, isOutdated, historyDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCostHistory::UpdateNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateNetCostHistory(id, date, value, currencyID, productID, isOutdated, historyDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string NetCostHistory::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != productID || 0 != currencyID || 0 != value || historyDate.empty() || (isOutdated == true || isOutdated == false))
		{
			return ormasDal.GetFilterForNetCostHistory(id, date, value, currencyID, productID, isOutdated, historyDate);
		}
		return "";
	}

	bool NetCostHistory::GetNetCostHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, std::string& errorMessage)
	{
		if (nID <= 0)
			return false;
		id = nID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostHistoryCollection> netCostHistoryVector = ormasDal.GetNetCostHistory(errorMessage, filter);
		if (0 != netCostHistoryVector.size())
		{
			id = std::get<0>(netCostHistoryVector.at(0));
			date = std::get<1>(netCostHistoryVector.at(0));
			value = std::get<2>(netCostHistoryVector.at(0));
			currencyID = std::get<3>(netCostHistoryVector.at(0));
			productID = std::get<4>(netCostHistoryVector.at(0));
			isOutdated = std::get<5>(netCostHistoryVector.at(0));
			date = std::get<6>(netCostHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find net cost with this id";
		}
		return false;
	}

	bool NetCostHistory::GetNetCostHistoryByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostHistoryCollection> netCostHistoryVector = ormasDal.GetNetCostHistory(errorMessage, filter);
		if (0 != netCostHistoryVector.size())
		{
			id = std::get<0>(netCostHistoryVector.at(0));
			date = std::get<1>(netCostHistoryVector.at(0));
			value = std::get<2>(netCostHistoryVector.at(0));
			currencyID = std::get<3>(netCostHistoryVector.at(0));
			productID = std::get<4>(netCostHistoryVector.at(0));
			isOutdated = std::get<5>(netCostHistoryVector.at(0));
			date = std::get<6>(netCostHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find net cost with this product id";
		}
		return false;
	}

	bool NetCostHistory::IsEmpty()
	{
		if (0 == id && date.empty() && 0.0 == value && 0 == currencyID && 0 == productID && isOutdated == true && historyDate.empty())
			return true;
		return false;
	}

	void NetCostHistory::Clear()
	{
		id = 0;
		date.clear();
		value = 0;
		currencyID = 0;
		productID = 0;
		isOutdated = true;
		historyDate.clear();
	}

	bool NetCostHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID, std::string historyDate,
		std::string& errorMessage)
	{
		NetCostHistory netCostHistory;
		netCostHistory.Clear();
		errorMessage.clear();
		netCostHistory.SetDate(nDate);
		netCostHistory.SetValue(nValue);
		netCostHistory.SetCurrencyID(cID);
		netCostHistory.SetProductID(prID);
		netCostHistory.SetHistoryDate(historyDate);
		std::string filter = netCostHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostHistoryCollection> netCostHistoryVector = ormasDal.GetNetCostHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == netCostHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Net cost with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool NetCostHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		NetCostHistory netCostHistory;
		netCostHistory.Clear();
		errorMessage.clear();
		netCostHistory.SetDate(date);
		netCostHistory.SetValue(value);
		netCostHistory.SetCurrencyID(currencyID);
		netCostHistory.SetProductID(productID);
		std::string filter = netCostHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostHistoryCollection> netCostHistoryVector = ormasDal.GetNetCostHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == netCostHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Net cost with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}