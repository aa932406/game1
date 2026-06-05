#pragma once

#include "ExtSystemBase.h"

#ifndef EXCHANGE_RECORD_DEFINED
#define EXCHANGE_RECORD_DEFINED
struct ExchangeRecord
{
	int8_t	nType;
	int16_t	nIndex;
	int32_t	nCount;
};
#endif
#ifndef EXCHANGE_RECORD_LIST_DEFINED
#define EXCHANGE_RECORD_LIST_DEFINED
typedef std::list<ExchangeRecord> ExchangeRecordList;
#endif

class PlayerDBData;

class CExtCharExchange : public CExtSystemBase
{
public:
	CExtCharExchange();
	virtual ~CExtCharExchange();

public:
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t	onAskExchangeInfo( Answer::NetPacket *inPacket );
	int32_t	onExchange( Answer::NetPacket *inPacket );
	void	sendExchangeInfo( int8_t nType );
	int32_t	getExchangeRecord( int8_t nType, int16_t nIndex );
	void	addExchangeRecord( int8_t nType, int16_t nIndex, int32_t nCount );

private:
	ExchangeRecordList	m_lstExchangeRecords;
};
