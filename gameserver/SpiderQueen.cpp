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
		broadcastEnd( true );
	}
	else
	{
		broadcastEnd( false );
	}
	BroadcastActivityState();
}

void CSqiderQueen::StopActivityBySqiderQueenDie()
{
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

void CSqiderQueen::broadcastEnd( bool IsTimeEnd )
{
	int32_t GongGaoId = 0;
	if ( IsTimeEnd )
	{
		GongGaoId = BCI_SQ_ACTIVITY_END_BY_TIME;
	}
	else
	{
		GongGaoId = BCI_SQ_ACTIVITY_END_BY_SQ_DIE;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( GongGaoId );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}