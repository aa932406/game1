#ifndef __RONG_LIAN_H__
#define __RONG_LIAN_H__

#include "stdafx.h"
#include "Activity.h"

class CRongLian
    : public CActivity
{
public:
    CRongLian( const CfgActivity& cfgActivity )
        : CActivity( cfgActivity ) {}
    virtual ~CRongLian();

    virtual void broadcastStart();
    virtual void sendPlayerScore( Player* player );
};

#endif
