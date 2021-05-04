#ifndef WRITEOFFVIEWCLASS_H
#define WRITEOFFVIEWCLASS_H

#include "WriteOffClass.h"

namespace BusinessLayer
{
	class WriteOffView : public WriteOff
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
		WriteOffView(DataLayer::writeOffsViewCollection);
		WriteOffView(){};
		~WriteOffView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// WriteOffView class Accessors
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
		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetClientName(std::string);
		void SetClientSurname(std::string);
		void SetClientPhone(std::string);
		void SetClientAddress(std::string);
		void SetClientFirm(std::string);
		void SetCurrencyName(std::string);

	};
}
#endif //WRITEOFFVIEWCLASS_H
