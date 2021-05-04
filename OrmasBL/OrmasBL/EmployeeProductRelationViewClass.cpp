#include "stdafx.h"
#include "EmployeeProductRelationViewClass.h"

namespace BusinessLayer{
	EmployeeProductRelationView::EmployeeProductRelationView(DataLayer::employeeProductViewCollection wCollection)
	{
		id = std::get<0>(wCollection);
		userName = std::get<1>(wCollection);
		userSurname = std::get<2>(wCollection);
		userPhone = std::get<3>(wCollection);
		productName = std::get<4>(wCollection);
		price = std::get<5>(wCollection);
		employeeID = std::get<6>(wCollection);
		productID = std::get<7>(wCollection);
	}

	std::string EmployeeProductRelationView::GetUsername()
	{
		return userName;
	}
	std::string EmployeeProductRelationView::GetUserSurname()
	{
		return userSurname;
	}
	std::string EmployeeProductRelationView::GetUserPhone()
	{
		return userPhone;
	}
	std::string EmployeeProductRelationView::GetProductName()
	{
		return productName;
	}
	double EmployeeProductRelationView::GetPrice()
	{
		return price;
	}

	void EmployeeProductRelationView::SetUsername(std::string eUserName)
	{
		userName = eUserName;
	}
	void EmployeeProductRelationView::SetUserSurname(std::string eUserSurname )
	{
		userSurname = eUserSurname;
	}
	void EmployeeProductRelationView::SetUserPhone(std::string eUserPhone)
	{
		userPhone = eUserPhone;
	}
	void EmployeeProductRelationView::SetProductName(std::string eProductName)
	{
		productName = eProductName;
	}
	void EmployeeProductRelationView::SetPrice(double ePrice)
	{
		price = ePrice;
	}

	std::string EmployeeProductRelationView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !userName.empty() || !userSurname.empty() || !userPhone.empty() || !productName.empty() || 0 != price || 0 != employeeID || 0 != productID)
		{
			return ormasDal.GetFilterForEmpProductView(id, userName, userSurname, userPhone, productName, price, employeeID, productID);
		}
		return "";
	}
}