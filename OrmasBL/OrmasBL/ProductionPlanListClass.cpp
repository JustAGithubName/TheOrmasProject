#include "stdafx.h"
#include "ProductionPlanListClass.h"

namespace BusinessLayer
{
	ProductionPlanList::ProductionPlanList(DataLayer::productionPlanListCollection pListCollection)
	{
		id = std::get<0>(pListCollection);
		productionPlanID = std::get<1>(pListCollection);
		productID = std::get<2>(pListCollection);
		count = std::get<3>(pListCollection);
		sum = std::get<4>(pListCollection);
		statusID = std::get<5>(pListCollection);
		currencyID = std::get<6>(pListCollection);
	}

	int ProductionPlanList::GetID()
	{
		return id;
	}

	int ProductionPlanList::GetProductionPlanID()
	{
		return productionPlanID;
	}

	int ProductionPlanList::GetProductID()
	{
		return productID;
	}

	double ProductionPlanList::GetCount()
	{
		return count;
	}

	double ProductionPlanList::GetSum()
	{
		return sum;
	}

	int ProductionPlanList::GetStatusID()
	{
		return statusID;
	}

	int ProductionPlanList::GetCurrencyID()
	{
		return currencyID;
	}

	void ProductionPlanList::SetID(int pID)
	{
		id = pID;
	}
	void ProductionPlanList::SetProductionPlanID(int pProductionPlanID)
	{
		productionPlanID = pProductionPlanID;
	}
	void ProductionPlanList::SetProductID(int pProductID)
	{
		productID = pProductID;
	}
	void ProductionPlanList::SetCount(double pCount)
	{
		count = pCount;
	}
	void ProductionPlanList::SetSum(double pSum)
	{
		sum = pSum;
	}
	void ProductionPlanList::SetStatusID(int pStatusID)
	{
		statusID = pStatusID;
	}
	void ProductionPlanList::SetCurrencyID(int pCurrencyID)
	{
		currencyID = pCurrencyID;
	}

	bool ProductionPlanList::CreateProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ppID, int pID, double pplCount, double pplSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		productionPlanID = ppID;
		productID = pID;
		count = pplCount;
		sum = pplSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateProductionPlanList(id, productionPlanID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionPlanList::CreateProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateProductionPlanList(id, productionPlanID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionPlanList::DeleteProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInProductionPlanList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ProductionPlanList::DeleteListByProductionPlanID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		productionPlanID = oID;
		if (ormasDal.DeleteListByProductionPlanID(productionPlanID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool ProductionPlanList::UpdateProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int sID, int cID, std::string& errorMessage)
	{
		productionPlanID = oID;
		productID = pID;
		count = olCount;
		sum = olSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateProductionPlanList(id, productionPlanID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionPlanList::UpdateProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateProductionPlanList(id, productionPlanID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ProductionPlanList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productionPlanID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForProductionPlanList(id, productionPlanID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool ProductionPlanList::GetProductionPlanListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ppID, std::string& errorMessage)
	{
		if (ppID <= 0)
			return false;
		id = ppID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productionPlanListViewCollection> productionPlanListVector = ormasDal.GetProductionPlanList(errorMessage, filter);
		if (0 != productionPlanListVector.size())
		{
			id = std::get<0>(productionPlanListVector.at(0));
			productionPlanID = std::get<1>(productionPlanListVector.at(0));
			count = std::get<7>(productionPlanListVector.at(0));
			sum = std::get<8>(productionPlanListVector.at(0));
			productID = std::get<11>(productionPlanListVector.at(0));
			statusID = std::get<12>(productionPlanListVector.at(0));
			currencyID = std::get<13>(productionPlanListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find production plan list with this id";
		}
		return false;
	}

	bool ProductionPlanList::IsEmpty()
	{
		if (0 == id && 0 == productionPlanID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ProductionPlanList::Clear()
	{
		id = 0;
		productionPlanID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ProductionPlanList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ppID, int pID, double pplCount, double pplSum,
		int cID, std::string& errorMessage)
	{
		ProductionPlanList productionPlanList;
		productionPlanList.Clear();
		errorMessage.clear();
		productionPlanList.SetProductionPlanID(ppID);
		productionPlanList.SetProductID(pID);
		productionPlanList.SetCount(pplCount);
		productionPlanList.SetSum(pplSum);
		productionPlanList.SetCurrencyID(cID);
		std::string filter = productionPlanList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionPlanListViewCollection> productionPlanListVector = ormasDal.GetProductionPlanList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionPlanListVector.size())
		{
			return false;
		}
		errorMessage = "Production plan list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductionPlanList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ProductionPlanList productionPlanList;
		productionPlanList.Clear();
		errorMessage.clear();
		productionPlanList.SetProductionPlanID(productionPlanID);
		productionPlanList.SetProductID(productID);
		productionPlanList.SetCount(count);
		productionPlanList.SetSum(sum);
		productionPlanList.SetCurrencyID(currencyID);
		std::string filter = productionPlanList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionPlanListViewCollection> productionPlanListVector = ormasDal.GetProductionPlanList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionPlanListVector.size())
		{
			return false;
		}
		errorMessage = "Production plan list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}