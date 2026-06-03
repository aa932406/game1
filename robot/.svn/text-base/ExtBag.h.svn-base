#ifndef __EXT_BAG_H__
#define __EXT_BAG_H__

#include "ExtSystemBase.h"

class CRobot;
class CExtBag : public CExtSystemBase
{
public:
	CExtBag();
	virtual ~CExtBag();

public:
	virtual void		OnCleanUp();
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onBagInfo( Answer::NetPacket* inPacket );
	int32_t				onBagDirty( Answer::NetPacket* inPacket );
	int32_t				onBagItems( Answer::NetPacket* inPacket );
	int32_t				onEquips( Answer::NetPacket* inPacket );

public:
	void				SendUseMedicine( int8_t nType = 2 );

private:
	void				checkAddItem( int32_t nSlot );
	int8_t				getEquipPlace( int8_t nEquipType );
	void				sendDressEquip( int32_t nBagSlot, int8_t nEquipSlot );
	void				sendUseItem( int32_t nSlot );
	void				sendBuyItem( int32_t nIndex, int32_t nCount );

private:
	MemChrBag			m_equip[EQUIP_SLOT_TOTAL_NUM];
	MemChrBag			m_bag[MAX_BAG_SLOT_NUM];
	int32_t				m_nBagSize;
	int32_t				m_nCanOpenSize;
	int32_t				m_nLeftTime;

};

#endif	//__EXT_BAG_H__
