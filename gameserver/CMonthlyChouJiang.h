#ifndef __C_MONTHLY_CHOU_JIANG_H__
#define __C_MONTHLY_CHOU_JIANG_H__

#include "Shared.h"
#include "../share/DataStruct.h"
#include "ExtSystemBase.h"
#include <list>
#include <map>

class CMonthlyChouJiang
    : public CExtSystemBase
{
public:
    CMonthlyChouJiang();
    ~CMonthlyChouJiang();

    virtual void OnLoadFromDB(const PlayerDBData& dbData);
    virtual void OnSaveToDB(PlayerDBData& dbData);
    virtual void GetInterestsProtocol(ProcIdList& procList);
    virtual int32_t DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket* inPacket);
    virtual void OnCleanUp();
    virtual void OnUpdate(int64_t curTick) {}
    virtual void OnDaySwitch(int32_t nDiffDays);

    void OnMonthlySwitch();
    void OnChongZhi(int32_t NewValues, int32_t OldValues);

    int32_t GetKaiFuMonth();
    int32_t GetSocreTimes(int32_t nId);
    bool TodaySocreIsAllGet();

private:
    int32_t OnMonthlyChouJiang(Answer::NetPacket* inPacket);
    int32_t OnAskMonthlyChouJiangInfo(Answer::NetPacket* inPacket);

    void SendMonthlyChouJiangInfo();
    void SendMonthlyChouJiangResult(int32_t nId);
    void GetIcon(ShowIcon& icon);
    void GetIcon(IconStateList& IconList);
    void SendIcon();

    int32_t m_Score;
    int32_t m_AllScore;
    std::list<int32_t> m_GetItemList;
    std::map<int32_t, int32_t> m_GetTimes;
};

#endif
