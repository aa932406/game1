//////////////////////////////////////////////////////////////////////////
// 许愿系统
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_CHAR_WISH_H__
#define __TPOC_CHAR_WISH_H__

#include "ExtSystemBase.h"

class CExtCharWish : public CExtSystemBase
{
public:
	CExtCharWish(){}
	virtual ~CExtCharWish(){}

	virtual void	OnLoadFromDB( const PlayerDBData* dbData );
	virtual void	OnSaveToDB( PlayerDBData* dbData );

	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	void			AppendWishInfo( Answer::NetPacket* packet );

private:
	int32_t			OnWish( Answer::NetPacket* inPacket );			// 950
	int32_t			OnGetWishInfo( Answer::NetPacket* inPacket );	// 951
	int32_t			OnGetWishReward( Answer::NetPacket* inPacket );	// 952

	void			sendWishInfo();
	void			SendWishIcon();
	bool			canGetReward();
	int32_t			getLeftTime();

private:
	std::list<CharWishInfo>		m_lstWishs;
	int32_t						m_nNextId;
};

#endif	//__TPOC_CHAR_WISH_H__
