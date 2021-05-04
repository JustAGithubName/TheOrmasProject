#ifndef JOBSHEETCLASS_H
#define JOBSHEETCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Jobsheet{
	protected:
		int id = 0;
		std::string date = "";
		double count = 0.0;
		int productID = 0;
		int employeeID = 0;
	public:
		Jobsheet();
		Jobsheet(int jID, std::string jDate, double jCount, int pID, int eID) :id(jID), date(jDate), count(jCount), productID(jID),
		employeeID(eID){};
		Jobsheet(DataLayer::jobsheetCollection);
		~Jobsheet(){};

		std::string errorMessage = "";
		//Jobsheet class Jobsheetors
		int GetID();
		std::string GetDate();
		double GetCount();
		int GetProductID();
		int GetEmployeeID();

		//Jobsheet class Mutators
		void SetID(int);
		void SetDate(std::string);
		void SetCount(double);
		void SetProductID(int);
		void SetEmployeeID(int);

		// Create, delete and update Jobsheet
		bool CreateJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string jDate, double jCount, int pID, int eID, std::string& errorMessage);
		bool UpdateJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string jDate, double jCount, int pID, int eID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate);
		bool GetJobsheetByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int jID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string jDate, double jCount, int pID, int eID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //JOBSHEETCLASS_H