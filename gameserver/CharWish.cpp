#include "stdafx.h"
#include "CharWish.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "Bag.h"
#include "ItemHelper.h"
#include "Currency.h"
#include "Unit.h"

using namespace Answer;

void CExtCharWish::OnLoadFromDB( const PlayerDBData* dbData )
{
	if ( NULL == dbData )
	{
		return;
	}

	m_lstWishs = dbData->m_WishDBData.lstWishs;
	m_nNextId = (int32_t)m_lstWishs.size();
}

void CExtCharWish::OnSaveToDB( PlayerDBData* dbData )
{
	if ( NULL == dbData )
	{
		return;
	}

	dbData->m_WishDBData.lstWishs = m_lstWishs;
}

void CExtCharWish::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_WISH_WISH );
	procList.push_back( CM_WISH_INFO );
	procList.push_back( CM_WISH_REWARD );
}

int32_t CExtCharWish::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return 2;
	}

	switch ( nProcId )
	{
	case CM_WISH_WISH:		return OnWish( inPacket );
	case CM_WISH_INFO:		return OnGetWishInfo( inPacket );
	case CM_WISH_REWARD:	return OnGetWishReward( inPacket );
	}

	return 0;
}

int32_t CExtCharWish::OnWish( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int16_t nBagSlot = inPacket->readInt16();
	std::string info = inPacket->readUTF8(true);

	MemChrBag slotData = m_pPlayer->GetBag().GetSlotData( nBagSlot );
	if ( slotData.itemCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	const CfgItem* pItem = CFG_DATA.getItem( slotData.itemId );
	if ( NULL == pItem )
	{
		return ERR_INVALID_DATA;
	}

	if ( pItem->type != 160 )
	{
		return ERR_INVALID_DATA;
	}

	--slotData.itemCount;
	m_pPlayer->GetBag().SetSlotData( nBagSlot, slotData, ICR_WISH, 0 );

	int32_t Now = m_pPlayer->getNow();
	int32_t itemId = slotData.itemId;

	CharWishInfo wx;
	wx.nId = ++m_nNextId;
	wx.nItemId = itemId;
	wx.nStartTime = Now;
	wx.nGetReward = 0;
	wx.strInfo = info;
	m_lstWishs.push_back( wx );

	sendWishInfo();
	SendWishIcon();

	int16_t Proc = inPacket->getProc();
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), Proc, 0 );
	return 0;
}

int32_t CExtCharWish::OnGetWishInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return 2;
	}

	sendWishInfo();
	return 0;
}

int32_t CExtCharWish::OnGetWishReward( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nId = inPacket->readInt32();

	for ( std::list<CharWishInfo>::iterator iter = m_lstWishs.begin(); iter != m_lstWishs.end(); ++iter )
	{
		if ( iter->nId == nId )
		{
			if ( iter->nGetReward )
			{
				return ERR_INVALID_DATA;
			}

			int32_t nNowTime = m_pPlayer->getNow();
			int32_t v5 = nNowTime - iter->nStartTime;
			int32_t nItemId = iter->nItemId;

			const CfgWishReward* pReward = CFG_DATA.GetWishRewardTable()->GetReward( nItemId, v5 );
			if ( NULL == pReward )
			{
				return ERR_INVALID_DATA;
			}

			if ( !m_pPlayer->GetBag().AddItem( pReward->vReward, IACR_WISH ) )
			{
				return ERR_INVALID_DATA;
			}

			iter->nGetReward = 1;
			sendWishInfo();
			SendWishIcon();
			return 0;
		}
	}

	return 0;
}

void CExtCharWish::sendWishInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !canGetReward() )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_WISH_INFO );
	if ( NULL == packet )
	{
		return;
	}

	for ( std::list<CharWishInfo>::iterator iter = m_lstWishs.begin(); iter != m_lstWishs.end(); ++iter )
	{
		if ( !iter->nGetReward )
		{
			packet->writeInt32( iter->nId );
			packet->writeInt32( iter->nStartTime );
			packet->writeUTF8( iter->strInfo );
			break;
		}
	}

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtCharWish::SendWishIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	int8_t nCanGetReward = 0;
	int32_t nLeftTime = 0;
	int32_t nItemId = 0;

	for ( std::list<CharWishInfo>::iterator iter = m_lstWishs.begin(); iter != m_lstWishs.end(); ++iter )
	{
		if ( !iter->nGetReward )
		{
			nCanGetReward = 1;
			nLeftTime = CFG_DATA.GetWishRewardTable()->GetLeftTime( iter->nItemId, iter->nStartTime );
			nItemId = iter->nItemId;
			break;
		}
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_WISH_ICON );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( nCanGetReward );
	packet->writeInt32( nLeftTime );
	packet->writeInt32( nItemId );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CExtCharWish::AppendWishInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	uint32_t nOldOffset = packet->getWOffset();
	int8_t nCount = 0;
	packet->writeInt8( 0 );

	for ( std::list<CharWishInfo>::iterator iter = m_lstWishs.begin(); iter != m_lstWishs.end(); ++iter )
	{
		packet->writeUTF8( iter->strInfo );
		if ( ++nCount > 2 )
		{
			break;
		}
	}

	uint32_t nNewOffset = packet->getWOffset();
	packet->setWOffset( nOldOffset );
	packet->writeInt8( nCount );
	packet->setWOffset( nNewOffset );
}

bool CExtCharWish::canGetReward()
{
	for ( std::list<CharWishInfo>::iterator iter = m_lstWishs.begin(); iter != m_lstWishs.end(); ++iter )
	{
		if ( !iter->nGetReward )
		{
			return true;
		}
	}
	return false;
}

int32_t CExtCharWish::getLeftTime()
{
	for ( std::list<CharWishInfo>::iterator iter = m_lstWishs.begin(); iter != m_lstWishs.end(); ++iter )
	{
		if ( !iter->nGetReward )
		{
			return CFG_DATA.GetWishRewardTable()->GetLeftTime( iter->nItemId, iter->nStartTime );
		}
	}
	return 0;
}
