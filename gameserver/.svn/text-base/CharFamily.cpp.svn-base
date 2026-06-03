#include "stdafx.h"

#include "GameService.h"
#include "Player.h"
#include "CharFamily.h"
#include "FamilyManager.h"
#include "CfgData.h"
#include "ActivityMap.h"
#include "ActivityManager.h"
#include "FamilyWar.h"

using namespace Answer;

enum ERR_FAMILY
{
	ERR_FAMILY_REGIST_PET_ALREADY	= 6,		// 今天已经登记过这种宠物了
};

CExtCharFamily::CExtCharFamily()
{
	OnCleanUp();
}

CExtCharFamily::~CExtCharFamily()
{
}

void CExtCharFamily::OnCleanUp()
{
	m_nFamilyId				= 0;
	m_nPosition				= FP_NONE;
	m_nContribution			= 0;
	m_nRegistPetCount		= 0;
	m_nPetContribution	    = 0;
	m_IsLogin				= false;
	bzero( m_vRegistPetList, sizeof( m_vRegistPetList ) );
	bzero( m_vPetRegistTime, sizeof( m_vPetRegistTime ) );
}

void CExtCharFamily::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_nFamilyId			= dbData.m_FamilyData.nFamilyId;
	m_nPosition			= dbData.m_FamilyData.nPosition;
	m_nContribution		= dbData.m_FamilyData.nContribution;
	m_nPetContribution	= dbData.m_FamilyData.nPetContribution;
	for ( int32_t i = 0; i < MAX_PET_ID; ++i )
	{
		m_vPetRegistTime[i+1] = dbData.m_FamilyData.vRegFlag[i];
	}

	DBPetList::const_iterator iter = dbData.m_CharPets.charPets.begin();
	DBPetList::const_iterator eiter = dbData.m_CharPets.charPets.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( iter->nFamilyId > 0 )
		{
			CObjPet* pPet = m_pPlayer->GetCharPet().GetPet( iter->nPetId );
			if ( pPet != NULL )
			{
				m_vRegistPetList[pPet->GetBaseId()] = pPet;
				++m_nRegistPetCount;
			}
		}
	}
}

void CExtCharFamily::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_FamilyData.nFamilyId			= m_nFamilyId;
	dbData.m_FamilyData.nPosition			= m_nPosition;
	dbData.m_FamilyData.nContribution		= m_nContribution;
	dbData.m_FamilyData.nPetContribution	= m_nPetContribution;
	for ( int32_t i = 0; i < MAX_PET_ID; ++i )
	{
		dbData.m_FamilyData.vRegFlag[i] = m_vPetRegistTime[i+1];
	}
}

void CExtCharFamily::OnDaySwitch( int32_t nDiffDays )
{
	bzero( m_vPetRegistTime, sizeof( m_vPetRegistTime ) );	// 跨天清空登记情况
	if ( m_IsLogin )
	{
		recalPetAddContribute();
	}
}

void CExtCharFamily::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_FAMILY_CONTRIBUTION );						// 帮派捐献
	procList.push_back( CM_FAMILY_REGIST_PET );							// 注册宠物
	procList.push_back( CM_FAMILY_UNREGIST_PET );						// 取消注册宠物

	procList.push_back( IM_SOCIAL_GAME_CREATE_FAMILY );					// 创建帮派
	procList.push_back( IM_SOCIAL_GAME_UPDATE_FAMILY );					// 更新帮派信息


	procList.push_back( CM_REQUEST_ACTIVITY_FAMILY_WAR_PILLAR_INFO );
	procList.push_back( CM_ACTIVITY_FAMILYWAR_ADD_PILLAR_MONEY );
	procList.push_back( IM_SOCIAL_GAME_FAMILYWAR_PILLAR_ADD_MONEY );

	procList.push_back( CM_FAMILY_RECEIVE_TASK );						// 接收军团任务
	procList.push_back( CM_FAMILY_GET_TASK_REWARD );
}

int32_t CExtCharFamily::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
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
	case CM_FAMILY_CONTRIBUTION:			return onContribution( inPacket );
	case CM_FAMILY_REGIST_PET:				return onRegistPet( inPacket );
	case CM_FAMILY_UNREGIST_PET:			return onUnRegistPet( inPacket );

	case IM_SOCIAL_GAME_CREATE_FAMILY:		return onSocialCreateFamily( inPacket );
	case IM_SOCIAL_GAME_UPDATE_FAMILY:		return onSocialUpdateFamilyInfo( inPacket );


	case CM_REQUEST_ACTIVITY_FAMILY_WAR_PILLAR_INFO:	return onRequestFamilyWarPillarInfo( inPacket );
	case CM_ACTIVITY_FAMILYWAR_ADD_PILLAR_MONEY:		return onFamilyWarAddPillarMoney( inPacket );
	case IM_SOCIAL_GAME_FAMILYWAR_PILLAR_ADD_MONEY:		return onSocialFamilyWarPillarAddMoney( inPacket );

	case CM_FAMILY_RECEIVE_TASK:			return onReceiveFamilyTask( inPacket );
	case CM_FAMILY_GET_TASK_REWARD:			return onGetFamilyTaskReward( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onContribution( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t	nMoney	= inPacket->readInt32();
	int32_t	nGold	= inPacket->readInt32();

	if ( nMoney < 0 || nGold < 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( nGold > MAX_FAMILY_CONTRIBUTE_GOLD )
	{
		nGold = MAX_FAMILY_CONTRIBUTE_GOLD;
	}

	if ( nMoney > MAX_FAMILY_CONTRIBUTE_MONEY )
	{
		nMoney = MAX_FAMILY_CONTRIBUTE_MONEY;
	}

	if ( m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < nMoney || m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nGold )
	{
		return ERR_SYETEM_ERR;
	}

	int32_t nAddValue = CalFamilyContribute( nMoney, nGold );
	if ( nAddValue <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( nAddValue + m_nContribution > MAX_FAMILY_CONTRIBUTE )
	{
		nAddValue = MAX_FAMILY_CONTRIBUTE - m_nContribution;		// 到达捐献上限
	}

	m_nContribution += nAddValue;

	if ( nMoney > 0 )
	{
		m_pPlayer->GetCurrency().DecMoneyAndNoBind( nMoney, GCR_FAMILY_CONTRIBUTE );
	}

	if ( nGold > 0 )
	{
		m_pPlayer->DecCurrency( CURRENCY_GOLD, nGold, GCR_FAMILY_CONTRIBUTE, m_nFamilyId );
	}

	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_FAMILY_DONATE , nAddValue );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nAddValue );

	sendSocialAddContribution( nMoney, nGold );
	return ERR_OK;
}

void CExtCharFamily::AddContribution( int32_t GongXian, int32_t JunTuanZiJin )
{
	if ( GetFamilyId() <= 0 )
	{
		return;
	}
	sendSocialAddTaskContribution( GongXian, JunTuanZiJin );
	m_nContribution += GongXian;

}

void CExtCharFamily::sendSocialAddTaskContribution( int32_t GongXian, int32_t JunTuanZiJin )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_FAMILY_ADD_CONTRIBUTION );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( GongXian );
	packet->writeInt32( JunTuanZiJin );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

int32_t CExtCharFamily::onRegistPet( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t	nPetId	= inPacket->readInt64();
	CObjPet* pPet = m_pPlayer->GetCharPet().GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	if ( pPet->getLevel() < PET_RANK_OPEN_LEVEL )
	{
		return ERR_INVALID_DATA;
	}

	if ( pPet->IsRegInFamily() )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nBaseId = pPet->GetBaseId();
	if ( m_vRegistPetList[nBaseId] == pPet )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_vPetRegistTime[nBaseId] > 0 )
	{
		GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_FAMILY_REGIST_PET_ALREADY );
		return ERR_INVALID_DATA;
	}

// 	int32_t nFamilyLevel = GetFamilyLevel();
// 	int32_t nTotomNeedLevel = CFG_DATA.GetFamilyTable().GetTotomActiveLevel( nBaseId );
// 	if ( nFamilyLevel < nTotomNeedLevel )
// 	{
// 		return ERR_INVALID_DATA;		// 等级不够还没开
// 	}
	if ( !TotomIsOpened( nBaseId ) )
	{
		return ERR_INVALID_DATA;
	}

	CObjPet* pOldPet = m_vRegistPetList[nBaseId];
	if ( pOldPet != NULL )
	{
		pOldPet->SetRegInFamily( 0 );
	}
	else
	{
		int32_t nMaxRegPet = getMaxRegistPetNum( m_pPlayer->getLevel() );
		if ( m_nRegistPetCount < nMaxRegPet )
		{
			++m_nRegistPetCount;
		}
		else
		{
			return ERR_INVALID_DATA;
		}
	}

	pPet->SetRegInFamily( m_pPlayer->getFamilyId() );
	m_vRegistPetList[nBaseId] = pPet;
	m_vPetRegistTime[nBaseId] = 1;
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nPetId );

	sendSocialRegistPet( nPetId );
	recalPetAddContribute();
	m_pPlayer->recalcAttr();
	return ERR_OK;
}

int32_t CExtCharFamily::onUnRegistPet( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t	nBaseId	= inPacket->readInt32();
	if ( nBaseId < 0 || nBaseId > MAX_PET_ID )
	{
		return ERR_INVALID_DATA;
	}

	CObjPet* pPet = m_vRegistPetList[nBaseId];
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	pPet->SetRegInFamily( 0 );
	--m_nRegistPetCount;

	m_vRegistPetList[nBaseId] = NULL;
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), pPet->GetPetId() );

	sendSocialUnRegistPet( pPet->GetPetId() );
	recalPetAddContribute();
	m_pPlayer->recalcAttr();
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialCreateFamily( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, CREATE_FAMILY_COST_GOLD, GCR_CREATE_FAMILY ) )
	{
		return ERR_INVALID_DATA;
	}

	std::string	name = inPacket->readUTF8( true );
	std::string notice = inPacket->readUTF8(true);
	// 同步到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_CREATE_FAMILY );
	if (NULL == packet)
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeUTF8( name );
	packet->writeUTF8( notice );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialUpdateFamilyInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int64_t FamilyId = inPacket->readInt64();
	if ( m_nFamilyId != FamilyId )
	{
		m_nFamilyId = FamilyId;
		m_pPlayer->GetAchievemnet().AddAchievement( AT_FAMILY );
	}
	m_nPosition		= inPacket->readInt32();
	if ( m_nFamilyId == 0 )
	{
		m_nPosition			= 0;
		m_nContribution		= 0;
		m_nRegistPetCount	= 0;
		for ( int32_t i = 1; i <= MAX_PET_ID; ++i )
		{
			if ( m_vRegistPetList[i] != NULL )
			{
				m_vRegistPetList[i]->SetRegInFamily( 0 );	// 注册宠物全部取消
			}
		}
		bzero( m_vRegistPetList, sizeof( m_vRegistPetList ) );
	}

	m_pPlayer->recalcAttr();
	m_pPlayer->setNeedSyncSelf();
	m_pPlayer->setSyncStatusFlag();

	return ERR_OK; 
}

int32_t CExtCharFamily::onRequestFamilyWarPillarInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	CActivityMap* pActMap = dynamic_cast<CActivityMap*>( m_pPlayer->getMap() );
	if ( NULL == pActMap )
	{
		return ERR_INVALID_DATA;
	}

	CFamilyWar* pAct = dynamic_cast<CFamilyWar*>( pActMap->GetActivity() );
	if ( NULL == pAct )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pAct->IsRuning() )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->getFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	pAct->SendPlayerPillarInfo( m_pPlayer );
	return ERR_OK;
}

int32_t CExtCharFamily::onFamilyWarAddPillarMoney( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nActId		= inPacket->readInt32();
	int32_t nMoney		= inPacket->readInt32();
	CActivityMap* pActMap = dynamic_cast<CActivityMap*>( m_pPlayer->getMap() );
	if ( NULL == pActMap )
	{
		return ERR_INVALID_DATA;
	}

	CFamilyWar* pAct = dynamic_cast<CFamilyWar*>( pActMap->GetActivity() );
	if ( NULL == pAct )
	{
		return ERR_INVALID_DATA;
	}

	if ( pAct->GetId() != nActId )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pAct->IsRuning() )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->getFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pAct->CanAddPillarMoney( m_pPlayer ) )
	{
		return ERR_INVALID_DATA;
	}

	// 同步到社会服务器
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_FAMILYWAR_ADD_PILLAR_MONEY );
	if (NULL == packet)
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt64( m_pPlayer->getFamilyId() );
	packet->writeInt32( nMoney );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialFamilyWarPillarAddMoney( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nMoney		= inPacket->readInt32();
	CActivityMap* pActMap = dynamic_cast<CActivityMap*>( m_pPlayer->getMap() );
	if ( NULL == pActMap )
	{
		return ERR_INVALID_DATA;
	}

	CFamilyWar* pAct = dynamic_cast<CFamilyWar*>( pActMap->GetActivity() );
	if ( NULL == pAct )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nNowMoney = pAct->AddPillarMoney( nMoney );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), CM_ACTIVITY_FAMILYWAR_ADD_PILLAR_MONEY, nNowMoney );
	return ERR_OK;
}

int32_t	CExtCharFamily::onReceiveFamilyTask( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_pPlayer->getRecord(RP_FAMILY_TASK_COUNT) >= MAX_FAMILY_TASK_COUNT )
	{
		return ERR_INVALID_DATA;
	}
	int32_t FamilyTaskId = CFG_DATA.GetFamilyTaskTable().GetFamilyTask( m_pPlayer->getLevel() );
	m_pPlayer->GetTask().receive( FamilyTaskId, TT_FAMILY );
	return ERR_OK;
}

int32_t CExtCharFamily::onGetFamilyTaskReward( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	int32_t Index = inPacket->readInt8();
	int32_t OldRecord = m_pPlayer->getRecord( RP_FAMILY_TASK_REWARD );
	int32_t NewRecord = OldRecord | ( 1 << (Index - 1) );
	if ( OldRecord == NewRecord )
	{
		return ERR_SYETEM_ERR;
	}
	FamilyTaskReward* Rewards =	CFG_DATA.GetFamilyReward( Index );
	if ( NULL == Rewards )
	{
		return ERR_INVALID_DATA;
	}
	FamilyInfo	familyInfo = FAMILY_MANAGER.GetFamilyInfo( GetFamilyId() );
	if ( Rewards->NeedCount > familyInfo.FamilyTaskCount )
	{
		return ERR_INVALID_DATA;
	}
	if ( !m_pPlayer->GetBag().AddItemsAndEggs( Rewards->Rewards, IACR_FAMILY_TASK_REWARD ) )
	{
		return ERR_INVALID_DATA;
	}
	m_pPlayer->updateRecord( RP_FAMILY_TASK_REWARD, NewRecord );
	return ERR_OK;
}

FamilyId_t CExtCharFamily::GetFamilyId() const
{
	return m_nFamilyId;
}

std::string CExtCharFamily::GetFamilyName() const
{
	FamilyInfo info = FAMILY_MANAGER.GetFamilyInfo( m_nFamilyId );
	if ( info.IsEmpty() )
	{
		return "";
	}
	return info.strName;
}

int32_t CExtCharFamily::GetFamilyLevel() const
{
	FamilyInfo info = FAMILY_MANAGER.GetFamilyInfo( m_nFamilyId );
	if ( info.IsEmpty() )
	{
		return 0;
	}
	return info.nLevel;
}

bool CExtCharFamily::TotomIsOpened( int32_t PetBaseId )
{
	FamilyInfo info = FAMILY_MANAGER.GetFamilyInfo( m_nFamilyId );
	if ( info.IsEmpty() )
	{
		return false;
	}
	return info.TotomIsOpened( PetBaseId );
}

int32_t CExtCharFamily::GetFamilyAddBattle() const
{
	FamilyInfo info = FAMILY_MANAGER.GetFamilyInfo( m_nFamilyId );
	if ( info.IsEmpty() )
	{
		return 0;
	}

	const CfgFamily* pCfgFamily = CFG_DATA.GetFamilyTable().GetFamilyInfo( info.nLevel );
	const CfgFamilyPosition* pCfgPosition = CFG_DATA.GetFamilyTable().GetFamilyPosition( m_nPosition );
	if ( NULL == pCfgFamily || NULL == pCfgPosition )
	{
		return 0;
	}

	return ( pCfgFamily->nBattle  + GetFamilyTotomAddBattle() ) * pCfgPosition->nShareBattleRatio / 100;
}

int32_t CExtCharFamily::GetFamilyTotomAddBattle() const
{
	FamilyInfo info = FAMILY_MANAGER.GetFamilyInfo( m_nFamilyId );
	if ( info.IsEmpty() )
	{
		return 0;
	}
	return info.nAddBattle;
}

int8_t CExtCharFamily::GetPosition() const
{
	return m_nPosition;
}

int32_t CExtCharFamily::GetContribution() const
{
	return m_nContribution + m_nPetContribution;
}

bool CExtCharFamily::isFunctionOpen() const
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	return m_pPlayer->getLevel() >= FAMILY_OPEN_LEVEL;
}

int32_t CExtCharFamily::getMaxRegistPetNum( int32_t nLevel )
{
	return CFG_DATA.GetFamilyPetRegistTable().GetLevelCount( nLevel );
}

void CExtCharFamily::sendSocialAddContribution( int32_t nMoney, int32_t nGold )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_ADD_FAMILY_CONTRIBUTE );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( nMoney );
	packet->writeInt32( nGold );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharFamily::sendSocialUpdatePetContribution()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_UPDATE_PET_CONTRIBUTE );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( m_nPetContribution );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharFamily::sendSocialRegistPet( PetId_t nPetId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_FAMILY_REGIST_PET );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt64( nPetId );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharFamily::sendSocialUnRegistPet( PetId_t nPetId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_FAMILY_UNREGIST_PET );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt64( nPetId );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}

void CExtCharFamily::recalPetAddContribute()
{
	int32_t nNewAttribution = calPetAddContribute();
	if ( m_nPetContribution != nNewAttribution )
	{
		m_nPetContribution = nNewAttribution;
		sendSocialUpdatePetContribution();
	}
}

int32_t CExtCharFamily::calPetAddContribute()
{
	int32_t nSum = 0;
	for ( int32_t i = 0; i <= MAX_PET_ID; ++i )
	{
		CObjPet* pPet = m_vRegistPetList[i];
		if ( NULL != pPet )
		{
			nSum += CalPetRegistAddContribute( pPet->GetPoints() );
		}
	}
	return nSum;
}

void CExtCharFamily::OnSynPetContribution()
{
	m_IsLogin = true;
	recalPetAddContribute();
}

void CExtCharFamily::SendAddFamilyTaskCount()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_FAMILY_TASK_COUTN );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->setSize( packet->getWOffset() ); 
	GAME_SERVICE.sendPacket( packet );
}