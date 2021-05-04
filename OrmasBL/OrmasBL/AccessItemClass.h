#ifndef ACCESSITEMCLASS_H
#define ACCESSITEMCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class AccessItem{
	protected:
		int id = 0;
		std::string nameEng ="";
		std::string nameRu = "";
		std::string division = "";
	public:
		AccessItem();
		AccessItem(int aID, std::string aNameEng, std::string aNameRu, std::string aDivision) :id(aID), nameEng(aNameEng), 
			nameRu(aNameRu), division(aDivision){};
		AccessItem(DataLayer::accessItemsCollection);
		~AccessItem(){};

		std::string errorMessage = "";
		//AccessItem class Accessors
		int GetID();
		std::string GetNameEng();
		std::string GetNameRu();
		std::string GetDivision();

		//AccessItem class Mutators
		void SetID(int);
		void SetNameEng(std::string);
		void SetNameRu(std::string);
		void SetDivision(std::string);

		// Create, delete and update AccessItem
		bool CreateAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNameEng, std::string aNameRu, std::string aDivision, std::string& errorMessage);
		bool UpdateAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNameEng, std::string aNameRu, std::string aDivision, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccessItemByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool GetAccessItemByEngName(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string engName, std::string& errorMessage);
		bool GetAccessItemByRuName(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string ruName, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string& , std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNameEng, std::string aNameRu, std::string aDivision, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //ACCESSITEMCLASS_H