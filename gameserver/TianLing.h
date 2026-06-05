#pragma once

#include "ExtSystemBase.h"
#include "DataStructs.h"

class CTianLing : public CExtSystemBase
{
public:
	CTianLing( Player* pPlayer ) { m_pPlayer = pPlayer; }
	~CTianLing() {}

	virtual void	OnLoadFromDB() {}
	virtual void	OnSaveToDB( PlayerDBData& dbData ) {}
	virtual void	OnCleanUp() {}
	virtual void	OnUpdate( int64_t curTick ) {}

	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	void	InitSystem();			// 初始化三个子系统
	void	InitTianLing();			// 初始化天灵
	void	InitZhanHun();			// 初始化战魂
	void	InitSunAndMoon();		// 初始化日月
	void	AddCharAttr();			// 添加三个系统的属性

	int32_t	OnTianLingLevelUp( Answer::NetPacket* inPacket );
	int32_t	OnZhanHunLevelUp( Answer::NetPacket* inPacket );
	int32_t	OnSunAndMoonLevelUp( Answer::NetPacket* inPacket );

	bool	GetMonsterItem( MemChrBag item );
};
