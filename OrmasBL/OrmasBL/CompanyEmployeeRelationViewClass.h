#ifndef COMPANYEMPLOYEERELATIONVIEWCLASS_H
#define COMPANYEMPLOYEERELATIONVIEWCLASS_H

#include "CompanyEmployeeRelationClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class CompanyEmployeeRelationView : public CompanyEmployeeRelation
	{
		std::string companyName = "";
		std::string branchName = "";
		std::string userName = "";
		std::string userSurname = "";
		std::string userPhone = "";
	public:
		CompanyEmployeeRelationView(DataLayer::companyEmployeeViewCollection);
		CompanyEmployeeRelationView(){};
		~CompanyEmployeeRelationView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;
		// CompanyEmployeeRelationView class CompanyEmployeeRelationors
		std::string GetCompanyName();
		std::string GetBranchName();
		std::string GetUsername();
		std::string GetUserSurname();
		std::string GetUserPhone();

		void SetCompanyName(std::string);
		void SetBranchName(std::string);
		void SetUsername(std::string);
		void SetUserSurname(std::string);
		void SetUserPhone(std::string);
	};
}
#endif //COMPANYEMPLOYEERELATIONVIEWCLASS_H