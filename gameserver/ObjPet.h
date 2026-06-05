/*
* �������
* �����ڳ������͵�ͼ�еĳ���
*/

#ifndef __TPOC_OBJ_PET_H__
#define __TPOC_OBJ_PET_H__

#include "CfgData.h"
#include "Unit.h"
#include "Pet.h"

#define MAX_PET_EQUIP_SLOT		4		// 宠物装备槽位数
#define MAX_PET_SKILL_SLOT		9		// 宠物技能槽位数

// 宠物状态
enum PET_STATE
{
	PS_REST		= 0,	// ��Ϣ
	PS_FIGHTING	= 1,	// ��ս
	PS_ZOARIUM	= 2,	// ����
	PS_RIDE		= 3,	// ���
};

// ��ս״̬
enum PET_FIGHT_STATE
{
	PFS_AWAY_FROM_MAP	= 0,	// ���ڵ�ͼ��
	PFS_STAND			= 1,	// վ��
	PFS_FOLLOW			= 2,	// ����
	PFS_ATTACK			= 3,	// ����
	PFS_WALK_ATTACK		= 4,	// �ƶ�-����
};

// ���﹫��
enum PET_BROADCAST_TYPE
{
	PBCT_PHASE			= 1,	// ����
	PBCT_GROW_ATTR		= 2,	// �ɳ���ͻ��500
	PBCT_START_ATTR		= 3,	// ��ʼ���Գ���80%
	PBCT_LUCKY			= 4,	// ����ֵ100����
	PBCT_LEARN_SKILL	= 5,	// �û�����츳
	PBCT_SKILL_LEVEL_UP	= 6,	// �츳������3��
};

class CObjPet
	: public Unit
{
	typedef std::list<UnitHandle> UnitHandleList;
public:
	CObjPet();
	virtual ~CObjPet();

public:
	virtual	void	reset();
	virtual void	refresh();
	virtual EntityId_t getUnitId() const;
	virtual CharId_t getOwner() const;
	virtual	int32_t	getLevel() const;
	virtual int32_t	GetCalLevel() const;
	virtual int32_t	getBattle() const;
	virtual bool	isFriendSide(Unit *pUnit);
	virtual bool	checkSkillTarget(CfgSkill *pCfg, Unit *pUnit);				// ��⼼���Ƿ���Զ�Ŀ��ʩ��
	virtual void	postDamage(int32_t damge, UnitHandle launcher);

public:
	void			Init( CPet* pPet, Player* pOwner, bool bAlive = true, int32_t nSoul = 0, PET_STATE state = PS_REST, Direction nDir = LEFT );
	void			SetOwner( Player* pOwner );
	bool			AppendInfo( Answer::NetPacket *packet );
	CPet*			GetPet();
	Player*			GetPlayer();
	int32_t			OnMove(int32_t mapID,int16_t currentX, int16_t currentY, int16_t targetX, int16_t targetY, int16_t finalX, int16_t finalY, Direction direction);
	void			LeaveMap();
	void			EnterMap();
	void			OnLogout();

	PetId_t			GetPetId() const;
	//void			SetPetId( PetId_t nPetId );
	int32_t			GetBaseId() const;
	Job_t			GetPetJob() const;
	bool			IsRidePet() const;
	bool			AliveFlag() const;
	int8_t			GetBagType() const;
	void			SetBagType( int8_t nBagType );
	int8_t			GetKnight() const;
	void			SetKnight( int8_t nKnight );
	int32_t			GetPoints() const;
	int32_t			GetBattle() const;
	int32_t			GetLucky() const;
	PET_PHASE		GetPhase() const;
	void			Die();
	void			Relive();
	bool			IsFighting() const;
	bool			IsZoarium() const;
	bool			IsRide() const;
	bool			IsRest() const;
	void			Fighting();
	void			Zoarium();
	void			Ride();
	void			Rest();
	PET_STATE		GetState() const;
	void			SetState( PET_STATE state );
	void			SetSatandPlace( Direction nDir );
	void			SendPetInfo( bool bSendBase = true );
	void			SendPetStatus();
	void			AppendPetInfo( Answer::NetPacket* packet );
	PetSkillInfo*	GetSkill( SkillId_t nSkill );
	PetSkillInfo*	GetSkillByPos( int8_t nSkillPos );
	bool			LearnSkill( SkillId_t nSkill, int8_t nSkillPos );
	bool			ForgetSkill( SkillId_t nSkill );
	std::string		GetName() const;
	void			ChangeName( const std::string& strName );
	bool			AddExp( int64_t nExp );
	bool			AddSoul( int32_t nMonsterLevel, int32_t SoulLevel );
	void			AddSoul( int32_t AddValues );
	bool			CheckRecord( PET_RECORD record ) const;
	int32_t			AddRecord( PET_RECORD record, int32_t nAddVal = 1 );
	PET_PHASE		ChangePhase( PET_PHASE phase );
	int32_t			GetBaseAttr( PET_ATTR attr ) const;
	bool			CanIllusion( CObjPet* pPet, int8_t nType );
	bool			Illusion( CObjPet* pPet, int8_t nType, int8_t nUseItem );
	bool			UseLuckyItem();

	void			OnLoadFromDB( const DBPet& pet );
	void			OnSaveToDB( DBPet& pet );

	void			AddTarget( const UnitHandle& target );
	void			RemoveTarget( const UnitHandle& target );
	void			ClearTarget();
	void			ResetTargetTile( int32_t tx, int32_t ty, Direction dir );

	bool			IsRegInFamily() const;
	void			SetRegInFamily( FamilyId_t nFamilyId );

	int32_t			GetRankIndex( PET_RANK_TYPE Type );
	int32_t			GetTopRankIndex() const;
	int32_t			GetBattleTianFuLevel();
	int32_t			GetBattleTianFuBattle();

	void			SetMainPet( bool bFlg );
	void			RecalAttr();
	void			ReplyHp( int64_t CurTick );
	void			onDie();

	// ========== 新版本添加方法 ==========
	void			UpStar();
	void			SetFitting( bool bFitting );
	bool			IsFitting() const;
	void			ChangeAi( int8_t nAiState );
	int32_t			GetEquip( int32_t nSlot ) const;
	void			SetEquip( int32_t nSlot, int32_t nEquipId );
	void			CheckSkillOpen();
	int32_t			GetSkillMaxLevel( int8_t nSkillPos ) const;
	void			OnLevelUp();

	int8_t			GetQiShi() const;
	void			SetQiShi( int8_t Pos );
	bool			growAttrIllusionByItem( int8_t	nUseItem );
	int32_t			GetGrowPoints();
	int32_t			GetStar() const;
	void			SetStar( int32_t nStar );
	bool			IsXXoo();
private:
	void			onLevelUp();
	void			recalAttr();
	void			initBaseAttr();
	int32_t			calBaseAttr( PET_ATTR nStart, PET_ATTR nGrow, int32_t nLevel );
	void			addPassiveSkillAttr();

	void			appendAttrInfo( Answer::NetPacket* packet );

	void			checkSwitchMap();
	void			updateFightState();
	void			setFightState( PET_FIGHT_STATE state );
	void			onStand();
	void			onFollow();
	void			onAttack();
	void			onWalkAttack();
	void			changeTarget();
	void			checkFarAway();
	void			checkSpeed();
	void			backToPlayer();
	Position		getFollowTile( int32_t tx, int32_t ty, Direction dir ) const;
	int32_t			calAddBattle( int32_t nIndex ) const;
	void			AddKnightAttr();
	void			AddGemAttr();
	void			sendPetLearnSkill( int32_t nSkill );

	void			broadcastPetPhase( PET_PHASE phase );
	void			broadcastPetLearnSkill( int16_t nSkillId );
	void			broadcastPetSkillLevelUp( int16_t nSkillId, int16_t nSkillLevel );

private:
	Player*			m_pPlayer;
	CPet*			m_pPet;
	PET_STATE		m_nState;						// ���ﵱǰ״̬
	bool			m_bAlive;						// �Ƿ���
	int32_t			m_nSoul;						// ��������ֵ
	int8_t			m_nBagType;						// �洢λ��
	int8_t			m_nKnight;						// ��ʿ
	FamilyId_t		m_nRegistFamily;				// �ڰ�����ע��
	int8_t			m_nQiShi;						// ���������λ��

	UnitHandleList	m_lstTargets;					// ����б�
	UnitHandle		m_target;						// ��ǰĿ��
	PET_FIGHT_STATE	m_nFightState;					// �����ս״̬

	Direction		m_nStandPlace;					// ����վ�ںδ�

	bool			m_bMainPet;						// ���裨��ʦ��ʩ��AOE��ǣ�
	PetSkillInfo*	m_pNextSkill;					// �´�ʩ�ŵļ���
	int64_t			m_nLastSkillTick;				// �ϴ�ʩ�ż���ʱ��
	int64_t			m_nLastReplyHp;					// ��һ�λ�Ѫʱ��

	// ========== 新版本添加成员 ==========
	int32_t			m_vEquip[MAX_PET_EQUIP_SLOT];	// 宠物装备
	int8_t			m_nFitting;						// 是否在共鸣状态
	int8_t			m_AiState;						// AI状态
	int32_t			m_nStar;							// 星级
	PetSkillInfo	m_vSkill[PET_SKILL_BAR_SIZE];	// 宠物技能槽
};

#endif	// __TPOC_OBJ_PET_H__
