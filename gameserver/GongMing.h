#ifndef __C_GONG_MING_H__
#define __C_GONG_MING_H__

#include "ExtSystemBase.h"

class CGongMing : public CExtSystemBase
{
public:
    CGongMing();
    virtual ~CGongMing();

    virtual void        OnLoadFromDB( const PlayerDBData& dbData );
    virtual void        OnSaveToDB( PlayerDBData& dbData );
    virtual void        GetInterestsProtocol( ProcIdList& procList );
    virtual int32_t     DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
    virtual void        OnCleanUp();
    virtual void        OnUpdate( int64_t curTick );

    void                AddGongMingValues( int32_t Values );
    void                AddCharAttr();
    void                SendGongMinInfo();

private:
    int32_t             OnGongMinLevelUp( Answer::NetPacket *inPacket );
};

#endif // __C_GONG_MING_H__
