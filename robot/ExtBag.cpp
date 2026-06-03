#include "stdafx.h"

#include "ExtBag.h"
#include "Robot.h"
#include "CfgData.h"
#include "ClientServer.h"

using namespace Answer;

CExtBag::CExtBag()
{
	OnCleanUp();
}

CExtBag::~CExtBag()
{
}

void CExtBag::OnCleanUp()
{
	bzero( m_equip, sizeof( m_equip ) );
	bzero( m_bag, sizeof( m_bag ) );

	m_nBagSize		= 0;
	m_nCanOpenSize	= 0;
	m_nLeftTime		= 0;
}

void CExtBag::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( SM_SEND_BAG_INFO );
	procList.push_back( SM_SEND_BAG_DIRTY );
	procList.push_back( SM_BAG_ITEMS );
	procList.push_back( SM_SEND_EQUIP_INFO );
}

int32_t CExtBag::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case SM_SEND_BAG_INFO:		return onBagInfo( inPacket );
	case SM_SEND_BAG_DIRTY:		return onBagDirty( inPacket );
	case SM_BAG_ITEMS:			return onBagItems( inPacket );
	case SM_SEND_EQUIP_INFO:	return onEquips( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t CExtBag::onBagInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pRobot || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	m_nBagSize		= inPacket->readInt32();
	m_nCanOpenSize	= inPacket->readInt32();
	m_nLeftTime		= inPacket->readInt32();

	return ERR_OK;
}

int32_t CExtBag::onBagDirty( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pRobot || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t bagType = inPacket->readInt8();
	if ( bagType == CBT_BAG )
	{
		int32_t nCount = inPacket->readInt32();
		for ( int32_t i = 0; i < nCount; ++i )
		{
			int8_t bChange = inPacket->readInt8();
			int32_t nSlot = inPacket->readInt32();

			m_bag[nSlot].itemId		= inPacket->readInt32();
			m_bag[nSlot].itemClass	= inPacket->readInt8();
			m_bag[nSlot].itemCount	= inPacket->readInt32();
			m_bag[nSlot].bind		= inPacket->readInt8();
			m_bag[nSlot].endTime	= inPacket->readInt32();
			m_bag[nSlot].srcId		= inPacket->readInt64();

			//if ( bChange == 1 )
			{
				checkAddItem( nSlot );
			}
		}
	}
	else
	{
		if ( bagType == CBT_EQUIP )
		{
			int32_t nCount = inPacket->readInt32();
			for ( int32_t i = 0; i < nCount; ++i )
			{
				int32_t nSlot = inPacket->readInt32();

				m_equip[nSlot].itemId		= inPacket->readInt32();
				m_equip[nSlot].itemClass	= inPacket->readInt8();
				m_equip[nSlot].itemCount	= inPacket->readInt32();
				m_equip[nSlot].bind			= inPacket->readInt8();
				m_equip[nSlot].endTime		= inPacket->readInt32();
				m_equip[nSlot].srcId		= inPacket->readInt64();
			}
		}
	}

	return ERR_OK;
}

int32_t CExtBag::onBagItems( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pRobot || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCount = inPacket->readInt32();
	for ( int32_t i = 0; i < nCount; ++i )
	{
		int32_t nSlot = inPacket->readInt32();

		m_bag[nSlot].itemId		= inPacket->readInt32();
		m_bag[nSlot].itemClass	= inPacket->readInt8();
		m_bag[nSlot].itemCount	= inPacket->readInt32();
		m_bag[nSlot].bind		= inPacket->readInt8();
		m_bag[nSlot].endTime	= inPacket->readInt32();
		m_bag[nSlot].srcId		= inPacket->readInt64();
	}

	return ERR_OK;
}

int32_t CExtBag::onEquips( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pRobot || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nCount = inPacket->readInt8();
	for ( int8_t i = 0; i < nCount; ++i )
	{
		int8_t nSlot = inPacket->readInt8();

		m_equip[nSlot].itemId		= inPacket->readInt32();
		m_equip[nSlot].itemClass	= IC_EQUIP;
		m_equip[nSlot].itemCount	= 1;
		m_equip[nSlot].bind			= inPacket->readInt8();
		m_equip[nSlot].endTime		= inPacket->readInt32();
		m_equip[nSlot].srcId		= inPacket->readInt64();
	}

	return ERR_OK;
}

void CExtBag::SendUseMedicine( int8_t nType )
{
	for ( int32_t i = 0; i < m_nBagSize; ++i )
	{
		if ( m_bag[i].itemClass == IC_NORMAL )
		{
			CfgItem* pItem = CFG_DATA.getItem( m_bag[i].itemId );
			if ( pItem->type == nType && m_pRobot->getLevel() >= pItem->level )
			{
				sendUseItem( i );
				return;
			}
		}
	}

	CfgChrShop* pItem = CFG_DATA.getChrShopTop( nType, m_pRobot->getLevel() );
	if ( pItem != NULL )
	{
		sendBuyItem( pItem->Index, 99 );
	}
}

void CExtBag::checkAddItem( int32_t nSlot )
{
	if ( m_bag[nSlot].itemClass == IC_EQUIP )
	{
		const CfgEquip *pCfgEquip = CFG_DATA.getEquip( m_bag[nSlot].itemId );
		if ( NULL == pCfgEquip )
		{
			return;
		}

		if ( pCfgEquip->m_nLevel > m_pRobot->getLevel() )
		{
			return;
		}

		//if ( pCfgEquip->m_nSoulLevel > m_pRobot->GetSoulLevel() )
		//{
		//	return;
		//}

		if ( pCfgEquip->m_nJob != 0 && pCfgEquip->m_nJob != m_pRobot->getJob() )
		{
			return;
		}

		int8_t equipPlace = getEquipPlace( pCfgEquip->m_nType );
		if ( equipPlace == -1 )
		{
			return;
		}

		if ( m_equip[equipPlace].itemId < m_bag[nSlot].itemId )
		{
			sendDressEquip( nSlot, equipPlace );
		}
	}
	else if ( m_bag[nSlot].itemClass == IC_NORMAL )
	{
		CfgItem* pItem = CFG_DATA.getItem( m_bag[nSlot].itemId );
		if ( NULL == pItem )
		{
			return;
		}

		if ( m_pRobot->getLevel() < pItem->level )
		{
			return;
		}

		if ( pItem->type != 95 )	// 人物技能书
		{
			return;
		}

		m_pRobot->GetExtSkill().CheckLearnSkill( m_bag[nSlot].itemId, nSlot );
	}
}

int8_t CExtBag::getEquipPlace( int8_t nEquipType )
{
	switch ( nEquipType )
	{
	case ET_WEAPON:				return EQUIP_SLOT_WEAPON;
	case ET_NECK:				return EQUIP_SLOT_NECK;
	case ET_HAND:				return EQUIP_SLOT_HAND;
	case ET_CLOSE:				return EQUIP_SLOT_CLOTH;
	case ET_HEAD:				return EQUIP_SLOT_HEAD;
	case ET_SHOES:				return EQUIP_SLOT_SHOES;
	case ET_BELT:				return EQUIP_SLOT_BELT;
	case ET_RING:				return EQUIP_SLOT_RING;
	default: break;
	}
	return -1;
}

void CExtBag::sendDressEquip( int32_t nBagSlot, int8_t nEquipSlot )
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nBagSlot );
	packet->writeInt8( nEquipSlot );

	packet->setType( PACK_PROC );
	packet->setProc( CM_EQUIP_DRESS );
	packet->setSize( packet->getWOffset() );

	m_pRobot->Dispatch( packet );
}

void CExtBag::sendUseItem( int32_t nSlot )
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nSlot );
	packet->writeInt32( ET_PLAYER );

	packet->setType( PACK_PROC );
	packet->setProc( CM_USE_ITEM );
	packet->setSize( packet->getWOffset() );

	m_pRobot->Dispatch( packet );
}

void CExtBag::sendBuyItem( int32_t nIndex, int32_t nCount )
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nIndex );
	packet->writeInt32( nCount );

	packet->setType( PACK_PROC );
	packet->setProc( CM_BUY_GAME_CHR_ITEM );
	packet->setSize( packet->getWOffset() );

	m_pRobot->Dispatch( packet );
}
