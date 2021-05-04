#include "stdafx.h"
#include "OtherStocksClass.h"
#include <boost/algorithm/string.hpp>
#include "PriceClass.h"
#include "LowValueStockClass.h"

namespace BusinessLayer
{
	OtherStocks::OtherStocks(DataLayer::otherStocksCollection pCollection)
	{
		id = std::get<0>(pCollection);
		companyID = std::get<1>(pCollection);
		name = std::get<2>(pCollection);
		volume = std::get<3>(pCollection);
		measureID = std::get<4>(pCollection);
		price = std::get<5>(pCollection);
		currencyID = std::get<6>(pCollection);
		otherStocksTypeID = std::get<6>(pCollection);
	}

	int OtherStocks::GetID()
	{
		return id;
	}

	int OtherStocks::GetCompanyID()
	{
		return companyID;
	}

	std::string OtherStocks::GetName()
	{
		return name;
	}

	double OtherStocks::GetVolume()
	{
		return volume;
	}

	int OtherStocks::GetMeasureID()
	{
		return measureID;
	}

	double OtherStocks::GetPrice()
	{
		return price;
	}

	

	int OtherStocks::GetCurrencyID()
	{
		return currencyID;
	}

	int OtherStocks::GetOtherStocksTypeID()
	{
		return otherStocksTypeID;
	}

	void OtherStocks::SetID(int pID)
	{
		id = pID;
	}
	void OtherStocks::SetCompanyID(int pCompanyID)
	{
		companyID = pCompanyID;
	}
	void OtherStocks::SetName(std::string pName)
	{
		if (!pName.empty())
			boost::trim(pName);
		name = pName;
	}
	void OtherStocks::SetVolume(double pVolume)
	{
		volume = pVolume;
	}
	void OtherStocks::SetMeasureID(int pMeasureID)
	{
		measureID = pMeasureID;
	}
	void OtherStocks::SetPrice(double pPrice)
	{
		price = pPrice;
	}
	void OtherStocks::SetCurrencyID(int pCurrencyID)
	{
		currencyID = pCurrencyID;
	}

	void OtherStocks::SetOtherStocksTypeID(int pOtherStocksTypeID)
	{
		otherStocksTypeID = pOtherStocksTypeID;
	}

	bool OtherStocks::CreateOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double pri,
		int currID, int ostID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, cID, pName, vol, mID, price, currID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(pName);
		companyID = cID;
		name = pName;
		volume = vol;
		measureID = mID;
		price = pri;
		currencyID = currID;
		otherStocksTypeID = ostID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateOtherStocks(id, companyID, name, volume, measureID, price, currencyID, ostID, errorMessage))
		{
			//if (AddPriceData(globalVar, ormasDal, id, price, currencyID, errorMessage))
			//{
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			//}
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool OtherStocks::CreateOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateOtherStocks(id, companyID, name, volume, measureID, price,  currencyID, otherStocksTypeID, errorMessage))
		{
			//if (AddPriceData(globalVar, ormasDal, id, price, currencyID, errorMessage))
			//{
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			//}
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool OtherStocks::DeleteOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteOtherStocks(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool OtherStocks::UpdateOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double pri,
		 int pCurrencyID, int ostID, std::string& errorMessage)
	{
		TrimStrings(pName);
		companyID = cID;
		name = pName;
		volume = vol;
		measureID = mID;
		price = pri;
		currencyID = pCurrencyID;
		otherStocksTypeID = ostID;
		oldPrice = GetCurrentPrice(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateOtherStocks(id, companyID, name, volume, measureID, price,  currencyID, ostID, errorMessage))
		{
			//if (!AddPriceData(globalVar, ormasDal, id, price, currencyID, errorMessage))
			//{
				//ormasDal.CancelTransaction(errorMessage);
			//	return false;
			//}
			if (oldPrice != price)
			{
				if (!RecalculateStock(globalVar, ormasDal, id, oldPrice, price, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool OtherStocks::UpdateOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		oldPrice = GetCurrentPrice(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateOtherStocks(id, companyID, name, volume, measureID, price, currencyID, otherStocksTypeID, errorMessage))
		{
			//if (!AddPriceData(globalVar, ormasDal, id, price, currencyID, errorMessage))
			//{
				//ormasDal.CancelTransaction(errorMessage);
			//	return false;
			//}
			if (oldPrice != price)
			{
				if (!RecalculateStock(globalVar, ormasDal, id, oldPrice, price, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string OtherStocks::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != companyID || !name.empty() || 0 != volume || 0 != measureID || 0 != price || 0 != currencyID || 0 != otherStocksTypeID)
		{
			return ormasDal.GetFilterForOtherStocks(id, companyID, name, volume, measureID, price, currencyID, otherStocksTypeID);
		}
		return "";
	}

	std::string OtherStocks::GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> othSIDList)
	{
		if (othSIDList.size()>0)
		{
			return ormasDal.GetINFilterForOtherStocksID(othSIDList);
		}
		return "";
	}

	std::string OtherStocks::GenerateLikeFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string searchKey)
	{
		if (!searchKey.empty())
		{
			return ormasDal.GetLikeFilterForOtherStocksName(searchKey);
		}
		return "";
	}

	bool OtherStocks::GetOtherStocksByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int otsID, std::string& errorMessage)
	{
		if (otsID <= 0)
			return false;
		id = otsID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::otherStocksViewCollection> OtherStocksVector = ormasDal.GetOtherStocks(errorMessage, filter);
		if (0 != OtherStocksVector.size())
		{
			id = std::get<0>(OtherStocksVector.at(0));
			name = std::get<1>(OtherStocksVector.at(0));
			price = std::get<2>(OtherStocksVector.at(0));
			volume = std::get<4>(OtherStocksVector.at(0));
			companyID = std::get<8>(OtherStocksVector.at(0));
			measureID = std::get<9>(OtherStocksVector.at(0));
			currencyID = std::get<10>(OtherStocksVector.at(0));
			otherStocksTypeID = std::get<11>(OtherStocksVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find other stocks with this id";
		}
		return false;
	}

	bool OtherStocks::IsEmpty()
	{
		if (0 == id && name == "" && 0 == price && 0 == volume &&  0 == companyID
			&& 0 == measureID && 0 == currencyID && 0 == otherStocksTypeID)
			return true;
		return false;
	}

	void OtherStocks::Clear()
	{
		id = 0;
		name.clear();
		price = 0;
		volume = 0;
		companyID = 0;
		measureID = 0;
		currencyID = 0;
		otherStocksTypeID = 0;
	}

	void OtherStocks::TrimStrings(std::string& pName)
	{
		if (!pName.empty())
			boost::trim(pName);
	}

	bool OtherStocks::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double price,
		int curID, std::string& errorMessage)
	{
		OtherStocks otherStocks;
		otherStocks.Clear();
		errorMessage.clear();
		otherStocks.SetCompanyID(cID);
		otherStocks.SetName(pName);
		otherStocks.SetVolume(vol);
		otherStocks.SetMeasureID(mID);
		otherStocks.SetPrice(price);
		otherStocks.SetCurrencyID(curID);
		std::string filter = otherStocks.GenerateFilter(ormasDal);
		std::vector<DataLayer::otherStocksViewCollection> otherStocksVector = ormasDal.GetOtherStocks(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == otherStocksVector.size())
		{
			return false;
		}
		errorMessage = "Other stocks with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool OtherStocks::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		OtherStocks otherStocks;
		otherStocks.Clear();
		errorMessage.clear();
		otherStocks.SetCompanyID(companyID);
		otherStocks.SetName(name);
		otherStocks.SetVolume(volume);
		otherStocks.SetMeasureID(measureID);
		otherStocks.SetPrice(price);
		otherStocks.SetCurrencyID(currencyID);
		std::string filter = otherStocks.GenerateFilter(ormasDal);
		std::vector<DataLayer::otherStocksViewCollection> otherStocksVector = ormasDal.GetOtherStocks(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == otherStocksVector.size())
		{
			return false;
		}
		errorMessage = "Other stocks with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	/*bool OtherStocks::AddPriceData(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double pPrice, int curID, std::string& errorMessage)
	{
		Price pri;
		pri.SetDate(ormasDal.GetSystemDateTime());
		pri.SetValue(pPrice);
		pri.SetCurrencyID(curID);
		pri.SetOtherStocksID(pID);
		if (pri.CreatePrice(globalVar, ormasDal, errorMessage))
			return true;
		return false;
	}*/

	double OtherStocks::GetCurrentPrice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, std::string& errorMessage)
	{
		OtherStocks otherStocks;
		if (otherStocks.GetOtherStocksByID(globalVar, ormasDal, osID, errorMessage))
			return otherStocks.GetPrice();
		return 0;
	}

	bool OtherStocks::RecalculateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, double oldPrice, double newPrice, std::string& errorMessage)
	{
		LowValueStock stocks;
		if (stocks.RecalculateLowValueStock(globalVar, ormasDal, osID, oldPrice, newPrice, errorMessage))
			return true;
		return false;
	}
}