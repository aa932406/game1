#ifndef __TPOC_CURRENCY_H__
#define __TPOC_CURRENCY_H__

#include "ExtSystemBase.h"

class Player;
class CExtCurrency : public CExtSystemBase
{
public:
	CExtCurrency();
	virtual ~CExtCurrency();

public:
	virtual	void	OnCleanUp();
	virtual	void	OnUpdate( int64_t curTick );
	virtual	void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual	void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	GetInterestsProtocol( ProcIdList& procList );	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onSocialAddCurrency( Answer::NetPacket *inPacket );
	int32_t				OnCurrencyDuiHuan( Answer::NetPacket *inPacket );
	int32_t				syncGold( Answer::NetPacket *inPacket );

public:
	int64_t			GetCurrency( CURRENCY_TYPE const nType ) const;
	bool			AddCurrency( CURRENCY_TYPE const nType, int64_t nVal, int32_t opWay = 0, int64_t nParam = 0 );
	bool			DecCurrency( CURRENCY_TYPE const nType, int64_t nVal, int32_t opWay = 0, int64_t nParam = 0 );
	void			SendCurrencyInfo( bool bAll = true );
	int64_t			GetMoneyBindAndNoBind();
	bool			DecMoneyAndNoBind( int64_t nVal, int32_t opWay = 0, int64_t nParam = 0 );
	void			SynCurrency();
private:
	bool			checkCurrencyType( CURRENCY_TYPE const nType ) const;
	bool			changeCurrency( CURRENCY_TYPE const nType, int64_t nVal, int32_t opWay = 0, int64_t nParam = 0 );
	int64_t			getMaxVal( CURRENCY_TYPE const nType ) const;

private:
	int64_t			m_aCurrency[CURRENCY_TYPE_COUNT];
	bool			m_aUpdateSign[CURRENCY_TYPE_COUNT];
	bool			m_bNeedSync;
};

#endif	//__TPOC_CURRENCY_H__
