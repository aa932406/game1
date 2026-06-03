#include "stdafx.h"

#include "CfgData.h"
#include "Family.h"
#include "SocialService.h"
#include "DataStructs.h"
#include "PlayerManager.h"
#include "FamilyManager.h"
#include "PetManager.h"

using namespace Answer;
#define TOTOM_BATTLE_BASE 5000 //图腾10000 加1点战斗力

bool FamilyMemberContributionGreater::operator()( PlayerInfo* pLeft, PlayerInfo* pRight ) const
{
	if ( NULL == pLeft || NULL == pRight )
	{
		return false;
	}
	return pLeft->GetFamilyContribution() > pRight->GetFamilyContribution();
}

Family::Family()
{
	reset();
}

Family::~Family()
{

}

void Family::LoadFromDB( const FamilyDBData& dbData )
{
	m_nId				= dbData.nFamilyId;
	m_strName			= dbData.strName;
	m_nLevel			= dbData.nLevel;
	m_nMoney			= dbData.nMoney;
	m_strNotice			= dbData.strNotice;
	m_AutoAgree			= dbData.AutoAgree;
	m_FamilyTaskCount	= dbData.FamilyTaskCount;
	m_LastFamilyTaskTime= dbData.LastFamilyTaskTime;
	if ( DayTime::daydiff(m_LastFamilyTaskTime) > 0 )
	{
		ResetFamilyCount();
	}
	loadMembers();
	loadPets();
	loadTotom();
	loadLog();

	m_nContribution	= calContribution();
}

void Family::loadMembers()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_chr_family` WHERE `family_id`=%lld", m_nId );
	MySqlQuery result = db.query(szSQL);

	while ( !result.eof() )
	{
		CharId_t nCharId = result.getInt64Value("cid");
		PlayerInfo* pMember = PLAYER_MANAGER.GetPlayerInfo( nCharId );
		if ( NULL == pMember )
		{
			result.nextRow();
			continue;
		}

		pMember->nFamilyId				= m_nId;
		pMember->nFamilyPosition		= result.getIntValue("position");
		pMember->nFamilyContribution	= result.getIntValue("contribute");
		pMember->nFamilyPetContribution	= result.getIntValue("pet_contribute");

		m_vPosition[pMember->nFamilyPosition].push_back( pMember );
		++m_nMemberCount;
		result.nextRow();
	}
}

void Family::loadPets()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_chr_pet` WHERE `family_id`=%lld", m_nId );
	MySqlQuery result = db.query(szSQL);

	while ( !result.eof() )
	{
		PetId_t nPetId = result.getInt64Value("pid");
		CSocialPet* pPet = PET_MANAGER.GetPet( nPetId );
		if ( pPet != NULL )
		{
			m_vTotom[pPet->GetBaseId()].nTotalPoints += pPet->GetPoints() ;	
			m_lstRegistPet.push_back( pPet );
		}
		result.nextRow();
	}
}

void Family::loadTotom()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_family_totom` WHERE `family_id`=%lld", m_nId );
	MySqlQuery result = db.query(szSQL);

	int32_t nNowTime = DayTime::now();
	while ( !result.eof() )
	{
		int32_t nId	= result.getIntValue("totom_id");
		if ( nId > 0 && nId <= MAX_PET_ID )
		{
			m_OpenTotomCount++;
			m_vTotom[nId].nValue		= result.getIntValue("battle");
			m_vTotom[nId].nTotalPoints	= calTotomPoints( nId );
			m_vTotom[nId].nStartTime	= result.getIntValue("start_time");
			if ( nNowTime - m_vTotom[nId].nStartTime > FAMILY_TOTOM_ACTIVE_TIME )
			{
				m_vTotom[nId].nValue = 0;
			}
		}
		result.nextRow();
	}
}

void Family::loadLog()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_family_log` WHERE `id`=%lld ORDER BY `time` DESC LIMIT %d", m_nId, FAMILY_LOG_SIZE );
	MySqlQuery result = db.query(szSQL);

	FamilyLog log = {};
	while ( !result.eof() )
	{
		bzero( &log, sizeof( log ) );

		log.nType		= result.getIntValue("type");
		log.nTime		= result.getIntValue("time");
		log.vParam[0]	= result.getInt64Value("param1");
		log.vParam[1]	= result.getInt64Value("param2");
		log.vParam[2]	= result.getInt64Value("param3");
		log.vParam[3]	= result.getInt64Value("param4");
		log.vParam[4]	= result.getInt64Value("param5");
		m_lstFamilyLog.push_front( log );

		result.nextRow();
	}
}


void Family::reset()
{
	m_nId			= 0;
	m_strName		= "";
	m_nLevel		= 0;
	m_nContribution	= 0;
	m_nMoney		= 0;
	m_nMemberCount	= 0;
	m_strNotice		= "";
	m_AutoAgree		= 1;
	m_FamilyTaskCount		= 0;
	m_LastFamilyTaskTime	= 0;
	m_OpenTotomCount		= 0;
	for ( int8_t i = 0; i < FAMILY_POSITION_COUNT; ++i )
	{
		m_vPosition[i].clear();
	}
	bzero( m_vApplyer, sizeof( m_vApplyer ) );
//	bzero( m_vTotom, sizeof( m_vTotom ) );
}

void Family::Init( FamilyId_t nFamilyId, const std::string& name, SocialPlayer& creater )
{
	m_nId			= nFamilyId;
	m_strName		= name;
	m_nLevel		= 1;
	m_nContribution	= 0;
	m_nMoney		= 0;
	m_nMemberCount	= 1;
	bzero( m_vApplyer, sizeof( m_vApplyer ) );
	m_vPosition[FP_LEADER].push_back( creater.GetPlayerInfo() );
	//自动开帮派图腾
	std::list<int32_t> FreePetList = CFG_DATA.GetFreeOpenTotom();
	std::list<int32_t>::iterator it = FreePetList.begin();
	for ( ; it != FreePetList.end(); ++it )
	{
		OpenTotom(*it);
	}
	sendGameUpdateFamilyInfo( FUR_CREATE );
}

FamilyId_t Family::GetId() const
{
	return m_nId;
}

std::string Family::GetName() const
{
	return m_strName;
}

bool Family::OnApply( PlayerInfo* pApplyer )
{
	for ( int32_t i = 0; i < FAMILY_APPLY_COUNT; ++i ) 
	{
		if ( NULL == m_vApplyer[i] )
		{
			m_vApplyer[i] = pApplyer;
			return true;
		}
		if ( pApplyer == m_vApplyer[i] )
		{
			return false;
		}
	}
	return false;
}

void Family::onSetAutoAgree( int8_t nFlag )
{
	m_AutoAgree = nFlag;
	saveFamilyInfo();
}

bool Family::AutoAddMember( SocialPlayer* pPlayer, PlayerInfo* pInfo )
{
	if ( NULL == pPlayer || NULL == pInfo )
	{
		return false;
	}
	if ( !IsAuto() )
	{
		return false;
	}
	if ( addMember( *pPlayer, pInfo ) )
	{
		saveFamilyInfo();
		return true;
	}
	return false;
}

bool Family::OnApplyReply( SocialPlayer& player, PlayerInfo* pApplyer, bool bAccept )
{
	if ( NULL == pApplyer )
	{
		return false;
	}
	for ( int32_t i = 0; i < FAMILY_APPLY_COUNT; ++i )
	{
		if ( NULL == m_vApplyer[i] )
		{
			return false;
		}

		if ( pApplyer == m_vApplyer[i] )
		{
			if ( bAccept )
			{
				if ( addMember( player, pApplyer ) )
				{
					saveFamilyInfo();
				}
			}
			sendFamilyApplyResult( player.getName(), m_vApplyer[i], bAccept );
			for ( int32_t j = i; j < FAMILY_APPLY_COUNT-1; ++j )
			{
				m_vApplyer[j] = m_vApplyer[j+1];
			}
			m_vApplyer[FAMILY_APPLY_COUNT-1] = NULL;
			return true;
		}
	}

	return false;
}

void Family::OnApplyOperator( SocialPlayer& player, bool bAccept )
{
	bool bNeedSave = false;
	for ( int32_t i = 0; i < FAMILY_APPLY_COUNT; ++i )
	{
		if ( NULL == m_vApplyer[i] )
		{
			return;
		}
		if ( bAccept )
		{
			if ( addMember( player, m_vApplyer[i] ) )
			{
				bNeedSave = true;
			}
		}
		sendFamilyApplyResult( player.getName(), m_vApplyer[i], bAccept );
		m_vApplyer[i] = NULL;
	}
	if ( bNeedSave )
	{
		saveFamilyInfo();
	}
}

bool Family::RegistPet( const SocialPlayer& player, CSocialPet* pPet )
{
	if ( NULL == pPet )
	{
		return false;
	}
	// 军团注册幻兽
	RegPetList::iterator iter = m_lstRegistPet.begin();
	RegPetList::iterator eiter = m_lstRegistPet.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( *iter == pPet )
		{
			return false;
		}
	}
	m_lstRegistPet.push_back( pPet );

	recalTotomPoints( pPet->GetBaseId() );
	recalContribution();
	broadcastRegistPet( player.getName(), player.getCid(), pPet->GetBaseId(), CalPetRegistAddContribute( pPet->GetPoints() ) );
	sendGameUpdateFamilyInfo( FUR_UPDATE );
	SendTotomInfo( player );
	FamilyLog log = {};
	log.nType		= FLT_REGIST_PET;
	log.nTime		= DayTime::now();
	log.vParam[0]	= player.getCid();
	log.vParam[1]	= pPet->GetBaseId();
	log.vParam[2]	= pPet->GetPoints();
	addFamilyLog( log );
	return true;
}

bool Family::UnRegistPet( const SocialPlayer& player, CSocialPet* pPet )
{
	if ( NULL == pPet )
	{
		return false;
	}
	// 军团幻兽取消登记
	RegPetList::iterator iter = m_lstRegistPet.begin();
	RegPetList::iterator eiter = m_lstRegistPet.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( *iter == pPet )
		{
			break;
		}
	}
	if ( iter == m_lstRegistPet.end() )
	{
		return false;
	}
	m_lstRegistPet.erase( iter );
	recalContribution();
	recalTotomPoints( pPet->GetBaseId() );
	sendGameUpdateFamilyInfo( FUR_UPDATE );
	FamilyLog log = {};
	log.nType		= FLT_UNREGIST_PET;
	log.nTime		= DayTime::now();
	log.vParam[0]	= player.getCid();
	log.vParam[1]	= pPet->GetBaseId();
	log.vParam[2]	= pPet->GetPoints();
	addFamilyLog( log );
	return true;
}

bool Family::ActiveTotom( SocialPlayer& player, int32_t nTotomId, int32_t nAddBattle )
{
	if ( nTotomId <= 0 || nTotomId > MAX_PET_ID || nAddBattle <= 0 || nAddBattle > MAX_TOTOM_ADD_BATTLE )
	{
		return false;
	}

	if ( calTotomPoints( nTotomId ) < 2 * TOTOM_BATTLE_BASE )	//图腾2点战斗力才能加持
	{
		return false;
	}

// 	int32_t nNeedLevel = CFG_DATA.GetFamilyTable().GetTotomActiveLevel( nTotomId );
// 	if ( nNeedLevel < 0 )
// 	{
// 		return false;
// 	}
// 
// 	if ( nNeedLevel > m_nLevel )
// 	{
// 		return false;	// 军团等级不够 未激活
// 	}

	Totom& totom = m_vTotom[nTotomId];
	//if ( totom.nTotalPoints < pTotom->nActiveNeedPoints )
	//{
	//	return false;	// 等级幻兽总星级不够 未激活
	//}

	//if ( totom.nValue > 0 )
	//{
	//	return false;	// 图腾已经开启 不能再次激活
	//}

	int32_t nNeedMoney = CFG_DATA.GetFamilyTable().GetTotomActiveCost( nAddBattle );
	if ( nNeedMoney < 0 || nNeedMoney > m_nMoney )
	{
		return false;	// 军团资金不足
	}

	m_nMoney -= nNeedMoney;

	totom.nValue = nAddBattle;
	totom.nStartTime = DayTime::now();
	recalContribution();
	SendTotomInfo( player );
	saveFamilyInfo();
	saveTotomInfo( nTotomId, totom );
	sendGameUpdateFamilyInfo( FUR_UPDATE );
	broadcastGameNeedUpdatePlayerInfo();
	broadcastActiveTotom( player.getName(),player.getCid(), nTotomId, nAddBattle );

	FamilyLog log = {};
	log.nType		= FLT_ACTIVE_TOTOM;
	log.nTime		= DayTime::now();
	log.vParam[0]	= player.getCid();
	log.vParam[1]	= nTotomId;
	log.vParam[2]	= nAddBattle;
	addFamilyLog( log );
	return true;
}

PlayerInfo* Family::getLeader()
{
	if ( m_vPosition[FP_LEADER].empty() )
	{
		return NULL;
	}
	return m_vPosition[FP_LEADER].front();
}

bool Family::addMember( SocialPlayer& player, PlayerInfo* pPlayerInfo )
{
	if ( NULL == pPlayerInfo )
	{
		return false;
	}

	const CfgFamily* pCfgFamily = CFG_DATA.GetFamilyTable().GetFamilyInfo( m_nLevel );
	if ( NULL == pCfgFamily )
	{
		return false;
	}

	if ( m_nMemberCount >= pCfgFamily->nMaxMembers )
	{
		return false;
	}

	pPlayerInfo->nFamilyId			= m_nId;
	pPlayerInfo->nFamilyPosition	= FP_NONE;
	pPlayerInfo->nFamilyApplyCount	= 0;
	FAMILY_MANAGER.CleanApply( pPlayerInfo );

	m_vPosition[FP_NONE].push_back( pPlayerInfo );
	++m_nMemberCount;

	recalContribution();
	sendGameUpdatePlayerInfo( pPlayerInfo );
	broadcastEnterFamily( player.getName(), player.getCid(), pPlayerInfo->strName, pPlayerInfo->nCharId );
	FamilyLog log = {};
	log.nType		= FLT_MEMBER_JOIN;
	log.nTime		= DayTime::now();
	log.vParam[0]	= pPlayerInfo->nCharId;
	addFamilyLog( log );
	//通知成功加入军团
	SocialPlayer* TarPlayer = PLAYER_MANAGER.GetPlayerByCid( pPlayerInfo->nCharId );
	if ( NULL == TarPlayer )
	{
		return true;
	}
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return true;
	}
	packet->writeInt64( pPlayerInfo->nFamilyId );
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_JOINED );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( TarPlayer->getGateIndex(), packet );
	SendFamilyTaskCount(&player);
	return true;
}

bool Family::KickMember( SocialPlayer& player, PlayerInfo* pMember )
{
	if ( NULL == pMember )
	{
		return false;
	}

	if ( !removeMember( pMember ) )
	{
		return false;
	}
	// 广播踢人消息
	broadcastKickMember( player.getName(),player.getCid(), pMember->strName,pMember->nCharId );

	// 发送目标被踢
	SocialPlayer* pPlayer = PLAYER_MANAGER.GetPlayerByCid( pMember->nCharId );
	if ( pPlayer != NULL )
	{
		SOCIAL_SERVICE.replySuccess( pPlayer->getGateIndex(), CM_FAMILY_KICK, pMember->nCharId );
	}

	// 添加踢人日志
	FamilyLog log = {};
	log.nType		= FLT_KICK;
	log.nTime		= DayTime::now();
	log.vParam[0]	= player.getCid();
	log.vParam[1]	= pMember->nCharId;
	addFamilyLog( log );
	return true;
}

bool Family::LeaveMember( PlayerInfo* pMember )
{
	if ( NULL == pMember )
	{
		return false;
	}
	// 退出帮派
	if ( !removeMember( pMember ) )
	{
		return false;
	}
	// 广播离开消息
	broadcastLeaveFamily( pMember->strName,pMember->nCharId );

	// 添加离开日志
	FamilyLog log = {};
	log.nType		= FLT_MEMBER_LEAVE;
	log.nTime		= DayTime::now();
	log.vParam[0]	= pMember->nCharId;
	addFamilyLog( log );
	return true;
}

void Family::AddContribution( SocialPlayer& player, int32_t Contribution, int32_t Money )
{
	m_nContribution += Contribution;
	m_nMoney		+= Money;
	recalContribution();
	FamilyLog log = {};
	log.nType		= FLT_FAMILY_TASK;
	log.nTime		= DayTime::now();
	log.vParam[0]	= player.getCid();
	log.vParam[1]	= Contribution;
	log.vParam[2]	= Money;
	addFamilyLog( log );
}

void Family::AddContribution( SocialPlayer& player, int32_t nMoney, int32_t nGold, int32_t nAddValue )
{
	m_nContribution += nAddValue;
	m_nMoney += CalFamilyContribute( nMoney, nGold );
	if ( m_nMoney > MAX_FAMILY_MONEY )
	{
		m_nMoney = MAX_FAMILY_MONEY;
	}
	 
	recalContribution();

	if ( nMoney > 0 )
	{
		FamilyLog log = {};
		log.nType		= FLT_MONEY;
		log.nTime		= DayTime::now();
		log.vParam[0]	= player.getCid();
		log.vParam[1]	= nMoney;
		addFamilyLog( log );
	}
	if ( nGold > 0 )
	{
		FamilyLog log = {};
		log.nType		= FLT_GOLD;
		log.nTime		= DayTime::now();
		log.vParam[0]	= player.getCid();
		log.vParam[1]	= nGold;
		addFamilyLog( log );
	}
	SendFamilyInfo( player );
}

void Family::OnDestroy()
{
	for ( int32_t i = 0; i < FAMILY_POSITION_COUNT; ++i )
	{
		MemberList::iterator iter = m_vPosition[i].begin();
		MemberList::iterator eiter = m_vPosition[i].end();
		for ( ; iter != eiter; ++iter )
		{
			PlayerInfo* pMember = *iter;
			if ( NULL == pMember )
			{
				continue;
			}

			pMember->nFamilyId				= 0;
			pMember->nFamilyPosition		= FP_NONE;
			pMember->nFamilyContribution	= 0;
			pMember->nFamilyPetContribution	= 0;
			sendGameUpdatePlayerInfo( pMember );
		}
	}
	broadcastFamilyDestroy();
	sendGameUpdateFamilyInfo( FUR_DELETE );
}

void Family::OnUpdateContribution( SocialPlayer& player )
{
	recalContribution();
}


void Family::CheckTotomTime( int32_t nNowTime )
{
	for ( int32_t i = 0; i <= MAX_PET_ID; ++i )
	{
		Totom& totom = m_vTotom[i];
		if ( totom.nValue > 0 && nNowTime - totom.nStartTime > FAMILY_TOTOM_ACTIVE_TIME )
		{
			totom.nValue = 0;
			saveTotomInfo( i, totom );
			sendGameUpdateFamilyInfo( FUR_UPDATE );
			broadcastGameNeedUpdatePlayerInfo();
		}
	}
}

bool Family::removeMember( PlayerInfo* pMember )
{
	for ( int32_t i = 0; i < FAMILY_POSITION_COUNT; ++i )
	{
		MemberList::iterator iter = m_vPosition[i].begin();
		MemberList::iterator eiter = m_vPosition[i].end();
		for ( ; iter != eiter; ++iter )
		{
			if ( *iter == pMember )
			{
				pMember->nFamilyId				= 0;
				pMember->nFamilyPosition		= FP_NONE;
				pMember->nFamilyContribution	= 0;
				pMember->nFamilyPetContribution	= 0;
				m_vPosition[i].erase( iter );
				--m_nMemberCount;

				removeAllPlayerRegPet( pMember->nCharId );
				recalContribution();
				sendGameUpdatePlayerInfo( pMember );
				return true;
			}
		}
	}

	return false;
}

void Family::removeAllPlayerRegPet( CharId_t nCharId )
{
	RegPetList::iterator iter =	m_lstRegistPet.begin();
	RegPetList::iterator eiter = m_lstRegistPet.end();
	for ( ; iter != eiter; )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			m_lstRegistPet.erase( iter++ );
			continue;
		}
		if ( pPet->GetOwnerId() == nCharId )
		{
			m_lstRegistPet.erase( iter++ );
			recalTotomPoints( pPet->GetBaseId() );
			continue;
		}
		++iter;
	}
}

bool Family::SetHonorPosition( SocialPlayer& player, PlayerInfo* pMember, int8_t nPosition )
{
	if ( NULL == pMember )
	{
		return false;
	}

	// 检测是否是荣誉职位
	if ( !IsHonorPosition( nPosition ) )
	{
		return false;
	}

	const CfgFamily* pCfgFamily = CFG_DATA.GetFamilyTable().GetFamilyInfo( m_nLevel );
	if ( NULL == pCfgFamily )
	{
		return false;
	}

	// 检测职位人数上限
	int32_t nPositionMemberCount = m_vPosition[nPosition].size();
	if ( nPositionMemberCount >= pCfgFamily->vPosition[nPosition] )
	{
		return false;
	}

	int8_t nOldPosition = pMember->nFamilyPosition;
	if ( nOldPosition == nPosition )
	{
		return false;
	}

	MemberList::iterator iter = m_vPosition[nOldPosition].begin();
	MemberList::iterator eiter = m_vPosition[nOldPosition].end();
	for ( ; iter != eiter; ++iter )
	{
		PlayerInfo* ptemp = *iter;
		if ( ptemp != NULL && ptemp == pMember )
		{
			m_vPosition[nOldPosition].erase( iter );
			break;
		}
	}
	pMember->nFamilyPosition = nPosition;
	m_vPosition[nPosition].push_back( pMember );

	SendMemberInfo( player );
	sendGameUpdatePlayerInfo( pMember );
	broadcastSetPosition( player.getName(),player.getCid(), pMember->strName, pMember->nCharId, nPosition );

	if ( IsSortPosition( nOldPosition ) )
	{
		// 如果旧的职位不是荣誉职位则重排职位
		resetPosition();
	}

	FamilyLog log = {};
	log.nType		= FLT_APPOINT;
	log.nTime		= DayTime::now();
	log.vParam[0]	= player.getCid();
	log.vParam[1]	= pMember->nCharId;
	log.vParam[2]	= nPosition;
	addFamilyLog( log );
	return true;
}

bool Family::UnSetHonorPosition( SocialPlayer& player, PlayerInfo* pMember )
{
	if ( NULL == pMember )
	{
		return false;
	}

	int8_t nOldPosition = pMember->nFamilyPosition;
	if ( !IsHonorPosition( nOldPosition ) )
	{
		return false;
	}

	MemberList::iterator iter = m_vPosition[nOldPosition].begin();
	MemberList::iterator eiter = m_vPosition[nOldPosition].end();
	for ( ; iter != eiter; ++iter )
	{
		PlayerInfo* ptemp = *iter;
		if ( ptemp != NULL && ptemp == pMember )
		{
			m_vPosition[nOldPosition].erase( iter );
			break;
		}
	}

	pMember->nFamilyPosition = FP_NONE;
	m_vPosition[FP_NONE].push_back( pMember );

	resetPosition();
	SendMemberInfo( player );
	sendGameUpdatePlayerInfo( pMember );
	broadcastUnSetHonorPosition( player.getName(),player.getCid(), pMember->strName,pMember->nCharId );

	FamilyLog log = {};
	log.nType		= FLT_UN_APPOINT;
	log.nTime		= DayTime::now();
	log.vParam[0]	= player.getCid();
	log.vParam[1]	= pMember->nCharId;
	addFamilyLog( log );
	return true;
}

void Family::resetPosition()
{
	MemberSet tSet;
	for ( int8_t i = FP_NONE; i <= FP_VICE; ++i )
	{
		MemberList::iterator iter = m_vPosition[i].begin();
		MemberList::iterator eiter = m_vPosition[i].end();
		for ( ; iter != eiter; ++iter )
		{
			PlayerInfo* pMember  = *iter;
			if ( NULL == pMember )
			{
				continue;
			}
			tSet.insert( pMember );
		}
		m_vPosition[i].clear();
	}
	{
		MemberSet::iterator iter = tSet.begin();
		MemberSet::iterator eiter = tSet.end();
		for ( ; iter != eiter; ++iter )
		{
			PlayerInfo* pMember = *iter;
			if ( NULL == pMember )
			{
				continue;
			}

			setPosition( pMember );
		}
	}
}

void Family::setPosition( PlayerInfo* pMember )
{
	if ( NULL == pMember )
	{
		return;
	}
	const CfgFamily* pCfgFamily = CFG_DATA.GetFamilyTable().GetFamilyInfo( m_nLevel );
	if ( NULL == pCfgFamily )
	{
		return;
	}
	for ( int8_t i = FP_VICE; i > 0; --i )
	{
		const CfgFamilyPosition* pCfgFamilyPosition = CFG_DATA.GetFamilyTable().GetFamilyPosition( i );
		if ( NULL == pCfgFamilyPosition )
		{
			continue;
		}
		int32_t nPositionMemberCount = m_vPosition[i].size();
		if ( nPositionMemberCount < pCfgFamily->vPosition[i] &&							// 数量上限判定
			pCfgFamilyPosition->nNeedContribution <= pMember->GetFamilyContribution() )		// 贡献度判定
		{
			if ( pMember->nFamilyPosition != i )
			{
				FamilyLog log = {};
				if ( i > pMember->nFamilyPosition )
				{
					log.nType = FLT_POSITION_UP;
				}
				else
				{
					log.nType = FLT_POSITION_DOWN;
				}
				log.nTime = DayTime::now();
				log.vParam[0] = pMember->nCharId;
				log.vParam[1] = i;
				addFamilyLog( log );

				if ( pMember->nFamilyPosition < i )
				{
					broadcastPositionUp( pMember->strName, pMember->nCharId, i );
				}
				pMember->nFamilyPosition = i;
				sendGameUpdatePlayerInfo( pMember );
			}
			m_vPosition[i].push_back( pMember );
			return;
		}
	}

	// 防止未添加到列表中
	m_vPosition[FP_NONE].push_back( pMember );
}

//SocialPlayer* Family::getMember( CharId_t nCharId )
//{
//	MemberMap::iterator findIter = m_mMember.find( nCharId );
//	if ( findIter != m_mMember.end() )
//	{
//		return findIter->second;
//	}
//	return NULL;
//}

bool Family::isApplied( CharId_t nCharId ) const
{
	for ( int32_t i = 0; i < FAMILY_APPLY_COUNT; ++i )
	{
		if ( NULL == m_vApplyer[i] )
		{
			return false;
		}
		if ( m_vApplyer[i]->nCharId == nCharId )
		{
			return true;
		}
	}
	return false;
}

int32_t Family::calBattle() const
{
	int32_t nSum = 0;
	for ( int8_t i = 0; i < FAMILY_POSITION_COUNT; ++i )
	{
		MemberList::const_iterator iter = m_vPosition[i].begin();
		MemberList::const_iterator eiter = m_vPosition[i].end();
		for ( ; iter != eiter; ++iter )
		{
			const PlayerInfo* pMember = *iter;
			if ( NULL == pMember )
			{
				continue;
			}
			nSum += pMember->nBattle;
		}
	}
	return nSum;
}

int32_t Family::calContribution() const
{
	int32_t nSum = 0;
	for ( int8_t i = 0; i < FAMILY_POSITION_COUNT; ++i )
	{
		MemberList::const_iterator iter = m_vPosition[i].begin();
		MemberList::const_iterator eiter = m_vPosition[i].end();
		for ( ; iter != eiter; ++iter )
		{
			const PlayerInfo* pMember = *iter;
			if ( NULL == pMember )
			{
				continue;
			}
			nSum += pMember->GetFamilyContribution();
		}
	}
	return nSum;
}

void Family::recalContribution()
{
	m_nContribution = calContribution();
	int32_t StarTotom = RecalStatTotomCount();
	int32_t nLevel = CFG_DATA.GetFamilyTable().GetFamilyLevel( StarTotom );
	if ( nLevel != m_nLevel )
	{
		// 添加日志
		FamilyLog log = {};
		if ( nLevel > m_nLevel )
		{
			log.nType		= FLT_LEVEL_UP;
		}
		else
		{
			log.nType		= FLT_LEVEL_DOWN;
		}
		//onChangeLevel( nLevel );
		int8_t nFlag = 1;
		if ( nLevel < m_nLevel )
		{
			nFlag = 0;
		}
 
		m_nLevel = nLevel;

		log.nTime		= DayTime::now();
		log.vParam[0]	= m_nContribution;
		log.vParam[1]	= nLevel;
		addFamilyLog( log );

		// 广播升级/降级信息
		broadcastLevelChange( m_nLevel, nFlag );
		sendGameUpdateFamilyInfo( FUR_UPDATE );
	}
	resetPosition();
	saveFamilyInfo();
}

int32_t Family::RecalStatTotomCount()
{
	int32_t Count = 0;
	const CfgFamilyTable& FamilyTable = CFG_DATA.GetFamilyTable();
	for ( int32_t i = 0; i <= MAX_PET_ID; ++i )
	{
		if ( m_vTotom[i].nValue >= 0 )
		{
			const CfgTotomOpen* TotomOpenCfg = FamilyTable.GetTotomOpenCfg( i );
			if ( NULL == TotomOpenCfg )
			{
				continue;
			}
			if ( m_vTotom[i].nTotalPoints >= TotomOpenCfg->StarTotom )
			{
				Count++;
			} 
		}
	}
	return Count;
}

bool Family::AppendListInfo( Answer::NetPacket* packet, const SocialPlayer& player )
{
	if ( NULL == packet )
	{
		return false;
	}

	PlayerInfo* pLeader = getLeader();
	if ( NULL == pLeader )
	{
		return false;
	}
	int32_t nBattle		= calTotomBattle();
	int8_t	bApplied	= isApplied( player.getCid() ) ? 1 : 0;

	packet->writeInt64( m_nId );				// 帮派ID
	packet->writeInt8( m_nLevel );				// 帮派等级
	packet->writeUTF8( m_strName );				// 帮派名称
	packet->writeUTF8( pLeader->strName );		// 帮主名称
	packet->writeInt32( nBattle );				// 军团战斗力
	packet->writeInt32( m_nMemberCount );		// 军团人数
	packet->writeInt8( bApplied );				// 是否发送了申请
	return true;
}

void Family::AppendFamilyWarInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}
	MemberList memberList;
	PlayerInfo* pLeader = getLeader();
	if ( pLeader != NULL )
	{
		memberList.push_back( pLeader );
	}

	for ( MemberList::iterator i1 = m_vPosition[FP_VICE].begin(); i1 != m_vPosition[FP_VICE].end(); ++i1 )
	{
		memberList.push_back( *i1 );
	}
	for ( MemberList::iterator i2 = m_vPosition[FP_HONOR_VICE].begin(); i2 != m_vPosition[FP_HONOR_VICE].end(); ++i2 )
	{
		memberList.push_back( *i2 );
	}

	packet->writeUTF8( m_strName );
	int8_t nCount = 0;
	uint32_t offset = packet->getWOffset();
	packet->writeInt8( nCount );
	for ( MemberList::iterator iter = memberList.begin(); iter != memberList.end(); ++iter )
	{
		PlayerInfo* pMember = *iter;
		if ( pMember != NULL )
		{
			packet->writeInt64( pMember->nCharId );
			packet->writeUTF8( pMember->strName );
			packet->writeInt8( pMember->nFamilyPosition );
			packet->writeInt32( pMember->nLevel );
			packet->writeInt8( pMember->nJob );
			packet->writeInt8( pMember->nSex );
			packet->writeInt32( pMember->nWeapon );
			packet->writeInt32( pMember->nCloth );
			++nCount;
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt8( nCount );
	packet->setWOffset( oldOffset );
}

bool Family::DecFamilyMoney( int32_t nMoney )
{
	if ( m_nMoney < nMoney )
	{
		return false;
	}
	m_nMoney -= nMoney;
	saveFamilyInfo();
	return true;
}

bool Family::IsAuto() 
{
	return m_AutoAgree > 0; 
}

void Family::SendApplyInfo( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}
	uint32_t nOffset = packet->getWOffset();
	int16_t nCount = 0;
	packet->writeInt16( nCount);
	for ( int32_t i = 0; i < FAMILY_APPLY_COUNT; ++i )
	{
		PlayerInfo* pApplyer = m_vApplyer[i];
		if ( NULL == pApplyer )
		{
			continue;
		}
		packet->writeInt64( pApplyer->nCharId );
		packet->writeUTF8( pApplyer->strName );
		packet->writeInt32( pApplyer->nLevel );
		packet->writeInt32( pApplyer->nBattle );
		packet->writeInt8( pApplyer->nJob );
		++nCount;
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );
	packet->writeInt8( m_AutoAgree );						// 自动同意
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_APPLIERS );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void Family::SendFamilyInfo( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	PlayerInfo* pLeader = getLeader();
	if ( NULL == pLeader )
	{
		return;
	}

	packet->writeInt64( m_nId );							// 军团ID
	packet->writeInt32( m_nLevel );							// 军团等级
	packet->writeUTF8( m_strName );							// 军团名称
	packet->writeInt32( m_nContribution );					// 军团贡献度
	packet->writeInt32( m_nMoney );							// 军团资金
	packet->writeInt32( calTotomBattle() );					// 军团总战斗力
	packet->writeInt16( m_nMemberCount );					// 军团人数
	packet->writeUTF8( pLeader->strName );					// 军团长名称
	packet->writeInt32( pLeader->nLevel	);					// 军团长等级
	packet->writeInt8( player.GetFamilyPosition() );		// 自身职位
	packet->writeInt32( player.GetFamilyContribution() );	// 自身贡献度
	packet->writeUTF8( m_strNotice );						// 军团公告

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_INFO );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void Family::SendMemberInfo( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	uint32_t offset = packet->getWOffset();
	int16_t nCount = 0;
	packet->writeInt16( nCount);
	for ( int8_t i = 0; i < FAMILY_POSITION_COUNT; ++i )
	{
		MemberList::iterator iter = m_vPosition[i].begin();
		MemberList::iterator eiter = m_vPosition[i].end();
		for ( ; iter != eiter; ++iter )
		{
			PlayerInfo* pMember = *iter;
			if ( NULL == pMember )
			{
				continue;
			}
			packet->writeInt64( pMember->nCharId );					// ID
			packet->writeUTF8( pMember->strName );					// 名称
			packet->writeInt16( pMember->nLevel );					// 等级
			packet->writeInt8( pMember->nVip );						// VIP
			packet->writeInt8( i );									// 职位
			packet->writeInt32( pMember->GetFamilyContribution() );	// 贡献度
			packet->writeInt32( pMember->nLastLogoutTime );			// 登出时间

			++nCount;
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_MEMBER_INFO );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void Family::SendTotomInfo( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	uint32_t offset = packet->getWOffset();
	int16_t nCount = 0;
	packet->writeInt16( nCount );
	for ( int32_t i = 0; i <= MAX_PET_ID; ++i )
	{
		Totom& totom = m_vTotom[i];
		if ( totom.nTotalPoints > 0 || totom.nValue >= 0 )
		{
			packet->writeInt32( i );
			packet->writeInt8( totom.nValue );
			packet->writeInt32( totom.nTotalPoints );
			packet->writeInt8( totom.nStartTime );
			++nCount;
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_TOTOM_INFO );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void Family::SendRegistPetInfo( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	uint32_t offset = packet->getWOffset();
	int16_t nCount = 0;
	packet->writeInt16( nCount);
	RegPetList::iterator iter = m_lstRegistPet.begin();
	RegPetList::iterator eiter = m_lstRegistPet.end();
	for ( ; iter != eiter; ++iter)
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}

		PlayerInfo* pPlayer = PLAYER_MANAGER.GetPlayerInfo( pPet->GetOwnerId() );
		if ( NULL == pPlayer )
		{
			continue;
		}

		packet->writeInt64( pPet->GetPetId() );				// 宠物Id
		packet->writeInt32( pPet->GetBaseId() );			// BaseId
		packet->writeUTF8( pPet->GetPetName() );			// 宠物名称
		packet->writeUTF8( pPlayer->strName );				// 玩家名称
		packet->writeInt32( pPet->GetPoints() );			// 宠物评分
		++nCount;
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_PETS );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void Family::SendPlayerPetInfo( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	uint32_t offset = packet->getWOffset();
	int16_t nCount = 0;
	packet->writeInt16( nCount);
	RegPetList::iterator iter = m_lstRegistPet.begin();
	RegPetList::iterator eiter = m_lstRegistPet.end();
	for ( ; iter != eiter; ++iter)
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}

		if ( pPet->GetOwnerId() == player.getCid() )
		{
			packet->writeInt64( pPet->GetPetId() );				// 宠物Id
			++nCount;
		}
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( offset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_PLAYER_PETS );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void Family::SendLogInfo( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	uint32_t nOffset = packet->getWOffset();
	int16_t nCount = 0;
	packet->writeInt16( nCount);

	FamilyLogList::iterator iter = m_lstFamilyLog.begin();
	FamilyLogList::iterator eiter = m_lstFamilyLog.end();
	for ( ; iter != eiter; ++iter )
	{
		appendFamilyLogInfo( packet, *iter );
		++nCount;
	}

	uint32_t oldOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt16( nCount );
	packet->setWOffset( oldOffset );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_LOGS );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void Family::appendFamilyLogInfo( NetPacket* packet, const FamilyLog& log )
{
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( log.nType );
	packet->writeInt32( log.nTime );
	switch ( log.nType )
	{
	case FLT_MEMBER_LEAVE:
	case FLT_MEMBER_JOIN:
		{
			PlayerInfo* pPlayerInfo = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pPlayerInfo != NULL )
			{
				packet->writeUTF8( pPlayerInfo->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
		}
		break;
	case FLT_LEVEL_UP:
		{
			packet->writeInt16( static_cast<int16_t>( log.vParam[1] ) );
		}
		break;
	case FLT_LEVEL_DOWN:
		{
			packet->writeInt32( static_cast<int32_t>( log.vParam[0] ) );
			packet->writeInt16( static_cast<int16_t>( log.vParam[1] ) );
		}
		break;
	case FLT_GOLD:
	case FLT_MONEY:
		{
			PlayerInfo* pPlayerInfo = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pPlayerInfo != NULL )
			{
				packet->writeUTF8( pPlayerInfo->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			packet->writeInt32( static_cast<int32_t>( log.vParam[1] ) );
		}
		break;
	case FLT_APPOINT:
		{
			PlayerInfo* pSrc = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pSrc != NULL )
			{
				packet->writeUTF8( pSrc->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			PlayerInfo* pTar = PLAYER_MANAGER.GetPlayerInfo( log.vParam[1] );
			if ( pTar != NULL )
			{
				packet->writeUTF8( pTar->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			packet->writeInt8( static_cast<int8_t>( log.vParam[2] ) );
		}
		break;
	case FLT_UN_APPOINT:
		{
			PlayerInfo* pSrc = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pSrc != NULL )
			{
				packet->writeUTF8( pSrc->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			PlayerInfo* pTar = PLAYER_MANAGER.GetPlayerInfo( log.vParam[1] );
			if ( pTar != NULL )
			{
				packet->writeUTF8( pTar->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
		}
		break;
	case FLT_KICK:
		{
			PlayerInfo* pSrc = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pSrc != NULL )
			{
				packet->writeUTF8( pSrc->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			PlayerInfo* pTar = PLAYER_MANAGER.GetPlayerInfo( log.vParam[1] );
			if ( pTar != NULL )
			{
				packet->writeUTF8( pTar->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
		}
		break;
	case FLT_POSITION_UP:
	case FLT_POSITION_DOWN:
		{
			PlayerInfo* pPlayerInfo = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pPlayerInfo != NULL )
			{
				packet->writeUTF8( pPlayerInfo->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			packet->writeInt8( static_cast<int8_t>( log.vParam[1] ) );
		}
		break;
	case FLT_ACTIVE_TOTOM:
		{
			PlayerInfo* pPlayerInfo = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pPlayerInfo != NULL )
			{
				packet->writeUTF8( pPlayerInfo->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			packet->writeInt32( static_cast<int32_t>( log.vParam[1] ) );
			packet->writeInt32( static_cast<int32_t>( log.vParam[2] ) );
		}
		break;
	case FLT_REGIST_PET:
		{
			PlayerInfo* pPlayerInfo = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pPlayerInfo != NULL )
			{
				packet->writeUTF8( pPlayerInfo->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			packet->writeInt32( static_cast<int32_t>( log.vParam[1] ) );
			packet->writeInt32( static_cast<int32_t>( log.vParam[2] ) );
		}
		break;
	case FLT_UNREGIST_PET:
	case FLT_FAMILY_TASK:
		{
			PlayerInfo* pPlayerInfo = PLAYER_MANAGER.GetPlayerInfo( log.vParam[0] );
			if ( pPlayerInfo != NULL )
			{
				packet->writeUTF8( pPlayerInfo->strName );
			}
			else
			{
				packet->writeUTF8( "" );
			}
			packet->writeInt32( static_cast<int32_t>( log.vParam[1] ) );
			packet->writeInt32( static_cast<int32_t>( log.vParam[2] ) );
		}
		break;
	default:
		break;
	}
}

void Family::SendNotice( const SocialPlayer& player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeUTF8( m_strNotice );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_NOTICE );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( player.getGateIndex(), packet );
}

void Family::broadcastNotice()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeUTF8( m_strNotice );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_NOTICE );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::sendGameUpdateFamilyInfo( int8_t nReason )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( nReason );
	packet->writeInt64( m_nId );
	packet->writeUTF8( m_strName );
	packet->writeInt32( m_nLevel );
	packet->writeInt32( calTotomBattle() );
	packet->writeInt32( m_FamilyTaskCount );
	int32_t Count = 0;
	int32_t OldOffset = packet->getWOffset();
	packet->writeInt32(Count);
	for ( int32_t i = 0; i <= MAX_PET_ID; ++i )
	{
		if ( m_vTotom[i].nValue >= 0 )
		{
			packet->writeInt32( i );
			Count++;
		}
	}
	int32_t NewOffset = packet->getWOffset();
	packet->setWOffset( OldOffset );
	packet->writeInt32(Count);
	packet->setWOffset( NewOffset );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_ALL_GAME_UPDATE_FAMILY );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void Family::AddFamilyTaskCount()
{
	m_FamilyTaskCount++;
	m_LastFamilyTaskTime = DayTime::now();
	saveFamilyInfo();
	sendGameUpdateFamilyInfo( FUR_UPDATE );
}

void Family::SendFamilyTaskCount( SocialPlayer* player )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( m_FamilyTaskCount );
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_TASK_COUNT );
	packet->setSize( packet->getWOffset() );
	if ( player == NULL )
	{
		Broadcase( packet );
	}
	else
	{
		SOCIAL_SERVICE.sendPacketTo( player->getGateIndex(), packet );
	}
}

void Family::ResetFamilyCount()
{
	m_FamilyTaskCount		= 0;
	m_LastFamilyTaskTime	= 0;
	saveFamilyInfo();
	sendGameUpdateFamilyInfo( FUR_UPDATE );
	SendFamilyTaskCount();
}

void Family::sendGameUpdatePlayerInfo( PlayerInfo* pMember )
{
	if ( NULL == pMember )
	{
		return;
	}
	//不管在不在线,先改变数据库
	savePlayerInfo( pMember );	
	SocialPlayer* pPlayer = PLAYER_MANAGER.GetPlayerByCid( pMember->nCharId );
	if ( NULL == pPlayer )
	{
		return;
	}

	pPlayer->SendGameUpdateFamilyInfo();
}

void Family::ChangeNotice( const std::string& notice, bool IsCreate )
{
	m_strNotice = notice;
	if ( !IsCreate )
	{
		broadcastNotice();
	}

	MySqlDBGuard db( DBPOOL );
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "UPDATE `mem_family` SET `notice`='%s' WHERE `id`=%lld", notice.c_str(), m_nId );
	db.excute(szSQL);
}

void Family::Broadcase( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	Int16Vector indexes;
	indexes.reserve( m_nMemberCount );

	for ( int8_t i = 0; i < FAMILY_POSITION_COUNT; ++i )
	{
		MemberList::iterator iter = m_vPosition[i].begin();
		MemberList::iterator eiter = m_vPosition[i].end();
		for ( ; iter != eiter; ++iter )
		{
			PlayerInfo* pMember = *iter;
			if ( NULL == pMember )
			{
				continue;
			}
			SocialPlayer* pPlayer = PLAYER_MANAGER.GetPlayerByCid( pMember->nCharId );
			if ( NULL == pPlayer )
			{
				continue;
			}

			indexes.push_back( pPlayer->getGateIndex() );
		}
	}

	SOCIAL_SERVICE.broadcast( indexes, packet );
}

bool Family::RemoveApply( CharId_t nCharId )
{
	for ( int32_t i = 0; i < FAMILY_APPLY_COUNT; ++i ) 
	{
		if ( NULL == m_vApplyer[i] )
		{
			return false;
		}
		if ( m_vApplyer[i]->nCharId == nCharId )
		{
			for ( int32_t j = i; j < FAMILY_APPLY_COUNT-1; ++j )
			{
				m_vApplyer[j] = m_vApplyer[j+1];
			}
			m_vApplyer[FAMILY_APPLY_COUNT-1] = NULL;
			return true;
		}
	}
	return false;
}

int32_t Family::calTotomBattle() const
{
	int32_t nSum = 0;
	std::list<int32_t> BattleList;
	for ( int32_t i = 1; i <= MAX_PET_ID; ++i )
	{
		if ( m_vTotom[i].nValue == -1 )
		{
			continue;
		}
		int32_t AddBattle = m_vTotom[i].nValue + m_vTotom[i].nTotalPoints / TOTOM_BATTLE_BASE;
		if ( AddBattle > MAX_TOTOM_ADD_BATTLE )
		{
			AddBattle = MAX_TOTOM_ADD_BATTLE;
		}
		BattleList.push_back( AddBattle );
	}
	BattleList.sort();
	std::list<int32_t>::reverse_iterator it = BattleList.rbegin();
	int32_t Count = 0;
	for ( ; it !=  BattleList.rend(); ++it )
	{
		if ( Count >= 8 )
		{
			break;
		}
		nSum += *it;
		Count++;
	}
	return nSum;
}

int32_t Family::calTotomPoints( int32_t nTotomId ) const
{
	int32_t nSum = 0;
	RegPetList::const_iterator iter = m_lstRegistPet.begin();
	RegPetList::const_iterator eiter = m_lstRegistPet.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}

		if ( pPet->GetBaseId() == nTotomId )
		{
			nSum += pPet->GetPoints();
		}
	}
	return nSum;
}

void Family::recalTotomPoints( int32_t nBaseId )
{
	if ( nBaseId <= 0 || nBaseId > MAX_PET_ID )
	{
		return;
	}

	m_vTotom[nBaseId].nTotalPoints = calTotomPoints( nBaseId );
}

void Family::broadcastGameNeedUpdatePlayerInfo()
{
	// 发送给服务器需要更新玩家信息
	for ( int8_t i = 0; i < FAMILY_POSITION_COUNT; ++i )
	{
		MemberList::iterator iter = m_vPosition[i].begin();
		MemberList::iterator eiter = m_vPosition[i].end();
		for ( ; iter != eiter; ++iter )
		{
			PlayerInfo* pMember = *iter;
			if ( NULL == pMember )
			{
				continue;
			}
			SocialPlayer* pPlayer = PLAYER_MANAGER.GetPlayerByCid( pMember->nCharId );
			if ( NULL == pPlayer )
			{
				continue;
			}

			pPlayer->SendGameUpdateFamilyInfo();
		}
	}
}

void Family::broadcastLevelChange( int32_t nLevel, int8_t nFlg )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_LEVEL_CHANGE );
	packet->writeInt32( nLevel );
	packet->writeInt8( nFlg );
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastSetPosition( const std::string& opName,CharId_t CharId, const std::string& tarName,CharId_t tarCharId, int8_t nPosition )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_APPOINT );
	packet->writeUTF8( opName );
	packet->writeInt64( CharId );
	packet->writeUTF8( tarName );
	packet->writeInt64( tarCharId );
	packet->writeInt8( nPosition );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastUnSetHonorPosition( const std::string& opName,CharId_t CharId, const std::string& tarName, CharId_t tarCharId )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_UN_HONOR_POS );
	packet->writeUTF8( opName );
	packet->writeInt64( CharId );
	packet->writeUTF8( tarName );
	packet->writeInt64( tarCharId );
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastEnterFamily( const std::string& opName,CharId_t opId, const std::string& tarName, CharId_t CharId )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_APPROVE );
	packet->writeUTF8( opName );
	packet->writeInt64( opId );
	packet->writeUTF8( tarName );
	packet->writeInt64( CharId );
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastLeaveFamily( const std::string& memberName, CharId_t CharId )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_LEAVE );
	packet->writeUTF8( memberName );
	packet->writeInt64( CharId );
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastKickMember( const std::string& opName, CharId_t opId,const std::string& tarName, CharId_t tarId )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_KICK );
	packet->writeUTF8( opName );
	packet->writeInt64( opId );
	packet->writeUTF8( tarName );
	packet->writeInt64( tarId );
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastActiveTotom( const std::string& opName,CharId_t opId, int32_t nTotomId, int8_t nAddBattle )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_ACTIVE_TOTOM );
	packet->writeUTF8( opName );
	packet->writeInt64( opId );
	packet->writeInt32( nTotomId );
	packet->writeInt8( nAddBattle );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastRegistPet( const std::string& opName, CharId_t opId,int32_t nBaseId, int32_t nAddContribute )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_REGIST_PET );
	packet->writeUTF8( opName );
	packet->writeInt64( opId );
	packet->writeInt32( nBaseId );
	packet->writeInt32( nAddContribute );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastPositionUp( const std::string& opName, CharId_t opId,int8_t nPosition )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_POSITION_UP );
	packet->writeUTF8( opName );
	packet->writeInt64( opId );
	packet->writeInt8( nPosition );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::broadcastFamilyDestroy()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( FET_DESTROY );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_EVENT );
	packet->setSize( packet->getWOffset() );

	Broadcase( packet );
}

void Family::sendFamilyApplyResult( const std::string& opName, PlayerInfo* pApplyer, bool bAccept )
{
	if ( NULL == pApplyer )
	{
		return;
	}

	SocialPlayer* pPlayer = PLAYER_MANAGER.GetPlayerByCid( pApplyer->nCharId );
	if ( NULL == pPlayer )
	{
		return;
	}
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket(); 
	if ( NULL == packet )
	{
		return;
	}

	packet->writeUTF8( opName );
	packet->writeUTF8( m_strName );
	packet->writeInt8( bAccept ? 1 : 0 );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_FAMILY_APPLY_RESULT );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
}

void Family::saveFamilyInfo()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1,
		"UPDATE `mem_family` SET `level`=%d,`money`=%d,`count`=%d,`auto_agree`=%d, `task_count`=%d,`task_time`=%d WHERE `id`=%lld",
		m_nLevel,
		m_nMoney,
		m_nMemberCount,
		m_AutoAgree,
		m_FamilyTaskCount,
		m_LastFamilyTaskTime,
		m_nId);
	db.excute(szSQL);
}

void Family::savePlayerInfo( PlayerInfo* pMember )
{
	if ( NULL == pMember )
	{
		return;
	}

	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1,
		"INSERT INTO `mem_chr_family` (`cid`,`family_id`,`position`,`contribute`,`pet_contribute`) VALUES (%lld,%lld,%d,%d,%d) ON DUPLICATE KEY UPDATE `family_id`=%lld,`position`=%d,`contribute`=%d,`pet_contribute`=%d",
		pMember->nCharId,
		pMember->nFamilyId,
		pMember->nFamilyPosition,
		pMember->nFamilyContribution,
		pMember->nFamilyPetContribution,
		pMember->nFamilyId,
		pMember->nFamilyPosition,
		pMember->nFamilyContribution,
		pMember->nFamilyPetContribution );
	db.excute(szSQL);
}

void Family::saveTotomInfo( int32_t nTotomId, const Totom& totom )
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1,
		"INSERT INTO `mem_family_totom` (`family_id`,`totom_id`,`battle`,`start_time`) VALUES (%lld,%d,%d,%d) ON DUPLICATE KEY UPDATE `battle`=%d,`start_time`=%d",
		m_nId,
		nTotomId,
		totom.nValue,
		totom.nStartTime,
		totom.nValue,
		totom.nStartTime );
	db.excute(szSQL);
}

void Family::addFamilyLog( const FamilyLog& log )
{
	if ( m_lstFamilyLog.size() >= FAMILY_LOG_SIZE )
	{
		m_lstFamilyLog.pop_front();
	}
	m_lstFamilyLog.push_back( log );

	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1,
		"INSERT INTO `mem_family_log` (`id`,`type`,`param1`,`param2`,`param3`,`param4`,`param5`,`time`) VALUES (%lld,%d,%lld,%lld,%lld,%lld,%lld,%d)",
		m_nId,
		log.nType,
		log.vParam[0],
		log.vParam[1],
		log.vParam[2],
		log.vParam[3],
		log.vParam[4],
		log.nTime );
	db.excute(szSQL);
}

void Family::onOpenTotom( SocialPlayer* pPlayer,int32_t PetBaseId )
{
	if ( NULL == pPlayer || PetBaseId <= 0 || PetBaseId > MAX_PET_ID )
	{
		return;
	}
	if ( m_vTotom[PetBaseId].nValue >= 0 )
	{
		return;
	}
	const CfgFamilyTable& FamilyTable = CFG_DATA.GetFamilyTable();
	const CfgTotomOpen* TotomOpenCfg = FamilyTable.GetTotomOpenCfg( PetBaseId );
	if ( NULL == TotomOpenCfg )
	{
		return;
	}
	int32_t NeedMoney = CFG_DATA.GetOpenTotomNeedMoney( m_OpenTotomCount + 1 );
	if ( !DecFamilyMoney( NeedMoney ) )
	{
		return;
	}
	OpenTotom( PetBaseId );
	SendTotomInfo( *pPlayer );
	saveFamilyInfo();
	sendGameUpdateFamilyInfo( FUR_UPDATE );
}

bool Family::OpenTotom( int32_t PetBaseId )
{
	if ( PetBaseId <= 0 || PetBaseId > MAX_PET_ID )
	{
		return false;
	}
	m_vTotom[PetBaseId].nValue = 0;
	saveTotomInfo( PetBaseId, m_vTotom[PetBaseId] );
	m_OpenTotomCount++;
	return true;
}

