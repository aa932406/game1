#include "FaBao.h"
#include "CfgData.h"
#include "GameService.h"
CFaBao::CFaBao()
{
	OnCleanUp();
}

CFaBao::~CFaBao()
{

}

void CFaBao::OnCleanUp()
{
	bzero( m_FaBaoId, sizeof( m_FaBaoId ) );
	bzero( m_FaBaoDress, sizeof( m_FaBaoDress ) );
	bzero( m_UpFaBaoResource, sizeof( m_UpFaBaoResource ) );
}

void CFaBao::OnLoadFromDB( const PlayerDBData& dbData )
{
	memcpy( m_FaBaoId,dbData.m_FaBaoData.m_FaBaoId, sizeof( m_FaBaoId ) );
	memcpy( m_FaBaoDress,dbData.m_FaBaoData.m_FaBaoDress, sizeof( m_FaBaoDress ) );
	memcpy( m_UpFaBaoResource, dbData.m_FaBaoData.m_UpFaBaoResource, sizeof( m_UpFaBaoResource ) );
}

void CFaBao::OnSaveToDB( PlayerDBData& dbData )
{
	memcpy( dbData.m_FaBaoData.m_FaBaoId, m_FaBaoId, sizeof( m_FaBaoId ) );
	memcpy( dbData.m_FaBaoData.m_FaBaoDress, m_FaBaoDress, sizeof( m_FaBaoDress ) );
	memcpy( dbData.m_FaBaoData.m_UpFaBaoResource, m_UpFaBaoResource, sizeof( m_UpFaBaoResource ) );
}

void CFaBao::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_FA_BAO_INFO );
	procList.push_back( CM_UP_FA_BAO_LEVEL );
	procList.push_back( CM_DRESS_FA_BAO );
	procList.push_back( CM_BUY_FA_BAO_RES );
}

int32_t CFaBao::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_BUY_FA_BAO_RES:			return OnBuyFaBaoRes( inPacket );
	case CM_ASK_FA_BAO_INFO:		return OnAskFaBaoInfo( inPacket );
	case CM_UP_FA_BAO_LEVEL:		return OnUpFaBaoLevel( inPacket );
	case CM_DRESS_FA_BAO:			return OnDressFaBao( inPacket );
	default:
		return ERR_SYETEM_ERR;
	}
}

int32_t CFaBao::OnBuyFaBaoRes( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t ResId = inPacket->readInt32();
	BuyFaBaoResCfg* pFaBaoResCfg = CFG_DATA.GetBuyFaBaoResCfg( ResId );
	if ( NULL == pFaBaoResCfg )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pFaBaoResCfg->NeedGold <= 0 || pFaBaoResCfg->GetResValues <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !CheckFaBaoResType( static_cast<FaBaoResourceType>(pFaBaoResCfg->FaBaoResType) ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_pPlayer->GetCurrency(CURRENCY_GOLD) < pFaBaoResCfg->NeedGold )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !m_pPlayer->DecCurrency( CURRENCY_GOLD, pFaBaoResCfg->NeedGold, GCR_BUY_FA_BAO_RES, pFaBaoResCfg->id ))
	{
		return ERR_SYETEM_ERR;
	}
	
	AddFaBaoRes( static_cast<FaBaoResourceType>(pFaBaoResCfg->FaBaoResType), pFaBaoResCfg->GetResValues );
	return ERR_OK;
}

int32_t CFaBao::OnDressFaBao( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t nFaBaoType = inPacket->readInt8();
	if ( !CheckFaBaoType( static_cast<FaBaoType>( nFaBaoType ) ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_FaBaoId[nFaBaoType] != 0 )
	{
		if ( m_FaBaoDress[nFaBaoType] != 1 )
		{
			m_FaBaoDress[nFaBaoType] = 1;
		}
		else
		{
			m_FaBaoDress[nFaBaoType] = 0;
		}
		m_pPlayer->recalcAttr();
		SendFaBaoInfo();
	}
	else
	{
		return ERR_SYETEM_ERR;
	}
	return ERR_OK;
}

int32_t	CFaBao::OnAskFaBaoInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	SendFaBaoInfo();
	return ERR_OK;
}

int32_t	CFaBao::OnUpFaBaoLevel( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t	FaBaoId	= inPacket->readInt32();
	
	CfgFaBao* pFaBao = CFG_DATA.GetFaBaoTable().GetFaBaoCfg( FaBaoId );
	if ( NULL == pFaBao )
	{
		return ERR_SYETEM_ERR;
	}

	if ( !CheckFaBaoType( static_cast<FaBaoType>( pFaBao->FaBaoType ) ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( pFaBao->FaBaoId != m_FaBaoId[pFaBao->FaBaoType] )
	{
		if ( pFaBao->FaBaoLevel != 0 )
		{
			return ERR_SYETEM_ERR;
		}
	}
	if ( pFaBao->NextFaBaoId <= 0 )
	{
		return ERR_SYETEM_ERR;
	}
	int8_t FaBaoResType = 0;
	switch( pFaBao->FaBaoType )
	{
	case FA_BAO_TYPE_SHU_GUANG:
		{
			FaBaoResType	= FA_BAO_RES_SHU_GUANG;
			break;
		}
	case FA_BAO_TYPE_DI_LONG:
		{
			FaBaoResType	= FA_BAO_RES_DI_LONG;
			break;
		}
	case FA_BAO_TYPE_FU_WEN:
		{
			FaBaoResType	= FA_BAO_RES_FU_WEN;
			break;
		}
	default:
		return ERR_SYETEM_ERR;
	}
	if ( pFaBao->NeedRes > GetFaBaoRes( static_cast<FaBaoResourceType>( FaBaoResType ) ) )
	{
		return ERR_SYETEM_ERR;
	}
	if ( !DecFaBaoRes( static_cast<FaBaoResourceType>( FaBaoResType), pFaBao->NeedRes ) ) 
	{
		return ERR_SYETEM_ERR;
	}
	m_FaBaoId[pFaBao->FaBaoType] = pFaBao->NextFaBaoId;
	if ( pFaBao->FaBaoLevel == 0 )
	{
		m_FaBaoDress[pFaBao->FaBaoType] = 1;	//��ȡ����ʱ������
	}
	SendFaBaoInfo();
	if ( m_FaBaoDress[pFaBao->FaBaoType] == 1 )
	{
		m_pPlayer->recalcAttr();
	}
	if ( pFaBao->FaBaoLevel >= 3 )
	{
		GongGao( pFaBao->NextFaBaoId );
	}
	m_pPlayer->GetAchievemnet().AddAchievement( AT_FA_BAO, pFaBao->FaBaoType );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(),pFaBao->FaBaoId );
	return ERR_OK;
}

void CFaBao::GongGao( int32_t FaBaoID )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_FA_BAO_GONG_GAO);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt64( m_pPlayer->getCid() );
	packet->writeUTF8(  m_pPlayer->getName() );
	packet->writeInt32( FaBaoID );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast(packet);
}

void CFaBao::AddPlayerAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	for ( int32_t i = 0; i < FA_BAO_TYPE_COUNT; ++i )
	{
		CfgFaBao* pFaBao = CFG_DATA.GetFaBaoTable().GetFaBaoCfg( m_FaBaoId[i] );
		if ( NULL == pFaBao )
		{
			continue;
		}
		if ( m_FaBaoDress[i] != 1 )
		{
			continue;
		}
		AddAttrList::iterator it = pFaBao->m_AttrList.begin();
		for ( ; it != pFaBao->m_AttrList.end(); ++it )
		{ 
			if ( static_cast<CObjAttrs::Index_T>( it->m_nAddAttrType ) == CObjAttrs::ATTR_BATTLE )
			{
				continue;
			}
			m_pPlayer->AddAttrValue(static_cast<CObjAttrs::Index_T>( it->m_nAddAttrType ), it->m_nAddAttrValue );
		}
	}
}

void CFaBao::SendFaBaoInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_FA_BAO_INFO );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( static_cast<int8_t>( FA_BAO_TYPE_COUNT) );
	for ( int32_t i = 0; i < FA_BAO_TYPE_COUNT; i++ )
	{
		packet->writeInt8( i );
		packet->writeInt32( m_FaBaoId[i] );
		packet->writeInt8( m_FaBaoDress[i] );
	}

	packet->writeInt8( static_cast<int8_t>( FA_BAO_RES_COUNT) );
	for ( int32_t i = 0; i < FA_BAO_RES_COUNT; i++ )
	{
		packet->writeInt8( i );
		packet->writeInt32( m_UpFaBaoResource[i] );
	}
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

bool CFaBao::AddFaBaoRes( FaBaoResourceType Type, int32_t AddValues )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	if ( AddValues <= 0 )
	{
		return false;
	}
	if ( !CheckFaBaoResType( Type ) )
	{
		return false;
	}
	m_UpFaBaoResource[Type]+= AddValues;
	SendFaBaoInfo();
	int8_t nType = 0;
	switch(  Type )
	{
	case FA_BAO_RES_SHU_GUANG:
		{
			nType = GT_SHU_GUANG;
			break;
		}
	case FA_BAO_RES_DI_LONG:
		{
			nType = GT_DI_LONG;
			break;
		}
	case FA_BAO_RES_FU_WEN:
		{
			nType = GT_FU_WEN;
			break;
		}
	}
	m_pPlayer->sendGainInfo( nType, static_cast<int32_t>(AddValues),m_pPlayer->benefitType() );
	return true;
}

bool CFaBao::DecFaBaoRes( FaBaoResourceType Type, int32_t DecValues )
{
	if ( DecValues <= 0 )
	{
		return false;
	}
	if ( !CheckFaBaoResType( Type ) )
	{
		return false;
	}
	m_UpFaBaoResource[Type] -= DecValues;
	SendFaBaoInfo();
	return true;
}

int32_t	CFaBao::GetFaBaoRes( FaBaoResourceType Type )
{
	if ( !CheckFaBaoResType( Type ) )
	{
		return 0;
	}
	return m_UpFaBaoResource[Type];
}

bool CFaBao::CheckFaBaoType( FaBaoType Type )
{
	if ( Type < 0 || Type >= FA_BAO_TYPE_COUNT )
	{
		return false;
	}
	return true;
}

bool CFaBao::CheckFaBaoResType( FaBaoResourceType Type )
{
	if ( Type < 0 || Type >= FA_BAO_RES_COUNT )
	{
		return false;
	}
	return true;
}

int32_t CFaBao::GetFaBaoCount( int32_t& FaBaoSumLevel )
{
	int32_t FaBaoCount = 0;
	for ( int32_t i = 0; i < FA_BAO_TYPE_COUNT; ++i )
	{
		if ( m_FaBaoDress[i] == 1 )
		{
			FaBaoCount++;
			CfgFaBao* pFaBao = CFG_DATA.GetFaBaoTable().GetFaBaoCfg(m_FaBaoId[i] );
			if ( NULL == pFaBao )
			{
				continue;
			}
			FaBaoSumLevel += pFaBao->FaBaoLevel;
		}
	}
	return FaBaoCount;
}

int32_t CFaBao::GetBattleFaBaoInfo( int8_t& FaBaoLevel, int32_t& FaBaoBattle )
{
	if ( m_FaBaoDress[FA_BAO_TYPE_FU_WEN] != 1 )		//û���������ս����
	{
		return ERR_SYETEM_ERR;
	}
	CfgFaBao* pFaBao = CFG_DATA.GetFaBaoTable().GetFaBaoCfg(m_FaBaoId[FA_BAO_TYPE_FU_WEN] );
	if ( NULL == pFaBao )
	{
		return ERR_SYETEM_ERR;
	}
	FaBaoLevel = pFaBao->FaBaoLevel;
	AddAttrList::iterator it = pFaBao->m_AttrList.begin();
	for ( ; it != pFaBao->m_AttrList.end(); ++it )
	{ 
		if ( static_cast<CObjAttrs::Index_T>( it->m_nAddAttrType ) == CObjAttrs::ATTR_BATTLE )
		{
			FaBaoBattle += it->m_nAddAttrValue;
		}
	}
	return ERR_OK;
}

void CFaBao::PackFaBaoInfo( Answer::NetPacket *inPacket )
{
	if ( inPacket == NULL )
	{
		return;
	}
	for ( int8_t i = 0;  i < FA_BAO_TYPE_COUNT; i++ )
	{
		inPacket->writeInt8( i );
		inPacket->writeInt8( m_FaBaoId[i] );
		inPacket->writeInt8( m_FaBaoDress[i] );
	}
}

int32_t	CFaBao::GetFaBaoLevel( int8_t Type )
{
	if ( Type < 0 || Type >= FA_BAO_TYPE_COUNT )
	{
		return 0;
	}
	CfgFaBao* pFaBao = CFG_DATA.GetFaBaoTable().GetFaBaoCfg(m_FaBaoId[Type] );
	if ( NULL == pFaBao )
	{
		return 0;
	}
	return pFaBao->FaBaoLevel;
}