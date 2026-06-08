#include "Achievement.h"
#include "Player.h"
#include "GameService.h"
CAchievement::CAchievement()
{
	OnCleanUp();
}

CAchievement::~CAchievement()
{

}

void CAchievement::OnCleanUp()
{
	m_AchievementMap.clear();
}

void CAchievement::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_AchievementMap = dbData.m_AchievementData.m_AchievementMap;
}

void CAchievement::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_AchievementData.m_AchievementMap = m_AchievementMap;
}

void CAchievement::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( IM_SOCIAL_GAME_ADD_FRIEND );
	procList.push_back( CM_ACHIEVEMENT_GET_REWARD );
	procList.push_back( CM_ACHIEVEMENT_BUY_XUN_ZHANG_SOCER );
}

int32_t CAchievement::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	switch( nProcId )
	{
	case IM_SOCIAL_GAME_ADD_FRIEND:	
		{
			AddAchievement( AT_FRIEND );
		}
		break;
	case CM_ACHIEVEMENT_GET_REWARD:
		{
			return OnGetAchievemnetReward( inPacket );
		}
	case CM_ACHIEVEMENT_BUY_XUN_ZHANG_SOCER:
		{
			return OnBuyXunZhangSocre( inPacket );
		}
	default:
		break;
	}
	return ERR_OK;
}

int32_t	CAchievement::OnBuyXunZhangSocre( Answer::NetPacket * inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}
	int32_t nIndex = inPacket->readInt32();
	CfgBuyAcSocre* pCfg = CFG_DATA.GetBuyAcScoreCfg(nIndex);
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}
	int64_t HaveCount = m_pPlayer->GetCurrency( static_cast<CURRENCY_TYPE>(pCfg->CostType) );
	if ( pCfg->CostValues <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	if ( pCfg->CostValues > HaveCount )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_pPlayer->DecCurrency( static_cast<CURRENCY_TYPE>(pCfg->CostType), pCfg->CostValues, GCR_BUY_AC_SOCRE ) )
	{
		return ERR_INVALID_DATA;
	}
	m_pPlayer->AddCurrency( CURRENCY_AC_SOCRE, pCfg->GetValues,ACHIEVEMENT_BUY_SOCRE );
	return ERR_OK;
}	

int32_t	CAchievement::OnGetAchievemnetReward( Answer::NetPacket * inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}
	int32_t Index = inPacket->readInt32();
	AchievementMap::iterator it = m_AchievementMap.find(Index);
	if ( it == m_AchievementMap.end() )
	{
		return ERR_INVALID_DATA;
	}
	if ( it->second.AcState != ATS_FINISH )
	{
		return ERR_INVALID_DATA;
	}
	const CfgAchievement* pCfg = CFG_DATA.GetAchievementTable().GetAchievementTask( Index );
	if ( NULL == pCfg )
	{
		return ERR_INVALID_DATA;
	}
	it->second.AcState = ATS_GET_REWARD;
	if ( pCfg->Socre > 0 )
	{
		m_pPlayer->AddCurrency( CURRENCY_AC_SOCRE,pCfg->Socre, ACHIEVEMNET_SOCRE_GET );
	}
	CurrencyList::const_iterator itZY = pCfg->ZhiYuan.begin();
	for ( ; itZY != pCfg->ZhiYuan.end(); ++itZY )
	{
		m_pPlayer->AddCurrency( static_cast<CURRENCY_TYPE>( itZY->Type ), itZY->Values, MCR_ACHIEVEMENT_FINISHED );
	}
	std::list<int32_t> FinishList;
	FinishList.push_back( Index );
	SendFinishAchievement( FinishList );
	return ERR_OK;
}

void CAchievement::AddAchievement( int8_t GroupId, int32_t Effect, int32_t HuoDongId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	bool NeedSys	= false;
	std::list<int32_t> FinishList;
	const AchievementTask CfgTable = CFG_DATA.GetAchievementTable().GetAchievementTaskMap();
	AchievementTask::const_iterator it = CfgTable.begin();
	for ( ; it != CfgTable.end(); ++it )
	{
		if ( it->second.Group == GroupId && m_AchievementMap[it->first].AcState == ATS_NO_FINISH )
		{
			switch( GroupId )
			{
			case AT_TEAM:
			case AT_FRIEND:
			case AT_FAMILY:
			case AT_EQUIP_UP_STAR:
			case AT_PET_ILLUSION:
			case AT_LOGIN:
			case AT_THREE_PET:
			case AT_KILL_BOSS:
			case AT_KILL_MONSSTER:
			case AT_QI_FU_EXP:	
			case AT_QI_FU_MONEY:	
			case AT_CHOU_JIANG:		
			case AT_HALL_FAME:	
				{
					if ( Effect > 0 )
					{
						m_AchievementMap[it->first].FinishCount += Effect;
					}
					else
					{
						m_AchievementMap[it->first].FinishCount++;
					}

					if ( m_AchievementMap[it->first].FinishCount >= it->second.Request.param1 )
					{
						m_AchievementMap[it->first].AcState = ATS_FINISH;
						m_AchievementMap[it->first].Time	= m_pPlayer->getNow();
						NeedSys = true;
						FinishList.push_back( it->first );
					}
				}
				break;
			case AT_PET_KNIGHT:
				{
					int32_t nKnightCount = m_pPlayer->GetCharPet().GetKnightCount();
					if ( nKnightCount >= it->second.Request.param1 )
					{
						m_AchievementMap[it->first].AcState = ATS_FINISH;
						m_AchievementMap[it->first].Time	= m_pPlayer->getNow();
						NeedSys = true;
						FinishList.push_back( it->first );
					}
				}
				break;
			case AT_PET_POINTS_COUNT:
				{
					int32_t Count = m_pPlayer->GetCharPet().HavePetCountByPoints( it->second.Request.param1 );
					if ( Count >= it->second.Request.param2 )
					{
						m_AchievementMap[it->first].AcState = ATS_FINISH;
						m_AchievementMap[it->first].Time	= m_pPlayer->getNow();
						NeedSys = true;
						FinishList.push_back( it->first );
					}
				}
				break;
			case AT_DRESS_EQUIP:
				{
					int32_t Count = m_pPlayer->GetEquip().HaveStarEquipCount( it->second.Request.param1 );
					if ( Count >= it->second.Request.param2 )
					{
						m_AchievementMap[it->first].AcState = ATS_FINISH;
						m_AchievementMap[it->first].Time	= m_pPlayer->getNow();
						NeedSys = true;
						FinishList.push_back( it->first );
					}
				}
				break;
			case AT_KILL_MONSTER_BY_MID:
			case AT_DUNGEON:
				{
					if ( it->second.Request.param1 == Effect )
					{
						m_AchievementMap[it->first].FinishCount++;
						if ( m_AchievementMap[it->first].FinishCount >= it->second.Request.param2 )
						{
							m_AchievementMap[it->first].AcState = ATS_FINISH;
							m_AchievementMap[it->first].Time	= m_pPlayer->getNow();
							NeedSys = true;
							FinishList.push_back( it->first );
						}
					}
				}
				break;
			case AT_LEVEL:
			case AT_GUAN_WEI:
			case AT_INSID_PET_POINTS:
			case AT_WU_LING_POINTS:
			case AT_HUAN_LING_POINTS:
			case AT_LUCK_POINTS:
				{
					if ( Effect >= it->second.Request.param1 )
					{
						m_AchievementMap[it->first].AcState = ATS_FINISH;
						m_AchievementMap[it->first].Time	= m_pPlayer->getNow();
						NeedSys = true;
						FinishList.push_back( it->first );
					}
				}
				break;
			case AT_FA_BAO:
				{
					if ( it->second.Request.param1 == Effect )
					{
						int32_t Level = m_pPlayer->GetPlayerFaBao().GetFaBaoLevel( Effect );
						if ( Level > it->second.Request.param2 )
						{
							m_AchievementMap[it->first].AcState = ATS_FINISH;
							m_AchievementMap[it->first].Time	= m_pPlayer->getNow();
							NeedSys = true;
							FinishList.push_back( it->first );
						}
					}
				}
				break;
			case AT_JUE_WEI:
				{
					if ( Effect <= it->second.Request.param1 )
					{
						m_AchievementMap[it->first].AcState = ATS_FINISH;
						m_AchievementMap[it->first].Time	= m_pPlayer->getNow();
						NeedSys = true;
						FinishList.push_back( it->first );
					}
				}
				break;
			case AT_ACTIVITY:
				{
					if ( it->second.Request.param1 == Effect )
					{
						if ( m_pPlayer->GetPlayerDailyActivity().TodayHaveJoineThisActivity( Effect, HuoDongId ) )
						{
							m_AchievementMap[it->first].FinishCount++;
							m_AchievementMap[it->first].Time = m_pPlayer->getNow();
							if ( m_AchievementMap[it->first].FinishCount >= it->second.Request.param2 )
							{
								m_AchievementMap[it->first].AcState = ATS_FINISH;
								NeedSys = true;
								FinishList.push_back( it->first );
							}
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
	if ( NeedSys )
	{
		SendFinishAchievement( FinishList );
	}
}

void CAchievement::SendAchievementInfo()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ACHIEVEMENT_INFO );
	if (NULL == packet)
	{
		return;
	}
	int32_t nSize = 0;
	int32_t OldOffset = packet->getWOffset();
	packet->writeInt32( nSize );
	AchievementMap::iterator iter = m_AchievementMap.begin();
	for ( ; iter != m_AchievementMap.end(); ++iter )
	{
		if ( iter->second.AcState != ATS_NO_FINISH )
		{
			packet->writeInt32( iter->first );
			packet->writeInt8( iter->second.AcState );
			nSize++;
		}
	}
	int32_t NewOffset = packet->getWOffset();
	packet->setWOffset( OldOffset );
	packet->writeInt32( nSize );
	packet->setWOffset( NewOffset );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);		
}

void CAchievement::SendFinishAchievement( std::list<int32_t> FinishList )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_ACHIEVEMENT_INFO );
	if (NULL == packet)
	{
		return;
	}
	int32_t nSize = 0;
	int32_t OldOffset = packet->getWOffset();
	packet->writeInt32( nSize );

	std::list<int32_t>::iterator it = FinishList.begin();
	for ( ; it != FinishList.end(); ++it )
	{
		AchievementMap::iterator iter = m_AchievementMap.find( *it );
		if ( iter != m_AchievementMap.end() )
		{
			packet->writeInt32( iter->first );
			packet->writeInt8( iter->second.AcState );
			nSize++;
		}
	}

	int32_t NewOffset = packet->getWOffset();
	packet->setWOffset( OldOffset );
	packet->writeInt32( nSize );
	packet->setWOffset( NewOffset );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}
