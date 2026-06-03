#ifndef __FUNCTION_OPEN_H__
#define __FUNCTION_OPEN_H__
#include "ExtSystemBase.h"

enum FunctionType
{
	FT_DUAN_ZHAO				= 9,		//锻造
	FT_CYCLE_TASK				= 26,		//循环任务
	FT_CHOU_JIANG				= 50,		//抽奖
	FT_FA_BAO					= 51,		//法宝
	FT_BOSS						= 53,		//boss
	FT_JUE_WEI					= 54,		//爵位
	FT_BAI_TAN					= 55,		//摆摊
	FT_LING_SOU					= 56,		//灵兽
	FT_QI_FU					= 57,		//祈福
	FT_HUN_LI					= 58,		//魂力
	FT_HUO_DONG_DA_TING			= 59,		//活动大厅
	FT_JIANG_LI_DA_TING			= 60,		//奖励大厅
	FT_SHOU_CHONG_ICON			= 62,		//首冲图标控制
	FT_NEW_SERVER_TE_HUI		= 63,		//新服特惠
	FT_EVERYDAY_SHOUCHONG		= 64,		//每日首冲
	FT_TOU_ZI					= 65,		//投资
	FT_KAI_FU_HUO_DONG			= 66,		//开服活动
	FT_GUAN_WEI					= 67,		//官位
	FT_HALL_OF_FAME				= 68,		//名人堂
};


class CFunctionOpen:
	public CExtSystemBase
{
public:
	CFunctionOpen();
	~CFunctionOpen();
	virtual	void		OnCleanUp();
	void				InitFunctionOpen( int32_t TaskId, int32_t Level );
	void				CheckFunctionOpne( int32_t TaskId, int32_t Level );
	bool				IsOpened( int32_t FunctionId );
	void				FunctionInit( int32_t FunctionId );
private:
	std::list<int32_t> m_OpenedList;			//已开启的
};

#endif