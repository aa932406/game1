#ifndef __GAME_FAMILY_MANAGER_H__
#define __GAME_FAMILY_MANAGER_H__

// 家族副本数据
struct FamilyDungeonStu
{
	int32_t	StartCounts;	// 启动次数
	int32_t	StartTime;		// 启动时间
	int32_t	nMaxHard;		// 最大完成难度

	FamilyDungeonStu() : StartCounts(0), StartTime(0), nMaxHard(0) {}
};

typedef std::map<FamilyId_t, FamilyInfo> FamilyInfoMap;
typedef std::map<FamilyId_t, FamilyDungeonStu> FamilyDungeonStuMap;
typedef std::map<FamilyId_t, Dungeon*> FamilyDungeonMap;

class FamilyManager
{
public:
	FamilyManager();
	~FamilyManager();

public:
	void		Init(int32_t line = 0);
	void		OnUpdateFamilyInfo( Answer::NetPacket* inPacket );
	void		OnInitFamilyInfo( Answer::NetPacket* inPacket );
	FamilyInfo	GetFamilyInfo( FamilyId_t nId );
	void		SendSocialFinishBoss( FamilyId_t nFamilyId, int32_t ActId, int8_t result );

	// 领地与勋章
	int8_t		GetTerritoryState( FamilyId_t nFamilyId );
	int32_t		GetMedlLevel( FamilyId_t nFamilyId );

	// 家族副本
	bool		StartfamilyDungeon( FamilyId_t nFamilyId, int32_t DungeonId, int32_t Hard );
	void		DeleteFamilyDungeon( FamilyId_t nFamilyId );
	void		SetFamilyDungeonHard( FamilyId_t nFamilyId, int32_t Hard );

private:
	void		addFamilyInfo( const FamilyInfo& info );
	void		updateFamilyInfo( const FamilyInfo& info );
	void		deleteFamilyInfo( FamilyId_t nFamilyId );
	void		SaveFamilyDungeonStuMap( FamilyId_t nFamilyId );

private:
	FamilyInfoMap			m_mFamilyInfo;
	FamilyDungeonStuMap		m_FamilyDungeonStuMap;
	FamilyDungeonMap		m_FamilyDungeonMap;
	Answer::Mutex			m_Lock;
	int32_t					m_nLastTime;
};

#define FAMILY_MANAGER Answer::Singleton<FamilyManager>::instance()

#endif //__SOCIAL_FAMILY_MANAGER_H__
