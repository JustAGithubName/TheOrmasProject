#include "stdafx.h"
#include "WriteOffClass.h"
#include "WriteOffListClass.h"
#include "StockClass.h"
#include "StatusClass.h"

namespace BusinessLayer
{
	WriteOff::WriteOff(DataLayer::writeOffsCollection wCollection)
	{
		id = std::get<0>(wCollection);
		clientID = std::get<1>(wCollection);
		date = std::get<2>(wCollection);
		executionDate = std::get<3>(wCollection);
		employeeID = std::get<4>(wCollection);
		count = std::get<5>(wCollection);
		sum = std::get<6>(wCollection);
		statusID = std::get<7>(wCollection);
		currencyID = std::get<8>(wCollection);
	}

	int WriteOff::GetID()
	{
		return id;
	}

	int WriteOff::GetClientID()
	{
		return clientID;
	}

	std::string WriteOff::GetDate()
	{
		return date;
	}

	std::string WriteOff::GetExecutionDate()
	{
		return executionDate;
	}

	int WriteOff::GetEmployeeID()
	{
		return employeeID;
	}

	double WriteOff::GetCount()
	{
		return count;
	}

	double WriteOff::GetSum()
	{
		return sum;
	}

	int WriteOff::GetStatusID()
	{
		return statusID;
	}

	int WriteOff::GetCurrencyID()
	{
		return currencyID;
	}

	void WriteOff::SetID(int wID)
	{
		id = wID;
	}
	void WriteOff::SetClientID(int wClientID)
	{
		clientID = wClientID;
	}
	void WriteOff::SetDate(std::string wDate)
	{
		date = wDate;
	}
	void WriteOff::SetExecutionDate(std::string wExecutionDate)
	{
		executionDate = wExecutionDate;
	}
	void WriteOff::SetEmployeeID(int wEmployeeID)
	{
		employeeID = wEmployeeID;
	}

	void WriteOff::SetCount(double wCount)
	{
		count = wCount;
	}

	void WriteOff::SetSum(double wSum)
	{
		sum = wSum;
	}

	void WriteOff::SetStatusID(int wStatusID)
	{
		statusID = wStatusID;
	}

	void WriteOff::SetCurrencyID(int wCurrencyID)
	{
		currencyID = wCurrencyID;
	}

	bool WriteOff::CreateWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string wDate, std::string wExecDate, int eID, double wCount, double wSum,
		int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, clID, wDate, wCount, wSum, cID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		clientID = clID;
		date = wDate;
		executionDate = wExecDate;
		employeeID = eID;
		count = wCount;
		sum = wSum;
		statusID = sID;
		currencyID = cID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateWriteOff(id, clientID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
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
				if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
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

	bool WriteOff::CreateWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateWriteOff(id, clientID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
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
				if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
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
	bool WriteOff::DeleteWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		WriteOff wOff;
		if (!wOff.GetWriteOffByID(globalVar, ormasDal, id, errorMessage))
		{
			return false;
		}
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (wOff.GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			errorMessage = "Cannot delete document with \"EXECUTED\" status!";
			return false;
		}
		if (wOff.GetStatusID() == statusMap.find("ERROR")->second)
		{
			errorMessage = "Cannot delete document with \"ERROR\" status!";
			return false;
		}
		if (wOff.GetStatusID() == statusMap.find("RETURN")->second)
		{
			errorMessage = "Cannot delete document with \"RETURN\" status!";
			return false;
		}
		if (ormasDal.DeleteWriteOff(id, errorMessage))
		{
			if (ormasDal.DeleteListByWriteOffID(id, errorMessage))
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
	bool WriteOff::UpdateWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string wDate, std::string wExecDate, int eID,
		double wCount, double wSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetProductCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		clientID = clID;
		date = wDate;
		executionDate = wExecDate;
		employeeID = eID;
		count = wCount;
		sum = wSum;
		statusID = sID;
		currencyID = cID;
		prevSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		prevCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateWriteOff(id, clientID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
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
					if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
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
						if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
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
						if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
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
				if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
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
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, prodCountMap, prevSum, errorMessage))
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
	bool WriteOff::UpdateWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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
		if (0 != id && ormasDal.UpdateWriteOff(id, clientID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
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
					if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
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
						if (ChangesAtStockReverse(globalVar, ormasDal, id, employeeID, errorMessage))
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
						if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
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
				if (ChangesAtStock(globalVar, ormasDal, id, employeeID, errorMessage))
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
					if (ChangesAtStock(globalVar, ormasDal, id, employeeID, prodCountMap, prevSum, errorMessage))
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

	std::string WriteOff::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != clientID || !date.empty() || !executionDate.empty() || date.empty() || 0 != employeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForWriteOff(id, clientID, date, executionDate, employeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	std::string WriteOff::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForWriteOffForPeriod(id, clientID, date, executionDate, employeeID, count, sum, statusID, currencyID, fromDate, toDate);
		}
		return "";
	}

	bool WriteOff::GetWriteOffByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		id = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffsViewCollection> writeOffVector = ormasDal.GetWriteOffs(errorMessage, filter);
		if (0 != writeOffVector.size())
		{
			id = std::get<0>(writeOffVector.at(0));
			date = std::get<1>(writeOffVector.at(0));
			executionDate = std::get<2>(writeOffVector.at(0));
			count = std::get<13>(writeOffVector.at(0));
			sum = std::get<14>(writeOffVector.at(0));
			employeeID = std::get<16>(writeOffVector.at(0));
			clientID = std::get<17>(writeOffVector.at(0));
			statusID = std::get<18>(writeOffVector.at(0));
			currencyID = std::get<19>(writeOffVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find write-off with this id";
		}
		return false;
	}
	
	bool WriteOff::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == employeeID && 0 == clientID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void WriteOff::Clear()
	{
		id = 0;
		date.clear();
		executionDate.clear();
		count = 0;
		sum = 0;
		employeeID = 0;
		clientID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool WriteOff::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string wDate, double wCount, double wSum,
		int cID, std::string& errorMessage)
	{
		WriteOff writeOff;
		writeOff.Clear();
		errorMessage.clear();
		writeOff.SetClientID(clID);
		writeOff.SetDate(wDate);
		writeOff.SetCount(wCount);
		writeOff.SetSum(wSum);
		writeOff.SetCurrencyID(cID);
		std::string filter = writeOff.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffsViewCollection> writeOffVector = ormasDal.GetWriteOffs(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == writeOffVector.size())
		{
			return false;
		}
		errorMessage = "Write-off with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool WriteOff::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		WriteOff writeOff;
		writeOff.Clear();
		errorMessage.clear();
		writeOff.SetClientID(clientID);
		writeOff.SetDate(date);
		writeOff.SetCount(count);
		writeOff.SetSum(sum);
		writeOff.SetCurrencyID(currencyID);
		std::string filter = writeOff.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffsViewCollection> writeOffVector = ormasDal.GetWriteOffs(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == writeOffVector.size())
		{
			return false;
		}
		errorMessage = "Write-off with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool WriteOff::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int empID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByWriteOff(globalVar, ormasDal, wID, empID, errorMessage);
	}

	bool WriteOff::ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int empID, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByWriteOffReverse(globalVar, ormasDal, wID, empID, errorMessage);
	}

	bool WriteOff::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		Stock stock;
		return stock.ChangingByWriteOff(globalVar, ormasDal, wID, empID, pProdCountMap, pSum, errorMessage);
	}

	double WriteOff::GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		WriteOff wProduct;
		if (wProduct.GetWriteOffByID(globalVar, ormasDal, wID, errorMessage))
			return wProduct.GetSum();
		return 0;
	}

	double WriteOff::GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		WriteOff wProduct;
		if (wProduct.GetWriteOffByID(globalVar, ormasDal, wID, errorMessage))
			return wProduct.GetCount();
		return 0;
	}

	std::map<int, double> WriteOff::GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		std::map<int, double> mapProdCount;
		WriteOffList rPList;
		rPList.SetWriteOffID(cpID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffListViewCollection> productListVector = ormasDal.GetWriteOffList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				mapProdCount.insert(std::make_pair(std::get<11>(item), std::get<7>(item)));
			}
		}
		return mapProdCount;
	}

	int WriteOff::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage)
	{
		WriteOff wOff;
		wOff.GetWriteOffByID(globalVar, ormasDal, rID, errorMessage);
		if (errorMessage.empty())
			return wOff.GetStatusID();
		return 0;
	}
	bool WriteOff::CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal)
	{
		std::string errorMessage;
		WriteOffList rPList;
		double checkCount = 0;
		double checkSum = 0;
		rPList.SetWriteOffID(id);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::writeOffListViewCollection> productListVector = ormasDal.GetWriteOffList(errorMessage, filter);

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