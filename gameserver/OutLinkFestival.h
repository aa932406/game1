#ifndef __TPOC_OUT_LINK_FESTIVAL_H__
#define __TPOC_OUT_LINK_FESTIVAL_H__

#include "CfgData.h"

class COutLinkFestival
{
public:
    COutLinkFestival();
    ~COutLinkFestival();

    void    Init( int32_t line );
    void    OnNewMinute( int32_t nMinute );
    void    GetIconState( IconStateList& IconList );

protected:
    void    checkIconState();
    bool    isInIconList( const CfgOutLinkFestivalList& lst, int32_t nIndex );

protected:
    pthread_mutex_t         m_lock;
    CfgOutLinkFestivalList  m_lOutLinkIcons;
};

#endif  //__TPOC_OUT_LINK_FESTIVAL_H__
