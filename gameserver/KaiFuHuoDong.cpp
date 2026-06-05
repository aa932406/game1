#include "stdafx.h"
#include "KaiFuHuoDong.h"
#include "Player.h"
#include "GameService.h"
#include "ActivityManager.h"
#include "Timer.h"
#include "ItemHelper.h"
#include "MapManager.h"
#include "Monster.h"
#include "PoolManager.h"
#include "DBService.h"

using namespace Answer;
#define LEVEL_REWARD_REWARD "LEVEL_REWARD_REWARD_"		//�ȼ�������ڱ��
enum KaiFuHuoDongType
{
	KFHDT_LEVEL_UP		= 1,		//��һ��ȼ�
	KFHDT_PET			= 2,		//�ڶ������
	KFHDT_JUN_TUAN		= 3,		//���������ս
	KFHDT_BATTLE		= 4,		//������ս����
};
struct CButtonState
{
	int32_t ButtonIndex;
	int8_t  ButtonState;
	int32_t Param;
	int32_t LiftTimes;
	int32_t Conditions;
};

struct KaiFuHuoDongState
{
	int8_t		HdState;
	int8_t		CanGetReward;
};
typedef std::map<int8_t,KaiFuHuoDongState> KFHD_SATATE;
enum ERR_VALUES
{
	EV_ALREADY_GET		= 1,	//����ȡ
	EV_BROUGHT_OUT		= 2,	//������
	EV_TIME_OUT			= 3,	//������ȡʱ����
	EV_NO_FINISH		= 4,	//δ���
};

CKaiFuHuoDong::CKaiFuHuoDong()
{
	m_PetRank.clear();
	m_BattleRank.clear();
	m_HDLastDay	= 0;
	m_KaiFuHuoDongCfg	= CFG_DATA.GetKaiFuHuoDongCfg();
	KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin();
	for ( ; it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( it->second.Conditions == KFHDC_PET_RANK )
		{
			m_PetRankEndDay			= it->second.EndDay + 1;
		}
		else if ( it->second.Conditions == KFHDC_BATTLE_RANK )
		{
			m_BattleRankEndDay		= it->second.EndDay + 1;
		}
		if ( it->second.EndDay > m_HDLastDay )
		{
			m_HDLastDay = it->second.EndDay;
		}
	}
	
}

void CKaiFuHuoDong::Init()
{
	LoadData();
}

CKaiFuHuoDong::~CKaiFuHuoDong()
{

}

int32_t	CKaiFuHuoDong::KaiFuHuoDongOperator( Player* pPlayer, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch ( inPacket->getProc() )
	{
	case CM_ASK_KAI_FU_HUO_DAO_INFO:
		{
			return AskInfo( pPlayer, inPacket );
		}
	case CM_GET_KAI_FU_HUO_DAO_WARD:
		{
			return OnGetReward( pPlayer, inPacket );
		}
	case CM_ASK_KAI_FU_HUO_DONG_STATE:
		{
			 SendHuoDongState(pPlayer);
			 break;
		}
	default:
		return ERR_SYETEM_ERR;
	}
	return ERR_SYETEM_ERR;
}

int32_t CKaiFuHuoDong::OnGetReward( Player* pPlayer, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t Index = inPacket->readInt32();
	if ( CanGetReward( pPlayer,Index ) != ERR_OK )
	{
		return ERR_SYETEM_ERR;
	}
	KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.find( Index );
	if ( it == m_KaiFuHuoDongCfg.end() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pPlayer->GetBag().AddItemsAndEggs( it->second.ItemVector,IACR_KAI_FU_HUO_DONG ) )
	{
		if ( it->second.Conditions == KFHDC_LEVEL_UP )
		{
			AddLimitCount( GetLevelLimitString( it->second.Parm1 ) ,1 );
		}
		AddRewardRecord( pPlayer,Index );
		SendHuoDongState(pPlayer);
		SendHuoDongInfo(pPlayer, it->second.Type );
		SendKaiFuHuoDongIcon( pPlayer );
	}
	return ERR_OK;
}

void CKaiFuHuoDong::SendHuoDongState( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	KFHD_SATATE HDState;
	KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin();
	for ( ; it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( GetDiffDay() >= it->second.StartDay && GetDiffDay() <= it->second.EndDay )
		{
			HDState[it->second.Type].HdState = 1;
		}
		else if( GetDiffDay() > it->second.EndDay )
		{
			HDState[it->second.Type].HdState = 2;
		}
		else
		{
			HDState[it->second.Type].HdState = 0;
		}
		if ( CanGetReward( pPlayer, it->first ) == ERR_OK )
		{
			HDState[it->second.Type].CanGetReward++;
		}
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SEND_KAI_FU_HUO_DONG_STATE);
	if (NULL == packet)
	{
		return;
	}
	int32_t nSize = (int8_t)HDState.size();
	packet->writeInt8( nSize );
	KFHD_SATATE::iterator Hdit = HDState.begin();
	for ( ; Hdit != HDState.end(); ++Hdit )
	{
		packet->writeInt8( Hdit->first);
		packet->writeInt8( Hdit->second.HdState );
		packet->writeInt8( Hdit->second.CanGetReward );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);
}

void CKaiFuHuoDong::AddRewardRecord( Player* pPlayer, int32_t Index )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	int32_t OldRecord = pPlayer->getRecord( RP_KAI_FU_HUO_DONG_REWARD );
	int32_t NewRecord = OldRecord | ( 1 << ( Index - 1 ) ); 
	pPlayer->updateRecord( RP_KAI_FU_HUO_DONG_REWARD, NewRecord );
}

int32_t CKaiFuHuoDong::CanGetReward( Player* pPlayer, int32_t Index )
{
	if ( NULL == pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.find( Index );
	if ( it == m_KaiFuHuoDongCfg.end() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetDiffDay() < it->second.GetRewardDay )
	{
		return EV_TIME_OUT;
	}
	if ( IsAlreadyGet( pPlayer, Index ) )
	{
		return EV_ALREADY_GET;
	}
	return GetRewardState( pPlayer, it->second.Conditions, it->second.Parm1,it->second.Parm2, it->second.LimitCount );
}

bool CKaiFuHuoDong::IsAlreadyGet( Player* pPlayer,int32_t Index )
{
	if ( NULL == pPlayer )
	{
		return true;
	}
	int32_t RewardRecord = pPlayer->getRecord( RP_KAI_FU_HUO_DONG_REWARD );
	if ( ( ( RewardRecord >> ( Index -1 ) ) & 1 ) <= 0 )
	{
		return false;
	}
	return true;
}

int32_t CKaiFuHuoDong::GetLimitCount( std::string LimitString )
{
	if ( LimitString.empty() )
	{
		return 1000000;
	}
	MySqlDBGuard db(DBPOOL);
	char mySql[1024]={0};
	snprintf(mySql,1023,"SELECT `value` FROM `sys_server_config` WHERE `name`='%s'",LimitString.c_str() );
	MySqlQuery result = db.query(mySql);
	if ( !result.eof() )
	{
		return atoi( result.getStringValue(0) );
	}
	else
	{
		return 0;
	}
}

void CKaiFuHuoDong::AddLimitCount( std::string LimitString, int32_t Values )
{
	MySqlDBGuard db(DBPOOL);
	char mySql[1024]={0};
	snprintf(mySql,1023,"SELECT `value` FROM `sys_server_config` WHERE `name`='%s'",LimitString.c_str() );
	MySqlQuery result = db.query(mySql);
	if ( result.eof() )
	{
		char mySql[1024]={0};
		snprintf(mySql,1023,"INSERT INTO `sys_server_config` (`name`,`value`) VALUES('%s','%d')",LimitString.c_str(),Values);
		db.excute(mySql);
	}
	else
	{
		char mySql[1024]={0};
		snprintf(mySql,1023,"UPDATE `sys_server_config` SET `value`= value + %d WHERE `name`='%s'",Values, LimitString.c_str() );
		db.excute(mySql);
	}
}

std::string CKaiFuHuoDong::GetLevelLimitString( int32_t Level )
{
	std::stringstream ss;
	ss	<< LEVEL_REWARD_REWARD << Level;
	return ss.str();
}

int32_t CKaiFuHuoDong::GetRewardState( Player* pPlayer, int32_t Conditions, int32_t Param1, int32_t Param2, int32_t LimitCount )
{
	if ( NULL == pPlayer )
	{
		return false;
	}
	switch( Conditions )
	{
	case KFHDC_LEVEL_UP:
		{
			if ( GetLimitCount( GetLevelLimitString( Param1 ) ) >= LimitCount )
			{
				return EV_BROUGHT_OUT;
			}
			if ( pPlayer->getRecord( RP_KAI_FU_HUO_DONG_LEVEL ) >= Param1 )
			{
				return ERR_OK;
			}
			break;
		}
	case KFHDC_PET_RANK:
		{
			KaiFuHuoDongRank::iterator itRank =	m_PetRank.begin();
			for ( ; itRank != m_PetRank.end(); ++itRank )
			{
				if ( itRank->second.CharId == pPlayer->getCid() )
				{
					if ( Param1 <= itRank->first && Param2 >= itRank->first )
					{
						return ERR_OK;
					}
				}
			}
			break;
		}
	case KFHDC_PET_POINT:
		{
			if ( pPlayer->getRecord( RP_KAI_FU_HUO_DONG_PET_POINT ) >= Param1 )
			{
				return ERR_OK;
			}
			break;
		}
	case KFHDC_JUN_TUAN_LEADER:
		{
			if ( pPlayer->getRecord(RP_FIRST_JUN_TUAN_ZHAN_STATE) == 1 )
			{
				return ERR_OK;
			}
			break;
		}
	case KFHDC_JUN_TUAN_WIN:
		{
			if ( pPlayer->getRecord(RP_FIRST_JUN_TUAN_ZHAN_STATE) == 2 || pPlayer->getRecord(RP_FIRST_JUN_TUAN_ZHAN_STATE) == 1 )
			{
				return ERR_OK;
			}
			break;
		}
	case KFHDC_FAMILY_WAR_JOIN:
		{
			if ( pPlayer->getRecord(RP_FIRST_JUN_TUAN_ZHAN_STATE) > 0 )
			{
				return ERR_OK;
			}
			break;
		}
	case KFHDC_BATTLE_RANK:
		{
			KaiFuHuoDongRank::iterator itRank =	m_BattleRank.begin();
			for ( ; itRank != m_BattleRank.end(); ++itRank )
			{
				if ( itRank->second.CharId == pPlayer->getCid() )
				{
					if ( Param1 <= itRank->first && Param2 >= itRank->first )
					{
						return ERR_OK;
					}
				}
			}
			break;
		}
	case KFHDC_BATTLE_POINT:
		{
			if ( pPlayer->getRecord( RP_KAI_FU_HUO_DONG_BATTLE ) >= Param1 )
			{
				return ERR_OK;
			}
			break;
		}
	default:
		return EV_NO_FINISH;
	}
	return EV_NO_FINISH;
}

void CKaiFuHuoDong::SendHuoDongInfo( Player* pPlayer,int8_t Type )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	std::list<CButtonState> Buttons; 
	KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin();
	for ( ; it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( it->second.Type == Type )
		{
			CButtonState stu = {};
			stu.ButtonIndex = it->first;
			stu.ButtonState =  CanGetReward( pPlayer, it->first);
			stu.LiftTimes	= it->second.LimitCount;
			stu.Param		= it->second.Parm1;
			stu.Conditions	= it->second.Conditions;
			Buttons.push_back( stu );
		}
	}
	if ( Buttons.size() <= 0 )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_DISPATCH, SM_SEND_KAI_FU_HUO_DONG_INFO);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8(Type);
	int32_t Size = Buttons.size();
	packet->writeInt32( Size );
	std::list<CButtonState>::iterator ButtonIt = Buttons.begin();
	for ( ; ButtonIt != Buttons.end(); ++ButtonIt )
	{
		packet->writeInt32( ButtonIt->ButtonIndex );
		packet->writeInt8( ButtonIt->ButtonState );
		if ( Type == KFHDT_JUN_TUAN )
		{
			if ( ButtonIt->Conditions == KFHDC_JUN_TUAN_LEADER )
			{
				std::string LeaderName = ACTIVITY_MANAGER.GetFamilyWarLeaderName();
				packet->writeUTF8( LeaderName );
			}
			else if ( ButtonIt->Conditions == KFHDC_JUN_TUAN_WIN )
			{
				std::string FamilyName = ACTIVITY_MANAGER.GetFamilyWarWinnerName();
				packet->writeUTF8( FamilyName );
			}
			else
			{
				packet->writeUTF8( "0" );
			}

		}
		if ( Type == KFHDT_LEVEL_UP )
		{
			int32_t LiftTime = ButtonIt->LiftTimes - GetLimitCount( GetLevelLimitString( ButtonIt->Param ) );
			packet->writeInt32( LiftTime);
		}
	}

	if ( Type == KFHDT_PET )
	{
		int32_t nSize = m_PetRank.size();
		packet->writeInt32( nSize );
		KaiFuHuoDongRank::iterator itRank = m_PetRank.begin();
		for ( ; itRank != m_PetRank.end(); itRank++ )
		{
			packet->writeInt32( itRank->first );
			packet->writeInt64( itRank->second.CharId );
			packet->writeUTF8( itRank->second.CharName );
			packet->writeInt8( itRank->second.CharJob );
			packet->writeInt8( itRank->second.CharSex );
			packet->writeInt32( itRank->second.Param );
		}
	}
	else if ( Type == KFHDT_BATTLE )
	{
		int32_t nSize = m_BattleRank.size();
		packet->writeInt32( nSize );
		KaiFuHuoDongRank::iterator itRank = m_BattleRank.begin();
		for ( ; itRank != m_BattleRank.end(); itRank++ )
		{
			packet->writeInt32( itRank->first );
			packet->writeInt64( itRank->second.CharId );
			packet->writeUTF8( itRank->second.CharName );
			packet->writeInt8( itRank->second.CharJob );
			packet->writeInt8( itRank->second.CharSex );
			packet->writeInt32( itRank->second.Param );
		}
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);	
}

int32_t CKaiFuHuoDong::AskInfo( Player* pPlayer, Answer::NetPacket *inPacket )
{
	if ( NULL == pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t Type = inPacket->readInt8();

	SendHuoDongInfo( pPlayer ,Type );
	return ERR_OK;
}

void CKaiFuHuoDong::RecvRank( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}
	int32_t DiffDay = GetDiffDay();
	int8_t	RankType	= inPacket->readInt8();
	int32_t Minutes		= inPacket->readInt32();
	if ( RankType == 1 )
	{
		if ( DiffDay < m_PetRankEndDay || ( DiffDay == m_PetRankEndDay && Minutes == 0 ) )
		{
			int32_t Count = inPacket->readInt32();
			for ( int32_t i = 0; i < Count; i++ )
			{
				RankInfo stu = {};
				int32_t Rand	= inPacket->readInt32();
				stu.CharId		= inPacket->readInt64();
				stu.CharName	= inPacket->readUTF8(true);
				stu.CharJob		= inPacket->readInt8();
				stu.CharSex		= inPacket->readInt8();
				stu.Param		= inPacket->readUInt32();
				m_PetRank[Rand] = stu;
			}
		}
	}
	else
	{
		if ( DiffDay < m_BattleRankEndDay || ( DiffDay == m_PetRankEndDay && Minutes == 0 ) )
		{
			int32_t Count = inPacket->readInt32();
			for ( int32_t i = 0; i < Count; i++ )
			{
				RankInfo stu = {};
				int32_t Rand	= inPacket->readInt32();
				stu.CharId		= inPacket->readInt64();
				stu.CharName	= inPacket->readUTF8(true);
				stu.CharJob		= inPacket->readInt8();
				stu.CharSex		= inPacket->readInt8();
				stu.Param		= inPacket->readUInt32();
				m_BattleRank[Rand] = stu;
			}
		}
	}
}

void CKaiFuHuoDong::UpdateHDData( Player* pPlayer,KaiFuHuoDongCondition Type, int32_t Values )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	int32_t EndDay = 0;
	KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin();
	for ( ; it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( it->second.Conditions == Type )
		{
			EndDay	= it->second.EndDay;
			break;
		}
	}
	if ( EndDay <= 0 )
	{
		return;
	}
	if ( EndDay < GetDiffDay() )
	{
		return;
	}
	bool NeedSyn = false;
	switch( Type )
	{
	case KFHDC_LEVEL_UP:
		{
			pPlayer->updateRecord( RP_KAI_FU_HUO_DONG_LEVEL, Values );
			NeedSyn = true;
			break;
		}
	case KFHDC_PET_POINT:
		{
			if ( pPlayer->getRecord( RP_KAI_FU_HUO_DONG_PET_POINT ) < Values )
			{
				pPlayer->updateRecord( RP_KAI_FU_HUO_DONG_PET_POINT, Values );
				NeedSyn = true;
			}
			break;
		}
	case KFHDC_BATTLE_POINT:
		{
			if ( pPlayer->getRecord( RP_KAI_FU_HUO_DONG_BATTLE ) < Values )
			{
				pPlayer->updateRecord( RP_KAI_FU_HUO_DONG_BATTLE, Values );
				NeedSyn = true;
			}
			break;
		}
	default:
		break;
	}
	if ( NeedSyn )
	{
		SendKaiFuHuoDongIcon( pPlayer );
	}
}

void CKaiFuHuoDong::LoadData()
{
 	MySqlDBGuard db(DBPOOL);
 	char mySql[1024]={0};
 	snprintf(mySql,1023,"SELECT * FROM `mem_kai_fu_huo_dong` ");
 	MySqlQuery result = db.query(mySql);
 	while ( !result.eof() )
 	{
		RankInfo stu = {};
		int32_t Rank				= result.getIntValue("Rank");
		int32_t Type				= result.getIntValue("Type");
		stu.CharId					= result.getInt64Value("CharId");
		stu.CharName				= result.getStringValue("CharName");
		stu.CharJob					= result.getIntValue("CharJob");
		stu.CharSex					= result.getIntValue("CharSex");
		stu.Param					= result.getIntValue("Param");
		if ( Type == 1 )
		{
			m_PetRank[Rank]	= stu;
		}
		else
		{
			m_BattleRank[Rank] = stu;
		}
 		result.nextRow();
 	}
}

void CKaiFuHuoDong::SaveData()
{
	if ( GAME_SERVICE.getLine() != 1 )
	{
		return;
	}
	char szSQL[MAX_SQL_LENGTH] = "TRUNCATE mem_kai_fu_huo_dong";
	MySqlDBGuard db(DBPOOL);
	db.excute(szSQL);

	KaiFuHuoDongRank::iterator it = m_PetRank.begin();
	for ( ; it != m_PetRank.end(); ++it )
	{
		bzero( szSQL, sizeof(szSQL) );
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO mem_kai_fu_huo_dong ( Rank, Type, CharId,CharName, CharJob, CharSex, Param) VALUES (%d, %d,%lld,'%s',%d, %d,%d) ",\
			it->first,
			1,
			it->second.CharId,
			it->second.CharName.c_str(),
			it->second.CharJob,
			it->second.CharSex,
			it->second.Param);
		db.excute(szSQL);
	}

	KaiFuHuoDongRank::iterator bIt = m_BattleRank.begin();
	for ( ; bIt != m_BattleRank.end(); ++bIt )
	{
		bzero( szSQL, sizeof(szSQL) );
		snprintf(szSQL, sizeof(szSQL)-1, "INSERT INTO mem_kai_fu_huo_dong ( Rank, Type, CharId,CharName, CharJob, CharSex, Param) VALUES (%d, %d,%lld,'%s',%d, %d,%d) ",\
			bIt->first,
			2,
			bIt->second.CharId,
			bIt->second.CharName.c_str(),
			bIt->second.CharJob,
			bIt->second.CharSex,
			bIt->second.Param);
		db.excute(szSQL);
	}
}

int32_t CKaiFuHuoDong::GetDiffDay()
{
	int32_t DiffDay = CFG_DATA.getServerDiffTime() + 1;
	return DiffDay;
}

void CKaiFuHuoDong::GetKaiFuHuoDongIcon( Player* pPlayer, IconStateList& IconList )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	if ( !pPlayer->GetPlayerFunctionOpen().IsOpened( FT_KAI_FU_HUO_DONG ) )
	{
		return;
	}
	if ( GetDiffDay() > m_HDLastDay + 2 )
	{
		return;
	}
	IconList.push_back( GetKaiFuHuoDongIconStu( pPlayer ) );
}

void CKaiFuHuoDong::SendKaiFuHuoDongIcon( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	if ( !pPlayer->GetPlayerFunctionOpen().IsOpened( FT_KAI_FU_HUO_DONG ) )
	{
		return;
	}
 	if ( GetDiffDay() > m_HDLastDay + 2 )
 	{
 		return;
 	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetKaiFuHuoDongIconStu( pPlayer );

	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);	
}

ShowIcon CKaiFuHuoDong::GetKaiFuHuoDongIconStu( Player *pPlayer )
{	
	ShowIcon stu = {};
	if ( NULL == pPlayer )
	{
		return stu;
	}

	stu.nId			= KAI_FU_HUO_DONG_ID;
	if ( GetDiffDay() > m_HDLastDay + 2 )
	{
		stu.nState		= AS_TIME_OUT;
	}
	else
	{
		stu.nState		= AS_RUNNING;
	}
	stu.nLeftTime	= -1;
	if ( GetDiffDay() > m_HDLastDay )
	{
		stu.Effects		= 0;
	}
	else
	{
		stu.Effects		= 1;
	}
	
	stu.IconLeft	= 0;
	KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin();
	for ( ; it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( CanGetReward( pPlayer, it->first ) == ERR_OK )
		{
			stu.IconRight++;
		}
	}

	return stu;
}
// ========== Missing methods from decompiled code ==========

bool CKaiFuHuoDong::InTime()
{
	return CFG_DATA.getServerType() != 1 && GetDaysFromServerStart() <= m_HDLastDay;
}

int32_t CKaiFuHuoDong::GetDaysFromServerStart()
{
	if ( CFG_DATA.isUniteServer() )
	{
		return 99999;
	}
	int32_t DiffDay = CFG_DATA.getServerDiffDay( 0 ) + 1;
	if ( DiffDay > 0 )
	{
		return DiffDay;
	}
	return 99999;
}

void CKaiFuHuoDong::GongGao( Player* pPlayer, int32_t GongGaoId, int32_t Index )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( GongGaoId );
	packet->writeInt64( pPlayer->getCid() );
	packet->writeUTF8( pPlayer->getName() );
	packet->writeInt32( Index );
	packet->setSize( packet->getWOffset() );
	packet->setProc( SM_SEND_NOTICE_PARAM );
	GAME_SERVICE.worldBroadcast( packet );
}

int32_t CKaiFuHuoDong::GetLimitCount( int32_t index )
{
	std::stringstream ss;
	ss << "KAI_FU_LIMIT_" << index;
	MySqlDBGuard db(DBPOOL);
	char mySql[1024] = {0};
	snprintf( mySql, 1023, "SELECT `value` FROM `sys_server_config` WHERE `name`='%s'", ss.str().c_str() );
	MySqlQuery result = db.query( mySql );
	if ( !result.eof() )
	{
		return atoi( result.getStringValue(0) );
	}
	return 0;
}

void CKaiFuHuoDong::AddLimitCount( int32_t index, int32_t Values )
{
	std::stringstream ss;
	ss << "KAI_FU_LIMIT_" << index;
	MySqlDBGuard db(DBPOOL);
	char mySql[1024] = {0};
	snprintf( mySql, 1023, "SELECT `value` FROM `sys_server_config` WHERE `name`='%s'", ss.str().c_str() );
	MySqlQuery result = db.query( mySql );
	char mySql_0[1024] = {0};
	if ( result.eof() )
	{
		snprintf( mySql_0, 1023, "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('%s','%d')", ss.str().c_str(), Values );
	}
	else
	{
		snprintf( mySql_0, 1023, "UPDATE `sys_server_config` SET `value`= value + %d WHERE `name`='%s'", Values, ss.str().c_str() );
	}
	db.excute( mySql_0 );
}

int32_t CKaiFuHuoDong::HaveRewardCount( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return 0;
	}
	int32_t Count = 0;
	for ( KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin(); it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		int32_t Day = GetDaysFromServerStart();
		if ( Day < it->second.StartDay || Day > it->second.EndDay )
		{
			continue;
		}
		if ( IsAlreadyGet( pPlayer, it->first ) )
		{
			continue;
		}
		switch ( it->second.Type )
		{
		case 4: // Level up
			if ( pPlayer->getLevel() >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.LimitCount )
					++Count;
			}
			break;
		case 5: // Wing level
			if ( /* TODO: Wing module not ported */ 0 /* pPlayer->GetCharWing().GetLevel() */ >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.LimitCount )
					++Count;
			}
			break;
		case 10: // Record 1150
			if ( pPlayer->getRecord( 1150 ) >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.LimitCount )
					++Count;
			}
			break;
		case 11: // JueWei
			if ( pPlayer->GetPlayerJueWei().GetJueWei() >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.LimitCount )
					++Count;
			}
			break;
		case 12: // Equip level
			if ( pPlayer->GetEquip().IsAllPosLevel() >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.LimitCount )
					++Count;
			}
			break;
		case 13: // FaBao level
			if ( pPlayer->GetPlayerFaBao().GetFaBaoLevel( 3 ) >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.LimitCount )
					++Count;
			}
			break;
		case 17: // Flop draw
			{
				int32_t MaxFlopTimes = GetMaxFlopTimes( pPlayer );
				int32_t FlopCount = MaxFlopTimes - pPlayer->getRecord( 2130 );
				if ( FlopCount > 0 )
					Count += FlopCount;
			}
			break;
		default:
			break;
		}
	}
	return Count;
}

void CKaiFuHuoDong::OnKilledMonster( Player* pPlayer, int32_t Mid )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	int32_t Day = GetDaysFromServerStart();
	for ( KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin(); it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( it->second.Type == 8 && it->second.StartDay <= Day && it->second.EndDay >= Day )
		{
			std::map<int32_t,BossFirstKilled>::iterator bit = m_BossFirstKilledMap.find( Mid );
			if ( bit == m_BossFirstKilledMap.end() )
			{
				BossFirstKilled stu;
				stu.BossId = Mid;
				stu.Killer = pPlayer->getCid();
				stu.KillerName = pPlayer->getName();
				stu.KillTime = pPlayer->getNow();
				m_BossFirstKilledMap[Mid] = stu;
				GongGao( pPlayer, 0, Mid );
			}
			break;
		}
	}
}

void CKaiFuHuoDong::OnUpdateKilledMonster( int32_t Mid, CharId_t cid, const std::string& Name, int32_t KillTime )
{
	Answer::MutexGuard lock( m_Lock );
	std::map<int32_t,BossFirstKilled>::iterator it = m_BossFirstKilledMap.find( Mid );
	if ( it != m_BossFirstKilledMap.end() )
	{
		it->second.Killer = cid;
		it->second.KillerName = Name;
		it->second.KillTime = KillTime;
	}
}

void CKaiFuHuoDong::SendBossFirstKillInfo( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CED );
	if ( NULL == packet )
	{
		return;
	}
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,BossFirstKilled>::iterator it = m_BossFirstKilledMap.begin(); it != m_BossFirstKilledMap.end(); ++it )
	{
		if ( it->second.Killer > 0 )
		{
			packet->writeInt32( it->second.BossId );
			packet->writeUTF8( it->second.KillerName );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
}

bool CKaiFuHuoDong::HaveTeHuiGift( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return false;
	}
	for ( KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin(); it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( it->second.Type == 1 && !IsAlreadyGet( pPlayer, it->first ) )
		{
			return true;
		}
	}
	return false;
}

bool CKaiFuHuoDong::HaveBuyPetItem( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return false;
	}
	for ( KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin(); it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( it->second.Type == 2 && IsAlreadyGet( pPlayer, it->first ) )
		{
			return true;
		}
	}
	return false;
}

void CKaiFuHuoDong::GetKaiFuPetIcon( Player* pPlayer, IconStateList& IconList )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	if ( CFG_DATA.isUniteServer() )
	{
		return;
	}
	if ( !pPlayer->GetPlayerFunctionOpen().IsOpened( FT_KAI_FU_HUO_DONG ) )
	{
		return;
	}
	int32_t Day = GetDaysFromServerStart();
	if ( GetKaiFuPetEndDay() >= Day && GetKaiFuPetStartDay() <= Day )
	{
		IconList.push_back( GetKaiFuHuoDongIconStu( pPlayer ) );
	}
}

void CKaiFuHuoDong::SendKaiFuPetIcon( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return;
	}
	if ( CFG_DATA.isUniteServer() )
	{
		return;
	}
	if ( !pPlayer->GetPlayerFunctionOpen().IsOpened( FT_KAI_FU_HUO_DONG ) )
	{
		return;
	}
	// Send icon manually since Player::SendIconState is not available
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetKaiFuHuoDongIconStu( pPlayer );
	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(pPlayer->getGateIndex(), packet);
}

int32_t CKaiFuHuoDong::GetKaiFuPetStartDay()
{
	for ( KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin(); it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( it->second.Type == 2 )
		{
			return it->second.StartDay;
		}
	}
	return 0;
}

int32_t CKaiFuHuoDong::GetKaiFuPetEndDay()
{
	for ( KaiFuHuoDongCfg::iterator it = m_KaiFuHuoDongCfg.begin(); it != m_KaiFuHuoDongCfg.end(); ++it )
	{
		if ( it->second.Type == 2 )
		{
			return it->second.EndDay;
		}
	}
	return 0;
}

int32_t CKaiFuHuoDong::GetFlopType( int32_t nFlopId )
{
	if ( nFlopId >= 0 && m_FlopSize > nFlopId )
	{
		return m_FlopType[nFlopId];
	}
	return 0;
}

bool CKaiFuHuoDong::CanFlopDraw( Player* pPlayer, int32_t FlopId )
{
	if ( NULL == pPlayer )
	{
		return false;
	}
	int32_t Day = GetDaysFromServerStart();
	if ( Day < m_FlopStartTime || Day > m_FlopEndTime )
	{
		return false;
	}
	if ( FlopId < 0 || m_FlopSize <= FlopId )
	{
		return false;
	}
	// Check cost items
	if ( m_FlopCost[FlopId].m_nId > 0 )
	{
		if ( !pPlayer->GetBag().RemoveItem( m_FlopCost[FlopId], IDCR_FLOP ) )
		{
			return false;
		}
	}
	// Type 4 is free draw
	if ( m_FlopType[FlopId] == 4 )
	{
		return true;
	}
	int32_t FlopTimes = pPlayer->getRecord( 2130 );
	int32_t MaxTimes = GetMaxFlopTimes( pPlayer );
	if ( FlopTimes >= MaxTimes )
	{
		int32_t BuyTimes = pPlayer->getRecord( 2129 );
		if ( Day == m_FlopEndTime || m_FlopBuyTimes > BuyTimes )
		{
			int32_t NeedCost = 500 * ( BuyTimes + 1 );
			if ( NeedCost > 0 )
			{
				if ( pPlayer->DecCurrency( CURRENCY_GOLD, NeedCost, GCR_FLOP, 0 ) )
				{
					pPlayer->GetOperateLimit().AddLimitCount( 2129, 1 );
					pPlayer->GetOperateLimit().AddLimitCount( 2130, 1 );
					return true;
				}
			}
			return false;
		}
		return false;
	}
	else
	{
		pPlayer->GetOperateLimit().AddLimitCount( 2130, 1 );
		return true;
	}
}

int32_t CKaiFuHuoDong::GetMaxFlopTimes( Player* pPlayer )
{
	if ( NULL == pPlayer )
	{
		return 0;
	}
	int32_t Times = m_FlopFreeTimes;
	if ( pPlayer->GetTodayPayGold() > 0 )
	{
		++Times;
	}
	return pPlayer->getRecord( 2129 ) + Times;
}

// ========== New methods from COpenBeta ==========

void CKaiFuHuoDong::Init( int32_t line )
{
	if ( GAME_SERVICE.getLine() == 9 )
	{
		return;
	}
	
	m_nMinute = TIMER.GetLocalNow().tm_hour * 60 + TIMER.GetLocalNow().tm_min;
	
	Answer::Inifile ini;
	ini.parse( "./ServerConfig/Tables/OpenBetaAct.cfg" );
	
	// CONFIG section
	m_nStartDay = Answer::DayTime::StringToIntTime( ini.getStrValue( "CONFIG", "start_time" ) );
	m_nEndDay = ini.getIntValue( "CONFIG", "end_day" );
	m_nIcon = ini.getIntValue( "CONFIG", "icon" );
	
	int32_t now = Answer::DayTime::now();
	int32_t dayzero = Answer::DayTime::dayzero( now );
	m_nDay = ( dayzero - Answer::DayTime::dayzero( m_nStartDay ) ) / 86400;
	
	// RECHARGE section
	m_vStartDay[2] = ini.getIntValue( "RECHARGE", "start_day" );
	m_vEndDay[2] = ini.getIntValue( "RECHARGE", "end_day" );
	m_nRechargeDaysSize = ini.getIntValue( "RECHARGE", "size" );
	m_vRechargeValue.reserve( m_nRechargeDaysSize );
	m_vRechargeGift.reserve( m_nRechargeDaysSize );
	for ( int32_t i = 0; i < m_nRechargeDaysSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "gold%d", i + 1 );
		m_vRechargeValue.push_back( ini.getIntValue( "RECHARGE", szCol ) );
		
		snprintf( szCol, 63, "gift%d", i + 1 );
		MemChrBagVector items = CItemHelper::parseItemVectorString( ini.getStrValue( "RECHARGE", szCol ) );
		m_vRechargeGift.push_back( items );
	}
	
	// CHOU_JIANG section
	m_vStartDay[4] = ini.getIntValue( "CHOU_JIANG", "start_day" );
	m_vEndDay[4] = ini.getIntValue( "CHOU_JIANG", "end_day" );
	m_ChouJiangType = ini.getIntValue( "CHOU_JIANG", "Type" );
	
	// COLLECT_DROP section
	m_vStartDay[8] = ini.getIntValue( "COLLECT_DROP", "start_day" );
	m_vEndDay[8] = ini.getIntValue( "COLLECT_DROP", "end_day" );
	
	// BOSS section
	m_vStartDay[9] = ini.getIntValue( "BOSS", "start_day" );
	m_vEndDay[9] = ini.getIntValue( "BOSS", "end_day" );
	m_nBossIcon = ini.getIntValue( "BOSS", "icon" );
	m_nBossStartBroadcast = ini.getIntValue( "BOSS", "start_broadcast" );
	m_nBossEndBroadcast = ini.getIntValue( "BOSS", "end_broadcast" );
	m_nBossKillBroadcast = ini.getIntValue( "BOSS", "kill_broadcast" );
	int32_t nBossCount = ini.getIntValue( "BOSS", "count" );
	m_vBossMinute.reserve( nBossCount );
	for ( int32_t i = 0; i < nBossCount; ++i )
	{
		char szCol[64] = {0};
		TimeArea tarea;
		snprintf( szCol, 63, "start_minute%d", i + 1 );
		tarea.nStartTime = ini.getIntValue( "BOSS", szCol );
		snprintf( szCol, 63, "end_minute%d", i + 1 );
		tarea.nEndTime = ini.getIntValue( "BOSS", szCol );
		m_vBossMinute.push_back( tarea );
	}
	m_MapId = ini.getIntValue( "BOSS", "mapid" );
	m_X = ini.getIntValue( "BOSS", "x" );
	m_Y = ini.getIntValue( "BOSS", "y" );
	m_Mid = ini.getIntValue( "BOSS", "mid" );
	
	// DAILY_LIMIT_SHOP section
	m_vStartDay[3] = ini.getIntValue( "DAILY_LIMIT_SHOP", "start_day" );
	m_vEndDay[3] = ini.getIntValue( "DAILY_LIMIT_SHOP", "end_day" );
	m_nDailyLimitShopSize = ini.getIntValue( "DAILY_LIMIT_SHOP", "size" );
	m_vDailyLimitShopGoods.resize( m_nDailyLimitShopSize );
	m_vDailyLimitShopBroadcast.resize( m_nDailyLimitShopSize, 0 );
	for ( int32_t i = 0; i < m_nDailyLimitShopSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "price%d", i + 1 );
		m_vDailyLimitShopGoods[i].nPrice = ini.getIntValue( "DAILY_LIMIT_SHOP", szCol );
		snprintf( szCol, 63, "goods%d", i + 1 );
		m_vDailyLimitShopGoods[i].vItem = CItemHelper::parseItemVectorString( ini.getStrValue( "DAILY_LIMIT_SHOP", szCol ) );
		snprintf( szCol, 63, "broadcast%d", i + 1 );
		m_vDailyLimitShopBroadcast[i] = ini.getIntValue( "DAILY_LIMIT_SHOP", szCol );
	}
	
	// TITLE section
	m_vStartDay[6] = ini.getIntValue( "TITLE", "start_day" );
	m_vEndDay[6] = ini.getIntValue( "TITLE", "end_day" );
	m_nTitleShopSize = ini.getIntValue( "TITLE", "size" );
	m_vTitleShopGoods.resize( m_nTitleShopSize );
	m_vTitleShopBroadcast.resize( m_nTitleShopSize, 0 );
	for ( int32_t i = 0; i < m_nTitleShopSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "price%d", i + 1 );
		m_vTitleShopGoods[i].nPrice = ini.getIntValue( "TITLE", szCol );
		snprintf( szCol, 63, "goods%d", i + 1 );
		m_vTitleShopGoods[i].vItem = CItemHelper::parseItemVectorString( ini.getStrValue( "TITLE", szCol ) );
		snprintf( szCol, 63, "broadcast%d", i + 1 );
		m_vTitleShopBroadcast[i] = ini.getIntValue( "TITLE", szCol );
	}
	
	// SHI_ZHUANG section
	m_vStartDay[7] = ini.getIntValue( "SHI_ZHUANG", "start_day" );
	m_vEndDay[7] = ini.getIntValue( "SHI_ZHUANG", "end_day" );
	m_nShiZhuangShopSize = ini.getIntValue( "SHI_ZHUANG", "size" );
	m_vShizhuangShopGoods.resize( m_nShiZhuangShopSize );
	m_vShiZhuangShopBroadcast.resize( m_nShiZhuangShopSize, 0 );
	for ( int32_t i = 0; i < m_nShiZhuangShopSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "price%d", i + 1 );
		m_vShizhuangShopGoods[i].nPrice = ini.getIntValue( "SHI_ZHUANG", szCol );
		snprintf( szCol, 63, "goods%d", i + 1 );
		m_vShizhuangShopGoods[i].vItem = CItemHelper::parseItemVectorString( ini.getStrValue( "SHI_ZHUANG", szCol ) );
		snprintf( szCol, 63, "broadcast%d", i + 1 );
		m_vShiZhuangShopBroadcast[i] = ini.getIntValue( "SHI_ZHUANG", szCol );
	}
	
	// RED_PACK (Online reward) section
	m_vStartDay[1] = ini.getIntValue( "RED_PACK", "start_day" );
	m_vEndDay[1] = ini.getIntValue( "RED_PACK", "end_day" );
	m_nOnlineStartMinute = ini.getIntValue( "RED_PACK", "start_time" );
	m_nOnlineEndMinute = ini.getIntValue( "RED_PACK", "end_time" );
	m_nOnlineTimeArea = 60 * ini.getIntValue( "RED_PACK", "dis_time" );
	m_vOnlineReward = CItemHelper::parseItemVectorString( ini.getStrValue( "RED_PACK", "reward" ) );
	m_nMaxCount = ini.getIntValue( "RED_PACK", "max_count" );
	
	// XIAO_FEI_SUM_RANK section
	m_vStartDay[5] = ini.getIntValue( "XIAO_FEI_SUM_RANK", "start_day" );
	m_vEndDay[5] = ini.getIntValue( "XIAO_FEI_SUM_RANK", "end_day" );
	m_nShowSize = ini.getIntValue( "XIAO_FEI_SUM_RANK", "show_size" );
	m_nXiaoFeiSumRankSize = ini.getIntValue( "XIAO_FEI_SUM_RANK", "size" );
	m_nXiaoFeiSumRankLimit = ini.getIntValue( "XIAO_FEI_SUM_RANK", "limit" );
	m_vXiaoFeiSumRankMail.resize( m_nXiaoFeiSumRankSize, 0 );
	m_vXiaoFeiSumRankReward.resize( m_nXiaoFeiSumRankSize );
	for ( int32_t i = 0; i < m_nXiaoFeiSumRankSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "mail%d", i + 1 );
		m_vXiaoFeiSumRankMail[i] = ini.getIntValue( "XIAO_FEI_SUM_RANK", szCol );
		snprintf( szCol, 63, "reward%d", i + 1 );
		MemChrBagVector items = CItemHelper::parseItemVectorString( ini.getStrValue( "XIAO_FEI_SUM_RANK", szCol ) );
		m_vXiaoFeiSumRankReward[i] = items;
	}
	
	// OBT_FLOP section
	m_vStartDay[11] = ini.getIntValue( "OBT_FLOP", "start_day" );
	m_vEndDay[11] = ini.getIntValue( "OBT_FLOP", "end_day" );
	m_FlopSize = ini.getIntValue( "OBT_FLOP", "size" );
	m_FlopType.resize( m_FlopSize, 0 );
	m_FlopCost.resize( m_FlopSize );
	for ( int32_t i = 0; i < m_FlopSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "type%d", i + 1 );
		m_FlopType[i] = ini.getIntValue( "OBT_FLOP", szCol );
		snprintf( szCol, 63, "cost%d", i + 1 );
		{ std::list<ItemData> tmpList = CItemHelper::parseItemDataListString( ini.getStrValue( "OBT_FLOP", szCol ) ); if ( !tmpList.empty() ) m_FlopCost[i] = tmpList.front(); }
	}
	
	// OBT_LI_QUAN section
	m_vStartDay[10] = ini.getIntValue( "OBT_LI_QUAN", "start_day" );
	m_vEndDay[10] = ini.getIntValue( "OBT_LI_QUAN", "end_day" );
	m_LiQuanSize = ini.getIntValue( "OBT_LI_QUAN", "size" );
	m_LiQuanItem.resize( m_LiQuanSize );
	m_ItemDataVector.resize( m_LiQuanSize );
	m_LiQuanPriceVt.resize( m_LiQuanSize, 0 );
	m_LiQuanLimitCount.resize( m_LiQuanSize, 0 );
	for ( int32_t i = 0; i < m_LiQuanSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "item%d", i + 1 );
		{ MemChrBagVector tmpVec = CItemHelper::parseItemString( 0, ini.getStrValue( "OBT_LI_QUAN", szCol ) ); if ( !tmpVec.empty() ) m_LiQuanItem[i] = tmpVec[0]; }
		snprintf( szCol, 63, "price%d", i + 1 );
		m_LiQuanPriceVt[i] = ini.getIntValue( "OBT_LI_QUAN", szCol );
		snprintf( szCol, 63, "limit%d", i + 1 );
		m_LiQuanLimitCount[i] = ini.getIntValue( "OBT_LI_QUAN", szCol );
		snprintf( szCol, 63, "costitem%d", i + 1 );
		{ std::list<ItemData> tmpList = CItemHelper::parseItemDataListString( ini.getStrValue( "OBT_LI_QUAN", szCol ) ); if ( !tmpList.empty() ) m_ItemDataVector[i] = tmpList.front(); }
	}
	
	// OBT_QIAN_DAO section
	m_vStartDay[12] = ini.getIntValue( "OBT_QIAN_DAO", "start_day" );
	m_vEndDay[12] = ini.getIntValue( "OBT_QIAN_DAO", "end_day" );
	m_QianDaoSize = ini.getIntValue( "OBT_QIAN_DAO", "size" );
	m_QianDaoReward.resize( m_QianDaoSize );
	m_BuQianPrice.resize( m_QianDaoSize, 0 );
	for ( int32_t i = 0; i < m_QianDaoSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "item%d", i + 1 );
		{ MemChrBagVector tmpVec = CItemHelper::parseItemString( 0, ini.getStrValue( "OBT_QIAN_DAO", szCol ) ); if ( !tmpVec.empty() ) m_QianDaoReward[i] = tmpVec[0]; }
		snprintf( szCol, 63, "price%d", i + 1 );
		m_BuQianPrice[i] = ini.getIntValue( "OBT_QIAN_DAO", szCol );
	}
	
	// OBT_YAN_HUA section
	m_vStartDay[13] = ini.getIntValue( "OBT_YAN_HUA", "start_day" );
	m_vEndDay[13] = ini.getIntValue( "OBT_YAN_HUA", "end_day" );
	m_YanHuaSize = ini.getIntValue( "OBT_YAN_HUA", "size" );
	m_YanHuaReward.resize( m_YanHuaSize );
	m_YanHuaPointVt.resize( m_YanHuaSize, 0 );
	for ( int32_t i = 0; i < m_YanHuaSize; ++i )
	{
		char szCol[64] = {0};
		snprintf( szCol, 63, "item%d", i + 1 );
		{ MemChrBagVector tmpVec = CItemHelper::parseItemString( 0, ini.getStrValue( "OBT_YAN_HUA", szCol ) ); if ( !tmpVec.empty() ) m_YanHuaReward[i] = tmpVec[0]; }
		snprintf( szCol, 63, "point%d", i + 1 );
		m_YanHuaPointVt[i] = ini.getIntValue( "OBT_YAN_HUA", szCol );
	}
	
	// OBT_GUO_QING_TASK / REWARD sections
	m_vStartDay[16] = ini.getIntValue( "OBT_GUO_QING_TASK", "start_day" );
	m_vEndDay[16] = ini.getIntValue( "OBT_GUO_QING_TASK", "end_day" );
	m_vStartDay[17] = ini.getIntValue( "OBT_GUO_QING_REWARD", "start_day" );
	m_vEndDay[17] = ini.getIntValue( "OBT_GUO_QING_REWARD", "end_day" );
	
	// Load persisted data
	loadXiaoFeiSumRank();
	LoadYanHuaValue();
}

bool CKaiFuHuoDong::IsInTime( int8_t Type )
{
	if ( GAME_SERVICE.getLine() == 9 )
		return false;
	if ( Type <= 0 || Type > 17 )
		return false;
	return m_nDay >= m_vStartDay[Type] && m_nDay < m_vEndDay[Type];
}

bool CKaiFuHuoDong::IsOpenBetaTime()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return false;
	return m_nDay >= 0 && m_nDay < m_nEndDay;
}

bool CKaiFuHuoDong::IsInBossTime()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return false;
	return IsInTime( 9 );
}

int32_t CKaiFuHuoDong::getLeftTime()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return 0;
	return 86400 * ( m_nEndDay - m_nDay ) - 60 * m_nMinute;
}

void CKaiFuHuoDong::OnDaySwitch()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	m_nDay = Answer::DayTime::daydiff( m_nStartDay );
	
	if ( m_nDay == m_nEndDay )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2CC3 );
		if ( packet )
		{
			packet->writeInt32( m_nIcon );
			packet->writeInt8( 4 );
			packet->writeInt32( 0 );
			packet->writeInt8( 0 );
			packet->writeInt32( 0 );
			packet->writeInt8( 0 );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( packet );
		}
	}
	
	if ( m_nDay == m_vEndDay[5] )
		sendXiaoFeiSumRankMail();
	
	if ( IsOpenBetaTime() )
		SendBossIconState();
}

void CKaiFuHuoDong::OnNewMinute( int32_t nMinute )
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	m_nMinute = nMinute;
	CheckBoss();
	checkXiaoFeiSumRank();
}

void CKaiFuHuoDong::updateStartTime()
{
	// Placeholder - no-op in decompiled
}

void CKaiFuHuoDong::GetIconState( Player* player, IconStateList& IconList )
{
	if ( !player )
		return;
	if ( GAME_SERVICE.getLine() != 9 && m_nDay >= 0 && m_nDay < m_nEndDay )
	{
		ShowIcon stu;
		getIconState( stu, player );
		IconList.push_back( stu );
	}
}

void CKaiFuHuoDong::SendIconState( Player* player )
{
	if ( !player )
		return;
	if ( GAME_SERVICE.getLine() != 9 && IsOpenBetaTime() )
	{
		ShowIcon stu;
		getIconState( stu, player );
		// Send icon directly
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_ONE_ICON );
		if ( packet )
		{
			packet->writeInt32( stu.nId );
			packet->writeInt8( stu.nState );
			packet->writeInt32( stu.nLeftTime );
			packet->writeInt8( stu.IconLeft );
			packet->writeInt32( stu.IconRight );
			packet->writeInt8( stu.Effects );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
		}
	}
}

void CKaiFuHuoDong::getIconState( ShowIcon& stu, Player* player )
{
	memset( &stu, 0, sizeof( stu ) );
	stu.nId = m_nIcon;
	stu.nState = IsOpenBetaTime() ? AS_RUNNING : AS_TIME_OUT;
	stu.nLeftTime = getLeftTime();
	stu.IconLeft = 0;
	stu.IconRight = 0;
	stu.Effects = 0;
}

void CKaiFuHuoDong::SendActivityInfo( Player* player )
{
	if ( !player || GAME_SERVICE.getLine() == 9 )
		return;
	
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2EBD );
	if ( !packet )
		return;
	
	int32_t nRecord = player->GetOperateLimit().GetLimitCount( 1917 );
	packet->writeInt8( m_nTitleShopSize );
	for ( int32_t i = 0; i < m_nTitleShopSize; ++i )
		packet->writeInt8( ( nRecord >> i ) & 1 );
	
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CKaiFuHuoDong::GetBossIconState( IconStateList& IconList )
{
	if ( GAME_SERVICE.getLine() != 9 && IsInBossTime() )
	{
		ShowIcon stu;
		getBossIconState( stu );
		IconList.push_back( stu );
	}
}

void CKaiFuHuoDong::getBossIconState( ShowIcon& stu )
{
	memset( &stu, 0, sizeof( stu ) );
	stu.nId = m_nBossIcon;
	stu.nState = IsInBossTime() ? AS_RUNNING : AS_TIME_OUT;
	stu.nLeftTime = 0;
	stu.IconLeft = m_bDie ? 0 : 1;
	stu.IconRight = 0;
	stu.Effects = 1;
}

void CKaiFuHuoDong::SendBossIconState()
{
	if ( GAME_SERVICE.getLine() != 1 )
		return;
	
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2CC3 );
	if ( !packet )
		return;
	
	ShowIcon stu;
	getBossIconState( stu );
	packet->writeInt32( stu.nId );
	packet->writeInt8( stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CKaiFuHuoDong::CheckBoss()
{
	if ( GAME_SERVICE.getLine() == 9 || !IsInTime( 9 ) || m_vBossMinute.empty() )
		return;
	
	if ( GAME_SERVICE.getLine() != 1 )
		return;
	
	for ( size_t i = 0; i < m_vBossMinute.size(); ++i )
	{
		if ( m_nMinute == m_vBossMinute[i].nStartTime )
		{
			broadcastBossStart();
			SendBossIconState();
		}
		else if ( m_nMinute == m_vBossMinute[i].nEndTime && !m_bDie )
		{
			m_bDie = true;
			broadcastBossEnd();
			SendBossIconState();
		}
	}
}

void CKaiFuHuoDong::BossDie( int32_t MonsterId, std::string* p_name, CharId_t Cid )
{
	if ( GAME_SERVICE.getLine() != 9 && m_MonsterId > 0 && m_MonsterId == MonsterId )
	{
		m_bDie = true;
		BroadcastBossKilled( p_name, Cid );
		SendBossIconState();
	}
}

void CKaiFuHuoDong::BroadcastBossKilled( const std::string* name, CharId_t cid )
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2CD6 );
	if ( !packet )
		return;
	
	packet->writeInt32( m_nBossKillBroadcast );
	packet->writeUTF8( *name );
	packet->writeInt64( cid );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CKaiFuHuoDong::broadcastBossStart()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2CD6 );
	if ( !packet )
		return;
	
	packet->writeInt32( m_nBossStartBroadcast );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

void CKaiFuHuoDong::broadcastBossEnd()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2CD6 );
	if ( !packet )
		return;
	
	packet->writeInt32( m_nBossEndBroadcast );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast( packet );
}

int32_t CKaiFuHuoDong::GetRechargeGift( Player* player, int32_t nIndex )
{
	if ( !player || GAME_SERVICE.getLine() == 9 )
		return 10002;
	if ( !IsInTime( 2 ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_nRechargeDaysSize )
		return 10002;
	
	int32_t nRewardRecord = player->GetOperateLimit().GetLimitCount( 2091 );
	if ( player->GetTodayPayGold() < m_vRechargeValue[nIndex] )
		return 10002;
	
	int32_t nNewRecord = nRewardRecord | ( 1 << nIndex );
	if ( nRewardRecord == nNewRecord )
		return 10002;
	
	if ( !player->GetBag().AddItem( m_vRechargeGift[nIndex], IACR_OPEN_BETA ) )
		return 10002;
	
	player->GetOperateLimit().UpdateLimitCount( 2091, nNewRecord );
	SendIconState( player );
	SendResult( player, 2, nIndex, 0 );
	return 0;
}

int32_t CKaiFuHuoDong::BuyGiftShopItem( Player* player, int8_t nIndex )
{
	if ( !player || GAME_SERVICE.getLine() == 9 )
		return 10002;
	if ( !IsInTime( 3 ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_nDailyLimitShopSize )
		return 10002;
	
	int32_t nOldRecord = player->GetOperateLimit().GetLimitCount( 2092 );
	int32_t nNewRecord = nOldRecord | ( 1 << nIndex );
	if ( nOldRecord == nNewRecord )
		return 10002;
	
	const ShopGoods& goods = m_vDailyLimitShopGoods[nIndex];
	if ( player->GetCurrency( CURRENCY_GOLD ) < goods.nPrice )
		return 10002;
	if ( !player->GetBag().AddItem( goods.vItem, IACR_OPEN_BETA ) )
		return 10002;
	if ( !player->DecCurrency( CURRENCY_GOLD, goods.nPrice, GCR_OPEN_BETA, 0 ) )
		return 10002;
	
	player->GetOperateLimit().UpdateLimitCount( 2092, nNewRecord );
	
	if ( m_vDailyLimitShopBroadcast[nIndex] > 0 )
	{
		std::string name = player->getName();
		CharId_t cid = player->getCid();
		int32_t broadId = m_vDailyLimitShopBroadcast[nIndex];
		sendBroadcast( broadId, cid, &name );
	}
	
	SendResult( player, 3, nIndex, 0 );
	return 0;
}

int32_t CKaiFuHuoDong::BuyTitleShopItem( Player* player, int8_t nIndex )
{
	if ( !player || GAME_SERVICE.getLine() == 9 )
		return 10002;
	if ( !IsInTime( 6 ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_nTitleShopSize )
		return 10002;
	
	int32_t nOldRecord = player->GetOperateLimit().GetLimitCount( 1917 );
	int32_t nNewRecord = nOldRecord | ( 1 << nIndex );
	if ( nOldRecord == nNewRecord )
		return 10002;
	
	const ShopGoods& goods = m_vTitleShopGoods[nIndex];
	if ( player->GetCurrency( CURRENCY_GOLD ) < goods.nPrice )
		return 10002;
	if ( !player->GetBag().AddItem( goods.vItem, IACR_OPEN_BETA ) )
		return 10002;
	if ( !player->DecCurrency( CURRENCY_GOLD, goods.nPrice, GCR_OPEN_BETA, 0 ) )
		return 10002;
	
	player->GetOperateLimit().UpdateLimitCount( 1917, nNewRecord );
	
	if ( m_vTitleShopBroadcast[nIndex] > 0 )
	{
		std::string name = player->getName();
		CharId_t cid = player->getCid();
		int32_t broadId = m_vTitleShopBroadcast[nIndex];
		sendBroadcast( broadId, cid, &name );
	}
	
	SendResult( player, 6, nIndex, 0 );
	return 0;
}

int32_t CKaiFuHuoDong::BuyShiZhuangShopItem( Player* player, int8_t nIndex )
{
	if ( !player || GAME_SERVICE.getLine() == 9 )
		return 10002;
	if ( !IsInTime( 7 ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_nShiZhuangShopSize )
		return 10002;
	
	int32_t nOldRecord = player->GetOperateLimit().GetLimitCount( 1918 );
	int32_t nNewRecord = nOldRecord | ( 1 << nIndex );
	if ( nOldRecord == nNewRecord )
		return 10002;
	
	const ShopGoods& goods = m_vShizhuangShopGoods[nIndex];
	if ( player->GetCurrency( CURRENCY_GOLD ) < goods.nPrice )
		return 10002;
	if ( !player->GetBag().AddItem( goods.vItem, IACR_OPEN_BETA ) )
		return 10002;
	if ( !player->DecCurrency( CURRENCY_GOLD, goods.nPrice, GCR_OPEN_BETA, 0 ) )
		return 10002;
	
	player->GetOperateLimit().UpdateLimitCount( 1918, nNewRecord );
	
	if ( m_vShiZhuangShopBroadcast[nIndex] > 0 )
	{
		std::string name = player->getName();
		CharId_t cid = player->getCid();
		int32_t broadId = m_vShiZhuangShopBroadcast[nIndex];
		sendBroadcast( broadId, cid, &name );
	}
	
	SendResult( player, 7, nIndex, 0 );
	return 0;
}

int32_t CKaiFuHuoDong::BuyLiQuan( Player* player, int8_t nIndex )
{
	if ( GAME_SERVICE.getLine() == 9 )
		return 10002;
	if ( !player )
		return 10002;
	if ( !IsInTime( 10 ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_LiQuanSize )
		return 10002;
	
	// Check limit
	if ( m_LiQuanLimitCount[nIndex] <= player->getRecord( nIndex + 10000 ) )
		return 10002;
	
	// Check cost
	if ( m_LiQuanPriceVt[nIndex] > 0 )
	{
		if ( player->GetCurrency( CURRENCY_GOLD ) < m_LiQuanPriceVt[nIndex] )
			return 10002;
	}
	
	if ( player->GetBag().GetFreeSlotCount() <= 0 )
		return 10002;
	
	// Remove cost item
	ItemData& costItem = m_ItemDataVector[nIndex];
	if ( costItem.m_nId > 0 )
	{
		if ( !player->GetBag().RemoveItem( costItem, IDCR_OPEN_BETA_LI_QUAN ) )
			return 10002;
	}
	
	// Deduct gold if needed
	if ( m_LiQuanPriceVt[nIndex] > 0 )
	{
		if ( !player->DecCurrency( CURRENCY_GOLD, m_LiQuanPriceVt[nIndex], GCR_OPEN_BETA, 0 ) )
			return 10002;
	}
	
	player->GetOperateLimit().AddLimitCount( nIndex + 10000, 1 );
	player->GetBag().AddItem( m_LiQuanItem[nIndex], IACR_OPEN_BETA );
	return 0;
}

void CKaiFuHuoDong::AddOnlineRecord( Player* player )
{
	if ( GAME_SERVICE.getLine() == 9 || !IsInTime( 1 ) || !player )
		return;
	if ( m_nMinute < m_nOnlineStartMinute || m_nMinute >= m_nOnlineEndMinute )
		return;
	
	int32_t nOnlineTime = player->GetOperateLimit().GetLimitCount( 2093 );
	int32_t nRewardTimes = player->GetOperateLimit().GetLimitCount( 2094 );
	
	if ( m_nMaxCount > nRewardTimes )
	{
		player->GetOperateLimit().AddLimitCount( 2093, 1 );
		
		// Check if a new reward interval has been reached
		if ( nOnlineTime / m_nOnlineTimeArea - nRewardTimes !=
		     ( nOnlineTime + 1 ) / m_nOnlineTimeArea - nRewardTimes )
		{
			SendIconState( player );
		}
	}
}

bool CKaiFuHuoDong::canGetOnlineGift( Player* player )
{
	if ( GAME_SERVICE.getLine() == 9 || !player || !IsInTime( 1 ) )
		return false;
	
	int32_t nOnlineTime = player->GetOperateLimit().GetLimitCount( 2093 );
	int32_t nRewardTimes = player->GetOperateLimit().GetLimitCount( 2094 );
	
	return m_nMaxCount > nRewardTimes && nOnlineTime / m_nOnlineTimeArea > nRewardTimes;
}

int32_t CKaiFuHuoDong::GetOnlineTimeRewardTime( Player* player )
{
	if ( GAME_SERVICE.getLine() == 9 || !player )
		return 0;
	
	int32_t nOnlineTime = player->GetOperateLimit().GetLimitCount( 2093 );
	int32_t nRewardTimes = player->GetOperateLimit().GetLimitCount( 2094 );
	
	if ( nOnlineTime / m_nOnlineTimeArea > nRewardTimes )
		return 0;
	return ( nRewardTimes + 1 ) * m_nOnlineTimeArea - nOnlineTime;
}

int32_t CKaiFuHuoDong::GetOnlineGift( Player* player )
{
	if ( !player || GAME_SERVICE.getLine() == 9 )
		return 10002;
	if ( !canGetOnlineGift( player ) )
		return 10002;
	if ( !player->GetBag().AddItem( m_vOnlineReward, IACR_OPEN_BETA ) )
		return 10002;
	
	player->GetOperateLimit().AddLimitCount( 2094, 1 );
	SendIconState( player );
	SendResult( player, 1, GetOnlineTimeRewardTime( player ), 0 );
	return 0;
}

int32_t CKaiFuHuoDong::GetEndCollectDropTime()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return 0;
	if ( !IsInTime( 8 ) )
		return 0;
	return 86400 * m_vEndDay[8] + Answer::DayTime::dayzero( m_nStartDay ) - 1;
}

int32_t CKaiFuHuoDong::GetChouJiangType()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return 0;
	if ( IsInTime( 4 ) )
		return m_ChouJiangType;
	return 0;
}

void CKaiFuHuoDong::LoadYanHuaValue()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	MySqlDBGuard db( DBPOOL );
	char mySql[1024] = {0};
	snprintf( mySql, 1023, "SELECT `value` FROM `sys_server_config` WHERE `name`='YAN_HUA'" );
	MySqlQuery result = db.query( mySql );
	if ( !result.eof() )
	{
		m_CurrYanHuaPoint = atoi( result.getStringValue( 0 ) );
	}
}

void CKaiFuHuoDong::UpdateYanHuaValue()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	MySqlDBGuard db( DBPOOL );
	char mySql[1024] = {0};
	snprintf( mySql, 1023, "SELECT `value` FROM `sys_server_config` WHERE `name`='YAN_HUA'" );
	MySqlQuery result = db.query( mySql );
	char mySql_0[1024] = {0};
	if ( result.eof() )
	{
		snprintf( mySql_0, 1023, "INSERT INTO `sys_server_config` (`name`,`value`) VALUES('YAN_HUA','%d')", m_CurrYanHuaPoint );
	}
	else
	{
		snprintf( mySql_0, 1023, "UPDATE `sys_server_config` SET `value`= %d WHERE `name`='YAN_HUA'", m_CurrYanHuaPoint );
	}
	db.excute( mySql_0 );
}

void CKaiFuHuoDong::AddYanHuaPoint( int32_t Values )
{
	if ( GAME_SERVICE.getLine() == 9 || !IsInTime( 13 ) )
		return;
	
	bool NeedSendIcon = false;
	int32_t OldPoint = m_CurrYanHuaPoint;
	m_CurrYanHuaPoint = Values + OldPoint;
	UpdateYanHuaValue();
	
	for ( int32_t i = 0; i < m_YanHuaSize; ++i )
	{
		if ( m_YanHuaPointVt[i] > OldPoint && m_CurrYanHuaPoint >= m_YanHuaPointVt[i] )
		{
			NeedSendIcon = true;
			break;
		}
	}
	
	if ( NeedSendIcon )
	{
		SendBossIconState();
	}
}

int32_t CKaiFuHuoDong::GetYanHuaPointReward( Player* player, int8_t nIndex )
{
	if ( !player || GAME_SERVICE.getLine() == 9 )
		return 10002;
	if ( !IsInTime( 13 ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_YanHuaSize )
		return 10002;
	
	int32_t nOldRecord = player->GetOperateLimit().GetLimitCount( 1930 );
	int32_t nNewRecord = nOldRecord | ( 1 << nIndex );
	if ( nOldRecord == nNewRecord )
		return 10002;
	
	if ( m_CurrYanHuaPoint < m_YanHuaPointVt[nIndex] )
		return 10002;
	
	if ( !player->GetBag().AddItem( m_YanHuaReward[nIndex], IACR_OPEN_BETA ) )
		return 10002;
	
	player->GetOperateLimit().UpdateLimitCount( 1930, nNewRecord );
	SendResult( player, 13, nIndex, 0 );
	SendIconState( player );
	return 0;
}

int32_t CKaiFuHuoDong::GetQianDaoReward( Player* player, int8_t nIndex, int8_t nType )
{
	if ( !player || GAME_SERVICE.getLine() == 9 )
		return 10002;
	if ( !IsInTime( 12 ) )
		return 10002;
	if ( nIndex < 0 || nIndex >= m_QianDaoSize )
		return 10002;
	
	int32_t nOldRecord = player->GetOperateLimit().GetLimitCount( 1931 );
	int32_t nNewRecord = nOldRecord | ( 1 << nIndex );
	if ( nOldRecord == nNewRecord )
		return 10002;
	
	int32_t nQianDaoStartDay = m_nDay - m_vStartDay[12];
	if ( nQianDaoStartDay < 0 || m_QianDaoSize <= nQianDaoStartDay || nIndex > nQianDaoStartDay )
		return 10002;
	
	// If not the current day's item, must pay gold to make up
	if ( nIndex != nQianDaoStartDay )
	{
		if ( nType != 1 )
			return 10002;
		if ( player->GetCurrency( CURRENCY_GOLD ) < m_BuQianPrice[nIndex] )
			return 10002;
	}
	
	if ( !player->GetBag().AddItem( m_QianDaoReward[nIndex], IACR_OPEN_BETA ) )
		return 10002;
	
	if ( nIndex != nQianDaoStartDay )
	{
		player->DecCurrency( CURRENCY_GOLD, m_BuQianPrice[nIndex], GCR_OPEN_BETA, 0 );
	}
	
	player->GetOperateLimit().UpdateLimitCount( 1931, nNewRecord );
	SendResult( player, 12, nIndex, 0 );
	SendIconState( player );
	return 0;
}

void CKaiFuHuoDong::loadXiaoFeiSumRank()
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	MySqlDBGuard db( DBPOOL );
	MySqlQuery result = db.query(
		"SELECT * FROM `mem_open_beta_rank` WHERE `type`=5 ORDER BY `count` DESC,`time`" );
	
	int32_t nIndex = 0;
	FestivalRankVector vRank;
	vRank.resize( m_nShowSize );
	
	while ( !result.eof() && m_nShowSize > nIndex )
	{
		vRank[nIndex].nCharId = result.getInt64Value( "cid" );
		vRank[nIndex].strName = result.getStringValue( "name" );
		vRank[nIndex].nScore = result.getIntValue( "count" );
		vRank[nIndex].nTime = result.getIntValue( "time" );
		++nIndex;
		result.nextRow();
	}
	
	int8_t connid = 0;
	m_mXiaoFeiSumRank[connid] = vRank;
}

void CKaiFuHuoDong::updateXiaoFeiSumRank( Player* player, int32_t AddValues )
{
	if ( !player || GAME_SERVICE.getLine() == 9 || !IsInTime( 5 ) )
		return;
	
	player->GetOperateLimit().AddLimitCount( 1919, AddValues );
	int32_t nScore = player->GetOperateLimit().GetLimitCount( 1919 );
	
	if ( m_nXiaoFeiSumRankLimit > nScore )
		return;
	
	int8_t connid = 0;
	CharId_t nCharId = player->getCid();
	std::string strName = player->getName();
	
	checkXiaoFeiSumRankInvalid( connid );
	
	// Find insertion position (descending by score)
	int32_t nRankIndex = -1;
	for ( int16_t i = 0; i < m_nShowSize; ++i )
	{
		Answer::MutexGuard lock( m_Lock );
		if ( m_mXiaoFeiSumRank[connid][i].nScore >= nScore )
			continue;
		nRankIndex = i;
		break;
	}
	
	if ( nRankIndex < 0 )
		return;
	
	// Find old index
	int16_t nOldIndex = m_nShowSize - 1;
	for ( int16_t i = 0; i < m_nShowSize; ++i )
	{
		Answer::MutexGuard lock( m_Lock );
		if ( m_mXiaoFeiSumRank[connid][i].nCharId == nCharId )
		{
			nOldIndex = i;
			break;
		}
	}
	
	if ( nOldIndex < nRankIndex )
		nRankIndex = nOldIndex;
	
	if ( nOldIndex != nRankIndex )
	{
		// Shift entries down
		for ( int16_t i = nOldIndex; i > nRankIndex; --i )
		{
			Answer::MutexGuard lock( m_Lock );
			m_mXiaoFeiSumRank[connid][i] = m_mXiaoFeiSumRank[connid][i - 1];
			m_mXiaoFeiSumRank[connid][i].bChange = 1;
		}
	}
	
	{
		Answer::MutexGuard lock( m_Lock );
		m_mXiaoFeiSumRank[connid][nRankIndex].nCharId = nCharId;
		m_mXiaoFeiSumRank[connid][nRankIndex].strName = strName;
		m_mXiaoFeiSumRank[connid][nRankIndex].nScore = nScore;
		m_mXiaoFeiSumRank[connid][nRankIndex].nTime = player->getNow();
		m_mXiaoFeiSumRank[connid][nRankIndex].bChange = 1;
	}
}

void CKaiFuHuoDong::checkXiaoFeiSumRankInvalid( int8_t connid )
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	Answer::MutexGuard lock( m_Lock );
	if ( m_mXiaoFeiSumRank.find( connid ) == m_mXiaoFeiSumRank.end() )
	{
		FestivalRankVector vRank;
		vRank.resize( m_nShowSize );
		m_mXiaoFeiSumRank[connid] = vRank;
	}
}

void CKaiFuHuoDong::checkXiaoFeiSumRank()
{
	if ( GAME_SERVICE.getLine() == 9 || !IsInTime( 5 ) )
		return;
	
	Answer::MutexGuard lock( m_Lock );
	
	for ( std::map<int8_t, FestivalRankVector>::iterator iter = m_mXiaoFeiSumRank.begin();
	      iter != m_mXiaoFeiSumRank.end(); ++iter )
	{
		int8_t connid = iter->first;
		FestivalRankVector& vRank = iter->second;
		
		for ( int16_t i = 0; i < m_nShowSize && vRank[i].nCharId > 0; ++i )
		{
			if ( vRank[i].bChange )
			{
				vRank[i].bChange = 0;
				
				char szSQL[4096] = {0};
				snprintf( szSQL, 4095,
					"INSERT INTO `mem_open_beta_rank` (`type`, `day`, `cid`, `name`, `count`,`time`) "
					"VALUES (%d,%d,%lld,'%s',%d,%d) "
					"ON DUPLICATE KEY UPDATE `count`=%d,`time`=%d",
					5, 0,
					vRank[i].nCharId,
					vRank[i].strName.c_str(),
					vRank[i].nScore,
					vRank[i].nTime,
					vRank[i].nScore,
					vRank[i].nTime );
				
				MySqlDBGuard db( DBPOOL );
				db.excute( szSQL );
			}
		}
	}
}

void CKaiFuHuoDong::sendXiaoFeiSumRankMail()
{
	if ( GAME_SERVICE.getLine() != 1 )
		return;
	
	Answer::MutexGuard lock( m_Lock );
	
	for ( std::map<int8_t, FestivalRankVector>::iterator iter = m_mXiaoFeiSumRank.begin();
	      iter != m_mXiaoFeiSumRank.end(); ++iter )
	{
		int8_t connid = iter->first;
		FestivalRankVector& vRank = iter->second;
		
		for ( int16_t i = 0; i < m_nXiaoFeiSumRankSize; ++i )
		{
			if ( vRank[i].nCharId > 0 )
			{
				DB_SERVICE.OnSendSysMail(
					vRank[i].nCharId,
					m_vXiaoFeiSumRankMail[i],
					m_vXiaoFeiSumRankReward[i],
					"" );
			}
		}
	}
}

void CKaiFuHuoDong::sendBroadcast( int32_t nBroadId, CharId_t cid, const std::string* name )
{
	if ( GAME_SERVICE.getLine() == 9 )
		return;
	
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2CD6 );
	if ( !packet )
		return;
	
	packet->writeInt32( nBroadId );
	packet->writeUTF8( *name );
	packet->writeInt64( cid );
	packet->setSize( packet->getWOffset() );
	packet->setProc( 0x2CD6 );
	GAME_SERVICE.worldBroadcast( packet );
}

void CKaiFuHuoDong::SendResult( Player* pPlayer, int8_t Type, int32_t Index, int32_t param )
{
	if ( !pPlayer || GAME_SERVICE.getLine() == 9 )
		return;
	
	Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, 0x2EBE );
	if ( !packet )
		return;
	
	packet->writeInt8( Type );
	packet->writeInt32( Index );
	packet->writeInt32( param );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( pPlayer->getGateIndex(), packet );
}
