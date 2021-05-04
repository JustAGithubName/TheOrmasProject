#ifndef BORROWERVIEWCLASS_H
#define BorrowerVIEWCLASS_H

#include "BorrowerClass.h"

namespace BusinessLayer{
	class BorrowerView : public Borrower
	{
		std::string roleName = "";
	public:
		BorrowerView(DataLayer::borrowersViewCollection);
		BorrowerView(){};
		~BorrowerView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// BorrowerView class Accessors
		std::string GetRoleName();

		void SetRoleName(std::string);
	};
}

#endif //BorrowerVIEWCLASS_H