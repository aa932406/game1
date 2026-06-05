/*
* ����ϵͳ
* �����ҵĳ���ͳ��ﵰ��Ϣ
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

	// ========== ���°汾�·��� ==========
	void				OnInitPet();
	void				OnLevelUp();
	void				OnPlayerDie();
	bool				IsFighting() const;
	bool				IsFitting() const;
	bool				IsFunctionOpen() const;
	void				SendPetStatus();
	int32_t				GetSkillBattle();
	int32_t				GetStar() const;
	int32_t				GetHuanHua() const;
	void				AddPetAttr();
	void				clearSummonPet();
	bool				HaveSummonAlive();
	void				addSummonPet( CObjPet* pPet );
	void				removeSummonPet( CObjPet* pPet );
	void				OnSummon( int32_t nPetId );
	void				SummonInfo();

private:
	int32_t				onRequestPetInfo( Answer::NetPacket* inPacket );		// ���������Ϣ
	int32_t				onFighting( Answer::NetPacket* inPacket );				// ��ս
	int32_t				onFight( Answer::NetPacket* inPacket );					// ��ս
	int32_t				onRest( Answer::NetPacket* inPacket );					// ��Ϣ
	int32_t				onZoarium( Answer::NetPacket* inPacket );				// ����
	int32_t				onZoariumOff( Answer::NetPacket* inPacket );			// �������
	int32_t				onRide( Answer::NetPacket* inPacket );					// ���
	int32_t				onChangeName( Answer::NetPacket* inPacket );			// �������
	int32_t				onPetRelease( Answer::NetPacket* inPacket );			// ��������
	int32_t				onHatching( Answer::NetPacket* inPacket );				// ����
	int32_t				onMutiHatching( Answer::NetPacket* inPacket );			// ��������
	int32_t				onReHatching( Answer::NetPacket* inPacket );			// ���·���
	int32_t				onQuickHatching( Answer::NetPacket* inPacket );			// ���ٷ���
	int32_t				onStopHatching( Answer::NetPacket* inPacket );			// ֹͣ����
	int32_t				onPetEggMove( Answer::NetPacket* inPacket );			// ���ﵰ�ƶ�
	int32_t				onEggOpen( Answer::NetPacket* inPacket );				// �򿪳��ﵰ
	int32_t				onDropEgg( Answer::NetPacket* inPacket );				// ������
	int32_t				onUseExpItem( Answer::NetPacket* inPacket );			// ʹ�þ�����ߣ�ʥ��ħ�����������ؼ�������
	int32_t				onUsePhaseItem( Answer::NetPacket* inPacket );			// ʹ�øı����Ե��ߣ��罬ҩˮ�������
	int32_t				onIllusion( Answer::NetPacket* inPacket );				// �û�
	int32_t				onPetHuanHua( Answer::NetPacket* inPacket );			// ���û�
	int32_t				onUseLuckyItem( Answer::NetPacket* inPacket );			// ʹ�õ�������ֵ�û�
	int32_t				onLearnSkill( Answer::NetPacket* inPacket );			// ѧϰ����
	int32_t				onSkillUpLevel( Answer::NetPacket* inPacket );		// �������ܵȼ�
	int32_t				onForgetSkill( Answer::NetPacket* inPacket );			// ��������
	int32_t				onDeport( Answer::NetPacket* inPacket );				// �ֿ��ȡ
	int32_t				onSetKnight( Answer::NetPacket* inPacket );				// ������ʿ
	int32_t				onMoveToBag( Answer::NetPacket* inPacket );				// ���������
	int32_t				onGetFromBag( Answer::NetPacket* inPacket );			// �ӱ�����������
	int32_t				onWearQiShi( Answer::NetPacket *inPacket );				// �������
	int32_t				onLiBaoIllusion( Answer::NetPacket *inPacket );			// �̳ǹ�������û�
	int32_t				onUpStar( Answer::NetPacket* inPacket );				// �������Ǽ�
	int32_t				onDressEquip( Answer::NetPacket* inPacket );			// ���ų��ﵰ
	int32_t				onUnDressEquip( Answer::NetPacket* inPacket );			// ж�³��ﵰ
	int32_t				onFitting( Answer::NetPacket* inPacket );				// ���Ƴ���
	int32_t				onRestPet( Answer::NetPacket* inPacket );				// ���³���
	int32_t				onChangeAi( Answer::NetPacket* inPacket );				// �ı�����

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
	void				FightLastFightPet();				//��ս�������ͼ�ջصĳ���
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

	void				CheckMagMainPet();											//�����ս��ʦ

	void				AddSoul( int64_t CurTick );


private:
	int32_t				m_nFightingCount;											// ��ս�������
	int32_t				m_nFightingCountMax;										// ��ս�������

	CObjPet*			m_pRidePet;													// ��ǰ��˵ĳ���

	CObjPet*			m_vFightPet[PSP_SIZE];										// ��ս����
	CObjPet*			m_vAllPet[PET_LIST_SIZE];									// ������
	CObjPet*			m_vLastFightPet[PSP_SIZE];									// �����ͼ�ջصĳ���
	int32_t				m_vPetBagSize[PET_BAG_TYPE_SIZE];							// �����б��е�����

	PetEgg				m_vEggBag[PET_EGG_BAG_SIZE];								// ���ޱ���
	PetEgg				m_vHatchPool[PET_HATCH_POOL_SIZE];							// ���޷�����
	PetEgg				m_vMutiHatchPool[PET_MUTI_HATCH_POOL_SIZE];					// ������������

	CObjPet*			m_vPetKnight[PET_KNIGHT_SIZE];								// ������ʿ
	CObjPet*			m_vPetWearQiShi[QI_SHI_COUNT];								// ���������
	int32_t				m_vKnightAddValue[PET_KNIGHT_SIZE];							// ������ʿ����ӳ�ֵ


	PetEggList			m_nEggDirtyList;
	// ========== ���°汾����� ==========
	int32_t				m_nStar;												// ���Ǽ�
	int32_t				m_HuanHua;											// �û�
	typedef std::list<CObjPet*> SummonList;
	SummonList			m_lSummons;											// �ٻ�����

	int64_t				m_nLastTick;
	int64_t				m_nLastAddSoulTick;
};

#endif	//__TPOC_CHAR_PET_H__
