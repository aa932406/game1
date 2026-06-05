#ifndef __TPOC_CHAR_WU_HUN_H__
#define __TPOC_CHAR_WU_HUN_H__

#include "ExtSystemBase.h"
#include "DataStructs.h"
#include "Shared.h"
#include <list>

class Player;

class CCharWuHun : public CExtSystemBase
{
public:
	CCharWuHun();
	virtual ~CCharWuHun();

	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	void	AddCharAttr();

	void	OnAddTalent( int32_t TalentId, int32_t TalentLevel );
	void	OnRemoveTalent( int32_t TalentId, int32_t TalentLevel );

	bool	checkWuHunPlace( int32_t Type, int32_t Slot );
	int32_t	GetSuitLevel( int32_t nLevel );

private:
	int32_t	onAskWuHunInfo( Answer::NetPacket *inPacket );
	int32_t	onDressWuHun( Answer::NetPacket *inPacket );
	int32_t	onUnDressWuHun( Answer::NetPacket *inPacket );
	int32_t	onCreateWuHun( Answer::NetPacket *inPacket );

	void	sendWuHunInfo();
	void	sendWuHunSlotInfo( int32_t Level, int32_t Slot );

private:
	int32_t	m_WuHun[5][16];
};

#endif	//__TPOC_CHAR_WU_HUN_H__
