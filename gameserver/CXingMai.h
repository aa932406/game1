#ifndef __TPOC_XING_MAI_H__
#define __TPOC_XING_MAI_H__

#include "ExtSystemBase.h"
#include "CfgData.h"
#include <list>
#include <map>

class CXingMai : public CExtSystemBase
{
public:
	CXingMai();
	virtual ~CXingMai();

	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	int32_t	OnXingMaiLevelUp( Answer::NetPacket *inPacket );
	int32_t	OnXingMaiSlotActive( Answer::NetPacket *inPacket );

	void	AddCharAttr();
	int32_t	GetMaxBossScore();
	bool	IsXingMaiSlotActived( int8_t nEquipSlot );

private:
	void	activeSlot( int8_t nIndex );
	bool	isSlotActived( int8_t nIndex );
};

#endif	//__TPOC_XING_MAI_H__
