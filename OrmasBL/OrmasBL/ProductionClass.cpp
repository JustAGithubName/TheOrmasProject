#include "stdafx.h"
#include "ProductionClass.h"
#include "ProductionListClass.h"
#include "StockClass.h"
#include <map>

namespace BusinessLayer
{
	Production::Production(DataLayer::productionCollection pCollection)
	{
		id = std::get<0>(pCollection);
		productionDate = std::get<1>(pCollection);
		expiryDate = std::get<2>(pCollection);
		sessionStart = std::get<3>(pCollection);
		sessionEnd = std::get<4>(pCollection);
	}

	int Production::GetID()
	{
		return id;
	}

	std::string Production::GetProductionDate()
	{
		return productionDate;
	}

	std::string Production::GetExpiryDate()
	{
		return expiryDate;
	}

	std::string Production::GetSessionStart()
	{
		return sessionStart;
	}

	std::string Production::GetSessionEnd()
	{
		return sessionEnd;
	}

	void Production::SetID(int pID)
	{
		id = pID;
	}
	void Production::SetProductionDate(std::string pProductionDate)
	{
		productionDate = pProductionDate;
	}
	void Production::SetExpiryDate(std::string pExpiryDate)
	{
		expiryDate = pExpiryDate;
	}
	void Production::SetSessionStart(std::string pSessionStart)
	{
		sessionStart = pSessionStart;
	}
	void Production::SetSessionEnd(std::string pSessionEnd)
	{
		sessionEnd = pSessionEnd;
	}

	bool Production::CreateProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pProductionDate, std::string pExpiryDate,
		std::string pSessionStart, std::string pSessionEnd, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pProductionDate, pExpiryDate, pSessionStart, pSessionEnd, errorMessage))
			return false;
		productionDate = pProductionDate;
		expiryDate = pExpiryDate;
		sessionStart = pSessionStart;
		sessionEnd = pSessionEnd;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateProduction(id, productionDate, expiryDate, sessionStart, sessionEnd, errorMessage))
		{
			if (ChangesAtStock(globalVar, ormasDal, id, warehouseID, errorMessage))
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
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Production::CreateProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id &&ormasDal.CreateProduction(id, productionDate, expiryDate, sessionStart, sessionEnd, errorMessage))
		{
			if (ChangesAtStock(globalVar, ormasDal, id, warehouseID, errorMessage))
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
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Production::DeleteProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		//ormasDal.StartTransaction(errorMessage);
		if (ormasDal.DeleteProduction(id, errorMessage))
		{
			if (ormasDal.DeleteListByProductionID(id, errorMessage))
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
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Production::UpdateProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pProductionDate, std::string pExpiryDate,
		std::string pSessionStart, std::string pSessionEnd, std::string& errorMessage)
	{
		if (0 == prodCountMap.size())
			return false;
		productionDate = pProductionDate;
		expiryDate = pExpiryDate;
		sessionStart = pSessionStart;
		sessionEnd = pSessionEnd;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id &&ormasDal.UpdateProduction(id, productionDate, expiryDate, sessionStart, sessionEnd, errorMessage))
		{
			if (ChangesAtStock(globalVar, ormasDal, id, warehouseID, prodCountMap, errorMessage))
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
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Production::UpdateProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 == prodCountMap.size())
			return false;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id &&ormasDal.UpdateProduction(id, productionDate, expiryDate, sessionStart, sessionEnd, errorMessage))
		{
			if (ChangesAtStock(globalVar, ormasDal, id, warehouseID, prodCountMap, errorMessage))
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
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string Production::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !productionDate.empty() || !expiryDate.empty() || !sessionStart.empty() || !sessionEnd.empty())
		{
			return ormasDal.GetFilterForProduction(id, productionDate, expiryDate, sessionStart, sessionEnd);
		}
		return "";
	}

	std::string Production::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForProductionForPeriod(id, productionDate, expiryDate, sessionStart, sessionEnd, fromDate, toDate);
		}
		return "";
	}

	bool Production::GetProductionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productionCollection> productionVector = ormasDal.GetProduction(errorMessage, filter);
		if (0 != productionVector.size())
		{
			id = std::get<0>(productionVector.at(0));
			productionDate = std::get<1>(productionVector.at(0));
			expiryDate = std::get<2>(productionVector.at(0));
			sessionStart = std::get<3>(productionVector.at(0));
			sessionEnd = std::get<4>(productionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find production with this id";
		}
		return false;
	}
	
	bool Production::IsEmpty()
	{
		if (0 == id && productionDate == "" && expiryDate == "" && sessionStart == "" && sessionEnd == "")
			return true;
		return false;
	}

	void Production::Clear()
	{
		id = 0;
		productionDate.clear();
		expiryDate.clear();
		sessionEnd.clear();
		sessionStart.clear();
	}

	bool Production::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pProductionDate, std::string pExpiryDate,
		std::string pSessionStart, std::string pSessionEnd, std::string& errorMessage)
	{
		Production production;
		production.Clear();
		errorMessage.clear();
		production.SetProductionDate(pProductionDate);
		production.SetExpiryDate(pExpiryDate);
		production.SetSessionStart(pSessionStart);
		production.SetSessionEnd(pSessionEnd);
		std::string filter = production.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionCollection> productionVector = ormasDal.GetProduction(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionVector.size())
		{
			return false;
		}
		errorMessage = "Production with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Production::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Production production;
		production.Clear();
		errorMessage.clear();
		production.SetProductionDate(productionDate);
		production.SetExpiryDate(expiryDate);
		production.SetSessionStart(sessionStart);
		production.SetSessionEnd(sessionEnd);
		std::string filter = production.GenerateFilter(ormasDal);
		std::vector<DataLayer::productionCollection> productionVector = ormasDal.GetProduction(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productionVector.size())
		{
			return false;
		}
		errorMessage = "Production with this parameters are already exist! Please avoid the duplication!";
		return true;
	}


	bool Production::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int warID, std::string& errorMessage)
	{
		Stock pStock;
		return pStock.ChangingByProduction(globalVar, ormasDal, rpID, warID, errorMessage);
	}

	bool Production::ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int warID, std::map<int, double> pProdCountMap, std::string& errorMessage)
	{
		Stock pStock;
		return pStock.ChangingByProduction(globalVar, ormasDal, rpID, warID, pProdCountMap, errorMessage);
	}
}

