#pragma once

#include <cmath>
#include <list>
#include <map>
#include <string>
#include <vector>
//class Player;
//class MonsterActivity;
//enum ACTIVITY_MSG
//{
//	MSG_MATCHONE,
//	MSG_MATCHTWO,
//	MSG_MATCHTHREE,
//	MSG_MATCHSC,
//};

enum DungeonState
{
	DS_FREE,			// ����
	DS_WAIT,			// ׼���׶�
	DS_RUNNING,			// ������
	DS_WIN,				// ���
	DS_FAIL,			// ʧ��
	DS_RESET,			// ��Ҫ����
};

struct DungeonFinshInfo
{
	int32_t	kill_count;
	int32_t boss_count;
	int32_t escape_count;
	int32_t	get_exp;
	int32_t	lost_exp;
	int32_t	get_money;
	int32_t	normal_wave;
	int32_t	reward_wave;
};

//enum FamilyActivityState
//{
//	FAS_FREE,
//	FAS_RUNNING,
//	FAS_CAN_LEAVE,
//	FAS_MUST_LEAVE,
//	FAS_SUCESS,
//};

enum DungeonEventTriggerType
{
	DETT_TIME_LINE				= 1,	// ʱ�䵽��
	DETT_MONSTER_WAVE			= 2,	// ɱ���ض�����
	DETT_MONSTER_ID				= 3,	// ɱ��ĳ����
	DETT_MONSTER_WAVE_TIMELINE	= 4,	// ��ʱɱ����
	DETT_PLANT_GATHER			= 5,	// ֲ��ɼ�
	DETT_ARRIVE_AREA			= 6,	// ��������
	DETT_HP_PERCENT				= 7,	// ����ֵ
	DETT_MULTI_MONSTER_WAVE		= 8,	// ɱ���ನ��
	DETT_PLAYER_DIE				= 9,	// �������
};

enum DungeonEventEventType
{
	DEET_WIN			= 1,		// ����ͨ��
	DEET_FAIL			= 2,		// ����ʧ��
	DEET_ADD_MONSTER	= 3,		// ���ù���
	DEET_ADD_TRAP		= 4,		// ��������
	DEET_ADD_PLANT		= 5,		// ���òɼ���
	DEET_SHOW_MOVIE		= 6,		// ���Ź�������
	DEET_ACTIVE_EVENT	= 7,		// ���¼�
	DEET_REMOVE_MONSTER	= 8,		// �Ƴ�����
	DEET_ADD_TOWER		= 9,		// Ԥ������
	DEET_SET_WAIT_TIME	= 10,		// ����׼���׶Σ������󼤻��¼��б�
	DEET_REWARD_RATIO	= 11,		// ��������ϵ��(*100)
	DEET_ADD_STACK		= 12,		// �����ϰ���
	DEET_REMOVE_STACK	= 13,		// �����ϰ���
};

enum HPEventType
{
	HPET_PLAYER = 1,
	HPET_MONSTER = 2, 
};

enum ActivityEventTriggerType
{
	AETT_TIME_LINE				= 1,	// ʱ�䵽��
	AETT_MONSTER_WAVE			= 2,	// ɱ���ض�����
	AETT_MULTI_MONSTER_WAVE		= 3,	// ɱ���ನ��
	AETT_MONSTER_WAVE_TIMELINE	= 4,	// ��ʱɱ����
	AETT_MONSTER_ID				= 5,	// ɱ��ĳ����
	AETT_PLANT_GATHER			= 6,	// ֲ��ɼ�
	AETT_ARRIVE_AREA			= 7,	// ��������
	AETT_HP_PERCENT				= 8,	// ����ֵ
};

enum ActivityEventEffectType
{
	AEET_ADD_MONSTER	= 1,		// ���ù���
	AEET_ADD_TRAP		= 2,		// ��������
	AEET_ADD_PLANT		= 3,		// ���òɼ���
	AEET_ACTIVE_EVENT	= 4,		// ���¼�
	AEET_REMOVE_MONSTER	= 5,		// �Ƴ�����
	AEET_ADD_STACK		= 6,		// ������ײ
	AEET_REMOVE_STACK	= 7,		// �Ƴ���ײ
	AEET_BROADCAST		= 8,		// ��ɱ����
};


#define ACTICITY_MONSTER_ID_FAMILY_WAR_PILLAR	10003		// ����սս��֮��
#define ACTICITY_MONSTER_ID_FAMILY_WAR_STON		10004		// ����սʥս��ʯ
#define ACTIVITY_FAMILY_WAR_BUFF_ID				126			// ʧ��BUFF
#define ACTIVITY_HORSE_RACING_BUFF_ID			136			// �������buff

// ����� - ���Է������°汾
#define ATI_WORLD_BOSS			11
#define ATI_CAMP_WAR			12
#define ATI_PEERLESS_WAR		13
#define ATI_CITY_WAR			18
#define ATI_ULTIMATE_CHALLENGE	19
#define ATI_YA_BIAO				20
#define ATI_KAI_FU_BOSS			21
#define ATI_XIN_MAI_MAP			22
#define ATI_CROSS_TOWER			23
#define ATI_RONG_LIAN			24
#define ATI_REFRESH_MONSTER		26

struct CfgMapEvent 
{
	int32_t		id;
	int32_t		mapid;
	int32_t		trigger_id;
	int32_t		trigger_type;
	Int32Vector	trigger_param;
	int32_t		event_type;
	std::string	effect;

	bool		bOpen;
	bool		bDone;
};
typedef std::list<CfgMapEvent> CfgMapEventList;
typedef std::map<int32_t, CfgMapEventList> CfgMapEventMap;
typedef std::map<int32_t, CfgMapEventMap> CfgMapEventTable;

