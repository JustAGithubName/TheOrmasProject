#ifndef RETURNVIEWCLASS_H
#define RETURNVIEWCLASS_H

#include "ReturnClass.h"

namespace BusinessLayer
{
	class ReturnView : public Return
	{
		std::string statusCode = "";
		std::string statusName = "";
		std::string clientName = "";
		std::string clientSurname = "";
		std::string clientPhone = "";
		std::string clientAddres = "";
		std::string clientFirm = "";
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string currencyName = "";
	public:
		ReturnView(DataLayer::returnsViewCollection);
		ReturnView(){};
		~ReturnView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// ReturnView class Accessors
		std::string GetStatusCode();
		std::string GetStatusName();
		std::string GetClientName();
		std::string GetClientSurname();
		std::string GetClientPhone();
		std::string GetClientAddress();
		std::string GetClientFirm();
		std::string GetEmployeeName();
		std::string GetEmployeeSurname();
		std::string GetEmployeePhone();
		std::string GetCurrencyName();

		void SetStatusCode(std::string);
		void SetStatusName(std::string);
		void SetClientName(std::string);
		void SetClientSurname(std::string);
		void SetClientPhone(std::string);
		void SetClientAddress(std::string);
		void SetClientFirm(std::string);
		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetCurrencyName(std::string);


	};
}
#endif //RETURNVIEWCLASS