#ifndef __VIP_H__
#define __VIP_H__
#include "ExtSystemBase.h"
#include <map>
#include <string>

struct VipLuckyDrop
{
	VipLuckyDrop() : CanDropOrdinaryTimes(0), DropOrdinaryTimes(0),
		CanDropSpecialTimes(0), DropSpecialTimes(0) {}
	int32_t CanDropOrdinaryTimes;
	int32_t DropOrdinaryTimes;
	int32_t CanDropSpecialTimes;
	int32_t DropSpecialTimes;
};

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
	bool					AddVipLuckyDrop( int32_t Type, int32_t Times );
	int32_t					GetVipEquipBackRate();
	int32_t					GetTreasureTimes();
	int32_t					GetCycleTowerTimes();
	int32_t					GetStorePage();
	bool					HaveVipPrivilege();
	bool					CanAuction();
	void					GetClubDrop( int32_t Mid );
	void					GetLuckDropType( int32_t Mid );
	void					AddClubDropTime();
	void					SendClubInfo();
	bool					IsClub() const { return m_Club > 0; }

private:
	int32_t					OnBuyVipCard( Answer::NetPacket *inPacket );
	int32_t					OnGetVipGift( Answer::NetPacket *inPacket );
	int32_t					OnGetVipCardGift( Answer::NetPacket *inPacket );
	int32_t					OnEnterClub( Answer::NetPacket *inPacket );
	int32_t					OnBuyDropTimes( Answer::NetPacket *inPacket );
	int32_t					OnBuyAllVipCard( Answer::NetPacket *inPacket );
	void					SubVipExp( int32_t VipExp );
	int32_t					GetVipExp();
	void					AddVipTime( int8_t VipType, int32_t Seconds );
	int32_t					GetVipEndTime();
	void					SetVipUsed( int8_t VipId );
	bool					IsUsedTiYanCard();
	void					CheckVipEnd( int64_t curTick );
	void					BuyGongGao( int32_t GongGaoId, int8_t VipType, int8_t VipLevel );
	void					TiYanVipGongGao();
	bool					GetVipFlg( int8_t VipType );
	void					SendVipGiftIcon();
	ShowIcon				GetVipGiftIconStu();
	void					OnLoadVipEndTime( const std::string& VipEndTime );
	std::string				OnSaveVipEndTime();
	void					LoadDropString( const std::string& p_String );
	std::string				SaveDropString();
	void					SendLuckDrop( int32_t nType, MemChrBag stu, int32_t Mid );
	void					AddDropTimes( int32_t Type, int32_t VipLevel );
	int32_t					GetDropVipLevel( int32_t Type );

private:
	int32_t					m_PlatinumVipEndTime;					//铂金VIP到期时间
	int32_t					m_DiamVipEndTime;						//钻石VIP到期时间
	int32_t					m_StarVipEndTime;						//星辰VIP到期时间
	int32_t					m_UsedCard;								//已使用过的vip卡
	int64_t					m_LastUpdataTick;
	std::map<int, VipLuckyDrop> m_VipLuckyDropMap;
	int32_t					m_Club;									//Club状态
	int32_t					m_ClubDropTimes;						//Club掉落次数
	int32_t					m_BuyTimes;								//购买次数
	int32_t					m_nVip7Time;							//VIP7时间
	int32_t					m_nVip10Time;							//VIP10时间
};

#endif
