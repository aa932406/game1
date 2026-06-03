/********************************************************
* 地图线程												*
* 游戏主逻辑线程，处理地图上所有对象的逻辑运算			*
* 2014.12.3												*
* robin													*
********************************************************/

#ifndef __TPOC_MAP_RUNNER_H__
#define __TPOC_MAP_RUNNER_H__


class Map;
class CActivityMap;
class CActivity;
class Monster;
class CMapRunner : public Answer::Thread
{
	typedef std::list<Map*> MapList;
public:
	CMapRunner(){}
	~CMapRunner(){}

protected:
	virtual void run();

public:
	void SetId( int32_t nId );
	int32_t GetId() const;

	void Start();
	void Stop();

	void AddMap( Map* pMap );
	void DelMap( MapId_t nMapId );

	void PostMsg( GameMsgCode msgcode, void *ptr1, void *ptr2, int32_t iparam1, int32_t iparam2,void *ptr3=NULL );

private:
	void update();
	void checkMessage();
	void dealMessage( GameMsg *msg );

	void onPlayerEnterMap( Player *pPlayer, Map *pMap, int32_t x, int32_t y );
	void onPlayerLeaveMap( Player *pPlayer, Map *pMap, int32_t x, int32_t y );

	void onAddDungeon( Dungeon* pDungeon );
	void onDelDungeon( Dungeon* pDungeon );
	void onPlayerLogout( Player *pPlayer, int16_t nGateIndex );

	void onActivityStart( CActivityMap* pMap, CActivity* pActivity );
	void onActivityStop( CActivityMap* pMap, CActivity* pActivity );
	void onStartMoLingRuQin(Map* pMap, int32_t EndTime );
	void onKillMonster( Map* pMap, Monster* pMonster);

private:
	int32_t m_nId;

	MapList m_maps;
	bool m_bRunning;
	GameMsgQueue m_msgQueue;
	//FamilyApplyInfoVector  m_familyAppliers;
};

#endif	//__TPOC_MAP_RUNNER_H__
