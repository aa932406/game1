#include "stdafx.h"
#include "SpecialEquip.h"
#include "Player.h"
#include "FunctionOpen.h"
#include "Vip.h"
#include "CharSkill.h"
#include "GameService.h"
#include "CfgData.h"
#include "DataStructs.h"

using namespace Answer;

void CSpecialEquip::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 265 );
	procList.push_back( 266 );
}

int32_t CSpecialEquip::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( nProcId == 265 )
	{
		return OnActivation( inPacket );
	}

	if ( nProcId == 266 )
	{
		SendActivationInfo();
		return ERR_OK;
	}

	return ERR_INVALID_DATA;
}

void CSpecialEquip::InitSkill()
{
	int32_t nRecord = m_pPlayer->getRecord( 1149 );
	for ( int32_t i = 0; i <= 6; ++i )
	{
		if ( ((nRecord >> i) & 1) == 0 )
		{
			continue;
		}

		const SpeciaEquipCfg* pCfg = CFG_DATA.GetSpeciaEquipCfg( i + 1 );
		if ( NULL == pCfg )
		{
			continue;
		}

		m_pPlayer->GetCharSkill().AddOtherSkill( pCfg->nTalentId, 1 );
	}
}

bool CSpecialEquip::IsActivation( int32_t Day )
{
	return ((m_pPlayer->getRecord( 1149 ) >> (Day - 1)) & 1) == 1;
}

int32_t CSpecialEquip::CanActivationCount()
{
	int32_t nCount = 0;
	int32_t nRecord = m_pPlayer->getRecord( 1149 );
	for ( int32_t i = 0; i <= 6; ++i )
	{
		if ( ((nRecord >> i) & 1) != 0 )
		{
			continue;
		}

		const SpeciaEquipCfg* pCfg = CFG_DATA.GetSpeciaEquipCfg( i + 1 );
		if ( NULL == pCfg )
		{
			continue;
		}

		if ( pCfg->nContinueLogin > 0 && m_pPlayer->getRecord( 1011 ) < pCfg->nContinueLogin )
		{
			continue;
		}

		if ( pCfg->nNeedVipLevel > 0 && m_pPlayer->GetPlayerVip().GetVipLevel() < pCfg->nNeedVipLevel )
		{
			continue;
		}

		if ( pCfg->nBuyLimitVipLevel > 0 && m_pPlayer->GetPlayerVip().GetVipLevel() < pCfg->nBuyLimitVipLevel )
		{
			continue;
		}

		++nCount;
	}
	return nCount;
}

int32_t CSpecialEquip::OnActivation( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nIndex = inPacket->readInt32();
	int32_t nOldRecord = m_pPlayer->getRecord( 1149 );
	int32_t nNewRecord = nOldRecord | (1 << (nIndex - 1));
	if ( nOldRecord == nNewRecord )
	{
		return ERR_INVALID_DATA;
	}

	if ( !CanActivation( nIndex ) )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->updateRecord( 1149, nNewRecord );
	SendActivationInfo();
	m_pPlayer->RecalcAttr();

	const SpeciaEquipCfg* pCfg = CFG_DATA.GetSpeciaEquipCfg( nIndex );
	if ( NULL == pCfg )
	{
		return ERR_OK;
	}

	m_pPlayer->GetCharSkill().AddOtherSkill( pCfg->nTalentId, 1 );

	if ( pCfg->nGongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
		if ( packet != NULL )
		{
			packet->writeInt32( pCfg->nGongGaoId );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt32( nIndex );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}

	SendSpecialEquipIcon();
	return ERR_OK;
}

bool CSpecialEquip::CanActivation( int32_t nIndex )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}

	const SpeciaEquipCfg* pCfg = CFG_DATA.GetSpeciaEquipCfg( nIndex );
	if ( NULL == pCfg )
	{
		return false;
	}

	if ( pCfg->nContinueLogin > 0 && m_pPlayer->getRecord( 1011 ) >= pCfg->nContinueLogin )
	{
		return true;
	}

	if ( pCfg->nNeedVipLevel > 0 && m_pPlayer->GetPlayerVip().GetVipLevel() >= pCfg->nNeedVipLevel )
	{
		return true;
	}

	if ( pCfg->nNeedGold > 0 && m_pPlayer->GetPlayerVip().GetVipLevel() >= pCfg->nBuyLimitVipLevel )
	{
		return m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->nNeedGold, GCR_ACT_SPECIAL_EQUIP, 0 );
	}

	return false;
}

void CSpecialEquip::SendActivationInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2D37 );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_pPlayer->getRecord( 1011 ) );
	packet->writeInt32( m_pPlayer->getRecord( 1149 ) );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CSpecialEquip::GetSpecialEquipIcon( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 181 ) )
	{
		return;
	}

	ShowIcon stu;
	stu.nId = 106;
	stu.nState = ( CanActivationCount() > 0 ) ? 1 : 0;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
	IconList.push_back( stu );
}

void CSpecialEquip::SendSpecialEquipIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 181 ) )
	{
		return;
	}

	ShowIcon stu;
	stu.nId = 106;
	stu.nState = ( CanActivationCount() > 0 ) ? 1 : 0;
	stu.nLeftTime = 0;
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;

	// Send via GameService packet (since Player doesn't have SendIconState directly)
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ONE_ICON );
	if ( packet != NULL )
	{
		packet->writeInt32( stu.nId );
		packet->writeInt8( stu.nState );
		packet->writeInt32( stu.nLeftTime );
		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
	}
}
