#ifndef __EQUIP_RANSOM_H__
#define __EQUIP_RANSOM_H__
#include "stdafx.h"

class CEquipRansom
{
public:
	CEquipRansom();
	virtual ~CEquipRansom();
	
	void	 OnPlayerLogin( CharId_t Cid );				
	void	 GetRansomInfo( CharId_t Cid, RANSOM_ITEM_LIST& EquipList );		
	void	 PackRansomInfo( Answer::NetPacket *packet, RANSOM_ITEM_LIST& EquipList );
	void	 GetSpoilsInfo( CharId_t Cid, RANSOM_ITEM_LIST& EquipList );
	void	 GetRansomEquip( EquipId_t EquipId, DropEquipInfo& EquipInfo );
	void	 OnUpdatedRansom( Answer::NetPacket *packet );
	void	 DeleteRansom( EquipId_t nEquipId );
	void	 AddRansom( DropEquipInfo &EquipInfo );
	
private:
	std::map<EquipId_t,DropEquipInfo>	m_DropEquipMap;
	Answer::RwLock						m_DropEquipLock;
};

#define EQUIP_RANSOM Answer::Singleton<CEquipRansom>::instance()

#endif