#ifndef __YA_BIAO_H__
#define __YA_BIAO_H__

#include "stdafx.h"
#include "Activity.h"

class CYaBiao
    : public CActivity
{
public:
    CYaBiao( const CfgActivity& cfgActivity )
        : CActivity( cfgActivity ) {}
    virtual ~CYaBiao();

    virtual void broadcastStart();
    virtual void broadcastTimeEnd();
    virtual void broadcastReady();
};

#endif
