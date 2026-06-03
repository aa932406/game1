
#include <algorithm>

#include "stdafx.h"
#include "EquipManager.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
using namespace Answer;

CEquipManager::CEquipManager()
{
}

CEquipManager::~CEquipManager()
{
}

void CEquipManager::Init()
{
	MySqlDBGuard db(DBPOOL);

	MemEquip equip;
	MySqlQuery result = db.query("SELECT * FROM `mem_equip` WHERE owner>0");
	while ( !result.eof() )
	{
		equip.CleanUp();
		equip.id				= result.getInt64Value("id");
		equip.base				= result.getIntValue("base");
		equip.owner				= result.getInt64Value("owner");
		equip.star				= result.getIntValue("star");
		equip.starLucky			= result.getIntValue("starLucky");
		equip.addAttr			= result.getIntValue("addAttr");
		equip.UpGradeLucky		= result.getIntValue("UpGradeLucky");
		equip.UpQuality			= result.getIntValue("UpQuality");
		std::string GemString   = result.getStringValue("EquipGem");
		equip.ParesEquipString( GemString );
		m_mEquipTable[equip.id] = equip;

		result.nextRow();
	}
}

void CEquipManager::OnEquipUpdated( const MemEquipVector &memEquips )
{
	for ( MemEquipVector::const_iterator iter = memEquips.begin(); iter != memEquips.end(); ++iter )
	{
		RwLockWrGuard lock( m_rwEquipLock );
		m_mEquipTable[iter->id] = *iter;
	}
}

MemEquip CEquipManager::CreateMemEquip( int32_t nBaseId, int32_t nServerId, CharId_t nCreaterId, int32_t nStar, int32_t nAddAttr )
{
	MemEquip equip;
	const CfgEquip *pCfgEquip = CFG_DATA.GetEquipTable().GetEquip( nBaseId );
	if ( NULL == pCfgEquip )
	{
		LOG_ERROR("CEquipManager::CreateMemEquip() Equip not find! baseid=%d, owner=%d\n", nBaseId, nCreaterId );
		return equip;
	}

	equip.id		= getEquipId( nServerId );
	equip.base		= pCfgEquip->m_nId;
	equip.owner		= nCreaterId;
	equip.addAttr	= nAddAttr;
	equip.star		= nStar;

	if ( 0 == nAddAttr && GetAddAttrCount( pCfgEquip->m_nQuality ) > 0 )
	{
		const CfgEquipAddAttr* pCfgAddAttr = CFG_DATA.GetEquipTable().GetEquipAddAttr( pCfgEquip->m_nLevel );
		if ( NULL == pCfgAddAttr )
		{
			LOG_ERROR("CEquipManager::CreateMemEquip() AddAttr not find! level=%d\n", pCfgEquip->m_nLevel );
			return equip;
		}
		else
		{
			equip.addAttr = pCfgAddAttr->GetRandAttr();
		}
	}

	if ( equip.id > 0 )
	{
		{
			RwLockWrGuard lock( m_rwEquipLock );
			m_mEquipTable[equip.id] = equip;
		}
		DB_SERVICE.insertMemEquip( equip );
	}
	return equip;
}

MemEquip CEquipManager::GetMemEquip( EquipId_t nEquipId )
{
	{
		RwLockWrGuard lock( m_rwEquipLock );
		MemEquipTable::const_iterator iter = m_mEquipTable.find( nEquipId );
		if ( iter != m_mEquipTable.end() )
		{
			return iter->second;
		}
	}

	MemEquip equip;
	return equip;
}

void CEquipManager::UpdateMemEquip( const MemEquip &equip )
{
	bool bSuccess = false;
	{
		RwLockWrGuard lock( m_rwEquipLock );
		MemEquipTable::iterator iter = m_mEquipTable.find( equip.id );
		if ( iter != m_mEquipTable.end() )
		{
			iter->second = equip;
			bSuccess = true;
		}
	}

	if ( bSuccess )
	{
		DB_SERVICE.updateMemEquip( equip );
	}
}

void CEquipManager::DeleteMemEquip( EquipId_t nEquipId )
{
	{
		RwLockWrGuard lock( m_rwEquipLock );
		m_mEquipTable.erase( nEquipId );
	}
	DB_SERVICE.deleteMemEquip( nEquipId );
}

int32_t CEquipManager::GetAddAttrCount( int8_t nQuality )
{
	// 此处直接与策划约定
// 	switch ( nQuality )
// 	{
// 	case IQ_PURPLE:		return 3;
// 	case IQ_GOLD:		return 4;
// 	default: break;
// 	}
	return 0;
}

void CEquipManager::PacketEquipInfo( Answer::NetPacket *packet, const MemEquipVector &memEquips ) const
{
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( memEquips.size() );
	MemEquipVector::const_iterator iter = memEquips.begin();
	MemEquipVector::const_iterator eiter = memEquips.end();
	for ( ; iter != eiter; ++iter )
	{
		packet->writeInt64( iter->id );
		packet->writeInt32( iter->nFlag );
		packet->writeInt32( iter->base );
		packet->writeInt32( iter->star );
		packet->writeInt32( iter->starLucky );
		packet->writeInt32( iter->addAttr );
		packet->writeInt32( iter->UpGradeLucky );
		packet->writeInt32( iter->UpQuality );
		for ( int32_t i = 0; i < EQUIP_GEM_COUNT; i++ )
		{
			packet->writeInt32( iter->GemHole[i] );
		}
	}
}

void CEquipManager::SendPlayerEquipInfo( const Player& player )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_EQUIP_INFO );
	if( NULL == packet )
	{
		return;
	}

	int32_t nCount = 0;
	packet->writeInt32( nCount );
	RwLockWrGuard lock( m_rwEquipLock );
	MemEquipTable::const_iterator iter = m_mEquipTable.begin();
	MemEquipTable::const_iterator eiter = m_mEquipTable.end();
	for ( ; iter != eiter; ++iter )
	{
		const MemEquip& equip = iter->second;
		if ( equip.owner != player.getCid() )
		{
			continue;
		}
		packet->writeInt64( equip.id );
		packet->writeInt32( equip.nFlag );
		packet->writeInt32( equip.base );
		packet->writeInt32( equip.star );
		packet->writeInt32( equip.starLucky );
		packet->writeInt32( equip.addAttr );
		packet->writeInt32( equip.UpGradeLucky );
		packet->writeInt32( equip.UpQuality );
		for ( int32_t i = 0; i < EQUIP_GEM_COUNT; i++ )
		{
			packet->writeInt32( equip.GemHole[i] );
		}
		++nCount;
	}

	if ( nCount > 0 )
	{
		uint32_t oldwoffset = packet->getWOffset();
		packet->setWOffset( 0 );
		packet->writeInt32( nCount );
		packet->setWOffset( oldwoffset );
		packet->setSize( oldwoffset );
		GAME_SERVICE.sendPacketTo( player.getGateIndex(), packet );
	}
	else
	{
		packet->destroy();
	}
}

int64_t CEquipManager::getEquipId( int32_t nServerId ) const
{
	char szSql[MAX_SQL_LENGTH] = {};
	snprintf( szSql, sizeof( szSql ) - 1, "call NewEquipId(%d,@OutEquipId)", nServerId );

	MySqlDBGuard db(DBPOOL);
	MySqlQuery result = db.query( szSql );
	if ( !result.eof() )
	{
		int32_t nNewEquipId = result.getIntValue( 0 );
		if ( nNewEquipId > 0 )
		{
			return ( static_cast<CharId_t>( nServerId ) << 32 ) + nNewEquipId;
		}
	}

	LOG_ERROR( "CEquipManager::GetEquipId() FAIL! time=%d\n", TIMER.GetNow() );
	return 0;
}

void CEquipManager::ChangeOwner( EquipId_t nEquipId, CharId_t nOwner )
{
	MemEquip equip;
	{
		RwLockWrGuard lock( m_rwEquipLock );
		MemEquipTable::iterator iter = m_mEquipTable.find( nEquipId );
		if ( iter != m_mEquipTable.end() )
		{
			iter->second.owner = nOwner;
			equip = iter->second;
		}
	}

	if ( equip.owner != nOwner )
	{
		return;
	}

	Player* pPlayer = GAME_SERVICE.getPlayer( nOwner, 0, false );
	if ( NULL == pPlayer )
	{
		return;
	}

	pPlayer->sendEquipInfo( equip );
}
