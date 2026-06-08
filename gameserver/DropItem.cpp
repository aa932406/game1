#include "stdafx.h"

#include "DBService.h"
#include "DropItem.h"
#include "GameService.h"
#include "Map.h"
#include "Player.h"
#include "EquipManager.h"

using namespace Answer;

CDropItem::CDropItem()
	: Entity(ET_DROPITEM), m_itemId(0), m_itemClass(0), m_bindType(0), m_itemCount(0), m_owner(0)
{

}

CDropItem::~CDropItem()
{

}

void CDropItem::init(int32_t itemId, int8_t itemClass, int8_t bindType, int32_t itemCount, int32_t costType, int32_t costValue, CharId_t owner, Time_t endTime, int64_t	srcId )
{
	m_itemId		= itemId;
	m_itemClass		= itemClass;
	m_bindType		= bindType;
	m_itemCount		= itemCount;
	m_owner			= owner;
	m_costType		= costType;
	m_costValue		= costValue;
	m_endTime		= endTime;
	m_srcId			= srcId;
}

void CDropItem::reset()
{
	if (m_itemId != 0 || m_itemClass != 0 || m_itemCount != 0 || m_costType != CCT_NONE || m_costValue != 0)
	{
		m_itemId = 0;
		m_itemClass = 0;
		m_itemCount = 0;
		m_owner = 0;
		m_costType = CCT_NONE;
		m_costValue = 0;

		generateEntityId();
	}
}

int32_t CDropItem::getItemId() const
{
	return m_itemId;
}

int8_t CDropItem::getItemClass() const
{
	return m_itemClass;
}

int8_t CDropItem::getBindType() const
{
	return m_bindType;
}

int32_t CDropItem::getItemCount() const
{
	return m_itemCount;
}

int32_t CDropItem::getCostType() const
{
	return m_costType;
}

int32_t CDropItem::getCostValue() const
{
	return m_costValue;
}

CharId_t CDropItem::getOwner() const
{
	return m_owner;
}

int32_t CDropItem::getItemEndTime() const
{
	return m_endTime;
}

int64_t CDropItem::getItemSrcId() const
{
	return m_srcId;
}

CDropItemGroup::CDropItemGroup()
{

}

CDropItemGroup::~CDropItemGroup()
{

}

void CDropItemGroup::init(Map *pMap, const Position &centerPos, Player *pOwner, int32_t droperType, int32_t droperMid, DropItem (&dropItems)[MAX_DROPITEM_SIZE], const std::string &dropper, int32_t broadcast, int32_t autoPick)
{
	if ( NULL == pMap )
	{
		return;
	}
	m_map = pMap;

	m_centerPos = centerPos;

	for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
	{
		if (dropItems[i].itemId != 0 && dropItems[i].itemClass != 0 && dropItems[i].itemCount != 0)
		{
			Player* owner = pOwner;
			if (owner != NULL )
			{
				if ( droperType == ET_PLAYER )	//���pk����û�й���,���ڸ������
				{
					m_dropItems[i].init(dropItems[i].itemId, dropItems[i].itemClass, dropItems[i].bindType, dropItems[i].itemCount, dropItems[i].costType, dropItems[i].costValue, 0,dropItems[i].endTime,dropItems[i].srcId );		
				}
				else 
				{
					if ( autoPick )
					{
						m_dropItems[i].init(dropItems[i].itemId, dropItems[i].itemClass, dropItems[i].bindType, dropItems[i].itemCount, dropItems[i].costType, dropItems[i].costValue, 0,dropItems[i].endTime,dropItems[i].srcId );
					}
					else
					{
						m_dropItems[i].init(dropItems[i].itemId, dropItems[i].itemClass, dropItems[i].bindType, dropItems[i].itemCount, dropItems[i].costType, dropItems[i].costValue, owner->getCid(),dropItems[i].endTime,dropItems[i].srcId );
					}
				}
			}
			else
			{
				m_dropItems[i].init(dropItems[i].itemId, dropItems[i].itemClass, dropItems[i].bindType, dropItems[i].itemCount, dropItems[i].costType, dropItems[i].costValue, 0,dropItems[i].endTime,dropItems[i].srcId );
			}
			bool Broadcast = false;
			if ( m_dropItems[i].getItemClass() == IC_NORMAL )
			{
				CfgItem*pItem = CFG_DATA.getItem(m_dropItems[i].getItemId());
				if (pItem != NULL && pItem->broadcast > 0 )
				{
					Broadcast = true;
				}
			}
			else if ( m_dropItems[i].getItemClass() == IC_EQUIP )
			{
				const CfgEquip* pCfeEquip =CFG_DATA.getEquip( m_dropItems[i].getItemId() );
				if (pCfeEquip != NULL && pCfeEquip->m_nBroadcast > 0 )
				{
					Broadcast = true;
				}

			}
			else if ( m_dropItems[i].getItemClass() == IC_GEM )
			{
				const CfgItemGem* pCfgItemGem =CFG_DATA.GetItemGemTable().GetItemGem( m_dropItems[i].getItemId() );
				if (pCfgItemGem != NULL && pCfgItemGem->m_nBroadcast > 0 )
				{
					Broadcast = true;
				}
			}
			else if ( m_dropItems[i].getItemClass() == IC_PET_EGG )
			{
				const CfgPetEgg* pPetEgg = CFG_DATA.GetPetEggTable().GetEgg(m_dropItems[i].getItemId());
				if (pPetEgg != NULL && pPetEgg->broadcast > 0 )
				{
					Broadcast = true;
				}
			}
			if ( Broadcast )
			{
				if ( owner == NULL && droperType == ET_PLAYER )
				{
					//return;
				}
				else
				{
					Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( (pOwner != NULL ? pOwner->getConnId() : 0), Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
					if ( packet != NULL )
					{
						packet->writeInt32( BCI_MOUNT_DIE_DROP_GONG_GAO );
						if ( pOwner != NULL )
						{
							packet->writeUTF8( pOwner->getName() );
							packet->writeInt64( pOwner->getCid() );
						}
						else
						{
							packet->writeUTF8("");
							packet->writeInt64(0);
						}
						packet->writeInt32( pMap->GetId() );
						packet->writeInt32( droperMid );
						packet->writeUTF8( dropper );

						packet->writeInt8( m_dropItems[i].getItemClass() );
						packet->writeInt32( m_dropItems[i].getItemId() );
						packet->setSize(packet->getWOffset());
						GAME_SERVICE.worldBroadcast((pOwner != NULL ? pOwner->getConnId() : 0), packet);
					}
				}
			}

			if (droperType == ET_MONSTER)
			{
				if (owner != NULL)
				{
					m_freeTick = pMap->getTick() + 40 * 1000;
					m_ownerName = owner->getName();
				}
				else
				{
					m_freeTick = pMap->getTick() - 10 * 1000;
					m_ownerName = "";
				}
			}
			else if (droperType == ET_PLAYER)
			{
				m_freeTick = pMap->getTick() - 10 * 1000;
				m_ownerName = "";
			}
		}
	}
	m_DropTime		= pMap->getNow();
	m_endTick		= pMap->getTick() + 60 * 1000;
	m_autoPick		= autoPick;
}

void CDropItemGroup::reset()
{
	m_map = NULL;

	m_centerPos.x = 0;
	m_centerPos.y = 0;

	m_freeTick = 0;
	m_endTick = 0;

	for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
	{
		m_dropItems[i].reset();
	}
	m_broadcastItem = 0;
	m_autoPick = 0;
}

int32_t CDropItemGroup::getBroadCastItem()
{
	return m_broadcastItem;
}

void CDropItemGroup::leaveMap()
{
	broadcastRemoveFromMap();
}

bool CDropItemGroup::checkEnd()
{
	return m_map == NULL || m_map->getTick() > m_endTick;
}

void CDropItemGroup::appendInfo(Answer::NetPacket *packet)
{
	if ((m_map == NULL)||(NULL == packet))
	{
		return;
	}

	packet->writeInt16(static_cast<int16_t>(m_centerPos.x));
	packet->writeInt16(static_cast<int16_t>(m_centerPos.y));
	if (m_map->getTick() > m_freeTick)
	{
		packet->writeInt32(0);
	}
	else
	{
		packet->writeInt32(static_cast<int32_t>(m_freeTick-m_map->getTick()));
	}
	packet->writeInt32( m_DropTime );
	packet->writeUTF8(m_ownerName);
	packet->writeInt32(m_autoPick);

	packet->writeInt16(getDropItemCount());
	for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
	{
		if (m_dropItems[i].getItemId() > 0 && m_dropItems[i].getItemClass() > 0)
		{
			packet->writeInt64(m_dropItems[i].getEntityId());
			packet->writeInt32(m_dropItems[i].getItemId());
			packet->writeInt8(m_dropItems[i].getItemClass());
			packet->writeInt64(m_dropItems[i].getOwner());
			packet->writeInt32(m_dropItems[i].getCostType());
			packet->writeInt32(m_dropItems[i].getCostValue());
		}
	}
}

bool CDropItemGroup::hasDropItem(EntityId_t dropid)
{
	for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
	{
		if (m_dropItems[i].getItemId() > 0 && m_dropItems[i].getItemClass() > 0 && m_dropItems[i].getEntityId() == dropid)
		{
			return true;
		}
	}

	return false;
}

int32_t CDropItemGroup::getDropItem(EntityId_t dropid)
{
	for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
	{
		if (m_dropItems[i].getItemId() > 0 && m_dropItems[i].getItemClass() > 0 && m_dropItems[i].getEntityId() == dropid)
		{
			return i;
		}
	}

	return -1;
}

int32_t CDropItemGroup::pick(Player &player, EntityId_t dropid)
{
	if (m_map == NULL || player.getMap() != m_map)
	{
		return ERR_INVALID_DATA;
	}

	int32_t index = getDropItem(dropid);
	if (index < 0)
	{
		return ERR_INVALID_DATA;
	}

	if (!checkOwner(index, player.getCid()))
	{
		return ERR_INVALID_DATA;
	}

	switch (m_dropItems[index].getCostType())
	{
	case CCT_MONEY:
		if ( player.GetCurrency().GetMoneyBindAndNoBind() < m_dropItems[index].getCostValue() )
		{
			return ERR_INVALID_DATA;
		}
		break;
	case CCT_SYS_GOLD:
		if ( player.GetCurrency( CURRENCY_GOLD ) < m_dropItems[index].getCostValue())
		{
			return ERR_INVALID_DATA;
		}
		break;
	case CCT_GOLD:
		if ( player.GetCurrency( CURRENCY_GOLD ) < m_dropItems[index].getCostValue())
		{
			return ERR_INVALID_DATA;
		}
		break;
	}

	MemChrBag add = {};
	add.itemId		= m_dropItems[index].getItemId();
	add.itemClass	= m_dropItems[index].getItemClass(); 
	add.bind		= m_dropItems[index].getBindType();
	add.itemCount	= m_dropItems[index].getItemCount();
	add.endTime		= m_dropItems[index].getItemEndTime();
	add.srcId		= m_dropItems[index].getItemSrcId();

	if ( add.itemClass == IC_PET_EGG )
	{
		std::list<int32_t> Eggs;
		Eggs.push_back(  add.itemId );
		player.GetCharPet().AddEggs( Eggs );
	}
	else if (add.itemCount > 0 && !player.autoUseItem(add))
	{
		int32_t baseid = m_dropItems[index].getItemId();
		if (!player.GetBag().AddItem( add, IACR_PICK ))
		{
			return ERR_BAG_IS_FULL;
		}

		if (add.itemClass == IC_EQUIP)
		{
			MemEquip Equip =  EQUIP_MANAGER.GetMemEquip( add.srcId );
			if ( Equip.base == baseid )
			{
				Equip.owner = player.getCid();
				++Equip.nFlag;
				EQUIP_MANAGER.UpdateMemEquip( Equip );
				player.sendEquipInfo( Equip );
			}
		}
	}

	switch (m_dropItems[index].getCostType())
	{
	case CCT_MONEY:
		player.GetCurrency().DecMoneyAndNoBind(  m_dropItems[index].getCostValue(), MCR_GET_DROP_ITEM, dropid );
		break;
	case CCT_SYS_GOLD:
		player.DecCurrency( CURRENCY_CASH, m_dropItems[index].getCostValue(), GCR_GET_DROP_ITEM, dropid );
		break;
	case CCT_GOLD:
		player.DecCurrency( CURRENCY_GOLD, m_dropItems[index].getCostValue(), GCR_GET_DROP_ITEM, dropid );
		break;
	}

	m_dropItems[index].reset();

	broadcastRemoveDropItem(dropid);
	return ERR_OK;
}

bool CDropItemGroup::hasItems() const
{
	for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
	{
		if (m_dropItems[i].getItemId() > 0 && m_dropItems[i].getItemClass() > 0)
			return true;
	}
	return false;
}

EntityId_t CDropItemGroup::getFirstDropItemId() const
{
	for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
	{
		if (m_dropItems[i].getItemId() > 0 && m_dropItems[i].getItemClass() > 0)
			return m_dropItems[i].getEntityId();
	}
	return 0;
}

int16_t CDropItemGroup::getDropItemCount()
{
	int16_t dropItemCount = 0;
	for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
	{
		if (m_dropItems[i].getItemId() > 0 && m_dropItems[i].getItemClass() > 0)
		{
			++dropItemCount;
		}
	}
	return dropItemCount;
}

bool CDropItemGroup::checkOwner(int32_t index, CharId_t cid)
{
	if (m_map == NULL)
	{
		return false;
	}

	if (m_map->getTick() < m_freeTick)
	{
		CDropItem &dropItem = m_dropItems[index];

		if (dropItem.getOwner() == 0 || dropItem.getOwner() == cid)
		{
			return true;
		}

		return false;
	}
	else
	{
		return true;
	}
}

void CDropItemGroup::broadcastRemoveDropItem(EntityId_t dropid)
{
	if (m_map == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(0, PACK_DISPATCH, SM_REMOVE_DROP_ITEM);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(1);
	packet->writeInt64(dropid);
	packet->setSize(packet->getWOffset());
	m_map->broadcast(packet);
}

void CDropItemGroup::broadcastRemoveFromMap()
{
	if (m_map == NULL)
	{
		return;
	}

	int16_t dropItemCount = getDropItemCount();
	if (dropItemCount > 0)
	{
		NetPacket *packet = GAME_SERVICE.popNetpacket(0, PACK_DISPATCH, SM_REMOVE_DROP_ITEM);
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32(dropItemCount);
		for (int32_t i = 0; i < MAX_DROPITEM_SIZE; ++i)
		{
			if (m_dropItems[i].getItemId() > 0 && m_dropItems[i].getItemClass() > 0)
			{
				packet->writeInt64(m_dropItems[i].getEntityId());
			}
		}
		packet->setSize(packet->getWOffset());
		m_map->broadcast(packet);
	}
}
