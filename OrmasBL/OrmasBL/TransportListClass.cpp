#include "stdafx.h"
#include "TransportListClass.h"
#include "TransportChangeLogClass.h"
#include "EntryClass.h"
#include <codecvt>

namespace BusinessLayer
{
	TransportList::TransportList(DataLayer::transportListCollection tListCollection)
	{
		id = std::get<0>(tListCollection);
		transportID = std::get<1>(tListCollection);
		productID = std::get<2>(tListCollection);
		count = std::get<3>(tListCollection);
		sum = std::get<4>(tListCollection);
		statusID = std::get<5>(tListCollection);
		currencyID = std::get<6>(tListCollection);
	}

	int TransportList::GetID()
	{
		return id;
	}

	int TransportList::GetTransportID()
	{
		return transportID;
	}

	int TransportList::GetProductID()
	{
		return productID;
	}

	double TransportList::GetCount()
	{
		return count;
	}

	double TransportList::GetSum()
	{
		return sum;
	}

	int TransportList::GetStatusID()
	{
		return statusID;
	}

	int TransportList::GetCurrencyID()
	{
		return currencyID;
	}

	void TransportList::SetID(int tID)
	{
		id = tID;
	}
	void TransportList::SetTransportID(int tTransportID)
	{
		transportID = tTransportID;
	}
	void TransportList::SetProductID(int tProductID)
	{
		productID = tProductID;
	}
	void TransportList::SetCount(double tCount)
	{
		count = tCount;
	}
	void TransportList::SetSum(double tSum)
	{
		sum = tSum;
	}
	void TransportList::SetStatusID(int tStatusID)
	{
		statusID = tStatusID;
	}
	void TransportList::SetCurrencyID(int tCurrencyID)
	{
		currencyID = tCurrencyID;
	}

	bool TransportList::CreateTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double tlCount, double tlSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		transportID = tID;
		productID = pID;
		count = tlCount;
		sum = tlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateTransportList(id, transportID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			if (CreateTransportChangeLog(globalVar, ormasDal, transportID, productID, count, sum, statusID, currencyID, errorMessage))
				return true;
		}
		return false;
	}
	bool TransportList::CreateTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateTransportList(id, transportID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			if (CreateTransportChangeLog(globalVar, ormasDal, transportID, productID, count, sum, statusID, currencyID, errorMessage))
				return true;
		}
		return false;
	}
	bool TransportList::DeleteTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInTransportList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool TransportList::DeleteListByTransportID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, std::string& errorMessage)
	{
		transportID = tID;
		if (ormasDal.DeleteListByTransportID(transportID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool TransportList::UpdateTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double tlCount, double tlSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		transportID = tID;
		productID = pID;
		count = tlCount;
		sum = tlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateTransportList(id, transportID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			if (CreateTransportChangeLog(globalVar, ormasDal, transportID, productID, count, sum, statusID, currencyID, errorMessage))
				return true;
		}
		return false;
	}
	bool TransportList::UpdateTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateTransportList(id, transportID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			if (CreateTransportChangeLog(globalVar, ormasDal, transportID, productID, count, sum, statusID, currencyID, errorMessage))
				return true;
		}
		return false;
	}

	std::string TransportList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != transportID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForTransportList(id, transportID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool TransportList::GetTransportListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, std::string& errorMessage)
	{
		if (tID <= 0)
			return false;
		id = tID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportListViewCollection> transportListVector = ormasDal.GetTransportList(errorMessage, filter);
		if (0 != transportListVector.size())
		{
			id = std::get<0>(transportListVector.at(0));
			transportID = std::get<1>(transportListVector.at(0));
			count = std::get<7>(transportListVector.at(0));
			sum = std::get<8>(transportListVector.at(0));
			productID = std::get<11>(transportListVector.at(0));
			statusID = std::get<12>(transportListVector.at(0));
			currencyID = std::get<13>(transportListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find ttansport list with this id";
		}
		return false;
	}

	bool TransportList::GetTransportListByTransportAndProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, std::string& errorMessage)
	{
		if (tID <= 0)
			return false;
		if (pID <= 0)
			return false;
		transportID = tID;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportListViewCollection> transportListVector = ormasDal.GetTransportList(errorMessage, filter);
		if (0 != transportListVector.size())
		{
			id = std::get<0>(transportListVector.at(0));
			transportID = std::get<1>(transportListVector.at(0));
			count = std::get<7>(transportListVector.at(0));
			sum = std::get<8>(transportListVector.at(0));
			productID = std::get<11>(transportListVector.at(0));
			statusID = std::get<12>(transportListVector.at(0));
			currencyID = std::get<13>(transportListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find ttansport list with this id";
		}
		return false;
	}

	bool TransportList::IsEmpty()
	{
		if (0 == id && 0 == transportID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void TransportList::Clear()
	{
		id = 0;
		transportID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool TransportList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double tlCount, double tlSum,
		int cID, std::string& errorMessage)
	{
		TransportList transportList;
		transportList.Clear();
		errorMessage.clear();
		transportList.SetTransportID(tID);
		transportList.SetProductID(pID);
		transportList.SetCount(tlCount);
		transportList.SetSum(tlSum);
		transportList.SetCurrencyID(cID);
		std::string filter = transportList.GenerateFilter(ormasDal);
		std::vector<DataLayer::transportListViewCollection> transportListVector = ormasDal.GetTransportList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == transportListVector.size())
		{
			return false;
		}
		errorMessage = "Transport list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool TransportList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		TransportList transportList;
		transportList.Clear();
		errorMessage.clear();
		transportList.SetTransportID(transportID);
		transportList.SetProductID(productID);
		transportList.SetCount(count);
		transportList.SetSum(sum);
		transportList.SetCurrencyID(currencyID);
		std::string filter = transportList.GenerateFilter(ormasDal);
		std::vector<DataLayer::transportListViewCollection> transportListVector = ormasDal.GetTransportList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == transportListVector.size())
		{
			return false;
		}
		errorMessage = "Transport list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::string TransportList::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}

	bool TransportList::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string& errorMessage)
	{
		Entry entry;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Коррекция себестоимости товара в транспорте"));
		if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			return false;
		}
		return true;
	}
	bool TransportList::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage)
	{
		Entry entry;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена коррекция себестоимости товара в транспорте"));
		if (!entry.CreateEntry(globalVar, ormasDal, errorMessage, true))
		{
			return false;
		}
		entry.Clear();
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Коррекция себестоимости товара в транспорте"));
		if (!entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			return false;
		}
		return true;
	}

	bool TransportList::CreateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double tlCount, double tlSum,
		int sID, int cID, std::string& errorMessage)
	{
		TransportChangeLog scLog;
		scLog.SetTransportID(tID);
		scLog.SetProductID(pID);
		scLog.SetCount(tlCount);
		scLog.SetSum(tlSum);
		scLog.SetStatusID(sID);
		scLog.SetCurrencyID(cID);
		scLog.SetLogDate(ormasDal.GetSystemDateTime());
		scLog.SetUserID(globalVar->userID);
		scLog.SetOperationID(globalVar->currentOperationID);
		if (scLog.CreateTransportChangeLog(globalVar, ormasDal, errorMessage))
			return true;
		return false;
	}
}