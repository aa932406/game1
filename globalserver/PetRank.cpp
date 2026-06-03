#include "stdafx.h"

#include "PetRank.h"
#include "PetManager.h"
#include "SocialService.h"

#define PET_RANK_REFRESH_TIME	1000		// 排行榜刷新延迟
#define PET_RANK_SIZE			100			// 排行榜最大显示人数

using namespace Answer;


bool PetPointsRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
{
	if ( _Left == NULL || _Right == NULL )
	{
		return false;
	}
	return _Left->GetPoints() > _Right->GetPoints();
}

// bool PetStartHPRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
// {
// 	if ( _Left == NULL || _Right == NULL )
// 	{
// 		return false;
// 	}
// 	return _Left->GetBaseAttr( PET_ATTR_START_HP ) > _Right->GetBaseAttr( PET_ATTR_START_HP );
// }
// 
// bool PetStartPhyAtkMinRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
// {
// 	if ( _Left == NULL || _Right == NULL )
// 	{
// 		return false;
// 	}
// 	return _Left->GetBaseAttr( PET_ATTR_START_PHY_ATK_MIN ) > _Right->GetBaseAttr( PET_ATTR_START_PHY_ATK_MIN );
// }
// 
// bool PetStartPhyAtkMaxRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
// {
// 	if ( _Left == NULL || _Right == NULL )
// 	{
// 		return false;
// 	}
// 	return _Left->GetBaseAttr( PET_ATTR_START_PHY_ATK_MAX ) > _Right->GetBaseAttr( PET_ATTR_START_PHY_ATK_MAX );
// }

// bool PetStartPhyDefRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
// {
// 	if ( _Left == NULL || _Right == NULL )
// 	{
// 		return false;
// 	}
// 	return _Left->GetBaseAttr( PET_ATTR_START_PHY_DEF ) > _Right->GetBaseAttr( PET_ATTR_START_PHY_DEF );
// }
// 
// bool PetStartMagAtkMinRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
// {
// 	if ( _Left == NULL || _Right == NULL )
// 	{
// 		return false;
// 	}
// 	return _Left->GetBaseAttr( PET_ATTR_START_MAG_ATK_MIN ) > _Right->GetBaseAttr( PET_ATTR_START_MAG_ATK_MIN );
// }
// 
// bool PetStartMagAtkMaxRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
// {
// 	if ( _Left == NULL || _Right == NULL )
// 	{
// 		return false;
// 	}
// 	return _Left->GetBaseAttr( PET_ATTR_START_MAG_ATK_MAX ) > _Right->GetBaseAttr( PET_ATTR_START_MAG_ATK_MAX );
// }
// 
// bool PetStartMagDefRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
// {
// 	if ( _Left == NULL || _Right == NULL )
// 	{
// 		return false;
// 	}
// 	return _Left->GetBaseAttr( PET_ATTR_START_MAG_DEF ) > _Right->GetBaseAttr( PET_ATTR_START_MAG_DEF );
// }

bool PetGrowHPRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
{
	if ( _Left == NULL || _Right == NULL )
	{
		return false;
	}
	return _Left->GetBaseAttr( PET_ATTR_GROW_HP ) > _Right->GetBaseAttr( PET_ATTR_GROW_HP );
}

bool PetGrowPhyAtkMinRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
{
	if ( _Left == NULL || _Right == NULL )
	{
		return false;
	}
	return _Left->GetBaseAttr( PET_ATTR_GROW_PHY_ATK_MIN ) > _Right->GetBaseAttr( PET_ATTR_GROW_PHY_ATK_MIN );
}

bool PetGrowPhyAtkMaxRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
{
	if ( _Left == NULL || _Right == NULL )
	{
		return false;
	}
	return _Left->GetBaseAttr( PET_ATTR_GROW_PHY_ATK_MAX ) > _Right->GetBaseAttr( PET_ATTR_GROW_PHY_ATK_MAX );
}

bool PetGrowPhyDefRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
{
	if ( _Left == NULL || _Right == NULL )
	{
		return false;
	}
	return _Left->GetBaseAttr( PET_ATTR_GROW_PHY_DEF ) > _Right->GetBaseAttr( PET_ATTR_GROW_PHY_DEF );
}

bool PetGrowMagAtkMinRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
{
	if ( _Left == NULL || _Right == NULL )
	{
		return false;
	}
	return _Left->GetBaseAttr( PET_ATTR_GROW_MAG_ATK_MIN ) > _Right->GetBaseAttr( PET_ATTR_GROW_MAG_ATK_MIN );
}

bool PetGrowMagAtkMaxRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
{
	if ( _Left == NULL || _Right == NULL )
	{
		return false;
	}
	return _Left->GetBaseAttr( PET_ATTR_GROW_MAG_ATK_MAX ) > _Right->GetBaseAttr( PET_ATTR_GROW_MAG_ATK_MAX );
}

bool PetGrowMagDefRankGreater::operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const
{
	if ( _Left == NULL || _Right == NULL )
	{
		return false;
	}
	return _Left->GetBaseAttr( PET_ATTR_GROW_MAG_DEF ) > _Right->GetBaseAttr( PET_ATTR_GROW_MAG_DEF );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPetRank::CPetRank()
{

}

CPetRank::~CPetRank()
{

}

void CPetRank::AddPet( CSocialPet* pPet, bool bNeedRefresh )
{
	if ( NULL == pPet )
	{
		return;
	}

	m_pointsRank.insert( pPet );
// 	m_startHPRank.insert( pPet );
// 	m_startPhyAtkMinRank.insert( pPet );
// 	m_startPhyAtkMaxRank.insert( pPet );
// 	m_startPhyDefRank.insert( pPet );
// 	m_startMagAtkMinRank.insert( pPet );
// 	m_startMagAtkMaxRank.insert( pPet );
// 	m_startMagDefRank.insert( pPet );
	m_growHPRank.insert( pPet );
	m_growPhyAtkMinRank.insert( pPet );
	m_growPhyAtkMaxRank.insert( pPet );
	m_growPhyDefRank.insert( pPet );
	m_growMagAtkMinRank.insert( pPet );
	m_growMagAtkMaxRank.insert( pPet );
	m_growMagDefRank.insert( pPet );

	if ( bNeedRefresh )
	{
		RefreshRank();
	}
}

void CPetRank::DelPet( CSocialPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}

	m_pointsRank.erase( pPet );
// 	m_startHPRank.erase( pPet );
// 	m_startPhyAtkMinRank.erase( pPet );
// 	m_startPhyAtkMaxRank.erase( pPet );
// 	m_startPhyDefRank.erase( pPet );
// 	m_startMagAtkMinRank.erase( pPet );
// 	m_startMagAtkMaxRank.erase( pPet );
// 	m_startMagDefRank.erase( pPet );
	m_growHPRank.erase( pPet );
	m_growPhyAtkMinRank.erase( pPet );
	m_growPhyAtkMaxRank.erase( pPet );
	m_growPhyDefRank.erase( pPet );
	m_growMagAtkMinRank.erase( pPet );
	m_growMagAtkMaxRank.erase( pPet );
	m_growMagDefRank.erase( pPet );

	RefreshRank();
}

void CPetRank::UpdatePet( CSocialPet* pPet, const SocialPetData& pet )
{
	if ( NULL == pPet )
	{
		return;
	}

	int32_t nFlag = pet.nRankFlag;
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_HP			 ) )	{	m_startHPRank.erase( pPet );			}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_PHY_ATK_MIN ) )	{	m_startPhyAtkMinRank.erase( pPet );		}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_PHY_ATK_MAX ) )	{	m_startPhyAtkMaxRank.erase( pPet );		}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_PHY_DEF	 ) )	{	m_startPhyDefRank.erase( pPet );		}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_MAG_ATK_MIN ) )	{	m_startMagAtkMinRank.erase( pPet );		}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_MAG_ATK_MAX ) )	{	m_startMagAtkMaxRank.erase( pPet );		}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_MAG_DEF	 ) )	{	m_startMagDefRank.erase( pPet );		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_HP			 ) )	{	m_growHPRank.erase( pPet );				}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_PHY_ATK_MIN	 ) )	{	m_growPhyAtkMinRank.erase( pPet );		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_PHY_ATK_MAX	 ) )	{	m_growPhyAtkMaxRank.erase( pPet );		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_PHY_DEF		 ) )	{	m_growPhyDefRank.erase( pPet );			}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_MAG_ATK_MIN	 ) )	{	m_growMagAtkMinRank.erase( pPet );		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_MAG_ATK_MAX	 ) )	{	m_growMagAtkMaxRank.erase( pPet );		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_MAG_DEF		 ) )	{	m_growMagDefRank.erase( pPet );			}
	m_pointsRank.erase( pPet );

	pPet->Set( pet );	// 更新必须在此处，不然set中无法删除原节点

// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_HP			 ) )	{	m_startHPRank.insert( pPet );			refreshStartHPRank();			}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_PHY_ATK_MIN ) )	{	m_startPhyAtkMinRank.insert( pPet );	refreshStartPhyAtkMinRank();	}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_PHY_ATK_MAX ) )	{	m_startPhyAtkMaxRank.insert( pPet );	refreshStartPhyAtkMaxRank();	}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_PHY_DEF	 ) )	{	m_startPhyDefRank.insert( pPet );		refreshStartPhyDefRank();		}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_MAG_ATK_MIN ) )	{	m_startMagAtkMinRank.insert( pPet );	refreshStartMagAtkMinRank();	}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_MAG_ATK_MAX ) )	{	m_startMagAtkMaxRank.insert( pPet );	refreshStartMagAtkMaxRank();	}
// 	if ( checkRefreshFlag( nFlag, PET_ATTR_START_MAG_DEF	 ) )	{	m_startMagDefRank.insert( pPet );		refreshStartMagDefRank();		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_HP			 ) )	{	m_growHPRank.insert( pPet );			refreshGrowHPRank();			}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_PHY_ATK_MIN	 ) )	{	m_growPhyAtkMinRank.insert( pPet );		refreshGrowPhyAtkMinRank();		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_PHY_ATK_MAX	 ) )	{	m_growPhyAtkMaxRank.insert( pPet );		refreshGrowPhyAtkMaxRank();		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_PHY_DEF		 ) )	{	m_growPhyDefRank.insert( pPet );		refreshGrowPhyDefRank();		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_MAG_ATK_MIN	 ) )	{	m_growMagAtkMinRank.insert( pPet );		refreshGrowMagAtkMinRank();		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_MAG_ATK_MAX	 ) )	{	m_growMagAtkMaxRank.insert( pPet );		refreshGrowMagAtkMaxRank();		}
	if ( checkRefreshFlag( nFlag, PET_ATTR_GROW_MAG_DEF		 ) )	{	m_growMagDefRank.insert( pPet );		refreshGrowMagDefRank();		}
	m_pointsRank.erase( pPet );
	m_pointsRank.insert( pPet );

	refreshPointsRank();

	sendDirty();
}

bool CPetRank::checkRefreshFlag( int32_t flag, PET_ATTR attr ) const
{
	return ( flag & ( 1 << attr ) ) != 0;
}

void CPetRank::RefreshRank()
{
	refreshPointsRank();
// 	refreshStartHPRank();
// 	refreshStartPhyAtkMinRank();
// 	refreshStartPhyAtkMaxRank();
// 	refreshStartPhyDefRank();
// 	refreshStartMagAtkMinRank();
// 	refreshStartMagAtkMaxRank();
// 	refreshStartMagDefRank();
	refreshGrowHPRank();
	refreshGrowPhyAtkMinRank();	
	refreshGrowPhyAtkMaxRank();	
	refreshGrowPhyDefRank();
	refreshGrowMagAtkMinRank();	
	refreshGrowMagAtkMaxRank();	
	refreshGrowMagDefRank();

	sendDirty();
}

void CPetRank::AppendRankList( int8_t nRankType, Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	uint32_t nOffset = packet->getWOffset();
	int8_t nCount = 0;
	packet->writeInt8( nCount );
	switch( nRankType )
	{
	case PRT_POINTS:			appendPointsRankList( packet, nCount );				break;
// 	case PRT_START_HP:			appendStartHPRankList( packet, nCount );			break;
// 	case PRT_START_PHY_ATK_MIN:	appendStartPhyAtkMinRankList( packet, nCount );		break;
// 	case PRT_START_PHY_ATK_MAX:	appendStartPhyAtkMaxRankList( packet, nCount );		break;
// 	case PRT_START_PHY_DEF:		appendStartPhyDefRankList( packet, nCount );		break;
// 	case PRT_START_MAG_ATK_MIN:	appendStartMagAtkMinRankList( packet, nCount );		break;
// 	case PRT_START_MAG_ATK_MAX:	appendStartMagAtkMaxRankList( packet, nCount );		break;
// 	case PRT_START_MAG_DEF:		appendStartMagDefRankList( packet, nCount );		break;
	case PRT_GROW_HP:			appendGrowHPRankList( packet, nCount );				break;
	case PRT_GROW_PHY_ATK_MIN:	appendGrowPhyAtkMinRankList( packet, nCount );		break;
	case PRT_GROW_PHY_ATK_MAX:	appendGrowPhyAtkMaxRankList( packet, nCount );		break;
	case PRT_GROW_PHY_DEF:		appendGrowPhyDefRankList( packet, nCount );			break;
	case PRT_GROW_MAG_ATK_MIN:	appendGrowMagAtkMinRankList( packet, nCount );		break;
	case PRT_GROW_MAG_ATK_MAX:	appendGrowMagAtkMaxRankList( packet, nCount );		break;
	case PRT_GROW_MAG_DEF:		appendGrowMagDefRankList( packet, nCount );			break;
	default:break;
	}
	uint32_t nOldOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt8( nCount );
	packet->setWOffset( nOldOffset );
}

void CPetRank::refreshPointsRank()
{
	int32_t nIndex = 1;
	PetPointsRank::iterator iter = m_pointsRank.begin();
	PetPointsRank::iterator eiter = m_pointsRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( pPet != NULL )
		{
			if ( pPet->SetPointsRankIndex( nIndex ) )
			{
				addDirty( pPet->GetPetId() );
			}
			++nIndex;
		}
	}
}

// void CPetRank::refreshStartHPRank()
// {
// 	int32_t nIndex = 1;
// 	PetStartHPRank::iterator iter = m_startHPRank.begin();
// 	PetStartHPRank::iterator eiter = m_startHPRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( pPet != NULL )
// 		{
// 			if ( pPet->SetRankIndex( PET_ATTR_START_HP, nIndex ) )
// 			{
// 				addDirty( pPet->GetPetId() );
// 			}
// 			++nIndex;
// 		}
// 	}
// }

// void CPetRank::refreshStartPhyAtkMinRank()
// {
// 	int32_t nIndex = 1;
// 	PetStartPhyAtkMinRank::iterator iter = m_startPhyAtkMinRank.begin();
// 	PetStartPhyAtkMinRank::iterator eiter = m_startPhyAtkMinRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( pPet != NULL )
// 		{
// 			if ( pPet->SetRankIndex( PET_ATTR_START_PHY_ATK_MIN, nIndex ) )
// 			{
// 				addDirty( pPet->GetPetId() );
// 			}
// 			++nIndex;
// 		}
// 	}
// }

// void CPetRank::refreshStartPhyAtkMaxRank()
// {
// 	int32_t nIndex = 1;
// 	PetStartPhyAtkMaxRank::iterator iter = m_startPhyAtkMaxRank.begin();
// 	PetStartPhyAtkMaxRank::iterator eiter = m_startPhyAtkMaxRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( pPet != NULL )
// 		{
// 			if ( pPet->SetRankIndex( PET_ATTR_START_PHY_ATK_MAX, nIndex ) )
// 			{
// 				addDirty( pPet->GetPetId() );
// 			}
// 			++nIndex;
// 		}
// 	}
// }

// void CPetRank::refreshStartPhyDefRank()
// {
// 	int32_t nIndex = 1;
// 	PetStartPhyDefRank::iterator iter = m_startPhyDefRank.begin();
// 	PetStartPhyDefRank::iterator eiter = m_startPhyDefRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( pPet != NULL )
// 		{
// 			if ( pPet->SetRankIndex( PET_ATTR_START_PHY_DEF, nIndex )  )
// 			{
// 				addDirty( pPet->GetPetId() );
// 			}
// 			++nIndex;
// 		}
// 	}
// }

// void CPetRank::refreshStartMagAtkMinRank()
// {
// 	int32_t nIndex = 1;
// 	PetStartMagAtkMinRank::iterator iter = m_startMagAtkMinRank.begin();
// 	PetStartMagAtkMinRank::iterator eiter = m_startMagAtkMinRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( pPet != NULL )
// 		{
// 			if ( pPet->SetRankIndex( PET_ATTR_START_MAG_ATK_MIN, nIndex ) )
// 			{
// 				addDirty( pPet->GetPetId() );
// 			}
// 			++nIndex;
// 		}
// 	}
// }

// void CPetRank::refreshStartMagAtkMaxRank()
// {
// 	int32_t nIndex = 1;
// 	PetStartMagAtkMaxRank::iterator iter = m_startMagAtkMaxRank.begin();
// 	PetStartMagAtkMaxRank::iterator eiter = m_startMagAtkMaxRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( pPet != NULL )
// 		{
// 			if ( pPet->SetRankIndex( PET_ATTR_START_MAG_ATK_MAX, nIndex ) )
// 			{
// 				addDirty( pPet->GetPetId() );
// 			}
// 			++nIndex;
// 		}
// 	}
// }

// void CPetRank::refreshStartMagDefRank()
// {
// 	int32_t nIndex = 1;
// 	PetStartMagDefRank::iterator iter = m_startMagDefRank.begin();
// 	PetStartMagDefRank::iterator eiter = m_startMagDefRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( pPet != NULL )
// 		{
// 			if ( pPet->SetRankIndex( PET_ATTR_START_MAG_DEF, nIndex ) )
// 			{
// 				addDirty( pPet->GetPetId() );
// 			}
// 			++nIndex;
// 		}
// 	}
// }

void CPetRank::refreshGrowHPRank()
{
	int32_t nIndex = 1;
	PetGrowHPRank::iterator iter = m_growHPRank.begin();
	PetGrowHPRank::iterator eiter = m_growHPRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( pPet != NULL )
		{
			if ( pPet->SetRankIndex( PET_ATTR_GROW_HP, nIndex ) )
			{
				addDirty( pPet->GetPetId() );
			}
			++nIndex;
		}
	}
}

void CPetRank::refreshGrowPhyAtkMinRank()
{
	int32_t nIndex = 1;
	PetGrowPhyAtkMinRank::iterator iter = m_growPhyAtkMinRank.begin();
	PetGrowPhyAtkMinRank::iterator eiter = m_growPhyAtkMinRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( pPet != NULL )
		{
			if ( pPet->SetRankIndex( PET_ATTR_GROW_PHY_ATK_MIN, nIndex ) )
			{
				addDirty( pPet->GetPetId() );
			}
			++nIndex;
		}
	}
}

void CPetRank::refreshGrowPhyAtkMaxRank()
{
	int32_t nIndex = 1;
	PetGrowPhyAtkMaxRank::iterator iter = m_growPhyAtkMaxRank.begin();
	PetGrowPhyAtkMaxRank::iterator eiter = m_growPhyAtkMaxRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( pPet != NULL )
		{
			if ( pPet->SetRankIndex( PET_ATTR_GROW_PHY_ATK_MAX, nIndex ) )
			{
				addDirty( pPet->GetPetId() );
			}
			++nIndex;
		}
	}
}

void CPetRank::refreshGrowPhyDefRank()
{
	int32_t nIndex = 1;
	PetGrowPhyDefRank::iterator iter = m_growPhyDefRank.begin();
	PetGrowPhyDefRank::iterator eiter = m_growPhyDefRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( pPet != NULL )
		{
			if ( pPet->SetRankIndex( PET_ATTR_GROW_PHY_DEF, nIndex ) )
			{
				addDirty( pPet->GetPetId() );
			}
			++nIndex;
		}
	}
}

void CPetRank::refreshGrowMagAtkMinRank()
{
	int32_t nIndex = 1;
	PetGrowMagAtkMinRank::iterator iter = m_growMagAtkMinRank.begin();
	PetGrowMagAtkMinRank::iterator eiter = m_growMagAtkMinRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( pPet != NULL )
		{
			if ( pPet->SetRankIndex( PET_ATTR_GROW_MAG_ATK_MIN, nIndex ) )
			{
				addDirty( pPet->GetPetId() );
			}
			++nIndex;
		}
	}
}

void CPetRank::refreshGrowMagAtkMaxRank()
{
	int32_t nIndex = 1;
	PetGrowMagAtkMaxRank::iterator iter = m_growMagAtkMaxRank.begin();
	PetGrowMagAtkMaxRank::iterator eiter = m_growMagAtkMaxRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( pPet != NULL )
		{
			if ( pPet->SetRankIndex( PET_ATTR_GROW_MAG_ATK_MAX, nIndex ) )
			{
				addDirty( pPet->GetPetId() );
			}
			++nIndex;
		}
	}
}

void CPetRank::refreshGrowMagDefRank()
{
	int32_t nIndex = 1;
	PetGrowMagDefRank::iterator iter = m_growMagDefRank.begin();
	PetGrowMagDefRank::iterator eiter = m_growMagDefRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( pPet != NULL )
		{
			if ( pPet->SetRankIndex( PET_ATTR_GROW_MAG_DEF, nIndex ) )
			{
				addDirty( pPet->GetPetId() );
			}
			++nIndex;
		}
	}
}

void CPetRank::appendPointsRankList( Answer::NetPacket* packet, int8_t& nCount )
{
	PetPointsRank::const_iterator iter = m_pointsRank.begin();
	PetPointsRank::const_iterator eiter = m_pointsRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}
		++nCount;

		packet->writeInt8( nCount );
		pPet->AppendRankList( packet );
		packet->writeInt32( pPet->GetPoints() );

		if ( nCount >= PET_RANK_SIZE )
		{
			break;
		}
	}
}

// void CPetRank::appendStartHPRankList( Answer::NetPacket* packet, int8_t& nCount )
// {
// 	PetStartHPRank::const_iterator iter = m_startHPRank.begin();
// 	PetStartHPRank::const_iterator eiter = m_startHPRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( NULL == pPet )
// 		{
// 			continue;
// 		}
// 		++nCount;
// 
// 		packet->writeInt8( nCount );
// 		pPet->AppendRankList( packet );
// 		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_START_HP ) );
// 
// 		if ( nCount >= PET_RANK_SIZE )
// 		{
// 			break;
// 		}
// 	}
// }

// void CPetRank::appendStartPhyAtkMinRankList( Answer::NetPacket* packet, int8_t& nCount )
// {
// 	PetStartPhyAtkMinRank::const_iterator iter = m_startPhyAtkMinRank.begin();
// 	PetStartPhyAtkMinRank::const_iterator eiter = m_startPhyAtkMinRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( NULL == pPet )
// 		{
// 			continue;
// 		}
// 		++nCount;
// 
// 		packet->writeInt8( nCount );
// 		pPet->AppendRankList( packet );
// 		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_START_PHY_ATK_MIN ) );
// 
// 		if ( nCount >= PET_RANK_SIZE )
// 		{
// 			break;
// 		}
// 	}
// }

// void CPetRank::appendStartPhyAtkMaxRankList( Answer::NetPacket* packet, int8_t& nCount )
// {
// 	PetStartPhyAtkMaxRank::const_iterator iter = m_startPhyAtkMaxRank.begin();
// 	PetStartPhyAtkMaxRank::const_iterator eiter = m_startPhyAtkMaxRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( NULL == pPet )
// 		{
// 			continue;
// 		}
// 		++nCount;
// 
// 		packet->writeInt8( nCount );
// 		pPet->AppendRankList( packet );
// 		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_START_PHY_ATK_MAX ) );
// 
// 		if ( nCount >= PET_RANK_SIZE )
// 		{
// 			break;
// 		}
// 	}
// }

// void CPetRank::appendStartPhyDefRankList( Answer::NetPacket* packet, int8_t& nCount )
// {
// 	PetStartPhyDefRank::const_iterator iter = m_startPhyDefRank.begin();
// 	PetStartPhyDefRank::const_iterator eiter = m_startPhyDefRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( NULL == pPet )
// 		{
// 			continue;
// 		}
// 		++nCount;
// 
// 		packet->writeInt8( nCount );
// 		pPet->AppendRankList( packet );
// 		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_START_PHY_DEF ) );
// 
// 		if ( nCount >= PET_RANK_SIZE )
// 		{
// 			break;
// 		}
// 	}
// }

// void CPetRank::appendStartMagAtkMinRankList( Answer::NetPacket* packet, int8_t& nCount )
// {
// 	PetStartMagAtkMinRank::const_iterator iter = m_startMagAtkMinRank.begin();
// 	PetStartMagAtkMinRank::const_iterator eiter = m_startMagAtkMinRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( NULL == pPet )
// 		{
// 			continue;
// 		}
// 		++nCount;
// 
// 		packet->writeInt8( nCount );
// 		pPet->AppendRankList( packet );
// 		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_START_MAG_ATK_MIN ) );
// 
// 		if ( nCount >= PET_RANK_SIZE )
// 		{
// 			break;
// 		}
// 	}
// }

// void CPetRank::appendStartMagAtkMaxRankList( Answer::NetPacket* packet, int8_t& nCount )
// {
// 	PetStartMagAtkMaxRank::const_iterator iter = m_startMagAtkMaxRank.begin();
// 	PetStartMagAtkMaxRank::const_iterator eiter = m_startMagAtkMaxRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( NULL == pPet )
// 		{
// 			continue;
// 		}
// 		++nCount;
// 
// 		packet->writeInt8( nCount );
// 		pPet->AppendRankList( packet );
// 		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_START_MAG_ATK_MAX ) );
// 
// 		if ( nCount >= PET_RANK_SIZE )
// 		{
// 			break;
// 		}
// 	}
// }

// void CPetRank::appendStartMagDefRankList( Answer::NetPacket* packet, int8_t& nCount )
// {
// 	PetStartMagDefRank::const_iterator iter = m_startMagDefRank.begin();
// 	PetStartMagDefRank::const_iterator eiter = m_startMagDefRank.end();
// 	for ( ; iter != eiter; ++iter )
// 	{
// 		CSocialPet* pPet = *iter;
// 		if ( NULL == pPet )
// 		{
// 			continue;
// 		}
// 		++nCount;
// 
// 		packet->writeInt8( nCount );
// 		pPet->AppendRankList( packet );
// 		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_START_MAG_DEF ) );
// 
// 		if ( nCount >= PET_RANK_SIZE )
// 		{
// 			break;
// 		}
// 	}
// }

void CPetRank::appendGrowHPRankList( Answer::NetPacket* packet, int8_t& nCount )
{
	PetGrowHPRank::const_iterator iter = m_growHPRank.begin();
	PetGrowHPRank::const_iterator eiter = m_growHPRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}
		++nCount;

		packet->writeInt8( nCount );
		pPet->AppendRankList( packet );
		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_GROW_HP ) );

		if ( nCount >= PET_RANK_SIZE )
		{
			break;
		}
	}
}

void CPetRank::appendGrowPhyAtkMinRankList( Answer::NetPacket* packet, int8_t& nCount )
{
	PetGrowPhyAtkMinRank::const_iterator iter = m_growPhyAtkMinRank.begin();
	PetGrowPhyAtkMinRank::const_iterator eiter = m_growPhyAtkMinRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}
		++nCount;

		packet->writeInt8( nCount );
		pPet->AppendRankList( packet );
		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_GROW_PHY_ATK_MIN ) );

		if ( nCount >= PET_RANK_SIZE )
		{
			break;
		}
	}
}

void CPetRank::appendGrowPhyAtkMaxRankList( Answer::NetPacket* packet, int8_t& nCount )
{
	PetGrowPhyAtkMaxRank::const_iterator iter = m_growPhyAtkMaxRank.begin();
	PetGrowPhyAtkMaxRank::const_iterator eiter = m_growPhyAtkMaxRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}
		++nCount;

		packet->writeInt8( nCount );
		pPet->AppendRankList( packet );
		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_GROW_PHY_ATK_MAX ) );

		if ( nCount >= PET_RANK_SIZE )
		{
			break;
		}
	}
}

void CPetRank::appendGrowPhyDefRankList( Answer::NetPacket* packet, int8_t& nCount )
{
	PetGrowPhyDefRank::const_iterator iter = m_growPhyDefRank.begin();
	PetGrowPhyDefRank::const_iterator eiter = m_growPhyDefRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}
		++nCount;

		packet->writeInt8( nCount );
		pPet->AppendRankList( packet );
		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_GROW_PHY_DEF ) );

		if ( nCount >= PET_RANK_SIZE )
		{
			break;
		}
	}
}

void CPetRank::appendGrowMagAtkMinRankList( Answer::NetPacket* packet, int8_t& nCount )
{
	PetGrowMagAtkMinRank::const_iterator iter = m_growMagAtkMinRank.begin();
	PetGrowMagAtkMinRank::const_iterator eiter = m_growMagAtkMinRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}
		++nCount;

		packet->writeInt8( nCount );
		pPet->AppendRankList( packet );
		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_GROW_MAG_ATK_MIN ) );

		if ( nCount >= PET_RANK_SIZE )
		{
			break;
		}
	}
}

void CPetRank::appendGrowMagAtkMaxRankList( Answer::NetPacket* packet, int8_t& nCount )
{
	PetGrowMagAtkMaxRank::const_iterator iter = m_growMagAtkMaxRank.begin();
	PetGrowMagAtkMaxRank::const_iterator eiter = m_growMagAtkMaxRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}
		++nCount;

		packet->writeInt8( nCount );
		pPet->AppendRankList( packet );
		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_GROW_MAG_ATK_MAX ) );

		if ( nCount >= PET_RANK_SIZE )
		{
			break;
		}
	}
}

void CPetRank::appendGrowMagDefRankList( Answer::NetPacket* packet, int8_t& nCount )
{
	PetGrowMagDefRank::const_iterator iter = m_growMagDefRank.begin();
	PetGrowMagDefRank::const_iterator eiter = m_growMagDefRank.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = *iter;
		if ( NULL == pPet )
		{
			continue;
		}
		++nCount;

		packet->writeInt8( nCount );
		pPet->AppendRankList( packet );
		packet->writeInt32( pPet->GetBaseAttr( PET_ATTR_GROW_MAG_DEF ) );

		if ( nCount >= PET_RANK_SIZE )
		{
			break;
		}
	}
}

void CPetRank::addDirty( PetId_t nPetId )
{
	PetIdList::iterator iter = m_lstDirty.begin();
	PetIdList::iterator eiter = m_lstDirty.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( *iter == nPetId )
		{
			return;
		}
	}

	m_lstDirty.push_back( nPetId );
}

void CPetRank::sendDirty()
{
	if ( m_lstDirty.empty() )
	{
		return;
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	uint16_t nOffset = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt32( nCount );
	PetIdList::iterator iter = m_lstDirty.begin();
	PetIdList::iterator eiter = m_lstDirty.end();
	for ( ; iter != eiter; ++iter )
	{
		CSocialPet* pPet = PET_MANAGER.GetPet( *iter );
		if ( NULL == pPet )
		{
			continue;
		}

		pPet->AppendRankInfo( packet );
		++nCount;
	}

	uint16_t nOldOffset = packet->getWOffset();
	packet->setWOffset( nOffset );
	packet->writeInt32( nCount );
	packet->setWOffset( nOldOffset );

	packet->setType( PACK_PROC );
	packet->setProc( IM_SOCIAL_ALL_GAME_UPDATE_PET_RANK );
	packet->setSize( packet->getWOffset() );
	SOCIAL_SERVICE.sendPacket( packet );

	m_lstDirty.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPetRankManager::CPetRankManager()
{
}

CPetRankManager::~CPetRankManager()
{
}

void CPetRankManager::RefreshRank()
{
	for ( int32_t i = 1; i <= MAX_PET_ID; ++i )
	{
		m_vPetRank[i].RefreshRank();
	}
}

void CPetRankManager::AddPet( CSocialPet* pPet, bool bNeedRefresh )
{
	if ( NULL == pPet )
	{
		return;
	}
	int32_t nBaseId = pPet->GetBaseId();
	if ( nBaseId <= 0 || nBaseId > MAX_PET_ID )
	{
		return;
	}

	m_vPetRank[nBaseId].AddPet( pPet, bNeedRefresh );
}

void CPetRankManager::DelPet( CSocialPet* pPet )
{
	if ( NULL == pPet )
	{
		return;
	}
	int32_t nBaseId = pPet->GetBaseId();
	if ( nBaseId <= 0 || nBaseId > MAX_PET_ID )
	{
		return;
	}
	m_vPetRank[nBaseId].DelPet( pPet );
}

void CPetRankManager::UpdatePet( CSocialPet* pPet, const SocialPetData& pet )
{
	if ( NULL == pPet )
	{
		return;
	}
	int32_t nBaseId = pPet->GetBaseId();
	if ( nBaseId <= 0 || nBaseId > MAX_PET_ID )
	{
		return;
	}
	m_vPetRank[nBaseId].UpdatePet( pPet, pet );
}

void CPetRankManager::SendPetRankList( int32_t nBaseId, int8_t nRankType, int16_t nGateIndex )
{
	if ( nBaseId <= 0 || nBaseId > MAX_PET_ID )
	{
		return;
	}

	NetPacket *packet = SOCIAL_SERVICE.popNetpacket();
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt32( nBaseId );
	packet->writeInt8( nRankType );
	m_vPetRank[nBaseId].AppendRankList( nRankType, packet );

	packet->setType( PACK_DISPATCH );
	packet->setProc( SM_PET_RANK_LIST );
	packet->setSize( packet->getWOffset() );

	SOCIAL_SERVICE.sendPacketTo( nGateIndex, packet);
}

