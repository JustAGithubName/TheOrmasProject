#include "stdafx.h"
#include "StockLimitClass.h"
#include "ProductClass.h"
#include "StockClass.h"


namespace BusinessLayer
{
	StockLimit::StockLimit(DataLayer::stockLimitCollection sCollection)
	{
		id = std::get<0>(sCollection);
		stockID = std::get<1>(sCollection);
		productID = std::get<2>(sCollection);
		minValue = std::get<3>(sCollection);
		maxValue = std::get<4>(sCollection);
	}

	int StockLimit::GetID()
	{
		return id;
	}

	int StockLimit::GetProductID()
	{
		return productID;
	}
	int StockLimit::GetStockID()
	{
		return stockID;
	}

	double StockLimit::GetMinValue()
	{
		return minValue;
	}

	double StockLimit::GetMaxValue()
	{
		return maxValue;
	}

	
	void StockLimit::SetID(int sID)
	{
		id = sID;
	}

	void StockLimit::SetStockID(int sStockID)
	{
		stockID = sStockID;
	}

	void StockLimit::SetProductID(int sProductID)
	{
		productID = sProductID;
	}
	void StockLimit::SetMinValue(double sMinValue)
	{
		minValue = sMinValue;
	}
	void StockLimit::SetMaxValue(double sMaxValue)
	{
		maxValue = sMaxValue;
	}
	
	bool StockLimit::CreateStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal,int sID, int pID, double sMin, double sMax, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		stockID = sID;
		productID = pID;
		minValue = sMin;
		maxValue = sMax;
		if (0 != id && ormasDal.CreateStockLimit(id, stockID, productID, minValue, maxValue, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockLimit::CreateStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateStockLimit(id, stockID, productID, minValue, maxValue, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockLimit::DeleteStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteStockLimit(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool StockLimit::UpdateStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, double sMin, double sMax, std::string& errorMessage)
	{
		productID = pID;
		stockID = sID;
		minValue = sMin;
		maxValue = sMax;
		if (0 != id && ormasDal.UpdateStockLimit(id, stockID, productID, minValue, maxValue, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool StockLimit::UpdateStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateStockLimit(id, stockID, productID, minValue, maxValue, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string StockLimit::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != minValue || 0 != maxValue || 0 != stockID)
		{
			return ormasDal.GetFilterForStockLimit(id, stockID, productID, minValue, maxValue);
		}
		return "";
	}

	bool StockLimit::GetStockLimitByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stlID, std::string& errorMessage)
	{
		if (stlID <= 0)
			return false;
		id = stlID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockLimitViewCollection> stockLimitVector = ormasDal.GetStockLimit(errorMessage, filter);
		if (0 != stockLimitVector.size())
		{
			id = std::get<0>(stockLimitVector.at(0));
			stockID = std::get<5>(stockLimitVector.at(0));
			productID = std::get<6>(stockLimitVector.at(0));
			minValue = std::get<3>(stockLimitVector.at(0));
			maxValue = std::get<4>(stockLimitVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find StockLimit with this id";
		}
		return false;
	}

	bool StockLimit::GetStockLimitByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockLimitViewCollection> stockLimitVector = ormasDal.GetStockLimit(errorMessage, filter);
		if (0 != stockLimitVector.size())
		{
			id = std::get<0>(stockLimitVector.at(0));
			stockID = std::get<5>(stockLimitVector.at(0));
			productID = std::get<6>(stockLimitVector.at(0));
			minValue = std::get<3>(stockLimitVector.at(0));
			maxValue = std::get<4>(stockLimitVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find StockLimit with this id";
		}
		return false;
	}

	bool StockLimit::GetStockLimitByStockID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		stockID = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockLimitViewCollection> stockLimitVector = ormasDal.GetStockLimit(errorMessage, filter);
		if (0 != stockLimitVector.size())
		{
			id = std::get<0>(stockLimitVector.at(0));
			stockID = std::get<5>(stockLimitVector.at(0));
			productID = std::get<6>(stockLimitVector.at(0));
			minValue = std::get<3>(stockLimitVector.at(0));
			maxValue = std::get<4>(stockLimitVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find StockLimit with this id";
		}
		return false;
	}

	bool StockLimit::IsEmpty()
	{
		if (0 == id && 0 == minValue && 0 == maxValue && 0 == productID && 0 == stockID)
			return true;
		return false;
	}

	void StockLimit::Clear()
	{
		id = 0;
		minValue = 0;
		maxValue = 0;
		productID = 0;
		stockID = 0;
	}

	bool StockLimit::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int sID, std::string& errorMessage)
	{
		StockLimit stockLimit;
		stockLimit.Clear();
		errorMessage.clear();
		stockLimit.SetProductID(pID);
		stockLimit.SetStockID(sID);
		std::string filter = stockLimit.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockLimitViewCollection> stockLimitVector = ormasDal.GetStockLimit(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == stockLimitVector.size())
		{
			return false;
		}
		errorMessage = "StockLimit with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool StockLimit::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		StockLimit stockLimit;
		stockLimit.Clear();
		errorMessage.clear();
		stockLimit.SetProductID(productID);
		stockLimit.SetStockID(stockID);
		std::string filter = stockLimit.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockLimitViewCollection> stockLimitVector = ormasDal.GetStockLimit(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == stockLimitVector.size())
		{
			return false;
		}
		errorMessage = "StockLimit with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}