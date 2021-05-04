#include "stdafx.h"
#include "BorrowerViewClass.h"

namespace BusinessLayer{
	BorrowerView::BorrowerView(DataLayer::borrowersViewCollection bCollection)
	{
		id = std::get<0>(bCollection);
		userID = std::get<0>(bCollection);
		name = std::get<1>(bCollection);
		surname = std::get<2>(bCollection);
		comment = std::get<3>(bCollection);
		phone = std::get<4>(bCollection);
		address = std::get<5>(bCollection);
		roleName = std::get<6>(bCollection);
		password = std::get<7>(bCollection);
		email = std::get<8>(bCollection);
		activated = std::get<9>(bCollection);
		roleID = std::get<10>(bCollection);
	}

	std::string BorrowerView::GetRoleName()
	{
		return roleName;
	}

	void BorrowerView::SetRoleName(std::string bRoleName)
	{
		roleName=bRoleName;
	}

	std::string BorrowerView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != userID || !name.empty() || !surname.empty() || !comment.empty() || !phone.empty() || !address.empty()
			|| !roleName.empty() || !password.empty() || !email.empty() || 0 != roleID)
		{
			return ormasDal.GetFilterForBorrowersView(userID, name, surname, comment, phone, address, roleName, password, email, roleID);
		}
		return "";
	}
}