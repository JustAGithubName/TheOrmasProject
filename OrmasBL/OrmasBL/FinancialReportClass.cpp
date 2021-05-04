#include "stdafx.h"
#include "FinancialReportClass.h"

namespace BusinessLayer{
	FinancialReport::FinancialReport(DataLayer::financialReportCollection jCollection)
	{
		id = std::get<0>(jCollection);
		account44010 = std::get<1>(jCollection);
		account55010 = std::get<2>(jCollection);
		account552 = std::get<3>(jCollection);
		account55270 = std::get<4>(jCollection);
		account553 = std::get<5>(jCollection);
		account55321 = std::get<6>(jCollection);
		account44020_90 = std::get<7>(jCollection);
		account66010_66110 = std::get<8>(jCollection);
		account66020_66120 = std::get<9>(jCollection);
		account66040_66140 = std::get<10>(jCollection);
		account66050_66150 = std::get<11>(jCollection);
		account66060_66160 = std::get<12>(jCollection);
		account66130 = std::get<13>(jCollection);
		account66070_66170 = std::get<14>(jCollection);
		tax = std::get<15>(jCollection);
		fromDate = std::get<16>(jCollection);
		tillDate = std::get<17>(jCollection);
	}
	FinancialReport::FinancialReport()
	{
		id = 0;
		account44010 = 0;
		account55010 = 0;
		account552 = 0;
		account55270 = 0;
		account553 = 0;
		account55321 = 0;
		account44020_90 = 0;
		account66010_66110 = 0;
		account66020_66120 = 0;
		account66040_66140 = 0;
		account66050_66150 = 0;
		account66060_66160 = 0;
		account66130 = 0;
		account66070_66170 = 0;
		tax = 0;
		fromDate = "";
		tillDate = "";
	}

	int FinancialReport::GetID()
	{
		return id;
	}

	double FinancialReport::GetAccount55010()
	{
		return account55010;
	}

	double FinancialReport::GetAccount44010()
	{
		return account44010;
	}

	double FinancialReport::GetAccount552()
	{
		return account552;
	}

	double FinancialReport::GetAccount55270()
	{
		return account55270;
	}

	double FinancialReport::GetAccount553()
	{
		return account553;
	}

	double FinancialReport::GetAccount55321()
	{
		return account55321;
	}

	double FinancialReport::GetAccount44020_90()
	{
		return account44020_90;
	}

	double FinancialReport::GetAccount66010_66110()
	{
		return account66010_66110;
	}

	double FinancialReport::GetAccount66020_66120()
	{
		return account66020_66120;
	}

	double FinancialReport::GetAccount66040_66140()
	{
		return account66040_66140;
	}
	
	double FinancialReport::GetAccount66050_66150()
	{
		return account66050_66150;
	}

	double FinancialReport::GetAccount66060_66160()
	{
		return account66060_66160;
	}

	double FinancialReport::GetAccount66130()
	{
		return account66130;
	}

	double FinancialReport::GetAccount66070_66170()
	{
		return account66070_66170;
	}

	double FinancialReport::GetTax()
	{
		return tax;
	}

	std::string FinancialReport::GetFromDate()
	{
		return fromDate;
	}

	std::string FinancialReport::GetTillDate()
	{
		return tillDate;
	}

	void FinancialReport::SetID(int fID)
	{
		id = fID;
	}

	void FinancialReport::SetAccount55010(double fAccount55010)
	{
		account55010 = fAccount55010;
	}

	void FinancialReport::SetAccount44010(double fAccount44010)
	{
		account44010 = fAccount44010;
	}

	void FinancialReport::SetAccount552(double fAccount552)
	{
		account552 = fAccount552;
	}

	void FinancialReport::SetAccount55270(double fAccount55270)
	{
		account55270 = fAccount55270;
	}

	void FinancialReport::SetAccount553(double fAccount553)
	{
		account553 = fAccount553;
	}

	void FinancialReport::SetAccount55321(double fAccount55321)
	{
		account55321 = fAccount55321;
	}

	void FinancialReport::SetAccount44020_90(double fAccount44020_90)
	{
		account44020_90 = fAccount44020_90;
	}

	void FinancialReport::SetAccount66010_66110(double fAccount66010_66110)
	{
		account66010_66110 = fAccount66010_66110;
	}

	void FinancialReport::SetAccount66020_66120(double fAccount66020_66120)
	{
		account66020_66120 = fAccount66020_66120;
	}

	void FinancialReport::SetAccount66040_66140(double fAccount66040_66140)
	{
		account66040_66140 = fAccount66040_66140;
	}

	void FinancialReport::SetAccount66050_66150(double fAccount66050_66150)
	{
		account66050_66150 = fAccount66050_66150;
	}

	void FinancialReport::SetAccount66060_66160(double fAccount66060_66160)
	{
		account66060_66160 = fAccount66060_66160;
	}

	void FinancialReport::SetAccount66130(double fAccount66130)
	{
		account66130 = fAccount66130;
	}

	void FinancialReport::SetAccount66070_66170(double fAccount66070_66170)
	{
		account66070_66170 = fAccount66070_66170;
	}

	void FinancialReport::SetTax(double fTax)
	{
		tax = fTax;
	}

	void FinancialReport::SetFromDate(std::string fFromDate)
	{
		fromDate = fFromDate;
	}

	void FinancialReport::SetTillDate(std::string fTillDate)
	{
		tillDate = fTillDate;
	}

	bool FinancialReport::CreateFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double fAccount44010, double fAccount55010, double fAccount552, double fAccount55270,
		double fAccount553, double fAccount55321, double fAccount44020_90, double fAccount66010_66110, double fAccount66020_66120,
		double fAccount66040_66140, double fAccount66050_66150, double fAccount66060_66160, double fAccount66130, double fAccount66070_66170,
		double fTax, std::string fFromDate, std::string fTillDate, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, fFromDate, fTillDate, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		account44010 = fAccount44010;
		account55010 = fAccount55010;
		account552 = fAccount552;
		account55270 = fAccount55270;
		account553 = fAccount553;
		account55321 = fAccount55321;
		account44020_90 = fAccount44020_90;
		account66010_66110 = fAccount66010_66110;
		account66020_66120 = fAccount66020_66120;
		account66040_66140 = fAccount66040_66140;
		account66050_66150 = fAccount66050_66150;
		account66060_66160 = fAccount66060_66160;
		account66130 = fAccount66130;
		account66070_66170 = fAccount66070_66170;
		tax = fTax;
		fromDate = fFromDate;
		tillDate = fTillDate;
		if (0 != id && ormasDal.CreateFinancialReport(id, account44010, account55010, account552, account55270, account553, 
			account55321, account44020_90, account66010_66110, account66020_66120, account66040_66140, account66050_66150,
			account66060_66160, account66130, account66070_66170, tax, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool FinancialReport::CreateFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateFinancialReport(id, account44010, account55010, account552, account55270, account553,
			account55321, account44020_90, account66010_66110, account66020_66120, account66040_66140, account66050_66150,
			account66060_66160, account66130, account66070_66170, tax, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool FinancialReport::DeleteFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteFinancialReport(id, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}

	bool FinancialReport::UpdateFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double fAccount44010, double fAccount55010, double fAccount552, double fAccount55270,
		double fAccount553, double fAccount55321, double fAccount44020_90, double fAccount66010_66110, double fAccount66020_66120,
		double fAccount66040_66140, double fAccount66050_66150, double fAccount66060_66160, double fAccount66130, double fAccount66070_66170,
		double fTax, std::string fFromDate, std::string fTillDate, std::string& errorMessage)
	{
		account44010 = fAccount44010;
		account55010 = fAccount55010;
		account552 = fAccount552;
		account55270 = fAccount55270;
		account553 = fAccount553;
		account55321 = fAccount55321;
		account44020_90 = fAccount44020_90;
		account66010_66110 = fAccount66010_66110;
		account66020_66120 = fAccount66020_66120;
		account66040_66140 = fAccount66040_66140;
		account66050_66150 = fAccount66050_66150;
		account66060_66160 = fAccount66060_66160;
		account66130 = fAccount66130;
		account66070_66170 = fAccount66070_66170;
		tax = fTax;
		fromDate = fFromDate;
		tillDate = fTillDate;
		if (0 != id && ormasDal.UpdateFinancialReport(id, account44010, account55010, account552, account55270, account553,
			account55321, account44020_90, account66010_66110, account66020_66120, account66040_66140, account66050_66150,
			account66060_66160, account66130, account66070_66170, tax, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool FinancialReport::UpdateFinancialReport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateFinancialReport(id, account44010, account55010, account552, account55270, account553,
			account55321, account44020_90, account66010_66110, account66020_66120, account66040_66140, account66050_66150,
			account66060_66160, account66130, account66070_66170, tax, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string FinancialReport::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != account44010 || 0 != account55010 || 0 != account552 || 0 != account55270 || 0 != account553 
			|| 0 != account55321 || 0 != account44020_90 || 0 != account66010_66110 || 0 != account66020_66120 || 0 != account66040_66140 
			|| 0 != account66050_66150 || 0 != account66060_66160 || 0 != account66130 || 0 != account66070_66170 || 0 != tax || !fromDate.empty() || !tillDate.empty())
		{
			return ormasDal.GetFilterForFinancialReport(id, account44010, account55010, account552, account55270, account553,
				account55321, account44020_90, account66010_66110, account66020_66120, account66040_66140, account66050_66150,
				account66060_66160, account66130, account66070_66170, tax, fromDate, tillDate);
		}
		return "";
	}

	bool FinancialReport::GetFinancialReportByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fID, std::string& errorMessage)
	{
		if (fID <= 0)
			return false;
		id = fID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::financialReportCollection> financialReportVector = ormasDal.GetFinancialReport(errorMessage, filter);
		if (0 != financialReportVector.size())
		{
			id = std::get<0>(financialReportVector.at(0));
			account44010 = std::get<1>(financialReportVector.at(0));
			account55010 = std::get<2>(financialReportVector.at(0));
			account552 = std::get<3>(financialReportVector.at(0));
			account55270 = std::get<4>(financialReportVector.at(0));
			account553 = std::get<5>(financialReportVector.at(0));
			account55321 = std::get<6>(financialReportVector.at(0));
			account44020_90 = std::get<7>(financialReportVector.at(0));
			account66010_66110 = std::get<8>(financialReportVector.at(0));
			account66020_66120 = std::get<9>(financialReportVector.at(0));
			account66040_66140 = std::get<10>(financialReportVector.at(0));
			account66050_66150 = std::get<11>(financialReportVector.at(0));
			account66060_66160 = std::get<12>(financialReportVector.at(0));
			account66130 = std::get<13>(financialReportVector.at(0));
			account66070_66170 = std::get<14>(financialReportVector.at(0));
			tax = std::get<15>(financialReportVector.at(0));
			fromDate = std::get<16>(financialReportVector.at(0));
			tillDate = std::get<17>(financialReportVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find financial report with this id";
		}
		return false;
	}

	bool FinancialReport::IsEmpty()
	{
		if (0 == id || 0 == account44010 || 0 == account55010 || 0 == account552 || 0 == account55270 || 0 == account553
			|| 0 == account55321 || 0 == account44020_90 || 0 == account66010_66110 || 0 == account66020_66120 || 0 == account66040_66140
			|| 0 == account66050_66150 || 0 == account66060_66160 || 0 == account66130 || 0 == account66070_66170 || 0 == tax || fromDate.empty() || tillDate.empty())
			return true;
		return false;
	}

	void FinancialReport::Clear()
	{
		id = 0;
		account44010 = 0;
		account55010 = 0;
		account552 = 0;
		account55270 = 0;
		account553 = 0;
		account55321 = 0;
		account44020_90 = 0;
		account66010_66110 = 0;
		account66020_66120 = 0;
		account66040_66140 = 0;
		account66050_66150 = 0;
		account66060_66160 = 0;
		account66130 = 0;
		account66070_66170 = 0;
		tax = 0;
		fromDate = "";
		tillDate = "";
	}

	bool FinancialReport::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aFromDate, std::string aTillDate, std::string& errorMessage)
	{
		FinancialReport financialReport;
		financialReport.Clear();
		errorMessage.clear();
		financialReport.SetFromDate(aFromDate);
		financialReport.SetTillDate(aTillDate);
		std::string filter = financialReport.GenerateFilter(ormasDal);
		std::vector<DataLayer::financialReportCollection> financialReportVector = ormasDal.GetFinancialReport(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == financialReportVector.size())
		{
			return false;
		}
		errorMessage = "Financial report with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool FinancialReport::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		FinancialReport financialReport;
		financialReport.Clear();
		errorMessage.clear();
		financialReport.SetFromDate(fromDate);
		financialReport.SetTillDate(tillDate);
		std::string filter = financialReport.GenerateFilter(ormasDal);
		std::vector<DataLayer::financialReportCollection> financialReportVector = ormasDal.GetFinancialReport(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == financialReportVector.size())
		{
			return false;
		}
		errorMessage = "Financial report with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}