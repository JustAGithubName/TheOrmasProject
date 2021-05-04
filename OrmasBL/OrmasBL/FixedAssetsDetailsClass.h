#ifndef FIXEDASSETSDETAILSCLASS_H
#define FIXEDASSETSDETAILSCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class FixedAssetsDetails
	{
	protected:
		int id = 0;
		int amortizeGroupID = 0;
		int amortizeTypeID = 0;
		int departmentID = 0;
		std::string fixedAssetsLocation = "";
		int primaryCostAccountID = 0;
		int amortizeAccountID = 0;
		std::string barcodeNumber = "";
		double amortizeValue = 0;
	public:
		FixedAssetsDetails(int fID, int agID, int atID, int dID, std::string faLocation, int paID, int aaID, std::string bCode, double amValue) : id(fID),
			amortizeGroupID(agID), amortizeTypeID(atID), departmentID(dID), fixedAssetsLocation(faLocation), primaryCostAccountID(paID),
			amortizeAccountID(aaID), barcodeNumber(bCode), amortizeValue(amValue){};
		int fixedAssetsAccountID = 0;
		FixedAssetsDetails(DataLayer::fixedAssetsDetailsCollection);
		FixedAssetsDetails(){};
		~FixedAssetsDetails(){};

		//Consume Product class Accessors
		int GetID();
		int GetAmortizeGroupID();
		int GetAmortizeTypeID();
		int GetDepartmentID();
		std::string GetFixedAssetsLocation();
		int GetPrimaryCostAccountID();
		int GetAmortizeAccountID();
		std::string GetBarcodeNumber();
		double GetAmortizeValue();

		//Consume Product class Mutators
		void SetID(int);
		void SetAmortizeGroupID(int);
		void SetAmortizeTypeID(int);
		void SetDepartmentID(int);
		void SetFixedAssetsLocation(std::string);
		void SetPrimaryCostAccountID(int);
		void SetAmortizeAccountID(int);
		void SetBarcodeNumber(std::string);
		void SetAmortizeValue(double);

		//Create, delete, update methods
		bool CreateFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int agID, int atID, int dID, std::string faLocation,
			int paID, int aaID, std::string bNumber, double amValue, std::string& errorMessage);
		bool UpdateFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int agID, int atID, int dID, std::string faLocation,
			int paID, int aaID, std::string bNumber, double amValue, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetFixedAssetsDetailsByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		int GenerateAmortizeSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double currentValue, std::string& errorMessage);
		int GeneratePrimeSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double currentValue, std::string& errorMessage);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int aID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		
	};
}
#endif //FixedAssetsDetailsCLASS_H