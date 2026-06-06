#include "stdafx.h"
#include "CfgData.h"
#include "MingGeChip.h"
#include "Player.h"
#include "CMingGeExt.h"

MingGeChip::MingGeChip()
    : ItemEffect()
    , m_nId(0)
    , m_Chip(0)
{
}

MingGeChip::~MingGeChip()
{
}

int32_t MingGeChip::effect(Player &launcher, Unit &target, int32_t count)
{
    int32_t v4 = count * m_Chip;
    CMingGeExt* pExt = &launcher.GetCMingGeExt();
    if (!pExt->AddMingGeChip(v4))
        return 2;
    return 0;
}

bool MingGeChip::parseEffect(int32_t id, const std::string &strEffect)
{
    if (strEffect.empty())
        return false;
    m_nId = id;
    m_Chip = atoi(strEffect.c_str());
    return m_Chip > 0;
}
