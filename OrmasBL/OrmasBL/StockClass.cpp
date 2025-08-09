#include "stdafx.h"
#include "StockClass.h"
#include "EntryOperationRelationClass.h"
#include "BalanceClass.h"
#include "OrderRawClass.h"
#include "OrderRawListClass.h"
#include "OrderRawListViewClass.h"
#include "ConsumeProductClass.h"
#include "ConsumeProductListClass.h"
#include "ConsumeProductListViewClass.h"
#include "ConsumeRawClass.h"
#include "ConsumeRawListClass.h"
#include "ConsumeRawListViewClass.h"
#include "ReceiptProductClass.h"
#include "ReceiptProductListClass.h"
#include "ReceiptProductListViewClass.h"
#include "StockTransferClass.h"
#include "StockTransferListClass.h"
#include "StockTransferListViewClass.h"
#include "ReturnClass.h"
#include "ReturnListClass.h"
#include "ReturnListViewClass.h"
#include "WriteOffClass.h"
#include "WriteOffListClass.h"
#include "WriteOffListViewClass.h"
#include "WriteOffRawClass.h"
#include "WriteOffRawListClass.h"
#include "WriteOffRawListViewClass.h"
#include "ProductClass.h"
#include "StatusClass.h"
#include "EntryClass.h"
#include "AccountClass.h"
#include "SubaccountClass.h"
#include "CompanyAccountRelationClass.h"
#include "NetCostClass.h"
#include "ProductTypeClass.h"
#include "WarehouseClass.h"
#include "WarehouseTypeClass.h"
#include "WarehouseEmployeeRelationClass.h"
#include "UserClass.h"
#include "ProductionConsumeRawClass.h"
#include "ProductionConsumeRawListClass.h"
#include "ProductionConsumeRawListViewClass.h"
#include "ProductionListClass.h"
#include "ProductionListViewClass.h"
#include "StockChangeLogClass.h"
#include "CurrencyClass.h"
#include "MulticurrencyClass.h"
#include "CurrencyRateClass.h"
#include <codecvt>

namespace BusinessLayer
{
	Stock::Stock(DataLayer::stockCollection sCollection)
	{
		id = std::get<0>(sCollection);
		productID = std::get<1>(sCollection);
		count = std::get<2>(sCollection);
		sum = std::get<3>(sCollection);
		statusID = std::get<4>(sCollection);
		currencyID = std::get<5>(sCollection);
		warehouseID = std::get<6>(sCollection);
	}

	int Stock::GetID()
	{
		return id;
	}

	int Stock::GetProductID()
	{
		return productID;
	}

	double Stock::GetCount()
	{
		return count;
	}

	double Stock::GetSum()
	{
		return sum;
	}

	int Stock::GetStatusID()
	{
		return statusID;
	}

	int Stock::GetCurrencyID()
	{
		return currencyID;
	}

	int Stock::GetWarehouseID()
	{
		return warehouseID;
	}

	void Stock::SetID(int sID)
	{
		id = sID;
	}
	
	void Stock::SetProductID(int sProductID)
	{
		productID = sProductID;
	}
	void Stock::SetCount(double sCount)
	{
		count = sCount;
	}
	void Stock::SetSum(double sSum)
	{
		sum = sSum;
	}
	void Stock::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void Stock::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void Stock::SetWarehouseID(int sWarehouseID)
	{
		warehouseID = sWarehouseID;
	}

	bool Stock::CreateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		if (0 != id && ormasDal.CreateStock(id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			if (CreateStockChangeLog(globalVar, ormasDal, id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
				return true;
		}
		return false;
	}
	bool Stock::CreateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateStock(id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			if (CreateStockChangeLog(globalVar, ormasDal, id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
				return true;
		}
		return false;
	}
	bool Stock::DeleteStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteStock(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool Stock::UpdateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string& errorMessage)
	{
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		if (count < 0 || sum < 0)
		{
			errorMessage += "Count or sum cannot be less then 0! Product ID = ";
			errorMessage += std::to_string(productID);
			return false;
		}
		if (0 != id && ormasDal.UpdateStock(id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			if (CreateStockChangeLog(globalVar, ormasDal, id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
				return true;
		}
		return false;
	}
	bool Stock::UpdateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage += "Count or sum cannot be less then 0! Product ID = ";
			errorMessage += std::to_string(productID);
			return false;
		}
		if (0 != id && ormasDal.UpdateStock(id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			if (CreateStockChangeLog(globalVar, ormasDal, id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
				return true;
		}
		return false;
	}

	std::string Stock::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != count || 0 != sum || 0 != statusID || 0 != warehouseID)
		{
			return ormasDal.GetFilterForStock(id, productID, count, sum, statusID, currencyID, warehouseID);
		}
		return "";
	}

	bool Stock::GetStockByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockViewCollection> stockVector = ormasDal.GetStock(errorMessage, filter);
		if (0 != stockVector.size())
		{
			id = std::get<0>(stockVector.at(0));
			count = std::get<6>(stockVector.at(0));
			sum = std::get<7>(stockVector.at(0));
			productID = std::get<12>(stockVector.at(0));
			statusID = std::get<13>(stockVector.at(0));
			currencyID = std::get<14>(stockVector.at(0));
			warehouseID = std::get<15>(stockVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find stock with this id";
		}
		return false;
	}

	bool Stock::GetStockByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockViewCollection> stockVector = ormasDal.GetStock(errorMessage, filter);
		if (0 != stockVector.size())
		{
			id = std::get<0>(stockVector.at(0));
			count = std::get<6>(stockVector.at(0));
			sum = std::get<7>(stockVector.at(0));
			productID = std::get<12>(stockVector.at(0));
			statusID = std::get<13>(stockVector.at(0));
			currencyID = std::get<14>(stockVector.at(0));
			warehouseID = std::get<15>(stockVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find stock with this id";
		}
		return false;
	}

	bool Stock::GetStockByProductAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		if (wID <= 0)
			return false;
		productID = pID;
		warehouseID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockViewCollection> stockVector = ormasDal.GetStock(errorMessage, filter);
		if (0 != stockVector.size())
		{
			id = std::get<0>(stockVector.at(0));
			count = std::get<6>(stockVector.at(0));
			sum = std::get<7>(stockVector.at(0));
			productID = std::get<12>(stockVector.at(0));
			statusID = std::get<13>(stockVector.at(0));
			currencyID = std::get<14>(stockVector.at(0));
			warehouseID = std::get<15>(stockVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find stock with this product ID and warehouse ID";
		}
		return false;
	}

	std::vector<int> Stock::GetAllProductIDByWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		std::vector<int> prodIDList;
		if (wID <= 0)
			return prodIDList;
		warehouseID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockViewCollection> stockVector = ormasDal.GetStock(errorMessage, filter);
		if (0 < stockVector.size())
		{
			for each (auto weItem in stockVector)
			{
				prodIDList.push_back(std::get<12>(weItem));
			}
		}
		else
		{
			errorMessage = "Cannot find products in these warehouse!";
		}
		return prodIDList;
	}

	bool Stock::IsEmpty()
	{
		if (0 == id && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID && 0 == warehouseID)
			return true;
		return false;
	}

	void Stock::Clear()
	{
		id = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
		warehouseID = 0;
	}

	bool Stock::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		Stock stock;
		stock.Clear();
		errorMessage.clear();
		stock.SetProductID(pID);
		stock.SetWarehouseID(wID);
		std::string filter = stock.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockViewCollection> stockVector = ormasDal.GetStock(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == stockVector.size())
		{
			return false;
		}
		errorMessage = "Stock with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Stock::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Stock stock;
		stock.Clear();
		errorMessage.clear();
		stock.SetProductID(productID);
		stock.SetWarehouseID(warehouseID);
		std::string filter = stock.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockViewCollection> stockVector = ormasDal.GetStock(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == stockVector.size())
		{
			return false;
		}
		errorMessage = "Stock with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Stock::ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int stockEmpID, std::string& errorMessage)
	{
		ConsumeProduct consumeProduct;
		ConsumeProductList cPList;
		std::vector<ConsumeProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;
		
		cPList.SetConsumeProductID(cpID);
		std::string filter = cPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeProductListViewCollection> productListVector = ormasDal.GetConsumeProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(ConsumeProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConProd(globalVar, ormasDal, stockEmpID , warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			NetCost nCost;
			ConsumeProductList cpOldList;
			double oldCount = 0;
			double oldSum = 0;
			double docNewSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				
				//clear section
				stock.Clear();
				product.Clear();
				nCost.Clear();
				cpOldList.Clear();
				//check stock for existens of product
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the stock!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(stock.GetCount());
							
						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - (item.GetCount()*nCost.GetValue()));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
				if (item.GetSum() != item.GetCount()*nCost.GetValue())
				{
					if (!cpOldList.GetConsumeProductListByID(globalVar, ormasDal, item.GetID(), errorMessage))
						return false;
					cpOldList.SetSum(item.GetCount()*nCost.GetValue());
					if (!cpOldList.UpdateConsumeProductList(globalVar, ormasDal, errorMessage))
						return false;
					docNewSum += item.GetCount()*nCost.GetValue();
				}
				else
				{
					docNewSum += item.GetSum();
				}
			}
			if (consumeProduct.GetConsumeProductByID(globalVar, ormasDal, cpID, errorMessage))
			{
				consumeProduct.SetSum(std::round(docNewSum * 1000) / 1000);
				if (!consumeProduct.SimpleUpdateConsumeProduct(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10742", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		
		if (!this->CreateEntry(globalVar, ormasDal, cpID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByConsumeProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int stockEmpID, std::string& errorMessage)
	{
		
		ConsumeProductList cPList;
		std::vector<ConsumeProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cPList.SetConsumeProductID(cpID);
		std::string filter = cPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeProductListViewCollection> productListVector = ormasDal.GetConsumeProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(ConsumeProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			return false;
		}

		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;

		if (cPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConProd(globalVar, ormasDal, stockEmpID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;

			for each (auto item in cPListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum((item.GetCount()*nCost.GetValue()));
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + (item.GetCount()*nCost.GetValue()));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue())*1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
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
		int debAccID = subAccID;
		int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10742", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, cpID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}


	bool Stock::ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		ConsumeProduct consumeProduct;
		ConsumeProductList cPList;
		std::vector<ConsumeProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0; 
		int subAccID = 0;
		int warehouseID = 0;

		cPList.SetConsumeProductID(cpID);
		std::string filter = cPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeProductListViewCollection> productListVector = ormasDal.GetConsumeProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(ConsumeProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConProd(globalVar, ormasDal, stockEmpID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			NetCost nCost;
			ConsumeProductList cpOldList;
			double oldCount = 0;
			double oldSum = 0;
			double docNewSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{

				//clear section
				stock.Clear();
				product.Clear();
				nCost.Clear();
				cpOldList.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the stock!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(stock.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetCount()*nCost.GetValue();
						stock.SetCount(stock.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - ((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - (item.GetCount() - pProdCountMap.find(product.GetID())->second)) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum -((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue()))) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
				if (item.GetSum() != item.GetCount()*nCost.GetValue())
				{
					if (!cpOldList.GetConsumeProductListByID(globalVar, ormasDal, item.GetID(), errorMessage))
						return false;
					cpOldList.SetSum(item.GetCount()*nCost.GetValue());
					if (!cpOldList.UpdateConsumeProductList(globalVar, ormasDal, errorMessage))
						return false;
					docNewSum += item.GetCount()*nCost.GetValue();
				}
				else
				{
					docNewSum += item.GetSum();
				}
			}
			if (consumeProduct.GetConsumeProductByID(globalVar, ormasDal, cpID, errorMessage))
			{
				consumeProduct.SetSum(std::round(docNewSum * 1000) / 1000);
				if (!consumeProduct.SimpleUpdateConsumeProduct(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10742", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, cpID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		
		return true;
	}

	bool Stock::ChangingByConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::string& errorMessage)
	{
		
		ConsumeRawList cRList;
		std::vector<ConsumeRawListView> cRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;
		double correctingConRawSum = 0;
		double correctingConRawTotalSum = 0;
		int acc55020ID = 0;

		cRList.SetConsumeRawID(crID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> productListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cRListVec.push_back(ConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConRaw(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			double oldCount = 0;
			double oldSum = 0;
			correctingConRawSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cRListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						stock.SetCount(stock.GetCount() - item.GetCount());
						correctingConRawSum = std::round(product.GetPrice()* item.GetCount() - item.GetSum()) * 1000 / 1000;
						correctingConRawTotalSum += correctingConRawSum;
						if (0 == correctingConRawSum)
						{
							if (stock.GetCount() == 0)
							{
								// must add correcting entry, to datele tails from table(like 0.0011)
								stock.SetSum(0);
							}
							else
							{
								stock.SetSum(((stock.GetSum() - item.GetSum())) *1000 / 1000);
							}
							
						}
						else if (correctingConRawSum > 0)
						{
							if ((stock.GetSum() - item.GetSum() - correctingConRawSum) < 0.5 &&
								(stock.GetSum() - item.GetSum() - correctingConRawSum) > -0.5
								&& stock.GetCount() == 0 )
							{
								stock.SetSum(0);
							}
							else
							{
								stock.SetSum(std::round((stock.GetSum() - item.GetSum() - correctingConRawSum)*1000)/1000);
							}
						}
						else if (correctingConRawSum < 0)
						{
							if ((stock.GetSum() - item.GetSum() - correctingConRawSum) < 0.5 &&
								(stock.GetSum() - item.GetSum() - correctingConRawSum) > -0.5
								&& stock.GetCount() == 0)
							{
								stock.SetSum(0);
							}
							else
							{
								stock.SetSum(std::round((stock.GetSum() - item.GetSum() + correctingConRawSum*(-1)) * 1000) / 1000);
							}
						}

						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
						{
							stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
							if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
							{
								//ormasDal.CancelTransaction(errorMessage);
								return false;
							}
						}
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = debSaccID;
		int credAccID = credSaccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, crID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (0 != correctingConRawTotalSum)
		{
			acc55020ID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
			if (correctingConRawTotalSum > 0)
			{
				if (!this->CreateEntry(globalVar, ormasDal, id, acc55020ID, correctingConRawTotalSum, credAccID, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			else if (correctingConRawTotalSum < 0)
			{
				if (!this->CreateEntry(globalVar, ormasDal, id, credAccID, correctingConRawTotalSum*(-1), acc55020ID, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
		}
		if (!ChangingByConsumeRawAtSecondStock(globalVar, ormasDal, crID, debWerID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByConsumeRawReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::string& errorMessage)
	{
		
		ConsumeRawList cRList;
		std::vector<ConsumeRawListView> cRListVec;
		double totalSum = 0.0;
		double correctingSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;
		double correctingConRawSum = 0;
		int acc55020ID = 0;

		cRList.SetConsumeRawID(crID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> productListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cRListVec.push_back(ConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConRaw(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cRListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum += item.GetSum(); 
					correctingSum += std::round((product.GetPrice() * item.GetCount()) * 1000) / 1000;
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(std::round((product.GetPrice() * item.GetCount()) * 1000) / 1000);
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					stock.SetWarehouseID(warehouseID);
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum += item.GetSum();
					correctingSum += std::round((product.GetPrice() * item.GetCount()) * 1000) / 1000;
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + (std::round((product.GetPrice() * item.GetCount()) * 1000) / 1000));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
					{
						stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
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
		int debAccID = credSaccID;
		int credAccID = debSaccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, crID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		correctingConRawSum = totalSum - correctingSum;
		if (0 != correctingConRawSum)
		{
			acc55020ID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
			if (correctingConRawSum > 0)
			{
				if (!this->CreateEntry(globalVar, ormasDal, id, acc55020ID, correctingConRawSum, credAccID, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			else if (correctingConRawSum < 0)
			{
				if (!this->CreateEntry(globalVar, ormasDal, id, credAccID, correctingConRawSum*(-1), acc55020ID, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
		}
		if (!ChangingByConsumeRawAtSecondStockReverse(globalVar, ormasDal, crID, debWerID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}


	bool Stock::ChangingByConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		ConsumeRawList cRList;
		std::vector<ConsumeRawListView> cRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;
		int acc55020ID = 0;
		double correctingConRawSum = 0;

		cRList.SetConsumeRawID(crID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> productListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cRListVec.push_back(ConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromConRaw(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cRListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						stock.SetCount(stock.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							correctingConRawSum = std::round(product.GetPrice()* item.GetCount() - item.GetSum()) * 1000 / 1000;
							if (0 == correctingConRawSum)
							{
								stock.SetSum(stock.GetSum() - (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
							}
							else if (correctingConRawSum > 0)
							{
								stock.SetSum(stock.GetSum() - (item.GetSum() + correctingConRawSum - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
							}
							else if (correctingConRawSum < 0)
							{
								stock.SetSum(stock.GetSum() - (item.GetSum() + correctingConRawSum - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
							}
							
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
						{
							stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
							if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
							{
								//ormasDal.CancelTransaction(errorMessage);
								return false;
							}
						}
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = debSaccID;
		int credAccID = credSaccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, crID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (0 != correctingConRawSum)
		{
			acc55020ID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
			if (correctingConRawSum > 0)
			{
				if (!this->CreateEntry(globalVar, ormasDal, id, acc55020ID, correctingConRawSum, credAccID, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			else if (correctingConRawSum < 0)
			{
				if (!this->CreateEntry(globalVar, ormasDal, id, credAccID, correctingConRawSum*(-1), acc55020ID, errorMessage))
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
		}
		if (!ChangingByConsumeRawAtSecondStock(globalVar, ormasDal, crID, debWerID, pProdCountMap, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByConsumeRawAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int debWerID, std::string& errorMessage)
	{
		
		ConsumeRawList cRList;
		std::vector<ConsumeRawListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cRList.SetConsumeRawID(rrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> productListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(ConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID, errorMessage))
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot consume this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetProductID(item.GetProductID());
					pStock.SetCount(item.GetCount());
					pStock.SetSum(item.GetSum());
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += pStock.GetCount();
				}
				else
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetCount(pStock.GetCount() + item.GetCount());
					pStock.SetSum(pStock.GetSum() + item.GetSum());
					if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
						return false;
					totalNewCount += pStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByConsumeRawAtSecondStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int debWerID, std::string& errorMessage)
	{
		
		ConsumeRawList cRList;
		std::vector<ConsumeRawListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cRList.SetConsumeRawID(rrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> productListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(ConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				pStock.Clear();
				product.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (pStock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(pStock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = pStock.GetCount();
						oldSum = pStock.GetSum();
						totalOldCount += pStock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						pStock.SetCount(pStock.GetCount() - item.GetCount());
						if (0 == pStock.GetCount())
						{
							pStock.SetSum(0);
						}
						else
						{
							pStock.SetSum((pStock.GetSum() - item.GetSum()));
						}
						if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
							return false;
						totalNewCount += pStock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByConsumeRawAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int debWerID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		ConsumeRawList cRList;
		std::vector<ConsumeRawListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cRList.SetConsumeRawID(rrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeRawListViewCollection> productListVector = ormasDal.GetConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(ConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID,errorMessage))
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetProductID(item.GetProductID());
					pStock.SetCount(item.GetCount());
					pStock.SetSum(item.GetSum());
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += pStock.GetCount();
				}
				else
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetCount(pStock.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					pStock.SetSum(pStock.GetSum() + (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
					if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
						return false;
					totalNewCount += pStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage)
	{
		
		OrderRaw oRaw;
		OrderRawList oRList;
		std::vector<OrderRawListView> oRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		oRList.SetOrderRawID(orID);
		std::string filter = oRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> productListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				oRListVec.push_back(OrderRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (oRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromOrderRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in oRListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + (item.GetSum());
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetCount()*product.GetPrice());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					stock.SetWarehouseID(warehouseID);
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + (item.GetCount()*product.GetPrice()));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
					{
						stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!oRaw.GetOrderRawByID(globalVar, ormasDal, orID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, oRaw.GetPurveyorID(), errorMessage))
			return false;
		CompanyAccountRelation caRel;
		int debAccID = subAccID;
		int credAccID = balance.GetSubaccountID();
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, orID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByOrderRawReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage)
	{
		
		OrderRaw oRaw;
		OrderRawList oRList;
		std::vector<OrderRawListView> oRListVec;
		double totalSum = 0.0;
		double newSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		oRList.SetOrderRawID(orID);
		std::string filter = oRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> productListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				oRListVec.push_back(OrderRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (oRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromOrderRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in oRListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						newSum = newSum + std::round(item.GetCount()* product.GetPrice() * 1000) / 1000;
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum((stock.GetSum() - std::round(item.GetCount()* product.GetPrice() * 1000) / 1000));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
						{
							stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
							if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
							{
								//ormasDal.CancelTransaction(errorMessage);
								return false;
							}
						}
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!oRaw.GetOrderRawByID(globalVar, ormasDal, orID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, oRaw.GetPurveyorID(), errorMessage))
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

		if (!this->CreateEntry(globalVar, ormasDal, orID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		double checkSum = totalSum - newSum;
		if (checkSum > 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, orID, acc55020ID, checkSum, debAccID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		else if (checkSum < 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, orID, debAccID, checkSum *(-1), acc55020ID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		return true;
	}

	

	bool Stock::ChangingByOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		OrderRaw oRaw;
		OrderRawList oRList;
		std::vector<OrderRawListView> oRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		oRList.SetOrderRawID(orID);
		std::string filter = oRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> productListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				oRListVec.push_back(OrderRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (oRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromOrderRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			for each (auto item in oRListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetSum());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					stock.SetWarehouseID(warehouseID);
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetCount(stock.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					stock.SetSum(stock.GetSum() + (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
					{
						stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!oRaw.GetOrderRawByID(globalVar, ormasDal, orID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, oRaw.GetPurveyorID(), errorMessage))
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

	bool Stock::ChangingByOrderRawForMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage)
	{
		OrderRaw oRaw;
		OrderRawList oRList;
		std::vector<OrderRawListView> oRListVec;
		std::vector<OrderRawListView> oRExtListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int currencyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		Currency currency;
		int mainCurID = 0;
		mainCurID = currency.GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (0 == mainCurID)
			return false;

		oRList.SetOrderRawID(orID);
		std::string filter = oRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> productListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				if (mainCurID == std::get<13>(item))
				{
					oRListVec.push_back(OrderRawListView(item));
				}
				else
				{
					currencyID = std::get<13>(item);
					oRExtListVec.push_back(OrderRawListView(item));
				}
				
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			return false;
		}
	
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;

		if (oRExtListVec.size() > 0)
		{
			oRListVec.clear();
			oRListVec = oRExtListVec;
		}

		if (oRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromOrderRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in oRListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + (item.GetSum());
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetCount()*product.GetPrice());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					stock.SetWarehouseID(warehouseID);
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + (item.GetCount()*product.GetPrice()));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
					{
						stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!oRaw.GetOrderRawByID(globalVar, ormasDal, orID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, oRaw.GetPurveyorID(), errorMessage))
			return false;
		CompanyAccountRelation caRel;
		int debAccID = subAccID;
		
		Multicurrency multicurrency;
		if (!multicurrency.GetMulticurrencyByMainCurrencyID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			return false;
		Subaccount subExch;
		if (!subExch.GetSubaccountByID(globalVar, ormasDal, multicurrency.GetSubaccountCurrencyID(), errorMessage))
			return false;
		if (subExch.GetCurrencyID() != currencyID)
		{
			errorMessage = "This subaccount have diffenent currency, selected currency not correct!";
			return false;
		}
		CurrencyRate currencyRate;
		if (!currencyRate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, currencyID, errorMessage))
			return false;

		int credAccID = balance.GetSubaccountID();
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!this->CreateEntry(globalVar, ormasDal, orID, debAccID, totalSum * currencyRate.GetToValue() / currencyRate.GetFromValue(), credAccID, errorMessage))
		{
			return false;
		}

		
		//subExch.SetCurrentBalance(subExch.GetCurrentBalance() - totalSum);
		//ormasDal.CancelTransaction(errorMessage);
		//if (!subExch.UpdateSubaccount(globalVar, ormasDal, errorMessage))
		//	return false;

		return true;
	}

	bool Stock::ChangingByOrderRawReverseForMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage)
	{
		OrderRaw oRaw;
		OrderRawList oRList;
		std::vector<OrderRawListView> oRListVec;
		std::vector<OrderRawListView> oRExtListVec;
		double totalSum = 0.0;
		double newSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;
		int currencyID = 0;

		Currency currency;
		int mainCurID = 0;
		mainCurID = currency.GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (0 == mainCurID)
			return false;

		oRList.SetOrderRawID(orID);
		std::string filter = oRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> productListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				if (mainCurID == std::get<13>(item))
				{
					oRListVec.push_back(OrderRawListView(item));
				}
				else
				{
					currencyID = std::get<13>(item);
					oRExtListVec.push_back(OrderRawListView(item));
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;


		if (oRExtListVec.size() > 0)
		{
			oRListVec.clear();
			oRListVec = oRExtListVec;
		}

		if (oRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromOrderRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in oRListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						newSum = newSum + std::round(item.GetCount()* product.GetPrice() * 1000) / 1000;
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum((stock.GetSum() - std::round(item.GetCount()* product.GetPrice() * 1000) / 1000));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
						{
							stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
							if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
							{
								//ormasDal.CancelTransaction(errorMessage);
								return false;
							}
						}
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!oRaw.GetOrderRawByID(globalVar, ormasDal, orID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, oRaw.GetPurveyorID(), errorMessage))
			return false;
		CompanyAccountRelation caRel;

		int debAccID = subAccID;

		Multicurrency multicurrency;
		if (!multicurrency.GetMulticurrencyByMainCurrencyID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			return false;
		Subaccount subExch;
		if (!subExch.GetSubaccountByID(globalVar, ormasDal, multicurrency.GetSubaccountCurrencyID(), errorMessage))
			return false;
		if (subExch.GetCurrencyID() != currencyID)
		{
			errorMessage = "This subaccount have diffenent currency, selected currency not correct!";
			return false;
		}

		CurrencyRate currencyRate;
		if (!currencyRate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, currencyID, errorMessage))
			return false;

		int credAccID = multicurrency.GetSubaccountMainCurrencyID();
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		
		
		int acc55020ID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, orID, credAccID, totalSum * currencyRate.GetToValue() / currencyRate.GetFromValue(), debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		double checkSum  = totalSum - newSum / currencyRate.GetToValue() / currencyRate.GetFromValue();
		checkSum *= currencyRate.GetToValue() / currencyRate.GetFromValue();
		if (checkSum > 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, orID, acc55020ID, checkSum, debAccID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		else if (checkSum < 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, orID, debAccID, checkSum *(-1), acc55020ID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}

		
		//subExch.SetCurrentBalance(subExch.GetCurrentBalance() + totalSum );
		//ormasDal.CancelTransaction(errorMessage);
		//if (!subExch.UpdateSubaccount(globalVar, ormasDal, errorMessage))
		//	return false;

		return true;
	}



	bool Stock::ChangingByOrderRawForMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		OrderRaw oRaw;
		OrderRawList oRList;
		std::vector<OrderRawListView> oRListVec;
		std::vector<OrderRawListView> oRExtListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;
		int currencyID = 0;

		Currency currency;
		int mainCurID = 0;
		mainCurID = currency.GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (0 == mainCurID)
			return false;

		oRList.SetOrderRawID(orID);
		std::string filter = oRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> productListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				if (mainCurID == std::get<13>(item))
				{
					oRListVec.push_back(OrderRawListView(item));
				}
				else
				{
					currencyID = std::get<13>(item);
					oRExtListVec.push_back(OrderRawListView(item));
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;

		if (oRExtListVec.size() > 0)
		{
			oRListVec.clear();
			oRListVec = oRExtListVec;
		}

		if (oRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromOrderRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			for each (auto item in oRListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetSum());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					stock.SetWarehouseID(warehouseID);
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetCount(stock.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					stock.SetSum(stock.GetSum() + (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round(product.GetPrice()*stock.GetCount() * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
					{
						stock.SetSum(std::round(product.GetPrice()*stock.GetCount() * 1000) / 1000);
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Order raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!oRaw.GetOrderRawByID(globalVar, ormasDal, orID, errorMessage))
			return false;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, oRaw.GetPurveyorID(), errorMessage))
			return false;
		CompanyAccountRelation caRel;
		int debAccID = subAccID;

		Multicurrency multicurrency;
		if (!multicurrency.GetMulticurrencyByMainCurrencyID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			return false;
		Subaccount subExch;
		if (!subExch.GetSubaccountByID(globalVar, ormasDal, multicurrency.GetSubaccountCurrencyID(), errorMessage))
			return false;
		if (subExch.GetCurrencyID() != currencyID)
		{
			errorMessage = "This subaccount have diffenent currency, selected currency not correct!";
			return false;
		}

		CurrencyRate currencyRate;
		if (!currencyRate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, currencyID, errorMessage))
			return false;

		int credAccID = multicurrency.GetSubaccountMainCurrencyID();
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, orID, debAccID, totalSum * currencyRate.GetToValue() / currencyRate.GetFromValue(), credAccID, pSum* currencyRate.GetToValue() / currencyRate.GetFromValue(), errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		//subExch.SetCurrentBalance(subExch.GetCurrentBalance() - totalSum );
		//ormasDal.CancelTransaction(errorMessage);
		//if (!subExch.UpdateSubaccount(globalVar, ormasDal, errorMessage))
		//	return false;

		return true;
	}

	bool Stock::ChangingByReceiptProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int empID, int stockEmpID, std::string& errorMessage)
	{
		
		ReceiptProductList rPList;
		std::vector<ReceiptProductListView> rPListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;

		rPList.SetReceiptProductID(rpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> productListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rPListVec.push_back(ReceiptProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpProd(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			for each (auto item in rPListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum((item.GetCount()*nCost.GetValue()));
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					if (!stock.CreateStock(globalVar, ormasDal,errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum +item.GetCount()*nCost.GetValue() ;
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + (item.GetCount()*nCost.GetValue()));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt product list is empty!";
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
		int debAccID = debSaccID;
		int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rpID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!ChangingByReceiptProductAtSecondStock(globalVar, ormasDal, rpID, credWerID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByReceiptProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int empID, int stockEmpID, std::string& errorMessage)
	{
		
		ReceiptProductList rPList;
		std::vector<ReceiptProductListView> rPListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;

		rPList.SetReceiptProductID(rpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> productListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rPListVec.push_back(ReceiptProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpProd(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			for each (auto item in rPListVec)
			{
				//clear section
				stock.Clear();
				product.Clear();
				nCost.Clear();

				//check stock for existens of product
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the stock!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(stock.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - (item.GetCount()*nCost.GetValue()));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = debSaccID;
		int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rpID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!ChangingByReceiptProductAtSecondStockReverse(globalVar, ormasDal, rpID, credWerID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByReceiptProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int empID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		ReceiptProductList rPList;
		std::vector<ReceiptProductListView> rPListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;

		rPList.SetReceiptProductID(rpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> productListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rPListVec.push_back(ReceiptProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpProd(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rPListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetCount()*nCost.GetValue());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue() ;
					stock.SetCount(stock.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					stock.SetSum(stock.GetSum() + ((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt product list is empty!";
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
		int debAccID = debSaccID;
		int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rpID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!ChangingByReceiptProductAtSecondStock(globalVar, ormasDal, rpID, credWerID, pProdCountMap, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByReceiptProductAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::string& errorMessage)
	{
		
		ReceiptProductListView rPList;
		std::vector<ReceiptProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;

		rPList.SetReceiptProductID(rpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> productListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(ReceiptProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cPListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				pStock.Clear();
				product.Clear();
				nCost.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (pStock.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the production stock!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(pStock.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = pStock.GetCount();
						oldSum = pStock.GetSum();
						totalOldCount += pStock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetCount()*nCost.GetValue();
						pStock.SetCount(pStock.GetCount() - item.GetCount());
						if (0 == pStock.GetCount())
						{
							pStock.SetSum(0);
						}
						else
						{
							pStock.SetSum(pStock.GetSum() - (item.GetCount()*nCost.GetValue()));
						}

						if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(pStock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += pStock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		return true;
	}

	bool Stock::ChangingByReceiptProductAtSecondStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::string& errorMessage)
	{
		
		ReceiptProductListView rPList;
		std::vector<ReceiptProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;

		rPList.SetReceiptProductID(rpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> productListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(ReceiptProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cPListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			NetCost nCost;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					pStock.SetProductID(item.GetProductID());
					pStock.SetCount(item.GetCount());
					pStock.SetSum((item.GetCount()*nCost.GetValue()));
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += pStock.GetCount();
				}
				else
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					pStock.SetCount(pStock.GetCount() + item.GetCount());
					pStock.SetSum(pStock.GetSum() + (item.GetCount()*nCost.GetValue()));
					if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(pStock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += pStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		return true;
	}

	bool Stock::ChangingByReceiptProductAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		ReceiptProductListView rPList;
		std::vector<ReceiptProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;

		rPList.SetReceiptProductID(rpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptProductListViewCollection> productListVector = ormasDal.GetReceiptProductList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(ReceiptProductListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cPListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				pStock.Clear();
				product.Clear();
				nCost.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (pStock.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the stock!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(pStock.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = pStock.GetCount();
						oldSum = pStock.GetSum();
						totalOldCount += pStock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetCount()*nCost.GetValue();
						pStock.SetCount(pStock.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == pStock.GetCount())
						{
							pStock.SetSum(0);
						}
						else
						{
							pStock.SetSum(pStock.GetSum() - ((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
						}

						if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(pStock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += pStock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		return true;
	}

	bool Stock::ChangingByStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int empID, int stockEmpID, std::string& errorMessage)
	{
		StockTransfer stockTransfer;
		StockTransferList rRList;
		std::vector<StockTransferListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;

		rRList.SetStockTransferID(rrID);
		std::string filter = rRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> productListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(StockTransferListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpRaw(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			StockTransferList stockTransferNew;
			Stock stock;
			Product product;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			double docNewSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				stock.Clear();
				product.Clear();
				nCost.Clear();
				stockTransferNew.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum((stock.GetSum() - item.GetCount()*nCost.GetValue()));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
				if (item.GetSum() != item.GetCount()*nCost.GetValue())
				{
					if (!stockTransferNew.GetStockTransferListByID(globalVar, ormasDal, item.GetID(), errorMessage))
						return false;
					stockTransferNew.SetSum(item.GetCount()*nCost.GetValue());
					if (!stockTransferNew.UpdateStockTransferList(globalVar, ormasDal, errorMessage))
						return false;
					docNewSum += item.GetCount()*nCost.GetValue();
				}
				else
				{
					docNewSum += item.GetSum();
				}
			}
			if (stockTransfer.GetStockTransferByID(globalVar, ormasDal, rrID, errorMessage))
			{
				stockTransfer.SetSum(std::round(docNewSum * 1000) / 1000);
				if (!stockTransfer.SimpleUpdateStockTransfer(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = debSaccID;
		int credAccID = credSaccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!this->CreateEntry(globalVar, ormasDal, rrID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!ChangingByStockTransferAtSecondStock(globalVar, ormasDal, rrID, debWerID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByStockTransferReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int empID, int stockEmpID, std::string& errorMessage)
	{
		
		StockTransferList rRList;
		std::vector<StockTransferListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;

		rRList.SetStockTransferID(rrID);
		std::string filter = rRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> productListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(StockTransferListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpRaw(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			NetCost nCost;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum((item.GetCount()*nCost.GetValue()));
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + (item.GetCount()*nCost.GetValue()));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetSum()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Stock transfer list is empty!";
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
		int debAccID = debSaccID;
		int credAccID = credSaccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!this->CreateEntry(globalVar, ormasDal, rrID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!ChangingByStockTransferAtSecondStockReverse(globalVar, ormasDal, rrID, debWerID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int empID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		StockTransfer stockTransfer;
		StockTransferList rRList;
		std::vector<StockTransferListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int debSaccID = 0;
		int credSaccID = 0;
		int debWerID = 0;
		int credWerID = 0;

		rRList.SetStockTransferID(rrID);
		std::string filter = rRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> productListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(StockTransferListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromRcpRaw(globalVar, ormasDal, empID, stockEmpID, debWerID, credWerID, debSaccID, credSaccID, errorMessage))
				return false;
			StockTransferList stockTransferNew;
			Stock stock;
			Product product;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			double docNewSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				stock.Clear();
				product.Clear();
				nCost.Clear();
				stockTransferNew.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), credWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{

						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
						stock.SetCount(stock.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - (item.GetCount()*nCost.GetValue() - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
				if (item.GetSum() != item.GetCount()*nCost.GetValue())
				{
					if (!stockTransferNew.GetStockTransferListByID(globalVar, ormasDal, item.GetID(), errorMessage))
						return false;
					stockTransferNew.SetSum(item.GetCount()*nCost.GetValue());
					if (!stockTransferNew.UpdateStockTransferList(globalVar, ormasDal, errorMessage))
						return false;
					docNewSum += item.GetCount()*nCost.GetValue();
				}
				else
				{
					docNewSum += item.GetSum();
				}
			}
			if (stockTransfer.GetStockTransferByID(globalVar, ormasDal, rrID, errorMessage))
			{
				stockTransfer.SetSum(std::round(docNewSum * 1000) / 1000);
				if (!stockTransfer.SimpleUpdateStockTransfer(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = debSaccID;
		int credAccID = credSaccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rrID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (!ChangingByStockTransferAtSecondStock(globalVar, ormasDal, rrID, debWerID, pProdCountMap, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByStockTransferAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int debWerID, std::string& errorMessage)
	{
		
		StockTransferList cRList;
		std::vector<StockTransferListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cRList.SetStockTransferID(rrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> productListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(StockTransferListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID, errorMessage))
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetProductID(item.GetProductID());
					pStock.SetCount(item.GetCount());
					pStock.SetSum(item.GetSum());
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += pStock.GetCount();
				}
				else
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetCount(pStock.GetCount() + item.GetCount());
					pStock.SetSum(pStock.GetSum() + item.GetCount()*nCost.GetValue());
					if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(pStock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += pStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByStockTransferAtSecondStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int debWerID, std::string& errorMessage)
	{
		
		StockTransferList cRList;
		std::vector<StockTransferListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cRList.SetStockTransferID(rrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> productListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(StockTransferListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Stock transfer list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				//clear section
				pStock.Clear();
				product.Clear();
				nCost.Clear();

				//check stock for existens of product
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (pStock.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the stock!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(pStock.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = pStock.GetCount();
						oldSum = pStock.GetSum();
						totalOldCount += pStock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
						pStock.SetCount(pStock.GetCount() - item.GetCount());
						if (0 == pStock.GetCount())
						{
							pStock.SetSum(0);
						}
						else
						{
							pStock.SetSum(pStock.GetSum() - (item.GetCount()*nCost.GetValue()));
						}
						if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(pStock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += pStock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Stock transfer list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByStockTransferAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int debWerID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		StockTransferList cRList;
		std::vector<StockTransferListView> rRListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cRList.SetStockTransferID(rrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> productListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rRListVec.push_back(StockTransferListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rRListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), debWerID, errorMessage))
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetProductID(item.GetProductID());
					pStock.SetCount(item.GetCount());
					pStock.SetSum(item.GetSum());
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += pStock.GetCount();
				}
				else
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetCount(pStock.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					pStock.SetSum(pStock.GetSum() + (item.GetCount()*nCost.GetValue() - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
					if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(pStock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += pStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByReturnProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int cID, int wareID, std::string& errorMessage)
	{
		
		ReturnList rList;
		std::vector<ReturnListView> rListVec;
		double totalSum = 0.0;
		double netSum = 0.0;
		int companyID = 0;

		rList.SetReturnID(rpID);
		std::string filter = rList.GenerateFilter(ormasDal);
		std::vector<DataLayer::returnListViewCollection> productListVector = ormasDal.GetReturnList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rListVec.push_back(ReturnListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Return list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rListVec.size() > 0)
		{
			Stock stock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), wareID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot return this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum += (item.GetSum() - item.GetCount()*nCost.GetValue());
					netSum += item.GetCount()*nCost.GetValue();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetCount()*nCost.GetValue());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum += (item.GetSum() - item.GetCount()*nCost.GetValue());
					netSum += item.GetCount()*nCost.GetValue();
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + item.GetCount()*nCost.GetValue());
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Return list is empty!";
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
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, cID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		Warehouse warehouse;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, wareID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		int debAccID10740 = warehouse.GetSubaccountID();
		int credAccID = balance.GetSubaccountID();
		int debAccID44090 = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "44090", errorMessage);
		if (0 == debAccID10740 || 0 == credAccID || 0 == debAccID44090)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rpID, debAccID10740, netSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (totalSum > 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, rpID, debAccID44090, totalSum, credAccID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		if (totalSum < 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, rpID, credAccID, totalSum*(-1), debAccID44090, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		return true;
	}

	bool Stock::ChangingByReturnProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int cID, int wareID, std::string& errorMessage)
	{
		
		ReturnList rList;
		std::vector<ReturnListView> rListVec;
		double totalSum = 0.0;
		double netSum = 0.0;
		int companyID = 0;

		rList.SetReturnID(rpID);
		std::string filter = rList.GenerateFilter(ormasDal);
		std::vector<DataLayer::returnListViewCollection> productListVector = ormasDal.GetReturnList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rListVec.push_back(ReturnListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Return list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rListVec.size() > 0)
		{
			Stock stock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				//check stock for existens of product
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), wareID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the stock!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(stock.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						netSum += round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
						totalSum += round(item.GetCount()*product.GetPrice() * 1000) / 1000;
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - round(item.GetCount()*nCost.GetValue() * 1000) / 1000);
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Return list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, cID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		Warehouse warehouse;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, wareID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		int debAccID10740 = warehouse.GetSubaccountID();
		int credAccID = balance.GetSubaccountID();
		int debAccID44090 = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "44090", errorMessage);
		if (0 == debAccID10740 || 0 == credAccID || 0 == debAccID44090)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rpID, credAccID, netSum, debAccID10740, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (totalSum - netSum > 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, rpID, credAccID, totalSum - netSum, debAccID44090, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		if (totalSum - netSum < 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, rpID, debAccID44090, (totalSum - netSum)*(-1), credAccID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		return true;
	}

	bool Stock::ChangingByReturnProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int cID, int wareID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		ReturnList rList;
		std::vector<ReturnListView> rListVec;
		double totalSum = 0.0;
		double netSum = 0.0;
		int companyID = 0;

		rList.SetReturnID(rpID);
		std::string filter = rList.GenerateFilter(ormasDal);
		std::vector<DataLayer::returnListViewCollection> productListVector = ormasDal.GetReturnList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				rListVec.push_back(ReturnListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Return list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (rListVec.size() > 0)
		{
			Stock stock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), wareID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum += (item.GetSum() - item.GetCount()*nCost.GetValue());
					netSum += item.GetCount()*nCost.GetValue();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetCount()*nCost.GetValue());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum += (item.GetSum() - item.GetCount()*nCost.GetValue());
					netSum += item.GetCount()*nCost.GetValue();
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + item.GetCount()*nCost.GetValue());
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt product list is empty!";
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
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, cID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		Warehouse warehouse;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, wareID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		int debAccID10740 = warehouse.GetSubaccountID();
		int credAccID = balance.GetSubaccountID();
		int debAccID44090 = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "44090", errorMessage);
		if (0 == debAccID10740 || 0 == credAccID || 0 == debAccID44090)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, rpID, debAccID10740, netSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (totalSum > 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, rpID, debAccID44090, totalSum, credAccID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		if (totalSum < 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, rpID, credAccID, totalSum*(-1), debAccID44090, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		return true;
	}

	bool Stock::ChangingByWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wpID, int empID, std::string& errorMessage)
	{
		
		WriteOffList cPList;
		std::vector<WriteOffListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cPList.SetWriteOffID(wpID);
		std::string filter = cPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffListViewCollection> productListVector = ormasDal.GetWriteOffList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(WriteOffListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromWOffProd(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum= totalSum+ item.GetSum();
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - item.GetSum());
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetSum()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "44090", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, wpID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByWriteOffReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wpID, int empID, std::string& errorMessage)
	{
		
		WriteOffList cPList;
		std::vector<WriteOffListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cPList.SetWriteOffID(wpID);
		std::string filter = cPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffListViewCollection> productListVector = ormasDal.GetWriteOffList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(WriteOffListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromWOffProd(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot receipt this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetSum());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + item.GetSum());
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetSum()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off product list is empty!";
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
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "44090", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, wpID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wpID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		WriteOffList cPList;
		std::vector<WriteOffListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cPList.SetWriteOffID(wpID);
		std::string filter = cPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffListViewCollection> productListVector = ormasDal.GetWriteOffList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cPListVec.push_back(WriteOffListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cPListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromWOffProd(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName(); 
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum= totalSum+ item.GetSum();
						stock.SetCount(stock.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetSum()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		CompanyAccountRelation caRel;
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "44090", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, wpID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wrID, int empID, std::string& errorMessage)
	{
		
		WriteOffRawList wRList;
		std::vector<WriteOffRawListView> wRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		wRList.SetWriteOffRawID(wrID);
		std::string filter = wRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawListViewCollection> productListVector = ormasDal.GetWriteOffRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				wRListVec.push_back(WriteOffRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (wRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromWOffRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in wRListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum= totalSum+ item.GetSum();
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - item.GetSum());
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetSum()) * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
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

		if (!this->CreateEntry(globalVar, ormasDal, wrID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByWriteOffRawReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wrID, int empID, std::string& errorMessage)
	{
		
		WriteOffRawList wRList;
		std::vector<WriteOffRawListView> wRListVec;
		double totalSum = 0.0;
		double newSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		wRList.SetWriteOffRawID(wrID);
		std::string filter = wRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawListViewCollection> productListVector = ormasDal.GetWriteOffRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				wRListVec.push_back(WriteOffRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (wRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromWOffRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in wRListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + std::round((product.GetPrice() * item.GetCount()) * 1000) / 1000;
					newSum = newSum + (item.GetSum());
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(std::round((product.GetPrice() * item.GetCount()) * 1000) / 1000);
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					stock.SetWarehouseID(warehouseID);
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + std::round((product.GetPrice() * item.GetCount()) * 1000) / 1000;
					newSum = newSum + (item.GetSum());
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + (std::round((product.GetPrice() * item.GetCount()) * 1000) / 1000));
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetSum()) * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
						return false;
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off raw list is empty!";
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
		int acc55020ID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
		int credAccID = subAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, wrID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		double checkSum = totalSum - newSum;
		if (checkSum > 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, wrID, acc55020ID, checkSum, credAccID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		else if (checkSum < 0)
		{
			if (!this->CreateEntry(globalVar, ormasDal, wrID, credAccID, checkSum *(-1), acc55020ID, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		return true;
	}

	bool Stock::ChangingByWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wrID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		WriteOffRawList wRList;
		std::vector<WriteOffRawListView> wRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		wRList.SetWriteOffRawID(wrID);
		std::string filter = wRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawListViewCollection> productListVector = ormasDal.GetWriteOffRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				wRListVec.push_back(WriteOffRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (wRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromWOffRaw(globalVar, ormasDal, empID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in wRListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum= totalSum+ item.GetSum();
						stock.SetCount(stock.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetSum()) * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
							return false;
						totalNewCount += stock.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Write-off raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
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

		if (!this->CreateEntry(globalVar, ormasDal, wrID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByProdConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pcrID, int stockEmpID, std::string& errorMessage)
	{
		
		ProductionConsumeRawList cRList;
		ProductionConsumeRaw cRaw;
		if (!cRaw.GetProductionConsumeRawByID(globalVar, ormasDal, pcrID, errorMessage))
			return false;
		std::vector<ProductionConsumeRawListView> cRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cRList.SetProductionConsumeRawID(pcrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawListViewCollection> productListVector = ormasDal.GetProductionConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cRListVec.push_back(ProductionConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		double totalOldSum = 0;
		double totalNewSum = 0;
		double totalChangingSum = 0;
		if (cRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromProdnConRaw(globalVar, ormasDal, stockEmpID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cRListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (item.GetCount()*(stock.GetSum() / stock.GetCount()) != item.GetSum())
						{
							item.SetSum(item.GetCount()*(stock.GetSum() / stock.GetCount()));
							item.stockEmployeeID = cRaw.GetStockEmployeeID();
							if (!item.UpdateProductionConsumeRawList(globalVar, ormasDal, errorMessage))
								return false;
						}
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						totalOldSum += stock.GetSum();
						totalChangingSum += item.GetSum();
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						stock.SetCount(stock.GetCount() - item.GetCount());
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum((stock.GetSum() - item.GetSum()));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (stock.GetCount() > 0)
						{
							if (std::round((oldSum - item.GetSum()) * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
								return false;
						}
						totalNewCount += stock.GetCount();
						totalNewSum += std::round(stock.GetSum() * 1000) / 1000;
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		ProductionConsumeRaw cpRaw;
		if (!cpRaw.GetProductionConsumeRawByID(globalVar, ormasDal, pcrID, errorMessage))
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		cpRaw.SetSum(totalSum);
		if (!cpRaw.SimpleUpdateProductionConsumeRaw(globalVar, ormasDal, errorMessage))
		{
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

		if (!this->CreateEntry(globalVar, ormasDal, pcrID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByProdConsumeRawReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pcrID, int stockEmpID, std::string& errorMessage)
	{
		
		ProductionConsumeRawList cRList;
		std::vector<ProductionConsumeRawListView> cRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cRList.SetProductionConsumeRawID(pcrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawListViewCollection> productListVector = ormasDal.GetProductionConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cRListVec.push_back(ProductionConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (cRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromProdnConRaw(globalVar, ormasDal, stockEmpID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			Status status;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cRListVec)
			{
				stock.Clear();
				product.Clear();
				status.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot order this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + (item.GetSum());
					stock.SetProductID(item.GetProductID());
					stock.SetCount(item.GetCount());
					stock.SetSum(item.GetCount()*product.GetPrice());
					stock.SetCurrencyID(item.GetCurrencyID());
					stock.SetStatusID(status.GetID());
					stock.SetWarehouseID(warehouseID);
					if (!stock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += stock.GetCount();
				}
				else
				{
					oldCount = stock.GetCount();
					oldSum = stock.GetSum();
					totalOldCount += stock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					stock.SetCount(stock.GetCount() + item.GetCount());
					stock.SetSum(stock.GetSum() + item.GetSum());
					if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
						return false;
					if (stock.GetCount() > 0)
					{
						if (std::round((oldSum + item.GetSum()) * 1000) / 1000 != std::round(stock.GetSum() * 1000) / 1000)
							return false;
					}
					totalNewCount += stock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
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

		if (!this->CreateEntry(globalVar, ormasDal, pcrID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByProdConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pcrID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		
		ProductionConsumeRawList cRList;
		ProductionConsumeRaw cRaw;
		if (!cRaw.GetProductionConsumeRawByID(globalVar, ormasDal, pcrID, errorMessage))
			return false;
		std::vector<ProductionConsumeRawListView> cRListVec;
		double totalSum = 0.0;
		int companyID = 0;
		int subAccID = 0;
		int warehouseID = 0;

		cRList.SetProductionConsumeRawID(pcrID);
		std::string filter = cRList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawListViewCollection> productListVector = ormasDal.GetProductionConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				cRListVec.push_back(ProductionConsumeRawListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		double totalOldSum = 0;
		double totalNewSum = 0;
		double totalChangingSum = 0;
		if (cRListVec.size() > 0)
		{
			if (!GetSubIDAndWerhIDFromProdnConRaw(globalVar, ormasDal, stockEmpID, warehouseID, subAccID, errorMessage))
				return false;
			Stock stock;
			Product product;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cRListVec)
			{
				stock.Clear();
				product.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warehouseID, errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of stock:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (stock.GetCount() < item.GetCount())
					{
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						errorMessage = "ERROR! There is not enough product in the stock!";
						errorMessage += " Product name:";
						errorMessage += product.GetName();
						errorMessage += ", Product count:";
						errorMessage += std::to_string(stock.GetCount());
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = stock.GetCount();
						oldSum = stock.GetSum();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (item.GetCount()*(stock.GetSum() / stock.GetCount()) != item.GetSum())
						{
							item.SetSum(item.GetCount()*(stock.GetSum() / stock.GetCount()));
							item.stockEmployeeID = cRaw.GetStockEmployeeID();
							if (!item.UpdateProductionConsumeRawList(globalVar, ormasDal, errorMessage))
								return false;
						}
						totalOldCount += stock.GetCount();
						totalChangingCount += item.GetCount();
						totalOldSum += stock.GetSum();
						totalChangingSum += item.GetSum();
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetSum();
						stock.SetCount(stock.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == stock.GetCount())
						{
							stock.SetSum(0);
						}
						else
						{
							stock.SetSum(stock.GetSum() - (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
						}
						if (!stock.UpdateStock(globalVar, ormasDal, errorMessage))
						{
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(stock.GetCount() * 1000) / 1000)
							return false;
						if (stock.GetCount() > 0)
						{
							if (std::round((oldSum - item.GetSum()) * 10) / 10 != std::round(stock.GetSum() * 10) / 10)
								return false;
						}
						totalNewCount += stock.GetCount();
						totalNewSum += stock.GetSum();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount - totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		ProductionConsumeRaw cpRaw;
		if (!cpRaw.GetProductionConsumeRawByID(globalVar, ormasDal, pcrID, errorMessage))
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		cpRaw.SetSum(totalSum);
		if (!cpRaw.SimpleUpdateProductionConsumeRaw(globalVar, ormasDal, errorMessage))
		{
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

		if (!this->CreateEntry(globalVar, ormasDal, pcrID, debAccID, totalSum, credAccID, pSum, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int warID, std::string& errorMessage)
	{
		
		ProductionList rPList;
		std::vector<ProductionListView> pListVec;
		double totalSum = 0.0;
		int companyID = 0;

		rPList.SetProductionID(pID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionListViewCollection> productListVector = ormasDal.GetProductionList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				pListVec.push_back(ProductionListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (pListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in pListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warID, errorMessage))
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
					pStock.SetProductID(item.GetProductID());
					pStock.SetCount(item.GetCount());
					pStock.SetSum(round((item.GetCount()*nCost.GetValue()) * 1000) / 1000);
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += pStock.GetCount();
				}
				else
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					pStock.SetCount(pStock.GetCount() + item.GetCount());
					pStock.SetSum(pStock.GetSum() + (item.GetCount()*nCost.GetValue()));
					if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(pStock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += pStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::ChangingByProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int warID, std::map<int, double> pProdCountMap, std::string& errorMessage)
	{
		
		ProductionList rPList;
		std::vector<ProductionListView> pListVec;
		double totalSum = 0.0;
		int companyID = 0;

		rPList.SetProductionID(pID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionListViewCollection> productListVector = ormasDal.GetProductionList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				pListVec.push_back(ProductionListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Product list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (pListVec.size() > 0)
		{
			Stock pStock;
			Product product;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in pListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!pStock.GetStockByProductAndWarehouseID(globalVar, ormasDal, item.GetProductID(), warID, errorMessage))
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					pStock.SetProductID(item.GetProductID());
					pStock.SetCount(item.GetCount());
					pStock.SetSum((item.GetCount()*nCost.GetValue()));
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += pStock.GetCount();
				}
				else
				{
					oldCount = pStock.GetCount();
					oldSum = pStock.GetSum();
					totalOldCount += pStock.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					pStock.SetCount(pStock.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					pStock.SetSum(pStock.GetSum() + ((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
					if (!pStock.UpdateStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(pStock.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(pStock.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += pStock.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		if (std::round((totalOldCount + totalChangingCount) * 1000) / 1000 != std::round(totalNewCount * 1000) / 1000)
		{
			errorMessage = "Document is wrong! Sum and count does not the same in list and document.";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Stock::RecalculateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage)
	{
		
		Stock checkStock;
		Stock stock;
		std::vector<DataLayer::stockViewCollection> stockVector;
		std::string filter;
		WarehouseType wType;
		Warehouse warehouse;
		Product product;
		ProductType pType;
		checkStock.Clear();
		int companyID = 0;
		double difference = 0;
		if (!wType.GetWarehouseTypeByCode(globalVar, ormasDal, "RAW", errorMessage))
		{
			return false;
		}
		checkStock.SetProductID(pID);
		filter = checkStock.GenerateFilter(ormasDal);
		stockVector = ormasDal.GetStock(errorMessage, filter);
		if (stockVector.size() == 0)
		{
			return true;
		}
		else
		{
			for each (auto stockObject in stockVector)
			{
				stock.Clear();
				warehouse.Clear();
				product.Clear();
				pType.Clear();
				if (!stock.GetStockByID(globalVar, ormasDal, std::get<0>(stockObject), errorMessage))
					return false;
				if (stock.GetCount() > 0)
				{
					if (!warehouse.GetWarehouseByID(globalVar, ormasDal, stock.GetWarehouseID(), errorMessage))
						return false;
					if (warehouse.GetWarehouseTypeID() == wType.GetID())
					{
						if (!product.GetProductByID(globalVar, ormasDal, pID, errorMessage))
							return false;
						if (!pType.GetProductTypeByCode(globalVar, ormasDal, "PRODUCT", errorMessage))
							return false;
						if (product.GetProductTypeID() == pType.GetID())
							continue;

						companyID = product.GetCompanyID();
						difference = std::round((stock.GetCount()*newPrice - stock.GetCount()*oldPrice) * 1000) / 1000;
						stock.SetSum(stock.GetSum() + difference);
						stock.UpdateStock(globalVar, ormasDal, errorMessage);


						if (difference > 0 && difference != 0)
						{
							CompanyAccountRelation caRel;
							int debAccID = warehouse.GetSubaccountID();
							int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55020", errorMessage);
							if (0 == debAccID || 0 == credAccID)
							{
								return false;
							}
							if (!this->CreateEntry(globalVar, ormasDal, product.GetID(), debAccID, difference, credAccID, errorMessage))
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
							if (!this->CreateEntry(globalVar, ormasDal, product.GetID(), credAccID, difference * (-1), debAccID, errorMessage))
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
	
	bool Stock::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		std::string	entryText;
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
	bool Stock::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		std::string	entryText;
		entryText += wstring_to_utf8(L"Складская операция. ID операции = ");
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

	bool Stock::CreateCorrectongEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		std::string	entryText;
		entryText += wstring_to_utf8(L"Коррекция счета 10740 готовая продукция, после переоценки себестоимости продукта, ID продукта = ");
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
	
	bool Stock::CreateCorrectongEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		std::string	entryText;
		entryText += wstring_to_utf8(L"Коррекция счета 10740 готовая продукция, после переоценки себестоимости продукта, ID продукта = ");
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
		entryText += wstring_to_utf8(L"Коррекция счета 10740 готовая продукция, после переоценки себестоимости продукта, ID продукта = ");
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

	std::string Stock::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}

	bool Stock::GetSubIDAndWerhIDFromConProd(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stockEmpID, int& warehouseID, int& subAccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, stockEmpID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		warehouseID = warehouse.GetID();
		subAccID = warehouse.GetSubaccountID();
		return true;
	}

	bool Stock::GetSubIDAndWerhIDFromConRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int stockEmpID,  int& debWerID, int& credWerID, int& debSaccID, int& credSaccID, std::string& errorMessage)
	{
		
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, empID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		debSaccID = warehouse.GetSubaccountID();
		debWerID = warehouse.GetID();
		weRel.Clear();
		warehouse.Clear();
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, stockEmpID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		credSaccID = warehouse.GetSubaccountID();
		credWerID = warehouse.GetID();
		return true;
	}

	bool Stock::GetSubIDAndWerhIDFromOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage)
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

	bool Stock::GetSubIDAndWerhIDFromRcpRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int stockEmpID, int& debWerID, int& credWerID, int& debSaccID, int& credSaccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, empID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		credSaccID = warehouse.GetSubaccountID();
		credWerID = warehouse.GetID();
		weRel.Clear();
		warehouse.Clear();
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, stockEmpID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		debSaccID = warehouse.GetSubaccountID();
		debWerID = warehouse.GetID();
		return true;
	}

	bool Stock::GetSubIDAndWerhIDFromRcpProd(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int stockEmpID, int& debWerID, int& credWerID, int& debSaccID, int& credSaccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, empID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		credSaccID = warehouse.GetSubaccountID();
		credWerID = warehouse.GetID();
		weRel.Clear();
		warehouse.Clear();
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, stockEmpID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		debSaccID = warehouse.GetSubaccountID();
		debWerID = warehouse.GetID();
		return true;
	}

	bool Stock::GetSubIDAndWerhIDFromRtrnProd(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, empID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		subAccID = warehouse.GetSubaccountID();
		warehouseID = warehouse.GetID();
		return true;
	}

	bool Stock::GetSubIDAndWerhIDFromWOffProd(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, empID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		subAccID = warehouse.GetSubaccountID();
		warehouseID = warehouse.GetID();
		return true;
	}

	bool Stock::GetSubIDAndWerhIDFromProdnConRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stockEmpID, int& warehouseID, int& subAccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, stockEmpID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		subAccID = warehouse.GetSubaccountID();
		warehouseID = warehouse.GetID();
		return true;
	}

	bool Stock::GetSubIDAndWerhIDFromWOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRel;
		Warehouse warehouse;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, empID, errorMessage))
			return false;
		if (!warehouse.GetWarehouseByID(globalVar, ormasDal, weRel.GetWarehouseID(), errorMessage))
			return false;
		subAccID = warehouse.GetSubaccountID();
		warehouseID = warehouse.GetID();
		return true;
	}

	bool Stock::CreateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stockID, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string& errorMessage)
	{
		StockChangeLog scLog;
		scLog.SetStockID(stockID);
		scLog.SetProductID(pID);
		scLog.SetCount(sCount);
		scLog.SetSum(sSum);
		scLog.SetStatusID(sID);
		scLog.SetCurrencyID(cID);
		scLog.SetWarehouseID(wID);
		scLog.SetLogDate(ormasDal.GetSystemDateTime());
		scLog.SetUserID(globalVar->userID);
		scLog.SetOperationID(globalVar->currentOperationID);
		if (scLog.CreateStockChangeLog(globalVar, ormasDal, errorMessage))
			return true;
		return false;
	}

	bool Stock::IsStockValid(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		return true;
	}
}