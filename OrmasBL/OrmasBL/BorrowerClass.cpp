#include "stdafx.h"
#include "BorrowerClass.h"
#include "CompanyClass.h"
#include "BranchClass.h"
#include "CompanyEmployeeRelationClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	Borrower::Borrower(DataLayer::borrowersCollection cCollection)
	{
		userID = std::get<0>(cCollection);
		comment = std::get<1>(cCollection);
	}

	int Borrower::GetUserID()
	{
		return userID;
	}
	std::string Borrower::GetComment()
	{
		return comment;
	}

	void Borrower::SetUserID(int bID)
	{
		userID = bID;
		if (0 == id || id != bID)
			id = userID;
	}
	void Borrower::SetComment(std::string bComment)
	{
		if (!bComment.empty())
			boost::trim(bComment);
		comment = bComment;
	}
	
	bool Borrower::CreateBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
		std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string bComment, std::string& errorMessage)
	{
		if (0 == id)
		{
			if (IsDuplicate(globalVar, ormasDal, uName, uSurname, uPhone, errorMessage))
				return false;
			if (!IsUnique(globalVar, ormasDal, uPhone, errorMessage))
				return false;
			id = ormasDal.GenerateID();
			TrimStrings(uEmail, uName, uSurname, uPhone, uAddress, uPassword, comment);
			userID = id;
			email = uEmail;
			name = uName;
			surname = uSurname;
			phone = uPhone;
			address = uAddress;
			roleID = uRoleID;
			password = uPassword;
			activated = uActivated;
			comment = bComment;
			if (0 != id && ormasDal.CreateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
			{
				if (ormasDal.CreateBorrower(userID, comment, errorMessage) && this->CreateCompanyEmployeeRelation(globalVar, ormasDal, errorMessage))
				{
					if (CreateBalance(globalVar, ormasDal, errorMessage) && CreateBalanceForBorrower(globalVar, ormasDal, userID, errorMessage))
						return true;
					return false;
				}
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		else
		{
			userID = id;
			comment = bComment;
			if (ormasDal.CreateBorrower(userID, comment, errorMessage))
			{
				if (CreateBalanceForBorrower(globalVar, ormasDal, userID, errorMessage))
					return true;
				return false;
			}
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
	}
	bool Borrower::CreateBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 == id)
		{
			if (IsDuplicate(globalVar, ormasDal, name, surname, phone, errorMessage))
				return false;
			if (!IsUnique(globalVar, ormasDal, phone, errorMessage))
				return false;
			id = ormasDal.GenerateID();
			userID = id;
			if (0 != id && ormasDal.CreateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
			{
				if (ormasDal.CreateBorrower(userID, comment, errorMessage) && this->CreateCompanyEmployeeRelation(globalVar, ormasDal, errorMessage))
				{
					if (CreateBalance(globalVar, ormasDal, errorMessage) && CreateBalanceForBorrower(globalVar, ormasDal, userID, errorMessage))
						return true;
					return false;
				}
				//ormasDal.CancelTransaction(errorMessage);
				return false;
			}
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
		else
		{
			userID = id;
			if (ormasDal.CreateBorrower(userID, comment, errorMessage))
			{
				if (CreateBalanceForBorrower(globalVar, ormasDal, userID, errorMessage))
					return true;
				return false;
			}
			//ormasDal.CancelTransaction(errorMessage);
			return false;
		}
	}

	bool Borrower::DeleteBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteBorrower(id, errorMessage))
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
	bool Borrower::UpdateBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
		std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string bComment, std::string& errorMessage)
	{
		std::string prevPhone = GetCurrentPhone(globalVar, ormasDal, id, errorMessage);
		if (0 != prevPhone.compare(uPhone))
		{
			if (!IsUnique(globalVar, ormasDal, uPhone, errorMessage))
				return false;
		}
		TrimStrings(uEmail, uName, uSurname, uPhone, uAddress, uPassword, comment);
		email = uEmail;
		name = uName;
		surname = uSurname;
		phone = uPhone;
		address = uAddress;
		roleID = uRoleID;
		password = uPassword;
		activated = uActivated;
		userID = id;
		comment = bComment;
		userID = id;
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (0 != id && ormasDal.UpdateUser(id, email, name, surname, phone, address, roleID, password, activated, errorMessage))
		{
			if (ormasDal.UpdateBorrower(userID, comment, errorMessage))
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
	bool Borrower::UpdateBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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
			if (ormasDal.UpdateBorrower(userID, comment, errorMessage))
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

	std::string Borrower::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !surname.empty() || !address.empty() || !phone.empty()
			|| !password.empty() || !email.empty() || !comment.empty())
		{
			return ormasDal.GetFilterForBorrower(id, name, surname, phone, address, roleID , comment);
		}
		return "";
	}

	bool Borrower::GetBorrowerByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		userID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::borrowersViewCollection> borrowerVector = ormasDal.GetBorrowers(errorMessage, filter);
		if (0 != borrowerVector.size())
		{
			userID = std::get<0>(borrowerVector.at(0));
			comment = std::get<1>(borrowerVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Borrower with this id";
		}
		return false;
	}

	bool Borrower::GetBorrowerByCredentials(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uPhone, std::string uEmail, std::string uPassword)
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
		password = uPassword;
		if (uPassword.empty())
			return false;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::borrowersViewCollection> borrowerVector = ormasDal.GetBorrowers(errorMessage, filter);
		if (0 != borrowerVector.size())
		{
			userID = std::get<0>(borrowerVector.at(0));
			comment = std::get<0>(borrowerVector.at(0));
			return true;
		}
		return false;
	}

	bool Borrower::IsEmpty()
	{
		if (0 == id && name.empty() && surname.empty() && address.empty() && phone.empty()
			&& password.empty() && email.empty() && 0 == roleID)
			return true;
		return false;
	}

	void Borrower::Clear()
	{
		id = 0;
		name.clear();
		address.clear();
		phone.clear();
		password.clear();
		email.clear();
		roleID = 0;
		comment.clear();
	}

	void Borrower::TrimStrings(std::string& uEmail, std::string& uName, std::string& uSurname, std::string& uPhone,
		std::string& uAddress, std::string& uPassword, std::string& bCommnet)
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
		if (!bCommnet.empty())
			boost::trim(bCommnet);
	}

	bool Borrower::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uName, std::string uSurname, std::string uPhone, std::string& errorMessage)
	{
		Borrower borrower;
		borrower.Clear();
		errorMessage.clear();
		borrower.SetName(uName);
		borrower.SetSurname(uSurname);
		borrower.SetPhone(uPhone);
		std::string filter = borrower.GenerateFilter(ormasDal);
		std::vector<DataLayer::borrowersViewCollection> borrowerVector = ormasDal.GetBorrowers(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == borrowerVector.size())
		{
			return false;
		}
		errorMessage = "Borrower with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Borrower::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Borrower borrower;
		borrower.Clear();
		errorMessage.clear();
		borrower.SetName(name);
		borrower.SetSurname(surname);
		borrower.SetPhone(phone);
		std::string filter = borrower.GenerateFilter(ormasDal);
		std::vector<DataLayer::borrowersViewCollection> borrowerVector = ormasDal.GetBorrowers(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == borrowerVector.size())
		{
			return false;
		}
		errorMessage = "Borrower with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::string Borrower::GetCurrentPhone(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		User user;
		if (user.GetUserByID(globalVar, ormasDal, uID, errorMessage))
			return user.GetPhone();
		return 0;
	}

	bool Borrower::CreateCompanyEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Company company;
		Branch branch;
		int branchID = 0;
		std::vector<DataLayer::branchesCollection> vecBranch = ormasDal.GetBranches(errorMessage);
		if (0 == vecBranch.size())
		{
			return false;
		}
		else
		{
			branchID = std::get<0>(vecBranch.at(0));
		}
		int companyID = company.GetCompanyID(globalVar, ormasDal, errorMessage);
		if (0 == companyID)
			return false;
		CompanyEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(id);
		ceRelation.SetCompanyID(companyID);
		ceRelation.SetBranchID(branchID);
		return ceRelation.CreateCompanyEmployeeRelation(globalVar, ormasDal, errorMessage);
	}


}