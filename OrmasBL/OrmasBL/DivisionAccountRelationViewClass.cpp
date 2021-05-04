#include "stdafx.h"
#include "DivisionAccountRelationViewClass.h"

namespace BusinessLayer{
	DivisionAccountRelationView::DivisionAccountRelationView(DataLayer::divisionAccountViewCollection dCollection)
	{
		id = std::get<0>(dCollection);
		divisionName = std::get<1>(dCollection);
		accountNumber = std::get<2>(dCollection);
		accountName = std::get<3>(dCollection);
		code = std::get<4>(dCollection);
		divisionID = std::get<5>(dCollection);
		accountID = std::get<6>(dCollection);
	}

	std::string DivisionAccountRelationView::GetDivisionName()
	{
		return divisionName;
	}

	std::string DivisionAccountRelationView::GetAccountNumber()
	{
		return accountNumber;
	}

	std::string DivisionAccountRelationView::GetAccountName()
	{
		return accountName;
	}

	void DivisionAccountRelationView::SetDivisionName(std::string dDivisionName)
	{
		divisionName = dDivisionName;
	}

	void DivisionAccountRelationView::SetAccountNumber(std::string dAccountNumber)
	{
		accountNumber = dAccountNumber;
	}

	void DivisionAccountRelationView::SetAccountName(std::string dAccountName)
	{
		accountName = dAccountName;
	}

	std::string DivisionAccountRelationView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{

		if (0 != id || !divisionName.empty() || !accountNumber.empty() || !accountName.empty() || !code.empty() || 0 != divisionID || 0 != accountID )
		{
			return ormasDal.GetFilterForDivisionAccountView(id, divisionName, accountNumber, accountName, code, divisionID, accountID);
		}
		return "";
	}
}