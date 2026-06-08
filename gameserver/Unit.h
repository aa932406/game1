#pragma once

#include "Buff.h"
#include "Entity.h"
#include "Attribute.h"

class Map;

class Unit
	: public Entity
{
public:
	Unit(EntityType entitytype);
	virtual ~Unit() = 0;

public:
	UnitHandle getHandle();

	void update();

	//void addDelayMsg(GameMsgCode msgcode, void *ptr1, void *ptr2, int32_t iparam1, int32_t iparam2, int64_t delay);

	Map* getMap();
	int32_t getMapId();
	int32_t getMapType();

	bool InDungeon() const;
	bool InActivity() const;

	int32_t GetRunnerId() const;
	
	Position getCurrentPixel();
	Position getTargetTile();
	Direction getDirection();

	void leaveTile();
	void setAtTile(Map *pMap, int32_t tx, int32_t ty);//???????
	void setTargetTile(int32_t tx, int32_t ty);
	bool resetDirection( int32_t tx, int32_t ty );

	void instantMove(int32_t tx, int32_t ty, InstanceMoveReason reason);
	void setStand();

	bool updatePosition();
	bool isMoving();

	bool isInRectangle(Position pst1,Position pst2) const;

	int64_t getTick() const;
	int32_t getNow() const;
	tm getLocalNow() const;

	double pixelDistance(Unit *unit);
	int32_t tileDistance(Unit *unit);

	bool isAlive() const;
	//int32_t getHP();
	//virtual void addHP(int32_t addon);
	//void addMP(int32_t addon);
	int32_t struckDamage(int32_t damge, int32_t attackType, UnitHandle launcher);

	//int32_t getBaseAttr(int32_t index);

	int32_t getBuffCount();
	int32_t addBuff(Buff *buff);
	void removeBuff(int32_t buffId);
	void clearDebuff();
	Buff* findBuffBySpecail(int32_t special);
	bool checkBuffBySpecail(int32_t special);
	bool checkBuffIsPDEF(int32_t buffId);
	bool checkBuffIsMDEF(int32_t buffId);
	bool checkBuffIsBeing(int32_t buffId,int32_t special);
	bool HasBuffById(int32_t buffId);
	MemChrBuffVector getPersistBuffs();

	//void addBuffState(BuffState buffState);
	//void removeBuffState(BuffState buffState);
	//bool hasBuffState(BuffState buffState);

	void addFans(int16_t cgindex);
	void removeFans(int16_t cgindex);
	void clearFans();
	void onThrowed();
	int32_t onKickOutMove(int16_t currentX, int16_t currentY, int16_t targetX, int16_t targetY, int16_t finalX, int16_t finalY, Direction direction);

	virtual void reset();
	virtual void refresh() = 0;
	virtual EntityId_t getUnitId() const = 0;
	virtual CharId_t getOwner() const = 0;
	virtual int32_t getLevel() const = 0;
	virtual int32_t getBattle() const = 0;
	virtual int32_t getDeadTime() const;
	//virtual int32_t getAttr(int32_t index) const;
	//virtual int32_t addBuffAttr(int32_t index, int32_t rate, int32_t addon);
	virtual void postDamage(int32_t damge, UnitHandle launcher) = 0;
	virtual bool isFriendSide(Unit *pUnit);
	virtual bool checkSkillTarget(CfgSkill *pCfg, Unit *pUnit);				// ��⼼���Ƿ���Զ�Ŀ��ʩ��
	virtual bool needMapBroadcast();
	virtual Position getCurrentTile();
	virtual void onArriveTarget();
	virtual bool isBoss() const;
	virtual int32_t GetCalLevel() const;

	virtual int32_t GetHurtIncreace() const;	// �˺�����

	int32_t GetPosX() const;
	int32_t GetPosY() const;
	int32_t	GetBaseAttr( CObjAttrs::Index_T const nIdx ) const;
	int32_t	GetAttrValue( CObjAttrs::Index_T const nIdx ) const;
	int32_t	AddAttrValue( CObjAttrs::Index_T const nIdx, int32_t nAddVal );
	int32_t	AddBuffAttrRatio( CObjAttrs::Index_T const nIdx, int32_t nRate );
	int32_t	AddBuffAttrValue( CObjAttrs::Index_T const nIdx, int32_t nAddVal );
	int32_t	AddSpeedBuffRatio( int32_t nRate );
	int32_t	RemoveSpeedBuffRatio( int32_t nRate );

	bool	HasBuffState( CObjState::Index_T const nIdx ) const;
	void	AddBuffState( CObjState::Index_T const nIdx );
	void	RemoveBuffState( CObjState::Index_T const nIdx );

	int32_t	GetHP() const;		// ����ֵ
	int32_t	GetMP() const;		// ����ֵ
	int32_t	GetPP() const;		// ����ֵ
	int32_t	GetXP() const;		// ��ɱֵ

	int32_t	GetMaxHP() const;
	int32_t	GetMaxMP() const;
	int32_t	GetMaxPP() const;
	int32_t	GetMaxXP() const;
	int32_t	GetMoveSpeed() const;

	void	AddHP( int32_t nAddValue );
	void	AddMP( int32_t nAddValue );
	void	AddPP( int32_t nAddValue );
	void	AddXP( int32_t nAddValue );

	void	FillHP( int32_t nPercent = 100 );
	void	FillMP( int32_t nPercent = 100 );
	int32_t	GetDefValue() const;

	int32_t	GetSkillFlag( bool bIncrease = false );
	void	SetSkillFlag( int32_t SkillFlag );

	void	broadcastBuffList();
	void	PacketBuffList( Answer::NetPacket *inPacket );
protected:
	void	resetUnitAttr();
	void	adjustUnitAttr();
	void	adjustAttr( int32_t& nAttr, int32_t nMaxValue, int32_t nMinValue = 0 );
	void	setHP( int32_t nValue );
	void	setMP( int32_t nValue );
	void	setPP( int32_t nValue );
	void	setXP( int32_t nValue );
	//virtual void onDelayGameMsg(GameMsg *msg);
	//virtual void addSecondAttrAddon(int32_t index, int32_t addon);
	virtual void broadcastBasicData();
	
	void broadcastMove();
	void broadcastInstantMove(int16_t finalX, int16_t finalY, InstanceMoveReason reason);
	void broadcastLeave();
	void broadcastKickOutedMove();
	void broadcastThrowed();
	void sendBuffList(int16_t cgindex);
	void broadcastBuffEnd(Int32Vector buffids);
	void fansBroadcast(Answer::NetPacket *inPacket);
	
	//void checkDelayGameMsg();
	void checkBuffList();
	void syncBasicData();

	//void onSkillDelayResult(CfgSkill *cfg, int32_t param1, int32_t param2);

	//void adjustUnitAttr();

	void deathClearBuff();

	double getDirectionSpeed();

	void	SetAttrValue( CObjAttrs::Index_T const nIdx, int32_t nVal );
	void	ResetAttrs();

	void	setNeedSync();
	void	setNeedSyncSelf();

protected:
	Map	*m_pMap;
	//SecondAttr m_secondAttr;
	//SecondAttr m_secondAttrAddon;
	//SecondAttr m_secondAttrBuff;
	//SecondAttr m_secondFormation;    //??????

	UnitAttr m_unitAttr;
	bool m_needSync; 
	bool m_needSyncSelf;
	bool m_bDie;
	int64_t m_throwedTick;
private:
	GameMsgQueue m_delayMsgQueue;

	Position m_currentTile;
	Position m_targetTile;

	Position m_currentPos;
	Position m_targetPos;
	double m_xOffset;
	double m_yOffset;

	Direction m_direction;

	int64_t m_posUpdateTick;
	Buff *m_buffs[MAX_UNIT_BUFF_NUM];
	//int32_t m_buffStates[BS_BUFF_STATE_MAX];


	CObjAttrs	m_baseAttr;				// ��������ֵ
	CObjAttrs	m_buffAttrValue;				// BUFFֱ��ֵ
	CObjAttrs	m_buffAttrRatio;		// BUFF�ٷֱ�ֵ
	CObjState	m_buffStates;

	int32_t		m_nSkillFlag;

	Int16List m_fans;
	Answer::Mutex m_fansLock;
};
