#ifndef ORDERPRICECORRECTIONCLASS_H
#define ORDERPRICECORRECTIONCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class OrderPriceCorrection{
	protected:
		int id = 0;
		int orderID = 0;
		int priceExtensionID = 0;
		int orderListID = 0;
		double standartValue = 0.0;
		double newValue = 0.0;
	public:
		OrderPriceCorrection();
		OrderPriceCorrection(int pID, int oID, int peID, int olID, double sValue, double nValue) :id(pID), orderID(oID), priceExtensionID(peID),
			orderListID(oID), standartValue(sValue), newValue(nValue){};
		OrderPriceCorrection(DataLayer::orderPriceCorrectionCollection);
		~OrderPriceCorrection(){};

		std::string errorMessage = "";
		//OrderPriceCorrection class OrderPriceCorrectionors
		int GetID();
		int GetOrderID();
		int GetPriceExtensionID();
		int GetOrderListID();
		double GetStandartValue();
		double GetNewValue();

		//OrderPriceCorrection class Mutators
		void SetID(int);
		void SetOrderID(int);
		void SetPriceExtensionID(int);
		void SetOrderListID(int);
		void SetStandartValue(double);
		void SetNewValue(double);


		// Create, delete and update OrderPriceCorrection
		bool CreateOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage);
		bool UpdateOrderPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetOrderPriceCorrectionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetOrderPriceCorrectionByOrderID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool GetOrderPriceCorrectionByPriceExtensionID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		bool GetOrderPriceCorrectionByOrderListID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int olID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //OrderPriceCorrectionCLASS_H