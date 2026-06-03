#include "SocialDaTiHD.h"
#include "SocialService.h"
#include "PlayerManager.h"
#include <algorithm>
using namespace Answer;
#define SEND_RANK_MAX_COUNT 3	//发送排行榜前三
#define LOWEST_POINTS		20  //每题最低积分
CSocialDaTiHD::CSocialDaTiHD()
{
	m_DaTiState					= 0;			
	m_DaTiHDStartSeconds		= 0;	
	m_QuestionsStartSeconds		= 0;
	m_QuestionsIndex			= 0;		
	m_QuestionsId				= 0;			
	m_AnswerId					= 0;
	m_HdId						= 0;
	m_DaTiInfo.clear();
}

CSocialDaTiHD::~CSocialDaTiHD()
{

}

void CSocialDaTiHD::Reset()
{
	m_DaTiState					= 0;			
	m_DaTiHDStartSeconds		= 0;	
	m_QuestionsStartSeconds		= 0;
	m_QuestionsIndex			= 0;		
	m_QuestionsId				= 0;			
	m_AnswerId					= 0;
	m_HdId						= 0;
	m_DaTiInfo.clear();
}

int32_t	CSocialDaTiHD::OnRecvHDReadyStart( Answer::NetPacket* InPacket )
{
	if ( NULL == InPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t NowSeconds		= InPacket->readInt32();
	m_DaTiHDStartSeconds	= InPacket->readInt32();
	m_HdId					= InPacket->readInt32();
	SetHDState( AS_READY );

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return ERR_SYETEM_ERR;
	}
	packet->writeInt32( m_DaTiHDStartSeconds - NowSeconds );
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_SEND_DA_TI_READY_START);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.worldBroadcast( packet );
	return ERR_OK;
}

void CSocialDaTiHD::SendCharReadyStart( SocialPlayer* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	int32_t NowSeconds = GetNowSeconds();
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_DaTiHDStartSeconds - NowSeconds );
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_SEND_DA_TI_READY_START);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet );
}

int32_t	CSocialDaTiHD::OnRecvHDStart( Answer::NetPacket* packet )
{
	SetHDState( AS_RUNNING );
	return ERR_OK;
}

int32_t CSocialDaTiHD::OnRecvHDEnd( Answer::NetPacket* packet )
{
	SetHDState( AS_END );
	SortRank( m_DaTiInfo );
	SendRankInfo();	
	SendDaTiHDEndToGs();
	Reset();
	return ERR_OK;
}

void CSocialDaTiHD::SortRank( DaTiInofVct & DaTiInfo )
{
	std::sort( DaTiInfo.begin(), DaTiInfo.end(), std::greater<DaTiHDInfo>() );
}

int32_t CSocialDaTiHD::OnRecvRandAnswer()
{
	DaTiInofVct::iterator it = m_DaTiInfo.begin();
	for ( ; it != m_DaTiInfo.end(); ++it )
	{
		if ( it->m_LastAnswerIndex != m_QuestionsIndex )
		{
			int32_t nRand = RANDOM.generate( 1, 4 );
			if ( nRand == m_AnswerId )
			{
				it->m_DaTiState = ANSWER_IS_RIGHT;
				it->m_Points += LOWEST_POINTS;
				it->m_LastPoints = LOWEST_POINTS;
			}
			else
			{
				it->m_DaTiState = ANSWER_IS_WRONG;
				it->m_LastPoints = 0;
			}
			it->m_CostTime += RAND_ANSWER_TIME;
			it->m_LastAnswerIndex = m_QuestionsIndex;
			it->m_LastAnswerId = nRand;
		}
	}
	SortRank(  m_DaTiInfo );
	DaTiInofVct::iterator itTmp = m_DaTiInfo.begin();
	for ( ; itTmp != m_DaTiInfo.end(); ++itTmp )
	{
		SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( itTmp->m_CharID );
		if ( NULL == pSocialPlayer )
		{
			continue;
		}
		SendQuestionsToClient(pSocialPlayer);
		SendCharRankInfo(pSocialPlayer);
	}
	SendRankInfo();
	return ERR_OK;
}

int32_t CSocialDaTiHD::OnRecvQuestionsInfo( Answer::NetPacket* InPacket )
{
	if ( NULL == InPacket )
	{
		return ERR_SYETEM_ERR;
	}
	m_QuestionsIndex			= InPacket->readInt8();				
	m_QuestionsId				= InPacket->readInt32();					
	m_AnswerId					= InPacket->readInt8();
	m_QuestionsStartSeconds		= InPacket->readInt32();
	SendQuestionsToClient();
	return ERR_OK;
}

void CSocialDaTiHD::SendQuestionsToClient( SocialPlayer* pPlayer )
{
	int32_t NowSeconds = GetNowSeconds();
	
	if ( NULL == pPlayer ) //游戏服发来题目信息
	{
		NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt8( m_QuestionsIndex );
		packet->writeInt32( m_QuestionsId );
		packet->writeInt32( DA_TIME_MAX_TIME - ( NowSeconds - m_QuestionsStartSeconds ) );
		packet->writeInt8( 1 );
		packet->writeInt8( 0 );
		packet->writeInt32( 0 );
		packet->setType(PACK_DISPATCH);
		packet->setProc(SM_SEND_QUESTIONS_TO_CLIENT);
		packet->setSize(packet->getWOffset());
		SOCIAL_SERVICE.worldBroadcast( packet );
	}
	else
	{
		bool IsInDaTiInfo = false;
		DaTiInofVct::iterator it =  m_DaTiInfo.begin();
		for ( ; it != m_DaTiInfo.end(); ++it )
		{
			if ( it->m_CharID == pPlayer->getCid() )
			{
				IsInDaTiInfo = true;
				NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
				if (NULL == packet)
				{
					return;
				}
				packet->writeInt8( m_QuestionsIndex );
				packet->writeInt32( m_QuestionsId );
				packet->writeInt32( DA_TIME_MAX_TIME - ( NowSeconds - m_QuestionsStartSeconds ) );
				if ( it->m_LastAnswerIndex != m_QuestionsIndex )
				{	
					packet->writeInt8( 1 );
					packet->writeInt8( 0 );
					packet->writeInt32( 0 );
				}
				else
				{
					packet->writeInt8( it->m_DaTiState );
					packet->writeInt8( it->m_LastAnswerId );
					packet->writeInt32( it->m_LastPoints );
				}
				packet->setType(PACK_DISPATCH);
				packet->setProc(SM_SEND_QUESTIONS_TO_CLIENT);
				packet->setSize(packet->getWOffset());
				SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet );
				break;
			}
		}
		if ( !IsInDaTiInfo )
		{
			NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
			if (NULL == packet)
			{
				return;
			}
			packet->writeInt8( m_QuestionsIndex );
			packet->writeInt32( m_QuestionsId );
			packet->writeInt32( DA_TIME_MAX_TIME - ( NowSeconds - m_QuestionsStartSeconds ) );
			packet->writeInt8( 1 );
			packet->writeInt8( 0 );
			packet->writeInt32( 0 );
			packet->setType(PACK_DISPATCH);
			packet->setProc(SM_SEND_QUESTIONS_TO_CLIENT);
			packet->setSize(packet->getWOffset());
			SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet );
		}
	}
}

int32_t CSocialDaTiHD::OnReqAnswerQuestion( SocialPlayer* pPlayer, Answer::NetPacket* packet )
{
	if ( NULL == pPlayer || NULL == packet )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t	 QuestionsIndex = packet->readInt8();
	int8_t	 AnswerId		= packet->readInt8();
	DaTiInofVct::iterator it = m_DaTiInfo.begin();
	if ( QuestionsIndex != m_QuestionsIndex )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t DiffSeconds		= 0;
	int32_t CanAddPoints	= GetPoints( DiffSeconds );
	if ( DiffSeconds > RAND_ANSWER_TIME )
	{
		return ERR_SYETEM_ERR;
	}
	if ( AnswerId != m_AnswerId )
	{
		CanAddPoints = 0;
	}
	int32_t CharRank = 0;
	bool    IsInDaTiInfo = false;
	for ( ; it != m_DaTiInfo.end(); ++it )
	{
		CharRank++;
		if ( pPlayer->getCid() == it->m_CharID )
		{
			if ( it->m_LastAnswerIndex == QuestionsIndex )
			{
				return ERR_SYETEM_ERR;
			}
			IsInDaTiInfo = true;
			it->m_Points += CanAddPoints;
			it->m_CostTime += RAND_ANSWER_TIME;
			it->m_LastAnswerIndex = m_QuestionsIndex;
			it->m_LastPoints = CanAddPoints;
			it->m_LastAnswerId = AnswerId;
			if ( CanAddPoints > 0 )
			{
				it->m_DaTiState	 = ANSWER_IS_RIGHT;
			}
			else
			{
				it->m_DaTiState	 = ANSWER_IS_WRONG;
			}
			break;
		}
	}
	if ( !IsInDaTiInfo )
	{
		DaTiHDInfo DaTiInfo;
		DaTiInfo.m_CharID			= pPlayer->getCid();
		DaTiInfo.m_Name				= pPlayer->getName();

		DaTiInfo.m_Points			+= CanAddPoints;
		DaTiInfo.m_CostTime			+= DiffSeconds;
		DaTiInfo.m_LastAnswerIndex   = QuestionsIndex; 
		DaTiInfo.m_LastPoints		 = CanAddPoints;
		DaTiInfo.m_LastAnswerId	     = AnswerId;
		if ( CanAddPoints > 0 )
		{
			DaTiInfo.m_DaTiState	 = ANSWER_IS_RIGHT;
		}
		else
		{
			DaTiInfo.m_DaTiState	 = ANSWER_IS_WRONG;
		}
		m_DaTiInfo.push_back( DaTiInfo );	
	}
	SendAnswered( pPlayer );
	SendQuestionsToClient( pPlayer );
	SendCharRankInfo(pPlayer);
	return ERR_OK;
}

void CSocialDaTiHD::SendAnswered(SocialPlayer* pPlayer)
{
	if ( NULL == pPlayer )
	{
		return;
	}

	NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == Packet)
	{
		return;
	}
	Packet->writeInt32( pPlayer->getuid() );
	Packet->writeInt32( pPlayer->getsid() );
	Packet->writeInt32( pPlayer->getGateIndex() );
	Packet->writeInt32( m_HdId );
	Packet->writeInt32( ATI_DA_TI_HUO_DONG );
	Packet->setType(PACK_DISPATCH);
	Packet->setProc(IM_SOCIAL_GAME_ALREADY);
	Packet->setSize(Packet->getWOffset());
	SOCIAL_SERVICE.sendPacket(Packet);
}

int32_t CSocialDaTiHD::GetNowSeconds()
{
	tm tmNow = DayTime::localnow();
	int32_t NowSeconds = tmNow.tm_hour*60*60 + tmNow.tm_min*60 + tmNow.tm_sec;
	return NowSeconds;
}

int32_t CSocialDaTiHD::GetPoints( int32_t & DiffSeconds )
{
	int32_t NowSeconds = GetNowSeconds();
	DiffSeconds = NowSeconds - m_QuestionsStartSeconds;
	if ( DiffSeconds <= 5 )
	{
		return 100;
	}
	else if ( DiffSeconds <= 10 )
	{
		return 80;
	}
	else if ( DiffSeconds <= 15 )
	{
		return 60;
	}
	else if ( DiffSeconds <= 20 )
	{
		return 40;
	}
	else if ( DiffSeconds <= 25 )
	{
		return LOWEST_POINTS;
	}
	return 0;
}

int32_t CSocialDaTiHD::SendLogInDaTiInfo( SocialPlayer* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return ERR_INVALID_DATA;
	}
	if ( GetHDState() == AS_READY )
	{
		SendCharReadyStart( pPlayer );
	}
	else if( GetHDState() == AS_RUNNING )
	{
		SendQuestionsToClient( pPlayer );
		SendRankInfo( pPlayer );
		SendCharRankInfo(pPlayer);
	}
	return ERR_OK;
}

void CSocialDaTiHD::SendDaTiId( SocialPlayer* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(m_HdId);
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_SEND_DA_TI_HUO_DONG_ID);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet );
}

void CSocialDaTiHD::SendDaTiHDEndToGs()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	int32_t Index = 1;
	packet->writeInt32(1);							//发到1线
	int32_t nSize = m_DaTiInfo.size();
	packet->writeInt32( nSize );
	DaTiInofVct::iterator it = m_DaTiInfo.begin();
	for ( ; it  != m_DaTiInfo.end(); ++it )
	{
		packet->writeInt64(it->m_CharID);
		packet->writeUTF8( it->m_Name );
		packet->writeInt32(Index);
		Index++;
	} 
	packet->setType(PACK_DISPATCH);
	packet->setProc(IM_SOCIAL_SINGLE_GAME_DA_TI_RANK);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacket( packet );
}

void CSocialDaTiHD::SendRankInfo( SocialPlayer* pPlayer )
{

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	PickRankInfo( packet );
	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_SEND_DA_TI_RANK);
	packet->setSize(packet->getWOffset());
	if ( pPlayer == NULL )
	{
		SOCIAL_SERVICE.worldBroadcast( packet );
	}
	else
	{	
		SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet );
	}
}

void CSocialDaTiHD::SendCharRankInfo( SocialPlayer* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	int32_t CharRank = 0;
	bool IsInDaTiInfo = false;
	DaTiInofVct::iterator it = m_DaTiInfo.begin();
	for ( ; it != m_DaTiInfo.end(); ++it )
	{
		CharRank++;
		if ( it->m_CharID == pPlayer->getCid() )
		{
			IsInDaTiInfo = true;
			NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
			if (NULL == packet)
			{
				return;
			}
			packet->writeInt32( CharRank );
			packet->writeInt32( it->m_Points );
			packet->writeInt32( it->m_CostTime );
			packet->setType(PACK_DISPATCH);
			packet->setProc(SM_SEND_CHAR_DA_TI_INFO);
			packet->setSize(packet->getWOffset());
			SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet );
			break;
		}
	}

	if ( !IsInDaTiInfo )
	{
		NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
		if (NULL == packet)
		{
			return;
		}
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
		packet->setType(PACK_DISPATCH);
		packet->setProc(SM_SEND_CHAR_DA_TI_INFO);
		packet->setSize(packet->getWOffset());
		SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet );
	}
}

void CSocialDaTiHD::PickRankInfo( NetPacket *packet )
{
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( GetHDState() );
	int32_t SendCount = 0;;
	int32_t OldOffset = packet->getWOffset();
	packet->writeInt8( SendCount );
	DaTiInofVct::iterator it = m_DaTiInfo.begin();
	for ( ; it != m_DaTiInfo.end(); ++it )
	{
		SendCount++;
		packet->writeInt32( SendCount );
		packet->writeInt64( it->m_CharID );
		packet->writeUTF8( it->m_Name );
		packet->writeInt32( it->m_Points );
		packet->writeInt32( it->m_CostTime );
		if ( SendCount == SEND_RANK_MAX_COUNT )
		{
			break;
		}
	}
	int32_t NewOffset = packet->getWOffset();
	packet->setWOffset( OldOffset );
	packet->writeInt8( SendCount );
	packet->setWOffset( NewOffset );
}

void CSocialDaTiHD::SetHDState( int8_t State )
{
	m_DaTiState = State;
}

int8_t CSocialDaTiHD::GetHDState()
{
	return m_DaTiState;
}
