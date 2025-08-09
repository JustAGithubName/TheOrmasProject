#include "stdafx.h"
#include "EntryClass.h"
#include "EntryRoutingClass.h"
#include "AccountClass.h"
#include "SubaccountClass.h"
#include "AccountTypeClass.h"
#include "EntrySubaccountRelationClass.h"
#include "MulticurrencyClass.h"
#include "CurrencyRateClass.h"
#include "CurrencyClass.h"

namespace BusinessLayer{
	Entry::Entry(DataLayer::entriesCollection eCollection)
	{
		id = std::get<0>(eCollection);
		date = std::get<1>(eCollection);
		debitingAccountID = std::get<2>(eCollection);
		value = std::get<3>(eCollection);
		creditingAccountID = std::get<4>(eCollection);
		description = std::get<5>(eCollection);
	}
	Entry::Entry()
	{
		date = "";
		debitingAccountID = 0;
		value = 0.0;
		creditingAccountID = 0;
		description = "";
	}
	int Entry::GetID()
	{
		return id;
	}

	std::string Entry::GetDate()
	{
		return date;
	}

	int Entry::GetDebitingAccountID()
	{
		return debitingAccountID;
	}
	
	double Entry::GetValue()
	{
		return value;
	}
	
	int Entry::GetCreditingAccountID()
	{
		return creditingAccountID;
	}

	std::string Entry::GetDescription()
	{
		return description;
	}

	void Entry::SetID(int eID)
	{
		id = eID;
	}

	void Entry::SetDate(std::string eDate)
	{
		date = eDate;
	}

	void Entry::SetDebitingAccountID(int daID)
	{
		debitingAccountID = daID;
	}

	void Entry::SetValue(double eValue)
	{
		value = eValue;
	}

	void Entry::SetCreditingAccountID(int caID)
	{
		creditingAccountID = caID;
	}

	void Entry::SetDescription(std::string eDescription)
	{
		description = eDescription;
	}


	bool Entry::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eDate, int daID, double eValue, int caID, 
		std::string eDescription, std::string& errorMessage, bool corrEntry)
	{
		if (IsDuplicate(globalVar, ormasDal, eDate, daID, eValue, caID, errorMessage))
			return false;
		if (corrEntry == false)
		{
			if (!EntryRoutingValidation(globalVar, ormasDal, daID, caID, errorMessage))
				return false;
		}
		id = ormasDal.GenerateID();
		date = eDate;
		debitingAccountID = daID;
		value = eValue;
		creditingAccountID = caID;
		description = eDescription;
		//ormasDal.StartTransaction(errorMessage);
		Subaccount dSAcc;
		Subaccount cSAcc;
		Account dAccount;
		Account cAccount;
		int dSAccParentID = 0;
		int cSAccParentID = 0;
		if (!dSAcc.GetSubaccountByID(globalVar, ormasDal, debitingAccountID, errorMessage))
		{
			dSAccParentID = debitingAccountID;
			dSAcc.Clear();
			errorMessage.clear();
			if (dAccount.HaveSubaccount(globalVar, ormasDal, dSAccParentID))
			{
				return false;
			}
		}
		else
		{
			dSAccParentID = dSAcc.GetParentAccountID();
			errorMessage.clear();
		}
		if (!cSAcc.GetSubaccountByID(globalVar, ormasDal, creditingAccountID, errorMessage))
		{
			cSAccParentID = creditingAccountID;
			cSAcc.Clear();
			errorMessage.clear();
			if (cAccount.HaveSubaccount(globalVar, ormasDal, cSAccParentID))
			{
				return false;
			}
		}
		else
		{
			cSAccParentID = cSAcc.GetParentAccountID();
			errorMessage.clear();
		}
		if (0 != id && ormasDal.CreateEntry(id, date, dSAccParentID, value, cSAccParentID, eDescription, errorMessage))
		{
			if (DebitAccount(globalVar, ormasDal, debitingAccountID, value, creditingAccountID) && CreditAccount(globalVar, ormasDal, creditingAccountID, value, debitingAccountID))
			{
				if (!ReCalculateParentAccount(globalVar, ormasDal, debitingAccountID, creditingAccountID,  value, errorMessage))
					return false;
				EntrySubaccountRelation debRelation;
				EntrySubaccountRelation credRelation;
				if (!dSAcc.IsEmpty())
				{
					debRelation.SetSubaccountID(debitingAccountID);
					debRelation.SetEntryID(id);
					if (!debRelation.CreateEntrySubaccountRelation(globalVar, ormasDal, errorMessage))
					{
						return false;
					}
				}
				if (!cSAcc.IsEmpty())
				{
					credRelation.SetSubaccountID(creditingAccountID);
					credRelation.SetEntryID(id);
					if (!credRelation.CreateEntrySubaccountRelation(globalVar, ormasDal, errorMessage))
					{
						return false;
					}
				}
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.StartTransaction(errorMessage);
		return false;
	}
	bool Entry::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage, bool corrEntry)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		if (corrEntry == false)
		{
			if (!EntryRoutingValidation(globalVar, ormasDal, debitingAccountID, creditingAccountID, errorMessage))
				return false;
		}
		if (value < 0)
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		Subaccount dSAcc;
		Subaccount cSAcc; 
		Account cAccount;
		Account dAccount;
		int dSAccParentID = 0;
		int cSAccParentID = 0;
		if (!dSAcc.GetSubaccountByID(globalVar, ormasDal, debitingAccountID, errorMessage))
		{
			dSAccParentID = debitingAccountID;
			dSAcc.Clear();
			errorMessage.clear();
			if (dAccount.HaveSubaccount(globalVar, ormasDal, dSAccParentID))
			{
				return false;
			}
		}
		else
		{
			dSAccParentID = dSAcc.GetParentAccountID();
			errorMessage.clear();
		}
		if (!cSAcc.GetSubaccountByID(globalVar, ormasDal, creditingAccountID, errorMessage))
		{
			cSAccParentID = creditingAccountID;
			cSAcc.Clear();
			errorMessage.clear();
			if (cAccount.HaveSubaccount(globalVar, ormasDal, cSAccParentID))
			{
				return false;
			}
		}
		else
		{
			cSAccParentID = cSAcc.GetParentAccountID();
			errorMessage.clear();
		}
		if (0 != id && ormasDal.CreateEntry(id, date, dSAccParentID, value, cSAccParentID, description, errorMessage))
		{
			if (DebitAccount(globalVar, ormasDal, debitingAccountID, value, creditingAccountID) && CreditAccount(globalVar, ormasDal, creditingAccountID, value, debitingAccountID))
			{
				if (!ReCalculateParentAccount(globalVar, ormasDal, debitingAccountID, creditingAccountID, value, errorMessage))
					return false;
				EntrySubaccountRelation debRelation;
				EntrySubaccountRelation credRelation;
				debRelation.SetSubaccountID(debitingAccountID);
				debRelation.SetEntryID(id);
				credRelation.SetSubaccountID(creditingAccountID);
				credRelation.SetEntryID(id);
				if (!dSAcc.IsEmpty())
				{
					debRelation.SetSubaccountID(debitingAccountID);
					debRelation.SetEntryID(id);
					if (!debRelation.CreateEntrySubaccountRelation(globalVar, ormasDal, errorMessage))
					{
						return false;
					}
				}
				if (!cSAcc.IsEmpty())
				{
					credRelation.SetSubaccountID(creditingAccountID);
					credRelation.SetEntryID(id);
					if (!credRelation.CreateEntrySubaccountRelation(globalVar, ormasDal, errorMessage))
					{
						return false;
					}
				}
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.StartTransaction(errorMessage);
		return false;
	}
	bool Entry::DeleteEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteEntry(id, errorMessage))
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

	bool Entry::UpdateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eDate, int daID, double eValue, int caID, 
		std::string eDescription, std::string& errorMessage, bool corrEntry)
	{
		date = eDate;
		debitingAccountID = daID;
		value = eValue;
		creditingAccountID = caID;
		description = eDescription;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateEntry(id, date, debitingAccountID, value, creditingAccountID, description, errorMessage))
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
	bool Entry::UpdateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage, bool corrEntry)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateEntry(id, date, debitingAccountID, value, creditingAccountID, description, errorMessage))
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

	std::string Entry::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || 0.0 != value || 0 != debitingAccountID || 0 != creditingAccountID || !description.empty())
		{
			return ormasDal.GetFilterForEntry(id, date, debitingAccountID, value, creditingAccountID, description);
		}
		return "";
	}

	std::string Entry::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (0 != id || !date.empty() || 0.0 != value || 0 != debitingAccountID || 0 != creditingAccountID || !description.empty())
		{
			return ormasDal.GetFilterForEntryForPeriod(id, date, debitingAccountID, value, creditingAccountID, description, fromDate, toDate);
		}
		return "";
	}

	bool Entry::GetEntryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		if (eID <= 0)
			return false;
		id = eID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::entriesViewCollection> entryVector = ormasDal.GetEntries(errorMessage, filter);
		if (0 != entryVector.size())
		{
			id = std::get<0>(entryVector.at(0));
			date = std::get<1>(entryVector.at(0));
			debitingAccountID = std::get<5>(entryVector.at(0));
			value = std::get<3>(entryVector.at(0));
			creditingAccountID = std::get<6>(entryVector.at(0));
			description = std::get<7>(entryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find entry with this id";
		}
		return false;
	}

	bool Entry::IsEmpty()
	{
		if (0 == id && date.empty() && 0.0 == value && 0 == debitingAccountID && 0 == creditingAccountID && description.empty())
			return true;
		return false;
	}

	void Entry::Clear()
	{
		id = 0;
		date.clear();
		value = 0;
		debitingAccountID = 0;
		creditingAccountID = 0;
		description.clear();
	}

	bool Entry::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eDate, int daID, double eValue, int caID, std::string& errorMessage)
	{
		Entry entry;
		entry.Clear();
		errorMessage.clear();
		entry.SetDate(eDate);
		entry.SetDebitingAccountID(daID);
		entry.SetValue(eValue);
		entry.SetCreditingAccountID(caID);
		std::string filter = entry.GenerateFilter(ormasDal);
		std::vector<DataLayer::entriesViewCollection> entryVector = ormasDal.GetEntries(errorMessage, filter);
		if (0 == entryVector.size())
		{
			return false;
		}
		errorMessage = "Entry with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Entry::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Entry entry;
		entry.Clear();
		errorMessage.clear();
		entry.SetDate(date);
		entry.SetDebitingAccountID(debitingAccountID);
		entry.SetValue(value);
		entry.SetCreditingAccountID(creditingAccountID);
		std::string filter = entry.GenerateFilter(ormasDal);
		std::vector<DataLayer::entriesViewCollection> entryVector = ormasDal.GetEntries(errorMessage, filter);
		if (0 == entryVector.size())
		{
			return false;
		}
		errorMessage = "Entry with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Entry::DebitAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debaccountID, double value, int credaccountID)
	{
		Subaccount subAcc;
		Account dAcc;
		AccountType atype;
		if (dAcc.GetAccountByID(globalVar, ormasDal, debaccountID, errorMessage))
		{
			/*if (atype.GetAccountTypeByNumber(globalVar, ormasDal, dAcc.GetAccountTypeNumber(ormasDal), errorMessage))
			{
				if (0 == atype.GetName().compare("ACTIVE"))
				{
					dAcc.SetCurrentBalance(dAcc.GetCurrentBalance() + value);
				}
				else if (0 == atype.GetName().compare("PASSIVE"))
				{
					dAcc.SetCurrentBalance(dAcc.GetCurrentBalance() - value);
				}
			}*/
			if (dAcc.AccountOperationValidation(globalVar, ormasDal, dAcc.GetCurrentBalance() + value))
			{
				dAcc.SetCurrentBalance(dAcc.GetCurrentBalance() + value);
				if (dAcc.UpdateAccount(globalVar, ormasDal, errorMessage))
					return true;
			}
		}
		else if (subAcc.GetSubaccountByID(globalVar, ormasDal, debaccountID, errorMessage))
		{
			/*if (atype.GetAccountTypeByNumber(globalVar, ormasDal, dAcc.GetAccountTypeNumber(ormasDal), errorMessage))
			{
			if (0 == atype.GetName().compare("ACTIVE"))
			{
			dAcc.SetCurrentBalance(dAcc.GetCurrentBalance() + value);
			}
			else if (0 == atype.GetName().compare("PASSIVE"))
			{
			dAcc.SetCurrentBalance(dAcc.GetCurrentBalance() - value);
			}
			}*/
			Multicurrency multicurrency;
			if (multicurrency.GetMulticurrencyByMainCurrencyID(globalVar, ormasDal, subAcc.GetID(), errorMessage))
			{
				Account acc66040;
				Account acc66140;
				if (!acc66040.GetAccountByNumber(globalVar, ormasDal, "66040", errorMessage))
					return false;
				if (!acc66140.GetAccountByNumber(globalVar, ormasDal, "66140", errorMessage))
					return false;
				if (acc66040.GetID() != credaccountID && acc66140.GetID() != credaccountID)
				{
					Subaccount subMulticurrency;
					if (!subMulticurrency.GetSubaccountByID(globalVar, ormasDal, multicurrency.GetSubaccountCurrencyID(), errorMessage))
						return false;
					CurrencyRate rate;
					if (!rate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, subMulticurrency.GetCurrencyID(), errorMessage))
						return false;
					subMulticurrency.SetCurrentBalance(subMulticurrency.GetCurrentBalance() + value / (rate.GetToValue() / rate.GetFromValue()));
					if (!subMulticurrency.UpdateSubaccount(globalVar, ormasDal, errorMessage))
						return false;
				}
			}
			multicurrency.Clear();
			errorMessage.clear();
			if (multicurrency.GetMulticurrencyBySubCurrencyID(globalVar, ormasDal, subAcc.GetID(), errorMessage))
			{
				Subaccount subMulticurrency;
				if (!subMulticurrency.GetSubaccountByID(globalVar, ormasDal, multicurrency.GetSubaccountMainCurrencyID(), errorMessage))
					return false;
				Account acc66040;
				Account acc66140;
				if (!acc66040.GetAccountByNumber(globalVar, ormasDal, "66040", errorMessage))
					return false;
				if (!acc66140.GetAccountByNumber(globalVar, ormasDal, "66140", errorMessage))
					return false;
				if (acc66040.GetID() != credaccountID && acc66140.GetID() != credaccountID)
				{
					CurrencyRate rate;
					if (!rate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, subAcc.GetCurrencyID(), errorMessage))
						return false;
					subAcc.SetCurrentBalance(subAcc.GetCurrentBalance() + value / (rate.GetToValue() / rate.GetFromValue()));
					if (!subAcc.UpdateSubaccount(globalVar, ormasDal, errorMessage))
						return false;
				}
				subAcc.Clear();
				subAcc = subMulticurrency;
			}
			if (dAcc.GetAccountByID(globalVar, ormasDal, subAcc.GetParentAccountID(), errorMessage))
			{
				if (dAcc.AccountOperationValidation(globalVar, ormasDal, dAcc.GetCurrentBalance() + value))
				{
					dAcc.SetCurrentBalance(dAcc.GetCurrentBalance() + value);
					subAcc.SetCurrentBalance(subAcc.GetCurrentBalance() + value);
					if (dAcc.UpdateAccount(globalVar, ormasDal, errorMessage) && subAcc.UpdateSubaccount(globalVar, ormasDal, errorMessage))
						return true;
				}
			}
		}
		return false;
	}

	bool Entry::CreditAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int credaccountID, double value, int debaccountID)
	{
		Subaccount subAcc;
		Account cAcc;
		AccountType atype;
		std::string parentNumber = "";
		if (cAcc.GetAccountByID(globalVar, ormasDal, credaccountID, errorMessage))
		{
			/*if (atype.GetAccountTypeByNumber(globalVar, ormasDal, cAcc.GetAccountTypeNumber(ormasDal), errorMessage))
			{
				if (0 == atype.GetName().compare("ACTIVE"))
				{
					cAcc.SetCurrentBalance(cAcc.GetCurrentBalance() - value);
				}
				else if (0 == atype.GetName().compare("PASSIVE"))
				{
					cAcc.SetCurrentBalance(cAcc.GetCurrentBalance() + value);
				}
			}*/
			cAcc.SetCurrentBalance(cAcc.GetCurrentBalance() - value);
			if (cAcc.UpdateAccount(globalVar, ormasDal, errorMessage))
				return true;
		}
		else if (subAcc.GetSubaccountByID(globalVar, ormasDal, credaccountID, errorMessage))
		{
			/*if (atype.GetAccountTypeByNumber(globalVar, ormasDal, cAcc.GetAccountTypeNumber(ormasDal), errorMessage))
			{
			if (0 == atype.GetName().compare("ACTIVE"))
			{
			cAcc.SetCurrentBalance(cAcc.GetCurrentBalance() - value);
			}
			else if (0 == atype.GetName().compare("PASSIVE"))
			{
			cAcc.SetCurrentBalance(cAcc.GetCurrentBalance() + value);
			}
			}*/
			Multicurrency multicurrency;
			if (multicurrency.GetMulticurrencyByMainCurrencyID(globalVar, ormasDal, subAcc.GetID(), errorMessage))
			{
				Account acc66040;
				Account acc66140;
				if (!acc66040.GetAccountByNumber(globalVar, ormasDal, "66040", errorMessage))
					return false;
				if (!acc66140.GetAccountByNumber(globalVar, ormasDal, "66140", errorMessage))
					return false;
				if (acc66040.GetID() != debaccountID && acc66140.GetID() != debaccountID)
				{
					Subaccount subMulticurrency;
					if (!subMulticurrency.GetSubaccountByID(globalVar, ormasDal, multicurrency.GetSubaccountCurrencyID(), errorMessage))
						return false;
					CurrencyRate rate;
					if (!rate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, subMulticurrency.GetCurrencyID(), errorMessage))
						return false;
					subMulticurrency.SetCurrentBalance(subMulticurrency.GetCurrentBalance() - value / (rate.GetToValue() / rate.GetFromValue()));
					if (!subMulticurrency.UpdateSubaccount(globalVar, ormasDal, errorMessage))
						return false;
				}
			}
			multicurrency.Clear();
			errorMessage.clear();
			if (multicurrency.GetMulticurrencyBySubCurrencyID(globalVar, ormasDal, subAcc.GetID(), errorMessage))
			{
				Subaccount subMulticurrency;
				if (!subMulticurrency.GetSubaccountByID(globalVar, ormasDal, multicurrency.GetSubaccountMainCurrencyID(), errorMessage))
					return false;
				Account acc66040;
				Account acc66140;
				if (!acc66040.GetAccountByNumber(globalVar, ormasDal, "66040", errorMessage))
					return false;
				if (!acc66140.GetAccountByNumber(globalVar, ormasDal, "66140", errorMessage))
					return false;
				if (acc66040.GetID() != credaccountID && acc66140.GetID() != credaccountID)
				{
					CurrencyRate rate;
					if (!rate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, subAcc.GetCurrencyID(), errorMessage))
						return false;
					subAcc.SetCurrentBalance(subAcc.GetCurrentBalance() - value / (rate.GetToValue() / rate.GetFromValue()));
					if (!subAcc.UpdateSubaccount(globalVar, ormasDal, errorMessage))
						return false;
				}
				subAcc.Clear();
				subAcc = subMulticurrency;
			}
			if (cAcc.GetAccountByID(globalVar, ormasDal, subAcc.GetParentAccountID(), errorMessage))
			{
				if (cAcc.AccountOperationValidation(globalVar, ormasDal, cAcc.GetCurrentBalance() + value))
				{
					cAcc.SetCurrentBalance(cAcc.GetCurrentBalance() - value);
					subAcc.SetCurrentBalance(subAcc.GetCurrentBalance() - value);
					if (cAcc.UpdateAccount(globalVar, ormasDal, errorMessage) && subAcc.UpdateSubaccount(globalVar, ormasDal, errorMessage))
						return true;
				}
			}
		}
		return false;
	}

	bool Entry::EntryRoutingValidation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int daID, int caID, std::string& errorMessage)
	{
		/*EntryRouting eRouting;
		Account dAcc;
		Account cAcc;
		if (dAcc.GetAccountByID(globalVar, ormasDal, daID, errorMessage) && cAcc.GetAccountByID(globalVar, ormasDal, caID, errorMessage))
		{
			return eRouting.CheckEntryRouting(globalVar, ormasDal, std::stoi(dAcc.GetNumber()), std::stoi(cAcc.GetNumber()), errorMessage);
		}
		return false;*/
		return true;
	}

	bool Entry::ReCalculateParentAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dAccID, int cAccID, double value, std::string& errorMessage)
	{
		Account dAcc;
		Account cAcc;
		Account dParentAcc;
		Account cParentAcc;
		Subaccount dSubAcc;
		Subaccount cSubAcc;
		std::string dParentNumber = "";
		std::string cParentNumber = "";
		dAcc.Clear();
		if (!dAcc.GetAccountByID(globalVar, ormasDal, dAccID, errorMessage))
		{
			if (!dSubAcc.GetSubaccountByID(globalVar, ormasDal, dAccID, errorMessage))
			{
				return false;
			}
			else
			{
				if (!dAcc.GetAccountByID(globalVar, ormasDal, dSubAcc.GetParentAccountID(), errorMessage))
					return false;
			}
		}		
		cAcc.Clear();
		if (!cAcc.GetAccountByID(globalVar, ormasDal, cAccID, errorMessage))
		{
			if (!cSubAcc.GetSubaccountByID(globalVar, ormasDal, cAccID, errorMessage))
			{
				return false;
			}
			else
			{
				if (!cAcc.GetAccountByID(globalVar, ormasDal, cSubAcc.GetParentAccountID(), errorMessage))
					return false;
			}
		}
		if (cAcc.GetID() == dAcc.GetID())
			return true;
		if (dAcc.GetNumber().substr(0, 3) != cAcc.GetNumber().substr(0, 3))
		{
			dParentNumber += dAcc.GetNumber().substr(0, 3);
			dParentNumber += "00";
			cParentNumber += cAcc.GetNumber().substr(0, 3);
			cParentNumber += "00";
			if (dAcc.GetNumber() != dParentNumber && cAcc.GetNumber() != cParentNumber)
			{
				if (!dParentAcc.GetAccountByNumber(globalVar, ormasDal, dParentNumber, errorMessage))
					return false;
				if (!cParentAcc.GetAccountByNumber(globalVar, ormasDal, cParentNumber, errorMessage))
					return false;
				dParentAcc.SetCurrentBalance(dParentAcc.GetCurrentBalance() + value);
				cParentAcc.SetCurrentBalance(cParentAcc.GetCurrentBalance() - value);
				if (!dParentAcc.UpdateAccount(globalVar, ormasDal, errorMessage) || !cParentAcc.UpdateAccount(globalVar, ormasDal, errorMessage))
					return false;
			}
			else if (dAcc.GetNumber() != dParentNumber)
			{
				if (!dParentAcc.GetAccountByNumber(globalVar, ormasDal, dParentNumber, errorMessage))
					return false;
				dParentAcc.SetCurrentBalance(dParentAcc.GetCurrentBalance() + value);
				if (!dParentAcc.UpdateAccount(globalVar, ormasDal, errorMessage))
					return false;
			}
			else if (cAcc.GetNumber() != cParentNumber)
			{
				if (!cParentAcc.GetAccountByNumber(globalVar, ormasDal, cParentNumber, errorMessage))
					return false;
				cParentAcc.SetCurrentBalance(cParentAcc.GetCurrentBalance() - value);
				if (!cParentAcc.UpdateAccount(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		errorMessage = "";
		return true;
	}
}
