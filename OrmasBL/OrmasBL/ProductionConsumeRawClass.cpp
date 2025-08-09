#include "stdafx.h"
#include "ProductionConsumeRawClass.h"
#include "ProductionConsumeRawListClass.h"
#include "UserClass.h"
#include "StatusClass.h"
#include "StockClass.h"
#include "ProductClass.h"
#include "WarehouseEmployeeRelationClass.h"


namespace BusinessLayer
{
	ProductionConsumeRaw::ProductionConsumeRaw(DataLayer::productionConsumeRawsCollection cCollection)
	{
		id = std::get<0>(cCollection);
		employeeID = std::get<1>(cCollection);
		date = std::get<2>(cCollection);
		executionDate = std::get<3>(cCollection);
		stockEmployeeID = std::get<4>(cCollection);
		count = std::get<5>(cCollection);
		sum = std::get<6>(cCollection);
		statusID = std::get<7>(cCollection);
		currencyID = std::get<8>(cCollection);
	}

	int ProductionConsumeRaw::GetID()
	{
		return id;
	}

	int ProductionConsumeRaw::GetEmployeeID()
	{
		return employeeID;
	}

	std::string ProductionConsumeRaw::GetDate()
	{
		return date;
	}

	std::string ProductionConsumeRaw::GetExecutionDate()
	{
		return executionDate;
	}

	int ProductionConsumeRaw::GetStockEmployeeID()
	{
		return stockEmployeeID;
	}

	double ProductionConsumeRaw::GetCount()
	{
		return count;
	}

	double ProductionConsumeRaw::GetSum()
	{
		return sum;
	}

	int ProductionConsumeRaw::GetStatusID()
	{
		return statusID;
	}

	int ProductionConsumeRaw::GetCurrencyID()
	{
		return currencyID;
	}

	void ProductionConsumeRaw::SetID(int cID)
	{
		id = cID;
	}
	void ProductionConsumeRaw::SetEmployeeID(int cEmployeeID)
	{
		employeeID = cEmployeeID;
	}
	void ProductionConsumeRaw::SetDate(std::string cDate)
	{
		date = cDate;
	}
	void ProductionConsumeRaw::SetExecutionDate(std::string cExecutionDate)
	{
		executionDate = cExecutionDate;
	}
	void ProductionConsumeRaw::SetStockEmployeeID(int cStockEmployeeID)
	{
		stockEmployeeID = cStockEmployeeID;
	}

	void ProductionConsumeRaw::SetCount(double cCount)
	{
		count = cCount;
	}

	void ProductionConsumeRaw::SetSum(double cSum)
	{
		sum = cSum;
	}

	void ProductionConsumeRaw::SetStatusID(int cStatusID)
	{
		statusID = cStatusID;
	}

	void ProductionConsumeRaw::SetCurrencyID(int cCurrencyID)
	{
		currencyID = cCurrencyID;
	}

	bool ProductionConsumeRaw::CreateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string cpDate, std::string cpExecDate, 
		int seID, double cpCount, double cpSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, cpDate, seID ,cpCount, cpSum, cID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		employeeID = uID;
		date = cpDate;
		executionDate = cpExecDate;
		stockEmployeeID = seID;
		count = cpCount;
		sum = cpSum;
		statusID = sID;
		currencyID = cID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateProductionConsumeRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (!CheckDocumentCorrectness(ormasDal))
				{
					errorMessage = "Document isn't correct. Check sum and count in list!";
					return false;
				}
				if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
				{
					
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}

			}
			if (statusID == statusMap.find("RETURN")->second)
			{
				if (!CheckDocumentCorrectness(ormasDal))
				{
					errorMessage = "Document isn't correct. Check sum and count in list!";
					return false;
				}
				if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
				{
					
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}

			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool ProductionConsumeRaw::CreateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateProductionConsumeRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (!CheckDocumentCorrectness(ormasDal))
				{
					errorMessage = "Document isn't correct. Check sum and count in list!";
					return false;
				}
				if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
				{
					
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (statusID == statusMap.find("RETURN")->second)
			{
				if (!CheckDocumentCorrectness(ormasDal))
				{
					errorMessage = "Document isn't correct. Check sum and count in list!";
					return false;
				}
				if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
				{
					
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}

			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool ProductionConsumeRaw::DeleteProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		ProductionConsumeRaw cRaw;
		if (!cRaw.GetProductionConsumeRawByID(globalVar, ormasDal, id, errorMessage))
		{
			return false;
		}
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (cRaw.GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			errorMessage = "Cannot delete document with \"EXECUTED\" status!";
			return false;
		}
		if (cRaw.GetStatusID() == statusMap.find("ERROR")->second)
		{
			errorMessage = "Cannot delete document with \"ERROR\" status!";
			return false;
		}
		if (cRaw.GetStatusID() == statusMap.find("RETURN")->second)
		{
			errorMessage = "Cannot delete document with \"RETURN\" status!";
			return false;
		}
		if (ormasDal.DeleteProductionConsumeRaw(id, errorMessage))
		{
			if (ormasDal.DeleteListByProductionConsumeRawID(id, errorMessage))
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
	bool ProductionConsumeRaw::UpdateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string cpDate, std::string cpExecnDate,
		int eID, double cpCount, double cpSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetProductCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		employeeID = uID;
		date = cpDate;
		executionDate = cpExecnDate;
		stockEmployeeID = eID;
		count = cpCount;
		sum = cpSum;
		statusID = sID;
		currencyID = cID;
		prevSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		prevCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateProductionConsumeRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (!CheckDocumentCorrectness(ormasDal))
					{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
					}
					if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
					{
						
						return true;
					}
					else
					{
						//ormasDal.CommitTransaction(errorMessage);
						return false;
					}
				}
				else if (statusID == statusMap.find("RETURN")->second)
				{
					if (!CheckDocumentCorrectness(ormasDal))
					{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
					}
					if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
					{
						
						return true;
					}
					else
					{
						//ormasDal.CommitTransaction(errorMessage);
						return false;
					}
				}
				else
				{
					return true;
				}
			}
			else
			{
				if (statusID == statusMap.find("ERROR")->second)
				{
					if (previousStatusID == statusMap.find("EXECUTED")->second)
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
						{
							
							return true;
						}
						else
						{
							//ormasDal.CommitTransaction(errorMessage);
							return false;
						}
					}
					if (previousStatusID == statusMap.find("RETURN")->second)
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
						{
							
							return true;
						}
						else
						{
							//ormasDal.CommitTransaction(errorMessage);
							return false;
						}
					}

				}
				else
				{
					errorMessage = "Cannot update this document, only \"Error\" status is acceptable!";
					return false;
				}
			}
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool ProductionConsumeRaw::UpdateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetProductCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		prevSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		prevCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;		
		if (0 != id && ormasDal.UpdateProductionConsumeRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (!CheckDocumentCorrectness(ormasDal))
					{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
					}
					if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
					{
						
						return true;
					}
					else
					{
						//ormasDal.CommitTransaction(errorMessage);
						return false;
					}
				}
				else if (statusID == statusMap.find("RETURN")->second)
				{
					if (!CheckDocumentCorrectness(ormasDal))
					{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
					}
					if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
					{
					
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else
				{
					return true;
				}
			}
			else
			{
				if (statusID == statusMap.find("ERROR")->second)
				{
					if (previousStatusID == statusMap.find("EXECUTED")->second)
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
						{
							
							return true;
						}
						else
						{
							//ormasDal.CommitTransaction(errorMessage);
							return false;
						}
					}
					if (previousStatusID == statusMap.find("RETURN")->second)
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
						{
							
							return true;
						}
						else
						{
							//ormasDal.CommitTransaction(errorMessage);
							return false;
						}
					}
					
				}
				else
				{
					errorMessage = "Cannot update this document, only \"Error\" status is acceptable!";
					return false;
				}
			}
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool ProductionConsumeRaw::SimpleUpdateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateProductionConsumeRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	bool ProductionConsumeRaw::SimpleUpdateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string cpDate, std::string cpExecnDate,
		int eID, double cpCount, double cpSum, int sID, int cID, std::string& errorMessage)
	{
		employeeID = uID;
		date = cpDate;
		executionDate = cpExecnDate;
		stockEmployeeID = eID;
		count = cpCount;
		sum = cpSum;
		statusID = sID;
		currencyID = cID;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateProductionConsumeRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ProductionConsumeRaw::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || !date.empty() || !executionDate.empty() || 0 != stockEmployeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForProductionConsumeRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	std::string ProductionConsumeRaw::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{

		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForProductionConsumeRawForPeriod(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, fromDate, toDate);
		}
		return "";
	}

	bool ProductionConsumeRaw::GetProductionConsumeRawByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawsViewCollection> productionConsumeRawVector = ormasDal.GetProductionConsumeRaws(errorMessage, filter);
		if (0 != productionConsumeRawVector.size())
		{
			id = std::get<0>(productionConsumeRawVector.at(0));
			date = std::get<1>(productionConsumeRawVector.at(0));
			executionDate = std::get<2>(productionConsumeRawVector.at(0));
			count = std::get<13>(productionConsumeRawVector.at(0));
			sum = std::get<14>(productionConsumeRawVector.at(0));
			stockEmployeeID = std::get<16>(productionConsumeRawVector.at(0));
			employeeID = std::get<17>(productionConsumeRawVector.at(0));
			statusID = std::get<18>(productionConsumeRawVector.at(0));
			currencyID = std::get<19>(productionConsumeRawVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find production consume product with this id";
		}
		return false;
	}

	bool ProductionConsumeRaw::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == stockEmployeeID && 0 == employeeID && 0 == statusID
			&& 0 == currencyID)
			return true;
		return false;
	}

	void ProductionConsumeRaw::Clear()
	{
		id = 0;
		date.clear();
		executionDate.clear();
		count = 0;
		sum = 0;
		stockEmployeeID = 0;
		employeeID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ProductionConsumeRaw::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string cDate, int seID, double cCount, double cSum,
		int cID, std::string& errorMessage)
	{
		ProductionConsumeRaw productionConsumeRaw;
		productionConsumeRaw.Clear();
		errorMessage.clear();
		productionConsumeRaw.SetEmployeeID(eID);
		productionConsumeRaw.SetDate(cDate);
		productionConsumeRaw.SetStockEmployeeID(seID);
		productionConsumeRaw.SetCount(cCount);
		productionConsumeRaw.SetSum(cSum);
		productionConsumeRaw.SetCurrencyID(cID);
		std::string filter = productionConsumeRaw.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawsViewCollection> productionConsumeRawVector = ormasDal.GetProductionConsumeRaws(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionConsumeRawVector.size())
		{
			return false;
		}
		errorMessage = "Production consume raw with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductionConsumeRaw::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ProductionConsumeRaw productionConsumeRaw;
		productionConsumeRaw.Clear();
		errorMessage.clear();
		productionConsumeRaw.SetEmployeeID(employeeID);
		productionConsumeRaw.SetDate(date);
		productionConsumeRaw.SetStockEmployeeID(stockEmployeeID);
		productionConsumeRaw.SetCount(count);
		productionConsumeRaw.SetSum(sum);
		productionConsumeRaw.SetCurrencyID(currencyID);
		std::string filter = productionConsumeRaw.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawsViewCollection> productionConsumeRawVector = ormasDal.GetProductionConsumeRaws(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionConsumeRawVector.size())
		{
			return false;
		}
		errorMessage = "Production consume raw with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductionConsumeRaw::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int stockEmpID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByProdConsumeRaw(globalVar, ormasDal, crID, stockEmpID, errorMessage);
	}

	bool ProductionConsumeRaw::ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int stockEmpID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByProdConsumeRawReverse(globalVar, ormasDal, crID, stockEmpID, errorMessage);
	}

	bool ProductionConsumeRaw::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByProdConsumeRaw(globalVar, ormasDal, crID, stockEmpID, pProdCountMap, pSum, errorMessage);
	}

	double ProductionConsumeRaw::GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage)
	{
		ProductionConsumeRaw cRaw;
		if (cRaw.GetProductionConsumeRawByID(globalVar, ormasDal, crID, errorMessage))
			return cRaw.GetSum();
		return 0;
	}

	double ProductionConsumeRaw::GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage)
	{
		ProductionConsumeRaw cRaw;
		if (cRaw.GetProductionConsumeRawByID(globalVar, ormasDal, crID, errorMessage))
			return cRaw.GetCount();
		return 0;
	}

	int ProductionConsumeRaw::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		ProductionConsumeRaw cRaw;
		if (cRaw.GetProductionConsumeRawByID(globalVar, ormasDal, cID, errorMessage))
			return cRaw.GetStatusID();
		return 0;
	}

	std::map<int, double> ProductionConsumeRaw::GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		std::map<int, double> mapProdCount;
		ProductionConsumeRawList rPList;
		rPList.SetProductionConsumeRawID(cpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawListViewCollection> productListVector = ormasDal.GetProductionConsumeRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				mapProdCount.insert(std::make_pair(std::get<11>(item), std::get<7>(item)));
			}
		}
		return mapProdCount;
	}
	
	bool ProductionConsumeRaw::CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal)
	{
		std::string errorMessage;
		ProductionConsumeRawList rPList;
		ProductionConsumeRaw consume;
		WarehouseEmployeeRelation weRel;
		Stock stock;
		GlobalVariable gVar;
		double checkCount = 0;
		double checkSum = 0;
		double checkPriceSum = 0;
		rPList.SetProductionConsumeRawID(id);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawListViewCollection> productListVector = ormasDal.GetProductionConsumeRawList(errorMessage, filter);

		if (!consume.GetProductionConsumeRawByID(&gVar, ormasDal, id, errorMessage))
			return false;
		if (!weRel.GetWarehouseEmployeeByEmployeeID(&gVar, ormasDal, consume.GetStockEmployeeID(), errorMessage))
			return false;
		if (productListVector.size() > 0)
		{
			
			for each (auto item in productListVector)
			{
				stock.Clear();
				if (!stock.GetStockByProductAndWarehouseID(&gVar, ormasDal, std::get<11>(item), weRel.GetWarehouseID(), errorMessage))
					return false;
				checkPriceSum += std::round(stock.GetSum() / stock.GetCount() * 1000) / 1000 * std::get<7>(item);
				checkCount += std::get<7>(item);
				checkSum += std::get<8>(item);
			}
		}

		if (fabs(checkPriceSum - checkSum) > 0.1)
		{
			UpdatePriceToLastState(&gVar, ormasDal);

			checkCount = 0;
			checkSum = 0;
			checkPriceSum = 0;
			rPList.Clear();
			filter.clear();
			productListVector.clear();
			rPList.SetProductionConsumeRawID(id);
			std::string filter = rPList.GenerateFilter(ormasDal);
			std::vector<DataLayer::productionConsumeRawListViewCollection> productListVector = ormasDal.GetProductionConsumeRawList(errorMessage, filter);

			if (productListVector.size() > 0)
			{
				for each (auto item in productListVector)
				{
					stock.Clear();
					if (!stock.GetStockByProductAndWarehouseID(&gVar, ormasDal, std::get<11>(item), weRel.GetWarehouseID(), errorMessage))
						return false;
					checkPriceSum += std::round(stock.GetSum() / stock.GetCount() * 1000) / 1000 * std::get<7>(item);
					checkCount += std::get<7>(item);
					checkSum += std::get<8>(item);
				}
			}
		}
		consume.Clear();
		if (!consume.GetProductionConsumeRawByID(&gVar, ormasDal, id, errorMessage))
			return false;
		if (fabs(consume.GetSum() - checkSum) > 0.1 || fabs(consume.GetCount() - checkCount) > 0.1)
			return false;
		return true;
	}

	bool ProductionConsumeRaw::UpdatePriceToLastState(GlobalVariable* globalVar, DataLayer::OrmasDal& ormasDal)
	{
		ProductionConsumeRaw consume;
		std::string errorMessage;
		ProductionConsumeRawList rPList;
		ProductionConsumeRawList rUpdatePList;
		WarehouseEmployeeRelation weRel;
		Stock stock;
		double totalSum = 0;
		rPList.SetProductionConsumeRawID(id);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionConsumeRawListViewCollection> productListVector = ormasDal.GetProductionConsumeRawList(errorMessage, filter);

		if (productListVector.size() > 0)
		{
			if (!consume.GetProductionConsumeRawByID(globalVar, ormasDal, id, errorMessage))
				return false;
			if (!weRel.GetWarehouseEmployeeByEmployeeID(globalVar, ormasDal, consume.GetStockEmployeeID(), errorMessage))
				return false;

			for each (auto item in productListVector)
			{
				stock.Clear();
				if (!stock.GetStockByProductAndWarehouseID(globalVar, ormasDal, std::get<11>(item), weRel.GetWarehouseID(), errorMessage))
					return false;
				if (fabs(std::round(stock.GetSum() / stock.GetCount() * 1000) / 1000 * std::get<7>(item) -std::get<8>(item)) > 0.1)
				{
					totalSum += std::round(stock.GetSum() / stock.GetCount() * 1000) / 1000 * std::get<7>(item) -std::get<8>(item);
					rUpdatePList.Clear();
					if (!rUpdatePList.GetProductionConsumeRawListByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
						return false;
					rUpdatePList.SetSum(std::round(stock.GetSum() / stock.GetCount() * 1000) / 1000 * std::get<7>(item));
					if (!rUpdatePList.UpdateProductionConsumeRawList(globalVar, ormasDal, errorMessage))
						return false;
				}
			}
		}
		if (totalSum != 0)
		{
			if (!consume.GetProductionConsumeRawByID(globalVar, ormasDal, id, errorMessage))
				return false;
			double newSum = consume.GetSum() + totalSum;
			consume.SetSum(newSum);
			if (!consume.SimpleUpdateProductionConsumeRaw(globalVar, ormasDal, errorMessage))
				return false;
		}

		return true;
	}
}