//////////////////////////////////////////////////////////////////////////
// 鬼谷道人系统 (存根 - 待完整移植)
//////////////////////////////////////////////////////////////////////////

#ifndef __GUI_GU_DAO_REN_H__
#define __GUI_GU_DAO_REN_H__

#include "stdafx.h"
#include "CfgData.h"

// 融合记录
struct RongHeRecord
{
	RongHeRecord()
		: nCid(0), nCostId(0), nGiveId(0), nSuccess(0), nTime(0)
	{
	}

	RongHeRecord(const RongHeRecord& other)
		: strName(other.strName), nCid(other.nCid), nCostId(other.nCostId),
		  nGiveId(other.nGiveId), nSuccess(other.nSuccess), nTime(other.nTime)
	{
	}

	~RongHeRecord() {}

	RongHeRecord& operator=(const RongHeRecord& other)
	{
		if (this != &other)
		{
			strName = other.strName;
			nCid = other.nCid;
			nCostId = other.nCostId;
			nGiveId = other.nGiveId;
			nSuccess = other.nSuccess;
			nTime = other.nTime;
		}
		return *this;
	}

	std::string	strName;
	CharId_t	nCid;
	int32_t		nCostId;
	int32_t		nGiveId;
	int32_t		nSuccess;
	int32_t		nTime;
};

class CGuiGuDaoRen
{
public:
	static CGuiGuDaoRen* instance()
	{
		static CGuiGuDaoRen s_instance;
		return &s_instance;
	}

	int32_t GetRongHeRate()
	{
		// TODO: 完整实现
		return 0;
	}

	void AddRongHeRecord(RongHeRecord* pRecord)
	{
		// TODO: 完整实现
	}

	void AddRongHeCount(int32_t nCostValue, int32_t nGetValue)
	{
		// TODO: 完整实现
	}
};

#endif // __GUI_GU_DAO_REN_H__
