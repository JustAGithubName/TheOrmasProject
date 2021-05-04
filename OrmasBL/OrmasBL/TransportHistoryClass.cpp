#include "stdafx.h"
#include "TransportHistoryClass.h"
#include <codecvt>

namespace BusinessLayer
{
	TransportHistory::TransportHistory(DataLayer::transportHistoryCollection sCollection)
	{
		id = std::get<0>(sCollection);
		transportID = std::get<1>(sCollection);
		productID = std::get<2>(sCollection);
		count = std::get<3>(sCollection);
		sum = std::get<4>(sCollection);
		statusID = std::get<5>(sCollection);
		currencyID = std::get<6>(sCollection);
		fromDate = std::get<7>(sCollection);
		tillDate = std::get<8>(sCollection);
	}

	int TransportHistory::GetID()
	{
		return id;
	}

	int TransportHistory::GetProductID()
	{
		return productID;
	}

	double TransportHistory::GetCount()
	{
		return count;
	}

	double TransportHistory::GetSum()
	{
		return sum;
	}

	int TransportHistory::GetStatusID()
	{
		return statusID;
	}

	int TransportHistory::GetCurrencyID()
	{
		return currencyID;
	}

	int TransportHistory::GetTransportID()
	{
		return transportID;
	}

	std::string TransportHistory::GetFromDate()
	{
		return fromDate;
	}

	std::string TransportHistory::GetTillDate()
	{
		return tillDate;
	}

	void TransportHistory::SetID(int sID)
	{
		id = sID;
	}

	void TransportHistory::SetProductID(int sProductID)
	{
		productID = sProductID;
	}
	void TransportHistory::SetCount(double sCount)
	{
		count = sCount;
	}
	void TransportHistory::SetSum(double sSum)
	{
		sum = sSum;
	}
	void TransportHistory::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void TransportHistory::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void TransportHistory::SetTransportID(int stransportID)
	{
		transportID = stransportID;
	}

	void TransportHistory::SetFromDate(std::string fDate)
	{
		fromDate = fDate;
	}

	void TransportHistory::SetTillDate(std::string tDate)
	{
		tillDate = tDate;
	}

	bool TransportHistory::CreateTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
		int sID, int cID,  std::string sFromDate, std::string sTillDate, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		transportID = tID;
		fromDate = sFromDate;
		tillDate = sTillDate;
		if (0 != id && ormasDal.CreateTransportHistory(id, transportID, productID, count, sum, statusID, currencyID, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool TransportHistory::CreateTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateTransportHistory(id, transportID, productID, count, sum, statusID, currencyID, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool TransportHistory::DeleteTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteTransportHistory(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool TransportHistory::UpdateTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
		int sID, int cID,  std::string sFromDate, std::string sTillDate, std::string& errorMessage)
	{
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		transportID = tID;
		fromDate = sFromDate;
		tillDate = sTillDate;
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateTransportHistory(id, transportID, productID, count, sum, statusID, currencyID, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool TransportHistory::UpdateTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateTransportHistory(id, transportID, productID, count, sum, statusID, currencyID, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string TransportHistory::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != count || 0 != sum || 0 != statusID || 0 != transportID || !fromDate.empty() || !tillDate.empty())
		{
			return ormasDal.GetFilterForTransportHistory(id, transportID, productID, count, sum, statusID, currencyID, fromDate, tillDate);
		}
		return "";
	}

	bool TransportHistory::GetTransportHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportHistoryCollection> transportHistoryVector = ormasDal.GetTransportHistory(errorMessage, filter);
		if (0 != transportHistoryVector.size())
		{
			id = std::get<0>(transportHistoryVector.at(0));
			transportID = std::get<1>(transportHistoryVector.at(0));
			productID = std::get<2>(transportHistoryVector.at(0));
			count = std::get<3>(transportHistoryVector.at(0));
			sum = std::get<4>(transportHistoryVector.at(0));
			statusID = std::get<5>(transportHistoryVector.at(0));
			currencyID = std::get<6>(transportHistoryVector.at(0));
			fromDate = std::get<7>(transportHistoryVector.at(0));
			tillDate = std::get<8>(transportHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find TransportHistory with this id";
		}
		return false;
	}

	bool TransportHistory::GetTransportHistoryByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportHistoryCollection> transportHistoryVector = ormasDal.GetTransportHistory(errorMessage, filter);
		if (0 != transportHistoryVector.size())
		{
			id = std::get<0>(transportHistoryVector.at(0));
			transportID = std::get<1>(transportHistoryVector.at(0));
			productID = std::get<2>(transportHistoryVector.at(0));
			count = std::get<3>(transportHistoryVector.at(0));
			sum = std::get<4>(transportHistoryVector.at(0));
			statusID = std::get<5>(transportHistoryVector.at(0));
			currencyID = std::get<6>(transportHistoryVector.at(0));
			fromDate = std::get<7>(transportHistoryVector.at(0));
			tillDate = std::get<7>(transportHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find TransportHistory with this id";
		}
		return false;
	}

	bool TransportHistory::GetTransportHistoryByProductAndtransportID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		if (wID <= 0)
			return false;
		productID = pID;
		transportID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportHistoryCollection> transportHistoryVector = ormasDal.GetTransportHistory(errorMessage, filter);
		if (0 != transportHistoryVector.size())
		{
			id = std::get<0>(transportHistoryVector.at(0));
			transportID = std::get<1>(transportHistoryVector.at(0));
			productID = std::get<2>(transportHistoryVector.at(0));
			count = std::get<3>(transportHistoryVector.at(0));
			sum = std::get<4>(transportHistoryVector.at(0));
			statusID = std::get<5>(transportHistoryVector.at(0));
			currencyID = std::get<6>(transportHistoryVector.at(0));
			fromDate = std::get<7>(transportHistoryVector.at(0));
			tillDate = std::get<8>(transportHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find TransportHistory with this product ID and transport ID";
		}
		return false;
	}

	bool TransportHistory::IsEmpty()
	{
		if (0 == id && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID && 0 == transportID && fromDate.empty() && tillDate.empty())
			return true;
		return false;
	}

	void TransportHistory::Clear()
	{
		id = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
		transportID = 0;
		fromDate.empty();
		tillDate.empty();
	}

	bool TransportHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		TransportHistory transportHistory;
		transportHistory.Clear();
		errorMessage.clear();
		transportHistory.SetProductID(pID);
		transportHistory.SetTransportID(wID);
		std::string filter = transportHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::transportHistoryCollection> transportHistoryVector = ormasDal.GetTransportHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == transportHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Transport history with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool TransportHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		TransportHistory transportHistory;
		transportHistory.Clear();
		errorMessage.clear();
		transportHistory.SetProductID(productID);
		transportHistory.SetTransportID(transportID);
		std::string filter = transportHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::transportHistoryCollection> transportHistoryVector = ormasDal.GetTransportHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == transportHistoryVector.size())
		{
			return false;
		}
		errorMessage = "TransportHistory with this parameters are already exist! Please avoid the duplication!";
		return true;
	}


}