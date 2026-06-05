#include "stdafx.h"
#include "ShenWei.h"
#include "Player.h"
#include "CfgData.h"
#include "FunctionOpen.h"
#include "RankMirror.h"
#include "GameService.h"

CShenWei::CShenWei()
{
}

CShenWei::~CShenWei()
{
}

void CShenWei::OnDaySwitch( int32_t nDiffDays )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	while ( nDiffDays > 0 )
	{
		int32_t nLevel = GetShenWeiLevel();
		const CfgCachet* pCfg = CFG_DATA.GetCfgCachet( nLevel );
		if ( NULL == pCfg || pCfg->nDeduct <= 0 )
		{
			break;
		}
		m_pPlayer->DecCurrency( CURRENCY_HONOR, pCfg->nDeduct, HCR_HALL_DAY_SWITCH, 0 );
		--nDiffDays;
	}
}

void CShenWei::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 188 ) )
	{
		return;
	}

	int32_t nLevel = GetShenWeiLevel();
	const CfgCachet* pCfg = CFG_DATA.GetCfgCachet( nLevel );
	if ( NULL == pCfg )
	{
		return;
	}

	for ( AddAttrList::const_iterator it = pCfg->lAttrList.begin(); it != pCfg->lAttrList.end(); ++it )
	{
		m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue );
	}
}

int32_t CShenWei::GetRankAttr( int64_t Exp )
{
	if ( GAME_SERVICE.getLine() == 9 )
	{
		return 0;
	}

	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	if ( m_pPlayer->GetCurrency( CURRENCY_HONOR ) <= Exp )
	{
		return 0;
	}

	CharId_t cid = m_pPlayer->getCid();
	int32_t nWeiWangIndex = CRankMirror::instance()->GetWeiWangIndex( cid );

	switch ( nWeiWangIndex )
	{
	case 1:
		return 12;
	case 2:
		return 10;
	case 3:
		return 8;
	default:
		return 6;
	}
}

int32_t CShenWei::GetShenWeiLevel()
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	int64_t nHonor = m_pPlayer->GetCurrency( CURRENCY_HONOR );
	return CFG_DATA.GetCachetLevel( nHonor );
}
