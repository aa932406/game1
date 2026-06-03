#ifndef __CHAR_WORSHIP_H__
#define __CHAR_WORSHIP_H__

#include "ExtSystemBase.h"

class Player;
class CExtCharWorship : public CExtSystemBase
{
public:
	CExtCharWorship();
	virtual ~CExtCharWorship();

public:
	virtual void		OnCleanUp();
	virtual void		OnLoadFromDB( const PlayerDBData& dbData );
	virtual void		OnSaveToDB( PlayerDBData& dbData );
	virtual void		OnDaySwitch( int32_t nDiffDays );
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onSocialWorship( Answer::NetPacket* inPacket );
	void				sendSocialWorship( CharId_t nCharId );

public:
	void				SendWorshipInfo();

private:
	bool				isFunctionOpen() const;
	bool				isWorshiped( CharId_t nCharId ) const;
	bool				isTimesLimit() const;

	void				loadCharList( const std::string& str );
	std::string			saveCharList();

private:
	int32_t				m_nWorshipTimes;
	CharIdList			m_lstChars;
};

#endif	//__CHAR_WORSHIP_H__
