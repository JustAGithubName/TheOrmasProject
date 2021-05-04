#ifndef ORDERRAWLISTCLASS_H
#define ORDERRAWLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class OrderRawList
	{
	protected:
		int id = 0;
		int orderRawID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		OrderRawList(int olID, int oID, int pID, double olCount, double olSum, int sID, int cID) :id(olID), orderRawID(oID),
			productID(pID),	count(olCount), sum(olSum), statusID(sID), currencyID(cID){};
		OrderRawList(DataLayer::orderRawListCollection);
		OrderRawList(){};
		~OrderRawList(){};

		int employeeID = 0 ;
		//OrderRawList class Accessors
		int GetID();
		int GetOrderRawID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//OrderRawList class Mutators
		void SetID(int);
		void SetOrderRawID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByOrderRawID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool CreateOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateOrderRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetOrderRawListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
		int GetSubaccountIDForEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif