#ifndef AMORTIZEGROUPCLASS_H
#define AMORTIZEGROUPCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class AmortizeGroup{
	protected:
		int id = 0;
		int groupNumber = 0;
		int fromMonth = 0;
		int toMonth = 0;
	public:
		AmortizeGroup();
		AmortizeGroup(int aID, int gNumber, int fMonth, int tMonth) :id(aID), groupNumber(gNumber), fromMonth(fMonth),
			toMonth(tMonth){};
		AmortizeGroup(DataLayer::amortizeGroupCollection);
		~AmortizeGroup(){};

		std::string errorMessage = "";

		//AmortizeGroup class Accessors
		int GetID();
		int GetGroupNumber();
		int GetFromMonth();
		int GetToMonth();

		//AmortizeGroup class Mutators
		void SetID(int);
		void SetGroupNumber(int);
		void SetFromMonth(int);
		void SetToMonth(int);

		// Create, delete and update AmortizeGroup
		bool CreateAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int gNumber, int fMonth, int tMonth, std::string& errorMessage);
		bool UpdateAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int gNumber, int fMonth, int tMonth, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAmortizeGroupByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool GetAmortizeGroupByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int gNumber, std::string& errorMessage);
		bool IsEmpty();

		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aNumber, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //AmortizeGroupCLASS_H