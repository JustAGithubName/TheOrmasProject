#include "stdafx.h"
#include "BranchClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	Branch::Branch(DataLayer::branchesCollection bCollection)
	{
		id = std::get<0>(bCollection);
		name = std::get<1>(bCollection);
		address = std::get<2>(bCollection);
		phone = std::get<3>(bCollection);
		comment = std::get<4>(bCollection);
	}
	Branch::Branch()
	{
		name = "";
		address = "";
		phone = "";
		comment = "";
	}
	int Branch::GetID()
	{
		return id;
	}

	std::string Branch::GetName()
	{
		return name;
	}

	std::string Branch::GetAddress()
	{
		return address;
	}

	std::string Branch::GetPhone()
	{
		return phone;
	}

	std::string Branch::GetComment()
	{
		return comment;
	}

	void Branch::SetID(int cID)
	{
		id = cID;
	}
	void Branch::SetName(std::string cName)
	{
		if (!cName.empty())
			boost::trim(cName);
		name = cName;
	}
	void Branch::SetPhone(std::string cPhone)
	{
		if (!cPhone.empty())
			boost::trim(cPhone);
		phone = cPhone;
	}
	void Branch::SetAddress(std::string cAddress)
	{
		if (!cAddress.empty())
			boost::trim(cAddress);
		address = cAddress;
	}
	void Branch::SetComment(std::string cComment)
	{
		comment = cComment;
	}

	bool Branch::CreateBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone,
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
		if (0 != id && ormasDal.CreateBranch(id, name, address, phone, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Branch::CreateBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateBranch(id, name, address, phone, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Branch::DeleteBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteBranch(id, errorMessage))
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

	bool Branch::UpdateBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone
		, std::string cComment, std::string& errorMessage)
	{
		TrimStrings(cName, cAddress, cPhone);
		name = cName;
		address = cAddress;
		phone = cPhone;
		comment = cComment;
		if (0 != id && ormasDal.UpdateBranch(id, name, address, phone, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Branch::UpdateBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateBranch(id, name, address, phone, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Branch::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !address.empty() || !phone.empty() || !comment.empty())
		{
			return ormasDal.GetFilterForBranch(id, name, address, phone, comment);
		}
		return "";
	}

	bool Branch::GetBranchByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::branchesCollection> branchVector = ormasDal.GetBranches(errorMessage, filter);
		if (0 != branchVector.size())
		{
			id = std::get<0>(branchVector.at(0));
			name = std::get<1>(branchVector.at(0));
			address = std::get<2>(branchVector.at(0));
			phone = std::get<3>(branchVector.at(0));
			comment = std::get<4>(branchVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Branch with this id";
		}
		return false;
	}

	int Branch::GetBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::string filter = this->GenerateFilter(ormasDal);
		std::vector<DataLayer::branchesCollection> branchVector = ormasDal.GetBranches(errorMessage, filter);
		if (0 != branchVector.size())
		{
			return std::get<0>(branchVector.at(0));
		}
		else
		{
			errorMessage = "Cannot find Branch with this id";
		}
		return 0;
	}

	bool Branch::IsEmpty()
	{
		if (0 == id && name == "" && address == "" && phone == "" && comment == "")
			return true;
		return false;
	}

	void Branch::Clear()
	{
		id = 0;
		name.clear();
		address.clear();
		phone.clear();
		comment.clear();
	}

	void Branch::TrimStrings(std::string& cName, std::string& cAddress, std::string& cPhone)
	{
		if (!cName.empty())
			boost::trim(cName);
		if (!cAddress.empty())
			boost::trim(cAddress);
		if (!cPhone.empty())
			boost::trim(cPhone);
	}

	bool Branch::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, std::string& errorMessage)
	{
		Branch branch;
		branch.Clear();
		errorMessage.clear();
		branch.SetName(cName);
		branch.SetAddress(cAddress);
		branch.SetPhone(cPhone);
		std::string filter = branch.GenerateFilter(ormasDal);
		std::vector<DataLayer::branchesCollection> branchVector = ormasDal.GetBranches(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == branchVector.size())
		{
			return false;
		}
		errorMessage = "Branch with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Branch::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Branch branch;
		branch.Clear();
		errorMessage.clear();
		branch.SetName(name);
		branch.SetAddress(address);
		branch.SetPhone(phone);
		std::string filter = branch.GenerateFilter(ormasDal);
		std::vector<DataLayer::branchesCollection> branchVector = ormasDal.GetBranches(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == branchVector.size())
		{
			return false;
		}
		errorMessage = "Branch with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

