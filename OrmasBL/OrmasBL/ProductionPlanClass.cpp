#include "stdafx.h"
#include "ProductionPlanClass.h"
#include "UserClass.h"
#include "StatusClass.h"

namespace BusinessLayer
{
	ProductionPlan::ProductionPlan(DataLayer::productionPlanCollection pCollection)
	{
		id = std::get<0>(pCollection);
		date = std::get<1>(pCollection);
		employeeID = std::get<2>(pCollection);
		count = std::get<3>(pCollection);
		sum = std::get<4>(pCollection);
		statusID = std::get<5>(pCollection);
		currencyID = std::get<6>(pCollection);
	}

	int ProductionPlan::GetID()
	{
		return id;
	}

	std::string ProductionPlan::GetDate()
	{
		return date;
	}

	int ProductionPlan::GetEmployeeID()
	{
		return employeeID;
	}

	double ProductionPlan::GetCount()
	{
		return count;
	}

	double ProductionPlan::GetSum()
	{
		return sum;
	}

	int ProductionPlan::GetStatusID()
	{
		return statusID;
	}

	int ProductionPlan::GetCurrencyID()
	{
		return currencyID;
	}

	void ProductionPlan::SetID(int pID)
	{
		id = pID;
	}
	void ProductionPlan::SetDate(std::string pDate)
	{
		date = pDate;
	}
	void ProductionPlan::SetEmployeeID(int pEmployeeID)
	{
		employeeID = pEmployeeID;
	}

	void ProductionPlan::SetCount(double pCount)
	{
		count = pCount;
	}

	void ProductionPlan::SetSum(double pSum)
	{
		sum = pSum;
	}

	void ProductionPlan::SetStatusID(int pStatusID)
	{
		statusID = pStatusID;
	}

	void ProductionPlan::SetCurrencyID(int pCurrencyID)
	{
		currencyID = pCurrencyID;
	}

	bool ProductionPlan::CreateProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, int eID, double pCount,
		double pSum, int sID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pDate, pCount, pSum, cID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		date = pDate;
		employeeID = eID;
		count = pCount;
		sum = pSum;
		statusID = sID;
		currencyID = cID;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateProductionPlan(id, date, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			//ormasDal.CommitTransaction(errorMessage);
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.StartTransaction(errorMessage);
		return false;
	}

	bool ProductionPlan::CreateProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateProductionPlan(id, date, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
			//ormasDal.CommitTransaction(errorMessage);
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.StartTransaction(errorMessage);
		return false;
	}
	bool ProductionPlan::DeleteProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeleteProductionPlan(id, errorMessage))
		{
			if (ormasDal.DeleteListByProductionPlanID(id, errorMessage))
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
	bool ProductionPlan::UpdateProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, int eID, double pCount,
		double pSum, int sID, int cID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		date = pDate;
		employeeID = eID;
		count = pCount;
		sum = pSum;
		statusID = sID;
		currencyID = cID;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateProductionPlan(id, date, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
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
	bool ProductionPlan::UpdateProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateProductionPlan(id, date, employeeID, count, sum, statusID, currencyID, errorMessage))
		{
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

	std::string ProductionPlan::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || 0 != employeeID || 0 != count || 0 != sum || 0 != statusID)
		{
			return ormasDal.GetFilterForProductionPlan(id, date, employeeID, count, sum, statusID, currencyID);
		}
		return "";
	}

	bool ProductionPlan::GetProductionPlanByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		id = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productionPlanViewCollection> productionPlanVector = ormasDal.GetProductionPlan(errorMessage, filter);
		if (0 != productionPlanVector.size())
		{
			id = std::get<0>(productionPlanVector.at(0));
			date = std::get<1>(productionPlanVector.at(0));
			count = std::get<2>(productionPlanVector.at(0));
			sum = std::get<3>(productionPlanVector.at(0));
			employeeID = std::get<10>(productionPlanVector.at(0));
			statusID = std::get<11>(productionPlanVector.at(0));
			currencyID = std::get<12>(productionPlanVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find production plan with this id";
		}
		return false;
	}

	bool ProductionPlan::IsEmpty()
	{
		if (0 == id && date == "" && 0 == count && 0 == sum && 0 == employeeID && 0 == statusID && 0 == currencyID)
			return true;
		return false;
	}

	void ProductionPlan::Clear()
	{
		id = 0;
		date.clear();
		count = 0;
		sum = 0;
		employeeID = 0;
		statusID = 0;
		currencyID = 0;
	}

	bool ProductionPlan::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pCount, double pSum,
		int cID, std::string& errorMessage)
	{
		ProductionPlan productionPlan;
		productionPlan.Clear();
		errorMessage.clear();
		productionPlan.SetDate(pDate);
		productionPlan.SetCount(pCount);
		productionPlan.SetSum(pSum);
		productionPlan.SetCurrencyID(cID);
		std::string filter = productionPlan.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionPlanViewCollection> productionPlanVector = ormasDal.GetProductionPlan(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionPlanVector.size())
		{
			return false;
		}
		errorMessage = "Production plan with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductionPlan::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ProductionPlan productionPlan;
		productionPlan.Clear();
		errorMessage.clear();
		productionPlan.SetDate(date);
		productionPlan.SetCount(count);
		productionPlan.SetSum(sum);
		productionPlan.SetCurrencyID(currencyID);
		std::string filter = productionPlan.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionPlanViewCollection> productionPlanVector = ormasDal.GetProductionPlan(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionPlanVector.size())
		{
			return false;
		}
		errorMessage = "Production plan with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

}