// ����ʵ��
#ifndef __TPOC_EQUIP_H__
#define __TPOC_EQUIP_H__

#include "CfgData.h"
#include "ExtSystemBase.h"

// Equipment slot constants
#define EQUIP_SLOT_TOTAL_NUM		10
#define GEM_SLOT_NUM			3
#define MAX_EQUIP_POS		EQUIP_SLOT_TOTAL_NUM
#define MAX_GEM_SLOT		GEM_SLOT_NUM
#define MAX_SHENYAO_POS		EQUIP_SLOT_TOTAL_NUM


enum EquipGongGaoType
{
	UP_EQUIP_STAR		= 1,		//���ǹ���
	UP_EQUIP_QUALITY	= 2,		//��Ʒ����	
	UP_EQUIP_GRADE		= 3,		//��������
	OPEN_GEM_HOLE		= 4,		//���׹���
	XIANG_QIAN_GEM		= 5,		//��Ƕ����
	UP_QUALITY_OPEN_HOLE= 6,		//��Ʒ������ʯ��
	ITEM_COMBI			= 7,		//�ϳ�
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

	// ========== ���°汾���¼ӿ� ==========
	void				loadGemString( const std::string& strGem );
	void				loadPosLevelString( const std::string& strPos );
	void				LoadStrengthenString( const std::string& strStrengthen );
	void				LoadShenYaoString( const std::string& strShenYao );
	std::string			saveGemString() const;
	std::string			savePosLevelString() const;
	std::string			saveStrengthenString() const;
	std::string			saveShenYaoString() const;
	int32_t				GetEquipAllGemLevel() const;
	int32_t				GetEquipAllUpPosLevel() const;
	int32_t				GetEquipSlotPlace( int8_t nSlot ) const;
	int32_t				GetEquipStar( int8_t nSlot ) const;
	int32_t				GetEquipSuitId( int8_t nSlot ) const;
	int32_t				GetEquipType( int8_t nSlot ) const;
	int32_t				GetGemOpenLevel() const;
	int32_t				GetGongMingSuitId() const;
	int32_t				CheckGongMingSuitBuff() const;
	int32_t				GetMaxPolishLevel() const;
	int32_t				GetMaxRefiningLevel() const;
	int32_t				GetMoFuSuitLevel( int32_t nSuitId ) const;
	int32_t				GetPosLevel( int8_t nSlot ) const;
	int32_t				GetQualityCount( int8_t nQuality ) const;
	int32_t				getStrenGthenLevel( int8_t nSlot ) const;
	int32_t				GetTeJieValue( int32_t nSlot ) const;
	int32_t				GetWeaponBless() const;
	int32_t				GetWingEquipCount3SuitId() const;
	int32_t				GetWingEquipCount6SuitId() const;
	int32_t				GetCount6SuitId() const;
	int32_t				GetCount12SuitId() const;
	int32_t				GetAddGemCount() const;
	int32_t				HaveQualityGradeEquipCount( int32_t nQuality, int32_t nGrade ) const;
	int32_t				GetGongMingBuffBattle() const;
	bool				IsAllPosLevel() const;
	bool				IsAllPosTop() const;
	int32_t				SetWeaponBless( int32_t nVal );
	void				checkGongMingSuit();
	int32_t				CheckSuitId( int32_t nSuitId ) const;
	void				clearGemInfo();
	void				broadcastItemCombi( int32_t nItemId, int8_t nItemClass );
	void				broadcastGemLevelUp( int8_t nEquipSlot, int8_t nHolePos, int32_t nGemId );
	std::vector<int32_t> getCanDropEquipSlots() const;
	void				SendPosLevelInfo();
	void				SendShenYaoPosLevelInfo();
	void				SendStrenGthenInfo();
	void				PackageShenYaoPosLevelUp( Answer::NetPacket* packet ) const;
	void				updateEquipGem( int8_t nSlot, int32_t nGemId, int8_t nHoleIndex );
	void				updateEquipStar( int8_t nSlot, int32_t nStar );
	void				AddStrengthenAttr();
	void				addPosLevelAttr();
	void				addShenYaoPosAttr();

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
	// ========== ���°汾�¼����� ==========
	int32_t				onBackEquip( Answer::NetPacket* inPacket );
	int32_t				onEquipStrenGthen( Answer::NetPacket* inPacket );
	int32_t				onEquipUpPhase( Answer::NetPacket* inPacket );
	int32_t				onEquipUpPos( Answer::NetPacket* inPacket );
	int32_t				onGemAdd( Answer::NetPacket* inPacket );
	int32_t				onGemLevelUp( Answer::NetPacket* inPacket );
	int32_t				onGemOpenHole( Answer::NetPacket* inPacket );
	int32_t				onGemRemove( Answer::NetPacket* inPacket );
	int32_t				onMoFuDuiHuan( Answer::NetPacket* inPacket );
	int32_t				onMoFuHuiShou( Answer::NetPacket* inPacket );
	int32_t				onRelieveBind( Answer::NetPacket* inPacket );
	int32_t				onShenYaoPosLevelUp( Answer::NetPacket* inPacket );
	int32_t				OnXinMoEquipHuiShou( Answer::NetPacket* inPacket );


//�±�ʯ�淨
private:
	int32_t				OnNewEquipAddGem( Answer::NetPacket *inPacket );
	int32_t				OnNewEquipRemoveGem( Answer::NetPacket *inPacket );
	int32_t				OnNewEquipOpenHole( Answer::NetPacket *inPacket );

	bool				CanAddGem( NEW_GEM_TYPE GemType, int8_t EquipType );
	void				SendOpenGemHole( int8_t HoleIndex,  int8_t BagType, int32_t slot );
	void				UpQualityOpenGemHole( MemEquip& equip, const CfgEquipUpQuality* pCfgUpQuality, int8_t BagType, int32_t slot );
	void				CombiGongGao( int32_t ItemId, int8_t ItemClass );

//����
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

	void				checkGemSlotOpen();							// ��ⱦʯ�׿���״̬

	// ��װ���
	void				checkEquipGoalStarLevel();
	void				checkEquipGoalGemLevel();
	void				checkEquipSuit();

private:
	MemChrBag			m_vMemEquip[EQUIP_SLOT_TOTAL_NUM];
	int32_t				m_vMemGem[EQUIP_SLOT_TOTAL_NUM][GEM_SLOT_NUM];

	Int32List			m_lstDirty;										// ������

	int32_t				m_nEquipGoalStarLevel;							// ��װǿ���ȼ�
	int32_t				m_nEquipGoalGemLevel;							// ��װ��ʯ�ȼ�

	// ========== ���°汾����� ==========
	int32_t				m_vMemStrengthen[EQUIP_SLOT_TOTAL_NUM];			// ǿ���ȼ�
	int32_t				m_vMemPosLevel[EQUIP_SLOT_TOTAL_NUM];			// ��λ�ȼ�
	int32_t				m_vShenYaoEquipPos[MAX_SHENYAO_POS];							// ���ε�λ
	int32_t				m_vMemMoFu[EQUIP_SLOT_TOTAL_NUM];				// ħ������

	typedef std::map<int32_t, int32_t> EquipSuitMap;
	EquipSuitMap		m_mEquipSuit;									// ��װ����
};

#endif	//__TPOC_EQUIP_H__
