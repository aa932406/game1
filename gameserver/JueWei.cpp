#include "JueWei.h"
#include "CfgData.h"
#include "GameService.h"
using namespace Answer;
#define  MIN_DONATE_MONEY  3000000		//��С���
#define  GOLD_TO_MONEY	   10000		//1ħʯ��ȡ�Ľ����
#define  GONG_GAO_CONDITION 10000000	//1000�򹫸�

enum JueWeiInfo
{
	JUE_WEI_TYPE_KING			= 1,	//��
	JUE_WEI_TYPE_GONG_JUE		= 2,	//����
	JUE_WEI_TYPE_HOU_JUE		= 3,	//���
	JUE_WEI_TYPE_BO_JUE			= 4,	//����
	JUE_WEI_TYPE_ZI_JUE			= 5,	//�Ӿ�
	JUE_WEI_TYPE_XUN_JUE		= 6,	//ѫ��
	JUE_WEI_TYPE_INVALID		= 7,	//ƽ��
};

CJueWei::CJueWei()
{
	m_Rank			= 0;
	m_DonateMoney	= 0;
	m_nJueWei		= 0;
	m_FinishLogin	= false;
}

CJueWei::~CJueWei()
{

}

void CJueWei::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_DonateMoney = dbData.m_JueWeiData.m_DonateMoney;
	m_nJueWei = dbData.m_JueWeiData.m_nJueWei;
}

void CJueWei::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_JueWeiData.m_DonateMoney = m_DonateMoney;
	dbData.m_JueWeiData.m_nJueWei = m_nJueWei;
}

void CJueWei::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_JUE_WEI_DONATE_MONEY );
	procList.push_back( CM_ASK_JUE_WEI_INFO );
	procList.push_back( IM_SOCIAL_GAME_SEND_JUE_WEI_RANK );
	procList.push_back( CM_JUE_WEI_REQUEST_INFO );
	procList.push_back( CM_JUE_WEI_LEVEL_UP );
}

int32_t CJueWei::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_JUE_WEI_DONATE_MONEY:
		{
			return OnDonateMoney( inPacket );
		}
	case CM_ASK_JUE_WEI_INFO:
		{
			return OnAskDonateInfo( inPacket );
		}
	case IM_SOCIAL_GAME_SEND_JUE_WEI_RANK:
		{
			return OnReceiveRank( inPacket );
		}
	case CM_JUE_WEI_REQUEST_INFO:
		{
			return onRequestJueWeiInfo( inPacket );
		}
	case CM_JUE_WEI_LEVEL_UP:
		{
			return onAskJueWeiLevelUp( inPacket );
		}
	default:
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t CJueWei::OnDonateMoney( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t  MoneyType	= inPacket->readInt8();
	int64_t	DonateMoney = inPacket->readInt64();
	int64_t DecGold		= DonateMoney;
	if ( MoneyType == CURRENCY_GOLD )
	{
		if ( DonateMoney <= 0 )
		{
			return ERR_SYETEM_ERR;
		}
		DonateMoney	*= GOLD_TO_MONEY;
	}
	else if ( MoneyType != CURRENCY_MONEY )
	{
		return ERR_SYETEM_ERR;
	}

	if ( DonateMoney < MIN_DONATE_MONEY )
	{
		return ERR_SYETEM_ERR;
	}
	
	// �۳�ħʯ��ͭǮ
	if ( MoneyType == CURRENCY_GOLD )
	{
		if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < DecGold )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, DecGold, GCR_DONATION_JUE_WEI, m_Rank ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	else
	{
		if ( m_pPlayer->GetCurrency().GetMoneyBindAndNoBind() < DonateMoney )
		{
			return ERR_SYETEM_ERR;
		}
		if ( !m_pPlayer->GetCurrency().DecMoneyAndNoBind( DonateMoney, MCR_DONATION_JUE_WEI ) )
		{
			return ERR_SYETEM_ERR;
		}
	}
	if ( DonateMoney >= GONG_GAO_CONDITION )
	{
		GongGao( 1, DonateMoney );
	}
	m_DonateMoney+= DonateMoney;
	SendDonateMoney();
	SendDonateMoneyToGlobal();
	return ERR_OK;
}

void CJueWei::GongGao( int8_t GongGaoType, int64_t Values )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_JUE_WEI_GONG_GAO);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt8( m_pPlayer->getSex() );
	packet->writeInt8( GongGaoType );
	if ( GongGaoType == 1 )
	{
		packet->writeInt64( Values );
	}
	else if ( GongGaoType == 2 )
	{
		packet->writeInt8( static_cast<int8_t>( Values ) );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

int32_t CJueWei::OnAskDonateInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	SendDonateMoney();
	SendRankInfo();
	return ERR_OK;
}

int32_t CJueWei::OnReceiveRank( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket|| NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t Rank	= inPacket->readInt32();
	bool  IsLogin   = inPacket->readInt8() == 1 ? true : false;
	if ( IsLogin )
	{
		m_FinishLogin	= true;
	}
	int8_t OldJueWei = GetJueWei();
	if ( Rank != GetRank() )
	{
		SetRank( Rank );
		m_pPlayer->recalcAttr();
	}
	SendRankInfo();
	int8_t NewJueWei = GetJueWei();
	if ( OldJueWei != NewJueWei )
	{
		m_pPlayer->GetAchievemnet().AddAchievement( AT_JUE_WEI,NewJueWei );
		m_pPlayer->sendUpdateSocialPlayerInfo( PII_JUE_WEI, GetJueWei() );
		m_pPlayer->GetCharPet().UnSetKnightBuyJueWei();
		m_pPlayer->setSyncStatusFlag();
	}
	if ( !IsLogin )
	{
		if ( NewJueWei < OldJueWei )
		{
			GongGao( 2, NewJueWei );
		}
	}
	else
	{
		m_pPlayer->sendUpdateSocialPlayerInfo( PII_JUE_WEI, GetJueWei() );
		m_pPlayer->setSyncStatusFlag();
	}
	return ERR_OK;
}

void CJueWei::SendRankInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_JUE_WEI_RANK );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_Rank );
	packet->writeInt8( GetJueWei() );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CJueWei::SendDonateMoney()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_JUE_WEI_DONATE_MONEY );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt64( m_DonateMoney );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CJueWei::SendDonateMoneyToGlobal()
{
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_PROC, IM_GAME_SOCIAL_JUE_WEI_DONATE_MONEY);
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt8( m_pPlayer->getSex() );
	packet->writeInt64( m_DonateMoney );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

void CJueWei::RequestDonateRank()
{
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_PROC, IM_GAME_SOCIAL_ASK_JUE_WEI_RANK);
	if ( NULL == packet || NULL == m_pPlayer )
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getGateIndex() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

void CJueWei::SetRank( int32_t Rank )
{
	m_Rank	= Rank;
}

int32_t CJueWei::GetRank()
{
	if ( m_DonateMoney < JUE_WEI_RANK_MIN_DONATE )
	{
		return 0;
	}
	return m_Rank;
}

int8_t CJueWei::GetJueWei()
{
	if ( m_DonateMoney < JUE_WEI_RANK_MIN_DONATE )
	{
		return JUE_WEI_TYPE_INVALID;
	}
	if ( !m_FinishLogin )	//û���յ����ķ�������
	{
		return JUE_WEI_TYPE_INVALID;
	}
	if ( m_Rank == 0 || m_Rank > 20 )
	{
		if ( m_DonateMoney >= 1000000000 )
		{
			return JUE_WEI_TYPE_BO_JUE;
		}
		if ( m_DonateMoney >= 300000000 )
		{
			return JUE_WEI_TYPE_ZI_JUE;
		}
		if ( m_DonateMoney >= 70000000 )
		{
			return JUE_WEI_TYPE_XUN_JUE;
		}
		return JUE_WEI_TYPE_INVALID;
	}
	else if ( m_Rank <= 3 )
	{
		return JUE_WEI_TYPE_KING;
	}
	else if ( m_Rank <= 10)
	{
		return JUE_WEI_TYPE_GONG_JUE;
	}
	else if ( m_Rank <= 20 )
	{
		return JUE_WEI_TYPE_HOU_JUE;
	}
	return JUE_WEI_TYPE_INVALID;
}

int32_t CJueWei::GetBattleValues()
{
	int8_t JueWei = GetJueWei();
	switch( JueWei )
	{
	case JUE_WEI_TYPE_KING:
		{
			return 100;
		}
	case JUE_WEI_TYPE_GONG_JUE:
		{
			return 80;
		}
	case JUE_WEI_TYPE_HOU_JUE:
		{
			return 60;
		}
	case JUE_WEI_TYPE_BO_JUE:
		{
			return 40;
		}
	case JUE_WEI_TYPE_ZI_JUE:
		{
			return 20;
		}
	case JUE_WEI_TYPE_XUN_JUE:
		{
			return 10;
		}
	default:
		return 0;
	}
}

// ========== 新版本方法 - 升级爵位系统 ==========

int32_t CJueWei::onRequestJueWeiInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	sendJueWeiInfo();
	return ERR_OK;
}

int32_t CJueWei::onAskJueWeiLevelUp( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}

	const CfgJueWei* pCfgJueWei = CFG_DATA.GetJueWeiTable()->GetJueWei( static_cast<int8_t>( m_nJueWei ) );
	if ( NULL == pCfgJueWei )
	{
		return ERR_SYETEM_ERR;
	}

	if ( pCfgJueWei->nNeedLevel > m_pPlayer->getLevel() )
	{
		return ERR_SYETEM_ERR;
	}

	int8_t nNextJueWei = static_cast<int8_t>( m_nJueWei + 1 );
	if ( NULL == CFG_DATA.GetJueWeiTable()->GetJueWei( nNextJueWei ) )
	{
		return ERR_SYETEM_ERR;
	}

	if ( pCfgJueWei->nNeedViGour <= 0 )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_VIGOUR, pCfgJueWei->nNeedViGour, MCR_DONATION_JUE_WEI, 0 ) )
	{
		return ERR_NOT_ENOUGH_MONEY;
	}

	m_nJueWei++;
	m_pPlayer->sendUpdateSocialPlayerInfo( PII_JUE_WEI, m_nJueWei );
	GongGao( 2, m_nJueWei );
	sendJueWeiInfo();
	m_pPlayer->setSyncStatusFlag();
	m_pPlayer->recalcAttr();
	m_pPlayer->GetTask().updateTaskCount( 39 );

	return ERR_OK;
}

void CJueWei::sendJueWeiInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_JUE_WEI_LEVEL_INFO );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( m_nJueWei ) );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CJueWei::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	const CfgJueWei* pCfgJueWei = CFG_DATA.GetJueWeiTable()->GetJueWei( static_cast<int8_t>( m_nJueWei ) );
	if ( NULL == pCfgJueWei )
	{
		return;
	}

	for ( AttrAddonVector::const_iterator iter = pCfgJueWei->vAttr.begin();
		iter != pCfgJueWei->vAttr.end(); ++iter )
	{
		m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( iter->index ), iter->addon );
	}
}
