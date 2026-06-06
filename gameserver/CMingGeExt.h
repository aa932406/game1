#ifndef __TPOC_CMING_GE_EXT_H__
#define __TPOC_CMING_GE_EXT_H__

#include "ExtSystemBase.h"
#include "CMingGeData.h"

class CMingGeExt : public CExtSystemBase
{
public:
    CMingGeExt();
    virtual ~CMingGeExt();

    virtual void GetInterestsProtocol( ProcIdList& procList );
    virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
    virtual void OnLoadFromDB( const PlayerDBData *const dbData );
    virtual void OnSaveToDB( PlayerDBData *const dbData );
    virtual void OnCleanUp();

    // Send
    void SendMingGeInfo();
    void SendMingGeBagInfo( int32_t nType );
    void SendMingGeBagInfo( int32_t nType, int32_t nSlot );

    // Pack
    void PackMingGeBagInfo( Answer::NetPacket *packet );
    void PackLeiMingBagInfo( Answer::NetPacket *packet );
    void PackMingGeEquipBagInfo( Answer::NetPacket *packet );

    // Protocol handlers
    int32_t OnMingGeLevelUp( Answer::NetPacket *inPacket );
    int32_t OnPickupMingGe( Answer::NetPacket *inPacket );
    int32_t OnLock( Answer::NetPacket *inPacket );
    int32_t OnDecMingGe( Answer::NetPacket *inPacket );
    int32_t OnDuiHuan( Answer::NetPacket *inPacket );
    int32_t OnLieMing( Answer::NetPacket *inPacket );
    int32_t OnDress( Answer::NetPacket *inPacket );
    int32_t OnUnDress( Answer::NetPacket *inPacket );
    int32_t OnBuyNpc( Answer::NetPacket *inPacket );

    // Bag operations
    int32_t GetBagFreeSlot( int32_t nType );
    int32_t GetBagFreeSlotCount( int32_t nType );
    int32_t GetSameTypeMingGe( int32_t MingGeId );
    bool AddBagItem( int32_t nType, int32_t Slot, MingGe stu, ITEM_CHANGE_REASON Reason );
    bool RemoveItem( int32_t nType, int32_t Slot, ITEM_CHANGE_REASON Reason );
    bool SetSlot( int32_t nType, int32_t Slot, MingGe stu, ITEM_CHANGE_REASON Reason );
    MingGe GetSlotItem( int32_t nType, int32_t Slot );

    // Logic
    void AddAttr();
    bool AddMingGeChip( int32_t Count );
    bool AddItem( int32_t nId, ITEM_CHANGE_REASON Reason );
    bool AddExp( int32_t Exp );
    void GongGao( int32_t GongGaoId, int32_t MingGeId );
    void AddMingGeLog( MGLog Stu );
    float GetRate( int32_t Times );

    // Data access
    MingGe* GetMingGeBag() { return m_MingGeBag; }
    MingGe* GetLieMingBag() { return m_LieMingBag; }
    MingGe* GetMingGeEquip() { return m_MingGeEquip; }
    int32_t GetMingGeExp() const { return m_MingGeExp; }
    int32_t GetMingChip() const { return m_MingChip; }

private:
    MingGe m_MingGeBag[100];
    MingGe m_LieMingBag[30];
    MingGe m_MingGeEquip[8];
    int32_t m_MingGeNpc[5];
    int32_t m_MingGeExp;
    int32_t m_MingChip;
};

#endif
