#include "ExtSystemMgr.h"
#include "ExtSystemBase.h"

CExtSystemMgr::CExtSystemMgr()
{

}

CExtSystemMgr::~CExtSystemMgr()
{

}

void CExtSystemMgr::Register( CExtSystemBase* pExtSystem )
{
	if ( NULL != pExtSystem )
	{
		m_lstExtSystems.push_back( pExtSystem );

		ProcIdList procList;
		pExtSystem->GetInterestsProtocol( procList );
		
		ProcIdList::iterator iter = procList.begin();
		ProcIdList::iterator eiter = procList.end();
		for ( ; iter != eiter; ++iter )
		{
			registProtocolHandler( *iter, pExtSystem );
		}
	}
}

bool CExtSystemMgr::IsProcRegisted( ProcId_t nProc )
{
	return m_mapProcHandler[nProc] != NULL;
}

void CExtSystemMgr::registProtocolHandler( ProcId_t procId, CExtSystemBase* pHanlder )
{
	if ( NULL == pHanlder)
	{
		return;
	}

#ifdef _DEBUG
	if (NULL != m_mapProcHandler[procId])
	{
		ASSERT(0);
		throw(0);
	}
#endif

	m_mapProcHandler[procId] = pHanlder;
}

//void CExtSystemMgr::OnLoadFromDB( const PlayerDBData& dbData )
//{
//	ExtSysList::iterator iter = m_lstExtSystems.begin(); 
//	ExtSysList::iterator eiter = m_lstExtSystems.end();
//	for (; iter != eiter; ++iter )
//	{
//		(*iter)->OnLoadFromDB( dbData );
//	}
//}
//
//void CExtSystemMgr::OnSaveToDB( PlayerDBData& dbData )
//{
//	ExtSysList::iterator iter = m_lstExtSystems.begin(); 
//	ExtSysList::iterator eiter = m_lstExtSystems.end();
//	for (; iter != eiter; ++iter )
//	{
//		(*iter)->OnSaveToDB( dbData );
//	}
//}

void CExtSystemMgr::OnUpdate( int64_t curTick)
{
	ExtSysList::iterator iter = m_lstExtSystems.begin(); 
	ExtSysList::iterator eiter = m_lstExtSystems.end();
	for (; iter != eiter; ++iter )
	{
		(*iter)->OnUpdate( curTick );
	}
}

//void CExtSystemMgr::OnDaySwitch( int32_t nDiffDays )
//{
//	ExtSysList::iterator iter = m_lstExtSystems.begin(); 
//	ExtSysList::iterator eiter = m_lstExtSystems.end();
//	for (; iter != eiter; ++iter )
//	{
//		(*iter)->OnDaySwitch( nDiffDays );
//	}
//}

void CExtSystemMgr::OnCleanUp()
{
	ExtSysList::iterator iter = m_lstExtSystems.begin(); 
	ExtSysList::iterator eiter = m_lstExtSystems.end();
	for (; iter != eiter; ++iter )
	{
		(*iter)->OnCleanUp();
	}
}

int32_t CExtSystemMgr::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	CExtSystemBase* pHandler = m_mapProcHandler[nProcId];
	if ( NULL == pHandler )
	{
		return ERR_INVALID_DATA;
	}

	return pHandler->DispatchNetDatas( nProcId, inPacket );
}
