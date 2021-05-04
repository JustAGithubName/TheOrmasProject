#include "stdafx.h"
#include "WriteOffRawListClass.h"

namespace BusinessLayer
{
	WriteOffRawList::WriteOffRawList(DataLayer::writeOffRawListCollection wListCollection)
	{
		id = std::get<0>(wListCollection);
		writeOffRawID = std::get<1>(wListCollection);
		productID = std::get<2>(wListCollection);
		count = std::get<3>(wListCollection);
		sum = std::get<4>(wListCollection);
		statusID = std::get<5>(wListCollection);
		currencyID = std::get<6>(wListCollection);
	}

	int WriteOffRawList::GetID()
	{
		return id;
	}

	int WriteOffRawList::GetWriteOffRawID()
	{
		return writeOffRawID;
	}

	int WriteOffRawList::GetProductID()
	{
		return productID;
	}

	double WriteOffRawList::GetCount()
	{
		return count;
	}

	double WriteOffRawList::GetSum()
	{
		return sum;
	}

	int WriteOffRawList::GetStatusID()
	{
		return statusID;
	}

	int WriteOffRawList::GetCurrencyID()
	{
		return currencyID;
	}

	void WriteOffRawList::SetID(int wID)
	{
		id = wID;
	}
	void WriteOffRawList::SetWriteOffRawID(int wWriteOffRawID)
	{
		writeOffRawID = wWriteOffRawID;
	}
	void WriteOffRawList::SetProductID(int wProductID)
	{
		productID = wProductID;
	}
	void WriteOffRawList::SetCount(double wCount)
	{
		count = wCount;
	}
	void WriteOffRawList::SetSum(double wSum)
	{
		sum = wSum;
	}
	void WriteOffRawList::SetStatusID(int wStatusID)
	{
		statusID = wStatusID;
	}
	void WriteOffRawList::SetCurrencyID(int wCurrencyID)
	{
		currencyID = wCurrencyID;
	}

	bool WriteOffRawList::CreateWriteOffRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int pID, double wlCount, double wlSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		writeOffRawID = wID;
		productID = pID;
		count = wlCount;
		sum = wlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateWriteOffRawList(id, writeOffRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool WriteOffRawList::CreateWriteOffRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateWriteOffRawList(id, writeOffRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool WriteOffRawList::DeleteWriteOffRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInWriteOffRawList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool WriteOffRawList::DeleteListByWriteOffRawID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		writeOffRawID = wID;
		if (ormasDal.DeleteListByWriteOffRawID(writeOffRawID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool WriteOffRawList::UpdateWriteOffRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int pID, double wlCount, double wlSum,
		int sID, int cID, std::string& errorMessage)
	{
		writeOffRawID = wID;
		productID = pID;
		count = wlCount;
		sum = wlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateWriteOffRawList(id, writeOffRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool WriteOffRawList::UpdateWriteOffRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateWriteOffRawList(id, writeOffRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string WriteOffRawList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != writeOffRawID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForWriteOffRawList(id, writeOffRawID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool WriteOffRawList::GetWriteOffRawListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawListViewCollection> writeOffRawListVector = ormasDal.GetWriteOffRawList(errorMessage, filter);
		if (0 != writeOffRawListVector.size())
		{
			id = std::get<0>(writeOffRawListVector.at(0));
			writeOffRawID = std::get<1>(writeOffRawListVector.at(0));
			count = std::get<7>(writeOffRawListVector.at(0));
			sum = std::get<8>(writeOffRawListVector.at(0));
			productID = std::get<11>(writeOffRawListVector.at(0));
			statusID = std::get<12>(writeOffRawListVector.at(0));
			currencyID = std::get<13>(writeOffRawListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find write-off raw list with this id";
		}
		return false;
	}

	bool WriteOffRawList::IsEmpty()
	{
		if (0 == id && 0 == writeOffRawID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void WriteOffRawList::Clear()
	{
		id = 0;
		writeOffRawID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool WriteOffRawList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int pID, double wlCount, double wlSum,
		int cID, std::string& errorMessage)
	{
		WriteOffRawList writeOffRawList;
		writeOffRawList.Clear();
		errorMessage.clear();
		writeOffRawList.SetWriteOffRawID(wID);
		writeOffRawList.SetProductID(pID);
		writeOffRawList.SetCount(wlCount);
		writeOffRawList.SetSum(wlSum);
		writeOffRawList.SetCurrencyID(cID);
		std::string filter = writeOffRawList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawListViewCollection> writeOffRawListVector = ormasDal.GetWriteOffRawList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == writeOffRawListVector.size())
		{
			return false;
		}
		errorMessage = "Write-off raw list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool WriteOffRawList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		WriteOffRawList writeOffRawList;
		writeOffRawList.Clear();
		errorMessage.clear();
		writeOffRawList.SetWriteOffRawID(writeOffRawID);
		writeOffRawList.SetProductID(productID);
		writeOffRawList.SetCount(count);
		writeOffRawList.SetSum(sum);
		writeOffRawList.SetCurrencyID(currencyID);
		std::string filter = writeOffRawList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawListViewCollection> writeOffRawListVector = ormasDal.GetWriteOffRawList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == writeOffRawListVector.size())
		{
			return false;
		}
		errorMessage = "Write-off raw list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}