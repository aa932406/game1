/*
* 装备管理器
* 管理服务器所有装备的数据
* 所有已创建的装备数据都在此
*/

#ifndef __TPOC_EQUIP_MANAGER_H__
#define __TPOC_EQUIP_MANAGER_H__

#include "CfgData.h"

// 装备ID缓存，按服号缓存ID范围，避免每次都查DB
struct ServerNewId
{
	int64_t nNextId = 0;
	int64_t nMaxId = 0;
};

class CEquipManager
{
public:
	CEquipManager();
	virtual ~CEquipManager();

public:
	void			Init(int32_t line = 0);																					// 初始化从数据库中读取数据
	void			OnEquipUpdated( const MemEquipVector &memEquips );															// 有装备数据更新时接收到的消息（主要是跨线信息和人物登陆初始化更新人物装备）

public:
	MemEquip		CreateMemEquip( int32_t nBaseId, int32_t nServerId, CharId_t nCreaterId, int32_t nStar = 0, int32_t nAddAttr = 0 );			// 创建一件装备
	MemEquip		GetMemEquip( EquipId_t nEquipId );																			// 查找一件装备
	void			UpdateMemEquip( int8_t connid, const MemEquip &equip, int32_t nReason = 0 );								// 更新一件装备
	void			UpdateMemEquip( const MemEquip &equip ) { UpdateMemEquip(0, equip, 0); }									// 兼容旧调用
	void			DeleteMemEquip( int8_t connid, EquipId_t nEquipId, int32_t nReason = 0 );									// 删除一件装备
	void			DeleteMemEquip( EquipId_t nEquipId ) { DeleteMemEquip(0, nEquipId, 0); }									// 兼容旧调用

	int32_t			GetAddAttrCount( int8_t nQuality );																			// 获得附加属性条数（约定）
	void			PacketEquipInfo( Answer::NetPacket *packet, const MemEquipVector &memEquips ) const;						// 打包装备信息
	void			SendPlayerEquipInfo( Player* pPlayer );																		// 发送玩家全部装备（多连接版）
	void			SendPlayerEquipInfo( const Player& player ) { SendPlayerEquipInfo(const_cast<Player*>(&player)); }			// 兼容旧调用
	void			SendPlayerEquipInfo( Player* pPlayer, const MemEquip &equip );												// 发送单件装备
	void			SendPlayerEquipInfo( Player* pPlayer, const MemEquipVector &vEquip );										// 发送装备向量
	void			BroadcastEquipInfo( const MemEquip &equip );																// 世界广播装备信息
	void			ChangeOwner( EquipId_t nEquipId, CharId_t nOwner );

private:
	int64_t			getEquipId( int32_t nServerId ) const;																		// 获得装备ID（缓存机制）
	void			getEquipIdFromDB( int32_t nServerId, int64_t &nNextId, int64_t &nMaxId );									// 从DB获取ID范围

private:
	MemEquipTable	m_mEquipTable;
	Answer::RwLock	m_rwEquipLock;
	std::map<int, ServerNewId>	m_mNewId;																					// 按服号缓存的ID范围
	Answer::RwLock	m_IdLock;																									// m_mNewId读写锁
};

#define EQUIP_MANAGER Answer::Singleton<CEquipManager>::instance()

#endif	//__TPOC_EQUIP_MANAGER_H__
