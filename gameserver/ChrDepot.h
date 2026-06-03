#pragma once

#include "CfgData.h"
#include "DataStruct.h"
#include "ExtSystemBase.h"

class CChrDepot:
	public CExtSystemBase
{
public:
	CChrDepot();
	~CChrDepot();

	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnUpdate( int64_t curTick );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	void				SendDepotInfo();
	void				SendDepotCurrency();
	void				SendDepotItem();

	void				AddCharAttr();
private:
	void				CleanUp();
	int32_t				OnGetDepotItem( Answer::NetPacket *inPacket );
	int32_t				OnSaveItemToDepot( Answer::NetPacket *inPacket );
	int32_t				OnGetDepotCurrency( Answer::NetPacket *inPacket );
	int32_t				OnSaveDepotCurrency( Answer::NetPacket *inPacket );
	int32_t				OnSortDepot( Answer::NetPacket *inPacket );
	int32_t				OnOpenDepotSlot( Answer::NetPacket *inPacket );

	int32_t				GetCurrency( CURRENCY_TYPE const Type );
	void				AddDirty( int32_t Slot );
	void				CheckDirty();
	bool				SendDirty();
	void				ClearDirty();

	int32_t         	GetDepotSize();
	bool				IsSlotValid( int32_t Slot );
	const MemChrBag&	GetSlotData( int32_t Slot );
	bool				setSlotData( int32_t Slot, const MemChrBag &slotData );
	bool				compairSlot( const MemChrBag& left, const MemChrBag& right );
	bool				AddItem( const MemChrBag& item );
	bool				RemoveItem( int32_t Slot );
	void				CheckOpenSlot();
	
	void				CheckCurrency();
private:
	ChrBagInfo			m_DepotInfo;
	MemChrBag			m_DepotData[MAX_DEPOT_SLOT];					// 仓库数据
	MemChrBag			m_nullobj;
	int32_t				m_aCurrency[CURRENCY_TYPE_COUNT];				// 资源
	bool				m_NeedSendCurrency;

	Int32List			m_lstDirty;							// 脏数据
	bool				m_NeedSendDirty;
	int32_t				m_lastCheckSlotOpen;
};