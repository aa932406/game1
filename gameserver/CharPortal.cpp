#include "CharPortal.h"
#include "GameService.h"
#include "Player.h"

using namespace Answer;

CExtCharPortal::CExtCharPortal()
{
}

CExtCharPortal::~CExtCharPortal()
{
}

void CExtCharPortal::OnCleanUp()
{
	m_nPortalId = 0;
	m_lstPortal.clear();
	m_nLastTick = 0;
}

void CExtCharPortal::OnLoadFromDB( const PlayerDBData* dbData )
{
	if ( NULL == dbData )
	{
		return;
	}
	m_lstPortal = dbData->m_PortalDBData.lstPortal;
	m_nPortalId = dbData->m_PortalDBData.nPortalId;
	checkPortalTime( true );
}

void CExtCharPortal::OnSaveToDB( PlayerDBData* dbData )
{
	if ( NULL == dbData )
	{
		return;
	}
	dbData->m_PortalDBData.lstPortal = m_lstPortal;
}

void CExtCharPortal::OnUpdate( int64_t curTick )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( curTick - m_nLastTick > 999 )
	{
		checkPortalTime( false );
		m_nLastTick = curTick;
	}
}

void CExtCharPortal::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 809 );	// 请求传送门信息
	procList.push_back( 810 );	// 使用传送门
}

int32_t CExtCharPortal::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	switch ( nProcId )
	{
	case 809: return onRequestInfo( inPacket );
	case 810: return onUsePortal( inPacket );
	default: break;
	}
	return ERR_OK;
}

// ========== 809 请求传送门信息 ==========
int32_t CExtCharPortal::onRequestInfo( NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	SendPortalInfo( &m_lstPortal );
	return ERR_OK;
}

// ========== 810 使用传送门 ==========
int32_t CExtCharPortal::onUsePortal( NetPacket* inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nId = inPacket->readInt32();

	// 查找传送门
	for ( PortalInfoList::iterator iter = m_lstPortal.begin(); iter != m_lstPortal.end(); ++iter )
	{
		if ( iter->nId == nId )
		{
			if ( iter->bClose )
			{
				return ERR_INVALID_DATA;
			}

			// 进入副本
			int32_t nErr = Player::enterDungeon( m_pPlayer, iter->nDungeon, inPacket->getProc(), 0, 0, 0, 0, 0 );
			if ( nErr )
			{
				return nErr;
			}

			iter->bClose = 1;
			SendPortalClose( nId );
			return ERR_OK;
		}
	}

	return ERR_INVALID_DATA;
}

// ========== 添加传送门（对外接口） ==========
void CExtCharPortal::AddPortal( int32_t nMapId, int32_t nPosX, int32_t nPosY, int32_t nDungeon, int32_t nStartTime, int32_t nDuration )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	PortalInfo info;
	memset( &info, 0, sizeof( info ) );
	info.nId = getPortalId();
	info.nMapId = nMapId;
	info.nPosX = nPosX;
	info.nPosY = nPosY;
	info.nDungeon = nDungeon;
	info.nStartTime = nStartTime;
	info.nDuration = nDuration;

	m_lstPortal.push_back( info );
	SendPortalInfo( &info );
	BroadcastPortal();
}

// ========== 发送单个传送门信息 ==========
void CExtCharPortal::SendPortalInfo( const PortalInfo* info )
{
	if ( NULL == m_pPlayer || NULL == info )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PORTAL_INFO );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( 1 );	// 数量
	packet->writeInt32( info->nId );
	packet->writeInt32( info->nMapId );
	packet->writeInt32( info->nPosX );
	packet->writeInt32( info->nPosY );
	packet->writeInt32( info->nDungeon );
	packet->writeInt32( info->nStartTime );
	packet->writeInt32( info->nDuration );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

// ========== 发送传送门列表 ==========
void CExtCharPortal::SendPortalInfo( const PortalInfoList* lst )
{
	if ( NULL == m_pPlayer || NULL == lst )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PORTAL_INFO );
	if ( NULL == packet )
	{
		return;
	}

	int32_t nCount = 0;
	uint32_t nOldOffset = packet->getWOffset();
	packet->writeInt32( 0 );	// 占位，稍后写入实际数量

	for ( PortalInfoList::const_iterator iter = lst->begin(); iter != lst->end(); ++iter )
	{
		if ( iter->bClose )
		{
			continue;
		}

		packet->writeInt32( iter->nId );
		packet->writeInt32( iter->nMapId );
		packet->writeInt32( iter->nPosX );
		packet->writeInt32( iter->nPosY );
		packet->writeInt32( iter->nDungeon );
		packet->writeInt32( iter->nStartTime );
		packet->writeInt32( iter->nDuration );
		++nCount;
	}

	if ( nCount > 0 )
	{
		uint32_t nNewOffset = packet->getWOffset();
		packet->setWOffset( nOldOffset );
		packet->writeInt32( nCount );
		packet->setWOffset( nNewOffset );

		packet->setSize( packet->getWOffset() );
		GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
	}
}

// ========== 发送传送门关闭 ==========
void CExtCharPortal::SendPortalClose( int32_t nId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PORTAL_CLOSE );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( nId );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

// ========== 广播传送门 ==========
void CExtCharPortal::BroadcastPortal()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_BROADCAST_PORTAL );
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( 538 );	// portal广播ID
	std::string name = m_pPlayer->getName();
	packet->writeUTF8( name );
	packet->writeInt64( m_pPlayer->getCid() );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

// ========== 获取传送门ID ==========
int32_t CExtCharPortal::getPortalId()
{
	if ( ++m_nPortalId > 9999 )
	{
		m_nPortalId = 1;
	}
	return m_nPortalId;
}

// ========== 检查传送门超时 ==========
void CExtCharPortal::checkPortalTime( bool bInit )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	int32_t nNowTime = m_pPlayer->getNow();
	PortalInfoList::iterator iter = m_lstPortal.begin();
	while ( iter != m_lstPortal.end() )
	{
		if ( !iter->bClose && iter->nStartTime + iter->nDuration <= nNowTime )
		{
			iter->bClose = 1;
			if ( !bInit )
			{
				SendPortalClose( iter->nId );
			}
		}
		++iter;
	}
}
