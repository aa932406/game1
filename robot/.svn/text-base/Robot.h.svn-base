/*
* 机器人系统
* 服务器压力测试
* 服务器功能测试
*/

#ifndef __TPOC_ROBOT_H__
#define __TPOC_ROBOT_H__

#include <string>
#include "CfgData.h"
#include "ClientConnection.h"
#include "ExtSystemMgr.h"

#include "ExtTask.h"
#include "ExtBag.h"
#include "ExtSkill.h"

enum PlayerState
{
	PS_INVALID,
	PS_STAND,
	PS_WALK,
	PS_WALK_ATTACK,
	PS_ATTACK,
	PS_GHOST,
};

typedef std::list<Position> PositionList;

// 目标类型
#define	DS_NPC			'n'
#define DS_MONSTER		'g'

class Character
{
public:
	Character()
	{
	}
	~Character()
	{
	}

public:
	void reset()
	{
	}

public:
	int32_t m_cid;
	std::string m_name;
	int32_t m_sex;
	int32_t m_style;
	int32_t m_head;
	int32_t m_kingdom;

	int32_t m_job;
	int32_t m_level;

	int32_t m_mapid;
	int32_t fight_power;
	int32_t m_x;
	int32_t m_y;
};

class CRobot
	: public ClientConnection
{
public:
	CRobot( const std::string& passport, int32_t sid, const std::string& name, Sex_t sex, Job_t job, int32_t head, int32_t nLine=1 );
	~CRobot();

protected:
	virtual void onNetPacket(Answer::NetPacket *inPacket);
	virtual void onDisconnect();

public:
	CharId_t getCid() const;
	int32_t getUit() const;
	int32_t getSid() const;
	int32_t getLevel() const;
	Job_t getJob() const;
	Sex_t getSex() const;
	Position getCurPos() const;
	Position getCurTile() const;
	const std::string getPassPort() const;

	void	update( int64_t curTick );

	void	sendStartPacket();										// 登陆游戏
	void	Dispatch( Answer::NetPacket* packet );


private:
	void	initExtSystems();
	int32_t handleNetPacket(Answer::NetPacket *inPacket);
	void	sendPacketTo( Answer::NetPacket *packet );
	bool	needIncreace( ProcId_t nProc );

	int32_t	onUserToken( Answer::NetPacket* inPacket );				// 登陆验证
	int32_t	onLineList( Answer::NetPacket* inPacket );				// 线路列表
	int32_t	onCharacterList( Answer::NetPacket* inPacket );			// 角色列表
	int32_t	onEnterMap( Answer::NetPacket* inPacket );				// 进入地图
	int32_t	onCharInfo( Answer::NetPacket* inPacket );				// 人物基本信息
	int32_t	onInstantMove( Answer::NetPacket* inPacket );			// 强制移动
	int32_t	onMonsterInMap( Answer::NetPacket* inPacket );			// 地图怪物初始化
	int32_t	onUnitBasicData( Answer::NetPacket* inPacket );			// 地图怪物更新
	int32_t	onUnitMove( Answer::NetPacket* inPacket );				// 地图怪物移动
	int32_t	onUnitEnterArea( Answer::NetPacket* inPacket );			// 地图怪物进入视野

	void	sendLogin();											// 登陆验证
	void	sendGetCharacter();										// 获取角色列表
	void	sendEnterGame();										// 进入游戏
	void	sendCreateCharacter();									// 创角
	void	sendTransToMap( MapId_t mapid, int32_t x, int32_t y );	// 传送到随机地图
	void	sendAttack( int32_t nSkillId );							// 攻击
	void	sendRelive();											// 复活

	int32_t	handleToExtSystem( Answer::NetPacket *packet );
	void	checkNetPackets();

public:
	void	SetTarget( MapId_t mid, Position pos, int8_t nState = PS_WALK );

private:
	void	onUpdateState( int64_t curTick );
	void	onMove( int64_t curTick );
	void	onStand( int64_t curTick );
	void	onWalk( int64_t curTick );
	void	onWalkAttack( int64_t curTick );
	void	onAttack( int64_t curTick );
	void	onGhost( int64_t curTick );
	void	moveToPos( int32_t x, int32_t y );						// 向目标移动
	double	getDirectionSpeed( int8_t dir );
	void	moveToNextPos();
	void	clearTarget();
	bool	isProcRegisted( ProcId_t nProc );
	void	transToTarget( MapId_t mapid, int32_t x, int32_t y );
	bool	isArrived();
	void	resetMoveTick( const Position& curTile, const Position& tarTile );
	void	resetRoad();
	void	checkUseMedicine();

	UnitVector getSkillTargets( CfgSkill *pCfg );

private:
	typedef Answer::SafeQueue<Answer::NetPacket*> PacketList;
	int16_t		m_cgindex;
	CharId_t	m_cid;
	int32_t		m_uid;
	int32_t		m_sid;
	std::string	m_passport;
	//std::string	m_name;	// 定义在父类中了
	int32_t		m_style;
	int32_t		m_head;
	int32_t		m_kingdom;
	Sex_t		m_sex;
	Job_t		m_job;
	int32_t		m_level;
	MapId_t		m_mapid;
	int32_t		m_x;
	int32_t		m_y;

	int32_t		m_nIncreace;
	std::string	m_token;
	int32_t		m_line;

	int32_t		m_lastLoginTime;
	std::string	m_lastLoginIp;

	MapId_t		m_nTargetMap;
	Position	m_NextPos;

	Position	m_TargetPos;

	bool		m_start;

	PacketList	m_netPackets;

	int64_t		m_nActionTick;
	int64_t		m_nMedicineTick;
	int64_t		m_nCurTick;

	Unit*		m_pTarget;
	int8_t		m_nState;
	int32_t		m_nSpeed;
	int8_t		m_direction;

	int32_t		m_nHP;
	int32_t		m_nMaxHP;
	int32_t		m_nMP;
	int32_t		m_nMaxMP;

	PositionList	m_road;

	CExtSystemMgr	m_ExtSysMgr;

private:		CExtTask		m_ExtTask;
public:			CExtTask&		GetExtTask() { return m_ExtTask; }

private:		CExtBag			m_ExtBag;
public:			CExtBag&		GetExtBag() { return m_ExtBag; }

private:		CExtSkill		m_ExtSkill;
public:			CExtSkill		GetExtSkill() { return m_ExtSkill; }
};


#endif	//__TPOC_ROBOT_H__
