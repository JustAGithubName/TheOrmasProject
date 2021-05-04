#ifndef SubaccountLimitVIEWCLASS_H
#define SubaccountLimitVIEWCLASS_H

#include "SubaccountLimitClass.h"

namespace BusinessLayer{
	class SubaccountLimitView : public SubaccountLimit
	{
		std::string subaccountNumber = "";
	public:
		SubaccountLimitView(DataLayer::subaccountLimitViewCollection);
		SubaccountLimitView(){};
		~SubaccountLimitView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// AccountView class Accessors
		std::string GetSubaccountNumber();

		void SetSubaccountNumber(std::string);
	};
}

#endif //SubaccountLimitVIEWCLASS_H