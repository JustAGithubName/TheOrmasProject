#ifndef PRODUCTIONCONSUMERAWCLASS_H
#define PRODUCTIONCONSUMERAWCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class ProductionConsumeRaw
	{
	protected:
		int id = 0;
		int employeeID = 0;
		std::string date = "";
		std::string executionDate = "";
		int stockEmployeeID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ProductionConsumeRaw(int crID, int eID, std::string crDate, std::string crExecDate, int seID, double crCount, double crSum, int sID, int cID) :
			id(crID), employeeID(eID), date(crDate), executionDate(crExecDate), stockEmployeeID(seID), count(crCount), sum(crSum),
			statusID(sID), currencyID(cID){};
		ProductionConsumeRaw(DataLayer::productionConsumeRawsCollection);
		ProductionConsumeRaw(){};
		~ProductionConsumeRaw(){};

		//Consume Product class Accessors
		int GetID();
		int GetEmployeeID();
		std::string GetDate();
		std::string GetExecutionDate();
		int GetStockEmployeeID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//Consume Product class Mutators
		void SetID(int);
		void SetEmployeeID(int);
		void SetDate(std::string);
		void SetExecutionDate(std::string);
		void SetStockEmployeeID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool SimpleUpdateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string crDate, std::string crExecDate, int seID,
			double crCount, double crSum, int sID, int cID, std::string& errorMessage);
		bool UpdateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string crDate, std::string crExecDate, int seID, 
			double crCount, double crSum, int sID, int cID, std::string& errorMessage);
		bool SimpleUpdateProductionConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string crDate, std::string crExecDate, int seID,
			double crCount, double crSum, int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate);
		bool GetProductionConsumeRawByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double prevSum = 0;
		double prevCount = 0;
		int previousStatusID = 0;
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string crDate, int seID, double crCount, double crSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int stockEmpID, std::string& errorMessage);
		bool ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int stockEmpID, std::string& errorMessage);
		bool ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		double GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage);
		double GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage);
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		std::map<int, double> GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal);
		bool UpdatePriceToLastState(GlobalVariable* globalVar, DataLayer::OrmasDal& ormasDal);
	};
}
#endif //ProductionConsumeRawCLASS_H