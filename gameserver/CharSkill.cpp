
#include <algorithm>

#include "stdafx.h"
#include "CharSkill.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "DBService.h"
#include "PDUDefine.h"
#include "GameLogs.h"
#include "CharCarrier.h"
#include "CharPet.h"
#include "CharTeam.h"
#include "OperateLimit.h"
#include "Skill.h"
#include "ItemHelper.h"

using namespace Answer;


CExtCharSkill::CExtCharSkill()
{
	OnCleanUp();
}

CExtCharSkill::~CExtCharSkill()
{
}

void CExtCharSkill::OnCleanUp()
{
	m_bXP = false;
	m_nXP = 0;
	m_nSelectXP = 0;
	m_nXPAddExp = 0;
	m_nLastTick = 0;
	m_nStartTick = 0;

	m_SkillLevelMap.clear();
	m_lAddonSkills.clear();
	m_lSummonSkills.clear();
	m_lActiveTalent.clear();
	m_lActiveSkills.clear();
	m_lPassiveSkills.clear();
	m_lTrigSkills.clear();
	m_mActiveSkills.clear();
	m_OthreSkillLevelMap.clear();
	m_mSkillCD.clear();
	m_nPower = 0;
	m_nDropMoneyRate = 0;
	m_SkillBattle = 0;
	m_SkillPublicCD = 0;
	m_nLastAddonTick = 0;
	m_PowerLastTick = 0;
	m_lastActionTick = 0;
	m_nLastEnergyTick = 0;
	m_nSuitSkillEnergy = 0;
}

void CExtCharSkill::OnLoadFromDB( const PlayerDBData& dbData )
{
	loadTalentPoints( dbData.skillData.talents );
	m_nPower = dbData.skillData.m_nPower;
	for ( auto it = m_SkillLevelMap.begin(); it != m_SkillLevelMap.end(); ++it )
	{
		initSkills( it->first, it->second.Level );
	}
	CallSkillBattle();
}

void CExtCharSkill::OnSaveToDB( PlayerDBData& dbData )
{
	std::string strTalent = saveTalentPoints();
	dbData.skillData.talents = strTalent;
	dbData.skillData.m_nPower = m_nPower;
}

void CExtCharSkill::OnUpdate( int64_t curTick )
{
	checkAddonSkills( curTick );
	checkSummonSkills( curTick );
	checkSuitSkillEnergy( curTick );
	checkActiveList();
	if ( curTick - m_PowerLastTick > 59999 )
	{
		m_PowerLastTick = curTick;
		AddPower( 60 );
	}
	checkXP( curTick );
}

void CExtCharSkill::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_START_XP );		// 111
	procList.push_back( 40 );				// onDoUnitSkill
	procList.push_back( 38 );				// onDoAddonSkill
	procList.push_back( 37 );				// SendTalentInfo
}

int32_t CExtCharSkill::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( !inPacket )
		return ERR_SYETEM_ERR;

	if ( nProcId == 40 )
		return onDoUnitSkill( inPacket );
	if ( nProcId == 111 )
		return onAddTalentPoint( inPacket );
	if ( nProcId == 37 )
	{
		SendTalentInfo();
		return ERR_OK;
	}
	if ( nProcId == 38 )
		return onDoAddonSkill( inPacket );

	return ERR_OK;
}

// ==================== XP系统 ====================

int32_t CExtCharSkill::onStartXP( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
		return ERR_SYETEM_ERR;

	SkillId_t nSkillId = inPacket->readInt32();

	if ( !IsLearnedXPSkill() )
		return ERR_SYETEM_ERR;

	startXP( nSkillId );
	return ERR_OK;
}

int32_t CExtCharSkill::onSocialUpdateXP( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
		return ERR_SYETEM_ERR;

	CharId_t nCid = inPacket->readInt64();
	SkillId_t nSkillId = inPacket->readInt32();
	int32_t nFlag = inPacket->readInt32();

	if ( nFlag == 1 )
	{
		m_nSelectXP = nSkillId;
		sendSocialStartXP();
	}
	else
	{
		m_nSelectXP = 0;
		sendSocialEndXP();
	}
	return ERR_OK;
}

int32_t CExtCharSkill::onSocialAddExp( Answer::NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
		return ERR_SYETEM_ERR;

	int32_t nExp = inPacket->readInt32();
	AddPlayerExp( nExp );
	return ERR_OK;
}

void CExtCharSkill::AddPlayerExp( int32_t Exp )
{
	if ( NULL == m_pPlayer )
		return;

	m_nXPAddExp += Exp;
	if ( m_nXPAddExp < 0 )
		m_nXPAddExp = 0;

	SendXpRecord();
}

bool CExtCharSkill::IsInXP() const
{
	return m_bXP;
}

SkillId_t CExtCharSkill::GetSelectedXP() const
{
	return m_nSelectXP;
}

void CExtCharSkill::AddMonsterExp( int64_t nAddExp )
{
	if ( NULL == m_pPlayer )
		return;

	if ( !IsInXP() )
		return;

	m_nXPAddExp += nAddExp;
	if ( m_nXPAddExp < 0 )
		m_nXPAddExp = 0;

	SendXpRecord();
}

void CExtCharSkill::SendXpRecord()
{
	if ( NULL == m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x2CD9 );
	if ( !packet )
		return;

	packet->writeInt32( m_nXP );
	packet->writeInt64( m_nXPAddExp );
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int16_t gateIndex = m_pPlayer->getGateIndex();
	pService->sendPacketTo( connid, gateIndex, packet );
}

void CExtCharSkill::FillXP()
{
	if ( NULL == m_pPlayer )
		return;

	m_nXPAddExp = 10000;
	SendXpRecord();
}

void CExtCharSkill::LearnXPSkill()
{
	if ( NULL == m_pPlayer )
		return;

	m_bXP = true;
	sendSocialAddXP();
}

void CExtCharSkill::checkXP( int64_t curTick )
{
	if ( NULL == m_pPlayer )
		return;

	if ( !IsInXP() )
		return;

	m_nLastTick = curTick;

	if ( curTick - m_nStartTick > XP_TIME )
	{
		endXP();
	}
}

void CExtCharSkill::endXP()
{
	m_bXP = false;
	m_nSelectXP = 0;
	m_nXPAddExp = 0;
	sendSocialEndXP();
}

void CExtCharSkill::DieResetXp()
{
	m_bXP = false;
	m_nSelectXP = 0;
	m_nXPAddExp = 0;
	m_nLastTick = 0;
	m_nStartTick = 0;
}

void CExtCharSkill::ClearXP()
{
	m_bXP = false;
	m_nSelectXP = 0;
	m_nXPAddExp = 0;
}

bool CExtCharSkill::IsLearnedXPSkill() const
{
	if ( NULL == m_pPlayer )
		return false;

	return m_bXP;
}

void CExtCharSkill::sendXP()
{
	if ( NULL == m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x2CDA );
	if ( !packet )
		return;

	packet->writeInt32( m_nXP );
	packet->writeInt64( m_nXPAddExp );
	packet->writeInt32( m_nSelectXP );
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int16_t gateIndex = m_pPlayer->getGateIndex();
	pService->sendPacketTo( connid, gateIndex, packet );
}

void CExtCharSkill::sendSocialAddXP( int32_t AddXp )
{
	if ( NULL == m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x2CDA );
	if ( !packet )
		return;

	packet->writeInt32( AddXp );
	CharId_t cid = m_pPlayer->getCid();
	packet->writeInt64( cid );
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int8_t bConnId = m_pPlayer->getConnId();
	pService->worldBroadcast( bConnId, packet );
}

void CExtCharSkill::sendSocialStartXP()
{
	if ( NULL == m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x2CDB );
	if ( !packet )
		return;

	CharId_t cid = m_pPlayer->getCid();
	packet->writeInt64( cid );
	packet->writeInt32( m_nSelectXP );
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int8_t bConnId = m_pPlayer->getConnId();
	pService->worldBroadcast( bConnId, packet );
}

void CExtCharSkill::sendSocialEndXP()
{
	if ( NULL == m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x2CDC );
	if ( !packet )
		return;

	CharId_t cid = m_pPlayer->getCid();
	packet->writeInt64( cid );
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int8_t bConnId = m_pPlayer->getConnId();
	pService->worldBroadcast( bConnId, packet );
}

void CExtCharSkill::sendSocialBreakXP()
{
	if ( NULL == m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x2CDD );
	if ( !packet )
		return;

	CharId_t cid = m_pPlayer->getCid();
	packet->writeInt64( cid );
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int8_t bConnId = m_pPlayer->getConnId();
	pService->worldBroadcast( bConnId, packet );
}

void CExtCharSkill::SetInXP( bool bFlg )
{
	m_bXP = bFlg;
}

void CExtCharSkill::startXP( SkillId_t nSkillId )
{
	if ( NULL == m_pPlayer )
		return;

	m_bXP = true;
	m_nSelectXP = nSkillId;
	m_nStartTick = m_pPlayer->getTick();
	m_nLastTick = m_nStartTick;
	sendSocialStartXP();
}

// ==================== 2019核心方法 ====================

void CExtCharSkill::InitSystem()
{
	if ( m_pPlayer && m_pPlayer->getLastLogoutTime() > 0 )
	{
		int32_t Now = m_pPlayer->getNow();
		int32_t AddCount = (Now - m_pPlayer->getLastLogoutTime()) / 60;
		if ( AddCount > 0 )
			AddPower( 60 * AddCount );
		m_PowerLastTick = m_pPlayer->getTick();
	}
}

void CExtCharSkill::initSkills( int32_t TalentId, int32_t TalentLevel )
{
	if ( !m_pPlayer )
		return;

	const CfgTalent* pCfg = Singleton<CfgData>::instance()->GetTalentTable()->GetTalent( TalentId, TalentLevel );
	if ( !pCfg )
		return;

	int32_t skillid = pCfg->skillid;
	int8_t SkillType = Singleton<CfgData>::instance()->GetSkillTable()->GetSkillType( skillid );
	if ( SkillType == 2 )
	{
		m_lPassiveSkills.push_back( skillid );
	}
	else if ( SkillType == 3 )
	{
		m_lTrigSkills.push_back( skillid );
	}
	else if ( SkillType == 1 )
	{
		m_lActiveSkills.push_back( skillid );
	}
}

void CExtCharSkill::AddCharAttr()
{
	if ( !m_pPlayer )
		return;

	for ( auto it = m_lPassiveSkills.begin(); it != m_lPassiveSkills.end(); ++it )
	{
		const CfgPassiveSkill* pCfgSkill = Singleton<CfgData>::instance()->GetSkillTable()->GetPassiveSkill( *it );
		if ( pCfgSkill )
		{
			for ( auto& attr : pCfgSkill->vAttrs )
			{
				m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)attr.index, attr.addon );
			}
		}
	}
}

int32_t CExtCharSkill::CallSkillBattle()
{
	m_SkillBattle = 0;
	for ( auto it = m_lActiveSkills.begin(); it != m_lActiveSkills.end(); ++it )
	{
		const CfgActiveSkill* pCfg = Singleton<CfgData>::instance()->GetSkillTable()->GetActiveSkill( *it );
		if ( pCfg && pCfg->kind == 2 )
			++m_SkillBattle;
	}
	return m_SkillBattle;
}

int32_t CExtCharSkill::GetPower()
{
	return m_nPower;
}

int32_t CExtCharSkill::AddPower( int32_t nValue )
{
	m_nPower += nValue;
	return m_nPower;
}

int32_t CExtCharSkill::GetDropMoneyRate()
{
	return m_nDropMoneyRate;
}

void CExtCharSkill::recalDropMoneyRate()
{
	m_nDropMoneyRate = 0;
	for ( auto it = m_lPassiveSkills.begin(); it != m_lPassiveSkills.end(); ++it )
	{
		const CfgPassiveSkill* pCfg = Singleton<CfgData>::instance()->GetSkillTable()->GetPassiveSkill( *it );
		if ( pCfg && pCfg->type == 1 )
		{
			for ( auto& attr : pCfg->vAttrs )
			{
				if ( attr.index == CObjAttrs::INDEX_DROP_MONEY_RATE )
				{
					m_nDropMoneyRate += attr.addon;
				}
			}
		}
	}
}

bool CExtCharSkill::CanUseSkillAndMove( int64_t nCurTick, bool ResetTick )
{
	int32_t nPublicCd = calActiveSkillCD( 0 );
	if ( !ResetTick )
		nPublicCd /= 8;
	if ( nPublicCd > nCurTick - m_SkillPublicCD )
		return false;
	if ( ResetTick )
		m_SkillPublicCD = nCurTick;
	return true;
}

void CExtCharSkill::addSkillBuffTo( SkillId_t nSkillId, int32_t nGroupId, Unit* pTarget )
{
	if ( !m_pPlayer || !pTarget )
		return;

	const CfgActiveSkill* pCfgSkill = getActiveSkill( nSkillId );
	if ( !pCfgSkill )
		return;

	// 获取buff配置
	CfgBuff* pCfgBuff = CFG_DATA.getBuff( pCfgSkill->trigBuff );
	if ( !pCfgBuff )
		return;

	// 检查无敌和自由状态
	if ( !pCfgBuff->beneficial && pTarget->HasBuffState( OBS_WUDI ) )
		return;
	if ( pCfgBuff->control && pTarget->HasBuffState( OBS_FREEDOM ) )
		return;

	// 获取攻击者属性
	int32_t atkMin = m_pPlayer->GetAttrValue( ATTR_ATK_MIN );
	int32_t atkMax = m_pPlayer->GetAttrValue( ATTR_ATK_MAX );
	int32_t dmgAdd = m_pPlayer->GetAttrValue( ATTR_DMG_ADD_PEC );
	int32_t skillModify = pCfgBuff->modify;

	// 创建技能buff
	UnitHandle launcher;
	launcher.id = m_pPlayer->getUnitId();
	launcher.type = m_pPlayer->getType();

	SkillBuff* buff = new SkillBuff( pTarget, pCfgBuff, &launcher );
	if ( buff )
	{
		buff->init( nSkillId, atkMin, atkMax, 0, dmgAdd, skillModify, 0 );
		pTarget->addBuff( buff );

		// 特殊效果：持续伤害buff
		if ( buff->getSpecial() == 9 )
		{
			broadcastIntervalEffect( nSkillId );
		}
	}
}

void CExtCharSkill::broadcastIntervalEffect( int32_t nSkillId )
{
	if ( !m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x2CE0 );
	if ( !packet )
		return;

	packet->writeInt32( nSkillId );
	CharId_t cid = m_pPlayer->getCid();
	packet->writeInt64( cid );
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int16_t gateIndex = m_pPlayer->getGateIndex();
	pService->sendPacketTo( connid, gateIndex, packet );
}

int32_t CExtCharSkill::calActiveSkillCD( int32_t nSkillId )
{
	int32_t nCD = 0;
	for ( auto it = m_lActiveSkills.begin(); it != m_lActiveSkills.end(); ++it )
	{
		const CfgActiveSkill* pCfg = Singleton<CfgData>::instance()->GetSkillTable()->GetActiveSkill( *it );
		if ( pCfg )
		{
			if ( nSkillId == 0 || pCfg->id == nSkillId )
			{
				if ( pCfg->cd > nCD )
					nCD = pCfg->cd;
			}
		}
	}
	return nCD;
}

void CExtCharSkill::checkActiveList()
{
	// 清理无效的主动技能
	for ( auto it = m_lActiveSkills.begin(); it != m_lActiveSkills.end(); )
	{
		const CfgActiveSkill* pCfg = Singleton<CfgData>::instance()->GetSkillTable()->GetActiveSkill( *it );
		if ( !pCfg )
			it = m_lActiveSkills.erase( it );
		else
			++it;
	}
}

void CExtCharSkill::recalAcviveSkill()
{
	m_mActiveSkills.clear();
	m_lActiveSkills.clear();

	for ( auto it = m_SkillLevelMap.begin(); it != m_SkillLevelMap.end(); ++it )
	{
		const CfgTalent* pCfg = Singleton<CfgData>::instance()->GetTalentTable()->GetTalent( it->first, it->second.Level );
		if ( pCfg )
		{
			int8_t SkillType = Singleton<CfgData>::instance()->GetSkillTable()->GetSkillType( pCfg->skillid );
			if ( SkillType == 1 )
			{
				const CfgActiveSkill* pActiveSkill = Singleton<CfgData>::instance()->GetSkillTable()->GetActiveSkill( pCfg->skillid );
				if ( pActiveSkill )
				{
					m_mActiveSkills[pActiveSkill->id] = *pActiveSkill;
					m_lActiveSkills.push_back( pActiveSkill->id );
				}
			}
		}
	}
}

int32_t CExtCharSkill::doSkill( Answer::NetPacket* inPacket, const CfgActiveSkill* pCfgSkill,
	SkillResultVector* results, Position srcPos, int32_t nSkillId, int32_t nSkillFlag, bool bAction )
{
	if ( !m_pPlayer || !inPacket || !pCfgSkill )
		return 10002;

	Map* pMap = m_pPlayer->getMap();
	if ( !pMap )
		return 10002;

	Skill skill( pCfgSkill, nSkillFlag );
	Position pos = srcPos;

	if ( pCfgSkill->range == 1 )
	{
		// 单体目标
		UnitHandle target;
		target.id = inPacket->readInt64();
		target.type = inPacket->readInt32();

		if ( (pCfgSkill->attack_type == 7 || pCfgSkill->attack_type == 8) && target.type != 2 )
			return 10002;

		int32_t RunnerId = m_pPlayer->GetRunnerId();
		Unit* pTarget = Singleton<GameService>::instance()->getUnit( target.id, target.type, RunnerId );
		if ( !pTarget || pTarget->getMap() != pMap )
			return 10007;

		pos.x = inPacket->readInt32();
		pos.y = inPacket->readInt32();

		if ( !m_pPlayer->canAttackTarget( pCfgSkill, pTarget ) )
			return 10002;

		if ( skill.unitAction( m_pPlayer, target, results, pos, bAction ) < 0 )
			return 10002;
	}
	else if ( pCfgSkill->range == 10 )
	{
		// 组队技能
		CharIdList members;
		CExtCharTeam* pTeam = m_pPlayer->GetCharTeam();
		if ( pTeam )
			pTeam->GetTeamMembers( &members );

		UnitVector targets;
		targets.reserve( members.size() + 1 );
		Unit* pSelf = m_pPlayer;
		targets.push_back( &pSelf );

		for ( auto cid : members )
		{
			if ( cid != m_pPlayer->getCid() )
			{
				Player* pMember = Singleton<GameService>::instance()->getPlayer( cid, m_pPlayer->GetRunnerId(), 1 );
				if ( pMember && pMember->getMap() == pMap )
				{
					Position curPos = m_pPlayer->getCurrentTile();
					Position memberPos = pMember->getCurrentTile();
					if ( Position::tileDistance( memberPos, curPos ) <= 19 )
					{
						targets.push_back( &pMember );
					}
				}
			}
		}
		skill.posAction( m_pPlayer, srcPos, srcPos, &targets, results, bAction );
	}
	else if ( pCfgSkill->range != 0 )
	{
		// AOE技能
		pos.x = inPacket->readInt32();
		pos.y = inPacket->readInt32();

		UnitVector targets;
		int32_t count = inPacket->readInt32();
		if ( count <= 100 )
		{
			for ( int32_t i = 0; i < count && pCfgSkill->target_num > i; ++i )
			{
				UnitHandle target;
				target.id = inPacket->readInt64();
				target.type = inPacket->readInt32();

				int32_t RunnerId = m_pPlayer->GetRunnerId();
				Unit* pTarget = Singleton<GameService>::instance()->getUnit( target.id, target.type, RunnerId );
				if ( pTarget && m_pPlayer->canAttackTarget( pCfgSkill, pTarget ) )
				{
					if ( pTarget->getMap() == pMap )
						targets.push_back( pTarget );
				}
			}
		}
		skill.posAction( m_pPlayer, srcPos, pos, &targets, results, bAction );
	}
	else
	{
		// 自身技能
		UnitHandle targetHandle;
		targetHandle.id = m_pPlayer->getId();
		targetHandle.type = m_pPlayer->getType();
		if ( skill.unitAction( m_pPlayer, targetHandle, results, pos, bAction ) < 0 )
			return 10002;
	}

	// 处理非有益技能的战斗状态
	if ( !pCfgSkill->beneficial && !results->empty() )
	{
		m_pPlayer->SetInFight();
		for ( auto& sr : *results )
		{
			UnitHandle uh( sr.unitId, sr.unitType );
			m_pPlayer->onDamageEvent( uh, sr.hpChange );
			if ( sr.unitType == 1 )
			{
				int32_t RunnerId = m_pPlayer->GetRunnerId();
				Player* victm = Singleton<GameService>::instance()->getPlayer( sr.unitId, RunnerId, 1 );
				if ( victm )
				{
					UnitHandle launcher( m_pPlayer->getId(), m_pPlayer->getType() );
					victm->onDamagedEvent( launcher, sr.hpChange );
				}
			}
			if ( sr.unitType == 1 || sr.unitType == 4 )
			{
				m_pPlayer->SetInFight();  // SetInPvP - TODO: implement PvP state tracking
			}
		}
	}

	// 召唤技能
	if ( pCfgSkill->summon_id > 0 && pCfgSkill->summon_limit > 0 )
	{
		SummonSkill summon;
		summon.nSkillId = nSkillId;
		summon.nStartTick = pCfgSkill->summon_delay + m_pPlayer->getTick();
		summon.targetPos = pos;
		m_lSummonSkills.push_back( summon );
	}

	return 0;
}

void CExtCharSkill::doSkillActive( const CfgTrigSkill* pCfgSkill, Unit* pTarget )
{
	if ( !m_pPlayer || !pCfgSkill )
		return;

	// 触发技能激活逻辑
	if ( pCfgSkill->targetType == 1 )
	{
		UnitHandle handler( m_pPlayer->getId(), m_pPlayer->getType() );
		activeSkill( pCfgSkill->id, &handler );
	}
	else
	{
		UnitHandle handler( pTarget->getId(), pTarget->getType() );
		activeSkill( pCfgSkill->id, &handler );
	}
}

int32_t CExtCharSkill::activeSkill( int32_t nId, const UnitHandle* handler )
{
	if ( !m_pPlayer )
		return 0;

	// 简单的技能激活
	return 0;
}

const CfgActiveSkill* CExtCharSkill::getActiveSkill( int32_t nSkillId )
{
	auto it = m_mActiveSkills.find( nSkillId );
	if ( it != m_mActiveSkills.end() )
		return &it->second;

	// 也从全局配置查找
	return Singleton<CfgData>::instance()->GetSkillTable()->GetActiveSkill( nSkillId );
}

bool CExtCharSkill::addActiveSkill( const CfgActiveSkill* pCfgSkill )
{
	if ( !pCfgSkill )
		return false;

	m_mActiveSkills[pCfgSkill->id] = *pCfgSkill;
	return true;
}

AddonSkill* CExtCharSkill::getAddonSkill( int32_t nSkillFlag )
{
	for ( auto it = m_lAddonSkills.begin(); it != m_lAddonSkills.end(); ++it )
	{
		if ( it->nSkillFlag == nSkillFlag )
			return &(*it);
	}
	return nullptr;
}

bool CExtCharSkill::addAddonSkill( const AddonSkill* addonSkill )
{
	if ( !addonSkill )
		return false;
	m_lAddonSkills.push_back( *addonSkill );
	return true;
}

bool CExtCharSkill::removeAddonSkill( int32_t nSkillFlag )
{
	for ( auto it = m_lAddonSkills.begin(); it != m_lAddonSkills.end(); ++it )
	{
		if ( it->nSkillFlag == nSkillFlag )
		{
			m_lAddonSkills.erase( it );
			return true;
		}
	}
	return false;
}

void CExtCharSkill::checkAddonSkills( int64_t nCurTick )
{
	for ( auto it = m_lAddonSkills.begin(); it != m_lAddonSkills.end(); )
	{
		if ( it->nEndTick > 0 && nCurTick >= it->nEndTick )
		{
			it = m_lAddonSkills.erase( it );
		}
		else
		{
			++it;
		}
	}
}

void CExtCharSkill::checkSummonSkills( int64_t nCurTick )
{
	for ( auto it = m_lSummonSkills.begin(); it != m_lSummonSkills.end(); )
	{
		if ( nCurTick >= it->nStartTick )
		{
			// 执行召唤
			if ( m_pPlayer )
			{
				const CfgActiveSkill* pCfgSkill = getActiveSkill( it->nSkillId );
				if ( pCfgSkill )
				{
					// 执行召唤：通过宠物系统召唤
					CExtCharPet* pCharPet = m_pPlayer->GetCharPet();
					if ( pCharPet )
					{
						pCharPet->SummonBySkill( it->nSkillId );
					}
				}
			}
			it = m_lSummonSkills.erase( it );
		}
		else
		{
			++it;
		}
	}
}

void CExtCharSkill::CheckSummonBuff()
{
	if ( !m_pPlayer )
		return;

	bool bAdd = false;
	CExtCharPet* pCharPet = m_pPlayer->GetCharPet();
	if ( pCharPet )
		bAdd = pCharPet->HaveSummonAlive();

	int64_t nCurTick = m_pPlayer->getTick();
	for ( auto it = m_lTrigSkills.begin(); it != m_lTrigSkills.end(); ++it )
	{
		const CfgTrigSkill* pCfgSkill = Singleton<CfgData>::instance()->GetSkillTable()->GetTrigSkill( *it );
		if ( pCfgSkill && pCfgSkill->trigType == 6 )
		{
			if ( bAdd )
			{
				int32_t nGroupId = pCfgSkill->groupid;
				auto cdIt = m_mSkillCD.find( nGroupId );
				if ( cdIt != m_mSkillCD.end() && nCurTick - cdIt->second >= pCfgSkill->cdTime )
				{
					int32_t nRand = RANDOM.generate( 1, 100 );
					if ( pCfgSkill->trigRate >= nRand )
					{
						addSkillBuffTo( pCfgSkill->trigBuff, pCfgSkill->groupid, m_pPlayer );
						m_mSkillCD[nGroupId] = nCurTick;
					}
				}
			}
			else
			{
				m_pPlayer->removeBuff( pCfgSkill->trigBuff );
			}
		}
	}
}

void CExtCharSkill::CheckSelfTrigBuff( int8_t nTrigType )
{
	if ( !m_pPlayer )
		return;

	int64_t nCurTick = m_pPlayer->getTick();
	for ( auto it = m_lTrigSkills.begin(); it != m_lTrigSkills.end(); ++it )
	{
		const CfgTrigSkill* pCfgSkill = Singleton<CfgData>::instance()->GetSkillTable()->GetTrigSkill( *it );
		if ( pCfgSkill && pCfgSkill->trigType == nTrigType )
		{
			int32_t nGroupId = pCfgSkill->groupid;
			auto cdIt = m_mSkillCD.find( nGroupId );
			if ( cdIt == m_mSkillCD.end() || nCurTick - cdIt->second >= pCfgSkill->cdTime )
			{
				int32_t nRand = RANDOM.generate( 1, 100 );
				if ( pCfgSkill->trigRate >= nRand )
				{
					UnitHandle handler( m_pPlayer->getId(), m_pPlayer->getType() );
					activeSkill( pCfgSkill->id, &handler );
					m_mSkillCD[nGroupId] = nCurTick;
				}
			}
		}
	}
}

void CExtCharSkill::CheckHPPecentTrigBuff( int32_t nLastPecent, int32_t nNowPecent )
{
	if ( !m_pPlayer )
		return;

	int64_t nCurTick = m_pPlayer->getTick();
	for ( auto it = m_lTrigSkills.begin(); it != m_lTrigSkills.end(); ++it )
	{
		const CfgTrigSkill* pCfgSkill = Singleton<CfgData>::instance()->GetSkillTable()->GetTrigSkill( *it );
		if ( pCfgSkill && pCfgSkill->trigType == 4 )
		{
			int32_t nGroupId = pCfgSkill->groupid;
			auto cdIt = m_mSkillCD.find( nGroupId );
			if ( cdIt == m_mSkillCD.end() || nCurTick - cdIt->second >= pCfgSkill->cdTime )
			{
				int32_t trigLine = atoi( pCfgSkill->trigParam.c_str() );
				if ( nLastPecent > trigLine && nNowPecent <= trigLine )
				{
					int32_t nRand = RANDOM.generate( 1, 100 );
					if ( pCfgSkill->trigRate >= nRand )
					{
						UnitHandle handler( m_pPlayer->getId(), m_pPlayer->getType() );
						activeSkill( pCfgSkill->id, &handler );
						m_mSkillCD[nGroupId] = nCurTick;
					}
				}
			}
		}
	}
}

void CExtCharSkill::CheckPhaseDamageTrigBuff( int8_t nPhase )
{
	if ( !m_pPlayer )
		return;

	int64_t nCurTick = m_pPlayer->getTick();
	for ( auto it = m_lTrigSkills.begin(); it != m_lTrigSkills.end(); ++it )
	{
		const CfgTrigSkill* pCfgSkill = Singleton<CfgData>::instance()->GetSkillTable()->GetTrigSkill( *it );
		if ( pCfgSkill && pCfgSkill->trigType == 5 )
		{
			int32_t nGroupId = pCfgSkill->groupid;
			auto cdIt = m_mSkillCD.find( nGroupId );
			if ( cdIt == m_mSkillCD.end() || nCurTick - cdIt->second >= pCfgSkill->cdTime )
			{
				int32_t phase = atoi( pCfgSkill->trigParam.c_str() );
				if ( !phase || nPhase == phase )
				{
					int32_t nRand = RANDOM.generate( 1, 100 );
					if ( pCfgSkill->trigRate >= nRand )
					{
						UnitHandle handler( m_pPlayer->getId(), m_pPlayer->getType() );
						activeSkill( pCfgSkill->id, &handler );
						m_mSkillCD[nGroupId] = nCurTick;
					}
				}
			}
		}
	}
}

void CExtCharSkill::checkSkillTrigBuff( const CfgActiveSkill* pCfgSkill, const SkillResultVector* results )
{
	if ( !m_pPlayer || !pCfgSkill || !results )
		return;

	for ( auto& sr : *results )
	{
		if ( (sr.attackState & 2) == 0 )
		{
			int32_t RunnerId = m_pPlayer->GetRunnerId();
			Unit* pTarget = Singleton<GameService>::instance()->getUnit( sr.unitId, sr.unitType, RunnerId );
			if ( pTarget )
			{
				CheckSkillTrigBuff( pCfgSkill->groupid, pTarget, 1 );
				if ( !pTarget->isAlive() )
					CheckSkillTrigBuff( pCfgSkill->groupid, pTarget, 7 );
			}
		}
	}
}

void CExtCharSkill::CheckSkillTrigBuff( int32_t nSkillGroup, Unit* target, int8_t nTrigType )
{
	if ( !m_pPlayer )
		return;

	int64_t nCurTick = m_pPlayer->getTick();
	for ( auto it = m_lTrigSkills.begin(); it != m_lTrigSkills.end(); ++it )
	{
		const CfgTrigSkill* pCfgSkill = Singleton<CfgData>::instance()->GetSkillTable()->GetTrigSkill( *it );
		if ( pCfgSkill && pCfgSkill->trigType == nTrigType )
		{
			int32_t nGroupId = pCfgSkill->groupid;
			auto cdIt = m_mSkillCD.find( nGroupId );
			if ( cdIt == m_mSkillCD.end() || nCurTick - cdIt->second >= pCfgSkill->cdTime )
			{
				if ( pCfgSkill->isRespond( nSkillGroup ) )
				{
					int32_t nRand = RANDOM.generate( 1, 1000 );
					if ( pCfgSkill->trigRate >= nRand
						&& (pCfgSkill->IsPvp <= 0 || target->getType() == EntityType::ET_PLAYER) )
					{
						if ( pCfgSkill->targetType == 1 )
						{
							UnitHandle handler( m_pPlayer->getId(), m_pPlayer->getType() );
							activeSkill( pCfgSkill->id, &handler );
						}
						else
						{
							UnitHandle handler( target->getId(), target->getType() );
							activeSkill( pCfgSkill->id, &handler );
						}
						m_mSkillCD[nGroupId] = nCurTick;
					}
				}
			}
		}
	}
}

void CExtCharSkill::AddSuitSkillEnergy( int32_t nAddValue )
{
	m_nSuitSkillEnergy += nAddValue;
}

void CExtCharSkill::checkSuitSkillEnergy( int64_t nCurTick )
{
	// 套装技能能量检查 - 暂无完整逻辑
}

void CExtCharSkill::AddOtherSkill( int32_t nSkillId, int32_t nLevel )
{
	m_OthreSkillLevelMap[nSkillId] = nLevel;
}

void CExtCharSkill::addTalentAddon( const AddAttribute& stu )
{
	// 添加天赋附加
}

void CExtCharSkill::getTalentAddon( TalentAddonList* addonList )
{
	if ( !addonList )
		return;
	// 获取天赋附加列表
}

void CExtCharSkill::recalTalentAddon()
{
	if ( !m_pPlayer )
		return;

	m_lActiveTalent.clear();

	for ( auto it = m_SkillLevelMap.begin(); it != m_SkillLevelMap.end(); ++it )
	{
		const CfgTalent* pCfg = Singleton<CfgData>::instance()->GetTalentTable()->GetTalent( it->first, it->second.Level );
		if ( pCfg )
		{
			MemTalent mt;
			mt.nId = it->first;
			// 填充addon信息
			m_lActiveTalent.push_back( mt );
		}
	}
}

std::string CExtCharSkill::saveTalentPoints()
{
	std::stringstream ss;
	for ( auto it = m_SkillLevelMap.begin(); it != m_SkillLevelMap.end(); ++it )
	{
		if ( it != m_SkillLevelMap.begin() )
			ss << "|";
		ss << it->first << ":" << it->second.Level << ":" << it->second.Point;
	}
	return ss.str();
}

void CExtCharSkill::loadTalentPoints( const std::string& str )
{
	if ( str.empty() || !m_pPlayer )
		return;

	StringVector vStr;
	StringUtility::split( vStr, str, "|" );
	for ( auto& s : vStr )
	{
		StringVector vt;
		StringUtility::split( vt, s, ":" );
		if ( vt.size() == 3 )
		{
			int32_t nTalent = atoi( vt[0].c_str() );
			SkillLevelInfo stu;
			stu.Level = atoi( vt[1].c_str() );
			stu.Point = atoi( vt[2].c_str() );

			const CfgTalent* pCfgTalent = Singleton<CfgData>::instance()->GetTalentTable()->GetTalent( nTalent, stu.Level );
			if ( pCfgTalent )
			{
				const CfgTalentPage* pPage = Singleton<CfgData>::instance()->GetTalentTable()->GetTalentPage( m_pPlayer->getJob() );
				if ( pPage )
				{
					m_SkillLevelMap[nTalent] = stu;
				}
			}
		}
	}
}

void CExtCharSkill::SendTalentInfo()
{
	if ( !m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x276A );
	if ( !packet )
		return;

	int16_t nSize = (int16_t)m_SkillLevelMap.size();
	packet->writeInt16( nSize );
	for ( auto it = m_SkillLevelMap.begin(); it != m_SkillLevelMap.end(); ++it )
	{
		packet->writeInt32( it->first );
		packet->writeInt32( it->second.Level );
		packet->writeInt32( it->second.Point );
	}
	packet->writeInt32( m_pPlayer->getRecord( 1927 ) );
	packet->writeInt32( m_pPlayer->getRecord( 1928 ) );
	packet->writeInt32( m_pPlayer->getRecord( 1929 ) );
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int16_t gateIndex = m_pPlayer->getGateIndex();
	pService->sendPacketTo( connid, gateIndex, packet );
}

void CExtCharSkill::SendTalentAddon()
{
	if ( !m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x276B );
	if ( !packet )
		return;

	int16_t nSize = (int16_t)m_lActiveTalent.size();
	packet->writeInt16( nSize );
	for ( auto it = m_lActiveTalent.begin(); it != m_lActiveTalent.end(); ++it )
	{
		packet->writeInt32( it->nId );
		uint32_t nOldOffset = packet->getWOffset();
		int8_t nCount = 0;
		packet->writeInt8( 0 );
		for ( int i = 0; i <= 8; ++i )
		{
			if ( it->vAddon[i] )
			{
				packet->writeInt8( i );
				packet->writeInt32( it->vAddon[i] );
				++nCount;
			}
		}
		uint32_t nNewOffset = packet->getWOffset();
		packet->setWOffset( nOldOffset );
		packet->writeInt8( nCount );
		packet->setWOffset( nNewOffset );
	}
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int16_t gateIndex = m_pPlayer->getGateIndex();
	pService->sendPacketTo( connid, gateIndex, packet );
}

void CExtCharSkill::SendlearedSkill( int32_t nTalentId )
{
	if ( !m_pPlayer )
		return;

	int8_t connid = m_pPlayer->getConnId();
	GameService* pService = Singleton<GameService>::instance();
	NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x276C );
	if ( !packet )
		return;

	packet->writeInt32( nTalentId );
	auto it = m_SkillLevelMap.find( nTalentId );
	if ( it != m_SkillLevelMap.end() )
	{
		packet->writeInt32( it->second.Level );
		packet->writeInt32( it->second.Point );
	}
	else
	{
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
	}
	uint32_t WOffset = packet->getWOffset();
	packet->setSize( WOffset );

	int16_t gateIndex = m_pPlayer->getGateIndex();
	pService->sendPacketTo( connid, gateIndex, packet );
}

int32_t CExtCharSkill::AddSkillPoint( int32_t Id, int32_t Points )
{
	auto it = m_SkillLevelMap.find( Id );
	if ( it != m_SkillLevelMap.end() )
	{
		it->second.Point += Points;
		return it->second.Point;
	}
	return 0;
}

bool CExtCharSkill::UseSkillBook( int32_t Id )
{
	if ( !m_pPlayer )
		return false;

	auto it = m_SkillLevelMap.find( Id );
	if ( it == m_SkillLevelMap.end() )
		return false;

	const CfgTalent* pCfg = Singleton<CfgData>::instance()->GetTalentTable()->GetTalent( Id, it->second.Level );
	if ( !pCfg )
		return false;

	if ( it->second.Point < pCfg->nCostValue )
		return false;

	it->second.Point -= pCfg->nCostValue;
	return true;
}

bool CExtCharSkill::AddSkillBookPoint( int32_t Id, int32_t Points )
{
	auto it = m_SkillLevelMap.find( Id );
	if ( it != m_SkillLevelMap.end() )
	{
		it->second.Point += Points;
		return true;
	}
	return false;
}

void CExtCharSkill::removeSkillByTalent( int32_t TalentId, int32_t TalentLevel )
{
	const CfgTalent* pCfg = Singleton<CfgData>::instance()->GetTalentTable()->GetTalent( TalentId, TalentLevel );
	if ( !pCfg )
		return;

	int8_t nSkillType = Singleton<CfgData>::instance()->GetSkillTable()->GetSkillType( pCfg->skillid );
	switch ( nSkillType )
	{
		case 2:
		{
			for ( auto it = m_lPassiveSkills.begin(); it != m_lPassiveSkills.end(); ++it )
			{
				if ( *it == pCfg->skillid )
				{
					m_lPassiveSkills.erase( it );
					return;
				}
			}
			break;
		}
		case 3:
		{
			for ( auto it = m_lTrigSkills.begin(); it != m_lTrigSkills.end(); ++it )
			{
				if ( *it == pCfg->skillid )
				{
					m_lTrigSkills.erase( it );
					return;
				}
			}
			break;
		}
		case 1:
		{
			for ( auto it = m_lActiveSkills.begin(); it != m_lActiveSkills.end(); ++it )
			{
				if ( *it == pCfg->skillid )
				{
					m_lActiveSkills.erase( it );
					m_mActiveSkills.erase( pCfg->skillid );
					return;
				}
			}
			break;
		}
	}
}

// ==================== 网络包处理 ====================

int32_t CExtCharSkill::onDoUnitSkill( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer )
		return 10002;

	Map* pMap = m_pPlayer->getMap();
	if ( pMap && pMap->GetMapParam() == 21 )
		return 10002;

	if ( !m_pPlayer->isAlive() )
		return 10002;

	if ( m_pPlayer->IsInStall() )
		return 10002;

	if ( m_pPlayer->HasBuffState( CObjState::Index_T::OBS_CHENMO )
		|| m_pPlayer->HasBuffState( CObjState::Index_T::OBS_YUNXUAN )
		|| m_pPlayer->HasBuffState( CObjState::Index_T::OBS_SLEEP )
		|| m_pPlayer->HasBuffState( CObjState::Index_T::OBS_PLYSIS )
		|| m_pPlayer->HasBuffState( CObjState::Index_T::OBS_FROZEN ) )
	{
		return 10002;
	}

	int32_t nSkillId = inPacket->readInt32();
	int32_t nSkillFlag = inPacket->readInt32();

	// 检查载具技能
	CExtCharCarrier* pCarrier = m_pPlayer->GetCharCarrier();
	bool bInCarrier = pCarrier && pCarrier->IsInCarrier();
	if ( bInCarrier )
	{
		if ( !pCarrier->HaveSkill( nSkillId ) )
			return 10002;
	}
	else
	{
		auto found = std::find( m_lActiveSkills.begin(), m_lActiveSkills.end(), nSkillId );
		if ( found == m_lActiveSkills.end() )
			return 10002;
	}

	const CfgActiveSkill* pCfgSkill = getActiveSkill( nSkillId );
	if ( !pCfgSkill )
		return 10002;

	int32_t nGroupId = pCfgSkill->groupid;
	int32_t nCDTime = calActiveSkillCD( nSkillId );
	int64_t nCurTick = m_pPlayer->getTick();

	if ( !CanUseSkillAndMove( nCurTick, true ) )
		return 10002;

	// 特殊技能组CD检查
	switch ( nGroupId )
	{
		case 4001:
		{
			int32_t Now = m_pPlayer->getNow();
			int32_t Record = m_pPlayer->getRecord( 1927 );
			if ( Now - Record < nCDTime / 1000 )
				return 10002;
			m_pPlayer->updateRecord( 1927, m_pPlayer->getNow() );
			break;
		}
		case 3901:
		{
			int32_t Now = m_pPlayer->getNow();
			int32_t Record = m_pPlayer->getRecord( 1928 );
			if ( Now - Record < nCDTime / 1000 )
				return 10002;
			m_pPlayer->updateRecord( 1928, m_pPlayer->getNow() );
			break;
		}
		case 5001:
		{
			int32_t Now = m_pPlayer->getNow();
			int32_t Record = m_pPlayer->getRecord( 1929 );
			if ( Now - Record < nCDTime / 1000 )
				return 10002;
			m_pPlayer->updateRecord( 1929, m_pPlayer->getNow() );
			break;
		}
	}

	// 技能CD检查
	auto cdIt = m_mSkillCD.find( nGroupId );
	if ( cdIt != m_mSkillCD.end() && nCurTick - cdIt->second < nCDTime )
		return 10002;

	// MP/Power检查
	if ( pCfgSkill->kind == 2 )
	{
		CExtOperateLimit* pLimit = m_pPlayer->GetOperateLimit();
		if ( pLimit && pLimit->GetLimitCount( 1083 ) <= 99 )
			return 10002;
	}
	else
	{
		int32_t MP = m_pPlayer->GetMP();
		if ( MP < pCfgSkill->mp || m_nPower < pCfgSkill->power )
		{
			uint16_t Proc = inPacket->getProc();
			int16_t GateIndex = m_pPlayer->getGateIndex();
			int8_t ConnId = m_pPlayer->getConnId();
			Singleton<GameService>::instance()->replyfailure( ConnId, GateIndex, Proc, 10009, 0 );
			return 10009;
		}
	}

	// 执行技能
	SkillResultVector results;
	Position CurrentTile = m_pPlayer->getCurrentTile();
	int32_t ret = doSkill( inPacket, pCfgSkill, &results, CurrentTile, nSkillId, nSkillFlag, true );
	if ( ret )
	{
		uint16_t Proc = inPacket->getProc();
		int16_t GateIndex = m_pPlayer->getGateIndex();
		int8_t ConnId = m_pPlayer->getConnId();
		Singleton<GameService>::instance()->replyfailure( ConnId, GateIndex, Proc, ret, 0 );
		return ret;
	}

	// 成功处理
	m_pPlayer->setStand();
	if ( !bInCarrier )
	{
		m_pPlayer->checkBuffEffect( BUFF_EFFECT_TYPE::BET_USE_SKILL );
		checkSkillTrigBuff( pCfgSkill, &results );
		CheckSkillTrigBuff( pCfgSkill->groupid, m_pPlayer, 2 );
	}

	// 附加技能
	if ( pCfgSkill->addon_skill > 0 )
	{
		AddonSkill addonSkill;
		addonSkill.nEndTick = pCfgSkill->addon_time + m_pPlayer->getTick();
		addonSkill.nTrigTimes = 0;
		addonSkill.nSkillFlag = nSkillFlag;
		addonSkill.nSkillId = nSkillId;
		addAddonSkill( &addonSkill );
	}

	// 消耗
	if ( pCfgSkill->kind == 2 )
	{
		CExtOperateLimit* pLimit = m_pPlayer->GetOperateLimit();
		if ( pLimit )
			pLimit->Reset( 1083 );
	}
	else
	{
		if ( pCfgSkill->power )
			AddPower( -pCfgSkill->power );
		if ( pCfgSkill->mp )
			m_pPlayer->AddMP( -pCfgSkill->mp );
	}

	m_pPlayer->SetSkillFlag( nSkillFlag );
	m_pPlayer->SetStartProtect( 0 );

	// 任务更新
	ChrTask* pTask = m_pPlayer->GetTask();
	if ( pTask )
		pTask->updateTaskSkill( nSkillId );

	// CD记录
	m_mSkillCD[nGroupId] = nCurTick;
	m_lastActionTick = nCurTick;

	// 熟练度
	if ( pCfgSkill->shu_lian_du > 0 )
		AddSkillPoint( pCfgSkill->talent, 1 );

	// 回复成功
	int16_t GateIndex = m_pPlayer->getGateIndex();
	int8_t ConnId = m_pPlayer->getConnId();
	Singleton<GameService>::instance()->replySuccess( ConnId, GateIndex, 0x28, nSkillId );

	return 0;
}

int32_t CExtCharSkill::onDoAddonSkill( Answer::NetPacket* inPacket )
{
	if ( !m_pPlayer || !inPacket )
		return 10002;

	int32_t nSkillId = inPacket->readInt32();
	int32_t nSkillFlag = inPacket->readInt32();
	Position srcPos;
	srcPos.x = inPacket->readInt32();
	srcPos.y = inPacket->readInt32();

	AddonSkill* pAddonSkill = getAddonSkill( nSkillFlag );
	if ( !pAddonSkill )
		return 10002;

	const CfgActiveSkill* pCfgSkill = getActiveSkill( pAddonSkill->nSkillId );
	if ( !pCfgSkill )
		return 10002;

	Position CurrentTile = m_pPlayer->getCurrentTile();
	if ( Position::tileDistance( CurrentTile, srcPos ) > pCfgSkill->distance + 10 )
		return 10002;

	if ( pCfgSkill->addon_skill != nSkillId )
		return 10002;

	const CfgActiveSkill* pCfgAddonSkill = getActiveSkill( nSkillId );
	if ( !pCfgAddonSkill )
		return 10002;

	SkillResultVector results;
	if ( doSkill( inPacket, pCfgAddonSkill, &results, srcPos, nSkillId, nSkillFlag, false ) )
	{
		return 10002;
	}

	checkSkillTrigBuff( pCfgAddonSkill, &results );
	if ( ++pAddonSkill->nTrigTimes >= pCfgSkill->addon_trig_times )
		removeAddonSkill( nSkillFlag );

	return 0;
}

int32_t CExtCharSkill::onAddTalentPoint( Answer::NetPacket* inPacket )
{
	if ( !inPacket || !m_pPlayer )
		return 10002;

	int32_t nId = inPacket->readInt32();
	auto it = m_SkillLevelMap.find( nId );
	if ( it == m_SkillLevelMap.end() )
		return 10002;

	int32_t Level = it->second.Level;
	const CfgTalent* pCfgTalent = Singleton<CfgData>::instance()->GetTalentTable()->GetTalent( nId, Level );
	if ( !pCfgTalent )
		return 10002;

	int32_t v7 = Level + 1;
	const CfgTalent* pCfgNextTalent = Singleton<CfgData>::instance()->GetTalentTable()->GetTalent( nId, v7 );
	if ( !pCfgNextTalent )
		return 10002;

	if ( m_pPlayer->getLevel() < pCfgNextTalent->Playerlevel )
		return 10002;

	if ( it->second.Level > pCfgTalent->maxLevel )
		return 10002;

	if ( pCfgTalent->Point < 0 )
		return 10002;

	if ( it->second.Point < pCfgTalent->Point )
		return 10002;

	// 移除旧等级技能
	removeSkillByTalent( nId, it->second.Level );

	// 扣点升级
	it->second.Point -= pCfgTalent->Point;
	++it->second.Level;

	// 重新计算
	CallSkillBattle();
	initSkills( nId, it->second.Level );

	// 公告
	if ( pCfgTalent->GongGaoId > 0 )
	{
		int8_t connid = m_pPlayer->getConnId();
		GameService* pService = Singleton<GameService>::instance();
		NetPacket* packet = pService->popNetpacket( connid, PACK_DISPATCH, 0x2CD6 );
		if ( packet )
		{
			packet->writeInt32( pCfgTalent->GongGaoId );
			std::string name = m_pPlayer->getName();
			packet->writeUTF8( name );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( it->first );
			packet->writeInt32( it->second.Level );
			uint32_t WOffset = packet->getWOffset();
			packet->setSize( WOffset );
			int8_t bConnId = m_pPlayer->getConnId();
			pService->worldBroadcast( bConnId, packet );
		}
	}

	// 日志
	{
		skill_log stu;
		stu.log_Sid = m_pPlayer->getSid();
		stu.log_time = m_pPlayer->getNow();
		std::string passport = m_pPlayer->GetPassport();
		stu.passport = passport;
		stu.cid = m_pPlayer->getCid();
		stu.name = m_pPlayer->getName();
		stu.op_time = m_pPlayer->getNow();
		stu.skill_id = it->first;
		stu.oper_id = 2;
		stu.level = it->second.Level;

		int8_t connid = m_pPlayer->getConnId();
		DB_SERVICE.AddPlatformLog( connid, PLDT_SKILL, &stu );
	}

	SendTalentInfo();

	int64_t nRetId = nId;
	uint16_t Proc = inPacket->getProc();
	int16_t GateIndex = m_pPlayer->getGateIndex();
	int8_t ConnId = m_pPlayer->getConnId();
	Singleton<GameService>::instance()->replySuccess( ConnId, GateIndex, Proc, nRetId );

	return 0;
}
