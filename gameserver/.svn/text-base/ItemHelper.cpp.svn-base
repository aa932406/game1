
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
	case IC_GEM:
		{
			const CfgItemGem* pGem = CFG_DATA.GetItemGemTable().GetItemGem( nId );
			if ( pGem != NULL )
			{
				nType = pGem->m_nType;
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
	MemChrBagVector items;

	if (!strItems.empty())
	{
		StringVector items_receive = StringUtility::split(strItems, "|");
		for (StringVector::iterator it = items_receive.begin(); it != items_receive.end(); ++it)
		{
			StringVector item = StringUtility::split(*it, ":");
			if (item.size() == 3)
			{
				MemChrBag itemData = {};
				itemData.itemId			= atoi(item[0].c_str());
				itemData.itemClass		= atoi(item[1].c_str());
				itemData.itemCount		= atoi(item[2].c_str());
				items.push_back(itemData);
			}
			else if ( item.size() == 4 )
			{
				MemChrBag itemData = {};
				itemData.itemId			= atoi(item[0].c_str());
				itemData.itemClass		= atoi(item[1].c_str());
				itemData.itemCount		= atoi(item[2].c_str());
				itemData.bind			= atoi(item[3].c_str());
				items.push_back(itemData);
			}
			else if ( item.size() == 5 )
			{
				MemChrBag itemData = {};
				itemData.itemId			= atoi(item[0].c_str());
				itemData.itemClass		= atoi(item[1].c_str());
				itemData.itemCount		= atoi(item[2].c_str());
				itemData.bind			= atoi(item[3].c_str());
				itemData.endTime		= atoi(item[4].c_str());
				items.push_back(itemData);
			}
			else
			{
				LOG_ERROR("CfgData::parseItemString wrong data with id = %d, string = %s\n", id, strItems.c_str());
			}
		}
	}

	return items;
}
