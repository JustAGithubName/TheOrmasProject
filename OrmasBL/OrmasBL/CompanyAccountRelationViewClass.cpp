#include "stdafx.h"
#include "CompanyAccountRelationViewClass.h"

namespace BusinessLayer{
	CompanyAccountRelationView::CompanyAccountRelationView(DataLayer::companyAccountViewCollection aCollection)
	{
		id = std::get<0>(aCollection);
		companyName = std::get<1>(aCollection);
		accountNumber = std::get<2>(aCollection);
		companyID = std::get<3>(aCollection);
		accountID = std::get<4>(aCollection);
	}

	std::string CompanyAccountRelationView::GetCompanyName()
	{
		return companyName;
	}
	std::string CompanyAccountRelationView::GetAccountNumber()
	{
		return accountNumber;
	}

	void CompanyAccountRelationView::SetCompanyName(std::string cCompanyName)
	{
		companyName = cCompanyName;
	}
	void CompanyAccountRelationView::SetAccountNumber(std::string cAccountNumber)
	{
		accountNumber = cAccountNumber;
	}

	std::string CompanyAccountRelationView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != companyID || 0 != accountID)
		{
			return ormasDal.GetFilterForCompanyAccountView(id, companyName, accountNumber, companyID, accountID);
		}
		return "";
	}
}