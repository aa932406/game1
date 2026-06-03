#include "stdafx.h"

#include "Logger.h"
#include "SocialPlayer.h"
#include "SocialService.h"
#include "PlayerManager.h"
#include "PetRank.h"
#include "PetManager.h"
#include <string>
#include "TeamManager.h"
#include "Family.h"
#include "FamilyManager.h"
#include "RankManager.h"
#include "AuctionManager.h"
#include "GlobalJueWei.h"
#include "SocialDaTiHD.h"
#include "ZSZZDungeon.h"
#include "GlobalRecord.h"
#include "HallOfFame.h"

using namespace Answer;
using namespace std;

enum ERR_TEAM
{
	ERR_TEAM_NOT_FIND						= 1,
	ERR_TEAM_FULL							= 2,
	ERR_TEAM_REFUCE							= 3,
	ERR_FAMILY_APPLYER_NOT_FIND				= 4,		// 找不到申请信息
	ERR_FAMILY_APPLYER_ALREADY_IN_FAMILY	= 5,		// 对方已经有帮派了
	ERR_AUCTION_ITEM_NOT_FIND				= 6,		// 拍卖找不到道具
	ERR_TARGET_SET_NOT_INVITE				= 7,		// 对方设置了不能邀请入队
	ERR_IS_IN_TEAM							= 8,		// 对方已经有队伍
};

SocialPlayer::SocialPlayer()
{
	reset();
	m_Friend.Init(this);
}

SocialPlayer::~SocialPlayer()
{

}

void SocialPlayer::init( int32_t cgindex, CharId_t cid, int32_t uid, int32_t sid, PlayerInfo* pInfo )
{
	reset();

	m_cgindex = cgindex;
	m_cid = cid;
	m_uid = uid;
	m_sid = sid;
	m_pInfo = pInfo;
	m_activityState = 0;
	m_limitShopBuying = 0;
	m_LeaveFamilyTime	= 0;
	loadFamilyInfo();
	//loadApplyFamilyInfo();
	//sendBlessInitInfo();
	//sendFamilyApplyNote();	
	m_Friend.LoadFriend();
	//SOCIAL_SERVICE.sendLimitShop(m_cgindex);
	SOCIAL_DA_TI_HD.SendLogInDaTiInfo( this );
	Family*	Family = FAMILY_MANAGER.GetFamily( m_pInfo->nFamilyId );
	if ( NULL != Family )
	{
		Family->SendPlayerPetInfo( *this );
		Family->SendFamilyTaskCount( this );
	}
	pInfo->nLastLogoutTime = 0;

	HALL_OF_FAME.SendIconState( this );
}



void SocialPlayer::reset()
{
	m_cgindex = 0;
	m_cid = 0;
	m_uid = 0;
	//m_kingdom = KI_NEUTRAL;
	//m_level = 0;
	//m_name = "";
	//m_family_id = 0;
	//m_family_pos = 0;
	m_get_exchange_code = 0;
	//m_family_apply_count = 0;
	m_last_auction_tick = 0;
	//m_last_change_name_tick = 0;
	//m_vip=VT_NONE;
	//m_job=0;
	//m_sex = 0;
	//m_kingdom_contribute =0;
//	m_zhenLongZhiQi = 0;
	//m_family_contribute = 0;
	//m_applyFamily.clear();

	//m_gettingAwardZhiyuanqianxian = 0;

	m_pInfo = NULL;
	m_pTeam = NULL;
	m_pTeamDungeon = NULL;
	m_bTeamDungeonReady = false;
	m_lstInvite.clear();
	m_bAutoApply	= true;
	m_bAutoInvite	= true;
	m_bCanInvite	= true;
	m_bCanAddFriend = true;

	m_Friend.CleanUp();

	//m_bIsLearnedXP	= false;
	m_bJoinWithXP	= false;
	m_nXP			= 0;	
	m_nXPState		= 0;
	m_nXPAddExp		= 0;

	m_bStall		= false;
	//bzero( &m_familyInfo, sizeof( m_familyInfo ) );
}

int32_t SocialPlayer::handleNetPacket(Answer::NetPacket *inPacket)
{
	if (inPacket == NULL)
	{
		return ERR_INVALID_DATA;
	}
	int16_t nXY=inPacket->getProc();
	switch (nXY)
	{
		//case CM_QUERY_ACTIVITY_INFO: return onQueryActivityInfo(inPacket);
        
		//case CM_RANK_REQUEST_INFO: return onRankRequestInfo(inPacket);
		//case CM_QUERY_REAL_TIME_RANK: return onQueryRealTimeRank(inPacket);
		case CM_USE_EXCHANGE_CODE: return onUseExchangeCode(inPacket);
		case CM_SOCIAL_PUBLIC_CHAT: return onSocialPublicChat(inPacket);
		case CM_SOCIAL_PRIVATE_CHAT: return onSocialPrivateChat(inPacket);
		case CM_CHANGE_NAME: return onChangeName(inPacket);
		//case CM_KILLER_RANK_QUERY:return onQueryKillerRank(inPacket);
		//case CM_QUERY_GAMBLE_RECORD:return onQueryGambleRecord(inPacket);

		// 组队系统
		case CM_CREATE_TEAM:						return onCreateTeam( inPacket );
		case CM_INVITE_INTO_TEAM:					return onInviteIntoTeam( inPacket );
		case CM_SET_TEAM_LEADER:					return onSetTeamLeader( inPacket );
		case CM_KICKOUT_TEAM_MEMBER:				return onKickOutTeamMember( inPacket );
		case CM_LEAVE_TEAM:							return onLeaveTeam( inPacket );
		case CM_APPLY_INTO_TEAM:					return onApplyIntoTeam( inPacket );
		case CM_REPLY_TEAM_INVITE:					return onReplyTeamInvite( inPacket );
		case CM_REPLY_TEAM_APPLY:					return onReplyTeamApply( inPacket );
		case CM_TEAM_DESTROY_TEAM:					return onTeamDestroy( inPacket );
		case IM_GAME_SOCIAL_SET_TEAM_AUTO_OPERATE:	return onSetTeamAutoOperate(inPacket);
		case IM_GAME_SOCIAL_LEAVE_TEAM:				return onLeaveTeam( inPacket );

		// XP功能
		case IM_GAME_SOCIAL_ADD_XP:					return onGameAddXP( inPacket );
		case IM_GAME_SOCIAL_START_XP:				return onGameStartXP( inPacket );
		case IM_GAME_SOCIAL_END_XP:					return onGameEndXP(inPacket);
		case IM_GAME_SOCIAL_BREAK_XP:				return onGameBreakXP( inPacket );
		case IM_GAME_SOCIAL_RESET_XP:				return OnDieResetXp( inPacket );

		// 排行榜
		case CM_ASK_PET_RANK_INFO:					return onAskPetRankInfo( inPacket );
		case CM_ASK_PET_RANK_LIST:					return onAskPetRankList( inPacket );
		case CM_ASK_GAME_RANK:						return onAskGameRank( inPacket );

		// 帮派
		case CM_FAMILY_REQUEST_LIST:				return onFamilyRequestList(inPacket);
		case CM_FAMILY_REQUEST_INFO:				return onFamilyRequestInfo(inPacket);
		case CM_FAMILY_CREATE:						return onFamilyCreate(inPacket);
		case CM_FAMILY_EDIT_NOTICE:					return onFamilyChangeNotice(inPacket);
		case CM_FAMILY_REQUEST_MEMBER_LIST:			return onFamilyRequestMemberList(inPacket);
		case CM_FAMILY_REQUEST_TOTOM_LIST:			return onFamilyRequestTotomList(inPacket);
		case CM_FAMILY_REQUEST_APPLIERS:			return onFamilyRequestAppliers(inPacket);
		case CM_FAMILY_REQUEST_REGIST_PETS:			return onFamilyRequestRegistPets(inPacket);
		case CM_FAMILY_REQUEST_PLAYER_PETS:			return onFamilyRequestPlayerPets(inPacket);
		case CM_FAMILY_REQUEST_LOGS:				return onFamilyRequestLogs(inPacket);
		//case CM_FAMILY_QUERY_SELF_INFO:				return onQuerySelfFamilyInfo(inPacket);
		//case CM_FAMILY_UPGRADE_LEVEL:				return onUpgradeFamilyLevel(inPacket);
		//case CM_FAMILY_REQUEST_NOTICE:				return onQueryFamilyNotice(inPacket);
		case CM_FAMILY_APPLY:						return onFamilyApply(inPacket);
		case CM_FAMILY_AUTO_AGREE:					return onSetAutoAgree( inPacket );
		//case CM_FAMILY_INVITE:						return onFamilyInvite(inPacket);
		//case CM_FAMILY_APPOINT_INVITE:				return onFamilyAppointInvite(inPacket);
		case CM_FAMILY_APPROVE:						return onFamilyApprove(inPacket);
		case CM_FAMILY_APPOINT:						return onFamilyAppoint(inPacket);
		//case CM_FAMILY_LEADER_DOWN:					return onFamilyLeaderDown(inPacket);
		case CM_FAMILY_KICK:						return onFamilyKick(inPacket);
		case CM_FAMILY_LEAVE:						return onFamilyLeave(inPacket);
		//case CM_FAMILY_REQUEST_EVERY_REWARD:		return onFamilyLeave(inPacket);
		case CM_FAMILY_CANCLE_APPLY:				return onFamilyCancelApply(inPacket);
		case CM_FAMILY_ACTIVE_TOTOM:				return onFamilyActiveTotom(inPacket);
		case CM_FAMILY_DESTROY:						return onFamilyDestroy(inPacket);
		case CM_FAMILY_OPEN_TOTOM:					return onFamilyOpenTotom( inPacket );
		case CM_FAMILY_TASK_COUNT:					return onFamilyRequestTaskCount(inPacket);

		case IM_GAME_SOCIAL_CREATE_FAMILY:			return onGameCreateFamily(inPacket);
		case IM_GAME_SOCIAL_ADD_FAMILY_CONTRIBUTE:	return onGameAddFamilyContribute(inPacket);
		case IM_GAME_SOCIAL_UPDATE_PET_CONTRIBUTE:	return onGameUpdatePetContribute(inPacket);
		case IM_GAME_SOCIAL_FAMILY_REGIST_PET:		return onGameFamilyRegistPet(inPacket);
		case IM_GAME_SOCIAL_FAMILY_UNREGIST_PET:	return onGameFamilyUnRegistPet(inPacket);
		case IM_GAME_SOCIAL_FAMILY_TASK_COUTN:		return onGameFamilyAddTaskCount(inPacket);
		case IM_GAME_SOCIAL_FAMILY_ADD_CONTRIBUTION:return onGameFamilyAddContribute( inPacket );
		// 组队副本
		case CM_TEAM_DUNGEON_REQUEST_LIST:			return onTeamDungonRequestList( inPacket );
		case CM_TEAM_DUNGEON_LEAVE:					return onTeamDungeonLeave( inPacket );
		case CM_TEAM_DUNGEON_KICK:					return onTeamDungeonKick( inPacket );
		case CM_TEAM_DUNGEON_READY:					return onTeamDungeonReady( inPacket );
		case CM_TEAM_DUNGEON_SET_AUTO_START:		return onTeamDungeonSetAutoStart( inPacket );

		case IM_GAME_SOCIAL_TEAM_DUNGEON_CREATE:	return onGameTeamDungonCreate( inPacket );
		case IM_GAME_SOCIAL_TEAM_DUNGEON_JOIN:		return onGameTeamDungonJoin( inPacket );
		case IM_GAME_SOCIAL_TEAM_DUNGEON_START:		return onGameTeamDungeonStart( inPacket );
		case IM_GAME_SOCIAL_TEAM_DUNGEON_LEAVE:		return onGameTeamDungeonLeave( inPacket );

		// 崇拜
		case CM_REQUEST_WORSHIP_INFO:				return onRequestWorshipInfo( inPacket );
		case CM_WORSHIP:							return onWorship( inPacket );

		case IM_GAME_SOCIAL_WORSHIP:				return onGameWorship( inPacket );

			// 活动
		case IM_GAME_SOCIAL_NOTIFY_FAMILYWAR_INFO:			return onGameActivityNotifyFamilyWarInfo( inPacket );
		case IM_GAME_SOCIAL_FAMILYWAR_ADD_PILLAR_MONEY:		return onGameActivityFamilyWarAddPillarMoney( inPacket );

		// 拍卖
		case CM_AUCTION_SELL:						return onAuctionSell( inPacket );
		case CM_AUCTION_BUY:						return onAuctionBuy( inPacket );
		case CM_AUCTION_CANCEL:						return onAuctionCancel( inPacket );
		case CM_AUCTION_REQUEST_ITEM_LIST:			return onAuctionItemList( inPacket );
		case CM_AUCTION_REQUEST_SELF_ITEMS:			return onAuctionSelfItems( inPacket );
		case CM_AUCTION_REQUEST_RECORD:				return onAuctionRecords( inPacket );

		case IM_GAME_SOCIAL_AUCTION_SELL:			return onGameAuctionSell( inPacket );
		case IM_GAME_SOCIAL_AUCTION_BUY:			return onGameAuctionBuy( inPacket );
		case IM_GAME_SOCIAL_STALL:					return onGameStall( inPacket );

		// 名人堂
		case CM_HALL_OF_FAME_RANK:							return onHallOfFameRankInfo( inPacket );
		case CM_HALL_OF_FAME_GET_REWARD:					return onHallOfFameGetReward( inPacket );

		case IM_GAME_SOCIAL_HALL_OF_FAME_FIGHT:				return onGameHallOfFameFight( inPacket );
		case IM_GAME_SOCIAL_HALL_OF_FAME_REQUEST_INFO:		return onGameHallOfFameRequestInfo( inPacket );
		case IM_GAME_SOCIAL_HALL_OF_FAME_REWARD_RESULT:		return onGameHallOfFameRewardResult( inPacket );

		//好友系统
		case CM_ASK_FRIEND_LIST:		return	m_Friend.OnAskFriendList( inPacket );	
		case CM_ASK_ADD_FRIEND:			return	m_Friend.OnAskAddFriend( inPacket );
		case CM_REPLAY_ADD_FRIEND:		return	m_Friend.OnReplyAddFriend( inPacket );
		case CM_DELETE_FRIEND:			return	m_Friend.OnDeleteFriend( inPacket );
		case CM_SIFT_FRIEND:			return	m_Friend.OnSiftFriend( inPacket );
		case CM_GET_PLAYER_INFO:		return  m_Friend.OnGetPlayerInfo( inPacket );
		case IM_GAME_SOCIAL_ADD_ENEMY:  return  m_Friend.OnBeKilled( inPacket );
		//爵位
		case CM_ASK_JUE_WEI_RANK:		return GLOBAL_JUE_WEI.SendDonateRank( this );
		case IM_GAME_SOCIAL_JUE_WEI_DONATE_MONEY: return GLOBAL_JUE_WEI.OnUpdateDonateMoney( inPacket );
		case IM_GAME_SOCIAL_ASK_JUE_WEI_RANK:	  return GLOBAL_JUE_WEI.SendRankToGs( inPacket );
		// 答题
		case CM_ANSWER_QUESTIONS:	     return SOCIAL_DA_TI_HD.OnReqAnswerQuestion( this, inPacket );
		case CM_ASK_DA_TI_INFO:
			{
					SOCIAL_DA_TI_HD.SendDaTiId( this );
					SOCIAL_DA_TI_HD.SendLogInDaTiInfo( this );
			}
											 
		//商城购买限制物品
		case IM_GAME_SOCIAL_ASK_LIMIT_SHOP_INFO:	return OnAskItemLimitInfo( inPacket );
		case IM_GAME_SOCIAL_BUY_LIMIT_SHOP_ITEM:	return OnBuyLimitItem( inPacket );
		case IM_GAME_SOCIAL_BUY_LIMIT_SHOP_SUCCEED:	return OnReceiveBuySucceed( inPacket );
		// 诸神之战副本
		case CM_ASK_UP_TOWER_DUNGEON_RANK:	 ZSZZ_DUNGEON_RANK.SendCharInfo( this ); break;
		//抽奖
		case IM_GAME_SOCIAL_ADD_CHOU_JIANG_RECORD:		GLOBAL_RECORD.OnRecvChouJiangRecord( inPacket );break;
		case IM_GAME_SOCIAL_CLEAN_GLOBAL_POINT:			GLOBAL_RECORD.OnRecvCleanGlobalLuckPoint( inPacket ); break;
		case IM_GAME_SOCIAL_CHECK_GLOBAL_POINT:			GLOBAL_RECORD.OnRecvCheckGlobalLuckPoint( this,inPacket );break;
		case IM_GAME_SOCIAL_ASK_CHOU_JIANG_RECORD:		GLOBAL_RECORD.OnRecvAskChouJiangRecord( this, inPacket ); break;
		case IM_GAME_SOCIAL_ADD_TOU_ZI_RECORD:			GLOBAL_RECORD.OnRecvTouZiRecord( inPacket );break;
		case CM_ASK_ONE_TOU_ZI_RECORD:					GLOBAL_RECORD.SendOneTouZiRecord( this );break;
		case CM_ASK_ALL_TOU_ZI_RECORD:					GLOBAL_RECORD.SendAllTouZiRecord(this);break;	

		//.........................separator.........................
		case IM_GAME_SOCIAL_UPDATE_ACTIVITY_STATE:return onGameUpdateActivityState(inPacket);
		//case IM_GAME_SOCIAL_ADD_CONTRIBUTION: return onGameAddContribution(inPacket);
		case IM_GAME_SOCIAL_USE_EXCHANGE_CODE: return onGameUseExchangeCode(inPacket);
		case IM_GAME_SOCIAL_CHANGE_NAME: return onGameChangeName(inPacket);
		//case IM_GAME_SOCIAL_CHANGE_FAMILY_NAME: return onGameChangeFamilyName(inPacket);
		//case IM_GAME_SOCIAL_BREAK_FAMILY:return onGameBreakFamily(inPacket);
		//case IM_GAME_SOCIAL_UPDATE_KINGDOM_CONTRIBUTE:return onGameUpdateKingdomContribute(inPacket);
		//case IM_GAME_SOCIAL_UPDATE_FAMILY_MONEY:return onGameUpdateFamilyMoney(inPacket);

		case IM_GAME_SOCIAL_QUERY_PLAYER_INFO:	return onGameQueryPlayerInfo(inPacket);
		default: return ERR_INVALID_DATA;
	}
	return ERR_INVALID_DATA;
}

////选择国家 /叛国
//int32_t SocialPlayer::onSelectKingdom(Answer::NetPacket *inPacket)
//{
//	if(inPacket ==NULL) return ERR_INVALID_DATA;
//	int8_t action =inPacket->readInt8();
//	if(action !=0 && action !=1) return ERR_INVALID_DATA;
//	int8_t kingdomRecommend=KI_NEUTRAL;
//	//选择国家
//	if(action ==0)
//	{
//		if(getKingdom() !=KI_NEUTRAL) return ERR_INVALID_DATA;
//		int32_t tid=inPacket->readInt32();
//		if (tid !=10100) return ERR_INVALID_DATA;
//		kingdomRecommend = (RANDOM.generate(1,2) == (int8_t)KI_SHU?(int8_t)KI_SHU:(int8_t)KI_WU);
//	}
//	//叛国
//	if (action ==1)
//	{
//		kingdomRecommend=KI_WU;
//		if(m_kingdom ==KI_WU) kingdomRecommend=KI_SHU;
//	}
//	NetPacket *packet =SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return ERR_INVALID_DATA;
//	}
//	packet->writeInt8(action);
//	packet->writeInt8(kingdomRecommend);
//	packet->setType(PACK_DISPATCH);
//	packet->setProc(SM_KINGDOM_CREAT);
//	packet->setSize(packet->getWOffset());
//	SOCIAL_SERVICE.sendPacketTo(m_cgindex, packet);
//
//	return ERR_OK;
//}

CharId_t SocialPlayer::getCid() const
{
	return m_cid;
}

int32_t SocialPlayer::getuid() const
{
	return m_uid;
}

int32_t SocialPlayer::getsid() const
{
	return m_sid;
}

int16_t SocialPlayer::getGateIndex() const
{
	return m_cgindex;
}


Job_t SocialPlayer::getJob() const
{
	return m_pInfo != NULL ? m_pInfo->nJob : 0; 
}

Sex_t SocialPlayer::getSex() const
{
	return m_pInfo != NULL ? m_pInfo->nSex : 0; 
}

int32_t SocialPlayer::getLevel() const
{
	return m_pInfo != NULL ? m_pInfo->nLevel : 0;
}

std::string SocialPlayer::getName() const
{
	return m_pInfo != NULL ? m_pInfo->strName : "";
}

int8_t SocialPlayer::GetJueWei() const
{
	return m_pInfo != NULL ? m_pInfo->nJueWei : 0;
}

int8_t SocialPlayer::GetVip() const
{
	if ( NULL == m_pInfo )
	{
		return 0;
	}
	return m_pInfo->nVip;
}

int8_t SocialPlayer::GetVipLevel() const
{
	if ( GetVip() > 0 )
	{
		return m_pInfo->nVipLevel;
	}
	return 0;
}

bool SocialPlayer::inActivity() const
{
	return m_activityState == 1;
}

int32_t SocialPlayer::GetBattle() const
{
	return m_pInfo != NULL ? m_pInfo->nBattle : 0; 
}

int32_t SocialPlayer::GetLastLogOutTime() const
{
	return m_pInfo != NULL ? m_pInfo->nLastLogoutTime : 0; 
}

PlayerInfo*	SocialPlayer::GetPlayerInfo()
{
	return m_pInfo;
}

int32_t SocialPlayer::GetCloth() const
{
	return m_pInfo != NULL ? m_pInfo->nCloth : 0; 
}

int32_t SocialPlayer::GetWeapon() const
{
	return m_pInfo != NULL ? m_pInfo->nWeapon : 0; 
}


FamilyId_t SocialPlayer::GetFamilyId() const
{
	return m_pInfo != NULL ? m_pInfo->nFamilyId : 0;
}

int8_t SocialPlayer::GetFamilyPosition() const
{
	return m_pInfo != NULL ? m_pInfo->nFamilyPosition : 0;
}

std::string SocialPlayer::GetFamilyName() const
{
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	return pFamily != NULL ? pFamily->GetName() : "";
}

int32_t SocialPlayer::GetFamilyContribution() const
{
	return m_pInfo != NULL ? m_pInfo->GetFamilyContribution() : 0;
}

int32_t SocialPlayer::GetFamilyApplyCount() const
{
	return m_pInfo != NULL ? m_pInfo->nFamilyApplyCount : 0;
}

//void SocialPlayer::setFamilyId(int32_t value)
//{
//	m_family_id = value;
//}
//
//void SocialPlayer::setFamilyApplyCount(int32_t flag)
//{
//	switch(flag)
//	{
//	case 0:
//		if (m_family_apply_count >0)
//		{
//			m_family_apply_count--;
//		}
//		break;
//	case 1:
//		m_family_apply_count++;
//		break;
//	default:
//		break;
//	}
//}

//void SocialPlayer::setFamilyPos(int32_t value)
//{
//	m_family_pos = value;
//}

//void SocialPlayer::updateFamilyContribue(int32_t addon)
//{
//	if (addon < 0 )
//	{
//		if (m_family_contribute >= std::abs(addon))
//		{
//			m_family_contribute += addon;
//		}
//		else
//		{
//			m_family_contribute = 0;
//		}
//
//		sendGameUpdateFamilyContribute(addon);
//	}
//}
//
//void SocialPlayer::clearFamilyApply()
//{
//	m_applyFamily.clear();
//	m_family_apply_count = 0;
//}

void SocialPlayer::loadFamilyInfo()
{
	MySqlDBGuard db(DBPOOL);

	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_chr_family` WHERE `cid`=%lld", m_cid);

	MySqlQuery result = db.query(szSQL);

	if (!result.eof())
	{
		m_LeaveFamilyTime = result.getIntValue("Leave_family_time");
	}
}

void SocialPlayer::loadApplyFamilyInfo()
{
	//m_applyFamily.clear();
	//SOCIAL_SERVICE.loadFamilyApply(m_applyFamily,m_cid);
}
//
//int32_t SocialPlayer::onQueryActivityInfo(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int8_t activityId = inPacket->readInt8();
//	if (activityId < 0)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	int8_t select = inPacket->readInt8();
//	if (select <= 0  || select > 33)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int8_t kingdom = select % 10;
//	int8_t count = select / 10;
//
//	updateActivityData(activityId, kingdom, count);
//	sendActivityData();
//
//	return ERR_OK; 
//}


//void SocialPlayer::AppendFamilyRegistPetInfo( Answer::NetPacket* packet, int16_t& nCount )
//{
//	if ( NULL == packet )
//	{
//		return;
//	}
//
//	for ( int32_t i = 1; i <= MAX_PET_ID; ++i )
//	{
//		if ( m_familyInfo.m_vRegistPet[i] > 0 )
//		{
//			CSocialPet* pPet = PET_MANAGER.GetPet( m_familyInfo.m_vRegistPet[i] );
//			if ( pPet != NULL )
//			{
//				packet->writeInt32( i );							// BaseId
//				packet->writeInt64( pPet->GetPetId() );				// 宠物Id
//				packet->writeUTF8( pPet->GetPetName() );			// 宠物名称
//				packet->writeInt32( pPet->GetPoints() );			// 宠物评分
//			}
//		}
//	}
//}

int32_t SocialPlayer::onFamilyRequestList(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}

	FAMILY_MANAGER.SendFamilyList( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyRequestInfo(Answer::NetPacket *inPacket)
{
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->SendTotomInfo( *this );			//客户端需要图腾信息先发
	pFamily->SendFamilyInfo( *this );
	//pFamily->SendMemberInfo( *this );
	//pFamily->SendNotice( *this );
	//pFamily->SendPetInfo( *this );
	//pFamily->SendLogInfo( *this );
	return ERR_OK;
}

//int32_t SocialPlayer::onQueryFamilyNotice(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t family_id = inPacket->readInt32();
//	FamilyInfo*pFamilyInfo = SOCIAL_SERVICE.getFamilyInfo(family_id);
//	if (pFamilyInfo == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	sendFamilyNotice(family_id,pFamilyInfo->notice);
//
//	return ERR_OK;
//}

int32_t SocialPlayer::onFamilyChangeNotice( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	std::string notice = inPacket->readUTF8(true);

	if ( StringUtility::utf8Strlen( notice.c_str() ) > MAX_FAMILT_POST )
	{
		return ERR_INVALID_DATA;
	}

	// 职务判定
	int8_t nPosition = GetFamilyPosition(); 
	if ( nPosition != FP_LEADER	&& nPosition != FP_VICE	&& nPosition != FP_HONOR_VICE )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->ChangeNotice( notice );
	return ERR_OK;
}

//int32_t SocialPlayer::onQuerySelfFamilyInfo(Answer::NetPacket *inPacket)
//{
//	sendSelfFamilyInfo();
//
//	return ERR_OK;
//}

//int32_t SocialPlayer::onUpgradeFamilyLevel(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	 if (m_family_pos != FP_LEADER)
//	 {
//		 return ERR_INVALID_DATA;
//	 }
//
//	 FamilyInfo*pFamilyInfo = SOCIAL_SERVICE.getFamilyInfo(m_family_id);
//	 if (pFamilyInfo == NULL)
//	 {
//		 return ERR_INVALID_DATA;
//	 }
//
//	 CfgFamilyLevel*pFamilyLevel = SOCIAL_SERVICE.getCfgFamilyLevel(pFamilyInfo->level);
//	 if (pFamilyLevel == NULL)
//	 {
//		 return ERR_INVALID_DATA;
//	 }
//
//	 if (pFamilyLevel->cost_money > pFamilyInfo->money)
//	 {
//		 return ERR_INVALID_DATA;
//	 }
//
//	 pFamilyInfo->level++;
//	 pFamilyInfo->money -= pFamilyLevel->cost_money;
//
//	 SOCIAL_SERVICE.setFamilyInfo(pFamilyInfo,FII_LEVEL,pFamilyInfo->level);
//	 SOCIAL_SERVICE.setFamilyInfo(pFamilyInfo,FII_MONEY,pFamilyInfo->money);
//
//	 for (FamilyMemberInfoVector::iterator it = pFamilyInfo->members.begin();it != pFamilyInfo->members.end();++it)
//	 {
//		 SocialPlayer*pOtherPlayer = SOCIAL_SERVICE.getPlayerByCid(it->cid);
//		 if (pOtherPlayer != NULL)
//		 {
//			 sendGameSynFamilyLevel(pOtherPlayer->getGateIndex(),pOtherPlayer->getuid(),pOtherPlayer->getsid(),pFamilyInfo->level);
//		 }
//
//		 if (it->cid == m_cid)
//		 {
//			 sendFamilyResource(it->contribute);
//		 }
//	 }
//	 return ERR_OK;
//}

int32_t SocialPlayer::onFamilyRequestMemberList(Answer::NetPacket *inPacket)
{
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->SendMemberInfo( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyRequestTotomList(Answer::NetPacket *inPacket)
{
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->SendTotomInfo( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyRequestAppliers(Answer::NetPacket *inPacket)
{
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->SendApplyInfo( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyRequestRegistPets(Answer::NetPacket *inPacket)
{
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->SendRegistPetInfo( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyRequestPlayerPets(Answer::NetPacket *inPacket)
{
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->SendPlayerPetInfo( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyRequestLogs(Answer::NetPacket *inPacket)
{
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->SendLogInfo( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyCreate( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pInfo->nLevel < FAMILY_OPEN_LEVEL )
	{
		return ERR_INVALID_DATA;
	}

	if ( GetFamilyId() > 0)
	{
		return ERR_INVALID_DATA;
	}

	std::string name = inPacket->readUTF8(true);
	if ( name.empty() || StringUtility::utf8Strlen(name.c_str()) > MAX_NAME_LENGTH )
	{
		return ERR_INVALID_DATA;
	}
	std::string notice = inPacket->readUTF8(true);
	if ( FAMILY_MANAGER.CheckFamilyName( name ) )
	{
		return SOCIAL_SERVICE.replyfailure( m_cgindex, inPacket->getProc(), ERR_NAME_EXIST );
	}
	
	sendGameCreateFamily( name , notice );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyDestroy( Answer::NetPacket *inPacket )
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}

	FamilyId_t nFamilyId = GetFamilyId();
	Family* pFamily = FAMILY_MANAGER.GetFamily( nFamilyId );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( GetFamilyPosition() != FP_LEADER )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->OnDestroy();
	FAMILY_MANAGER.DestroyFamily( nFamilyId );
	return SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc(), nFamilyId );
}

//int32_t SocialPlayer::onFamilyInvite(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//     int32_t  tcid = inPacket->readInt32();
//	 SocialPlayer*player = SOCIAL_SERVICE.getPlayerByCid(tcid);
//	 if (player == NULL || player->getFamilyId() > 0)
//	 {
//		return ERR_INVALID_DATA;
//	 }
//
//	 int32_t tgindex = player->getGateIndex();
//
//	 FamilyInfo*pFamilyInfo =  SOCIAL_SERVICE.getFamilyInfo(getFamilyId());
//	 if(pFamilyInfo == NULL)
//	 {
//		 return ERR_INVALID_DATA;
//	 }
//	 
//	 sendInviteFamily(pFamilyInfo->name,tgindex);
//
//	 return ERR_OK;
//}

//int32_t SocialPlayer::onFamilyAppointInvite(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	   int32_t cid  =  inPacket->readInt32();
//	   if (m_family_pos < FP_VICE_LEADER)
//	   {
//		   return ERR_INVALID_DATA;
//	   }
//
//	   SocialPlayer*player = SOCIAL_SERVICE.getPlayerByCid(cid);
//	   if (player == NULL ||player->getFamilyId() > 0 ||player->getKingdom() != getKingdom())
//	   {
//		   return ERR_INVALID_DATA;
//	   }
//
//	   FamilyInfo*pFamilyinfo = SOCIAL_SERVICE.getFamilyInfo(m_family_id);
//	   if (pFamilyinfo == NULL)
//	   {
//		   return ERR_INVALID_DATA;
//	   }
//
//	   SOCIAL_SERVICE.removeAllFamilyApplier(cid);
//
//	   int32_t result = 0;
//	   approveForFamily(cid, result);
//	   sendFamilyAppliers();
//	   sendFamilyInfo();
//
//	   return ERR_OK;
//
//}

int32_t SocialPlayer::onFamilyOpenTotom( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	int32_t PetBaseId = inPacket->readInt32();
	if ( m_pInfo->nFamilyId <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( m_pInfo->nFamilyId );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}
	
	pFamily->onOpenTotom( this, PetBaseId );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyCancelApply(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	FamilyId_t nFamilyId = inPacket->readInt64();
	if ( m_pInfo->nFamilyId > 0 )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( nFamilyId );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( pFamily->RemoveApply( this->getCid() ) )
	{
		--m_pInfo->nFamilyApplyCount;
		SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc(), nFamilyId );
	}

	return ERR_OK;
}

int32_t SocialPlayer::onFamilyApply(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pInfo->nLevel < FAMILY_OPEN_LEVEL )
	{
		return ERR_INVALID_DATA;
	}
	if ( m_LeaveFamilyTime > DayTime::now() )
	{
		return ERR_INVALID_DATA;
	}
	FamilyId_t nFamilyId = inPacket->readInt64();
	if ( m_pInfo->nFamilyId > 0)
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pInfo->nFamilyApplyCount >= FAMILY_APPLY_COUNT )
	{
		return SOCIAL_SERVICE.replyfailure( m_cgindex, inPacket->getProc(),ERR_APPLY_COUNT_FULL );
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( nFamilyId );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( pFamily->AutoAddMember( this, m_pInfo ) )
	{
		return ERR_OK;
	}
	
	if ( pFamily->OnApply( m_pInfo ) )
	{
		++m_pInfo->nFamilyApplyCount;
		SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc(), nFamilyId );
	}

	return ERR_OK;
}

int32_t SocialPlayer::onSetAutoAgree( Answer::NetPacket* inPacket )
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	int8_t nFlag = inPacket->readInt8();
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( GetPositionLevel( GetFamilyPosition() ) < FPL_VICE )
	{
		return ERR_INVALID_DATA;
	}
	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}
	pFamily->onSetAutoAgree( nFlag );
	SOCIAL_SERVICE.replySuccess ( m_cgindex, inPacket->getProc(), pFamily->IsAuto() ? 1:0  );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyApprove(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( GetPositionLevel( GetFamilyPosition() ) < FPL_VICE )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCharId	= inPacket->readInt64();
	bool bAccept		= inPacket->readInt8() > 0;

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( nCharId > 0 )
	{
		PlayerInfo* pPlayerInfo = PLAYER_MANAGER.GetPlayerInfo( nCharId );
		if ( NULL == pPlayerInfo )
		{
			SOCIAL_SERVICE.replyfailure( m_cgindex, inPacket->getProc(), ERR_FAMILY_APPLYER_NOT_FIND );
			return ERR_INVALID_DATA;
		}
		if ( pPlayerInfo->nFamilyId > 0 )
		{
			SOCIAL_SERVICE.replyfailure( m_cgindex, inPacket->getProc(), ERR_FAMILY_APPLYER_ALREADY_IN_FAMILY );
			return ERR_INVALID_DATA;
		}
		pFamily->OnApplyReply( *this, pPlayerInfo, bAccept );
	}
	else
	{
		pFamily->OnApplyOperator( *this, bAccept );
	}
	//sendFamilyAppliers();
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyAppoint(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	CharId_t nCharId = inPacket->readInt64();
	int8_t nPosition = inPacket->readInt32();

	PlayerInfo* pTarget = PLAYER_MANAGER.GetPlayerInfo( nCharId );
	if( NULL == pTarget )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( pFamily->GetId() != pTarget->nFamilyId )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nCurPositionLevel = GetPositionLevel( GetFamilyPosition() );
	if ( nCurPositionLevel < FPL_VICE )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	nTarPositionLevel = GetPositionLevel( pTarget->nFamilyPosition );
	if ( nCurPositionLevel <= nTarPositionLevel )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nEndPositionLevel = GetPositionLevel( nPosition );
	if ( nCurPositionLevel <= nTarPositionLevel )
	{
		return ERR_INVALID_DATA;
	}

	if ( nPosition == FP_NONE )
	{
		if ( !pFamily->UnSetHonorPosition( *this, pTarget ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	else
	{
		if ( !pFamily->SetHonorPosition( *this, pTarget, nPosition ) )
		{
			return ERR_INVALID_DATA;
		}
	}
	
	return ERR_OK;
}

//int32_t SocialPlayer::onFamilyLeaderDown(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t tcid = inPacket->readInt32();
//	if (m_cid == tcid)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	//if (SOCIAL_SERVICE.checkCivilPosition(getCid(), CPT_SHENJIANG) || SOCIAL_SERVICE.checkCivilPosition(getCid(), CPT_ZHUGONG) || SOCIAL_SERVICE.checkCivilPosition(getCid(), CPT_TAIWEI))
//	//{
//	//	return ERR_INVALID_DATA;
//	//}
//
//	if (inActivity())
//	{
//		return SOCIAL_SERVICE.replyfailure(m_cgindex,inPacket->getProc(),ERR_MAP_ACTIVITY_INPLAY);
//	}
//
//	FamilyInfo*pFamilyInfo = SOCIAL_SERVICE.getFamilyInfo(m_family_id);
//	if (pFamilyInfo == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (pFamilyInfo->leader_cid !=  m_cid)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	SocialPlayer* pOtherPlayer = SOCIAL_SERVICE.getPlayerByCid(tcid);  
//	if (pOtherPlayer != NULL)
//	{
//		if (pOtherPlayer->getFamilyId() != m_family_id)
//		{
//			return ERR_INVALID_DATA;
//		}
//
//		if (pOtherPlayer->getFamilyPos() >= FP_LEADER)
//		{
//			return ERR_INVALID_DATA;
//		}
//
//		if (inActivity())
//		{
//			return SOCIAL_SERVICE.replyfailure(m_cgindex,inPacket->getProc(),ERR_MAP_ACTIVITY_INPLAY);
//		}
//
//		pOtherPlayer->sendGameLeaderDown(FP_LEADER);
//		pOtherPlayer->setFamilyPos(FP_LEADER);
//	}
//
//	sendGameLeaderDown(FP_MEMBER);
//
//	std::string tname = "";
//	PlayerInfo*pOtherPlayerInfo = SOCIAL_SERVICE.getPlayerInfo(tcid);
//	if (pOtherPlayerInfo != NULL)
//	{
//		if (pOtherPlayerInfo->family_id != m_family_id)
//		{
//			return ERR_INVALID_DATA;
//		}
//
//		tname = pOtherPlayerInfo->name;
//		pFamilyInfo->vip = pOtherPlayerInfo->vip;
//	}	
//
//	pFamilyInfo->leader_name = tname;
//	pFamilyInfo->leader_cid = tcid;
//	m_family_pos = FP_MEMBER;
//
//	for (FamilyMemberInfoVector::iterator it = pFamilyInfo->members.begin();it != pFamilyInfo->members.end();++it)
//	{
//		if (it->cid == m_cid)
//		{
//			it->position = FP_MEMBER;
//		}
//		else if (it->cid == tcid)
//		{
//			it->position = FP_LEADER;
//		}
//
//		SocialPlayer* player = SOCIAL_SERVICE.getPlayerByCid(it->cid);
//		if (player != NULL)
//		{
//			sendGameLeaderCid(tcid,player->getuid(),player->getsid(),player->getGateIndex());
//		}
//	}
//
//	{
//		MySqlDBGuard db(DBPOOL);
//		char szSQL[MAX_SQL_LENGTH] = "";
//		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_family` SET  `leader_cid` = %d WHERE `id` = %d",tcid,m_family_id);
//		db.excute(szSQL);
//
//		bzero(szSQL, sizeof(szSQL));
//		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_family` SET  `position` = %d WHERE `cid` = %d",FP_MEMBER,m_cid);
//		db.excute(szSQL);
//
//		bzero(szSQL, sizeof(szSQL));
//		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_chr_family` SET  `position` = %d WHERE `cid` = %d",FP_LEADER,tcid);
//		db.excute(szSQL);
//	}
//
//	sendFamilyInfo();
//	SOCIAL_SERVICE.broadcastFamilyLeaderDown(m_family_id, m_cid, getName(),tcid,tname);
//	return ERR_OK;
//}


int32_t SocialPlayer::onFamilyKick(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCharId = inPacket->readInt64();
	PlayerInfo* pTarget = PLAYER_MANAGER.GetPlayerInfo( nCharId );
	if ( NULL == pTarget )
	{
		return ERR_INVALID_DATA;
	}

	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( pFamily->KickMember( *this, pTarget ) )
	{
		SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc(), nCharId );
	}
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyLeave(Answer::NetPacket *inPacket)
{
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( pFamily->LeaveMember( m_pInfo ) )
	{
		SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc() );
	}
	if ( SOCIAL_SERVICE.GetServerDiffDay() >= 2 )
	{
		m_LeaveFamilyTime = DayTime::now() + 4 * 60 * 60;
		UpdatePlayerLeaveFamily();
	}
	return ERR_OK;
}

int32_t SocialPlayer::getLevelFamilyTime() const
{
	return m_LeaveFamilyTime;
}

void SocialPlayer::UpdatePlayerLeaveFamily()
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1,
		"UPDATE `mem_chr_family` SET `Leave_family_time`=%d WHERE cid =%lld",
		m_LeaveFamilyTime,
		getCid() );
	db.excute(szSQL);
}

int32_t SocialPlayer::onFamilyActiveTotom(Answer::NetPacket *inPacket)
{
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nTotomId	= inPacket->readInt32();
	int8_t	nAddBattle	= inPacket->readInt8();

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( pFamily->ActiveTotom( *this, nTotomId, nAddBattle ) )
	{
		SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc(), nTotomId );
	}
	return ERR_OK;
}

//int32_t SocialPlayer::onRankRequestInfo(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t tid = inPacket->readInt32();
//
//	if (tid <= RT_MIN || tid >= RT_MAX)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	SOCIAL_SERVICE.sendRankPack(m_cgindex, static_cast<RankType>(tid),m_cid);
//
//	return ERR_OK;
//}

//int32_t SocialPlayer::onQueryRealTimeRank(Answer::NetPacket *inPacket)
//{
//	SOCIAL_SERVICE.sendRealTimeRank(m_cgindex);
//	return ERR_OK;
//}

int32_t SocialPlayer::onUseExchangeCode(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	if (m_get_exchange_code != 0)
	{
		return ERR_INVALID_DATA;
	}
	std::string code = inPacket->readUTF8(true);
	
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_exchange_code` WHERE `code` = '%s'", code.c_str());
	MySqlQuery result = db.query(szSQL);

	int32_t item_id = 0;

	if (!result.eof())
	{
		item_id = result.getIntValue("item_id");

		int32_t usedRecord = result.getIntValue("used");
		if (usedRecord > 0)
		{
			return SOCIAL_SERVICE.replyfailure(m_cgindex,inPacket->getProc(),ERR_EXCHANGE_CODE_USED);
		}
		else
		{
			bzero(szSQL,sizeof(szSQL));
			snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_exchange_code` WHERE `item_id` = %d AND `used` = %lld", item_id, getCid());
			result = db.query(szSQL);

			if (!result.eof())
			{
				return SOCIAL_SERVICE.replyfailure(m_cgindex,inPacket->getProc(),ERR_EXCHANGE_CODE_SAME);
			}
			else
			{
				m_get_exchange_code = 1;
				sendGameUseExchangeCode(item_id, code);
			}
		}
	}
	else
	{
		return SOCIAL_SERVICE.replyfailure(m_cgindex,inPacket->getProc(),ERR_EXCHANGE_CODE_NOT);
	}

	return ERR_OK;
}

int32_t SocialPlayer::onSocialPublicChat(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	if (SOCIAL_SERVICE.isBanChat(m_uid))
	{
		return SOCIAL_SERVICE.replyfailure(m_cgindex, inPacket->getProc(), ERR_GM_BAN_CHAT);
	}

	int32_t channel = inPacket->readInt32();

	NetPacket *chatPacket = SOCIAL_SERVICE.popNetpacket();
	if (NULL == chatPacket)
	{
		return ERR_INVALID_DATA;
	}
	chatPacket->writeInt32(channel);
	chatPacket->writeInt64(getCid());
	chatPacket->writeInt8( GetVipLevel() );
	chatPacket->writeInt8( getSex() );
	chatPacket->writeInt8(0);//kingdom
	chatPacket->writeUTF8(getName());
	chatPacket->writeInt8( GetJueWei() );
	Int32Vector yellowVector = getYellowVipLevel(getCid());
	for (Int32Vector::iterator it = yellowVector.begin();it != yellowVector.end();++it)
	{
		chatPacket->writeInt32(*it);
	}

	chatPacket->write(inPacket->getBuffer()+sizeof(int32_t), inPacket->getSize()-sizeof(int32_t));
	chatPacket->setType(PACK_DISPATCH);
	chatPacket->setProc(SM_PUBLIC_CHAT);
	chatPacket->setSize(chatPacket->getWOffset());

	if (channel == CC_FAMILY)
	{
		Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
		if ( NULL != pFamily)
		{
			pFamily->Broadcase( chatPacket ); 
		}
		//SOCIAL_SERVICE.familyBroadcast( GetFamilyId(), 0, chatPacket);
	}
	else
	{
		chatPacket->destroy();
	}

	return ERR_OK;
}

int32_t SocialPlayer::onSocialPrivateChat(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	if (SOCIAL_SERVICE.isBanChat(m_uid))
	{
		return SOCIAL_SERVICE.replyfailure(m_cgindex, inPacket->getProc(), ERR_GM_BAN_CHAT);
	}

	CharId_t cid = inPacket->readInt64();

	SocialPlayer *player = PLAYER_MANAGER.GetPlayerByCid(cid);
	if (player == NULL)
	{
		return SOCIAL_SERVICE.replyfailure(m_cgindex, inPacket->getProc(), ERR_PLAYER_OFF_LINE);
	}

	SocialPlayer *chater[2] = {this, player};
	for (int i = 0; i < 2; ++i)
	{
		NetPacket *chatPacket = SOCIAL_SERVICE.popNetpacket();
		if (NULL == chatPacket)
		{
			return ERR_INVALID_DATA;
		}
		chatPacket->writeInt64(getCid());
		chatPacket->writeInt8( GetVip() );
		chatPacket->writeInt8( getSex() );
		chatPacket->writeInt8(0);//kingdom
		chatPacket->writeUTF8(getName());
		chatPacket->writeInt8(GetJueWei());
		chatPacket->writeInt64(player->getCid());
		chatPacket->writeUTF8(player->getName());
		chatPacket->write(inPacket->getBuffer()+sizeof(int32_t), inPacket->getSize()-sizeof(int32_t));
		chatPacket->setType(PACK_DISPATCH);
		chatPacket->setProc(SM_PRIVATE_CHAT);
		chatPacket->setSize(chatPacket->getWOffset());

		SOCIAL_SERVICE.sendPacketTo(chater[i]->getGateIndex(), chatPacket);
	}

	return ERR_OK;
}


//int32_t SocialPlayer::onQueryKillerRank(Answer::NetPacket *inPacket)
//{
//	SOCIAL_SERVICE.sendKillerRank(m_cgindex);
//
//	return ERR_OK;
//}

//int32_t SocialPlayer::onQueryGambleRecord(Answer::NetPacket *inPacket)
//{
//	SOCIAL_SERVICE.sendGambleRecord();
//
//	return ERR_OK;
//}

int32_t SocialPlayer::onChangeName(Answer::NetPacket *inPacket)
{
	//if (NULL == inPacket)
	//{
	//	return ERR_INVALID_DATA;
	//}
	//if (DayTime::tick() - m_last_change_name_tick <= 10000)
	//{
	//	return ERR_INVALID_DATA;
	//}

	//string name = inPacket->readUTF8(true);
	//if (name.empty() || StringUtility::utf8Strlen(name.c_str()) > MAX_NAME_LENGTH)
	//{
	//	return ERR_INVALID_DATA;
	//}
	//int32_t bag = inPacket->readInt32();
	//int32_t slot = inPacket->readInt32();

	//char szSQL[MAX_SQL_LENGTH] = {};
	//snprintf(szSQL, sizeof(szSQL)-1, "SELECT `cid` FROM `mem_character` WHERE `name`='%s'", name.c_str());

	//MySqlDBGuard db(DBPOOL);
	//MySqlQuery result = db.query(szSQL);
	//if (result.getRowCount() != 0)
	//{
	//	return SOCIAL_SERVICE.replyfailure(m_cgindex, inPacket->getProc(), ERR_NAME_EXIST);
	//}


	//m_last_change_name_tick = DayTime::tick();

	return ERR_OK;
}
//int32_t SocialPlayer::onCreateTeamDungeon(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	//int32_t cid = inPacket->readInt32();
//	//int32_t cid = 1011;
//	int32_t dungeonID = inPacket->readInt32();
//	//int32_t dungeonID = 6004;
//	if (!SOCIAL_SERVICE.checkCreateTeamDungeon(m_cid))
//	{
//		return ERR_INVALID_DATA;
//	}
//	sendGameCreateTeamDungeon(m_cid,dungeonID);
//	return ERR_OK;
//}

//int32_t SocialPlayer::onAddTeamDungeon(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t tcid = inPacket->readInt32();
//
//	//int32_t tcid =  1011;
//	int32_t dungeonID = inPacket->readInt32();
//	//int32_t dungeonID = 6004;
//
//	if (!SOCIAL_SERVICE.checkAddTeamDungeon(tcid,getCid()))
//	{
//		return ERR_INVALID_DATA;
//	}
//	
//	sendGameAddTeamDungeon(tcid,dungeonID);
//	return ERR_OK;
//}

//int32_t SocialPlayer::onQueryTeamDungeon(Answer::NetPacket *inPacket)
//{
//	SOCIAL_SERVICE.sendTeamDungeonInfo();
//
//	return ERR_OK;
//}

//int32_t SocialPlayer::onInviteTeamDungeon(Answer::NetPacket *inPacket)
//{
//	SOCIAL_SERVICE.broadcastInviteTeamDungeon(m_cid,m_family_id);
//
//	return ERR_OK;
//}

int32_t SocialPlayer::onGameUpdateActivityState(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	m_activityState = inPacket->readInt32();

	return ERR_OK;
}

int32_t SocialPlayer::onGameCreateFamily(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	std::string name	= inPacket->readUTF8(true);
	std::string notice	= inPacket->readUTF8( true );
	Family* pFamily = FAMILY_MANAGER.CreateFamily( name, *this );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}
	m_pInfo->nFamilyId			= pFamily->GetId();
	m_pInfo->nFamilyPosition	= FP_LEADER;
	pFamily->ChangeNotice( notice, true );
	SOCIAL_SERVICE.replySuccess( m_cgindex, CM_FAMILY_CREATE );
	pFamily->SendFamilyInfo( *this );
	SendGameUpdateFamilyInfo();
	return ERR_OK;
}

//int32_t SocialPlayer::onGameBreakFamily(Answer::NetPacket *inPacket)
//{
//	return SOCIAL_SERVICE.breakFamily(getFamilyId(), getCid());
//}

//int32_t SocialPlayer::onGameUpdateKingdomContribute(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	m_kingdom_contribute = inPacket->readInt32();
//
//	PlayerInfo* pPlayerInfo =SOCIAL_SERVICE.getPlayerInfo(getCid());
//	if(pPlayerInfo!=NULL)
//	{
//		pPlayerInfo->kingdom_contribute = m_kingdom_contribute;
//	}
//	return ERR_OK;
//}

//int32_t SocialPlayer::onGameUpdateFamilyMoney(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t money = inPacket->readInt32();
//	int32_t addon = inPacket->readInt32();
//	m_family_contribute += addon;
//
//	PlayerInfo* pPlayerInfo =SOCIAL_SERVICE.getPlayerInfo(getCid());
//	if(pPlayerInfo!= NULL)
//	{
//		pPlayerInfo->family_contribute = m_family_contribute;
//	}
//
//	FamilyInfo*pFamilyInfo = SOCIAL_SERVICE.getFamilyInfo(m_family_id);
//	if (pFamilyInfo!= NULL)
//	{
//		pFamilyInfo->money += money;
//		int32_t contribute = SOCIAL_SERVICE.addSelfFamilyContribute(pFamilyInfo,m_cid,addon);
//
//		sendFamilyResource(contribute);
//	}
//
//	SOCIAL_SERVICE.setFamilyInfo(pFamilyInfo,FII_MONEY,pFamilyInfo->money);
//	return ERR_OK;
//}

int32_t SocialPlayer::onGameFamilyAddContribute( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}
	int32_t GongXian			= inPacket->readInt32();
	int32_t JunTuanZiJin		= inPacket->readInt32();
	if ( GetFamilyId() <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}
	pFamily->AddContribution( *this,GongXian, JunTuanZiJin );
	m_pInfo->nFamilyContribution += GongXian;
	return ERR_INVALID_DATA;
}

int32_t SocialPlayer::onGameAddFamilyContribute(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nMoney		= inPacket->readInt32();
	int32_t nGold		= inPacket->readInt32();

	int32_t nAddValue = CalFamilyContribute( nMoney, nGold );
	m_pInfo->nFamilyContribution += nAddValue;

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->AddContribution( *this, nMoney, nGold, nAddValue );
	return ERR_OK;
}

int32_t SocialPlayer::onGameUpdatePetContribute(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	m_pInfo->nFamilyPetContribution = inPacket->readInt32();

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->OnUpdateContribution( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onGameFamilyRegistPet(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId = inPacket->readInt64();
	CSocialPet* pPet = PET_MANAGER.GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->RegistPet( *this, pPet );
	return ERR_OK;
}

int32_t SocialPlayer::onGameFamilyUnRegistPet(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	PetId_t nPetId = inPacket->readInt64();
	CSocialPet* pPet = PET_MANAGER.GetPet( nPetId );
	if ( NULL == pPet )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->UnRegistPet( *this, pPet );
	pFamily->SendTotomInfo( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onFamilyRequestTaskCount( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}
	pFamily->SendFamilyTaskCount();
	return ERR_OK;
}

int32_t SocialPlayer::onGameFamilyAddTaskCount(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket || NULL == m_pInfo )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	pFamily->AddFamilyTaskCount();
	pFamily->SendFamilyTaskCount();
	return ERR_OK;
}

//int32_t SocialPlayer::onGameAddTeamDungeon(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t flag = inPacket->readInt32();
//
//	if (flag == 0)
//	{
//		int32_t errFlag = inPacket->readInt32();
//		int32_t cid = inPacket->readInt32();
//
//		if (errFlag == 1)
//		{
//			SOCIAL_SERVICE.clearTeamDungeon(cid);
//		}
//
//		return SOCIAL_SERVICE.replyfailure(m_cgindex,CM_TEAM_DUNGEON_ADD,ERR_TEAM_DUNGEON_FAIL);
//
//	}
//	else if (flag == 1)
//	{
//		int32_t tcid = inPacket->readInt32();
//		int32_t cid = inPacket->readInt32();
//		int32_t dungeonID = inPacket->readInt32();
//
//		SOCIAL_SERVICE.addTeamDungeon(tcid,cid);
//		return SOCIAL_SERVICE.replySuccess(m_cgindex,CM_TEAM_DUNGEON_ADD,dungeonID);		
//	}
//	else if (flag == 3)
//	{
//		return SOCIAL_SERVICE.replyfailure(m_cgindex,CM_TEAM_DUNGEON_ADD,ERR_DUNGEON_COMMON);
//	}
//	return ERR_OK;
//}

//int32_t SocialPlayer::onGameCreateTeamDungeon(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t flag = inPacket->readInt32();
//	int32_t cid = inPacket->readInt32();
//	std::string name = inPacket->readUTF8(true);
//	int32_t dungeonID = inPacket->readInt32();
//	int32_t line = inPacket->readInt32();
//
//	if (flag == 1)
//	{
//		SOCIAL_SERVICE.createTeamDungeon(cid,name,dungeonID,line);
//		return SOCIAL_SERVICE.replySuccess(m_cgindex,CM_TEAM_DUNGEON_CREATE,dungeonID);
//	}
//	else if (flag == 3)
//	{
//		return SOCIAL_SERVICE.replyfailure(m_cgindex,CM_TEAM_DUNGEON_CREATE,ERR_DUNGEON_COMMON);
//	}
//    return SOCIAL_SERVICE.replyfailure(m_cgindex,CM_TEAM_DUNGEON_CREATE,ERR_TEAM_DUNGEON_FAIL);
//}

//int32_t SocialPlayer::onGameClearTeamDungeon(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t cid = inPacket->readInt32();
//	SOCIAL_SERVICE.clearTeamDungeon(cid);
//
//	return ERR_OK;
//}


//int32_t SocialPlayer::onGameStartTeamDungeon(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t cid = inPacket->readInt32();
//
//	SOCIAL_SERVICE.startTeamDungeon(cid);
//
//	return ERR_OK;
//	
//}

//int32_t SocialPlayer::onGameKickOutTeamNum(Answer::NetPacket *inPacket)
// {
//	 if (NULL == inPacket)
//	 {
//		 return ERR_INVALID_DATA;
//	 }
//	 int32_t cid = inPacket->readInt32();
//	 int32_t tcid = inPacket->readInt32();
//	 std::string name = inPacket->readUTF8(true);
//	
//	 SOCIAL_SERVICE.kickOutTeamDungeon(cid,tcid,name);
//
//	 return ERR_OK;
//}


//int32_t SocialPlayer::onGameAddContribution(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	int32_t addon = inPacket->readInt32();
//	if (addon <= 0)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	int32_t rate = inPacket->readInt32();
//	if (rate <= 0)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	if (getFamilyId() <= 0)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	FamilyInfo* family = SOCIAL_SERVICE.getFamilyInfo(getFamilyId());
//	if (family == NULL)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	sendFamilyStateData();
//
//	if (rate > 1)
//	{
//		SOCIAL_SERVICE.broadcastFamilyDonateCard(getFamilyId(), getName(), addon * rate);
//	}
//	SOCIAL_SERVICE.addFamilyContribution(getFamilyId(), getCid(), addon, rate);
//
//	return ERR_OK;
//}


int32_t SocialPlayer::onGameUseExchangeCode(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}
	int32_t flag = inPacket->readInt32();
	std::string code = inPacket->readUTF8(true);

	if (flag)
	{
		MySqlDBGuard db(DBPOOL);

		char szSQL[MAX_SQL_LENGTH] = {};

		snprintf(szSQL, sizeof(szSQL)-1, "UPDATE `mem_exchange_code` SET `used` = '%lld' , `name` = '%s' WHERE `code`='%s'", getCid(), getName().c_str(), code.c_str());
		db.excute(szSQL);

		m_get_exchange_code = 0;

		return SOCIAL_SERVICE.replySuccess(m_cgindex,CM_USE_EXCHANGE_CODE);
	}
	
	m_get_exchange_code = 0;

	return SOCIAL_SERVICE.replyfailure(m_cgindex,CM_USE_EXCHANGE_CODE,ERR_BAG_IS_FULL);
}

int32_t SocialPlayer::onGameChangeName(Answer::NetPacket *inPacket)
{
	//if (NULL == inPacket)
	//{
		return ERR_INVALID_DATA;
	//}
	//string name = inPacket->readUTF8(true);

	//int32_t err = SOCIAL_SERVICE.updatePlayerInfo(m_cid, name);
	//if (err == ERR_OK)
	//{
	//	m_name = name;
	//}

	//return err;
}

//int32_t SocialPlayer::onGameChangeFamilyName(Answer::NetPacket *inPacket)
//{
//	if (NULL == inPacket)
//	{
//		return ERR_INVALID_DATA;
//	}
//	string name = inPacket->readUTF8(true);
//	int32_t fid = inPacket->readInt32();
//
//	int32_t err = SOCIAL_SERVICE.changeNameFamily(fid, m_cid, name);
//	if (err == ERR_OK)
//	{
//		sendFamilyInfo();
//	}
//
//	return err;
//}

int32_t SocialPlayer::onGameQueryPlayerInfo(Answer::NetPacket *inPacket)
{
	if (NULL == inPacket)
	{
		return ERR_INVALID_DATA;
	}

	CharId_t cid = inPacket->readInt64();

	char szSQL[MAX_SQL_LENGTH] = {};
	MySqlDBGuard db(DBPOOL);
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT a.name,a.sex,a.hp,a.mp,a.pp,a.exp,a.job,a.level,b.family_id,c.name AS familyname FROM `mem_character` AS a LEFT JOIN `mem_chr_family` AS b ON a.cid=b.cid LEFT JOIN `mem_family` AS c ON b.family_id=c.id WHERE a.cid=%lld", cid);
	MySqlQuery result = db.query(szSQL);
	if (!result.eof())
	{
		std::string name		= result.getStringValue("name");
		int32_t	hp				= result.getIntValue("hp");
		int32_t mp				= result.getIntValue("mp");
		int32_t pp				= result.getIntValue("pp");
		int32_t level			= result.getIntValue("level");
		int32_t job				= result.getIntValue("job");
		int32_t sex				= result.getIntValue("sex");
		int64_t exp				= result.getInt64Value("exp");
		FamilyId_t	familyId	= result.getInt64Value("family_id");
		std::string familyName	= result.getStringValue("familyname");
		std::string currency	= result.getStringValue("currency");

		MemAttr attr = {};
		bzero(szSQL, sizeof(szSQL));
		snprintf( szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_chr_attr` WHERE `cid`=%lld", cid );
		result = db.query(szSQL);
		if(!result.eof())
		{
			attr.hp				= result.getIntValue("hp");
			attr.mp				= result.getIntValue("mp");
			attr.pp				= result.getIntValue("pp");
			attr.xp				= result.getIntValue("xp");
			attr.phy_atk_min	= result.getIntValue("phy_atk_min");
			attr.phy_atk_max	= result.getIntValue("phy_atk_max");
			attr.mag_atk_min	= result.getIntValue("mag_atk_min");
			attr.mag_atk_max	= result.getIntValue("mag_atk_max");
			attr.phy_def		= result.getIntValue("phy_def");
			attr.mag_def		= result.getIntValue("mag_def");
			attr.hitrate		= result.getIntValue("hitrate");
			attr.dodge			= result.getIntValue("dodge");
			attr.critrate		= result.getIntValue("critrate");
			attr.dmg_add		= result.getIntValue("dmg_add");
			attr.dmg_rdc		= result.getIntValue("dmg_rdc");
			attr.dmg_add_pec	= result.getIntValue("dmg_add_pec");
			attr.dmg_rdc_pec	= result.getIntValue("dmg_rdc_pec");
			attr.movespeed		= result.getIntValue("movespeed");
			attr.battle			= result.getIntValue("battle");
			attr.lucky			= result.getIntValue("lucky");
		}

		NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
		if (NULL == packet)
		{
			return ERR_INVALID_DATA;
		}
		packet->writeInt64( cid );					// cid
		packet->writeUTF8( name );					// 名字
		packet->writeInt64( familyId );				// 帮派ID
		packet->writeUTF8( familyName );			// 帮派名字
		packet->writeInt8( sex );					// 性别
		packet->writeInt8( job );					// 职业
		packet->writeInt16( level );				// 等级
		packet->writeInt64( exp );					// 当前经验
		packet->writeInt64( exp );					// 升级需求经验值
		packet->writeInt32( hp );					// 当前血量
		packet->writeInt32( attr.hp );				// 最大生命值
		packet->writeInt32( mp );
		packet->writeInt32( attr.mp );				// 最大法力值
		packet->writeInt32( pp );
		packet->writeInt32( attr.pp );				// 最大体力值
		packet->writeInt32( attr.phy_atk_min );		// 最小物理攻击
		packet->writeInt32( attr.phy_atk_max );		// 最大物理攻击
		packet->writeInt32( attr.mag_atk_min );		// 最小魔法攻击
		packet->writeInt32( attr.mag_atk_max );		// 最大魔法攻击
		packet->writeInt32( attr.phy_def );			// 物理防御
		packet->writeInt32( attr.mag_def );			// 魔法防御
		packet->writeInt32( attr.hitrate );			// 命中
		packet->writeInt32( attr.dodge );			// 闪避
		packet->writeInt32( attr.critrate );		// 暴击
		packet->writeInt32( attr.battle );			// 战斗力

		// 打包装备信息
		int32_t equipCount = 0;
		int32_t oldBengin = packet->getWOffset();
		packet->writeInt8( equipCount );

		bzero(szSQL, sizeof(szSQL));
		snprintf(szSQL, sizeof(szSQL)-1, "SELECT mem_chr_bag.id, mem_chr_bag.slot, mem_chr_bag.srcid, mem_chr_bag.bind, mem_chr_bag.endtime, mem_equip.star, mem_equip.starLucky, mem_equip.addAttr, mem_equip.UpGradeLucky,mem_equip.UpQuality, mem_equip.EquipGem FROM `mem_chr_bag` LEFT JOIN `mem_equip` ON mem_chr_bag.srcid=mem_equip.id WHERE `cid`= %lld AND `bag`=0", cid);
		result = db.query(szSQL);
		while(!result.eof())
		{
			MemEquip Equip;
			packet->writeInt64( result.getInt64Value("srcid") );
			packet->writeInt8( result.getIntValue("slot") );
			packet->writeInt32( result.getIntValue("id") );
			packet->writeInt32( result.getIntValue("star") );
			packet->writeInt32( result.getIntValue("starLucky") );
			packet->writeInt8( result.getIntValue("bind") );
			packet->writeInt32( result.getIntValue("endtime") );
			packet->writeInt32( result.getIntValue("UpGradeLucky"));
			packet->writeInt32( result.getIntValue("UpQuality"));
			std::string EquipHole = result.getStringValue("EquipGem");
			Equip.ParesEquipString(EquipHole);
			for ( int32_t i = 0; i < EQUIP_GEM_COUNT; i++ )
			{
				packet->writeInt32( Equip.GemHole[i] );
			}
			++equipCount;

			result.nextRow();
		}
		int oldwoffset = packet->getWOffset();
		packet->setWOffset( oldBengin );
		packet->writeInt8( equipCount );
		packet->setWOffset( oldwoffset );

		std::string FaBaoLevelString	= "";
		std::string FaBaoDressString	= "";
		bzero( szSQL, sizeof( szSQL ) );
		snprintf( szSQL, sizeof( szSQL ) - 1, "SELECT * FROM `mem_chr_fabao` WHERE `Cid`=%lld", cid );
		Answer::MySqlQuery result = db.query( szSQL );
		while(!result.eof())
		{
			FaBaoLevelString			= result.getStringValue("FaBaoLevel");
			FaBaoDressString			= result.getStringValue("FaBaoDress");
			
			result.nextRow();
		}
		InitFaBaoInfo( FaBaoLevelString, FaBaoDressString, packet );
		packet->setType(PACK_DISPATCH);
		packet->setProc(SM_QUERY_PLAYER_INFO);
		packet->setSize(packet->getWOffset());
		SOCIAL_SERVICE.sendPacketTo(m_cgindex, packet);
	}

	return ERR_OK;
}

void SocialPlayer::InitFaBaoInfo( std::string  FaBaoLevelString, std::string FaBaoDressString, Answer::NetPacket *inPacket )
{
	int8_t FaBaoLevel[FA_BAO_TYPE_COUNT] = {};
	int8_t FaBaoDress[FA_BAO_TYPE_COUNT] = {};
	if ( !FaBaoLevelString.empty() )
	{
		StringVector ItemVector = Answer::StringUtility::split(FaBaoLevelString, ":");
		if ( ItemVector.size() == FA_BAO_TYPE_COUNT )
		{
			for ( int32_t i = 0; i < FA_BAO_TYPE_COUNT; ++i )
			{
				FaBaoLevel[i]	= atoi(ItemVector[i].c_str());
			}
		}
	}
	
	if ( !FaBaoDressString.empty() )
	{
		StringVector ItemVector = Answer::StringUtility::split(FaBaoDressString, ":");
		if ( ItemVector.size() == FA_BAO_TYPE_COUNT )
		{
			for ( int32_t i = 0; i < FA_BAO_TYPE_COUNT; ++i )
			{
				FaBaoDress[i]	= atoi(ItemVector[i].c_str());
			}
		}
	}

	if ( inPacket == NULL )
	{
		return;
	}
	for ( int8_t i = 0;  i < FA_BAO_TYPE_COUNT; i++ )
	{
		inPacket->writeInt8( i );
		inPacket->writeInt8( FaBaoLevel[i] );
		inPacket->writeInt8( FaBaoDress[i] );
	}
}

//int32_t SocialPlayer::getSumOfZhiyuanqianxian()
//{
//	MySqlDBGuard db(DBPOOL);
//
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT SUM(`value`) FROM `mem_chr_juanxianwuzi`");
//	MySqlQuery sumResult = db.query(szSQL);
//	int32_t sum = 0;
//	if(!sumResult.eof())
//	{
//		sum = sumResult.getIntValue(0);
//	}
//	return sum;
//}

//void SocialPlayer::noticeRelationMessage(int32_t tcid, int32_t rtype)
//{
//	SocialPlayer* targetPlayer = PLAYER_MANAGER.GetPlayerByCid(tcid);
//	if(targetPlayer != NULL)
//	{
//		NetPacket *relationPacket = SOCIAL_SERVICE.popNetpacket();
//		if (NULL == relationPacket)
//		{
//			return;
//		}
//		relationPacket->writeInt32(getCid());
//		relationPacket->writeInt32(rtype);
//		relationPacket->writeUTF8(getName());
//		relationPacket->setType(PACK_DISPATCH);
//		relationPacket->setProc(SM_RELATION_MESSAGE);
//		relationPacket->setSize(relationPacket->getWOffset());
//
//		SOCIAL_SERVICE.sendPacketTo(targetPlayer->getGateIndex(), relationPacket);
//	}
//}

//
//void SocialPlayer::sendInviteFamily(std::string familyname,int32_t tcgindex)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(getCid());
//	familyPacket->writeUTF8(getName());
//	familyPacket->writeUTF8(familyname);
//
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_INVITE);
//	familyPacket->setSize(familyPacket->getWOffset());
//
//	SOCIAL_SERVICE.sendPacketTo(m_cgindex, familyPacket);
//}

//void SocialPlayer::sendFamilyResource(int32_t contribute)
//{
//	FamilyInfo* info = SOCIAL_SERVICE.getFamilyInfo(m_family_id);
//	if (info == NULL)
//	{
//		return;
//	}
//
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket(); 
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt16(info->level);
//	familyPacket->writeInt32(info->money);
//	familyPacket->writeInt32(contribute);
//
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_RESOURCE);
//	familyPacket->setSize(familyPacket->getWOffset());
//
//	SOCIAL_SERVICE.sendPacketTo(m_cgindex, familyPacket);
//}

//void SocialPlayer::sendSelfFamilyInfo()
//{
//	FamilyInfo* info = SOCIAL_SERVICE.getFamilyInfo(m_family_id);
//	if (info == NULL)
//	{
//		return;
//	}
//
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket(); 
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(info->fid);
//	familyPacket->writeUTF8(info->name);
//	familyPacket->writeUTF8(info->leader_name);
//	familyPacket->writeInt16(info->count);
//	familyPacket->writeInt16(info->level);
//	//familyPacket->writeInt32(info->exp);
//	familyPacket->writeInt32(info->money);
//	familyPacket->writeUTF8(info->notice);
//	familyPacket->writeInt16(info->appliers.size());
//
//	for (FamilyApplyInfoVector::iterator it = info->appliers.begin();it != info->appliers.end();++it)
//	{
//		familyPacket->writeInt32(it->cid);
//		familyPacket->writeUTF8(it->name);
//		familyPacket->writeInt8(it->job);
//		familyPacket->writeInt16(it->level);
//	}
//
//	familyPacket->writeInt8(m_family_pos);
//	
//	bool bFind = false;
//	for (FamilyMemberInfoVector::iterator it = info->members.begin();it != info->members.end();++it)
//	{
//		if (it->cid == m_cid)
//		{
//			bFind = true;
//			familyPacket->writeInt32(it->contribute);
//			break;
//		}
//	}
//
//	if (!bFind)
//	{
//		familyPacket->writeInt32(0);
//	}
//
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_SELF_FAMILY_INFO);
//	familyPacket->setSize(familyPacket->getWOffset());
//
//	SOCIAL_SERVICE.sendPacketTo(m_cgindex, familyPacket);
//
//}

//void SocialPlayer::sendFamilyNotice(int32_t fid,const std::string &notice)
//{
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(fid);
//	familyPacket->writeUTF8(notice);
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_NOTICE);
//	familyPacket->setSize(familyPacket->getWOffset());
//
//	SOCIAL_SERVICE.sendPacketTo(m_cgindex, familyPacket);
//}

//void SocialPlayer::sendFamilyInfo()
//{
//}

//void SocialPlayer::sendFamilyAppliers()
//{
//	if ( GetFamilyId() <= 0)
//	{
//		return;
//	}
//
//	Family* pFamily = FAMILY_MANAGER.GetFamily( GetFamilyId() );
//	if ( NULL == pFamily )
//	{
//		return;
//	}
//
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//
//	pFamily->AppendApplyInfo( packet );
//
//	packet->setType( PACK_DISPATCH );
//	packet->setProc( SM_FAMILY_APPLIERS );
//	packet->setSize( packet->getWOffset() );
//
//	SOCIAL_SERVICE.sendPacketTo( m_cgindex, packet );
//}

//int32_t SocialPlayer::createFamily(std::string name,std::string &notice,const Int32Vector &slot)
//{
//	if (getFamilyId() > 0)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	{
//		MySqlDBGuard db(DBPOOL);
//		char szSQL[MAX_SQL_LENGTH] = {};
//		snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_family` WHERE `name`='%s'", name.c_str());
//		MySqlQuery result = db.query(szSQL);
//		if (result.getRowCount() > 0) //duplicate
//		{
//			return SOCIAL_SERVICE.replyfailure(m_cgindex,CM_FAMILY_CREATE,ERR_NAME_EXIST);
//		}
//	}
//
//	sendGameCreateFamily(name,notice,slot);
//	return ERR_OK;
//}

//int32_t SocialPlayer::approveForFamily(int32_t cid, int32_t result)
//{
//	if ( GetFamilyId() <= 0)
//	{
//		return ERR_INVALID_DATA;
//	}
//
//	//int32_t err = SOCIAL_SERVICE.approveFamilyApply(getFamilyId(), getCid(), cid, result);
//	//if (err != ERR_OK)
//	//{
//	//	return err;
//	//}
//
//	//if (result == 1)
//	//{
//	//	FamilyInfo* family = SOCIAL_SERVICE.getFamilyInfo(getFamilyId());
//	//	if (family == NULL)
//	//	{
//	//		return ERR_INVALID_DATA;
//	//	}
//
//	//	SocialPlayer* targetPlayer = SOCIAL_SERVICE.getPlayerByCid(cid);
//	//	if(targetPlayer != NULL)
//	//	{
//	//		targetPlayer->setFamilyId(getFamilyId());
//	//		targetPlayer->setFamilyPos(FP_MEMBER);
//	//		targetPlayer->clearFamilyApply();
//	//		targetPlayer->sendGameSynFamily(UFIR_JOIN);
//	//		targetPlayer->sendFamilyStateData();
//
//	//		PlayerInfo* playerInfo = SOCIAL_SERVICE.getPlayerInfo(cid);
//	//		if (playerInfo != NULL)
//	//		{
//	//			playerInfo->family_id = getFamilyId();
//	//		}
//	//		SOCIAL_SERVICE.broadcastFamilyApprove(getFamilyId(), targetPlayer->getCid(), targetPlayer->getName(), family->name);
//	//	}
//	//}
//	//else if (result == 0)
//	//{
//	//	SocialPlayer* targetPlayer = SOCIAL_SERVICE.getPlayerByCid(cid);
//	//	if(targetPlayer != NULL)
//	//	{
//	//		targetPlayer->clearFamilyApply();
//	//	}
//	//}
//
//	return ERR_OK;
//}

//int32_t SocialPlayer::appointFamily(int32_t tcid, int32_t pos)
//{
//	//if ( GetFamilyId() <= 0 )
//	//{
//	//	return ERR_INVALID_DATA;
//	//}
//
//	//int32_t err = SOCIAL_SERVICE.appointFamily( GetFamilyId(), getCid(), tcid, pos );
//	//if ( err != ERR_OK )
//	//{
//	//	return SOCIAL_SERVICE.replyfailure(m_cgindex, CM_FAMILY_APPOINT, err);
//	//}
//
//	//sendFamilyInfo();
//	//FamilyInfo* pFamilyInfo = SOCIAL_SERVICE.getFamilyInfo(getFamilyId());
//	//if (pFamilyInfo != NULL)
//	//{
//	//	sendGameFamilyPosChange(pFamilyInfo->name,pos);
//	//}
//	//
//	//if (pos == FP_LEADER)
//	//{
//	//	setFamilyPos(FP_MEMBER);
//	//	sendFamilyStateData();
//	//}
//
//	//SocialPlayer* targetPlayer = SOCIAL_SERVICE.getPlayerByCid(tcid);
//	//if(targetPlayer != NULL)
//	//{
//	//	targetPlayer->setFamilyPos(pos);
//	//	targetPlayer->sendFamilyStateData();
//	//}
//
//	return ERR_OK;
//}


//void SocialPlayer::sendFamilyApplyNote()
//{
//	if (m_family_id <= 0 || (m_family_pos != FP_LEADER && m_family_pos != FP_VICE_LEADER))
//	{
//		return;
//	}
//
//	FamilyInfo* pFamilyInfo = SOCIAL_SERVICE.getFamilyInfo(m_family_id);
//	if (pFamilyInfo == NULL)
//	{
//		return  ;
//	}
//
//	if (pFamilyInfo->appliers.size() <= 0 )
//	{
//		return ;
//	}
//
//	NetPacket *familyPacket = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == familyPacket)
//	{
//		return;
//	}
//	familyPacket->writeInt32(pFamilyInfo->appliers.size());
//	familyPacket->setType(PACK_DISPATCH);
//	familyPacket->setProc(SM_FAMILY_APPLY_NOTE);
//	familyPacket->setSize(familyPacket->getWOffset());
//
//	SOCIAL_SERVICE.sendPacketTo(m_cgindex, familyPacket);
//}

//void SocialPlayer::sendGameCreateTeamDungeon(int32_t cid,int32_t dungeonID)
//{
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(m_uid);
//	packet->writeInt32(m_sid);
//	packet->writeInt32(m_cgindex);
//	//packet->writeInt32(cid);
//	packet->writeInt32(dungeonID);
//
//	packet->setType(PACK_PROC);
//	packet->setProc(IM_SOCIAL_GAME_CREATE_TEAM_DUNGEON);
//	packet->setSize(packet->getWOffset());
//	SOCIAL_SERVICE.sendPacket(packet);
//}

//void SocialPlayer::sendGameAddTeamDungeon(int32_t tcid,int32_t dungeonID)
//{
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(m_uid);
//	packet->writeInt32(m_sid);
//	packet->writeInt32(m_cgindex);
//	packet->writeInt32(tcid);
//	packet->writeInt32(dungeonID);
//
//	packet->setType(PACK_PROC);
//	packet->setProc(IM_SOCIAL_GAME_ADD_TEAM_DUNGEON);
//	packet->setSize(packet->getWOffset());
//	SOCIAL_SERVICE.sendPacket(packet);
//}

void SocialPlayer::sendGameCreateFamily( const std::string &name, const std::string &notice )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeUTF8( name );
	packet->writeUTF8( notice );
	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_CREATE_FAMILY );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialPlayer::SendGameAddCurrency( int8_t nCurrency, int32_t nCount )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeInt8( nCurrency );
	packet->writeInt32( nCount );
	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_ADD_CURRENCY );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

//void SocialPlayer::sendGameUpdateFamilyContribute(int32_t addon)
//{
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(m_uid);
//	packet->writeInt32(m_sid);
//	packet->writeInt32(m_cgindex);
//	packet->writeInt32(addon);
//
//	packet->setType(PACK_PROC);
//	packet->setProc(IM_SOCIAL_GAME_UPDATE_FAMILY_CONTRIBUTE);
//	packet->setSize(packet->getWOffset());
//	SOCIAL_SERVICE.sendPacket(packet);
//}

//void SocialPlayer::sendGameLeaderDown(int32_t tcid)
//{
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(m_uid);
//	packet->writeInt32(m_sid);
//	packet->writeInt32(m_cgindex);
//	packet->writeInt32(tcid);
//
//	packet->setType(PACK_PROC);
//	packet->setProc(IM_SOCIAL_GAME_LEADER_DOWN);
//	packet->setSize(packet->getWOffset());
//	SOCIAL_SERVICE.sendPacket(packet);
//}

//void SocialPlayer::sendGameLeaderCid(int32_t cid,int32_t uid,int32_t sid,int32_t cgindex)
//{
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(uid);
//	packet->writeInt32(sid);
//	packet->writeInt32(cgindex);
//	packet->writeInt32(cid);
//
//	packet->setType(PACK_PROC);
//	packet->setProc(IM_SOCIAL_GAME_UPDATE_LEADER_CID);
//	packet->setSize(packet->getWOffset());
//	SOCIAL_SERVICE.sendPacket(packet);
//}


//void SocialPlayer::sendGotoEnemy(int32_t cid,int32_t type,const BagSlotVector & item)
//{
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt32(m_uid);
//	packet->writeInt32(m_sid);
//	packet->writeInt32(m_cgindex);
//	packet->writeInt32(cid);
//	packet->writeInt32(type);
//	packet->writeInt32(item.size());
//	for (BagSlotVector::const_iterator it = item.begin();it != item.end();++it)
//	{
//		packet->writeInt32(it->bag);
//		packet->writeInt32(it->slot);
//	}
//	packet->setType(PACK_PROC);
//	packet->setProc(IM_SOCIAL_GAME_GOTO_ENEMY);
//	packet->setSize(packet->getWOffset());
//	SOCIAL_SERVICE.sendPacket(packet);
//}

//void SocialPlayer::sendGameFamilyPosChange(const std::string &name,int32_t position)
//{
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeUTF8(name);
//	packet->writeInt32(position);
//	packet->setType(PACK_PROC);
//	packet->setProc(IM_SOCIAL_GAME_CHANGE_FAMILY_INFO);
//	packet->setSize(packet->getWOffset());
//	SOCIAL_SERVICE.sendPacket(packet);
//}

void SocialPlayer::sendGameUseExchangeCode(int32_t item_id,const std::string &code)
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32(m_uid);
	packet->writeInt32(m_sid);
	packet->writeInt32(m_cgindex);
	packet->writeInt32(item_id);
	packet->writeUTF8(code);
	packet->setType(PACK_PROC);
	packet->setProc(IM_SOCIAL_GAME_USE_EXCHANGE_CODE);
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacket(packet);
}

void SocialPlayer::SendGameUpdateFamilyInfo()
{
	if ( NULL == m_pInfo )
	{
		return;
	}
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );

	packet->writeInt64( m_pInfo->nFamilyId );
	packet->writeInt32( m_pInfo->nFamilyPosition );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_UPDATE_FAMILY );
	packet->setSize(packet->getWOffset());
	SOCIAL_SERVICE.sendPacket(packet);
}

//void SocialPlayer::sendActivityData()
//{
//	if (m_activityRanks.size() == 0)
//	{
//		SOCIAL_SERVICE.replyfailure(m_cgindex, SM_QUERY_ACTIVITY_INFO, ERR_ACTIVITY_DATA_EMPTY);
//		return;
//	}
//
//	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
//	if (NULL == packet)
//	{
//		return;
//	}
//	packet->writeInt8(m_activityRanks.size());
//	int32_t date = m_activityRanks[0]->date;
//	for (ActivityRankPtrVector::iterator it = m_activityRanks.begin(); it != m_activityRanks.end(); it++)
//	{
//		packet->writeInt8((*it)->rank);
//		packet->writeInt32((*it)->jifen);
//		packet->writeUTF8((*it)->name);
//	}
//	packet->writeInt32(date);
//	packet->setType(PACK_PROC);
//	packet->setProc(SM_QUERY_ACTIVITY_INFO);
//	packet->setSize(packet->getWOffset());
//
//	SOCIAL_SERVICE.sendPacketTo(m_cgindex, packet);
//}

//void SocialPlayer::updateActivityData(int8_t activityId, int8_t kingdom, int8_t count)
//{
//	ActivityRankVector *acRanks = NULL;
//	SOCIAL_SERVICE.getActivityRank(&acRanks);
//	m_activityRanks.clear();
//	int32_t time =0;
//	bool firstFlag = true;
//
//	if (acRanks == NULL)
//	{
//		return;
//	}
//	else
//	{
//		for (ActivityRankVector::iterator acRankIt = acRanks->begin(); acRankIt != acRanks->end(); acRankIt++)
//		{
//			if (acRankIt->acId == activityId)
//			{
//				if (firstFlag)
//				{
//					time = acRankIt->date;
//					firstFlag = false;
//				}
//
//				if (time == acRankIt->date && acRankIt->kingdom == kingdom && acRankIt->count == count)
//				{
//					m_activityRanks.push_back(&(*acRankIt));
//				}
//
//				//查询国家数据的时候
//				if (acRankIt->count == 1 && acRankIt->count == kingdom && count == 0 && time == acRankIt->date)
//				{
//					m_activityRanks.push_back(&(*acRankIt));
//				}
//			}
//			else
//			{
//				//如果还没遍历到
//				if (firstFlag == true)
//				{
//					continue;
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//	}
//}

Int32Vector SocialPlayer::getYellowVipLevel( CharId_t tcid)
{
	int level = 0;
	int isYellowYearVip = 0;
	int isYellowHighVip = 0;
	Int32Vector yellowVector;
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = {};
	int32_t tuid = 0;
	int32_t tsid = 0;
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `mem_character` WHERE `cid`=%lld", tcid);
	MySqlQuery result = db.query(szSQL);
	if (result.getRowCount() == 1)
	{
		tuid = result.getIntValue("uid");
		tsid = result.getIntValue("sid");
	}

	bzero(szSQL,sizeof(szSQL));
	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `sys_user_token` WHERE `uid`=%d AND `sid` = %d", tuid,tsid);
	result = db.query(szSQL);
	if (result.getRowCount() == 1)
	{
		level = result.getIntValue("yellow_vip_level");
		isYellowYearVip  = result.getIntValue("is_yellow_year_vip");
		isYellowHighVip = result.getIntValue("is_yellow_high_vip");

	}
	yellowVector.push_back(level);
	yellowVector.push_back(isYellowYearVip);
	yellowVector.push_back(isYellowYearVip);
	return yellowVector;
}

//AttrAddonInfoVector SocialPlayer::parseEffect(int32_t id, const std::string &str)
//{
//	AttrAddonInfoVector attrAddons;
//
//	if (!str.empty()&& str!="0")
//	{
//		StringVector strAttrAddons = StringUtility::split(str, "|");
//		for (StringVector::iterator it = strAttrAddons.begin(); it != strAttrAddons.end(); ++it)
//		{
//			StringVector strAttrAddon = StringUtility::split(*it, ":");
//			if (strAttrAddon.size() == 2)
//			{
//				AttrAddonInfo attrAddon = {};
//				attrAddon.index = atoi(strAttrAddon[0].c_str());
//				attrAddon.addon = atoi(strAttrAddon[1].c_str());
//				if (attrAddon.index > 0 && attrAddon.addon > 0)
//				{
//					attrAddons.push_back(attrAddon);
//				}
//			}
//			else
//			{
//				LOG_ERROR("CfgData::parseEffect wrong data with id = %d, str = %s\n", id, str.c_str());
//			}
//		}
//	}
//
//	return attrAddons;
//}

//AttrAddonInfoVector SocialPlayer::getEquipSecondAttrAddon(const ViceGeneralEquipInfo &memEquip,int32_t position)
//{
//	AttrAddonInfoVector attrAddon;
//
//	if (memEquip.vid > 0)
//	{
//		//???
//		AttrAddonInfoVector gemRatioAddon;
//		AttrAddonInfo gemAddon = {};;
//		gemAddon = getGemRatioAddon(memEquip.gem_slot_1);
//		if (gemAddon.index)gemRatioAddon.push_back(gemAddon);
//		gemAddon = getGemRatioAddon(memEquip.gem_slot_2);
//		if (gemAddon.index)gemRatioAddon.push_back(gemAddon);
//		gemAddon = getGemRatioAddon(memEquip.gem_slot_3);
//		if (gemAddon.index)gemRatioAddon.push_back(gemAddon);
//		gemAddon = getGemRatioAddon(memEquip.gem_slot_4);
//		if (gemAddon.index)gemRatioAddon.push_back(gemAddon);
//		gemAddon = getGemRatioAddon(memEquip.gem_slot_5);
//		if (gemAddon.index)gemRatioAddon.push_back(gemAddon);
//		gemAddon = getGemRatioAddon(memEquip.gem_slot_6);
//		if (gemAddon.index)gemRatioAddon.push_back(gemAddon);
//
//		for (AttrAddonInfoVector::iterator it = gemRatioAddon.begin(); it != gemRatioAddon.end(); ++it)
//		{
//			attrAddon.push_back(*it);
//		}
//
//		MySqlDBGuard db(DBPOOL);
//		char szSQL[MAX_SQL_LENGTH] = {};
//		snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `cfg_equip_enhance_level` where `equip_position` = %d and level = %d", position,memEquip.enhance_level);
//		MySqlQuery result = db.query(szSQL);
//		if (!result.eof())
//		{
//			AttrAddonInfoVector enhanceAttrAddon  =parseEffect(memEquip.enhance_level,result.getStringValue("addon"));;
//			for (AttrAddonInfoVector::iterator it = enhanceAttrAddon.begin(); it != enhanceAttrAddon.end(); ++it)
//			{
//				attrAddon.push_back(*it);
//
//			}
//		
//	}
//
//	}	
//	return attrAddon;
//	
//
//}

//AttrAddonInfo SocialPlayer::getGemRatioAddon(int32_t id)
//{
//	AttrAddonInfo attrAddon = {};
//	MySqlDBGuard db(DBPOOL);
//	char szSQL[MAX_SQL_LENGTH] = {};
//	snprintf(szSQL, sizeof(szSQL)-1, "SELECT * FROM `cfg_item` where id = %d", id);
//	MySqlQuery result = db.query(szSQL);
//	if (!result.eof())
//	{
//		int32_t type = result.getIntValue("type");
//		if ((type == 15 ||type == 16 ||type == 17|| type == 18 ||
//			type == 19 ||type == 20))
//		{
//			StringVector strAttrAddon = StringUtility::split(result.getStringValue("effect"), ":");
//			if (strAttrAddon.size() == 2)
//			{
//				attrAddon.index = atoi(strAttrAddon[0].c_str());
//				attrAddon.addon = atoi(strAttrAddon[1].c_str());
//			}
//		}
//	}
//	return attrAddon;
//}



int32_t SocialPlayer::onCreateTeam( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pTeam != NULL )
	{
		return ERR_INVALID_DATA;
	}

	m_pTeam = TEAM_MANAGER.CreateTeam( this );
	if ( NULL == m_pTeam )
	{
		return ERR_INVALID_DATA;
	}
	
	m_pTeam->BroadcastMembers();
	SOCIAL_SERVICE.replySuccess( this->getGateIndex(), inPacket->getProc() );
	//this->SendGameUpdateTeamInfo();
	return ERR_OK;
}

int32_t SocialPlayer::onInviteIntoTeam( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeam || m_pTeam->GetLeader() != this )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pTeam->IsFull() )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCid = inPacket->readInt64();

	SocialPlayer *pTarget = PLAYER_MANAGER.GetPlayerByCid( nCid );
	if ( pTarget == NULL || pTarget->IsInTeam() )
	{
		SOCIAL_SERVICE.replyfailure( this->getGateIndex(), inPacket->getProc(), ERR_IS_IN_TEAM );
		return ERR_INVALID_DATA;
	}
	if ( !pTarget->CanAcceptInvite() )
	{	
		SOCIAL_SERVICE.replyfailure( this->getGateIndex(), inPacket->getProc(), ERR_TARGET_SET_NOT_INVITE );
		return ERR_INVALID_DATA;
	}
	if ( pTarget->IsAutoAcceptInvite() )
	{
		m_pTeam->MemberJoin( pTarget );
		SOCIAL_SERVICE.replySuccess( this->getGateIndex(), inPacket->getProc(), 1 );
		SOCIAL_SERVICE.replySuccess( pTarget->getGateIndex(), CM_REPLY_TEAM_INVITE );
	}
	else
	{
		pTarget->AddInvite( m_pTeam );

		NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
		if ( NULL == packet )
		{
			return ERR_INVALID_DATA;
		}

		packet->writeInt32( m_pTeam->GetId() );
		packet->writeInt64( this->getCid() );
		packet->writeUTF8( this->getName() );
		packet->setSize( packet->getWOffset() );
		packet->setProc( SM_TEAM_INVITE );
		SOCIAL_SERVICE.sendPacketTo( pTarget->getGateIndex(), packet );
		SOCIAL_SERVICE.replySuccess( this->getGateIndex(), inPacket->getProc(), 2 );
	}
	return ERR_OK;
}

int32_t SocialPlayer::onSetTeamLeader( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCid = inPacket->readInt64();
	if ( nCid <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeam || m_pTeam->GetLeader() != this )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pTeam->SetLeader( nCid ) )
	{
		return ERR_INVALID_DATA;
	}

	return ERR_OK;
}

int32_t SocialPlayer::onKickOutTeamMember( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCid = inPacket->readInt64();
	if ( nCid <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeam || m_pTeam->GetLeader() != this )
	{
		return ERR_INVALID_DATA;
	}

	////在副本地图中
	//if ( inDungeon() )
	//{
	//	return ERR_INVALID_DATA;
	//}

	if ( !m_pTeam->MemberLeave( nCid, LTR_KICKED ) )
	{
		return ERR_INVALID_DATA;
	}

	return ERR_OK;
}

int32_t SocialPlayer::onLeaveTeam( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeam )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pTeam->MemberLeave( this->getCid() ) )
	{
		return ERR_INVALID_DATA;
	}

	////在副本地图中
	//if ( m_pPlayer->inDungeon() )
	//{
	//	m_pPlayer->leaveDungeon();
	//}

	return ERR_OK;
}

int32_t SocialPlayer::onApplyIntoTeam( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCid = inPacket->readInt64();
	SocialPlayer *pLeader = PLAYER_MANAGER.GetPlayerByCid( nCid );
	if ( NULL == pLeader )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pTeam != NULL )
	{
		return ERR_INVALID_DATA;
	}

	Team* pTeam = pLeader->GetTeam();
	if ( NULL == pTeam )
	{
		SOCIAL_SERVICE.replyfailure( this->getGateIndex(), inPacket->getProc(), ERR_TEAM_NOT_FIND );
		return ERR_INVALID_DATA;
	}

	if ( pTeam->IsFull() )
	{
		SOCIAL_SERVICE.replyfailure( this->getGateIndex(), inPacket->getProc(), ERR_TEAM_FULL );
		return ERR_INVALID_DATA;
	}

	if ( pLeader->IsAutoAcceptApply() )
	{
		pTeam->MemberJoin( this );
		SOCIAL_SERVICE.replySuccess( this->getGateIndex(), inPacket->getProc() );
		SOCIAL_SERVICE.replySuccess( pLeader->getGateIndex(), CM_REPLY_TEAM_APPLY );
	}
	else
	{
		pTeam->AddApplyer( this );

		NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
		if (NULL == packet)
		{
			return ERR_INVALID_DATA;
		}
		packet->writeInt64( this->getCid() );
		packet->writeUTF8( this->getName() );
		packet->setSize( packet->getWOffset() );
		packet->setProc( SM_TEAM_APPLY );
		SOCIAL_SERVICE.sendPacketTo( pLeader->getGateIndex(), packet );
	}

	return ERR_OK;
}

int32_t SocialPlayer::onReplyTeamInvite( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( IsInTeam() )
	{
		return ERR_INVALID_DATA;
	}

	int32_t	nTeamId = inPacket->readInt32();
	int8_t	accept = inPacket->readInt8();

	Team* pTeam;
	TeamList::iterator iter = m_lstInvite.begin();
	TeamList::iterator eiter = m_lstInvite.end(); 
	for ( ; iter != eiter; ++iter )
	{
		pTeam = *iter;
		if ( pTeam != NULL && pTeam->GetId() == nTeamId )
		{
			break;
		}
	}

	if ( iter == eiter || NULL == pTeam )
	{
		if ( accept > 0 )
		{
			// 通知玩家找不到队伍
			SOCIAL_SERVICE.replyfailure( this->getGateIndex(), inPacket->getProc(), ERR_TEAM_NOT_FIND );
		}
		return ERR_INVALID_DATA;
	}


	SocialPlayer *pLeader = pTeam->GetLeader();
	if ( NULL == pLeader )
	{
		m_lstInvite.erase( iter );
		return ERR_INVALID_DATA;
	}

	if ( accept > 0 )
	{
		if ( pTeam->IsFull() )
		{
			// 通知玩家队伍满消息
			m_lstInvite.erase( iter );
			SOCIAL_SERVICE.replyfailure( this->getGateIndex(), inPacket->getProc(), ERR_TEAM_FULL );
			return ERR_INVALID_DATA;
		}
		pTeam->MemberJoin( this );
		SOCIAL_SERVICE.replySuccess( this->getGateIndex(), inPacket->getProc() );
		SOCIAL_SERVICE.replySuccess( pLeader->getGateIndex(), CM_INVITE_INTO_TEAM );
	}
	else
	{
		// 通知队长拒绝消息
		SOCIAL_SERVICE.replyfailure( pLeader->getGateIndex(), inPacket->getProc(), ERR_TEAM_REFUCE, this->getCid() );
	}
	return ERR_OK;
}

int32_t SocialPlayer::onReplyTeamApply( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCid = inPacket->readInt64();
	int8_t	 accept = inPacket->readInt8();

	if ( NULL == m_pTeam || m_pTeam->GetLeader() != this )
	{
		return ERR_INVALID_DATA;
	}

	SocialPlayer* pApplyer = m_pTeam->CheckInApplyList( nCid );
	if ( NULL == pApplyer )
	{
		return ERR_INVALID_DATA;
	}

	if ( pApplyer->IsInTeam() )
	{
		m_pTeam->RemoveApplyer( pApplyer->getCid() );
		return ERR_INVALID_DATA;
	}

	if ( accept > 0 )
	{
		if ( m_pTeam->IsFull() )
		{
			// 通知玩家队伍满消息
			m_pTeam->RemoveApplyer( pApplyer->getCid() );
			SOCIAL_SERVICE.replyfailure( this->getGateIndex(), inPacket->getProc(), ERR_TEAM_FULL );
			return ERR_INVALID_DATA;
		}
		m_pTeam->MemberJoin( pApplyer );
		SOCIAL_SERVICE.replySuccess( this->getGateIndex(), inPacket->getProc() );
		SOCIAL_SERVICE.replySuccess( pApplyer->getGateIndex(), CM_APPLY_INTO_TEAM );
	}
	else
	{
		// 通知申请者拒绝消息
		SOCIAL_SERVICE.replyfailure( pApplyer->getGateIndex(), inPacket->getProc(), ERR_TEAM_REFUCE );
	}

	m_pTeam->RemoveApplyer( nCid );
	return ERR_OK;
}

int32_t SocialPlayer::onSetTeamAutoOperate( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	m_bAutoInvite	= inPacket->readInt8() > 0 ? true : false;
	m_bAutoApply	= inPacket->readInt8() > 0 ? true : false;
	m_bCanInvite	= inPacket->readInt8() <= 0 ? true : false;
	m_bCanAddFriend = inPacket->readInt8() <= 0 ? true : false;
	return ERR_OK;
}

int32_t SocialPlayer::onTeamDestroy( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeam || m_pTeam->GetLeader() != this )
	{
		return ERR_INVALID_DATA;
	}

	m_pTeam->Destroy();
	return ERR_OK;
}

int32_t	SocialPlayer::onGameAddXP( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pTeam != NULL && m_pTeam->IsInXP() )
	{
		return ERR_INVALID_DATA;
	}
	int32_t AddXp = inPacket->readInt32();
	AddXP( AddXp );
	return ERR_OK;
}

int32_t	SocialPlayer::onGameStartXP( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	m_nXP			= 0;
	m_nXPState		= XS_DO_SKILL;
	m_nXPAddExp		= 0;
	m_bJoinWithXP	= false;
	return ERR_OK;
}

int32_t	SocialPlayer::onGameEndXP( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	m_nXPAddExp = inPacket->readInt64();

	if ( NULL == m_pTeam )
	{
		resetXP();
	}
	else if ( m_pTeam->GetMemberCount() > 1 )
	{
		m_nXP = 0;
		if ( m_bJoinWithXP )
		{
			m_nXPState = XS_OTHER_END;
		}
		else
		{
			m_nXPState = XS_END;
		}
		m_pTeam->CheckEndXP();
	}
	else
	{
		resetXP();
	}
	return ERR_OK;
}

int32_t	SocialPlayer::onGameBreakXP( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeam )
	{
		resetXP();
	}
	else if ( m_pTeam->GetMemberCount() > 1 )
	{
		m_nXP = 0;
		m_nXPState = XS_BREAK;
		SendGameUpdateXP();
		m_pTeam->CheckEndXP();
	}
	else
	{
		resetXP();
	}
	return ERR_OK;
}

int32_t SocialPlayer::OnDieResetXp( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	if ( NULL == m_pTeam )
	{
		resetXP();
	}
	else
	{
		if ( m_pTeam->GetMemberCount() > 1 )
		{
			resetXP();
			m_nXPState = XS_STOP;
		}
		if ( m_pTeam->AllMembersXpStateStop() )
		{
			m_pTeam->resetXP( 0 );
		}
	}

	return ERR_OK;
}

int32_t	SocialPlayer::onAskPetRankInfo( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	PetIdList petIdList;
	int8_t nCount = inPacket->readInt8();
	for ( int8_t i = 0; i < nCount; ++i )
	{
		petIdList.push_back( static_cast<PetId_t>( inPacket->readInt64() ) );
	}
	PET_MANAGER.SendPetRankInfo( petIdList, m_cgindex );
	return ERR_OK;
}

int32_t	SocialPlayer::onAskPetRankList( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nBaseId		= inPacket->readInt32();
	int8_t	nRankType	= inPacket->readInt8();
	PET_RANK.SendPetRankList( nBaseId, nRankType, m_cgindex );
	return ERR_OK;
}

int32_t	SocialPlayer::onAskGameRank( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	nRankType	= inPacket->readInt8();
	RANK_MANAGER.SendGameRank( nRankType, m_cgindex );
	return ERR_OK;
}

void SocialPlayer::SendGameUpdateTeamInfo()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	int32_t nTeamId = 0;
	CharId_t nLeaderId = 0;
	std::string strLeaderName = "";
	TeamMemberList members;
	if ( m_pTeam != NULL )
	{
		nTeamId = m_pTeam->GetId();
		SocialPlayer* pLeader = m_pTeam->GetLeader();
		if ( pLeader != NULL )
		{
			nLeaderId = pLeader->getCid();
			strLeaderName = pLeader->getName();
		}
		m_pTeam->GetMembers( members );
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeInt32( nTeamId );
	packet->writeInt64( nLeaderId );
	packet->writeUTF8( strLeaderName );
	packet->writeInt8( members.size() );
	for ( TeamMemberList::iterator iter = members.begin(); iter != members.end(); ++iter )
	{
		packet->writeInt64( iter->nCharId );
		packet->writeUTF8( iter->strName );
		packet->writeInt16( iter->nIndex );
	}

	packet->setSize( packet->getWOffset() );
	packet->setProc( IM_SOCIAL_GAME_UPDATE_TEAM_INFO );
	SOCIAL_SERVICE.sendPacket( packet );
}

bool SocialPlayer::IsInTeam() const
{
	return m_pTeam != NULL;
}

bool SocialPlayer::IsAutoAcceptInvite() const
{
	return m_bAutoInvite;
}

bool SocialPlayer::IsAutoAcceptApply() const
{
	return m_bAutoApply;
}

bool SocialPlayer::CanAcceptInvite() const
{
	return m_bCanInvite;
}

bool SocialPlayer::CanAddFriend()  const
{
	return m_bCanAddFriend;
}

void SocialPlayer::AddInvite( Team* pTeam )
{
	if ( NULL == pTeam )
	{
		return;
	}
	TeamList::iterator iter = m_lstInvite.begin();
	TeamList::iterator eiter = m_lstInvite.end(); 
	for ( ; iter != eiter; ++iter )
	{
		Team* pTemp = *iter;
		if ( pTemp != NULL && pTemp == pTeam )
		{
			return;
		}
	}
	m_lstInvite.push_back( pTeam );
}

void SocialPlayer::SetTeam( Team* pTeam )
{
	m_pTeam = pTeam;
}

Team* SocialPlayer::GetTeam()
{
	return m_pTeam;
}

void SocialPlayer::AddXP( int32_t AddXp )
{
	if ( !IsLearnedXP() )
	{
		return;
	}
	if ( GetXPState() == XS_STOP )
	{
		return;
	}
	if ( AddXp > 0 )
	{
		m_nXP += AddXp;
	}
	else
	{
		m_nXP += ADD_XP_POINTS;
	}
	if ( m_nXP > MAX_XP_POINTS )
	{
		m_nXP = MAX_XP_POINTS;
	}
	SendGameUpdateXP();
}

int32_t SocialPlayer::GetXP() const
{
	return m_nXP;
}

int8_t SocialPlayer::GetXPState() const
{
	return m_nXPState;
}

int64_t SocialPlayer::GetXPAddExp() const
{
	return m_nXPAddExp;
}

bool SocialPlayer::IsLearnedXP() const
{
	return m_pInfo != NULL ? m_pInfo->bLearnedXP : false;
}

void SocialPlayer::ResetXP( int32_t nValue )
{
	if ( m_nXPState == XS_DO_SKILL )
	{
		return;
	}
	resetXP( nValue );
}

void SocialPlayer::resetXP( int32_t nValue )
{
	if ( !IsLearnedXP() )
	{
		return;
	}
	m_nXP			= nValue;
	m_nXPState		= XS_INCREACE;
	m_nXPAddExp		= 0;
	m_bJoinWithXP	= false;
	SendGameUpdateXP();
}

void SocialPlayer::SendGameUpdateXP()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeInt32( m_nXP );

	packet->setSize( packet->getWOffset() );
	packet->setProc( IM_SOCIAL_GAME_UPDATE_XP );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialPlayer::SendGameAddExp( int64_t nExp )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeInt64( nExp );

	packet->setSize( packet->getWOffset() );
	packet->setProc( IM_SOCIAL_GAME_ADD_XP );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialPlayer::SetJoinWithXP()
{
	m_bJoinWithXP = true;
}

TeamDungeon* SocialPlayer::GetTeamDungeon()
{
	return m_pTeamDungeon;
}

void SocialPlayer::SetTeamDungeon( TeamDungeon* pTeamDungeon )
{
	m_pTeamDungeon = pTeamDungeon;
	SendGameTeamDungeonUpdateInfo();
}

bool SocialPlayer::IsTeamDungeonReady()
{
	return m_bTeamDungeonReady;
}

bool SocialPlayer::IsInStall() const
{
	return m_bStall;
}

void SocialPlayer::SendGameTeamDungeonStart( int32_t nLine )
{
	// 发送游戏服组队副本开始 不在队长线路的玩家需要切换到创建线路
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );

	packet->writeInt32( nLine );

	packet->setSize( packet->getWOffset() );
	packet->setProc( IM_SOCIAL_GAME_TEAM_DUNGEON_START );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialPlayer::SendGameTeamDungeonUpdateInfo()
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );

	if ( m_pTeamDungeon != NULL )
	{
		packet->writeInt32( m_pTeamDungeon->GetId() );
		packet->writeInt32( m_pTeamDungeon->GetDungeonId() );
		packet->writeInt64( m_pTeamDungeon->GetLeader()->getCid() );
	}
	else
	{
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
	}

	packet->setSize( packet->getWOffset() );
	packet->setProc( IM_SOCIAL_GAME_TEAM_DUNGEON_UPDATE_INFO );
	SOCIAL_SERVICE.sendPacket( packet );
}

int32_t SocialPlayer::onTeamDungonRequestList(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nDungeonId = inPacket->readInt32();

	TEAM_DUNGEON_MANAGER.SendDungeonList( this, nDungeonId );
	return ERR_OK;
}

int32_t SocialPlayer::onTeamDungeonLeave(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeamDungeon )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pTeamDungeon->MemberLeave( this ) )
	{
		SendGameTeamDungeonUpdateInfo();
	}
	SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc() );
	return ERR_OK;
}

int32_t SocialPlayer::onTeamDungeonKick(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nMemberId = inPacket->readInt64();

	if ( NULL == m_pTeamDungeon )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pTeamDungeon->KickMember( this, nMemberId ) )
	{
		return ERR_INVALID_DATA;
	}
	SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc() );
	return ERR_OK;
}

int32_t SocialPlayer::onTeamDungeonReady(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	bReady = inPacket->readInt8();

	if ( NULL == m_pTeamDungeon )
	{
		return ERR_INVALID_DATA;
	}

	m_bTeamDungeonReady = ( bReady > 0 );
	m_pTeamDungeon->BroadcastMemberInfo();
	m_pTeamDungeon->CheckAutoStart();
	return ERR_OK;
}

int32_t SocialPlayer::onTeamDungeonSetAutoStart(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	bAuto = inPacket->readInt8();
	if ( NULL == m_pTeamDungeon )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pTeamDungeon->SetAutoStart( this, bAuto ) )
	{
		return ERR_INVALID_DATA;
	}
	m_pTeamDungeon->BroadcastMemberInfo();
	return ERR_OK;
}

int32_t SocialPlayer::onGameTeamDungeonStart(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeamDungeon )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pTeamDungeon->StartDungeon( this ) )
	{
		return ERR_INVALID_DATA;
	}
	return ERR_OK;
}

int32_t SocialPlayer::onGameTeamDungeonLeave(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( NULL == m_pTeamDungeon )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pTeamDungeon->MemberLeave( this ) )
	{
		return ERR_INVALID_DATA;
	}
	SOCIAL_SERVICE.replySuccess( m_cgindex, CM_TEAM_DUNGEON_LEAVE );
	return ERR_OK;
}

int32_t SocialPlayer::onGameTeamDungonCreate(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nDungeonId	= inPacket->readInt32();
	int32_t nLimitBattle= inPacket->readInt32();
	int32_t nLine		= inPacket->readInt32();
	if ( m_pTeamDungeon != NULL )
	{
		return ERR_INVALID_DATA;
	}

	m_pTeamDungeon = TEAM_DUNGEON_MANAGER.CreateTeamDungeon( this, nDungeonId, nLimitBattle, nLine );
	if ( NULL == m_pTeamDungeon )
	{
		return ERR_INVALID_DATA;
	}
	m_pTeamDungeon->BroadcastMemberInfo();
	SendGameTeamDungeonUpdateInfo();
	SOCIAL_SERVICE.replySuccess( m_cgindex, CM_TEAM_DUNGEON_CREATE );
	return ERR_OK;
}

int32_t SocialPlayer::onGameTeamDungonJoin(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nId = inPacket->readInt32();
	int32_t nDungeonId = inPacket->readInt32();
	if ( m_pTeamDungeon != NULL )
	{
		return ERR_INVALID_DATA;
	}

	m_bTeamDungeonReady = false;
	TeamDungeon* pDungeon = TEAM_DUNGEON_MANAGER.GetTeamDungeon( nId );
	if ( NULL == pDungeon )
	{
		SOCIAL_SERVICE.replyfailure( m_cgindex, inPacket->getProc(), ERR_TEAM_NOT_FIND );
		return ERR_INVALID_DATA;
	}

	if ( pDungeon->GetDungeonId() != nDungeonId )
	{
		return ERR_INVALID_DATA;
	}

	if ( GetBattle() < pDungeon->GetLimitBattle() )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pDungeon->MemberJoin( this ) )
	{
		SOCIAL_SERVICE.replyfailure( m_cgindex, inPacket->getProc(), ERR_TEAM_FULL );
		return ERR_INVALID_DATA;
	}

	SendGameTeamDungeonUpdateInfo();
	SOCIAL_SERVICE.replySuccess( m_cgindex, CM_TEAM_DUNGEON_JOIN );
	return ERR_OK;
}

int32_t SocialPlayer::OnAskItemLimitInfo( Answer::NetPacket *inPacket )
{
	NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == Packet)
	{
		return ERR_SYETEM_ERR;
	}
	SOCIAL_SERVICE.PacketItemLimitInfo( Packet );
	Packet->setType(PACK_DISPATCH);
	Packet->setProc(SM_SEND_ITEM_LIMIT_COUNT);
	Packet->setSize(Packet->getWOffset());
	SOCIAL_SERVICE.sendPacketTo( getGateIndex(), Packet);
	return ERR_OK;
}

int32_t SocialPlayer::OnBuyLimitItem( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t ShopId		= inPacket->readInt32();
	int32_t BuyCount	= inPacket->readInt32();
	CfgGameShop* pGameShop = SOCIAL_SERVICE.GetCfgGameShop( ShopId );
	if ( NULL == pGameShop )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pGameShop->LimitType != LIMIT_TYPE_SERVER )
	{
		return ERR_SYETEM_ERR;
	}
	if ( BuyCount <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t LimitCount = SOCIAL_SERVICE.GetLimitCount( ShopId );
	if ( LimitCount + BuyCount > pGameShop->LimitCount )
	{
		return ERR_SYETEM_ERR;
	}
	SendBuyItemCount( ShopId, BuyCount );
	return ERR_SYETEM_ERR;
}

void SocialPlayer::SendBuyItemCount( int32_t ShopId, int32_t AddCount )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( getuid() );
	packet->writeInt32( getsid() );
	packet->writeInt32( getGateIndex() );
	packet->writeInt32( ShopId );
	packet->writeInt32( AddCount );
	packet->setSize( packet->getWOffset() );
	packet->setProc( IM_SOCIAL_GAME_BUY_LIMIT_ITEM );
	SOCIAL_SERVICE.sendPacket( packet );
}

int32_t SocialPlayer::OnReceiveBuySucceed( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t ShopId		= inPacket->readInt32();
	int32_t BuyCount	= inPacket->readInt32();
	if ( BuyCount <= 0 || ShopId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	CfgGameShop* pGameShop = SOCIAL_SERVICE.GetCfgGameShop( ShopId );
	if ( NULL == pGameShop )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pGameShop->LimitType != LIMIT_TYPE_SERVER )
	{
		return ERR_SYETEM_ERR;
	}
	SOCIAL_SERVICE.AddLimitCount( ShopId, BuyCount );
	SendLimitItemCountChange( ShopId );
	return ERR_OK;
}

void SocialPlayer::SendLimitItemCountChange( int32_t ShopId )
{
	int32_t LimitCount = SOCIAL_SERVICE.GetLimitCount( ShopId );
	NetPacket *Packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == Packet)
	{
		return;
	}
	Packet->writeInt32( 1 );
	Packet->writeInt32( ShopId );
	Packet->writeInt32( LimitCount );
	Packet->setType(PACK_DISPATCH);
	Packet->setProc(SM_SEND_ITEM_LIMIT_COUNT);
	Packet->setSize(Packet->getWOffset());
	SOCIAL_SERVICE.worldBroadcast( Packet);
}

int32_t SocialPlayer::onWorship(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCharId = inPacket->readInt64();
	PlayerInfo* player = PLAYER_MANAGER.GetPlayerInfo( nCharId );
	if ( NULL == player )
	{
		return ERR_INVALID_DATA;
	}

	sendGameWorship( nCharId );
	return ERR_OK;
}

int32_t SocialPlayer::onRequestWorshipInfo(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCharId = inPacket->readInt64();
	PlayerInfo* player = PLAYER_MANAGER.GetPlayerInfo( nCharId );
	if ( NULL == player )
	{
		return ERR_INVALID_DATA;
	}

	notifyWorshipInfo( nCharId );
	return ERR_OK;
}

int32_t SocialPlayer::onGameWorship(Answer::NetPacket *inPacket)
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	CharId_t nCharId = inPacket->readInt64();
	PlayerInfo* player = PLAYER_MANAGER.GetPlayerInfo( nCharId );
	if ( NULL == player )
	{
		return ERR_INVALID_DATA;
	}

	++player->nWorshipRecord;
	SOCIAL_SERVICE.replySuccess( m_cgindex, CM_WORSHIP, nCharId );

	savePlayerWorshipRecord( nCharId, player->nWorshipRecord );
	return ERR_OK;
}

void SocialPlayer::sendGameWorship( CharId_t nCharId )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeInt64( nCharId );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_WORSHIP );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialPlayer::notifyWorshipInfo( CharId_t nCharId )
{
	PlayerInfo* player = PLAYER_MANAGER.GetPlayerInfo( nCharId );
	if ( NULL == player )
	{
		return;
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt64( nCharId );
	packet->writeUTF8( player->strName );
	packet->writeInt8( player->nSex );
	packet->writeInt8( player->nJob );
	packet->writeUInt32( player->nWeapon );
	packet->writeUInt32( player->nCloth );
	packet->writeInt32( player->nWorshipRecord );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_NOTIFY_WORSHIP_INFO );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( m_cgindex, packet );
}

void SocialPlayer::savePlayerWorshipRecord( CharId_t nCharId, int32_t nWorshipRecord )
{
	MySqlDBGuard db(DBPOOL);
	char szSQL[MAX_SQL_LENGTH] = "";
	snprintf( szSQL, sizeof(szSQL)-1, "UPDATE `mem_char_worship` SET `record`=%d WHERE `cid`=%lld", nWorshipRecord, nCharId );
	db.excute(szSQL);
}


int32_t	SocialPlayer::onAuctionSell( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t	nType		= inPacket->readInt8();
	int32_t nBagSlot	= inPacket->readInt32();
	int32_t	nCount		= inPacket->readInt32();
	int32_t nPrice		= inPacket->readInt32();
	if ( nPrice <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !AUCTION_MANAGER.CanSell( getCid(), nType ) )
	{
		return ERR_INVALID_DATA;
	}

	sendGameAuctionSell( nType, nBagSlot, nCount, nPrice );
	return ERR_OK;
}

int32_t SocialPlayer::onAuctionBuy( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t	nId = inPacket->readInt32();
	AuctionItem* pItem = AUCTION_MANAGER.GetAuctionItem( nId );
	if ( NULL == pItem )
	{
		SOCIAL_SERVICE.replyfailure( m_cgindex, inPacket->getProc(), ERR_AUCTION_ITEM_NOT_FIND, nId );	// 找不到道具
		return ERR_INVALID_DATA;
	}

	if ( pItem->nSeller == getCid() )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nPayType = CURRENCY_GOLD_ID;
	if ( pItem->nClass == IC_CURRENCY && pItem->nId == CURRENCY_GOLD_ID )
	{
		nPayType = CURRENCY_MONEY_ID;
	}

	sendGameAuctionBuy( nId, nPayType, pItem->nPrice );
	return ERR_OK;
}

int32_t SocialPlayer::onAuctionCancel( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nId = inPacket->readInt32();
	if ( !AUCTION_MANAGER.CancelItem( getCid(), nId ) )
	{
		return ERR_INVALID_DATA;
	}

	SOCIAL_SERVICE.replySuccess( m_cgindex, inPacket->getProc(), nId );
	return ERR_OK;
}

int32_t SocialPlayer::onAuctionItemList( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	AUCTION_MANAGER.SendItemList( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onAuctionSelfItems( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	AUCTION_MANAGER.SendSelfItems( *this );
	return ERR_OK;
}

int32_t SocialPlayer::onAuctionRecords( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	AUCTION_MANAGER.SendRecords( *this );
	return ERR_OK;
}

int32_t	SocialPlayer::onGameAuctionSell( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	AuctionItem item = {};
	item.nId		= inPacket->readInt32();
	item.nClass		= inPacket->readInt8();
	item.nCount		= inPacket->readInt32();
	item.nSrcId		= inPacket->readInt64();
	item.nPrice		= inPacket->readInt32();
	item.nEquipStar	= inPacket->readInt32();
	item.nSeller= getCid();

	int32_t nId = AUCTION_MANAGER.SellItem( getCid(), item );
	sendClientSellItem( nId, item );
	SOCIAL_SERVICE.replySuccess( m_cgindex, CM_AUCTION_SELL, nId );
	return ERR_OK;
}

void SocialPlayer::sendClientSellItem( int32_t nId, const AuctionItem& item )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( nId );
	packet->writeInt32( item.nId );
	packet->writeInt8( item.nClass );
	packet->writeInt32( item.nCount );
	packet->writeInt64( item.nSrcId );
	packet->writeInt32( item.nPrice );
	packet->writeInt32( item.nEquipStar );
	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_AUCTION_SELL_ITEM );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( m_cgindex, packet );
}

int32_t	SocialPlayer::onGameAuctionBuy( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t nId = inPacket->readInt32();
	AUCTION_MANAGER.BuyItem( getCid(), nId );
	SOCIAL_SERVICE.replySuccess( m_cgindex, CM_AUCTION_BUY, nId );
	return ERR_OK;
}

int32_t	SocialPlayer::onGameStall( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	m_bStall = ( inPacket->readInt8() != 0 );
	return ERR_OK;
}

void SocialPlayer::sendGameAuctionSell( int8_t nType, int32_t nBagSlot, int32_t nCount, int32_t nPrice )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeInt8( nType );
	packet->writeInt32( nBagSlot );
	packet->writeInt32( nCount );
	packet->writeInt32( nPrice );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_AUCTION_SELL );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialPlayer::sendGameAuctionBuy( int32_t nId, int8_t nPayType, int32_t nPrice )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeInt32( nId );
	packet->writeInt8( nPayType );
	packet->writeInt32( nPrice );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_AUCTION_BUY );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

int32_t SocialPlayer::onGameActivityNotifyFamilyWarInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t		nActId	 = inPacket->readInt32();
	FamilyId_t	nFamilyId = inPacket->readInt64();
	int32_t		nNextTime = inPacket->readInt32();
	int8_t		bDouble	  = inPacket->readInt8();

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return ERR_INVALID_DATA;
	}

	packet->writeInt32( nActId );
	packet->writeInt64( nFamilyId );
	packet->writeInt32( nNextTime );

	Family* pFamily = FAMILY_MANAGER.GetFamily( nFamilyId );
	if ( pFamily != NULL )
	{
		pFamily->AppendFamilyWarInfo( packet );
	}
	else
	{
		packet->writeUTF8( "" );
		packet->writeInt8( 0 );
	}
	packet->writeInt8( bDouble );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_NOTIFY_ACTIVITY_INFO );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacketTo( m_cgindex,  packet );
	return ERR_OK;
}

int32_t SocialPlayer::onGameActivityFamilyWarAddPillarMoney( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	FamilyId_t	nFamilyId	= inPacket->readInt64();
	int32_t		nMoney		= inPacket->readInt32();
	if ( nFamilyId != GetFamilyId() )
	{
		return ERR_INVALID_DATA;
	}

	Family* pFamily = FAMILY_MANAGER.GetFamily( nFamilyId );
	if ( NULL == pFamily )
	{
		return ERR_INVALID_DATA;
	}

	if ( !pFamily->DecFamilyMoney( nMoney ) )
	{
		SOCIAL_SERVICE.replyfailure( m_cgindex, CM_ACTIVITY_FAMILYWAR_ADD_PILLAR_MONEY, 1 );
		return ERR_INVALID_DATA;
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return ERR_INVALID_DATA;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );
	packet->writeInt32( nMoney );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_FAMILYWAR_PILLAR_ADD_MONEY );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
	return ERR_OK;
}


int32_t	SocialPlayer::onHallOfFameRankInfo( Answer::NetPacket *inPacket )
{
	return HALL_OF_FAME.OnRequestRankInfo( this, inPacket );
}

int32_t	SocialPlayer::onHallOfFameGetReward( Answer::NetPacket *inPacket )
{
	return HALL_OF_FAME.OnGetReward( this, inPacket );
}

int32_t	SocialPlayer::onGameHallOfFameFight( Answer::NetPacket *inPacket )
{
	return HALL_OF_FAME.OnFight( this, inPacket );
}

int32_t	SocialPlayer::onGameHallOfFameRequestInfo( Answer::NetPacket *inPacket )
{
	return HALL_OF_FAME.OnRequestInfo( this, inPacket );
}

int32_t	SocialPlayer::onGameHallOfFameRewardResult( Answer::NetPacket *inPacket )
{
	return HALL_OF_FAME.OnRewardResult( this, inPacket );
}

void SocialPlayer::SendGameFightResult( bool bWin )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );

	packet->writeInt8( bWin ? 1 : 0 );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_HALL_OF_FAME_FIGHT_RESULT );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialPlayer::SendGameGetHallOfFameRankReward( int32_t nIndex )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );

	packet->writeInt32( nIndex );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_HALL_OF_FAME_GET_REWARD );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}

void SocialPlayer::SendGameHallOfFameRankRewardInfo( int32_t nIndex, int8_t nReward )
{
	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( m_uid );
	packet->writeInt32( m_sid );
	packet->writeInt32( m_cgindex );

	packet->writeInt32( nIndex );
	packet->writeInt8( nReward );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_GAME_HALL_OF_FAME_RANK_REWARD_INFO );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );
}
