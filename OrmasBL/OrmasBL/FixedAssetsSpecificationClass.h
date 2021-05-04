#ifndef FIXEDASSETSSPECIFICATIONCLASS_H
#define FIXEDASSETSSPECIFICATIONCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class FixedAssetsSpecification
	{
	protected:
		int id = 0;
		std::string name = "";
		std::string factoryNumber = "";
		std::string developer = "";
		std::string document = "";
		std::string objectCharacters = "";
		std::string condition = "";
		std::string dateOfConstruction = "";
	public:
		FixedAssetsSpecification(int sID, std::string sName, std::string sFactoryNumber, std::string sDeveloper, std::string sDocument, 
			std::string sObjChar, std::string sCondition, std::string sDateOfConst) : id(sID),factoryNumber(sFactoryNumber), 
			developer(sDeveloper), document(sDocument), objectCharacters(sObjChar), condition(sCondition), dateOfConstruction(sDateOfConst){};
		FixedAssetsSpecification(DataLayer::fixedAssetsSpecificationCollection);
		FixedAssetsSpecification(){};
		~FixedAssetsSpecification(){};

		//Consume Product class Accessors
		int GetID();
		std::string GetName();
		std::string GetFactoryNumber();
		std::string GetDeveloper();
		std::string GetDocument();
		std::string GetObjectCharacters();
		std::string GetCondition();
		std::string GetDateOfConstruction();

		//Consume Product class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetFactoryNumber(std::string);
		void SetDeveloper(std::string);
		void SetDocument(std::string);
		void SetObjectCharacters(std::string);
		void SetCondition(std::string);
		void SetDateOfConstruction(std::string);

		//Create, delete, update methods
		bool CreateFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sName, std::string sFactoryNumber, std::string sDeveloper, std::string sDocument,
			std::string sObjChar, std::string sCondition, std::string sDateOfConst, std::string& errorMessage);
		bool UpdateFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sName, std::string sFactoryNumber, std::string sDeveloper, std::string sDocument,
			std::string sObjChar, std::string sCondition, std::string sDateOfConst, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetFixedAssetsSpecificationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		//bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sFactoryNumber, std::string& errorMessage);
		//bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //FixedAssetsSpecificationCLASS_H