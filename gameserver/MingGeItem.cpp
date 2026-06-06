#include "stdafx.h"
#include "CfgData.h"
#include "MingGeItem.h"
#include "Player.h"
#include "CMingGeExt.h"

MingGeItem::MingGeItem()
    : ItemEffect()
    , m_nId(0)
    , m_Chip(0)
{
}

MingGeItem::~MingGeItem()
{
}

int32_t MingGeItem::effect(Player &launcher, Unit &target, int32_t count)
{
    if (count > 1)
        return 10002;
    CMingGeExt* pExt = &launcher.GetCMingGeExt();
    if (!pExt->AddItem(m_Chip, ICR_BAG_USE))
        return 2;
    return 0;
}

bool MingGeItem::parseEffect(int32_t id, const std::string &strEffect)
{
    if (strEffect.empty())
        return false;
    m_nId = id;
    m_Chip = atoi(strEffect.c_str());
    return m_Chip > 0;
}
