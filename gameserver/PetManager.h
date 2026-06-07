/*
* 宠物数据管理
*/

#ifndef __TPOC_PET_MANAGER_H__
#define __TPOC_PET_MANAGER_H__

#include "CfgData.h"
#include "Pet.h"

// 宠物ID缓存，按服号缓存ID范围，避免每次都查DB
struct PetNewId
{
	int64_t nNextId = 0;
	int64_t nMaxId = 0;
};

class CPetManager
{
	typedef std::list<CPet*> PetList;
	typedef std::map<PetId_t, CPet*> PetMap;
public:
	CPetManager();
	virtual ~CPetManager();

public:
	void			Init(int32_t line = 0);
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

	// 宠物排名
	int32_t			GetPetRankIndex( PetId_t nPetId );

private:
	PetId_t			getPetId( int32_t nServerId ) const;
	void			getPetIdFromDB( int32_t nServerId, int64_t &nNextId, int64_t &nMaxId );
	void			sendSocialUpdatePet( CPet* pPet );
	void			sendSocialDeletePet( PetId_t nPetId );

private:
	PetMap			m_mPet;
	std::map<PetId_t, int16_t>	m_mPetRank;			// 宠物排名缓存

	Answer::RwLock	m_rwLock;
	int64_t			m_nLastTick;
	std::list<PetId_t> m_NeedUpdatePet;

	std::map<int, PetNewId>	m_mNewId;				// 按服号缓存的宠物ID范围
	Answer::RwLock	m_IdLock;							// m_mNewId读写锁
};

#define PET_MANAGER Answer::Singleton<CPetManager>::instance()

#endif	//__TPOC_PET_MANAGER_H__
