#include "stdafx.h"
#include "StockTransferClass.h"
#include "StockTransferListClass.h"
#include "UserClass.h"
#include "StatusClass.h"
#include "StockClass.h"

namespace BusinessLayer
{
	StockTransfer::StockTransfer(DataLayer::stockTransferCollection rCollection)
	{
		id = std::get<0>(rCollection);
		employeeID = std::get<1>(rCollection);
		date = std::get<2>(rCollection);
		executionDate = std::get<3>(rCollection);
		stockEmployeeID = std::get<4>(rCollection);
		count = std::get<5>(rCollection);
		sum = std::get<6>(rCollection);
		statusID = std::get<7>(rCollection);
		currencyID = std::get<8>(rCollection);
	}

	int StockTransfer::GetID()
	{
		return id;
	}

	int StockTransfer::GetEmployeeID()
	{
		return employeeID;
	}

	std::string StockTransfer::GetDate()
	{
		return date;
	}

	std::string StockTransfer::GetExecutionDate()
	{
		return executionDate;
	}

	int StockTransfer::GetStockEmployeeID()
	{
		return stockEmployeeID;
	}

	double StockTransfer::GetCount()
	{
		return count;
	}

	double StockTransfer::GetSum()
	{
		return sum;
	}

	int StockTransfer::GetStatusID()
	{
		return statusID;
	}

	int StockTransfer::GetCurrencyID()
	{
		return currencyID;
	}

	void StockTransfer::SetID(int rID)
	{
		id = rID;
	}
	void StockTransfer::SetEmployeeID(int rEmployeeID)
	{
		employeeID = rEmployeeID;
	}
	void StockTransfer::SetDate(std::string rDate)
	{
		date = rDate;
	}
	void StockTransfer::SetExecutionDate(std::string rExecutionDate)
	{
		executionDate = rExecutionDate;
	}
	void StockTransfer::SetStockEmployeeID(int rStockEmployeeID)
	{
		stockEmployeeID = rStockEmployeeID;
	}

	void StockTransfer::SetCount(double rCount)
	{
		count = rCount;
	}

	void StockTransfer::SetSum(double rSum)
	{
		sum = rSum;
	}

	void StockTransfer::SetStatusID(int rStatusID)
	{
		statusID = rStatusID;
	}

	void StockTransfer::SetCurrencyID(int rCurrencyID)
	{
		currencyID = rCurrencyID;
	}

	bool StockTransfer::CreateStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string rDate, std::string rExecDate, 
		int seID, double rCount, double rSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, rDate, seID , rCount, rSum, cID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		employeeID = uID;
		date = rDate;
		executionDate = rExecDate;
		stockEmployeeID = seID;
		count = rCount;
		sum = rSum;
		statusID = sID;
		currencyID = cID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateStockTransfer(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
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

	bool StockTransfer::CreateStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateStockTransfer(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
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
	bool StockTransfer::DeleteStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		StockTransfer sTran;
		if (!sTran.GetStockTransferByID(globalVar, ormasDal, id, errorMessage))
		{
			return false;
		}
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (sTran.GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			errorMessage = "Cannot delete document with \"EXECUTED\" status!";
			return false;
		}
		if (sTran.GetStatusID() == statusMap.find("ERROR")->second)
		{
			errorMessage = "Cannot delete document with \"ERROR\" status!";
			return false;
		}
		if (ormasDal.DeleteStockTransfer(id, errorMessage))
		{
			if (ormasDal.DeleteListByStockTransferID(id, errorMessage))
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
	bool StockTransfer::UpdateStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string rDate, std::string rExecnDate,
		int eID, double rCount, double rSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetProductCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		employeeID = uID;
		date = rDate;
		executionDate = rExecnDate;
		stockEmployeeID = eID;
		count = rCount;
		sum = rSum;
		statusID = sID;
		currencyID = cID;
		prevSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		prevCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateStockTransfer(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
					{
						/*if (!CheckDocumentCorrectness(ormasDal))
						{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
						}*/
						//ormasDal.CommitTransaction(errorMessage);
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
					if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
					{
						/*if (!CheckDocumentCorrectness(ormasDal))
						{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
						}*/
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
							/*if (!CheckDocumentCorrectness(ormasDal))
							{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
							}*/
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
							/*if (!CheckDocumentCorrectness(ormasDal))
							{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
							}*/
							//ormasDal.CommitTransaction(errorMessage);
							return true;

						}
						else
						{
							//ormasDal.CommitTransaction(errorMessage);
							return false;
						}
					}
					return true;
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
					//ormasDal.CommitTransaction(errorMessage);
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
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;*/
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool StockTransfer::UpdateStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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
		if (0 != id && ormasDal.UpdateStockTransfer(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
					{
						/*if (!CheckDocumentCorrectness(ormasDal))
						{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
						}*/
						//ormasDal.CommitTransaction(errorMessage);
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
					if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, stockEmployeeID, errorMessage))
					{
						/*if (!CheckDocumentCorrectness(ormasDal))
						{
						errorMessage = "Document isn't correct. Check sum and count in list!";
						return false;
						}*/
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
							/*if (!CheckDocumentCorrectness(ormasDal))
							{
							errorMessage = "Document isn't correct. Check sum and count in list!";
							return false;
							}*/
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
							/*if (!CheckDocumentCorrectness(ormasDal))
							{
								errorMessage = "Document isn't correct. Check sum and count in list!";
								return false;
							}*/
							//ormasDal.CommitTransaction(errorMessage);
							return true;

						}
						else
						{
							//ormasDal.CommitTransaction(errorMessage);
							return false;
						}
					}
					return true;
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
					//ormasDal.CommitTransaction(errorMessage);
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
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;*/
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string StockTransfer::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || !date.empty() || !executionDate.empty() || 0 != stockEmployeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForStockTransfer(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	std::string StockTransfer::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForStockTransferForPeriod(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, fromDate, toDate);
		}
		return "";
	}

	bool StockTransfer::SimpleUpdateStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		
		if (0 != id && ormasDal.UpdateStockTransfer(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	

	bool StockTransfer::GetStockTransferByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage)
	{
		if (rID <= 0)
			return false;
		id = rID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferViewCollection> stockTransferVector = ormasDal.GetStockTransfer(errorMessage, filter);
		if (0 != stockTransferVector.size())
		{
			id = std::get<0>(stockTransferVector.at(0));
			date = std::get<1>(stockTransferVector.at(0));
			executionDate = std::get<2>(stockTransferVector.at(0));
			count = std::get<13>(stockTransferVector.at(0));
			sum = std::get<14>(stockTransferVector.at(0));
			stockEmployeeID = std::get<16>(stockTransferVector.at(0));
			employeeID = std::get<17>(stockTransferVector.at(0));
			statusID = std::get<18>(stockTransferVector.at(0));
			currencyID = std::get<19>(stockTransferVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find stock transfer with this id";
		}
		return false;
	}

	bool StockTransfer::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == stockEmployeeID && 0 == employeeID && 0 == statusID
			&& 0 == currencyID)
			return true;
		return false;
	}

	void StockTransfer::Clear()
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

	bool StockTransfer::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string rDate, int seID, double rCount, double rSum,
		int cID, std::string& errorMessage)
	{
		StockTransfer stockTransfer;
		stockTransfer.Clear();
		errorMessage.clear();
		stockTransfer.SetEmployeeID(eID);
		stockTransfer.SetDate(rDate);
		stockTransfer.SetStockEmployeeID(seID);
		stockTransfer.SetCount(rCount);
		stockTransfer.SetSum(rSum);
		stockTransfer.SetCurrencyID(cID);
		std::string filter = stockTransfer.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferViewCollection> stockTransferVector = ormasDal.GetStockTransfer(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == stockTransferVector.size())
		{
			return false;
		}
		errorMessage = "Stock transfer with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool StockTransfer::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		StockTransfer stockTransfer;
		stockTransfer.Clear();
		errorMessage.clear();
		stockTransfer.SetEmployeeID(employeeID);
		stockTransfer.SetDate(date);
		stockTransfer.SetStockEmployeeID(stockEmployeeID);
		stockTransfer.SetCount(count);
		stockTransfer.SetSum(sum);
		stockTransfer.SetCurrencyID(currencyID);
		std::string filter = stockTransfer.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferViewCollection> stockTransferVector = ormasDal.GetStockTransfer(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == stockTransferVector.size())
		{
			return false;
		}
		errorMessage = "Stock transfer with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool StockTransfer::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, int stockEmpID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByStockTransfer(globalVar, ormasDal, cpID, empID, stockEmpID, errorMessage);
	}

	bool StockTransfer::ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, int stockEmpID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByStockTransferReverse(globalVar, ormasDal, cpID, empID, stockEmpID, errorMessage);
	}

	bool StockTransfer::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByStockTransfer(globalVar, ormasDal, cpID, empID, stockEmpID, pProdCountMap, pSum, errorMessage);
	}

	double StockTransfer::GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		StockTransfer sTran;
		if (sTran.GetStockTransferByID(globalVar, ormasDal, cpID, errorMessage))
			return sTran.GetSum();
		return 0;
	}

	double StockTransfer::GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		StockTransfer sTran;
		if (sTran.GetStockTransferByID(globalVar, ormasDal, cpID, errorMessage))
			return sTran.GetCount();
		return 0;
	}

	int StockTransfer::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		StockTransfer sTran;
		if (sTran.GetStockTransferByID(globalVar, ormasDal, cID, errorMessage))
			return sTran.GetStatusID();
		return 0;
	}

	std::map<int, double> StockTransfer::GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		std::map<int, double> mapProdCount;
		StockTransferList rPList;
		rPList.SetStockTransferID(cpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> productListVector = ormasDal.GetStockTransferList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				mapProdCount.insert(std::make_pair(std::get<11>(item), std::get<7>(item)));
			}
		}
		return mapProdCount;
	}
	bool StockTransfer::CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal)
	{
		std::string errorMessage;
		StockTransferList rPList;
		double checkCount = 0;
		double checkSum = 0;
		rPList.SetStockTransferID(id);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::stockTransferListViewCollection> productListVector = ormasDal.GetStockTransferList(errorMessage, filter);

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