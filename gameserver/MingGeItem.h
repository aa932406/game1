#ifndef __TPOC_MING_GE_ITEM_H__
#define __TPOC_MING_GE_ITEM_H__

#include "ItemEffect.h"

class MingGeItem : public ItemEffect
{
public:
    MingGeItem();
    virtual ~MingGeItem();

    virtual int32_t effect(Player &launcher, Unit &target, int32_t count = 0);
    virtual bool parseEffect(int32_t id, const std::string &strEffect);

private:
    int32_t m_nId;
    int32_t m_Chip;
};

#endif
