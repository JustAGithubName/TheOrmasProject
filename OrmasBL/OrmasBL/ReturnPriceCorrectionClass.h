#ifndef RETURNPRICECORRECTIONCLASS_H
#define RETURNPRICECORRECTIONCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class ReturnPriceCorrection{
	protected:
		int id = 0;
		int returnID = 0;
		int priceExtensionID = 0;
		int returnListID = 0;
		double standartValue = 0.0;
		double newValue = 0.0;
	public:
		ReturnPriceCorrection();
		ReturnPriceCorrection(int pID, int oID, int peID, int olID, double sValue, double nValue) :id(pID), returnID(oID), priceExtensionID(peID),
			returnListID(oID), standartValue(sValue), newValue(nValue){};
		ReturnPriceCorrection(DataLayer::returnPriceCorrectionCollection);
		~ReturnPriceCorrection(){};

		std::string errorMessage = "";
		//ReturnPriceCorrection class ReturnPriceCorrectionors
		int GetID();
		int GetReturnID();
		int GetPriceExtensionID();
		int GetReturnListID();
		double GetStandartValue();
		double GetNewValue();

		//ReturnPriceCorrection class Mutators
		void SetID(int);
		void SetReturnID(int);
		void SetPriceExtensionID(int);
		void SetReturnListID(int);
		void SetStandartValue(double);
		void SetNewValue(double);


		// Create, delete and update ReturnPriceCorrection
		bool CreateReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage);
		bool UpdateReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetReturnPriceCorrectionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetReturnPriceCorrectionByReturnID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool GetReturnPriceCorrectionByPriceExtensionID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		bool GetReturnPriceCorrectionByReturnListID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int olID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //ReturnPriceCorrectionCLASS_H