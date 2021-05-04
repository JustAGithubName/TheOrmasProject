#include "stdafx.h"
#include "ReceiptProductListClass.h"

namespace BusinessLayer
{
	ReceiptProductList::ReceiptProductList(DataLayer::receiptProductListCollection rListCollection)
	{
		id = std::get<0>(rListCollection);
		receiptProductID = std::get<1>(rListCollection);
		productID = std::get<2>(rListCollection);
		count = std::get<3>(rListCollection);
		sum = std::get<4>(rListCollection);
		statusID = std::get<5>(rListCollection);
		currencyID = std::get<6>(rListCollection);
	}

	int ReceiptProductList::GetID()
	{
		return id;
	}

	int ReceiptProductList::GetReceiptProductID()
	{
		return receiptProductID;
	}

	int ReceiptProductList::GetProductID()
	{
		return productID;
	}

	double ReceiptProductList::GetCount()
	{
		return count;
	}

	double ReceiptProductList::GetSum()
	{
		return sum;
	}

	int ReceiptProductList::GetStatusID()
	{
		return statusID;
	}

	int ReceiptProductList::GetCurrencyID()
	{
		return currencyID;
	}

	void ReceiptProductList::SetID(int rID)
	{
		id = rID;
	}
	void ReceiptProductList::SetReceiptProductID(int rReceiptProductID)
	{
		receiptProductID = rReceiptProductID;
	}
	void ReceiptProductList::SetProductID(int rProductID)
	{
		productID = rProductID;
	}
	void ReceiptProductList::SetCount(double rCount)
	{
		count = rCount;
	}
	void ReceiptProductList::SetSum(double rSum)
	{
		sum = rSum;
	}
	void ReceiptProductList::SetStatusID(int rStatusID)
	{
		statusID = rStatusID;
	}
	void ReceiptProductList::SetCurrencyID(int rCurrencyID)
	{
		currencyID = rCurrencyID;
	}

	bool ReceiptProductList::CreateReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int pID, double rplCount, double rplSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		receiptProductID = rpID;
		productID = pID;
		count = rplCount;
		sum = rplSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateReceiptProductList(id, receiptProductID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReceiptProductList::CreateReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateReceiptProductList(id, receiptProductID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReceiptProductList::DeleteReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInReceiptProductList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ReceiptProductList::DeleteListByReceiptProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		receiptProductID = oID;
		if (ormasDal.DeleteListByReceiptProductID(receiptProductID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool ReceiptProductList::UpdateReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
		int sID, int cID, std::string& errorMessage)
	{
		receiptProductID = rID;
		productID = pID;
		count = rlCount;
		sum = rlSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateReceiptProductList(id, receiptProductID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReceiptProductList::UpdateReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateReceiptProductList(id, receiptProductID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ReceiptProductList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != receiptProductID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForReceiptProductList(id, receiptProductID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool ReceiptProductList::GetReceiptProductListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage)
	{
		if (rID <= 0)
			return false;
		id = rID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> receiptProductListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (0 != receiptProductListVector.size())
		{
			id = std::get<0>(receiptProductListVector.at(0));
			receiptProductID = std::get<1>(receiptProductListVector.at(0));
			count = std::get<7>(receiptProductListVector.at(0));
			sum = std::get<8>(receiptProductListVector.at(0));
			productID = std::get<11>(receiptProductListVector.at(0));
			statusID = std::get<12>(receiptProductListVector.at(0));
			currencyID = std::get<13>(receiptProductListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find receipt product list with this id";
		}
		return false;
	}

	bool ReceiptProductList::IsEmpty()
	{
		if (0 == id && 0 == receiptProductID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ReceiptProductList::Clear()
	{
		id = 0;
		receiptProductID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ReceiptProductList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
		int cID, std::string& errorMessage)
	{
		ReceiptProductList receiptProductList;
		receiptProductList.Clear();
		errorMessage.clear();
		receiptProductList.SetReceiptProductID(rID);
		receiptProductList.SetProductID(pID);
		receiptProductList.SetCount(rlCount);
		receiptProductList.SetSum(rlSum);
		receiptProductList.SetCurrencyID(cID);
		std::string filter = receiptProductList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> receiptProductListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == receiptProductListVector.size())
		{
			return false;
		}
		errorMessage = "Receipt product list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ReceiptProductList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ReceiptProductList receiptProductList;
		receiptProductList.Clear();
		errorMessage.clear();
		receiptProductList.SetReceiptProductID(receiptProductID);
		receiptProductList.SetProductID(productID);
		receiptProductList.SetCount(count);
		receiptProductList.SetSum(sum);
		receiptProductList.SetCurrencyID(currencyID);
		std::string filter = receiptProductList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> receiptProductListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == receiptProductListVector.size())
		{
			return false;
		}
		errorMessage = "Receipt product list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}