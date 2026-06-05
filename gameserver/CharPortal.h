#pragma once
//////////////////////////////////////////////////////////////////////////
// 传送门系统
// Protocol: 809 (请求信息), 810 (使用传送门)
//////////////////////////////////////////////////////////////////////////

#include "ExtSystemBase.h"

// 协议常量
#define SM_PORTAL_INFO			0x2F53		// 12115
#define SM_PORTAL_CLOSE			0x2F54		// 12116
#define SM_BROADCAST_PORTAL		0x2CD6		// 11478

class CExtCharPortal : public CExtSystemBase
{
	friend class CExtSystemMgr;
public:
	CExtCharPortal();
	virtual ~CExtCharPortal();

	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData* dbData );
	virtual void	OnSaveToDB( PlayerDBData* dbData );
	virtual void	OnUpdate( int64_t curTick );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual	int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	// 对外接口 — 由其他系统调用
	void	AddPortal( int32_t nMapId, int32_t nPosX, int32_t nPosY, int32_t nDungeon, int32_t nStartTime, int32_t nDuration );

protected:
	// 协议处理
	int32_t		onRequestInfo( Answer::NetPacket* inPacket );	// 809
	int32_t		onUsePortal( Answer::NetPacket* inPacket );		// 810

	// 内部方法
	void		SendPortalInfo( const PortalInfoList* lst );
	void		SendPortalInfo( const PortalInfo* info );
	void		SendPortalClose( int32_t nId );
	void		BroadcastPortal();
	int32_t		getPortalId();
	void		checkPortalTime( bool bInit );

protected:
	PortalInfoList	m_lstPortal;		// 传送门列表
	int32_t			m_nPortalId;		// 传送门ID计数器
	int64_t			m_nLastTick;		// 上次检查时间
};
