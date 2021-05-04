#ifndef USEREXTENDEDVIEWCLASS_H
#define USEREXTENDEDVIEWCLASS_H
#include "UserClass.h"

namespace BusinessLayer
{
	class UserExtendedView : public User
	{
		std::string companyName = "";
		std::string branchName = "";
		std::string roleName = "";
		std::string subaccountNumber = "";
		int subaccountID = 0;
		int accountID = 0;
		int companyID = 0;
		int branchID = 0;
	public:
		UserExtendedView(DataLayer::userExtendedViewCollection);
		UserExtendedView(){};
		~UserExtendedView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//UserExtendedView class Accessors
		std::string GetCompanyName();
		std::string GetBranchName();
		std::string GetRoleName();
		std::string GetSubaccountNumber();
		int GetSubaccountID();
		int GetAccountID();
		int GetCompanyID();		
		int GetBranchID();


		void SetCompanyName(std::string);
		void SetBranchName(std::string);
		void SetRoleName(std::string);
		void SetSubaccountNumber(std::string);
		void SetSubaccountID(int);
		void SetAccountID(int);
		void SetCompanyID(int);
		void SetBranchID(int);
	};
}

#endif //UserExtendedViewCLASS_H