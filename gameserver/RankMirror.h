//////////////////////////////////////////////////////////////////////////
// 威望排名系统 (存根 - 待完整移植)
//////////////////////////////////////////////////////////////////////////

#ifndef __RANK_MIRROR_H__
#define __RANK_MIRROR_H__

#include "stdafx.h"
#include "DataStructs.h"

class CRankMirror
{
public:
	static CRankMirror* instance()
	{
		static CRankMirror s_instance;
		return &s_instance;
	}

	int32_t GetWeiWangIndex( CharId_t cid )
	{
		// TODO: 完整实现 - 从 globalserver 获取威望排名
		return 0;
	}
};

#endif // __RANK_MIRROR_H__
