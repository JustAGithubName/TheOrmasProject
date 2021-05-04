#include "stdafx.h"
#include "ConsumeOtherStocksClass.h"
#include "ConsumeOtherStocksListClass.h"
#include "UserClass.h"
#include "StatusClass.h"
#include "LowValueStockClass.h"


namespace BusinessLayer
{
	ConsumeOtherStocks::ConsumeOtherStocks(DataLayer::consumeOtherStocksCollection cCollection)
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

	int ConsumeOtherStocks::GetID()
	{
		return id;
	}

	int ConsumeOtherStocks::GetEmployeeID()
	{
		return employeeID;
	}

	std::string ConsumeOtherStocks::GetDate()
	{
		return date;
	}

	std::string ConsumeOtherStocks::GetExecutionDate()
	{
		return executionDate;
	}

	int ConsumeOtherStocks::GetStockEmployeeID()
	{
		return stockEmployeeID;
	}

	double ConsumeOtherStocks::GetCount()
	{
		return count;
	}

	double ConsumeOtherStocks::GetSum()
	{
		return sum;
	}

	int ConsumeOtherStocks::GetStatusID()
	{
		return statusID;
	}

	int ConsumeOtherStocks::GetCurrencyID()
	{
		return currencyID;
	}

	void ConsumeOtherStocks::SetID(int cID)
	{
		id = cID;
	}
	void ConsumeOtherStocks::SetEmployeeID(int cEmployeeID)
	{
		employeeID = cEmployeeID;
	}
	void ConsumeOtherStocks::SetDate(std::string cDate)
	{
		date = cDate;
	}
	void ConsumeOtherStocks::SetExecutionDate(std::string cExecutionDate)
	{
		executionDate = cExecutionDate;
	}
	void ConsumeOtherStocks::SetStockEmployeeID(int cStockEmployeeID)
	{
		stockEmployeeID = cStockEmployeeID;
	}

	void ConsumeOtherStocks::SetCount(double cCount)
	{
		count = cCount;
	}

	void ConsumeOtherStocks::SetSum(double cSum)
	{
		sum = cSum;
	}

	void ConsumeOtherStocks::SetStatusID(int cStatusID)
	{
		statusID = cStatusID;
	}

	void ConsumeOtherStocks::SetCurrencyID(int cCurrencyID)
	{
		currencyID = cCurrencyID;
	}

	bool ConsumeOtherStocks::CreateConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string cpDate, std::string cpExecDate,
		int seID, double cpCount, double cpSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, cpDate, seID, cpCount, cpSum, cID, errorMessage))
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
		globalVar->currentOperationID = id;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateConsumeOtherStocks(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
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
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (statusID == statusMap.find("RETURN")->second)
			{
				if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
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

	bool ConsumeOtherStocks::CreateConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateConsumeOtherStocks(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
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
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			if (statusID == statusMap.find("RETURN")->second)
			{
				if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
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
	bool ConsumeOtherStocks::DeleteConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		ConsumeOtherStocks cOtherStocks;
		if (!cOtherStocks.GetConsumeOtherStocksByID(globalVar, ormasDal, id, errorMessage))
		{
			return false;
		}
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (cOtherStocks.GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			errorMessage = "Cannot delete document with \"EXECUTED\" status!";
			return false;
		}
		if (cOtherStocks.GetStatusID() == statusMap.find("ERROR")->second)
		{
			errorMessage = "Cannot delete document with \"ERROR\" status!";
			return false;
		}
		if (cOtherStocks.GetStatusID() == statusMap.find("RETURN")->second)
		{
			errorMessage = "Cannot delete document with \"RETURN\" status!";
			return false;
		}
		if (ormasDal.DeleteConsumeOtherStocks(id, errorMessage))
		{
			if (ormasDal.DeleteListByConsumeOtherStocksID(id, errorMessage))
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
	bool ConsumeOtherStocks::UpdateConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string cpDate, std::string cpExecnDate,
		int eID, double cpCount, double cpSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetOtherStocksCount(globalVar, ormasDal, id, errorMessage);
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
		if (0 != id && ormasDal.UpdateConsumeOtherStocks(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						//ormasDal.CommitTransaction(errorMessage);
						return false;
					}
				}
				if (statusID == statusMap.find("RETURN")->second)
				{
					if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						//ormasDal.CommitTransaction(errorMessage);
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
						if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
						{
							if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}
							//ormasDal.CommitTransaction(errorMessage);
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
						if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
						{
							if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}
							//ormasDal.CommitTransaction(errorMessage);
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
			if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
			{
			return true;
			}
			else
			{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
			}
			}
			if (statusID == statusMap.find("EXECUTED")->second && previousStatusID == statusMap.find("EXECUTED")->second)
			{
			if (count != prevCount || sum != prevSum)
			{
			if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, prodCountMap, prevSum, errorMessage))
			{
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
			//ormasDal.CommitTransaction(errorMessage);
			return true;
			}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;
			*/
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool ConsumeOtherStocks::UpdateConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetOtherStocksCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		prevSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		prevCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateConsumeOtherStocks(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						//ormasDal.CommitTransaction(errorMessage);
						return false;
					}
				}
				else if (statusID == statusMap.find("RETURN")->second)
				{
					if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
					{
						if (!CheckDocumentCorrectness(ormasDal))
						{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
						}
						//ormasDal.CommitTransaction(errorMessage);
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
						if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
						{
							if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}
							//ormasDal.CommitTransaction(errorMessage);
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
						if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
						{
							if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}
							//ormasDal.CommitTransaction(errorMessage);
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
			if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
			{
			return true;
			}
			else
			{
			//ormasDal.CancelTransaction(errorMessage);
			return false;
			}
			}
			if (statusID == statusMap.find("EXECUTED")->second && previousStatusID == statusMap.find("EXECUTED")->second)
			{
			if (count != prevCount || sum != prevSum)
			{
			if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, prodCountMap, prevSum, errorMessage))
			{
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
			//ormasDal.CommitTransaction(errorMessage);
			return true;
			}
			}*/
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

	std::string ConsumeOtherStocks::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || !date.empty() || !executionDate.empty() || 0 != stockEmployeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForConsumeOtherStocks(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	std::string ConsumeOtherStocks::GenerateINFilterForStockEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> sEmpIDList)
	{
		if (sEmpIDList.size()>0)
		{
			return ormasDal.GetINFilterForStockEmployeeID(sEmpIDList);
		}
		return "";
	}

	std::string ConsumeOtherStocks::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForConsumeOtherStocksForPeriod(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, fromDate, toDate);
		}
		return "";
	}

	bool ConsumeOtherStocks::GetConsumeOtherStocksByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksViewCollection> consumeOtherStocksVector = ormasDal.GetConsumeOtherStocks(errorMessage, filter);
		if (0 != consumeOtherStocksVector.size())
		{
			id = std::get<0>(consumeOtherStocksVector.at(0));
			date = std::get<1>(consumeOtherStocksVector.at(0));
			executionDate = std::get<2>(consumeOtherStocksVector.at(0));
			count = std::get<13>(consumeOtherStocksVector.at(0));
			sum = std::get<14>(consumeOtherStocksVector.at(0));
			stockEmployeeID = std::get<16>(consumeOtherStocksVector.at(0));
			employeeID = std::get<17>(consumeOtherStocksVector.at(0));
			statusID = std::get<18>(consumeOtherStocksVector.at(0));
			currencyID = std::get<19>(consumeOtherStocksVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find consume other stocks with this id";
		}
		return false;
	}

	bool ConsumeOtherStocks::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == stockEmployeeID && 0 == employeeID && 0 == statusID
			&& 0 == currencyID)
			return true;
		return false;
	}

	void ConsumeOtherStocks::Clear()
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

	bool ConsumeOtherStocks::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string cDate, int seID, double cCount, double cSum,
		int cID, std::string& errorMessage)
	{
		ConsumeOtherStocks consumeOtherStocks;
		consumeOtherStocks.Clear();
		errorMessage.clear();
		consumeOtherStocks.SetEmployeeID(eID);
		consumeOtherStocks.SetDate(cDate);
		consumeOtherStocks.SetStockEmployeeID(seID);
		consumeOtherStocks.SetCount(cCount);
		consumeOtherStocks.SetSum(cSum);
		consumeOtherStocks.SetCurrencyID(cID);
		std::string filter = consumeOtherStocks.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksViewCollection> consumeOtherStocksVector = ormasDal.GetConsumeOtherStocks(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == consumeOtherStocksVector.size())
		{
			return false;
		}
		errorMessage = "Consume other stocks with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ConsumeOtherStocks::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ConsumeOtherStocks consumeOtherStocks;
		consumeOtherStocks.Clear();
		errorMessage.clear();
		consumeOtherStocks.SetEmployeeID(employeeID);
		consumeOtherStocks.SetDate(date);
		consumeOtherStocks.SetStockEmployeeID(stockEmployeeID);
		consumeOtherStocks.SetCount(count);
		consumeOtherStocks.SetSum(sum);
		consumeOtherStocks.SetCurrencyID(currencyID);
		std::string filter = consumeOtherStocks.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksViewCollection> consumeOtherStocksVector = ormasDal.GetConsumeOtherStocks(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == consumeOtherStocksVector.size())
		{
			return false;
		}
		errorMessage = "Consume other stocks with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ConsumeOtherStocks::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::string& errorMessage)
	{
		LowValueStock stock;
		return  true;//stock.ChangingByConsumeOtherStocks(globalVar, ormasDal, crID, empID, stockEmpID, errorMessage);
	}

	bool ConsumeOtherStocks::ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::string& errorMessage)
	{
		LowValueStock stock;
		return  true;//stock.ChangingByConsumeOtherStocksReverse(globalVar, ormasDal, crID, empID, stockEmpID, errorMessage);
	}

	bool ConsumeOtherStocks::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		LowValueStock stock;
		return true;// stock.ChangingByConsumeOtherStocks(globalVar, ormasDal, crID, empID, stockEmpID, pProdCountMap, pSum, errorMessage);
	}

	double ConsumeOtherStocks::GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage)
	{
		ConsumeOtherStocks cOtherStocks;
		if (cOtherStocks.GetConsumeOtherStocksByID(globalVar, ormasDal, crID, errorMessage))
			return cOtherStocks.GetSum();
		return 0;
	}

	double ConsumeOtherStocks::GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage)
	{
		ConsumeOtherStocks cOtherStocks;
		if (cOtherStocks.GetConsumeOtherStocksByID(globalVar, ormasDal, crID, errorMessage))
			return cOtherStocks.GetCount();
		return 0;
	}

	int ConsumeOtherStocks::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		ConsumeOtherStocks cOtherStocks;
		if (cOtherStocks.GetConsumeOtherStocksByID(globalVar, ormasDal, cID, errorMessage))
			return cOtherStocks.GetStatusID();
		return 0;
	}

	std::map<int, double> ConsumeOtherStocks::GetOtherStocksCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		std::map<int, double> mapOthStockCount;
		ConsumeOtherStocksList rPList;
		rPList.SetConsumeOtherStocksID(cpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksListViewCollection> othStListVector = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);
		if (othStListVector.size() > 0)
		{
			for each (auto item in othStListVector)
			{
				mapOthStockCount.insert(std::make_pair(std::get<11>(item), std::get<7>(item)));
			}
		}
		return mapOthStockCount;
	}

	bool ConsumeOtherStocks::CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal)
	{
		std::string errorMessage;
		ConsumeOtherStocksList rPList;
		double checkCount = 0;
		double checkSum = 0;
		rPList.SetConsumeOtherStocksID(id);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::consumeOtherStocksListViewCollection> productListVector = ormasDal.GetConsumeOtherStocksList(errorMessage, filter);

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