#ifndef CONSUMEOTHERSTOCKSVIEWCLASS_H
#define CONSUMEOTHERSTOCKSVIEWCLASS_H

#include "ConsumeOtherStocksClass.h"

namespace BusinessLayer
{
	class ConsumeOtherStocksView : public ConsumeOtherStocks
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
		ConsumeOtherStocksView(DataLayer::consumeOtherStocksViewCollection);
		ConsumeOtherStocksView(){};
		~ConsumeOtherStocksView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;
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
#endif //CONSUMEOtherStocksVIEWCLASS_H
