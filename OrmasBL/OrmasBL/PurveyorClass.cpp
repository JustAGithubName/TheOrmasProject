#include "stdafx.h"
#include "PurveyorClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	Purveyor::Purveyor(DataLayer::purveyorsCollection pCollection)
	{
		userID = std::get<0>(pCollection);
		companyName = std::get<1>(pCollection);
		locationID = std::get<2>(pCollection);
	}

	int Purveyor::GetUserID()
	{
		return userID;
	}
	std::string Purveyor::GetCompanyName()
	{
		return companyName;
	}
	int Purveyor::GetLocationID()
	{
		return locationID;
	}

	void Purveyor::SetUserID(int cID)
	{
		userID = cID;
		if (0 == id || id != cID)
			id = userID;
	}
	void Purveyor::SetCompanyName(std::string pCompanyName)
	{
		if (!pCompanyName.empty())
			boost::trim(pCompanyName);
		companyName = pCompanyName;
	}
	void Purveyor::SetLocationID(int cLocationID)
	{
		locationID = cLocationID;
	}

	bool Purveyor::CreatePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
		std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string pCompanyName,
		int lID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uName, uSurname, uPhone, uRoleID, pCompanyName, errorMessage))
			return false;
		if (!IsUnique(globalVar, ormasDal, uPhone, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(uEmail, uName, uSurname, uPhone, uAddress, uPassword, pCompanyName);
		userID = id;
		email = uEmail;
		name = uName;
		surname = uSurname;
		phone = uPhone;
		address = uAddress;
		roleID = uRoleID;
		password = uPassword;
		activated = uActivated;
		userID = id;
		companyName = pCompanyName;
		locationID = lID;
		if (0 != id && ormasDal.CreateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (ormasDal.CreatePurveyor(userID, companyName, locationID, errorMessage))
			{
				if (CreateBalance(globalVar, ormasDal, errorMessage))
					return true;
				return false;
			}
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Purveyor::CreatePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		if (!IsUnique(globalVar, ormasDal, phone, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		userID = id;
		if (0 != id && ormasDal.CreateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (ormasDal.CreatePurveyor(userID, companyName, locationID, errorMessage))
			{
				if (CreateBalance(globalVar, ormasDal, errorMessage))
					return true;
				return false;
			}
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Purveyor::DeletePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeletePurveyor(id, errorMessage))
		{
			User user;
			if (user.GetUserByID(globalVar, ormasDal, id, errorMessage))
			{
				if (user.DeleteUser(globalVar, ormasDal, errorMessage))
					return true;
			}
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Purveyor::UpdatePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
		std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string pCompanyName,
		int lID, std::string& errorMessage)
	{
		std::string prevPhone = GetCurrentPhone(globalVar, ormasDal, id, errorMessage);
		if (0 != prevPhone.compare(uPhone))
		{
			if (!IsUnique(globalVar, ormasDal, uPhone, errorMessage))
				return false;
		}
		TrimStrings(uEmail, uName, uSurname, uPhone, uAddress, uPassword, pCompanyName);
		email = uEmail;
		name = uName;
		surname = uSurname;
		phone = uPhone;
		address = uAddress;
		roleID = uRoleID;
		password = uPassword;
		activated = uActivated;
		userID = id;
		companyName = pCompanyName;		
		locationID = lID;
		userID = id;
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (0 != id && ormasDal.UpdateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (ormasDal.UpdatePurveyor(userID, companyName, locationID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				if (!errorMessage.empty())
				{
					return false;
				}
				return true;
			}
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Purveyor::UpdatePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::string prevPhone = GetCurrentPhone(globalVar, ormasDal, id, errorMessage);
		if (0 != prevPhone.compare(phone))
		{
			if (!IsUnique(globalVar, ormasDal, phone, errorMessage))
				return false;
		}
		//ormasDal.StartTransaction(errorMessage);
		userID = id;
		if (!errorMessage.empty())
			return false;
		if (0 != id && ormasDal.UpdateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (ormasDal.UpdatePurveyor(userID, companyName, locationID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				if (!errorMessage.empty())
				{
					return false;
				}
				return true;
			}
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	std::string Purveyor::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !surname.empty() || !address.empty() || !phone.empty() || !companyName.empty() 
			|| !password.empty() || !email.empty() || 0 != roleID || 0 != locationID)
		{
			return ormasDal.GetFilterForPurveyor(id, name, surname, phone, address, companyName, password, email, activated,
				roleID, locationID);
		}
		return "";
	}

	bool Purveyor::GetPurveyorByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		id = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::purveyorsViewCollection> purveyorVector = ormasDal.GetPurveyors(errorMessage, filter);
		if (0 != purveyorVector.size())
		{
			id = std::get<0>(purveyorVector.at(0));
			name = std::get<1>(purveyorVector.at(0));
			surname = std::get<2>(purveyorVector.at(0));
			phone = std::get<3>(purveyorVector.at(0));
			address = std::get<7>(purveyorVector.at(0));
			companyName = std::get<8>(purveyorVector.at(0));
			password = std::get<10>(purveyorVector.at(0));
			email = std::get<11>(purveyorVector.at(0));
			activated = std::get<12>(purveyorVector.at(0));
			roleID = std::get<13>(purveyorVector.at(0));
			locationID = std::get<14>(purveyorVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find purveyor with this id";
		}
		return false;
	}

	bool Purveyor::GetPurveyorByCredentials(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uPhone, std::string uEmail, std::string uPassword)
	{
		std::string errorMessage = "";
		if (!uPhone.empty())
		{
			phone = uPhone;
		}
		if (!uEmail.empty())
		{
			email = uEmail;
		}
		if (password.empty())
			return false;
		password = uPassword;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::purveyorsViewCollection> purveyorVector = ormasDal.GetPurveyors(errorMessage, filter);
		if (0 != purveyorVector.size())
		{
			id = std::get<0>(purveyorVector.at(0));
			name = std::get<1>(purveyorVector.at(0));
			surname = std::get<2>(purveyorVector.at(0));
			phone = std::get<3>(purveyorVector.at(0));
			address = std::get<7>(purveyorVector.at(0));
			companyName = std::get<8>(purveyorVector.at(0));
			password = std::get<10>(purveyorVector.at(0));
			email = std::get<11>(purveyorVector.at(0));
			activated = std::get<12>(purveyorVector.at(0));
			roleID = std::get<13>(purveyorVector.at(0));
			locationID = std::get<14>(purveyorVector.at(0));
			return true;
		}
		return false;
	}

	bool Purveyor::IsEmpty()
	{
		if (0 == id && name.empty() && surname.empty() && address.empty() && phone.empty() && companyName.empty()
			&& password.empty() && email.empty() && 0 == roleID && 0 == locationID)
			return true;
		return false;
	}

	void Purveyor::Clear()
	{
		id = 0;
		name.clear();
		surname.clear();
		address.clear();
		phone.clear();
		companyName.clear();
		password.clear();
		email.clear();
		roleID = 0;
		locationID = 0;
	}

	void Purveyor::TrimStrings(std::string& uEmail, std::string& uName, std::string& uSurname, std::string& uPhone,
		std::string& uAddress, std::string& uPassword, std::string& pCompanyName)
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
		if (!pCompanyName.empty())
			boost::trim(pCompanyName);
	}

	bool Purveyor::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uName, std::string uSurname, std::string uPhone,
		int uRoleID, std::string pCompanyName, std::string& errorMessage)
	{
		Purveyor purveyor;
		purveyor.Clear();
		errorMessage.clear();
		purveyor.SetName(uName);
		purveyor.SetSurname(uSurname);
		purveyor.SetPhone(uPhone);
		purveyor.SetRoleID(uRoleID);
		purveyor.SetCompanyName(pCompanyName);
		std::string filter = purveyor.GenerateFilter(ormasDal);
		std::vector<DataLayer::purveyorsViewCollection> purveyorVector = ormasDal.GetPurveyors(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == purveyorVector.size())
		{
			return false;
		}
		errorMessage = "Purveyor with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Purveyor::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Purveyor purveyor;
		purveyor.Clear();
		errorMessage.clear();
		purveyor.SetName(name);
		purveyor.SetSurname(surname);
		purveyor.SetPhone(phone);
		purveyor.SetRoleID(roleID);
		purveyor.SetCompanyName(companyName);
		std::string filter = purveyor.GenerateFilter(ormasDal);
		std::vector<DataLayer::purveyorsViewCollection> purveyorVector = ormasDal.GetPurveyors(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == purveyorVector.size())
		{
			return false;
		}
		errorMessage = "Purveyor with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::string Purveyor::GetCurrentPhone(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		User user;
		if (user.GetUserByID(globalVar, ormasDal, uID, errorMessage))
			return user.GetPhone();
		return 0;
	}
}