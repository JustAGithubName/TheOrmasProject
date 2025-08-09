#include "stdafx.h"
#include "ReceiptOtherStocksClass.h"
#include "ReceiptOtherStocksListClass.h"
#include "BalanceClass.h"
#include "UserClass.h"
#include "LowValueStockClass.h"
#include "StatusClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyEmployeeRelationClass.h"


namespace BusinessLayer
{
	ReceiptOtherStocks::ReceiptOtherStocks(DataLayer::receiptOtherStocksCollection oCollection)
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

	int ReceiptOtherStocks::GetID()
	{
		return id;
	}

	int ReceiptOtherStocks::GetPurveyorID()
	{
		return purveyorID;
	}

	std::string ReceiptOtherStocks::GetDate()
	{
		return date;
	}

	std::string ReceiptOtherStocks::GetExecutionDate()
	{
		return executionDate;
	}

	int ReceiptOtherStocks::GetEmployeeID()
	{
		return employeeID;
	}

	double ReceiptOtherStocks::GetCount()
	{
		return count;
	}

	double ReceiptOtherStocks::GetSum()
	{
		return sum;
	}

	int ReceiptOtherStocks::GetStatusID()
	{
		return statusID;
	}

	int ReceiptOtherStocks::GetCurrencyID()
	{
		return currencyID;
	}

	void ReceiptOtherStocks::SetID(int oID)
	{
		id = oID;
	}
	void ReceiptOtherStocks::SetPurveyorID(int oPurveyorID)
	{
		purveyorID = oPurveyorID;
	}
	void ReceiptOtherStocks::SetDate(std::string oDate)
	{
		date = oDate;
	}
	void ReceiptOtherStocks::SetExecutionDate(std::string oExecutionDate)
	{
		executionDate = oExecutionDate;
	}
	void ReceiptOtherStocks::SetEmployeeID(int oEmployeeID)
	{
		employeeID = oEmployeeID;
	}

	void ReceiptOtherStocks::SetCount(double oCount)
	{
		count = oCount;
	}

	void ReceiptOtherStocks::SetSum(double oSum)
	{
		sum = oSum;
	}

	void ReceiptOtherStocks::SetStatusID(int oStatusID)
	{
		statusID = oStatusID;
	}

	void ReceiptOtherStocks::SetCurrencyID(int oCurrencyID)
	{
		currencyID = oCurrencyID;
	}

	bool ReceiptOtherStocks::CreateReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string oDate, std::string oExecDate,
		int eID, double oCount, double oSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, oDate, eID, oCount, oSum, cID, errorMessage))
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
		if (0 != id && ormasDal.CreateReceiptOtherStocks(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
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

	bool ReceiptOtherStocks::CreateReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateReceiptOtherStocks(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
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
	bool ReceiptOtherStocks::DeleteReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		ReceiptOtherStocks oRaw;
		if (!oRaw.GetReceiptOtherStocksByID(globalVar, ormasDal, id, errorMessage))
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
		if (ormasDal.DeleteReceiptOtherStocks(id, errorMessage))
		{
			if (ormasDal.DeleteListByReceiptOtherStocksID(id, errorMessage))
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
	bool ReceiptOtherStocks::UpdateReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string oDate, std::string oExecnDate,
		int eID, double oCount, double oSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetOtherStocksCount(globalVar, ormasDal, id, errorMessage);
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
		if (0 != id && ormasDal.UpdateReceiptOtherStocks(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
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
	bool ReceiptOtherStocks::UpdateReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		std::map<int, double> prodCountMap = GetOtherStocksCount(globalVar, ormasDal, id, errorMessage);
		if (0 == prodCountMap.size())
			return false;
		previousSum = GetCurrentSum(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		previousCount = GetCurrentCount(globalVar, ormasDal, id, errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateReceiptOtherStocks(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, errorMessage))
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

	std::string ReceiptOtherStocks::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != purveyorID || !date.empty() || !executionDate.empty() || 0 != employeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForReceiptOtherStocks(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	std::string ReceiptOtherStocks::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForReceiptOtherStocksForPeriod(id, purveyorID, date, executionDate, employeeID, count, sum, statusID, currencyID, fromDate, toDate);
		}
		return "";
	}

	bool ReceiptOtherStocks::GetReceiptOtherStocksByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksViewCollection> receiptOtherStocksVector = ormasDal.GetReceiptOtherStocks(errorMessage, filter);
		if (0 != receiptOtherStocksVector.size())
		{
			id = std::get<0>(receiptOtherStocksVector.at(0));
			date = std::get<1>(receiptOtherStocksVector.at(0));
			executionDate = std::get<2>(receiptOtherStocksVector.at(0));
			count = std::get<13>(receiptOtherStocksVector.at(0));
			sum = std::get<14>(receiptOtherStocksVector.at(0));
			employeeID = std::get<16>(receiptOtherStocksVector.at(0));
			purveyorID = std::get<17>(receiptOtherStocksVector.at(0));
			statusID = std::get<18>(receiptOtherStocksVector.at(0));
			currencyID = std::get<19>(receiptOtherStocksVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find receipt other stocks with this id";
		}
		return false;
	}

	bool ReceiptOtherStocks::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == employeeID && 0 == purveyorID && 0 == statusID
			&& 0 == currencyID)
			return true;
		return false;
	}

	void ReceiptOtherStocks::Clear()
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

	bool ReceiptOtherStocks::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string oDate, int eID, double oCount, double oSum,
		int cID, std::string& errorMessage)
	{
		ReceiptOtherStocks receiptOtherStocks;
		receiptOtherStocks.Clear();
		errorMessage.clear();
		receiptOtherStocks.SetPurveyorID(pID);
		receiptOtherStocks.SetDate(oDate);
		receiptOtherStocks.SetEmployeeID(eID);
		receiptOtherStocks.SetCount(oCount);
		receiptOtherStocks.SetSum(oSum);
		receiptOtherStocks.SetCurrencyID(cID);
		std::string filter = receiptOtherStocks.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksViewCollection> receiptOtherStocksVector = ormasDal.GetReceiptOtherStocks(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == receiptOtherStocksVector.size())
		{
			return false;
		}
		errorMessage = "Receipt other stocks with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ReceiptOtherStocks::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ReceiptOtherStocks receiptOtherStocks;
		receiptOtherStocks.Clear();
		errorMessage.clear();
		receiptOtherStocks.SetPurveyorID(purveyorID);
		receiptOtherStocks.SetDate(date);
		receiptOtherStocks.SetEmployeeID(employeeID);
		receiptOtherStocks.SetCount(count);
		receiptOtherStocks.SetSum(sum);
		receiptOtherStocks.SetCurrencyID(currencyID);
		std::string filter = receiptOtherStocks.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksViewCollection> receiptOtherStocksVector = ormasDal.GetReceiptOtherStocks(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == receiptOtherStocksVector.size())
		{
			return false;
		}
		errorMessage = "Receipt other stocks with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	double ReceiptOtherStocks::GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		ReceiptOtherStocks ReceiptOtherStocks;
		if (ReceiptOtherStocks.GetReceiptOtherStocksByID(globalVar, ormasDal, oID, errorMessage))
			return ReceiptOtherStocks.GetSum();
		return 0;
	}

	int ReceiptOtherStocks::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		ReceiptOtherStocks ReceiptOtherStocks;
		if (ReceiptOtherStocks.GetReceiptOtherStocksByID(globalVar, ormasDal, oID, errorMessage))
			return ReceiptOtherStocks.GetStatusID();
		return 0;
	}

	bool ReceiptOtherStocks::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::string& errorMessage)
	{
		LowValueStock stock;
		return stock.ChangingByReceiptOtherStocks(globalVar, ormasDal, cpID, empID, errorMessage);
	}

	bool ReceiptOtherStocks::ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::string& errorMessage)
	{
		LowValueStock stock;
		return stock.ChangingByReceiptOtherStocksReverse(globalVar, ormasDal, cpID, empID, errorMessage);
	}

	bool ReceiptOtherStocks::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage)
	{
		LowValueStock stock;
		return stock.ChangingByReceiptOtherStocks(globalVar, ormasDal, cpID, empID, pProdCountMap, pSum, errorMessage);
	}

	double ReceiptOtherStocks::GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage)
	{
		ReceiptOtherStocks rRaw;
		if (rRaw.GetReceiptOtherStocksByID(globalVar, ormasDal, cpID, errorMessage))
			return rRaw.GetCount();
		return 0;
	}

	std::map<int, double> ReceiptOtherStocks::GetOtherStocksCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, std::string& errorMessage)
	{
		std::map<int, double> mapOthSCount;
		ReceiptOtherStocksList rPList;
		rPList.SetReceiptOtherStocksID(orID);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksListViewCollection> productListVector = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);
		if (productListVector.size() > 0)
		{
			for each (auto item in productListVector)
			{
				mapOthSCount.insert(std::make_pair(std::get<11>(item), std::get<7>(item)));
			}
		}
		return mapOthSCount;
	}
	bool ReceiptOtherStocks::CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal)
	{
		std::string errorMessage;
		ReceiptOtherStocksList rPList;
		double checkCount = 0;
		double checkSum = 0;
		rPList.SetReceiptOtherStocksID(id);
		std::string filter = rPList.GenerateFilter(ormasDal);
		std::vector<DataLayer::receiptOtherStocksListViewCollection> othSListVector = ormasDal.GetReceiptOtherStocksList(errorMessage, filter);

		if (othSListVector.size() > 0)
		{
			for each (auto item in othSListVector)
			{
				checkCount += std::get<7>(item);
				checkSum += std::get<8>(item);
			}
		}

		if (fabs(sum - checkSum) > 0.01 || fabs(count - checkCount) > 0.01)
			return false;
		return true;
	}
}