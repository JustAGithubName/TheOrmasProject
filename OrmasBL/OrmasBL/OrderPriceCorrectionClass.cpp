#include "stdafx.h"
#include "OrderPriceCorrectionClass.h"

namespace BusinessLayer{
	OrderPriceCorrection::OrderPriceCorrection(DataLayer::orderPriceCorrectionCollection pCollection)
	{
		id = std::get<0>(pCollection);
		orderID = std::get<1>(pCollection);
		priceExtensionID = std::get<2>(pCollection);
		orderListID = std::get<3>(pCollection);
		standartValue = std::get<4>(pCollection);
		newValue = std::get<5>(pCollection);
	}
	OrderPriceCorrection::OrderPriceCorrection()
	{
		id = 0;
		orderID = 0;
		priceExtensionID =0;
		orderListID = 0;
		standartValue = 0;
		newValue = 0;
	}

	int OrderPriceCorrection::GetID()
	{
		return id;
	}

	int OrderPriceCorrection::GetOrderID()
	{
		return orderID;
	}

	int OrderPriceCorrection::GetPriceExtensionID()
	{
		return priceExtensionID;
	}

	int OrderPriceCorrection::GetOrderListID()
	{
		return orderListID;
	}

	double OrderPriceCorrection::GetStandartValue()
	{
		return standartValue;
	}

	double OrderPriceCorrection::GetNewValue()
	{
		return newValue;
	}

	
	void OrderPriceCorrection::SetID(int pID)
	{
		id = pID;
	}

	void OrderPriceCorrection::SetOrderID(int oOrderID)
	{
		orderID = oOrderID;
	}

	void OrderPriceCorrection::SetPriceExtensionID(int pExtensionID)
	{
		priceExtensionID = pExtensionID;
	}

	void OrderPriceCorrection::SetOrderListID(int oListID)
	{
		orderListID = oListID;
	}

	void OrderPriceCorrection::SetStandartValue(double sValue)
	{
		standartValue = sValue;
	}

	void OrderPriceCorrection::SetNewValue(double nValue)
	{
		newValue = nValue;
	}

	
	bool OrderPriceCorrection::CreateOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, oID, peID, olID, sValue, nValue, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		orderID = oID;
		priceExtensionID = peID;
		orderListID = olID;
		standartValue = sValue;
		newValue = nValue;
		if (0 != id && ormasDal.CreateOrderPriceCorrection(id, orderID, priceExtensionID, orderListID, standartValue, newValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool OrderPriceCorrection::CreateOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateOrderPriceCorrection(id, orderID, priceExtensionID, orderListID, standartValue, newValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool OrderPriceCorrection::DeleteOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteOrderPriceCorrection(id, errorMessage))
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

	bool OrderPriceCorrection::UpdateOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage)
	{
		orderID = oID;
		priceExtensionID = peID;
		orderListID = olID;
		standartValue = sValue;
		newValue = nValue;
		if (0 != id && ormasDal.UpdateOrderPriceCorrection(id, orderID, priceExtensionID, orderListID, standartValue, newValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool OrderPriceCorrection::UpdateOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateOrderPriceCorrection(id, orderID, priceExtensionID, orderListID, standartValue, newValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string OrderPriceCorrection::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != orderID || 0 != priceExtensionID || 0 != orderListID || 0 != standartValue || 0 != newValue)
		{
			return ormasDal.GetFilterForOrderPriceCorrection(id, orderID, priceExtensionID, orderListID, standartValue, newValue);
		}
		return "";
	}

	bool OrderPriceCorrection::GetOrderPriceCorrectionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::orderPriceCorrectionCollection> OrderPriceCorrectionVector = ormasDal.GetOrderPriceCorrection(errorMessage, filter);
		if (0 != OrderPriceCorrectionVector.size())
		{
			id = std::get<0>(OrderPriceCorrectionVector.at(0));
			orderID = std::get<1>(OrderPriceCorrectionVector.at(0));
			priceExtensionID = std::get<2>(OrderPriceCorrectionVector.at(0));
			orderListID = std::get<3>(OrderPriceCorrectionVector.at(0));
			standartValue = std::get<4>(OrderPriceCorrectionVector.at(0));
			newValue = std::get<5>(OrderPriceCorrectionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find order price correction with this id";
		}
		return false;
	}

	bool OrderPriceCorrection::GetOrderPriceCorrectionByPriceExtensionID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		priceExtensionID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::orderPriceCorrectionCollection> OrderPriceCorrectionVector = ormasDal.GetOrderPriceCorrection(errorMessage, filter);
		if (0 != OrderPriceCorrectionVector.size())
		{
			id = std::get<0>(OrderPriceCorrectionVector.at(0));
			orderID = std::get<1>(OrderPriceCorrectionVector.at(0));
			priceExtensionID = std::get<2>(OrderPriceCorrectionVector.at(0));
			orderListID = std::get<3>(OrderPriceCorrectionVector.at(0));
			standartValue = std::get<4>(OrderPriceCorrectionVector.at(0));
			newValue = std::get<5>(OrderPriceCorrectionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find order price correction with this id";
		}
		return false;
	}

	bool OrderPriceCorrection::GetOrderPriceCorrectionByOrderListID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int olID, std::string& errorMessage)
	{
		if (olID <= 0)
			return false;
		orderListID = olID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::orderPriceCorrectionCollection> OrderPriceCorrectionVector = ormasDal.GetOrderPriceCorrection(errorMessage, filter);
		if (0 != OrderPriceCorrectionVector.size())
		{
			id = std::get<0>(OrderPriceCorrectionVector.at(0));
			orderID = std::get<1>(OrderPriceCorrectionVector.at(0));
			priceExtensionID = std::get<2>(OrderPriceCorrectionVector.at(0));
			orderListID = std::get<3>(OrderPriceCorrectionVector.at(0));
			standartValue = std::get<4>(OrderPriceCorrectionVector.at(0));
			newValue = std::get<5>(OrderPriceCorrectionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find order price correction with this id";
		}
		return false;
	}

	bool OrderPriceCorrection::GetOrderPriceCorrectionByOrderID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		orderID = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::orderPriceCorrectionCollection> OrderPriceCorrectionVector = ormasDal.GetOrderPriceCorrection(errorMessage, filter);
		if (0 != OrderPriceCorrectionVector.size())
		{
			id = std::get<0>(OrderPriceCorrectionVector.at(0));
			orderID = std::get<1>(OrderPriceCorrectionVector.at(0));
			priceExtensionID = std::get<2>(OrderPriceCorrectionVector.at(0));
			orderListID = std::get<3>(OrderPriceCorrectionVector.at(0));
			standartValue = std::get<4>(OrderPriceCorrectionVector.at(0));
			newValue = std::get<5>(OrderPriceCorrectionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find order price correction with this id";
		}
		return false;
	}

	

	bool OrderPriceCorrection::IsEmpty()
	{
		if (0 == id && 0 == orderID  && 0.0 == standartValue  && 0.0 == newValue && 0 == priceExtensionID && 0 == orderListID)
			return true;
		return false;
	}

	void OrderPriceCorrection::Clear()
	{
		id = 0;
		orderID = 0;
		priceExtensionID = 0;
		orderListID = 0;
		standartValue = 0;
		newValue = 0;
	}

	bool OrderPriceCorrection::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage)
	{
		OrderPriceCorrection orderPriceCorrection;
		orderPriceCorrection.Clear();
		errorMessage.clear();
		orderPriceCorrection.SetOrderID(oID);
		orderPriceCorrection.SetPriceExtensionID(peID);
		orderPriceCorrection.SetOrderListID(olID);
		orderPriceCorrection.SetStandartValue(sValue);
		orderPriceCorrection.SetNewValue(nValue);
		std::string filter = orderPriceCorrection.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderPriceCorrectionCollection> orderPriceCorrectionVector = ormasDal.GetOrderPriceCorrection(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == orderPriceCorrectionVector.size())
		{
			return false;
		}
		errorMessage = "Order price correction with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool OrderPriceCorrection::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		OrderPriceCorrection orderPriceCorrection;
		orderPriceCorrection.Clear();
		errorMessage.clear();
		orderPriceCorrection.SetOrderID(orderID);
		orderPriceCorrection.SetPriceExtensionID(priceExtensionID);
		orderPriceCorrection.SetOrderListID(orderListID);
		orderPriceCorrection.SetStandartValue(standartValue);
		orderPriceCorrection.SetNewValue(newValue);
		std::string filter = orderPriceCorrection.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderPriceCorrectionCollection> orderPriceCorrectionVector = ormasDal.GetOrderPriceCorrection(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == orderPriceCorrectionVector.size())
		{
			return false;
		}
		errorMessage = "Order price correction with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}