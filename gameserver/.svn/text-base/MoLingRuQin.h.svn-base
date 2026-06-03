#ifndef __MO_LING_RU_QIN_H__
#define __MO_LING_RU_QIN_H__
#include "stdafx.h"
#include "Activity.h"

class CMoLingRuQin
	: public CActivity
{
public:
	CMoLingRuQin( const CfgActivity& cfgActivity );
	~CMoLingRuQin();
	virtual void	CheckActivity();
	virtual void	startActivity();	// 开始活动
	virtual void	stopActivity();		// 结束活动
private:
	void			FlushNpc();
	int32_t			m_LastFlushTime;
};

#endif

