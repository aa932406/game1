#pragma once

#include "ExtSystemBase.h"

class CObjCarrier;
class Player;

// 协议号 921 - WXJ 范围 (900~998)
#define CM_LEAVE_CARRIER 921

class CExtCharCarrier : public CExtSystemBase
{
public:
	CExtCharCarrier();
	virtual ~CExtCharCarrier();

public:
	virtual void OnCleanUp();
	virtual void OnUpdate( int64_t curTick );

public:
	virtual void GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

public:
	void EnterCarrier( int32_t nId );
	void LeaveCarrier();
	int32_t GetCarrierId() const;
	bool HaveSkill( int32_t nSkillId ) const;
	bool IsInCarrier() const { return m_pCarrier != NULL; }
	CObjCarrier* GetCarrier() const { return m_pCarrier; }

private:
	int32_t onLeaveCarrier( Answer::NetPacket *inPacket );

private:
	CObjCarrier* m_pCarrier;
};
