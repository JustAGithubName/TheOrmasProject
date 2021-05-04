#ifndef FIXEDASSETSCLASS_H
#define FIXEDASSETSCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class FixedAssets
	{
	protected:
		int id = 0;
		int specificationID = 0;
		std::string inventoryNumber = "";
		double primaryCost = 0;
		double stopCost = 0;
		int serviceLife = 0;
		bool isAmortize = false;
		std::string buyDate = "";
		std::string startOfOperationDate = "";
		std::string endOfOperationDate = "";
		int statusID = 0;
		int fixedAssetsDetailsID = 0;
	public:
		FixedAssets(int fID, int sID, std::string iNumber, double pCost, double sCost, int sLife, bool isAmor, std::string bDate, 
			std::string sOfDate, std::string eOfDate, int statID, int fadID) : id(fID), specificationID(sID), inventoryNumber(iNumber), 
			primaryCost(pCost), stopCost(sCost), serviceLife(isAmor), buyDate(bDate), startOfOperationDate(sOfDate), 
			endOfOperationDate(eOfDate), statusID(statID), fixedAssetsDetailsID(fadID){};
		FixedAssets(DataLayer::fixedAssetsCollection);
		FixedAssets(){};
		~FixedAssets(){};

		//Consume Product class Accessors
		int GetID();
		int GetSpecificationID();
		std::string GetInventoryNumber();
		double GetPrimaryCost();
		double GetStopCost();
		int GetServiceLife();
		bool GetIsAmortize();
		std::string GetBuyDate();
		std::string GetStartOfOperationDate();
		std::string GetEndOfOperationDate();
		int GetStatusID();
		int GetFixedAssetsDetailsID();

		//Consume Product class Mutators
		void SetID(int);
		void SetSpecificationID(int);
		void SetInventoryNumber(std::string);
		void SetPrimaryCost(double);
		void SetStopCost(double);
		void SetServiceLife(int);
		void SetIsAmortize(bool);
		void SetBuyDate(std::string);
		void SetStartOfOperationDate(std::string);
		void SetEndOfOperationDate(std::string);
		void SetStatusID(int);
		void SetFixedAssetsDetailsID(int);


		//Create, delete, update methods
		bool CreateFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string iNumber, double pCost, double sCost, int sLife, bool isAmor, std::string bDate,
			std::string sOfDate, std::string eOfDate, int statID, int fadID, std::string& errorMessage);
		bool UpdateFixedAssets(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string iNumber, double pCost, double sCost, int sLife, bool isAmor, std::string bDate,
			std::string sOfDate, std::string eOfDate, int statID, int fadID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetFixedAssetsByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		bool CreatePostingFixedAssetsEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int acctbID, int purID, int accID, int debitingAccID, double value, std::string execDate, std::string& errorMessage);
		bool CreatePostingFixedAssetsEntryReverce(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int acctbID, int purID, int accID, int debitingAccID, double value, std::string execDate, std::string& errorMessage);
		bool CreatePostingFixedAssetsEntryWriteOFF(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fixedAssetsID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		bool CreateEntryWriteOFF(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		bool CreateEntryCancel(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string iNumber, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}
#endif //FixedAssetsCLASS_H