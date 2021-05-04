#include "stdafx.h"
#include "ProductionListClass.h"


namespace BusinessLayer
{
	ProductionList::ProductionList(DataLayer::productionListCollection pListCollection)
	{
		id = std::get<0>(pListCollection);
		productionID = std::get<1>(pListCollection);
		productID = std::get<2>(pListCollection);
		count = std::get<3>(pListCollection);
		sum = std::get<4>(pListCollection);
		statusID = std::get<5>(pListCollection);
		currencyID = std::get<6>(pListCollection);
	}

	int ProductionList::GetID()
	{
		return id;
	}

	int ProductionList::GetProductionID()
	{
		return productionID;
	}

	int ProductionList::GetProductID()
	{
		return productID;
	}

	double ProductionList::GetCount()
	{
		return count;
	}

	double ProductionList::GetSum()
	{
		return sum;
	}

	int ProductionList::GetStatusID()
	{
		return statusID;
	}

	int ProductionList::GetCurrencyID()
	{
		return currencyID;
	}

	void ProductionList::SetID(int pID)
	{
		id = pID;
	}
	void ProductionList::SetProductionID(int pProductionID)
	{
		productionID = pProductionID;
	}
	void ProductionList::SetProductID(int pProductID)
	{
		productID = pProductID;
	}
	void ProductionList::SetCount(double pCount)
	{
		count = pCount;
	}
	void ProductionList::SetSum(double pSum)
	{
		sum = pSum;
	}
	void ProductionList::SetStatusID(int pStatusID)
	{
		statusID = pStatusID;
	}
	void ProductionList::SetCurrencyID(int pCurrencyID)
	{
		currencyID = pCurrencyID;
	}

	bool ProductionList::CreateProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int pID, double prCount, double prSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		productionID = prID;
		productID = pID;
		count = prCount;
		sum = prSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateProductionList(id, productionID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionList::CreateProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateProductionList(id, productionID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionList::DeleteProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{		
		if (ormasDal.DeleteItemInProductionList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ProductionList::DeleteListByProductionID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		productionID = pID;
		if (ormasDal.DeleteListByOrderID(productionID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ProductionList::UpdateProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int pID, double prCount, double prSum,
		int sID, int cID, std::string& errorMessage)
	{
		productionID = prID;
		productID = pID;
		count = prCount;
		sum = prSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateProductionList(id, productionID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionList::UpdateProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateProductionList(id, productionID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ProductionList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productionID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForProductionList(id, productionID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}
	
	std::string ProductionList::GenerateFilterForEnum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> vecProdnID)
	{
		if (vecProdnID.size()>0)
		{
			return ormasDal.GetFilterForProductionListInEnum(id, productionID, productID, count, sum, statusID, currencyID, vecProdnID);
		}
		return "";
	}

	bool ProductionList::GetProductionListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productionListViewCollection> productionListVector = ormasDal.GetProductionList(errorMessage, filter);
		if (0 != productionListVector.size())
		{
			id = std::get<0>(productionListVector.at(0));
			productionID = std::get<1>(productionListVector.at(0));
			count = std::get<7>(productionListVector.at(0));
			sum = std::get<8>(productionListVector.at(0));
			productID = std::get<11>(productionListVector.at(0));
			statusID = std::get<12>(productionListVector.at(0));
			currencyID = std::get<13>(productionListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Production list with this id";
		}
		return false;
	}
	
	bool ProductionList::IsEmpty()
	{
		if (0 == id && 0 == productionID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ProductionList::Clear()
	{
		id = 0;
		productionID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ProductionList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int pID, double plCount, double plSum,
		int cID, std::string& errorMessage)
	{
		ProductionList productionList;
		productionList.Clear();
		errorMessage.clear();
		productionList.SetProductionID(prID);
		productionList.SetProductID(pID);
		productionList.SetCount(plCount);
		productionList.SetSum(plSum);
		productionList.SetCurrencyID(cID);
		std::string filter = productionList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionListViewCollection> productionListVector = ormasDal.GetProductionList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionListVector.size())
		{
			return false;
		}
		errorMessage = "Production list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductionList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ProductionList productionList;
		productionList.Clear();
		errorMessage.clear();
		productionList.SetProductionID(productionID);
		productionList.SetProductID(productID);
		productionList.SetCount(count);
		productionList.SetSum(sum);
		productionList.SetCurrencyID(currencyID);
		std::string filter = productionList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionListViewCollection> productionListVector = ormasDal.GetProductionList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionListVector.size())
		{
			return false;
		}
		errorMessage = "Production list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::map<int, double> ProductionList::GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<int, double> mapProdCount;
		ProductionList rPList;
		rPList.SetProductionID(productionID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionListViewCollection> productListVector = ormasDal.GetProductionList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				mapProdCount.insert(std::make_pair(std::get<11>(item), std::get<7>(item)));
			}
		}
		return mapProdCount;
	}
}