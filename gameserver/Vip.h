#ifndef __VIP_H__
#define __VIP_H__
#include "ExtSystemBase.h"

class CVip:
	public CExtSystemBase
{
public:
	CVip();
	~CVip();

	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void			OnCleanUp();
	virtual void			OnUpdate( int64_t curTick );
	virtual void			OnDaySwitch( int32_t nDiffDays );

public:
	void					AddVipAttr();
	bool					CanFreeFlying();
	int32_t					GetOpenBagRate();
	int32_t					GetExpRate();
	int8_t					GetVipLevel();
	int32_t					AddDailyTaskTimes();
	void					AddVipExp( int32_t VipExp );
	int32_t					GetMaxVipLevel() const;
	int32_t					GetAddPetDeportCount();
	bool					UseVipTiYanCard();
	void					SendVipInfo();
	int8_t					GetVipType();
	int32_t					GetHallOfFameBuyTimes();
	void					GetVipGiftIconState( IconStateList& IconList );
	bool					CanSiteRevive();
private:
	int32_t					OnBuyVipCard( Answer::NetPacket *inPacket );
	int32_t					OnGetVipGift( Answer::NetPacket *inPacket );
	int32_t					OnGetVipCardGift( Answer::NetPacket *inPacket );
	void					SubVipExp( int32_t VipExp );
	int32_t					GetVipExp();
	void					AddVipTime( int32_t Seconds );
	int32_t					GetVipEndTime();
	void					SetVipUsed( int8_t VipId );
	bool					IsUsedTiYanCard();
	void					CheckVipEnd( int64_t curTick );
	void					BuyGongGao( int32_t GongGaoId, int8_t VipType, int8_t VipLevel );
	void					TiYanVipGongGao();

	void					SendVipGiftIcon();
	ShowIcon				GetVipGiftIconStu();

private:
	int32_t					m_VipEndTime;							//vip到期时间
	int32_t					m_UsedCard;								//已使用过的vip卡
	int64_t					m_LastUpdataTick;						
};

#endif