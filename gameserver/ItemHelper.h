#ifndef __TPOC_ITEM_HELPER__
#define __TPOC_ITEM_HELPER__

class CItemHelper
{
public:
	static	int32_t	GetItemType( int32_t nId, int8_t nClass );
	static  MemChrBagVector parseItemString(int32_t id, const std::string &strItems);
};


#endif	//__TPOC_ITEM_HELPER__