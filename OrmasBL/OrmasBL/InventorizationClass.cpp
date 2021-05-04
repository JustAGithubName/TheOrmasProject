#include "stdafx.h"
#include "InventorizationClass.h"
#include "UserClass.h"
#include "StatusClass.h"

namespace BusinessLayer
{
	Inventorization::Inventorization(DataLayer::inventorizationsCollection iCollection)
	{
		id = std::get<0>(iCollection);
		employeeID = std::get<1>(iCollection);
		date = std::get<2>(iCollection);
		executionDate = std::get<3>(iCollection);
		stockEmployeeID = std::get<4>(iCollection);
		count = std::get<5>(iCollection);
		sum = std::get<6>(iCollection);
		statusID = std::get<7>(iCollection);
		currencyID = std::get<8>(iCollection);
	}

	int Inventorization::GetID()
	{
		return id;
	}

	int Inventorization::GetEmployeeID()
	{
		return employeeID;
	}

	std::string Inventorization::GetDate()
	{
		return date;
	}

	std::string Inventorization::GetExecutionDate()
	{
		return executionDate;
	}

	int Inventorization::GetStockEmployeeID()
	{
		return stockEmployeeID;
	}

	double Inventorization::GetCount()
	{
		return count;
	}

	double Inventorization::GetSum()
	{
		return sum;
	}

	int Inventorization::GetStatusID()
	{
		return statusID;
	}

	int Inventorization::GetCurrencyID()
	{
		return currencyID;
	}

	void Inventorization::SetID(int iID)
	{
		id = iID;
	}
	void Inventorization::SetEmployeeID(int iEmployeeID)
	{
		employeeID = iEmployeeID;
	}
	void Inventorization::SetDate(std::string iDate)
	{
		date = iDate;
	}
	void Inventorization::SetExecutionDate(std::string iExecutionDate)
	{
		executionDate = iExecutionDate;
	}
	void Inventorization::SetStockEmployeeID(int iStockEmployeeID)
	{
		stockEmployeeID = iStockEmployeeID;
	}

	void Inventorization::SetCount(double iCount)
	{
		count = iCount;
	}

	void Inventorization::SetSum(double iSum)
	{
		sum = iSum;
	}

	void Inventorization::SetStatusID(int iStatusID)
	{
		statusID = iStatusID;
	}

	void Inventorization::SetCurrencyID(int iCurrencyID)
	{
		currencyID = iCurrencyID;
	}

	bool Inventorization::CreateInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string iDate, std::string iExecDate, 
		int seID, double iCount, double iSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, iDate, seID ,iCount, iSum, cID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		employeeID = uID;
		date = iDate;
		executionDate = iExecDate;
		stockEmployeeID = seID;
		count = iCount;
		sum = iSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.CreateInventorization(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	bool Inventorization::CreateInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (0 != id && ormasDal.CreateInventorization(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Inventorization::DeleteInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeleteInventorization(id, errorMessage))
		{
			if (ormasDal.DeleteListByInventorizationID(id, errorMessage))
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
	bool Inventorization::UpdateInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string iDate, std::string iExecnDate,
		int eID, double iCount, double iSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		employeeID = uID;
		date = iDate;
		executionDate = iExecnDate;
		stockEmployeeID = eID;
		count = iCount;
		sum = iSum;
		statusID = sID;
		currencyID = cID;
		if (0 != id && ormasDal.UpdateInventorization(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Inventorization::UpdateInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (0 != id && ormasDal.UpdateInventorization(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Inventorization::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || !date.empty() || !executionDate.empty() || 0 != stockEmployeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForInventorization(id, employeeID, date, executionDate, stockEmployeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool Inventorization::GetInventorizationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage)
	{
		if (iID <= 0)
			return false;
		id = iID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::inventorizationsViewCollection> inventorizationVector = ormasDal.GetInventorizations(errorMessage, filter);
		if (0 != inventorizationVector.size())
		{
			id = std::get<0>(inventorizationVector.at(0));
			date = std::get<1>(inventorizationVector.at(0));
			executionDate = std::get<2>(inventorizationVector.at(0));
			count = std::get<13>(inventorizationVector.at(0));
			sum = std::get<14>(inventorizationVector.at(0));
			stockEmployeeID = std::get<16>(inventorizationVector.at(0));
			employeeID = std::get<17>(inventorizationVector.at(0));
			statusID = std::get<18>(inventorizationVector.at(0));
			currencyID = std::get<19>(inventorizationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find inventorization with this id";
		}
		return false;
	}

	bool Inventorization::IsEmpty()
	{
		if (0 == id && date == "" && executionDate == "" && 0 == count && 0 == sum && 0 == stockEmployeeID && 0 == employeeID && 0 == statusID
			&& 0 == currencyID)
			return false;
		return true;
	}

	void Inventorization::Clear()
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

	bool Inventorization::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string iDate, int seID, double iCount, double iSum,
		int cID, std::string& errorMessage)
	{
		Inventorization inventorization;
		inventorization.Clear();
		errorMessage.clear();
		inventorization.SetEmployeeID(eID);
		inventorization.SetDate(iDate);
		inventorization.SetStockEmployeeID(seID);
		inventorization.SetCount(iCount);
		inventorization.SetSum(iSum);
		inventorization.SetCurrencyID(cID);
		std::string filter = inventorization.GenerateFilter(ormasDal);
		std::vector<DataLayer::inventorizationsViewCollection> inventorizationVector = ormasDal.GetInventorizations(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == inventorizationVector.size())
		{
			return false;
		}
		errorMessage = "Inventorization with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Inventorization::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Inventorization inventorization;
		inventorization.Clear();
		errorMessage.clear();
		inventorization.SetEmployeeID(employeeID);
		inventorization.SetDate(date);
		inventorization.SetStockEmployeeID(stockEmployeeID);
		inventorization.SetCount(count);
		inventorization.SetSum(sum);
		inventorization.SetCurrencyID(currencyID);
		std::string filter = inventorization.GenerateFilter(ormasDal);
		std::vector<DataLayer::inventorizationsViewCollection> inventorizationVector = ormasDal.GetInventorizations(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == inventorizationVector.size())
		{
			return false;
		}
		errorMessage = "Inventorization with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

}