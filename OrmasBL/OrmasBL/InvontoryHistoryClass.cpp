#include "stdafx.h"
#include "InventoryHistoryClass.h"

namespace BusinessLayer
{
	InventoryHistory::InventoryHistory(DataLayer::inventoryHistoryCollection iCollection)
	{
		id = std::get<0>(iCollection);
		inventoryID = std::get<1>(iCollection);
		comment = std::get<2>(iCollection);
		changeDate = std::get<3>(iCollection);
	}

	int InventoryHistory::GetID()
	{
		return id;
	}

	int InventoryHistory::GetInventoryID()
	{
		return inventoryID;
	}

	std::string InventoryHistory::GetComment()
	{
		return comment;
	}

	std::string InventoryHistory::GetChangeDate()
	{
		return changeDate;
	}

	void InventoryHistory::SetID(int iID)
	{
		id = iID;
	}

	void InventoryHistory::SetInventoryID(int invID)
	{
		inventoryID = invID;
	}

	void InventoryHistory::SetComment(std::string iComment)
	{
		comment = iComment;
	}

	void InventoryHistory::SetChangeDate(std::string iChangeDate)
	{
		changeDate = iChangeDate;
	}

	bool InventoryHistory::CreateInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int invID, std::string iComment, std::string iChangeDate, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, invID, iComment, iChangeDate, errorMessage))
			return true;
		id = ormasDal.GenerateID();
		inventoryID = invID;
		comment = iComment;
		changeDate = iChangeDate;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateInventoryHistory(id, inventoryID, comment, changeDate, errorMessage))
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

	bool InventoryHistory::CreateInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return true;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateInventoryHistory(id, inventoryID, comment, changeDate, errorMessage))
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
	bool InventoryHistory::DeleteInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeleteFixedAssetsOperation(id, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool InventoryHistory::UpdateInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int invID, std::string iComment, std::string iChangeDate, std::string& errorMessage)
	{
		inventoryID = invID;
		comment = iComment;
		changeDate = iChangeDate;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateInventoryHistory(id, inventoryID, comment, changeDate, errorMessage))
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
	bool InventoryHistory::UpdateInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateInventoryHistory(id, inventoryID, comment, changeDate, errorMessage))
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

	std::string InventoryHistory::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != inventoryID || !comment.empty() || !changeDate.empty())
		{
			return ormasDal.GetFilterForInventoryHistory(id, inventoryID, comment, changeDate);
		}
		return "";
	}

	bool InventoryHistory::GetInventoryHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage)
	{
		if (iID <= 0)
			return false;
		id = iID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::inventoryHistoryCollection> inventoryHistoryVector = ormasDal.GetInventoryHistory(errorMessage, filter);
		if (0 != inventoryHistoryVector.size())
		{
			id = std::get<0>(inventoryHistoryVector.at(0));
			inventoryID = std::get<1>(inventoryHistoryVector.at(0));
			comment = std::get<2>(inventoryHistoryVector.at(0));
			changeDate = std::get<3>(inventoryHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find inventry with this id";
		}
		return false;
	}

	bool InventoryHistory::IsEmpty()
	{
		if (0 == id && 0 == inventoryID && comment == "" &&  changeDate == "")
			return true;
		return false;
	}

	void InventoryHistory::Clear()
	{
		id = 0;
		inventoryID = 0;
		comment = "";
		changeDate = "";
	}

	bool InventoryHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int invID, std::string iComment, std::string iChangeDate, std::string& errorMessage)
	{
		InventoryHistory inventoryHistory;
		inventoryHistory.Clear();
		errorMessage.clear();
		inventoryHistory.SetInventoryID(invID);
		inventoryHistory.SetComment(iComment);
		inventoryHistory.SetChangeDate(iChangeDate);
		std::string filter = inventoryHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::inventoryHistoryCollection> inventoryHistoryVector = ormasDal.GetInventoryHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == inventoryHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Inventory history with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool InventoryHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		InventoryHistory inventoryHistory;
		inventoryHistory.Clear();
		errorMessage.clear();
		inventoryHistory.SetInventoryID(inventoryID);
		inventoryHistory.SetComment(comment);
		inventoryHistory.SetChangeDate(changeDate);
		std::string filter = inventoryHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::inventoryHistoryCollection> inventoryHistoryVector = ormasDal.GetInventoryHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == inventoryHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Inventory history with these parameters are already exist! Please avoid the duplication!";
		return true;
	}
}
