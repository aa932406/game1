#include "KillMonsterTongJi.h"
#include "GameService.h"

CKillMonsterTongJi::CKillMonsterTongJi()
{
	OnCleanUp();
}

CKillMonsterTongJi::~CKillMonsterTongJi()
{

}

void CKillMonsterTongJi::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_KILL_MONSTER_COUNT );
}

int32_t CKillMonsterTongJi::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_ASK_KILL_MONSTER_COUNT:
		{
			SendKillMonsterInfo();
		}
		break;
	default:break;
	}
	return ERR_SYETEM_ERR;
}

void CKillMonsterTongJi::OnCleanUp()
{
	m_KillMonsterMap.clear();
}

void CKillMonsterTongJi::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_KillMonsterMap = dbData.m_KillMonsterData.m_KillMonsterMap;
}

void CKillMonsterTongJi::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_KillMonsterData.m_KillMonsterMap = m_KillMonsterMap;
}

void CKillMonsterTongJi::AddKillCount( int32_t GroupId, int32_t Mid, int8_t BossSign )
{
	if ( GroupId < 0 )
	{
		return;
	}
	KillMonsterMap::iterator it = m_KillMonsterMap.find( GroupId );
	if ( it != m_KillMonsterMap.end() )
	{
		it->second.m_KillCount++;
	}
	else
	{
		KillMonsterInfo stu;
		bzero( &stu, sizeof( stu ) );
		stu.m_BossSign		= BossSign;
		stu.m_KillCount		= 1;
		stu.m_MonsterMid	= Mid;
		m_KillMonsterMap[GroupId] = stu;
	}
	//SendChangeMonsterInfo( GroupId );
}

void CKillMonsterTongJi::SendKillMonsterInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket* pNetData = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_KILL_MONSTER_COUNT);
	if (pNetData != NULL)
	{
		KillMonsterMap::iterator it = m_KillMonsterMap.begin();
		int32_t MonsterCount = m_KillMonsterMap.size();
		pNetData->writeInt32( MonsterCount );
		for ( ; it != m_KillMonsterMap.end(); ++it )
		{
			pNetData->writeInt32( it->first );
			pNetData->writeInt32( it->second.m_MonsterMid );
			pNetData->writeInt8( it->second.m_BossSign );
			pNetData->writeInt32( it->second.m_KillCount );
		}
		pNetData->setSize(pNetData->getWOffset());
		GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), pNetData);
	}
}

void CKillMonsterTongJi::SendChangeMonsterInfo( int32_t GroupId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket* pNetData = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_NOTIFY_KILL_MONSTER_CHANGE);
	if (pNetData != NULL)
	{
		KillMonsterMap::iterator it = m_KillMonsterMap.find( GroupId );
		if ( it != m_KillMonsterMap.end() )
		{
			pNetData->writeInt32( it->first );
			pNetData->writeInt32( it->second.m_MonsterMid );
			pNetData->writeInt8( it->second.m_BossSign );
			pNetData->writeInt32( it->second.m_KillCount );
			pNetData->setSize(pNetData->getWOffset());
			GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), pNetData);
		}
	}
}
