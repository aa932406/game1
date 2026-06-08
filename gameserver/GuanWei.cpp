#include "GuanWei.h"
#include "Player.h"
#include "DBService.h"
#include "GameService.h"
CGuanWei::CGuanWei()
{

}

CGuanWei::~CGuanWei()
{

}

void CGuanWei::OnLoadFromDB( const PlayerDBData& dbData )
{
// 	if ( NULL == m_pPlayer )
// 	{
// 		return;
// 	}
// 	int32_t GuanWei = m_pPlayer->getRecord( RP_CUR_GUAN_WEI );
// 	if ( GuanWei == 0 )
// 	{
// 		m_pPlayer->updateRecord( RP_CUR_GUAN_WEI, 1 );
// 	}
}

void CGuanWei::InitGuanWei()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	int32_t GuanWei = m_pPlayer->getRecord( RP_CUR_GUAN_WEI );
	if ( GuanWei == 0 )
	{
		m_pPlayer->updateRecord( RP_CUR_GUAN_WEI, 1 );
		SendGuanWeiInfo();
		m_pPlayer->setSyncStatusFlag();
		int32_t CurGuanWei = m_pPlayer->getRecord( RP_CUR_GUAN_WEI );
		m_pPlayer->sendUpdateSocialPlayerInfo( PII_GUAN_WEI, CurGuanWei );
		m_pPlayer->GetAchievemnet().AddAchievement( AT_GUAN_WEI, CurGuanWei );
	}	
}

void CGuanWei::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_GUAN_WEI_INFO );
	procList.push_back( CM_ASK_GUAN_WEI_REWARD );
	procList.push_back( CM_UP_GUAN_WEI );
}

int32_t	CGuanWei::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_OK;
	}
	switch( nProcId )
	{
	case CM_ASK_GUAN_WEI_INFO:
		{
			return OnAskGuanWeiInfo( inPacket );
		}
	case CM_ASK_GUAN_WEI_REWARD:
		{
			return OnGetDailyReward( inPacket );
		}
	case CM_UP_GUAN_WEI:
		{
			return OnUpGuanWei( inPacket );
		}
	default:
		break;
	}
	return ERR_OK;
}


int32_t	CGuanWei::OnAskGuanWeiInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	SendGuanWeiInfo();
	return ERR_OK;
}

int32_t	CGuanWei::OnGetDailyReward( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->getRecord( RP_CUR_GUAN_WEI_DAILY_REWARD ) > 0 )
	{
		return ERR_SYETEM_ERR;
	}
	CfgGuanWei* pCfg = CFG_DATA.GetGuanWeiCfg( m_pPlayer->getRecord( RP_CUR_GUAN_WEI) );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pCfg->GetMoney > 0 )
	{
		m_pPlayer->AddCurrency( CURRENCY_MONEY,pCfg->GetMoney,MCR_GUAN_WEI_GET );
	}
	if ( pCfg->GetMoney > 0 )
	{
		m_pPlayer->addExp( pCfg->GetExp );
	}
	m_pPlayer->updateRecord( RP_CUR_GUAN_WEI_DAILY_REWARD, 1 );
	SendGuanWeiInfo();
	return ERR_OK;
}

int32_t	CGuanWei::OnUpGuanWei( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	CfgGuanWei* pCfg = CFG_DATA.GetGuanWeiCfg( m_pPlayer->getRecord( RP_CUR_GUAN_WEI) + 1 );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pCfg->NeedLevel > m_pPlayer->getLevel() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_HONOR, pCfg->NeedWeiWang, HCR_BUY_GUAN_WEI, pCfg->GuanWei ) )
	{
		return ERR_SYETEM_ERR;
	}
	m_pPlayer->updateRecord( RP_CUR_GUAN_WEI, m_pPlayer->getRecord( RP_CUR_GUAN_WEI) + 1 );
	if ( m_pPlayer->getRecord( RP_CUR_GUAN_WEI) > 5 )
	{
		GongGao( m_pPlayer->getRecord( RP_CUR_GUAN_WEI) );
	}
	DB_SERVICE.OnSendSysMail( m_pPlayer->getCid(), pCfg->MailId );
	SendGuanWeiInfo();
	m_pPlayer->sendUpdateSocialPlayerInfo( PII_GUAN_WEI, m_pPlayer->getRecord( RP_CUR_GUAN_WEI ) );
	m_pPlayer->recalcAttr();
	m_pPlayer->setSyncStatusFlag();
	m_pPlayer->GetAchievemnet().AddAchievement( AT_GUAN_WEI, m_pPlayer->getRecord( RP_CUR_GUAN_WEI ) );
	return ERR_OK;
}

void CGuanWei::GongGao( int32_t GuanWei )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( BCI_GUAN_WEI_UP );
	packet->writeUTF8( m_pPlayer->getName() );
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeInt32( GuanWei );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CGuanWei::SendGuanWeiInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_GUAN_WEI_INFO );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( m_pPlayer->getRecord( RP_CUR_GUAN_WEI ) );
	packet->writeInt8( (int8_t)m_pPlayer->getRecord( RP_CUR_GUAN_WEI_DAILY_REWARD ) );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

void CGuanWei::AddGuanWeiAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	CfgGuanWei* pCfg = CFG_DATA.GetGuanWeiCfg( m_pPlayer->getRecord( RP_CUR_GUAN_WEI) + 1 );
	if ( NULL == pCfg )
	{
		return;
	}
	AddAttrList::iterator it = pCfg->Attrs.begin(); 
	for ( ; it != pCfg->Attrs.end(); it++ )
	{
		m_pPlayer->AddAttrValue(static_cast<CObjAttrs::Index_T>( it->m_nAddAttrType ), it->m_nAddAttrValue );
	}
}

int32_t CGuanWei::GetAddBattle()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}
	if ( m_pPlayer->getRecord( RP_CUR_GUAN_WEI) <= 0 )
	{
		return 0;
	}
	CfgGuanWei* pCfg = CFG_DATA.GetGuanWeiCfg( m_pPlayer->getRecord( RP_CUR_GUAN_WEI));
	if ( NULL == pCfg )
	{
		return 0;
	}
	return pCfg->Battle;
}
