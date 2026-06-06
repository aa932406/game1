#ifndef __TPOC_WAN_360_H__
#define __TPOC_WAN_360_H__

#include "ExtSystemBase.h"
#include "CfgData.h"
#include <list>
#include <map>
#include <string>
#include <vector>

class CWan360 : public CExtSystemBase
{
public:
	CWan360();
	virtual ~CWan360();

	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	OnUpdate( int64_t curTick );
	virtual void	OnCleanUp();
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	int32_t	OnGetJiaSuQiuReward( Answer::NetPacket *inPacket );
	int32_t	OnGetGameAppReward( Answer::NetPacket *inPacket );
	int32_t	OnLoginFromGameApp( Answer::NetPacket *inPacket );
	int32_t	OnLoginFromSouGouSkin( Answer::NetPacket *inPacket );
	int32_t	OnGetSpeed360Reward( Answer::NetPacket *inPacket );

	void	SendSouGouSkinIcon();
	void	GetSouGouSkinIconState( IconStateList& IconList );
	void	SendGameAppIcon();
	void	GetGameAppIconState( IconStateList& IconList );
	void	SendJiaShuQiuIcon();
	void	GetJiaShuQiuIconState( IconStateList& IconList );
	void	SendWeiXinIcon();
	void	GetWeiXinIconState( IconStateList& IconList );
	void	SendSpeed360Icon();
	void	GetSpeed360State( IconStateList& IconList );

private:
	bool	InSpeed360Time();

	int64_t	m_LastUpdateTiem;
	bool	m_IsSpeed360Start;
	bool	m_IsGameAppLogin;
	bool	m_bSouGouSkinLogin;
};

#endif	//__TPOC_WAN_360_H__
