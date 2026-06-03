
#include "TouZi.h"
#include "Player.h"
#include "GameService.h"
using namespace Answer;
#define MOON_CARD_NEED_GOLD				 500	//月卡投资500
#define MAX_LEVEL_UP_TOU_ZI_COUNT		 10000  //等级投资最大金额

enum Record_Typ
{
	MOON_CARD_TOU_ZI		= 1,		//月卡投资
	LEVEL_UP_TOU_ZI			= 2,		//等级投资
	GET_MOON_CARD_REWARD	= 3,		//领取月卡投资奖励
	GET_LEVEL_UP_REWARD		= 4,		//领取等级投资
};

CTouZi::CTouZi()
{
	OnCleanUp();
}

CTouZi::~CTouZi()
{

}

void CTouZi::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_TouZiValues		= dbData.m_TouZiData.m_TouZiValues;
	m_MoonCardStartTime = dbData.m_TouZiData.m_MoonCardStartTime;
	m_MoonCardRecord	= dbData.m_TouZiData.m_MoonCardRecord;
	m_LevelUpRecord		= dbData.m_TouZiData.m_LevelUpRecord;
}

void CTouZi::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_TouZiData.m_TouZiValues			= m_TouZiValues;
	dbData.m_TouZiData.m_MoonCardStartTime		= m_MoonCardStartTime;
	dbData.m_TouZiData.m_MoonCardRecord			= m_MoonCardRecord;
	dbData.m_TouZiData.m_LevelUpRecord			= m_LevelUpRecord;
}

void CTouZi::OnCleanUp()
{
	m_TouZiValues			 = 0;			
	m_MoonCardStartTime		 = 0;		
	m_MoonCardRecord.clear();		
	m_LevelUpRecord.clear();		
}

void CTouZi::OnUpdate( int64_t curTick )
{

}

void CTouZi::OnDaySwitch( int32_t nDiffDays )
{
	if ( GetDiffDay() > 30 )
	{
		bool	IsHaveReward = IsHaveMoonCardReward();
		if ( !IsHaveReward )
		{
			m_MoonCardStartTime		= 0;
			m_MoonCardRecord.clear();
			//SendMoonCardTouZiInfo();
		}
	}
	SendTouZiIcon();
}

void CTouZi::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_TOU_ZI_INFO );					
	procList.push_back( CM_GET_TOU_ZI_REWARD );			
	procList.push_back( CM_TOU_ZI );							
}
int32_t	CTouZi::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_ASK_TOU_ZI_INFO:
		{
			return OnAskTouZiInfo( inPacket );
		}
	case CM_GET_TOU_ZI_REWARD:
		{
			return OnGetTouZiReward( inPacket );
		}
	case CM_TOU_ZI:
		{
			return OnTouZi( inPacket );
		}
	}
	return ERR_OK;
}

int32_t	CTouZi::OnTouZi( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t		Type	= inPacket->readInt8();
	int32_t		Values	= inPacket->readInt32();
	if ( Type == TT_MOON_CARD )
	{
		if ( GetMoonCardStartTime() > 0 )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, MOON_CARD_NEED_GOLD,GCR_TOU_ZHI_SHI_QU, Type ) )
		{
			return ERR_OK;
		}
		m_MoonCardStartTime	= m_pPlayer->getNow();
		AddTouZhiRecord( MOON_CARD_TOU_ZI, CURRENCY_GOLD, MOON_CARD_NEED_GOLD );
		broadcastTouZi( BCI_TOU_ZI_MOON_CARD );
		SendMoonCardTouZiInfo();
	}
	else if ( Type == TT_LEVEL_UP )
	{
		if ( !CheckLevelUpTouZiValues( Values ) )
		{
			return ERR_SYETEM_ERR;
		}
		if ( GetLevelUpTouZhiValues() + Values > MAX_LEVEL_UP_TOU_ZI_COUNT )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, Values,GCR_TOU_ZHI_SHI_QU, Type ) )
		{
			return ERR_OK;
		}
		m_TouZiValues += Values;
		AddTouZhiRecord( LEVEL_UP_TOU_ZI, CURRENCY_GOLD, Values );
		broadcastTouZi( BCI_TOU_ZI_LEVEL_UP );
		SendLevelUpTouZiInfo();
	}
	GAME_SERVICE.replySuccess( m_pPlayer->getGateIndex(),inPacket->getProc(), Type );
	SendTouZiIcon();
	return ERR_OK;
}

int32_t	CTouZi::OnGetTouZiReward( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t	Type	= inPacket->readInt8();
	int16_t	Index	= inPacket->readInt16();
	if ( Type == TT_MOON_CARD )
	{
		return GetMoonCardReward( Index );
	}
	else if ( Type == TT_LEVEL_UP )
	{
		return GetLevelUpReward( Index );
	}
	return ERR_OK;
}

int32_t	CTouZi::OnAskTouZiInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t	Type = inPacket->readInt8();
	if ( Type == TT_MOON_CARD )
	{
		SendMoonCardTouZiInfo();
	}
	else if( Type == TT_LEVEL_UP )
	{
		SendLevelUpTouZiInfo();
	}
	return ERR_OK;
}

int32_t CTouZi::GetMoonCardReward( int16_t Index )
{
	if ( NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetMoonCardStartTime() <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	MoonCardTouZiCfg* pCfg = CFG_DATA.GetTouZhiCfg().GetMoonCardTouZiCfg( Index );
	if ( pCfg == NULL )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t DiffDay  = GetDiffDay();
	if ( pCfg->NeedDay > DiffDay )
	{
		return ERR_SYETEM_ERR;
	}
	RecordMap::iterator it = m_MoonCardRecord.find( Index );
	if ( it != m_MoonCardRecord.end() )
	{
		return ERR_SYETEM_ERR;
	}
	m_MoonCardRecord[Index]		= 1;
	m_pPlayer->AddCurrency(static_cast<CURRENCY_TYPE>( pCfg->CurrencyType),pCfg->CurrencyValues,GCR_TOU_ZHI_HUO_DE, pCfg->Index );
	AddTouZhiRecord( GET_MOON_CARD_REWARD, pCfg->CurrencyType, pCfg->CurrencyValues );
	SendGetRewardSucceed( TT_MOON_CARD, Index );
	if ( GetDiffDay() > 30 )
	{
		bool	IsHaveReward = IsHaveMoonCardReward();
		
		if ( !IsHaveReward )
		{
			m_MoonCardStartTime		= 0;
			m_MoonCardRecord.clear();
			SendMoonCardTouZiInfo();
		}
	}
	SendTouZiIcon();
	return ERR_OK;
}

bool CTouZi::IsHaveMoonCardReward()
{
	MoonCardTouZiCfgMap MoonCardTable = CFG_DATA.GetTouZhiCfg().GetMoonCardTable();
	MoonCardTouZiCfgMap::iterator it = MoonCardTable.begin();
	for ( ; it != MoonCardTable.end(); ++it )
	{
		if ( it->second.NeedDay > GetDiffDay() )
		{
			continue;
		}
		RecordMap::iterator iter = m_MoonCardRecord.find( it->first );
		if ( iter != m_MoonCardRecord.end() )
		{
			continue;
		}
		return true;
	}
	return false;
}

int32_t	CTouZi::GetLevelUpReward( int16_t Index )
{
	if ( NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( GetLevelUpTouZhiValues() <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	LevelUpTouZiCfg* pCfg = CFG_DATA.GetTouZhiCfg().GetLevelUpTouZiCfg( Index );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pCfg->NeedLevel > m_pPlayer->getLevel() )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t TouZhiValues = 0;
	RecordMap::iterator it = m_LevelUpRecord.find( Index );
	if ( it != m_LevelUpRecord.end() )
	{
		if ( it->second >= GetLevelUpTouZhiValues() )
		{
			return ERR_SYETEM_ERR;
		}
		TouZhiValues = GetLevelUpTouZhiValues() - it->second;
	}
	else
	{
		TouZhiValues = GetLevelUpTouZhiValues();
	}
	int32_t CanGetGold = TouZhiValues / 100 * pCfg->Rate;
	if ( CanGetGold <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	m_LevelUpRecord[Index] = GetLevelUpTouZhiValues();
	m_pPlayer->AddCurrency( CURRENCY_CASH, CanGetGold, GCR_TOU_ZHI_HUO_DE, pCfg->Index );
	AddTouZhiRecord( GET_LEVEL_UP_REWARD, CURRENCY_CASH, CanGetGold );
	SendGetRewardSucceed( TT_LEVEL_UP, Index );
	SendTouZiIcon();
	return ERR_OK;
}

void CTouZi::SendMoonCardTouZiInfo()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_TOU_ZI_INFO);
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}
	packet->writeInt8( 1 );
	if ( GetMoonCardStartTime() <= 0 )
	{
		packet->writeInt8( 0 );
	}
	else
	{
		packet->writeInt8( 1 );
		packet->writeInt8( static_cast<int8_t>( GetDiffDay() ));
		int16_t nSize = static_cast<int16_t>( m_MoonCardRecord.size() );
		packet->writeInt16( nSize );
		RecordMap::iterator it = m_MoonCardRecord.begin();
		for ( ; it != m_MoonCardRecord.end(); ++it )
		{
			packet->writeInt16( it->first );
		}
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CTouZi::SendLevelUpTouZiInfo()
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_TOU_ZI_INFO);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( 2 );
	packet->writeInt32( GetLevelUpTouZhiValues() );
	if ( GetLevelUpTouZhiValues() > 0 )
	{
		int16_t	nSize = static_cast<int16_t>(m_LevelUpRecord.size());
		packet->writeInt16( nSize );
		RecordMap::iterator it =	m_LevelUpRecord.begin();
		for ( ; it != m_LevelUpRecord.end(); ++it )
		{
			packet->writeInt16( it->first );
			packet->writeInt32( it->second );
		}
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CTouZi::SendGetRewardSucceed( int8_t Type, int16_t Index )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_GET_RESULT);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( Type );
	packet->writeInt16( Index );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

int32_t	CTouZi::GetMoonCardStartTime()
{
	return m_MoonCardStartTime;
}

int32_t CTouZi::GetDiffDay()
{
	return DayTime::daydiff( m_MoonCardStartTime ) + 1;
}

int32_t	CTouZi::GetLevelUpTouZhiValues()
{
	return m_TouZiValues;
}

bool CTouZi::CheckLevelUpTouZiValues( int32_t Values )
{
	switch( Values )
	{
	case 1000:
	case 3000:
	case 5000:
	case 10000:
		{
			return true;
		}
	default:
		return false;
	}
}

void CTouZi::AddTouZhiRecord( int8_t Type, int8_t MoneyType, int32_t MoneyValues )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_PROC, IM_GAME_SOCIAL_ADD_TOU_ZI_RECORD );
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt8( Type );
	packet->writeInt8( MoneyType );
	packet->writeInt32( MoneyValues );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

void CTouZi::GetTouZiIconState( IconStateList& IconList )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_TOU_ZI ) )
	{
		return;
	}
	IconList.push_back( GetTouZiIconStu() );
}

void CTouZi::SendTouZiIcon()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( FT_TOU_ZI ) )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = GetTouZiIconStu();
	packet->writeInt32( stu.nId );
	packet->writeInt8(  stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

int32_t CTouZi::GetRewardCount()
{
	int32_t	nCount  = 0;
	if ( GetMoonCardStartTime() > 0 )
	{
		MoonCardTouZiCfgMap MoonCardTable = CFG_DATA.GetTouZhiCfg().GetMoonCardTable();
		MoonCardTouZiCfgMap::iterator it = MoonCardTable.begin();
		for ( ; it != MoonCardTable.end(); ++it )
		{
			if ( it->second.NeedDay > GetDiffDay() )
			{
				continue;
			}
			RecordMap::iterator iter = m_MoonCardRecord.find( it->first );
			if ( iter != m_MoonCardRecord.end() )
			{
				continue;
			}
			nCount++;
		}
	}

	if ( GetLevelUpTouZhiValues() > 0 )
	{
		LevelUpTouZiCfgMap&	LevelUpTable = CFG_DATA.GetTouZhiCfg().GetLevelUpTable();
		LevelUpTouZiCfgMap::iterator it = LevelUpTable.begin();
		for ( ; it != LevelUpTable.end(); ++it )
		{
			if ( it->second.NeedLevel > m_pPlayer->getLevel() )
			{
				continue;
			}
			int32_t TouZhiValues = 0;
			RecordMap::iterator iter = m_LevelUpRecord.find( it->first );
			if ( iter != m_LevelUpRecord.end() )
			{
				if ( iter->second >= GetLevelUpTouZhiValues() )
				{
					continue;
				}
				TouZhiValues = GetLevelUpTouZhiValues() - iter->second;
			}
			else
			{
				TouZhiValues = GetLevelUpTouZhiValues();
			}
			if ( TouZhiValues > 0 )
			{
				nCount++;
			}
		}
	}
	return nCount;
}

ShowIcon CTouZi::GetTouZiIconStu()
{
	ShowIcon stu = {};
	stu.nId			= TOU_ZI;
	stu.nState		= AS_RUNNING;
	stu.nLeftTime	= -1;
	if ( GetMoonCardStartTime() > 0 || GetLevelUpTouZhiValues() > 0 )
	{
		stu.Effects		= 0;
	}
	else
	{
		stu.Effects	    = 1;
	}
	stu.IconRight	= GetRewardCount();
	return stu;
}

void CTouZi::broadcastTouZi( int32_t ID)
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( ID );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}