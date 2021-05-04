#ifndef POSTINGFIXEDASSETSVIEWCLASS_H
#define POSTINGFIXEDASSETSVIEWCLASS_H

#include "PostingFixedAssetsClass.h"

namespace BusinessLayer
{
	class PostingFixedAssetsView : public PostingFixedAssets
	{
	protected:
		std::string surname = "";
		std::string accountName = "";
	public:
		PostingFixedAssetsView(DataLayer::postingFixedAssetsViewCollection);
		PostingFixedAssetsView(){};
		~PostingFixedAssetsView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// OrderView class Accessors
		std::string GetSurname();
		std::string GetAccountName();

		void SetSurname(std::string);
		void SetAccountName(std::string);
	};
}
#endif //POSTINGFIXEDASSETSVIEWCLASS_H
