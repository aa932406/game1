#include "DaTiHD.h"
#include "GameService.h"
#include "DBService.h"
#include "Timer.h"
using namespace Answer;
#define	 MAX_QUESTIONS_COUNT	30		//题目数量


CDaTiHD::CDaTiHD( const CfgActivity& cfgActivity )
:CActivity( cfgActivity )
{
	m_DaTiIndex			= 0;
	m_LastSendQuestions = 0;
	m_RandAnswerDaTiIndex = 0;
	m_IsSendReadyStartToCs	= 0;
	m_QuestionsVct	= CFG_DATA.GetAllQuestions();
}

CDaTiHD::~CDaTiHD()
{
	
}

void CDaTiHD::reset()
{
	CActivity::reset();
	m_DaTiIndex				= 0;
	m_LastSendQuestions		= 0;
	m_RandAnswerDaTiIndex	= 0;
}

void CDaTiHD::Init()
{
}

void CDaTiHD::CheckActivity()
{
	if ( !checkData() )		// 日期
	{
		m_nState = AS_TIME_OUT;
		return;
	}

	if ( !checkWeek() )
	{
		m_nState = AS_NOT_START;
		return;
	}

	bool bRightLine			= checkLine();
	ACTIVITY_STATE nState	= checkTime();
	switch ( nState )
	{
	case AS_NOT_START:
		{
			if ( m_nState == AS_END )
			{
				m_nState = AS_NOT_START;
			}
			else if ( m_nState == AS_RUNNING )
			{			
				m_nState = AS_NOT_START;
				if ( bRightLine )
				{
					SendEndDaTiHD();
					BroadcastActivityState();
				}
				reset();
			}
		}
		break;
	case AS_END:
		{
			if ( m_nState == AS_RUNNING )
			{	
				m_nState = AS_END;
				if ( bRightLine )
				{
					SendEndDaTiHD();
					BroadcastActivityState();
				}
				reset();
			}
			m_nState = AS_END;
		}
		break;
	case AS_READY:
		{
			if ( m_nState == AS_END || m_nState == AS_NOT_START )
			{
				m_nState = AS_READY;
				
			}
			if ( m_nState == AS_READY )
			{
				if ( bRightLine )
				{
					tm localnow = TIMER.GetLocalNow();
					int32_t NowSeconds	= localnow.tm_hour * 60 * 60 + localnow.tm_min * 60 + localnow.tm_sec;
					int32_t startSeconds = m_cfgActivity.start_hour[0]*60;
					if ( startSeconds - NowSeconds <= 100 && m_IsSendReadyStartToCs == 0 )
					{
						broadcastReady();
						BroadcastActivityState();
						SendReadyStartDaTiHD();
						m_IsSendReadyStartToCs	= 1;
					}
				}
			}
		}
		break;
	case AS_RUNNING:
		{
			if ( m_nState == AS_READY )
			{	
				m_nState = AS_RUNNING;
				if ( bRightLine )
				{
					RandomQuestions();
					SendStartDaTiHD();
					broadcastStart();
					BroadcastActivityState();
				}
			}
			else if ( m_nState == AS_RUNNING )
			{
				tm localnow = TIMER.GetLocalNow();
				int32_t NowSeconds	= localnow.tm_hour * 60 * 60 + localnow.tm_min * 60 + localnow.tm_sec; 
				if ( m_LastSendQuestions + DA_TIME_MAX_TIME <= NowSeconds )
				{
					m_DaTiIndex++;
					SendQuestionsInfo( NowSeconds );
					m_LastSendQuestions = NowSeconds;
				}

				if ( m_LastSendQuestions + RAND_ANSWER_TIME <= NowSeconds && m_RandAnswerDaTiIndex != m_DaTiIndex )
				{
					m_RandAnswerDaTiIndex = m_DaTiIndex;
					RandAnswer();
				}
			}
		}
		break;
	default:
		return;
	}
}

void CDaTiHD::RandAnswer()
{
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_PROC, IM_SOCIAL_RAND_ANSWER );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8(0);
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

void CDaTiHD::RandomQuestions()
{
	srand( TIMER.GetNow());
	std::random_shuffle(m_QuestionsVct.begin(),m_QuestionsVct.end());
}

void CDaTiHD::SendReadyStartDaTiHD()
{
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_PROC, IM_SOCIAL_DA_TI_START_READY);
	if (NULL == packet)
	{
		return;
	}
	tm localnow    = TIMER.GetLocalNow();
	int32_t NowSeconds	= localnow.tm_hour * 60 * 60 + localnow.tm_min * 60 + localnow.tm_sec; 
	int32_t StartSeconds  = m_cfgActivity.start_hour[0] * 60;
	packet->writeInt32( NowSeconds );
	packet->writeInt32( StartSeconds );
	packet->writeInt32( GetId() );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

void CDaTiHD::SendEndDaTiHD()
{
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_PROC, IM_SOCIAL_DA_TI_END);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8(0);
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

void CDaTiHD::SendStartDaTiHD()
{
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_PROC, IM_SOCIAL_DA_TI_START);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8(0);
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}

void CDaTiHD::SendQuestionsInfo( int32_t NowSeconds )
{
	if ( m_DaTiIndex > MAX_QUESTIONS_COUNT )
	{
		return;
	}
	if ( m_DaTiIndex < 0 )
	{
		return;
	}
	if ( static_cast<size_t>(m_DaTiIndex) > m_QuestionsVct.size() )
	{
		return;
	}
	
	NetPacket *packet = GAME_SERVICE.popNetpacket(PACK_PROC, IM_SOCIAL_QUESTIONS);
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( m_DaTiIndex );
	packet->writeInt32( m_QuestionsVct[m_DaTiIndex-1].QuestionId );
	packet->writeInt8( m_QuestionsVct[m_DaTiIndex-1].AnswerId );
	packet->writeInt32( NowSeconds );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacket(packet);
}
