#include "stdafx.h"
#include "ItemHelper.h"
#include "CfgData.h"

using namespace Answer;

int32_t CItemHelper::GetItemType( int32_t nId, int8_t nClass )
{
	int32_t nType = -1;
	switch ( nClass )
	{
	case IC_NORMAL:
		{
			CfgItem* pItem = CFG_DATA.getItem( nId );
			if ( pItem != NULL )
			{
				nType = pItem->type;
			}
		}
		break;
	case IC_EQUIP:
		{
			const CfgEquip* pEquip = CFG_DATA.GetEquipTable().GetEquip( nId );
			if ( pEquip != NULL )
			{
				nType = pEquip->m_nType;
			}
		}
		break;
	default:
		break;
	}
	return nType;
}

MemChrBagVector CItemHelper::parseItemString(int32_t id, const std::string &strItems)
{
	return parseItemVectorString(strItems);
}

MemChrBagVector CItemHelper::parseItemVectorString(const std::string &strItems)
{
	MemChrBagVector items;
	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() >= 3)
			{
				MemChrBag bag;
				memset(&bag, 0, sizeof(bag));
				bag.itemId = atoi(item[0].c_str());
				bag.itemClass = (int8_t)atoi(item[1].c_str());
				bag.itemCount = atoi(item[2].c_str());
				if (item.size() >= 4) bag.bind = (int8_t)atoi(item[3].c_str());
				if (item.size() >= 5) bag.endTime = atoi(item[4].c_str());
				items.push_back(bag);
			}
		}
	}
	return items;
}

std::list<ItemData> CItemHelper::parseItemDataListString(const std::string &strItems)
{
	std::list<ItemData> items;
	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() >= 3)
			{
				ItemData itemData;
				itemData.m_nId		= atoi(item[0].c_str());
				itemData.m_nClass	= atoi(item[1].c_str());
				itemData.m_nCount	= atoi(item[2].c_str());
				items.push_back(itemData);
			}
		}
	}
	return items;
}

void CItemHelper::parseRateItemDataString(RateItem& outItem, const std::string& strData)
{
	StringVector parts = StringUtility::split(strData, ":");
	if (parts.size() >= 6)
	{
		outItem.nItemId = atoi(parts[0].c_str());
		outItem.nItemClass = atoi(parts[1].c_str());
		outItem.nItemCount = atoi(parts[2].c_str());
		outItem.nBind = (int8_t)atoi(parts[3].c_str());
		outItem.nRate = atoi(parts[4].c_str());
		outItem.nGongGaoId = atoi(parts[5].c_str());
	}
}
