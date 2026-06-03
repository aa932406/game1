#include "GlobalRecord.h"
#include "SocialService.h"
using namespace Answer;

#define MAX_GLOBAL_CHOU_JIANG_RECORD 50			//抽奖记录保存50个
#define MAX_GLOBAL_LUCK_POINT	1000			//最多幸运值1000
#define MAX_GLOBAL_TOU_ZI_RECORD_COUNT 100		//投资记录100条

GlobalRecord::GlobalRecord()
{
	m_CJRecordList.clear();
	m_LuckPoint		= 0;
}

GlobalRecord::~GlobalRecord()
{
	
}

void GlobalRecord::Init()
{
	m_TouZiRecord.reserve(MAX_GLOBAL_TOU_ZI_RECORD_COUNT);
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "SELECT * FROM `mem_global_luck_point` WHERE `id`=1";
	MySqlQuery result = db.query(szSQL);
	while (!result.eof())
	{
		m_LuckPoint	= result.getIntValue("GlobalLuckPint");
		result.nextRow();
	}

	bzero(szSQL,sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_global_chou_jiang_record` ");
	MySqlQuery result_2 = db.query(szSQL);
	while (!result_2.eof())
	{
		GlobalChouJiangRecord Record = {};
		Record.Name			= result_2.getStringValue("Name");
		Record.Cid			= result_2.getInt64Value( "Cid" );
		Record.ItemClass	= result_2.getIntValue( "ItemClass" );
		Record.ItemId		= result_2.getIntValue( "ItemId" );
		Record.ItemCount	= result_2.getIntValue( "ItemCount" );
		m_CJRecordList.push_back( Record );
		result_2.nextRow();
	}

	bzero(szSQL,sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_tou_zi_record` ");
	MySqlQuery result_3 = db.query(szSQL);
	while( !result_3.eof() )
	{
		TouZiRecord Record = {};
		Record.Cid		   = result_3.getInt64Value("Cid");
		Record.Name		   = result_3.getStringValue("Name");
		Record.RecordType  = (int8_t)result_3.getIntValue("RecordType");
		Record.MoneyType   = (int8_t)result_3.getIntValue("MoneyType");
		Record.MoneyValues = result_3.getIntValue("MoneyValues");
		m_TouZiRecord.push_back( Record );
		result_3.nextRow();
	}
}

void GlobalRecord::OnRecvChouJiangRecord( Answer::NetPacket* InPacket )
{
	if ( NULL == InPacket )
	{
		return;
	}
	GlobalChouJiangRecord Record = {};
	Record.Cid			= InPacket->readInt64();
	Record.Name			= InPacket->readUTF8(true);
	Record.ItemClass	= InPacket->readInt8();
	Record.ItemId		= InPacket->readInt32();
	Record.ItemCount	= InPacket->readInt32();
	if ( m_CJRecordList.size() >= MAX_GLOBAL_CHOU_JIANG_RECORD )
	{
		m_CJRecordList.pop_front();
		m_CJRecordList.push_back( Record );
	}
	else
	{
		m_CJRecordList.push_back( Record );
	}
	BroadcastNewRecord( Record );
}

void GlobalRecord::OnRecvTouZiRecord( Answer::NetPacket* InPacket )
{
	if ( NULL == InPacket )
	{
		return;
	}
	TouZiRecord Record = {};
	Record.Cid		   = InPacket->readInt64();
	Record.Name		   = InPacket->readUTF8(true);
	Record.RecordType  = InPacket->readInt8();
	Record.MoneyType   = InPacket->readInt8();
	Record.MoneyValues = InPacket->readInt32();
	if ( m_TouZiRecord.size() >= MAX_GLOBAL_TOU_ZI_RECORD_COUNT )
	{
		m_TouZiRecord[MAX_GLOBAL_TOU_ZI_RECORD_COUNT-1] = Record;
	}
	else
	{
		m_TouZiRecord.push_back( Record );
	}
}

void GlobalRecord::SaveRecordToDB()
{
	char szSQL[MAX_SQL_LENGTH] = "TRUNCATE mem_global_chou_jiang_record";
	MySqlDBGuard db(DBPOOL);
	db.excute(szSQL);

	GlobalCJRecordList::iterator it = m_CJRecordList.begin();
	for ( ; it != m_CJRecordList.end(); ++it )
	{
		bzero( szSQL, sizeof(szSQL) );
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO mem_global_chou_jiang_record ( Cid, Name, ItemClass,ItemId, ItemCount ) VALUES (%lld, '%s',%d, %d,%d) ",\
			it->Cid,it->Name.c_str(),it->ItemClass,it->ItemId,it->ItemCount );
		db.excute(szSQL);

	}

	bzero( szSQL, sizeof(szSQL) );
	snprintf(szSQL, sizeof(szSQL)-1,"TRUNCATE mem_tou_zi_record");
	db.excute(szSQL);

	TouZiRecordVector::iterator iter = m_TouZiRecord.begin();
	for ( ; iter != m_TouZiRecord.end(); ++iter )
	{
		bzero( szSQL, sizeof(szSQL) );
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO mem_tou_zi_record ( Cid, Name, RecordType,MoneyType, MoneyValues ) VALUES (%lld, '%s',%d, %d,%d) ",\
			iter->Cid,iter->Name.c_str(),iter->RecordType,iter->MoneyValues,iter->MoneyValues );
		db.excute(szSQL);
	}
}

void GlobalRecord::OnRecvCleanGlobalLuckPoint( Answer::NetPacket* InPacket )
{
	if ( NULL == InPacket )
	{
		return;
	}
	int8_t AddCount = InPacket->readInt8();
	bool   IsClean  = InPacket->readInt8() == 1 ? true :false; 
	if ( IsClean )
	{
		m_LuckPoint = 0;
	}
	else
	{
		m_LuckPoint += AddCount;
	}

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO mem_global_luck_point (Id) VALUES (1) ON DUPLICATE KEY UPDATE GlobalLuckPint=%d", m_LuckPoint );
	MySqlDBGuard db(DBPOOL);
	db.excute(szSQL);
}

void GlobalRecord::OnRecvCheckGlobalLuckPoint( SocialPlayer*  pSocialPlayer, Answer::NetPacket* InPacket )
{
	if ( NULL == InPacket )
	{
		return;
	}
	int8_t ChouJiangType	= InPacket->readInt8();
	int8_t ChouJiangTimes   = InPacket->readInt8(); 
	bool   Special	= false;
	if ( m_LuckPoint + ChouJiangTimes >= MAX_GLOBAL_LUCK_POINT  )
	{
		Special = true;
	}
	if ( NULL != pSocialPlayer )
	{
		NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
		if (NULL == Packet)
		{
			return;
		}
		Packet->writeInt32( pSocialPlayer->getuid() );
		Packet->writeInt32( pSocialPlayer->getsid() );
		Packet->writeInt32( pSocialPlayer->getGateIndex() );
		Packet->writeInt8( ChouJiangType );
		Packet->writeInt8( ChouJiangTimes );
		Packet->writeInt8( Special ? 1 : 0);			
		Packet->setType(PACK_DISPATCH);
		Packet->setProc(IM_SOCIAL_GAME_ASK_CHOU_JIANG);
		Packet->setSize(Packet->getWOffset());
		SOCIAL_SERVICE.sendPacket(Packet);
	}
}

void GlobalRecord::OnRecvAskChouJiangRecord( SocialPlayer* pPlayer, Answer::NetPacket* InPacket )
{
	if ( NULL == InPacket || NULL == pPlayer )
	{
		return;
	}
	SendChouJiangRecord( pPlayer );	
}

void GlobalRecord::SendChouJiangRecord( SocialPlayer* pPlayer )
{
	Answer::NetPacket *packet = SOCIAL_SERVICE.popNetpacket( );
	if (NULL == packet)
	{
		return;
	}
	int32_t Count = m_CJRecordList.size();
	packet->writeInt32( Count );
	GlobalCJRecordList::iterator it = m_CJRecordList.begin();
	for ( ; it != m_CJRecordList.end(); ++it )
	{
		packet->writeInt64( it->Cid );
		packet->writeUTF8( it->Name );
		packet->writeInt8( it->ItemClass );
		packet->writeInt32( it->ItemId );
		packet->writeInt32( it->ItemCount );
	}
	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_SEND_GLOBAL_CHOU_JIANG_RECORD );
	SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);	
}
	
void GlobalRecord::BroadcastNewRecord( GlobalChouJiangRecord& Record )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt64( Record.Cid );
	packet->writeUTF8( Record.Name );
	packet->writeInt8( Record.ItemClass );
	packet->writeInt32( Record.ItemId );
	packet->writeInt32( Record.ItemCount );
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_SEND_ADD_GLOBAL_CHOU_JIANG_RECORD);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.worldBroadcast( packet );
}

void GlobalRecord::SendAllTouZiRecord( SocialPlayer* pPlayer )
{
	Answer::NetPacket *packet = SOCIAL_SERVICE.popNetpacket( );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( 3 );					//=3投资记录
	int16_t nSize = m_TouZiRecord.size();
	packet->writeInt16( nSize );
	TouZiRecordVector::reverse_iterator it = m_TouZiRecord.rbegin();
	for ( ; it != m_TouZiRecord.rend(); ++it )
	{
		packet->writeUTF8( it->Name );
		packet->writeInt8( it->RecordType );
		packet->writeInt8( it->MoneyType );
		packet->writeUInt32( it->MoneyValues );
	}
	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_SEND_TOU_ZI_INFO );
	SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);	
}

void GlobalRecord::SendOneTouZiRecord( SocialPlayer *pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = SOCIAL_SERVICE.popNetpacket( );
	if (NULL == packet)
	{
		return;
	}
	int32_t nSize = m_TouZiRecord.size();
	if ( nSize <= 0 )
	{
		return;
	}
	int32_t nRand = RANDOM.generate( 0,nSize );
	if ( nRand < 0 || nRand >= nSize )
	{
		return;
	}
	packet->writeUTF8( m_TouZiRecord[nRand].Name );
	packet->writeInt8( m_TouZiRecord[nRand].RecordType );
	packet->writeInt8( m_TouZiRecord[nRand].MoneyType );
	packet->writeUInt32( m_TouZiRecord[nRand].MoneyValues );
	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_SEND_TOU_ZI_RECORD );
	SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);	
}
