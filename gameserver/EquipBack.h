#ifndef __EQUIP_BACK_H__
#define __EQUIP_BACK_H__

#include "stdafx.h"
#include "CfgData.h"

// 装备回购记录
struct BackRecord
{
	int32_t		nId;
	int8_t		nType;		// 1=金币回购, 2=开服回购
	std::string	name;
	int32_t		nTime;
};

// 装备回购仓库
struct BackDepot
{
	int32_t		nId;
	int32_t		Count;
};

// 装备回购限购信息
struct BackLimitInfo
{
	int32_t		nId;
	int32_t		nCount;
	std::string	sLastName;
};

class CEquipBack
{
public:
	CEquipBack();
	virtual ~CEquipBack();

	void Init();

	// 金币回购
	int32_t OnGoldBack( Player* pPlayer, Answer::NetPacket* packet );
	// 回购
	int32_t OnBuyBack( Player* pPlayer, Answer::NetPacket* packet );
	// 开服装备回购
	void KiaFuEquipBack( int32_t Index, int32_t EquipId, int32_t Mid, Player* pPlayer );

	// 发送信息
	void SendEquipBackInfo( Player* pPlayer );
	void SendEquipBackOnRecord( Player* pPlayer, BackRecord* p_stu );
	void SendEquipBackCountChange( Player* pPlayer, int32_t nId );
	void SendEquipBackLimitChange( Player* pPlayer, int32_t nId );

	// 操作
	void AddLimitCount( BackLimitInfo* p_stu );
	void ChangeDeptCount( BackDepot stu );
	void AddRecord( BackRecord* p_stu );

	// DB更新
	void UpdateEquipRecord( int32_t nId, int8_t nType, int32_t nTime, std::string* p_Name );
	void UpdateEquipBackInfo( int32_t nId, int8_t nType, int32_t nCount, std::string* p_Name );

private:
	std::list<BackRecord>		m_BackRecord;
	std::map<int32_t, BackDepot>	m_BackDepotMap;
	std::map<int32_t, BackLimitInfo>	m_BackLimitInfoMap;
	Answer::Mutex				m_RecordLock;
	Answer::Mutex				m_DepotLock;
};

#define EQUIP_BACK Answer::Singleton<CEquipBack>::instance()

#endif // __EQUIP_BACK_H__
