#include "MoLingRuQin.h"
#include "MapManager.h"
#include "Timer.h"
#include "Map.h"
#define  FLUSH_TIME  10 * 60 //10分钟刷新一次


CMoLingRuQin::CMoLingRuQin( const CfgActivity& cfgActivity)
:CActivity( cfgActivity )
{
	m_LastFlushTime = 0;
}

CMoLingRuQin::~CMoLingRuQin()
{

}

void CMoLingRuQin::CheckActivity()
{
	if ( !checkData() )		// 日期
	{
		m_nState = AS_TIME_OUT;
		return;
	}

	if ( !checkWeek() )
	{
		m_nState = AS_NOT_START;
		return;
	}

	bool bRightLine			= checkLine();
	ACTIVITY_STATE nState	= checkTime();
	switch ( nState )
	{
	case AS_NOT_START:
		{
			if ( m_nState == AS_END )
			{
				m_nState = AS_NOT_START;
			}
			else if ( m_nState == AS_RUNNING )
			{
				if ( bRightLine )
				{
					stopActivity();
					BroadcastActivityState();
				}
				m_nState = AS_NOT_START;
			}
		}
		break;
	case AS_END:
		{
			if ( m_nState == AS_RUNNING )
			{
				if ( bRightLine )
				{
					stopActivity();
					BroadcastActivityState();
				}
				m_nState = AS_END;
			}
			m_nState = AS_END;
		}
		break;
	case AS_READY:
		{
			if ( m_nState == AS_END || m_nState == AS_NOT_START )
			{
				m_nState = AS_READY;
				if ( bRightLine )
				{
					BroadcastActivityState();
					broadcastReady();
				}
			}
		}
		break;
	case AS_RUNNING:
		{
			if ( m_nState == AS_READY )
			{
				if ( bRightLine )
				{
					startActivity();
					BroadcastActivityState();
					broadcastStart();
				}
				m_nState = AS_RUNNING;
			}
			FlushNpc();
		}
		break;
	default:
		return;
	}
}


void CMoLingRuQin::FlushNpc()
{
	int32_t NowTime = TIMER.GetNow();
	if ( NowTime - m_LastFlushTime >= FLUSH_TIME )
	{
		int32_t AddTime = getLeftTime() > FLUSH_TIME ? FLUSH_TIME:getLeftTime();
		int32_t EndTime = NowTime + AddTime;
		Int32Vector::const_iterator it = m_cfgActivity.maps.begin();
		for ( ; it != m_cfgActivity.maps.end(); ++it )
		{
			Map* pMap = MAP_MANAGER.GetMap(*it);
			if ( NULL == pMap )
			{
				continue;
			}

			MAP_MANAGER.PostMsg( pMap->GetRunnerId(), GMC_MO_LING_RU_QIN_START, pMap, this, EndTime );
		}
		m_LastFlushTime = NowTime;
	}
}

void CMoLingRuQin::startActivity()
{
	m_nState = AS_RUNNING;
	FlushNpc();
}

void CMoLingRuQin::stopActivity()
{
	m_nState = AS_NOT_START;
}

