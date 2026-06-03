#ifndef __KAI_FU_HUO_DONG_H__
#define __KAI_FU_HUO_DONG_H__
#include "CfgData.h"
class CKaiFuHuoDong
{
public:
	CKaiFuHuoDong();
	~CKaiFuHuoDong();

	void				Init();

	int32_t				KaiFuHuoDongOperator( Player* pPlayer, Answer::NetPacket *inPacket );
	int32_t				OnGetReward( Player* pPlayer, Answer::NetPacket *inPacket );
	int32_t				AskInfo( Player* pPlayer, Answer::NetPacket *inPacket );
	void				RecvRank( Answer::NetPacket *inPacket );
	void				SendHuoDongState( Player* pPlayer );
	
	void				AddRewardRecord( Player* pPlayer, int32_t Index );
	int32_t				CanGetReward( Player* pPlayer, int32_t Index );
	bool				IsAlreadyGet( Player* pPlayer,int32_t Index );
	int32_t				GetLimitCount( std::string LimitString );
	void				AddLimitCount( std::string LimitString, int32_t Values );
	int32_t				GetRewardState( Player* pPlayer, int32_t Conditions, int32_t Param1, int32_t Param2, int32_t LimitCount );
	void				UpdateHDData( Player* pPlayer,KaiFuHuoDongCondition Type, int32_t Values );
	void				GetKaiFuHuoDongIcon( Player* pPlayer, IconStateList& IconList );
	void				SendKaiFuHuoDongIcon( Player* pPlayer );
	ShowIcon			GetKaiFuHuoDongIconStu( Player *pPlayer );
	void				SendHuoDongInfo( Player* pPlayer,int8_t Type );
	std::string			GetLevelLimitString( int32_t Level );
	int32_t				GetDiffDay();
	void				LoadData();
	void				SaveData();
private:
	KaiFuHuoDongRank		m_PetRank;
	KaiFuHuoDongRank		m_BattleRank;
	int32_t					m_PetRankEndDay;		
	int32_t					m_BattleRankEndDay;
	int32_t					m_HDLastDay;
	KaiFuHuoDongCfg			m_KaiFuHuoDongCfg;
};
#define KAI_FU_HUO_DONG Answer::Singleton<CKaiFuHuoDong>::instance()
#endif