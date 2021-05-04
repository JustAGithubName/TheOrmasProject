#include "stdafx.h"
#include "EntryRoutingClass.h"

namespace BusinessLayer{
	EntryRouting::EntryRouting(DataLayer::entryRoutingCollection eCollection)
	{
		id = std::get<0>(eCollection);
		operation = std::get<1>(eCollection);
		debitAccountID = std::get<2>(eCollection);
		creditAccountID = std::get<3>(eCollection);
	}
	EntryRouting::EntryRouting()
	{
		operation = "";
		debitAccountID = 0;
		creditAccountID = 0;
	}
	int EntryRouting::GetID()
	{
		return id;
	}

	std::string EntryRouting::GetOperation()
	{
		return operation;
	}

	int EntryRouting::GetDebitAccountID()
	{
		return debitAccountID;
	}

	int EntryRouting::GetCreditAccountID()
	{
		return creditAccountID;
	}

	void EntryRouting::SetID(int eID)
	{
		id = eID;
	}

	void EntryRouting::SetOperation(std::string eOperation)
	{
		operation = eOperation;
	}

	void EntryRouting::SetDebitAccountID(int eDebitAccountID)
	{
		debitAccountID = eDebitAccountID;
	}

	void EntryRouting::SetCreditAccountID(int eCreditAccountID)
	{
		creditAccountID = eCreditAccountID;
	}


	bool EntryRouting::CreateEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eOperation, int eDebitAccountID, int eCreditAccountID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, eOperation, eDebitAccountID, eCreditAccountID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		operation = eOperation;
		debitAccountID = eDebitAccountID;
		creditAccountID = eCreditAccountID;
		if (0 != id && ormasDal.CreateEntryRouting(id, operation, debitAccountID, creditAccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EntryRouting::CreateEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateEntryRouting(id, operation, debitAccountID, creditAccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EntryRouting::DeleteEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteEntryRouting(id, errorMessage))
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

	bool EntryRouting::UpdateEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eOperation, int eDebitAccountID, int eCreditAccountID, std::string& errorMessage)
	{
		operation = eOperation;
		debitAccountID = eDebitAccountID;
		creditAccountID = eCreditAccountID;
		if (0 != id && ormasDal.UpdateEntryRouting(id, operation, debitAccountID, creditAccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EntryRouting::UpdateEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateEntryRouting(id, operation, debitAccountID, creditAccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string EntryRouting::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || operation.empty() || 0 != debitAccountID || 0 != creditAccountID)
		{
			return ormasDal.GetFilterForEntryRouting(id, operation, debitAccountID, creditAccountID);
		}
		return "";
	}

	bool EntryRouting::GetEntryRoutingByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		if (eID <= 0)
			return false;
		id = eID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::entryRoutingCollection> entryRoutingVector = ormasDal.GetEntryRouting(errorMessage, filter);
		if (0 != entryRoutingVector.size())
		{
			id = std::get<0>(entryRoutingVector.at(0));
			operation = std::get<1>(entryRoutingVector.at(0));
			debitAccountID = std::get<2>(entryRoutingVector.at(0));
			creditAccountID = std::get<3>(entryRoutingVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find entry routing with this id";
		}
		return false;
	}

	bool EntryRouting::IsEmpty()
	{
		if (0 == id && operation.empty()  && 0 == debitAccountID && 0 == creditAccountID)
			return true;
		return false;
	}

	void EntryRouting::Clear()
	{
		id = 0;
		operation.clear();
		debitAccountID = 0;
		creditAccountID = 0;
	}

	bool EntryRouting::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eOperation, int eDebitAccountID, int eCreditAccountID, std::string& errorMessage)
	{
		EntryRouting entryRouting;
		entryRouting.Clear();
		errorMessage.clear();
		entryRouting.SetOperation(eOperation);
		entryRouting.SetDebitAccountID(eDebitAccountID);
		entryRouting.SetCreditAccountID(eCreditAccountID);
		std::string filter = entryRouting.GenerateFilter(ormasDal);
		errorMessage.clear();
		std::vector<DataLayer::entryRoutingCollection> entryRoutingVector = ormasDal.GetEntryRouting(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == entryRoutingVector.size())
		{
			return false;
		}
		errorMessage = "Entry routing with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool EntryRouting::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		EntryRouting entryRouting;
		entryRouting.Clear();
		errorMessage.clear();
		entryRouting.SetOperation(operation);
		entryRouting.SetDebitAccountID(debitAccountID);
		entryRouting.SetCreditAccountID(creditAccountID);
		std::string filter = entryRouting.GenerateFilter(ormasDal);
		errorMessage.clear();
		std::vector<DataLayer::entryRoutingCollection> entryRoutingVector = ormasDal.GetEntryRouting(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == entryRoutingVector.size())
		{
			return false;
		}
		errorMessage = "Entry routing with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool EntryRouting::CheckEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eDebitAccountID, int eCreditAccountID, std::string& errorMessage)
	{
		EntryRouting entryRouting;
		entryRouting.SetDebitAccountID(eDebitAccountID);
		entryRouting.SetCreditAccountID(eCreditAccountID);
		std::string filter = entryRouting.GenerateFilter(ormasDal);
		errorMessage.clear();
		std::vector<DataLayer::entryRoutingCollection> entryRoutingVector = ormasDal.GetEntryRouting(errorMessage, filter);
		if (!errorMessage.empty())
			return false;
		if (0 < entryRoutingVector.size())
		{
			return true;
		}
		errorMessage = "Entry routing with these parameters does not exist! This entry isn't valid!";
		return false;
	}
}