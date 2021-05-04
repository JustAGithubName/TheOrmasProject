#include "stdafx.h"
#include "CreditorClass.h"
#include "BalanceClass.h"
#include "CurrencyClass.h"
#include "AccountClass.h"
#include "SubaccountClass.h"
#include "StatusClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	Creditor::Creditor(DataLayer::creditorsCollection cCollection)
	{
		id = std::get<0>(cCollection);
		name = std::get<1>(cCollection);
		address = std::get<2>(cCollection);
		phone = std::get<3>(cCollection);
		bankID = std::get<4>(cCollection);
		userID = std::get<5>(cCollection);
	}

	int Creditor::GetID()
	{
		return id;
	}
	std::string Creditor::GetName()
	{
		return name;
	}
	std::string Creditor::GetAddress()
	{
		return address;
	}
	std::string Creditor::GetPhone()
	{
		return phone;
	}
	int Creditor::GetBankID()
	{
		return bankID;
	}
	int Creditor::GetUserID()
	{
		return userID;
	}

	void Creditor::SetID(int cID)
	{
		id = cID;
	}
	void Creditor::SetName(std::string cName)
	{
		if (!cName.empty())
			boost::trim(cName);
		name = cName;
	}
	void Creditor::SetAddress(std::string cAddress)
	{
		if (!cAddress.empty())
			boost::trim(cAddress);
		address = cAddress;
	}
	void Creditor::SetPhone(std::string cPhone)
	{
		if (!cPhone.empty())
			boost::trim(cPhone);
		phone = cPhone;
	}

	bool Creditor::CreateCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, int bID, int uID, std::string& errorMessage)
	{
		TrimStrings(cName, cAddress, cPhone);
		id = ormasDal.GenerateID();
		name = cName;
		address = cAddress;
		phone = cPhone;
		bankID = bID;
		userID = uID;
		if (ormasDal.CreateCreditor(id, name, address, phone, bankID, userID,  errorMessage))
		{
			if (CreateBalanceForCreditor(globalVar, ormasDal, errorMessage))
				return true;
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Creditor::CreateCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.CreateCreditor(id, name, address, phone, bankID, userID, errorMessage))
		{
			if (CreateBalanceForCreditor(globalVar, ormasDal, errorMessage))
				return true;
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Creditor::DeleteCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteCreditor(id, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Creditor::UpdateCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, int bID, int uID, std::string& errorMessage)
	{
		TrimStrings(cName, cAddress, cPhone);
		name = cName;
		address = cAddress;
		phone = cPhone;
		bankID = bID;
		userID = uID;
		//ormasDal.StartTransaction(errorMessage);
		if (ormasDal.UpdateCreditor(id, name, address, phone, bankID, userID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool Creditor::UpdateCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateCreditor(id, name, address, phone, bankID, userID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string Creditor::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !address.empty() || !phone.empty() || 0 != bankID || 0 != userID)
		{
			return ormasDal.GetFilterForCreditor(id, name, address, phone, bankID, userID);
		}
		return "";
	}

	std::string Creditor::GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> creditorIDList)
	{
		if (creditorIDList.size()>0)
		{
			return ormasDal.GetINFilterForCreditorID(creditorIDList);
		}
		return "";
	}

	bool Creditor::GetCreditorByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::creditorsCollection> creditorVector = ormasDal.GetCreditors(errorMessage, filter);
		if (0 != creditorVector.size())
		{
			id = std::get<0>(creditorVector.at(0));
			name = std::get<1>(creditorVector.at(0));
			address = std::get<2>(creditorVector.at(0));
			phone = std::get<3>(creditorVector.at(0));
			bankID = std::get<4>(creditorVector.at(0));
			userID = std::get<5>(creditorVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Creditor with this id";
		}
		return false;
	}

	bool Creditor::IsEmpty()
	{
		if (0 == id && name.empty() && address.empty() && phone.empty() && 0 == bankID && 0 == userID)
			return true;
		return false;
	}

	void Creditor::Clear()
	{
		id = 0;
		name.clear();
		address.clear();
		phone.clear();
		bankID = 0;
		userID = 0;
	}

	void Creditor::TrimStrings(std::string& cName, std::string& cAddress, std::string& cPhone)
	{
		if (!cName.empty())
			boost::trim(cName);
		if (!cAddress.empty())
			boost::trim(cAddress);
		if (!cPhone.empty())
			boost::trim(cPhone);
	}

	bool Creditor::CreateBalanceForCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Currency currency;
		std::string number = "";
		std::string genAccRawNumber = "";
		int currID = currency.GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (0 != currID)
		{
			Status status;
			if (!status.GetStatusByName(globalVar, ormasDal, "OPEN", errorMessage))
				return false;
			if (!currency.GetCurrencyByID(globalVar, ormasDal, currID, errorMessage))
				return false;
			Subaccount subaccount;
			Account account;

			account.Clear();
			if (account.GetAccountByNumber(globalVar, ormasDal, "22120", errorMessage))
				number = std::to_string(10410);
			if (number.empty())
				return false;

			number.append(std::to_string(currency.GetCode()));
			genAccRawNumber = subaccount.GenerateRawNumber(globalVar, ormasDal, errorMessage);
			if (genAccRawNumber.empty())
				return false;
			number.append(genAccRawNumber);

			std::string owner;
			owner += name;

			subaccount.SetParentAccountID(account.GetID());
			subaccount.SetNumber(number);
			subaccount.SetStartBalance(0.0);
			subaccount.SetCurrentBalance(0.0);
			subaccount.SetCurrencyID(currID);
			subaccount.SetStatusID(status.GetID());
			subaccount.SetOpenedDate(ormasDal.GetSystemDate());
			subaccount.SetClosedDate("");
			subaccount.SetDetails(owner);

			if (!subaccount.CreateSubaccount(globalVar, ormasDal, errorMessage))
				return false;
		}
		return false;
	}
}