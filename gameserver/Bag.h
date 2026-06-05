#pragma once

#include "CfgData.h"
#include "DataStruct.h"
#include "ExtSystemBase.h"

class Player;
class CExtCharBag : public CExtSystemBase
{
struct BagDirty
{
	int32_t nSlot;
	bool	bChange;
};
typedef std::list<BagDirty> BagDirtyList;

public:
	CExtCharBag();
	virtual ~CExtCharBag();

	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnUpdate( int64_t curTick );
	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	void			reset();
	int32_t			onAddBagSlots( Answer::NetPacket *inPacket );
	int32_t			onMoveItem( Answer::NetPacket *inPacket );
	int32_t			onSplitItem( Answer::NetPacket *inPacket );
	int32_t			onSort( Answer::NetPacket *inPacket );																									// ��������
	int32_t			onSellItem( Answer::NetPacket *inPacket );

	int32_t			OnAskRansomInfo( Answer::NetPacket *inPacket );
	int32_t			OnAskSpoilsInfo( Answer::NetPacket *inPacket );
	int32_t			OnAskRansomItem( Answer::NetPacket *inPacket );
	// ========== ���°汾�ӿ� ==========
	int32_t			onUseItem( Answer::NetPacket *inPacket );
	int32_t			onPatchUseItem( Answer::NetPacket *inPacket );
	int32_t			onSelectItem( Answer::NetPacket *inPacket );
	int32_t			onDiscardItem( Answer::NetPacket *inPacket );
	int32_t			onUseMutiItem( Answer::NetPacket *inPacket );
	int32_t			onAddItem( Answer::NetPacket *inPacket );
	bool			canUseItem( int32_t nSlot, const CfgItem* cfgItem );
	bool			isAutoUseItem( const CfgItem* cfgItem );
	bool			autoUseItem( const MemChrBag& item );
	void			sendUseBroadcast( int32_t nBroadcast, const std::string& p_name, CharId_t cid, int32_t nItemId );
	void			CleanItemId( int32_t nId, int32_t nReason, int8_t nClass );
	int32_t			GetItemSlot( int32_t nId, int8_t nClass ) const;
	int32_t			GetTypeItem( int32_t nType ) const;
	bool			AddItemsAndMingGe( const MemChrBagVector& vItem, int32_t addReason );
public:
	int32_t addBagSlots( int32_t slot,int32_t &buySlots,int32_t& openSlots);
	int32_t useItem( int32_t slot,int32_t type );
	int32_t patchUseItem( int32_t slot, int32_t count );
	void    updateBagSlots(int32_t slots);

	//�����̵� ������Ʒ
	int32_t buyChrShopItem( CfgChrShop* pCharShop,int32_t id,int32_t count );

	//�ع���Ʒ
	int32_t buyBackChrShopItem(int32_t index,int32_t itemID,int32_t itemClass);

private:
	void	setSellItem( const MemChrBag& sellItem );
	void	cleanSellItem();
	void	deleteSellItem(int32_t index);
	void	sendGoldCashChange(int32_t type, int32_t addon, BenefitType benefitType);
	void	RansomGongGao( DropEquipInfo EquipInfo, int32_t Gold );

// ����ɾ������ start
public:
	bool	AddAndRemoveItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason, const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	AddAndRemoveItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason, const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason );
	bool	AddAndRemoveItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason, const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	AddAndRemoveItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason, const ItemData& data, ITEM_DEL_REASON delReason );
	bool	AddAndRemoveItem( const MemChrBag& item, ITEM_ADD_REASON addReason, const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	AddAndRemoveItem( const MemChrBag& item, ITEM_ADD_REASON addReason, const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason );
	bool	AddAndRemoveItem( const MemChrBag& item, ITEM_ADD_REASON addReason, const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	AddAndRemoveItem( const MemChrBag& item, ITEM_ADD_REASON addReason, const ItemData& data, ITEM_DEL_REASON delReason );

	bool	AddItem( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason );
	bool	AddItem( const MemChrBag& item, ITEM_ADD_REASON addReason );
	bool	RemoveItem( const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	RemoveItem( const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason );
	bool	RemoveItem( const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	RemoveItem( const ItemData& data, ITEM_DEL_REASON delReason );

	bool	AddItemsAndEggs( const MemChrBagVector &vItem, ITEM_ADD_REASON addReason );

	bool	RemoveItem( const ItemData& data, ITEM_DEL_REASON delReason, int32_t& BindCount, int32_t& UnBindCount );
	bool	removeItem( const ItemData& data, ITEM_DEL_REASON delReason, int32_t& BindCount, int32_t& UnBindCount );
	//�������ֻ�ںϳɵ�ʱ����,����ɾ����ʱ��Ʒ,��ɾ���󶨵�
	bool	RemoveCombiItem( const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	removeCombiItem( const ItemDataList& lst, ITEM_DEL_REASON delReason );
	int32_t	HaveItemCount( const ItemData& data, bool IsBind, bool IsTimeLiness ); //�Ƿ�����ʱЧ��Ʒ
	void	SetSlotData( int32_t slot, const MemChrBag &slotData, int32_t reason = 0, int32_t count = 0 );	// ȡ�ߵ�ʱ��������������ɾ��װ��������Ϣ
	void	CleanSlot( int32_t slot, int32_t reason );														// ���ٵ�ʱ������������ֱ��ɾ��װ��������Ϣ

private:
	bool	addItem( const MemChrBagVector &vItem, ITEM_ADD_REASON reason );
	bool	addItem( const MemChrBag &item, ITEM_ADD_REASON reason );
	bool	removeItem( const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	removeItem( const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason );
	bool	removeItem( const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	removeItem( const ItemData& data, ITEM_DEL_REASON delReason );
	void	setSlotData( int32_t slot, const MemChrBag &slotData, int32_t reason = 0, int32_t count = 0 );
// ����ɾ������ end

public:
	void				SendBagInfo();
	void				SendBagItem();
	void				SendBagSellItem();
	void				SaveDBData( PlayerDBData& dbData );
	int32_t				GetItemCount( int32_t nId, int8_t nClass ) const;
	const ChrBagInfo&	GetChrBagInfo() const;																					// ��ȡ������Ϣ
	int32_t				GetFirstFreeSlot() const;																				// ��õ�һ���ո�λ��
	int32_t				GetItemCount( const Int32Vector& vSlot, int8_t nClass, int32_t nId ) const;								// ��ȡ��������
	int32_t				GetItemType( const MemChrBag& item ) const;																// ��ȡ��������
	bool				IsEmptySlot( const MemChrBag& slot ) const;																// �ձ������ж�
	const MemChrBag&	GetSlotData( int32_t slot ) const;																		// ��ȡ��������Ϣ
	int32_t				GetFreeSlotCount() const;																				// ��ȡ����ʣ��ո�����
	bool				IsSlotValid( int32_t slot ) const;																		// �����߸��Ƿ񿪷�
	bool				HasItem( const ItemData& data ) const;																	// �����������Ƿ���
	bool				HasItem( int32_t nId, int8_t nClass, int32_t nCount ) const;											// �����������Ƿ���
	int32_t				GetBagSize() const;
	int32_t				GetbagFreeSize();
	void				OnLogout();
	void				GetDropItem( Player *pKiller, PkDropRate* DropRate,MemChrBagVector& ItemVector, int32_t Mid );
	void				ForceSendDirty();

private:
	void				backUpBagData();																								// ���ݱ������ݣ�����ɾ������֮ǰ�ȱ��ݣ�
	void				recoverBagData();																								// ��ԭ�������ݣ�����ɾ������ʧ�ܺ�ʹ�ñ��ݻ�ԭ���ݣ�
	void				addItemChangeLog( int32_t nReason, int32_t nId, int8_t nClass, int64_t nSrcId, int32_t nCount, int8_t nFlag );	// ���ӵ��߱����־
	void				saveItemChangeLog();																							// �洢���߱����־
	void				clearItemChangeLog();																							// ������߱����־
	bool				compairItem( const MemChrBag& bagSlot, const ItemData& data );													// ����Ƿ�ƥ��
	bool				compairSlot( const MemChrBag& left, const MemChrBag& right );													// ����Ƿ�ƥ��

	// ������
	void				addDirty( int32_t nSlot, int32_t reason, bool bNeedCreate = false );
	void				checkDirty();
	void				clearDirty();
	bool				sendDirty();

	// ����������
	void				checkCreate();

	// �����Զ�����
	void				checkBagOpen();

	void				SendRansomInfo();
	void				SendSpoilsInfo();
public:
	void				AddCharAttr();
	void				SendLimitCount();
private:
	bool				UseCurrencyItem( const MemChrBag& Item, ITEM_ADD_REASON addReason );
	int32_t				GetLimitCount(int32_t index);
	void				AddLimitCount( int32_t index, int32_t Count );
private:
	ChrBagInfo			m_bagInfo;
	MemChrBag			m_bagData[MAX_BAG_SLOT_NUM];					// ��������
	MemChrBag			m_nullobj;
    MemChrBag			m_sellItemInfo[MAX_SELL_ITEM_COUNT];
	int64_t				m_lastItemTick[ITEM_CD_GROUP_COUNT];

	MemChrBag			m_bagBackUp[MAX_BAG_SLOT_NUM];					// ��������
	LogItemChangeList	m_lstItemChangeLog;

	BagDirtyList		m_lstDirty;										// ������
	Int32List			m_lstWaitCreate;								// �������б�
	ItemLimitMap		m_ItemLimit;									// ������Ʒ
	int32_t				m_lastCheckSlotOpen;
};

