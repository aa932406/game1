#include "stdafx.h"
#include "Goblin.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "EquipManager.h"
#include "DBService.h"

using namespace Answer;

// Helper: check if nType is a valid Goblin type (29-34)
static bool IsGoblinTypeImpl( int32_t nType )
{
	return nType >= 29 && nType <= 34;
}

// Helper: determine if type is "left" (29-31) or "right" (32-34)
static bool IsLeftTypeImpl( int32_t nType )
{
	return nType >= 29 && nType <= 31;
}

CGoblin::CGoblin()
{
}

CGoblin::~CGoblin()
{
}

void CGoblin::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_GoblinInfoMap			= dbData.m_CGoblinData.m_GoblinInfoMap;
	m_ShouHuRefiningLeveMap	= dbData.m_CGoblinData.m_ShouHuRefiningLeveMap;
	m_WingEquipPolishMap	= dbData.m_CGoblinData.m_WingEquipPolishMap;
	m_MoFuZhuNengMap		= dbData.m_CGoblinData.m_MoFuZhuNengMap;
	m_WingEquipRefiningMap	= dbData.m_CGoblinData.m_WingEquipRefiningMap;
	m_VipEquipPosLevelMap	= dbData.m_CGoblinData.m_VipEquipPosLevelMap;

	// Apply VIP equip pos level suit talent
	int32_t SuitId = GetVipEquipPosLevelSuitId();
	if ( SuitId > 0 )
	{
		const VipEQuipPosSuit* pCfg = CFG_DATA.GetVipEQuipPosSuit( SuitId );
		if ( pCfg != NULL && pCfg->nTalentId > 0 && pCfg->TalentLevel > 0 )
		{
			m_pPlayer->GetCharSkill().AddOtherSkill( pCfg->nTalentId, pCfg->TalentLevel );
		}
	}
}

void CGoblin::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_CGoblinData.m_GoblinInfoMap			= m_GoblinInfoMap;
	dbData.m_CGoblinData.m_ShouHuRefiningLeveMap	= m_ShouHuRefiningLeveMap;
	dbData.m_CGoblinData.m_WingEquipPolishMap		= m_WingEquipPolishMap;
	dbData.m_CGoblinData.m_MoFuZhuNengMap			= m_MoFuZhuNengMap;
	dbData.m_CGoblinData.m_WingEquipRefiningMap		= m_WingEquipRefiningMap;
	dbData.m_CGoblinData.m_VipEquipPosLevelMap		= m_VipEquipPosLevelMap;
}

void CGoblin::OnCleanUp()
{
	m_GoblinInfoMap.clear();
	m_ShouHuRefiningLeveMap.clear();
	m_WingEquipPolishMap.clear();
	m_MoFuZhuNengMap.clear();
	m_WingEquipRefiningMap.clear();
	m_VipEquipPosLevelMap.clear();
}

void CGoblin::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 550 );	// CM_GOBLIN_LEVEL_UP (0x226)
	procList.push_back( 546 );	// CM_SHOU_HU_REFINING (0x222)
	procList.push_back( 547 );	// CM_WING_EQUIP_POLISH (0x223)
	procList.push_back( 548 );	// CM_MO_FU_ZHU_NENG (0x224)
	procList.push_back( 549 );	// CM_WING_EQUIP_REFINING (0x225)
	procList.push_back( 542 );	// CM_VIP_EQUIP_POS_LEVEL (0x21E)
}

int32_t CGoblin::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch ( nProcId )
	{
	case 542:	return OnVipEquipPosLevellUp( inPacket );
	case 546:	return OnShouHuRefiningLevelUp( inPacket );
	case 547:	return OnWingEquipPolishLevelUp( inPacket );
	case 548:	return OnMoFuZhuNeng( inPacket );
	case 549:	return OnWingEquipRefiningLevelUp( inPacket );
	case 550:	return OnGoblinLevelUp( inPacket );
	default:	return ERR_SYETEM_ERR;
	}
}

// ========== Goblin Core ==========

bool CGoblin::IsGoblinType( int32_t nType )
{
	return IsGoblinTypeImpl( nType );
}

bool CGoblin::IsLeftType( int32_t nType )
{
	return IsLeftTypeImpl( nType );
}

int32_t CGoblin::GetSuitId( int32_t IsLeft )
{
	int32_t Start = IsLeft ? 29 : 32;
	int32_t End   = IsLeft ? 31 : 34;
	int32_t SuitId = 0;
	for ( int32_t i = Start; i <= End; ++i )
	{
		std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.find( i );
		if ( it == m_GoblinInfoMap.end() )
		{
			return 0;
		}
		const GoblinCfg* pCfg = CFG_DATA.GetGoblinCfg( i, it->second.GoblinLevel );
		if ( NULL == pCfg || pCfg->SuitId <= 0 )
		{
			return 0;
		}
		if ( SuitId == 0 || pCfg->SuitId < SuitId )
		{
			SuitId = pCfg->SuitId;
		}
	}
	return SuitId;
}

int32_t CGoblin::GetAddAttrRate( int32_t nType )
{
	if ( !IsGoblinTypeImpl( nType ) )
	{
		return 0;
	}
	std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.find( nType );
	if ( it != m_GoblinInfoMap.end() )
	{
		const GoblinCfg* pCfg = CFG_DATA.GetGoblinCfg( nType, it->second.GoblinLevel );
		if ( pCfg != NULL )
		{
			return pCfg->UpAttr;
		}
	}
	return 0;
}

bool CGoblin::AddGoblinRes( int8_t nType, int32_t Values )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	if ( !IsGoblinTypeImpl( nType ) || Values <= 0 )
	{
		return false;
	}
	m_GoblinInfoMap[nType].GoblinRes += Values;
	SendGoblinInfo( nType );
	return true;
}

void CGoblin::SendAllGoblinInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD1 );
	if ( NULL == packet )
	{
		return;
	}
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.begin(); it != m_GoblinInfoMap.end(); ++it )
	{
		GoblinInfo& info = it->second;
		if ( info.GoblinLevel > 0 || info.GoblinRes > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( info.GoblinLevel );
			packet->writeInt32( info.GoblinRes );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

int32_t CGoblin::OnGoblinLevelUp( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nType = inPacket->readInt8();
	if ( !IsGoblinTypeImpl( nType ) )
	{
		return ERR_SYETEM_ERR;
	}
	bool IsLeft = IsLeftTypeImpl( nType );
	int32_t OldSuitId = GetSuitId( IsLeft );
	int32_t NewLevel = m_GoblinInfoMap[nType].GoblinLevel + 1;
	const GoblinCfg* pCfg = CFG_DATA.GetGoblinCfg( nType, NewLevel );
	if ( NULL == pCfg || pCfg->ConstCurr < 0 )
	{
		return ERR_SYETEM_ERR;
	}
	if ( m_GoblinInfoMap[nType].GoblinRes < pCfg->ConstCurr )
	{
		return ERR_SYETEM_ERR;
	}
	m_GoblinInfoMap[nType].GoblinRes -= pCfg->ConstCurr;
	m_GoblinInfoMap[nType].GoblinLevel++;
	SendGoblinInfo( nType );
	m_pPlayer->RecalcAttr();
	GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nType);

	int32_t NewSuitId = GetSuitId( IsLeft );
	if ( NewSuitId != OldSuitId )
	{
		int32_t GongGaoId = IsLeft ? 477 : 478;
		Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet != NULL )
		{
			packet->writeInt32( GongGaoId );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt32( NewSuitId );
			packet->setSize( packet->getWOffset() );
			packet->setProc( SM_SEND_NOTICE_PARAM );
			GAME_SERVICE.worldBroadcast( m_pPlayer->getConnId(), packet );
		}
	}
	return ERR_OK;
}

void CGoblin::SendGoblinInfo( int32_t nType )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD0 );
	if ( NULL == packet )
	{
		return;
	}
	std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.find( nType );
	if ( it == m_GoblinInfoMap.end() )
	{
		packet->writeInt32( nType );
		packet->writeInt32( 0 );
		packet->writeInt32( 0 );
	}
	else
	{
		packet->writeInt32( nType );
		packet->writeInt32( it->second.GoblinLevel );
		packet->writeInt32( it->second.GoblinRes );
	}
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddChrAttr()
{
	for ( std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.begin(); it != m_GoblinInfoMap.end(); ++it )
	{
		int32_t AttrRate = GetAddAttrRate( it->first );
		if ( AttrRate > 0 )
		{
			// Add attribute based on cfg
			const GoblinCfg* pCfg = CFG_DATA.GetGoblinCfg( it->first, it->second.GoblinLevel );
			if ( pCfg != NULL && pCfg->m_nAddAttrType > 0 )
			{
				m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, AttrRate );
			}
		}
	}
}

void CGoblin::AppendInfo( Answer::NetPacket *packet )
{
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.begin(); it != m_GoblinInfoMap.end(); ++it )
	{
		if ( it->second.GoblinLevel > 0 || it->second.GoblinRes > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second.GoblinLevel );
			packet->writeInt32( it->second.GoblinRes );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
}


// ========== ShouHu Refining ==========

void CGoblin::SendAllShouHuRefiningInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD2 );
	if ( NULL == packet )
	{
		return;
	}
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,int32_t>::iterator it = m_ShouHuRefiningLeveMap.begin(); it != m_ShouHuRefiningLeveMap.end(); ++it )
	{
		if ( it->second > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddShouHuChrAttr()
{
	for ( std::map<int32_t,int32_t>::iterator it = m_ShouHuRefiningLeveMap.begin(); it != m_ShouHuRefiningLeveMap.end(); ++it )
	{
		const ShouHuRefiningCfg* pCfg = CFG_DATA.GetShouHuRefiningCfg( it->first, it->second );
		if ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, pCfg->m_nAddAttrValue );
		}
	}
}

void CGoblin::AppendShouHuInfo( Answer::NetPacket *packet )
{
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,int32_t>::iterator it = m_ShouHuRefiningLeveMap.begin(); it != m_ShouHuRefiningLeveMap.end(); ++it )
	{
		if ( it->second > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
}

int32_t CGoblin::GetShouHuSuitId()
{
	// Find lowest suit level using cfg
	int32_t SuitId = 0;
	for ( std::map<int32_t,int32_t>::iterator it = m_ShouHuRefiningLeveMap.begin(); it != m_ShouHuRefiningLeveMap.end(); ++it )
	{
		const ShouHuRefiningCfg* pCfg = CFG_DATA.GetShouHuRefiningCfg( it->first, it->second );
		if ( pCfg != NULL && pCfg->SuitId > 0 )
		{
			if ( SuitId == 0 || pCfg->SuitId < SuitId )
			{
				SuitId = pCfg->SuitId;
			}
		}
	}
	return SuitId;
}

int32_t CGoblin::OnShouHuRefiningLevelUp( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nType = inPacket->readInt8();
	int32_t NewLevel = m_ShouHuRefiningLeveMap[nType] + 1;
	const ShouHuRefiningCfg* pCfg = CFG_DATA.GetShouHuRefiningCfg( nType, NewLevel );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	// Check cost
	if ( pCfg->NeedGold > 0 )
	{
		if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_SHOU_HU_REFINING, 0 );
	}
	m_ShouHuRefiningLeveMap[nType] = NewLevel;
	m_pPlayer->RecalcAttr();
	SendShouHuRefiningInfo( nType );
	GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
	return ERR_OK;
}

void CGoblin::SendShouHuRefiningInfo( int32_t nType )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD3 );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( nType );
	packet->writeInt32( m_ShouHuRefiningLeveMap[nType] );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}


// ========== Wing Equip Polish ==========

void CGoblin::SendAllWingEquipPolishInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD4 );
	if ( NULL == packet )
	{
		return;
	}
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,int32_t>::iterator it = m_WingEquipPolishMap.begin(); it != m_WingEquipPolishMap.end(); ++it )
	{
		if ( it->second > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddWingEquipPolishChrAttr()
{
	for ( std::map<int32_t,int32_t>::iterator it = m_WingEquipPolishMap.begin(); it != m_WingEquipPolishMap.end(); ++it )
	{
		const WingPolishCfg* pCfg = CFG_DATA.GetWingPolishCfg( it->first, it->second );
		if ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, pCfg->m_nAddAttrValue );
		}
	}
}

void CGoblin::AppendWingEquipPolishInfo( Answer::NetPacket *packet )
{
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,int32_t>::iterator it = m_WingEquipPolishMap.begin(); it != m_WingEquipPolishMap.end(); ++it )
	{
		if ( it->second > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
}

int32_t CGoblin::GetWingEquipPolishSuitId()
{
	int32_t SuitId = 0;
	for ( std::map<int32_t,int32_t>::iterator it = m_WingEquipPolishMap.begin(); it != m_WingEquipPolishMap.end(); ++it )
	{
		const WingPolishCfg* pCfg = CFG_DATA.GetWingPolishCfg( it->first, it->second );
		if ( pCfg != NULL && pCfg->SuitId > 0 )
		{
			if ( SuitId == 0 || pCfg->SuitId < SuitId )
			{
				SuitId = pCfg->SuitId;
			}
		}
	}
	return SuitId;
}

int32_t CGoblin::OnWingEquipPolishLevelUp( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nSlot = inPacket->readInt8();
	int32_t NewLevel = m_WingEquipPolishMap[nSlot] + 1;
	const WingPolishCfg* pCfg = CFG_DATA.GetWingPolishCfg( nSlot, NewLevel );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	// Check cost
	if ( pCfg->NeedGold > 0 )
	{
		if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_WING_POLISH, 0 );
	}
	m_WingEquipPolishMap[nSlot] = NewLevel;
	m_pPlayer->RecalcAttr();
	SendWingEquipPolishInfo( nSlot );
	GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
	return ERR_OK;
}

void CGoblin::SendWingEquipPolishInfo( int32_t nSlot )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD5 );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( nSlot );
	packet->writeInt32( m_WingEquipPolishMap[nSlot] );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}


// ========== MoFu ZhuNeng ==========

void CGoblin::SendAllMoFuZhuNengInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD6 );
	if ( NULL == packet )
	{
		return;
	}
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,int32_t>::iterator it = m_MoFuZhuNengMap.begin(); it != m_MoFuZhuNengMap.end(); ++it )
	{
		if ( it->second > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

int32_t CGoblin::GetMoFuChrAttr( int32_t Slot )
{
	std::map<int32_t,int32_t>::iterator it = m_MoFuZhuNengMap.find( Slot );
	if ( it == m_MoFuZhuNengMap.end() )
	{
		return 0;
	}
	const MoFuZhuNengCfg* pCfg = CFG_DATA.GetMoFuZhuNengCfg( Slot, it->second );
	if ( pCfg != NULL && pCfg->m_nAddAttrType > 0 )
	{
		return pCfg->m_nAddAttrValue;
	}
	return 0;
}

int32_t CGoblin::OnMoFuZhuNeng( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nSlot = inPacket->readInt8();
	int32_t NewLevel = m_MoFuZhuNengMap[nSlot] + 1;
	const MoFuZhuNengCfg* pCfg = CFG_DATA.GetMoFuZhuNengCfg( nSlot, NewLevel );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	// Check cost
	if ( pCfg->NeedGold > 0 )
	{
		if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_MO_FU_ZHU_NENG, 0 );
	}
	m_MoFuZhuNengMap[nSlot] = NewLevel;
	m_pPlayer->RecalcAttr();
	SendMoFuZhuNengInfo( nSlot );
	GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
	return ERR_OK;
}

void CGoblin::SendMoFuZhuNengInfo( int32_t nSlot )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD7 );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( nSlot );
	packet->writeInt32( m_MoFuZhuNengMap[nSlot] );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}


// ========== Wing Equip Refining ==========

void CGoblin::SendAllWingEquipRefiningInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD8 );
	if ( NULL == packet )
	{
		return;
	}
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.begin(); it != m_WingEquipRefiningMap.end(); ++it )
	{
		if ( it->second > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddWingEquipRefiningChrAttr()
{
	for ( std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.begin(); it != m_WingEquipRefiningMap.end(); ++it )
	{
		const WingRefiningCfg* pCfg = CFG_DATA.GetWingRefiningCfg( it->first, it->second );
		if ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, pCfg->m_nAddAttrValue );
		}
	}
}

void CGoblin::AppendWingEquipRefiningInfo( Answer::NetPacket *packet )
{
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.begin(); it != m_WingEquipRefiningMap.end(); ++it )
	{
		if ( it->second > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
}

int32_t CGoblin::GetWingEquipRefiningSuitId()
{
	int32_t SuitId = 0;
	for ( std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.begin(); it != m_WingEquipRefiningMap.end(); ++it )
	{
		const WingRefiningCfg* pCfg = CFG_DATA.GetWingRefiningCfg( it->first, it->second );
		if ( pCfg != NULL && pCfg->SuitId > 0 )
		{
			if ( SuitId == 0 || pCfg->SuitId < SuitId )
			{
				SuitId = pCfg->SuitId;
			}
		}
	}
	return SuitId;
}

int32_t CGoblin::OnWingEquipRefiningLevelUp( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nSlot = inPacket->readInt8();
	int32_t NewLevel = m_WingEquipRefiningMap[nSlot] + 1;
	const WingRefiningCfg* pCfg = CFG_DATA.GetWingRefiningCfg( nSlot, NewLevel );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	// Check cost
	if ( pCfg->NeedGold > 0 )
	{
		if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_WING_REFINING, 0 );
	}
	m_WingEquipRefiningMap[nSlot] = NewLevel;
	m_pPlayer->RecalcAttr();
	SendWingEquipRefiningInfo( nSlot );
	GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
	return ERR_OK;
}

void CGoblin::SendWingEquipRefiningInfo( int32_t nSlot )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CD9 );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( nSlot );
	packet->writeInt32( m_WingEquipRefiningMap[nSlot] );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

int32_t CGoblin::GetWingEquipRefiningAttr( int32_t nSlot )
{
	std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.find( nSlot );
	if ( it == m_WingEquipRefiningMap.end() )
	{
		return 0;
	}
	const WingRefiningCfg* pCfg = CFG_DATA.GetWingRefiningCfg( nSlot, it->second );
	if ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
	{
		return pCfg->m_nAddAttrValue;
	}
	return 0;
}


// ========== Vip Equip Pos Level ==========

void CGoblin::SendAllVipEquipPosLevelInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CDA );
	if ( NULL == packet )
	{
		return;
	}
	int32_t Count = 0;
	int32_t Oldoffset = packet->getWOffset();
	packet->writeInt32( 0 );
	for ( std::map<int32_t,int32_t>::iterator it = m_VipEquipPosLevelMap.begin(); it != m_VipEquipPosLevelMap.end(); ++it )
	{
		if ( it->second > 0 )
		{
			packet->writeInt32( it->first );
			packet->writeInt32( it->second );
			++Count;
		}
	}
	int32_t NewWoffset = packet->getWOffset();
	packet->setWOffset( Oldoffset );
	packet->writeInt32( Count );
	packet->setWOffset( NewWoffset );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddVipEquipPosLevelCharAttr()
{
	int32_t SuitId = GetVipEquipPosLevelSuitId();
	if ( SuitId > 0 )
	{
		const VipEQuipPosSuit* pCfg = CFG_DATA.GetVipEQuipPosSuit( SuitId );
		if ( pCfg != NULL && pCfg->nTalentId > 0 && pCfg->TalentLevel > 0 )
		{
			m_pPlayer->GetCharSkill().AddOtherSkill( pCfg->nTalentId, pCfg->TalentLevel );
		}
	}
	for ( std::map<int32_t,int32_t>::iterator it = m_VipEquipPosLevelMap.begin(); it != m_VipEquipPosLevelMap.end(); ++it )
	{
		const VipEquipPosLevelCfg* pCfg = CFG_DATA.GetVipEquipPosLevelCfg( it->first, it->second );
		if ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, pCfg->m_nAddAttrValue );
		}
	}
}

void CGoblin::SendVipEquipPosLevelInfo( int32_t nSlot )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, 0x2CDB );
	if ( NULL == packet )
	{
		return;
	}
	packet->writeInt32( nSlot );
	packet->writeInt32( m_VipEquipPosLevelMap[nSlot] );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet );
}

int32_t CGoblin::GetVipEquipPosLevelSuitId()
{
	int32_t SuitId = 0;
	for ( std::map<int32_t,int32_t>::iterator it = m_VipEquipPosLevelMap.begin(); it != m_VipEquipPosLevelMap.end(); ++it )
	{
		const VipEquipPosLevelCfg* pCfg = CFG_DATA.GetVipEquipPosLevelCfg( it->first, it->second );
		if ( pCfg != NULL && pCfg->SuitId > 0 )
		{
			if ( SuitId == 0 || pCfg->SuitId < SuitId )
			{
				SuitId = pCfg->SuitId;
			}
		}
	}
	return SuitId;
}

int32_t CGoblin::OnVipEquipPosLevellUp( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t nSlot = inPacket->readInt8();
	int32_t NewLevel = m_VipEquipPosLevelMap[nSlot] + 1;
	const VipEquipPosLevelCfg* pCfg = CFG_DATA.GetVipEquipPosLevelCfg( nSlot, NewLevel );
	if ( NULL == pCfg )
	{
		return ERR_SYETEM_ERR;
	}
	// Check cost
	if ( pCfg->NeedGold > 0 )
	{
		if ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
		{
			return ERR_SYETEM_ERR;
		}
		m_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_VIP_EQUIP_POS, 0 );
	}
	m_VipEquipPosLevelMap[nSlot] = NewLevel;
	m_pPlayer->RecalcAttr();
	SendVipEquipPosLevelInfo( nSlot );
	GAME_SERVICE.replySuccess(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0);
	return ERR_OK;
}
