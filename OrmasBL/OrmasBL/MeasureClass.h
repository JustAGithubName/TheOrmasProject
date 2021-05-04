#ifndef MEASURECLASS_H
#define MEASURECLASS_H

#include "OrmasDAL.h"
namespace BusinessLayer
{
	class Measure
	{
		int id = 0;
		std::string name = "";
		std::string shortName = "";
		int unit = 0;
	public:
		Measure(){};
		Measure(int mID, std::string mName, std::string mShortName, int mUnit) :id(mID),
			name(mName), shortName(mShortName), unit(mUnit){};
		Measure(DataLayer::measuresCollection);
		~Measure(){};
		
		//Measure class Accessors
		int GetID();
		std::string GetName();
		std::string GetShortName();
		int GetUnit();

		//Measure class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetShortName(std::string);
		void SetUnit(int);

		//Create, delete and update methods 
		bool CreateMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string mName, std::string mShortName, int mUnit, std::string& errorMessage);
		bool UpdateMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string mName, std::string mShortName, int mUnit, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetMeasureByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int mID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string mName, std::string mShortName, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //MEASURECLASS_H