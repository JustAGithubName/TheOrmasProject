#ifndef COMPANYACCOUNTRELATIONVIEWCLASS_H
#define COMPANYACCOUNTRELATIONVIEWCLASS_H

#include "CompanyAccountRelationClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class CompanyAccountRelationView : public CompanyAccountRelation
	{
		std::string companyName = "";
		std::string accountNumber = "";
	public:
		CompanyAccountRelationView(DataLayer::companyAccountViewCollection);
		CompanyAccountRelationView(){};
		~CompanyAccountRelationView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// CompanyAccountRelationView class CompanyAccountRelationors
		std::string GetCompanyName();
		std::string GetAccountNumber();

		void SetCompanyName(std::string);
		void SetAccountNumber(std::string);
	};
}
#endif //COMPANYACCOUNTRELATIONVIEWCLASS_H