#ifndef __GAME_FAMILY_MANAGER_H__
#define __GAME_FAMILY_MANAGER_H__

typedef std::map<FamilyId_t, FamilyInfo> FamilyInfoMap;
class FamilyManager
{
public:
	FamilyManager();
	~FamilyManager();

public:
	void		Init(int32_t line = 0);
	void		OnUpdateFamilyInfo( Answer::NetPacket* inPacket );
	FamilyInfo	GetFamilyInfo( FamilyId_t nId );
	void		SendSocialFinishBoss( FamilyId_t nFamilyId, int32_t ActId, int8_t result );

private:
	void		addFamilyInfo( const FamilyInfo& info );
	void		updateFamilyInfo( const FamilyInfo& info );
	void		deleteFamilyInfo( FamilyId_t nFamilyId );

private:
	FamilyInfoMap	m_mFamilyInfo;
	Answer::Mutex   m_Lock;
	int32_t			m_nLastTime;
};

#define FAMILY_MANAGER Answer::Singleton<FamilyManager>::instance()

#endif //__SOCIAL_FAMILY_MANAGER_H__