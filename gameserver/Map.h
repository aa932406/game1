#pragma once
//////////////////////////////////////////////////////////////////////////
//author :zxj			modify Time:2012 -7-7
//description:��ͼ������
//////////////////////////////////////////////////////////////////////////
#include <vector>

#include "CfgData.h"
#include "Tile.h"
#include "DropItem.h"
#include "ObjPet.h"

#define AREA_WIDTH			600			// �����
#define AREA_HEIGHT			400			// �����
#define AREA_VIEW_SIZE		1			// ��Ұ 2x+1

typedef std::list<CDropItemGroup*> DropItemGroupList;class CLittleHelper;
class Player;

class Map
{
public:
	Map();
	//Map(const CfgMap &cfgmap, Kingdom *kingdom);
	virtual ~Map();

public:
	static Position pixelToTile(int32_t px, int32_t py);
	static Position tileToPixel(int32_t tx, int32_t ty);
	static Direction pixelDirection(int32_t cx, int32_t cy, int32_t tx, int32_t ty);
	static Direction tileDirection(int32_t cx, int32_t cy, int32_t tx, int32_t ty);
	static Direction UnitDirection( const Position& src, const Position& tar );
	static Position getAroundTile(int32_t tx, int32_t ty, Direction direction);

public:
	virtual void init( const CfgMap &cfgmap );//��ͼ���ݳ�ʼ��
	virtual void update();
	
	virtual int32_t canEnter(Player *player);//�ж��Ƿ���Խ���
	virtual int32_t getPkMode() const;
	virtual int32_t getReive( Player* player );
	virtual bool randomTransfer();
	virtual bool canRevive();
	virtual void onPlayerKilled( Player* pDier, Player *pKiller );
	virtual void onMonsterDie(Monster *monster, Player *player);
	virtual void onPlayerDie(Player *dier);
	virtual void addPlayer(Player *player, int32_t x, int32_t y);
	virtual void removePlayer(Player *player, bool islogout);
	virtual bool IsActivityMap() const;
	virtual bool IsDungeonMap() const;
	virtual bool OnSitRevive( Player* player );
	virtual bool OnSafeRevive( Player* player );
	virtual bool CanUseXP() const;
	virtual bool CanUsePet() const;
	virtual bool IsFullXP() const;
	virtual bool CanJump() const;
	bool IsXinMoMap() const;
	bool IsXinMoCun() const;

public:
	int32_t GetId() const;
	int32_t GetRunnerId() const;
	int32_t GetType() const;
	int32_t getAntiProtect() const;
	int32_t getHideMini();
	//*����ȥ��
	bool isRunning();
	void onPlantGather(int wava);

	//Kingdom* getKingdom() const;

	int64_t getTick();
	int32_t getNow();
	tm getLocalNow();

	//Tile* getTileAstart(int32_t tx, int32_t ty);

	Tile* getTile(int32_t tx, int32_t ty);
	void checkAreaChange( Unit *pUnit, const Position& oldPos );
	bool isWalkablePosition( int32_t tx, int32_t ty );
	bool inStack( int32_t tx, int32_t ty ) const;

	virtual Player* getEnemySidePlayer(Monster *monster);
	virtual Unit* GetNearestAliveEnemySideUnit(Monster *monster);

	virtual void addMonster(Monster *monster, int32_t x, int32_t y);
	Monster* getEnemySideMonster(Monster *monster);

	void addNpc(Npc	*npc, int32_t x, int32_t y);
	Npc* getNpc(EntityId_t id);
	void removeNpc( EntityId_t npcid );

	void addDropItemGroup(CDropItemGroup *dropItemGroup);
	CDropItemGroup* getDropItemGroup(EntityId_t dropid);

	void addPlant(Plant *plant);
	Plant* getPlant(EntityId_t id);
	void removePlant(EntityId_t id);

	void addTrailer(Trailer *trailer);
	void removeTrailer(Trailer *trailer);

	void AddLittleHelper(CLittleHelper *pLittleHelper);
	void removeLittleHelper(CLittleHelper *pLittleHelper);	bool		GetNearestDropPos(Unit *pUnit, Position& outPos, EntityId_t& outDropId);

	void addPet( CObjPet *pet );
	void removePet( CObjPet *pet );

	void addTrap( Trap *trap );
	Trap* getTrap( EntityId_t id );
	void removeTrap( Trap *trap );

	bool inSafeRegion(const Position &pos);
	UnitVector getSkillTargets(Unit &launcher, Position pos,CfgSkill *pCfg);
	bool checkSkillTarget(Unit &launcher, Position pos, Unit &target, CfgSkill *pCfg);

	bool inRegion(const Position &pos, const CfgMapRegion &region);
	Position getRandomWalkablePosition();
	Position getRandomWalkablePositionInRegion(const CfgMapRegion &region);
	Position getRandomWalkableAroundPosition(int32_t tx, int32_t ty);

	void sendEnterMap(Player *player, int32_t x, int32_t y);
	void sendPlayersInMap(Player *player);
	void sendPetsInMap( Player* player );
	void sendMonstersInMap(Player *player);
	//void sendActivityMonsterDamageInfoInMap(Player *player);
	void sendNpcsInMap(Player *player);
	void sendDropItemsInMap(Player *player);
	void sendPlantsInMap(Player *player);
	void sendTrailersInMap(Player *player);
	void sendTrapsInMap( Player *player );

	void sendTeamsInMap( Player *player );			// ���Ҹ�������ʱ�·�

	void broadcastPlayerIntoMap(Player *player);
	void broadcastMonsterIntoMap(Monster *monster);
	void broadcastNpcIntoMap(Npc *npc);
	void broadcastDropItemIntoMap(CDropItemGroup *dropItemGroup);
	void broadcastPlantIntoMap(Plant *plant);
	void broadcastTrailerIntoMap(Trailer *trailer);
	void broadcastPetIntoMap( CObjPet* pet );
	void broadcastTrapIntoMap( Trap *trap );

	//void broadcastActivityEventDialog(int32_t evtid,int32_t actid);
	//void broadcastPhenixAppear(int32_t x, int32_t y);
	//void broadcastFengYuDroped(int32_t x, int32_t y);
	//void broadcastFengYuPicked(const std::string &name, int32_t x, int32_t y);
	//void broadcastFengYuChangeOwner(const std::string &dier, const std::string &killer, int32_t x, int32_t y);
	//void broadcastFengYuProtect(const std::string &name, int32_t killCount);
	//void broadcastSurvivalFirstKill(const std::string &name);
	//void broadcastSurvivalContinuousKill(const std::string &name, int32_t count);
	//void broadcastKingdomWarContinuousKill(const std::string &name, int32_t kingdom, int32_t count);
	//void broadcastKingdomWarKillFlag(const std::string &name, int32_t kingdom, int32_t loseKingdom);
	//void broadcastKingdomWarKillMonster(const std::string &name, int32_t kingdom, const std::string &monster, int32_t loseKingdom);

	void broadcast(Answer::NetPacket *inPacket);
	void broadcastAreaAround(Answer::NetPacket *inPacket, Unit *pUnit);
	void broadcastToList(Answer::NetPacket *inPacket, const Int16Vector &indexes);

	int32_t xAddHalfY(int32_t x, int32_t y);
	int32_t xSubHalfY(int32_t x, int32_t y);
	//bool  isMultiVicegeneral();
	Position firstLinePosition(Position src, Position dest);

	int32_t GetWidthTileCount();
	int32_t GetHeightTileCount();

	void	AddStack( const PosList& posList );
	void	RemoveStack( const PosList& posList );
	void	SendStacksInMap( Player *player );
	void	SendBuffList( Player* player );
	bool	IsVipGuaJiMap();
	void	OnStartMoLingRuQin( int32_t EndTime );
	void	OnKillMonster( EntityId_t MonsterId );
	int32_t GetMapParam();

	void	ResetRefreshMonster();

private:
	bool		inAreas(Unit *pUnit, const PositionVector &areas);
	bool		checkPos( const Position& pos, const Position& area ) const;

	Position	getAreaByPos( const Position& pos );
	int32_t		getViewAreaCount( int32_t nSize = AREA_VIEW_SIZE ) const;
	void		getViewAreas( const Position& pos, PositionVector& outAreas, int32_t nSize = AREA_VIEW_SIZE );
	void		getNewAreas( const Position& oldPos, const Position& newPos, PositionVector& outAreas, int32_t nSize = AREA_VIEW_SIZE );
	void		getAreaUnits( const PositionVector& areas, UnitList& outUnits );
	void		getAreaTargets( Unit &launcher, Position pos, CfgSkill *pCfg, UnitList& outUnits );

	Answer::NetPacket*	packageUnitEnterArea( const UnitList& inList );
	Answer::NetPacket*  packageUnitEnterAreaBuff( const UnitList& inList );
	void		broadcastToAreas( Answer::NetPacket *packet, const PositionVector& areas );
	void		sendSelfEnterArea( Player* player, const Position& oldPos );

	void		updatePlayers();
	void		updateMonsters();
	void		updateNpcs();
	void		updatePlants();
	void		updateDropItems();
	void		updateTraps();
	void		removeStack( const Position& pos );
	void		appendStack( Answer::NetPacket *packet, const PosList& posList );

	void		CheckVipGuaJiEnd();

protected:
	CfgMap		m_cfgmap;
	//Kingdom*	m_kingdom;

	int32_t		m_widthTileCount;
	int32_t		m_heightTileCount;

	int32_t		m_widthAreaCount;
	int32_t		m_heightAreaCount;

	PlayerList	m_players;
	MonsterList m_monsters;
	NpcList		m_npcs;
	DropItemGroupList m_dropItems;
	PlantList	m_plants;
	TrailerList m_trailers;
	std::list<CLittleHelper*> m_CLittleHelperList;
	ObjPetList	m_pets;
	TrapList	m_traps;
	int32_t		m_lastUpdateTime;
	PosList		m_lstStack;			// ��ʱ��ײ��
	bool		m_IsVipGuaJiMap;
	tm			m_lastLocalNow;

	std::map<int32_t, int32_t>	m_MonsterReviveMap;	// 怪物复活时间表 (mid -> reviveTime)
	int8_t				m_NeedUpdate;		// 是否需要更新怪物刷新
};

