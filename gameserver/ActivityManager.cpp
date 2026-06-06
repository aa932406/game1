#include "stdafx.h"

#include "ActivityManager.h"
#include "GameService.h"
#include "Timer.h"
#include "DaTiHD.h"
#include "FamilyWar.h"
#include "TerritoryWar.h"
#include "HorseRacing.h"
#include "FamilyLight.h"
#include "MoLingRuQin.h"
#include "TianJiangBaoXiang.h"
#include "VipGuaJi.h"
#include "SpiderQueen.h"
#include "CityWar.h"
#include "CampWar.h"
#include "PeerlessWar.h"
#include "ActivityWorldBoss.h"
#include "CXinMaiMap.h"
#include "CRefreshMonster.h"
#include "CrossTower.h"
#include "KaiFuBoss.h"
#include "UltimateChallenge.h"
#include "RongLian.h"
#include "YaBiao.h"
#include <algorithm>

using namespace Answer;

CActivityManager::CActivityManager()
{
}

CActivityManager::~CActivityManager()
{

}

//���ʼ������
void CActivityManager::Init()
{
	const CfgActivityTable &cfgAllActivity = CFG_DATA.getAllActivity();
	CfgActivityTable::const_iterator iter = cfgAllActivity.begin();
	CfgActivityTable::const_iterator eiter = cfgAllActivity.end();

	bool TerritorySign = true;
	for ( ; iter != eiter; ++iter )
	{
		const CfgActivity& cfgActivity = iter->second;
		CActivity* pActivity = NULL;
		switch ( cfgActivity.typeId )
		{
		case ATI_FAMILY_WAR:		pActivity = new CFamilyWar( cfgActivity );						break;
		case ATI_HORSE_RACING:		pActivity = new CHorseRacing( cfgActivity );					break;
		case ATI_FAMILY_LIGHT:		pActivity = new CFamilyLight( cfgActivity );					break;
		case ATI_MO_LING_RU_QIN:	pActivity = new CMoLingRuQin( cfgActivity );					break;
		case ATI_DA_TI_HUO_DONG:	pActivity = new CDaTiHD( cfgActivity );							break;
		case ATI_BAO_XIANG:			pActivity = new CTianJiangBaoXiang(cfgActivity);				break;
		case ATI_TERRITORY_WAR:		pActivity = new CTerritoryWar( cfgActivity, TerritorySign );	break;
		case ATI_SPIDER_QUEEN:		pActivity = new CSqiderQueen( cfgActivity );					break;
		// �·��� - ���Է������°汾
		case ATI_WORLD_BOSS:		pActivity = new CActivityWorldBoss( cfgActivity );				break;
		case ATI_CAMP_WAR:			pActivity = new CCampWar( cfgActivity );						break;
		case ATI_PEERLESS_WAR:		pActivity = new CPeerlessWar( cfgActivity );					break;
		case ATI_CITY_WAR:			pActivity = new CCityWar( cfgActivity );						break;
		case ATI_CROSS_TOWER:		pActivity = new CCrossTower( cfgActivity );					break;
		case ATI_KAI_FU_BOSS:		pActivity = new CKaiFuBoss( cfgActivity );						break;
		case ATI_ULTIMATE_CHALLENGE:	pActivity = new CUltimateChallenge( cfgActivity );				break;
		case ATI_RONG_LIAN:			pActivity = new CRongLian( cfgActivity );						break;
		case ATI_YA_BIAO:			pActivity = new CYaBiao( cfgActivity );							break;
		case ATI_XIN_MAI_MAP:	pActivity = new CXinMaiMap( cfgActivity );			break;
		case ATI_REFRESH_MONSTER:	pActivity = new CRefreshMonster( cfgActivity );		break;			break;
		default: break;
		}
		if ( pActivity != NULL )
		{
			pActivity->Init();
			m_mActivity[pActivity->GetId()] = pActivity;
		}
		else
		{
			LOG_ERROR( "CActivityManager::Init() actid=%d create Activity fail!!!\n", cfgActivity.id );
		}
	}
}

void CActivityManager::OnUpdate()
{
	VIP_GUA_JI_SINGLETON.CheckStar();
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL )
		{
			pActivity->CheckActivity();
		}
	}
}

void CActivityManager::SendActivityInfo( Player* player, int32_t nId )
{
	ActivityMap::iterator iter = m_mActivity.find( nId );
	if ( iter != m_mActivity.end() )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL )
		{
			pActivity->SendPlayerActivityInfo( player );
		}
	}
}

int32_t CActivityManager::GiveDailyReward( Player* player, int32_t nId )
{
	ActivityMap::iterator iter = m_mActivity.find( nId );
	if ( iter != m_mActivity.end() )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL )
		{
			return pActivity->GiveDailyReward( player );
		}
	}
	return ERR_INVALID_DATA;
}

int32_t	CActivityManager::HaveRewardCount( Player* Player, int32_t nId )
{
	ActivityMap::iterator iter = m_mActivity.find( nId );
	if ( iter != m_mActivity.end() )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL )
		{
			return pActivity->HaveRewardCount( Player );
		}
	}
	return 0;
}

bool CActivityManager::IsActivityRunning( int32_t id )
{
	ActivityMap::iterator iter = m_mActivity.find( id );
	if ( iter == m_mActivity.end() )
	{
		return false;
	}

	CActivity* pActivity = iter->second;
	if ( NULL == pActivity )
	{
		return false;
	}

	return pActivity->IsRuning();
}

CActivity* CActivityManager::GetActivity( int32_t id )
{
	ActivityMap::iterator iter = m_mActivity.find( id );
	if ( iter != m_mActivity.end() )
	{
		return iter->second;
	}

	return NULL;
}

//��ȡ���л������д�뵽���ݰ���
void CActivityManager::AppendActivityState(Answer::NetPacket *packet)
{
	if (NULL == packet)
	{
		return;
	}
	tm localnow		= TIMER.GetLocalNow();
	int8_t nWeek	= TIMER.GetWeekDay();

	int32_t nCount = m_mActivity.size();
	packet->writeInt8( 0 );
	packet->writeInt32( nCount );
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		if( pActivity != NULL )
		{
			nCount++;
			packet->writeInt32( pActivity->GetId() );
			packet->writeInt32( pActivity->GetState() );
		}
	}

	uint32_t oldwoffset = packet->getWOffset();
	packet->setWOffset( 1 );
	packet->writeInt32( nCount );
	packet->setWOffset( oldwoffset );
}

FamilyId_t	CActivityManager::GetFamilyWarWinner()
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CFamilyWar* pFamilyWar = dynamic_cast<CFamilyWar*>( iter->second );
		if ( pFamilyWar != NULL )
		{
			return pFamilyWar->GetWinFamily();
		}
	}
	return 0;
}

std::string CActivityManager::GetFamilyWarWinnerName()
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CFamilyWar* pFamilyWar = dynamic_cast<CFamilyWar*>( iter->second );
		if ( pFamilyWar != NULL )
		{
			return pFamilyWar->GetFamilyName();
		}
	}
	return "";
}

std::string CActivityManager::GetFamilyWarLeaderName()
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CFamilyWar* pFamilyWar = dynamic_cast<CFamilyWar*>( iter->second );
		if ( pFamilyWar != NULL )
		{
			return pFamilyWar->GetFamilyLeaderName();
		}
	}
	return "";
}

void CActivityManager::OnFamilyWarResult( int32_t nActId, FamilyId_t nFamilyId, int16_t nWinTimes, string FamilyName, string LeadyerName  )
{
	ActivityMap::iterator iter = m_mActivity.find( nActId );
	if ( iter != m_mActivity.end() )
	{
		CFamilyWar* pFamilyWar = dynamic_cast<CFamilyWar*>( iter->second );
		if ( pFamilyWar != NULL )
		{
			return pFamilyWar->OnFamilyWarResult( nFamilyId, nWinTimes, FamilyName, LeadyerName );
		}
	}
}

void CActivityManager::OnTerritoryWarResult( int32_t nActId, std::string winners )
{
	ActivityMap::iterator iter = m_mActivity.find( nActId );
	if ( iter != m_mActivity.end() )
	{
		CTerritoryWar* pTerritoryWar = dynamic_cast<CTerritoryWar*>( iter->second );
		if ( pTerritoryWar != NULL )
		{
			return pTerritoryWar->OnTerritoryWarResult( winners );
		}
	}
}

void CActivityManager::GetActicityIconState( IconStateList& iconList )
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL )
		{
			pActivity->GetIconState( iconList );
		}
	}
}

void CActivityManager::OnTerritoryWarInfo( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_TERRITORY_INFO );
	if (NULL == packet)
	{
		return;
	}

	int32_t nCount = 0;
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL && pActivity->GetType() == ATI_TERRITORY_WAR )
		{
			CTerritoryWar* pTerritoryWar = dynamic_cast<CTerritoryWar*>( pActivity );
			if ( pTerritoryWar != NULL )
			{
				pTerritoryWar->AppendTerritoryWarInfo( packet, nCount );
			}
		}
	}

	uint32_t offset = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( offset );
	packet->setSize( offset );

	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

int8_t CActivityManager::GetTerritoryWarState()
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL && pActivity->GetType() == ATI_TERRITORY_WAR )
		{
			return pActivity->GetState();
		}
	}
	return AS_NOT_START;
}



void CActivityManager::StopSqiderQueen()
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		CSqiderQueen* pSqiderQueen = dynamic_cast<CSqiderQueen*>(pActivity);
		if ( pSqiderQueen != NULL  )
		{
			if ( pSqiderQueen->IsRuning() )
			{
				pSqiderQueen->StopActivityBySqiderQueenDie();
			}
		}
	}
}

void CActivityManager::NotifyActivityInfo( Player* player )
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL  )
		{
			pActivity->NotifyActivityInfo( player );
		}
	}
}

// ========== �·��� - ���Է������°汾 ==========

void CActivityManager::SendActivityRankInfo( Player* player, int32_t nId )
{
	ActivityMap::iterator iter = m_mActivity.find( nId );
	if ( iter != m_mActivity.end() && iter->second != NULL )
	{
		// ���÷��ˢ�·��а���Ϣ
		// ÿ���������ʵ���Լ��ķ��а�߼�
	}
}

void CActivityManager::UpdateActivityState( int32_t nId, int32_t nState )
{
	ActivityMap::iterator iter = m_mActivity.find( nId );
	if ( iter != m_mActivity.end() && iter->second != NULL )
	{
		// ֪ͨ����ͻ��˸��»״̬
	}
}

bool CActivityManager::IsActivityRunningByType( int32_t nType )
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL && pActivity->GetType() == nType && pActivity->IsRuning() )
		{
			return true;
		}
	}
	return false;
}

int32_t CActivityManager::GetCurActivityId()
{
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CActivity* pActivity = iter->second;
		if ( pActivity != NULL && pActivity->IsRuning() )
		{
			return pActivity->GetId();
		}
	}
	return 0;
}

FamilyId_t CActivityManager::GetCityWarWinner()
{
	return m_nCityWarWinner;
}

void CActivityManager::SetCityWarWinner( FamilyId_t nFamilyId )
{
	m_nCityWarWinner = nFamilyId;
}

FamilyId_t CActivityManager::GetPeerlessWarWinner()
{
	return m_nPeerlessWarWinner;
}

void CActivityManager::SetPeerlessWarWinner( FamilyId_t nFamilyId )
{
	m_nPeerlessWarWinner = nFamilyId;
}

void CActivityManager::OnCityWarResult( int32_t nActId, FamilyId_t nWinnerId, const std::string& winnerName )
{
	ActivityMap::iterator iter = m_mActivity.find( nActId );
	if ( iter != m_mActivity.end() )
	{
		SetCityWarWinner( nWinnerId );
		m_sCityWarWinnerName = winnerName;
	}
}

void CActivityManager::OnPeerlessWarResult( int32_t nActId, FamilyId_t nWinnerId, const std::string& winnerName )
{
	ActivityMap::iterator iter = m_mActivity.find( nActId );
	if ( iter != m_mActivity.end() )
	{
		SetPeerlessWarWinner( nWinnerId );
		m_sPeerlessWarWinnerName = winnerName;
	}
}

void CActivityManager::AddTianJiangBaoXiangCount( Player* player, int32_t nCount )
{
	// ���ӽ�����򿪷��������
}

void CActivityManager::ApplyCityWar( Player* player )
{
	if ( NULL == player )
	{
		return;
	}
	for ( ActivityMap::iterator iter = m_mActivity.begin(); iter != m_mActivity.end(); ++iter )
	{
		CCityWar* pCityWar = dynamic_cast<CCityWar*>( iter->second );
		if ( pCityWar != NULL )
		{
			pCityWar->ApplyCityWar( player );
			break;
		}
	}
}

void CActivityManager::SetCrossTowerResult( CharId_t nWinnerId, int32_t nBattle, const std::string& winnerName )
{
	m_nCrossTowerWinner = nWinnerId;
	m_sCrossTowerWinnerName = winnerName;
	m_nCrossTowerBattle = nBattle;
}