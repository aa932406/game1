#ifndef __GLOBAL_CHOU_JIANG_H__
#define __GLOBAL_CHOU_JIANG_H__
#include "stdafx.h"
#include "SocialPlayer.h"

struct GlobalChouJiangRecord
{
	std::string			Name;
	CharId_t			Cid;
	int8_t				ItemClass;
	int32_t				ItemId;
	int32_t				ItemCount;
};

typedef std::list<GlobalChouJiangRecord> GlobalCJRecordList;

struct TouZiRecord
{
	std::string			Name;
	CharId_t			Cid;
	int8_t				RecordType;
	int8_t				MoneyType;
	int32_t				MoneyValues;
};
typedef std::vector<TouZiRecord> TouZiRecordVector;


class GlobalRecord
{
public:
	GlobalRecord();
	~GlobalRecord();
	void		Init();

	void		OnRecvChouJiangRecord( Answer::NetPacket* InPacket );
	void		OnRecvCleanGlobalLuckPoint( Answer::NetPacket* InPacket );
	void		OnRecvCheckGlobalLuckPoint(SocialPlayer*  pSocialPlayer, Answer::NetPacket* InPacket );
	void		OnRecvAskChouJiangRecord( SocialPlayer* pPlayer, Answer::NetPacket* InPacket );
	
	void		OnRecvTouZiRecord( Answer::NetPacket* InPacket );

	void		SendChouJiangRecord( SocialPlayer* pPlayer );
	void		BroadcastNewRecord( GlobalChouJiangRecord& Record );
	
	void		SendAllTouZiRecord( SocialPlayer* pPlayer );
	void		SendOneTouZiRecord( SocialPlayer *pPlayer );

	void		SaveRecordToDB();
private:
	GlobalCJRecordList m_CJRecordList;
	int32_t			   m_LuckPoint;	 

	TouZiRecordVector  m_TouZiRecord;
};

#define  GLOBAL_RECORD Answer::Singleton<GlobalRecord>::instance()
#endif