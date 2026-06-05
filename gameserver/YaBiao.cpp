#include "stdafx.h"
#include "YaBiao.h"
#include "GameService.h"

using namespace Answer;

CYaBiao::~CYaBiao()
{
}

void CYaBiao::broadcastReady()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( 444 );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}

void CYaBiao::broadcastStart()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( 445 );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}

void CYaBiao::broadcastTimeEnd()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( 446 );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}
