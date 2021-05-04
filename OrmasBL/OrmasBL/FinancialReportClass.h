#ifndef FINANCIALREPORTCLASS_H
#define FINANCIALREPORTCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class FinancialReport{
	protected:
		int id = 0;
		double account44010 = 0.0;
		double account55010 = 0.0;
		double account552 = 0.0;
		double account55270 = 0.0;
		double account553 = 0.0;
		double account55321 = 0.0;
		double account44020_90 = 0.0;
		double account66010_66110 = 0.0;
		double account66020_66120 = 0.0;
		double account66040_66140 = 0.0;
		double account66050_66150 = 0.0;
		double account66060_66160 = 0.0;
		double account66130 = 0.0;
		double account66070_66170 = 0.0;
		double tax = 0.0;
		std::string fromDate = "";
		std::string tillDate = "";
	public:
		FinancialReport();
		FinancialReport(int aID, double fAccount44010, double fAccount55010, double fAccount552, double fAccount55270,
			double fAccount553, double fAccount55321, double fAccount44020_90, double fAccount66010_66110, double fAccount66020_66120,
			double fAccount66040_66140, double fAccount66050_66150, double fAccount66060_66160, double fAccount66130, double fAccount66070_66170,
			double fTax, std::string fFromDate, std::string fTillDate) :id(aID), account44010(fAccount44010), account55010(fAccount55010),
			account552(fAccount552), account55270(fAccount55270), account553(fAccount553), account55321(fAccount55321),
			account44020_90(fAccount44020_90), account66010_66110(fAccount66010_66110), account66020_66120(fAccount66020_66120),
			account66040_66140(fAccount66040_66140), account66050_66150(fAccount66050_66150), account66060_66160(fAccount66060_66160),
			account66130(fAccount66130), account66070_66170(fAccount66070_66170), tax(fTax), fromDate(fFromDate), tillDate(fTillDate){};
		FinancialReport(DataLayer::financialReportCollection);
		~FinancialReport(){};

		std::string errorMessage = "";

		//FinancialReport class Accessors
		int GetID();
		double GetAccount44010();
		double GetAccount55010();
		double GetAccount552();
		double GetAccount55270();
		double GetAccount553();
		double GetAccount55321();
		double GetAccount44020_90();
		double GetAccount66010_66110();
		double GetAccount66020_66120();
		double GetAccount66040_66140();
		double GetAccount66050_66150();
		double GetAccount66060_66160();
		double GetAccount66130();
		double GetAccount66070_66170();
		double GetTax();
		std::string GetFromDate();
		std::string GetTillDate();

		//FinancialReport class Mutators
		void SetID(int);
		void SetAccount44010(double);
		void SetAccount55010(double);
		void SetAccount552(double);
		void SetAccount55270(double);
		void SetAccount553(double);
		void SetAccount55321(double);
		void SetAccount44020_90(double);
		void SetAccount66010_66110(double);
		void SetAccount66020_66120(double);
		void SetAccount66040_66140(double);
		void SetAccount66050_66150(double);
		void SetAccount66060_66160(double);
		void SetAccount66130(double);
		void SetAccount66070_66170(double);
		void SetTax(double);
		void SetFromDate(std::string);
		void SetTillDate(std::string);

		// Create, delete and update FinancialReport
		bool CreateFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double fAccount44010, double fAccount55010, double fAccount552, double fAccount55270,
			double fAccount553, double fAccount55321, double fAccount44020_90, double fAccount66010_66110, double fAccount66020_66120,
			double fAccount66040_66140, double fAccount66050_66150, double fAccount66060_66160, double fAccount66130, 
			double fAccount66070_66170,	double fTax, std::string fFromDate, std::string fTillDate, std::string& errorMessage);
		bool UpdateFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double fAccount44010, double fAccount55010, double fAccount552, double fAccount55270,
			double fAccount553, double fAccount55321, double fAccount44020_90, double fAccount66010_66110, double fAccount66020_66120,
			double fAccount66040_66140, double fAccount66050_66150, double fAccount66060_66160, double fAccount66130, double fAccount66070_66170,
			double fTax, std::string fFromDate, std::string fTillDate, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetFinancialReportByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ahID, std::string& errorMessage);
		bool GetFinancialReportByAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aAccountID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aFromDate, std::string aTillDate, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //FinancialReportCLASS_H