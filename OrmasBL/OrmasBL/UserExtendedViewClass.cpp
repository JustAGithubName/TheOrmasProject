#include "stdafx.h"
#include "UserExtendedViewClass.h"

namespace BusinessLayer
{
	UserExtendedView::UserExtendedView(DataLayer::userExtendedViewCollection uCollection)
	{
		id = std::get<0>(uCollection);
		name = std::get<1>(uCollection);
		surname = std::get<2>(uCollection);
		phone = std::get<3>(uCollection);
		address = std::get<4>(uCollection);
		companyName = std::get<5>(uCollection);
		branchName = std::get<6>(uCollection);
		roleName = std::get<7>(uCollection);	
		subaccountNumber = std::get<8>(uCollection);
		roleID = std::get<9>(uCollection);
		subaccountID = std::get<10>(uCollection);
		accountID = std::get<11>(uCollection);
		companyID = std::get<12>(uCollection);
		branchID = std::get<13>(uCollection);
	}

	std::string UserExtendedView::GetCompanyName()
	{
		return companyName;
	}
	std::string UserExtendedView::GetBranchName()
	{
		return branchName;
	}
	std::string UserExtendedView::GetRoleName()
	{
		return roleName;
	}
	std::string UserExtendedView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}
	int UserExtendedView::GetAccountID()
	{
		return accountID;
	}
	int UserExtendedView::GetSubaccountID()
	{
		return subaccountID;
	}
	int UserExtendedView::GetCompanyID()
	{
		return companyID;
	}
	int UserExtendedView::GetBranchID()
	{
		return branchID;
	}

	void UserExtendedView::SetCompanyName(std::string aCompanyName)
	{
		companyName = aCompanyName;
	}
	void UserExtendedView::SetBranchName(std::string aBranchName)
	{
		branchName = aBranchName;
	}
	void UserExtendedView::SetRoleName(std::string aRoleName)
	{
		roleName = aRoleName;
	}
	void UserExtendedView::SetSubaccountNumber(std::string aSubaccountNumber)
	{
		subaccountNumber = aSubaccountNumber;
	}
	void UserExtendedView::SetAccountID(int aAccountID)
	{
		accountID = aAccountID;
	}
	void UserExtendedView::SetSubaccountID(int aSubaccountID)
	{
		subaccountID = aSubaccountID;
	}
	void UserExtendedView::SetCompanyID(int aCompanyID)
	{
		companyID = aCompanyID;
	}
	void UserExtendedView::SetBranchID(int cBranchID)
	{
		branchID = cBranchID;
	}

	std::string UserExtendedView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !surname.empty() || !phone.empty() || !address.empty() || !companyName.empty() || !branchName.empty() || !roleName.empty()
			|| !subaccountNumber.empty() || 0 != roleID || 0 != subaccountID || 0 != accountID || 0 != companyID || 0 != branchID)
		{
			return ormasDal.GetFilterForUserExtendedView(id, name, surname, phone, address, companyName, branchName, roleName, subaccountNumber, roleID,
				subaccountID, accountID, companyID, branchID);
		}
		return "";
	}
}