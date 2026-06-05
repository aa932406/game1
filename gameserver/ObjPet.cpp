#include "stdafx.h"

#include "CfgData.h"
#include "GameService.h"
#include "Map.h"
#include "Player.h"
#include "ObjPet.h"
#include "PoolManager.h"
#include "PetManager.h"

#define MAX_SOUL_POINT	10000
#define BATTLE_TIAN_FU  126			//ս�����츳����id
#define REPLY_HP_CD     10 * 1000	//��Ѫcd
#define REPLAY_HP_CD_90 2 * 1000	//30��ǰ��Ѫcd
using namespace Answer;

CObjPet::CObjPet()
	: Unit(ET_PET),  m_pPlayer( NULL )
{

}

CObjPet::~CObjPet()
{

}

void CObjPet::refresh()
{
	if ( m_nState == PS_FIGHTING )
	{
		checkSpeed();
		checkSwitchMap();
		updateFightState();
	}

	if ( m_pPet != NULL )
	{
		if ( m_pPet->NeedSyncSelf() )
		{
			m_pPet->SendPetInfo( m_pPlayer );
			m_pPet->SetSyncSelf();
		}

		if ( m_pPet->NeedSyncStatus() )
		{
			SendPetStatus();
			m_pPet->SetSyncStatus();
		}
	}

	if ( m_needSyncSelf )
	{
		SendPetInfo( false );
		m_needSyncSelf = false;
	}
}

EntityId_t CObjPet::getUnitId() const
{
	return GetPetId();
}

CharId_t CObjPet::getOwner() const
{
	if (m_pPlayer != NULL)
	{
		return m_pPlayer->getCid();
	}
	else
	{
		return 0;
	}
}

int32_t CObjPet::getLevel() const
{
	return m_pPet != NULL ? m_pPet->GetLevel() : 0;
}

int32_t CObjPet::GetCalLevel() const
{
	return m_pPlayer != NULL ? m_pPlayer->GetCalLevel() : getLevel();
}

int32_t CObjPet::getBattle() const
{
	return m_pPlayer != NULL ? m_pPlayer->getBattle() : 0;
}

bool CObjPet::isFriendSide(Unit *pUnit)
{
	return m_pPlayer != NULL ? m_pPlayer->isFriendSide( pUnit ) : false;
}

bool CObjPet::checkSkillTarget(CfgSkill *pCfg, Unit *pUnit)
{
	return m_pPlayer != NULL ? m_pPlayer->checkSkillTarget( pCfg, pUnit ) : false;
}

void CObjPet::postDamage(int32_t damge, UnitHandle launcher)
{
	if (!isAlive())
	{
		onDie();
	}
	else
	{
		AddTarget( launcher );
	}
}

void CObjPet::onDie()
{
	Die();
}

void CObjPet::reset()
{
	Unit::reset();

	m_pPlayer			= NULL;
	m_pPet				= NULL;
	m_bAlive			= false;
	m_nSoul				= 0;
	m_nState			= PS_REST;
	m_nFightState		= PFS_AWAY_FROM_MAP;
	m_nStandPlace		= LEFT;
	m_nBagType			= PBT_DEPORT;
	m_nKnight			= PK_NONE;
	m_nRegistFamily		= 0;
	m_bMainPet			= false;
	m_nLastSkillTick	= 0;
	m_nLastReplyHp		= 0;
	m_pNextSkill		= NULL;
	m_nQiShi			= 0;
	m_target.clear();
	m_lstTargets.clear();

	// Initialize new version members
	bzero( m_vEquip, sizeof( m_vEquip ) );
	m_nFitting = 0;
	m_AiState = 0;
	m_nStar = 0;
}

void CObjPet::Init( CPet* pPet, Player* pOwner, bool bAlive, int32_t nSoul, PET_STATE state, Direction nDir )
{
	m_pPet			= pPet;
	m_pPlayer		= pOwner;
	m_bAlive		= bAlive;
	m_nSoul			= nSoul;
	m_nState		= state;
	m_nFightState	= PFS_AWAY_FROM_MAP;
	m_nStandPlace	= nDir;
	m_target.clear();
	m_lstTargets.clear();

	recalAttr();
	FillHP();
}

void CObjPet::ReplyHp( int64_t CurTick )
{
	if ( !isAlive() )
	{
		return;
	}
	if ( getLevel() <= 90 )
	{
		if ( CurTick - m_nLastReplyHp < REPLAY_HP_CD_90 )
		{
			return;
		}
	}
	else
	{
		if ( CurTick - m_nLastReplyHp < REPLY_HP_CD )
		{
			return;
		}
	}
	
	m_nLastReplyHp = CurTick;
	if ( GetHP() >= GetMaxHP() )
	{
		return;
	}
	int32_t ReplyRate = 10;
	if ( getLevel() <= 90 )
	{
		ReplyRate = 20;
	}
	int32_t NeedAddHp = GetMaxHP() / 100 * ReplyRate;
	AddHP(NeedAddHp);
}

void CObjPet::SetOwner( Player* pOwner )
{
	m_pPlayer = pOwner;
}

bool CObjPet::AppendInfo(Answer::NetPacket *packet)
{
	if ( NULL == m_pPlayer || NULL == packet )
	{
		return false;
	}

	packet->writeInt64( GetPetId() );					// ����ID
	packet->writeInt32( GetBaseId() );					// ����ID
	packet->writeUTF8( GetName() );						// ��������
	packet->writeInt64( m_pPlayer->getCid() );			// ӵ����ID
	packet->writeUTF8( m_pPlayer->getName() );			// ӵ��������
	packet->writeInt16( getCurrentTile().x );			// ��ǰ����X
	packet->writeInt16( getCurrentTile().y );			// ��ǰ����Y
	packet->writeInt16( getTargetTile().x );			// Ŀ������X
	packet->writeInt16( getTargetTile().y );			// Ŀ������Y
	packet->writeInt32( GetHP() );						// ��ǰѪ��
	packet->writeInt32( GetMaxHP() );					// ���Ѫ��
	packet->writeInt32( GetMoveSpeed() );				// �ƶ��ٶ�
	packet->writeInt32( GetTopRankIndex() );			// ������Σ�ʥ�ޣ�
	packet->writeInt32( GetPoints() );					// Ʒ��

	return true;
}

Player* CObjPet::GetPlayer()
{
	return m_pPlayer;
}

CPet* CObjPet::GetPet()
{
	return m_pPet;
}

PetId_t CObjPet::GetPetId() const
{
	return m_pPet != NULL ? m_pPet->GetPetId() : 0;
}

//void CObjPet::SetPetId( PetId_t nPetId )
//{
//	m_nPetId = nPetId;
//}

int32_t CObjPet::GetBaseId() const
{
	return m_pPet != NULL ? m_pPet->GetBaseId() : 0;
}

Job_t CObjPet::GetPetJob() const
{
	return m_pPet != NULL ? m_pPet->GetPetJob() : 0;
}

bool CObjPet::IsRidePet() const
{
	return m_pPet != NULL ? m_pPet->IsRidePet() : false;
}

bool CObjPet::AliveFlag() const
{
	return m_bAlive;
}

int8_t CObjPet::GetBagType() const
{
	return m_nBagType;
}

void CObjPet::SetBagType( int8_t nBagType )
{
	m_nBagType = nBagType;
}

int8_t CObjPet::GetKnight() const
{
	return m_nKnight;
}

void CObjPet::SetKnight( int8_t nKnight )
{
	m_nKnight = nKnight;
}

int32_t CObjPet::GetPoints() const
{
	if ( m_pPet != NULL )
	{
		return m_pPet->GetPoints();
	}
	return 0;
}

int32_t	CObjPet::GetBattle() const
{
	if ( m_pPet != NULL )
	{
		return m_pPet->GetBattle();
	}
	return 0;
}

int32_t CObjPet::GetLucky() const
{
	if ( NULL == m_pPet )
	{
		return 0;
	}
	return m_pPet->GetLucky();
}

PET_PHASE CObjPet::GetPhase() const
{
	if ( NULL == m_pPet )
	{
		return PP_INVALID;
	}
	return m_pPet->GetPhase();
}

void CObjPet::Die()
{
	if ( IsZoarium() )
	{
		Fighting();
		EnterMap();
		m_pPlayer->GetCharPet().OnZoariumPetDie();
	}
	m_bAlive = false;
	m_nSoul = 0;
	ClearTarget();
	backToPlayer();
}

void CObjPet::Relive()
{
	FillHP();
	m_bAlive = true;
	setNeedSync();
}

PET_STATE CObjPet::GetState() const
{
	return m_nState;
}

void CObjPet::SetState( PET_STATE state )
{
	m_nState = state;
}

void CObjPet::SetSatandPlace( Direction nDir )
{
	m_nStandPlace = nDir;
}

bool CObjPet::IsFighting() const
{
	return m_nState == PS_FIGHTING;
}

bool CObjPet::IsZoarium() const
{
	return m_nState == PS_ZOARIUM;
}

bool CObjPet::IsRide() const
{
	return m_nState == PS_RIDE;
}

bool CObjPet::IsRest() const
{
	return m_nState == PS_REST;
}

void CObjPet::Fighting()
{
	m_nState = PS_FIGHTING;
}

void CObjPet::Zoarium()
{
	m_nState = PS_ZOARIUM;
}

void CObjPet::Ride()
{
	m_nState = PS_RIDE;
}

void CObjPet::Rest()
{
	m_nState = PS_REST;
}

void CObjPet::SendPetInfo( bool bSendBase )
{
	if ( NULL == m_pPlayer || NULL == m_pPet )
	{
		return;
	}

	if ( bSendBase )
	{
		m_pPet->SendPetInfo( m_pPlayer );
		m_pPet->SetSyncSelf();
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_LIST );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( 1 );
	AppendPetInfo( packet );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CObjPet::SendPetStatus()
{
	if ( NULL == m_pPlayer || NULL == m_pPet || NULL == m_pMap )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_STATUS );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt64( m_pPet->GetPetId() );		// ����ID
	packet->writeInt32( m_pPet->GetPoints() );		// ����
	packet->writeInt32( GetTopRankIndex() );		// ��������

	packet->setSize( packet->getWOffset() );

	m_pMap->broadcastAreaAround( packet, this );
}

void CObjPet::AppendPetInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet || NULL == m_pPet )
	{
		return;
	}

	packet->writeInt8( m_nBagType );							// �洢λ��
	packet->writeInt64( m_pPet->GetPetId() );					// ����ID
	packet->writeInt32( m_pPet->GetFlag() );					// ���±��
	packet->writeInt8( m_bAlive ? 1 : 0 );						// �Ƿ���
	packet->writeInt32( m_nSoul );								// ��������ֵ
	packet->writeInt8( static_cast<int8_t>( m_nState ) );		// ���ﵱǰ״̬
	packet->writeInt8( m_nKnight );								// ��ʿ
	packet->writeInt8( m_nQiShi );								// ���������
	appendAttrInfo( packet );									// ��������
}

void CObjPet::appendAttrInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}
	
	packet->writeInt32( GetHP() );										// ��ǰѪ��
	packet->writeInt32( GetMaxHP() );									// ���Ѫ��
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_PHY_ATK_MIN ) );	// ��С��������
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_PHY_ATK_MAX ) );	// �����������
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_MAG_ATK_MIN ) );	// ��Сħ������
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_MAG_ATK_MAX ) );	// ���ħ������
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_PHY_DEF ) );		// ��������
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_MAG_DEF ) );		// ħ������
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_HITRATE ) );		// ����
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_DODGE ) );		// ����
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_CRITRATE ) );		// ������Ԥ����
	packet->writeInt32( GetAttrValue( CObjAttrs::ATTR_TENACITY ) );		// ���ԣ�Ԥ����
}

PetSkillInfo* CObjPet::GetSkill( SkillId_t nSkill )
{
	if ( NULL == m_pPet )
	{
		return NULL;
	}
	return m_pPet->GetSkill( nSkill );
}

PetSkillInfo* CObjPet::GetSkillByPos( int8_t nSkillPos )
{
	if ( NULL == m_pPet )
	{
		return NULL;
	}
	return m_pPet->GetSkillByPos( nSkillPos );
}

bool CObjPet::LearnSkill( SkillId_t nSkill, int8_t nSkillPos )
{
	if ( NULL == m_pPet )
	{
		return false;
	}

	bool bChange = m_pPet->LearnSkill( nSkill, nSkillPos );
	if ( bChange )
	{
		PetSkillInfo* pSkill = m_pPet->GetSkillByPos( nSkillPos );
		if ( pSkill != NULL && pSkill->nLevel >= 3 )
		{
			broadcastPetSkillLevelUp( pSkill->nId, pSkill->nLevel );
		}
		recalAttr();
	}
	return bChange;
}

bool CObjPet::ForgetSkill( SkillId_t nSkill )
{
	if ( NULL == m_pPet )
	{
		return false;
	}
	bool bChange = m_pPet->ForgetSkill( nSkill );
	if ( bChange )
	{
		recalAttr();
	}
	return bChange;
}

void CObjPet::ChangeName( const std::string& strName )
{
	if ( NULL == m_pPet )
	{
		return;
	}
	m_pPet->ChangeName( strName );
	setNeedSyncSelf();
}

std::string CObjPet::GetName() const
{
	return m_pPet != NULL ? m_pPet->GetName() : "";
}

int32_t CObjPet::OnMove(int32_t mapID,int16_t currentX, int16_t currentY, int16_t targetX, int16_t targetY, int16_t finalX, int16_t finalY, Direction direction)
{
	if (m_pPlayer == NULL || m_pMap == NULL || m_pMap != m_pPlayer->getMap() || m_pMap->GetId() != mapID)
	{
		return ERR_INVALID_DATA;
	}

	Tile *pCurrentTile = m_pMap->getTile(currentX, currentY);
	Tile *pTargetTile = m_pMap->getTile(targetX, targetY);
	Tile *pFinalTile = m_pMap->getTile(finalX, finalY);

	if (pCurrentTile == NULL || pTargetTile == NULL || pFinalTile == NULL)
	{
		return ERR_INVALID_DATA;
	}

	if (Position(currentX, currentY).tileDistance(Position(finalX, finalY)) > 20)
	{
		return ERR_INVALID_DATA;
	}

	setAtTile(m_pMap, currentX, currentY);
	
	setTargetTile(targetX, targetY);
	
	broadcastMove();

	return ERR_OK;
}

void CObjPet::LeaveMap()
{
	if (m_pMap != NULL)
	{
		ClearTarget();
		setFightState( PFS_AWAY_FROM_MAP );
		m_pMap->removePet( this );
		broadcastLeave();
		m_pMap = NULL;
	}
}

void CObjPet::EnterMap()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Map* pMap = m_pPlayer->getMap();
	if ( NULL == pMap )
	{
		return;
	}
	Position targetTile = getFollowTile( m_pPlayer->getCurrentTile().x, m_pPlayer->getCurrentTile().y, m_pPlayer->getDirection() );
	setAtTile( pMap, targetTile.x, targetTile.y );
	pMap->addPet( this );

	ClearTarget();
	setFightState( PFS_STAND );
}

void CObjPet::OnLogout()
{
	if ( m_pPlayer == NULL || m_pMap == NULL )
	{
		return;
	}
	LeaveMap();
}

void CObjPet::checkSwitchMap()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Map *pMap = m_pPlayer->getMap();
	if ( pMap == NULL )
	{
		return;
	}

	if ( pMap != m_pMap )
	{
		LeaveMap();
		EnterMap();
	}
}

bool CObjPet::AddExp( int64_t nExp )
{
	if ( NULL == m_pPet )
	{
		return false;
	}
	bool bLevelUp = false;
	if ( m_pPet->AddExp( nExp ) )
	{
		onLevelUp();
		bLevelUp = true;
	}
	SendPetInfo();
	return bLevelUp;
}

bool CObjPet::AddSoul( int32_t nMonsterLevel, int32_t SoulLevel )
{
	if ( NULL == m_pPet )
	{
		return false;
	}

	int32_t nDiffLevel = nMonsterLevel - ( m_pPet->GetLevel() + SoulLevel );
	int32_t nAddValue = 0;//
	if ( nDiffLevel >= 90 )
	{
		nAddValue = 10000;
	}
	else if ( nDiffLevel >= 50 )
	{
		nAddValue = 5000;
	}
	else if ( nDiffLevel >= 20 )
	{
		nAddValue = 2000;
	}
	else if ( nDiffLevel >= 0 )
	{
		nAddValue = 1000;
	}
	else if ( nDiffLevel >= -10 )
	{
		nAddValue = 700;
	}
	else if ( nDiffLevel >= -30 )
	{
		nAddValue = 500;
	}
	else
	{
		nAddValue = 200;
	}

	m_nSoul += nAddValue;
	if ( m_nSoul >= MAX_SOUL_POINT )
	{
		Relive();
	}
	setNeedSyncSelf();
	return true;
}

void CObjPet::AddSoul( int32_t AddValues )
{
	m_nSoul += AddValues;
	if ( m_nSoul >= MAX_SOUL_POINT )
	{
		Relive();
	}
	setNeedSyncSelf();
}

void CObjPet::onLevelUp()
{
	recalAttr();
	FillHP();
	m_bAlive = true;
	// TODO����������
	setNeedSync();
	setNeedSyncSelf();
}

void CObjPet::AddTarget( const UnitHandle& target )
{
	if ( !AliveFlag() )
	{
		return;
	}
	if ( m_nState != PS_FIGHTING )
	{
		return;
	}

	if ( m_nFightState == PFS_AWAY_FROM_MAP )
	{
		return;
	}

	if ( m_target == target )
	{
		return;
	}

	UnitHandleList::iterator iter = m_lstTargets.begin();
	UnitHandleList::iterator eiter = m_lstTargets.end();
	for ( ; iter != eiter; ++iter )
	{
		const UnitHandle& unit = *iter;
		if ( unit == target )
		{
			return;
		}
	}
	m_lstTargets.push_back( target );
}

void CObjPet::RemoveTarget( const UnitHandle& target )
{
	if ( m_lstTargets.empty() )
	{
		return;
	}

	UnitHandleList::iterator iter = m_lstTargets.begin();
	UnitHandleList::iterator eiter = m_lstTargets.end();
	for ( ; iter != eiter; ++iter )
	{
		const UnitHandle& unit = *iter;
		if ( unit == target )
		{
			m_lstTargets.erase( iter );
			return;
		}
	}
}

void CObjPet::ClearTarget()
{
	m_target.clear();
	m_lstTargets.clear();
}

void CObjPet::ResetTargetTile( int32_t tx, int32_t ty, Direction dir )
{
	if ( NULL == m_pMap )
	{
		return;
	}
	if ( HasBuffState(CObjState::OBS_YUNXUAN) )
	{
		return;
	}
	if ( m_nFightState == PFS_STAND || m_nFightState == PFS_FOLLOW )
	{
		Position targetTile = getFollowTile( tx, ty, dir );
		if( m_pMap->isWalkablePosition( targetTile.x, targetTile.y ) )
		{
			setTargetTile( targetTile.x, targetTile.y );
		}
		else
		{
			setTargetTile( tx, ty );
		}
		broadcastMove();
		setFightState( PFS_FOLLOW );
	}
}

bool CObjPet::IsRegInFamily() const
{
	return m_nRegistFamily > 0;
}

void CObjPet::SetRegInFamily( FamilyId_t nFamilyId )
{
	m_nRegistFamily = nFamilyId;
}

void CObjPet::backToPlayer()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( HasBuffState(CObjState::OBS_YUNXUAN) )
	{
		return;
	}
	ClearTarget();
	setFightState( PFS_STAND );
	ResetTargetTile( m_pPlayer->getCurrentTile().x, m_pPlayer->getCurrentTile().y, m_pPlayer->getDirection() );
}

Position CObjPet::getFollowTile( int32_t tx, int32_t ty, Direction dir ) const
{
	Direction nDir = static_cast<Direction>( ( dir + m_nStandPlace ) % DIRECTION_NUM );
	switch ( nDir )
	{
	case DOWN:			return Position( tx,	ty+6 );
	case DOWN_LEFT:		return Position( tx-2,	ty+4 );
	case LEFT:			return Position( tx-3,	ty );
	case UP_LEFT:		return Position( tx-2,	ty-4 );
	case UP:			return Position( tx,	ty-6 );
	case UP_RIGHT:		return Position( tx+2,	ty-4 );
	case RIGHT:			return Position( tx+3,	ty );
	case DOWN_RIGHT:	return Position( tx+2,	ty+4 );
	default:			return Position( tx,	ty );
	}
}

void CObjPet::recalAttr()
{
	ResetAttrs();
	// �����������
	initBaseAttr();
	// ��������츳����
	addPassiveSkillAttr();
	// װ����ʯ����
	AddGemAttr();
	//������ʿ
	AddKnightAttr();
	if ( m_pPlayer != NULL )
	{
		m_pPlayer->GetCharInsidePet().AddAttrToTarget( this );
	}
	adjustUnitAttr();
	setNeedSync();
	setNeedSyncSelf();
}

void CObjPet::AddKnightAttr()
{
	if ( m_pPlayer == NULL )
	{
		return;
	}
	m_pPlayer->GetCharPet().AddKnightPetAttrToPet( this );
}

void CObjPet::AddGemAttr()
{
	if ( m_pPlayer == NULL )
	{
		return;
	}
	int32_t Dammage = m_pPlayer->GetEquip().GetGemAddEffectTypeRate( GEM_TYPE_DAMMAGE );
	int32_t Attack  = m_pPlayer->GetEquip().GetGemAddEffectTypeRate( GEM_TYPE_ATTACK );
	AddAttrValue(CObjAttrs::ATTR_DMG_ADD_PEC,Attack );
	AddAttrValue(CObjAttrs::ATTR_DMG_RDC_PEC,Dammage );
}

void CObjPet::SetMainPet( bool bFlg )
{
	m_bMainPet = bFlg;
}

void CObjPet::initBaseAttr()
{
	if ( NULL == m_pPet )
	{
		return;
	}

	int32_t nLevel = m_pPet->GetLevel();
	SetAttrValue( CObjAttrs::ATTR_HP,			calBaseAttr( PET_ATTR_START_HP,				PET_ATTR_GROW_HP,			nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_PHY_ATK_MIN,	calBaseAttr( PET_ATTR_START_PHY_ATK_MIN,	PET_ATTR_GROW_PHY_ATK_MIN,	nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_PHY_ATK_MAX,	calBaseAttr( PET_ATTR_START_PHY_ATK_MAX,	PET_ATTR_GROW_PHY_ATK_MAX,	nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_PHY_DEF,		calBaseAttr( PET_ATTR_START_PHY_DEF,		PET_ATTR_GROW_PHY_DEF,		nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_MAG_ATK_MIN,	calBaseAttr( PET_ATTR_START_MAG_ATK_MIN,	PET_ATTR_GROW_MAG_ATK_MIN,	nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_MAG_ATK_MAX,	calBaseAttr( PET_ATTR_START_MAG_ATK_MAX,	PET_ATTR_GROW_MAG_ATK_MAX,	nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_MAG_DEF,		calBaseAttr( PET_ATTR_START_MAG_DEF,		PET_ATTR_GROW_MAG_DEF,		nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_DODGE,		calBaseAttr( PET_ATTR_START_DODGE,			PET_ATTR_GROW_DODGE,		nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_HITRATE,		calBaseAttr( PET_ATTR_START_HITRATE,		PET_ATTR_GROW_HITRATE,		nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_CRITRATE,		calBaseAttr( PET_ATTR_START_CRITRATE,		PET_ATTR_GROW_CRITRATE,		nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_TENACITY,		calBaseAttr( PET_ATTR_START_TENACITY,		PET_ATTR_GROW_TENACITY,		nLevel ) );
	SetAttrValue( CObjAttrs::ATTR_LUCKY,m_pPet->GetLucky() );
}

int32_t CObjPet::calBaseAttr( PET_ATTR nStart, PET_ATTR nGrow, int32_t nLevel )
{
	int32_t nStartAttr = m_pPet->GetBaseAttr( nStart );
	int32_t nGrowAttr = m_pPet->GetBaseAttr( nGrow );
	return nStartAttr + nGrowAttr * ( nLevel - 1 ) / 1000;	// ������ֵ��ʵ����ֵ��1000��
}

int32_t CObjPet::GetBattleTianFuLevel()
{
	for ( int32_t i = 1; i < PET_SKILL_BAR_SIZE; ++i )
	{
		PetSkillInfo* pSkillInfo = m_pPet->GetSkillByPos( i );

		if ( pSkillInfo == NULL )
		{
			continue;
		}
		if ( pSkillInfo->nId == BATTLE_TIAN_FU )
		{
			return pSkillInfo->nLevel;
		}
	}
	return 0;
}

int32_t CObjPet::GetBattleTianFuBattle()
{
	int32_t Battle = 0;
	for ( int32_t i = 1; i < PET_SKILL_BAR_SIZE; ++i )
	{
		PetSkillInfo* pSkillInfo = m_pPet->GetSkillByPos( i );
		if ( pSkillInfo == NULL )
		{
			continue;
		}
		if ( pSkillInfo->nId == BATTLE_TIAN_FU )
		{
			CfgSkill *pCfgSkill = CFG_DATA.getSkill( BATTLE_TIAN_FU );
			if ( pCfgSkill != NULL && pCfgSkill->type == SK_PASSIVE && pCfgSkill->buff > 0 )
			{
				CfgBuff *pCfgBuff = CFG_DATA.getBuff( pCfgSkill->buff );
				if ( pCfgBuff != NULL )
				{
					for (int32_t i = 0; i < 2; ++i)
					{
						if ( static_cast<CObjAttrs::Index_T>(pCfgBuff->buffAttr[i].attr) == CObjAttrs::ATTR_BATTLE )
						{
							Battle += pCfgBuff->buffAttr[i].getAddon( pSkillInfo->nLevel );
						}
					}
				}
			}
		}
	}
	return Battle;
}

void CObjPet::addPassiveSkillAttr()
{
	if ( NULL == m_pPet )
	{
		return;
	}
	for ( int32_t i = 1; i < PET_SKILL_BAR_SIZE; ++i )
	{
		PetSkillInfo* pSkillInfo = m_pPet->GetSkillByPos( i );
		if ( pSkillInfo == NULL )
		{
			continue;
		}
		if ( pSkillInfo->nId  == BATTLE_TIAN_FU )	//ս�������������
		{
			continue;
		}
		if (  pSkillInfo->nId > 0 && pSkillInfo->nLevel > 0 )
		{
			CfgSkill *pCfgSkill = CFG_DATA.getSkill( pSkillInfo->nId );
			if ( pCfgSkill != NULL && pCfgSkill->type == SK_PASSIVE && pCfgSkill->buff > 0 )
			{
				CfgBuff *pCfgBuff = CFG_DATA.getBuff( pCfgSkill->buff );
				if ( pCfgBuff != NULL )
				{
					for (int32_t i = 0; i < 2; ++i)
					{
						if ( pCfgBuff->buffAttr[i].attr > 0 )
						{
							AddAttrValue( static_cast<CObjAttrs::Index_T>( pCfgBuff->buffAttr[i].attr ), pCfgBuff->buffAttr[i].getAddon( pSkillInfo->nLevel ) );
						}
					}
				}
			}
		}
	}
}

bool CObjPet::CheckRecord( PET_RECORD record ) const
{
	if ( NULL == m_pPet )
	{
		return false;
	}
	return m_pPet->CheckRecord( record );
}

int32_t CObjPet::AddRecord( PET_RECORD record, int32_t nAddVal )
{
	if ( NULL == m_pPet )
	{
		return false;
	}
	return m_pPet->AddRecord( record, nAddVal );
}

PET_PHASE CObjPet::ChangePhase( PET_PHASE phase )
{
	if ( NULL == m_pPet )
	{
		return PP_INVALID;
	}

	PET_PHASE finalPhase = m_pPet->ChangePhase( phase );
	if ( finalPhase == PP_ELECTRIC || finalPhase == PP_GOLD )
	{
		recalAttr();

		// ���ӹ���
		broadcastPetPhase( finalPhase );
	}
	return finalPhase;
}

int32_t CObjPet::GetBaseAttr( PET_ATTR attr ) const
{
	if ( NULL == m_pPet )
	{
		return 0;
	}
	return m_pPet->GetBaseAttr( attr );
}

bool CObjPet::CanIllusion( CObjPet* pPet, int8_t nType )
{
	if ( NULL == pPet )
	{
		return false;
	}
	return m_pPet->CanIllusion( pPet->GetPet(), nType );
}

int32_t	CObjPet::GetGrowPoints()
{
	if ( NULL == m_pPet )
	{
		return 0;
	}
	return m_pPet->GetGrowPoints();
}

bool CObjPet::growAttrIllusionByItem( int8_t	nUseItem )
{
	if ( NULL == m_pPet )
	{
		return false;
	}
	if ( !m_pPet->growAttrIllusionByItem( nUseItem ) )
	{
		return false;
	}
	int32_t nSkillId = m_pPet->RandSkill();
	if ( nSkillId > 0 )
	{
		sendPetLearnSkill( nSkillId );
		broadcastPetLearnSkill( nSkillId );
	}
	recalAttr();
	return true;
}

bool CObjPet::IsXXoo()
{
	if ( NULL == m_pPet )
	{
		return false;
	}
	return m_pPet->IsXOType();
}

bool CObjPet::Illusion( CObjPet* pPet, int8_t nType, int8_t nUseItem )
{
	if ( NULL == pPet || NULL == m_pPlayer )
	{
		return false;
	}

	if ( !m_pPet->Illusion( pPet->GetPet(), nType, nUseItem ) )
	{
		return false;
	}

	int32_t nSkillId = m_pPet->RandSkill();
	if ( nSkillId > 0 )
	{
		sendPetLearnSkill( nSkillId );
		broadcastPetLearnSkill( nSkillId );
	}

	recalAttr();
	return true;
}

void CObjPet::sendPetLearnSkill( int32_t nSkill )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_LEARN_NEW_SKILL );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt64( m_pPet->GetPetId() );
	packet->writeInt32( nSkill );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CObjPet::broadcastPetPhase( PET_PHASE phase )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PET_BROADCASE );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( PBCT_PHASE );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt32( m_pPet->GetBaseId() );
	packet->writeUTF8( m_pPet->GetName() );
	packet->writeInt64( m_pPet->GetPetId() );
	packet->writeInt8( phase );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast(packet);
}

void CObjPet::broadcastPetLearnSkill( int16_t nSkillId )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PET_BROADCASE );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( PBCT_LEARN_SKILL );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt32( m_pPet->GetBaseId() );
	packet->writeUTF8( m_pPet->GetName() );
	packet->writeInt64( m_pPet->GetPetId() );
	packet->writeInt16( nSkillId );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CObjPet::broadcastPetSkillLevelUp( int16_t nSkillId, int16_t nSkillLevel )
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PET_BROADCASE );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( PBCT_SKILL_LEVEL_UP );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt32( m_pPet->GetBaseId() );
	packet->writeUTF8( m_pPet->GetName() );
	packet->writeInt64( m_pPet->GetPetId() );
	packet->writeInt16( nSkillId );
	packet->writeInt16( nSkillLevel );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}


bool CObjPet::UseLuckyItem()
{
	if ( NULL == m_pPet )
	{
		return false;
	}
	return m_pPet->UseLuckyItem();
}

void CObjPet::OnLoadFromDB( const DBPet& pet )
{
	m_pPet			= PET_MANAGER.GetPet( pet.nPetId );
	m_bAlive		= pet.bAlive > 0;
	m_nSoul			= pet.nSoul;
	m_nState		= static_cast<PET_STATE>( pet.nState );	
	m_nBagType		= pet.nBag;
	m_nKnight		= pet.nKnight;
	m_nQiShi		= pet.nQiShi;
	m_nRegistFamily	= pet.nFamilyId;
	recalAttr();
	setHP( pet.nHP );
}

void CObjPet::OnSaveToDB( DBPet& pet )
{
	if ( NULL == m_pPet )
	{
		return;
	}
	pet.nPetId		= m_pPet->GetPetId();
	pet.bAlive		= m_bAlive ? 1 : 0;
	pet.nSoul		= m_nSoul;
	pet.nState		= m_nState;
	pet.nHP			= GetHP();
	pet.nBag		= m_nBagType;
	pet.nKnight		= m_nKnight;
	pet.nFamilyId	= m_nRegistFamily;
	pet.nQiShi		= m_nQiShi;
}

void CObjPet::updateFightState()
{
	checkFarAway();
	switch( m_nFightState )
	{
	case PFS_STAND:			onStand();		break;
	case PFS_FOLLOW:		onFollow();		break;
	case PFS_ATTACK:		onAttack();		break;
	case PFS_WALK_ATTACK:	onWalkAttack();	break;
	default: break;
	}
}

void CObjPet::setFightState( PET_FIGHT_STATE state )
{
	m_nFightState = state;
	switch( m_nFightState )
	{
	case PFS_AWAY_FROM_MAP:	break;
	case PFS_STAND:			setStand();	break;
	case PFS_FOLLOW:		break;
	case PFS_ATTACK:		setStand(); break;
	case PFS_WALK_ATTACK:	break;
	default:break;
	}
}

void CObjPet::onStand()
{
	if ( NULL == m_pPlayer || NULL == m_pMap )
	{
		return;
	}

	if ( !AliveFlag() )
	{
		return;
	}

	if ( !m_lstTargets.empty() )
	{
		changeTarget();
	}
}

void CObjPet::onFollow()
{
	if ( NULL == m_pPlayer || NULL == m_pMap )
	{
		return;
	}

	if ( getCurrentTile() == getTargetTile() )
	{
		setFightState( PFS_STAND );
	}
}

void CObjPet::onAttack()
{
	int64_t nCurTick = getTick();
	if ( nCurTick - m_nLastSkillTick < SKILL_PUBLIC_CD )
	{
		return;		// ����CD
	}

	if ( NULL == m_pPlayer || NULL == m_pMap )
	{
		backToPlayer();
		return;
	}

	if ( m_target.isEmpty() )
	{
		changeTarget();
		return;
	}

	Unit *pTarget = GAME_SERVICE.getUnit( m_target.id, m_target.type, GetRunnerId() );
	if ( NULL == pTarget )
	{
		changeTarget();
		return;
	}

	if ( pTarget->getMap() != m_pMap )
	{
		changeTarget();
		return;
	}

	if ( !pTarget->isAlive() )
	{
		changeTarget();
		return;
	}

	if ( HasBuffState( CObjState::OBS_BINGDONG ) || HasBuffState( CObjState::OBS_YUNXUAN ) )
	{
		return;
	}

	if ( NULL == m_pNextSkill )
	{
		if ( m_pPet->GetPetJob() == PET_JOB_ZHANSHI )
		{
			int32_t nRand = RANDOM.generate( 0, 1000 );
			if ( nRand < 80 )
			{
				m_pNextSkill = m_pPet->GetSkillByPos( 1 );
			}
			else
			{
				m_pNextSkill = m_pPet->GetSkillByPos( 0 );
			}
		}
		else if ( m_pPet->GetPetJob() == PET_JOB_FASHI )
		{
			if ( m_bMainPet )
			{
				m_pNextSkill = m_pPet->GetSkillByPos( 1 );
			}
			else
			{
				m_pNextSkill = m_pPet->GetSkillByPos( 0 );
			}
		}
	}

	if ( NULL == m_pNextSkill )
	{
		backToPlayer();
		return;
	}

	CfgSkill* pCfgSkill = CFG_DATA.getSkill( m_pNextSkill->nId );
	if ( NULL == pCfgSkill )
	{
		backToPlayer();
		return;
	}

	int32_t tileDistance = getCurrentTile().tileDistance( pTarget->getCurrentTile() );
	if ( tileDistance > pCfgSkill->distance )
	{
		setFightState( PFS_WALK_ATTACK );
		return;
	}

	if ( nCurTick - m_pNextSkill->nCDTime < pCfgSkill->cd )
	{
		// ����CD��
		return;
	}

	Skill skill( m_pNextSkill->nId, m_pNextSkill->nLevel );
	int32_t attackValue = 0;
	switch( pCfgSkill->range )
	{
	case SR_SELF:
		{
			skill.unitAction( *this, getHandle(), attackValue );
		}
		break;
	case SR_SOLO:
		{
			// ��⼼���Ƿ���Զ�Ŀ��ʩ��
			if (!checkSkillTarget(pCfgSkill, pTarget))
			{
				changeTarget();
				return;
			}
			skill.unitAction( *this, m_target, attackValue );
			if ( !pCfgSkill->beneficial && m_target.type == ET_PLAYER )
			{
				Player *victm = static_cast<Player*>( pTarget );
				if (victm != NULL)
				{
					victm->onDamagedEvent( getHandle(), attackValue );
				}
			}
		}
		break;
	default:
		{
			if ( !checkSkillTarget(pCfgSkill, pTarget ) )
			{
				changeTarget();
				return;
			}
			Position pos = pTarget->getCurrentTile();
			if ( pCfgSkill->range == SR_HALF_ROUND || pCfgSkill->range == SR_LINE )
			{
				resetDirection( pos.x, pos.y );
			}
			UnitVector targets = m_pMap->getSkillTargets( *this, pos, pCfgSkill );;

			EntityIdInt32Map attackValues;
			skill.posAction(*this, pos, targets, attackValues);
			if (!pCfgSkill->beneficial)
			{
				for (UnitVector::iterator it = targets.begin(); it != targets.end(); ++it)
				{
					Unit *target = *it;
					if ( target != NULL && target->getType() == ET_PLAYER && checkSkillTarget(pCfgSkill, target) )
					{
						Player *victm = GAME_SERVICE.getPlayer( target->getUnitId(), GetRunnerId() );
						if (victm != NULL)
						{
							victm->onDamagedEvent( getHandle(), attackValues[target->getUnitId()] );
						}
					}
				}
			}
		}
		break;
	}

	m_pNextSkill->nCDTime	= nCurTick;
	m_nLastSkillTick		= nCurTick;
	m_pNextSkill			= NULL;			// ��Ϊ�գ��´��������
}

void CObjPet::onWalkAttack()
{
	if ( NULL == m_pPlayer || NULL == m_pMap || NULL == m_pPet )
	{
		backToPlayer();
		return;
	}

	if ( m_target.isEmpty() )
	{
		changeTarget();
		return;
	}

	Unit *pTarget = GAME_SERVICE.getUnit( m_target.id, m_target.type, GetRunnerId() );
	if ( NULL == pTarget )
	{
		changeTarget();
		return;
	}

	if ( !pTarget->isAlive() )
	{
		changeTarget();
		return;
	}

	if ( pTarget->getMap() != m_pMap )
	{
		changeTarget();
		return;
	}

	PetSkillInfo* pSkillInfo = m_pPet->GetSkillByPos( 0 );
	if ( NULL == pSkillInfo )
	{
		backToPlayer();
		return;
	}

	CfgSkill* pSkill = CFG_DATA.getSkill( pSkillInfo->nId );
	if ( NULL == pSkill )
	{
		backToPlayer();
		return;
	}

	if ( getCurrentTile().tileDistance( pTarget->getCurrentTile() ) <= pSkill->distance )
	{
		setFightState( PFS_ATTACK );
		return;
	}

	if ( !isMoving() )
	{
		Position pos = Map::getAroundTile( pTarget->getCurrentTile().x, pTarget->getCurrentTile().y, static_cast<Direction>( RANDOM.generate( DOWN, DOWN_LEFT ) ) );
		if ( m_pMap->isWalkablePosition( pos.x, pos.y ) )
		{
			Position targetPos = m_pMap->firstLinePosition( getCurrentTile(), pos );
			if ( targetPos.x == -1 || targetPos.y == -1 )
			{
				backToPlayer();
				return;
			}
			setTargetTile(targetPos.x, targetPos.y);
			broadcastMove();
		}
	}
}

void CObjPet::changeTarget()
{
	if ( m_lstTargets.empty() )
	{
		backToPlayer();
		return;
	}

	m_target = m_lstTargets.front();
	m_lstTargets.pop_front();
	if ( m_target.isEmpty() )
	{
		return;
	}

	setFightState( PFS_WALK_ATTACK );
}

void CObjPet::checkFarAway()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( HasBuffState(CObjState::OBS_YUNXUAN) )
	{
		return;
	}
	if ( getCurrentTile().tileDistance( m_pPlayer->getCurrentTile() ) > 10 )
	{
		ClearTarget();
		Position targetTile = getFollowTile( m_pPlayer->getCurrentTile().x, m_pPlayer->getCurrentTile().y, m_pPlayer->getDirection() );
		instantMove( targetTile.x, targetTile.y, IMR_TRANSFER );
		setFightState( PFS_STAND );
		if ( m_pPlayer->isMoving() )
		{
			ResetTargetTile( m_pPlayer->getTargetTile().x, m_pPlayer->getTargetTile().y, m_pPlayer->getDirection() );
		}
	}
}

void CObjPet::checkSpeed()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( GetMoveSpeed() != m_pPlayer->GetMoveSpeed() )
	{
		SetAttrValue( CObjAttrs::ATTR_MOVE_SPEED, m_pPlayer->GetMoveSpeed() );
		setNeedSync();
	}
}

int32_t CObjPet::calAddBattle( int32_t nIndex ) const
{
	if ( nIndex <= 0 )
	{
		return 0;
	}
	if ( nIndex == 1 )
	{
		return 20;
	}
	else if ( nIndex == 2 )
	{
		return 19;
	}
	else if ( nIndex == 3 )
	{
		return 18;
	}
	else if ( nIndex <= 10 )
	{
		return 15;
	}
	else if ( nIndex <= 20 )
	{
		return 13;
	}
	else if ( nIndex <= 50 )
	{
		return 12;
	}
	else if ( nIndex <= 80 )
	{
		return 10;
	}
	else if ( nIndex <= 90 )
	{
		return 8;
	}
	else if ( nIndex <= 100 )
	{
		return 5;
	}
	else
	{
		return 0;
	}
}

int32_t	CObjPet::GetRankIndex( PET_RANK_TYPE Type )
{
	if ( NULL == m_pPet )
	{
		return 0;
	}
	return m_pPet->GetRankIndex( Type );
}

int32_t CObjPet::GetTopRankIndex() const
{
	if ( NULL == m_pPet )
	{
		return 0;
	}
	int32_t nIndex = 0;
	for ( int8_t i = PRT_POINTS; i <= PRT_GROW_MAG_DEF; ++i  )
	{
		int32_t tri = m_pPet->GetRankIndex( static_cast<PET_RANK_TYPE>( i ) );
		if ( tri == 0 )
		{
			continue;
		}
		if ( nIndex == 0 )
		{
			nIndex = tri;
			continue;
		}
		if ( tri < nIndex )
		{
			nIndex = tri;
		}
	}

	return nIndex;
}

void CObjPet::RecalAttr()
{
	recalAttr();
}

int8_t CObjPet::GetQiShi() const
{
	return m_nQiShi;
}

void CObjPet::SetQiShi( int8_t Pos )
{
	m_nQiShi = Pos;
}
// ========== 新版本添加方法 ==========

void CObjPet::UpStar()
{
	if ( m_pPet != NULL )
	{
		m_nStar++;
	}
}

void CObjPet::SetFitting( bool bFitting )
{
	if ( bFitting )
	{
		m_nFitting = 1;
	}
	else
	{
		m_nFitting = 0;
	}
}

bool CObjPet::IsFitting() const
{
	return m_nFitting != 0;
}

void CObjPet::ChangeAi( int8_t nAiState )
{
	if ( m_AiState != nAiState )
	{
		m_AiState = nAiState;
		if ( m_AiState == 1 )
		{
			ClearTarget();
		}
	}
}

int32_t CObjPet::GetEquip( int32_t nSlot ) const
{
	if ( nSlot < 0 || nSlot >= MAX_PET_EQUIP_SLOT )
	{
		return 0;
	}
	return m_vEquip[nSlot];
}

void CObjPet::SetEquip( int32_t nSlot, int32_t nEquipId )
{
	if ( nSlot < 0 || nSlot >= MAX_PET_EQUIP_SLOT )
	{
		return;
	}
	m_vEquip[nSlot] = nEquipId;
	CObjPet::recalAttr();
}

void CObjPet::CheckSkillOpen()
{
	if ( m_pPet == NULL )
	{
		return;
	}
	const CfgPetUpStar* pCfgUpStar = CFG_DATA.GetPetTable().GetPetUpStar( GetStar() );
	if ( NULL == pCfgUpStar )
	{
		return;
	}
	uint32_t nSkillSize = static_cast<uint32_t>( pCfgUpStar->vSkillLevel.size() );
	for ( int32_t i = 0; i < MAX_PET_SKILL_SLOT; ++i )
	{
		if ( static_cast<uint32_t>(i) >= nSkillSize )
		{
			m_vSkill[i].nLevel = 0;
		}
		else
		{
			m_vSkill[i].nLevel = pCfgUpStar->vSkillLevel[i];
		}
	}
}

int32_t CObjPet::GetSkillMaxLevel( int8_t nSkillPos ) const
{
	if ( nSkillPos < 0 || nSkillPos >= MAX_PET_SKILL_SLOT )
	{
		return 0;
	}
	// Check star config for max skill level
	const CfgPetUpStar* pCfgUpStar = CFG_DATA.GetPetTable().GetPetUpStar( GetStar() );
	if ( NULL != pCfgUpStar && nSkillPos < static_cast<int32_t>(pCfgUpStar->vSkillLevel.size()) )
	{
		return pCfgUpStar->vSkillLevel[nSkillPos];
	}
	return MAX_SKILL_LEVEL;
}

void CObjPet::OnLevelUp()
{
	recalAttr();
	if ( m_bAlive )
	{
		AddHP( 100 );
	}
	setNeedSync();
}

int32_t CObjPet::GetStar() const
{
    return m_nStar;
}
