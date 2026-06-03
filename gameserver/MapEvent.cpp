#include "stdafx.h"

#include "MapEvent.h"

using namespace Answer;

IMapEvent::IMapEvent()
{
}

IMapEvent::~IMapEvent()
{
}

void IMapEvent::init( const CfgMapEventList& events )
{
	m_events = events;
}

void IMapEvent::clear()
{
	m_events.clear();
}

void IMapEvent::openEvent( int32_t nEvent )
{
	for ( CfgMapEventList::iterator iter = m_events.begin(); iter != m_events.end(); ++iter )
	{
		if ( iter->trigger_id == nEvent && !iter->bOpen )
		{
			iter->bOpen = true;
			checkEvent( *iter );	// 开启后立即检测一次，因为是后开启的，可能已经完成
		}
	}
}

void IMapEvent::openEvents( const Int32List& events )
{
	for ( Int32List::const_iterator iter = events.begin(); iter != events.end(); ++iter )
	{
		openEvent( *iter );
	}
}
