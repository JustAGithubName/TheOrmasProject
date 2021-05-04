#include "stdafx.h"
#include "WriteOffRawClass.h"
#include "WriteOffRawListClass.h"
#include "UserClass.h"
#include "StatusClass.h"
#include "StockClass.h"

namespace BusinessLayer
{
	WriteOffRaw::WriteOffRaw(DataLayer::writeOffRawsCollection wCollection)
	{
		id = std::get<0>(wCollection);
		employeeID = std::get<1>(wCollection);
		date = std::get<2>(wCollection);
		executionDate = std::get<3>(wCollection);
		stockEmployeeID = std::get<4>(wCollection);
		count = std::get<5>(wCollection);
		sum = std::get<6>(wCollection);
		statusID = std::get<7>(wCollection);
		currencyID = std::get<8>(wCollection);
	}

	int WriteOffRaw::GetID()
	{
		return id;
	}

	int WriteOffRaw::GetEmployeeID()
	{
		return employeeID;
	}

	std::string WriteOffRaw::GetDate()
	{
		return date;
	}

	std::string WriteOffRaw::GetExecutionDate()
	{
		return executionDate;
	}

	int WriteOffRaw::GetStockEmployeeID()
	{
		return stockEmployeeID;
	}

	double WriteOffRaw::GetCount()
	{
		return count;
	}

	double WriteOffRaw::GetSum()
	{
		return sum;
	}

	int WriteOffRaw::GetStatusID()
	{
		return statusID;
	}

	int WriteOffRaw::GetCurrencyID()
	{
		return currencyID;
	}

	void WriteOffRaw::SetID(int wID)
	{
		id = wID;
	}
	void WriteOffRaw::SetEmployeeID(int wEmployeeID)
	{
		employeeID = wEmployeeID;
	}
	void WriteOffRaw::SetDate(std::string wDate)
	{
		date = wDate;
	}
	void WriteOffRaw::SetExecutionDate(std::string wExecutionDate)
	{
		executionDate = wExecutionDate;
	}
	void WriteOffRaw::SetStockEmployeeID(int wStockEmployeeID)
	{
		stockEmployeeID = wStockEmployeeID;
	}

	void WriteOffRaw::SetCount(double wCount)
	{
		count = wCount;
	}

	void WriteOffRaw::SetSum(double wSum)
	{
		sum = wSum;
	}

	void WriteOffRaw::SetStatusID(int wStatusID)
	{
		statusID = wStatusID;
	}

	void WriteOffRaw::SetCurrencyID(int wCurrencyID)
	{
		currencyID = wCurrencyID;
	}

	bool WriteOffRaw::CreateWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string wDate, std::string wExecutionDate,
		int seID, double wCount, double wSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, wDate, seID , wCount, wSum, cID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		employeeID = uID;
		date = wDate;
		executionDate = wExecutionDate;
		stockEmployeeID = seID;
		count = wCount;
		sum = wSum;
		statusID = sID;
		currencyID = cID;
		globalVar->currentOperationID = id;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateWriteOffRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
				if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool WriteOffRaw::CreateWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateWriteOffRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
				if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool WriteOffRaw::DeleteWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		WriteOffRaw wOffRaw;
		if (!wOffRaw.GetWriteOffRawByID(globalVar, ormasDal, id, errorMessage))
		{
			return false;
		}
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (wOffRaw.GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			errorMessage = "Cannot delete document with \"EXECUTED\" status!";
			return false;
		}
		if (wOffRaw.GetStatusID() == statusMap.find("ERROR")->second)
		{
			errorMessage = "Cannot delete document with \"ERROR\" status!";
			return false;
		}
		if (wOffRaw.GetStatusID() == statusMap.find("RETURN")->second)
		{
			errorMessage = "Cannot delete document with \"RETURN\" status!";
			return false;
		}
		if (ormasDal.DeleteWriteOffRaw(id, errorMessage))
		{
			if (ormasDal.DeleteListByWriteOffRawID(id, errorMessage))
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
	bool WriteOffRaw::UpdateWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string wDate, std::string wExecDate,
		int eID, double wCount, double wSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetProductCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		employeeID = uID;
		date = wDate;
		executionDate = wExecDate;
		stockEmployeeID = eID;
		count = wCount;
		sum = wSum;
		statusID = sID;
		currencyID = cID;
		prevSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		prevCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateWriteOffRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
				else if (statusID == statusMap.find("RETURN")->second)
				{
					if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
						if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
						if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
				if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
				{
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
				else
				{
					//ormasDal.CommitTransaction(errorMessage);
					return false;
				}
			}
			if (statusID == statusMap.find("EXECUTED")->second && previousStatusID == statusMap.find("EXECUTED")->second && prevSum != sum)
			{
				if (count != prevCount || sum != prevSum)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, prodCountMap, prevSum, errorMessage))
					{
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
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
			}
			//ormasDal.CancelTransaction(errorMessage);
			return true;*/
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool WriteOffRaw::UpdateWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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
		if (0 != id && ormasDal.UpdateWriteOffRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			if (statusID != statusMap.find("ERROR")->second &&
				previousStatusID != statusMap.find("EXECUTED")->second &&
				previousStatusID != statusMap.find("RETURN")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
					if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
						if (ChangesAtStockReverse(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
						if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
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
				if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, errorMessage))
				{
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
				else
				{
					//ormasDal.CommitTransaction(errorMessage);
					return false;
				}
			}
			if (statusID == statusMap.find("EXECUTED")->second && previousStatusID == statusMap.find("EXECUTED")->second && prevSum != sum)
			{
				if (count != prevCount || sum != prevSum)
				{
					if (ChangesAtStock(globalVar, ormasDal, id, stockEmployeeID, prodCountMap, prevSum, errorMessage))
					{
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
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
			}
			//ormasDal.CancelTransaction(errorMessage);
			return true;*/
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string WriteOffRaw::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || !date.empty() || !executionDate.empty() || 0 != stockEmployeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForWriteOffRaw(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	std::string WriteOffRaw::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForWriteOffRawForPeriod(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, fromDate, toDate);
		}
		return "";
	}

	bool WriteOffRaw::GetWriteOffRawByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawsViewCollection> writeOffRawVector = ormasDal.GetWriteOffRaws(errorMessage, filter);
		if (0 != writeOffRawVector.size())
		{
			id = std::get<0>(writeOffRawVector.at(0));
			date = std::get<1>(writeOffRawVector.at(0));
			count = std::get<13>(writeOffRawVector.at(0));
			sum = std::get<14>(writeOffRawVector.at(0));
			stockEmployeeID = std::get<16>(writeOffRawVector.at(0));
			employeeID = std::get<17>(writeOffRawVector.at(0));
			statusID = std::get<18>(writeOffRawVector.at(0));
			currencyID = std::get<19>(writeOffRawVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find write-off raw with this id";
		}
		return false;
	}

	bool WriteOffRaw::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == stockEmployeeID && 0 == employeeID && 0 == statusID
			&& 0 == currencyID)
			return true;
		return false;
	}

	void WriteOffRaw::Clear()
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

	bool WriteOffRaw::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string wDate, int seID, double wCount, double wSum,
		int cID, std::string& errorMessage)
	{
		WriteOffRaw writeOffRaw;
		writeOffRaw.Clear();
		errorMessage.clear();
		writeOffRaw.SetEmployeeID(eID);
		writeOffRaw.SetDate(wDate);
		writeOffRaw.SetStockEmployeeID(seID);
		writeOffRaw.SetCount(wCount);
		writeOffRaw.SetSum(wSum);
		writeOffRaw.SetCurrencyID(cID);
		std::string filter = writeOffRaw.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawsViewCollection> writeOffRawVector = ormasDal.GetWriteOffRaws(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == writeOffRawVector.size())
		{
			return false;
		}
		errorMessage = "Write-off raw with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool WriteOffRaw::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		WriteOffRaw writeOffRaw;
		writeOffRaw.Clear();
		errorMessage.clear();
		writeOffRaw.SetEmployeeID(employeeID);
		writeOffRaw.SetDate(date);
		writeOffRaw.SetStockEmployeeID(stockEmployeeID);
		writeOffRaw.SetCount(count);
		writeOffRaw.SetSum(sum);
		writeOffRaw.SetCurrencyID(currencyID);
		std::string filter = writeOffRaw.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawsViewCollection> writeOffRawVector = ormasDal.GetWriteOffRaws(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == writeOffRawVector.size())
		{
			return false;
		}
		errorMessage = "Write-off raw with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool WriteOffRaw::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByWriteOffRaw(globalVar, ormasDal, cpID, empID, errorMessage);
	}

	bool WriteOffRaw::ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByWriteOffRawReverse(globalVar, ormasDal, cpID, empID, errorMessage);
	}

	bool WriteOffRaw::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByWriteOffRaw(globalVar, ormasDal, cpID, empID, pProdCountMap, pSum, errorMessage);
	}

	double WriteOffRaw::GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		WriteOffRaw wProduct;
		if (wProduct.GetWriteOffRawByID(globalVar, ormasDal, cpID, errorMessage))
			return wProduct.GetSum();
		return 0;
	}

	double WriteOffRaw::GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		WriteOffRaw wProduct;
		if (wProduct.GetWriteOffRawByID(globalVar, ormasDal, cpID, errorMessage))
			return wProduct.GetCount();
		return 0;
	}

	std::map<int, double> WriteOffRaw::GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		std::map<int, double> mapProdCount;
		WriteOffRawList rPList;
		rPList.SetWriteOffRawID(cpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawListViewCollection> productListVector = ormasDal.GetWriteOffRawList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				mapProdCount.insert(std::make_pair(std::get<11>(item), std::get<7>(item)));
			}
		}
		return mapProdCount;
	}

	int WriteOffRaw::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage)
	{
		WriteOffRaw wOff;
		wOff.GetWriteOffRawByID(globalVar, ormasDal, rID, errorMessage);
		if (errorMessage.empty())
			return wOff.GetStatusID();
		return 0;
	}
	bool WriteOffRaw::CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal)
	{
		std::string errorMessage;
		WriteOffRawList rPList;
		double checkCount = 0;
		double checkSum = 0;
		rPList.SetWriteOffRawID(id);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffRawListViewCollection> productListVector = ormasDal.GetWriteOffRawList(errorMessage, filter);

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