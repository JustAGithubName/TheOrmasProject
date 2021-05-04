#include "stdafx.h"
#include "ClientClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	Client::Client(DataLayer::clientsCollection cCollection)
	{
		userID = std::get<0>(cCollection);
		firm = std::get<1>(cCollection);
		firmNumber = std::get<2>(cCollection);
		locationID = std::get<3>(cCollection);
	}
	
	int Client::GetUserID()
	{
		return userID;
	}
	std::string Client::GetFirm()
	{
		return firm;
	}
	std::string Client::GetFirmNumber()
	{
		return firmNumber;
	}
	int Client::GetLocationID()
	{
		return locationID;
	}

	void Client::SetUserID(int cID)
	{
		userID = cID;
		if (0 == id || id != cID)
			id = userID;
	}
	void Client::SetFirm(std::string cFirm)
	{
		if (!cFirm.empty())
			boost::trim(cFirm);
		firm = cFirm;
	}
	void Client::SetFirmNumber(std::string cFirmNumber)
	{
		if (!cFirmNumber.empty())
			boost::trim(cFirmNumber);
		firmNumber = cFirmNumber;
	}
	void Client::SetLocationID(int cLocationID)
	{
		locationID = cLocationID;
	}

	bool Client::CreateClient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
		std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string cFirm, std::string cFirmNumber,
		int lID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uName, uSurname, uPhone, uRoleID, cFirm, errorMessage))
			return false;
		if (!IsUnique(globalVar, ormasDal, uPhone, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(uEmail, uName, uSurname, uPhone, uAddress, uPassword, cFirm, cFirmNumber);
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
		firm = cFirm;
		firmNumber = cFirmNumber;
		locationID = lID;
		if (0 != id && ormasDal.CreateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (ormasDal.CreateClient(userID, firm, firmNumber, locationID, errorMessage))
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
	bool Client::CreateClient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		if (!IsUnique(globalVar, ormasDal, phone, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		userID = id;
		if (0 != id && ormasDal.CreateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (ormasDal.CreateClient(userID, firm, firmNumber, locationID, errorMessage))
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
	bool Client::DeleteClient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteClient(id, errorMessage))
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
	bool Client::UpdateClient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
		std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string cFirm, std::string cFirmNumber,
		int lID, std::string& errorMessage)
	{
		std::string prevPhone = GetCurrentPhone(globalVar, ormasDal, id, errorMessage);
		if (0 != prevPhone.compare(uPhone))
		{
			if (!IsUnique(globalVar, ormasDal, uPhone, errorMessage))
				return false;
		}
		TrimStrings(uEmail, uName, uSurname, uPhone, uAddress, uPassword, cFirm, cFirmNumber);
		email = uEmail;
		name = uName;
		surname = uSurname;
		phone = uPhone;
		address = uAddress;
		roleID = uRoleID;
		password = uPassword;
		activated = uActivated;
		userID = id;
		firm = cFirm;
		firmNumber = cFirmNumber;
		locationID = lID;
		userID = id;
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (0 != id && ormasDal.UpdateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (ormasDal.UpdateClient(userID, firm, firmNumber, locationID, errorMessage))
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
	bool Client::UpdateClient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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
			if (ormasDal.UpdateClient(userID, firm, firmNumber, locationID, errorMessage))
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
	std::string Client::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !surname.empty() || !address.empty() || !phone.empty() || !firm.empty() || !firmNumber.empty() 
			|| !password.empty() || !email.empty() || 0 != roleID || 0!= locationID)
		{
			return ormasDal.GetFilterForClient(id, name, surname, phone, address, firm, firmNumber, password, email, activated,
				roleID, locationID);
		}
		return "";
	}

	bool Client::GetClientByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		id = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::clientsViewCollection> clientVector = ormasDal.GetClients(errorMessage, filter);
		if (0 != clientVector.size())
		{
			id = std::get<0>(clientVector.at(0));
			name = std::get<1>(clientVector.at(0));
			surname = std::get<2>(clientVector.at(0));
			phone = std::get<3>(clientVector.at(0));
			address = std::get<7>(clientVector.at(0));
			firm = std::get<8>(clientVector.at(0));
			firmNumber = std::get<9>(clientVector.at(0));
			password = std::get<11>(clientVector.at(0));
			email = std::get<12>(clientVector.at(0));
			activated = std::get<13>(clientVector.at(0));
			roleID = std::get<14>(clientVector.at(0));
			locationID = std::get<15>(clientVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find client with this id";
		}
		return false;
	}

	bool Client::GetClientByCredentials(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uPhone, std::string uEmail, std::string uPassword)
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
		if (uPassword.empty())
			return false;
		password = uPassword;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::clientsViewCollection> clientVector = ormasDal.GetClients(errorMessage, filter);
		if (0 != clientVector.size())
		{
			id = std::get<0>(clientVector.at(0));
			name = std::get<1>(clientVector.at(0));
			surname = std::get<2>(clientVector.at(0));
			phone = std::get<3>(clientVector.at(0));
			address = std::get<7>(clientVector.at(0));
			firm = std::get<8>(clientVector.at(0));
			firmNumber = std::get<9>(clientVector.at(0));
			password = std::get<11>(clientVector.at(0));
			email = std::get<12>(clientVector.at(0));
			activated = std::get<13>(clientVector.at(0));
			roleID = std::get<14>(clientVector.at(0));
			locationID = std::get<15>(clientVector.at(0));
			return true;
		}
		return false;
	}

	bool Client::IsEmpty()
	{
		if (0 == id && name.empty() && surname.empty() && address.empty() && phone.empty() && firm.empty() && firmNumber.empty()
			&& password.empty() && email.empty() && 0 == roleID && 0 == locationID)
			return true;
		return false;
	}

	void Client::Clear()
	{
		id = 0;
		name.clear();
		surname.clear();
		address.clear();
		phone.clear();
		firm.clear();
		firmNumber.clear();
		password.clear();
		email.clear();
		roleID = 0;
		locationID = 0;
	}

	void Client::TrimStrings(std::string& uEmail, std::string& uName, std::string& uSurname, std::string& uPhone,
		std::string& uAddress, std::string& uPassword, std::string& cFirm, std::string& cFirmNumber)
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
		if (!cFirm.empty())
			boost::trim(cFirm);
		if (!cFirmNumber.empty())
			boost::trim(cFirmNumber);
	}

	bool Client::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uName, std::string uSurname, std::string uPhone,
		int uRoleID, std::string cFirm, std::string& errorMessage)
	{
		Client client;
		client.Clear();
		errorMessage.clear();
		client.SetName(uName);
		client.SetSurname(uSurname);
		client.SetPhone(uPhone);
		client.SetRoleID(uRoleID);
		client.SetFirm(cFirm);
		std::string filter = client.GenerateFilter(ormasDal);
		std::vector<DataLayer::clientsViewCollection> clientVector = ormasDal.GetClients(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == clientVector.size())
		{
			return false;
		}
		errorMessage = "Client with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Client::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Client client;
		client.Clear();
		errorMessage.clear();
		client.SetName(name);
		client.SetSurname(surname);
		client.SetPhone(phone);
		client.SetRoleID(roleID);
		client.SetFirm(firm);
		std::string filter = client.GenerateFilter(ormasDal);
		std::vector<DataLayer::clientsViewCollection> clientVector = ormasDal.GetClients(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == clientVector.size())
		{
			return false;
		}
		errorMessage = "Client with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::string Client::GetCurrentPhone(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		User user;
		if (user.GetUserByID(globalVar, ormasDal, uID, errorMessage))
			return user.GetPhone();
		return 0;
	}
}