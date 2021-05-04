#ifndef ShareholderVIEWCLASS_H
#define SHAREHOLDERVIEWCLASS_H

#include "ShareholderClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class ShareholderView : public Shareholder
	{
		std::string userName = "";
		std::string userSurname = "";
		std::string userPhone = "";
		std::string userAddress = "";
	public:
		ShareholderView(DataLayer::shareholdersViewCollection);
		ShareholderView(){};
		~ShareholderView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// ShareholderView class Shareholderors
		std::string GetUsername();
		std::string GetUserSurname();
		std::string GetUserPhone();
		std::string GetUserAddress();

		void SetUsername(std::string);
		void SetUserSurname(std::string);
		void SetUserPhone(std::string);
		void SetUserAddress(std::string);
	};
}
#endif //ShareholderVIEWCLASS_H