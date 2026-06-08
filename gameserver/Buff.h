#pragma once

#include "CfgData.h"
#include "DataStructs.h"

#include <list>
#include <vector>

enum BuffType
{
	BT_ITEM,
	BT_SKILL,
	BT_PERSIST,
	BT_DUNGEON,
	BT_MONSTER,
	BT_WARFIELDARTIFACT,
	BT_MAGICWEAPON,
};

//enum BuffState
//{
//	BS_XUANYUN = 1,//ѣ��
//	BS_WUDI,//�޵�
//	BS_PERSIST_HP,//������Ѫ
//	BS_BINGDONG,//����
//	BS_SLOW,//�ٻ�
//	BS_CONFUSION,//����
//	BS_WEAK,//����
//	BS_BURN,//����
//	BS_REBOUND,//����
//	BS_EXCITE,//�˷�
//	BS_ANTI_JUMP,
//	BS_BATEPDEF, // ������������
//	BS_BATEMDEF, // ������������
//	BS_BATEHITP, // ������
//	BS_BATEDP, // ������
//	BS_HERO_DUNGEON_MONSTER, //Ӣ�۸��������״̬
//	BS_BUFF_STATE_MAX,
//};

enum SkillSpecial
{
	SS_NONE			= 0,
	SS_SHUNYI		= 1,	// ��λ
	SS_XUANYUN		= 2,	// ѣ��
	SS_WUDI			= 3,	// �޵�
	SS_PERSIST_HP	= 4,	// ������Ѫ
	SS_BINGDONG		= 5,	// ����
	SS_SLOW			= 6,	// �ٻ�
	SS_CONFUSION	= 7,	// ����
	SS_WEAK			= 8,	// ����
	SS_BURN			= 9,	// ����
	SS_EXCITE		= 10,	// �˷�
	SS_FUHUO		= 11,	// ����
	SS_ANTI_JUMP	= 12,
	SS_JUMP			= 21,
	SS_SHAKE		= 22,
	SS_PULL			= 23,
	SS_HIT			= 24,
	SS_KICKOUT		= 25,
	SS_SPEED_UP		= 26,	//����
	SS_DIVIDE		= 28,	//�˺�����
	SS_CLEAR = 100,			//����쳣״̬	
};

struct BuffAttrAddon 
{
	int32_t index;
	int32_t ratio;
	int32_t addon;
};

class Buff
{
public:
	Buff(Unit &unit, CfgBuff &cfgBuff, const UnitHandle &launcher = UnitHandle(), int8_t nType = 0, bool bClear = true);
	virtual ~Buff();

public:
	int32_t remainTick();
	int32_t getId();
	bool beneficial();
	int32_t getSpecial();
	CfgBuff& getCfgBuff();
	bool	NeedShow();

public:
	virtual bool expire();

	virtual void effect();
	virtual void interval();
	virtual void restore();

	virtual bool deathClear() = 0;

	virtual int32_t getType() const = 0;
	virtual int32_t getGroupId() const = 0;
	virtual int32_t getLevel() const = 0;

	bool shieldDamage(int32_t &nDamage);
	void trigTime();
	bool effectTimes();

protected:
	Unit &m_unit;
	CfgBuff &m_cfgBuff;
	UnitHandle m_launcher;

	int64_t m_endTick;
	int64_t m_lastEffectTick;
	int64_t m_lastIntervalTick;
	int32_t m_nShield;
	int32_t m_nEffectTimes;
	int8_t m_nType;
	bool m_bDeathClear;
	std::vector<BuffAttrAddon> m_restore;
};
typedef std::list<Buff*> BuffList;
