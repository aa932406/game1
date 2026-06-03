/*
* ª√ ﬁ Ù–‘
*/

#ifndef __TPOC_SOCIAL_PET_H__
#define __TPOC_SOCIAL_PET_H__

#include <set>

class CSocialPet
{
public:
	CSocialPet();
	~CSocialPet();

	void		reset();

	void		Set( const SocialPetData& petData );
	int32_t		GetBaseId() const;
	PetId_t		GetPetId() const;
	std::string	GetPetName() const;
	CharId_t	GetOwnerId() const;
	int32_t		GetRankFlag() const;
	int32_t		GetPoints() const;
	int32_t		GetBaseAttr( PET_ATTR nAttr ) const;
	bool		SetPointsRankIndex( int32_t nIndex );
	bool		SetRankIndex( PET_ATTR nAttr, int32_t nIndex );

	void		AppendRankInfo( Answer::NetPacket* packet );
	void		AppendRankList( Answer::NetPacket* packet );

	bool		IsInRank() const;

	bool		ChangeOwner( CharId_t nOwnerId );

private:
	SocialPetData	m_petData;
	PetRankIndex	m_rankIndex;
};

#endif	// __TPOC_SOCIAL_PET_H__
