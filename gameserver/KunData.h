#ifndef __KUN_DATA_H__
#define __KUN_DATA_H__

struct KunLingZhuBagItem
{
	int32_t nId;
	int32_t nCount;
};

struct KunDanTianItem
{
	int32_t nMid;
	int32_t nId;
	int32_t nEndTime;
};

#define MAX_LING_ZHU_BAG	100
#define MAX_LING_ZHU_POS	20
#define MAX_DAN_TIAN			6

#endif // __KUN_DATA_H__
