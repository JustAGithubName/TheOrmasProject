#include "stdafx.h"
#include "OrderListClass.h"
#include "PriceExtensionClass.h"
#include "OrderPriceCorrectionClass.h"

namespace BusinessLayer
{
	OrderList::OrderList(DataLayer::orderListCollection oListCollection)
	{
		id = std::get<0>(oListCollection);
		orderID = std::get<1>(oListCollection);
		productID = std::get<2>(oListCollection);
		count = std::get<3>(oListCollection);
		sum = std::get<4>(oListCollection);
		statusID = std::get<5>(oListCollection);
		currencyID = std::get<6>(oListCollection);
	}

	int OrderList::GetID()
	{
		return id;
	}

	int OrderList::GetOrderID()
	{
		return orderID;
	}

	int OrderList::GetProductID()
	{
		return productID;
	}

	double OrderList::GetCount()
	{
		return count;
	}

	double OrderList::GetSum()
	{
		return sum;
	}

	int OrderList::GetStatusID()
	{
		return statusID;
	}

	int OrderList::GetCurrencyID()
	{
		return currencyID;
	}

	void OrderList::SetID(int pID)
	{
		id = pID;
	}
	void OrderList::SetOrderID(int pOrderID)
	{
		orderID = pOrderID;
	}
	void OrderList::SetProductID(int pProductID)
	{
		productID = pProductID;
	}
	void OrderList::SetCount(double pCount)
	{
		count = pCount;
	}
	void OrderList::SetSum(double pSum)
	{
		sum = pSum;
	}
	void OrderList::SetStatusID(int pStatusID)
	{
		statusID = pStatusID;
	}
	void OrderList::SetCurrencyID(int pCurrencyID)
	{
		currencyID = pCurrencyID;
	}

	bool OrderList::CreateOrderList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int sID, int cID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		orderID = oID;
		productID = pID;
		count = olCount;
		sum = olSum;
		statusID = sID;
		currencyID = cID;
		int priceExtensionID = 0;
		double oldValue = sum;
		double extendedPrice = GetExtendedPrice(globalVar, ormasDal, productID, priceExtensionID, errorMessage);
		if (extendedPrice != 0)
			sum = sum + count*extendedPrice;
		if (0 != id && ormasDal.CreateOrderList(id, orderID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			if (priceExtensionID > 0)
			{
				OrderPriceCorrection opCorrection;
				opCorrection.SetOrderID(orderID);
				opCorrection.SetOrderListID(id);
				opCorrection.SetPriceExtensionID(priceExtensionID);
				opCorrection.SetStandartValue(oldValue);
				opCorrection.SetNewValue(sum);
				if (!opCorrection.CreateOrderPriceCorrection(globalVar, ormasDal, errorMessage))
					return false;
			}
			return true;
		}
		return false;
	}
	bool OrderList::CreateOrderList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		int priceExtensionID = 0;
		double oldValue = sum;
		double extendedPrice = GetExtendedPrice(globalVar, ormasDal, productID, priceExtensionID, errorMessage);
		if (extendedPrice != 0)
			sum = sum + count*extendedPrice;
		if (0 != id && ormasDal.CreateOrderList(id, orderID,productID, count, sum, statusID, currencyID, errorMessage))
		{
			if (priceExtensionID > 0)
			{
				OrderPriceCorrection opCorrection;
				opCorrection.SetOrderID(orderID);
				opCorrection.SetOrderListID(id);
				opCorrection.SetPriceExtensionID(priceExtensionID);
				opCorrection.SetStandartValue(oldValue);
				opCorrection.SetNewValue(sum);
				if (!opCorrection.CreateOrderPriceCorrection(globalVar, ormasDal, errorMessage))
					return false;
			}
			return true;
		}
		return false;
	}
	bool OrderList::DeleteOrderList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInOrderList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool OrderList::DeleteListByOrderID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		orderID = oID;
		if (ormasDal.DeleteListByOrderID(orderID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool OrderList::UpdateOrderList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int sID, int cID, std::string& errorMessage)
	{
		orderID = oID;
		productID = pID;
		count = olCount;
		sum = olSum;
		statusID = sID;
		currencyID = cID;
		int priceExtensionID = 0;
		double oldValue = sum;
		double extendedPrice = GetExtendedPrice(globalVar, ormasDal, productID, priceExtensionID, errorMessage);
		if (extendedPrice != 0)
			sum = sum + count*extendedPrice;
		if (0 != id && ormasDal.UpdateOrderList(id, orderID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			if (priceExtensionID > 0)
			{
				OrderPriceCorrection opCorrection;
				opCorrection.SetOrderID(orderID);
				opCorrection.SetOrderListID(id);
				opCorrection.SetPriceExtensionID(priceExtensionID);
				opCorrection.SetStandartValue(oldValue);
				opCorrection.SetNewValue(sum);
				if (!opCorrection.CreateOrderPriceCorrection(globalVar, ormasDal, errorMessage))
					return false;
			}
			return true;
		}
		return false;
	}
	bool OrderList::UpdateOrderList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		int priceExtensionID = 0;
		double oldValue = sum;
		double extendedPrice = GetExtendedPrice(globalVar, ormasDal, productID, priceExtensionID, errorMessage);
		if (extendedPrice != 0)
			sum = sum + count*extendedPrice;
		if (0 != id && ormasDal.UpdateOrderList(id, orderID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			if (priceExtensionID > 0)
			{
				OrderPriceCorrection opCorrection;
				opCorrection.SetOrderID(orderID);
				opCorrection.SetOrderListID(id);
				opCorrection.SetPriceExtensionID(priceExtensionID);
				opCorrection.SetStandartValue(oldValue);
				opCorrection.SetNewValue(sum);
				if (!opCorrection.CreateOrderPriceCorrection(globalVar, ormasDal, errorMessage))
					return false;
			}
			return true;
		}
		return false;
	}

	std::string OrderList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != orderID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForOrderList(id, orderID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool OrderList::GetOrderListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::orderListViewCollection> orderListVector = ormasDal.GetOrderList(errorMessage, filter);
		if (0 != orderListVector.size())
		{
			id = std::get<0>(orderListVector.at(0));
			orderID = std::get<1>(orderListVector.at(0));
			count = std::get<7>(orderListVector.at(0));
			sum = std::get<8>(orderListVector.at(0));
			productID = std::get<11>(orderListVector.at(0));
			statusID = std::get<12>(orderListVector.at(0));
			currencyID = std::get<13>(orderListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find order list with this id";
		}
		return false;
	}
	
	bool OrderList::IsEmpty()
	{
		if (0 == id && 0 == orderID &&  0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void OrderList::Clear()
	{
		id = 0;
		orderID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool OrderList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int cID, std::string& errorMessage)
	{
		OrderList orderList;
		orderList.Clear();
		errorMessage.clear();
		orderList.SetOrderID(oID);
		orderList.SetProductID(pID);
		orderList.SetCount(olCount);
		orderList.SetSum(olSum);
		orderList.SetCurrencyID(cID);
		std::string filter = orderList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderListViewCollection> orderListVector = ormasDal.GetOrderList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == orderListVector.size())
		{
			return false;
		}
		errorMessage = "Order list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool OrderList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		OrderList orderList;
		orderList.Clear();
		errorMessage.clear();
		orderList.SetOrderID(orderID);
		orderList.SetProductID(productID);
		orderList.SetCount(count);
		orderList.SetSum(sum);
		orderList.SetCurrencyID(currencyID);
		std::string filter = orderList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderListViewCollection> orderListVector = ormasDal.GetOrderList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == orderListVector.size())
		{
			return false;
		}
		errorMessage = "Order list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	double OrderList::GetExtendedPrice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prodID, int& prExt, std::string& errorMessage)
	{
		PriceExtension pExension;
		if (!pExension.GetPriceExtensionByProductIDAndExpeditorID(globalVar, ormasDal, prodID, employeeID, errorMessage))
			return 0;
		if (pExension.GetValue() != 0)
		{
			prExt = pExension.GetID();
			return pExension.GetValue();
		}
		return 0;
	}
}