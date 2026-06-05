//////////////////////////////////////////////////////////////////////////
// 神威系统 (CShenWei)
// 基于威望排行和荣誉值提供属性加成
//////////////////////////////////////////////////////////////////////////

#ifndef __SHEN_WEI_H__
#define __SHEN_WEI_H__

#include "stdafx.h"
#include "ExtSystemBase.h"

class CShenWei : public CExtSystemBase
{
public:
	CShenWei();
	virtual ~CShenWei();

	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	AddCharAttr();
	virtual int32_t	GetRankAttr( int64_t Exp );
	virtual int32_t	GetShenWeiLevel();
};

#endif // __SHEN_WEI_H__
