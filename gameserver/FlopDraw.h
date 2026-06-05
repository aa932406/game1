/*
* 翻牌抽奖
*/

#ifndef __TPOC_FLOP_DRAW_H__
#define __TPOC_FLOP_DRAW_H__

#include "DataStruct.h"
#include "CfgData.h"
typedef std::list<FlopDrawCfg> FlopDrawCfgList;

class CExtFlopDraw : public CExtSystemBase
{
public:
	CExtFlopDraw();
	virtual ~CExtFlopDraw();

public:
	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );

public:
	bool			OnFlopDraw( int32_t nType, int32_t nFlopId );
	int32_t			GetFlopType( int32_t nType, int32_t nFlopId );
	bool			DrawAndCost( int32_t nType, int32_t nFlopId );
	bool			IsGet( int32_t nType, int32_t nId );
	bool			IsFloped( int32_t nType, int32_t nFlopId );
	void			addDrawTimes( int32_t nType, int32_t nFlopId, int32_t FlopResult );
	void			SendFlopRecord( Player* player, int32_t nType );
	void			SendFlopOneRecord( Player* player, int32_t nType, int32_t FlopId, int32_t FlopResult );

private:
	std::map<int, std::map<int,int>>	m_FlopDrawRecordMap;
};

#endif	//__TPOC_FLOP_DRAW_H__
