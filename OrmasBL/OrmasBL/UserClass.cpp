#include "stdafx.h"
#include "UserClass.h"
#include "BalanceClass.h"
#include "CurrencyClass.h"
#include "AccountClass.h"
#include "SubaccountClass.h"
#include "StatusClass.h"
#include "RoleClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer
{
	User::User(DataLayer::usersCollection uCollection)
	{
		id = std::get<0>(uCollection);
		email = std::get<1>(uCollection);
		name = std::get<2>(uCollection);
		surname = std::get<3>(uCollection);
		phone = std::get<4>(uCollection);
		address = std::get<5>(uCollection);
		roleID = std::get<6>(uCollection);
		password = std::get<7>(uCollection);
		activated = std::get<8>(uCollection);
	}

	int User::GetID()
	{
		return id;
	}

	std::string User::GetEmail()
	{
		return email;
	}

	std::string User::GetName()
	{
		return name;
	}

	std::string User::GetSurname()
	{
		return surname;
	}

	std::string User::GetPhone()
	{
		return phone;
	}

	std::string User::GetAddress()
	{
		return address;
	}

	int User::GetRoleID()
	{
		return roleID;
	}

	std::string User::GetPassword()
	{
		return password;
	}

	bool User::GetActivated()
	{
		return activated;
	}

	void User::SetID(int uID)
	{
		id = uID;
	}
	void User::SetEmail(std::string uEmail)
	{
		if (!uEmail.empty())
			boost::trim(uEmail);
		email = uEmail;
	}
	void User::SetName(std::string uName)
	{
		if (!uName.empty())
			boost::trim(uName);
		name = uName;
	}
	void User::SetSurname(std::string uSurname)
	{
		if (!uSurname.empty())
			boost::trim(uSurname);
		surname = uSurname;
	}
	void User::SetPhone(std::string uPhone)
	{
		if (!uPhone.empty())
			boost::trim(uPhone);
		phone = uPhone;
	}
	void User::SetAddress(std::string uAddress)
	{
		if (!uAddress.empty())
			boost::trim(uAddress);
		address = uAddress;
	}
	void User::SetRoleID(int uRoleID)
	{
		roleID = uRoleID;
	}
	void User::SetPassword(std::string uPassword)
	{
		if (!uPassword.empty())
			boost::trim(uPassword);
		password = uPassword;
	}
	void User::SetActivated(bool uActivated)
	{
		activated = uActivated;
	}

	bool User::CreateUser(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, 
		std::string uPhone,	std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uName, uSurname, uPhone, uAddress, uRoleID, errorMessage))
			return false;
		if (!IsUnique(globalVar, ormasDal, uPhone, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(uEmail, uName, uSurname, uPhone, uAddress, uPassword);
		email = uEmail;
		name = uName;
		surname = uSurname;
		phone = uPhone;
		address = uAddress;
		roleID = uRoleID;
		password = uPassword;
		activated = uActivated;
		if (0 != id && ormasDal.CreateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			CreateBalance(globalVar, ormasDal, errorMessage);
			return true;
		}
		return false;
	}
	bool User::CreateUser(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		if (!IsUnique(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (CreateBalance(globalVar, ormasDal, errorMessage))
				return true;
			return false;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool User::DeleteUser(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		Balance balance;
		Subaccount subAcc;
		if (balance.GetBalanceByUserID(globalVar, ormasDal, id, errorMessage))
		{
			
			if (subAcc.GetSubaccountByID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			{
				if (balance.DeleteBalance(globalVar, ormasDal, errorMessage) && subAcc.DeleteSubaccount(globalVar, ormasDal, errorMessage)
					&& ormasDal.DeleteUser(id, errorMessage))
				{
					Clear();
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
			}
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool User::UpdateUser(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname,
		std::string uPhone, std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string& errorMessage)
	{
		std::string prevPhone = GetCurrentPhone(globalVar, ormasDal, id, errorMessage);
		if (0 != prevPhone.compare(uPhone))
		{
			if (!IsUnique(globalVar, ormasDal, uPhone, errorMessage))
				return false;
		}
		TrimStrings(uEmail, uName, uSurname, uPhone, uAddress, uPassword);
		email = uEmail;
		name = uName;
		surname = uSurname;
		phone = uPhone;
		address = uAddress;
		roleID = uRoleID;
		password = uPassword;
		activated = uActivated;
		if (0 != id && ormasDal.UpdateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool User::UpdateUser(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::string prevPhone = GetCurrentPhone(globalVar, ormasDal, id, errorMessage);
		if (0 != prevPhone.compare(phone))
		{
			if (!IsUnique(globalVar, ormasDal, phone, errorMessage))
				return false;
		}
		if (0 != id && ormasDal.UpdateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	
	std::string User::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !email.empty() || !name.empty() || !surname.empty() || !address.empty() || !phone.empty() || !password.empty() 
			|| 0 != roleID)
		{
			return ormasDal.GetFilterForUser(id, email, name, surname, phone, address, roleID, password, activated);
		}
		return "";
	}

	std::string User::GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> userIDList)
	{
		if (userIDList.size()>0)
		{
			return ormasDal.GetINFilterForUserID(userIDList);
		}
		return "";
	}

	bool User::GetUserByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		id = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::usersViewCollection> userVector = ormasDal.GetUsers(errorMessage, filter);
		if (0 != userVector.size())
		{
			id = std::get<0>(userVector.at(0));
			email = std::get<1>(userVector.at(0));
			name = std::get<2>(userVector.at(0));
			surname = std::get<3>(userVector.at(0));
			phone = std::get<4>(userVector.at(0));
			address = std::get<5>(userVector.at(0));
			password = std::get<7>(userVector.at(0));
			activated = std::get<8>(userVector.at(0));
			roleID = std::get<9>(userVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find user with this id";
		}
		return false;
	}
	
	bool User::GetUserByCredentials(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uPhone, std::string uPassword)
	{
		std::string errorMessage = "";
		if (!uPhone.empty() && !uPassword.empty())
		{
			if (uPhone.empty())
				return false;
			if (uPassword.empty())
				return false;
			phone = uPhone;
			password = uPassword;
			std::string filter = GenerateFilter(ormasDal);
			std::vector<DataLayer::usersViewCollection> userVector = ormasDal.GetUsers(errorMessage, filter);
			if (0 != userVector.size())
			{
				id = std::get<0>(userVector.at(0));
				email = std::get<1>(userVector.at(0));
				name = std::get<2>(userVector.at(0));
				surname = std::get<3>(userVector.at(0));
				phone = std::get<4>(userVector.at(0));
				address = std::get<5>(userVector.at(0));
				password = std::get<7>(userVector.at(0));
				activated = std::get<8>(userVector.at(0));
				roleID = std::get<9>(userVector.at(0));
				return true;
			}
		}
		return false;
	}
	
	bool User::IsEmpty()
	{
		if (0 == id && email == "" && name == "" && surname == "" && phone == "" && address == "" && password == "" &&
			activated == false && 0 == roleID)
			return true;
		return false;
	}

	void User::Clear()
	{
		id = 0;
		email.clear();
		name.clear();
		surname.clear();
		phone.clear();
		address.clear();
		password.clear();
		activated = false;
		roleID = 0;
	}

	void User::TrimStrings(std::string& uEmail, std::string& uName, std::string& uSurname, std::string& uPhone,
		std::string& uAddress, std::string& uPassword)
	{
		if (!uEmail.empty())
			boost::trim(uEmail);
		if (!uName.empty())
			boost::trim(uName);
		if (!uSurname.empty())
			boost::trim(uSurname);
		if (!uPhone.empty())
			boost::trim(uPhone);
		if (!uAddress.empty())
			boost::trim(uAddress);
		if (!uPassword.empty())
			boost::trim(uPassword);
	}

	bool User::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uName, std::string uSurname, std::string uPhone,
		std::string uAddress, int uRoleID, std::string& errorMessage)
	{
		User user;
		user.Clear();
		errorMessage.clear();
		user.SetName(uName);
		user.SetSurname(uSurname);
		user.SetPhone(uPhone);
		user.SetAddress(uAddress);
		user.SetRoleID(uRoleID);
		std::string filter = user.GenerateFilter(ormasDal);
		std::vector<DataLayer::usersViewCollection> userVector = ormasDal.GetUsers(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == userVector.size())
		{
			return false;
		}
		errorMessage = "User with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool User::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		User user;
		user.Clear();
		errorMessage.clear();
		user.SetName(name);
		user.SetSurname(surname);
		user.SetPhone(phone);
		user.SetAddress(address);
		user.SetRoleID(roleID);
		std::string filter = user.GenerateFilter(ormasDal);
		std::vector<DataLayer::usersViewCollection> userVector = ormasDal.GetUsers(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == userVector.size())
		{
			return false;
		}
		errorMessage = "User with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool User::IsUnique(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uPhone, std::string& errorMessage)
	{
		User user;
		user.SetPhone(uPhone);
		std::string filter = user.GenerateFilter(ormasDal);
		std::vector<DataLayer::usersViewCollection> userVector = ormasDal.GetUsers(errorMessage, filter);
		if (!errorMessage.empty())
			return false;
		if (0 == userVector.size())
		{
			return true;
		}
		errorMessage = "User with these phone already exist";
		return false;
	}

	bool User::IsUnique(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		User user;
		user.SetPhone(phone);
		std::string filter = user.GenerateFilter(ormasDal);
		std::vector<DataLayer::usersViewCollection> userVector = ormasDal.GetUsers(errorMessage, filter);
		if (!errorMessage.empty())
			return false;
		if (0 == userVector.size())
		{
			return true;
		}
		errorMessage = "User with these phone already exist";
		return false;
	}

	bool User::CreateBalance(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Currency currency;
		std::string number = "";
		std::string genAccRawNumber = "";
		int currID = currency.GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (0 != currID)
		{
			Status status;
			if (!status.GetStatusByName(globalVar, ormasDal, "OPEN" , errorMessage))
				return false;
			if (!currency.GetCurrencyByID(globalVar, ormasDal, currID, errorMessage))
				return false;
			Subaccount subaccount;
			Account account;
			Role roleClient;
			Role rolePurveyor;
			if (roleID == roleClient.GetRoleIDByName(globalVar, ormasDal, "CLIENT", errorMessage))
			{
				account.Clear();
				if (account.GetAccountByNumber(globalVar, ormasDal,"10410",errorMessage))
					number = std::to_string(10410);
			}
			else if (roleID == rolePurveyor.GetRoleIDByName(globalVar, ormasDal, "PURVEYOR", errorMessage))
			{
				account.Clear();
				if (account.GetAccountByNumber(globalVar, ormasDal, "22010", errorMessage))
					number = std::to_string(22010);
			}
			else
			{
				account.Clear();
				if (account.GetAccountByNumber(globalVar, ormasDal, "22210", errorMessage))
					number = std::to_string(22210);
			}
			if (number.empty())
				return false;
		
			number.append(std::to_string(currency.GetCode()));
			genAccRawNumber = subaccount.GenerateRawNumber(globalVar, ormasDal, errorMessage);
			if (genAccRawNumber.empty())
				return false;
			number.append(genAccRawNumber);
			subaccount.SetParentAccountID(account.GetID());
			subaccount.SetNumber(number);
			subaccount.SetStartBalance(0.0);
			subaccount.SetCurrentBalance(0.0);
			subaccount.SetCurrencyID(currID);
			subaccount.SetStatusID(status.GetID());
			subaccount.SetOpenedDate(ormasDal.GetSystemDate());
			subaccount.SetClosedDate("");
			subaccount.SetDetails("Generated by system");

			if (!subaccount.CreateSubaccount(globalVar, ormasDal, errorMessage))
				return false;
			Balance balance;
			balance.SetUserID(id);
			balance.SetSubaccountID(subaccount.GetID());
			if (balance.CreateBalance(globalVar, ormasDal, errorMessage))
				return true;
		}
		return false;
	}

	bool User::CreateBalanceForAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		User user;
		if (!user.GetUserByID(globalVar, ormasDal, uID, errorMessage))
			return false;
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
			if (account.GetAccountByNumber(globalVar, ormasDal, "10520", errorMessage))
				number = std::to_string(10520);
			if (number.empty())
				return false;

			number.append(std::to_string(currency.GetCode()));
			genAccRawNumber = subaccount.GenerateRawNumber(globalVar, ormasDal, errorMessage);
			if (genAccRawNumber.empty())
				return false;
			number.append(genAccRawNumber);

			std::string owner;
			owner += user.GetSurname();
			owner += " ";
			owner += user.GetName();

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
			Balance balance;
			balance.SetUserID(user.GetID());
			balance.SetSubaccountID(subaccount.GetID());
			if (balance.CreateBalance(globalVar, ormasDal, errorMessage))
				return true;
		}
		return false;
	}

	bool User::CreateBalanceForBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		User user;
		if (!user.GetUserByID(globalVar, ormasDal, uID, errorMessage))
			return false;
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
			if (account.GetAccountByNumber(globalVar, ormasDal, "11620", errorMessage))
				number = std::to_string(11620);
			if (number.empty())
				return false;

			number.append(std::to_string(currency.GetCode()));
			genAccRawNumber = subaccount.GenerateRawNumber(globalVar, ormasDal, errorMessage);
			if (genAccRawNumber.empty())
				return false;
			number.append(genAccRawNumber);

			std::string owner;
			owner += user.GetSurname();
			owner += " ";
			owner += user.GetName();

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
			Balance balance;
			balance.SetUserID(user.GetID());
			balance.SetSubaccountID(subaccount.GetID());
			if (balance.CreateBalance(globalVar, ormasDal, errorMessage))
				return true;
		}
		return false;
	}

	bool User::CreateBalanceForShareholder(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		User user;
		if (!user.GetUserByID(globalVar, ormasDal, uID, errorMessage))
			return false;
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
			if (account.GetAccountByNumber(globalVar, ormasDal, "33010", errorMessage))
				number = std::to_string(33010);
			if (number.empty())
				return false;

			number.append(std::to_string(currency.GetCode()));
			genAccRawNumber = subaccount.GenerateRawNumber(globalVar, ormasDal, errorMessage);
			if (genAccRawNumber.empty())
				return false;
			number.append(genAccRawNumber);

			std::string owner;
			owner += user.GetSurname();
			owner += " ";
			owner += user.GetName();

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
			Balance balance;
			balance.SetUserID(user.GetID());
			balance.SetSubaccountID(subaccount.GetID());
			if (balance.CreateBalance(globalVar, ormasDal, errorMessage))
				return true;
		}
		return false;
	}

	int User::GetUserBalanceID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		Balance balance;
		if (balance.GetBalanceByUserID(globalVar, ormasDal, cID, errorMessage))
			return balance.GetID();
		return 0;
	}

	std::string User::GetCurrentPhone(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		User user;
		if (user.GetUserByID(globalVar, ormasDal, uID, errorMessage))
			return user.GetPhone();
		return 0;
	}
}

