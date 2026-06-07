#ifndef __CKUN_EXT_H__
#define __CKUN_EXT_H__

#include "KunData.h"
#include "KunLingTable.h"

class Player;

// ========== CKunExt Class ==========

class CKunExt : public IExtSystem
{
public:
    CKunExt();
    virtual ~CKunExt();

    // IExtSystem interface
    virtual void Init(Player* pPlayer);
    virtual void OnLoadFromDB(const PlayerDBData& dbData);
    virtual void OnSaveToDB(PlayerDBData& dbData);
    virtual void OnCleanUp();
    virtual void GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);
    virtual void OnUpdate(int64_t curTick);
    virtual void OnDaySwitch(int32_t nDiffDays);

    // Public methods
    void SendKunLingInfo();
    void SendLingZhuBagAllItem();
    void SendLingZhuBagChangeItem(Int32List& changeList);
    void SendDanTianInfo(int32_t Pos);
    void SendLingZhuPosInfo(int32_t Pos);
    bool AddLingZhuBagItem(int32_t LingZhuId, int32_t Count, ITEM_CHANGE_REASON addReason);
    int32_t GetEmptyBagCount();
    void AddExp(int32_t Exp);
    bool ReMoveLingZhuItem(int32_t LingZhuId, int32_t Count, ITEM_CHANGE_REASON addReason);
    void RemoveLingZhuItem(Int32List& pPos, ITEM_CHANGE_REASON addReason);
    bool AddDanTian(int32_t Mid);
    void AddCharAttr();
    int32_t GetLeftLianHuaTimes();
    void CheckSuit();
    void CheckAddSuitSkill();

private:
    // Protocol handlers
    int32_t OnKunLingLevelUp(Answer::NetPacket* inPacket);
    int32_t OnGetLingZhu(Answer::NetPacket* inPacket);
    int32_t OnRecoveryLingZhu(Answer::NetPacket* inPacket);
    int32_t OnFastFining(Answer::NetPacket* inPacket);
    int32_t OnLingZhuLevelUp(Answer::NetPacket* inPacket);
    int32_t OnBuyLianHuaTime(Answer::NetPacket* inPacket);
    int32_t OnKunWeiYang(Answer::NetPacket* inPacket);

private:
    Player* m_pPlayer;

    // Data
    int32_t m_nKunLevel;                    // 鲲等级
    int32_t m_nExp;                         // 鲲经验
    int32_t m_nBuyTime;                     // 购买次数
    int32_t m_nLianHuaTime;                 // 炼化次数
    int64_t m_LastUpdateTick;               // 上次更新tick

    // Arrays (using KunData.h structs)
    KunLingZhuBagItem m_LingZhuBag[MAX_LING_ZHU_BAG];  // 灵珠背包
    KunDanTianItem    m_DanTian[MAX_DAN_TIAN];          // 丹田
    int32_t           m_LingZhuPos[MAX_LING_ZHU_POS];   // 灵珠位置

    std::list<int32_t> lSuitList;           // 套装列表
};

#endif // __CKUN_EXT_H__
