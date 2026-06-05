
#include <algorithm>

#include "stdafx.h"
#include "DataStructs.h"
#include "CharPet.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "PetManager.h"
#include "RandHelper.h"
#include "PDUDefine.h"
#include "PoolManager.h"

int32_t	vPetBagSize[PET_BAG_TYPE_SIZE] = { PET_BAG_SIZE, PET_DEPORT_SIZE };
#define ADD_SOUL	800		//�������޻ָ����ֵ
using namespace Answer;

enum ERR_PET
{
	ERR_PET_USE_LUCKY_ITEM_FAIL	= 1,		// ����ʹ������ֵ����ʧ��
};

CExtCharPet::CExtCharPet()
{
//	initEggBag( PEBT_BAG, PET_EGG_BAG_SIZE );
	initEggBag( PEBT_HATCH_POOL, PET_HATCH_POOL_SIZE );
//	initEggBag( PEBT_MUTI_HATCH_POOL, PET_MUTI_HATCH_POOL_SIZE );

	// ָ���ʼ��
	m_pRidePet	= NULL;
	bzero( m_vFightPet,		sizeof( m_vFightPet ) );
	bzero( m_vAllPet,		sizeof( m_vAllPet ) );
	bzero( m_vPetKnight,	sizeof( m_vPetKnight ) );
	bzero( m_vPetWearQiShi, sizeof( m_vPetWearQiShi ) );
	bzero ( m_vLastFightPet,sizeof( m_vLastFightPet ) );
}

CExtCharPet::~CExtCharPet()
{
}

void CExtCharPet::OnCleanUp()
{
	cleanPet();
//	cleanEggBag( PEBT_BAG, PET_EGG_BAG_SIZE );
	cleanEggBag( PEBT_HATCH_POOL, PET_HATCH_POOL_SIZE );
//	cleanEggBag( PEBT_MUTI_HATCH_POOL, PET_MUTI_HATCH_POOL_SIZE );

	m_nEggDirtyList.clear();
	m_nLastTick = 0;
	m_nLastAddSoulTick	= 0;
	m_pRidePet	= NULL;
	bzero( m_vFightPet,		sizeof( m_vFightPet ) );
	bzero( m_vAllPet,		sizeof( m_vAllPet ) );
	bzero( m_vPetKnight,	sizeof( m_vPetKnight ) );
	bzero( m_vPetWearQiShi, sizeof( m_vPetWearQiShi ) );
	bzero ( m_vLastFightPet,sizeof( m_vLastFightPet ) );
}

void CExtCharPet::cleanPet()
{
	m_nFightingCount	= 0;
	m_pRidePet			= NULL;
	bzero( m_vFightPet,			sizeof( m_vFightPet ) );
	bzero( m_vPetKnight,		sizeof( m_vPetKnight ) );
	bzero( m_vKnightAddValue,	sizeof( m_vKnightAddValue ) );
	bzero( m_vPetBagSize,		sizeof( m_vPetBagSize ) );

	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( pPet != NULL )
		{
			pPet->LeaveMap();
			GAME_SERVICE.removePet( pPet );
			POOL_MANAGER.push<CObjPet>( pPet );
			m_vAllPet[i] = NULL;
		}
	}
}

void CExtCharPet::AddPetFromGift( CfgPetGift* pPetGift )
{
	if ( NULL == pPetGift )
	{
		return;
	}
	CPet* pPet1 = PET_MANAGER.CreateNewPet( pPetGift->nPetBaseId, m_pPlayer, PFW_GIFT );
	CObjPet* pObjPet1 = POOL_MANAGER.pop<CObjPet>();
	if ( NULL == pPet1|| NULL == pObjPet1 )
	{
		return;
	}
	pPet1->ReSetBaseAttr( pPetGift );
	PET_MANAGER.AddPet( pPet1 );
	pPet1->SetPetBorn();
	pObjPet1->Init( pPet1, m_pPlayer );
	GAME_SERVICE.addPet( pObjPet1 );
	addPet( pObjPet1, PBT_BAG );
	pObjPet1->SendPetInfo();
}

void CExtCharPet::OnLoadFromDB( const PlayerDBData& dbData )
{
	if ( dbData.m_CharPets.charPets.empty() )	// ��ʼ��û�г������ֻ
	{
		if ( NULL == m_pPlayer )
		{
			return;
		}
		const Int32List& pets = CFG_DATA.GetPetTable().GetInitPets( m_pPlayer->getJob() );
		for ( Int32List::const_iterator iter = pets.begin(); iter != pets.end(); ++iter )
		{
			CPet* pPet = PET_MANAGER.CreateNewPet( *iter, m_pPlayer, PFW_BORN );
			CObjPet* pObjPet = POOL_MANAGER.pop<CObjPet>();
			if ( NULL == pPet || NULL == pObjPet )
			{
				return;
			}

			PET_MANAGER.AddPet( pPet );
			pPet->SetPetBorn();
			pObjPet->Init( pPet, m_pPlayer );
			if ( addFightPet( pObjPet ) )
			{
				pObjPet->Fighting();
			}			
			GAME_SERVICE.addPet( pObjPet );
			addPet( pObjPet, PBT_BAG );
			pObjPet->SendPetInfo();
		}
	}
	else
	{
		DBPetList::const_iterator iter = dbData.m_CharPets.charPets.begin();
		DBPetList::const_iterator eiter = dbData.m_CharPets.charPets.end();
		for ( ; iter != eiter; ++iter )
		{
			CObjPet* pPet = POOL_MANAGER.pop<CObjPet>();
			if ( pPet != NULL )
			{
				pPet->SetOwner( m_pPlayer );
				pPet->OnLoadFromDB( *iter );
				if ( pPet->GetPet() == NULL )
				{
					continue;
				}
				if ( pPet->GetState() == PS_FIGHTING || pPet->GetState() == PS_ZOARIUM )
				{
					addFightPet( pPet );
				}
				else if ( pPet->GetState() == PS_RIDE )
				{
					ridePet( pPet );
				}
				addPet( pPet, pPet->GetBagType() );
				GAME_SERVICE.addPet( pPet );
			}
		}
		initKnight();
	}
	{
		DBPetEggList::const_iterator iter = dbData.m_CharPets.charPetEggs.begin();
		DBPetEggList::const_iterator eiter = dbData.m_CharPets.charPetEggs.end();
		for ( ; iter != eiter; ++iter )
		{
			PetEgg* pEgg = getEgg( iter->nBag,	iter->nSlot );
			if ( pEgg != NULL )
			{
				pEgg->Init( *iter );
			}
		}
	}
}

void CExtCharPet::OnSaveToDB( PlayerDBData& dbData )
{
	savePets( dbData.m_CharPets.charPets );
	saveEggBag( PEBT_BAG, dbData.m_CharPets.charPetEggs );
	saveEggBag( PEBT_HATCH_POOL, dbData.m_CharPets.charPetEggs );
	saveEggBag( PEBT_MUTI_HATCH_POOL, dbData.m_CharPets.charPetEggs );
}

void CExtCharPet::OnUpdate( int64_t curTick )
{
	for ( int32_t i = 0; i < PET_LIST_SIZE ; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( NULL == pPet )
		{
			continue;
		}

		if ( pPet->IsFighting() )
		{
			pPet->update();
			pPet->ReplyHp( curTick );
		}
		else
		{
			pPet->refresh();
		}
	}
	AddSoul( curTick );
	checkPetEggDirty();

	if ( curTick - m_nLastTick < 1000 )
	{
		return;
	}
	m_nLastTick = curTick;
	checkHatchPool( PEBT_HATCH_POOL, PET_EGG_HATCH_TIME, m_pPlayer->getNow() );
	//checkHatchPool( PEBT_MUTI_HATCH_POOL, PET_EGG_MUTI_HATCH_TIME, m_pPlayer->getNow() );
}

void CExtCharPet::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back ( CM_PET_REQUEST_INFO );
	procList.push_back ( CM_PET_FIGHTING );
	procList.push_back ( CM_PET_REST );
	procList.push_back ( CM_PET_ZOARIUM );
	procList.push_back ( CM_PET_ZOARIUM_OFF );
	procList.push_back ( CM_PET_RIDE );
	procList.push_back ( CM_PET_CHANGE_NAME	);
	procList.push_back ( CM_PET_RELEASE );
	procList.push_back ( CM_PET_HATCHING );
	procList.push_back ( CM_PET_MUTI_HATCHING );
	procList.push_back ( CM_PET_REHATCHING );
	procList.push_back ( CM_PET_OPEN_EGG );
	procList.push_back ( CM_PET_DROP_EGG );
	procList.push_back ( CM_PET_USE_EXP_ITEM );
	procList.push_back ( CM_PET_USE_PHASE_ITEM );
	procList.push_back ( CM_PET_STOP_HATCHING );
	procList.push_back ( CM_PET_QUICK_HATCHING );
	procList.push_back ( CM_PET_EGG_MOVE );
	procList.push_back ( CM_PET_LEARN_SKILL );
	procList.push_back ( CM_PET_FORGET_SKILL );
	procList.push_back ( CM_PET_ILLUSION );
	procList.push_back ( CM_PET_DEPORT );
	procList.push_back ( CM_PET_SET_KNIGHT );
	procList.push_back ( CM_PET_USE_LUCKY_ITEM );
	procList.push_back ( CM_PET_MOVE_TO_BAG );
	procList.push_back ( CM_PET_GET_FROM_BAG );
	procList.push_back ( CM_WEAR_QI_SHI );
	procList.push_back( CM_PET_ILLUSION_BY_LI_BAO );
procList.push_back( CM_PET_FIGHT );
	procList.push_back( CM_PET_HUANHUA );
	procList.push_back( CM_PET_UP_STAR );
	procList.push_back( CM_PET_DRESS_EQUIP );
	procList.push_back( CM_PET_UNDRESS_EQUIP );
	procList.push_back( CM_PET_FITTING );
	procList.push_back( CM_PET_REST_PET );
	procList.push_back( CM_PET_CHANGE_AI );
	procList.push_back( CM_PET_SKILL_UP_LEVEL );
}

int32_t CExtCharPet::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch ( nProcId )
	{
	case CM_PET_REQUEST_INFO:					return onRequestPetInfo( inPacket );
	case CM_PET_FIGHTING:						return onFighting( inPacket );
	case CM_PET_REST:							return onRest( inPacket );
	case CM_PET_ZOARIUM:						return onZoarium( inPacket );
	case CM_PET_ZOARIUM_OFF:					return onZoariumOff( inPacket );
	case CM_PET_RIDE:							return onRide( inPacket );
	case CM_PET_CHANGE_NAME:					return onChangeName( inPacket );
	case CM_PET_RELEASE:						return onPetRelease( inPacket );
//	case CM_PET_HATCHING:						return onHatching( inPacket );
//	case CM_PET_MUTI_HATCHING:					return onMutiHatching( inPacket );
	case CM_PET_REHATCHING:						return onReHatching( inPacket );
	case CM_PET_OPEN_EGG:						return onEggOpen( inPacket );
	case CM_PET_DROP_EGG:						return onDropEgg( inPacket );
	case CM_PET_USE_EXP_ITEM:					return onUseExpItem( inPacket );
	case CM_PET_USE_PHASE_ITEM:					return onUsePhaseItem( inPacket );
	case CM_PET_STOP_HATCHING:					return onStopHatching( inPacket );
	case CM_PET_QUICK_HATCHING:					return onQuickHatching( inPacket );
	case CM_PET_EGG_MOVE:						return onPetEggMove( inPacket );
	case CM_PET_LEARN_SKILL:					return onLearnSkill( inPacket );
	case CM_PET_FORGET_SKILL:					return onForgetSkill( inPacket );
	case CM_PET_ILLUSION:						return onIllusion( inPacket );
	case CM_PET_DEPORT:							return onDeport( inPacket );
	case CM_PET_SET_KNIGHT:						return onSetKnight( inPacket );
	case CM_PET_USE_LUCKY_ITEM:					return onUseLuckyItem( inPacket );
// 	case CM_PET_MOVE_TO_BAG:					return onMoveToBag( inPacket );
// 	case CM_PET_GET_FROM_BAG:					return onGetFromBag( inPacket );
	case CM_WEAR_QI_SHI:						return onWearQiShi( inPacket );
	case CM_PET_ILLUSION_BY_LI_BAO:			return onLiBaoIllusion( inPacket );
	case CM_PET_FIGHT:						return onFight( inPacket );
	case CM_PET_HUANHUA:					return onPetHuanHua( inPacket );
	case CM_PET_UP_STAR:					return onUpStar( inPacket );
	case CM_PET_DRESS_EQUIP:				return onDressEquip( inPacket );
	case CM_PET_UNDRESS_EQUIP:				return onUnDressEquip( inPacket );
	case CM_PET_FITTING:					return onFitting( inPacket );
	case CM_PET_REST_PET:					return onRestPet( inPacket );
	case CM_PET_CHANGE_AI:					return onChangeAi( inPacket );
	case CM_PET_SKILL_UP_LEVEL:				return onSkillUpLevel( inPacket );
	default:	break;
	}
	return ERR_OK;
}

int32_t CExtCharPet::onRequestPetInfo( NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CPet* pPet = PET_MANAGER.GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	pPet->SendPetInfo( m_pPlayer );
	return ERR_OK;
}

int32_t CExtCharPet::Fighting( CObjPet* pPet )
{
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}

// 	if ( m_pPlayer->getLevel() + 9 < pPet->getLevel() )
// 	{
// 		return ERR_SYETEM_ERR;
// 	}

	if ( pPet->IsZoarium() || pPet->IsFighting() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pPet->GetBagType() != PBT_BAG )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pPet->getOwner() != m_pPlayer->getCid() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pPet->IsRide() )
	{
		ridePet( NULL );
	}
	Map* pMap = m_pPlayer->getMap();
	if ( NULL == pMap )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !pMap->CanUsePet() )
	{
		return ERR_INVALID_DATA;
	}

	addFightPet( pPet );
	pPet->Fighting();
	pPet->EnterMap();
	pPet->SendPetInfo( false );
	m_pPlayer->recalcAttr();
	broadcastMapPetFighting( pPet );
	return ERR_OK;
}

int32_t CExtCharPet::onFighting( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	if ( m_nFightingCount >= getMaxFightPet() )
	{
		return ERR_SYETEM_ERR;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( pPet == NULL )
	{
		return ERR_SYETEM_ERR;
	}
	Fighting( pPet );
	return ERR_OK;
}

int32_t CExtCharPet::onRest( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !pPet->IsFighting() )
	{
		return ERR_SYETEM_ERR;
	}

	removeFightPet( pPet );
	pPet->Rest();
	pPet->LeaveMap();
	pPet->SendPetInfo( false );
	m_pPlayer->recalcAttr();
	return ERR_OK;
}

int32_t CExtCharPet::onZoarium( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( pPet->GetBaseId() );
	if ( NULL == pCfgPet )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pCfgPet->m_Zoarium != 1 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pPet->GetState() == PS_RIDE )
	{
		if ( m_nFightingCount >= getMaxFightPet() )
		{
			return ERR_SYETEM_ERR;
		}
		ridePet( NULL );
		if ( !addFightPet(pPet) )
		{
			return ERR_SYETEM_ERR;
		}
		pPet->Fighting();
	}

	if ( !pPet->IsFighting() )
	{
		return ERR_SYETEM_ERR;
	}

	// �����Ժ�ӵ�ͼ��ʧ
	pPet->Zoarium();
	pPet->LeaveMap();
	pPet->SendPetInfo( false );
	m_pPlayer->recalcAttr();
	m_pPlayer->AddHP( pPet->GetAttrValue( CObjAttrs::ATTR_HP ) / 10 );
	return ERR_OK;
}

int32_t CExtCharPet::onZoariumOff( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !pPet->IsZoarium() )
	{
		return ERR_SYETEM_ERR;
	}

	// ��������Ժ��ս
	int32_t SubHp		= pPet->GetAttrValue( CObjAttrs::ATTR_HP ) / 10;
	int32_t PlayerHp	= m_pPlayer->GetHP();
	if ( SubHp >= PlayerHp )
	{
		SubHp = PlayerHp - 1;
	}
	m_pPlayer->AddHP( -1 * SubHp );
	pPet->Fighting();
	pPet->EnterMap();
	pPet->SendPetInfo( false );
	m_pPlayer->recalcAttr();
	broadcastMapPetFighting( pPet );
	return ERR_OK;
}

int32_t CExtCharPet::onRide( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	if ( nPetId == 0 )	// ������
	{
		ridePet( NULL );
		m_pPlayer->recalcAttr();
		return ERR_OK;
	}

	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !pPet->isAlive() )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !pPet->IsRidePet() )
	{
		return ERR_SYETEM_ERR;
	}

	if ( pPet->IsRide() )
	{
		return ERR_SYETEM_ERR;
	}

	if ( pPet->IsFighting() )
	{
		removeFightPet( pPet );
		pPet->Rest();
		pPet->LeaveMap();
	}
	else if ( pPet->IsZoarium() )
	{
		removeFightPet( pPet );
		pPet->Rest();
	}

	ridePet( pPet );
	m_pPlayer->recalcAttr();
	return ERR_OK;
}

int32_t CExtCharPet::onChangeName( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	std::string	strName = inPacket->readUTF8(true);
	
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pPet->IsRest() )
	{
		return ERR_INVALID_DATA;
	}

	pPet->ChangeName( strName );
	pPet->SendPetInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtCharPet::onPetRelease( Answer::NetPacket* inPacket )			// ��������
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pPet->IsRest() || pPet->GetKnight() != PK_NONE || pPet->IsRegInFamily() || pPet->GetQiShi() != 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( IsTopPet( pPet ) )
	{
		return ERR_INVALID_DATA;
	}

	RemovePet( pPet );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nPetId );
	return ERR_OK;
}

int32_t CExtCharPet::onHatching( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nSlot = inPacket->readInt32();
	PetEgg* pEgg = getEgg( PEBT_BAG, nSlot );
	if ( pEgg == NULL || pEgg->IsEmpty() || pEgg->GetState() != PES_NORMAL )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nHatchIndex = addEgg( PEBT_HATCH_POOL, *pEgg );
	if ( nHatchIndex == -1 )
	{
		return ERR_INVALID_DATA;
	}

	PetEgg* pHatchEgg = getEgg( PEBT_HATCH_POOL, nHatchIndex );
	if ( NULL == pHatchEgg )
	{
		return ERR_INVALID_DATA;
	}

	pHatchEgg->StartHatch( m_pPlayer->getNow() );
	removeEgg( PEBT_BAG, nSlot );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nHatchIndex );
	return ERR_OK;
}

bool CExtCharPet::AddHatchBag( int32_t PetId )
{
// 	if ( !m_pPlayer->GetSysSettingInfo(  SS_PETEGG ) )
// 	{
// 		return false;
// 	}
	PetEgg egg;
	egg.Init( PetId );	
	int32_t nHatchIndex = addEgg( PEBT_HATCH_POOL, egg );
	if ( nHatchIndex == -1 )
	{
		return false;
	}
	PetEgg* pHatchEgg = getEgg( PEBT_HATCH_POOL, nHatchIndex );
	if ( NULL == pHatchEgg )
	{
		return false;
	}
	pHatchEgg->StartHatch( m_pPlayer->getNow() );
	return true;
}

int32_t CExtCharPet::GetEggBagAddHatchBagFreeCount()
{
	int32_t BagFreeCount = 0;
// 	PetEgg* pEggPool = getEggBagPool( PEBT_BAG );
// 	if ( NULL == pEggPool )
// 	{
// 		return BagFreeCount;
// 	}
// 	int32_t nSize = getEggBagSize( PEBT_BAG );
// 	for ( int32_t i = 0; i < nSize; ++i )
// 	{
// 		if ( pEggPool[i].IsEmpty() )
// 		{
// 			BagFreeCount++;
// 		}
// 	}
// 
// 	if ( !m_pPlayer->GetSysSettingInfo(  SS_PETEGG ) )
// 	{
// 		return BagFreeCount;
// 	}
	PetEgg* pEggPool = getEggBagPool( PEBT_HATCH_POOL );
	if ( NULL == pEggPool )
	{
		return BagFreeCount;
	}
	int32_t nSize = getEggBagSize( PEBT_HATCH_POOL );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		 if ( pEggPool[i].IsEmpty() )
		 {
			 BagFreeCount++;
		 }
	}
	return BagFreeCount;
}

int32_t	CExtCharPet::onMutiHatching( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCount = inPacket->readInt32();
	Int32List slotList;
	for ( int32_t i = 0; i < nCount; ++i )
	{
		slotList.push_back( inPacket->readInt32() );
	}

	if ( getEmptyEggPos( PEBT_MUTI_HATCH_POOL ) < nCount )
	{
		return ERR_INVALID_DATA;
	}

	PetEggList eggList;
	if ( !getEggList( PEBT_BAG, slotList, eggList ) )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nStartTime = m_pPlayer->getNow();
	PetEggList::iterator iter = eggList.begin();
	PetEggList::iterator eiter = eggList.end();
	for ( ; iter != eiter; ++iter )
	{
		PetEgg* pEgg = *iter;
		if ( pEgg != NULL )
		{
			pEgg->StartHatch( nStartTime );
			addEgg( PEBT_MUTI_HATCH_POOL, *pEgg );
		}
	}

	removeEgg( PEBT_BAG, slotList );
	return ERR_OK;
}

int32_t CExtCharPet::onReHatching( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCount = inPacket->readInt32();
	PetEggList eggList;
	for ( int32_t i = 0; i < nCount; ++i )
	{
		int32_t nSlot = inPacket->readInt32();
		PetEgg* pEgg = getEgg( PEBT_MUTI_HATCH_POOL, nSlot );
		if ( pEgg == NULL || pEgg->IsEmpty() || pEgg->GetState() != PES_CAN_OPEN )
		{
			return ERR_INVALID_DATA;
		}
		eggList.push_back( pEgg );
	}

	// ÿ�ŵ�����3ħʯ
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, PET_EGG_REHATCH_COST * ( nCount > 10 ? 10 : nCount ), GCR_PET_EGG_REHATCH ) )
	{
		return ERR_INVALID_DATA;
	}

	PetEggList::iterator iter = eggList.begin();
	PetEggList::iterator eiter = eggList.end();
	for ( ; iter != eiter; ++iter )
	{
		PetEgg* pEgg = *iter;
		if ( pEgg != NULL )
		{
			CPet* pPet = PET_MANAGER.GetPet( pEgg->GetPetId() );
			if ( NULL == pPet )
			{
				return ERR_INVALID_DATA;
			}

			pEgg->StartHatch( m_pPlayer->getNow() );
			addPetEggDirty( pEgg );
		}
	}

	return ERR_OK;
}

int32_t CExtCharPet::onQuickHatching( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCount = inPacket->readInt32();
	int32_t nNow = m_pPlayer->getNow();
	int32_t nTotalTime = 0;
	PetEggList eggList;
	for ( int32_t i = 0; i < nCount; ++i )
	{
		int8_t	nBag = inPacket->readInt8();
		int32_t nSlot = inPacket->readInt32();
		if ( nBag != PEBT_MUTI_HATCH_POOL )
		{
			continue;
		}
		PetEgg* pEgg = getEgg( nBag, nSlot );
		if ( pEgg == NULL || pEgg->IsEmpty() || pEgg->GetState() != PES_HATCHING )
		{
			return ERR_INVALID_DATA;
		}
		eggList.push_back( pEgg );
		nTotalTime += pEgg->GetStartTime() + PET_EGG_MUTI_HATCH_TIME - nNow;
	}
	// ÿ30��������1ħʯ
	int32_t nNeedGold = nTotalTime % PET_EGG_QUICK_HATCH_COST == 0 ? nTotalTime / PET_EGG_QUICK_HATCH_COST : nTotalTime / PET_EGG_QUICK_HATCH_COST + 1;
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nNeedGold, GCR_PET_EGG_QUICK_HATCH ) )
	{
		return ERR_INVALID_DATA;
	}

	PetEggList::iterator iter = eggList.begin();
	PetEggList::iterator eiter = eggList.end();
	for ( ; iter != eiter; ++iter )
	{
		PetEgg* pEgg = *iter;
		if ( pEgg != NULL )
		{
			petBorn( *pEgg );
		}
	}
	return ERR_OK;
}

int32_t CExtCharPet::onStopHatching( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	nBag	= inPacket->readInt8();
	int32_t nSlot	= inPacket->readInt32();

	PetEgg* pEgg = getEgg( nBag, nSlot );
	if ( NULL == pEgg )
	{
		return ERR_INVALID_DATA;
	}

	if ( pEgg->GetState() != PES_HATCHING )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nDesSlot = addEgg( PEBT_BAG, *pEgg );
	PetEgg* pDesEgg = getEgg( PEBT_BAG, nDesSlot );
	if ( NULL == pDesEgg )
	{
		return ERR_INVALID_DATA;
	}

	pDesEgg->StopHatch();
	removeEgg( nBag, nSlot );
	return ERR_OK;
}

int32_t CExtCharPet::onPetEggMove( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	nBag		= inPacket->readInt8();
	int32_t nSrcSlot	= inPacket->readInt32();
	int32_t nDesSlot	= inPacket->readInt32();

	PetEgg* pSrcEgg = getEgg( nBag, nSrcSlot );
	PetEgg* pDesEgg = getEgg( nBag, nDesSlot );
	if ( NULL == pSrcEgg || NULL == pDesEgg )
	{
		return ERR_INVALID_DATA;
	}

	PetEgg egg;
	egg.Set( *pSrcEgg );
	pSrcEgg->Set( *pDesEgg );
	pDesEgg->Set( egg );
	addPetEggDirty( pSrcEgg );
	addPetEggDirty( pDesEgg );
	return ERR_OK;
}

int32_t CExtCharPet::onEggOpen( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	nBag	= inPacket->readInt8();
	int32_t nSlot	= inPacket->readInt32();
	PetEgg* pEgg = getEgg( nBag, nSlot );
	if ( NULL == pEgg )
	{
		return ERR_INVALID_DATA;
	}

	if ( pEgg->GetState() != PES_CAN_OPEN )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_vPetBagSize[PBT_BAG] >= PET_BAG_SIZE )
	{
		return ERR_INVALID_DATA;
	}

	CPet* pPet = PET_MANAGER.GetPet( pEgg->GetPetId() );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	CObjPet* pObjPet = POOL_MANAGER.pop<CObjPet>();
	if ( NULL == pObjPet )
	{
		return ERR_INVALID_DATA;
	}

	if ( pPet != NULL )
	{
		pPet->SetPetBorn();
	}

	pObjPet->Init( pPet, m_pPlayer );
	GAME_SERVICE.addPet( pObjPet );

	removeEgg( nBag, nSlot );
	addPet( pObjPet, PBT_BAG );

	pObjPet->SendPetInfo();
	return ERR_OK;
}

int32_t CExtCharPet::onDropEgg( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	nBag	= inPacket->readInt8();
	int32_t nSlot	= inPacket->readInt32();

	PetEgg* pEgg = getEgg( nBag, nSlot );
	if ( NULL == pEgg )
	{
		return ERR_INVALID_DATA;
	}

	CPet* pPet = PET_MANAGER.GetPet( pEgg->GetPetId() );

	if ( !removeEgg( nBag, nSlot ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( pPet != NULL )
	{
		PET_MANAGER.DelPet( pPet );	// ɾ������
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nSlot );
	return ERR_OK;
}

int32_t CExtCharPet::onUseExpItem( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	int32_t nBagSlot = inPacket->readInt32();
	
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pPet->AliveFlag() )
	{
		// �������ܳԾ�����
		return ERR_INVALID_DATA;
	}

	MemChrBag slot = m_pPlayer->getBagSlotData( nBagSlot );
	if ( slot.itemClass != IC_NORMAL )
	{
		return ERR_INVALID_DATA;
	}

	CfgItem* cfgItem = CFG_DATA.getItem( slot.itemId );
	if ( NULL == cfgItem )
	{
		return ERR_INVALID_DATA;
	}

	bool bNeedCheck = false;
	PET_RECORD record;
	int32_t nAddExp = 0;
	if ( slot.itemId == ISI_PET_EXP_GRAIN )				// ʥ��ħ��
	{
		record = PR_USE_EXP_GRAIN;
		bNeedCheck = true;
		nAddExp = atoi( cfgItem->effect.c_str() );
	}
	else if ( slot.itemId == ISI_EXP_BALL )				// ������
	{
		if( pPet->getLevel() >= m_pPlayer->getLevel() + LEVEL_DIFF )
		{
			return ERR_INVALID_DATA;
		}
		record = PR_USE_EXP_BALL;
		bNeedCheck = true;
		nAddExp = atoi( cfgItem->effect.c_str() );
	}
	else if ( slot.itemId == ISI_SPECIAL_EXP_BALL )		// �ؼ�������
	{
		if( pPet->getLevel() >= m_pPlayer->getLevel() + LEVEL_DIFF )
		{
			return ERR_INVALID_DATA;
		}
		bNeedCheck = false;
		nAddExp = atoi( cfgItem->effect.c_str() );
	}
	else
	{
		return ERR_INVALID_DATA;
	}

	if ( bNeedCheck && !pPet->CheckRecord( record ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( bNeedCheck )
	{
		if ( !pPet->CheckRecord( record ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	Int32Vector vSlot;
	vSlot.push_back( nBagSlot );
	ItemData data = { slot.itemId, slot.itemClass, 1 };
	
	if ( !m_pPlayer->GetBag().RemoveItem( vSlot, data, IDCR_PET_USE_ITEM ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( bNeedCheck )
	{
		pPet->AddRecord( record );
	}
	pPet->AddExp( nAddExp );
	pPet->SendPetInfo();

	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nAddExp );
	return ERR_OK;
}

int32_t CExtCharPet::onUsePhaseItem( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId		= static_cast<PetId_t>( inPacket->readInt64() );
	int32_t nBagSlot	= inPacket->readInt32();

	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag slot = m_pPlayer->getBagSlotData( nBagSlot );
	if ( slot.itemClass != IC_NORMAL )
	{
		return ERR_INVALID_DATA;
	}

	PET_PHASE phase = PP_INVALID;
	if ( slot.itemId == ISI_PET_KIWI_FRUIT )				// �����
	{
		phase = PP_INVALID;	// �Զ����
	}
	else if ( slot.itemId == ISI_PET_ELECTRIC_POTION )		// �罬ҩˮ
	{
		phase = PP_ELECTRIC;
	}
	else
	{
		return ERR_INVALID_DATA;
	}

	Int32Vector vSlot;
	vSlot.push_back( nBagSlot );
	ItemData data = { slot.itemId, slot.itemClass, 1 };
	if ( !m_pPlayer->GetBag().RemoveItem( vSlot, data, IDCR_PET_USE_ITEM ) )
	{
		return ERR_INVALID_DATA;
	}

	PET_PHASE finalPhase = pPet->ChangePhase( phase );
	pPet->SendPetInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), finalPhase );
	return ERR_OK;
}

int32_t CExtCharPet::onLearnSkill( Answer::NetPacket* inPacket )
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}

	PetId_t		nPetId		= static_cast<PetId_t>( inPacket->readInt64() );
	SkillId_t	nSkillId	= inPacket->readInt32();
	int32_t		nBagSlot	= inPacket->readInt32();
	int8_t		nSkillPos	= inPacket->readInt8();

	++nSkillPos;	// ����˶�һ�����ͨ����
	
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nSkillLevel = 0;
	PetSkillInfo* pSkillInfo = pPet->GetSkillByPos( nSkillPos );
	if ( NULL == pSkillInfo )
	{
		return ERR_INVALID_DATA;
	}

	if ( 0 == pSkillInfo->nId )
	{
		CfgSkill* pCfgSkill = CFG_DATA.getSkill( nSkillId );
		if ( NULL == pCfgSkill )
		{
			return ERR_INVALID_DATA;
		}
	}
	else
	{
		if ( pSkillInfo->nId != nSkillId )
		{
			return ERR_INVALID_DATA;
		}
		nSkillLevel = pSkillInfo->nLevel;
	}

	int32_t nBookId = CFG_DATA.GetSkillLevelUpTable().GetBook( nSkillId, nSkillLevel );
	if ( 0 == nBookId )
	{
		return ERR_INVALID_DATA;
	}

	const MemChrBag& bagItem = m_pPlayer->GetBag().GetSlotData( nBagSlot );
	if ( m_pPlayer->GetBag().IsEmptySlot( bagItem ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( bagItem.itemClass != IC_NORMAL || bagItem.itemId != nBookId )
	{
		return ERR_INVALID_DATA;
	}

	CfgItem* pItem = CFG_DATA.getItem( bagItem.itemId );
	if ( NULL == pItem )
	{
		return ERR_INVALID_DATA;
	}

	if ( pPet->getLevel() < pItem->level )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pPet->LearnSkill( nSkillId, nSkillPos ) )
	{
		return ERR_INVALID_DATA;
	}

	pPet->SendPetInfo();

	Int32Vector vSlot;
	vSlot.push_back( nBagSlot );
	ItemData data;
	data.m_nClass	= IC_NORMAL;
	data.m_nId		= nBookId;
	data.m_nCount	= 1;
	m_pPlayer->GetBag().RemoveItem( vSlot, data, IDCR_MOUNT_LEAR_SKILL );
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nSkillId );
	return ERR_OK;
}

int32_t	CExtCharPet::onLiBaoIllusion( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer)
	{
		return ERR_INVALID_DATA;
	}
	PetId_t nMainPetId	= static_cast<PetId_t>( inPacket->readInt64() );
	int32_t ShopId		= inPacket->readInt32();
	int8_t	nUseItem	= inPacket->readInt8();	
	CObjPet* pMainPet = GetPet( nMainPetId );
	if ( NULL == pMainPet )
	{
		return ERR_INVALID_DATA;
	}
	int32_t Level = CFG_DATA.GetHuanHuaNeedRoleLevel( pMainPet->GetPoints() );
	if ( m_pPlayer->getLevel() < Level )
	{
		return ERR_INVALID_DATA;
	}
	CPet* pPet = pMainPet->GetPet();
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}
	if ( pPet->IsReinLimit() )
	{
		return ERR_INVALID_DATA;
	}
	const CfgPetIllusionGrow* pGrow = CFG_DATA.GetPetIllusionTable().GetGrow( pPet->GetGrowPoints() );
	if ( NULL == pGrow )
	{
		return ERR_INVALID_DATA;
	}
	if ( !CFG_DATA.GetPetIllusionTable().IsRightShopId( pPet->GetGrowPoints(),ShopId ) )
	{
		return ERR_INVALID_DATA;
	}
	int32_t Points = CFG_DATA.GetPetTable().GetBuyPetPoints(ShopId);
	const CfgPetIllusionGrow* pVicePetGrow = CFG_DATA.GetPetIllusionTable().GetGrowViceGrow( Points );
	if (  NULL == pVicePetGrow )
	{
		return ERR_INVALID_DATA;
	}
	int32_t DiffTime = pVicePetGrow->Compensation - pGrow->Compensation + 1;
	if ( DiffTime <= 0  )
	{
		return ERR_INVALID_DATA;
	}
	if ( ERR_OK != m_pPlayer->GetPlayerShangCheng().BuyShopItem( ShopId, 1, false ) )
	{
		return ERR_INVALID_DATA;
	}
	
	ItemData itemData = {};

	switch ( nUseItem )
	{
	case PIIT_NONE:	break;
	case PIIT_LUCKY_GRASS:	itemData.m_nId	= ISI_PET_LUCKY_GRASS;		break;
	case PIIT_GOD_GRASS:	itemData.m_nId	= ISI_PET_GOD_GRASS;		break;
	default:break;
	}
	itemData.m_nClass = IC_NORMAL;
	itemData.m_nCount = 1*DiffTime;

	if ( itemData.m_nId > 0 )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( itemData, IDCR_PET_USE_ITEM ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	for ( int32_t i = 0; i < DiffTime; ++i )
	{
		pMainPet->growAttrIllusionByItem( nUseItem );
	}
	pMainPet->SendPetInfo();
	if ( pMainPet->IsFighting() && pMainPet->GetPetJob() == PET_JOB_FASHI )
	{
		CheckMagMainPet();
	}
	m_pPlayer->recalcAttr();
	m_pPlayer->GetTask().updateTaskCount( TC_PET_ILLUSION );
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_ILLUSION );
	m_pPlayer->GetTask().updateTaskCount( TC_PET_POINTS_COUNT );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_PET_ILLUSION );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_PET_POINTS_COUNT );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
	return ERR_OK;
}

int32_t CExtCharPet::onForgetSkill( Answer::NetPacket* inPacket )
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}

	PetId_t		nPetId		= static_cast<PetId_t>( inPacket->readInt64() );
	SkillId_t	nSkillId	= inPacket->readInt32();

	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pPet->ForgetSkill( nSkillId ) )
	{
		return ERR_INVALID_DATA;
	}

	pPet->SendPetInfo();
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nSkillId );
	return ERR_OK;
}

int32_t CExtCharPet::onIllusion( Answer::NetPacket* inPacket )
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nMainPetId	= static_cast<PetId_t>( inPacket->readInt64() );
	PetId_t nVicePetId	= static_cast<PetId_t>( inPacket->readInt64() );
	int8_t	nType		= inPacket->readInt8();		// �������Իû����ɳ��ʻû�������ֵ�û�
	int8_t	nUseItem	= inPacket->readInt8();		// �ɳ��ʻû���0 ��ʹ�õ��� 1 ���˲� 2 ���ɲ�

	CObjPet* pMainPet = GetPet( nMainPetId );
	CObjPet* pVicePet = GetPet( nVicePetId );
	if ( NULL == pMainPet || NULL == pVicePet || pMainPet == pVicePet )
	{
		return ERR_INVALID_DATA;
	}
	
	// ������
	if ( !pVicePet->IsRest() || pVicePet->GetKnight() != PK_NONE || pVicePet->IsRegInFamily() || IsTopPet( pVicePet ) || pVicePet->GetQiShi() != 0 )
	{
		return ERR_SYETEM_ERR;
	}

	// ��⸱����û�����
	if ( !pMainPet->CanIllusion( pVicePet, nType ) )
	{
		return ERR_INVALID_DATA;
	}
	int32_t Level = CFG_DATA.GetHuanHuaNeedRoleLevel( pMainPet->GetPoints() );
	if ( m_pPlayer->getLevel() < Level )
	{
		return ERR_INVALID_DATA;
	}
	const CfgPetIllusionGrow* pMainPetGrow = CFG_DATA.GetPetIllusionTable().GetGrow( pMainPet->GetGrowPoints() );
	const CfgPetIllusionGrow* pVicePetGrow = CFG_DATA.GetPetIllusionTable().GetGrowViceGrow( pVicePet->GetPoints() );
	if ( NULL == pMainPetGrow || NULL == pVicePetGrow )
	{
		return ERR_INVALID_DATA;
	}
	int32_t DiffTime = pVicePetGrow->Compensation - pMainPetGrow->Compensation + 1;
	if ( DiffTime <= 0  )
	{
		return ERR_INVALID_DATA;
	}
	// ������
	ItemData itemData = {};
	if ( nType == PHT_GROW_ATTR )
	{
		switch ( nUseItem )
		{
		case PIIT_NONE:	break;
		case PIIT_LUCKY_GRASS:	itemData.m_nId	= ISI_PET_LUCKY_GRASS;		break;
		case PIIT_GOD_GRASS:	itemData.m_nId	= ISI_PET_GOD_GRASS;		break;
		default:break;
		}
		itemData.m_nClass = IC_NORMAL;
		itemData.m_nCount = 1*DiffTime;
	}
	if ( itemData.m_nId > 0 )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( itemData, IDCR_PET_USE_ITEM ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	for ( int32_t i = 0; i < DiffTime; i++ )
	{
		pMainPet->Illusion( pVicePet, nType, nUseItem );
	}
	pMainPet->SendPetInfo();
	RemovePet( pVicePet );
	if ( pMainPet->IsFighting() && pMainPet->GetPetJob() == PET_JOB_FASHI )
	{
		CheckMagMainPet();
	}
	m_pPlayer->recalcAttr();
	m_pPlayer->GetTask().updateTaskCount( TC_PET_ILLUSION );
	m_pPlayer->GetPlayerHuoYueDu().AddHuoYueDuRecord( HYDT_ILLUSION );
	m_pPlayer->GetTask().updateTaskCount( TC_PET_POINTS_COUNT );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_PET_ILLUSION );
	m_pPlayer->GetAchievemnet().AddAchievement( AT_PET_POINTS_COUNT );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nVicePetId );
	return ERR_OK;
}

int32_t CExtCharPet::onUseLuckyItem( Answer::NetPacket* inPacket )
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId	= static_cast<PetId_t>( inPacket->readInt64() );
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	// ������
	const CfgPetLuckyItem*	pCfgLucky = CFG_DATA.GetCharPetTable().GetPetLuckyItem( pPet->GetLucky() );
	if ( NULL == pCfgLucky )
	{
		return ERR_INVALID_DATA;
	}

	ItemData itemData = {};
	itemData.m_nClass	= pCfgLucky->nClass;
	itemData.m_nId		= pCfgLucky->nId;
	itemData.m_nCount	= pCfgLucky->nCount;

	if ( itemData.m_nId > 0 )
	{
		if ( !m_pPlayer->GetBag().RemoveItem( vSlot, itemData, IDCR_PET_USE_ITEM ) )
		{
			return ERR_INVALID_DATA;
		}
	}

	if ( pCfgLucky->nRate < RANDOM.generate( 0, 10000 ) )
	{
		GAME_SERVICE.replyfailure( m_pPlayer->getGateIndex(), inPacket->getProc(), ERR_PET_USE_LUCKY_ITEM_FAIL, nPetId );
		return ERR_INVALID_DATA;
	}

	if ( !pPet->UseLuckyItem() )
	{
		return ERR_INVALID_DATA;
	}

	pPet->SendPetInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nPetId );
	return ERR_OK;
}

int32_t	CExtCharPet::onDeport( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	int8_t	nBagType = inPacket->readInt8();
	if ( nBagType != PBT_BAG && nBagType != PBT_DEPORT )
	{
		return ERR_INVALID_DATA;
	}
	int32_t MaxSize = vPetBagSize[nBagType];
	if ( nBagType == PBT_DEPORT )
	{
		int32_t AddCount = m_pPlayer->GetPlayerVip().GetAddPetDeportCount();
		MaxSize += AddCount;
	}
	if ( m_vPetBagSize[nBagType] >= MaxSize )
	{
		return ERR_INVALID_DATA;
	}

	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( NULL == pPet )
		{
			continue;
		}
		if ( pPet->GetPetId() == nPetId )
		{
			if ( pPet->GetBagType() == nBagType )
			{
				return ERR_INVALID_DATA;
			}
			if ( pPet->IsFighting() )
			{
				removeFightPet( pPet );
				pPet->LeaveMap();
				pPet->Rest();
				m_pPlayer->recalcAttr();
			}
			else if ( pPet->IsZoarium() )
			{
				removeFightPet( pPet );
				pPet->Rest();
				m_pPlayer->recalcAttr();
			}
			else if ( pPet->IsRide() )
			{
				ridePet( NULL );
			}

			--m_vPetBagSize[pPet->GetBagType()];
			++m_vPetBagSize[nBagType];
			pPet->SetBagType( nBagType );
			pPet->SendPetInfo( false );
			break;
		}
	}
	return ERR_OK;
}

int32_t CExtCharPet::UnSetKnightBuyJueWei()
{
	for ( int8_t i = 0; i < PET_KNIGHT_SIZE; ++i )
	{
		CObjPet* pPet = m_vPetKnight[i];
		if ( NULL == pPet )
		{
			continue;
		}

		const CfgPetKnight* pCfgKnight = CFG_DATA.GetPetKnightTable().GetKnight( i );
		if ( NULL == pCfgKnight )
		{
			continue;
		}
		if ( m_pPlayer->GetPlayerJueWei().GetJueWei() > pCfgKnight->nTitle )
		{
			if ( pCfgKnight->nEffectType == PKE_ADD_MAX_HP )
			{
				int32_t nAddValue = m_vKnightAddValue[i];
				if ( nAddValue > 0 )
				{
					m_pPlayer->AddBuffAttrRatio( CObjAttrs::ATTR_HP, -1*nAddValue );
					AddKnightPetHp( -1*nAddValue );
					m_vKnightAddValue[i] = 0;
				}
			}
			pPet->SetKnight( PK_NONE );
			pPet->SendPetInfo( false );
			m_vPetKnight[i] = NULL;
		}
	}
	return ERR_OK;
}

int32_t CExtCharPet::onSetKnight( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	nKnight = inPacket->readInt8();
	PetId_t nPetId	= static_cast<PetId_t>( inPacket->readInt64() );
	if ( nKnight <= PK_NONE || nKnight >= PET_KNIGHT_SIZE )
	{
		return ERR_INVALID_DATA;
	}

	const CfgPetKnight* pCfgKnight = CFG_DATA.GetPetKnightTable().GetKnight( nKnight );
	if ( NULL == pCfgKnight )
	{
		return ERR_INVALID_DATA;
	}

// 	bool bNeedCal = false;
// 	if ( pCfgKnight->IsNeedCal() )
// 	{
// 		bNeedCal = true;
// 	}
	CObjPet* pPet = GetPet( nPetId );
	if ( pPet != NULL )
	{
		if (  pPet->GetPet() == NULL || pPet->GetPet()->IsXOType() )
		{
			return ERR_INVALID_DATA;
		}
		if ( m_pPlayer->getLevel() < pCfgKnight->nLevel )
		{
			return ERR_INVALID_DATA;
		}
		if ( m_pPlayer->GetPlayerJueWei().GetJueWei() > pCfgKnight->nTitle )
		{
			return ERR_INVALID_DATA;
		}
		if ( pPet->GetPoints() < pCfgKnight->vQuality[0] )
		{
			return ERR_INVALID_DATA;
		}

		if ( !pCfgKnight->IsInCompList( pPet->GetBaseId() ) )
		{
			return ERR_INVALID_DATA;
		}

		int8_t nPetKnight = pPet->GetKnight();
		if ( nPetKnight == nKnight )
		{
			return ERR_INVALID_DATA;
		}
		if ( nPetKnight > PK_NONE && nPetKnight < PET_KNIGHT_SIZE )
		{
			m_vPetKnight[nPetKnight] = NULL;
		}
	}

	if ( pCfgKnight->nEffectType == PKE_ADD_MAX_HP )
	{
		int32_t nAddValue = m_vKnightAddValue[nKnight];
		if ( nAddValue > 0 )
		{
			m_pPlayer->AddBuffAttrRatio( CObjAttrs::ATTR_HP, -1*nAddValue );
			AddKnightPetHp( -1*nAddValue );
			m_vKnightAddValue[nKnight] = 0;
		}
	}

	CObjPet* pOldPet = m_vPetKnight[nKnight];
	if ( pOldPet != NULL )
	{
		pOldPet->SetKnight( PK_NONE );
		pOldPet->SendPetInfo( false );
	}

	if ( pPet != NULL )
	{
		pPet->SetKnight( nKnight );
		pPet->SendPetInfo( false );
		if ( pCfgKnight->nEffectType == PKE_ADD_MAX_HP )
		{
			int32_t nEffectValue = pCfgKnight->GetEffectValue( pPet->GetPoints() );
			m_vKnightAddValue[nKnight] = m_pPlayer->AddBuffAttrRatio( CObjAttrs::ATTR_HP, nEffectValue );
			AddKnightPetHp( nEffectValue );
		}
	}
	m_vPetKnight[nKnight] = pPet;

// 	if ( bNeedCal )
// 	{
		m_pPlayer->recalcAttr();
//	}
	RecalPetsAttr();
	m_pPlayer->GetAchievemnet().AddAchievement( AT_PET_KNIGHT );
	return ERR_OK;
}

int32_t CExtCharPet::onWearQiShi( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	Pos = inPacket->readInt8();
	PetId_t nPetId	= static_cast<PetId_t>( inPacket->readInt64() );
	if ( Pos <= 0 || Pos > QI_SHI_COUNT )
	{
		return ERR_INVALID_DATA;
	}
	CfgQiShi* pQiShi = CFG_DATA.GetQiShiCfg( Pos );
	if ( NULL == pQiShi )
	{
		return ERR_SYETEM_ERR;
	}
	CObjPet* pPet = GetPet( nPetId );
	if ( pPet != NULL )
	{
		if (  pPet->GetPet() == NULL || pPet->GetPet()->IsXOType() )
		{
			return ERR_INVALID_DATA;
		}
		if ( pPet->GetPoints() < pQiShi->vQuality[0] )
		{
			return ERR_INVALID_DATA;
		}

		int8_t QiShiPos = pPet->GetQiShi();
		if ( Pos == QiShiPos )
		{
			return ERR_INVALID_DATA;
		}
		if ( QiShiPos <= 0 && QiShiPos > QI_SHI_COUNT )
		{
			m_vPetWearQiShi[QiShiPos -1] = NULL;
		}
	}

	CObjPet* pOldPet = m_vPetWearQiShi[Pos - 1];
	if ( pOldPet != NULL )
	{
		pOldPet->SetQiShi( 0 );
		pOldPet->SendPetInfo( false );
	}

	if ( pPet != NULL )
	{
		pPet->SetQiShi( Pos );
		pPet->SendPetInfo( false );
	}
	m_vPetWearQiShi[Pos -1] = pPet;
	m_pPlayer->recalcAttr();
	return ERR_OK;
}

int32_t CExtCharPet::onMoveToBag( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId	= static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	// û��ս ���� û��������ʿ û���ھ��ŵǼ� û���������
	if ( !pPet->IsRest() || !pPet->AliveFlag() || pPet->GetKnight() != PK_NONE || pPet->IsRegInFamily() || pPet->GetQiShi() != 0 )
	{
		return ERR_INVALID_DATA;
	}
	
	if ( m_pPlayer->GetBag().GetbagFreeSize() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	// ��Ǯ
	const PetPackageCost* pCost = CFG_DATA.GetPetTable().GetPackageCost( pPet->GetPoints() );
	if ( NULL == pCost )
	{
		return ERR_INVALID_DATA;
	}
	int32_t nType	= 0;
	int32_t nCost   = 0;
	if ( pPet->GetPet()->IsXOType() )
	{
		nType	= pCost->nXoCostType;
		nCost	= pCost->nXoCostValue;
	}
	else
	{
		nType = pCost->nCostType;
		nCost = pCost->nCostValue;
	}

	if ( nType == 1 )
	{
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( nCost, MCR_PET_TO_BAG ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	else if ( nType == 2 )
	{
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, nCost, GCR_PET_TO_BAG ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	else if ( nType == 3 )
	{
		if ( !m_pPlayer->DecGoldAndCash( nCost, GCR_PET_TO_BAG ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	else
	{
		return ERR_INVALID_DATA;
	}

	MemChrBag item = {};
	item.itemClass	= IC_PET;
	item.itemId		= pPet->GetBaseId();
	item.itemCount	= 1;
	item.srcId		= pPet->GetPetId();
	if ( !m_pPlayer->GetBag().AddItem( item, IACR_FROM_PET ) )
	{
		return ERR_INVALID_DATA;
	}

	RemovePet( pPet, false );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), nPetId );
	return true;
}

int32_t CExtCharPet::onGetFromBag( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}

	int32_t	nSlot = inPacket->readInt32();
	MemChrBag item = m_pPlayer->GetBag().GetSlotData( nSlot );
	if ( item.itemClass != IC_PET )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_vPetBagSize[PBT_BAG] >= PET_BAG_SIZE )
	{
		return ERR_INVALID_DATA;
	}

	CPet* pPet = PET_MANAGER.GetPet( static_cast<PetId_t>( item.srcId ) );
	if ( NULL == pPet || pPet->GetBaseId() != item.itemId )
	{
		return ERR_INVALID_DATA;
	}

	CObjPet* pObjPet = POOL_MANAGER.pop<CObjPet>();
	if ( NULL == pObjPet )
	{
		return ERR_INVALID_DATA;
	}

	pObjPet->Init( pPet, m_pPlayer );
	GAME_SERVICE.addPet( pObjPet );
	addPet( pObjPet, PBT_BAG );
	pObjPet->SendPetInfo( false );

	MemChrBag emptySlot = {};
	m_pPlayer->GetBag().SetSlotData( nSlot, emptySlot, IDCR_TO_PET );
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc(), pPet->GetPetId() );
	return ERR_OK;
}

void CExtCharPet::AddTarget( const UnitHandle& target )
{
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( pPet != NULL )
		{
			pPet->AddTarget( target );
		}
	}
}

int32_t CExtCharPet::GetAliveFightPetCount()
{
	int32_t Count = 0;
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( pPet != NULL )
		{
			if ( pPet->isAlive() )
			{
				Count++;
			}
		}
	}
	return Count;
}

void CExtCharPet::DivideHurt( int32_t Damage )
{
	if ( Damage <= 0 )
	{
		return;
	}
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( pPet != NULL )
		{
			if ( pPet->isAlive() )
			{
				pPet->AddHP( -1 * Damage );
				if ( !pPet->isAlive() )
				{
					pPet->onDie();
				}
			}
		}
	}
}

void CExtCharPet::RemoveTarget( const UnitHandle& target )
{
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( pPet != NULL )
		{
			pPet->RemoveTarget( target );
		}
	}
}

void CExtCharPet::SetTargetTile( int32_t tx, int32_t ty, Direction dir )
{
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		if ( m_vFightPet[i] != NULL )
		{
			m_vFightPet[i]->ResetTargetTile( tx, ty, dir );
		}
	}
}

CObjPet* CExtCharPet::GetFightPet()
{
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		if ( m_vFightPet[i] != NULL )
		{
			if ( m_vFightPet[i]->AliveFlag() )
			{
				return m_vFightPet[i];
			}
		}
	}
	return NULL;
}

CObjPet* CExtCharPet::GetFightPet( int32_t Index )
{
	if ( Index >= PSP_SIZE || Index < 0 )
	{
		return NULL;
	}
	return m_vFightPet[Index];
}

void CExtCharPet::GetFightPet( UnitList& outUnits )
{
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		if ( m_vFightPet[i] != NULL )
		{
			outUnits.push_back( m_vFightPet[i] );
		}
	}
}

CObjPet* CExtCharPet::GetZoariumPet()
{
	CObjPet* pRet = NULL;
	int32_t nMaxDef = -1;
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( NULL == pPet )
		{
			continue;
		}

		if ( pPet->AliveFlag() && pPet->IsZoarium() )
		{
			int32_t nDef = pPet->GetDefValue();
			if ( nDef > nMaxDef )
			{
				nMaxDef = nDef;
				pRet = pPet;
			}
		}
	}

	return pRet;
}

void CExtCharPet::ZoariumPetDame( int32_t Dame, UnitHandle launcher )
{
	if ( Dame <= 0 || NULL == m_pPlayer )
	{
		return;
	}
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( NULL == pPet )
		{
			continue;
		}
		if ( pPet->AliveFlag() && pPet->IsZoarium() )
		{
			int32_t AddHp = 0;
			if ( Dame - pPet->GetHP() > 0 )
			{
				AddHp = pPet->GetHP();
				pPet->AddHP(-1*AddHp);
				Dame -= AddHp;
			}
			else
			{
				AddHp = -1 * Dame;
				pPet->AddHP( -1 * Dame );
				Dame = 0;
			}
			//pPet->AddHP( -1 * AddHp );
			pPet->postDamage( -1 * AddHp, launcher );
		}
		if ( Dame <= 0 )
		{
			break;
		}
	}
	if ( Dame > 0 )
	{
		m_pPlayer->AddHP( -1 * Dame );
		m_pPlayer->postDamage( -1 * Dame, launcher );
	}
}

void CExtCharPet::AddZoariumPetAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( NULL == pPet )
		{
			continue;
		}

		if ( pPet->AliveFlag() && pPet->IsZoarium() )
		{
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_HP,			pPet->GetAttrValue( CObjAttrs::ATTR_HP ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_PHY_ATK_MIN,	pPet->GetAttrValue( CObjAttrs::ATTR_PHY_ATK_MIN ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_PHY_ATK_MAX,	pPet->GetAttrValue( CObjAttrs::ATTR_PHY_ATK_MAX ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_MAG_ATK_MIN,	pPet->GetAttrValue( CObjAttrs::ATTR_MAG_ATK_MIN ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_MAG_ATK_MAX,	pPet->GetAttrValue( CObjAttrs::ATTR_MAG_ATK_MAX ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_PHY_DEF,		pPet->GetAttrValue( CObjAttrs::ATTR_PHY_DEF ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_MAG_DEF,		pPet->GetAttrValue( CObjAttrs::ATTR_MAG_DEF ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_HITRATE,		pPet->GetAttrValue( CObjAttrs::ATTR_HITRATE ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_DODGE,			pPet->GetAttrValue( CObjAttrs::ATTR_DODGE ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_CRITRATE,		pPet->GetAttrValue( CObjAttrs::ATTR_CRITRATE ) / 10 );
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_TENACITY,		pPet->GetAttrValue( CObjAttrs::ATTR_TENACITY ) / 10 );
		}
	}
}

void CExtCharPet::OnZoariumPetDie()
{
	if ( m_pPlayer != NULL )
	{
		m_pPlayer->recalcAttr();
	}
}

int32_t CExtCharPet::GetKnightExpRatio()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	int32_t nSum = 0;
	for ( int8_t i = 0; i < PET_KNIGHT_SIZE; ++i )
	{
		CObjPet* pPet = m_vPetKnight[i];
		if ( NULL == pPet )
		{
			continue;
		}

		const CfgPetKnight* pCfgKnight = CFG_DATA.GetPetKnightTable().GetKnight( i );
		if ( NULL == pCfgKnight )
		{
			continue;
		}
		int32_t nEffectValue = pCfgKnight->GetEffectValue( pPet->GetPoints() );
		if ( nEffectValue <= 0 )
		{
			continue;
		}
		if ( pCfgKnight->nEffectType == PKE_ADD_EXP )
		{
			nSum += nEffectValue;
		}
	}
	return nSum;
}

void CExtCharPet::AddKnightPetAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int8_t i = 0; i < PET_KNIGHT_SIZE; ++i )
	{
		CObjPet* pPet = m_vPetKnight[i];
		if ( NULL == pPet )
		{
			continue;
		}

		const CfgPetKnight* pCfgKnight = CFG_DATA.GetPetKnightTable().GetKnight( i );
		if ( NULL == pCfgKnight )
		{
			continue;
		}
		int32_t nEffectValue = pCfgKnight->GetEffectValue( pPet->GetPoints() );
		if ( nEffectValue <= 0 )
		{
			continue;
		}
		switch( pCfgKnight->nEffectType )
		{
		//case PKE_ADD_BATTLE:		m_pPlayer->AddAttrValue( CObjAttrs::ATTR_BATTLE, nEffectValue );			break;
		case PKE_REMINE_DAMAGE:		m_pPlayer->AddAttrValue( CObjAttrs::ATTR_DMG_RDC_PEC, nEffectValue );		break;
		case PKE_ADD_DAMAGE:		m_pPlayer->AddAttrValue( CObjAttrs::ATTR_DMG_ADD_PEC, nEffectValue );		break;
		default: break;
		}
	}
}

void CExtCharPet::AddQiShiAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int8_t i = 0; i < QI_SHI_COUNT; ++i )
	{
		CObjPet* pPet = m_vPetWearQiShi[i];
		if ( NULL == pPet )
		{
			continue;
		}
		AddAttrList AttrList = CFG_DATA.GetQiShiAttr( i+1, pPet->GetPoints() );
		AddAttrList::iterator it = AttrList.begin();
		for ( ; it != AttrList.end(); ++it )
		{
			m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>(it->m_nAddAttrType), it->m_nAddAttrValue );
		}
	}
}

int32_t CExtCharPet::GetQiShiCount()
{
	int32_t Count = 0;
	for ( int8_t i = 0; i < QI_SHI_COUNT; ++i )
	{
		CObjPet* pPet = m_vPetWearQiShi[i];
		if ( NULL == pPet )
		{
			continue;
		}
		Count++;
	}
	return Count;
}

int32_t CExtCharPet::GetQiShiAddBattle()
{
	int32_t Battle = 0;
	for ( int8_t i = 0; i < QI_SHI_COUNT; ++i )
	{
		CObjPet* pPet = m_vPetWearQiShi[i];
		if ( NULL == pPet )
		{
			continue;
		}
		CfgQiShi* pCfg = CFG_DATA.GetQiShiCfg( i+1 );
		if ( NULL != pCfg )
		{
			Battle += pCfg->AddBattle;
		}
	}
	return Battle;
}

void CExtCharPet::AddKnightPetAttrToPet( CObjPet *TarPet )
{
	if ( NULL == m_pPlayer || NULL == TarPet )
	{
		return;
	}
	for ( int8_t i = 0; i < PET_KNIGHT_SIZE; ++i )
	{
		CObjPet* pPet = m_vPetKnight[i];
		if ( NULL == pPet )
		{
			continue;
		}

		const CfgPetKnight* pCfgKnight = CFG_DATA.GetPetKnightTable().GetKnight( i );
		if ( NULL == pCfgKnight )
		{
			continue;
		}
		int32_t nEffectValue = pCfgKnight->GetEffectValue( pPet->GetPoints() );
		if ( nEffectValue <= 0 )
		{
			continue;
		}
		switch( pCfgKnight->nEffectType )
		{
			//case PKE_ADD_BATTLE:		m_pPlayer->AddAttrValue( CObjAttrs::ATTR_BATTLE, nEffectValue );			break;
		case PKE_REMINE_DAMAGE:		TarPet->AddAttrValue( CObjAttrs::ATTR_DMG_RDC_PEC, nEffectValue );		break;
		case PKE_ADD_DAMAGE:		TarPet->AddAttrValue( CObjAttrs::ATTR_DMG_ADD_PEC, nEffectValue );		break;
		default: break;
		}
	}
}

void CExtCharPet::AddMoveSpeed()
{
	if ( m_pRidePet != NULL )
	{
		int32_t Star = m_pRidePet->GetPoints() / 100;
		float   Rate = 0.0f;
		int32_t BaseSpeed	= m_pPlayer->GetAttrValue( CObjAttrs::ATTR_MOVE_SPEED );
		if ( Star >= 100 )
		{
			Rate = 0.6f;
		}
		else
		{
			Rate = 0.3f;
		}
		int32_t	AddSpeed = static_cast<int32_t>( BaseSpeed * Rate ) ; 
		if ( AddSpeed > 0 )
		{
			m_pPlayer->AddAttrValue( CObjAttrs::ATTR_MOVE_SPEED, AddSpeed );
		}
	}
}

int32_t CExtCharPet::GetKnightEffectValue( int8_t Knight )
{
	if ( Knight < 0 || Knight >= PET_KNIGHT_SIZE )
	{
		return 0;
	}
	CObjPet* pPet = m_vPetKnight[Knight];
	if ( NULL == pPet )
	{
		return 0;
	}

	const CfgPetKnight* pCfgKnight = CFG_DATA.GetPetKnightTable().GetKnight( Knight );
	if ( NULL == pCfgKnight )
	{
		return 0;
	}
	int32_t nEffectValue = pCfgKnight->GetEffectValue( pPet->GetPoints() );
	if ( nEffectValue <= 0 )
	{
		return 0;
	}
	return nEffectValue;
}

void CExtCharPet::FreeAllFightPet( bool AotoFight )
{
	bool NeedSny = false;
	for( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( pPet != NULL )
		{
			pPet->Rest();
			pPet->LeaveMap();
			pPet->SendPetInfo( false );
			--m_nFightingCount;
			m_vFightPet[i] = NULL;
			if ( AotoFight )
			{
				m_vLastFightPet[i] = pPet;
			}
			NeedSny = true;
		}
	}
	if ( NULL != m_pPlayer && NeedSny )
	{
		m_pPlayer->recalcAttr();
	}
}

void CExtCharPet::FightLastFightPet()
{
	for( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vLastFightPet[i];
		if ( pPet != NULL )
		{
			Fighting( pPet );
			m_vLastFightPet[i] = NULL;
		}
	}
}

void CExtCharPet::SendPetInfoList()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	//TODO:���·�PetList;���·�ObjPetList;
	PetList pList;
	PET_MANAGER.GetPlayerPetList( m_pPlayer->getCid(), pList );
	sendPetInfo( pList );

	sendPetList();
}

void CExtCharPet::getEggPet( PetList& pList, int8_t nBag )
{
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return;
	}

	int32_t nSize = getEggBagSize( nBag );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		const PetEgg& egg = pEggPool[i];
		if ( egg.IsEmpty() )
		{
			continue;
		}
		if ( egg.GetState() != PES_CAN_OPEN )
		{
			continue;
		}
		CPet* pPet = PET_MANAGER.GetPet( egg.GetPetId() );
		if ( NULL == pPet )
		{
			continue;
		}
		pList.push_back( pPet );
	}
}

int32_t CExtCharPet::GetRidePet() const
{
	if ( m_pRidePet != NULL )
	{
		return m_pRidePet->GetBaseId();
	}
	return 0;
}

int32_t CExtCharPet::GetRidePetPoints() const
{
	if ( m_pRidePet != NULL )
	{
		return m_pRidePet->GetPoints();
	}
	return 0;
}

void CExtCharPet::SendPetEggPoolInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_EGG_INFO );
	if (NULL == packet)
	{
		return;
	}
	int32_t	nCount = 0;
	packet->writeInt32( nCount );

//	appendEggInfo( packet, nCount, PEBT_BAG );
	appendEggInfo( packet, nCount, PEBT_HATCH_POOL );
//	appendEggInfo( packet, nCount, PEBT_MUTI_HATCH_POOL );

	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt8( nCount );
	packet->setWOffset( endOffSet );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CExtCharPet::appendEggInfo( NetPacket* packet, int32_t& nCount, int8_t nBag )
{
	if ( NULL == packet )
	{
		return;
	}

	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return;
	}

	int32_t nSize = getEggBagSize( nBag );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		if ( pEggPool[i].IsEmpty() )
		{
			continue;
		}
		pEggPool[i].AppendInfo( packet );
		++nCount;
	}
}

void CExtCharPet::sendPetEggInfo( const PetEgg& egg )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_EGG_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( 1 );
	egg.AppendInfo( packet );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CExtCharPet::addPetEggDirty( PetEgg* pEgg )
{
	PetEggList::iterator iter = m_nEggDirtyList.begin();
	PetEggList::iterator eiter = m_nEggDirtyList.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( ( *iter ) == pEgg )
		{
			return;
		}
	}

	m_nEggDirtyList.push_back( pEgg );
}

void CExtCharPet::ForceSendDirty()
{
	if ( m_nEggDirtyList.empty() )
	{
		return;
	}
	sendPetEggDirty();
	m_nEggDirtyList.clear();
}

void CExtCharPet::checkPetEggDirty()
{
	if ( m_nEggDirtyList.empty() )
	{
		return;
	}
	sendPetEggDirty();
	m_nEggDirtyList.clear();
}

void CExtCharPet::sendPetEggDirty()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_EGG_INFO );
	if (NULL == packet)
	{
		return;
	}

	int32_t nCount = 0;

	packet->writeInt32( nCount );
	PetEggList::iterator iter = m_nEggDirtyList.begin();
	PetEggList::iterator eiter = m_nEggDirtyList.end();
	for ( ; iter != eiter; ++iter )
	{
		PetEgg* pEgg = *iter;
		if ( pEgg != NULL )
		{
			pEgg->AppendInfo( packet );
			++nCount;
		}
	}

	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt32( nCount );
	packet->setWOffset( endOffSet );

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

CObjPet* CExtCharPet::GetPet( PetId_t nPetId )
{
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( NULL == pPet )
		{
			continue;
		}
		if ( pPet->GetPetId() == nPetId )
		{
			return pPet;
		}
	}
	return NULL;
}

bool CExtCharPet::addPet( CObjPet* pPet, int8_t nBagType )
{
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		if ( NULL == m_vAllPet[i] )
		{
			pPet->AddBuffAttrRatio( CObjAttrs::ATTR_HP, m_vKnightAddValue[PK_SHENGGUANG] );
			pPet->SetBagType( nBagType );
			m_vAllPet[i] = pPet;
			++m_vPetBagSize[nBagType];
			m_pPlayer->GetTask().updateTaskCount( TC_PET_POINTS_COUNT );
			m_pPlayer->GetAchievemnet().AddAchievement( AT_PET_POINTS_COUNT );
			return true;
		}
	}
	return false;
}

bool CExtCharPet::RemovePet( CObjPet* pPet, bool bDel )
{
	if ( NULL == pPet )
	{
		return false;
	}

	bool bSuccess = false;
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		if ( m_vAllPet[i] == pPet )
		{
			m_vAllPet[i] = NULL;
			--m_vPetBagSize[pPet->GetBagType()];
			bSuccess = true;
			break;
		}
	}

	if ( bDel )
	{
		PET_MANAGER.DelPet( pPet->GetPet() );
	}
	GAME_SERVICE.removePet( pPet );
	POOL_MANAGER.push<CObjPet>( pPet );
	m_pPlayer->GetTask().updateTaskCount( TC_PET_POINTS_COUNT );
	return bSuccess;
}

PetEgg* CExtCharPet::getEgg( int8_t nBag, int32_t nSlot )
{
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return NULL;
	}

	int32_t nSize = getEggBagSize( nBag );
	if ( nSlot < 0 || nSlot >= nSize )
	{
		return NULL;
	}

	return &( pEggPool[nSlot] );
}

int32_t CExtCharPet::addEgg( int8_t nBag, const PetEgg& egg )
{
	int32_t nIndex = -1;
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return nIndex;
	}

	int32_t nSize = getEggBagSize( nBag );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		if ( pEggPool[i].IsEmpty() )
		{
			nIndex = i;
			pEggPool[nIndex].Set( egg );
			addPetEggDirty( &pEggPool[nIndex] );
			break;
		}
	}

	return nIndex;
}

int32_t CExtCharPet::GetFreePetFenceCount()
{
	return PET_BAG_SIZE - m_vPetBagSize[PBT_BAG];
}

int32_t CExtCharPet::GetBagFreeCount( int8_t nBag )
{
	int32_t BagFreeCount = 0;
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return BagFreeCount;
	}
	int32_t nSize = getEggBagSize( nBag );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		if ( pEggPool[i].IsEmpty() )
		{
			BagFreeCount++;
		}
	}
	return BagFreeCount;
}

void CExtCharPet::AddEggs( std::list<int32_t> EggIdList  )
{
	std::list<int32_t>::iterator it = EggIdList.begin();
	for ( ; it != EggIdList.end(); ++it )
	{
		if ( !AddHatchBag(*it) )
		{
			//AddEgg( *it );
		}
	}
}

PetEgg* CExtCharPet::GetEgg( int32_t nSlot )
{
	return getEgg( PEBT_HATCH_POOL, nSlot );
}

bool CExtCharPet::RemoveEgg( int32_t nSlot )
{
	return removeEgg( PEBT_HATCH_POOL, nSlot );
}

bool CExtCharPet::RemoveEgg( const Int32List& slotList )
{
	return removeEgg( PEBT_HATCH_POOL, slotList );
}

bool CExtCharPet::removeEgg( int8_t nBag, int32_t nSlot )
{
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return false;
	}

	int32_t nSize = getEggBagSize( nBag );

	if ( nSlot < 0 || nSlot >= nSize )
	{
		return false;
	}

	pEggPool[nSlot].CleanUp();
	addPetEggDirty( &pEggPool[nSlot] );
	//cleanEmptyEggPos( pEggPool, nPoolSize );
	return true;
}

bool CExtCharPet::removeEgg( int8_t nBag, const Int32List& slotList )
{
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return false;
	}

	int32_t nSize = getEggBagSize( nBag );

	Int32List::const_iterator iter = slotList.begin();
	Int32List::const_iterator eiter = slotList.end();
	for ( ; iter != eiter; ++iter )
	{
		int32_t nIndex = *iter;
		if ( nIndex < 0 || nIndex >= nSize )
		{
			return false;
		}

		if ( pEggPool[nIndex].GetPetId() > 0 )
		{
			CPet* pPet = PET_MANAGER.GetPet( pEggPool[nIndex].GetPetId() );
			if ( pPet != NULL )
			{
				PET_MANAGER.DelPet( pPet );
			}
		}
		pEggPool[nIndex].CleanUp();
		addPetEggDirty( &pEggPool[nIndex] );
	}

	//cleanEmptyEggPos( pEggPool, nPoolSize );
	return true;
}

bool CExtCharPet::getEggList( int8_t nBag, const Int32List& inList, PetEggList& outList )
{
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return false;
	}

	int32_t nSize = getEggBagSize( nBag );

	Int32List::const_iterator iter = inList.begin();
	Int32List::const_iterator eiter = inList.end();
	for ( ; iter != eiter; ++iter )
	{
		int32_t nIndex = *iter;
		if ( nIndex < 0 || nIndex >= nSize || pEggPool[nIndex].IsEmpty() )
		{
			return false;
		}

		outList.push_back( &( pEggPool[nIndex] ) );
	}
	return true;
}

int32_t CExtCharPet::getEmptyEggPos( int32_t nBag ) const
{
	const PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return 0;
	}

	int32_t nSize = getEggBagSize( nBag );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		if ( pEggPool[i].IsEmpty() )
		{
			return nSize - i;
		}
	}

	return 0;
}

//void CExtCharPet::cleanEmptyEggPos( int8_t nBagType )
//{
//	if ( NULL == pEggPool )
//	{
//		return;
//	}
//	PetEgg* pEggPool = getEggBagPool( nBagType );
//	if ( NULL == pEggPool )
//	{
//		return;
//	}
//
//	int32_t nSize = getEggBagSize( nBagType );
//	int32_t nFirstEmptyPos = 0;
//	for ( int32_t i = 0; i < nSize; ++i )
//	{
//		if ( pEggPool[i].IsEmpty() )
//		{
//			if ( 0 == nFirstEmptyPos )
//			{
//				nFirstEmptyPos = i;
//			}
//		}
//		else
//		{
//			if ( nFirstEmptyPos != 0 )
//			{
//				pEggPool[nFirstEmptyPos] = pEggPool[i];
//				pEggPool[i].CleanUp();
//				++nFirstEmptyPos;
//			}
//		}
//	}
//}

bool CExtCharPet::AddEgg( int32_t nEggId )
{
	PetEgg egg;
	egg.Init( nEggId );
	return addEgg( PEBT_BAG, egg ) != -1;
}

void CExtCharPet::OnAddExp( int64_t nExp, bool bFighting )
{
	if ( bFighting )
	{
		addExpToFightPet( nExp );
	}
	else
	{
		addExpToAllPet( nExp );
	}
}

void CExtCharPet::addExpToFightPet( int64_t nAddVal )
{
	for ( int32_t i = 0; i < PSP_SIZE ; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( NULL == pPet )
		{
			continue;
		}

		if ( !pPet->AliveFlag() )
		{
			continue;
		}

		pPet->AddExp( nAddVal );
	}
}

void CExtCharPet::addExpToAllPet( int64_t nAddVal )
{
	for ( int32_t i = 0; i < PET_LIST_SIZE ; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( NULL == pPet )
		{
			continue;
		}

		if ( !pPet->AliveFlag() )
		{
			continue;
		}

		if ( pPet->GetBagType() != PBT_BAG )
		{
			continue;
		}
		pPet->AddExp( nAddVal );
	}
}

void CExtCharPet::AddKnightPetHp( int32_t AddValues )
{
	for ( int32_t i = 0; i < PET_LIST_SIZE ; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( NULL == pPet )
		{
			continue;
		}
		pPet->AddBuffAttrRatio( CObjAttrs::ATTR_HP, AddValues );
	}
}

void CExtCharPet::OnKillMonster( int32_t nLevel )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( NULL == pPet )
		{
			continue;
		}

		if ( pPet->AliveFlag() )
		{
			continue;
		}

		pPet->AddSoul( nLevel, m_pPlayer->GetSoulLevel() );
		return;	//ֻ��һ���˵�
	}
}

void CExtCharPet::AddSoul( int64_t CurTick )
{
	if ( CurTick - m_nLastAddSoulTick  < 5 * 1000 )
	{
		return;
	}
	m_nLastAddSoulTick = CurTick;
	
	for ( int32_t i = 0; i < PET_LIST_SIZE ; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( NULL == pPet )
		{
			continue;
		}
		if ( pPet->isAlive() )
		{
			continue;
		}
		pPet->AddSoul( ADD_SOUL );
	}
}

void CExtCharPet::ridePet( CObjPet* pPet )
{
	if ( m_pRidePet != NULL )
	{
		m_pRidePet->Rest();
		m_pRidePet->SendPetInfo( false );
	}

	m_pRidePet = pPet;
	if ( m_pRidePet != NULL )
	{
		m_pRidePet->Ride();
		m_pRidePet->SendPetInfo( false );
	}
	m_pPlayer->setNeedSyncSelf();
	m_pPlayer->setSyncStatusFlag();
}

void CExtCharPet::checkHatchPool( int8_t nBag, int32_t nTime, int32_t nNow )
{
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return;
	}

	int32_t nSize = getEggBagSize( nBag );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		PetEgg& egg = pEggPool[i];
		const CfgPetEgg* pPetEgg = CFG_DATA.GetPetEggTable().GetEgg( egg.GetBaseId() );
		if ( NULL == pPetEgg )
		{
			continue;
		}
		if ( nBag == PEBT_HATCH_POOL )
		{
			nTime = pPetEgg->nHatchingTime;
		}
		else if ( nBag == PEBT_MUTI_HATCH_POOL )
		{
			nTime = pPetEgg->nMutiHatchingTime;
		}
		if ( egg.GetState() != PES_HATCHING )
		{
			continue;
		}
		if ( nNow - egg.GetStartTime() >= nTime )
		{
			petBorn( egg );
		}
	}
}

void CExtCharPet::petBorn( PetEgg& egg )
{
	CPet* pPet = NULL;
	if ( egg.GetPetId() > 0 )
	{
		pPet = PET_MANAGER.GetPet( egg.GetPetId() );
		if ( NULL == pPet )
		{
			return;
		}

		const CfgPetEgg* pEgg = CFG_DATA.GetPetEggTable().GetEgg( egg.GetBaseId() );
		if ( pEgg != NULL )
		{
			pPet->Reborn( *pEgg );
			PET_MANAGER.UpdatePet( pPet );
		}
	}
	else
	{
		pPet = PET_MANAGER.CreateNewPetFromEgg( egg.GetBaseId(), m_pPlayer );
		if ( NULL == pPet )
		{
			return;
		}
		PET_MANAGER.AddPet( pPet );
	}

	pPet->SendPetInfo( m_pPlayer );
	pPet->SetSyncSelf();

	egg.EndHatch( pPet->GetPetId() );
	addPetEggDirty( &egg );
}

void CExtCharPet::initEggBag( int8_t nBag, int32_t nSize )
{
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return;
	}

	for ( int32_t i = 0; i < nSize; ++i )
	{
		pEggPool[i].CleanUp();
		pEggPool[i].SetBagSlot( nBag, i );
	}
}

void CExtCharPet::cleanEggBag( int8_t nBag, int32_t nSize )
{
	PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return;
	}

	for ( int32_t i = 0; i < nSize; ++i )
	{
		pEggPool[i].CleanUp();
	}
}

PetEgg* CExtCharPet::getEggBagPool( int8_t nBag )
{
	switch ( nBag )
	{
	case PEBT_BAG:				return m_vEggBag;
	case PEBT_HATCH_POOL:		return m_vHatchPool;
	case PEBT_MUTI_HATCH_POOL:	return m_vMutiHatchPool;
	default:	break;
	}
	return NULL;
}

const PetEgg* CExtCharPet::getEggBagPool( int8_t nBag ) const
{
	switch ( nBag )
	{
	case PEBT_BAG:				return m_vEggBag;
	case PEBT_HATCH_POOL:		return m_vHatchPool;
	case PEBT_MUTI_HATCH_POOL:	return m_vMutiHatchPool;
	default:	break;
	}
	return NULL;
}

int32_t CExtCharPet::getEggBagSize( int8_t nBag ) const
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	
	int32_t nLevel = m_pPlayer->getLevel();
	int32_t nVipLevel = m_pPlayer->GetPlayerVip().GetMaxVipLevel();

	switch ( nBag )
	{
//	case PEBT_BAG:				return PET_EGG_BAG_SIZE;
	case PEBT_HATCH_POOL:		return CFG_DATA.GetCharPetTable().GetHatchPoolSize( nLevel, nVipLevel );
//	case PEBT_MUTI_HATCH_POOL:	return CFG_DATA.GetCharPetTable().GetMutiHatchPoolSize( nLevel, nVipLevel );
	default:	break;
	}
	return 0;
}

void CExtCharPet::savePets( DBPetList& petList )
{
	DBPet pet = {};
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( NULL == pPet )
		{
			continue;
		}

		bzero( &pet, sizeof( pet ) );
		pPet->OnSaveToDB( pet );
		petList.push_back( pet );
	}
}

void CExtCharPet::saveEggBag( int8_t nBag, DBPetEggList& eggList )
{
	const PetEgg* pEggPool = getEggBagPool( nBag );
	if ( NULL == pEggPool )
	{
		return;
	}

	DBPetEgg egg = {};
	int32_t nSize = getEggBagSize( nBag );
	for ( int32_t i = 0; i < nSize; ++i )
	{
		if ( pEggPool[i].IsEmpty() )
		{
			continue;
		}
		bzero( &egg, sizeof( egg ) );
		egg.nBag		= pEggPool[i].GetBag();
		egg.nSlot		= pEggPool[i].GetSlot();
		egg.nBaseId		= pEggPool[i].GetBaseId();
		egg.nState		= pEggPool[i].GetState();
		egg.nStartTime	= pEggPool[i].GetStartTime();
		egg.nPetId		= pEggPool[i].GetPetId();

		eggList.push_back( egg );
	}
}

void CExtCharPet::sendPetList()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_LIST );
	if (NULL == packet)
	{
		return;
	}

	int32_t	nCount = 0;
	packet->writeInt8( nCount );
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( NULL == pPet )
		{
			continue;
		}

		pPet->AppendPetInfo( packet );
		++nCount;
	}

	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt8( nCount );
	packet->setWOffset( endOffSet );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CExtCharPet::sendPetInfo( const PetList& pList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_INFO );
	if (NULL == packet)
	{
		return;
	}

	int32_t	nCount = 0;
	packet->writeInt8( nCount );
	PetList::const_iterator iter = pList.begin();
	PetList::const_iterator eiter = pList.end();
	for ( ; iter != eiter; ++iter )
	{
		CPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}

		pPet->AppendBaseInfo( packet );
		++nCount;
	}

	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( 0 );
	packet->writeInt8( nCount );
	packet->setWOffset( endOffSet );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CExtCharPet::getMaxFightPet() const
{
	if ( NULL == m_pPlayer )
	{
		return 2;
	}

	return m_pPlayer->GetOperateLimit().GetLimitCount( PR_OPEN_THIRED_FIGHT_PET );
}


bool CExtCharPet::addFightPet( CObjPet* pPet )
{
	if ( NULL == pPet )
	{
		return false;
	}
	if ( m_vFightPet[PSP_LEFT] == NULL )
	{
		++m_nFightingCount;
		m_vFightPet[PSP_LEFT] = pPet;
		pPet->SetSatandPlace( UP_LEFT );
		CheckMagMainPet();
		return true;
	}
	else if ( m_vFightPet[PSP_RIGHT] == NULL )
	{
		++m_nFightingCount;
		m_vFightPet[PSP_RIGHT] = pPet;
		pPet->SetSatandPlace( UP_RIGHT );
		CheckMagMainPet();
		return true;
	}
	else if ( m_vFightPet[PSP_DOWN] == NULL )
	{
		++m_nFightingCount;
		m_vFightPet[PSP_DOWN] = pPet;
		pPet->SetSatandPlace( UP );
		CheckMagMainPet();
		return true;
	}
	return false;
}

void CExtCharPet::removeFightPet( CObjPet* pPet )
{
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		if ( m_vFightPet[i] == pPet )
		{
			m_vFightPet[i]->SetMainPet( false );
			--m_nFightingCount;
			m_vFightPet[i] = NULL;
		}
	}
	CheckMagMainPet();
}

void CExtCharPet::CheckMagMainPet()
{
	int32_t MaxMagAtk		= 0;
	int32_t Pos				= -1;
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		if ( NULL != m_vFightPet[i] && m_vFightPet[i]->GetPet() != NULL )
		{
			if ( m_vFightPet[i]->GetPetJob() == PET_JOB_FASHI )
			{
				m_vFightPet[i]->SetMainPet( false );
				if ( m_vFightPet[i]->GetAttrValue( CObjAttrs::ATTR_MAG_ATK_MAX ) > MaxMagAtk )
				{
					Pos = i;
					MaxMagAtk = m_vFightPet[i]->GetAttrValue( CObjAttrs::ATTR_MAG_ATK_MAX );
				}
			}
		}
	}

	if ( Pos >= 0 && Pos < PSP_SIZE )
	{
		m_vFightPet[Pos]->SetMainPet( true );
	}
};

void CExtCharPet::initKnight()
{
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( pPet != NULL )
		{
			int8_t nKnight = pPet->GetKnight();
			if ( nKnight > PK_NONE && nKnight < PET_KNIGHT_SIZE )
			{
				m_vPetKnight[nKnight] = pPet;
				const CfgPetKnight* pCfgKnight = CFG_DATA.GetPetKnightTable().GetKnight( nKnight );
				if ( NULL != pCfgKnight )
				{
					if ( pCfgKnight->nEffectType == PKE_ADD_MAX_HP )
					{
						int32_t nEffectValue = pCfgKnight->GetEffectValue( pPet->GetPoints() );
						if ( nEffectValue > 0 )
						{
							m_vKnightAddValue[nKnight] = m_pPlayer->AddBuffAttrRatio( CObjAttrs::ATTR_HP, nEffectValue );
							AddKnightPetHp( nEffectValue );
						}
					}
				}
				
			}
			int8_t QiShi = pPet->GetQiShi();
			if ( QiShi > 0 && QiShi <= QI_SHI_COUNT )
			{
				m_vPetWearQiShi[QiShi-1] = pPet;
			}
		}
	}
}

bool CExtCharPet::IsTopPet( CObjPet* pPet ) const
{
	if ( NULL == pPet )
	{
		return false;
	}
	if ( pPet->GetPet() != NULL && pPet->GetPet()->IsXOType() )
	{
		return false;
	}
	if ( pPet->GetPoints() < 500 )
	{
		return false;
	}

	std::vector<CObjPet*> vSort;
	vSort.reserve( PET_LIST_SIZE );

	int32_t nCount = 0;
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		if ( m_vAllPet[i] != NULL )
		{
			vSort.push_back( m_vAllPet[i] );
			++nCount;
		}
	}

	if ( nCount <= 3 )
	{
		return false;
	}

	std::sort( vSort.begin(), vSort.end(), PetPointsSortGreater() );

	for ( uint32_t i = 0; i < vSort.size() && i < 3; ++i )
	{
		if ( vSort[i] == pPet )
		{
			return true;
		}
	}
	return false;
}

int8_t	CExtCharPet::GetKnightCount()
{
	int8_t Count = 0;
	for ( int32_t i = 0; i < PET_KNIGHT_SIZE; ++i )
	{
		if ( NULL == m_vPetKnight[i] )
		{
			continue;
		}
		Count++;
	}
	return Count;
}

int32_t CExtCharPet::GetKnightPoints( PET_KNIGHT Type )
{
	if ( Type < PET_KNIGHT_SIZE && Type > PK_NONE )
	{
		if ( NULL == m_vPetKnight[Type] )
		{
			return 0;
		}
		return m_vPetKnight[Type]->GetPoints();
	}
	return 0;
}

void CExtCharPet::broadcastMapPetFighting( CObjPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}
	Map* pMap = pPet->getMap();
	if ( NULL == pMap )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PET_SET_FIGHT );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt64( pPet->GetPetId() );
	packet->setSize( packet->getWOffset() );

	pMap->broadcastAreaAround( packet, pPet );
}

void CExtCharPet::RecalPetsAttr()
{
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		if ( m_vAllPet[i] != NULL )
		{
			m_vAllPet[i]->RecalAttr();
		}
	}
}

void CExtCharPet::ReviveAllPet()
{
	for ( int32_t i = 0; i < PET_BAG_SIZE; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( pPet != NULL )
		{
			pPet->Relive();
		}
	}
}

int32_t CExtCharPet::HavePetCountByPoints( int32_t Points )
{
	int32_t Count = 0;
	for ( int32_t i = 0; i < PET_LIST_SIZE; ++i )
	{
		CObjPet* pPet = m_vAllPet[i];
		if ( pPet != NULL )
		{
			if ( NULL != pPet->GetPet() && !pPet->GetPet()->IsXOType() )
			{
				if ( pPet->GetPoints() >= Points )
				{
					Count++;
				}
			}
		}
	}
	return Count;
}
// ========== 新版本添加方法 ==========

int32_t CExtCharPet::onFight( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	CObjPet* pPet = GetFightPet();
	if ( NULL == pPet )
	{
		PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
		pPet = GetPet( nPetId );
		if ( NULL == pPet )
		{
			return ERR_SYETEM_ERR;
		}
	}
	if ( !pPet->AliveFlag() )
	{
		return ERR_SYETEM_ERR;
	}
	Map* pMap = m_pPlayer->getMap();
	if ( NULL == pMap || !pMap->CanUsePet() )
	{
		return ERR_SYETEM_ERR;
	}
	// If pet is fitting, transition to fighting
	if ( pPet->IsFitting() )
	{
		pPet->SetFitting( false );
		pPet->Fighting();
		pPet->EnterMap();
		m_pPlayer->recalcAttr();
	}
	else if ( pPet->IsRest() )
	{
		pPet->Fighting();
		pPet->EnterMap();
		m_pPlayer->recalcAttr();
	}
	else
	{
		return ERR_SYETEM_ERR;
	}
	broadcastMapPetFighting( pPet );
	pPet->SendPetInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}



int32_t CExtCharPet::onPetHuanHua( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t HuanHua = inPacket->readInt32();
	if ( m_HuanHua == HuanHua )
	{
		return ERR_SYETEM_ERR;
	}
	m_HuanHua = HuanHua;
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}

int32_t CExtCharPet::onUpStar( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}
	// Check star config
	int32_t nNextStar = pPet->GetStar() + 1;
	const CfgPetUpStar* pCfgUpStar = CFG_DATA.GetPetTable().GetPetUpStar( nNextStar );
	if ( NULL == pCfgUpStar )
	{
		return ERR_SYETEM_ERR;
	}
	// Check items cost
	Int32Vector vSlot;
	if ( pCfgUpStar->nNeedItemId > 0 )
	{
		m_pPlayer->queryBagInfoByItemId( pCfgUpStar->nNeedItemId, pCfgUpStar->nNeedItemCount, vSlot );
		if ( vSlot.empty() )
		{
			return ERR_SYETEM_ERR;
		}
		ItemData itemData = {};
		itemData.m_nId = pCfgUpStar->nNeedItemId;
		itemData.m_nClass = IC_NORMAL;
		itemData.m_nCount = pCfgUpStar->nNeedItemCount;
		if ( !m_pPlayer->GetBag().RemoveItem( vSlot, itemData, IDCR_PET_UP_STAR ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	// Check money cost
	if ( pCfgUpStar->nCostMoney > 0 )
	{
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( pCfgUpStar->nCostMoney, MCR_PET_UP_STAR ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	// Check gold cost
	if ( pCfgUpStar->nCostGold > 0 )
	{
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfgUpStar->nCostGold, (CurrencyChangeReason)2059 ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	// Perform up star
	pPet->UpStar();
	m_nStar = nNextStar;
	pPet->SendPetInfo();
	pPet->RecalAttr();
	m_pPlayer->recalcAttr();
	// Check skill unlock
	pPet->CheckSkillOpen();
	// Broadcast if needed
	if ( pCfgUpStar->nBroadId > 0 )
	{
		std::string strMsg;
		// TODO: implement world broadcast for pet up-star (API removed)
		// broadcastWorld removed: GAME_SERVICE.broadcastWorld( strMsg );
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}



int32_t CExtCharPet::onDressEquip( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	Int32Vector vSlot;
	m_pPlayer->queryBagInfo( inPacket, vSlot );
	if ( vSlot.empty() )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nBagSlot = vSlot[0];
	int32_t nPetSlot = inPacket->readInt32();
	MemChrBag bagItem = m_pPlayer->GetBag().GetSlotData( nBagSlot );
	if ( m_pPlayer->GetBag().IsEmptySlot( bagItem ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( bagItem.itemClass != IC_PET_EQUIP )
	{
		return ERR_SYETEM_ERR;
	}
	CObjPet* pPet = GetFightPet();
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}
	// Check if pet slot already has equipment, swap it back
	int32_t nOldEquipId = pPet->GetEquip( nPetSlot );
	if ( nOldEquipId > 0 )
	{
		ItemData oldEquip = {};
		oldEquip.m_nId = nOldEquipId;
		oldEquip.m_nClass = IC_PET_EQUIP;
		oldEquip.m_nCount = 1;
		MemChrBag bagItem; bagItem.itemId = oldEquip.m_nId; bagItem.itemClass = oldEquip.m_nClass; bagItem.itemCount = oldEquip.m_nCount; bagItem.bind = 0; bagItem.endTime = 0; bagItem.srcId = 0; if ( !m_pPlayer->GetBag().AddItem( bagItem, IACR_FROM_PET ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	// Remove new item from bag
	MemChrBag emptySlot = {};
	m_pPlayer->GetBag().SetSlotData( nBagSlot, emptySlot, 39 );
	// Set equip on pet
	pPet->SetEquip( nPetSlot, bagItem.itemId );
	pPet->SendPetInfo();
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}



int32_t CExtCharPet::onUnDressEquip( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nPetSlot = inPacket->readInt32();
	CObjPet* pPet = GetFightPet();
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nEquipId = pPet->GetEquip( nPetSlot );
	if ( nEquipId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	// Return equipment to bag
	ItemData equipData = {};
	equipData.m_nId = nEquipId;
	equipData.m_nClass = IC_PET_EQUIP;
	equipData.m_nCount = 1;
	MemChrBag bagItem2; bagItem2.itemId = equipData.m_nId; bagItem2.itemClass = equipData.m_nClass; bagItem2.itemCount = equipData.m_nCount; bagItem2.bind = 0; bagItem2.endTime = 0; bagItem2.srcId = 0; if ( !m_pPlayer->GetBag().AddItem( bagItem2, IACR_FROM_PET ) )
	{
		return ERR_SYETEM_ERR;
	}
	// Clear pet slot
	pPet->SetEquip( nPetSlot, 0 );
	pPet->SendPetInfo();
	m_pPlayer->recalcAttr();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}



int32_t CExtCharPet::onFitting( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->GetEquip().GetGongMingSuitId() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pPet->IsFighting() )
	{
		pPet->LeaveMap();
		pPet->SetFitting( true );
		m_pPlayer->recalcAttr();
	}
	else if ( pPet->IsRest() )
	{
		pPet->SetFitting( true );
	}
	else
	{
		return ERR_SYETEM_ERR;
	}
	pPet->SendPetInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}



int32_t CExtCharPet::onRestPet( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pPet->IsFighting() )
	{
		pPet->LeaveMap();
		pPet->Rest();
		m_pPlayer->recalcAttr();
	}
	else if ( pPet->IsFitting() )
	{
		pPet->SetFitting( false );
		m_pPlayer->recalcAttr();
	}
	else
	{
		return ERR_SYETEM_ERR;
	}
	pPet->SendPetInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}


int32_t CExtCharPet::onChangeAi( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	int8_t nAiState = inPacket->readInt8();
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}
	if ( nAiState < 0 || nAiState > 1 )
	{
		return ERR_SYETEM_ERR;
	}
	pPet->ChangeAi( nAiState );
	pPet->SendPetInfo();
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}



int32_t CExtCharPet::onSkillUpLevel( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	PetId_t nPetId = static_cast<PetId_t>( inPacket->readInt64() );
	int8_t nSkillPos = inPacket->readInt8();
	CObjPet* pPet = GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_SYETEM_ERR;
	}
	PetSkillInfo* pSkill = pPet->GetSkill( nSkillPos );
	if ( NULL == pSkill || pSkill->nId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	// Check max level from talent config
	int32_t nMaxLevel = pPet->GetSkillMaxLevel( nSkillPos );
	if ( pSkill->nLevel >= nMaxLevel )
	{
		return ERR_SYETEM_ERR;
	}
	// Find cost item
	int32_t nNextLevel = pSkill->nLevel + 1;
	int32_t nBookId = CFG_DATA.GetSkillLevelUpTable().GetBook( pSkill->nId, pSkill->nLevel );
	if ( nBookId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	Int32Vector vSlot;
	m_pPlayer->queryBagInfoByItemId( nBookId, 1, vSlot );
	if ( vSlot.empty() )
	{
		return ERR_SYETEM_ERR;
	}
	ItemData itemData = {};
	itemData.m_nId = nBookId;
	itemData.m_nClass = IC_NORMAL;
	itemData.m_nCount = 1;
	if ( !m_pPlayer->GetBag().RemoveItem( vSlot, itemData, (ITEM_DEL_REASON)40 ) )
	{
		return ERR_SYETEM_ERR;
	}
	// Level up skill
	pPet->LearnSkill( pSkill->nId, nSkillPos );
	pPet->SendPetInfo();
	if ( pPet->IsFighting() )
	{
		m_pPlayer->recalcAttr();
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(), inPacket->getProc() );
	return ERR_OK;
}



bool CExtCharPet::IsFighting() const
{
	CObjPet* pPet = const_cast<CExtCharPet*>(this)->GetFightPet();
	return NULL != pPet;
}

bool CExtCharPet::IsFitting() const
{
	CObjPet* pFit = const_cast<CExtCharPet*>(this)->GetFightPet();
	if ( NULL != pFit )
	{
		return pFit->IsFitting();
	}
	return false;
}

bool CExtCharPet::IsFunctionOpen() const
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	return m_pPlayer->GetPlayerFunctionOpen().IsOpened( 32 );
}

void CExtCharPet::SendPetStatus()
{
	CObjPet* pPet2 = GetFightPet();
	if ( pPet2 != NULL && pPet2->GetState() == PS_FIGHTING )
	{
		pPet2->SendPetStatus();
	}
}

int32_t CExtCharPet::GetSkillBattle()
{
	return 0;
}

int32_t CExtCharPet::GetStar() const
{
	return m_nStar;
}

int32_t CExtCharPet::GetHuanHua() const
{
	return m_HuanHua;
}

void CExtCharPet::AddPetAttr()
{
	// 属性加成由各子模块自行处理
}

void CExtCharPet::clearSummonPet()
{
	SummonList::iterator iter = m_lSummons.begin();
	SummonList::iterator eiter = m_lSummons.end();
	for ( ; iter != eiter; ++iter )
	{
		CObjPet* pPet = *iter;
		if ( pPet != NULL )
		{
			pPet->LeaveMap();
			GAME_SERVICE.removePet( pPet );
			POOL_MANAGER.push<CObjPet>( pPet );
		}
	}
	m_lSummons.clear();
}

bool CExtCharPet::HaveSummonAlive()
{
	SummonList::iterator iter = m_lSummons.begin();
	SummonList::iterator eiter = m_lSummons.end();
	for ( ; iter != eiter; ++iter )
	{
		CObjPet* pPet = *iter;
		if ( pPet != NULL && pPet->AliveFlag() )
		{
			return true;
		}
	}
	return false;
}

void CExtCharPet::addSummonPet( CObjPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}
	m_lSummons.push_back( pPet );
}

void CExtCharPet::removeSummonPet( CObjPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}
	m_lSummons.remove( pPet );
	GAME_SERVICE.removePet( pPet );
	POOL_MANAGER.push<CObjPet>( pPet );
}

void CExtCharPet::OnSummon( int32_t nPetId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	CPet* pPet = PET_MANAGER.CreateNewPet( nPetId, m_pPlayer, PFW_SUMMON );
	CObjPet* pObjPet = POOL_MANAGER.pop<CObjPet>();
	if ( NULL == pPet || NULL == pObjPet )
	{
		return;
	}
	PET_MANAGER.AddPet( pPet );
	pObjPet->Init( pPet, m_pPlayer );
	GAME_SERVICE.addPet( pObjPet );
	m_lSummons.push_back( pObjPet );
	pObjPet->SendPetInfo();
}

void CExtCharPet::SummonInfo()
{
	// 发送召唤信息给客户端
}

void CExtCharPet::OnInitPet()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	CObjPet* pFightPet = GetFightPet();
	if ( pFightPet != NULL )
	{
		return;
	}
	int32_t nDefaultPetId = 101;
	CPet* pPet = PET_MANAGER.CreateNewPet( nDefaultPetId, m_pPlayer, PFW_BORN );
	CObjPet* pObjPet = POOL_MANAGER.pop<CObjPet>();
	if ( NULL == pPet || NULL == pObjPet )
	{
		return;
	}
	PET_MANAGER.AddPet( pPet );
	pPet->SetPetBorn();
	pObjPet->Init( pPet, m_pPlayer );
	GAME_SERVICE.addPet( pObjPet );
	addPet( pObjPet, PBT_BAG );
	Fighting( pObjPet );
	pObjPet->SendPetInfo();
}

void CExtCharPet::OnLevelUp()
{
	CObjPet* pLvl = GetFightPet();
	if ( NULL != pLvl )
	{
		pLvl->OnLevelUp();
		pLvl->SendPetInfo();
	}
	SummonList::iterator iter = m_lSummons.begin();
	SummonList::iterator eiter = m_lSummons.end();
	for ( ; iter != eiter; ++iter )
	{
		CObjPet* pPet = *iter;
		if ( pPet != NULL && pPet->AliveFlag() )
		{
			pPet->OnLevelUp();
		}
	}
}

void CExtCharPet::OnPlayerDie()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_vFightPet[i];
		if ( pPet != NULL )
		{
			if ( pPet->IsFighting() )
			{
				pPet->LeaveMap();
				pPet->Rest();
			}
		}
	}
	m_pPlayer->recalcAttr();
	clearSummonPet();
}
