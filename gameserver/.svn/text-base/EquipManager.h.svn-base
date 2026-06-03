/*
* 装备管理器
* 管理服务器所有装备的数据
* 所有已创建的装备数据都在此
*/

#ifndef __TPOC_EQUIP_MANAGER_H__
#define __TPOC_EQUIP_MANAGER_H__

#include "CfgData.h"

class CEquipManager
{
public:
	CEquipManager();
	virtual ~CEquipManager();

public:
	void			Init();																										// 初始化从数据库中读取数据
	void			OnEquipUpdated( const MemEquipVector &memEquips );															// 有装备数据更新时接收到的消息（主要是跨线信息和人物登陆初始化更新人物装备）

public:
	MemEquip		CreateMemEquip( int32_t nBaseId, int32_t nServerId, CharId_t nCreaterId, int32_t nStar = 0, int32_t nAddAttr = 0 );			// 创建一件装备
	MemEquip		GetMemEquip( EquipId_t nEquipId );																			// 查找一件装备
	void			UpdateMemEquip( const MemEquip &equip );																	// 更新一件装备
	void			DeleteMemEquip( EquipId_t nEquipId );																		// 删除一件装备

	int32_t			GetAddAttrCount( int8_t nQuality );																			// 获得附加属性条数（约定）
	void			PacketEquipInfo( Answer::NetPacket *packet, const MemEquipVector &memEquips ) const;						// 打包装备信息
	void			SendPlayerEquipInfo( const Player& player );
	void			ChangeOwner( EquipId_t nEquipId, CharId_t nOwner );

private:
	int64_t			getEquipId( int32_t nServerId ) const;																		// 获得装备ID，递增

private:
	MemEquipTable	m_mEquipTable;
	Answer::RwLock	m_rwEquipLock;
};

#define EQUIP_MANAGER Answer::Singleton<CEquipManager>::instance()

#endif	//__TPOC_EQUIP_MANAGER_H__
