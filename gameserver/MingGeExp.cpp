#include "stdafx.h"
#include "CfgData.h"
#include "MingGeExp.h"
#include "Player.h"
#include "CMingGeExt.h"

MingGeExp::MingGeExp()
    : ItemEffect()
    , m_nId(0)
    , m_Chip(0)
{
}

MingGeExp::~MingGeExp()
{
}

int32_t MingGeExp::effect(Player &launcher, Unit &target, int32_t count)
{
    int32_t v4 = count * m_Chip;
    CMingGeExt* pExt = &launcher.GetCMingGeExt();
    if (!pExt->AddExp(v4))
        return 2;
    return 0;
}

bool MingGeExp::parseEffect(int32_t id, const std::string &strEffect)
{
    if (strEffect.empty())
        return false;
    m_nId = id;
    m_Chip = atoi(strEffect.c_str());
    return m_Chip > 0;
}
