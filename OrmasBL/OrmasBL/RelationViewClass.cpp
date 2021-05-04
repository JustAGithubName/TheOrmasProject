#include "stdafx.h"
#include "RelationViewClass.h"

namespace BusinessLayer
{
	RelationView::RelationView(DataLayer::relationsViewCollection rCollection)
	{
		id = std::get<0>(rCollection);
		employeeName = std::get<1>(rCollection);
		employeeSurname = std::get<2>(rCollection);
		employeePhone = std::get<3>(rCollection);
		relationName = std::get<4>(rCollection);
		userName = std::get<5>(rCollection);
		userSurname = std::get<6>(rCollection);
		userPhone = std::get<7>(rCollection);
		user1ID = std::get<8>(rCollection);
		user2ID = std::get<9>(rCollection);
		relationTypeID = std::get<10>(rCollection);
	}

	std::string RelationView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string RelationView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string RelationView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string RelationView::GetRelationName()
	{
		return relationName;
	}
	std::string RelationView::GetUsername()
	{
		return userName;
	}
	std::string RelationView::GetUserSurname()
	{
		return userSurname;
	}
	std::string RelationView::GetUserPhone()
	{
		return userPhone;
	}

	void RelationView::SetEmployeeName(std::string rEmployeeName)
	{
		employeeName = rEmployeeName;
	}
	void RelationView::SetEmployeeSurname(std::string rEmployeeSurname)
	{
		employeeSurname = rEmployeeSurname;
	}
	void RelationView::SetEmployeePhone(std::string rEemployeePhone)
	{
		employeePhone = rEemployeePhone;
	}
	void RelationView::SetRelationName(std::string rRelationName)
	{
		relationName = rRelationName;
	}
	void RelationView::SetUsername(std::string rUserName)
	{
		userName = rUserName;
	}
	void RelationView::SetUserSurname(std::string rUserSurname)
	{
		userSurname = rUserSurname;
	}
	void RelationView::SetUserPhone(std::string rUserPhone)
	{
		userPhone = rUserPhone;
	}

	std::string RelationView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !employeeName.empty() || !employeeSurname.empty() || !employeePhone.empty() || !relationName.empty() || !userName.empty()
			|| !userSurname.empty() || !userPhone.empty()  || 0 != user1ID || 0 != user2ID || 0 != relationTypeID)
		{
			return ormasDal.GetFilterForRelationView(id, employeeName, employeeSurname, employeePhone, relationName, userName, userSurname, userPhone, user1ID, user2ID, relationTypeID);
		}
		return "";
	}

}

