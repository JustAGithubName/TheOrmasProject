#include "stdafx.h"
#include "LowValueStockClass.h"
#include "EntryOperationRelationClass.h"
#include "BalanceClass.h"
#include "ReceiptOtherStocksClass.h"
#include "ReceiptOtherStocksListClass.h"
#include "ReceiptOtherStocksListViewClass.h"
#include "ConsumeOtherStocksClass.h"
#include "ConsumeOtherStocksListClass.h"
#include "ConsumeOtherStocksListViewClass.h"
#include "OtherStocksClass.h"
#include "StatusClass.h"
#include "EntryClass.h"
#include "AccountClass.h"
#include "SubaccountClass.h"
#include "CompanyAccountRelationClass.h"
#include "WarehouseClass.h"
#include "WarehouseTypeClass.h"
#include "WarehouseEmployeeRelationClass.h"
#include "UserClass.h"
#include "LowValueStockChangeLogClass.h"
#include <codecvt>

namespace BusinessLayer
{
	LowValueStock::LowValueStock(DataLayer::lowValueStockCollection sCollection)
	{
		id = std::get<0>(sCollection);
		otherStocksID = std::get<1>(sCollection);
		count = std::get<2>(sCollection);
		sum = std::get<3>(sCollection);
		statusID = std::get<4>(sCollection);
		currencyID = std::get<5>(sCollection);
		warehouseID = std::get<6>(sCollection);
	}

	int LowValueStock::GetID()
	{
		return id;
	}

	int LowValueStock::GetOtherStocksID()
	{
		return otherStocksID;
	}

	double LowValueStock::GetCount()
	{
		return count;
	}

	double LowValueStock::GetSum()
	{
		return sum;
	}

	int LowValueStock::GetStatusID()
	{
		return statusID;
	}

	int LowValueStock::GetCurrencyID()
	{
		return currencyID;
	}

	int LowValueStock::GetWarehouseID()
	{
		return warehouseID;
	}

	void LowValueStock::SetID(int sID)
	{
		id = sID;
	}

	void LowValueStock::SetOtherStocksID(int sProductID)
	{
		otherStocksID = sProductID;
	}
	void LowValueStock::SetCount(double sCount)
	{
		count = sCount;
	}
	void LowValueStock::SetSum(double sSum)
	{
		sum = sSum;
	}
	void LowValueStock::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void LowValueStock::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void LowValueStock::SetWarehouseID(int sWarehouseID)
	{
		warehouseID = sWarehouseID;
	}

	bool LowValueStock::CreateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, double sCount, double sSum,
		int sID, int cID, int wID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		otherStocksID = osID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		if (0 != id && ormasDal.CreateLowValueStock(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			if (CreateLowValueStockChangeLog(globalVar, ormasDal, id, otherStocksID, count, sum, statusID, currencyID, warehouseID, errorMessage))
				return true;
		}
		return false;
	}
	bool LowValueStock::CreateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateLowValueStock(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			if (CreateLowValueStockChangeLog(globalVar, ormasDal, id, otherStocksID, count, sum, statusID, currencyID, warehouseID, errorMessage))
				return true;
		}
		return false;
	}
	bool LowValueStock::DeleteLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteLowValueStock(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool LowValueStock::UpdateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, double sCount, double sSum,
		int sID, int cID, int wID, std::string& errorMessage)
	{
		otherStocksID = osID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		if (count < 0 || sum < 0)
		{
			errorMessage += "Count or sum cannot be less then 0! Other stocks ID = ";
			errorMessage += std::to_string(otherStocksID);
			return false;
		}
		if (0 != id && ormasDal.UpdateLowValueStock(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			if (CreateLowValueStockChangeLog(globalVar, ormasDal, id, otherStocksID, count, sum, statusID, currencyID, warehouseID, errorMessage))
				return true;
		}
		return false;
	}
	bool LowValueStock::UpdateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage += "Count or sum cannot be less then 0! Other stocks ID = ";
			errorMessage += std::to_string(otherStocksID);
			return false;
		}
		if (0 != id && ormasDal.UpdateLowValueStock(id, otherStocksID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			if (CreateLowValueStockChangeLog(globalVar, ormasDal, id, otherStocksID, count, sum, statusID, currencyID, warehouseID, errorMessage))
				return true;
		}
		return false;
	}

	std::string LowValueStock::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != otherStocksID || 0 != count || 0 != sum || 0 != statusID || 0 != warehouseID)
		{
			return ormasDal.GetFilterForLowValueStock(id, otherStocksID, count, sum, statusID, currencyID, warehouseID);
		}
		return "";
	}

	bool LowValueStock::GetLowValueStockByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockViewCollection> lowValueStockVector = ormasDal.GetLowValueStock(errorMessage, filter);
		if (0 != lowValueStockVector.size())
		{
			id = std::get<0>(lowValueStockVector.at(0));
			count = std::get<6>(lowValueStockVector.at(0));
			sum = std::get<7>(lowValueStockVector.at(0));
			otherStocksID = std::get<12>(lowValueStockVector.at(0));
			statusID = std::get<13>(lowValueStockVector.at(0));
			currencyID = std::get<14>(lowValueStockVector.at(0));
			warehouseID = std::get<15>(lowValueStockVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock with this id";
		}
		return false;
	}

	bool LowValueStock::GetLowValueStockByOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, std::string& errorMessage)
	{
		if (osID <= 0)
			return false;
		otherStocksID = osID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockViewCollection> lowValueStockVector = ormasDal.GetLowValueStock(errorMessage, filter);
		if (0 != lowValueStockVector.size())
		{
			id = std::get<0>(lowValueStockVector.at(0));
			count = std::get<6>(lowValueStockVector.at(0));
			sum = std::get<7>(lowValueStockVector.at(0));
			otherStocksID = std::get<12>(lowValueStockVector.at(0));
			statusID = std::get<13>(lowValueStockVector.at(0));
			currencyID = std::get<14>(lowValueStockVector.at(0));
			warehouseID = std::get<15>(lowValueStockVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock with this id";
		}
		return false;
	}

	bool LowValueStock::GetLowValueStockByOtherStocksAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, int wID, std::string& errorMessage)
	{
		if (osID <= 0)
			return false;
		if (wID <= 0)
			return false;
		otherStocksID = osID;
		warehouseID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockViewCollection> lowValueStockVector = ormasDal.GetLowValueStock(errorMessage, filter);
		if (0 != lowValueStockVector.size())
		{
			id = std::get<0>(lowValueStockVector.at(0));
			count = std::get<6>(lowValueStockVector.at(0));
			sum = std::get<7>(lowValueStockVector.at(0));
			otherStocksID = std::get<12>(lowValueStockVector.at(0));
			statusID = std::get<13>(lowValueStockVector.at(0));
			currencyID = std::get<14>(lowValueStockVector.at(0));
			warehouseID = std::get<15>(lowValueStockVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find low value stock with this product ID and warehouse ID";
		}
		return false;
	}

	std::vector<int> LowValueStock::GetAllOtherStocksIDByWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		std::vector<int> othSIDList;
		if (wID <= 0)
			return othSIDList;
		warehouseID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockViewCollection> lowValueStockVector = ormasDal.GetLowValueStock(errorMessage, filter);
		if (0 < lowValueStockVector.size())
		{
			for each (auto weItem in lowValueStockVector)
			{
				othSIDList.push_back(std::get<12>(weItem));
			}
		}
		else
		{
			errorMessage = "Cannot find other stocks in these warehouse!";
		}
		return othSIDList;
	}

	bool LowValueStock::IsEmpty()
	{
		if (0 == id && 0 == count && 0 == sum && 0 == otherStocksID && 0 == statusID && 0 == currencyID && 0 == warehouseID)
			return true;
		return false;
	}

	void LowValueStock::Clear()
	{
		id = 0;
		count = 0;
		sum = 0;
		otherStocksID = 0;
		statusID = 0;
		currencyID = 0;
		warehouseID = 0;
	}

	bool LowValueStock::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, int wID, std::string& errorMessage)
	{
		LowValueStock lowValueStock;
		lowValueStock.Clear();
		errorMessage.clear();
		lowValueStock.SetOtherStocksID(osID);
		lowValueStock.SetWarehouseID(wID);
		std::string filter = lowValueStock.GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockViewCollection> lowValueStockVector = ormasDal.GetLowValueStock(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == lowValueStockVector.size())
		{
			return false;
		}
		errorMessage = "Low value stock with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool LowValueStock::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		LowValueStock lowValueStock;
		lowValueStock.Clear();
		errorMessage.clear();
		lowValueStock.SetOtherStocksID(otherStocksID);
		lowValueStock.SetWarehouseID(warehouseID);
		std::string filter = lowValueStock.GenerateFilter(ormasDal);
		std::vector<DataLayer::lowValueStockViewCollection> lowValueStockVector = ormasDal.GetLowValueStock(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == lowValueStockVector.size())
		{
			return false;
		}
		errorMessage = "Low value stock with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	
	bool LowValueStock::ChangingByReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rosID, int empID, std::string& errorMessage)
	{
		ReceiptOtherStocks rOthS;
		ReceiptOtherStocksList rOthSList;
		std::vector<ReceiptOtherStocksListView> rOthSListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		rOthSList.SetReceiptOtherStocksID(rosID);
		std::string filter = rOthSList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksListViewCollection> othSListVector = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);
		if (othSListVector.size() > 0)
		{
			for each (auto item in othSListVector)
			{
				rOthSListVec.push_back(ReceiptOtherStocksListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Other stocks list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rOthSListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpOthSt(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			LowValueStock lowValueStock;
			OtherStocks otherStocks;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rOthSListVec)
			{
				lowValueStock.Clear();
				otherStocks.Clear();
				status.Clear();
				if (!lowValueStock.GetLowValueStockByOtherStocksAndWarehouseID(globalVar, ormasDal, item.GetOtherStocksID(), warehouseID, errorMessage))
				{
					oldCount = lowValueStock.GetCount();
					oldSum = lowValueStock.GetSum();
					totalOldCount += lowValueStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					companyID = otherStocks.GetCompanyID();
					totalSum = totalSum + (item.GetSum());
					lowValueStock.SetOtherStocksID(item.GetOtherStocksID());
					lowValueStock.SetCount(item.GetCount());
					lowValueStock.SetSum(item.GetCount()*otherStocks.GetPrice());
					lowValueStock.SetCurrencyID(item.GetCurrencyID());
					lowValueStock.SetStatusID(status.GetID());
					lowValueStock.SetWarehouseID(warehouseID);
					if (!lowValueStock.CreateLowValueStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += lowValueStock.GetCount();
				}
				else
				{
					oldCount = lowValueStock.GetCount();
					oldSum = lowValueStock.GetSum();
					totalOldCount += lowValueStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					companyID = otherStocks.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					lowValueStock.SetCount(lowValueStock.GetCount() + item.GetCount());
					lowValueStock.SetSum(lowValueStock.GetSum() + (item.GetCount()*otherStocks.GetPrice()));
					if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(lowValueStock.GetCount() * 1000) / 1000)
						return false;
					if (std::round(otherStocks.GetPrice()*lowValueStock.GetCount() * 10) / 10 != std::round(lowValueStock.GetSum() * 10) / 10)
					{
						lowValueStock.SetSum(std::round(otherStocks.GetPrice()*lowValueStock.GetCount() * 1000) / 1000);
						if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					totalNewCount += lowValueStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt other stocks list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!rOthS.GetReceiptOtherStocksByID(globalVar, ormasDal, rosID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, rOthS.GetPurveyorID(), errorMessage))
			return false;
		CompanyAccountRelation caRel;
		int debAccID = subAccID;
		int credAccID = balance.GetSubaccountID();
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rosID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool LowValueStock::ChangingByReceiptOtherStocksReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rosID, int empID, std::string& errorMessage)
	{
		ReceiptOtherStocks rOthS;
		ReceiptOtherStocksList rOthSList;
		std::vector<ReceiptOtherStocksListView> rOthSListVec;
		double totalSum = 0.0;
		double newSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		rOthSList.SetReceiptOtherStocksID(rosID);
		std::string filter = rOthSList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksListViewCollection> othSListVector = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);
		if (othSListVector.size() > 0)
		{
			for each (auto item in othSListVector)
			{
				rOthSListVec.push_back(ReceiptOtherStocksListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt other stocks list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rOthSListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpOthSt(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			LowValueStock lowValueStock;
			OtherStocks otherStocks;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rOthSListVec)
			{
				lowValueStock.Clear();
				otherStocks.Clear();
				if (!lowValueStock.GetLowValueStockByOtherStocksAndWarehouseID(globalVar, ormasDal, item.GetOtherStocksID(), warehouseID, errorMessage))
				{
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					errorMessage = "ERROR! This other stocks is out of low value stock:";
					errorMessage += otherStocks.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (lowValueStock.GetCount() < item.GetCount())
					{
						if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough other stocks in the LowValueStock!";
						errorMessage += " Other stocks name:";
						errorMessage += otherStocks.GetName();
						errorMessage += ", Other stocks count:";
						errorMessage += std::to_string(lowValueStock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = lowValueStock.GetCount();
						oldSum = lowValueStock.GetSum();
						totalOldCount += lowValueStock.GetCount();
						totalChangingCount += item.GetCount();
						if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
							return false;
						companyID = otherStocks.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						newSum = newSum + std::round(item.GetCount()* otherStocks.GetPrice() * 1000) / 1000;
						lowValueStock.SetCount(lowValueStock.GetCount() - item.GetCount());
						if (0 == lowValueStock.GetCount())
						{
							lowValueStock.SetSum(0);
						}
						else
						{
							lowValueStock.SetSum((lowValueStock.GetSum() - std::round(item.GetCount()* otherStocks.GetPrice() * 1000) / 1000));
						}
						if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(lowValueStock.GetCount() * 1000) / 1000)
							return false;
						if (std::round(otherStocks.GetPrice()*lowValueStock.GetCount() * 10) / 10 != std::round(lowValueStock.GetSum() * 10) / 10)
						{
							lowValueStock.SetSum(std::round(otherStocks.GetPrice()*lowValueStock.GetCount() * 1000) / 1000);
							if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
							{
								//ormasDal.CancelTransaction(errorMessage);
								return false;
							}
						}
						totalNewCount += lowValueStock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt other stocks list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!rOthS.GetReceiptOtherStocksByID(globalVar, ormasDal, rosID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, rOthS.GetPurveyorID(), errorMessage))
			return false;
		CompanyAccountRelation caRel;
		int debAccID = subAccID;
		int credAccID = balance.GetSubaccountID();
		int acc55020ID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rosID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		double checkSum = totalSum - newSum;
		if (checkSum > 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, rosID, acc55020ID, checkSum, debAccID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		else if (checkSum < 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, rosID, debAccID, checkSum *(-1), acc55020ID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		return true;
	}



	bool LowValueStock::ChangingByReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		ReceiptOtherStocks rOthS;
		ReceiptOtherStocksList rOthSList;
		std::vector<ReceiptOtherStocksListView> rOthSListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		rOthSList.SetReceiptOtherStocksID(orID);
		std::string filter = rOthSList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksListViewCollection> othSListVector = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);
		if (othSListVector.size() > 0)
		{
			for each (auto item in othSListVector)
			{
				rOthSListVec.push_back(ReceiptOtherStocksListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt other stocks list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rOthSListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpOthSt(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			LowValueStock lowValueStock;
			OtherStocks otherStocks;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			for each (auto item in rOthSListVec)
			{
				lowValueStock.Clear();
				otherStocks.Clear();
				status.Clear();
				if (!lowValueStock.GetLowValueStockByOtherStocksAndWarehouseID(globalVar, ormasDal, item.GetOtherStocksID(), warehouseID, errorMessage))
				{
					oldCount = lowValueStock.GetCount();
					oldSum = lowValueStock.GetSum();
					totalOldCount += lowValueStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					companyID = otherStocks.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					lowValueStock.SetOtherStocksID(item.GetOtherStocksID());
					lowValueStock.SetCount(item.GetCount());
					lowValueStock.SetSum(item.GetSum());
					lowValueStock.SetCurrencyID(item.GetCurrencyID());
					lowValueStock.SetStatusID(status.GetID());
					lowValueStock.SetWarehouseID(warehouseID);
					if (!lowValueStock.CreateLowValueStock(globalVar, ormasDal, errorMessage))
					{
						return false;
					}
					totalNewCount += lowValueStock.GetCount();
				}
				else
				{
					oldCount = lowValueStock.GetCount();
					oldSum = lowValueStock.GetSum();
					totalOldCount += lowValueStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					companyID = otherStocks.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					lowValueStock.SetCount(lowValueStock.GetCount() + (item.GetCount() - pProdCountMap.find(otherStocks.GetID())->second));
					lowValueStock.SetSum(lowValueStock.GetSum() + (item.GetSum() - (pProdCountMap.find(otherStocks.GetID())->second * otherStocks.GetPrice())));
					if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(lowValueStock.GetCount() * 1000) / 1000)
						return false;
					if (std::round(otherStocks.GetPrice()*lowValueStock.GetCount() * 10) / 10 != std::round(lowValueStock.GetSum() * 10) / 10)
					{
						lowValueStock.SetSum(std::round(otherStocks.GetPrice()*lowValueStock.GetCount() * 1000) / 1000);
						if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					totalNewCount += lowValueStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt other stocks list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!rOthS.GetReceiptOtherStocksByID(globalVar, ormasDal, orID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, rOthS.GetPurveyorID(), errorMessage))
			return false;
		CompanyAccountRelation caRel;
		int debAccID = subAccID;
		int credAccID = balance.GetSubaccountID();
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, orID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool LowValueStock::ChangingByConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cosID, int lowValueStockEmpID, std::string& errorMessage)
	{
		ConsumeOtherStocksList cOSList;
		ConsumeOtherStocks cOthS;
		if (!cOthS.GetConsumeOtherStocksByID(globalVar, ormasDal, cosID, errorMessage))
			return false;
		std::vector<ConsumeOtherStocksListView> cOSListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cOSList.SetConsumeOtherStocksID(cosID);
		std::string filter = cOSList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksListViewCollection> othSListVector = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);
		if (othSListVector.size() > 0)
		{
			for each (auto item in othSListVector)
			{
				cOSListVec.push_back(ConsumeOtherStocksListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume other stocks list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		double totalOldSum = 0;
		double totalNewSum = 0;
		double totalChangingSum = 0;
		if (cOSListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConOthSt(globalVar, ormasDal, lowValueStockEmpID, warehouseID, subAccID, errorMessage))
				return false;
			LowValueStock lowValueStock;
			OtherStocks otherStocks;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cOSListVec)
			{
				lowValueStock.Clear();
				otherStocks.Clear();
				if (!lowValueStock.GetLowValueStockByOtherStocksAndWarehouseID(globalVar, ormasDal, item.GetOtherStocksID(), warehouseID, errorMessage))
				{
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					errorMessage = "ERROR! This other stocks is out of low value stock:";
					errorMessage += otherStocks.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (lowValueStock.GetCount() < item.GetCount())
					{
						if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough other stock in the low value stock!";
						errorMessage += " Other stock name:";
						errorMessage += otherStocks.GetName();
						errorMessage += ", Other stock count:";
						errorMessage += std::to_string(lowValueStock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = lowValueStock.GetCount();
						oldSum = lowValueStock.GetSum();
						if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
							return false;
						if (item.GetCount()*(lowValueStock.GetSum() / lowValueStock.GetCount()) != item.GetSum())
						{
							item.SetSum(item.GetCount()*(lowValueStock.GetSum() / lowValueStock.GetCount()));
							//item.Get = cOthS.GetStockEmployeeID();
							if (!item.UpdateConsumeOtherStocksList(globalVar, ormasDal, errorMessage))
								return false;
						}
						totalOldCount += lowValueStock.GetCount();
						totalChangingCount += item.GetCount();
						totalOldSum += lowValueStock.GetSum();
						totalChangingSum += item.GetSum();
						companyID = otherStocks.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						lowValueStock.SetCount(lowValueStock.GetCount() - item.GetCount());
						if (0 == lowValueStock.GetCount())
						{
							lowValueStock.SetSum(0);
						}
						else
						{
							lowValueStock.SetSum((lowValueStock.GetSum() - item.GetSum()));
						}
						if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(lowValueStock.GetCount() * 1000) / 1000)
							return false;
						if (lowValueStock.GetCount() > 0)
						{
							if (std::round((oldSum - item.GetSum()) * 10) / 10 != std::round(lowValueStock.GetSum() * 10) / 10)
								return false;
						}
						totalNewCount += lowValueStock.GetCount();
						totalNewSum += std::round(lowValueStock.GetSum() * 1000) / 1000;
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume other stocks list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		ConsumeOtherStocks cosRaw;
		if (!cosRaw.GetConsumeOtherStocksByID(globalVar, ormasDal, cosID, errorMessage))
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		/*cosRaw.SetSum(totalSum);
		if (!cosRaw.SimpleUpdateConsumeOtherStocks(globalVar, ormasDal, errorMessage))
		{
			return false;
		}*/
		CompanyAccountRelation caRel;
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, cosID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool LowValueStock::ChangingByConsumeOtherStocksReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cosID, int lowValueStockEmpID, std::string& errorMessage)
	{
		ConsumeOtherStocksList cOSList;
		std::vector<ConsumeOtherStocksListView> cCoListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cOSList.SetConsumeOtherStocksID(cosID);
		std::string filter = cOSList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksListViewCollection> otSListVector = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);
		if (otSListVector.size() > 0)
		{
			for each (auto item in otSListVector)
			{
				cCoListVec.push_back(ConsumeOtherStocksListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume other stocks list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cCoListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConOthSt(globalVar, ormasDal, lowValueStockEmpID, warehouseID, subAccID, errorMessage))
				return false;
			LowValueStock lowValueStock;
			OtherStocks otherStocks;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cCoListVec)
			{
				lowValueStock.Clear();
				otherStocks.Clear();
				status.Clear();
				if (!lowValueStock.GetLowValueStockByOtherStocksAndWarehouseID(globalVar, ormasDal, item.GetOtherStocksID(), warehouseID, errorMessage))
				{
					oldCount = lowValueStock.GetCount();
					oldSum = lowValueStock.GetSum();
					totalOldCount += lowValueStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					companyID = otherStocks.GetCompanyID();
					totalSum = totalSum + (item.GetSum());
					lowValueStock.SetOtherStocksID(item.GetOtherStocksID());
					lowValueStock.SetCount(item.GetCount());
					lowValueStock.SetSum(item.GetCount()*otherStocks.GetPrice());
					lowValueStock.SetCurrencyID(item.GetCurrencyID());
					lowValueStock.SetStatusID(status.GetID());
					lowValueStock.SetWarehouseID(warehouseID);
					if (!lowValueStock.CreateLowValueStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += lowValueStock.GetCount();
				}
				else
				{
					oldCount = lowValueStock.GetCount();
					oldSum = lowValueStock.GetSum();
					totalOldCount += lowValueStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					companyID = otherStocks.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					lowValueStock.SetCount(lowValueStock.GetCount() + item.GetCount());
					lowValueStock.SetSum(lowValueStock.GetSum() + item.GetSum());
					if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(lowValueStock.GetCount() * 1000) / 1000)
						return false;
					if (lowValueStock.GetCount() > 0)
					{
						if (std::round((oldSum + item.GetSum()) * 1000) / 1000 != std::round(lowValueStock.GetSum() * 1000) / 1000)
							return false;
					}
					totalNewCount += lowValueStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume other stocks list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, cosID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool LowValueStock::ChangingByConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cosID, int lowValueStockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		ConsumeOtherStocksList cOtSList;
		ConsumeOtherStocks otSRaw;
		if (!otSRaw.GetConsumeOtherStocksByID(globalVar, ormasDal, cosID, errorMessage))
			return false;
		std::vector<ConsumeOtherStocksListView> cOthSListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cOtSList.SetConsumeOtherStocksID(cosID);
		std::string filter = cOtSList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksListViewCollection> othStListVector = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);
		if (othStListVector.size() > 0)
		{
			for each (auto item in othStListVector)
			{
				cOthSListVec.push_back(ConsumeOtherStocksListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume other stocks list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		double totalOldSum = 0;
		double totalNewSum = 0;
		double totalChangingSum = 0;
		if (cOthSListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConOthSt(globalVar, ormasDal, lowValueStockEmpID, warehouseID, subAccID, errorMessage))
				return false;
			LowValueStock lowValueStock;
			OtherStocks otherStocks;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cOthSListVec)
			{
				lowValueStock.Clear();
				otherStocks.Clear();
				if (!lowValueStock.GetLowValueStockByOtherStocksAndWarehouseID(globalVar, ormasDal, item.GetOtherStocksID(), warehouseID, errorMessage))
				{
					if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
						return false;
					errorMessage = "ERROR! This other stocks is out of low value stock:";
					errorMessage += otherStocks.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (lowValueStock.GetCount() < item.GetCount())
					{
						if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough other stocks in the low value Stock!";
						errorMessage += " Other stocks name:";
						errorMessage += otherStocks.GetName();
						errorMessage += ", Other stocks count:";
						errorMessage += std::to_string(lowValueStock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = lowValueStock.GetCount();
						oldSum = lowValueStock.GetSum();
						if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, item.GetOtherStocksID(), errorMessage))
							return false;
						if (item.GetCount()*(lowValueStock.GetSum() / lowValueStock.GetCount()) != item.GetSum())
						{
							item.SetSum(item.GetCount()*(lowValueStock.GetSum() / lowValueStock.GetCount()));
							item.stockEmployeeID = otSRaw.GetStockEmployeeID();
							if (!item.UpdateConsumeOtherStocksList(globalVar, ormasDal, errorMessage))
								return false;
						}
						totalOldCount += lowValueStock.GetCount();
						totalChangingCount += item.GetCount();
						totalOldSum += lowValueStock.GetSum();
						totalChangingSum += item.GetSum();
						companyID = otherStocks.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						lowValueStock.SetCount(lowValueStock.GetCount() - (item.GetCount() - pProdCountMap.find(otherStocks.GetID())->second));
						if (0 == lowValueStock.GetCount())
						{
							lowValueStock.SetSum(0);
						}
						else
						{
							lowValueStock.SetSum(lowValueStock.GetSum() - (item.GetSum() - (pProdCountMap.find(otherStocks.GetID())->second * otherStocks.GetPrice())));
						}
						if (!lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(lowValueStock.GetCount() * 1000) / 1000)
							return false;
						if (lowValueStock.GetCount() > 0)
						{
							if (std::round((oldSum - item.GetSum()) * 10) / 10 != std::round(lowValueStock.GetSum() * 10) / 10)
								return false;
						}
						totalNewCount += lowValueStock.GetCount();
						totalNewSum += lowValueStock.GetSum();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume other stocks list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		ConsumeOtherStocks cosRaw;
		if (!cosRaw.GetConsumeOtherStocksByID(globalVar, ormasDal, cosID, errorMessage))
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		cosRaw.SetSum(totalSum);
		/*if (!cosRaw.SimpleUpdateConsumeOtherStocks(globalVar, ormasDal, errorMessage))
		{
			return false;
		}*/
		CompanyAccountRelation caRel;
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, cosID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool LowValueStock::RecalculateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage)
	{
		LowValueStock checkLowValueStock;
		LowValueStock lowValueStock;
		std::vector<DataLayer::lowValueStockViewCollection> lowValueStockVector;
		std::string filter;
		WarehouseType wType;
		Warehouse warehouse;
		OtherStocks otherStocks;
		checkLowValueStock.Clear();
		int companyID = 0;
		double difference = 0;
		if (!wType.GetWarehouseTypeByCode(globalVar, ormasDal, "OTHER STOCKS", errorMessage))
		{
			return false;
		}
		checkLowValueStock.SetOtherStocksID(pID);
		filter = checkLowValueStock.GenerateFilter(ormasDal);
		lowValueStockVector = ormasDal.GetLowValueStock(errorMessage, filter);
		if (lowValueStockVector.size() == 0)
		{
			return true;
		}
		else
		{
			for each (auto lowValueStockObject in lowValueStockVector)
			{
				lowValueStock.Clear();
				warehouse.Clear();
				otherStocks.Clear();
				
				if (!lowValueStock.GetLowValueStockByID(globalVar, ormasDal, std::get<0>(lowValueStockObject), errorMessage))
					return false;
				if (lowValueStock.GetCount() > 0)
				{
					if (!warehouse.GetWarehouseByID(globalVar, ormasDal, lowValueStock.GetWarehouseID(), errorMessage))
						return false;
					if (warehouse.GetWarehouseTypeID() == wType.GetID())
					{
						if (!otherStocks.GetOtherStocksByID(globalVar, ormasDal, pID, errorMessage))
							return false;
						
						companyID = otherStocks.GetCompanyID();
						difference = std::round((lowValueStock.GetCount()*newPrice - lowValueStock.GetCount()*oldPrice) * 1000) / 1000;
						lowValueStock.SetSum(lowValueStock.GetSum() + difference);
						lowValueStock.UpdateLowValueStock(globalVar, ormasDal, errorMessage);


						if (difference > 0 && difference != 0)
						{
							CompanyAccountRelation caRel;
							int debAccID = warehouse.GetSubaccountID();
							int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
							if (0 == debAccID || 0 == credAccID)
							{
								return false;
							}
							if (!this->CreateEntry(globalVar, ormasDal, otherStocks.GetID(), debAccID, difference, credAccID, errorMessage))
							{
								return false;
							}
						}
						if (difference < 0 && difference != 0)
						{
							CompanyAccountRelation caRel;
							int debAccID = warehouse.GetSubaccountID();
							int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
							if (0 == debAccID || 0 == credAccID)
							{
								return false;
							}
							if (!this->CreateEntry(globalVar, ormasDal, otherStocks.GetID(), credAccID, difference * (-1), debAccID, errorMessage))
							{
								return false;
							}
						}
					}
				}
			}
		}
		return true;
	}

	bool LowValueStock::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		std::string	entryText;
		entryText += wstring_to_utf8(L"Складская операция(прочие запасы). ID операции = ");
		entryText += std::to_string(operationID);
		entry.SetDescription(entryText);
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(operationID);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	bool LowValueStock::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		std::string	entryText;
		entryText += wstring_to_utf8(L"Складская операция(прочие запасы). ID операции = ");
		entryText += std::to_string(operationID);
		entry.SetDescription(entryText);
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage, true))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(operationID);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		entry.Clear();
		eoRelation.Clear();
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entryText += wstring_to_utf8(L"Складская операция. ID операции = ");
		entryText += std::to_string(operationID);
		entry.SetDescription(entryText);
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(operationID);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	bool LowValueStock::CreateCorrectongEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		std::string	entryText;
		entryText += wstring_to_utf8(L"Коррекция счета 10790 прочие запасы, после переоценки запасов, ID прочих запасов = ");
		entryText += std::to_string(operationID);
		entry.SetDescription(entryText);
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(operationID);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	bool LowValueStock::CreateCorrectongEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		std::string	entryText;
		entryText += wstring_to_utf8(L"Коррекция счета 10790 прочие запасы, после переоценки запасов, ID прочих запасов = ");
		entryText += std::to_string(operationID);
		entry.SetDescription(entryText);
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage, true))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(operationID);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		entry.Clear();
		eoRelation.Clear();
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entryText += wstring_to_utf8(L"Коррекция счета 10790 прочие запасы, после переоценки запасов, ID прочих запасов = ");
		entryText += std::to_string(operationID);
		entry.SetDescription(entryText);
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(operationID);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	std::string LowValueStock::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}

	bool LowValueStock::GetSubIDAndWerhIDFromRcpOthSt(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, empID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		warehouseID = warehouse.GetID();
		subAccID = warehouse.GetSubaccountID();
		return true;
	}

	bool LowValueStock::GetSubIDAndWerhIDFromConOthSt(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lowValueStockEmpID, int& warehouseID, int& subAccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, lowValueStockEmpID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		subAccID = warehouse.GetSubaccountID();
		warehouseID = warehouse.GetID();
		return true;
	}

	bool LowValueStock::CreateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stockID, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string& errorMessage)
	{
		LowValueStockChangeLog scLog;
		scLog.SetLowValueStockID(stockID);
		scLog.SetOtherStocksID(pID);
		scLog.SetCount(sCount);
		scLog.SetSum(sSum);
		scLog.SetStatusID(sID);
		scLog.SetCurrencyID(cID);
		scLog.SetWarehouseID(wID);
		scLog.SetLogDate(ormasDal.GetSystemDateTime());
		scLog.SetUserID(globalVar->userID);
		scLog.SetOperationID(globalVar->currentOperationID);
		if (scLog.CreateLowValueStockChangeLog(globalVar, ormasDal, errorMessage))
			return true;
		return false;
	}
}