/*
* 宠物蛋
* 宠物蛋中能包含具体宠物信息
*/

#ifndef __TPOC_PET_EGG_H__
#define __TPOC_PET_EGG_H__

class PetEgg
{
public:
	PetEgg();
	~PetEgg();

public:
	void				CleanUp();
	bool				IsEmpty() const;
	int8_t				GetBag() const;
	int32_t				GetSlot() const;
	int32_t				GetBaseId() const;
	PetId_t				GetPetId() const;
	int32_t				GetStartTime() const;
	PET_EGG_STATE		GetState() const;
	void				Init( int32_t nBaseId );
	void				SetBagSlot( int8_t nBag, int32_t nSlot );
	void				StartHatch( int32_t nStartTime );
	void				EndHatch( PetId_t nPetId );
	void				StopHatch();
	void				AppendInfo( Answer::NetPacket* packet ) const;
	void				Init( const DBPetEgg& egg );
	void				Set( const PetEgg& egg );

private:
	int8_t				m_nBag;
	int32_t				m_nSlot;
	int32_t				m_nBaseId;
	PET_EGG_STATE		m_nState;
	int32_t				m_nStartTime;
	PetId_t				m_nPetId;
};

#endif	//__TPOC_PET_EGG_H__
