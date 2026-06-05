#include "stdafx.h"
#include "OutLinkFestival.h"
#include "CfgData.h"
#include "GameService.h"
#include "Timer.h"
#include "actStructs.h"

COutLinkFestival::COutLinkFestival()
{
    pthread_mutex_init( &m_lock, NULL );
}

COutLinkFestival::~COutLinkFestival()
{
    pthread_mutex_destroy( &m_lock );
}

void COutLinkFestival::Init( int32_t line )
{
    Answer::DayTime::now();
    const CfgOutLinkFestivalTable* pTable = CFG_DATA.GetOutLinkFestivalTable();
    if ( NULL == pTable )
    {
        return;
    }
    CfgOutLinkFestivalList lShowIcons;
    pTable->GetShowIcons( lShowIcons );
    m_lOutLinkIcons = lShowIcons;
}

void COutLinkFestival::OnNewMinute( int32_t nMinute )
{
    if ( nMinute % 60 != 0 )
    {
        return;
    }

    if ( GAME_SERVICE.getLine() == 1 )
    {
        checkIconState();
    }
    else
    {
        TIMER.GetNow();
        const CfgOutLinkFestivalTable* pTable = CFG_DATA.GetOutLinkFestivalTable();
        if ( NULL == pTable )
        {
            return;
        }
        CfgOutLinkFestivalList lShowIcons;
        pTable->GetShowIcons( lShowIcons );
        m_lOutLinkIcons = lShowIcons;
    }
}

void COutLinkFestival::GetIconState( IconStateList& IconList )
{
    int32_t nNowTime = TIMER.GetNow();
    pthread_mutex_lock( &m_lock );
    const CfgOutLinkFestivalTable* pTable = CFG_DATA.GetOutLinkFestivalTable();
    if ( NULL == pTable )
    {
        pthread_mutex_unlock( &m_lock );
        return;
    }
    CfgOutLinkFestivalList lCurrentIcons;
    pTable->GetShowIcons( lCurrentIcons );
    m_lOutLinkIcons = lCurrentIcons;
    lCurrentIcons = m_lOutLinkIcons;
    pthread_mutex_unlock( &m_lock );

    if ( lCurrentIcons.empty() )
    {
        return;
    }

    for ( CfgOutLinkFestivalList::const_iterator iter = lCurrentIcons.begin();
        iter != lCurrentIcons.end(); ++iter )
    {
        ShowIcon stu;
        memset( &stu, 0, sizeof( stu ) );
        stu.nId        = iter->nIcon;
        stu.nState     = 2;
        stu.nLeftTime  = iter->nEndTime - nNowTime;
        IconList.push_back( stu );
    }
}

void COutLinkFestival::checkIconState()
{
    int32_t nNowTime = TIMER.GetNow();

    const CfgOutLinkFestivalTable* pTable = CFG_DATA.GetOutLinkFestivalTable();
    if ( NULL == pTable )
    {
        return;
    }
    CfgOutLinkFestivalList lShowIcons;
    pTable->GetShowIcons( lShowIcons );

    CfgOutLinkFestivalList lAdd;
    CfgOutLinkFestivalList lHide;

    pthread_mutex_lock( &m_lock );

    // Find new icons to add
    for ( CfgOutLinkFestivalList::const_iterator iter = lShowIcons.begin();
        iter != lShowIcons.end(); ++iter )
    {
        if ( !isInIconList( m_lOutLinkIcons, iter->nIndex ) )
        {
            lAdd.push_back( *iter );
        }
    }

    // Find icons to hide
    for ( CfgOutLinkFestivalList::const_iterator iter = m_lOutLinkIcons.begin();
        iter != m_lOutLinkIcons.end(); ++iter )
    {
        if ( !isInIconList( lShowIcons, iter->nIndex ) )
        {
            lHide.push_back( *iter );
        }
    }

    m_lOutLinkIcons = lShowIcons;
    pthread_mutex_unlock( &m_lock );

    // Broadcast added icons
    if ( !lAdd.empty() )
    {
        for ( CfgOutLinkFestivalList::const_iterator iter = lAdd.begin();
            iter != lAdd.end(); ++iter )
        {
            ShowIcon icon;
            memset( &icon, 0, sizeof( icon ) );
            icon.nId        = iter->nIcon;
            icon.nState     = 2;
            icon.nLeftTime  = iter->nEndTime - nNowTime;

            Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CC3 );
            if ( NULL != packet )
            {
                packet->writeInt32( icon.nId );
                packet->writeInt8( icon.nState );
                packet->writeInt32( icon.nLeftTime );
                packet->setSize( packet->getWOffset() );
                GAME_SERVICE.worldBroadcast( packet );
            }
        }
    }

    // Broadcast hidden icons
    if ( !lHide.empty() )
    {
        for ( CfgOutLinkFestivalList::const_iterator iter = lHide.begin();
            iter != lHide.end(); ++iter )
        {
            ShowIcon icon;
            memset( &icon, 0, sizeof( icon ) );
            icon.nId        = iter->nIcon;
            icon.nState     = 4;
            icon.nLeftTime  = 0;

            Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CC3 );
            if ( NULL != packet )
            {
                packet->writeInt32( icon.nId );
                packet->writeInt8( icon.nState );
                packet->writeInt32( icon.nLeftTime );
                packet->setSize( packet->getWOffset() );
                GAME_SERVICE.worldBroadcast( packet );
            }
        }
    }
}

bool COutLinkFestival::isInIconList( const CfgOutLinkFestivalList& lst, int32_t nIndex )
{
    for ( CfgOutLinkFestivalList::const_iterator iter = lst.begin();
        iter != lst.end(); ++iter )
    {
        if ( iter->nIndex == nIndex )
        {
            return true;
        }
    }
    return false;
}
