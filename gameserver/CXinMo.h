#ifndef __C_XIN_MO_H__
#define __C_XIN_MO_H__

#include "Shared.h"
#include "../share/DataStruct.h"
#include "XinMoTable.h"

class Player;

// ===== CXinMo 类 =====
class CXinMo : public IExtSystem
{
public:
    CXinMo() : m_pPlayer(NULL) { OnCleanUp(); }
    virtual ~CXinMo() {}
    void SetPlayer(Player* p) { m_pPlayer = p; }

    // IExtSystem 接口
    virtual const char*     GetName() const { return "CXinMo"; }
    virtual void            OnCleanUp();
    virtual void            OnDaySwitch(int32_t nDiffDays);
    virtual void            OnUpdate(int64_t curTick);
    virtual void            OnLoadFromDB(const PlayerDBData& dbData);
    virtual void            OnSaveToDB(PlayerDBData& dbData);
    virtual void            GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t         DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);

    // 公共方法
    void    AddCharAttr();
    void    AddExp(int32_t nValue);
    int32_t GetXinMoLevel() const { return m_XinMoLevel; }
    int32_t GetActiveXinMoLevel() const { return m_XinMoActiveLevel; }
    int32_t GetFreeSlotCount() const;

    // 七情相关
    int32_t GetQiQingLevel(int32_t nType) const;
    int32_t GetLeftYaoYiYaoTimes() const;
    int32_t GetChangeXinQingTimes() const;
    int32_t GetFlagCount() const;
    bool    IsYaoYiYao() const { return (m_QiQingInfo & (1 << 1)) != 0; }
    void    SetFlag(int32_t nId);
    void    SetYaoYiYaoFlag(int32_t nCount);
    void    GetNoFlagIdList(Int32Vector& nIdVt) const;
    void    AddYaoYiYaoTimes();
    void    AddChangeXinQingTimes();

    // 心魔背包
    bool    AddItem(MemChrBagVector* pItems);
    void    GetItem(int32_t nSlot);
    void    ResetBagSlot(int32_t nSlot, int32_t nOpway);
    void    AddXinMoBagLog(const MemChrBag& item, int32_t nFlag, int32_t nOpway);
    void    CleanXinMoBag();
    void    DieDropFromXinMoBag(MemChrBagVector* pTmpVt);

    // 数据发送
    void    SendXiMoInfo();
    void    SendXinQingInfo();
    void    SendXinMoQiQingLevel(int32_t nType);
    void    SendAllItem();
    void    SendChangeItem(const std::list<int>& itemList);

private:
    // 协议处理
    int32_t OnXinMoLevel(Answer::NetPacket* inPacket);
    int32_t OnActiveXinMo(Answer::NetPacket* inPacket);
    int32_t OnJinHua(Answer::NetPacket* inPacket);
    int32_t OnGetItem(Answer::NetPacket* inPacket);
    int32_t OnTidy(Answer::NetPacket* inPacket);
    int32_t OnDec(Answer::NetPacket* inPacket);
    int32_t OnQiQingLevelUp(Answer::NetPacket* inPacket);
    int32_t OnXinQing(Answer::NetPacket* inPacket);

    // 数据库成员
    int32_t             m_Exp;
    int32_t             m_XinMoLevel;
    int32_t             m_XinMoActiveLevel;
    std::map<int,int>   m_QiQingLevel;
    int32_t             m_QiQingInfo;       // bitmask flags 0-6
    MemChrBag           m_ItemList[56];     // 心魔背包
    Player*             m_pPlayer;
};

#endif // __C_XIN_MO_H__
