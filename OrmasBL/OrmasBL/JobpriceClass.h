#ifndef JOBPRICECLASS_H
#define JOBPRICECLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Jobprice{
	protected:
		int id = 0;
		int productID = 0;
		double value = 0.0;
		int currencyID = 0;
		double volume = 0.0;
		int measureID = 0;
		int positionID = 0;
	public:
		Jobprice();
		Jobprice(int jID, int pID, double jValue, int cID, double jVolume, int mID, int posID) :id(jID), productID(pID), value(jValue),
			currencyID(cID), volume(jVolume), measureID(mID), positionID(posID){};
		Jobprice(DataLayer::jobpriceCollection);
		~Jobprice(){};

		std::string errorMessage = "";
		
		//Jobprice class Accessors
		int GetID();
		int GetProductID();
		double GetValue();
		int GetCurrencyID();
		double GetVolume();
		int GetMeasureID();
		int GetPositionID();

		//Jobprice class Mutators
		void SetID(int);
		void SetProductID(int);
		void SetValue(double);
		void SetCurrencyID(int);
		void SetVolume(double);
		void SetMeasureID(int);
		void SetPositionID(int);

		// Create, delete and update Jobprice
		bool CreateJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double jValue, int cID, double jVolume, int mID,
			int posID, std::string& errorMessage);
		bool UpdateJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double jValue, int cID, double jVolume, int mID,
			int posID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetJobpriceByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int jID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double jValue, int cID, double jVolume, int mID,
			int posID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //JOBPRICECLASS_H