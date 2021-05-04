#include "stdafx.h"
#include "OrderRawClass.h"
#include "OrderRawListClass.h"
#include "BalanceClass.h"
#include "UserClass.h"
#include "StockClass.h"
#include "StatusClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyEmployeeRelationClass.h"


namespace BusinessLayer
{
	OrderRaw::OrderRaw(DataLayer::orderRawsCollection oCollection)
	{
		id = std::get<0>(oCollection);
		purveyorID = std::get<1>(oCollection);
		date = std::get<2>(oCollection);
		executionDate = std::get<3>(oCollection);
		employeeID = std::get<4>(oCollection);
		count = std::get<5>(oCollection);
		sum = std::get<6>(oCollection);
		statusID = std::get<7>(oCollection);
		currencyID = std::get<8>(oCollection);
	}

	int OrderRaw::GetID()
	{
		return id;
	}

	int OrderRaw::GetPurveyorID()
	{
		return purveyorID;
	}

	std::string OrderRaw::GetDate()
	{
		return date;
	}

	std::string OrderRaw::GetExecutionDate()
	{
		return executionDate;
	}

	int OrderRaw::GetEmployeeID()
	{
		return employeeID;
	}

	double OrderRaw::GetCount()
	{
		return count;
	}

	double OrderRaw::GetSum()
	{
		return sum;
	}

	int OrderRaw::GetStatusID()
	{
		return statusID;
	}

	int OrderRaw::GetCurrencyID()
	{
		return currencyID;
	}

	void OrderRaw::SetID(int oID)
	{
		id = oID;
	}
	void OrderRaw::SetPurveyorID(int oPurveyorID)
	{
		purveyorID = oPurveyorID;
	}
	void OrderRaw::SetDate(std::string oDate)
	{
		date = oDate;
	}
	void OrderRaw::SetExecutionDate(std::string oExecutionDate)
	{
		executionDate = oExecutionDate;
	}
	void OrderRaw::SetEmployeeID(int oEmployeeID)
	{
		employeeID = oEmployeeID;
	}

	void OrderRaw::SetCount(double oCount)
	{
		count = oCount;
	}

	void OrderRaw::SetSum(double oSum)
	{
		sum = oSum;
	}

	void OrderRaw::SetStatusID(int oStatusID)
	{
		statusID = oStatusID;
	}

	void OrderRaw::SetCurrencyID(int oCurrencyID)
	{
		currencyID = oCurrencyID;
	}

	bool OrderRaw::CreateOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string oDate, std::string oExecDate, 
		int eID, double oCount, double oSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, oDate, eID ,oCount, oSum, cID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		purveyorID = pID;
		date = oDate;
		executionDate = oExecDate;
		employeeID = eID;
		count = oCount;
		sum = oSum;
		statusID = sID;
		currencyID = cID;
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateOrderRaw(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
				{
					if (!CheckDocumentCorrectness(ormasDal))
					{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
			if (statusID == statusMap.find("RETURN")->second)
			{
				if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
				{
					if (!CheckDocumentCorrectness(ormasDal))
					{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	bool OrderRaw::CreateOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateOrderRaw(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
				{
					if (!CheckDocumentCorrectness(ormasDal))
					{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
			if (statusID == statusMap.find("RETURN")->second)
			{
				if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
				{
					if (!CheckDocumentCorrectness(ormasDal))
					{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool OrderRaw::DeleteOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		OrderRaw oRaw;
		if (!oRaw.GetOrderRawByID(globalVar, ormasDal, id, errorMessage))
		{
			return false;
		}
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (oRaw.GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			errorMessage = "Cannot delete document with \"EXECUTED\" status!";
			return false;
		}
		if (oRaw.GetStatusID() == statusMap.find("ERROR")->second)
		{
			errorMessage = "Cannot delete document with \"ERROR\" status!";
			return false;
		}
		if (oRaw.GetStatusID() == statusMap.find("RETURN")->second)
		{
			errorMessage = "Cannot delete document with \"RETURN\" status!";
			return false;
		}
		if (ormasDal.DeleteOrderRaw(id, errorMessage))
		{
			if (ormasDal.DeleteListByOrderRawID(id, errorMessage))
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
	bool OrderRaw::UpdateOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string oDate, std::string oExecnDate,
		int eID, double oCount, double oSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetProductCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		purveyorID = pID;
		date = oDate;
		executionDate = oExecnDate;
		employeeID = eID;
		count = oCount;
		sum = oSum;
		statusID = sID;
		currencyID = cID;
		previousSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		previousCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateOrderRaw(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
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
					if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
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

						if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
						{
							if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}
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

						if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
						{
							if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}
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
			/*if (statusID == statusMap.find("EXECUTED")->second && previousStatusID != statusMap.find("EXECUTED")->second)
			{
				if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
				{
				
					return true;
				}
				else
				{
					
					return false;
				}
			}
			if (statusID == statusMap.find("EXECUTED")->second && previousStatusID != statusMap.find("EXECUTED")->second)
			{
				if (count != previousCount || sum != previousSum)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, prodCountMap, previousSum, errorMessage))
					{
						
						return true;
					}
					else
					{
						
						return false;
					}
				}
			}
			
			return true;
			*/
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		
		return false;
	}
	bool OrderRaw::UpdateOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetProductCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		previousSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		previousCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		globalVar->currentOperationID = id;			
		if (0 != id && ormasDal.UpdateOrderRaw(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
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
					if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
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

						if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
						{
							if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}
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

						if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
						{
							if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}
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
			/*if (statusID == statusMap.find("EXECUTED")->second && previousStatusID != statusMap.find("EXECUTED")->second)
			{
				if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
				{
					
					return true;
				}
				else
				{
				
					return false;
				}
			}
			if (statusID == statusMap.find("EXECUTED")->second && previousStatusID != statusMap.find("EXECUTED")->second)
			{
				if (count != previousCount || sum != previousSum)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, prodCountMap, previousSum, errorMessage))
					{
						
						return true;
					}
					else
					{
						
						return false;
					}
				}
			}*/
			
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		
		return false;
	}

	std::string OrderRaw::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != purveyorID || !date.empty() || !executionDate.empty() || 0 != employeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForOrderRaw(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	std::string OrderRaw::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForOrderRawForPeriod(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, fromDate, toDate);
		}
		return "";
	}

	bool OrderRaw::GetOrderRawByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawsViewCollection> orderRawVector = ormasDal.GetOrderRaws(errorMessage, filter);
		if (0 != orderRawVector.size())
		{
			id = std::get<0>(orderRawVector.at(0));
			date = std::get<1>(orderRawVector.at(0));
			executionDate = std::get<2>(orderRawVector.at(0));
			count = std::get<13>(orderRawVector.at(0));
			sum = std::get<14>(orderRawVector.at(0));
			employeeID = std::get<16>(orderRawVector.at(0));
			purveyorID = std::get<17>(orderRawVector.at(0));
			statusID = std::get<18>(orderRawVector.at(0));
			currencyID = std::get<19>(orderRawVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find order raw with this id";
		}
		return false;
	}

	bool OrderRaw::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == employeeID && 0 == purveyorID && 0 == statusID
			&& 0 == currencyID)
			return true;
		return false;
	}

	void OrderRaw::Clear()
	{
		id = 0;
		date.clear();
		executionDate.clear();
		count = 0;
		sum = 0;
		employeeID = 0;
		purveyorID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool OrderRaw::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string oDate, int eID, double oCount, double oSum,
		int cID, std::string& errorMessage)
	{
		OrderRaw orderRaw;
		orderRaw.Clear();
		errorMessage.clear();
		orderRaw.SetPurveyorID(pID);
		orderRaw.SetDate(oDate);
		orderRaw.SetEmployeeID(eID);
		orderRaw.SetCount(oCount);
		orderRaw.SetSum(oSum);
		orderRaw.SetCurrencyID(cID);
		std::string filter = orderRaw.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawsViewCollection> orderRawVector = ormasDal.GetOrderRaws(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == orderRawVector.size())
		{
			return false;
		}
		errorMessage = "Order raw with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool OrderRaw::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		OrderRaw orderRaw;
		orderRaw.Clear();
		errorMessage.clear();
		orderRaw.SetPurveyorID(purveyorID);
		orderRaw.SetDate(date);
		orderRaw.SetEmployeeID(employeeID);
		orderRaw.SetCount(count);
		orderRaw.SetSum(sum);
		orderRaw.SetCurrencyID(currencyID);
		std::string filter = orderRaw.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawsViewCollection> orderRawVector = ormasDal.GetOrderRaws(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == orderRawVector.size())
		{
			return false;
		}
		errorMessage = "Order raw with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	double OrderRaw::GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		OrderRaw orderRaw;
		if (orderRaw.GetOrderRawByID(globalVar, ormasDal, oID, errorMessage))
			return orderRaw.GetSum();
		return 0;
	}

	int OrderRaw::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		OrderRaw orderRaw;
		if (orderRaw.GetOrderRawByID(globalVar, ormasDal, oID, errorMessage))
			return orderRaw.GetStatusID();
		return 0;
	}

	bool OrderRaw::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByOrderRaw(globalVar, ormasDal, cpID, empID, errorMessage);
	}

	bool OrderRaw::ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByOrderRawReverse(globalVar, ormasDal, cpID, empID, errorMessage);
	}

	bool OrderRaw::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByOrderRaw(globalVar, ormasDal, cpID, empID, pProdCountMap, pSum, errorMessage);
	}

	double OrderRaw::GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		OrderRaw rRaw;
		if (rRaw.GetOrderRawByID(globalVar, ormasDal, cpID, errorMessage))
			return rRaw.GetCount();
		return 0;
	}

	std::map<int, double> OrderRaw::GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, std::string& errorMessage)
	{
		std::map<int, double> mapProdCount;
		OrderRawList rPList;
		rPList.SetOrderRawID(orID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> productListVector = ormasDal.GetOrderRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				mapProdCount.insert(std::make_pair(std::get<11>(item), std::get<7>(item)));
			}
		}
		return mapProdCount;
	}
	bool OrderRaw::CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal)
	{
		std::string errorMessage;
		OrderRawList rPList;
		double checkCount = 0;
		double checkSum = 0;
		rPList.SetOrderRawID(id);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::orderRawListViewCollection> productListVector = ormasDal.GetOrderRawList(errorMessage, filter);

		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				checkCount += std::get<7>(item);
				checkSum += std::get<8>(item);
			}
		}

		if (std::round(sum * 10) / 10 != std::round(checkSum * 10) / 10
			|| std::round(count * 10) / 10 != std::round(checkCount * 10) / 10)
			return false;
		return true;
	}
}