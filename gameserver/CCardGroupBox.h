#ifndef __TPOC_CARD_GROUP_BOX_H__
#define __TPOC_CARD_GROUP_BOX_H__

#include "share/Shared.h"
#include <list>
#include <vector>
#include <cstring>

// Card group configuration
struct CardGroup
{
    CardGroup() : id(0), count(0), min(0), max(0) {}
    int32_t id;
    int32_t count;
    int32_t min;
    int32_t max;
};
typedef std::list<CardGroup> CardGroupList;

// A shuffled card deck with 10000 slots
class CCardGroupBox
{
public:
    CCardGroupBox();
    ~CCardGroupBox();

    void    Init( int32_t nId, const CardGroupList& lst );
    int32_t GetCard();
    int32_t GetId() const { return m_nId; }

private:
    void    resetCardGroup();
    void    initCardGroup( const CardGroup& group );
    int32_t getFirstEmptyIndex( int32_t nMin, int32_t nMax );

private:
    int32_t             m_nId;
    CardGroupList       m_lstCards;
    int32_t             m_vCardGroup[10000];
    int32_t             m_nIndex;
};

// Singleton manager for all card group boxes
class CCardGroupBoxManager
{
public:
    CCardGroupBoxManager();
    ~CCardGroupBoxManager();

    void    Add( int32_t nGroupId, const CardGroupList& lst );
    int32_t GetCard( int32_t nId );

private:
    std::list<CCardGroupBox> m_lCardGroupBox;
};

#define CARD_GROUP_BOX_MANAGER Answer::Singleton<CCardGroupBoxManager>::instance()

#endif //__TPOC_CARD_GROUP_BOX_H__
