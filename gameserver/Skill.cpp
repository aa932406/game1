#include "stdafx.h"

#include "CfgData.h"
#include "GameService.h"
#include "Map.h"
#include "Monster.h"
#include "Skill.h"
#include "SkillBuff.h"
#include "Attribute.h"

using namespace Answer;

Skill::Skill(int32_t killId,int32_t skillLevel)
{
	m_cfg = CFG_DATA.getSkill(killId);
	m_level = skillLevel;
}

Skill::~Skill()
{

}

int32_t Skill::unitAction(Unit &launcher, UnitHandle targetHandle, int32_t &attackValue, Position srcPos, Position tarPos)
{
	Unit *target = GAME_SERVICE.getUnit( targetHandle.id, targetHandle.type, launcher.GetRunnerId() );
	if (target == NULL || target->getMap() != launcher.getMap())
	{
		broadcastAction(launcher, Position(-1, -1), targetHandle);
		return -1;
	}

	int32_t distance = 3;	// 飞天连斩
	if ( launcher.getType() == ET_PLAYER && launcher.InDungeon() )
	{
		distance = 10;
	}
	if (launcher.getCurrentTile().tileDistance(target->getCurrentTile()) > m_cfg->distance + distance)
	{
		broadcastAction(launcher, Position(-1, -1), targetHandle);
		return -1;
	}

	if ( m_cfg->kind == SK_PUSH )		// 位移技能处理
	{
		Map* pMap = launcher.getMap();
		if ( pMap != NULL )
		{
			if ( pMap->isWalkablePosition( srcPos.x, srcPos.y ) )
			{
				launcher.setAtTile( launcher.getMap(), srcPos.x, srcPos.y );
			}
			if ( pMap->isWalkablePosition( tarPos.x, tarPos.y ) )
			{
				target->setAtTile( target->getMap(), tarPos.x, tarPos.y );
			}
		}
	}
	broadcastAction(launcher, target->getCurrentTile(), targetHandle,srcPos,tarPos);

	if (m_cfg->special == SS_SHUNYI)
	{
		Map	*pMap = target->getMap();
		if (pMap != NULL)
		{
			Position launcherPixel = launcher.getCurrentPixel();
			Position targetPixel = target->getCurrentPixel();
			Position targetTile = target->getCurrentTile();

			Position pos = Map::getAroundTile(targetTile.x, targetTile.y, Map::pixelDirection(targetPixel.x, targetPixel.y, launcherPixel.x, launcherPixel.y));
			Tile *pTile = pMap->getTile(pos.x, pos.y);
			if (pTile != NULL)
			{
				launcher.setAtTile( pMap, pos.x, pos.y );
			}
		}
	}

	return unitResult(launcher, targetHandle, attackValue);
}

int32_t Skill::unitResult( Unit &launcher, UnitHandle targetHandle, int32_t &attackValue )
{
	Unit *target = GAME_SERVICE.getUnit( targetHandle.id, targetHandle.type, launcher.GetRunnerId() );
	if (target == NULL || target->getMap() != launcher.getMap())
	{
		return -1;
	}

	if (m_cfg->special == SS_FUHUO)
	{
		if (target->isAlive())
		{
			return -1;
		}
	}
	else
	{
		if (!target->isAlive())
		{
			return -1;
		}
	}

	SkillResult launcherResult;
	launcherResult.unitid = launcher.getUnitId();
	launcherResult.unittype = launcher.getType();

	SkillResult targetResult;
	targetResult.unitid = targetHandle.id;
	targetResult.unittype = targetHandle.type;

	instantResult(launcher, *target, launcherResult, targetResult, attackValue);

	broadcastResult(launcher, launcherResult, target->getCurrentTile(), targetResult);

	return std::abs(targetResult.hpchange);
}

void Skill::posAction(Unit &launcher, Position pos, UnitVector &targets, EntityIdInt32Map &attackValues)
{
	int32_t distance = 3;	// 飞天连斩
	if ( launcher.getType() == ET_PLAYER && launcher.InDungeon() )
	{
		distance = 10;
	}
	if (pos.tileDistance(launcher.getCurrentTile()) > m_cfg->distance+distance)
	{
		broadcastAction(launcher, Position(-1, -1), UnitHandle(-1, -1));
		return;
	}

	broadcastAction(launcher, pos, UnitHandle(-1, -1));

	if (m_cfg->special == SS_SHUNYI)
	{
		Map	*pMap = launcher.getMap();
		if (pMap != NULL)
		{
			if ( pMap->isWalkablePosition( pos.x, pos.y ) )
			{
				launcher.setAtTile( pMap, pos.x, pos.y );
			}
		}
	}
	posResult(launcher, pos, targets, attackValues);
}

void Skill::posResult(Unit &launcher, Position pos, UnitVector &targets, EntityIdInt32Map &attackValues)
{
	Map *pMap = launcher.getMap();
	if (pMap == NULL)
	{
		return;
	}

	SkillResult launcherResult;
	launcherResult.unitid = launcher.getUnitId();
	launcherResult.unittype = launcher.getType();

	SkillResultVector results;

	for (UnitVector::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		Unit *target = *it;
		if (target != NULL && pMap->checkSkillTarget(launcher, pos, *target, m_cfg))
		{
			SkillResult result;
			result.unitid = target->getUnitId();
			result.unittype = target->getType();
			int32_t attackValue = 0;
			instantResult(launcher, *target, launcherResult, result, attackValue);
			attackValues[target->getUnitId()] = attackValue;
			results.push_back(result);
		}
	}

	broadcastResult(launcher, launcherResult, pos, results);
}

void Skill::calcDamage(Unit &launcher, Unit &target, int32_t &damge, SkillAttackState &attackState, int32_t &attackValue)
{
	int32_t src_hit = launcher.GetAttrValue( CObjAttrs::ATTR_HITRATE );
	if ( launcher.getType() == ET_PET )	// 宠物需要计算人物的命中闪避
	{
		CObjPet* pPet = dynamic_cast<CObjPet*>( &launcher );
		if ( pPet != NULL )
		{
			Player* pPlayer = pPet->GetPlayer();
			if ( pPlayer != NULL )
			{
				src_hit = pPlayer->GetAttrValue( CObjAttrs::ATTR_HITRATE );
			}
		}
	}

	int32_t	tar_dod = target.GetAttrValue( CObjAttrs::ATTR_DODGE );
	if ( target.getType() == ET_PET )	// 宠物需要计算人物的命中闪避
	{
		CObjPet* pPet = dynamic_cast<CObjPet*>( &target );
		if ( pPet != NULL )
		{
			Player* pPlayer = pPet->GetPlayer();
			if ( pPlayer != NULL )
			{
				tar_dod = pPlayer->GetAttrValue( CObjAttrs::ATTR_DODGE );
			}
		}
	}

	// 计算闪避
	//int32_t dodge = target.GetAttrValue( CObjAttrs::ATTR_DODGE ) - launcher.GetAttrValue( CObjAttrs::ATTR_HITRATE );
	if ( m_cfg->id != SKILL_ID_FLY_HIT && m_cfg->id != SKILL_ID_LIU_LIAN_ZHAN && m_cfg->id != SKILL_ID_LONG_HUN_QIANG )
	{
		int32_t dodge = tar_dod - src_hit;
		dodge = dodge < 0 ? 0 : dodge;
		int32_t dodgeRate = 5 + 50 * dodge / ( dodge + 1000 );
		dodgeRate = dodgeRate > 55 ? 55 : dodgeRate;
		if (RANDOM.generate(1, 100) < dodgeRate)
		{
			damge = 0;
			attackState = SAS_PARRY;
			return;
		}
	}
	

	//int32_t attackBase = 0;
	//int32_t defenceBase = 0;

	int32_t phyAtkMin = launcher.GetAttrValue( CObjAttrs::ATTR_PHY_ATK_MIN );
	int32_t phyAtkMax = launcher.GetAttrValue( CObjAttrs::ATTR_PHY_ATK_MAX );
	int32_t magAtkMin = launcher.GetAttrValue( CObjAttrs::ATTR_MAG_ATK_MIN );
	int32_t magAtkMax = launcher.GetAttrValue( CObjAttrs::ATTR_MAG_ATK_MAX );

	int32_t phyDef = target.GetAttrValue( CObjAttrs::ATTR_PHY_DEF );
	int32_t magDef = target.GetAttrValue( CObjAttrs::ATTR_MAG_DEF );
	int32_t lucky = launcher.GetAttrValue( CObjAttrs::ATTR_LUCKY );
	int32_t atkBattle = launcher.getBattle();
	int32_t defBattle = target.getBattle();

	int32_t addDmg = launcher.GetAttrValue( CObjAttrs::ATTR_DMG_ADD );
	int32_t redDmg = target.GetAttrValue( CObjAttrs::ATTR_DMG_RDC );

	int32_t addDmgPec = launcher.GetAttrValue( CObjAttrs::ATTR_DMG_ADD_PEC );
	int32_t redDmgPec = target.GetAttrValue( CObjAttrs::ATTR_DMG_RDC_PEC );

	if ( target.getType() == ET_PET )	// 合体宠物需要计算人物的防御
	{
		CObjPet* pPet = dynamic_cast<CObjPet*>( &target );
		if ( pPet != NULL && pPet->IsZoarium() )
		{
			Player* pPlayer = pPet->GetPlayer();
			if ( pPlayer != NULL )
			{
				phyDef = pPlayer->GetAttrValue( CObjAttrs::ATTR_PHY_DEF );
				magDef = pPlayer->GetAttrValue( CObjAttrs::ATTR_MAG_DEF );
			}
		}
	}

	if (m_cfg->attack_type == SAT_PATTACK)
	{
		int32_t atkMin = phyAtkMin + (phyAtkMax-phyAtkMin)*(lucky-50)/160;
		int32_t atkFinal = RANDOM.generate( atkMin, phyAtkMax );

		if ( launcher.getType() == ET_PLAYER && ( target.getType() == ET_PLAYER || target.getType() == ET_PET ) )
		{
			atkFinal = 1 * atkFinal;
		}
		else if( launcher.getType() == ET_PET && ( target.getType() == ET_PLAYER || target.getType() == ET_PET ) )
		{
			atkFinal = static_cast<int32_t>(0.5 * atkFinal);
		}
		int32_t baseDmg = atkFinal - phyDef / 3 + addDmg - redDmg;
		int32_t addDmgFinal = 100 + addDmgPec - redDmgPec;
		baseDmg = baseDmg > 0 ? baseDmg : 0;
		addDmgFinal = addDmgFinal > 0 ? addDmgFinal : 0;
		damge = ( baseDmg + m_cfg->getAttackAddon( m_level ) ) * addDmgFinal / 100;
	}
	else if (m_cfg->attack_type == SAT_MATTACK)
	{
		int32_t atkMin = magAtkMin + (magAtkMax-magAtkMin)*(lucky-50)/160;
		int32_t atkFinal = RANDOM.generate( atkMin, magAtkMax );
		if ( launcher.getType() == ET_PLAYER && ( target.getType() == ET_PLAYER || target.getType() == ET_PET ) )
		{
			atkFinal = 1 * atkFinal;
		}
		else if( launcher.getType() == ET_PET && ( target.getType() == ET_PLAYER || target.getType() == ET_PET ) )
		{
			atkFinal = static_cast<int32_t>( 0.5 * atkFinal );
		}
		int32_t baseDmg = ( atkFinal - magDef / 3 ) * 130/100 + addDmg - redDmg;
		int32_t addDmgFinal = 100 + addDmgPec - redDmgPec;
		baseDmg = baseDmg > 0 ? baseDmg : 0;
		addDmgFinal = addDmgFinal > 0 ? addDmgFinal : 0;
		damge = ( baseDmg + m_cfg->getAttackAddon( m_level ) ) * addDmgFinal / 100;
	}
	else
	{
		damge = 0;
		attackState = SAS_PARRY;
		return;
	}

	damge = damge < 0 ? 0 : damge;

	// 特殊处理 军团之柱没有资金时10倍伤害
	damge *= target.GetHurtIncreace();

	int32_t rate = atkBattle - defBattle;
	int32_t nKey = launcher.GetCalLevel() - target.GetCalLevel();
	int32_t	nAtkModify = m_cfg->getAttackModify( m_level );
	if ( m_cfg->kind == SK_XP )
	{
		if ( target.getType() == ET_PLAYER || target.getType() == ET_PET )
		{
			nAtkModify = 20;
		}
		else if ( target.isBoss() )
		{
			nAtkModify = 100;
		}
	}
	if ( ( launcher.getType() == ET_PLAYER || launcher.getType() == ET_PET ) && ( target.getType() == ET_PLAYER || target.getType() == ET_PET ) )
	{
		// 人对人
		// damge = static_cast<int32_t>( 0.5f * damge );
		if ( rate > 0 )
		{
			damge = static_cast<int32_t>( damge *  ( 1 + pow( rate/1000.0f, 0.8f ) * 1.5 ) * nAtkModify / 100 * 0.7f );
		}		
		else
		{
			//std::cout << pow( abs(rate/1000.0f), 0.4f ) << std::endl;
			damge = static_cast<int32_t>( damge * ( 1 - pow( abs(rate/1000.0f), 0.8f ) * 0.5 )  * nAtkModify / 100 * 0.7f );
		}

	}
	else if ( ( launcher.getType() == ET_PLAYER || launcher.getType() == ET_PET ) && ( target.getType() != ET_PLAYER && target.getType() != ET_PET ) )
	{
		// 人对怪
		rate = rate > 100 ? 100 : rate;
		rate = rate < -100 ? -100 : rate;
		damge = damge * ( 200 + rate ) / 200;

		int32_t nPec = nKey < -30 ? 50 : ( nKey < -10 ? 80 : ( nKey < 30 ? 100 : ( nKey < 60 ? 150 : 200 ) ) );
		if ( launcher.isBoss() || target.isBoss() )
		{
			nPec = 100;
		}
		damge = damge * nPec / 100 * nAtkModify / 100;
	}
	else
	{
		// 怪对人
		rate = rate > 100 ? 100 : rate;
		rate = rate < -100 ? -100 : rate;
		damge = damge * ( 200 + rate ) / 200;

		int32_t nPec = nKey < -60 ? 20 : ( nKey < -30 ? 50 : ( nKey < -10 ? 80 : ( nKey < 10 ? 100 : ( nKey < 30 ? 120 : ( nKey < 60 ? 200 : 300 ) )  ) ) );
		if ( launcher.isBoss() || target.isBoss() )
		{
			nPec = 100;
		}
		damge = damge * nPec / 100 * nAtkModify / 100;
	}

	damge = damge < 1 ? 1 : damge;

	//// 计算暴击
	//int32_t violentRate = static_cast<int32_t>( launcher.GetAttrValue( CObjAttrs::ATTR_CRITRATE ) - target.GetAttrValue( CObjAttrs::ATTR_TENACITY ) );
	//if (RANDOM.generate(1, 100) <= violentRate)
	//{
	//	damge = static_cast<int32_t>(damge * ( 1.5f + ( launcher.GetAttrValue( CObjAttrs::ATTR_CRI_DMG_ADD_PEC ) - target.GetAttrValue( CObjAttrs::ATTR_CRI_DMG_RDC_PEC ) )*0.01f ) );
	//	attackState = SAS_VIOLENT;
	//	return;
	//}

	attackValue = damge;
	attackState = SAS_NORMAL;
}

void Skill::instantResult(Unit &launcher, Unit &target, SkillResult &launcherResult, SkillResult &targetResult, int32_t &attackValue)
{
	if (m_cfg->special == SS_CLEAR)
	{
		target.clearDebuff();
	}
	else if (m_cfg->special == SS_FUHUO)
	{
		target.FillHP();
		targetResult.hpchange += target.GetMaxHP(); 

	}
	else
	{
		if (m_cfg->attack_type != 0)
		{
			Unit* pTarget = &target;
			if ( target.getType() == ET_PLAYER )
			{
				Player* pPlayer = dynamic_cast<Player*>( pTarget );
				if ( pPlayer != NULL )
				{
					CObjPet* pZoariumPet = pPlayer->GetCharPet().GetZoariumPet();
					if ( pZoariumPet != NULL )
					{
						pTarget = pZoariumPet;
					}
				}
			}
			int32_t damage = 0;
			SkillAttackState attackState = SAS_NORMAL;
			calcDamage(launcher, *pTarget, damage, attackState, attackValue);
			if (attackState != SAS_PARRY && damage <= 0)
			{
				damage = 1;
			}
			else if ( target.getType() == ET_PLAYER && damage > 0 )	//法师平分伤害技能处理
			{
				Player*pPlayer = dynamic_cast<Player*>( &target );
				if ( NULL != pPlayer )
				{
					if ( pPlayer->HasSkill( SKILL_ID_DIVIDE ) )
					{
						int32_t DivideDamage = damage * 10 / 100;
						int32_t PetCount = pPlayer->GetCharPet().GetAliveFightPetCount();
						pPlayer->GetCharPet().DivideHurt( DivideDamage );
						damage = damage - PetCount * DivideDamage;
					}
				}
			}
			bool IsStruckDamage = false;
			if ( m_cfg->id == SKILL_ID_FLY_HIT || m_cfg->id == SKILL_ID_LIU_LIAN_ZHAN || m_cfg->id == SKILL_ID_LONG_HUN_QIANG )
			{
				if ( pTarget->getType() == ET_PET )
				{
					CObjPet* pPet = dynamic_cast<CObjPet*>( pTarget );
					if ( pPet != NULL && pPet->IsZoarium() )
					{
						Player* pPlayer = pPet->GetPlayer();
						if ( pPlayer != NULL )
						{
							pPlayer->GetCharPet().ZoariumPetDame( damage, launcher.getHandle() );
							targetResult.attackState = attackState;
							targetResult.hpchange -= damage;
							IsStruckDamage = true;
						}
					}
				}
			}

			if ( !IsStruckDamage )
			{
				targetResult.hpchange -= pTarget->struckDamage(damage, m_cfg->attack_type, launcher.getHandle());
				targetResult.attackState = attackState;
			}


			//if (target.getType() == ET_PLAYER && attackValue > 0)
			//{
			//	Player* pTargetPlayer = GAME_SERVICE.getPlayer(target.getUnitId(), target.getType());
			//	if (pTargetPlayer != NULL)
			//	{
			//		MagicWeaponSkill* pMagicWeaponSkill = pTargetPlayer->getMagicWeaponSkill();
			//		if (pMagicWeaponSkill != NULL)
			//		{
			//			if (pMagicWeaponSkill->skill_id > 0 && pMagicWeaponSkill->trigger_type == MWSTT_PASSIVE)
			//			{
			//				CfgSkill* pSkill = CFG_DATA.getSkill(pMagicWeaponSkill->skill_id);
			//				if (pSkill != NULL && pSkill->special == SS_REBOUND)
			//				{
			//					int32_t rebound = attackValue * pMagicWeaponSkill->trigger_param / 1000;
			//					launcher.AddHp(-rebound);
			//					launcherResult.hpchange += -rebound;
			//				}
			//			}
			//		}
			//	}
			//}
		}
		else
		{
			//do nothing
		}
	}

	if (m_cfg->buff != 0 && RANDOM.generate(1, 100) < m_cfg->getBuffRate(m_level))
	{
		CfgBuff *cfgBuff = CFG_DATA.getBuff(m_cfg->buff);
		if (cfgBuff != NULL)
		{
			SkillBuff *buff = new SkillBuff(target, *cfgBuff);
			if (NULL == buff)
			{
				return;
			}
			buff->init( m_cfg->id, m_level, launcher.getHandle(), target.getHandle() );
			if (target.addBuff(buff) == ERR_OK)
			{
				targetResult.buffid = m_cfg->buff;
				targetResult.buffDuration = buff->remainTick();
			}
		}
	}
}

void Skill::broadcastAction(Unit &launcher, const Position &targetPos, const UnitHandle &targetHandle, Position srcPos, Position tarPos)
{
	Map *pMap = launcher.getMap();
	if (pMap == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SKILL_ACTION);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( launcher.GetSkillFlag( true ) );
	packet->writeInt16(static_cast<int16_t>(m_cfg->id));
	packet->writeInt64(launcher.getUnitId());
	packet->writeInt8(launcher.getType());
	packet->writeInt16(static_cast<int16_t>(targetPos.x));
	packet->writeInt16(static_cast<int16_t>(targetPos.y));
	packet->writeInt64(targetHandle.id);
	packet->writeInt8(targetHandle.type);
	if ( m_cfg->kind == SK_PUSH )							// 位移技能处理
	{
		packet->writeInt16(static_cast<int16_t>(srcPos.x));			// 人物最终位置
		packet->writeInt16(static_cast<int16_t>(srcPos.y));	
		packet->writeInt16(static_cast<int16_t>(tarPos.x));			// 目标最终位置
		packet->writeInt16(static_cast<int16_t>(tarPos.y));
	}
	packet->setSize(packet->getWOffset());
	pMap->broadcastAreaAround(packet, &launcher);
}

void Skill::broadcastResult(Unit &launcherUnit, const SkillResult &launcherResult, const Position &targetPos, const SkillResult &targetResult)
{
	Map *pMap = launcherUnit.getMap();
	if (pMap == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SKILL_RESULT);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( launcherUnit.GetSkillFlag() );
	packet->writeInt16(static_cast<int16_t>(m_cfg->id));
	packet->writeInt64(launcherResult.unitid);
	packet->writeInt8(static_cast<int8_t>(launcherResult.unittype));
	packet->writeInt32(launcherResult.hpchange);
	packet->writeInt16(targetPos.x);
	packet->writeInt16(targetPos.y);

	packet->writeInt32(1);
	packet->writeInt64(targetResult.unitid);
	packet->writeInt8(static_cast<int8_t>(targetResult.unittype));
	packet->writeInt32(targetResult.hpchange);
	packet->writeInt16(static_cast<int16_t>(targetResult.attackState));
	packet->writeInt32(targetResult.buffid);
	packet->writeInt32(targetResult.buffDuration);
	packet->setSize(packet->getWOffset());
	pMap->broadcastAreaAround(packet, &launcherUnit);
}

void Skill::broadcastResult(Unit &launcherUnit, const SkillResult &launcherResult, const Position &targetPos, const SkillResultVector &targetsResult)
{
	Map	*pMap = launcherUnit.getMap();
	if (pMap == NULL)
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SKILL_RESULT);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( launcherUnit.GetSkillFlag() );
	packet->writeInt16(static_cast<int16_t>(m_cfg->id));
	packet->writeInt64(launcherResult.unitid);
	packet->writeInt8(static_cast<int8_t>(launcherResult.unittype));
	packet->writeInt32(launcherResult.hpchange);
	packet->writeInt16(targetPos.x);
	packet->writeInt16(targetPos.y);
	packet->writeInt32(static_cast<int32_t>(targetsResult.size()));
	for (SkillResultVector::const_iterator it = targetsResult.begin(); it != targetsResult.end(); ++it)
	{
		packet->writeInt64(it->unitid);
		packet->writeInt8(static_cast<int8_t>(it->unittype));
		packet->writeInt32(it->hpchange);
		packet->writeInt16(static_cast<int16_t>(it->attackState));
		packet->writeInt32(it->buffid);
		packet->writeInt32(it->buffDuration);
	}
	packet->setSize(packet->getWOffset());
	pMap->broadcastAreaAround(packet, &launcherUnit);
}

