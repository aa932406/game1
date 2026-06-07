#include "stdafx.h"
#include "CXingMai.h"
#include "GameService.h"
#include "Player.h"
#include "Task.h"
#include "DBService.h"
#include "ItemHelper.h"
#include "Timer.h"

using namespace Answer;

CXingMai::CXingMai()
{
}

CXingMai::~CXingMai()
{
}

void CXingMai::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 300 );
	procList.push_back( 301 );
}

int32_t CXingMai::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	if ( nProcId == 300 )
	{
		return OnXingMaiLevelUp( inPacket );
	}
	if ( nProcId == 301 )
	{
		return OnXingMaiSlotActive( inPacket );
	}

	return ERR_INVALID_DATA;
}

int32_t CXingMai::OnXingMaiLevelUp( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int32_t CurLevel = m_pPlayer->getRecord( 1147 );
	const XingMaiCfg* CurCfg = CFG_DATA.GetXingMaiCfg( CurLevel );
	const XingMaiCfg* NextCfg = CFG_DATA.GetXingMaiCfg( CurLevel + 1 );

	if ( NULL == CurCfg || NULL == NextCfg )
	{
		return ERR_INVALID_DATA;
	}

	if ( NextCfg->PlayerLevel > m_pPlayer->getLevel() )
	{
		return ERR_INVALID_DATA;
	}

	if ( CurCfg->NeedBossScore <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_BOSS, CurCfg->NeedBossScore, SCR_XING_MAI_LEVEL_UP, 0 ) )
	{
		return ERR_INVALID_DATA;
	}

	m_pPlayer->updateRecord( 1147, CurLevel + 1 );
	m_pPlayer->RecalcAttr();

	if ( NextCfg->GongGaoId > 0 )
	{
		Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::Answer::PACK_DISPATCH, 0x2CD6 );
		if ( packet != NULL )
		{
			packet->writeInt32( NextCfg->GongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( CurLevel + 1 );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( m_pPlayer->getConnId(), packet );
		}
	}

	m_pPlayer->GetTask().updateTaskCount( 38, 0 );

	// Add platform log
	important_system_log stu;
	memset( &stu, 0, sizeof(stu) );
	stu.log_Sid = m_pPlayer->getSid();
	stu.log_time = m_pPlayer->getNow();
	m_pPlayer->GetPassport( stu.passport );
	stu.cid = m_pPlayer->getCid();
	stu.name = m_pPlayer->getName();
	stu.up_time = m_pPlayer->getNow();
	stu.sys_name = 3;
	stu.oper_id = 1;
	stu.level = CurLevel + 1;
	DB_SERVICE.AddPlatformLog( m_pPlayer->getConnId(), PLDT_SYSTEM, &stu );

	return ERR_OK;
}

int32_t CXingMai::OnXingMaiSlotActive( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_INVALID_DATA;
	}

	int8_t nIndex = inPacket->readInt8();
	const CfgXingMaiSlot* pCfgSlot = CFG_DATA.GetXingMaiSlot( nIndex );

	if ( NULL == pCfgSlot )
	{
		return ERR_INVALID_DATA;
	}

	if ( isSlotActived( nIndex ) )
	{
		return ERR_INVALID_DATA;
	}

	if ( m_pPlayer->GetOperateLimit().GetLimitCount( 1147 ) < pCfgSlot->nLevel )
	{
		return ERR_INVALID_DATA;
	}

	if ( pCfgSlot->nScore <= 0 )
	{
		return ERR_INVALID_DATA;
	}

	if ( !m_pPlayer->DecCurrency( CURRENCY_BOSS, pCfgSlot->nScore, SCR_XING_MAI_ACTIVE_SLOT, 0 ) )
	{
		return ERR_INVALID_DATA;
	}

	activeSlot( nIndex );

	return GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nIndex );
}

void CXingMai::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	int32_t CurLevel = m_pPlayer->getRecord( 1147 );
	const XingMaiCfg* CurCfg = CFG_DATA.GetXingMaiCfg( CurLevel );

	if ( NULL == CurCfg )
	{
		return;
	}

	for ( AddAttrList::const_iterator it = CurCfg->AttrList.begin(); it != CurCfg->AttrList.end(); ++it )
	{
		m_pPlayer->AddAttrValue( static_cast<CObjAttrs::Index_T>( it->m_nAddAttrType ), it->m_nAddAttrValue );

		if ( it->m_nAddAttrType == 45 )
		{
			m_pPlayer->AddBeiGongAttr( 4, it->m_nAddAttrValue );
		}
	}
}

int32_t CXingMai::GetMaxBossScore()
{
	int32_t CurLevel = m_pPlayer->getRecord( 1147 );
	const XingMaiCfg* CurCfg = CFG_DATA.GetXingMaiCfg( CurLevel );

	if ( NULL != CurCfg )
	{
		return CurCfg->BossScoreLimit;
	}

	return 0;
}

bool CXingMai::IsXingMaiSlotActived( int8_t nEquipSlot )
{
	if ( !isSlotActived( nEquipSlot ) )
	{
		return false;
	}

	int8_t XingMaiIndex = nEquipSlot; // For now, use the same index
	return isSlotActived( XingMaiIndex );
}

void CXingMai::activeSlot( int8_t nIndex )
{
	int32_t nState = ( 1 << nIndex ) | m_pPlayer->GetOperateLimit().GetLimitCount( 1157 );
	m_pPlayer->GetOperateLimit().UpdateLimitCount( 1157, nState );
}

bool CXingMai::isSlotActived( int8_t nIndex )
{
	return ( m_pPlayer->GetOperateLimit().GetLimitCount( 1157 ) >> nIndex ) & 1;
}
