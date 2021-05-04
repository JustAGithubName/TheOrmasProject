#ifndef JOBSHEETVIEWCLASS_H
#define JOBSHEETVIEWCLASS_H

#include "JobsheetClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class JobsheetView : public Jobsheet
	{
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string productName = "";
		std::string measureName = "";
	public:
		JobsheetView(DataLayer::jobsheetViewCollection);
		JobsheetView(){};
		~JobsheetView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);

		// JobsheetView class Accessors
		std::string GetEmployeeName();
		std::string GetEmployeeSurname();
		std::string GetEmployeePhone();
		std::string GetProductName();
		std::string GetMeasureName();

		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetProductName(std::string);
		void SetMeasureName(std::string);
	};
}

#endif