#include "stdafx.h"
#include "AccountableEntryClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	AccountableEntry::AccountableEntry(DataLayer::accountableEntryCollection cCollection)
	{
		id = std::get<0>(cCollection);;
		debitAccountID = std::get<1>(cCollection);;
		debitSubaccountID = std::get<2>(cCollection);
		value = std::get<3>(cCollection);
		creditAccountID = std::get<4>(cCollection);
		creditSubaccountID = std::get<5>(cCollection);
		accountableDocumentID = std::get<6>(cCollection);
	}

	int AccountableEntry::GetID()
	{
		return id;
	}

	int AccountableEntry::GetDebitAccountID()
	{
		return debitAccountID;
	}
	int AccountableEntry::GetDebitSubaccountID()
	{
		return debitSubaccountID;
	}
	double AccountableEntry::GetValue()
	{
		return value;
	}
	int AccountableEntry::GetCreditAccountID()
	{
		return creditAccountID;
	}

	int AccountableEntry::GetCreditSubaccountID()
	{
		return creditSubaccountID;
	}
	int AccountableEntry::GetAccountableDocumentID()
	{
		return accountableDocumentID;
	}

	void AccountableEntry::SetID(int aID)
	{
		id = aID;
	}
	void AccountableEntry::SetDebitAccountID(int debAccID)
	{
		debitAccountID = debAccID;
	}
	void AccountableEntry::SetDebitSubaccountID(int debSubaccID)
	{
		debitSubaccountID = debSubaccID;
	}
	void AccountableEntry::SetValue(double aValue)
	{
		value = aValue;
	}
	void AccountableEntry::SetCreditAccountID(int credAccID)
	{
		creditAccountID = credAccID;
	}
	void AccountableEntry::SetCreditSubaccountID(int credSubaccID)
	{
		creditSubaccountID = credSubaccID;
	}
	void AccountableEntry::SetAccountableDocumentID(int accDocID)
	{
		accountableDocumentID = accDocID;
	}

	bool AccountableEntry::CreateAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int daID, int dsID, double eValue, int caID, int csID, int aDocumentID, std::string& errorMessage)
	{

		//if (IsDuplicate(globalVar, ormasDal, eID, aInformation, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		debitAccountID = daID;
		debitSubaccountID = dsID;
		value = eValue;
		creditAccountID = caID;
		creditSubaccountID = csID;
		accountableDocumentID = aDocumentID;
		if (ormasDal.CreateAccountableEntry(id, debitAccountID, debitSubaccountID, value, creditAccountID, creditSubaccountID, accountableDocumentID, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableEntry::CreateAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAccountableEntry(id, debitAccountID, debitSubaccountID, value, creditAccountID, creditSubaccountID, accountableDocumentID, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableEntry::DeleteAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteAccountableEntry(id, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableEntry::DeleteAccountableEntryByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteAccountableEntryByDocumentID(accountableDocumentID, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableEntry::UpdateAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int daID, int dsID, double eValue, int caID, int csID, int aDocumentID, std::string& errorMessage)
	{
		debitAccountID = daID;
		debitSubaccountID = dsID;
		value = eValue;
		creditAccountID = caID;
		creditSubaccountID = csID;
		accountableDocumentID = aDocumentID;
		//ormasDal.StartTransaction(errorMessage);
		if (ormasDal.UpdateAccountableEntry(id, debitAccountID, debitSubaccountID, value, creditAccountID, creditSubaccountID, accountableDocumentID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool AccountableEntry::UpdateAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateAccountableEntry(id, debitAccountID, debitSubaccountID, value, creditAccountID, creditSubaccountID, accountableDocumentID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string AccountableEntry::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != debitAccountID || 0 != debitSubaccountID || 0 != value || 0 != creditAccountID || 0 != creditSubaccountID || 0 != accountableDocumentID)
		{
			return ormasDal.GetFilterForAccountableEntry(id, debitAccountID, debitSubaccountID, value, creditAccountID, creditSubaccountID, accountableDocumentID);
		}
		return "";
	}

	bool AccountableEntry::GetAccountableEntryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableEntryCollection> accountableEntryVector = ormasDal.GetAccountableEntry(errorMessage, filter);
		if (0 != accountableEntryVector.size())
		{
			id = std::get<0>(accountableEntryVector.at(0));
			debitAccountID = std::get<1>(accountableEntryVector.at(0));
			debitSubaccountID = std::get<2>(accountableEntryVector.at(0));
			value = std::get<3>(accountableEntryVector.at(0));
			creditAccountID = std::get<4>(accountableEntryVector.at(0));
			creditSubaccountID = std::get<5>(accountableEntryVector.at(0));
			accountableDocumentID = std::get<6>(accountableEntryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable Entry with this id";
		}
		return false;
	}

	std::vector<int> AccountableEntry::GetAllEntryByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, std::string& errorMessage)
	{
		std::vector<int> entryIDVector;
		AccountableEntry adlEntry;
		adlEntry.SetAccountableDocumentID(adID);
		std::string filter = adlEntry.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableEntryCollection> accountableEntryVector = ormasDal.GetAccountableEntry(errorMessage, filter);
		if (0 != accountableEntryVector.size())
		{
			for each (auto item in accountableEntryVector)
			{
				entryIDVector.push_back(std::get<0>(item));
			}
		}
		return entryIDVector;
	}



	bool AccountableEntry::IsEmpty()
	{
		if (0 == id && 0 == debitAccountID && 0 == debitSubaccountID && 0 == value && 0 == creditAccountID && 0 == creditSubaccountID && 0 == accountableDocumentID)
			return true;
		return false;
	}

	void AccountableEntry::Clear()
	{
		id = 0;
		debitAccountID = 0;
		debitSubaccountID = 0;
		value = 0;
		creditAccountID = 0;
		creditSubaccountID = 0;
		accountableDocumentID = 0;
	}

	bool AccountableEntry::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int daID, int dsID, double eValue, int caID, int csID, int aDocumentID, std::string& errorMessage)
	{
		AccountableEntry accountableEntry;
		accountableEntry.Clear();
		errorMessage.clear();
		accountableEntry.SetDebitAccountID(daID);
		accountableEntry.SetDebitSubaccountID(dsID);
		accountableEntry.SetValue(eValue);
		accountableEntry.SetCreditAccountID(caID);
		accountableEntry.SetCreditSubaccountID(csID);
		accountableEntry.SetAccountableDocumentID(aDocumentID);

		std::string filter = accountableEntry.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableEntryCollection> accountableEntryVector = ormasDal.GetAccountableEntry(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableEntryVector.size())
		{
			return false;
		}
		errorMessage = "Accountable Entry with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountableEntry::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountableEntry accountableEntry;
		accountableEntry.Clear();
		errorMessage.clear();
		accountableEntry.SetDebitAccountID(debitAccountID);
		accountableEntry.SetDebitSubaccountID(debitSubaccountID);
		accountableEntry.SetValue(value);
		accountableEntry.SetCreditAccountID(creditAccountID);
		accountableEntry.SetCreditSubaccountID(creditSubaccountID);
		accountableEntry.SetAccountableDocumentID(accountableDocumentID);

		std::string filter = accountableEntry.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableEntryCollection> accountableEntryVector = ormasDal.GetAccountableEntry(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableEntryVector.size())
		{
			return false;
		}
		errorMessage = "Accountable Entry with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountableEntry::ExecuteEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eRel;
		entry.SetDate(ormasDal.GetSystemDateTime());
		if (debitSubaccountID > 0)
			entry.SetDebitingAccountID(debitSubaccountID);
		else
			entry.SetDebitingAccountID(debitAccountID);
		entry.SetValue(value);
		if (creditSubaccountID > 0)
			entry.SetCreditingAccountID(creditSubaccountID);
		else
			entry.SetCreditingAccountID(creditAccountID);
		entry.SetDescription("Accounable report");
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eRel.SetEntryID(entry.GetID());
			eRel.SetOperationID(accountableDocumentID);
			if (eRel.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return true;
			}
		}
		return false;
	}

	bool AccountableEntry::ExecuteEntryReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{

		Entry entry;
		EntryOperationRelation eRel;
		entry.SetDate(ormasDal.GetSystemDateTime());
		if (creditSubaccountID > 0)
			entry.SetDebitingAccountID(creditSubaccountID);
		else
			entry.SetDebitingAccountID(creditAccountID);
		entry.SetValue(value);
		if (debitSubaccountID> 0)
			entry.SetCreditingAccountID(debitSubaccountID);
		else
			entry.SetCreditingAccountID(debitAccountID);
		entry.SetDescription("Accounable report");
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eRel.SetEntryID(entry.GetID());
			eRel.SetOperationID(accountableDocumentID);
			if (eRel.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return true;
			}
		}
		return false;
	}
}