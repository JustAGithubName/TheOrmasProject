#ifndef CASHBOXEMPLOYEERELATIONVIEWCLASS_H
#define CASHBOXEMPLOYEERELATIONVIEWCLASS_H

#include "CashboxEmployeeRelationClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class CashboxEmployeeRelationView : public CashboxEmployeeRelation
	{
		std::string subaccountNumber = "";
		std::string cashboxAddress = "";
		std::string userName = "";
		std::string userSurname = "";
		std::string userPhone = "";
		std::string roleName = "";
	public:
		CashboxEmployeeRelationView(DataLayer::cashboxEmployeeViewCollection);
		CashboxEmployeeRelationView(){};
		~CashboxEmployeeRelationView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// CashboxEmployeeRelationView class CashboxEmployeeRelationors
		std::string GetSubaccountNumber();
		std::string GetCashboxAddress();
		std::string GetUsername();
		std::string GetUserSurname();
		std::string GetUserPhone();
		std::string GetRoleName();

		void SetSubaccountNumber(std::string);
		void SetCashboxAddress(std::string);
		void SetUsername(std::string);
		void SetUserSurname(std::string);
		void SetUserPhone(std::string);
		void SetRoleName(std::string);
	};
}
#endif