#ifndef NetCostCoefficientCLASS_H
#define NetCostCoefficientCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class NetCostCoefficient{
	protected:
		int id = 0;
		int productID = 0;
		double value = 0.0;
		std::string comment = "";
	public:
		NetCostCoefficient();
		NetCostCoefficient(int nID, int pID, double pValue, std::string pComment) :id(nID), productID(pID), value(pValue),
			comment(pComment){};
		NetCostCoefficient(DataLayer::netCostCoefficientCollection);
		~NetCostCoefficient(){};

		std::string errorMessage = "";
		//NetCostCoefficient class NetCostCoefficientors
		int GetID();
		std::string GetComment();
		double GetValue();
		int GetProductID();

		//NetCostCoefficient class Mutators
		void SetID(int);
		void SetComment(std::string);
		void SetValue(double);
		void SetProductID(int);

		// Create, delete and update NetCostCoefficient
		bool CreateNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, int pID, double pValue, std::string pComment, std::string& errorMessage);
		bool UpdateNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, int pID, double pValue, std::string pComment, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetNetCostCoefficientByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, std::string& errorMessage);
		bool GetNetCostCoefficientByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prodID,
			std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //NetCostCoefficientCLASS_H