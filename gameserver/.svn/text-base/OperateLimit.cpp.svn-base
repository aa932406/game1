
#include "stdafx.h"
#include "OperateLimit.h"
#include "Player.h"
#include "GameService.h"

using namespace Answer;

CExtOperateLimit::CExtOperateLimit()
{
}

CExtOperateLimit::~CExtOperateLimit()
{
}

void CExtOperateLimit::OnCleanUp()
{
	m_mOperateLimit.clear();
}

void CExtOperateLimit::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_mOperateLimit = dbData.m_OperateLimit.m_mOperateLimit;
	if ( !CheckIsLimitedForever( PR_OPEN_THIRED_FIGHT_PET ) )
	{
		AddLimitCount( PR_OPEN_THIRED_FIGHT_PET, 2 );
	}
}

void CExtOperateLimit::OnSaveToDB( PlayerDBData& dbData )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	int32_t start_line = 0;
	int32_t LimitCount = 0;
	OperateLimitMap::iterator iter = m_mOperateLimit.begin();
	OperateLimitMap::iterator eiter = m_mOperateLimit.end();
	for ( ; iter != eiter; ++iter )
	{
		OperateLimit& limit = iter->second;
		if ( limit.LimitId > PR_MAX_TEMP_VALUE )
		{
			LimitCount = limit.LimitCount;
			OperateLimit stu = {};
			stu.LimitId		= limit.LimitId;
			stu.LimitCount	= LimitCount;
			dbData.m_OperateLimit.m_mOperateLimit[stu.LimitId] = stu;
		}
	}
}


int32_t	CExtOperateLimit::GetLimitCount( int32_t LimitId ) const
{
	OperateLimitMap::const_iterator iter = m_mOperateLimit.find( LimitId );
	if ( iter != m_mOperateLimit.end() )
	{
		return iter->second.LimitCount;
	}

	return 0;
}

void CExtOperateLimit::UpdateLimitCount( int32_t LimitId, int32_t LimitCount )
{
	Int32List updataList;
	OperateLimitMap::iterator iter = m_mOperateLimit.find( LimitId );
	if ( iter != m_mOperateLimit.end() )
	{
		if ( iter->second.LimitCount != LimitCount )
		{
			iter->second.LimitCount = LimitCount;
			iter->second.IsChaned	= true;
			updataList.push_back( LimitId );
		}
	}
	else
	{
		OperateLimit limit = {};
		limit.LimitId		= LimitId;
		limit.LimitCount	= LimitCount;
		limit.IsChaned		= true;
		m_mOperateLimit[LimitId] = limit;
		updataList.push_back( LimitId );
	}
	NotifyLimitInfo( updataList );
}

//增加玩家某操作限制数据
void CExtOperateLimit::AddLimitCount( int32_t LimitId, int32_t LimitCount )
{
	if ( 0 == LimitCount )
	{
		return;
	}
	OperateLimitMap::iterator iter = m_mOperateLimit.find( LimitId );
	if ( iter != m_mOperateLimit.end() )
	{
		iter->second.LimitCount += LimitCount;
		iter->second.IsChaned	= true;
	}
	else
	{
		OperateLimit limit = {};
		limit.LimitId		= LimitId;
		limit.LimitCount	= LimitCount;
		limit.IsChaned		= true;
		m_mOperateLimit[LimitId] = limit;
	}

	Int32List updataList;
	updataList.push_back( LimitId );
	NotifyLimitInfo( updataList );
}

//重置玩家某操作限制数据
void CExtOperateLimit::Reset( int32_t LimitId )
{
	Int32List updataList;
	OperateLimitMap::iterator iter = m_mOperateLimit.find( LimitId );
	if ( iter != m_mOperateLimit.end() )
	{
		if ( iter->second.LimitCount != 0 )
		{
			iter->second.LimitCount	= 0;
			iter->second.IsChaned	= true;
			updataList.push_back( iter->second.LimitId );
		}
	}
	NotifyLimitInfo( updataList );
}

void CExtOperateLimit::ResetRange( int32_t MinId, int32_t MaxId, int32_t DiffDay )
{
	Int32List updataList;
	std::list<OperateLimit> AddList;
	OperateLimitMap::iterator iter = m_mOperateLimit.begin();
	OperateLimitMap::iterator eiter = m_mOperateLimit.end();
	for ( ; iter != eiter; ++iter )
	{
		OperateLimit& limit = iter->second;
		if ( limit.LimitCount != 0 && limit.LimitId >= MinId && limit.LimitId <= MaxId )
		{
			if ( DiffDay == 1 && limit.LimitId >= RP_DUNGEON_DAILY_START && limit.LimitId <= RP_DUNGEON_DAILY_END )
			{
				OperateLimit stu = {};
				stu.LimitId		= limit.LimitId +SPECIAL_FLAG;
				stu.LimitCount	= limit.LimitCount;
				stu.IsChaned	= true;
				AddList.push_back( stu );
			}
			limit.LimitCount = 0;
			limit.IsChaned	 = 0;
			updataList.push_back( limit.LimitId );
		}
	}
	std::list<OperateLimit>::iterator it =  AddList.begin();
	for ( ; it != AddList.end(); ++it )
	{
		m_mOperateLimit[it->LimitId] = *it;
	}
	NotifyLimitInfo( updataList );
}

bool CExtOperateLimit::CheckCountIsLimited( int32_t LimitId, int32_t LimitCount ) const
{
	OperateLimitMap::const_iterator iter = m_mOperateLimit.find( LimitId );
	if ( iter != m_mOperateLimit.end() )
	{
		if ( iter->second.LimitCount >= LimitCount )
		{
			return true;//超过次数限制
		}
	}
	return false;
}

//检查玩家是否存在此限制(永久限制)
bool CExtOperateLimit::CheckIsLimitedForever( int32_t LimitId ) const
{
	OperateLimitMap::const_iterator iter = m_mOperateLimit.find( LimitId );
	if ( iter != m_mOperateLimit.end() )
	{
		return true;
	}
	return false;
}

void CExtOperateLimit::NotifyLimitInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_CHR_RECORD );
	if ( NULL == packet )
	{
		return;
	}

	int32_t nCount = 0;
	packet->writeInt32( nCount );

	OperateLimitMap::iterator iter = m_mOperateLimit.begin();
	OperateLimitMap::iterator eiter = m_mOperateLimit.end();
	for ( ; iter != eiter; ++iter )
	{
		OperateLimit& limit = iter->second;
		if ( isNeedNotify( limit.LimitId ) )
		{
			packet->writeInt32( limit.LimitId );
			packet->writeInt32( limit.LimitCount );
			++nCount;
		}
	}

	uint32_t offset = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( offset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CExtOperateLimit::NotifyLimitInfo( const Int32List& rcList )
{
	if ( NULL == m_pPlayer || rcList.empty() )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_CHR_RECORD );
	if ( NULL == packet )
	{
		return;
	}

	int32_t nCount = 0;
	packet->writeInt32( nCount );

	Int32List::const_iterator iter = rcList.begin();
	Int32List::const_iterator eiter = rcList.end();
	for ( ; iter != eiter ; ++iter )
	{
		int32_t nLimitId = *iter;
		if ( !isNeedNotify( nLimitId ) )
		{
			continue;
		}

		int32_t nLimitCount = 0;
		OperateLimitMap::iterator findIter = m_mOperateLimit.find( nLimitId );
		if ( findIter != m_mOperateLimit.end() )
		{
			nLimitCount = findIter->second.LimitCount;
		}
		packet->writeInt32( nLimitId );
		packet->writeInt32( nLimitCount );
		++nCount;
	}

	if ( 0 == nCount )
	{
		packet->destroy();
		return;
	}

	uint32_t offset = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( offset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

bool CExtOperateLimit::isNeedNotify( int32_t nLimitId )
{
 	if ( nLimitId > RP_DUNGEON_DAILY_START && nLimitId < RP_DUNGEON_DAILY_END )
	{
 		return true;
 	}

	if ( nLimitId > PR_DUNGEON_COMPLETED_BEING && nLimitId < PR_DUNGEON_COMPLETED_END )
	{
		return true;
	}

	if ( nLimitId > PR_ACTIVITY_DAILY_REAWRD_START && nLimitId < RP_ACTIVITY_DAILY_REAWRD_END )
	{
		return true;
	}

	switch ( nLimitId )
	{
	case PR_GEM_SLOT_RECORD:
	case PR_TEAM_AUTO_ACCEPT_INVITE:
	case PR_TEAM_AUTO_ACCEPT_APPLY:
	case PR_OPEN_THIRED_FIGHT_PET:
	case PR_XIAO_JV_HUA_SHI_YONG:
	case RP_DAILY_DWW_TIMES:
	case PR_FALL_OF_FAME_FIGHT_TIMES:
	case PR_FALL_OF_FAME_BUY_TIMES:
	case RP_FAMILY_TASK_COUNT:
	case RP_FAMILY_TASK_REWARD:
	case RP_VIP_SITEREVIVE_TIMES:
	case PR_LAST_FINISH_UP_TOWER_DUNGEON:
		return true;
	default:
		break;
	}
	return false;
}

