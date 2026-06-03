/*
* 宠物系统
* 存放玩家的宠物和宠物蛋信息
*/
#ifndef __TPOC_CHAR_PET_H__
#define __TPOC_CHAR_PET_H__

#include "CfgData.h"
#include "ExtSystemBase.h"
#include "PetEgg.h"
#include "Pet.h"
#include "ObjPet.h"

enum PET_STAND_PLACE
{
	PSP_LEFT	= 0,
	PSP_RIGHT	= 1,
	PSP_DOWN	= 2,
	PSP_SIZE,
};

struct PetPointsSortGreater 
{
	bool operator()( const CObjPet* pLeft, const CObjPet* pRight ) const
	{
		if ( NULL == pLeft || NULL == pRight )
		{
			return false;
		}
		return pLeft->GetPoints() > pRight->GetPoints();
	}
};

class Player;
class CExtCharPet : public CExtSystemBase
{
	typedef std::list<CPet*> PetList;
	typedef std::list<PetEgg*> PetEggList;
public:
	CExtCharPet();
	virtual ~CExtCharPet();

public:
	virtual void		OnCleanUp();
	virtual void		OnLoadFromDB( const PlayerDBData& dbData );
	virtual void		OnSaveToDB( PlayerDBData& dbData );
	virtual	void		OnUpdate( int64_t curTick );
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onRequestPetInfo( Answer::NetPacket* inPacket );		// 请求宠物信息
	int32_t				onFighting( Answer::NetPacket* inPacket );				// 出战
	int32_t				onRest( Answer::NetPacket* inPacket );					// 休息
	int32_t				onZoarium( Answer::NetPacket* inPacket );				// 合体
	int32_t				onZoariumOff( Answer::NetPacket* inPacket );			// 解除合体
	int32_t				onRide( Answer::NetPacket* inPacket );					// 骑乘
	int32_t				onChangeName( Answer::NetPacket* inPacket );			// 宠物改名
	int32_t				onPetRelease( Answer::NetPacket* inPacket );			// 放生宠物
	int32_t				onHatching( Answer::NetPacket* inPacket );				// 孵化
	int32_t				onMutiHatching( Answer::NetPacket* inPacket );			// 批量孵化
	int32_t				onReHatching( Answer::NetPacket* inPacket );			// 重新孵化
	int32_t				onQuickHatching( Answer::NetPacket* inPacket );			// 快速孵化
	int32_t				onStopHatching( Answer::NetPacket* inPacket );			// 停止孵化
	int32_t				onPetEggMove( Answer::NetPacket* inPacket );			// 宠物蛋移动
	int32_t				onEggOpen( Answer::NetPacket* inPacket );				// 打开宠物蛋
	int32_t				onDropEgg( Answer::NetPacket* inPacket );				// 丢弃蛋
	int32_t				onUseExpItem( Answer::NetPacket* inPacket );			// 使用经验道具：圣兽魔晶、经验球、特级经验球
	int32_t				onUsePhaseItem( Answer::NetPacket* inPacket );			// 使用改变相性道具：电浆药水、奇异果
	int32_t				onIllusion( Answer::NetPacket* inPacket );				// 幻化
	int32_t				onUseLuckyItem( Answer::NetPacket* inPacket );			// 使用道具幸运值幻化
	int32_t				onLearnSkill( Answer::NetPacket* inPacket );			// 学习技能
	int32_t				onForgetSkill( Answer::NetPacket* inPacket );			// 遗忘技能
	int32_t				onDeport( Answer::NetPacket* inPacket );				// 仓库存取
	int32_t				onSetKnight( Answer::NetPacket* inPacket );				// 任命骑士
	int32_t				onMoveToBag( Answer::NetPacket* inPacket );				// 打包到背包
	int32_t				onGetFromBag( Answer::NetPacket* inPacket );			// 从背包到幻兽栏
	int32_t				onWearQiShi( Answer::NetPacket *inPacket );				// 佩戴坐骑
	int32_t				onLiBaoIllusion( Answer::NetPacket *inPacket );			// 商城购买礼包幻化

public:
	void				SendPetInfoList();
	void				SendPetEggPoolInfo();
	bool				AddEgg( int32_t nEggId );
	void				OnAddExp( int64_t nExp, bool bFighting = true );
	int32_t				GetRidePet() const;
	int32_t				GetRidePetPoints() const;
	void				AddTarget( const UnitHandle& target );
	void				RemoveTarget( const UnitHandle& target );
	void				SetTargetTile( int32_t tx, int32_t ty, Direction dir );
	CObjPet*			GetPet( PetId_t nPetId );
	CObjPet*			GetFightPet();
	CObjPet*			GetFightPet( int32_t Index );
	void				GetFightPet( UnitList& outUnits );
	CObjPet*			GetZoariumPet();
	void				OnKillMonster( int32_t nLevel );
	void				AddZoariumPetAttr();
	void				OnZoariumPetDie();
	void				AddKnightPetAttr();
	int32_t				GetKnightExpRatio();
	void				FreeAllFightPet( bool AotoFight );
	void				FightLastFightPet();				//出战被特殊地图收回的宠物
	int8_t				GetKnightCount();
	int32_t				GetKnightPoints( PET_KNIGHT Type );

	int32_t				GetBagFreeCount( int8_t nBag );
	void				AddEggs( std::list<int32_t> EggIdList );
	int32_t				GetFreePetFenceCount();
	void				AddPetFromGift( CfgPetGift* pPetGift );
	bool				IsTopPet( CObjPet* pPet ) const;
	bool				RemovePet( CObjPet* pPet, bool bDel=true );
	void				RecalPetsAttr();

	PetEgg*				GetEgg( int32_t nSlot );
	bool				RemoveEgg( int32_t nSlot );
	bool				RemoveEgg( const Int32List& slotList );
	void				ForceSendDirty();
	void				ReviveAllPet();
	int32_t				GetAliveFightPetCount();
	void				DivideHurt( int32_t Damage );
	int32_t				GetEggBagAddHatchBagFreeCount();
	bool				AddHatchBag( int32_t PetId );
	int32_t				GetKnightEffectValue( int8_t Knight );
	void				AddMoveSpeed();
	void				AddKnightPetAttrToPet( CObjPet *TarPet );
	void				AddKnightPetHp( int32_t AddValues );
	int32_t				UnSetKnightBuyJueWei();
	void				ZoariumPetDame( int32_t Dame, UnitHandle launcher );
	void				AddQiShiAttr();
	int32_t				GetQiShiAddBattle();
	int32_t				GetQiShiCount();
	int32_t				HavePetCountByPoints( int32_t Points );
private:
	bool				addPet( CObjPet* pPet, int8_t nBagType );
	PetEgg*				getEgg( int8_t nBag, int32_t nSlot );
	int32_t				addEgg( int8_t nBag, const PetEgg& egg );
	bool				removeEgg( int8_t nBag, int32_t nSlot );
	bool				removeEgg( int8_t nBag, const Int32List& slotList );
	bool				getEggList( int8_t nBag, const Int32List& inList, PetEggList& outList );
	int32_t				getEmptyEggPos( int32_t nBag ) const;
	//void				cleanEmptyEggPos( int8_t nBagType );
	void				ridePet( CObjPet* pPet );
	void				checkHatchPool( int8_t nBag, int32_t nTime, int32_t nNow );
	void				appendEggInfo( Answer::NetPacket* packet, int32_t& nCount, int8_t nBag );
	void 				sendPetEggInfo( const PetEgg& egg );
	void				addPetEggDirty( PetEgg* pEgg );
	void				sendPetEggDirty();
	void				checkPetEggDirty();
	void				initEggBag( int8_t nBag, int32_t nSize );
	void				cleanEggBag( int8_t nBag, int32_t nSize );
	PetEgg*				getEggBagPool( int8_t nBag );
	const PetEgg*		getEggBagPool( int8_t nBag ) const;
	int32_t				getEggBagSize( int8_t nBag ) const;
	void				savePets( DBPetList& petList );
	void				saveEggBag( int8_t nBag, DBPetEggList& eggList );

	void				cleanPet();
	void				petBorn( PetEgg& egg );

	void				sendPetList();
	void				sendPetInfo( const PetList& pList );

	void				getEggPet( PetList& pList, int8_t nBag );

	int32_t				getMaxFightPet() const;
	bool				addFightPet( CObjPet* pPet );
	int32_t				Fighting( CObjPet* pPet );
	void				removeFightPet( CObjPet* pPet );
	void				initKnight();

	void				addExpToFightPet( int64_t nAddVal );
	void				addExpToAllPet( int64_t nAddVal );

	void				broadcastMapPetFighting( CObjPet* pPet );

	void				CheckMagMainPet();											//检测主战法师

	void				AddSoul( int64_t CurTick );


private:
	int32_t				m_nFightingCount;											// 出战宠物个数
	int32_t				m_nFightingCountMax;										// 出战宠物个数

	CObjPet*			m_pRidePet;													// 当前骑乘的宠物

	CObjPet*			m_vFightPet[PSP_SIZE];										// 出战宠物
	CObjPet*			m_vAllPet[PET_LIST_SIZE];									// 幻兽栏
	CObjPet*			m_vLastFightPet[PSP_SIZE];									// 特殊地图收回的宠物
	int32_t				m_vPetBagSize[PET_BAG_TYPE_SIZE];							// 宠物列表中的数量

	PetEgg				m_vEggBag[PET_EGG_BAG_SIZE];								// 幻兽背包
	PetEgg				m_vHatchPool[PET_HATCH_POOL_SIZE];							// 幻兽孵化池
	PetEgg				m_vMutiHatchPool[PET_MUTI_HATCH_POOL_SIZE];					// 幻兽批量孵化

	CObjPet*			m_vPetKnight[PET_KNIGHT_SIZE];								// 幻兽骑士
	CObjPet*			m_vPetWearQiShi[QI_SHI_COUNT];								// 佩戴的坐骑
	int32_t				m_vKnightAddValue[PET_KNIGHT_SIZE];							// 幻兽骑士具体加成值


	PetEggList			m_nEggDirtyList;
	int64_t				m_nLastTick;
	int64_t				m_nLastAddSoulTick;
};

#endif	//__TPOC_CHAR_PET_H__
