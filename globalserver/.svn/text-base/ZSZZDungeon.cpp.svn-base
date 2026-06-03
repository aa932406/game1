#include "ZSZZDungeon.h"
#include "SocialService.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace Answer;
#define ZSZZ_DUNGEON_RANK_MAX_COUNT  99

ZSZZDungeonRank::ZSZZDungeonRank()
{

}

ZSZZDungeonRank::~ZSZZDungeonRank()
{

}

void ZSZZDungeonRank::Init()
{
	//PR_LAST_FINISH_UP_TOWER_DUNGEON			= 37206,	//37206 定义在游戏服
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.cid, a.LimitCount, b.name FROM (( SELECT * FROM mem_char_operate_limit WHERE LimitId = 37206 ) AS a LEFT JOIN mem_character AS b ON b.cid = a.cid ) order by a.LimitCount desc limit 99" );
	MySqlQuery result = db.query(szSQL);
	while (!result.eof())
	{
		DungeonRankInfo stu;
		stu.nCharId				= result.getInt64Value("cid");
		stu.nCharName			= result.getStringValue("name");
		stu.nDungeonId			= result.getIntValue("LimitCount");
		m_RankVt.push_back( stu );
		result.nextRow();
	}
}

void ZSZZDungeonRank::OnUpdateRankInfo( Answer::NetPacket* InPacket )
{
	if ( NULL == InPacket )
	{
		return;
	}
	DungeonRankInfo stu;
	stu.nCharId			= InPacket->readInt64();
	stu.nCharName		= InPacket->readUTF8(true);
	stu.nDungeonId		= InPacket->readInt32();
	bool IsInRank = false;
	DungeonRankVct::iterator it = m_RankVt.begin();
	for ( ; it != m_RankVt.end(); ++it )
	{
		if ( it->nCharId == stu.nCharId )
		{
			IsInRank = true;
			it->nDungeonId		= stu.nDungeonId;
			break;
		}
	}
	if ( !IsInRank )
	{
		if ( m_RankVt.size() < ZSZZ_DUNGEON_RANK_MAX_COUNT )
		{
			m_RankVt.push_back(stu);
		}
		else if ( m_RankVt[ZSZZ_DUNGEON_RANK_MAX_COUNT-1].nDungeonId >= stu.nDungeonId )
		{
			return;
		}
		else
		{
			m_RankVt[ZSZZ_DUNGEON_RANK_MAX_COUNT-1] = stu;
		}
		
	}
	SortRank( m_RankVt );
}

void ZSZZDungeonRank::SortRank( DungeonRankVct& m_RankVt )
{
	std::sort( m_RankVt.begin(), m_RankVt.end(), std::greater<DungeonRankInfo>() );
}

void ZSZZDungeonRank::SendCharInfo( SocialPlayer* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	int32_t MyRank		= 0;
	int32_t MyDungeon	= 0;
	DungeonRankVct::iterator it = m_RankVt.begin();
	int8_t Count = 0;

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	int32_t OldOffset = packet->getWOffset();
	int32_t Index = 0;
	packet->writeInt8( Count );
	for ( ; it != m_RankVt.end(); ++it )
	{
		Index++;
		if ( it->nCharId == pPlayer->getCid() )
		{
			MyRank	  = Index;
			MyDungeon = it->nDungeonId;
		}
		if ( Count < 3 )
		{
			Count++;
			packet->writeInt32( Count );
			packet->writeInt64( it->nCharId );
			packet->writeUTF8( it->nCharName );
			packet->writeInt32( it->nDungeonId );
		}
	}
	int32_t NewOffset = packet->getWOffset();
	packet->setWOffset(OldOffset);
	packet->writeInt8(Count);
	packet->setWOffset(NewOffset);
	
	packet->writeInt32( MyRank );
//	packet->writeInt32( MyDungeon );

	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_SEND_ZSZZ_DUNGEON_RANK);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet );
}
