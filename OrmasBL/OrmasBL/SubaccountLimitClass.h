#ifndef SUBACCOUNTLIMITCLASS_H
#define SUBACCOUNTLIMITCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class SubaccountLimit{
	protected:
		int id = 0;
		int subaccountID = 0;
		double minValue = 0.0;
		double maxValue = 0.0;
	public:
		SubaccountLimit();
		SubaccountLimit(int slID, int sID, double slMin, double slMax) :id(slID), subaccountID(sID), minValue(slMin), maxValue(slMax){};
		SubaccountLimit(DataLayer::subaccountLimitCollection);
		~SubaccountLimit(){};

		std::string errorMessage = "";

		//SubaccountLimit class Accessors
		int GetID();
		int GetSubaccountID();
		double GetMinValue();
		double GetMaxValue();

		//SubaccountLimit class Mutators
		void SetID(int);
		void SetSubaccountID(int);
		void SetMinValue(double);
		void SetMaxValue(double);

		// Create, delete and update SubaccountLimit
		bool CreateSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double stMin, double stMax, std::string& errorMessage);
		bool UpdateSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double stMin, double stMax, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetSubaccountLimitByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool GetSubaccountLimitBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //SubaccountLimitCLASS_H