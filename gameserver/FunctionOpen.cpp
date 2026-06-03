#include "FunctionOpen.h"
#include "WorldBoss.h"
#include "KaiFuHuoDong.h"
#include "Player.h"
CFunctionOpen::CFunctionOpen()
{

}

CFunctionOpen::~CFunctionOpen()
{

}

void CFunctionOpen::OnCleanUp()
{
	m_OpenedList.clear();
}

void CFunctionOpen::InitFunctionOpen( int32_t TaskId, int32_t Level )
{
	FunctionOpenCfgMap CfgTable = CFG_DATA.GetOpenFunctionTable();
	FunctionOpenCfgMap::iterator it = CfgTable.begin();
	for ( ; it != CfgTable.end(); ++it )
	{
		if ( TaskId > 0 )
		{
			if ( it->second.TaskId > 0 )
			{
				CfgTask *pTask	=  CFG_DATA.getTask( it->second.TaskId );
				if ( NULL == pTask )
				{
					continue;
				}
				CfgTask *pCfgLastTrunk = CFG_DATA.getTask( TaskId );
				if ( pCfgLastTrunk != NULL )
				{
					if ( pCfgLastTrunk->main_order <= pTask->main_order )
					{
						continue;
					}
					else
					{
						m_OpenedList.push_back( it->first );
					}
				}
			}
		}	
		else
		{
			if ( it->second.TaskId <= 0 )
			{
				if ( it->second.Level <= Level )
				{
					m_OpenedList.push_back( it->first );
				}
				else
				{
					continue;
				}
			}
		}
	}
}

void CFunctionOpen::CheckFunctionOpne( int32_t TaskId, int32_t Level )
{
	std::list<int32_t> NewOpenList;
	NewOpenList.clear();
	FunctionOpenCfgMap CfgTable = CFG_DATA.GetOpenFunctionTable();
	FunctionOpenCfgMap::iterator it = CfgTable.begin();
	for ( ; it != CfgTable.end(); ++it )
	{
		if ( TaskId > 0 )
		{
			if ( it->second.TaskId <= 0 )
			{
				continue;
			}
			CfgTask *pTask	=  CFG_DATA.getTask( it->second.TaskId );
			if ( NULL == pTask )
			{
				continue;
			}
			CfgTask *pCfgLastTrunk = CFG_DATA.getTask( TaskId );
			if ( pCfgLastTrunk != NULL )
			{
				if ( pCfgLastTrunk->main_order < pTask->main_order )
				{
					continue;
				}
				else
				{
					if ( !IsOpened( it->first ) )
					{
						m_OpenedList.push_back( it->first );
						NewOpenList.push_back( it->first );
					}

				}
			}
		}
		else
		{
			if ( it->second.TaskId > 0 )
			{
				continue;
			}
			if ( it->second.Level <= Level )
			{
				if ( !IsOpened(it->first) )
				{
					m_OpenedList.push_back( it->first );
					NewOpenList.push_back( it->first );
				}
			}
			else
			{
				continue;
			}
		}
	}
	std::list<int32_t>::iterator itList = NewOpenList.begin();
	for ( ; itList != NewOpenList.end(); ++itList )
	{
		FunctionInit(*itList);
	}
}

void CFunctionOpen::FunctionInit( int32_t FunctionId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	switch( FunctionId )
	{
	case FT_BOSS:
		{
			WORLDBOSS.SendWorldBossIcon( m_pPlayer );
			break;
		}
	case FT_HUO_DONG_DA_TING:
		{
			m_pPlayer->GetPlayerDailyActivity().SendHuoDongDaTingIcon();
			break;
		}
	case FT_JIANG_LI_DA_TING:
		{
			m_pPlayer->GetPlayerDailyActivity().SendJiangLiDaTingIcon();
			break;
		}
	case FT_CYCLE_TASK:
		{
			m_pPlayer->GetCharTaskCycle().OpenCycleTask();
			break;
		}
	case FT_SHOU_CHONG_ICON:
		{
			m_pPlayer->GetPlayerYunYingHd().SendShouChongIcon();
			break;
		}
	case FT_NEW_SERVER_TE_HUI:
		{
			m_pPlayer->GetPlayerYunYingHd().SendTeHuiIcon();
			break;
		}
	case FT_EVERYDAY_SHOUCHONG:
		{
			m_pPlayer->GetPlayerYunYingHd().SendEveryDayChongZhiIcon();
			break;
		}
	case FT_TOU_ZI:
		{
			m_pPlayer->GetPlayerGetTouZi().SendTouZiIcon();
			break;
		}
	case FT_KAI_FU_HUO_DONG:
		{
			KAI_FU_HUO_DONG.SendKaiFuHuoDongIcon( m_pPlayer );
			break;
		}
	case FT_HALL_OF_FAME:
		{
			m_pPlayer->GetCharHallOfFame().SendIconState();
			break;
		}
	case FT_GUAN_WEI:
		{
			m_pPlayer->GetPlayerGuanWei().InitGuanWei();
			break;
		}
	case FT_CHOU_JIANG:
		{
			m_pPlayer->GetPlayerChouJiang().SendHuoDongIcon();
			break;
		}
	case FT_QI_FU:
		{
			m_pPlayer->GetPlayerQiFu().SendHuoDongIcon();
			break;
		}

	default:
		break;
	}
}

bool CFunctionOpen::IsOpened( int32_t FunctionId )
{
	FunctionOpenCfg* pCfg = CFG_DATA.GetOpenFunctionCfg( FunctionId );
	if ( pCfg == NULL )
	{
		return true;
	}
	std::list<int32_t>::iterator it = m_OpenedList.begin();
	for ( ; it != m_OpenedList.end(); ++it )
	{
		if ( *it == FunctionId )
		{
			return true;
		}
	}
	return false;
}