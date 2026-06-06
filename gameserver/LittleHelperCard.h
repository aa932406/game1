#ifndef __TPOC_LITTLE_HELPER_CARD_H__
#define __TPOC_LITTLE_HELPER_CARD_H__

#include "../share/Shared.h"
class Player;
class Unit;
#include <string>

class LittleHelperCard
{
public:
    LittleHelperCard()
        : m_nId( 0 )
        , m_nLittleHelpId( 0 )
        , m_nAddTime( 0 )
    {
    }
    ~LittleHelperCard() {}

    int32_t effect( Player *launcher, Unit *target, int32_t *count );
    bool parseEffect( int32_t id, const std::string *strEffect );

    int32_t m_nId;
    int32_t m_nLittleHelpId;
    int32_t m_nAddTime;
};

#endif
