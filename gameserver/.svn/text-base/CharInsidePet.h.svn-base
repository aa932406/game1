/*
* 内置宠（灵兽）
* 与宠物类似，但不能出战，纯加属性的系统
*/
#ifndef __TPOC_CHAR_INSIDE_PET_H__
#define __TPOC_CHAR_INSIDE_PET_H__

#include "CfgData.h"
#include "ExtSystemBase.h"
#include "PetEgg.h"
#include "Pet.h"
#include "ObjPet.h"

class Player;
class CExtCharInsidePet : public CExtSystemBase
{
public:
	CExtCharInsidePet();
	virtual ~CExtCharInsidePet();

public:
	virtual void		OnCleanUp();
	virtual void		OnLoadFromDB( const PlayerDBData& dbData );
	virtual void		OnSaveToDB( PlayerDBData& dbData );
	virtual	void		OnUpdate( int64_t curTick );
	virtual void		OnDaySwitch( int32_t nDiffDays );
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

public:
	void	AddAttrToTarget( Unit* pUnit );
	void	OnLevelUp();
	int32_t GetPoint();
	int32_t GetRank( PET_RANK_TYPE nRankType );
	void	sendBaseInfo();
private:
	int32_t	onRequestInfo( Answer::NetPacket* inPacket );				// 请求信息
//	int32_t	onBaseIllusion( Answer::NetPacket* inPacket );				// 初灵
	int32_t	onGrowIllusion( Answer::NetPacket* inPacket );				// 幻灵
//	int32_t	onLuckyIllusion( Answer::NetPacket* inPacket );				// 幸运
	int32_t	onExpIllusion( Answer::NetPacket* inPacket );				// 武灵
	int32_t	onUseLuckyItem( Answer::NetPacket* inPacket );				// 使用幸运值道具
	int32_t	onUsePhaseItem( Answer::NetPacket* inPacket );				// 使用相性道具		
	int32_t	onBuyExp( Answer::NetPacket* inPacket );					// 购买经验值	
	int32_t	onRequestBaseIllusion( Answer::NetPacket* inPacket );		// 请求初灵信息
	int32_t	onLiBaoIllusion( Answer::NetPacket *inPacket );				// 商城购买礼包幻化

private:
	void	recalAttr();
	void	sendBaseIllusionInfo();
	int8_t	randBaseAttr();
	int32_t	calBaseIllusionTime( int32_t startPoints );
	int32_t	calBaseIllusionCost( int32_t startPoints );
	int32_t	calBaseAttrAddValue( int8_t attr );
	int8_t	calBaseIllusionSpeed();
	void	checkBaseIllusionSpeed();
	void	checkBaseIllusion();
	bool	IsReinTimesLimit() const;
	int32_t	calEggAddExp( const PetEgg& egg ) const;
	int32_t	calEquipAddExp( const MemEquip& equip ) const;
	void	addExp( int64_t nAddExp );
	void	calBaseAttr( CObjAttrs::Index_T nIndex, PET_ATTR startAttr, PET_ATTR growAttr );
	int32_t GetWuLingPoints();


private:
	CPet*			m_pPet;								// 内置宠
	CObjAttrs		m_attrs;							// 属性值列表	

	// 初灵
	int8_t			m_bStartIllusion;					// 初灵修炼状态
	int8_t			m_nAttrType;						// 增加属性
	int32_t			m_nAttrValue;						// 增加值
	int32_t			m_nOnlineTime;						// 在线时间
	int32_t			m_nLeftTime;						// 初灵修炼结束时间（加速机制导致需要计算剩余时间）
	int8_t			m_nSpeed;							// 修炼速度

	// 武灵
	int16_t			m_nBuyExpTimes;						// 购买经验值次数

	int64_t			m_nLastTick;
};

#endif	//__TPOC_CHAR_INSIDE_PET_H__
