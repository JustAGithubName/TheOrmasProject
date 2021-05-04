#ifndef RETURNLISTCLASS_H
#define RETURNLISTCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer
{
	class ReturnList
	{
	protected:
		int id = 0;
		int returnID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ReturnList(int rlID, int rID, int pID, double rlCount, double rlSum, int sID, int cID) :id(rlID), returnID(rID), productID(pID),
			count(rlCount), sum(rlSum), statusID(sID), currencyID(cID){};
		ReturnList(DataLayer::returnListCollection);
		ReturnList(){};
		~ReturnList(){};

		int employeeID = 0;
		//ReturnList class Accessors
		int GetID();
		int GetReturnID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//ReturnList class Mutators
		void SetID(int);
		void SetReturnID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByReturnID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool CreateReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateReturnList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetReturnListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
			 int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif