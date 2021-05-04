#include "stdafx.h"
#include "NetCostClass.h"

namespace BusinessLayer{
	NetCost::NetCost(DataLayer::netCostCollection nCollection)
	{
		id = std::get<0>(nCollection);
		date = std::get<1>(nCollection);
		value = std::get<2>(nCollection);
		currencyID = std::get<3>(nCollection);
		productID = std::get<4>(nCollection);
		isOutdated = std::get<5>(nCollection);
	}
	NetCost::NetCost()
	{
		date = "";
		value = 0.0;
		currencyID = 0;
		productID = 0;
		isOutdated = true;
	}
	int NetCost::GetID()
	{
		return id;
	}

	std::string NetCost::GetDate()
	{
		return date;
	}

	double NetCost::GetValue()
	{
		return value;
	}

	int NetCost::GetCurrencyID()
	{
		return currencyID;
	}

	int NetCost::GetProductID()
	{
		return productID;
	}

	bool NetCost::GetIsOutdated()
	{
		return isOutdated;
	}

	void NetCost::SetID(int nID)
	{
		id = nID;
	}

	void NetCost::SetDate(std::string nDate)
	{
		date = nDate;
	}

	void NetCost::SetValue(double nValue)
	{
		value = nValue;
	}

	void NetCost::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}

	void NetCost::SetProductID(int prID)
	{
		productID = prID;
	}

	void NetCost::SetIsOutdated(bool nIsOutdated)
	{
		isOutdated = nIsOutdated;
	}

	bool NetCost::CreateNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID, bool nIsOutdated,
		std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, nDate, nValue, cID, prID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		date = nDate;
		value = nValue;
		currencyID = cID;
		productID = prID;
		isOutdated = nIsOutdated;
		if (0 != id && ormasDal.CreateNetCost(id, date, value, currencyID, productID, isOutdated, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCost::CreateNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateNetCost(id, date, value, currencyID, productID, isOutdated, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCost::DeleteNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteNetCost(id, errorMessage))
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

	bool NetCost::UpdateNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID, bool nIsOutdated,
		std::string& errorMessage)
	{
		date = nDate;
		value = nValue;
		currencyID = cID;
		productID = prID;
		isOutdated = nIsOutdated;
		if (0 != id && ormasDal.UpdateNetCost(id, date, value, currencyID, productID, isOutdated, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCost::UpdateNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateNetCost(id, date, value, currencyID, productID, isOutdated, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string NetCost::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != productID || 0 != currencyID || 0 != value || (isOutdated == true || isOutdated == false))
		{
			return ormasDal.GetFilterForNetCost(id, date, value, currencyID, productID, isOutdated);
		}
		return "";
	}

	bool NetCost::GetNetCostByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, std::string& errorMessage)
	{
		if (nID <= 0)
			return false;
		id = nID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostViewCollection> netCostVector = ormasDal.GetNetCost(errorMessage, filter);
		if (0 != netCostVector.size())
		{
			id = std::get<0>(netCostVector.at(0));
			date = std::get<1>(netCostVector.at(0));
			value = std::get<5>(netCostVector.at(0));
			currencyID = std::get<7>(netCostVector.at(0));
			productID = std::get<8>(netCostVector.at(0));
			isOutdated = std::get<9>(netCostVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find net cost with this id";
		}
		return false;
	}

	bool NetCost::GetNetCostByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostViewCollection> netCostVector = ormasDal.GetNetCost(errorMessage, filter);
		if (0 != netCostVector.size())
		{
			id = std::get<0>(netCostVector.at(0));
			date = std::get<1>(netCostVector.at(0));
			value = std::get<5>(netCostVector.at(0));
			currencyID = std::get<7>(netCostVector.at(0));
			productID = std::get<8>(netCostVector.at(0));
			isOutdated = std::get<9>(netCostVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find net cost with this product id";
		}
		return false;
	}

	bool NetCost::IsEmpty()
	{
		if (0 == id && date.empty() && 0.0 == value && 0 == currencyID && 0 == productID && isOutdated == true)
			return true;
		return false;
	}

	void NetCost::Clear()
	{
		id = 0;
		date.clear();
		value = 0;
		currencyID = 0;
		productID = 0;
		isOutdated = true;
	}

	bool NetCost::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID,
		std::string& errorMessage)
	{
		NetCost netCost;
		netCost.Clear();
		errorMessage.clear();
		netCost.SetDate(nDate);
		netCost.SetValue(nValue);
		netCost.SetCurrencyID(cID);
		netCost.SetProductID(prID);
		std::string filter = netCost.GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostViewCollection> netCostVector = ormasDal.GetNetCost(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == netCostVector.size())
		{
			return false;
		}
		errorMessage = "Net cost with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool NetCost::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		NetCost netCost;
		netCost.Clear();
		errorMessage.clear();
		netCost.SetDate(date);
		netCost.SetValue(value);
		netCost.SetCurrencyID(currencyID);
		netCost.SetProductID(productID);
		std::string filter = netCost.GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostViewCollection> netCostVector = ormasDal.GetNetCost(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == netCostVector.size())
		{
			return false;
		}
		errorMessage = "Net cost with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}