#include "stdafx.h"

#include "GMBackstage.h"
#include "GameService.h"
#include "Timer.h"

using namespace Answer;

CGMBackstate::CGMBackstate()
:m_nLastTick(0)
{
}

CGMBackstate::~CGMBackstate()
{

}

//初始化数据
void CGMBackstate::Init()
{
	initBroadcast();
	initBanChat();
}

void CGMBackstate::initBroadcast()
{

}

void CGMBackstate::initBanChat()
{
	MySqlDBGuard db( DBPOOL );
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "SELECT * FROM `gmt_ban_chat` WHERE `expire_time`>%d", TIMER.GetNow() );
	MySqlQuery result = db.query(szSQL);

	while( !result.eof() )
	{
		GMBanChat chat = {};
		chat.nCharId		= result.getInt64Value("cid");
		chat.nExpireTime	= result.getIntValue("expire_time");

		m_mBanChat[chat.nCharId] = chat;
		result.nextRow();
	}
}

void CGMBackstate::OnUpdate()
{
	int64_t curTick = TIMER.GetTick();
	if ( curTick - m_nLastTick < 1000 )
	{
		return;
	}
	m_nLastTick = curTick;

	checkBroadcast();
}

void CGMBackstate::checkBroadcast()
{
	int32_t nowTime = TIMER.GetNow();
	
	for ( GMBroadcastMap::iterator iter = m_mBroadcasts.begin(); iter != m_mBroadcasts.end(); ++iter )
	{
		GMBroadcast& broad = iter->second;
		if ( broad.nStartTime > nowTime )
		{
			continue;
		}

		if ( broad.nCount >= broad.nTimes )
		{
			continue;
		}

		if ( nowTime - broad.nLastTime < broad.nInterval )
		{
			continue;
		}

		sendGMBroadcast( broad.strText, broad.nType );
		++broad.nCount;
		broad.nLastTime = nowTime;
	}
}

void CGMBackstate::sendGMBroadcast( const std::string& text, int8_t type )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_GM_BROADCAST );
	if (NULL == packet)
	{
		return;
	}

	packet->writeUTF8( text );
	packet->writeInt8( type );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.broadcast( packet );
}

int32_t CGMBackstate::GetBanChatLeftTime( CharId_t cid )
{
	MutexGuard lock( m_mutex );	
	GMBanChatMap::iterator iter = m_mBanChat.find( cid );
	if ( iter == m_mBanChat.end() )
	{
		return -1;
	}

	int32_t nowTime = TIMER.GetNow();
	if ( iter->second.nExpireTime > nowTime )
	{
		return iter->second.nExpireTime - nowTime;
	}

	return -1;
}

int32_t CGMBackstate::GetSealLeftTime( CharId_t cid )
{
	MutexGuard lock( m_mutex );	
	GMSealMap::iterator iter = m_mSeal.find( cid );
	if ( iter == m_mSeal.end() )
	{
		return -1;
	}

	int32_t nowTime = TIMER.GetNow();
	if ( iter->second.nExpireTime > nowTime )
	{
		return iter->second.nExpireTime - nowTime;
	}

	return -1;
}

void CGMBackstate::onUpdateGMBroadcast( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	MutexGuard lock( m_mutex );
	int32_t isize = inPacket->readInt32();
	for ( int32_t i = 0; i < isize; ++i )
	{
		int32_t nId			= inPacket->readInt32();
		GMBroadcastMap::iterator iter = m_mBroadcasts.find( nId );
		if ( iter != m_mBroadcasts.end() )
		{
			iter->second.strText	= inPacket->readUTF8( true );
			iter->second.nType		= inPacket->readInt8();
			iter->second.nStartTime	= inPacket->readInt32();
			iter->second.nInterval	= inPacket->readInt32();
			iter->second.nTimes		= inPacket->readInt32();
		}
		else
		{
			std::string strText	= inPacket->readUTF8( true );
			int8_t	nType		= inPacket->readInt8();
			int32_t nStartTime	= inPacket->readInt32();
			int32_t nInterval	= inPacket->readInt32();
			int32_t nTimes		= inPacket->readInt32();
			m_mBroadcasts[nId]	= GMBroadcast( nId, strText, nType, nStartTime, nInterval, nTimes );
		}
	}
}

void CGMBackstate::onUpdateGMBanChat( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	MutexGuard lock( m_mutex );
	int32_t isize = inPacket->readInt32();
	for ( int32_t i = 0; i < isize; ++i )
	{
		CharId_t nCharId			= inPacket->readInt64();
		GMBanChatMap::iterator iter = m_mBanChat.find( nCharId );
		if ( iter != m_mBanChat.end() )
		{
			iter->second.nExpireTime	= inPacket->readInt32();
		}
		else
		{
			GMBanChat chat = {};
			chat.nCharId		= nCharId;
			chat.nExpireTime	= inPacket->readInt32();
			m_mBanChat[nCharId]	= chat;
		}
	}
}

void CGMBackstate::onUpdateGMSeal( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}

	MutexGuard lock( m_mutex );
	int32_t isize = inPacket->readInt32();
	for ( int32_t i = 0; i < isize; ++i )
	{
		CharId_t nCharId	= inPacket->readInt64();
		int32_t nExpireTime	= inPacket->readInt32();
		GMSealMap::iterator iter = m_mSeal.find( nCharId );
		if ( iter != m_mSeal.end() )
		{
			iter->second.nExpireTime	= nExpireTime;
			
		}
		else
		{
			GMSeal seal = {};
			seal.nCharId		= nCharId;
			seal.nExpireTime	= nExpireTime;
			m_mSeal[nCharId]	= seal;
		}

		if ( nExpireTime > TIMER.GetNow() )
		{
			GAME_SERVICE.KickUser( nCharId );
		}
	}
}
