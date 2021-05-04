#include "stdafx.h"
#include "ReceiptOtherStocksListClass.h"
#include "OtherStocksClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyClass.h"
#include "WarehouseClass.h"
#include "WarehouseEmployeeRelationClass.h"
#include <codecvt>



namespace BusinessLayer
{
	ReceiptOtherStocksList::ReceiptOtherStocksList(DataLayer::receiptOtherStocksListCollection oListCollection)
	{
		id = std::get<0>(oListCollection);
		receiptOtherStocksID = std::get<1>(oListCollection);
		otherStocksID = std::get<2>(oListCollection);
		count = std::get<3>(oListCollection);
		sum = std::get<4>(oListCollection);
		statusID = std::get<5>(oListCollection);
		currencyID = std::get<6>(oListCollection);
	}

	int ReceiptOtherStocksList::GetID()
	{
		return id;
	}

	int ReceiptOtherStocksList::GetReceiptOtherStocksID()
	{
		return receiptOtherStocksID;
	}

	int ReceiptOtherStocksList::GetOtherStocksID()
	{
		return otherStocksID;
	}

	double ReceiptOtherStocksList::GetCount()
	{
		return count;
	}

	double ReceiptOtherStocksList::GetSum()
	{
		return sum;
	}

	int ReceiptOtherStocksList::GetStatusID()
	{
		return statusID;
	}

	int ReceiptOtherStocksList::GetCurrencyID()
	{
		return currencyID;
	}

	void ReceiptOtherStocksList::SetID(int oID)
	{
		id = oID;
	}
	void ReceiptOtherStocksList::SetReceiptOtherStocksID(int oReceiptOtherStocksID)
	{
		receiptOtherStocksID = oReceiptOtherStocksID;
	}
	void ReceiptOtherStocksList::SetOtherStocksID(int oProductID)
	{
		otherStocksID = oProductID;
	}
	void ReceiptOtherStocksList::SetCount(double oCount)
	{
		count = oCount;
	}
	void ReceiptOtherStocksList::SetSum(double oSum)
	{
		sum = oSum;
	}
	void ReceiptOtherStocksList::SetStatusID(int oStatusID)
	{
		statusID = oStatusID;
	}
	void ReceiptOtherStocksList::SetCurrencyID(int oCurrencyID)
	{
		currencyID = oCurrencyID;
	}

	bool ReceiptOtherStocksList::CreateReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int sID, int cID, std::string& errorMessage)
	{
		int subAccID = GetSubaccountIDForEmployee(globalVar, ormasDal, errorMessage);
		if (0 == subAccID)
			return false;
		OtherStocks otherStocks;
		if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, pID, errorMessage))
			return false;
		if (otherStocks.GetPrice()*olCount > olSum || otherStocks.GetPrice()*olCount < olSum)
		{
			double newPrice = 0;
			newPrice = round(olSum / olCount * 1000) / 1000;
			if (newPrice != otherStocks.GetPrice())
			{
				otherStocks.SetPrice(newPrice);
				if (!otherStocks.UpdateOtherStocks(globalVar, ormasDal, errorMessage))
					return false;
				double correctionValue = 0;
				correctionValue = round((newPrice*olCount - olSum) * 1000) / 1000;
				if (correctionValue != 0)
				{
					int companyID = otherStocks.GetCompanyID();
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
					entrytext += otherStocks.GetName();
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
		receiptOtherStocksID = oID;
		otherStocksID = pID;
		count = olCount;
		sum = olSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateReceiptOtherStocksList(id, receiptOtherStocksID, otherStocksID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReceiptOtherStocksList::CreateReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		int subAccID = GetSubaccountIDForEmployee(globalVar, ormasDal, errorMessage);
		if (0 == subAccID)
			return false;
		OtherStocks otherStocks;
		if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, otherStocksID, errorMessage))
			return false;
		if (otherStocks.GetPrice()*count > sum || otherStocks.GetPrice()*count < sum)
		{
			double newPrice = 0;
			newPrice = round(sum / count * 1000) / 1000;
			if (newPrice != otherStocks.GetPrice())
			{
				otherStocks.SetPrice(newPrice);
				if (!otherStocks.UpdateOtherStocks(globalVar, ormasDal, errorMessage))
					return false;
				double correctionValue = 0;
				correctionValue = round((newPrice*count - sum) * 1000) / 1000;
				if (correctionValue != 0)
				{
					int companyID = otherStocks.GetCompanyID();
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
					entrytext += otherStocks.GetName();
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
		if (0 != id && ormasDal.CreateReceiptOtherStocksList(id, receiptOtherStocksID, otherStocksID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReceiptOtherStocksList::DeleteReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteItemInReceiptOtherStocksList(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}
	bool ReceiptOtherStocksList::DeleteListByReceiptOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		receiptOtherStocksID = oID;
		if (ormasDal.DeleteListByReceiptOtherStocksID(receiptOtherStocksID, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool ReceiptOtherStocksList::UpdateReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int sID, int cID, std::string& errorMessage)
	{
		receiptOtherStocksID = oID;
		otherStocksID = pID;
		count = olCount;
		sum = olSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateReceiptOtherStocksList(id, receiptOtherStocksID, otherStocksID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ReceiptOtherStocksList::UpdateReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateReceiptOtherStocksList(id, receiptOtherStocksID, otherStocksID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ReceiptOtherStocksList::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != receiptOtherStocksID || 0 != otherStocksID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForReceiptOtherStocksList(id, receiptOtherStocksID, otherStocksID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool ReceiptOtherStocksList::GetReceiptOtherStocksListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		id = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksListViewCollection> receiptOtherStocksListVector = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);
		if (0 != receiptOtherStocksListVector.size())
		{
			id = std::get<0>(receiptOtherStocksListVector.at(0));
			receiptOtherStocksID = std::get<1>(receiptOtherStocksListVector.at(0));
			count = std::get<7>(receiptOtherStocksListVector.at(0));
			sum = std::get<8>(receiptOtherStocksListVector.at(0));
			otherStocksID = std::get<11>(receiptOtherStocksListVector.at(0));
			statusID = std::get<12>(receiptOtherStocksListVector.at(0));
			currencyID = std::get<13>(receiptOtherStocksListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find receipt other stocks list with this id";
		}
		return false;
	}

	bool ReceiptOtherStocksList::IsEmpty()
	{
		if (0 == id && 0 == receiptOtherStocksID && 0 == count && 0 == sum && 0 == otherStocksID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ReceiptOtherStocksList::Clear()
	{
		id = 0;
		receiptOtherStocksID = 0;
		count = 0;
		sum = 0;
		otherStocksID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ReceiptOtherStocksList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
		int cID, std::string& errorMessage)
	{
		ReceiptOtherStocksList receiptOtherStocksList;
		receiptOtherStocksList.Clear();
		errorMessage.clear();
		receiptOtherStocksList.SetReceiptOtherStocksID(oID);
		receiptOtherStocksList.SetOtherStocksID(pID);
		receiptOtherStocksList.SetCount(olCount);
		receiptOtherStocksList.SetSum(olSum);
		receiptOtherStocksList.SetCurrencyID(cID);
		std::string filter = receiptOtherStocksList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksListViewCollection> receiptOtherStocksListVector = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == receiptOtherStocksListVector.size())
		{
			return false;
		}
		errorMessage = "Receipt other stocks list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ReceiptOtherStocksList::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ReceiptOtherStocksList receiptOtherStocksList;
		receiptOtherStocksList.Clear();
		errorMessage.clear();
		receiptOtherStocksList.SetReceiptOtherStocksID(receiptOtherStocksID);
		receiptOtherStocksList.SetOtherStocksID(otherStocksID);
		receiptOtherStocksList.SetCount(count);
		receiptOtherStocksList.SetSum(sum);
		receiptOtherStocksList.SetCurrencyID(currencyID);
		std::string filter = receiptOtherStocksList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksListViewCollection> receiptOtherStocksListVector = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == receiptOtherStocksListVector.size())
		{
			return false;
		}
		errorMessage = "Receipt other stocks list with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::string ReceiptOtherStocksList::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}

	int ReceiptOtherStocksList::GetSubaccountIDForEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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