#ifndef TaxCLASS_H
#define TaxCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Tax{
	protected:
		int id = 0;
		std::string name = "";
		std::string code = "";
		double fixedValue = 0.0;
		int percentValue = 0;
		std::string formulaValue = "";
	public:
		Tax();
		Tax(int tID, std::string tName, std::string tCode, double tFixedValue, int tPercentValue,
			std::string tFormulaValue) :id(tID), name(tName), code(tCode),
			fixedValue(tFixedValue), percentValue(tPercentValue), formulaValue(tFormulaValue){};
		Tax(DataLayer::taxesCollection);
		~Tax(){};

		std::string errorMessage = "";

		//Tax class Accessors
		int GetID();
		std::string GetName();
		std::string GetCode();
		double GetFixedValue();
		int GetPercentValue();
		std::string GetFormulaValue();
	

		//Tax class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetCode(std::string);
		void SetFixedValue(double);
		void SetPercentValue(int);
		void SetFormulaValue(std::string);
		

		// Create, delete and update Tax
		bool CreateTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string tName, std::string tCode, double tFixedValue, int tPercentValue,
			std::string tFormulaValue, std::string& errorMessage);
		bool UpdateTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string tName, std::string tCode, double tFixedValue, int tPercentValue,
			std::string tFormulaValue, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetTaxByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int shID, std::string& errorMessage);
		void TrimStrings(std::string& tName, std::string& tCode);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string tName, std::string tCode, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //TaxCLASS_H