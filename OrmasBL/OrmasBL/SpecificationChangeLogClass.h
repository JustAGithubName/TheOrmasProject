#ifndef SPECIFICATIONCHANGELOGCLASS_H
#define SPECIFICATIONCHANGELOGCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class SpecificationChangeLog
	{
	protected:
		int id = 0;
		int specificationID = 0;
		int productID = 0;
		double count = 0;
		std::string logDate = "";
		int userID = 0;
	public:
		SpecificationChangeLog(int slID, int sID, int pID, double slCount, std::string sLogDate, int sUserID) :id(slID),
			specificationID(sID), productID(pID), count(slCount), logDate(sLogDate), userID(sUserID){};
		SpecificationChangeLog(DataLayer::specificationChangeLogCollection);
		SpecificationChangeLog(){};
		~SpecificationChangeLog(){};

		//SpecificationChangeLog class Accessors
		int GetID();
		int GetSpecificationID();
		int GetProductID();
		double GetCount();
		std::string GetLogDate();
		int GetUserID();

		//SpecificationChangeLog class Mutators
		void SetID(int);
		void SetSpecificationID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetLogDate(std::string);
		void SetUserID(int);

		//Create, delete, update methods
		bool CreateSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, double slCount, std::string sLogDate, int sUserID,  std::string& errorMessage);
		bool UpdateSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, double slCount, std::string sLogDate, int sUserID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetSpecificationChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetSpecificationChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, double slCount, std::string sLogDate, int sUserID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif