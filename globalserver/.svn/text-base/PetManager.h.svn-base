/*
* ª√ ﬁ Ù–‘π‹¿Ì
*/

#ifndef __TPOC_PET_MANAGER_H__
#define __TPOC_PET_MANAGER_H__

#include "SocialPet.h"

class CPetManager
{
typedef	Answer::ObjectPool<CSocialPet>	SocialPetPool;
typedef std::map< PetId_t, CSocialPet* > SocialPetMap;
public:
	CPetManager();
	virtual ~CPetManager();

public:
	void			Init();

	CSocialPet*		GetPet( PetId_t nPetId );
	CSocialPet*		AddPet( const SocialPetData& pet, bool bNeedRefresh = true );
	CSocialPet*		UpdatePet( const SocialPetData& pet );
	void			DelPet( PetId_t nPetId );

	void			SendPetRankInfo( const PetIdList& petIdList, int16_t nGateIndex );
	void			SendGameAllRankInfo( int32_t nLine );
		
	void			GetAllPetRankData( PetRankDataVector& vPet );

	void			GetInsidePetRankData( PetRankDataVector& vPet );

	bool			ChangePetOwner( PetId_t nPetId, CharId_t nOwnerId );

private:
	SocialPetMap	m_mSocialPet;
	SocialPetPool	m_socialPetPool;
};

#define PET_MANAGER Answer::Singleton<CPetManager>::instance()

#endif	// __TPOC_PET_MANAGER_H__
