#ifndef __C_GOBLIN_H__
#define __C_GOBLIN_H__

#include "ExtSystemBase.h"
#include "DataStruct.h"
#include "DataStructs.h"

class CGoblin : public CExtSystemBase
{
public:
	CGoblin();
	virtual ~CGoblin();

	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			OnCleanUp();
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	int32_t				GetAddAttrRate( int32_t nType );
	bool				AddGoblinRes( int8_t nType, int32_t Values );
	void				SendAllGoblinInfo();
	int32_t				OnGoblinLevelUp( Answer::NetPacket *inPacket );
	void				SendGoblinInfo( int32_t nType );
	void				AddChrAttr();
	void				AppendInfo( Answer::NetPacket *packet );

	// ShouHu Refining
	void				SendAllShouHuRefiningInfo();
	void				AddShouHuChrAttr();
	void				AppendShouHuInfo( Answer::NetPacket *packet );
	int32_t				GetShouHuSuitId();
	int32_t				OnShouHuRefiningLevelUp( Answer::NetPacket *inPacket );
	void				SendShouHuRefiningInfo( int32_t nType );

	// Wing Equip Polish
	void				SendAllWingEquipPolishInfo();
	void				AddWingEquipPolishChrAttr();
	void				AppendWingEquipPolishInfo( Answer::NetPacket *packet );
	int32_t				GetWingEquipPolishSuitId();
	int32_t				OnWingEquipPolishLevelUp( Answer::NetPacket *inPacket );
	void				SendWingEquipPolishInfo( int32_t nSlot );

	// MoFu ZhuNeng
	void				SendAllMoFuZhuNengInfo();
	int32_t				GetMoFuChrAttr( int32_t Slot );
	int32_t				OnMoFuZhuNeng( Answer::NetPacket *inPacket );
	void				SendMoFuZhuNengInfo( int32_t nSlot );

	// Wing Equip Refining
	void				SendAllWingEquipRefiningInfo();
	void				AddWingEquipRefiningChrAttr();
	void				AppendWingEquipRefiningInfo( Answer::NetPacket *packet );
	int32_t				GetWingEquipRefiningSuitId();
	int32_t				OnWingEquipRefiningLevelUp( Answer::NetPacket *inPacket );
	void				SendWingEquipRefiningInfo( int32_t nSlot );
	int32_t				GetWingEquipRefiningAttr( int32_t nSlot );

	// Vip Equip Pos Level
	void				SendAllVipEquipPosLevelInfo();
	void				AddVipEquipPosLevelCharAttr();
	void				SendVipEquipPosLevelInfo( int32_t nSlot );
	int32_t				GetVipEquipPosLevelSuitId();
	int32_t				OnVipEquipPosLevellUp( Answer::NetPacket *inPacket );

private:
	bool				IsGoblinType( int32_t nType );
	bool				IsLeftType( int32_t nType );
	int32_t				GetSuitId( int32_t IsLeft );

	std::map<int32_t, GoblinInfo>	m_GoblinInfoMap;
	std::map<int32_t, int32_t>	m_ShouHuRefiningLeveMap;
	std::map<int32_t, int32_t>	m_WingEquipPolishMap;
	std::map<int32_t, int32_t>	m_MoFuZhuNengMap;
	std::map<int32_t, int32_t>	m_WingEquipRefiningMap;
	std::map<int32_t, int32_t>	m_VipEquipPosLevelMap;
};

#define GOBLIN		Answer::Singleton<CGoblin>::instance()

#endif
