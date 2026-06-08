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
	bool				CanOperateDepot();
	bool				IsEnterSecondPasswordOperate();
	int32_t				GetPageBySlot( int32_t Slot );
	void				CleanBag();
private:
	void				CleanUp();
	int32_t				OnGetDepotItem( Answer::NetPacket *inPacket );
	int32_t				OnSaveItemToDepot( Answer::NetPacket *inPacket );
	int32_t				OnGetDepotCurrency( Answer::NetPacket *inPacket );
	int32_t				OnSaveDepotCurrency( Answer::NetPacket *inPacket );
	int32_t				OnSortDepot( Answer::NetPacket *inPacket );
	int32_t				OnNewSortDepot( Answer::NetPacket *inPacket );
	int32_t				OnOpenDepotSlot( Answer::NetPacket *inPacket );
	int32_t				OnSetPassword( Answer::NetPacket *inPacket );
	int32_t				OnEnterPassword( Answer::NetPacket *inPacket );
	int32_t				OnModifyPassword( Answer::NetPacket *inPacket );
	int32_t				OnCancelPassword( Answer::NetPacket *inPacket );
	int32_t				OnSetSecondPassword( Answer::NetPacket *inPacket );
	int32_t				OnEnterSecondPassword( Answer::NetPacket *inPacket );
	int32_t				OnModifySecondPassword( Answer::NetPacket *inPacket );
	int32_t				OnCancelSecondPassword( Answer::NetPacket *inPacket );
	int32_t				OpenSlotCostGold( int32_t Slot );

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
	
	void				CheckCurrency();
private:
	ChrBagInfo			m_DepotInfo;
	MemChrBag			m_DepotData[MAX_DEPOT_SLOT];
	MemChrBag			m_nullobj;
	int32_t				m_aCurrency[CURRENCY_TYPE_COUNT];
	bool				m_NeedSendCurrency;

	Int32List			m_lstDirty;
	bool				m_NeedSendDirty;
	int32_t				m_OpenCount;
	std::string			m_Password;
	std::string			m_SendPassword;
};