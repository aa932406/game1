//////////////////////////////////////////////////////////////////////////
// 融合系统 (CRongHe)
// 包含物品融合、装备熔炼、拆卸、物品回收等功能
//////////////////////////////////////////////////////////////////////////

#ifndef __RONG_HE_H__
#define __RONG_HE_H__

#include "stdafx.h"
#include "ExtSystemBase.h"
#include "CfgData.h"
#include <map>

struct RongLianInfo;

class CRongHe : public CExtSystemBase
{
public:
	CRongHe();
	virtual ~CRongHe();

	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void	OnCleanUp();

	// 协议处理
	int32_t	OnRongLian( Answer::NetPacket *inPacket );
	int32_t	OnEquipRongLian( Answer::NetPacket *inPacket );
	int32_t	OnDismantlingEquip( Answer::NetPacket *inPacket );
	int32_t	OnItemRecovery( Answer::NetPacket *inPacket );
	int32_t	OnOneKeyItemRecovery( Answer::NetPacket *inPacket );

	// 数据同步
	void	SendAllRongHeInfo();
	void	SendOneRongHeInfo( int32_t nSlot );
	void	SendRongHeResult( int32_t nId, int32_t nSuccess, const MemChrBag& stu );

	// 序列化
	std::string	GetRongHeEquipString();
	void		ParesRongHeEquipString( const std::string& strData );

private:
	RongLianInfoMap	m_RongLianInfoMap;
};

#endif // __RONG_HE_H__
