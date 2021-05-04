#include "stdafx.h"
#include "OrderRawListClass.h"
#include "ProductClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyClass.h"
#include "WarehouseClass.h"
#include "WarehouseEmployeeRelationClass.h"
#include <codecvt>



namespace BusinessLayer
{
	OrderRawList::OrderRawList(DataLayer::orderRawListCollection oListCollection)
	{
		id = std::get<0>(oListCollection);
		orderRawID = std::get<1>(oListCollection);
		productID = std::get<2>(oListCollection);
		count = std::get<3>(oListCollection);
		sum = std::get<4>(oListCollection);
		statusID = std::get<5>(oListCollection);
		currencyID = std::get<6>(oListCollection);
	}

	int OrderRawList::GetID()
	{
		return id;
	}

	int OrderRawList::GetOrderRawID()
	{
		return orderRawID;
	}

	int OrderRawList::GetProductID()
	{
		return productID;
	}

	double OrderRawList::GetCount()
	{
		return count;
	}

	double OrderRawList::GetSum()
	{
		return sum;
	}

	int OrderRawList::GetStatusID()
	{
		return statusID;
	}

	int OrderRawList::GetCurrencyID()
	{
		return currencyID;
	}

	void OrderRawList::SetID(int oID)
	{
		id = oID;
	}
	void OrderRawList::SetOrderRawID(int oOrderRawID)
	{
		orderRawID = oOrderRawID;
	}
	void OrderRawList::SetProductID(int oProductID)
	{
		productID = oProductID;
	}
	void OrderRawList::SetCount(double oCount)
	{
		count = oCount;
	}
	void OrderRawList::SetSum(double oSum)
	{
		sum = oSum;
	}
	void OrderRawList::SetStatusID(int oStatusID)
	{
		statusID = oStatusID;
	}
	void OrderRawList::SetCurrencyID(int oCurrencyID)
	{
		currencyID = oCurrencyID;
	}

	bool OrderRawList::CreateOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int sID, int cID, std::string& errorMessage)
	{
		int subAccID = GetSubaccountIDForEmployee(globalVar, ormasDal, errorMessage);
		if (0 == subAccID)
			return false;
		Product product;
		if (!product.GetProductByID(globalVar, ormasDal, pID, errorMessage))
			return false;
		if (product.GetPrice()*olCount > olSum || product.GetPrice()*olCount < olSum)
		{
			double newPrice = 0;
			newPrice = round(olSum / olCount * 1000) / 1000;
			if (newPrice != product.GetPrice())
			{
				product.SetPrice(newPrice);
				if (!product.UpdateProduct(globalVar, ormasDal,errorMessage))
					return false;
				double correctionValue = 0;
				correctionValue = round((newPrice*olCount - olSum) * 1000) / 1000;
				if (correctionValue != 0)
				{
					int companyID = product.GetCompanyID();
					int debAccID = 0;
					int credAccID = 0;
					CompanyAccountRelation caRel;
					Entry entry;
					if (correctionValue > 0)
					{
						debAccID = subAccID;
						credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
						entry.SetValue(correctionValue);
					}
					if (correctionValue < 0)
					{
						debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
						credAccID = subAccID;
						entry.SetValue(correctionValue* (-1));
					}
					if (0 == debAccID || 0 == credAccID)
						return false;
					entry.SetDate(ormasDal.GetSystemDateTime());
					entry.SetDebitingAccountID(debAccID);
					entry.SetCreditingAccountID(credAccID);
					std::string entrytext;
					entrytext += wstring_to_utf8(L"Коррекция суммы продукта \"");
					entrytext += product.GetName();
					entrytext += wstring_to_utf8(L"\". Округление цены продукта для точности суммы на складе.");
					entry.SetDescription(entrytext);
					EntryOperationRelation eoRelation;
					if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
					{
						eoRelation.SetEntryID(entry.GetID());
						eoRelation.SetOperationID(id);
						if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
			}
		}
		id = ormasDal.GenerateID();
		orderRawID = oID;
		productID = pID;
		count = olCount;
		sum = olSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateOrderRawList(id, orderRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool OrderRawList::CreateOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		int subAccID = GetSubaccountIDForEmployee(globalVar, ormasDal, errorMessage);
		if (0 == subAccID)
			return false;
		Product product;
		if (!product.GetProductByID(globalVar, ormasDal, productID, errorMessage))
			return false;
		if (product.GetPrice()*count > sum || product.GetPrice()*count < sum)
		{
			double newPrice = 0;
			newPrice = round(sum / count * 1000) / 1000;
			if (newPrice != product.GetPrice())
			{
				product.SetPrice(newPrice);
				if (!product.UpdateProduct(globalVar, ormasDal, errorMessage))
					return false;
				double correctionValue = 0;
				correctionValue = round((newPrice*count - sum) * 1000) / 1000;
				if (correctionValue != 0)
				{
					int companyID = product.GetCompanyID();
					int debAccID = 0;
					int credAccID = 0;
					CompanyAccountRelation caRel;
					Entry entry;
					if (correctionValue > 0)
					{
						debAccID = subAccID;
						credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
						entry.SetValue(correctionValue);
					}
					if (correctionValue < 0)
					{
						debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
						credAccID = subAccID;
						entry.SetValue(correctionValue* (-1));
					}
					if (0 == debAccID || 0 == credAccID)
						return false;
					entry.SetDate(ormasDal.GetSystemDateTime());
					entry.SetDebitingAccountID(debAccID);
					entry.SetCreditingAccountID(credAccID);
					std::string entrytext;
					entrytext += wstring_to_utf8(L"Коррекция суммы продукта \"");
					entrytext += product.GetName();
					entrytext += wstring_to_utf8(L"\". Округление цены продукта для точности суммы на складе.");
					entry.SetDescription(entrytext);
					EntryOperationRelation eoRelation;
					if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
					{
						eoRelation.SetEntryID(entry.GetID());
						eoRelation.SetOperationID(id);
						if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
			}
		}
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateOrderRawList(id, orderRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool OrderRawList::DeleteOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInOrderRawList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool OrderRawList::DeleteListByOrderRawID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		orderRawID = oID;
		if (ormasDal.DeleteListByOrderRawID(orderRawID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool OrderRawList::UpdateOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int sID, int cID, std::string& errorMessage)
	{
		orderRawID = oID;
		productID = pID;
		count = olCount;
		sum = olSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateOrderRawList(id, orderRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool OrderRawList::UpdateOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateOrderRawList(id, orderRawID, productID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string OrderRawList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != orderRawID || 0 != productID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForOrderRawList(id, orderRawID, productID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool OrderRawList::GetOrderRawListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		id = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> orderRawListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (0 != orderRawListVector.size())
		{
			id = std::get<0>(orderRawListVector.at(0));
			orderRawID = std::get<1>(orderRawListVector.at(0));
			count = std::get<7>(orderRawListVector.at(0));
			sum = std::get<8>(orderRawListVector.at(0));
			productID = std::get<11>(orderRawListVector.at(0));
			statusID = std::get<12>(orderRawListVector.at(0));
			currencyID = std::get<13>(orderRawListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find order raw list with this id";
		}
		return false;
	}

	bool OrderRawList::IsEmpty()
	{
		if (0 == id && 0 == orderRawID && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void OrderRawList::Clear()
	{
		id = 0;
		orderRawID = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool OrderRawList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int cID, std::string& errorMessage)
	{
		OrderRawList orderRawList;
		orderRawList.Clear();
		errorMessage.clear();
		orderRawList.SetOrderRawID(oID);
		orderRawList.SetProductID(pID);
		orderRawList.SetCount(olCount);
		orderRawList.SetSum(olSum);
		orderRawList.SetCurrencyID(cID);
		std::string filter = orderRawList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> orderRawListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == orderRawListVector.size())
		{
			return false;
		}
		errorMessage = "Order raw list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool OrderRawList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		OrderRawList orderRawList;
		orderRawList.Clear();
		errorMessage.clear();
		orderRawList.SetOrderRawID(orderRawID);
		orderRawList.SetProductID(productID);
		orderRawList.SetCount(count);
		orderRawList.SetSum(sum);
		orderRawList.SetCurrencyID(currencyID);
		std::string filter = orderRawList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> orderRawListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == orderRawListVector.size())
		{
			return false;
		}
		errorMessage = "Order raw list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::string OrderRawList::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}

	int OrderRawList::GetSubaccountIDForEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (0 == employeeID)
			return 0;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, employeeID, errorMessage))
			return 0;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return 0;
		return warehouse.GetSubaccountID();
	}
}