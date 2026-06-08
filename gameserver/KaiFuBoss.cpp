#include "KaiFuBoss.h"
#include "GameService.h"
#include "Timer.h"
#include "MonsterActivity.h"

using namespace Answer;

CKaiFuBoss::CKaiFuBoss( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
, m_Boss( NULL )
{
}

CKaiFuBoss::~CKaiFuBoss()
{
}

void CKaiFuBoss::reset()
{
    m_Boss = NULL;
    CActivity::reset();
}

bool CKaiFuBoss::isSpecialDay( int32_t nStartDays ) const
{
    return nStartDays >= 0 && nStartDays <= 6;
}

bool CKaiFuBoss::checkData()
{
    int32_t startDays = TIMER.GetDaysFromStart();
    if ( isSpecialDay( startDays ) )
    {
        return true;
    }
    return CActivity::checkData();
}

bool CKaiFuBoss::checkWeek()
{
    int32_t startDays = TIMER.GetDaysFromStart();
    if ( isSpecialDay( startDays ) )
    {
        return true;
    }
    return CActivity::checkWeek();
}

int32_t CKaiFuBoss::getNextStartTime()
{
    if ( IsRuning() || m_cfgActivity.start_hour.empty() )
    {
        return 0;
    }

    int32_t nNowTime   = TIMER.GetNow();
    const tm& localnow = TIMER.GetLocalNow();
    int32_t nowMinute  = localnow.tm_hour * 60 + localnow.tm_min;

    int32_t startMinute = m_cfgActivity.start_hour[0];
    int32_t startTime   = 0;

    for ( uint32_t i = 0; i < m_cfgActivity.start_hour.size(); ++i )
    {
        startTime = Answer::DayTime::dayzero( nNowTime ) + 60 * m_cfgActivity.start_hour[i];
        if ( startTime > nNowTime )
        {
            startMinute = m_cfgActivity.start_hour[i];
            break;
        }
    }

    int32_t days = -1;

    if ( checkData() && checkWeek() )
    {
        if ( nowMinute < startMinute )
        {
            days = 0;
        }
    }

    if ( days < 0 )
    {
        if ( m_cfgActivity.weekday.empty() )
        {
            return 0;
        }

        int32_t weekday     = TIMER.GetWeekDay();
        int32_t nextweekday = 0;

        // 反向遍历：从右向左查找第一个大于当前星期几的值
        for ( int32_t i = (int32_t)m_cfgActivity.weekday.size() - 1; i >= 0; --i )
        {
            if ( m_cfgActivity.weekday[i] > weekday )
            {
                nextweekday = m_cfgActivity.weekday[i];
                break;
            }
        }

        if ( nextweekday == 0 )
        {
            nextweekday = m_cfgActivity.weekday.back();
        }

        if ( nextweekday >= weekday )
        {
            days = nextweekday - weekday;
        }
        else
        {
            days = nextweekday + 7 - weekday;
        }
    }

    return 86400 * days + 60 * startMinute + Answer::DayTime::dayzero( nNowTime );
}

void CKaiFuBoss::broadcastReady()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }
    packet->writeInt32( BCI_KF_BOSS_READY );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}

void CKaiFuBoss::broadcastStart()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }
    packet->writeInt32( BCI_KF_BOSS_START );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}

void CKaiFuBoss::broadcastTimeEnd()
{
    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
    if ( NULL == packet )
    {
        return;
    }

    int32_t nNoticeId = BCI_KF_BOSS_END_NORMAL;
    if ( m_Boss != NULL && !m_Boss->isDead() )
    {
        nNoticeId = BCI_KF_BOSS_END_KILLED;
    }

    packet->writeInt32( nNoticeId );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.worldBroadcast( packet );
}

void CKaiFuBoss::sendPlayerScore( Player* player )
{
    if ( NULL == player )
    {
        return;
    }

    Answer::NetPacket* packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_NOTIFY_ACTIVITY_SCORE );
    if ( NULL == packet )
    {
        return;
    }

    packet->writeInt32( m_cfgActivity.id );
    packet->writeInt32( getLeftTime() );
    packet->setSize( packet->getWOffset() );
    GAME_SERVICE.sendPacketTo( player->getGateIndex(), packet );
}

void CKaiFuBoss::onTimeEnd()
{
    broadcastTimeEnd();
    delayKickAll( 0 );
}

void CKaiFuBoss::onMonsterAdd( MonsterActivity* pMonster )
{
    if ( pMonster != NULL )
    {
        m_Boss = pMonster;
    }
}
