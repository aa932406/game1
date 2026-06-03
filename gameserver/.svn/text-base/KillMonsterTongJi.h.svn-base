#pragma once
#include "ExtSystemBase.h"
#include "Shared.h"

class CKillMonsterTongJi:
	public CExtSystemBase
{
public:
	CKillMonsterTongJi();
	~CKillMonsterTongJi();
	
	virtual void	OnCleanUp();
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );

	void	AddKillCount( int32_t GroupId, int32_t Mid, int8_t BossSign );
	void	SendKillMonsterInfo();
private:
	void	SendChangeMonsterInfo( int32_t GroupId );
private:
	KillMonsterMap		m_KillMonsterMap;	
};