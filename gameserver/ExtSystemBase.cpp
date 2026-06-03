#include "ExtSystemBase.h"

CExtSystemBase::CExtSystemBase()
{

}

CExtSystemBase::~CExtSystemBase()
{

}

void CExtSystemBase::Init( Player* pPlayer )
{
	m_pPlayer = pPlayer;
}

void CExtSystemBase::OnLoadFromDB( const PlayerDBData& dbData )
{

}

void CExtSystemBase::OnSaveToDB( PlayerDBData& dbData )
{

}

void CExtSystemBase::OnUpdate( int64_t curTick )
{

}

void CExtSystemBase::OnDaySwitch( int32_t nDiffDays )
{
	
}

void CExtSystemBase::OnCleanUp()
{

}

void CExtSystemBase::GetInterestsProtocol( ProcIdList& procList )
{

}

int32_t CExtSystemBase::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	return ERR_INVALID_DATA;
}