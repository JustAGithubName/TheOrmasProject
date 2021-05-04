#include "stdafx.h"
#include "TransportClass.h"
#include "TransportListClass.h"
#include "TransportListViewClass.h"
#include "ConsumeProductClass.h"
#include "ConsumeProductListClass.h"
#include "ConsumeProductListViewClass.h"
#include "OrderClass.h"
#include "OrderListClass.h"
#include "OrderListViewClass.h"
#include "UserClass.h"
#include "StatusClass.h"
#include "ProductClass.h"
#include "NetCostClass.h"
#include "CompanyAccountRelationClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "WarehouseClass.h"
#include "WarehouseTypeClass.h"
#include "WarehouseEmployeeRelationClass.h"
#include <codecvt>

namespace BusinessLayer
{
	Transport::Transport(DataLayer::transportsCollection tCollection)
	{
		id = std::get<0>(tCollection);
		userID = std::get<1>(tCollection);
		date = std::get<2>(tCollection);
		executionDate = std::get<3>(tCollection);
		employeeID = std::get<4>(tCollection);
		count = std::get<5>(tCollection);
		sum = std::get<6>(tCollection);
		statusID = std::get<7>(tCollection);
		currencyID = std::get<8>(tCollection);
	}

	int Transport::GetID()
	{
		return id;
	}

	int Transport::GetUserID()
	{
		return userID;
	}

	std::string Transport::GetDate()
	{
		return date;
	}

	std::string Transport::GetExecutionDate()
	{
		return executionDate;
	}

	int Transport::GetEmployeeID()
	{
		return employeeID;
	}

	double Transport::GetCount()
	{
		return count;
	}

	double Transport::GetSum()
	{
		return sum;
	}

	int Transport::GetStatusID()
	{
		return statusID;
	}

	int Transport::GetCurrencyID()
	{
		return currencyID;
	}

	void Transport::SetID(int tID)
	{
		id = tID;
	}
	void Transport::SetUserID(int tUserID)
	{
		userID = tUserID;
	}
	void Transport::SetDate(std::string tDate)
	{
		date = tDate;
	}
	void Transport::SetExecutionDate(std::string tExecutionDate)
	{
		executionDate = tExecutionDate;
	}
	void Transport::SetEmployeeID(int tEmployeeID)
	{
		employeeID = tEmployeeID;
	}

	void Transport::SetCount(double tCount)
	{
		count = tCount;
	}

	void Transport::SetSum(double tSum)
	{
		sum = tSum;
	}

	void Transport::SetStatusID(int tStatusID)
	{
		statusID = tStatusID;
	}

	void Transport::SetCurrencyID(int tCurrencyID)
	{
		currencyID = tCurrencyID;
	}

	bool Transport::CreateTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string tDate, std::string tExecDate, 
		int eID, double tCount, double tSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, eID ,errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		userID = uID;
		date = tDate;
		executionDate = tExecDate;
		employeeID = eID;
		count = tCount;
		sum = tSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateTransport(id, userID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	bool Transport::CreateTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (0 != id && ormasDal.CreateTransport(id, userID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Transport::DeleteTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeleteTransport(id, errorMessage))
		{
			if (ormasDal.DeleteListByTransportID(id, errorMessage))
			{
				Clear();
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
			else
			{
				//ormasDal.CancelTransaction(errorMessage);
			}
		}
		else
		{
			//ormasDal.CancelTransaction(errorMessage);
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Transport::UpdateTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string tDate, std::string tExecnDate,
		int eID, double tCount, double tSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		userID = uID;
		date = tDate;
		executionDate = tExecnDate;
		employeeID = eID;
		count = tCount;
		sum = tSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateTransport(id, userID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Transport::UpdateTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (0 != id && ormasDal.UpdateTransport(id, userID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Transport::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != userID || !date.empty() || !executionDate.empty() || 0 != employeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForTransport(id, userID, date, executionDate, employeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool Transport::GetTransportByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, std::string& errorMessage)
	{
		if (tID <= 0)
			return false;
		id = tID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportsViewCollection> transportVector = ormasDal.GetTransports(errorMessage, filter);
		if (0 != transportVector.size())
		{
			id = std::get<0>(transportVector.at(0));
			date = std::get<1>(transportVector.at(0));
			executionDate = std::get<2>(transportVector.at(0));
			count = std::get<13>(transportVector.at(0));
			sum = std::get<14>(transportVector.at(0));
			employeeID = std::get<16>(transportVector.at(0));
			userID = std::get<17>(transportVector.at(0));
			statusID = std::get<18>(transportVector.at(0));
			currencyID = std::get<19>(transportVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find transport with this id";
		}
		return false;
	}

	bool Transport::GetTransportByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		if (eID <= 0)
			return false;
		employeeID = eID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::transportsViewCollection> transportVector = ormasDal.GetTransports(errorMessage, filter);
		if (0 != transportVector.size())
		{
			id = std::get<0>(transportVector.at(0));
			date = std::get<1>(transportVector.at(0));
			executionDate = std::get<2>(transportVector.at(0));
			count = std::get<13>(transportVector.at(0));
			sum = std::get<14>(transportVector.at(0));
			employeeID = std::get<16>(transportVector.at(0));
			userID = std::get<17>(transportVector.at(0));
			statusID = std::get<18>(transportVector.at(0));
			currencyID = std::get<19>(transportVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find transport with this id";
		}
		return false;
	}

	bool Transport::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == employeeID && 0 == userID && 0 == statusID
			&& 0 == currencyID)
			return true;
		return false;
	}

	void Transport::Clear()
	{
		id = 0;
		date.clear();
		executionDate.clear();
		count = 0;
		sum = 0;
		employeeID = 0;
		userID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool Transport::ChangingByReceiptProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		ConsumeProduct consumeProduct;
		if (!consumeProduct.GetConsumeProductByID(globalVar, ormasDal, cpID, errorMessage))
			return false;
		Transport transport;
		if (!transport.GetTransportByEmployeeID(globalVar, ormasDal, consumeProduct.GetEmployeeID(), errorMessage))
		{
			transport.Clear();
			transport.SetID(ormasDal.GenerateID());
			transport.SetDate(ormasDal.GetSystemDate());
			transport.SetEmployeeID(consumeProduct.GetEmployeeID());
			if (!transport.CreateTransport(globalVar, ormasDal, errorMessage))
				return false;
		}
		
		ConsumeProductList cPList;
		std::vector<ConsumeProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;

		cPList.SetConsumeProductID(cpID);
		std::string filter = cPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeProductListViewCollection> productListVector = ormasDal.GetConsumeProductList(errorMessage, filter);
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
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
		if (cPListVec.size() > 0)
		{
			Product product;
			TransportList tList;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				tList.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!tList.GetTransportListByTransportAndProductID(globalVar, ormasDal, transport.GetID(), item.GetProductID(), errorMessage))
				{
					oldCount = tList.GetCount();
					oldSum = tList.GetSum();
					totalOldCount += tList.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "TRANSPORTING", errorMessage))
					{
						errorMessage = "ERROR! Cannot transport this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					tList.SetTransportID (transport.GetID());
					tList.SetProductID(item.GetProductID());
					tList.SetCount(item.GetCount());
					tList.SetSum((item.GetCount()*nCost.GetValue()));
					tList.SetCurrencyID(item.GetCurrencyID());
					tList.SetStatusID(status.GetID());
					if (!tList.CreateTransportList(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += tList.GetCount();
				}
				else
				{
					oldCount = tList.GetCount();
					oldSum = tList.GetSum();
					totalOldCount += tList.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					tList.SetCount(tList.GetCount() + item.GetCount());
					tList.SetSum(tList.GetSum() + (item.GetCount()*nCost.GetValue()));
					if (!tList.UpdateTransportList(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(tList.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(tList.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += tList.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Transport list is empty!";
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

	bool Transport::ChangingByReceiptProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		ConsumeProduct consumeProduct;
		if (!consumeProduct.GetConsumeProductByID(globalVar, ormasDal, cpID, errorMessage))
			return false;
		Transport transport;
		if (!transport.GetTransportByEmployeeID(globalVar, ormasDal, consumeProduct.GetEmployeeID(), errorMessage))
		{
			transport.Clear();
			transport.SetID(ormasDal.GenerateID());
			transport.SetDate(ormasDal.GetSystemDate());
			transport.SetEmployeeID(consumeProduct.GetEmployeeID());
			if (!transport.CreateTransport(globalVar, ormasDal, errorMessage))
				return false;
		}

		ConsumeProductList cPList;
		std::vector<ConsumeProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;

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
			Product product;
			TransportList tList;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				tList.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!tList.GetTransportListByTransportAndProductID(globalVar, ormasDal, transport.GetID(), item.GetProductID(), errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of transport:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (tList.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the transport!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(transport.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = tList.GetCount();
						oldSum = tList.GetSum();
						totalOldCount += tList.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
						tList.SetCount(tList.GetCount() - item.GetCount());
						if (0 == tList.GetCount())
						{
							tList.SetSum(0);
						}
						else
						{
							tList.SetSum(tList.GetSum() - (item.GetCount()*nCost.GetValue()));
						}
						if (!tList.UpdateTransportList(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(tList.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(tList.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += tList.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Transport list is empty!";
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

	bool Transport::ChangingByReceiptProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		ConsumeProduct consumeProduct;
		if (!consumeProduct.GetConsumeProductByID(globalVar, ormasDal, cpID, errorMessage))
			return false;
		Transport transport;
		if (!transport.GetTransportByEmployeeID(globalVar, ormasDal, consumeProduct.GetEmployeeID(), errorMessage))
		{
			transport.Clear();
			transport.SetID(ormasDal.GenerateID());
			transport.SetDate(ormasDal.GetSystemDate());
			transport.SetEmployeeID(consumeProduct.GetEmployeeID());
			if (!transport.CreateTransport(globalVar, ormasDal, errorMessage))
				return false;
		}

		ConsumeProductList cPList;
		std::vector<ConsumeProductListView> cPListVec;
		double totalSum = 0.0;
		int companyID = 0;

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
			Product product;
			TransportList tList;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in cPListVec)
			{
				tList.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!tList.GetTransportListByTransportAndProductID(globalVar, ormasDal, transport.GetID(), item.GetProductID(), errorMessage))
				{
					oldCount = tList.GetCount();
					oldSum = tList.GetSum();
					totalOldCount += tList.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "IN STOCK", errorMessage))
					{
						errorMessage = "ERROR! Cannot transport this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					tList.SetTransportID(transport.GetID());
					tList.SetProductID(item.GetProductID());
					tList.SetCount(item.GetCount());
					tList.SetSum(item.GetCount()*nCost.GetValue());
					tList.SetCurrencyID(item.GetCurrencyID());
					tList.SetStatusID(status.GetID());
					if (!tList.CreateTransportList(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += tList.GetCount();
				}
				else
				{
					oldCount = tList.GetCount();
					oldSum = tList.GetSum();
					totalOldCount += tList.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					tList.SetCount(tList.GetCount() + (item.GetCount() - pProdCountMap.find(product.GetID())->second));
					tList.SetSum(tList.GetSum() + ((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
					if (!tList.UpdateTransportList(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(tList.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(tList.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += tList.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Transport list is empty!";
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

	bool Transport::ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		Order order;
		if (!order.GetOrderByID(globalVar, ormasDal, oID, errorMessage))
			return false;
		Transport transport;
		if (!transport.GetTransportByEmployeeID(globalVar, ormasDal, order.GetEmployeeID(), errorMessage))
		{
			errorMessage = "This employee does not have a transport!";
			return false;
		}

		OrderList oList;
		std::vector<OrderListView> oListVec;
		double totalSum = 0.0;
		int companyID = 0;

		oList.SetOrderID(oID);
		std::string filter = oList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderListViewCollection> productListVector = ormasDal.GetOrderList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				oListVec.push_back(OrderListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Order list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (oListVec.size() > 0)
		{
			Product product;
			TransportList tList;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in oListVec)
			{
				tList.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!tList.GetTransportListByTransportAndProductID(globalVar, ormasDal, transport.GetID(), item.GetProductID(), errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of transport:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (tList.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the transport!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(transport.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = tList.GetCount();
						oldSum = tList.GetSum();
						totalOldCount += tList.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + round(item.GetCount()*nCost.GetValue() * 1000) / 1000;
						tList.SetCount(tList.GetCount() - item.GetCount());
						if (0 == tList.GetCount())
						{
							tList.SetSum(0);
						}
						else
						{
							tList.SetSum(tList.GetSum() - (item.GetCount()*nCost.GetValue()));
						}
						if (!tList.UpdateTransportList(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(tList.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(tList.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += tList.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Transport list is empty!";
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
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55010", errorMessage);
		int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10742", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, oID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Transport::ChangingByConsumeProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		Order order;
		if (!order.GetOrderByID(globalVar, ormasDal, oID, errorMessage))
			return false;
		Transport transport;
		if (!transport.GetTransportByEmployeeID(globalVar, ormasDal, order.GetEmployeeID(), errorMessage))
		{
			errorMessage = "This employee does not have a transport!";
			return false;
		}

		OrderList oList;
		std::vector<OrderListView> oListVec;
		double totalSum = 0.0;
		int companyID = 0;

		oList.SetOrderID(oID);
		std::string filter = oList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderListViewCollection> productListVector = ormasDal.GetOrderList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				oListVec.push_back(OrderListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Order list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (oListVec.size() > 0)
		{
			Product product;
			TransportList tList;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in oListVec)
			{
				tList.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!tList.GetTransportListByTransportAndProductID(globalVar, ormasDal, transport.GetID(), item.GetProductID(), errorMessage))
				{
					oldCount = tList.GetCount();
					oldSum = tList.GetSum();
					totalOldCount += tList.GetCount();
					totalChangingCount += item.GetCount();
					errorMessage.clear();
					if (!status.GetStatusByName(globalVar, ormasDal, "TRANSPORTING", errorMessage))
					{
						errorMessage = "ERROR! Cannot transport this product, status is not valied!";
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					tList.SetTransportID(transport.GetID());
					tList.SetProductID(item.GetProductID());
					tList.SetCount(item.GetCount());
					tList.SetSum((item.GetCount()*nCost.GetValue()));
					tList.SetCurrencyID(item.GetCurrencyID());
					tList.SetStatusID(status.GetID());
					if (!tList.CreateTransportList(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					totalNewCount += tList.GetCount();
				}
				else
				{
					oldCount = tList.GetCount();
					oldSum = tList.GetSum();
					totalOldCount += tList.GetCount();
					totalChangingCount += item.GetCount();
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
						return false;
					companyID = product.GetCompanyID();
					totalSum = totalSum + item.GetCount()*nCost.GetValue();
					tList.SetCount(tList.GetCount() + item.GetCount());
					tList.SetSum(tList.GetSum() + (item.GetCount()*nCost.GetValue()));
					if (!tList.UpdateTransportList(globalVar, ormasDal, errorMessage))
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					if (std::round((oldCount + item.GetCount()) * 1000) / 1000 != std::round(tList.GetCount() * 1000) / 1000)
						return false;
					if (std::round((oldSum + item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(tList.GetSum() * 1000) / 1000)
						return false;
					totalNewCount += tList.GetCount();
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Transport list is empty!";
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
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55010", errorMessage);
		int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10742", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, oID, credAccID, totalSum, debAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}


	bool Transport::ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		Order order;
		if (!order.GetOrderByID(globalVar, ormasDal, oID, errorMessage))
			return false;
		Transport transport;
		if (!transport.GetTransportByEmployeeID(globalVar, ormasDal, order.GetEmployeeID(), errorMessage))
		{
			errorMessage = "This employee does not have a transport!";
			return false;
		}

		OrderList oList;
		std::vector<OrderListView> oListVec;
		double totalSum = 0.0;
		int companyID = 0;

		oList.SetOrderID(oID);
		std::string filter = oList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderListViewCollection> productListVector = ormasDal.GetOrderList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				oListVec.push_back(OrderListView(item));
			}
		}
		else
		{
			errorMessage = "ERROR! Order list is empty!";
			return false;
		}
		double totalOldCount = 0;
		double totalNewCount = 0;
		double totalChangingCount = 0;
		if (oListVec.size() > 0)
		{
			Product product;
			TransportList tList;
			Status status;
			NetCost nCost;
			double oldCount = 0;
			double oldSum = 0;
			//ormasDal.StartTransaction(errorMessage);
			for each (auto item in oListVec)
			{
				tList.Clear();
				product.Clear();
				status.Clear();
				nCost.Clear();
				if (!tList.GetTransportListByTransportAndProductID(globalVar, ormasDal, transport.GetID(), item.GetProductID(), errorMessage))
				{
					if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						return false;
					errorMessage = "ERROR! This product is out of transport:";
					errorMessage += product.GetName();
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
				else
				{
					if (tList.GetCount() < item.GetCount())
					{
						if (product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
						{
							errorMessage = "ERROR! There is not enough product in the transport!";
							errorMessage += " Product name:";
							errorMessage += product.GetName();
							errorMessage += ", Product count:";
							errorMessage += std::to_string(transport.GetCount());

						}
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
					else
					{
						oldCount = tList.GetCount();
						oldSum = tList.GetSum();
						totalOldCount += tList.GetCount();
						totalChangingCount += item.GetCount();
						if (!product.GetProductByID(globalVar, ormasDal, item.GetProductID(), errorMessage))
							return false;
						if (!nCost.GetNetCostByProductID(globalVar, ormasDal, product.GetID(), errorMessage))
							return false;
						companyID = product.GetCompanyID();
						totalSum = totalSum + item.GetCount()*nCost.GetValue();
						tList.SetCount(tList.GetCount() - (item.GetCount() - pProdCountMap.find(product.GetID())->second));
						if (0 == tList.GetCount())
						{
							tList.SetSum(0);
						}
						else
						{
							tList.SetSum(tList.GetSum() - ((item.GetCount()*nCost.GetValue()) - (pProdCountMap.find(product.GetID())->second * nCost.GetValue())));
						}
						if (!tList.UpdateTransportList(globalVar, ormasDal, errorMessage))
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
						if (std::round((oldCount - item.GetCount()) * 1000) / 1000 != std::round(tList.GetCount() * 1000) / 1000)
							return false;
						if (std::round((oldSum - item.GetCount()*nCost.GetValue()) * 1000) / 1000 != std::round(tList.GetSum() * 1000) / 1000)
							return false;
						totalNewCount += tList.GetCount();
					}
				}
			}
		}
		else
		{
			errorMessage = "ERROR! Transport list is empty!";
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
		int debAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55010", errorMessage);
		int credAccID = caRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10742", errorMessage);
		if (0 == debAccID || 0 == credAccID)
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}

		if (!this->CreateEntry(globalVar, ormasDal, oID, debAccID, totalSum, credAccID, errorMessage))
		{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		return true;
	}

	bool Transport::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		Transport transport;
		transport.Clear();
		errorMessage.clear();
		transport.SetEmployeeID(eID);
		std::string filter = transport.GenerateFilter(ormasDal);
		std::vector<DataLayer::transportsViewCollection> transportVector = ormasDal.GetTransports(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == transportVector.size())
		{
			return false;
		}
		errorMessage = "Transport with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Transport::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Transport transport;
		transport.Clear();
		errorMessage.clear();
		transport.SetEmployeeID(employeeID);
		std::string filter = transport.GenerateFilter(ormasDal);
		std::vector<DataLayer::transportsViewCollection> transportVector = ormasDal.GetTransports(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == transportVector.size())
		{
			return false;
		}
		errorMessage = "Transport with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Transport::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Операция по приему и выдаче товара из транспортного средства"));
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
	bool Transport::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена выдачи товара из транспортного средства"));
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
		entry.SetDescription(wstring_to_utf8(L"Операция по приему и выдаче товара из транспортного средства"));
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

	std::string Transport::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}