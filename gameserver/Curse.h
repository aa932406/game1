#ifndef _CURSE_H_
#define _CURSE_H_

#include "ExtSystemBase.h"

class Curse : public CExtSystemBase
{
public:
	Curse();
	virtual ~Curse();

	virtual void GetInterestsProtocol(ProcIdList& procList);
	virtual int32_t DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket *inPacket);

	void AddCharAttr();
	int32_t DamageValue(int64_t MaxHp);

private:
	int32_t OnCurseLevelUp(Answer::NetPacket* inPacket);
};

#endif // _CURSE_H_
