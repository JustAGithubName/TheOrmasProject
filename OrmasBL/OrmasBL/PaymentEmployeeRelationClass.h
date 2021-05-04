#ifndef PAYMENTEMPLOYEERELATIONCLASS_H
#define PAYMENTEMPLOYEERELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class PaymentEmployeeRelation
	{
	protected:
		int id = 0;
		int paymentID = 0;
		int employeeID = 0;
	public:
		PaymentEmployeeRelation();
		PaymentEmployeeRelation(int peID, int pID, int eID) :id(peID), paymentID(pID), employeeID(eID){};
		PaymentEmployeeRelation(DataLayer::paymentEmployeeCollection);
		~PaymentEmployeeRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetEmployeeID();
		int GetPaymentID();

		//Access class Mutators
		void SetID(int);
		void SetEmployeeID(int);
		void SetPaymentID(int);

		// Create, delete and update Access
		bool CreatePaymentEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeletePaymentEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreatePaymentEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int eID, std::string& errorMessage);


		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::vector<int> GetAllPaymentByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		std::vector<int> GetAllEmployeeByPaymentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int eID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif