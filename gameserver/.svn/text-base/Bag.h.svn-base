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
	int32_t			onSort( Answer::NetPacket *inPacket );																									// 背包整理
	int32_t			onSellItem( Answer::NetPacket *inPacket );

	int32_t			OnAskRansomInfo( Answer::NetPacket *inPacket );
	int32_t			OnAskSpoilsInfo( Answer::NetPacket *inPacket );
	int32_t			OnAskRansomItem( Answer::NetPacket *inPacket );
public:
	int32_t addBagSlots( int32_t slot,int32_t &buySlots,int32_t& openSlots);
	int32_t useItem( int32_t slot,int32_t type );
	int32_t patchUseItem( int32_t slot, int32_t count );
	void    updateBagSlots(int32_t slots);

	//个人商店 购买物品
	int32_t buyChrShopItem( CfgChrShop* pCharShop,int32_t id,int32_t count );

	//回购物品
	int32_t buyBackChrShopItem(int32_t index,int32_t itemID,int32_t itemClass);

private:
	void	setSellItem( const MemChrBag& sellItem );
	void	cleanSellItem();
	void	deleteSellItem(int32_t index);
	void	sendGoldCashChange(int32_t type, int32_t addon, BenefitType benefitType);
	void	RansomGongGao( DropEquipInfo EquipInfo, int32_t Gold );

// 添加删除道具 start
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
	//这个函数只在合成的时候用,不会删除限时物品,先删除绑定的
	bool	RemoveCombiItem( const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	removeCombiItem( const ItemDataList& lst, ITEM_DEL_REASON delReason );
	int32_t	HaveItemCount( const ItemData& data, bool IsBind, bool IsTimeLiness ); //是否算上时效物品
	void	SetSlotData( int32_t slot, const MemChrBag &slotData, int32_t reason = 0, int32_t count = 0 );	// 取走的时候调用这个，不会删除装备主体信息
	void	CleanSlot( int32_t slot, int32_t reason );														// 销毁的时候调用这个，会直接删除装备主体信息

private:
	bool	addItem( const MemChrBagVector &vItem, ITEM_ADD_REASON reason );
	bool	addItem( const MemChrBag &item, ITEM_ADD_REASON reason );
	bool	removeItem( const Int32Vector& vSlot, const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	removeItem( const Int32Vector& vSlot, const ItemData& data, ITEM_DEL_REASON delReason );
	bool	removeItem( const ItemDataList& lst, ITEM_DEL_REASON delReason );
	bool	removeItem( const ItemData& data, ITEM_DEL_REASON delReason );
	void	setSlotData( int32_t slot, const MemChrBag &slotData, int32_t reason = 0, int32_t count = 0 );
// 添加删除道具 end

public:
	void				SendBagInfo();
	void				SendBagItem();
	void				SendBagSellItem();
	void				SaveDBData( PlayerDBData& dbData );
	int32_t				GetItemCount( int32_t nId, int8_t nClass ) const;
	const ChrBagInfo&	GetChrBagInfo() const;																					// 获取背包信息
	int32_t				GetFirstFreeSlot() const;																				// 获得第一个空格位置
	int32_t				GetItemCount( const Int32Vector& vSlot, int8_t nClass, int32_t nId ) const;								// 获取道具数量
	int32_t				GetItemType( const MemChrBag& item ) const;																// 获取道具类型
	bool				IsEmptySlot( const MemChrBag& slot ) const;																// 空背包格判断
	const MemChrBag&	GetSlotData( int32_t slot ) const;																		// 获取背包格信息
	int32_t				GetFreeSlotCount() const;																				// 获取背包剩余空格数量
	bool				IsSlotValid( int32_t slot ) const;																		// 检测道具格是否开放
	bool				HasItem( const ItemData& data ) const;																	// 检测道具数量是否达标
	bool				HasItem( int32_t nId, int8_t nClass, int32_t nCount ) const;											// 检测道具数量是否达标
	int32_t				GetBagSize() const;
	int32_t				GetbagFreeSize();
	void				OnLogout();
	void				GetDropItem( Player *pKiller, PkDropRate* DropRate,MemChrBagVector& ItemVector, int32_t Mid );
	void				ForceSendDirty();

private:
	void				backUpBagData();																								// 备份背包数据（添加删除操作之前先备份）
	void				recoverBagData();																								// 还原背包数据（添加删除操作失败后使用备份还原数据）
	void				addItemChangeLog( int32_t nReason, int32_t nId, int8_t nClass, int64_t nSrcId, int32_t nCount, int8_t nFlag );	// 添加道具变更日志
	void				saveItemChangeLog();																							// 存储道具变更日志
	void				clearItemChangeLog();																							// 清除道具变更日志
	bool				compairItem( const MemChrBag& bagSlot, const ItemData& data );													// 检测是否匹配
	bool				compairSlot( const MemChrBag& left, const MemChrBag& right );													// 检测是否匹配

	// 脏数据
	void				addDirty( int32_t nSlot, int32_t reason, bool bNeedCreate = false );
	void				checkDirty();
	void				clearDirty();
	bool				sendDirty();

	// 待创建数据
	void				checkCreate();

	// 背包自动开启
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
	MemChrBag			m_bagData[MAX_BAG_SLOT_NUM];					// 背包数据
	MemChrBag			m_nullobj;
    MemChrBag			m_sellItemInfo[MAX_SELL_ITEM_COUNT];
	int64_t				m_lastItemTick[ITEM_CD_GROUP_COUNT];

	MemChrBag			m_bagBackUp[MAX_BAG_SLOT_NUM];					// 背包备份
	LogItemChangeList	m_lstItemChangeLog;

	BagDirtyList		m_lstDirty;										// 脏数据
	Int32List			m_lstWaitCreate;								// 待创建列表
	ItemLimitMap		m_ItemLimit;									// 限制物品
	int32_t				m_lastCheckSlotOpen;
};

