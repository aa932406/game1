#include "stdafx.h"
#include "CCardGroupBox.h"
#include "share/Shared.h"
#include <algorithm>

using namespace Answer;

// ========== CCardGroupBox ==========

CCardGroupBox::CCardGroupBox()
    : m_nId( 0 )
    , m_nIndex( 0 )
{
    memset( m_vCardGroup, 0, sizeof(m_vCardGroup) );
}

CCardGroupBox::~CCardGroupBox()
{
}

void CCardGroupBox::Init( int32_t nId, const CardGroupList& lst )
{
    m_nId = nId;
    m_lstCards = lst;
    resetCardGroup();
}

int32_t CCardGroupBox::GetCard()
{
    if ( m_nIndex > 9999 )
    {
        resetCardGroup();
    }
    if ( m_nIndex < 0 || m_nIndex >= 10000 )
    {
        return 0;
    }
    return m_vCardGroup[m_nIndex++];
}

void CCardGroupBox::resetCardGroup()
{
    m_nIndex = 0;
    memset( m_vCardGroup, 0, sizeof(m_vCardGroup) );

    Int32Vector vIds;
    vIds.reserve( 10000 );

    for ( CardGroupList::iterator it = m_lstCards.begin(); it != m_lstCards.end(); ++it )
    {
        if ( it->min >= 0 && it->max > 0 )
        {
            // Random placement within percentage ranges
            initCardGroup( *it );
        }
        else
        {
            // Direct insertion: push id into vector 'count' times
            for ( int32_t i = 0; i < it->count; ++i )
            {
                vIds.push_back( it->id );
            }
        }
    }

    // Shuffle direct-insertion ids and fill empty slots
    std::random_shuffle( vIds.begin(), vIds.end() );

    int32_t nIndx = 0;
    for ( uint32_t i = 0; i < vIds.size(); ++i )
    {
        nIndx = getFirstEmptyIndex( nIndx, 10000 );
        if ( nIndx < 0 )
        {
            break;
        }
        m_vCardGroup[nIndx] = vIds[i];
    }
}

void CCardGroupBox::initCardGroup( const CardGroup& group )
{
    if ( group.count <= 0 || group.count > 10000 || group.min > 100 || group.max > 100 )
    {
        LOG_ERROR( "CCardGroup::initCardGroup() item count out of range where id=%d, count=%d\n",
                   group.id, group.count );
        return;
    }

    int32_t nCount = group.count;
    int32_t nArea = 10000 / nCount;
    int32_t nStart = 0;

    for ( int32_t i = 0; i < nCount; ++i )
    {
        int32_t nMin = nStart + nArea * group.min / 100;
        int32_t nMax = nStart + nArea * group.max / 100;

        if ( nMin > 10000 )
        {
            nMin = nStart;
        }
        if ( nMax > 10000 )
        {
            nMax = 10000;
        }

        int32_t nRand = RANDOM.generate( nMin, nMax - 1 );

        // If slot is already taken, find next empty slot in range
        if ( m_vCardGroup[i] != 0 )
        {
            nRand = getFirstEmptyIndex( nMin, nMax );
        }

        if ( nRand >= 0 )
        {
            m_vCardGroup[nRand] = group.id;
        }

        nStart += nArea;
    }
}

int32_t CCardGroupBox::getFirstEmptyIndex( int32_t nMin, int32_t nMax )
{
    while ( nMin < nMax )
    {
        if ( m_vCardGroup[nMin] == 0 )
        {
            return nMin;
        }
        ++nMin;
    }
    return -1;
}

// ========== CCardGroupBoxManager ==========

CCardGroupBoxManager::CCardGroupBoxManager()
{
}

CCardGroupBoxManager::~CCardGroupBoxManager()
{
}

void CCardGroupBoxManager::Add( int32_t nGroupId, const CardGroupList& lst )
{
    CCardGroupBox box;
    box.Init( nGroupId, lst );
    m_lCardGroupBox.push_back( box );
}

int32_t CCardGroupBoxManager::GetCard( int32_t nId )
{
    for ( std::list<CCardGroupBox>::iterator it = m_lCardGroupBox.begin();
          it != m_lCardGroupBox.end(); ++it )
    {
        if ( it->GetId() == nId )
        {
            return it->GetCard();
        }
    }
    return 0;
}
