#ifndef __JUE_WEI_H__
#define __JUE_WEI_H__
#include "ExtSystemBase.h"

class CJueWei
	:public CExtSystemBase
{
public:
	CJueWei();
	~CJueWei();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
private:
	int32_t			OnDonateMoney( Answer::NetPacket *inPacket );
	int32_t			OnAskDonateInfo( Answer::NetPacket *inPacket );
	int32_t			OnReceiveRank( Answer::NetPacket *inPacket );
	void			SendRankInfo();
	void			SendDonateMoney();
	void			SendDonateMoneyToGlobal();
	void			SetRank( int32_t Rank );
	int32_t			GetRank();
	void			GongGao( int8_t GongGaoType, int64_t Values );
	void			AddCharAttr();
	int32_t			onAskJueWeiLevelUp( Answer::NetPacket *inPacket );
	int32_t			onRequestJueWeiInfo( Answer::NetPacket *inPacket );
	void			sendJueWeiInfo();
public:
	int8_t			GetJueWei();
	int32_t			GetBattleValues();
	void			RequestDonateRank();
private:
	int32_t			m_Rank;
	int64_t			m_DonateMoney;
	int32_t			m_FinishLogin;
};

#endif