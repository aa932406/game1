
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

void CEquipManager::Init(int32_t line)
{
	// 跨服模式下跳过初始化
	if (line == 9)
		return;

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
		DB_SERVICE.insertMemEquip( 0, equip );
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

void CEquipManager::UpdateMemEquip( int8_t connid, const MemEquip &equip, int32_t nReason )
{
	{
		RwLockWrGuard lock( m_rwEquipLock );
		m_mEquipTable[equip.id] = equip;
	}

	DB_SERVICE.updateMemEquip( connid, equip, nReason );
}

void CEquipManager::DeleteMemEquip( int8_t connid, EquipId_t nEquipId, int32_t nReason )
{
	MemEquip equip;
	bool bFound = false;
	{
		RwLockWrGuard lock( m_rwEquipLock );
		MemEquipTable::iterator iter = m_mEquipTable.find( nEquipId );
		if ( iter != m_mEquipTable.end() )
		{
			equip = iter->second;
			m_mEquipTable.erase( iter );
			bFound = true;
		}
	}

	if ( bFound )
	{
		DB_SERVICE.deleteMemEquip( connid, equip, nReason );
	}
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

void CEquipManager::SendPlayerEquipInfo( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	MemEquipVector vEquip;
	{
		RwLockWrGuard lock( m_rwEquipLock );
		MemEquipTable::const_iterator iter = m_mEquipTable.begin();
		MemEquipTable::const_iterator eiter = m_mEquipTable.end();
		for ( ; iter != eiter; ++iter )
		{
			const MemEquip& equip = iter->second;
			if ( equip.owner != pPlayer->getCid() )
			{
				continue;
			}
			vEquip.push_back( equip );
		}
	}

	if ( !vEquip.empty() )
	{
		SendPlayerEquipInfo( pPlayer, vEquip );
	}
}

void CEquipManager::SendPlayerEquipInfo( Player* pPlayer, const MemEquip &equip )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	int8_t connid = (int8_t)pPlayer->getConnId();
	NetPacket *packet = GAME_SERVICE.popNetpacket( connid, PACK_DISPATCH, SM_EQUIP_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( 1 );
	equip.PackageClientData( packet );
	uint32_t offset = packet->getWOffset();
	packet->setSize( offset );
	GAME_SERVICE.sendPacketTo( connid, pPlayer->getGateIndex(), packet );
}

void CEquipManager::SendPlayerEquipInfo( Player* pPlayer, const MemEquipVector &vEquip )
{
	if ( NULL == pPlayer )
	{
		return;
	}

	int8_t connid = (int8_t)pPlayer->getConnId();
	NetPacket *packet = GAME_SERVICE.popNetpacket( connid, PACK_DISPATCH, SM_EQUIP_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( vEquip.size() );
	MemEquipVector::const_iterator iter = vEquip.begin();
	MemEquipVector::const_iterator eiter = vEquip.end();
	for ( ; iter != eiter; ++iter )
	{
		iter->PackageClientData( packet );
	}
	uint32_t offset = packet->getWOffset();
	packet->setSize( offset );
	GAME_SERVICE.sendPacketTo( connid, pPlayer->getGateIndex(), packet );
}

void CEquipManager::BroadcastEquipInfo( const MemEquip &equip )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_EQUIP_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( 1 );
	equip.PackageClientData( packet );
	uint32_t offset = packet->getWOffset();
	packet->setSize( offset );
	GAME_SERVICE.worldBroadcast( packet );
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

int64_t CEquipManager::getEquipId( int32_t nServerId ) const
{
	// 跨服模式统一使用 serverId=0
	int32_t useServerId = nServerId;
	if ( GAME_SERVICE.getLine() == 9 )
	{
		useServerId = 0;
	}

	RwLockWrGuard lock( m_IdLock );
	std::map<int, ServerNewId>::iterator iter = m_mNewId.find( useServerId );
	if ( iter != m_mNewId.end() )
	{
		// 缓存中的ID已用完，从DB重新获取范围
		if ( iter->second.nNextId >= iter->second.nMaxId )
		{
			CEquipManager* self = const_cast<CEquipManager*>(this);
			self->getEquipIdFromDB( useServerId, iter->second.nNextId, iter->second.nMaxId );
		}
		int64_t ret = iter->second.nNextId;
		iter->second.nNextId = ret + 1;
		return ret;
	}
	else
	{
		// 首次请求该服号的ID，从DB获取
		ServerNewId newId;
		newId.nNextId = 0;
		newId.nMaxId = 0;
		CEquipManager* self = const_cast<CEquipManager*>(this);
		self->getEquipIdFromDB( useServerId, newId.nNextId, newId.nMaxId );
		m_mNewId[useServerId] = newId;
		int64_t ret = newId.nNextId;
		m_mNewId[useServerId].nNextId = ret + 1;
		return ret;
	}
}

void CEquipManager::getEquipIdFromDB( int32_t nServerId, int64_t &nNextId, int64_t &nMaxId )
{
	char szSql[MAX_SQL_LENGTH] = {};

	MySqlDBGuard db(DBPOOL);
	if ( GAME_SERVICE.getLine() == 9 )
	{
		// 跨服模式
		MySqlQuery result = db.query( "call NewEquipId(@OutEquipId)" );
		if ( !result.eof() )
		{
			nNextId = result.getInt64Value( "OutEquipId", 0 );
			nMaxId = nNextId + 20;
		}
		else
		{
			LOG_ERROR( "CEquipManager::GetEquipId() FAIL! time=%d\n", TIMER.GetNow() );
		}
	}
	else
	{
		snprintf( szSql, sizeof( szSql ) - 1, "call NewEquipId(%d,@OutEquipId)", nServerId );
		MySqlQuery result = db.query( szSql );
		if ( !result.eof() )
		{
			int32_t nNewEquipId = result.getIntValue( 0 );
			nNextId = ( static_cast<int64_t>( nServerId ) << 32 ) + nNewEquipId;
			nMaxId = nNextId + 20;
		}
		else
		{
			LOG_ERROR( "CEquipManager::GetEquipId() FAIL! time=%d\n", TIMER.GetNow() );
		}
	}
}
