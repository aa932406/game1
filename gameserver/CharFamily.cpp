#include "stdafx.h"

#include "GameService.h"
#include "Player.h"
#include "CharFamily.h"
#include "FamilyManager.h"
#include "CfgData.h"
#include "ActivityMap.h"
#include "ActivityManager.h"
#include "FamilyWar.h"
#include "FamilyLight.h"

using namespace Answer;

enum ERR_FAMILY
{
	ERR_FAMILY_REGIST_PET_ALREADY	= 6,		// �����Ѿ��Ǽǹ����ֳ�����
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
	bzero( m_vPetRegistTime, sizeof( m_vPetRegistTime ) );	// ������յǼ����
	if ( m_IsLogin )
	{
		recalPetAddContribute();
	}
}

void CExtCharFamily::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_FAMILY_CONTRIBUTION );						// ���ɾ���
	procList.push_back( CM_FAMILY_REGIST_PET );							// ע�����
	procList.push_back( CM_FAMILY_UNREGIST_PET );						// ȡ��ע�����

	procList.push_back( IM_SOCIAL_GAME_CREATE_FAMILY );					// ��������
	procList.push_back( IM_SOCIAL_GAME_UPDATE_FAMILY );					// ���°�����Ϣ


	procList.push_back( CM_REQUEST_ACTIVITY_FAMILY_WAR_PILLAR_INFO );
	procList.push_back( CM_ACTIVITY_FAMILYWAR_ADD_PILLAR_MONEY );
	procList.push_back( IM_SOCIAL_GAME_FAMILYWAR_PILLAR_ADD_MONEY );

	procList.push_back( CM_FAMILY_RECEIVE_TASK );						// ���վ�������
	procList.push_back( CM_FAMILY_GET_TASK_REWARD );

	procList.push_back( CM_FAMILY_UPGRADE_TOTEM );
	procList.push_back( CM_FAMILY_PRAY );
	procList.push_back( CM_FAMILY_ASK_PRAY_RANK );
	procList.push_back( CM_FAMILY_ASK_TOTEM_RANK );
	procList.push_back( CM_FAMILY_ACTIVE_LIGHT );
	procList.push_back( CM_FAMILY_ASK_WAR_INFO );
	procList.push_back( CM_FAMILY_START_WAR );
	procList.push_back( CM_FAMILY_DONATE_ITEM );
	procList.push_back( CM_FAMILY_ASK_DONATE_LOG );
	procList.push_back( CM_FAMILY_RECEIVE_NEW_TASK );
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
	case CM_FAMILY_UPGRADE_TOTEM:			return onUpgradeTotem( inPacket );
	case CM_FAMILY_PRAY:					return onPray( inPacket );
	case CM_FAMILY_ASK_PRAY_RANK:			return onAskPrayRank( inPacket );
	case CM_FAMILY_ASK_TOTEM_RANK:			return onAskTotemRank( inPacket );
	case CM_FAMILY_ACTIVE_LIGHT:			return onActiveFamilyLight( inPacket );
	case CM_FAMILY_ASK_WAR_INFO:			return onAskFamilyWarInfo( inPacket );
	case CM_FAMILY_START_WAR:				return onStartFamilyWar( inPacket );
	case CM_FAMILY_DONATE_ITEM:				return onDonateItem( inPacket );
	case CM_FAMILY_ASK_DONATE_LOG:			return onAskFamilyDonateLog( inPacket );
	case CM_FAMILY_RECEIVE_NEW_TASK:		return onReceiveTask( inPacket );
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
		nAddValue = MAX_FAMILY_CONTRIBUTE - m_nContribution;		// �����������
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
// 		return ERR_INVALID_DATA;		// �ȼ�������û��
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
	// ͬ������������
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
				m_vRegistPetList[i]->SetRegInFamily( 0 );	// ע�����ȫ��ȡ��
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

	// ͬ������������
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
}// ========== 新版本添加方法 ==========

int32_t CExtCharFamily::onAskFamilyInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onAskFamilyMemberList( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onAskFamilyLogs( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onAskFamilyTotem( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onActiveTotem( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onOpenTotem( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}


int32_t CExtCharFamily::onSocialApplyFamily( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialApprove( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialKick( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialLeave( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialDestroy( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialAppoint( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialEditNotice( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialRequestFamilyInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialRequestMemberList( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialRequestLogs( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialRequestTotemList( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialRequestApplicants( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialCancelApply( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialRequestFamilyWarPillarInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialFamilyWarAddPillarMoney( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialGetDailyReward( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onGetTaskReward( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialRequestPlayerPets( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialFamilyTaskCount( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialRequestRegistPets( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::onSocialAddContribution( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CExtCharFamily::OnDaySwitch()
{
	return ERR_OK;
}

void CExtCharFamily::FamilySay( const char* pMsg )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
}

// ========== 新版本添加方法实现 ==========

int32_t CExtCharFamily::onReceiveTask( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
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
	if ( FamilyTaskId <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	m_pPlayer->GetTask().receive( FamilyTaskId, TT_FAMILY );
	return ERR_OK;
}

int32_t CExtCharFamily::onUpgradeTotem( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nPetBaseId = inPacket->readInt32();
	if ( nPetBaseId <= 0 || nPetBaseId > MAX_PET_ID )
	{
		return ERR_INVALID_DATA;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	// Check totem is already opened
	if ( !TotomIsOpened( nPetBaseId ) )
	{
		return ERR_INVALID_DATA;
	}
	// Check family level meets requirement
	int32_t nNeedLevel = CFG_DATA.GetFamilyTable().GetTotomActiveLevel( nPetBaseId );
	if ( nNeedLevel <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	if ( GetFamilyLevel() < nNeedLevel )
	{
		return ERR_FAMILY_LEVEL_LOW;
	}
	// Upgrade totem: send social message
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_FAMILY_ADD_CONTRIBUTION );
	if ( NULL == packet )
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( 0 );
	packet->writeInt32( 0 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacket( packet );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nPetBaseId );
	return ERR_OK;
}

int32_t CExtCharFamily::onPray( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	int32_t nGold = inPacket->readInt32();
	if ( nGold <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	if ( nGold > MAX_FAMILY_CONTRIBUTE_GOLD )
	{
		nGold = MAX_FAMILY_CONTRIBUTE_GOLD;
	}
	if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < nGold )
	{
		return ERR_NOT_ENOUGH_GOLD;
	}
	// Check daily pray limit
	int32_t nPrayCount = m_pPlayer->getRecord( RP_FAMILY_PRAY_COUNT );
	if ( nPrayCount >= 10 )
	{
		return ERR_INVALID_DATA;
	}
	m_pPlayer->updateRecord( RP_FAMILY_PRAY_COUNT, nPrayCount + 1 );
	// Deduct gold, add exp and contribution
	m_pPlayer->DecCurrency( CURRENCY_GOLD, nGold, GCR_FAMILY_CONTRIBUTE, m_nFamilyId );
	int32_t nAddExp = nGold * 100;
	int32_t nAddContrib = nGold * 10;
	m_pPlayer->addExp( nAddExp );
	m_nContribution += nAddContrib;
	// Send to social server
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_FAMILY_ADD_CONTRIBUTION );
	if ( NULL == packet )
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( nAddContrib );
	packet->writeInt32( nGold );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacket( packet );
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_FAMILY_DONATE, nAddContrib );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nAddContrib );
	return ERR_OK;
}

int32_t CExtCharFamily::onAskPrayRank( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	// Reply with current contribution rank info
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), m_nContribution );
	return ERR_OK;
}

int32_t CExtCharFamily::onAskTotemRank( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	// Reply with family level as totem rank
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), GetFamilyLevel() );
	return ERR_OK;
}

int32_t CExtCharFamily::onActiveFamilyLight( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	int32_t nCount = inPacket->readInt32();
	if ( nCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	// Check player is in family light map
	CActivityMap* pActMap = dynamic_cast<CActivityMap*>( m_pPlayer->getMap() );
	if ( NULL == pActMap )
	{
		return ERR_INVALID_DATA;
	}
	CFamilyLight* pLight = dynamic_cast<CFamilyLight*>( pActMap->GetActivity() );
	if ( NULL == pLight )
	{
		return ERR_INVALID_DATA;
	}
	if ( !pLight->IsRuning() )
	{
		return ERR_INVALID_DATA;
	}
	pLight->DrinkWine( m_pPlayer, nCount );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nCount );
	return ERR_OK;
}

int32_t CExtCharFamily::onAskFamilyWarInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	// Get family war activity and send info
	int32_t nActId = inPacket->readInt32();
	CActivity* pActivity = ACTIVITY_MANAGER.GetActivity( nActId );
	if ( NULL == pActivity )
	{
		return ERR_INVALID_DATA;
	}
	if ( pActivity->GetType() != ATI_FAMILY_WAR )
	{
		return ERR_INVALID_DATA;
	}
	pActivity->SendPlayerActivityInfo( m_pPlayer );
	return ERR_OK;
}

int32_t CExtCharFamily::onStartFamilyWar( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	// Only family leader can start war
	if ( m_nPosition != FP_LEADER )
	{
		return ERR_INVALID_DATA;
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), m_nFamilyId );
	return ERR_OK;
}

int32_t CExtCharFamily::onDonateItem( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	int32_t nBagSlot = inPacket->readInt32();
	int32_t nCount = inPacket->readInt32();
	if ( nBagSlot < 0 || nCount <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	MemChrBag bagItem = m_pPlayer->getBagSlotData( nBagSlot );
	if ( bagItem.itemId <= 0 || bagItem.itemCount < nCount )
	{
		return ERR_INVALID_DATA;
	}
	// Check daily donate limit
	int32_t nDonateCount = m_pPlayer->getRecord( RP_FAMILY_DONATE_COUNT );
	if ( nDonateCount >= 20 )
	{
		return ERR_INVALID_DATA;
	}
	m_pPlayer->updateRecord( RP_FAMILY_DONATE_COUNT, nDonateCount + 1 );
	// Remove item from bag
	ItemData itemData;
	itemData.m_nId = bagItem.itemId;
	itemData.m_nClass = bagItem.itemClass;
	itemData.m_nCount = nCount;
	Int32Vector vSlot( 1, nBagSlot );
	if ( !m_pPlayer->GetBag().RemoveItem( vSlot, itemData, IDCR_FAMILY_DONATE ) )
	{
		return ERR_SYETEM_ERR;
	}
	// Add contribution based on item quantity
	int32_t nAddContrib = nCount * 100;
	if ( nAddContrib + m_nContribution > MAX_FAMILY_CONTRIBUTE )
	{
		nAddContrib = MAX_FAMILY_CONTRIBUTE - m_nContribution;
	}
	m_nContribution += nAddContrib;
	// Send to social server
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, IM_GAME_SOCIAL_FAMILY_ADD_CONTRIBUTION );
	if ( NULL == packet )
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt32( nAddContrib );
	packet->writeInt32( 0 );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacket( packet );
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_FAMILY_DONATE, nAddContrib );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nAddContrib );
	return ERR_OK;
}

int32_t CExtCharFamily::onAskFamilyDonateLog( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}
	// Send current contribution as donation log
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), m_nContribution );
	return ERR_OK;
}
