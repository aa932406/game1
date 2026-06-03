#ifndef __SOCIAL_FAMILY_MANAGER_H__
#define __SOCIAL_FAMILY_MANAGER_H__

#include "Family.h"

typedef std::map<FamilyId_t, Family*> FamilyMap;
class FamilyManager
{
typedef Answer::ObjectPool<Family> FamilyPool;
public:
	FamilyManager();
	~FamilyManager();

public:
	bool	Init();
	Family*	GetFamily( FamilyId_t nId );
	void	SendFamilyList( const SocialPlayer& player );
	bool	CheckFamilyName( const std::string& name );
	Family*	CreateFamily( const std::string& name, SocialPlayer& player );
	void	CleanApply( PlayerInfo* pPlayerInfo );
	void	DestroyFamily( FamilyId_t nFamilyId );
	void	CheckFamilyTotom( int32_t nNowTime );
	void	UpdateFamilyInfo();
	void	ResetFamilyCount();
private:
	FamilyId_t getFamilyId( int32_t nServerId ) const;

private:
	FamilyMap		m_mFamily;
	FamilyPool		m_FamilyPool;
};

#define FAMILY_MANAGER Answer::Singleton<FamilyManager>::instance()

#endif //__SOCIAL_FAMILY_MANAGER_H__