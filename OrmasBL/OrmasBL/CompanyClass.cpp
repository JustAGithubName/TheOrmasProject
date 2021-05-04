#include "stdafx.h"
#include "CompanyClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	Company::Company(DataLayer::companiesCollection compCollection)
	{
		id = std::get<0>(compCollection);
		name = std::get<1>(compCollection);
		address = std::get<2>(compCollection);
		phone = std::get<3>(compCollection);
		comment = std::get<4>(compCollection);
	}
	Company::Company()
	{
		name = "";
		address = "";
		phone = "";
		comment = "";
	}
	int Company::GetID()
	{
		return id;
	}

	std::string Company::GetName()
	{
		return name;
	}

	std::string Company::GetAddress()
	{
		return address;
	}

	std::string Company::GetPhone()
	{
		return phone;
	}

	std::string Company::GetComment()
	{
		return comment;
	}

	void Company::SetID(int cID)
	{
		id = cID;
	}
	void Company::SetName(std::string cName)
	{
		if (!cName.empty())
			boost::trim(cName);
		name = cName;
	}
	void Company::SetPhone(std::string cPhone)
	{
		if (!cPhone.empty())
			boost::trim(cPhone);
		phone = cPhone;
	}
	void Company::SetAddress(std::string cAddress)
	{
		if (!cAddress.empty())
			boost::trim(cAddress);
		address = cAddress;
	}
	void Company::SetComment(std::string cComment)
	{
		comment = cComment;
	}

	bool Company::CreateCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone,
		std::string cComment, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, cName, cAddress, cPhone, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(cName, cAddress, cPhone);
		name = cName;
		address = cAddress;
		phone = cPhone;
		comment = cComment;
		if (0 != id && ormasDal.CreateCompany(id, name, address, phone, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Company::CreateCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateCompany(id, name, address, phone, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Company::DeleteCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteCompany(id, errorMessage))
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

	bool Company::UpdateCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone
		, std::string cComment, std::string& errorMessage)
	{
		TrimStrings(cName, cAddress, cPhone);
		name = cName;
		address = cAddress;
		phone = cPhone;
		comment = cComment;
		if (0 != id && ormasDal.UpdateCompany(id, name, address, phone, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Company::UpdateCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateCompany(id, name, address, phone, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Company::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !address.empty() || !phone.empty() || !comment.empty())
		{
			return ormasDal.GetFilterForCompany(id, name, address, phone, comment);
		}
		return "";
	}

	bool Company::GetCompanyByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::companiesCollection> companyVector = ormasDal.GetCompanies(errorMessage, filter);
		if (0 != companyVector.size())
		{
			id = std::get<0>(companyVector.at(0));
			name = std::get<1>(companyVector.at(0));
			address = std::get<2>(companyVector.at(0));
			phone = std::get<3>(companyVector.at(0));
			comment = std::get<4>(companyVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find company with this id";
		}
		return false;
	}

	int Company::GetCompanyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::string filter = this->GenerateFilter(ormasDal);
		std::vector<DataLayer::companiesCollection> companyVector = ormasDal.GetCompanies(errorMessage, filter);
		if (0 != companyVector.size())
		{
			return std::get<0>(companyVector.at(0));
		}
		else
		{
			errorMessage = "Cannot find company with this id";
		}
		return 0;
	}

	bool Company::IsEmpty()
	{
		if (0 == id && name == "" && address == "" && phone == "" && comment == "")
			return true;
		return false;
	}

	void Company::Clear()
	{
		id = 0;
		name.clear();
		address.clear();
		phone.clear();
		comment.clear();
	}

	void Company::TrimStrings(std::string& cName, std::string& cAddress, std::string& cPhone)
	{
		if (!cName.empty())
			boost::trim(cName);
		if (!cAddress.empty())
			boost::trim(cAddress);
		if (!cPhone.empty())
			boost::trim(cPhone);
	}

	bool Company::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, std::string& errorMessage)
	{
		Company company;
		company.Clear();
		errorMessage.clear();
		company.SetName(cName);
		company.SetAddress(cAddress);
		company.SetPhone(cPhone);
		std::string filter = company.GenerateFilter(ormasDal);
		std::vector<DataLayer::companiesCollection> companyVector = ormasDal.GetCompanies(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == companyVector.size())
		{
			return false;
		}
		errorMessage = "Company with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Company::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Company company;
		company.Clear();
		errorMessage.clear();
		company.SetName(name);
		company.SetAddress(address);
		company.SetPhone(phone);
		std::string filter = company.GenerateFilter(ormasDal);
		std::vector<DataLayer::companiesCollection> companyVector = ormasDal.GetCompanies(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == companyVector.size())
		{
			return false;
		}
		errorMessage = "Company with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

