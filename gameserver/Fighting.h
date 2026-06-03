#ifndef __FIGHTING_H__
#define __FIGHTING_H__
#include "ExtSystemBase.h"
enum FightingType
{
	Type_Level				= 1,	//人物等级
	Type_Ling_Sou			= 2,	//灵兽加成
	Type_Huan_Sou_Star		= 3,	//幻兽星级
	Type_Huan_Sou_Rand		= 4,	//幻兽排名
	Type_Huan_Sou_Talent	= 5,    //战斗力天赋
	Type_QiShi_Appoint		= 6,	//骑士任命
	Type_QiShi_Special		= 7,	//特殊骑士
	Type_Equip_Base			= 8,	//装备基本
	Type_Equip_Quality		= 9,	//装备品质
	Type_Equip_Gem			= 10,	//宝石
	Type_Fa_Bao				= 11,	//法宝
	Type_JunTuan_Post		= 12,	//军团职位
	Type_The_Title			= 13,	//爵位加成
	Type_Soul				= 14,	//魂力
	Type_Guan_Wei		    = 15,	//官位
	Type_Guan_Wei_Qi_Shi	= 16,	//官位骑士
	Type_Zhu_Sheng_Zi_Zhan  = 17,	//诸神之战
	Type_Ling_Sou_Rand		= 18,	//灵兽排行榜
};
#define FAMILY_LEADER_BATTLE 50
class CPetFighting
{
public:
	CPetFighting()
	{
		m_PetId				= 0;
		m_PetBaseId			= 0;				
		m_PetQuality		= 0;	
		m_PetRank			= 0;		
		m_PetFighting		= 0;
		m_PetFightingLevel	= 0;
	}
	PetId_t			m_PetId;				// 幻宠id
	int32_t			m_PetBaseId;			// 幻宠配置表id
	int32_t			m_PetQuality;			// 幻宠品质
	int32_t			m_PetRank;				// 幻宠排名
	int32_t			m_PetFightingLevel;		// 幻宠战斗力天赋等级
	int32_t			m_PetFighting;			// 幻宠战斗力天赋等级
};

class CFighting:
	public CExtSystemBase
{
public:
	CFighting();
	~CFighting();

	virtual void	OnCleanUp();
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	int32_t		GetBattle() const;
	void		AddFighting();
private:
	int32_t		OnAskFightingInfo( Answer::NetPacket *inPacket );
	void		SendFightingInfo();					
	int32_t		GetPetRankBattle( int32_t PetRank );

	int32_t		GetPetKnightBattle( PET_KNIGHT knight );
private:
	int32_t		m_nBattle;
};

#endif  