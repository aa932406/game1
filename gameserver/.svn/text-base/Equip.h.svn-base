// 道具实体
#ifndef __TPOC_EQUIP_H__
#define __TPOC_EQUIP_H__

#include "CfgData.h"
#include "ExtSystemBase.h"

enum EquipGongGaoType
{
	UP_EQUIP_STAR		= 1,		//升星公告
	UP_EQUIP_QUALITY	= 2,		//提品公告	
	UP_EQUIP_GRADE		= 3,		//升级公告
	OPEN_GEM_HOLE		= 4,		//开孔公告
	XIANG_QIAN_GEM		= 5,		//镶嵌公告
	UP_QUALITY_OPEN_HOLE= 6,		//提品开启宝石孔
	ITEM_COMBI			= 7,		//合成
};

class Player;
class CExtEquip : public CExtSystemBase
{
public:
	CExtEquip();
	virtual ~CExtEquip();

public:
	virtual void		OnCleanUp();
	virtual void		OnLoadFromDB( const PlayerDBData& dbData );
	virtual void		OnSaveToDB( PlayerDBData& dbData );
	virtual	void		OnUpdate( int64_t curTick );
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onRequestEquipInfo( Answer::NetPacket* inPacket );
	int32_t				onEquipDress( Answer::NetPacket* inPacket );
	int32_t				onEquipUnDress( Answer::NetPacket* inPacket );
	int32_t				onEquipUpGrade( Answer::NetPacket *inPacket );
	int32_t				onEquipUpStar( Answer::NetPacket *inPacket );
	int32_t				onEquipUpQuality( Answer::NetPacket *inPacket );
	int32_t				onEquipAddGem( Answer::NetPacket *inPacket );
	int32_t				onEquipRemoveGem( Answer::NetPacket *inPacket );
	int32_t				onEquipItemCombi( Answer::NetPacket *inPacket );
	int32_t				onEquipExchangeStar( Answer::NetPacket* inPacket );
	int32_t				onUpXunZhangLevel( Answer::NetPacket * inPacket );
	void				UpStarSuccess( MemEquip& equip, int8_t nBagType, int8_t nPos, MemChrBag& bagItem, bool bBind  );


//新宝石玩法
private:
	int32_t				OnNewEquipAddGem( Answer::NetPacket *inPacket );
	int32_t				OnNewEquipRemoveGem( Answer::NetPacket *inPacket );
	int32_t				OnNewEquipOpenHole( Answer::NetPacket *inPacket );

	bool				CanAddGem( NEW_GEM_TYPE GemType, int8_t EquipType );
	void				SendOpenGemHole( int8_t HoleIndex,  int8_t BagType, int32_t slot );
	void				UpQualityOpenGemHole( MemEquip& equip, const CfgEquipUpQuality* pCfgUpQuality, int8_t BagType, int32_t slot );
	void				CombiGongGao( int32_t ItemId, int8_t ItemClass );

//公告
	void				EquipOpenGemHoelGongGao( int32_t EquipBaseId, int8_t HoleIndex,EquipId_t EquipId );
	void				EquipAddGemGongGao( int32_t EquipBaseId ,int32_t GemId, EquipId_t EquipId );
	void				EquipUpGradeGongGao( int32_t NewBaseId, int32_t OldBaseId, EquipId_t EquipId );
	void				EquipUpQualityGongGao( int32_t NewBaseId, int32_t OldBaseId, EquipId_t EquipId );
	void				EquipUpStarGongGao( MemEquip& Equip );
	void				EquipUpQualityOpenGemHole( MemEquip& Equip, int8_t HoleIndex );
public:
	int32_t				GetGemAddEffectTypeRate( NEW_GEM_TYPE GemType );

public:
	int32_t				GetMaxEquipedStar() const;
	const MemChrBag&	GetEquipSlot( int8_t nSlot ) const;
	void				PackageEquipInfo( Answer::NetPacket* packet ) const;
	void				PackageGemInfo( Answer::NetPacket* packet ) const;
	void				SendEquipInfo();
	void				SendGemInfo();
	void				SendGemInfo( int8_t nPos, int8_t nSlot );

	void				AddCharAttr();

	void				GetDropEquip( Player *pKiller, int32_t DropCount, int32_t DropRate, MemChrBagVector &DropItemVt, int32_t Mid  );
	int32_t				GetSuitEquipCount();
	int32_t				GetLowestStar();
	int32_t				GetEquipAllStar( int32_t& Battle);
	int32_t				GetEquipAllCount();
	int32_t				GetEquipBaseBattle();
	void				GetEquipInfo( int32_t& HoleCount, int32_t& BattleGemCount, int32_t& GemCount, int32_t& EquipQualityBattle,int32_t& GemLevelBattle );
	int32_t				HaveLevelEquipCount( int32_t Level );
	int32_t				HaveStarEquipCount( int32_t Star );
private:
	float				GetUpStarAttrRate( int8_t Star );

	int8_t				getGemSlot( int8_t nGemType ) const;
	bool				onEquipExchange( int32_t nBagSlot, int8_t nEquipSlot );
	bool				checkDressEquip( int32_t nBagSlot, int8_t nEquipSlot ) const;
	void				addEquipAttr();
	void				addGemAttr();
	void				addSuitAttr();
	bool				checkEquipPlace( int8_t nEquipType, int8_t nEquipSlot ) const;
	bool				checkCombiItemList( ItemDataList& NeedItemList, Int32Vector& vSlot, int32_t& nCanGiveCount, int32_t& nCanGiveUnBindCount ) const;

	void				addDirty( int32_t nSlot );
	void				checkDirty();
	bool				sendDirty();
	void				clearDirty();
	bool				isGemSlotOpen( int8_t nGemSlot );

	void				checkGemSlotOpen();							// 检测宝石孔开启状态

	// 套装检测
	void				checkEquipGoalStarLevel();
	void				checkEquipGoalGemLevel();
	void				checkEquipSuit();

private:
	MemChrBag			m_vMemEquip[EQUIP_SLOT_TOTAL_NUM];
	int32_t				m_vMemGem[EQUIP_SLOT_TOTAL_NUM][GEM_SLOT_NUM];

	Int32List			m_lstDirty;										// 脏数据

	int32_t				m_nEquipGoalStarLevel;							// 套装强化等级
	int32_t				m_nEquipGoalGemLevel;							// 套装宝石等级

	typedef std::map<int32_t, int32_t> EquipSuitMap;
	EquipSuitMap		m_mEquipSuit;									// 套装数量
};

#endif	//__TPOC_EQUIP_H__
