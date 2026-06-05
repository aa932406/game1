#include "stdafx.h"
#include "KaiFuHuoDong.h"
#include "Player.h"
#include "GameService.h"
#include "ActivityManager.h"

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
	int32_t count = 0;
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
	int32_t DiffDay = CFG_DATA.getServerDiffDay( SVT_NORMAL ) + 1;
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
				if ( GetLimitCount( it->first ) < it->second.Limit )
					++Count;
			}
			break;
		case 5: // Wing level
			if ( pPlayer->GetCharWing().GetLevel() >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.Limit )
					++Count;
			}
			break;
		case 10: // Record 1150
			if ( pPlayer->getRecord( 1150 ) >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.Limit )
					++Count;
			}
			break;
		case 11: // JueWei
			if ( pPlayer->GetCharJueWei().GetJueWei() >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.Limit )
					++Count;
			}
			break;
		case 12: // Equip level
			if ( pPlayer->GetEquip().IsAllPosLevel() >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.Limit )
					++Count;
			}
			break;
		case 13: // FaBao level
			if ( pPlayer->GetPlayerFaBao().GetFaBaoLevel( 3 ) >= it->second.Conditions )
			{
				if ( GetLimitCount( it->first ) < it->second.Limit )
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
	pPlayer->SendIconState( GetKaiFuHuoDongIconStu( pPlayer ) );
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
