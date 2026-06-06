#ifndef __TPOC_CHAR_LITTLER_HELPER_H__
#define __TPOC_CHAR_LITTLER_HELPER_H__

#include "ExtSystemBase.h"
#include "CLittleHelper.h"
class CLittleHelperData;
class Player;
#include "../share/Shared.h"
#include <map>
#include <set>
#include <string>

class CharLittlerHelper : public CExtSystemBase
{
public:
    CharLittlerHelper();
    virtual ~CharLittlerHelper();

    virtual void GetInterestsProtocol( ProcIdList& procList );
    virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
    virtual void OnLoadFromDB( const PlayerDBData *const dbData );
    virtual void OnSaveToDB( PlayerDBData *const dbData );
    virtual void OnCleanUp();
    virtual void OnUpdate( int64_t curTick );

    int32_t OnAutoWork();
    int32_t OnWork( int32_t nId );
    int32_t OnWork( Answer::NetPacket *inPacket );
    int32_t OnRest( Answer::NetPacket *inPacket );
    int32_t OnRest();
    int32_t OnBuyLittlerHelper( Answer::NetPacket *inPacket );
    int32_t AddLittlerHelper( int32_t nId, int32_t nAddTime );

    void SetTargetTile( int32_t tx, int32_t ty, Direction dir );
    void AddCharAttr();
    void SendCharLittlerhelper();

    bool CanPick( int8_t nClass, int32_t nId );
    bool IsFilterItem( int8_t nclass, int32_t nId );
    bool IsFilterEquipGrade( int32_t Grade );
    void parsePickString( std::string *pStr );

    ActLittleHelperInfo* GetActLittleHelperInfo( int32_t nId );

    bool IsPickMoney() const { return m_PickSetUp[0] != 0; }
    bool IsPickSYB() const { return m_PickSetUp[1] != 0; }
    bool IsPickImte() const { return m_PickSetUp[2] != 0; }
    bool IsPickEquip() const { return m_PickSetUp[3] != 0; }
    bool IsPickShouHu() const { return m_PickSetUp[4] != 0; }
    bool IsPickSpecialEquip() const { return m_PickSetUp[5] != 0; }

    std::map<int32_t, ActLittleHelperInfo> m_ActMap;
    int32_t         m_LittleHelperId;
    CLittleHelper*  m_CLittleHelper;

    std::map<std::pair<int8_t, int32_t>, int32_t> m_ItemFilterMap;
    std::set<int32_t> m_EquipFilter;
    int32_t         m_NeedPick;
    int8_t          m_PickSetUp[6];
};

#endif
