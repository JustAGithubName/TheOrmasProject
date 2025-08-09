#ifndef FIXEDASSETSOPERATIONSCLASS_H
#define FIXEDASSETSOPERATIONSCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class FixedAssetsOperations
	{
	protected:
		int id = 0;
		std::string date="";
		std::string name = "";
		double value = 0.0;
		bool increment = false;
		bool decrement = false;
		int fixedAssetsID = 0;
		bool revaluation = false;
	public:
		FixedAssetsOperations(int faoID, std::string oDate, std::string oName, double oValue, bool oIncrement, bool oDecrement, int faID, bool revalue) : id(faoID),
			date(oDate), name(oName), value(oValue), increment(oIncrement), decrement(oDecrement), fixedAssetsID(faID), revaluation(revalue){};
		FixedAssetsOperations(DataLayer::fixedAssetsOperationsCollection);
		FixedAssetsOperations(){};
		~FixedAssetsOperations(){};

		//Consume Product class Accessors
		int GetID();
		std::string GetDate();
		std::string GetName();
		double GetValue();
		bool GetIncrement();
	    bool GetDecrement();
		int GetFixedAssetsID();
		bool GetRevaluation();

		//Consume Product class Mutators
		void SetID(int);
		void SetDate(std::string);
		void SetName(std::string);
		void SetValue(double);
		void SetIncrement(bool);
		void SetDecrement(bool);
		void SetFixedAssetsID(int);
		void SetRevaluation(bool);

		//Create, delete, update methods
		bool CreateFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, std::string oName, 
			double oValue, bool oIncrement, bool oDecrement, int faID, bool oRevaluation, std::string& errorMessage);
		bool UpdateFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, std::string oName,
			double oValue, bool oIncrement, bool oDecrement, int faID, bool oRevation, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetFixedAssetsOperationsByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool CreateIncrementOperation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fxID, std::string oName, double value, std::string oDate, std::string& errorMessage);
		bool CreateDecrementOperation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fxID, std::string oName, double value, std::string oDate, std::string& errorMessage);
		bool CreateRevaluationOperation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fxID, std::string oName, double value, std::string oDate, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, std::string oName, double oValue, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //FixedAssetsOperationsCLASS_H