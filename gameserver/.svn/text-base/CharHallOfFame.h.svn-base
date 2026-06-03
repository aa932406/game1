#ifndef __CHAR_HALL_OF_FAME_H__
#define __CHAR_HALL_OF_FAME_H__

#include "ExtSystemBase.h"

class Player;
class CExtCharHallOfFame : public CExtSystemBase
{
public:
	CExtCharHallOfFame();
	virtual ~CExtCharHallOfFame();

public:
	virtual void		OnCleanUp();
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t	onFight( Answer::NetPacket* inPacket );
	int32_t	onBuyTimes( Answer::NetPacket* inPacket );
	int32_t	onClearCD( Answer::NetPacket* inPacket );
	int32_t	onRequestInfo( Answer::NetPacket* inPacket );
	int32_t onSocialFightResult( Answer::NetPacket* inPacket );
	int32_t onSocialGetReward( Answer::NetPacket* inPacket );
	int32_t onSocialRankRewardInfo( Answer::NetPacket* inPacket );

public:
	bool	IsFunctionOpen() const;
	void	GetIconState( IconStateList& iconList );
	void	SendIconState( int32_t nReward=0 );

private:
	void	sendSocialFight( int32_t nIndex );
	void	sendSocialRequestInfo();
	void	sendSocialRewardResult( int32_t nLastIndex, bool bSuccess );

private:
	int32_t	getFightTimes() const;
	int32_t	getLimitFightTimes() const;
	int32_t getBuyTimes() const;
	int32_t getLimitBuyTimes() const;
	int32_t	getCDTime() const;
	void	addFightTimes();
	void	addBuyTimes();
	void	addCDTime();
	void	clearCDTime();

private:
	//int32_t	m_nCDTime;
};

#endif	//__CHAR_HALL_OF_FAME_H__
