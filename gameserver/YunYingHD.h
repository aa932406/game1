#ifndef __YUN_YING_HD_H__
#define __YUN_YING_HD_H__
#include "ExtSystemBase.h"
class CYunYingHD
	:public CExtSystemBase
{
public:
	CYunYingHD();
	~CYunYingHD();
	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void			OnCleanUp();
	virtual void			OnUpdate( int64_t curTick );
	virtual void			OnDaySwitch( int32_t nDiffDays );
private:
	int32_t					OnGetShouChongReward( Answer::NetPacket *inPacket );
	int32_t					OnGetBuyTeHuiItem( Answer::NetPacket *inPacket );
	int32_t					OnGetEveryDayChongZhiGift( Answer::NetPacket *inPacket );
	int32_t					OnGetThreePetGift( Answer::NetPacket *inPacket );
	int32_t					OnGetTotalChongZhi( Answer::NetPacket *inPacket );
public:
	void					SendShouChongIcon();
	void					SendShouChongInfo();
	void					GetShouChongIconState( IconStateList& IconList );

	void					SendTeHuiInfo();
	void					SendTeHuiIcon();
	void					GetTeHuiIconState( IconStateList& IconList );

	void					SendEveryDayChongZhiInfo( int8_t nType = 3 );
	void					SendEveryDayChongZhiIcon( int8_t nType = 3 );
	void					GetEveryDayChongZhiIconState( IconStateList& IconList );

	void					SendThreePetGiftIcon();
	void					GetThreePetGiftIconState( IconStateList& IconList );
	ShowIcon				GetThreePetGiftIconStu();

	void					SendTotalChongZhiIcon();
	void					SendTotalChongZhiInfo();
	void					GetTotalChongZhiIconState( IconStateList& IconList );
	ShowIcon				GetTotalChongZhiIconStu();
	void					AddTotalChongZhiCount( int32_t AddCount );
	int32_t					HaveTotalChongZhiRewardCount();
	bool					AllGetTotalChongZhiReward();
public:
	// === Missing methods from decompiled code ===
	int32_t					getTeHuiLimitTime();
	void					checkTeHuiTime();
	bool					CanShowEveryChongZhiIcon();
	int32_t					getEveryDayChongZhiIcon( int8_t nType );
	bool					HaveEveryDayChongZhiGiftCount( int8_t nType, int32_t& Count );

	void					GetMobilePhoneGiftIconState( IconStateList& IconList );
	void					SendMobilePhoneGiftIcon();

	void					GetAdultGiftIconState( IconStateList& IconList );
	void					SendAdultGiftIcon();

	void					SuperMemberRecharge( int32_t nGold );
	void					GetSuperMemberIconState( IconStateList& IconList );

	void					OnZeroBuyPetOpen();
	void					SendZeroBuyPetIcon();
	void					GetZeroBuyPetIconState( IconStateList& IconList );

private:
	int32_t					OnGetMobilePhoneGift( Answer::NetPacket *inPacket );
	int32_t					OnDBGetMobilePhoneGift( Answer::NetPacket *inPacket );
	int32_t					OnGetZeroBuyPetGift( Answer::NetPacket *inPacket );

	ShowIcon				GetMobilePhoneGiftIconStu( int32_t nIcon );
	ShowIcon				GetAdultGiftIconStu( int32_t nIconId );
	ShowIcon				GetZeroBuyPetIconStu();

	int8_t					GetShouChongState();
	ShowIcon				GetShouChongIconStu();

	ShowIcon				GetTeHuiIconStu();
	bool					IsHaveTeHuiGift();

	ShowIcon				GetEveryDayChongZhiIconStu( int8_t nType = 3 );
	bool					IsHaveEveryDayChongZhiGift();

	void					GongGao( int32_t GongGaoId );

	int32_t					m_TotalChongZhiDay;
	int32_t					m_nLastTeHui;
};

#endif