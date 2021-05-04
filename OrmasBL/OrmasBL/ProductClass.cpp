#include "stdafx.h"
#include "ProductClass.h"
#include <boost/algorithm/string.hpp>
#include "PriceClass.h"
#include "SpecificationClass.h"
#include "StockClass.h"

namespace BusinessLayer
{
	Product::Product(DataLayer::productsCollection pCollection)
	{
		id = std::get<0>(pCollection);
		companyID = std::get<1>(pCollection);
		name = std::get<2>(pCollection);
		volume = std::get<3>(pCollection);
		measureID = std::get<4>(pCollection);
		price = std::get<5>(pCollection);
		productTypeID = std::get<6>(pCollection);
		shelfLife = std::get<7>(pCollection);
		currencyID = std::get<8>(pCollection);
	}

	int Product::GetID()
	{
		return id;
	}

	int Product::GetCompanyID()
	{
		return companyID;
	}

	std::string Product::GetName()
	{
		return name;
	}

	double Product::GetVolume()
	{
		return volume;
	}

	int Product::GetMeasureID()
	{
		return measureID;
	}

	double Product::GetPrice()
	{
		return price;
	}

	int Product::GetProductTypeID()
	{
		return productTypeID;
	}

	int Product::GetShelfLife()
	{
		return shelfLife;
	}

	int Product::GetCurrencyID()
	{
		return currencyID;
	}

	void Product::SetID(int pID)
	{
		id = pID;
	}
	void Product::SetCompanyID(int pCompanyID)
	{
		companyID = pCompanyID;
	}
	void Product::SetName(std::string pName)
	{
		if (!pName.empty())
			boost::trim(pName);
		name = pName;
	}
	void Product::SetVolume(double pVolume)
	{
		volume = pVolume;
	}
	void Product::SetMeasureID(int pMeasureID)
	{
		measureID = pMeasureID;
	}
	void Product::SetPrice(double pPrice)
	{
		price = pPrice;
	}
	void Product::SetProductTypeID(int pProdTypeID)
	{
		productTypeID = pProdTypeID;
	}
	void Product::SetShelfLife(int pShelfLife)
	{
		shelfLife = pShelfLife;
	}
	void Product::SetCurrencyID(int pCurrencyID)
	{
		currencyID = pCurrencyID;
	}

	bool Product::CreateProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double pri,
		int pTypeID, int pShelfLife, int currID, std::string& errorMessage)
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
		productTypeID = pTypeID;
		shelfLife = pShelfLife;
		currencyID = currID;
		//ormasDal.StartTransaction(errorMessage);
		if (0 == globalVar->currentOperationID)
			globalVar->currentOperationID = id;	
		if (0 != id && ormasDal.CreateProduct(id, companyID, name, volume, measureID, price, productTypeID, shelfLife, currencyID, errorMessage))
		{
			if (AddPriceData(globalVar, ormasDal, id, price, currencyID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Product::CreateProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		if (0 == globalVar->currentOperationID)
			globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateProduct(id, companyID, name, volume, measureID, price, productTypeID, shelfLife, currencyID, errorMessage))
		{
			if (AddPriceData(globalVar, ormasDal, id, price, currencyID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Product::DeleteProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteProduct(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool Product::UpdateProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double pri,
		int pTypeID, int pShelfLife, int pCurrencyID, std::string& errorMessage)
	{
		TrimStrings(pName);
		companyID = cID;
		name = pName;
		volume = vol;
		measureID = mID;
		price = pri;
		productTypeID = pTypeID;
		shelfLife = pShelfLife;
		currencyID = pCurrencyID;
		oldPrice = GetCurrentPrice(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		if (0 == globalVar->currentOperationID)
			globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateProduct(id, companyID, name, volume, measureID, price, productTypeID, shelfLife, currencyID, errorMessage))
		{
			if (!AddPriceData(globalVar, ormasDal, id, price, currencyID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
			if (oldPrice != price)
			{
				if (!RecalculateStock(globalVar, ormasDal, id, oldPrice, price, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				if (!UpdateSpecifications(globalVar, ormasDal, id, oldPrice, price, errorMessage))
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
	bool Product::UpdateProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		oldPrice = GetCurrentPrice(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		if (0 == globalVar->currentOperationID)
			globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateProduct(id, companyID, name, volume, measureID, price, productTypeID, shelfLife, currencyID, errorMessage))
		{
			if (!AddPriceData(globalVar, ormasDal, id, price, currencyID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}				
			if (oldPrice != price)
			{
				if (!RecalculateStock(globalVar, ormasDal, id, oldPrice, price, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				if (!UpdateSpecifications(globalVar, ormasDal, id, oldPrice, price, errorMessage))
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

	std::string Product::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != companyID || !name.empty() || 0 != volume || 0 != measureID || 0 != price || 0 != productTypeID 
			|| 0 != shelfLife || 0 != currencyID)
		{
			return ormasDal.GetFilterForProduct(id, companyID, name, volume, measureID, price, productTypeID, shelfLife, currencyID);
		}
		return "";
	}

	std::string Product::GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> prodIDList)
	{
		if (prodIDList.size()>0)
		{
			return ormasDal.GetINFilterForProductID(prodIDList);
		}
		return "";
	}

	std::string Product::GenerateLikeFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string searchKey)
	{
		if (!searchKey.empty())
		{
			return ormasDal.GetLikeFilterForProductName(searchKey);
		}
		return "";
	}

	bool Product::GetProductByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productsViewCollection> productVector = ormasDal.GetProducts(errorMessage, filter);
		if (0 != productVector.size())
		{
			id = std::get<0>(productVector.at(0));
			name = std::get<1>(productVector.at(0));
			price = std::get<2>(productVector.at(0));
			volume = std::get<4>(productVector.at(0));
			shelfLife = std::get<7>(productVector.at(0));
			companyID = std::get<9>(productVector.at(0));
			measureID = std::get<10>(productVector.at(0));
			productTypeID = std::get<11>(productVector.at(0));
			currencyID = std::get<12>(productVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find product with this id";
		}
		return false;
	}
	
	bool Product::IsEmpty()
	{
		if(0 == id && name == "" && 0 == price && 0 == volume && 0 == shelfLife && 0 == companyID 
			&& 0 == measureID && 0 == productTypeID && 0 == currencyID)
			return true;
		return false;
	}

	void Product::Clear()
	{
		id = 0;
		name.clear();
		price = 0;
		volume = 0;
		shelfLife = 0;
		companyID = 0;
		measureID = 0;
		productTypeID = 0;
		currencyID = 0;
	}

	void Product::TrimStrings(std::string& pName)
	{
		if (!pName.empty())
			boost::trim(pName);
	}

	bool Product::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double price,
		int curID, std::string& errorMessage)
	{
		Product product;
		product.Clear();
		errorMessage.clear();
		product.SetCompanyID(cID);
		product.SetName(pName);
		product.SetVolume(vol);
		product.SetMeasureID(mID);
		product.SetPrice(price);
		product.SetCurrencyID(curID);
		std::string filter = product.GenerateFilter(ormasDal);
		std::vector<DataLayer::productsViewCollection> productVector = ormasDal.GetProducts(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productVector.size())
		{
			return false;
		}
		errorMessage = "Product with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Product::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Product product;
		product.Clear();
		errorMessage.clear();
		product.SetCompanyID(companyID);
		product.SetName(name);
		product.SetVolume(volume);
		product.SetMeasureID(measureID);
		product.SetPrice(price);
		product.SetCurrencyID(currencyID);
		std::string filter = product.GenerateFilter(ormasDal);
		std::vector<DataLayer::productsViewCollection> productVector = ormasDal.GetProducts(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productVector.size())
		{
			return false;
		}
		errorMessage = "Product with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Product::AddPriceData(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double pPrice, int curID, std::string& errorMessage)
	{
		Price pri;
		pri.SetDate(ormasDal.GetSystemDateTime());
		pri.SetValue(pPrice);
		pri.SetCurrencyID(curID);
		pri.SetProductID(pID);
		if (pri.CreatePrice(globalVar, ormasDal, errorMessage))
			return true;
		return false;
	}

	double Product::GetCurrentPrice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		Product product;
		if (product.GetProductByID(globalVar, ormasDal, pID, errorMessage))
			return product.GetPrice();
		return 0;
	}

	bool Product::UpdateSpecifications(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage)
	{
		Specification spec;
		if (spec.UpdateSpecificationByProductID(globalVar, ormasDal, pID, oldPrice, newPrice, errorMessage))
			return true;
		return false;
	}
	bool Product::RecalculateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage)
	{
		Stock stock;
		if (stock.RecalculateStock(globalVar, ormasDal, pID, oldPrice, newPrice, errorMessage))
			return true;
		return false;
	}
}