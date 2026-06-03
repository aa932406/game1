#ifndef __TOU_ZHI_H__
#define __TOU_ZHI_H__
#include "ExtSystemBase.h"

class CTouZi
	:public CExtSystemBase
{
public:
	CTouZi();
	~CTouZi();
	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void			OnCleanUp();
	virtual void			OnUpdate( int64_t curTick );
	virtual void			OnDaySwitch( int32_t nDiffDays );
	
	void					GetTouZiIconState( IconStateList& IconList );
public:
	void					SendTouZiIcon();
	ShowIcon				GetTouZiIconStu();

private:
	int32_t					OnGetTouZiReward( Answer::NetPacket *inPacket );
	int32_t					OnAskTouZiInfo( Answer::NetPacket *inPacket );
	int32_t					OnTouZi( Answer::NetPacket *inPacket );
	void					SendMoonCardTouZiInfo();
	void					SendLevelUpTouZiInfo();
	void					SendGetRewardSucceed( int8_t Type, int16_t Index );
	int32_t					GetMoonCardReward( int16_t Index );
	int32_t					GetLevelUpReward( int16_t Index );
	int32_t					GetMoonCardStartTime();
	int32_t					GetLevelUpTouZhiValues();
	bool					CheckLevelUpTouZiValues( int32_t Values );
	int32_t					GetDiffDay();
	void					AddTouZhiRecord( int8_t Type, int8_t MoneyType, int32_t MoneyValues );
	int32_t					GetRewardCount();
	void					broadcastTouZi( int32_t ID);
	bool					IsHaveMoonCardReward();
private:
	int32_t					m_TouZiValues;			//等级投资金额
	int32_t					m_MoonCardStartTime;	//月卡投资时间
	RecordMap				m_MoonCardRecord;		//月卡投资领取记录
	RecordMap				m_LevelUpRecord;		//等级投资领取记录
};

#endif
