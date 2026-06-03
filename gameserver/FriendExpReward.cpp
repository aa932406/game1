#include "stdafx.h"
#include "FriendExpReward.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
CFriendExpReward::CFriendExpReward()
{
	OnCleanUp();
}

CFriendExpReward:: ~CFriendExpReward()
{

}

void CFriendExpReward::OnCleanUp()
{
	m_RewardInfo.clear();
}

void CFriendExpReward::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_RewardInfo	=  dbData.m_FriendExpReward.RewardInfo;
}

void CFriendExpReward::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_FriendExpReward.RewardInfo = m_RewardInfo;
}

void CFriendExpReward::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_FRIEND_REWARD_INFO );
	procList.push_back( CM_ASK_GET_FRIEND_REWARD );
	procList.push_back( IM_SOCIAL_GAME_UPDATE_FRIEND_LEVEL_UP );
}

int32_t CFriendExpReward::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}
	switch(nProcId)
	{
	case CM_ASK_FRIEND_REWARD_INFO:
		{
			return OnAskRewardInfo( inPacket );
		}
	case CM_ASK_GET_FRIEND_REWARD:
		{
			return OnAskGetReward( inPacket );
		}
	case IM_SOCIAL_GAME_UPDATE_FRIEND_LEVEL_UP:
		{
			return OnUpdateRewardInfo( inPacket );
		}
	default:
		break;
	}
	return ERR_OK;
}


int32_t CFriendExpReward::OnAskRewardInfo( Answer::NetPacket* pData )
{
	if ( NULL == m_pPlayer || NULL == pData )
	{
		return ERR_SYETEM_ERR;
	}
	SendRewardInfo();
	return ERR_OK;
}

int32_t	CFriendExpReward::OnAskGetReward( Answer::NetPacket* pData )
{
	if ( NULL == m_pPlayer || NULL == pData )
	{
		return ERR_SYETEM_ERR;
	}
	int64_t	AddExp = 0;
	FriendExpMap::iterator it = m_RewardInfo.begin();
	for ( ; it != m_RewardInfo.end(); ++it )
	{
		AddExp += it->second.GetExp;
	}
	if ( AddExp <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	m_pPlayer->addExp( AddExp );
	m_RewardInfo.clear();
	GAME_SERVICE.replySuccess(m_pPlayer->getGateIndex(), pData->getProc() );
	return ERR_OK;
}
	
int32_t CFriendExpReward::OnUpdateRewardInfo( Answer::NetPacket* pData )
{
	if ( NULL == m_pPlayer || NULL == pData )
	{
		return ERR_SYETEM_ERR;
	}
	CharId_t FriendId	 = pData->readInt64();
	int32_t OldLevel     = pData->readInt32();
	int32_t Level		 = pData->readInt32();
	std::string	Name	 = pData->readUTF8(true);

	int32_t GetExp = 0;
	for ( int32_t i = OldLevel + 1; i <= Level; i++)
	{
		int32_t ExpTmp = CFG_DATA.GetFriendExpByLevel( i );
		if ( ExpTmp <= 0 )
		{
			continue;
		}
		GetExp += ExpTmp;
	}
	FriendExpMap::iterator it =	m_RewardInfo.find( FriendId );
	if ( it != m_RewardInfo.end() )
	{
		it->second.GetExp += GetExp;
		it->second.Level   = Level;
	}
	else
	{
		ExpReward Reward;
		Reward.FriendId = FriendId;
		Reward.GetExp	= GetExp;
		Reward.Name		= Name;
		Reward.Level	= Level;
		m_RewardInfo[FriendId] = Reward;
	}
	SendRewardInfo();
	return ERR_OK;
}

void CFriendExpReward::SendRewardInfo()
{
	if(m_pPlayer == NULL)
	{
		return ;
	}
	Answer::NetPacket* pNetData = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_FRIEND_REWARD);
	if (pNetData != NULL)
	{
		int32_t nSize = m_RewardInfo.size();
		pNetData->writeInt32( nSize );
		FriendExpMap::iterator it = m_RewardInfo.begin();
		for ( ; it != m_RewardInfo.end(); ++it )
		{
			pNetData->writeInt64( it->second.FriendId );
			pNetData->writeInt32( it->second.GetExp );
			pNetData->writeInt32( it->second.Level );
			pNetData->writeUTF8( it->second.Name );
		}
		pNetData->setSize(pNetData->getWOffset());
		GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), pNetData);
	}
}
