#ifndef __TPOC_ITEM_HELPER__
#define __TPOC_ITEM_HELPER__

class CItemHelper
{
public:
	static	int32_t	GetItemType( int32_t nId, int8_t nClass );
	static  MemChrBagVector parseItemString(int32_t id, const std::string &strItems);
	static  MemChrBagVector parseItemVectorString(const std::string &strItems);
	static  std::list<ItemData> parseItemDataListString(const std::string &strItems);
	static	void parseRateItemDataString(RateItem& outItem, const std::string& strData);
};


#endif	//__TPOC_ITEM_HELPER__