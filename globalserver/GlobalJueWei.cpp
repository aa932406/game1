#include "GlobalJueWei.h"
#include "PlayerManager.h"
#include "SocialService.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace Answer;
CGlobalJueWei::CGlobalJueWei()
{
	m_DonateVector.clear();
}

CGlobalJueWei::~CGlobalJueWei()
{

}

void CGlobalJueWei::Init()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.CharId, a.DonateMoney, b.name, b.sex FROM `mem_chr_jue_wei` AS a LEFT JOIN mem_character AS b ON b.cid = a.CharId order by a.DonateMoney desc limit 50" );
	MySqlQuery result = db.query(szSQL);
	while (!result.eof())
	{
		CJueWeiInfo stu;
		stu.m_Charid		= result.getInt64Value("CharId");
		stu.m_CharName		= result.getStringValue("name");
		stu.m_Sex			= result.getIntValue("sex");
		stu.m_DonateMoney	= result.getInt64Value("DonateMoney");
		if ( stu.m_DonateMoney >= JUE_WEI_RANK_MIN_DONATE )
		{
			m_DonateVector.push_back( stu );
		}
		
		result.nextRow();
	}
	RefreshRank();
}

int32_t CGlobalJueWei::OnUpdateDonateMoney( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return ERR_SYETEM_ERR;
	}

	CJueWeiInfo stu;
	stu.m_Charid		= packet->readInt64();
	stu.m_CharName		= packet->readUTF8(true);
	stu.m_Sex			= packet->readInt8();
	stu.m_DonateMoney	= packet->readInt64();
	if ( stu.m_DonateMoney < JUE_WEI_RANK_MIN_DONATE )
	{
		SendRankToGs( stu.m_Charid, 0 );
		return ERR_OK;
	}

	JueWeiInfoVector::iterator it = m_DonateVector.begin();
	for ( ; it != m_DonateVector.end(); ++it )
	{
		if ( it->m_Charid	== stu.m_Charid )
		{
			it->m_DonateMoney = stu.m_DonateMoney;
			RefreshRank();
			SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( stu.m_Charid );
			if ( NULL != pSocialPlayer )
			{
				SendDonateRank( pSocialPlayer );
			}
			return ERR_OK;
		}
	}
	if (  m_DonateVector.size() < JUE_WEI_RANK_MAX_COUNT )
	{
		m_DonateVector.push_back( stu );
		RefreshRank();
		SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( stu.m_Charid );
		if ( NULL != pSocialPlayer )
		{
			SendDonateRank( pSocialPlayer );
		}
	}
	else
	{
		if ( m_DonateVector[JUE_WEI_RANK_MAX_COUNT-1].m_DonateMoney >= stu.m_DonateMoney )
		{
			SendRankToGs( stu.m_Charid, 0 );
			return ERR_OK;
		}
		else
		{
			SendRankToGs( m_DonateVector[JUE_WEI_RANK_MAX_COUNT-1].m_Charid , 0 );
			m_DonateVector[JUE_WEI_RANK_MAX_COUNT-1] = stu;
			RefreshRank();
			SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( stu.m_Charid );
			if ( NULL != pSocialPlayer )
			{
				SendDonateRank( pSocialPlayer );
			}
			return ERR_OK;
		}
	}
	return ERR_OK;
}

void CGlobalJueWei::RefreshRank()
{
	SortVector( m_DonateVector );
	JueWeiInfoVector::iterator it = m_DonateVector.begin();
	int32_t Index = 1;
	for ( ; it != m_DonateVector.end(); ++it )
	{
		if ( it->m_Rank != Index )
		{
			it->m_Rank = Index;
			SendRankToGs( it->m_Charid, Index );
		}
		Index++;
	}
}

void CGlobalJueWei::SortVector(std::vector<CJueWeiInfo>& RankVct)
{
	std::sort( RankVct.begin(), RankVct.end(), std::greater<CJueWeiInfo>() );
}

int32_t CGlobalJueWei::SendRankToGs( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return ERR_SYETEM_ERR;
	}
	CharId_t CharId = packet->readInt64();
	int32_t  Rank	= 0;
	JueWeiInfoVector::iterator it = m_DonateVector.begin();
	for ( ; it != m_DonateVector.end(); ++it )
	{
		if ( CharId == it->m_Charid )
		{
			Rank = it->m_Rank;
		}
	}
	SendRankToGs( CharId, Rank, true );
	return ERR_OK;
}

void CGlobalJueWei::SendRankToGs( CharId_t CharID, int32_t Rank, bool IsLogin )
{
	SocialPlayer*  pSocialPlayer = PLAYER_MANAGER.GetPlayerByCid( CharID );
	if ( NULL != pSocialPlayer )
	{
		NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
		if (NULL == Packet)
		{
			return;
		}
		Packet->writeInt32( pSocialPlayer->getuid() );
		Packet->writeInt32( pSocialPlayer->getsid() );
		Packet->writeInt32( pSocialPlayer->getGateIndex() );
		Packet->writeInt32( Rank );
		Packet->writeInt8( IsLogin ? 1 : 0 );
		Packet->setType(PACK_DISPATCH);
		Packet->setProc(IM_SOCIAL_GAME_SEND_JUE_WEI_RANK);
		Packet->setSize(Packet->getWOffset());
		SOCIAL_SERVICE.sendPacket(Packet);
	}
}

int32_t CGlobalJueWei::SendDonateRank( SocialPlayer* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nSize = 0;
	int32_t Offset = packet->getWOffset();
	packet->writeInt32( nSize );
	JueWeiInfoVector::iterator it = m_DonateVector.begin();
	for ( ; it != m_DonateVector.end(); ++it )
	{
		packet->writeInt64( it->m_Charid );
		packet->writeInt32( it->m_Rank );
		packet->writeInt64( it->m_DonateMoney );
		packet->writeUTF8( it->m_CharName );
		packet->writeInt8( it->m_Sex );
		nSize++;
		if ( nSize >= JUE_WEI_RANK_MAX_COUNT )
		{
			break;
		}
	}
	uint32_t endOffSet = packet->getWOffset();
	packet->setWOffset( Offset );
	packet->writeInt32( nSize );
	packet->setWOffset( endOffSet );

	packet->setType(PACK_DISPATCH);
	packet->setProc(SM_SEND_JUE_TOTAL_RANK);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);
	return ERR_OK;
}