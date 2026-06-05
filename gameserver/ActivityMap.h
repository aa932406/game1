#pragma once

#include "actStructs.h"
#include "Map.h"
#include "Player.h"
#include "PlantActivity.h"
#include "MapEvent.h"
//////////////////////////////////////////////////////////////////////////
//author:zxj			modify Time:2012-7-7
//description:���ͼ
//////////////////////////////////////////////////////////////////////////

class CActivity;
class MonsterActivity;
class PlantActivity;

class CActivityMap
	: public Map, public IMapEvent
{
	friend class Trap;
	friend class Plant;
	typedef std::list<MonsterActivity*> ActivityMonsterList;
	typedef std::list<PlantActivity*> ActivityPlantList;
public:
	CActivityMap();
	virtual ~CActivityMap();

public:
	virtual void	init( const CfgMap &cfgmap );
	virtual bool	IsActivityMap() const;
	virtual void	update();
	virtual int32_t canEnter(Player *player);
	virtual int32_t getPkMode() const;
	virtual bool	canRevive();
	virtual int32_t getReive( Player* player );

	virtual void	onPlayerDie( Player *pDier );
	virtual void	onPlayerKilled( Player* pDier, Player *pKiller );
	virtual void	onMonsterDie( Monster *monster, Player *player );
	virtual void	removePlayer( Player *player, bool islogout );
	virtual void	addPlayer( Player *player, int32_t x, int32_t y );
	virtual bool	OnSitRevive( Player* player );
	virtual bool	CanUseXP() const;
	virtual bool	CanUsePet() const;

public:
	void		onActivityStart( CActivity* pActivity );
	void		onActivityStop( CActivity* pActivity );
	void		onMonsterDie( MonsterActivity *monster );
	void		onMonsterHPEvent( MonsterActivity *monster, int32_t id );
	void		onPlantGather( Plant *plant, Player *player );
	int32_t		onBeginGather(  Plant* plant, Player *player );
	void		onMonsterArriveRoadEnd( MonsterActivity *monster );
	void		onMonsterDamaged( MonsterActivity* pMonster, int32_t nDamage, const UnitHandle& launcher );
	Position	GetBornPos( Player* player );
	CActivity*	GetActivity();						// ��ǰ�
	virtual void AddActivityNpc( string& Effect );

	// �·��� - ���Է������°汾
	bool		CanSitRevive();
	bool		SpecialSitRevive( Player* player );
	int32_t		GetTop10Battle();
	int32_t		HaveAliveMonster() const;
	int32_t		HaveAlivePet() const;
	int32_t		GetAlivePlayerCount() const;
	void		OnPlayerRevive( Player* player );
protected:
	virtual void checkEvents();
	virtual void checkEvent( CfgMapEvent &mapEvent );
	virtual void triggerEvent( CfgMapEvent &mapEvent, Unit* pUnit = NULL );

private:
	void	clear();
	void	generateMonster( const std::string &str );
	void	checkAddMonster( int64_t curTick );
	bool	flashMonster( MonsterWait& waitAddMonster, int64_t curTick );
	void	flashMonster( CfgActivityMonster* pCfgDungeonMonster, CfgMonster *pCfgMonster, int32_t x, int32_t y, MonsterBuff* pMonsterBuff = NULL );
	void	addMonsterHPEventInfo( MonsterActivity* pMonster );

private:
	CActivity*			m_pActivity;						// ��ǰ�
	int64_t				m_nStartTick;						// ��ʼʱ��

	Int32MonsterWaveMap m_monsterWave;						// ���ﲨ��
	MonsterWaitList		m_waitMonster;						// �ȴ�ˢ�µĹ���

	ActivityMonsterList	m_actMonsters;						// �����
	ActivityPlantList	m_actPlants;						// ��ɼ���
	std::map<int64_t, int32_t> m_CidBattle;				// ���·��а� - ���Է������°汾
};
