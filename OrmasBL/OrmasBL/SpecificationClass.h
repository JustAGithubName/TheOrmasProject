#ifndef SPECIFICATIONCLASS_H
#define SPECIFICATIONCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class Specification
	{
	protected:
		int id = 0;
		int productID = 0;
		double sum = 0;
		int currencyID = 0;
		int employeeID = 0;
		std::string date = "";
	public:
		Specification(int sID, int pID, double sSum, int cID, int eID, std::string sDate) : id(sID), productID(pID), sum(sSum), 
			currencyID(cID), employeeID(eID), date(sDate){};
		Specification(DataLayer::specificationsCollection);
		Specification(){};
		~Specification(){};

		//Specification class Accessors
		int GetID();
		int GetProductID();
		double GetSum();
		int GetCurrencyID();
		int GetEmployeeID();
		std::string GetDate();
		
		//Specification class Mutators
		void SetID(int);
		void SetProductID(int);
		void SetSum(double);
		void SetCurrencyID(int);
		void SetEmployeeID(int);
		void SetDate(std::string);

		//Create, delete, update methods
		bool CreateSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sSum, int cID, int eID, std::string sDate, std::string& errorMessage);
		bool UpdateSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sSum, int cID, int eID, std::string sDate, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetSpecificationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetSpecificationByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool UpdateSpecificationByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sSum, int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //SpecificationCLASS_H