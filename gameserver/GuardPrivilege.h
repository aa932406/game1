#ifndef __C_GUARD_PRIVILEGE_H__
#define __C_GUARD_PRIVILEGE_H__

#include "ExtSystemBase.h"

class CGuardPrivilege : public CExtSystemBase
{
public:
    CGuardPrivilege();
    virtual ~CGuardPrivilege();

    virtual void        OnLoadFromDB( const PlayerDBData& dbData );
    virtual void        OnSaveToDB( PlayerDBData& dbData );
    virtual void        GetInterestsProtocol( ProcIdList& procList );
    virtual int32_t     DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
    virtual void        OnCleanUp();
    virtual void        OnUpdate( int64_t curTick );

    void                GetIconState( IconStateList& iconList );

private:
    int32_t             onRequestInfo( Answer::NetPacket *inPacket );
    int32_t             onGetReward( Answer::NetPacket *inPacket );
    int32_t             onDBGetReward( Answer::NetPacket *inPacket );

    void                sendInfo();
    void                sendIconState();
    bool                isOpen();
    int8_t              getTimeState();

    int8_t              m_nState;
    int64_t             m_nLastTick;
};

#endif // __C_GUARD_PRIVILEGE_H__
