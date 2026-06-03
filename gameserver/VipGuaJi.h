#ifndef __VIP_GUA_JI_H__
#define __VIP_GUA_JI_H__
#include "stdafx.h"

class CVipGuaJi
{
public:
	CVipGuaJi();
	~CVipGuaJi();

	 void		CheckStar();
	 void		GetIconState( IconStateList& iconList );
	 int8_t		GetState();
private:
	bool		IsInHuoDong();
	void		SetState( int8_t State );
	void		SendHuoDongIcon( bool IsStart );
private:
	int8_t		m_State;
};
#define VIP_GUA_JI_SINGLETON Answer::Singleton<CVipGuaJi>::instance()

#endif