#include "VipGuaJi.h"
#include "Timer.h"
#include "GameService.h"
CVipGuaJi::CVipGuaJi()
{
	m_State = AS_NOT_START;
}

CVipGuaJi::~CVipGuaJi()
{

}

void CVipGuaJi::CheckStar()
{
	if ( GAME_SERVICE.getLine() != 1 )
	{
		return;
	}
	if ( GetState() == AS_NOT_START )
	{
		if ( IsInHuoDong() )
		{
			SetState( AS_RUNNING );
			SendHuoDongIcon( true );
		}
	}
	else if ( GetState() == AS_RUNNING )
	{
		if ( !IsInHuoDong() )
		{
			SetState( AS_NOT_START );
			SendHuoDongIcon( false );
		}
	}
}

bool CVipGuaJi::IsInHuoDong()
{
	tm localnow =  TIMER.GetLocalNow();
	if ( localnow.tm_hour >= 22 || localnow.tm_hour <= 9  )
	{
		if ( localnow.tm_hour == 9 )
		{
			if ( localnow.tm_min < 30 )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}

int8_t CVipGuaJi::GetState()
{
	return m_State;
}

void CVipGuaJi::SetState( int8_t State )
{
	m_State = State;
}

void CVipGuaJi::SendHuoDongIcon( bool IsStart )
{
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket(Answer::PACK_DISPATCH, SM_SEND_ONE_ICON);
	if (NULL == packet)
	{
		return;
	}
	ShowIcon stu = {};
	stu.nId			= VIP_GUA_JI;
	stu.nState		= GetState();
	stu.nLeftTime	= -1;
	if ( IsStart )
	{
		stu.Effects = 1;
	}
	packet->writeInt32( stu.nId );
	packet->writeInt8( stu.nState );
	packet->writeInt32( stu.nLeftTime );
	packet->writeInt8( stu.IconLeft );
	packet->writeInt32( stu.IconRight );
	packet->writeInt8( stu.Effects );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.worldBroadcast( packet );	
}

void CVipGuaJi::GetIconState( IconStateList& iconList )
{
	ShowIcon icon = {};
	icon.nId		= VIP_GUA_JI;
	icon.nState		= GetState();
	icon.nLeftTime	= -1;
	if ( AS_RUNNING == icon.nState )
	{
		icon.Effects = 1;
	}
	iconList.push_back( icon );
}