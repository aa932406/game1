/*
* 幻兽属性排行管理
*/

#ifndef __TPOC_PET_RANK_H__
#define __TPOC_PET_RANK_H__

#include "SocialPet.h"

struct PetPointsRankGreater			{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
// struct PetStartHPRankGreater		{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
// struct PetStartPhyAtkMinRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
// struct PetStartPhyAtkMaxRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
// struct PetStartPhyDefRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
// struct PetStartMagAtkMinRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
// struct PetStartMagAtkMaxRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
// struct PetStartMagDefRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
struct PetGrowHPRankGreater			{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
struct PetGrowPhyAtkMinRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
struct PetGrowPhyAtkMaxRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
struct PetGrowPhyDefRankGreater		{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
struct PetGrowMagAtkMinRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
struct PetGrowMagAtkMaxRankGreater	{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};
struct PetGrowMagDefRankGreater		{	bool operator()( const CSocialPet* _Left, const CSocialPet* _Right ) const;	};

typedef std::multiset< CSocialPet*, PetPointsRankGreater >			PetPointsRank;
// typedef std::multiset< CSocialPet*, PetStartHPRankGreater >			PetStartHPRank;
// typedef std::multiset< CSocialPet*, PetStartPhyAtkMinRankGreater >	PetStartPhyAtkMinRank;
// typedef std::multiset< CSocialPet*, PetStartPhyAtkMaxRankGreater >	PetStartPhyAtkMaxRank;
// typedef std::multiset< CSocialPet*, PetStartPhyDefRankGreater >		PetStartPhyDefRank;
// typedef std::multiset< CSocialPet*, PetStartMagAtkMinRankGreater >	PetStartMagAtkMinRank;
// typedef std::multiset< CSocialPet*, PetStartMagAtkMaxRankGreater >	PetStartMagAtkMaxRank;
// typedef std::multiset< CSocialPet*, PetStartMagDefRankGreater >		PetStartMagDefRank;
typedef std::multiset< CSocialPet*, PetGrowHPRankGreater >			PetGrowHPRank;
typedef std::multiset< CSocialPet*, PetGrowPhyAtkMinRankGreater >	PetGrowPhyAtkMinRank;
typedef std::multiset< CSocialPet*, PetGrowPhyAtkMaxRankGreater >	PetGrowPhyAtkMaxRank;
typedef std::multiset< CSocialPet*, PetGrowPhyDefRankGreater >		PetGrowPhyDefRank;
typedef std::multiset< CSocialPet*, PetGrowMagAtkMinRankGreater >	PetGrowMagAtkMinRank;
typedef std::multiset< CSocialPet*, PetGrowMagAtkMaxRankGreater >	PetGrowMagAtkMaxRank;
typedef std::multiset< CSocialPet*, PetGrowMagDefRankGreater >		PetGrowMagDefRank;

class CPetRank
{
public:
	CPetRank();
	~CPetRank();

	void AddPet( CSocialPet* pPet, bool bNeedRefresh = true );
	void DelPet( CSocialPet* pPet );
	void UpdatePet( CSocialPet* pPet, const SocialPetData& pet );
	void RefreshRank();

	void AppendRankList( int8_t nRankType, Answer::NetPacket* packet );

private:
	void refreshPointsRank();
// 	void refreshStartHPRank();
// 	void refreshStartPhyAtkMinRank();
// 	void refreshStartPhyAtkMaxRank();
// 	void refreshStartPhyDefRank();
// 	void refreshStartMagAtkMinRank();
// 	void refreshStartMagAtkMaxRank();
// 	void refreshStartMagDefRank();
	void refreshGrowHPRank();
	void refreshGrowPhyAtkMinRank();
	void refreshGrowPhyAtkMaxRank();
	void refreshGrowPhyDefRank();
	void refreshGrowMagAtkMinRank();
	void refreshGrowMagAtkMaxRank();
	void refreshGrowMagDefRank();

	bool checkRefreshFlag( int32_t flag, PET_ATTR attr ) const;

	void appendPointsRankList( Answer::NetPacket* packet, int8_t& nCount );
// 	void appendStartHPRankList( Answer::NetPacket* packet, int8_t& nCount );
// 	void appendStartPhyAtkMinRankList( Answer::NetPacket* packet, int8_t& nCount );
// 	void appendStartPhyAtkMaxRankList( Answer::NetPacket* packet, int8_t& nCount );
// 	void appendStartPhyDefRankList( Answer::NetPacket* packet, int8_t& nCount );
// 	void appendStartMagAtkMinRankList( Answer::NetPacket* packet, int8_t& nCount );
// 	void appendStartMagAtkMaxRankList( Answer::NetPacket* packet, int8_t& nCount );
// 	void appendStartMagDefRankList( Answer::NetPacket* packet, int8_t& nCount );
	void appendGrowHPRankList( Answer::NetPacket* packet, int8_t& nCount );
	void appendGrowPhyAtkMinRankList( Answer::NetPacket* packet, int8_t& nCount );
	void appendGrowPhyAtkMaxRankList( Answer::NetPacket* packet, int8_t& nCount );
	void appendGrowPhyDefRankList( Answer::NetPacket* packet, int8_t& nCount );
	void appendGrowMagAtkMinRankList( Answer::NetPacket* packet, int8_t& nCount );
	void appendGrowMagAtkMaxRankList( Answer::NetPacket* packet, int8_t& nCount );
	void appendGrowMagDefRankList( Answer::NetPacket* packet, int8_t& nCount );

	void addDirty( PetId_t nPetId );
	void sendDirty();

private:
	PetPointsRank			m_pointsRank;
// 	PetStartHPRank			m_startHPRank;
// 	PetStartPhyAtkMinRank	m_startPhyAtkMinRank;
// 	PetStartPhyAtkMaxRank	m_startPhyAtkMaxRank;
// 	PetStartPhyDefRank		m_startPhyDefRank;
// 	PetStartMagAtkMinRank	m_startMagAtkMinRank;
// 	PetStartMagAtkMaxRank	m_startMagAtkMaxRank;
// 	PetStartMagDefRank		m_startMagDefRank;
	PetGrowHPRank			m_growHPRank;
	PetGrowPhyAtkMinRank	m_growPhyAtkMinRank;
	PetGrowPhyAtkMaxRank	m_growPhyAtkMaxRank;
	PetGrowPhyDefRank		m_growPhyDefRank;
	PetGrowMagAtkMinRank	m_growMagAtkMinRank;
	PetGrowMagAtkMaxRank	m_growMagAtkMaxRank;
	PetGrowMagDefRank		m_growMagDefRank;

	CharIdList				m_lstDirty;
};

/*
* 幻兽管理
*/
class CPetRankManager
{
public:
	CPetRankManager();
	virtual ~CPetRankManager();

public:
	void			DelPet( CSocialPet* pPet );
	void			AddPet( CSocialPet* pPet, bool bNeedRefresh = true );
	void			UpdatePet( CSocialPet* pPet, const SocialPetData& pet );
	void			SendPetRankList( int32_t nBaseId, int8_t nRankType, int16_t nGateIndex );
	void			RefreshRank();

private:
	CPetRank		m_vPetRank[MAX_PET_ID+1];
};

#define PET_RANK Answer::Singleton<CPetRankManager>::instance()

#endif	// __TPOC_PET_MANAGER_H__
