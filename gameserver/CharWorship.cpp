#include "stdafx.h"

#include "GameService.h"
#include "Player.h"
#include "CharFamily.h"
#include "FamilyManager.h"
#include "CfgData.h"

using namespace Answer;

CExtCharWorship::CExtCharWorship()
{
	OnCleanUp();
}

CExtCharWorship::~CExtCharWorship()
{
}

void CExtCharWorship::OnCleanUp()
{
	m_nWorshipTimes = 0;
	m_lstChars.clear();
}

void CExtCharWorship::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_nWorshipTimes = dbData.m_WorshipData.nTimes;
	loadCharList( dbData.m_WorshipData.strCharList  );
}

void CExtCharWorship::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_WorshipData.nTimes		= m_nWorshipTimes;
	dbData.m_WorshipData.strCharList= saveCharList();
}

void CExtCharWorship::OnDaySwitch( int32_t nDiffDays )
{
	// 跨天清空崇拜记录
	m_nWorshipTimes = 0;
	m_lstChars.clear();

	SendWorshipInfo();
}

void CExtCharWorship::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( IM_SOCIAL_GAME_WORSHIP );					// 崇拜
}

int32_t CExtCharWorship::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !isFunctionOpen() )
	{
		return ERR_INVALID_DATA;
	}

	switch( nProcId )
	{
	case IM_SOCIAL_GAME_WORSHIP:			return onSocialWorship( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t CExtCharWorship::onSocialWorship( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCharId	= inPacket->readInt64();
	if ( nCharId <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( isTimesLimit() )				// 次数上限
	{
		return ERR_INVALID_DATA;
	}

	if ( isWorshiped( nCharId ) )		// 已经崇拜过了
	{
		return ERR_INVALID_DATA;
	}

	m_lstChars.push_back( nCharId );
	++m_nWorshipTimes;
	m_pPlayer->addExp( 10000 );			// 暂时定1w

	// 同步到社会服务器
	sendSocialWorship( nCharId );
	return ERR_OK;
}

void CExtCharWorship::sendSocialWorship( CharId_t nCharId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_WORSHIP );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt64( nCharId );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharWorship::SendWorshipInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SELF_WORSHIP_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_nWorshipTimes );
	for ( CharIdList::iterator iter = m_lstChars.begin(); iter != m_lstChars.end(); ++iter )
	{
		packet->writeInt64( *iter );
	}
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

bool CExtCharWorship::isFunctionOpen() const
{
	return true;
	//if ( NULL == m_pPlayer )
	//{
	//	return false;
	//}
	//return m_pPlayer->getLevel() >= FAMILY_OPEN_LEVEL;
}

bool CExtCharWorship::isWorshiped( CharId_t nCharId ) const
{
	CharIdList::const_iterator iter = m_lstChars.begin();
	CharIdList::const_iterator eiter = m_lstChars.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( *iter == nCharId )
		{
			return true;
		}
	}
	return false;
}

bool CExtCharWorship::isTimesLimit() const
{
	return m_nWorshipTimes >= 10;
}

void CExtCharWorship::loadCharList( const std::string& str )
{
	StringVector vCharIds = Answer::StringUtility::split( str, ":" );
	if ( vCharIds.empty() )
	{
		return;
	}

	m_nWorshipTimes = 0;
	for ( uint32_t i = 0; i < vCharIds.size(); ++i )
	{
		CharId_t cid = _atoi64( vCharIds[i].c_str() );
		if ( cid > 0 )
		{
			m_lstChars.push_back( cid );
			++m_nWorshipTimes;
		}
	}
}

std::string CExtCharWorship::saveCharList()
{
	if ( m_lstChars.empty() )
	{
		return "";
	}
	std::stringstream ss;
	for ( CharIdList::iterator iter = m_lstChars.begin(); iter != m_lstChars.end(); ++iter )
	{
		ss << *iter << ":";
	}

	return ss.str();
}
