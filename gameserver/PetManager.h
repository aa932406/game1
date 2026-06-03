/*
* 宠物数据管理
*/

#ifndef __TPOC_PET_MANAGER_H__
#define __TPOC_PET_MANAGER_H__

#include "CfgData.h"
#include "Pet.h"

class CPetManager
{
	typedef std::list<CPet*> PetList;
	typedef std::map<PetId_t, CPet*> PetMap;
public:
	CPetManager();
	virtual ~CPetManager();

public:
	void			Init();
	void			OnUpdated( const MemPetDBData& pet );
	void			OnDeleted( PetId_t nPetId );
	void			ResetRecords();
	void			OnUpdatePetRank( Answer::NetPacket* inPacket );
	void			OnInitPetRank( Answer::NetPacket* inPacket );

public:
	CPet*			GetPet( PetId_t nPetId );
	CPet*			CreateNewPetFromEgg( int32_t nEggId, Player* pCreater, int32_t nFromWay = PFW_NORMAL );
	CPet*			CreateNewPet( int32_t nBaseId, Player* pCreater, int8_t nFromWay = PFW_NORMAL );
	void			AddPet( CPet* pPet );
	void			DelPet( CPet* pPet );
	void			UpdatePet( CPet* pPet );
	void			GetPlayerPetList( CharId_t nCharId, PetList& pets );
	void			ChangeOwner( PetId_t nPetId, CharId_t nOwner );
	void			UpdataChangedPet();

private:
	PetId_t			getPetId( int32_t nServerId ) const;
	void			sendSocialUpdatePet( CPet* pPet );
	void			sendSocialDeletePet( PetId_t nPetId );

private:
	PetMap			m_mPet;

	Answer::RwLock	m_rwLock;
	int64_t			m_nLastTick;
	std::list<PetId_t> m_NeedUpdatePet;
};

#define PET_MANAGER Answer::Singleton<CPetManager>::instance()

#endif	// __TPOC_PET_MANAGER_H__
