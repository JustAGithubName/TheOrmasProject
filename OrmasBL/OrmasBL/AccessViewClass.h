#ifndef ACCESSVIEWCLASS_H
#define ACCESSVIEWCLASS_H

#include "AccessClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class AccessView : public Access
	{
		std::string roleName = "";
		std::string accessItemEng = "";
		std::string accessItemRu = "";
		std::string division = "";
	public:
		AccessView(DataLayer::accessesViewCollection);
		AccessView(){};
		~AccessView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// AccessView class Accessors
		std::string GetRoleName();
		std::string GetAccessItemEng();
		std::string GetAccessItemRu();
		std::string GetDivision();
		
		// AccessView class Accessors
		void SetRoleName(std::string);
		void SetAccessItemEng(std::string);
		void SetAccessItemRu(std::string);
		void SetDivision(std::string);
	};
}
#endif //ACCESSVIEWCLASS_H