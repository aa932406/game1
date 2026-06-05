#ifndef __TPOC_LEVEL_REFINING_H__
#define __TPOC_LEVEL_REFINING_H__

#include "ExtSystemBase.h"

// Protocol IDs
#define CM_REFIN_INFO				768
#define CM_REFIN_UPGRADE			769
#define SM_REFIN_INFO				0x2D0A

class CLevelRefining : public CExtSystemBase
{
public:
	CLevelRefining();
	virtual ~CLevelRefining();

	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	int32_t				OnRefining( Answer::NetPacket* inPacket );
	void				SendRefinInfo();
	int32_t				GetLeftTime();
	void				GetIcon( IconStateList& IconList );
	void				SendIcon();
	void				GetIconStu( ShowIcon* stu );
};

#define LEVEL_REFINING	Answer::Singleton<CLevelRefining>::instance()

#endif
