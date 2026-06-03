#include "EquipRansom.h"
#include "DBService.h"
#include "GameService.h"

CEquipRansom::CEquipRansom()
{

}

CEquipRansom::~CEquipRansom()
{

}

void CEquipRansom::OnPlayerLogin( CharId_t Cid )
{
	Answer::MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_char_ransom` WHERE CharId =%lld or KillerId=%lld",Cid,Cid);

	Answer::MySqlQuery result = db.query( szSQL );
	
	Answer::RwLockWrGuard lock( m_DropEquipLock );
	while ( !result.eof() )
	{
		DropEquipInfo equip;
		equip.CharId			= result.getInt64Value("CharId");
		equip.CharName			= result.getStringValue("CharName");
		equip.KillerId			= result.getInt64Value("KillerId");
		equip.KillerName		= result.getStringValue("KillerName");
		equip.CanGetLastTime	= result.getIntValue("CanGetLastTime");
		equip.itemId			= result.getIntValue("ItemId");
		equip.itemClass			= result.getIntValue("ItemClass");
		equip.itemCount			= result.getIntValue("ItemCount");
		equip.bind				= result.getIntValue("Bind");
		equip.endTime			= result.getIntValue("EndTime");
		equip.srcId				= result.getInt64Value("SrcId");
		equip.Mid				= result.getIntValue("Mid");

		m_DropEquipMap[equip.srcId] = equip;

		result.nextRow();
	}
}

void CEquipRansom::GetRansomInfo( CharId_t Cid, RANSOM_ITEM_LIST& EquipList )
{
	Answer::RwLockWrGuard lock( m_DropEquipLock );
	std::map<EquipId_t,DropEquipInfo>::iterator it = m_DropEquipMap.begin();
	for ( ; it != m_DropEquipMap.end(); ++it )
	{
		if ( it->second.CharId == Cid && it->second.CanGetLastTime > Answer::DayTime::now() )
		{
			EquipList.push_back(it->second);
		}
	}
}

void CEquipRansom::PackRansomInfo( Answer::NetPacket *packet, RANSOM_ITEM_LIST& EquipList )
{
	if ( NULL == packet )
	{
		return;
	}
	int32_t nSize = EquipList.size();
	packet->writeInt32( nSize );
	std::list<DropEquipInfo>::iterator it = EquipList.begin();
	for ( ; it != EquipList.end(); ++it)
	{
		packet->writeInt64( it->CharId );	
		packet->writeUTF8( it->CharName	);
		packet->writeInt64( it->KillerId );
		packet->writeUTF8( it->KillerName );
		packet->writeInt32( it->CanGetLastTime - Answer::DayTime::now() );
		packet->writeInt32( it->itemId );
		packet->writeInt8( it->itemClass );
		packet->writeInt32( it->itemCount );
		packet->writeInt8( it->bind );		
		packet->writeInt32( it->endTime );
		packet->writeInt64( it->srcId	);
		packet->writeInt32( it->Mid );
	}
}

void CEquipRansom::GetSpoilsInfo( CharId_t Cid, RANSOM_ITEM_LIST& EquipList )
{
	Answer::RwLockWrGuard lock( m_DropEquipLock );
	std::map<EquipId_t,DropEquipInfo>::iterator it = m_DropEquipMap.begin();
	for ( ; it != m_DropEquipMap.end(); ++it )
	{
		if ( it->second.KillerId == Cid && it->second.CanGetLastTime > Answer::DayTime::now() )
		{
			EquipList.push_back( it->second );	
		}
	}
}

void CEquipRansom::GetRansomEquip( EquipId_t EquipId, DropEquipInfo& EquipInfo )
{
	Answer::RwLockWrGuard lock( m_DropEquipLock );
	std::map<EquipId_t,DropEquipInfo>::iterator it = m_DropEquipMap.find( EquipId );
	if ( it != m_DropEquipMap.end() )
	{
		EquipInfo = it->second;
	}
}

void CEquipRansom::OnUpdatedRansom( Answer::NetPacket *packet )
{
	if ( NULL == packet )
	{
		return;
	}
	int8_t  UpdateType	= packet->readInt8();
	if ( ADD_RANSOM == UpdateType )
	{
		DropEquipInfo DropEquip;
		DropEquip.CharId				= packet->readInt64();	
		DropEquip.CharName				= packet->readUTF8(true);
		DropEquip.KillerId				= packet->readInt64();
		DropEquip.KillerName			= packet->readUTF8(true);
		DropEquip.CanGetLastTime		= packet->readInt32();
		DropEquip.itemId				= packet->readInt32();
		DropEquip.itemClass				= packet->readInt8();
		DropEquip.itemCount				= packet->readInt32();
		DropEquip.bind					= packet->readInt8();
		DropEquip.endTime				= packet->readInt32();
		DropEquip.srcId					= packet->readInt64();
		DropEquip.Mid					= packet->readInt32();
		Answer::RwLockWrGuard lock( m_DropEquipLock );
		m_DropEquipMap[DropEquip.srcId] = DropEquip;
	}
	else if ( SUB_RANSOM == UpdateType )
	{
		EquipId_t nEquipId = packet->readInt64();
		Answer::RwLockWrGuard lock( m_DropEquipLock );
		std::map<EquipId_t,DropEquipInfo>::iterator it = m_DropEquipMap.find( nEquipId );
		if ( it != m_DropEquipMap.end() )
		{
			m_DropEquipMap.erase( it );
		}
	}
}

void CEquipRansom::DeleteRansom( EquipId_t nEquipId )
{
	Answer::RwLockWrGuard lock( m_DropEquipLock );
	std::map<EquipId_t,DropEquipInfo>::iterator it = m_DropEquipMap.find( nEquipId );
	if ( it != m_DropEquipMap.end() )
	{
		m_DropEquipMap.erase( it );
	}
	DB_SERVICE.OnDleRansom( nEquipId );
}

void CEquipRansom::AddRansom( DropEquipInfo &EquipInfo )
{
	Answer::RwLockWrGuard lock( m_DropEquipLock );
	m_DropEquipMap[EquipInfo.srcId] = EquipInfo;
	DB_SERVICE.OnAddRansom( EquipInfo );
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	if ( EquipInfo.KillerId > 0 )
	{
		packet->writeInt32( BCI_DROP_EQUIP );
		packet->writeUTF8(  EquipInfo.KillerName );
		packet->writeInt64( EquipInfo.KillerId );
		packet->writeUTF8(  EquipInfo.CharName );
		packet->writeInt64( EquipInfo.CharId );
		packet->writeInt32( EquipInfo.itemId );
		packet->writeInt64( EquipInfo.srcId );
	}
	else
	{
		packet->writeInt32( BCI_DROP_EQUIP_2 );
		packet->writeInt32( EquipInfo.Mid );
		packet->writeUTF8(  EquipInfo.CharName );
		packet->writeInt64( EquipInfo.CharId );
		packet->writeInt32( EquipInfo.itemId );
		packet->writeInt64( EquipInfo.srcId );
	}
	
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}


