#include "stdafx.h"
#include "LittleHelperCard.h"
#include "Player.h"
#include "CharLittlerHelper.h"

int32_t LittleHelperCard::effect( Player *launcher, Unit *target, int32_t *count )
{
    if ( NULL == launcher )
        return 0;
    CharLittlerHelper& helper = launcher->GetCharLittlerHelper();
    return helper.AddLittlerHelper( m_nLittleHelpId, m_nAddTime );
}

bool LittleHelperCard::parseEffect( int32_t id, const std::string *strEffect )
{
    m_nId = id;
#if 0
    // Stub: StringUtility::split API needs verification
    std::vector<std::string> vParam;
    Answer::StringUtility::split( &vParam, strEffect, ":", 0 );
    if ( vParam.size() == 2 )
    {
        m_nLittleHelpId = atoi( vParam[0].c_str() );
        m_nAddTime = atoi( vParam[1].c_str() );
        m_nAddTime *= 86400;
        return true;
    }
#endif
    return false;
}
