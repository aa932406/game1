#include "stdafx.h"
#include "RongLian.h"
#include "GameService.h"
#include "Timer.h"

using namespace Answer;

CRongLian::~CRongLian()
{
}

void CRongLian::broadcastStart()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( 522 );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}

void CRongLian::sendPlayerScore( Player* player )
{
    if ( NULL == player )
    {
        return;
    }

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt32( getLeftTime() );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}
