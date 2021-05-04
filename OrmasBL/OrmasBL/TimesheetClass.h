#ifndef TimesheetCLASS_H
#define TimesheetCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Timesheet{
	protected:
		int id = 0;
		int salaryID = 0;
		double workedTime = 0.0;
		std::string date = "";
	public:
		Timesheet();
		Timesheet(int tID, int sID, std::string tDate, double pWorkedTime) :id(tID), salaryID(sID), date(tDate),
			workedTime(pWorkedTime){};
		Timesheet(DataLayer::timesheetCollection);
		~Timesheet(){};

		std::string errorMessage = "";
		//Timesheet class Timesheetors
		int GetID();
		int GetSalaryID();
		double GetWorkedTime();
		std::string GetDate();

		//Timesheet class Mutators
		void SetID(int);
		void SetSalaryID(int);
		void SetWorkedTime(double);
		void SetDate(std::string);
		
		// Create, delete and update Timesheet
		bool CreateTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double tWorkedTime, std::string tDate, std::string& errorMessage);
		bool UpdateTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double tWorkedTime, std::string tDate, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string tilDate);
		bool GetTimesheetByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double tWorkedTime, std::string tDate, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif