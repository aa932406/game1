#ifndef __PLAYER_MAIL_H__
#define __PLAYER_MAIL_H__
#include "ExtSystemBase.h"


class CPlayerMail:
	public CExtSystemBase
{
public:
	CPlayerMail();
	~CPlayerMail();

	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnUpdate( int64_t curTick );
	virtual void	OnDaySwitch( int32_t nDiffDays );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	int32_t			OnReciveNewMail( Answer::NetPacket *inPacket );
private:
	int32_t			OnReadMail( Answer::NetPacket *inPacket );
	int32_t			OnRequestMailList( Answer::NetPacket *inPacket );
	int32_t			OnGetFuJian( Answer::NetPacket *inPacket );
	int32_t			OnDeleteMail( Answer::NetPacket *inPacket );
	void			PackParam( std::string Param, Answer::NetPacket *inPacket );

	void			SendMailList();
	void			SendMailContent( int32_t MailId );
	void			SendNewMail();
private:
	MailInfoMap		m_MailInfo;
};

#endif