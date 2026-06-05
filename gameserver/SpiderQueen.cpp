#include "SpiderQueen.h"
#include "WorldBoss.h"
#include "GameService.h"

CSqiderQueen::CSqiderQueen( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
{

}

CSqiderQueen::~CSqiderQueen()
{

}

void CSqiderQueen::stopActivity()
{
	m_nState = AS_END;
	if ( !WORLDBOSS.IsAllSpiderQueenDie() )
	{
		WORLDBOSS.KillAllSpiderQueen();
		broadcastTimeEnd();
	}
	BroadcastActivityState();
}

void CSqiderQueen::StopActivityBySqiderQueenDie()
{
	broadcastKillAllSqiderQueen();
	stopActivity();
}

void CSqiderQueen::broadcastStart()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_SQ_ACTIVITY_START );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CSqiderQueen::broadcastTimeEnd()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_SQ_ACTIVITY_END_BY_TIME );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CSqiderQueen::broadcastKillAllSqiderQueen()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_SQ_ACTIVITY_END_BY_SQ_DIE );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}