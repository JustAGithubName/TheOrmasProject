#ifndef PAYSLIPORDERRELATIONCLASS_H
#define PAYSLIPORDERRELATIONCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer{
	class PayslipOrderRelation
	{
	protected:
		int id = 0;
		int payslipID = 0;
		int orderID = 0;		
	public:
		PayslipOrderRelation();
		PayslipOrderRelation(int poID, int pID, int oID) : id(poID), payslipID(pID), orderID(oID){};
		PayslipOrderRelation(DataLayer::payslipOrderCollection);
		~PayslipOrderRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetOrderID();
		int GetPayslipID();

		//Access class Mutators
		void SetID(int);
		void SetOrderID(int);
		void SetPayslipID(int);

		// Create, delete and update Access
		bool CreatePayslipOrderRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeletePayslipOrderRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreatePayslipOrderRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int oID, std::string& errorMessage);


		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::vector<int> GetAllPayslipByOrderID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		std::vector<int> GetAllOrderByPayslipID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif