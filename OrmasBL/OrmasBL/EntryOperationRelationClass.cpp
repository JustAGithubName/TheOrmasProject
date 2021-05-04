#include "stdafx.h"
#include "EntryOperationRelationClass.h"


namespace BusinessLayer{
	EntryOperationRelation::EntryOperationRelation(DataLayer::entryOperationCollection aeCollection)
	{
		id = std::get<0>(aeCollection);
		entryID = std::get<1>(aeCollection);
		operationID = std::get<2>(aeCollection);
	}
	EntryOperationRelation::EntryOperationRelation()
	{
		id = 0;
		entryID = 0;
		operationID = 0;
	}

	int EntryOperationRelation::GetID()
	{
		return id;
	}

	int EntryOperationRelation::GetOperationID()
	{
		return operationID;
	}

	int EntryOperationRelation::GetEntryID()
	{
		return entryID;
	}

	void EntryOperationRelation::SetID(int eoID)
	{
		id = eoID;
	}
	void EntryOperationRelation::SetOperationID(int oID)
	{
		operationID = oID;
	}
	void EntryOperationRelation::SetEntryID(int eID)
	{
		entryID = eID;
	}

	bool EntryOperationRelation::CreateEntryOperationRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int oID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, eID, oID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		operationID = oID;
		entryID = eID;

		if (ormasDal.CreateEntryOperation(id, entryID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EntryOperationRelation::CreateEntryOperationRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateEntryOperation(id, entryID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EntryOperationRelation::DeleteEntryOperationRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteEntryOperation(entryID, operationID, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}



	std::string EntryOperationRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != operationID || 0 != entryID)
		{
			return ormasDal.GetFilterForEntryOperation(id, entryID, operationID);
		}
		return "";
	}

	std::vector<int> EntryOperationRelation::GetAllEntryByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		std::vector<int> entryIDVector;
		EntryOperationRelation aeRelation;
		aeRelation.SetOperationID(oID);
		aeRelation.SetEntryID(0);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::entryOperationCollection> entryOperationVector = ormasDal.GetEntryOperation(errorMessage, filter);
		if (0 != entryOperationVector.size())
		{
			for each (auto item in entryOperationVector)
			{
				entryIDVector.push_back(std::get<1>(item));
			}
		}
		return entryIDVector;
	}

	std::vector<int> EntryOperationRelation::GetAllOperationByEntryID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		std::vector<int> operationIDVector;
		EntryOperationRelation aeRelation;
		aeRelation.SetOperationID(0);
		aeRelation.SetEntryID(eID);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::entryOperationCollection> entryOperationVector = ormasDal.GetEntryOperation(errorMessage, filter);
		if (0 != entryOperationVector.size())
		{
			for each (auto item in entryOperationVector)
			{
				operationIDVector.push_back(std::get<2>(item));
			}
		}
		return operationIDVector;
	}


	bool EntryOperationRelation::IsEmpty()
	{
		if (0 == id && 0 == operationID && 0 == entryID)
			return true;
		return false;
	}

	void EntryOperationRelation::Clear()
	{
		id = 0;
		operationID = 0;
		entryID = 0;
	}

	bool EntryOperationRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int sID, std::string& errorMessage)
	{
		EntryOperationRelation aeRelation;
		aeRelation.Clear();
		errorMessage.clear();
		aeRelation.SetOperationID(sID);
		aeRelation.SetEntryID(eID);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::entryOperationCollection> entryOperationVector = ormasDal.GetEntryOperation(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == entryOperationVector.size())
		{
			return false;
		}
		errorMessage = "Entry-Operation Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool EntryOperationRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		EntryOperationRelation aeRelation;
		aeRelation.Clear();
		errorMessage.clear();
		aeRelation.SetOperationID(operationID);
		aeRelation.SetEntryID(entryID);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::entryOperationCollection> entryOperationVector = ormasDal.GetEntryOperation(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == entryOperationVector.size())
		{
			return false;
		}
		errorMessage = "Entry-Operation Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}