#include "stdafx.h"
#include "CharWuHun.h"
#include "Player.h"
#include "CfgData.h"
#include "Bag.h"
#include "CharSkill.h"
#include "Task.h"
#include "GameService.h"

using namespace Answer;

CCharWuHun::CCharWuHun()
{
	memset( m_WuHun, 0, sizeof(m_WuHun) );
}

CCharWuHun::~CCharWuHun()
{
}

void CCharWuHun::OnLoadFromDB( const PlayerDBData& dbData )
{
	memcpy( m_WuHun, dbData.m_WuHunShopDBData.m_WuHun, sizeof(m_WuHun) );

	for ( int32_t i = 0; i < 5; ++i )
	{
		for ( int32_t j = 0; j < 16; ++j )
		{
			int32_t nId = m_WuHun[i][j];
			if ( nId > 0 )
			{
				WuHunItem* pCfg = CFG_DATA.GetWuHunItem( nId );
				if ( pCfg && pCfg->nTalentId > 0 )
				{
					OnAddTalent( pCfg->nTalentId, pCfg->nTalentLevel );
				}
			}
		}
	}
}

void CCharWuHun::OnSaveToDB( PlayerDBData& dbData )
{
	memcpy( dbData.m_WuHunShopDBData.m_WuHun, m_WuHun, sizeof(m_WuHun) );
}

void CCharWuHun::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 653 );
	procList.push_back( 654 );
	procList.push_back( 655 );
	procList.push_back( 656 );
}

int32_t CCharWuHun::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( !inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( nProcId == 654 )
	{
		return onDressWuHun( inPacket );
	}
	else if ( nProcId == 655 )
	{
		return onUnDressWuHun( inPacket );
	}
	else if ( nProcId == 656 )
	{
		return onCreateWuHun( inPacket );
	}
	else if ( nProcId == 653 )
	{
		return onAskWuHunInfo( inPacket );
	}

	return 0;
}

void CCharWuHun::AddCharAttr()
{
	if ( !m_pPlayer )
	{
		return;
	}

	for ( int32_t i = 0; i < 5; ++i )
	{
		for ( int32_t j = 0; j < 16; ++j )
		{
			if ( m_WuHun[i][j] > 0 )
			{
				WuHunItem* pCfg = CFG_DATA.GetWuHunItem( m_WuHun[i][j] );
				if ( pCfg )
				{
					for ( AddAttrList::iterator it = pCfg->lAttrList.begin(); it != pCfg->lAttrList.end(); ++it )
					{
						m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue );
					}
				}
			}
		}
	}
}

int32_t CCharWuHun::onAskWuHunInfo( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	inPacket->readInt32();

	sendWuHunInfo();
	return 0;
}

int32_t CCharWuHun::onDressWuHun( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t Level = inPacket->readInt32();
	int32_t BagSlot = inPacket->readInt32();
	int32_t WuHunSlot = inPacket->readInt32();

	if ( Level <= 0 || Level > 5 )
	{
		return ERR_INVALID_DATA;
	}

	if ( WuHunSlot < 0 || WuHunSlot >= 16 )
	{
		return ERR_INVALID_DATA;
	}

	// Get item from bag
	const MemChrBag& bagSlot = m_pPlayer->GetBag().GetSlotData( BagSlot );
	WuHunItem* pCfg = CFG_DATA.GetWuHunItem( bagSlot.itemId );
	if ( !pCfg || bagSlot.itemClass != 8 )
	{
		return ERR_INVALID_DATA;
	}

	// Check level requirement
	if ( pCfg->nDressLevel > m_pPlayer->getLevel() )
	{
		return ERR_INVALID_DATA;
	}

	// Check quality requirement
	if ( pCfg->nNeedQuality > 0 && GetSuitLevel( Level ) < pCfg->nNeedQuality )
	{
		return ERR_INVALID_DATA;
	}

	// Check slot compatibility
	if ( !checkWuHunPlace( pCfg->nType, WuHunSlot ) )
	{
		return ERR_INVALID_DATA;
	}

	// Replace current WuHun in slot
	int32_t OldId = m_WuHun[Level - 1][WuHunSlot];
	m_WuHun[Level - 1][WuHunSlot] = bagSlot.itemId;

	// Decrement bag item count
	MemChrBag newBagSlot = bagSlot;
	--newBagSlot.itemCount;
	m_pPlayer->GetBag().SetSlotData( BagSlot, newBagSlot, (ITEM_ADD_REASON)IACR_WU_HUN_DRESS, 0 );

	// Return old WuHun to bag
	if ( OldId > 0 )
	{
		WuHunItem* pOld = CFG_DATA.GetWuHunItem( OldId );
		if ( pOld )
		{
			MemChrBag stu;
			memset( &stu, 0, sizeof(stu) );
			stu.itemId = OldId;
			stu.itemClass = 8;
			stu.itemCount = 1;

			if ( !m_pPlayer->GetBag().AddItem( stu, (ITEM_ADD_REASON)IACR_WU_HUN_DRESS ) )
			{
				return ERR_INVALID_DATA;
			}

			if ( pOld->nTalentId > 0 )
			{
				OnRemoveTalent( pOld->nTalentId, pOld->nTalentLevel );
			}
		}
	}

	// Add new talent
	if ( pCfg->nTalentId > 0 )
	{
		OnAddTalent( pCfg->nTalentId, pCfg->nTalentLevel );
	}

	// Send update and recalc
	sendWuHunSlotInfo( Level, WuHunSlot );
	m_pPlayer->RecalcAttr();

	return 0;
}

int32_t CCharWuHun::onUnDressWuHun( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t Level = inPacket->readInt32();
	int32_t WuHunSlot = inPacket->readInt32();

	if ( Level <= 0 || Level > 5 )
	{
		return ERR_INVALID_DATA;
	}

	if ( WuHunSlot < 0 || WuHunSlot >= 16 )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_WuHun[Level - 1][WuHunSlot] <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nId = m_WuHun[Level - 1][WuHunSlot];
	WuHunItem* pOld = CFG_DATA.GetWuHunItem( nId );
	if ( !pOld )
	{
		return ERR_INVALID_DATA;
	}

	// Return to bag
	MemChrBag stu;
	memset( &stu, 0, sizeof(stu) );
	stu.itemId = pOld->nId;
	stu.itemClass = 8;
	stu.bind = 1;
	stu.itemCount = 1;

	if ( !m_pPlayer->GetBag().AddItem( stu, (ITEM_ADD_REASON)IACR_WU_HUN_UNDRESS ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( pOld->nTalentId > 0 )
	{
		OnRemoveTalent( pOld->nTalentId, pOld->nTalentLevel );
	}

	m_WuHun[Level - 1][WuHunSlot] = 0;
	sendWuHunSlotInfo( Level, WuHunSlot );
	m_pPlayer->RecalcAttr();

	return 0;
}

int32_t CCharWuHun::onCreateWuHun( Answer::NetPacket *inPacket )
{
	if ( !inPacket || !m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nId = inPacket->readInt32();
	int8_t CostSpecial = inPacket->readInt8();

	CreateWuHun* pCfg = CFG_DATA.GetCreateWuHun( nId );
	if ( !pCfg )
	{
		return ERR_INVALID_DATA;
	}

	// Check bag space
	if ( m_pPlayer->GetBag().GetFreeSlotCount() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t GongGaoId = 0;
	MemChrBag stu;
	memset( &stu, 0, sizeof(stu) );

	RateItemList Items = pCfg->GetItemRate;
	ItemDataList CostItem = pCfg->ConstItem;

	if ( CostSpecial == 1 )
	{
		if ( pCfg->SpecialCost.m_nId <= 0 )
		{
			return ERR_INVALID_DATA;
		}
		Items = pCfg->GetItemRate2;
		CostItem.push_back( pCfg->SpecialCost );
	}

	// Random selection
	int32_t nRand = RANDOM.generate( 1, 10000 );
	for ( RateItemList::iterator it = Items.begin(); it != Items.end(); ++it )
	{
		if ( it->nRate >= nRand )
		{
			stu.itemId = it->nItemId;
			stu.itemClass = it->nItemClass;
			stu.itemCount = it->nItemCount;
			stu.bind = it->nBind;
			if ( it->nGongGaoId > 0 )
			{
				GongGaoId = it->nGongGaoId;
			}
			break;
		}
		nRand -= it->nRate;
	}

	if ( stu.itemId <= 0 || stu.itemCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	// Remove cost items
	if ( !m_pPlayer->GetBag().RemoveItem( CostItem, (ITEM_DEL_REASON)IDCR_WU_HUN_CREATE ) )
	{
		return ERR_INVALID_DATA;
	}

	// Add reward item
	m_pPlayer->GetBag().AddItem( stu, (ITEM_ADD_REASON)IACR_WU_HUN_CREATE );

	// Broadcast if needed
	WuHunItem* pCfgItem = CFG_DATA.GetWuHunItem( stu.itemId );
	if ( pCfgItem && GongGaoId > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2CD6 );
		if ( packet )
		{
			packet->writeInt32( GongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( stu.itemId );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	// Update task
	if ( pCfgItem )
	{
		m_pPlayer->GetTask().updateTaskCount( pCfgItem->nType );
	}

	// Reply success
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), stu.itemId );

	return 0;
}

void CCharWuHun::sendWuHunInfo()
{
	if ( !m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2EA1 );
	if ( !packet )
	{
		return;
	}

	for ( int32_t i = 0; i < 5; ++i )
	{
		packet->writeInt32( i + 1 );

		int32_t oldoffest = packet->getWOffset();
		packet->writeInt8( 0 ); // placeholder for count

		int8_t Count = 0;
		for ( int32_t j = 0; j < 16; ++j )
		{
			if ( m_WuHun[i][j] > 0 )
			{
				packet->writeInt32( j );
				packet->writeInt32( m_WuHun[i][j] );
				++Count;
			}
		}

		int32_t newwoffset = packet->getWOffset();
		packet->setWOffset( oldoffest );
		packet->writeInt8( Count );
		packet->setWOffset( newwoffset );
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CCharWuHun::sendWuHunSlotInfo( int32_t Level, int32_t Slot )
{
	if ( !m_pPlayer || Level <= 0 || Level > 5 || Slot < 0 || Slot >= 16 )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2EA2 );
	if ( !packet )
	{
		return;
	}

	packet->writeInt32( Level );
	packet->writeInt32( Slot );
	packet->writeInt32( m_WuHun[Level - 1][Slot] );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CCharWuHun::OnAddTalent( int32_t TalentId, int32_t TalentLevel )
{
	if ( m_pPlayer )
	{
		m_pPlayer->GetCharSkill().AddOtherSkill( TalentId, TalentLevel );
	}
}

void CCharWuHun::OnRemoveTalent( int32_t TalentId, int32_t TalentLevel )
{
	if ( m_pPlayer )
	{
		m_pPlayer->GetCharSkill().removeSkillByTalent( TalentId );
	}
}

bool CCharWuHun::checkWuHunPlace( int32_t Type, int32_t Slot )
{
	if ( Type == 1 )
	{
		return Slot >= 0 && Slot <= 4;
	}
	if ( Type == 2 )
	{
		return Slot > 4 && Slot <= 9;
	}
	if ( Type == 3 )
	{
		return Slot > 9 && Slot <= 14;
	}
	if ( Type == 4 )
	{
		return Slot == 15;
	}
	return false;
}

int32_t CCharWuHun::GetSuitLevel( int32_t nLevel )
{
	if ( nLevel <= 0 || nLevel > 5 )
	{
		return 0;
	}

	int32_t Level = 0;
	for ( int32_t i = 0; i < 15; ++i )
	{
		if ( m_WuHun[nLevel - 1][i] <= 0 )
		{
			return 0;
		}

		if ( Level == 0 )
		{
			Level = m_WuHun[nLevel - 1][i];
		}
		else if ( m_WuHun[nLevel - 1][i] < Level )
		{
			Level = m_WuHun[nLevel - 1][i];
		}
	}

	return Level;
}
