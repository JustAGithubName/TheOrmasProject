#ifndef StockTransferVIEWCLASS_H
#define StockTransferVIEWCLASS_H

#include "StockTransferClass.h"

namespace BusinessLayer
{
	class StockTransferView : public StockTransfer
	{
		std::string statusCode = "";
		std::string statusName = "";
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string employeePosition = "";
		std::string stockEmployeeName = "";
		std::string stockEmployeeSurname = "";
		std::string stockEmployeePhone = "";
		std::string stockEmployeePosition = "";
		std::string currencyName = "";
	public:
		StockTransferView(DataLayer::stockTransferViewCollection);
		StockTransferView(){};
		~StockTransferView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);

		// OrderView class Accessors
		std::string GetStatusCode();
		std::string GetStatusName();
		std::string GetEmployeeName();
		std::string GetEmployeeSurname();
		std::string GetEmployeePhone();
		std::string GetEmployeePosition();
		std::string GetStockEmployeeName();
		std::string GetStockEmployeeSurname();
		std::string GetStockEmployeePhone();
		std::string GetStockEmployeePosition();
		std::string GetCurrencyName();

		void SetStatusCode(std::string);
		void SetStatusName(std::string);
		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetEmployeePosition(std::string);
		void SetStockEmployeeName(std::string);
		void SetStockEmployeeSurname(std::string);
		void SetStockEmployeePhone(std::string);
		void SetStockEmployeePosition(std::string);
		void SetCurrencyName(std::string);

	};
}
#endif //StockTransferVIEWCLASS_H
