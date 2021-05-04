#include "stdafx.h"
#include "EmployeeViewClass.h"

namespace BusinessLayer{
	EmployeeView::EmployeeView(DataLayer::employeesViewCollection cCollection)
	{
		id = std::get<0>(cCollection);
		name = std::get<1>(cCollection);
		surname = std::get<2>(cCollection);
		positionName = std::get<3>(cCollection);
		phone = std::get<4>(cCollection);
		address = std::get<5>(cCollection);
		birthDate = std::get<6>(cCollection);
		roleName = std::get<7>(cCollection);
		hireDate = std::get<8>(cCollection);
		password = std::get<9>(cCollection);
		email = std::get<10>(cCollection);
		activated = std::get<11>(cCollection);
		roleID = std::get<12>(cCollection);
		positionID = std::get<13>(cCollection);
		divisionEmployeeID = std::get<14>(cCollection);
		divisionID = std::get<15>(cCollection);
		isContract = std::get<16>(cCollection);
	}

	std::string EmployeeView::GetPositionName()
	{
		return positionName;
	}
	std::string EmployeeView::GetRoleName()
	{
		return roleName;
	}

	int EmployeeView::GetDivisionEmployeeID()
	{
		return divisionEmployeeID;
	}

	int EmployeeView::GetDivisionID()
	{
		return divisionID;
	}

	bool EmployeeView::GetIsContract()
	{
		return isContract;
	}

	void EmployeeView::SetPositionName(std::string ePositionName)
	{
		positionName = ePositionName;
	}
	void EmployeeView::SetRoleName(std::string eRoleNamee)
	{
		roleName = eRoleNamee;
	}

	void EmployeeView::SetDivisionEmployeeID(int eDivisionEmployeeID)
	{
		divisionEmployeeID = eDivisionEmployeeID;
	}

	void EmployeeView::SetDivisionID(int eDivisionID)
	{
		divisionID = eDivisionID;
	}

	std::string EmployeeView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !surname.empty() || !positionName.empty() || !phone.empty() || !address.empty() || !birthDate.empty() || !roleName.empty() 
			|| !hireDate.empty() || !password.empty() || !email.empty() || 0 != roleID || 0 != positionID || 0 != divisionEmployeeID || 0 != divisionID)
		{
			return ormasDal.GetFilterForEmployeeView(id, name, surname, positionName, phone, address, birthDate, roleName, hireDate, password, email, 
				roleID, positionID, divisionID);
		}
		return "";
	}
}