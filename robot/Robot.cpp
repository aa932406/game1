#include "stdafx.h"
#include "Robot.h"
#include "ClientServer.h"
#include "MapManager.h"
#include "PathFinder.h"
#include <iostream>

int32_t DELTA_X[] = { 0, 1, 1, 1, 0, -1, -1,  -1 };
int32_t DELTA_Y[] = { 1, 1, 0, -1, -1, -1, 0,  1 };

using namespace Answer;
using namespace std;

CRobot::CRobot( const std::string& passport, int32_t sid, const std::string& name, Sex_t sex, Job_t job, int32_t head, int32_t nLine )
	:ClientConnection( CLIENT_RECV_BUFFER*2, CLIENT_SEND_BUFFER, name )
	,m_passport( passport )
	,m_cgindex( 0 )
	,m_cid( 0 )
	,m_uid( 0 )
	,m_sid( sid )
	,m_nIncreace( 1 )
	,m_line( nLine )
	,m_style( 0 )
	,m_head( head )
	,m_kingdom( 0 )
	,m_sex( sex )
	,m_job( job )
	,m_level( 0 )
	,m_mapid( 0 )
	,m_x( -1 )
	,m_y( -1 )
	,m_token( "" )
	,m_lastLoginTime( 0 )
	,m_lastLoginIp( "" )
	,m_nTargetMap( 0 )
	,m_start( false )
	,m_pTarget( NULL )
	,m_nState( PS_INVALID )
	,m_nSpeed( 150 )
	,m_direction( DOWN )
	,m_nCurTick( 0 )
	,m_nHP(1000)
	,m_nMaxHP(1000)
	,m_nMP(1000)
	,m_nMaxMP(1000)
	,m_nActionTick(0)
	,m_nMedicineTick(0)
{
	initExtSystems();
}

CRobot::~CRobot()
{

}

CharId_t CRobot::getCid() const
{
	return m_cid;
}

int32_t CRobot::getUit() const
{
	return m_uid;
}

int32_t CRobot::getSid() const
{
	return m_sid;
}

int32_t CRobot::getLevel() const
{
	return m_level;
}

Job_t CRobot::getJob() const
{
	return m_job;
}

Sex_t CRobot::getSex() const
{
	return m_sex;
}

Position CRobot::getCurPos() const
{
	return Map::tileToPixel( m_x, m_y );
}

Position CRobot::getCurTile() const
{
	return Position( m_x, m_y );
}

const std::string CRobot::getPassPort() const
{
	return m_passport;
}

void CRobot::update( int64_t curTick )
{
	m_nCurTick = curTick;
	if ( !isconnected() )
	{
		return;
	}
	checkNetPackets();
	if ( !m_start )
	{
		return;
	}

	// 机器人AI
	onMove( curTick );
	onUpdateState( curTick );
	checkUseMedicine();

	// 扩展系统
	m_ExtSysMgr.OnUpdate( curTick );
}

void CRobot::onUpdateState( int64_t curTick )
{
	if ( curTick < m_nActionTick )
	{
		return;		// 移动中
	}

	switch( m_nState )
	{
	case PS_STAND:			onStand( curTick );				break;
	case PS_WALK:			onWalk( curTick );				break;
	case PS_WALK_ATTACK:	onWalkAttack( curTick );		break;
	case PS_ATTACK:			onAttack( curTick );			break;
	case PS_GHOST:			onGhost( curTick );				break;
	}
}

void CRobot::sendStartPacket()
{
	Answer::NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cgindex );
	packet->writeUTF8( m_passport );
	packet->writeInt32( m_sid );

	packet->setType( PACK_PROC );
	packet->setProc( CM_USER_LOGIN );
	packet->setSize( packet->getWOffset() );

	sendPacketTo( packet );

	printf( "CRobot::sendStartPacket() passport = %s, name=%s\n", m_passport.c_str(), m_name.c_str() );
}

void CRobot::onNetPacket(Answer::NetPacket *inPacket)
{
	if ( !isProcRegisted( inPacket->getProc() ) )
	{
		inPacket->destroy();
		return;
	}
	m_netPackets.push( inPacket );
}

void CRobot::onDisconnect()
{
	m_start = false;

	printf( "CRobot::onDisconnect() name=%s\n", m_name.c_str() );
	LOG_INFO( "CRobot::onDisconnect() name=%s\n", m_name.c_str() );
}

void CRobot::checkNetPackets()
{
	Answer::NetPacket* inPacket = m_netPackets.pop();
	while ( inPacket != NULL )
	{
		int32_t err = handleNetPacket( inPacket );
		//if ( err != ERR_OK )
		//{
		//	std::cout << "CRobot::onNetPacket() proc = " << inPacket->getProc() << " err = " << err << std::endl;
		//}
		inPacket->destroy();
		inPacket = m_netPackets.pop();
	}
}

void CRobot::initExtSystems()
{
	m_ExtTask.Init( this );
	m_ExtSysMgr.Register( &m_ExtTask );

	m_ExtBag.Init( this );
	m_ExtSysMgr.Register( &m_ExtBag );

	m_ExtSkill.Init( this );
	m_ExtSysMgr.Register( &m_ExtSkill );
}

bool CRobot::isProcRegisted( ProcId_t nProc )
{
	switch ( nProc )
	{
	case SM_USER_TOKEN:
	case SM_LINE_LIST:
	case SM_CHARACTER_LIST:
	case SM_SKILL_LIST:
	case SM_ENTER_MAP:
	case SM_CHR_INFO:
	case SM_INSTANT_MOVE:
	case SM_MONSTER_INTO_MAP:
	case SM_UNIT_BASIC_DATA:
	case SM_MOVE:
		return true;
	default:break;
	}

	return m_ExtSysMgr.IsProcRegisted( nProc );
}

int32_t CRobot::handleNetPacket( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	ProcId_t nProc = inPacket->getProc();
	//printf( "CRobot::handleNetPacket name=%s, proc = %d\n", m_name.c_str(), nProc );
	switch ( nProc )
	{
		case SM_USER_TOKEN:				return onUserToken( inPacket );
		case SM_LINE_LIST:				return onLineList( inPacket );
		case SM_CHARACTER_LIST:			return onCharacterList( inPacket );
		case SM_ENTER_MAP:				return onEnterMap( inPacket );
		case SM_CHR_INFO:				return onCharInfo( inPacket );
		case SM_INSTANT_MOVE:			return onInstantMove( inPacket );
		case SM_MONSTER_INTO_MAP:		return onMonsterInMap( inPacket );
		case SM_UNIT_BASIC_DATA:		return onUnitBasicData( inPacket );
		case SM_MOVE:					return onUnitMove( inPacket );
		case SM_UNIT_ENTER_AREA:		return onUnitEnterArea( inPacket );
		//case SM_TASK_LIST:				return onTaskList( inPacket );
		//case SM_TASK_KILLED_MONSTER:	return onTaskKillMonster( inPacket );
        default:break;
	}
	
	return handleToExtSystem( inPacket );
}

void CRobot::Dispatch( NetPacket *packet )
{
	if ( NULL == packet )
	{
		return;
	}

	// 添加index
	int32_t offset = packet->getWOffset();
	int32_t oldSize = packet->getSize();
	int32_t addSize = sizeof( int32_t );
	packet->rightShift( addSize );
	packet->writeInt32( m_cgindex );
	packet->setWOffset( offset + addSize );
	//packet->setSize( oldSize + addSize );


	// 加自增长标记
	packet->writeInt32( m_nIncreace );
	if ( needIncreace( packet->getProc() ) )
	{
		++m_nIncreace;
	}

	// 加标记位
	int8_t nKey = 0;
	uint32_t woffset = packet->getWOffset();
	char* buffer = packet->getBuffer();
	for ( uint32_t i = 4; i < woffset; ++i )
	{
		nKey ^= buffer[i];
	}
	packet->writeInt8( nKey );
	packet->setSize( packet->getWOffset() );
	// 加密
	packet->decryCode();

	sendPacket( packet );
}

void CRobot::sendPacketTo( NetPacket *packet )
{
	if ( NULL == packet )
	{
		return;
	}

	// 加自增长标记
	packet->writeInt32( m_nIncreace );
	if ( needIncreace( packet->getProc() ) )
	{
		++m_nIncreace;
	}

	// 加标记位
	int8_t nKey = 0;
	uint32_t woffset = packet->getWOffset();
	char* buffer = packet->getBuffer();
	for ( uint32_t i = 4; i < woffset; ++i )
	{
		nKey ^= buffer[i];
	}
	packet->writeInt8( nKey );
	packet->setSize( packet->getWOffset() );
	// 加密
	packet->decryCode();
	sendPacket( packet );
}

bool CRobot::needIncreace( ProcId_t nProc )
{
	if (nProc > CM_CHARACTER_MIN && nProc < CM_CHARACTER_MAX)
	{
		return true;
	}
	else if (nProc > CM_GAME_MIN && nProc < CM_GAME_MAX)
	{
		return true;
	}
	else if (nProc > CM_GATE_MIN && nProc < CM_GATE_MAX)
	{
		if (nProc == CM_GATE_LOGIN || nProc == CM_GATE_LOGIN_ROBOT)
		{
			return false;
		}
		return true;
	}
	else if (nProc > CM_SOCIAL_MIN && nProc < CM_SOCIAL_MAX)
	{
		return true;
	}
	return false;
}

int32_t	CRobot::handleToExtSystem( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	ProcId_t nPorc = inPacket->getProc();
	return m_ExtSysMgr.DispatchNetDatas( nPorc, inPacket );
}

int32_t	CRobot::onUserToken( Answer::NetPacket* inPacket )
{
	m_uid	= inPacket->readInt32();
	m_sid	= inPacket->readInt32();
	m_token	= inPacket->readUTF8(true);

	sendLogin();
	return ERR_OK;
}

int32_t	CRobot::onLineList( Answer::NetPacket* inPacket )
{
	int32_t nCount = inPacket->readInt32();
	for ( int32_t i = 0; i < nCount; ++i )
	{
		int32_t nLine	= inPacket->readInt32();
		int32_t nStatus	= inPacket->readInt32();
	}

	sendGetCharacter();
	return ERR_OK;
}

int32_t	CRobot::onCharacterList( Answer::NetPacket* inPacket )
{
	m_lastLoginTime = inPacket->readInt32();
	m_lastLoginIp	= inPacket->readUTF8( true );
	int32_t nChrNum	= inPacket->readInt32();
	if ( nChrNum > 0 )
	{
		m_cid		= inPacket->readInt64();
		m_name		= inPacket->readUTF8(true);
		m_sex		= inPacket->readInt32();
		m_style		= inPacket->readInt32();
		m_head		= inPacket->readInt32();
		m_kingdom	= inPacket->readInt32();
		m_job		= inPacket->readInt32();
		m_level		= inPacket->readInt32();
		m_mapid		= inPacket->readInt32();
		m_x			= inPacket->readInt32();
		m_y			= inPacket->readInt32();
		sendEnterGame();
	}
	else
	{
		sendCreateCharacter();
	}
	return ERR_OK;
}

int32_t CRobot::onEnterMap( Answer::NetPacket* inPacket )
{
	//SM_ENTER_MAP
	m_cid			= inPacket->readInt64();
	m_kingdom		= inPacket->readInt32();
	m_mapid			= inPacket->readInt32();
	m_x				= inPacket->readInt32();
	m_y				= inPacket->readInt32();
	m_line			= inPacket->readInt32();

	m_NextPos.x	= m_x;
	m_NextPos.y	= m_y;

	m_nActionTick = DayTime::tick();

	if ( !m_start )
	{
		m_start = true;
	}

	m_nState = PS_STAND;
	return ERR_OK;
}

int32_t CRobot::onCharInfo( Answer::NetPacket* inPacket )
{
	//SM_ENTER_MAP
	m_cid			= inPacket->readInt64();			// cid
	m_name			= inPacket->readUTF8( true );		// 名字
	FamilyId_t fid	= inPacket->readInt64();			// 帮派ID
	string fname	= inPacket->readUTF8( true );		// 帮派名字
	m_sex			= inPacket->readInt8();				// 性别
	m_job			= inPacket->readInt8();				// 职业
	m_level			= inPacket->readInt16();			// 等级
	int64_t exp		= inPacket->readInt64();			// 当前经验
	int64_t	mexp	= inPacket->readInt64();			// 升级需求经验值
	m_nHP			= inPacket->readInt32();			// 当前血量
	m_nMP			= inPacket->readInt32();			// 当前法力值
	int32_t pp		= inPacket->readInt32();			// 当前体力值
	int32_t xp		= inPacket->readInt32();			// 当前XP值
	m_nMaxHP		= inPacket->readInt32();			// 最大血量
	m_nMaxMP		= inPacket->readInt32();			// 最大法力值
	int32_t maxpp	= inPacket->readInt32();			// 最大体力值
	int32_t maxxp	= inPacket->readInt32();			// 最大XP值
	int32_t patks	= inPacket->readInt32();			// 最小物理攻击		
	int32_t patkl	= inPacket->readInt32();			// 最大物理攻击
	int32_t	matks	= inPacket->readInt32();			// 最小魔法攻击
	int32_t matkl	= inPacket->readInt32();			// 最大魔法攻击
	int32_t pdef	= inPacket->readInt32();			// 物理防御
	int32_t mdef	= inPacket->readInt32();			// 魔法防御
	int32_t hit		= inPacket->readInt32();			// 命中
	int32_t dod		= inPacket->readInt32();			// 闪避
	int32_t cri		= inPacket->readInt32();			// 暴击
	int32_t battle	= inPacket->readInt32();			// 战斗力
	int32_t pkvl	= inPacket->readInt32();			// pk值
	int32_t pkmd	= inPacket->readInt8();				// pk模式
	int32_t pktm	= inPacket->readInt32();			// pk保护时间
	int32_t blnm	= inPacket->readInt8();				// 蓝名
	int32_t fst		= inPacket->readInt8();				// 是否是第一次进入游戏
	int32_t stall	= inPacket->readInt8();				// 摆摊状态

	if ( m_nHP <= 0 )
	{
		m_road.clear();
		m_NextPos = getCurTile();
		m_pTarget = NULL;
		m_nState = PS_GHOST;
	}
	else
	{
		if ( m_nState == PS_GHOST )
		{
			m_nState = PS_STAND;
		}
	}
	return ERR_OK;
}

int32_t CRobot::onInstantMove( Answer::NetPacket* inPacket )
{
	//SM_ENTER_MAP
	int32_t nCharId	= inPacket->readInt32();
	int8_t	nType	= inPacket->readInt8();
	if ( nType == ET_PLAYER && nCharId == m_cid )
	{
		m_x	= inPacket->readInt16();
		m_y	= inPacket->readInt16();

		m_NextPos.x	= m_x;
		m_NextPos.y	= m_y;
		m_nActionTick = DayTime::tick();
		m_nState = PS_STAND;
	}
	return ERR_OK;
}

int32_t CRobot::onMonsterInMap( Answer::NetPacket* inPacket )
{
	Map* pMap = MAP_MANAGER.GetMap( m_mapid );
	if ( NULL == pMap )
	{
		return ERR_INVALID_DATA;
	}
	//SM_MONSTER_INTO_MAP
	int32_t nCount = inPacket->readInt32();
	for ( int32_t i = 0; i < nCount; ++i )
	{
		EntityId_t	nUnitId	= inPacket->readInt64();
		int32_t		nMid	= inPacket->readInt32();
		int16_t		nX		= inPacket->readInt16();
		int16_t		nY		= inPacket->readInt16();
		int16_t		nTarX	= inPacket->readInt16();
		int16_t		nTarY	= inPacket->readInt16();
		int32_t		nHP		= inPacket->readInt32();
		int32_t		nMaxHP	= inPacket->readInt32();
		int16_t		nSpeed	= inPacket->readInt16();
		int8_t		nSide	= inPacket->readInt8();
		FamilyId_t	nFamily	= inPacket->readInt64();

		Monster* pMonster = pMap->getMonster( nUnitId );
		if ( NULL == pMonster )
		{
			pMonster = new Monster;
			pMonster->Init( nUnitId, m_mapid, nX, nY, nHP, nMaxHP, nMid );
			pMap->AddMonster( pMonster );
		}
		else
		{
			pMonster->UpdateAttr( nHP, nMaxHP );
			pMonster->UpdatePosition( nX, nY );
		}
	}

	return ERR_OK;
}

int32_t CRobot::onUnitBasicData( Answer::NetPacket* inPacket )
{
	Map* pMap = MAP_MANAGER.GetMap( m_mapid );
	if ( NULL == pMap )
	{
		return ERR_INVALID_DATA;
	}

	EntityId_t nUnitId	= inPacket->readInt64();
	int8_t		nType	= inPacket->readInt8();
	int32_t		nHP		= inPacket->readInt32();
	int32_t		nMaxHP	= inPacket->readInt32();
	int16_t		nSpeed	= inPacket->readInt16();
	int8_t		nFlag	= inPacket->readInt8();
	int32_t		nDTime	= inPacket->readInt32();

	if ( nType == ET_MONSTER )
	{
		Monster* pMonster = pMap->getMonster( nUnitId );
		if ( NULL == pMonster )
		{
			return ERR_INVALID_DATA;
		}
		pMonster->UpdateAttr( nHP, nMaxHP );
	}

	return ERR_OK;
}

int32_t CRobot::onUnitMove( Answer::NetPacket* inPacket )
{
	Map* pMap = MAP_MANAGER.GetMap( m_mapid );
	if ( NULL == pMap )
	{
		return ERR_INVALID_DATA;
	}

	EntityId_t nUnitId	= inPacket->readInt64();
	int8_t	nType		= inPacket->readInt8();
	int16_t nX			= inPacket->readInt16();
	int16_t nY			= inPacket->readInt16();

	if ( nType == ET_MONSTER )
	{
		Monster* pMonster = pMap->getMonster( nUnitId );
		if ( NULL == pMonster )
		{
			return ERR_INVALID_DATA;
		}
		pMonster->UpdatePosition( nX, nY );
	}
	//else if ( nType == ET_PLAYER )
	//{
	//	if ( nUnitId == m_cid )
	//	{
	//		m_NextPos.x = nX;
	//		m_NextPos.y = nY;

	//		//Position curTile = getCurTile();
	//		//m_direction = Map::tileDirection( curTile.x, curTile.y, m_NextPos.x, m_NextPos.y );

	//		//Position curPos = getCurPos();
	//		//Position tarPos = Map::tileToPixel( m_NextPos.x, m_NextPos.y );

	//		//double distance = sqrt(static_cast<double>((tarPos.x-curPos.x)*(tarPos.x-curPos.x) + (tarPos.y-curPos.y)*(tarPos.y-curPos.y)));
	//		//int32_t nUseTime = roundInt( distance / getDirectionSpeed() * 1000 );
	//		//m_nActionTick = m_nCurTick + nUseTime;

	//		resetMoveTick( getCurTile(), m_NextPos );
	//	}
	//}

	return ERR_OK;
}

int32_t CRobot::onUnitEnterArea( Answer::NetPacket* inPacket )
{
	Map* pMap = MAP_MANAGER.GetMap( m_mapid );
	if ( NULL == pMap )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCount = inPacket->readInt32();
	for ( int32_t i = 0; i < nCount; ++i )
	{
		EntityId_t nUnitId	= inPacket->readInt64();
		int8_t	nType		= inPacket->readInt8();
		int32_t nPosX		= inPacket->readInt32();
		int32_t nPosY		= inPacket->readInt32();
		int16_t nX			= inPacket->readInt16();
		int16_t nY			= inPacket->readInt16();
		int32_t nHP			= inPacket->readInt32();
		int32_t nMaxHP		= inPacket->readInt32();
		int32_t nSpeed		= inPacket->readInt32();

		if ( nType == ET_MONSTER )
		{
			Monster* pMonster = pMap->getMonster( nUnitId );
			if ( NULL == pMonster )
			{
				return ERR_INVALID_DATA;
			}
			pMonster->UpdatePosition( nX, nY );
			pMonster->UpdateAttr( nHP, nMaxHP );
		}
	}
	return ERR_OK;
}

void CRobot::sendLogin()
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cgindex );
	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeUTF8( m_token );

	packet->writeUTF8( "" );
	packet->writeUTF8( "" );
	packet->writeUTF8( "" );
	packet->writeUTF8( "" );

	packet->setType( PACK_PROC );
	packet->setProc( CM_GATE_LOGIN );
	packet->setSize( packet->getWOffset() );

	sendPacketTo( packet );
}

void CRobot::sendGetCharacter()
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cgindex );
	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );

	packet->setType( PACK_PROC );
	packet->setProc( CM_GET_CHARACTER );
	packet->setSize( packet->getWOffset() );

	sendPacketTo( packet );
}

void CRobot::sendEnterGame()
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt64( m_cid );
	packet->writeInt32( m_line );

	packet->setType( PACK_PROC );
	packet->setProc( CM_ENTER_GAME );
	packet->setSize( packet->getWOffset() );

	sendPacketTo( packet );
}

void CRobot::sendCreateCharacter()
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cgindex );
	packet->writeUTF8( m_name );
	packet->writeInt32( m_sex );
	packet->writeInt32( m_job );
	packet->writeInt32( m_head );

	packet->setType( PACK_PROC );
	packet->setProc( CM_NEW_CHARACTER );
	packet->setSize( packet->getWOffset() );

	sendPacketTo( packet );
}

void CRobot::sendTransToMap( MapId_t mapid, int32_t x, int32_t y )
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cgindex );
	packet->writeInt32( 4 );					// 传送
	packet->writeInt32( mapid );
	packet->writeInt32( x );
	packet->writeInt32( y );

	packet->setType( PACK_PROC );
	packet->setProc( CM_DEBUG_CMD );
	packet->setSize( packet->getWOffset() );

	sendPacketTo( packet );
}

void CRobot::onMove( int64_t curTick )
{
	if ( m_nState != PS_WALK && m_nState != PS_WALK_ATTACK )
	{
		return;
	}

	if ( curTick < m_nActionTick )
	{
		return;
	}

	if ( m_nTargetMap != m_mapid )
	{
		// 跨地图寻路 直接飞吧
		transToTarget( m_nTargetMap, m_TargetPos.x, m_TargetPos.y );
		m_nActionTick = m_nCurTick + 500;
		return;
	}

	if ( getCurTile() == m_NextPos )
	{
		moveToNextPos();
		return;
	}

	m_x = m_NextPos.x;
	m_y = m_NextPos.y;

	moveToNextPos();

	//printf( "CRobot::onMove() tick=%lld,tarx=%d,tary=%d,delay=%d\n",curTick, m_NextPos.x, m_NextPos.y, m_nMoveDelay );
}

void CRobot::SetTarget( MapId_t mid, Position pos, int8_t nState )
{
	printf( "SetTarget mid=%d, x=%d, y=%d, state=%d\n", mid, pos.x, pos.y, nState );
	m_nTargetMap = mid;
	m_TargetPos = pos;
	m_nState = nState;
}

void CRobot::moveToNextPos()
{
	//if ( NULL == m_pTarget )
	//{
	//	return;
	//}

	Map* pMap = MAP_MANAGER.GetMap( m_mapid );
	if ( NULL == pMap )
	{
		return;
	}

	//resetRoad();
	if ( m_road.empty() )
	{
		resetRoad();
	}

	if ( m_road.empty() )
	{
		return;
	}

	//Position curTile = getCurTile();
	//Position tarTile = pMap->firstLinePosition( curTile, m_TargetPos );
	//if ( tarTile.x < 0 || tarTile.y < 0 )
	//{
	//	return;
	//}

	//if ( curTile == tarTile )
	//{
	//	return;
	//}

	//m_NextPos = tarTile;
	m_NextPos = m_road.front();
	m_road.pop_front();

	resetMoveTick( getCurTile(), m_NextPos );
	moveToPos( m_NextPos.x, m_NextPos.y );
}

void CRobot::clearTarget()
{
	m_pTarget = NULL;
}

bool CRobot::isArrived()
{
	if ( ( m_nTargetMap > 0 && m_nTargetMap != m_mapid ) || ( m_TargetPos.x > 0 && m_TargetPos.y > 0 && m_TargetPos != getCurTile() ) )
	{
		return false;
	}
	return true;
}

void CRobot::onStand( int64_t curTick )
{
	printf( "onStand()\n" );
	const TaskDest* pDest = m_ExtTask.GetDest();
	if ( pDest != NULL )
	{
		if ( pDest->type == DS_NPC )		// npc
		{
			CfgNpc* pNpc = CFG_DATA.getNpc( pDest->pram );
			if ( pNpc != NULL )
			{
				SetTarget( pNpc->mapids[0], Position( pNpc->x, pNpc->y ) );
			}
			if ( isArrived() )
			{
				m_ExtTask.EndTask();
				return;
			}
		}
		else if ( pDest->type == DS_MONSTER )	// monster
		{
			Map* pMap = MAP_MANAGER.GetMap( m_mapid );
			if ( pMap != NULL )
			{
				Monster* pMonster = pMap->GetNearestAliveMonster(  getCurTile(), pDest->pram );
				if ( pMonster != NULL )
				{
					m_pTarget = pMonster;
					SetTarget( pMonster->GetMapId(), pMonster->GetCurTile(), PS_WALK_ATTACK );
					return;
				}
				else
				{
					CfgMapMonster* pMapMonster = CFG_DATA.GetMapMonsterInfoByMid( pDest->pram, m_mapid );
					if ( pMapMonster != NULL )
					{
						SetTarget( pMapMonster->mapid, Position( pMapMonster->x, pMapMonster->y ) );
					}
				}
			}
		}
		else
		{
			m_ExtTask.ForceSubmit();
		}
	}

	if ( !isArrived() )
	{
		m_nState = PS_WALK;
		return;
	}

	return;
}

void CRobot::onWalk( int64_t curTick )
{
	printf( "onWalk()\n" );
	Map* pMap = MAP_MANAGER.GetMap( m_nTargetMap );
	if ( NULL == pMap )
	{
		return;
	}

	if ( m_nTargetMap == m_mapid && m_TargetPos == Position( m_x, m_y ) )
	{
		m_nState = PS_STAND;
		return;
	}

	//if ( m_nTargetMap != m_mapid )
	//{
	//	// 跨地图寻路 直接飞吧
	//	transToTarget( m_nTargetMap, m_TargetPos.x, m_TargetPos.y );
	//}
	//else if ( m_TargetPos != Position( m_x, m_y ) )
	//{
	//	// 本地图寻路
	//	Position pos = pMap->firstLinePosition( Position( m_x, m_y ), m_TargetPos );
	//	moveToPos( pos.x, pos.y );
	//}
	//else
	//{
	//	// 已经到达
	//}

	return;
}

void CRobot::onWalkAttack( int64_t curTick )
{
	printf( "onWalkAttack()\n" );
	if ( NULL == m_pTarget )
	{
		m_nState = PS_STAND;
		return;
	}

	if ( !m_pTarget->IsAlive() )
	{
		clearTarget();
		m_nState = PS_STAND;
		return;
	}

	if ( getCurTile().tileDistance( m_pTarget->GetCurTile() ) <= 4 )
	{
		m_nState = PS_ATTACK;
		return;
	}
}

void CRobot::onAttack( int64_t curTick )
{
	printf( "onAttack()\n" );
	if ( NULL == m_pTarget )
	{
		m_nState = PS_STAND;
		return;
	}

	if ( !m_pTarget->IsAlive() )
	{
		clearTarget();
		m_nState = PS_STAND;
		return;
	}

	if ( getCurTile().tileDistance( m_pTarget->GetCurTile() ) > 4 )
	{
		m_nState = PS_WALK_ATTACK;
		return;
	}

	int32_t nSkillId	= m_ExtSkill.GetSkillId( m_nCurTick );
	if ( nSkillId > 0 )
	{
		sendAttack( nSkillId );
		m_nActionTick = m_nCurTick + 1000;
	}
}

void CRobot::onGhost( int64_t curTick )
{
	sendRelive();
}

void CRobot::sendAttack( int32_t nSkillId )
{
	if ( NULL == m_pTarget )
	{
		return;
	}

	Map* pMap = MAP_MANAGER.GetMap( m_mapid );
	if ( NULL == pMap )
	{
		return;
	}

	CfgSkill *pCfgSkill = CFG_DATA.getSkill( nSkillId );
	if ( NULL == pCfgSkill )
	{
		return;
	}

	switch( pCfgSkill->range )
	{
	case SR_SELF:
		{
			NetPacket* packet = CLIENT_SERVER.popNetpacket();
			if ( NULL == packet )
			{
				return;
			}

			packet->writeInt32( nSkillId );
			packet->writeInt32( m_ExtSkill.GetSkillFlag() );
			packet->writeInt64( m_cid );
			packet->writeInt32( ET_PLAYER );

			packet->setType( PACK_PROC );
			packet->setProc( CM_DO_UNIT_SKILL );
			packet->setSize( packet->getWOffset() );

			Dispatch( packet );
		}
		break;
	case SR_SOLO:
		{
			NetPacket* packet = CLIENT_SERVER.popNetpacket();
			if ( NULL == packet )
			{
				return;
			}

			packet->writeInt32( nSkillId );
			packet->writeInt32( m_ExtSkill.GetSkillFlag() );
			packet->writeInt64( m_pTarget->GetId() );
			packet->writeInt32( m_pTarget->GetType() );

			packet->setType( PACK_PROC );
			packet->setProc( CM_DO_UNIT_SKILL );
			packet->setSize( packet->getWOffset() );

			Dispatch( packet );
		}
		break;
	default:
		{
			UnitVector targets = getSkillTargets( pCfgSkill );

			NetPacket* packet = CLIENT_SERVER.popNetpacket();
			if ( NULL == packet )
			{
				return;
			}

			packet->writeInt32( nSkillId );
			packet->writeInt32( m_ExtSkill.GetSkillFlag() );

			packet->writeInt32( m_x );
			packet->writeInt32( m_y );

			int32_t nCount = 0;
			uint32_t oldOffset = packet->getWOffset();
			packet->writeInt32( nCount );

			for ( UnitVector::iterator iter = targets.begin(); iter != targets.end(); ++iter )
			{
				Unit* pUnit = *iter;
				if ( pUnit != NULL )
				{
					packet->writeInt64( pUnit->GetId() );
					packet->writeInt32( pUnit->GetType() );
					++nCount;
				}
			}

			uint32_t offset = packet->getWOffset();
			packet->setWOffset( oldOffset );
			packet->writeInt32( nCount );
			packet->setWOffset( offset );

			packet->setType( PACK_PROC );
			packet->setProc( CM_DO_UNIT_SKILL );
			packet->setSize( packet->getWOffset() );

			Dispatch( packet );
		}
		break;
	}
}

void CRobot::sendRelive()
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cgindex );

	packet->setType( PACK_PROC );
	packet->setProc( CM_SAFE_REVIVE );
	packet->setSize( packet->getWOffset() );

	sendPacketTo( packet );
}

void CRobot::checkUseMedicine()
{
	if ( m_nState == PS_GHOST )
	{
		return;
	}

	if ( m_nCurTick < m_nMedicineTick + 3000 )
	{
		return;
	}
	m_nMedicineTick = m_nCurTick;

	if ( m_nHP < m_nMaxHP * 3 / 4 )
	{
		m_ExtBag.SendUseMedicine();
		return;
	}

	if ( m_nMP < m_nMaxMP / 10 )
	{
		m_ExtBag.SendUseMedicine( 5 );
	}
}

void CRobot::moveToPos( int32_t x, int32_t y )
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( m_cgindex );
	packet->writeInt16( m_x );		// currentX
	packet->writeInt16( m_y );		// currentY
	packet->writeInt16( x );		// targetX 
	packet->writeInt16( y );		// targetY 
	packet->writeInt16( x );		// finalX
	packet->writeInt16( y );		// finalY
	packet->writeInt8( 0 );			// direction

	packet->setType( PACK_PROC );
	packet->setProc( CM_MOVE );
	packet->setSize( packet->getWOffset() );

	sendPacketTo( packet );

	printf( "Move from pos %d,%d to pos %d,%d\n", m_x, m_y, x, y );

	//m_x = x;
	//m_y = y;
}

void CRobot::transToTarget( MapId_t mapid, int32_t x, int32_t y )
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( 4 );					// 提交任务
	packet->writeInt32( mapid );
	packet->writeInt32( x );
	packet->writeInt32( y );

	packet->setType( PACK_PROC );
	packet->setProc( CM_DEBUG_CMD );
	packet->setSize( packet->getWOffset() );

	Dispatch( packet );

	printf( "Fly from pos map %d (%d,%d) to map %d (%d,%d)\n", m_mapid, m_x, m_y, mapid, x, y );
}

double CRobot::getDirectionSpeed( int8_t dir )
{
	double baseSpeed = m_nSpeed;
	double directionSpeed = baseSpeed;

	switch ( dir )
	{
	case DOWN:
	case UP:
		directionSpeed = baseSpeed;
		break;
	case LEFT:
	case RIGHT:
		directionSpeed = baseSpeed*1.2;
		break;
	case DOWN_LEFT:
	case UP_LEFT:
	case UP_RIGHT:
	case DOWN_RIGHT:
		directionSpeed = baseSpeed*1.5;
		break;
	default:
		LOG_ERROR("Unit::setTargetPosition with m_direction = %d\n", m_direction);
		break;
	}

	return directionSpeed;
}

void CRobot::resetMoveTick( const Position& curTile, const Position& tarTile )
{
	int8_t dir = Map::tileDirection( curTile.x, curTile.y, tarTile.x, tarTile.y );

	Position curPos = Map::tileToPixel( curTile.x, curTile.y );
	Position tarPos = Map::tileToPixel( tarTile.x, tarTile.y );

	double distance = sqrt(static_cast<double>((tarPos.x-curPos.x)*(tarPos.x-curPos.x) + (tarPos.y-curPos.y)*(tarPos.y-curPos.y)));
	int32_t nUseTime = roundInt( distance / getDirectionSpeed( dir ) * 1000 );
	m_nActionTick = m_nCurTick + nUseTime;
}

void CRobot::resetRoad()
{
	Position src = getCurTile();
	Position tar = m_TargetPos;
	if ( src == tar )
	{
		return;
	}

	Map* pMap = MAP_MANAGER.GetMap( m_mapid );
	if ( NULL == pMap )
	{
		return;
	}

	PathFinder pathFinder( *pMap );
	PositionVector path = pathFinder.findPath( getCurTile(), tar );
	if ( path.size() < 2 )
	{
		printf( "CRobot::resetRoad() search road fail!! mapid=%d, src(%d,%d), tar(%d,%d)\n", m_mapid, src.x, src.y, tar.x, tar.y );
		return;
	}

	m_road.clear();

	Direction dir = Map::tileDirection( src.x, src.y, path[1].x, path[1].y);
	Position pos = path[1];

	for (size_t i = 2; i < path.size(); ++i)
	{
		Direction nextDir = Map::tileDirection( path[i-1].x, path[i-1].y, path[i].x, path[i].y);
		if ( nextDir != dir )
		{
			dir = nextDir;
			m_road.push_back( pos );
		}

		pos = path[i];
	}
	m_road.push_back( pos );
}

UnitVector CRobot::getSkillTargets( CfgSkill *pCfg )
{
	UnitVector targets;
	if ( NULL == pCfg || NULL == m_pTarget )
	{
		return targets;
	}

	Map* pMap = MAP_MANAGER.GetMap( m_mapid );
	if ( NULL == pMap )
	{
		return targets;
	}

	Position center = getCurTile();
	if ( pCfg->range == SR_AROUND && pCfg->self != STP_SELF && pCfg->self != STP_POS )
	{
		center = m_pTarget->GetCurTile();
	}

	UnitList areaUnits;
	pMap->getAreaMonsters( center, pCfg->area, areaUnits );
	Direction dir = Map::tileDirection( m_x, m_y, m_pTarget->GetX(), m_pTarget->GetY() );
	switch (pCfg->range)
	{
	case SR_LINE:
		{
			for ( UnitList::iterator it = areaUnits.begin(); it != areaUnits.end(); ++it)
			{
				Unit* pTarget = *it;
				if ( pTarget != NULL )
				{
					Direction tdir = Map::tileDirection( center.x, center.y, pTarget->GetX(), pTarget->GetY() );
					if ( tdir != dir )
					{
						continue;
					}
					targets.push_back( pTarget );
				}
			}
		}
		break;
	case SR_AROUND:
		{
			for ( UnitList::iterator it = areaUnits.begin(); it != areaUnits.end(); ++it)
			{
				Unit* pTarget = *it;
				if ( pTarget != NULL )
				{
					targets.push_back( pTarget );
				}
			}
		}
		break;
	case SR_HALF_ROUND:
		{
			int32_t tx = DELTA_X[dir];
			int32_t ty = DELTA_Y[dir];

			for ( UnitList::iterator it = areaUnits.begin(); it != areaUnits.end(); ++it)
			{
				Unit* pTarget = *it;
				if ( pTarget != NULL )
				{
					Position tpos = pTarget->GetCurTile();
					if ( ty == 0 )					// 左右
					{
						if ( ( tpos.x - center.x ) * tx < 0 )
						{
							continue;
						}
					}
					else if ( tx == 0 )				// 上下
					{
						if ( ( tpos.y - center.y ) * ty < 0 )
						{
							continue;
						}
					}
					else if ( tx > 0  )	
					{
						if ( ty > 0 )				// 右下
						{
							if ( ( tpos.y - center.y ) + ( tpos.x - center.x ) * 2 < 0 )
							{
								continue;
							}
						}
						else if ( ty < 0 )			// 右上
						{
							if ( ( tpos.y - center.y ) > ( tpos.x - center.x ) * 2 )
							{
								continue;
							}
						}
					}
					else if ( tx < 0  )
					{
						if ( ty < 0 )				// 左上
						{
							if ( ( tpos.y - center.y ) + ( tpos.x - center.x ) * 2 > 0 )
							{
								continue;
							}
						}
						else if ( ty > 0 )			// 左下
						{
							if ( ( tpos.y - center.y ) < ( tpos.x - center.x ) * 2 )
							{
								continue;
							}
						}
					}

					targets.push_back( pTarget );
				}
			}

		}
		break;
	default:
		break;
	}

	if (static_cast<int32_t>(targets.size()) > pCfg->target_num)
	{
		random_shuffle(targets.begin(), targets.end());
		targets.resize(pCfg->target_num);
	}

	return targets;
}
