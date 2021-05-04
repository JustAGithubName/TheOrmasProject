#include "stdafx.h"
#include "ProductionStockClass.h"
#include "BalanceClass.h"
#include "ProductionListClass.h"
#include "ProductionListViewClass.h"
#include "ProductClass.h"
#include "StatusClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "AccountClass.h"
#include "SubaccountClass.h"
#include "CompanyAccountRelationClass.h"
#include "ConsumeRawListClass.h"
#include "ConsumeRawListViewClass.h"
#include "ReceiptProductListClass.h"
#include "ReceiptProductListViewClass.h"
#include "NetCostClass.h"
#include "ProductionConsumeRawListClass.h"
#include "ProductionConsumeRawListViewClass.h"
#include <codecvt>

namespace BusinessLayer
{
	ProductionStock::ProductionStock(DataLayer::productionStockCollection sCollection)
	{
		id = std::get<0>(sCollection);
		productID = std::get<1>(sCollection);
		count = std::get<2>(sCollection);
		sum = std::get<3>(sCollection);
		statusID = std::get<4>(sCollection);
		currencyID = std::get<5>(sCollection);
		warehouseID = std::get<6>(sCollection);
	}

	int ProductionStock::GetID()
	{
		return id;
	}

	int ProductionStock::GetProductID()
	{
		return productID;
	}

	double ProductionStock::GetCount()
	{
		return count;
	}

	double ProductionStock::GetSum()
	{
		return sum;
	}

	int ProductionStock::GetStatusID()
	{
		return statusID;
	}

	int ProductionStock::GetCurrencyID()
	{
		return currencyID;
	}

	int ProductionStock::GetWarehouseID()
	{
		return warehouseID;
	}

	void ProductionStock::SetID(int sID)
	{
		id = sID;
	}

	void ProductionStock::SetProductID(int sProductID)
	{
		productID = sProductID;
	}
	void ProductionStock::SetCount(double sCount)
	{
		count = sCount;
	}
	void ProductionStock::SetSum(double sSum)
	{
		sum = sSum;
	}
	void ProductionStock::SetStatusID(int sStatusID)
	{
		statusID = sStatusID;
	}
	void ProductionStock::SetCurrencyID(int sCurrencyID)
	{
		currencyID = sCurrencyID;
	}
	void ProductionStock::SetWarehouseID(int sWarehouseID)
	{
		warehouseID = sWarehouseID;
	}

	bool ProductionStock::CreateProductionStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
		int sID, int cID, int wID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		productID = pID;
		count = sCount;
		sum = sSum;
		statusID = sID;
		currencyID = cID;
		warehouseID = wID;
		if (0 != id && ormasDal.CreateProductionStock(id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionStock::CreateProductionStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateProductionStock(id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionStock::DeleteProductionStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteProductionStock(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool ProductionStock::UpdateProductionStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
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
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateProductionStock(id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ProductionStock::UpdateProductionStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (count < 0 || sum < 0)
		{
			errorMessage = "Count or sum cannot be less then 0!";
			return false;
		}
		if (0 != id && ormasDal.UpdateProductionStock(id, productID, count, sum, statusID, currencyID, warehouseID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ProductionStock::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != count || 0 != sum || 0 != statusID || 0 != warehouseID)
		{
			return ormasDal.GetFilterForProductionStock(id, productID, count, sum, statusID, currencyID, warehouseID);
		}
		return "";
	}

	bool ProductionStock::GetProductionStockByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productionStockViewCollection> productionStockVector = ormasDal.GetProductionStock(errorMessage, filter);
		if (0 != productionStockVector.size())
		{
			id = std::get<0>(productionStockVector.at(0));
			count = std::get<6>(productionStockVector.at(0));
			sum = std::get<7>(productionStockVector.at(0));
			productID = std::get<12>(productionStockVector.at(0));
			statusID = std::get<13>(productionStockVector.at(0));
			currencyID = std::get<14>(productionStockVector.at(0));
			warehouseID = std::get<15>(productionStockVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Production Stock with this id";
		}
		return false;
	}

	bool ProductionStock::GetProductionStockByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productionStockViewCollection> productionStockVector = ormasDal.GetProductionStock(errorMessage, filter);
		if (0 != productionStockVector.size())
		{
			id = std::get<0>(productionStockVector.at(0));
			count = std::get<6>(productionStockVector.at(0));
			sum = std::get<7>(productionStockVector.at(0));
			productID = std::get<12>(productionStockVector.at(0));
			statusID = std::get<13>(productionStockVector.at(0));
			currencyID = std::get<14>(productionStockVector.at(0));
			warehouseID = std::get<15>(productionStockVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Production Stock with this id";
		}
		return false;
	}

	bool ProductionStock::IsEmpty()
	{
		if (0 == id && 0 == count && 0 == sum && 0 == productID && 0 == statusID && 0 == currencyID && 0 == warehouseID)
			return true;
		return false;
	}

	void ProductionStock::Clear()
	{
		id = 0;
		count = 0;
		sum = 0;
		productID = 0;
		statusID = 0;
		currencyID = 0;
		warehouseID = 0;
	}

	bool ProductionStock::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		ProductionStock productionStock;
		productionStock.Clear();
		errorMessage.clear();
		productionStock.SetProductID(pID);
		std::string filter = productionStock.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionStockViewCollection> productionStockVector = ormasDal.GetProductionStock(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionStockVector.size())
		{
			return false;
		}
		errorMessage = "Production Stock with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductionStock::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ProductionStock productionStock;
		productionStock.Clear();
		errorMessage.clear();
		productionStock.SetProductID(productID);
		std::string filter = productionStock.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionStockViewCollection> productionStockVector = ormasDal.GetProductionStock(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionStockVector.size())
		{
			return false;
		}
		errorMessage = "ProductionStock with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductionStock::ChangingByStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, std::string& errorMessage)
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
		if (rRListVec.size() > 0)
		{
			ProductionStock pStock;
			Product product;
			Status status;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
				{
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
					if (!pStock.CreateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetCount(pStock.GetCount() + item.GetCount());
					pStock.SetSum(pStock.GetSum() + item.GetSum());
					if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
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
		return true;
	}

	bool ProductionStock::ChangingByStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
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
		if (rRListVec.size() > 0)
		{
			ProductionStock pStock;
			Product product;
			Status status;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in rRListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
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
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetProductID(item.GetProductID());
					pStock.SetCount(item.GetCount());
					pStock.SetSum(item.GetSum());
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetCount(pStock.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					pStock.SetSum(pStock.GetSum() + (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
					if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Receipt raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool ProductionStock::ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		ReceiptProductListView rPList;
		std::vector<ReceiptProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;

		rPList.SetReceiptProductID(cpID);
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
		if (cPListVec.size() > 0)
		{
			ProductionStock pStock;
			Product product;
			NetCost nCost;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				pStock.Clear();
				product.Clear();
				nCost.Clear();
				if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
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
						
						if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
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

		
		return true;
	}

	bool ProductionStock::ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		ReceiptProductListView rPList;
		std::vector<ReceiptProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;

		rPList.SetReceiptProductID(cpID);
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
		if (cPListVec.size() > 0)
		{
			ProductionStock pStock;
			Product product;
			NetCost nCost;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				pStock.Clear();
				product.Clear();
				nCost.Clear();
				if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
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
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetCount()*nCost.GetValue();
						pStock.SetCount(pStock.GetCount() -(item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == pStock.GetCount())
						{
							pStock.SetSum(0);
						}
						else
						{
							pStock.SetSum(pStock.GetSum() - ((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
						}
						
						if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
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

		
		return true;
	}

	bool ProductionStock::ChangingByProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
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
		if (pListVec.size() > 0)
		{
			ProductionStock pStock;
			Product product;
			Status status;
			NetCost nCost;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in pListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
				{
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
					pStock.SetSum(round((item.GetCount()*nCost.GetValue())*1000)/1000);
					pStock.SetCurrencyID(item.GetCurrencyID());
					pStock.SetStatusID(status.GetID());
					if (!pStock.CreateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					pStock.SetCount(pStock.GetCount() + item.GetCount());
					pStock.SetSum(pStock.GetSum() + (item.GetCount()*nCost.GetValue()));
					if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		
		return true;
	}

	bool ProductionStock::ChangingByProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::map<int, double> pProdCountMap, std::string& errorMessage)
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
		if (pListVec.size() > 0)
		{
			ProductionStock pStock;
			Product product;
			Status status;
			NetCost nCost;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in pListVec)
			{
				pStock.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
				{
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
					if (!pStock.CreateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					pStock.SetCount(pStock.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					pStock.SetSum(pStock.GetSum() + ((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
					if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Product list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		
		return true;
	}

	bool ProductionStock::ChangingByConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage)
	{
		ProductionConsumeRawList cRList;
		std::vector<ProductionConsumeRawListView> cRListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cRList.SetProductionConsumeRawID(crID);
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
			errorMessage = "ERROR! Production Consume raw list is empty!";
			return false;
		}
		if (cRListVec.size() > 0)
		{
			ProductionStock pStock;
			Product product;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cRListVec)
			{
				pStock.Clear();
				product.Clear();
				if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
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
						pStock.SetSum(pStock.GetSum() - item.GetSum());
					}
					if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Production consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		
		return true;
	}

	bool ProductionStock::ChangingByConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		ProductionConsumeRawList cRList;
		std::vector<ProductionConsumeRawListView> cRListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cRList.SetProductionConsumeRawID(crID);
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
			errorMessage = "ERROR! Production Consume raw list is empty!";
			return false;
		}
		if (cRListVec.size() > 0)
		{
			ProductionStock pStock;
			Product product;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cRListVec)
			{
				pStock.Clear();
				product.Clear();
				if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, item.GetProductID(), errorMessage))
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
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetSum();
					pStock.SetCount(pStock.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					if (0 == pStock.GetCount())
					{
						pStock.SetSum(0);
					}
					else
					{
						pStock.SetSum(pStock.GetSum() - (item.GetSum() - (pProdCountMap.find(product.GetID())->second * product.GetPrice())));
					}
					if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
					{
						return false;
					}

				}
			}
		}
		else
		{
			errorMessage = "ERROR! Production consume raw list is empty!";
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		
		return true;
	}

	bool ProductionStock::ChangingByReworkRawDec(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double count, double sum, std::string& errorMessage)
	{
		ProductionStock pStock;
		Product product;
		pStock.Clear();
		product.Clear();
		if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, pID, errorMessage))
		{
			if (!product.GetProductByID(globalVar, ormasDal, pID, errorMessage))
				return false;
			errorMessage = "ERROR! This product is out of stock:";
			errorMessage += product.GetName();
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		else
		{
			if (!product.GetProductByID(globalVar, ormasDal, pID, errorMessage))
				return false;
			pStock.SetCount(pStock.GetCount() - count);
			if (0 == pStock.GetCount())
			{
				pStock.SetSum(0);
			}
			else
			{
				pStock.SetSum(pStock.GetSum() - sum);
			}
			if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		return true;
	}

	bool ProductionStock::ChangingByReworkRawInc(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double count, double sum, std::string& errorMessage)
	{
		ProductionStock pStock;
		Product product;
		Status status;
		pStock.Clear();
		product.Clear();
		status.Clear();
		if (!pStock.GetProductionStockByProductID(globalVar, ormasDal, pID, errorMessage))
		{
			errorMessage.clear();
			if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
			{
				errorMessage = "ERROR! Cannot consume this product, status is not valied!";
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
			if (!product.GetProductByID(globalVar, ormasDal, pID, errorMessage))
				return false;
			pStock.SetProductID(pID);
			pStock.SetCount(count);
			pStock.SetSum(sum);
			pStock.SetCurrencyID(product.GetCurrencyID());
			pStock.SetStatusID(status.GetID());
			if (!pStock.CreateProductionStock(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			if (!product.GetProductByID(globalVar, ormasDal, pID, errorMessage))
				return false;
			pStock.SetCount(pStock.GetCount() + count);
			pStock.SetSum(pStock.GetSum() + sum);
			if (!pStock.UpdateProductionStock(globalVar, ormasDal, errorMessage))
			{
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
		}
		return true;
	}

	bool ProductionStock::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Складская операция"));
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
		return true;
	}
	bool ProductionStock::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Складская операция, обратная проводка"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage, true))
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
		entry.Clear();
		eoRelation.Clear();
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Складская операция"));
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
		return true;
	}

	std::string ProductionStock::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}