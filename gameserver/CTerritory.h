#ifndef __C_TERRITORY_H__
#define __C_TERRITORY_H__

#include "stdafx.h"
#include "Map.h"

class CTerritory : public Map
{
public:
	CTerritory();
	virtual ~CTerritory();

	virtual void init( const CfgMap &cfgmap ) {}  // Use init(pRunner, cfgmap, FamilyId) instead
	void init( CMapRunner* pRunner, const CfgMap& cfgmap, FamilyId_t FamilyId );

	virtual void addMonster( Monster* monster, int32_t x, int32_t y );
	virtual void addPlayer( Player* player, int32_t x, int32_t y );
	virtual void removePlayer( Player* player, bool islogout );
	virtual void onMonsterDie( Monster* monster, Player* player );

	void reset();
	void AddFamilyMonster( bool bInit );

private:
	FamilyId_t	m_FamilyId;
	Monster*	m_Piglet;
};

#endif	//__C_TERRITORY_H__
