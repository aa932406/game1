
#include <algorithm>

#include "stdafx.h"
#include "CharSoul.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "PDUDefine.h"

#define EXP_SOUL_RATE				5000		// 经验魂力比率
#define EXP_MIN_VALUE				10000000	// 最小兑换值
#define SOUL_PLAYER_LEVEL_RATE		10			// 魂力等级对人物最大等级加成比率 


using namespace Answer;


CExtCharSoul::CExtCharSoul()
{
	OnCleanUp();
}

CExtCharSoul::~CExtCharSoul()
{
}

void CExtCharSoul::OnCleanUp()
{

}

void CExtCharSoul::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_nLevel = dbData.m_SoulData.nLevel;
	m_nExp	 = dbData.m_SoulData.nSoul;
}

void CExtCharSoul::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_SoulData.nLevel	= m_nLevel;
	dbData.m_SoulData.nSoul		= m_nExp;
}

void CExtCharSoul::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back ( CM_ADD_SOUL );
	procList.push_back ( CM_UPGRADE_SOUL_LEVEL );
}

int32_t CExtCharSoul::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( !IsFunctionOpen() )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case CM_ADD_SOUL:							return onAddSoul( inPacket );
	case CM_UPGRADE_SOUL_LEVEL:					return onUpgradeSoulLevel( inPacket );
	default:	break;
	}
	return ERR_OK;
}

bool CExtCharSoul::IsFunctionOpen() const
{
	return m_pPlayer != NULL && m_pPlayer->getLevel() >= MAX_PLAYER_LEVEL;
}

int32_t CExtCharSoul::onAddSoul( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int64_t nValue = inPacket->readInt64();
	if ( nValue < EXP_MIN_VALUE )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->getExp() < nValue )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->delExp( nValue );
	m_nExp += nValue / EXP_SOUL_RATE;

	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), m_pPlayer->getExp() );
	return ERR_OK;
}

int32_t CExtCharSoul::onUpgradeSoulLevel( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nLevelUpNeedExp = CFG_DATA.GetSoulAttrTable().GetLevelExp( m_nLevel );
	if ( nLevelUpNeedExp < 0 || m_nExp < nLevelUpNeedExp )
	{
		return ERR_INVALID_DATA;
	}

	m_nExp -= nLevelUpNeedExp;
	++m_nLevel;

	if ( m_nLevel % SOUL_PLAYER_LEVEL_RATE == 0 )
	{
		broadcastLevelUp();
		m_pPlayer->autoUpgradeLevel();
	}
	m_pPlayer->recalcAttr();
	m_pPlayer->FillHP();
	m_pPlayer->FillMP();
	SendSoulInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), m_pPlayer->getExp() );
	return ERR_OK;
}

int32_t CExtCharSoul::AddLevel( int32_t Level )
{
	m_nLevel+= Level;
	if ( m_nLevel % SOUL_PLAYER_LEVEL_RATE == 0 )
	{
		broadcastLevelUp();
		m_pPlayer->autoUpgradeLevel();
	}
	m_pPlayer->recalcAttr();
	m_pPlayer->FillHP();
	m_pPlayer->FillMP();
	SendSoulInfo();
	return ERR_OK;
}

void CExtCharSoul::SendSoulInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SOUL_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_nLevel );
	packet->writeInt64( m_nExp );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CExtCharSoul::broadcastLevelUp()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( BCI_SOUL_LEVEL_UP );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeInt32( m_nLevel );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CExtCharSoul::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	const AttrAddonVector& attrAddons = CFG_DATA.GetSoulAttrTable().GetAttrAddon( m_nLevel, m_pPlayer->getJob() );
	for ( uint32_t i = 0; i < attrAddons.size(); ++i )
	{
		if ( attrAddons[i].addon > 0 )
		{
			m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( attrAddons[i].index ), attrAddons[i].addon );
		}
	}
}

int32_t	CExtCharSoul::GetLevel() const
{
	return m_nLevel;
}

int32_t	CExtCharSoul::GetPlayerMaxLevel() const
{
	return MAX_PLAYER_LEVEL + m_nLevel / SOUL_PLAYER_LEVEL_RATE;
}
