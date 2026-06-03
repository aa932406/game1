/**********************************************
* 地图触发事件接口
**********************************************/

#ifndef __TPOC_MAP_EVENT_H__
#define __TPOC_MAP_EVENT_H__

#include "actStructs.h"

class Player;
class IMapEvent
{
public:
	IMapEvent();
	virtual ~IMapEvent();

protected:
	void init( const CfgMapEventList& events );
	void clear();

protected:
	virtual void checkEvents() = 0;
	virtual void checkEvent( CfgMapEvent &mapEvent ) = 0;
	virtual void triggerEvent( CfgMapEvent &mapEvent, Unit* pUnit = NULL ) = 0;

protected:
	void openEvent( int32_t nEvent );
	void openEvents( const Int32List& events );

protected:
	CfgMapEventList	m_events;				// 触发器列表
};


#endif	//__TPOC_MAP_EVENT_H__
