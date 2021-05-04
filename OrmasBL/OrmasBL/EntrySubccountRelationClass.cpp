#include "stdafx.h"
#include "EntrySubaccountRelationClass.h"


namespace BusinessLayer{
	EntrySubaccountRelation::EntrySubaccountRelation(DataLayer::entrySubaccountCollection aeCollection)
	{
		id = std::get<0>(aeCollection);
		entryID = std::get<1>(aeCollection);
		subaccountID = std::get<2>(aeCollection);
	}
	EntrySubaccountRelation::EntrySubaccountRelation()
	{
		id = 0;
		entryID = 0;
		subaccountID = 0;
	}

	int EntrySubaccountRelation::GetID()
	{
		return id;
	}

	int EntrySubaccountRelation::GetSubaccountID()
	{
		return subaccountID;
	}

	int EntrySubaccountRelation::GetEntryID()
	{
		return entryID;
	}

	void EntrySubaccountRelation::SetID(int esID)
	{
		id = esID;
	}
	void EntrySubaccountRelation::SetSubaccountID(int sID)
	{
		subaccountID = sID;
	}
	void EntrySubaccountRelation::SetEntryID(int eID)
	{
		entryID = eID;
	}

	bool EntrySubaccountRelation::CreateEntrySubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int sID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, eID, sID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		subaccountID = sID;
		entryID = eID;

		if (ormasDal.CreateEntrySubaccount(id, entryID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EntrySubaccountRelation::CreateEntrySubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateEntrySubaccount(id, entryID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EntrySubaccountRelation::DeleteEntrySubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteEntrySubaccount(entryID, subaccountID, errorMessage))
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



	std::string EntrySubaccountRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != subaccountID || 0 != entryID)
		{
			return ormasDal.GetFilterForEntrySubaccount(id, entryID, subaccountID);
		}
		return "";
	}

	std::vector<int> EntrySubaccountRelation::GetAllEntryBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		std::vector<int> entryIDVector;
		EntrySubaccountRelation aeRelation;
		aeRelation.SetSubaccountID(sID);
		aeRelation.SetEntryID(0);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::entrySubaccountCollection> entrySubaccountVector = ormasDal.GetEntrySubaccount(errorMessage, filter);
		if (0 != entrySubaccountVector.size())
		{
			for each (auto item in entrySubaccountVector)
			{
				entryIDVector.push_back(std::get<1>(item));
			}
		}
		return entryIDVector;
	}

	std::vector<int> EntrySubaccountRelation::GetAllSubaccountByEntryID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		std::vector<int> subaccountIDVector;
		EntrySubaccountRelation aeRelation;
		aeRelation.SetSubaccountID(0);
		aeRelation.SetEntryID(eID);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::entrySubaccountCollection> entrySubaccountVector = ormasDal.GetEntrySubaccount(errorMessage, filter);
		if (0 != entrySubaccountVector.size())
		{
			for each (auto item in entrySubaccountVector)
			{
				subaccountIDVector.push_back(std::get<2>(item));
			}
		}
		return subaccountIDVector;
	}


	bool EntrySubaccountRelation::IsEmpty()
	{
		if (0 == id && 0 == subaccountID && 0 == entryID)
			return true;
		return false;
	}

	void EntrySubaccountRelation::Clear()
	{
		id = 0;
		subaccountID = 0;
		entryID = 0;
	}

	bool EntrySubaccountRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int sID, std::string& errorMessage)
	{
		EntrySubaccountRelation aeRelation;
		aeRelation.Clear();
		errorMessage.clear();
		aeRelation.SetSubaccountID(sID);
		aeRelation.SetEntryID(eID);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::entrySubaccountCollection> entrySubaccountVector = ormasDal.GetEntrySubaccount(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == entrySubaccountVector.size())
		{
			return false;
		}
		errorMessage = "Entry-Subaccount Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool EntrySubaccountRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		EntrySubaccountRelation aeRelation;
		aeRelation.Clear();
		errorMessage.clear();
		aeRelation.SetSubaccountID(subaccountID);
		aeRelation.SetEntryID(entryID);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::entrySubaccountCollection> entrySubaccountVector = ormasDal.GetEntrySubaccount(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == entrySubaccountVector.size())
		{
			return false;
		}
		errorMessage = "Entry-Subaccount Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}