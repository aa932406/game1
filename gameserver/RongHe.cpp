#include "stdafx.h"
#include "RongHe.h"
#include "Player.h"
#include "CfgData.h"
#include "GameService.h"
#include "GuiGuDaoRen.h"

CRongHe::CRongHe()
{
}

CRongHe::~CRongHe()
{
}

void CRongHe::OnCleanUp()
{
	m_RongLianInfoMap.clear();
}

void CRongHe::OnLoadFromDB( const PlayerDBData& dbData )
{
	// TODO: load from DB when RongHeEquipData is added to PlayerDBData
}

void CRongHe::OnSaveToDB( PlayerDBData& dbData )
{
	// TODO: save to DB when RongHeEquipData is added to PlayerDBData
}

void CRongHe::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 944 );
	procList.push_back( 945 );
	procList.push_back( 946 );
	procList.push_back( 947 );
	procList.push_back( 948 );
}

int32_t CRongHe::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return 10002;
	}

	switch ( nProcId )
	{
	case 944:	return OnRongLian( inPacket );
	case 945:	return OnEquipRongLian( inPacket );
	case 946:	return OnDismantlingEquip( inPacket );
	case 947:	return OnItemRecovery( inPacket );
	case 948:	return OnOneKeyItemRecovery( inPacket );
	default:
		return 10002;
	}
}

int32_t CRongHe::OnRongLian( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}

	int32_t nId = inPacket->readInt32();
	const RongHeCfg* pCfg = CFG_DATA.GetRongHeCfg( nId );
	if ( NULL == pCfg )
	{
		return 2;
	}

	if ( m_pPlayer->GetBag().GetFreeSlotCount() <= 0 )
	{
		m_pPlayer->TiShiInfo( 2048, 0 );
		return 10002;
	}

	RongHeItem resultItem;
	resultItem.CleanUp();

	// Weighted random selection
	int32_t nRand = RANDOM.generate( 1, pCfg->nMaxRate );
	for ( RongHeItemList::const_iterator it = pCfg->lRongHeItemList.begin(); it != pCfg->lRongHeItemList.end(); ++it )
	{
		if ( nRand <= it->nRate )
		{
			resultItem = *it;
			break;
		}
		nRand -= it->nRate;
	}

	if ( resultItem.item.itemId <= 0 )
	{
		return 10002;
	}

	// Remove cost item
	ItemData costItem = pCfg->nCostItem;
	if ( !m_pPlayer->GetBag().RemoveItem( costItem, IDCR_RONG_HE_COST ) )
	{
		return 10002;
	}

	// Add result item
	if ( !m_pPlayer->GetBag().AddItem( resultItem.item, IACR_AUCTION_BUY ) )
	{
		return 10002;
	}

	m_pPlayer->GetBag().ForceSendDirty();
	SendRongHeResult( nId, resultItem.nSuccess, resultItem.item );

	// Broadcast if needed
	if ( resultItem.nGongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet )
		{
			packet->writeInt32( resultItem.nGongGaoId );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt32( costItem.m_nId );
			packet->writeInt32( resultItem.item.itemId );
			packet->writeInt8( resultItem.item.itemClass );
			packet->writeInt32( resultItem.item.itemCount );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	// Reply success
	Answer::NetPacket* reply = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, inPacket->getProc() );
	if ( reply )
	{
		reply->writeInt64( resultItem.nSuccess );
		reply->setSize( reply->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), reply );
	}
	return 0;
}

int32_t CRongHe::OnEquipRongLian( Answer::NetPacket *inPacket )
{
	// TODO: equip fusion - needs EquipRongHeCfg, CfgEquip::m_CanRongHe, CExtEquip API
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}
	return 10002;
}

int32_t CRongHe::OnDismantlingEquip( Answer::NetPacket *inPacket )
{
	// TODO: dismantle equip
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}
	return 10002;
}

int32_t CRongHe::OnItemRecovery( Answer::NetPacket *inPacket )
{
	// TODO: item recovery - needs RongHeReceovery in CfgItem
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}
	return 10002;
}

int32_t CRongHe::OnOneKeyItemRecovery( Answer::NetPacket *inPacket )
{
	// TODO: one-key recovery
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return 2;
	}
	return 10002;
}

void CRongHe::SendAllRongHeInfo()
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 11716 );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( (int32_t)m_RongLianInfoMap.size() );
	for ( RongLianInfoMap::const_iterator it = m_RongLianInfoMap.begin(); it != m_RongLianInfoMap.end(); ++it )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second.nItemId );
		packet->writeInt32( it->second.nCount );
		packet->writeInt32( it->second.nEquipId );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CRongHe::SendOneRongHeInfo( int32_t nSlot )
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 11717 );
	if ( NULL == packet )
	{
		return;
	}

	RongLianInfoMap::const_iterator it = m_RongLianInfoMap.find( nSlot );
	if ( it != m_RongLianInfoMap.end() )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second.nItemId );
		packet->writeInt32( it->second.nCount );
		packet->writeInt32( it->second.nEquipId );
	}
	else
	{
		packet->writeInt32( nSlot );
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CRongHe::SendRongHeResult( int32_t nId, int32_t nSuccess, const MemChrBag& stu )
{
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 11718 );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nId );
	packet->writeInt32( nSuccess );
	packet->writeInt32( stu.itemId );
	packet->writeInt8( stu.itemClass );
	packet->writeInt32( stu.itemCount );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

std::string CRongHe::GetRongHeEquipString()
{
	std::stringstream ss;
	for ( RongLianInfoMap::const_iterator it = m_RongLianInfoMap.begin(); it != m_RongLianInfoMap.end(); ++it )
	{
		if ( it != m_RongLianInfoMap.begin() )
		{
			ss << "\r\n";
		}
		ss << it->first << ":|" << it->second.nItemId << ":|" << it->second.nCount << ":|" << it->second.nEquipId;
	}
	return ss.str();
}

void CRongHe::ParesRongHeEquipString( const std::string& strData )
{
	m_RongLianInfoMap.clear();
	if ( strData.empty() )
	{
		return;
	}

	StringVector vStr = Answer::StringUtility::split( strData, "\r\n" );
	for ( size_t i = 0; i < vStr.size(); ++i )
	{
		StringVector tv = Answer::StringUtility::split( vStr[i], ":|" );
		if ( tv.size() == 4 )
		{
			int32_t nType = atoi( tv[0].c_str() );
			if ( (uint32_t)nType <= 9 )
			{
				RongLianInfo& info = m_RongLianInfoMap[nType];
				info.nItemId = atoi( tv[1].c_str() );
				info.nCount = atoi( tv[2].c_str() );
				info.nEquipId = atoi( tv[3].c_str() );
			}
		}
	}
}
