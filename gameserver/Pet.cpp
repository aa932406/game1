#include "stdafx.h"

#include "CfgData.h"
#include "GameService.h"
#include "Map.h"
#include "Player.h"
#include "Pet.h"
#include "PoolManager.h"
#include "PetManager.h"
#include "KaiFuHuoDong.h"

using namespace Answer;

CPet::CPet()
{
	reset();
}

CPet::~CPet()
{

}

void CPet::reset()
{
	m_nOwner		= 0;
	m_nBaseId		= 0;
	m_nLevel		= 0;
	m_nExp			= 0;
	m_nPotential	= 0;
	m_nRein			= 0;
	m_nAdjustRein	= 0;
	m_nNumber		= 0;
	m_nLucky		= 0;
	m_nPhase		= PP_INVALID;
	m_nFromWay		= PFW_NORMAL;
	m_nGrowTimes	= 0;

	bzero( m_strName, sizeof( m_strName ) );
	bzero( m_vRecord, sizeof( m_vRecord ) );
	bzero( m_vAttr, sizeof( m_vAttr ) );
	bzero( m_vSkill, sizeof( m_vSkill ) );
	bzero( &m_RankIndex, sizeof( m_RankIndex ) );

	m_nFlag				= 0;
	m_nBattle			= 0;
	m_nPoints			= 0;
	m_nRankFlag			= 0;
	m_bPetBorn			= false;
	m_nStartPoints		= 0;
	m_nGrowPoints		= 0;
	m_bNeedSyncSelf		= false;
	m_bNeedSyncStatus	= false;
}

void CPet::Init( CharId_t nOwner, PetId_t nPetId, int32_t nBaseId, int8_t nFromWay )
{
	m_nOwner	= nOwner;
	m_nPetId	= nPetId;
	m_nBaseId	= nBaseId;
	m_nFromWay	= nFromWay;
	born();
}

void CPet::Init( CharId_t nOwner, PetId_t nPetId, const CfgPetEgg& cfgEgg, int8_t nFromWay )
{
	m_nOwner	= nOwner;
	m_nPetId	= nPetId;
	m_nBaseId	= cfgEgg.nPetId;
	m_nFromWay	= nFromWay;
	born( cfgEgg );
}

void CPet::Reborn( const CfgPetEgg& cfgEgg )
{
	born( cfgEgg );
	onChange();
}

void CPet::born( const CfgPetEgg& cfgEgg )
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return;
	}

	// ��ʼ��������������
	setPhase( pCfgPet->m_nPhase );

	m_nLevel		= cfgEgg.nLevel;
	m_nExp			= 0;
	m_nPotential	= 0;
	m_nRein			= cfgEgg.nRein * PET_REIN_RATE;
	m_nGrowTimes	= cfgEgg.nRein * PET_REIN_RATE;
	m_nNumber		= 0;
	m_nAdjustRein	= 0;

	m_nFlag			= 0;
	m_nBattle		= 0;
	m_nPoints		= 0;
	m_nRankFlag		= 0;
	m_bPetBorn		= false;
	m_bNeedSyncSelf	= true;

	bzero( m_strName, sizeof( m_strName )  );	// ����Ϊ��ʱ�ͻ����Լ�����
	//snprintf( m_strName, MAX_NAME_CCH_LENGTH, pCfgPet->m_strName.c_str() );
	initBaseAttr( cfgEgg );
	initSkill();
	calPoints();
}

void CPet::born()
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return;
	}

	// ��ʼ��������������
	setPhase( pCfgPet->m_nPhase );

	m_nLevel		= 1;
	m_nExp			= 0;
	m_nPotential	= 0;
	m_nRein			= 0;
	m_nGrowTimes	= 0;
	m_nNumber		= 0;
	m_nAdjustRein	= 0;

	m_nFlag			= 0;
	m_nBattle		= 0;
	m_nPoints		= 0;
	m_nRankFlag		= 0;
	m_bPetBorn		= false;
	m_bNeedSyncSelf	= true;

	bzero( m_strName, sizeof( m_strName )  );	// ����Ϊ��ʱ�ͻ����Լ�����
	//snprintf( m_strName, MAX_NAME_CCH_LENGTH, pCfgPet->m_strName.c_str() );
	initBaseAttr();
	initSkill();
	calPoints();
}

void CPet::OnLoadFromDB( const MemPetDBData& pet, bool bCal )
{
	m_nOwner		= pet.nOwner;
	m_nPetId		= pet.nPetId;
	m_nBaseId		= pet.nBaseId;
	m_nLevel		= pet.nLevel;
	m_nExp			= pet.nExp;
	m_nLucky		= pet.nLucky;
	m_nPotential	= pet.nPotential;
	m_nRein			= pet.nRein;
	m_nAdjustRein	= pet.nAdjustRein;
	m_nNumber		= pet.nNumber;
	m_nPhase		= static_cast<PET_PHASE>( pet.nPhase );	
	m_nFromWay		= pet.nFromWay;
	m_nGrowTimes	= pet.nGrowTimes;

	m_nFlag			= pet.nFlag;
	m_nBattle		= pet.nBattle;
	m_nPoints		= pet.nPoints;
	m_bPetBorn		= pet.nBornFlag > 0;
	m_bNeedSyncSelf	= true;

	snprintf( m_strName, MAX_NAME_CCH_LENGTH, pet.strName.c_str() );
	memcpy( m_vAttr, pet.vAttr, sizeof( m_vAttr ) );
	loadRecords( pet.records );
	loadSkills( pet.skills );

	if ( bCal )
	{
		calPoints();
	}
}

void CPet::loadRecords( const std::string& str )
{
	StringVector vStr = Answer::StringUtility::split( str, "|" );
	int32_t isize = vStr.size();
	for ( int8_t i = 0; i < isize && i < PET_RECORD_SIZE; ++i )
	{
		m_vRecord[i] = atoi( vStr[i].c_str() );
	}
}

void CPet::loadSkills( const std::string& str )
{
	StringVector vStr = Answer::StringUtility::split( str, "|" );
	int32_t isize = vStr.size();
	for ( int32_t i = 0; i < isize; ++i )
	{
		StringVector vSkill = Answer::StringUtility::split( vStr[i], ":" );
		if ( vSkill.size() == 3 )
		{
			int32_t nIndex = atoi( vSkill[0].c_str() );
			if ( nIndex < 0 || nIndex >= PET_SKILL_BAR_SIZE )
			{
				continue;
			}
			m_vSkill[nIndex].nId		= atoi( vSkill[1].c_str() );
			m_vSkill[nIndex].nLevel		= atoi( vSkill[2].c_str() );
		}
	}
}

void CPet::OnSaveToDB( MemPetDBData& pet )
{
	pet.nOwner		= m_nOwner;
	pet.nPetId		= m_nPetId;
	pet.nBaseId		= m_nBaseId;				
	pet.nLevel		= m_nLevel;					
	pet.nExp		= m_nExp;						
	pet.nLucky		= m_nLucky;
	pet.nPotential	= m_nPotential;				
	pet.nRein		= m_nRein;				
	pet.nAdjustRein	= m_nAdjustRein;			
	pet.nNumber		= m_nNumber;					
	pet.nPhase		= m_nPhase;
	pet.nFromWay	= m_nFromWay;
	pet.nGrowTimes	= m_nGrowTimes;

	pet.strName		= m_strName;
	memcpy( pet.vAttr, m_vAttr, sizeof( m_vAttr ) );
	pet.records		= saveRecords();
	pet.skills		= saveSkills();

	pet.nFlag		= m_nFlag;
	pet.nBattle		= m_nBattle;
	pet.nPoints		= m_nPoints;
	pet.nBornFlag	= m_bPetBorn ? 1 : 0;
}

std::string CPet::saveRecords() const
{
	std::stringstream ss;
	for ( int8_t i = 0; i < PET_RECORD_SIZE; ++i )
	{
		ss << "|" << m_vRecord[i];
	}
	return ss.str();
}

std::string CPet::saveSkills() const
{
	std::stringstream ss;
	for ( int32_t i = 0; i < PET_SKILL_BAR_SIZE; ++i )
	{
		if ( m_vSkill[i].nId > 0 )
		{
			ss << "|" << i << ":" << m_vSkill[i].nId << ":" << m_vSkill[i].nLevel;
		}
	}
	return ss.str();
}

PetId_t CPet::GetPetId() const
{
	return m_nPetId;
}

int32_t CPet::GetFlag() const
{
	return m_nFlag;
}

void CPet::SetPetId( PetId_t nPetId )
{
	m_nPetId = nPetId;
}

int32_t CPet::GetBaseId() const
{
	return m_nBaseId;
}

int32_t CPet::GetLevel() const
{
	if ( IsInsidePet( m_nBaseId ) )
	{
		Player* pPlayer = GAME_SERVICE.getPlayer( m_nOwner, 0, false );
		if ( pPlayer != NULL )
		{
			return pPlayer->getLevel();
		}
	}
	return m_nLevel;
}

int32_t CPet::GetPetLevel() const
{
	return m_nLevel;
}

int64_t CPet::GetExp() const
{
	return m_nExp;
}

PET_PHASE CPet::GetPhase() const
{
	return m_nPhase;
}

Job_t CPet::GetOrderJob() const
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return 0;
	}

	return pCfgPet->m_nOrderJob;
}

Job_t CPet::GetPetJob() const
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return 0;
	}

	return pCfgPet->m_nPetJob;
}

bool CPet::IsXOType() const
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return 0;
	}

	return pCfgPet->m_nXxoo == 0 ? false : true;
}

int32_t CPet::GetRare() const
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return 0;
	}

	return pCfgPet->m_nRare;
}

int32_t CPet::GetRein() const
{
	return m_nRein / PET_REIN_RATE;
}

int32_t CPet::GetReinLimit() const
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return 0;
	}

	return pCfgPet->m_nRein + m_nAdjustRein;
}

bool CPet::IsRidePet() const
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return false;
	}
	return pCfgPet->m_nRideSkin > 0;
}

bool CPet::IsReinLimit() const
{
	return GetRein() >= GetReinLimit();
}

void CPet::AppendBaseInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt64( m_nPetId );								// ����ID
	packet->writeInt32( m_nFlag );								// ����ID
	packet->writeInt32( m_nBaseId );							// ����ID
	packet->writeUTF8( m_strName );								// ��������
	packet->writeInt32( m_nLevel );								// ����ȼ�
	packet->writeInt64( m_nExp );								// ���ﾭ��ֵ
	packet->writeInt32( m_nPotential );							// Ǳ��ֵ��			
	packet->writeInt32( GetRein() );							// ת��������		
	packet->writeInt32( GetReinLimit() );						// ת���������ƣ�	
	packet->writeInt32( m_nNumber );							// �����ƣ�			
	packet->writeInt32( m_nPhase );								// �������ԣ�
	packet->writeInt32( m_nLucky );								// ��������ֵ		
	packet->writeInt32( m_nPoints );							// ����Ʒ�ʣ�		
	packet->writeInt32( m_nBattle );							// ս������	
	packet->writeInt8( m_nFromWay );							// ��Դ��Ϣ
	packet->writeInt32( GetGrowTimes() );						// ����ɳ��ʻû�����
	
	appendInitInfo( packet );									// �����ʼ����
	appendSkillInfo( packet );									// ���＼��
	appendRecordInfo( packet );									// �����¼
	appendRankInfo( packet );									// �������а���Ϣ
}

void CPet::appendInitInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	for ( int8_t i = PET_ATTR_GROW_HP; i < PET_ATTR_COUNT; ++i )				// ���޳�ʼ����
	{
		packet->writeInt32( m_vAttr[i] );
	}
}

void CPet::appendSkillInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	uint32_t nOffSet = packet->getWOffset();
	int8_t nCount = 0;
	packet->writeInt8( nCount );
	for ( int8_t i = 1; i < PET_SKILL_BAR_SIZE; ++i )
	{
		if ( m_vSkill[i].nId > 0 )
		{
			packet->writeInt8( i - 1 );
			packet->writeInt32( m_vSkill[i].nId );
			packet->writeInt32( m_vSkill[i].nLevel );
			++nCount;
		}
	}
	uint32_t nOldOffSet = packet->getWOffset();
	packet->setWOffset( nOffSet );
	packet->writeInt8( nCount );
	packet->setWOffset( nOldOffSet );
}

void CPet::appendRecordInfo( Answer::NetPacket* packet )
{
	if ( NULL == packet )
	{
		return;
	}

	uint32_t nOffSet = packet->getWOffset();
	int32_t nCount = 0;
	packet->writeInt8( nCount );
	for ( int8_t i = 0; i < PET_RECORD_SIZE; ++i )
	{
		if ( m_vRecord[i] > 0 )
		{
			packet->writeInt8( i );
			packet->writeInt32( m_vRecord[i] );
			++nCount;
		}
	}
	int32_t nOldOffSet = packet->getWOffset();
	packet->setWOffset( nOffSet );
	packet->writeInt8( nCount );
	packet->setWOffset( nOldOffSet );
}

void CPet::appendRankInfo( Answer::NetPacket* packet )
{
	packet->writeInt16( m_RankIndex.nPointsIndex );
// 	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_START_HP] );
// 	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_ATK_MIN] );
// 	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_ATK_MAX] );
// 	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_DEF] );
// 	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_ATK_MIN] );
// 	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_ATK_MAX] );
// 	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_DEF] );
	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_GROW_HP] );
	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_ATK_MIN] );
	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_ATK_MAX] );
	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_DEF] );
	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_ATK_MIN] );
	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_ATK_MAX] );
	packet->writeInt16( m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_DEF] );
}

PetSkillInfo* CPet::GetSkill( SkillId_t nSkill )
{
	if ( nSkill <= 0 )
	{
		return NULL;
	}
	for ( int32_t i = 0; i < PET_SKILL_BAR_SIZE; ++i )
	{
		if ( m_vSkill[i].nId == nSkill )
		{
			return &m_vSkill[i];
		}
	}
	return NULL;
}

PetSkillInfo* CPet::GetSkillByPos( int8_t nSkillPos )
{
	if ( nSkillPos < 0 || nSkillPos >= PET_SKILL_BAR_SIZE )
	{
		return NULL;
	}

	return &m_vSkill[nSkillPos];
}

bool CPet::LearnSkill( SkillId_t nSkill, int8_t nSkillPos )
{
	int8_t nSkillBarSize = getSkillBarSize();
	if ( nSkillPos < 0 || nSkillPos >= nSkillBarSize )
	{
		return false;
	}

	for ( int8_t i = 1; i < nSkillBarSize; ++i )
	{
		if ( m_vSkill[i].nId == nSkill && nSkillPos != i )
		{
			return false;
		}
	}

	if ( m_vSkill[nSkillPos].nId == 0 )
	{
		m_vSkill[nSkillPos].nId = nSkill;
	}
	else if ( m_vSkill[nSkillPos].nId != nSkill )
	{
		return false;
	}

	++m_vSkill[nSkillPos].nLevel;
	calPoints();
	onChange();
	return true;
}

bool CPet::ForgetSkill( SkillId_t nSkill )
{
	for ( int32_t i = 1; i < PET_SKILL_BAR_SIZE; ++i )
	{
		if ( m_vSkill[i].nId == nSkill )
		{
			if ( i == 0 )
			{
				return false;	// �츳���ܲ�������
			}
			m_vSkill[i].nId = 0;
			m_vSkill[i].nLevel = 0;
			m_vSkill[i].nCDTime = 0;
			calPoints();
			onChange();
			return true;
		}
	}
	return false;
}

void CPet::ChangeName( const std::string& strName )
{
	snprintf( m_strName, MAX_NAME_CCH_LENGTH, strName.c_str() );
	onChange();
}

void CPet::ChangeOwner( CharId_t nOwner, bool bSend )
{
	m_nOwner = nOwner;
	if ( bSend )
	{
		onChange();
	}
}

std::string CPet::GetName() const
{
	return m_strName;
}


bool CPet::CheckRecord( PET_RECORD record ) const
{
	if ( record < 0 || record >= PET_RECORD_SIZE )
	{
		return false;
	}

	return checkRecord( record, m_vRecord[record] );
}

int32_t CPet::AddRecord( PET_RECORD record, int32_t nAddVal )
{
	if ( record < 0 || record >= PET_RECORD_SIZE )
	{
		return 0;
	}

	m_vRecord[record] += nAddVal;
	onChange();
	return m_vRecord[record];
}

bool CPet::checkRecord( PET_RECORD record, int32_t nVal ) const
{
	switch ( record )
	{
	case PR_USE_EXP_GRAIN:			return nVal < PRL_USE_EXP_GRAIN;
	case PR_USE_EXP_BALL:			return nVal < PRL_USE_EXP_BALL;
	default:break;
	}
	return false;
}

PET_PHASE CPet::ChangePhase( PET_PHASE phase )
{
	if ( m_nPhase != phase )
	{
		setPhase( phase );
		calPoints();
		onChange();
	}
	return m_nPhase;
}

void CPet::setPhase( PET_PHASE phase )
{
	if ( phase == PP_INVALID )
	{
		m_nPhase = randPhase();
	}
	else
	{
		m_nPhase = phase;
	}
}

PET_PHASE CPet::randPhase()
{
	int32_t nRand = RANDOM.generate( 1, 1000 );
	if ( nRand < 250 )
	{
		return PP_WIND;
	}
	else if ( nRand < 500 )
	{
		return PP_WATER;
	}
	else if ( nRand < 750 )
	{
		return PP_FIRE;
	}
	else if ( nRand < 1000 )
	{
		return PP_EARTH;
	}

	return PP_ELECTRIC;		// nRand == 1000
}

int32_t CPet::GetBaseAttr( PET_ATTR attr ) const
{
	if ( attr < 0 || attr >= PET_ATTR_COUNT )
	{
		return 0;
	}
	if ( attr < PET_ATTR_GROW_HP )
	{
		const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
		if ( NULL == pCfgPet )
		{
			return 0;
		}
		return pCfgPet->m_vMaxAttr[attr];
	}
	return m_vAttr[ attr ];
}

int32_t CPet::GetBattle() const
{
	return m_nBattle;
}

int32_t CPet::GetPoints() const
{
	return m_nPoints;
}

int32_t CPet::GetStartPoints() const
{
	return m_nStartPoints;
}

int32_t CPet::GetGrowPoints() const
{
	return m_nGrowPoints;
}

int32_t CPet::GetGrowTimes() const
{
	return m_nGrowTimes / PET_REIN_RATE;
}

int8_t CPet::GetFromWay() const
{
	return m_nFromWay;
}

int32_t CPet::GetLucky() const
{
	return m_nLucky;
}

bool CPet::AddExp( int64_t nExp )
{
	Player* pPlayer = GAME_SERVICE.getPlayer( m_nOwner, 0, false );
	if ( NULL == pPlayer )
	{
		return false;
	}
	int32_t Level = pPlayer->getLevel();
	if ( !IsInsidePet( GetBaseId() ) && Level + LEVEL_DIFF < GetLevel() )
	{
		return false;
	}

	m_nExp += nExp;
	if ( checkLevelUp( Level ) )
	{
		onLevelUp();
		return true;
	}

	m_bNeedSyncSelf	= true;
	return false;
}

bool CPet::checkLevelUp( int32_t OwnerLevel )
{
	bool bLevelUp = false;
	// ������������
	int64_t nLevelUpNeedExp = getLevelUpExp();
	if ( nLevelUpNeedExp < 0 )
	{
		return false;
	}
	while ( m_nExp > nLevelUpNeedExp )
	{	
		if ( !IsInsidePet( GetBaseId() ) && m_nLevel  >= OwnerLevel + LEVEL_DIFF )
		{
			m_nExp = 0;
			break;
		}
		m_nExp -= nLevelUpNeedExp;
		++m_nLevel;
		nLevelUpNeedExp = CFG_DATA.GetPetExp( m_nLevel );
		bLevelUp = true;
	}
	return bLevelUp;
}

int32_t CPet::getLevelUpExp() const
{
	if ( IsInsidePet( GetBaseId() ) )
	{
		return CFG_DATA.GetInsidePetTable().GetLevelExp( m_nLevel );
	}
	else
	{
		return CFG_DATA.GetPetExp( m_nLevel );
	}
}

void CPet::onLevelUp()
{
	calPoints();
	onChange();
}

void CPet::calPoints()
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return;
	}

	int32_t sum = 0;
	// ���ó��������֣���ͨ��û�����
	if ( IsInsidePet( m_nBaseId ) )
	{
		sum += m_nLevel * WU_LING_RATE;
	}
	// 2)�������ԣ��硢ˮ�����������ֶ�Ϊ0��ֻ�������Բ���300���֡�
	if ( m_nPhase == PP_ELECTRIC )
	{
		sum += 300;
	}

	// 3)���޺�����Ϊ��ͨ������Ϊ0��������ʽ�ɺ����ȵ���ֵ�������֣�1��1��
	sum += pCfgPet->m_nRare;

	// 4)����ֵ���� = ( x �C 50 ) * 2
	if ( IsInsidePet( m_nBaseId ) )
	{
		sum += ( m_nLucky - 50 ) * 10;
	}
	else
	{
		sum += ( m_nLucky - 50 ) * 2;
	}


	// 5)ת��������ת����������Ҫ�ڻ��޻û����ۼӵģ�ÿ����1��ת��������1�����֡�
	sum += GetRein();

	// 6)�ɳ��ʣ��ɳ��ʵ�����ͨ���ɳ�������ͳ�ƻ�á�
	m_nGrowPoints = 0;
	{
		for ( int8_t i = PET_ATTR_GROW_HP; i <= PET_ATTR_GROW_MAG_DEF; ++i )
		{
			if ( IsInsidePet( m_nBaseId ) )
			{
				if ( i == PET_ATTR_GROW_PHY_ATK_MIN || i == PET_ATTR_GROW_MAG_ATK_MIN )
				{
					continue;
				}
			}
			int32_t attrPoint = calGrowAttrPoints( GetBaseAttr( static_cast<PET_ATTR>( i ) ), pCfgPet->m_vMaxAttr[i], pCfgPet->m_vMaxPoints[i] );
			m_nGrowPoints += attrPoint;
		}
	}
	sum += m_nGrowPoints;

	// 7)��ʼ���ԣ���ʼ���Ե�����ͨ����ʼ��������ͳ�ƻ�á�
	m_nStartPoints = 0;
// 	{
// 		for ( int8_t i = PET_ATTR_START_HP; i <= PET_ATTR_START_MAG_DEF; ++i )
// 		{
// 			int32_t attrPoint = calStartAttrPoints( GetBaseAttr( static_cast<PET_ATTR>( i ) ), pCfgPet->m_vMaxAttr[i], pCfgPet->m_vMaxPoints[i] );
// 			m_nStartPoints += attrPoint;
// 		}
// 	}
	sum += m_nStartPoints;

	// 8)�츳��ͨ�����츳���ּ��㣬��ʱ�ƶ�Ϊÿ���츳Ϊ50���֡�
	for ( int32_t i = 1; i < PET_SKILL_BAR_SIZE; ++i )
	{
		if ( m_vSkill[i].nLevel > 0 )
		{
			sum += 50 * m_vSkill[i].nLevel;
		}
	}

	// Deduct initial talent skill count
	if ( m_vSkill[1].nId > 0 )
	{
		sum -= 50;
	}

	if ( m_nPoints != sum )
	{
		m_nPoints = sum;

		m_bNeedSyncSelf	= true;
		m_bNeedSyncStatus = true;

		Player* pPlayer = GAME_SERVICE.getPlayer( m_nOwner, 0, false );
		if ( NULL == pPlayer )
		{
			return;
		}
		KAI_FU_HUO_DONG.UpdateHDData( pPlayer, KFHDC_PET_POINT, m_nPoints );
	}
}

int32_t CPet::calStartAttrPoints( int32_t nVal, int32_t nMaxVal, int32_t nMaxPoints )
{
	// ���޳�ʼ�������� = [ ( n �C int(max * 0.17) )/(max �Cint(max * 0.17)) ] ^2 *x
	int32_t nt = static_cast<int32_t>( static_cast<float>( nMaxVal ) * 0.17f );
	if ( nVal <= nt )
	{
		return 0;
	}
	float ft = static_cast<float>( nVal - nt ) / static_cast<float>( nMaxVal - nt );
	return static_cast<int32_t>( ft * ft * nMaxPoints );
}

int32_t CPet::calGrowAttrPoints( int32_t nVal, int32_t nMaxVal, int32_t nMaxPoints )
{
	float fPecent = static_cast<float>( nVal ) / static_cast<float>( nMaxVal );
	if ( fPecent >= 1.0f )
	{
		//x���� = int ( ( x  / max�ɳ���) ^ 1.3 * max�ɳ�������)
		float f1 = static_cast<float>( nVal ) / static_cast<float>( nMaxVal );
		return static_cast<int32_t>( std::pow( f1, 1.3f ) * nMaxPoints );
	}
	else if ( fPecent >= 0.33f )
	{
		//x���� = int ( ( ( x �C max * 0.33) / max�ɳ��� * 0.67 ) ^ 2 * max�ɳ������� )
		float f1 = ( static_cast<float>( nVal ) - static_cast<float>( nMaxVal ) * 0.33f ) / ( static_cast<float>( nMaxVal ) * 0.67f );
		return static_cast<int32_t>( f1 * f1 * nMaxPoints );
	}
	else if ( fPecent >= 0.327f )
	{
		return -1;
	}
	else if ( fPecent >= 0.324f )
	{
		return -2;
	}
	else if ( fPecent >= 0.321f )
	{
		return -3;
	}
	else if ( fPecent >= 0.318f )
	{
		return -4;
	}
	else if ( fPecent >= 0.315f )
	{
		return -5;
	}
	else if ( fPecent >= 0.312f )
	{
		return -6;
	}
	else if ( fPecent >= 0.309f )
	{
		return -7;
	}
	else if ( fPecent >= 0.306f )
	{
		return -8;
	}
	else if ( fPecent >= 0.303f )
	{
		return -9;
	}
	else
	{
		return -10;
	}
}

void CPet::initSkill()
{
	bzero( m_vSkill, sizeof( m_vSkill ) );

	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return;
	}

	// �����츳����
	m_vSkill[0].nId = pCfgPet->m_nSkillId;
	m_vSkill[0].nLevel = 1;
	m_vSkill[1].nId = pCfgPet->m_nSecondSkillId;
	m_vSkill[1].nLevel = 1;
}

bool CPet::CanIllusion( CPet* pPet, int8_t nType )
{
	//// �����Դ����ﲻ��������
	//if ( pPet->GetFromWay() == PFW_BORN )
	//{
	//	return false;
	//}

	// ת����������
	if ( IsReinLimit() )
	{
		return false;
	}

	// 1)����������ͬ�����������
	if ( pPet->GetBaseId() != GetBaseId() && !pPet->IsXOType() )
	{
		return false;
	}

	// 2)���ݻ��޵������޵ĳɳ������֣���ʾ��ͬ�ĵȼ�����
	// 3)���ݻ��޵������޵ĳɳ������֣���ʾ��ͬ�ĸ�������������
	// 4)���ݻ��޵������޵ĳɳ������֣���ʾ��ͬ����������

	switch ( nType )
	{
//	case PHT_START_ATTR:	return checkStartAttrIllusion( pPet );
	case PHT_GROW_ATTR:		return checkGrowAttrIllusion( pPet );
//	case PHT_LUCKY:			return checkLuckyIllusion( pPet );
	default: break;
	}
	return false;
}

// bool CPet::checkStartAttrIllusion( CPet* pPet )
// {
// 	if ( NULL == pPet )
// 	{
// 		return false;
// 	}
// 
// 	for ( int8_t i = PET_ATTR_START_HP; i < PET_ATTR_GROW_HP; ++i )
// 	{
// 		if ( m_vAttr[i] < pPet->m_vAttr[i] )
// 		{
// 			return true;
// 		}
// 	}
// 	return false;
// }

bool CPet::checkGrowAttrIllusion( CPet* pPet )
{
	if ( NULL == pPet )
	{
		return false;
	}

	// ���Բ�ͬ
	if ( m_nGrowPoints >= 10000 )
	{
		if ( m_nPhase != PP_ELECTRIC && m_nPhase != pPet->GetPhase() )
		{
			return false;
		}
	}

	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return false;
	}

	const CfgPetIllusionGrow* pGrow = CFG_DATA.GetPetIllusionTable().GetGrow( m_nGrowPoints );
	if ( NULL == pGrow )
	{
		return false;
	}

	// ���ֲ���
	if ( pPet->GetPoints() < pGrow->nVicePoint )
	{
		return false;
	}

	// ���Եȼ�����
	if ( pPet->GetLevel() < pGrow->nViceLevel )
	{
		return false;
	}

	return true;
}

// bool CPet::checkLuckyIllusion( CPet* pPet )
// {
// 	if ( NULL == pPet )
// 	{
// 		return false;
// 	}
// 
// 	return m_nLucky < pPet->m_nLucky;
// }

bool CPet::Illusion( CPet* pPet, int8_t nType, int8_t nUseItem )
{
	bool bSuccess = false;
	switch ( nType )
	{
//	case PHT_START_ATTR:	bSuccess = startAttrIllusion( pPet, nUseItem );		break;
	case PHT_GROW_ATTR:		bSuccess = growAttrIllusion( pPet, nUseItem );		break;
//	case PHT_LUCKY:			bSuccess = luckyIllusion( pPet, nUseItem );			break;
	default: break;
	}
	if ( bSuccess )
	{
		calPoints();
		onChange();
	}
	return bSuccess;
}

bool CPet::NeedSyncSelf() const
{
	return m_bNeedSyncSelf;
}

void CPet::SetSyncSelf( bool bSync )
{
	m_bNeedSyncSelf = bSync;
}

bool CPet::NeedSyncStatus() const
{
	return m_bNeedSyncStatus;
}

void CPet::SetSyncStatus( bool bSync )
{
	m_bNeedSyncStatus = bSync;
}

void CPet::SendPetInfo( Player* player )
{
	if ( NULL == player )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_PET_INFO );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( 1 );
	AppendBaseInfo( packet );
	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.sendPacketTo( player->getConnId(), player->getGateIndex(), packet );
}

// bool CPet::startAttrIllusion( CPet* pPet, int8_t nUseItem )
// {
// 	if ( NULL == pPet )
// 	{
// 		return false;
// 	}
// 
// 	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
// 	if ( NULL == pCfgPet )
// 	{
// 		return false;
// 	}
// 
// 	int32_t nKey = calIllusionKey( nUseItem );
// 	int32_t nRein = calIllusionRein( nUseItem );
// 	if ( nKey == 0 || nRein == 0 )
// 	{
// 		return false;
// 	}
// 
// 	for ( int8_t i = PET_ATTR_START_HP; i < PET_ATTR_GROW_HP; ++i )
// 	{
// 		if ( calStartAttrIllusion( m_vAttr[i], pPet->m_vAttr[i], nKey ) )
// 		{
// 			attrChange( static_cast<PET_ATTR>( i ) );
// 			if ( i <= PET_ATTR_START_MAG_DEF && m_vAttr[i] >= pCfgPet->m_vMaxAttr[i] * 80 / 100)
// 			{
// 				broadcastPetStartAttr( i, m_vAttr[i] );
// 			}
// 		}
// 	}
// 
// 	m_nRein += nRein;
// 	return true;
// }

bool CPet::growAttrIllusionByItem( int8_t nUseItem )
{
	bool bSuccess = Illuseion( nUseItem );
	if ( bSuccess )
	{
		calPoints();
		onChange();
	}
	return bSuccess;
}

bool CPet::Illuseion( int8_t nUseItem )
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return false;
	}
	if ( IsReinLimit() )
	{
		return false;
	}

	int32_t nKey = calIllusionKey( nUseItem );
	int32_t nRein = calIllusionRein( nUseItem );
	if ( nKey == 0 || nRein == 0 )
	{
		return false;
	}

	int32_t nOldPoints = m_nGrowPoints;
	int32_t nNewPoints = 0;
	for ( int8_t i = PET_ATTR_GROW_HP; i < PET_ATTR_COUNT; ++i )
	{
		if ( IsInsidePet( m_nBaseId ) )
		{
			if ( i == PET_ATTR_GROW_MAG_ATK_MIN || i == PET_ATTR_GROW_PHY_ATK_MIN )
			{
				continue;
			}
		}
		if ( calGrowAttrIllusion( m_vAttr[i], pCfgPet->m_vMaxAttr[i], pCfgPet->m_nGrowRatio, GetGrowTimes(), nKey ) )
		{
			attrChange( static_cast<PET_ATTR>( i ) );
		}
		if ( i <= PET_ATTR_GROW_MAG_DEF )
		{
			nNewPoints += calGrowAttrPoints( GetBaseAttr( static_cast<PET_ATTR>( i ) ), pCfgPet->m_vMaxAttr[i], pCfgPet->m_vMaxPoints[i] );
		}
	}
	
	if ( nNewPoints >= 500 && ( nOldPoints / 500 != nNewPoints / 500 || nNewPoints % 500 == 0 ) )
	{
		broadcastPetGrowAttr( nNewPoints );
	}

	m_nRein += nRein;
	m_nGrowTimes += nRein;
	return true;
}

bool CPet::growAttrIllusion( CPet* pPet, int8_t nUseItem )
{
	if ( NULL == pPet )
	{
		return false;
	}
	return Illuseion( nUseItem );
}

// bool CPet::luckyIllusion( CPet* pPet, int8_t nUseItem )
// {
// 	if ( NULL == pPet )
// 	{
// 		return false;
// 	}
// 
// 	int32_t nMainVal = m_nLucky;
// 	int32_t nViceVal = pPet->m_nLucky;
// 
// 	if ( nMainVal > nViceVal )
// 	{
// 		return false;
// 	}
// 
// 	int32_t nRein = calIllusionRein( nUseItem );
// 	if ( nRein == 0 )
// 	{
// 		return false;
// 	}
// 
// 	//����������ֵ A������������ֵ B
// 	//A = ( B �C A ) *0.8 ������A��������ȡ����
// 	//ʹ�û��޾�ʯ��������ֵ�Ĳ�ͬ�в�ͬ�ĸ���ʹ����ֵ���ӡ�
// 	//ʹ�û��޾�ʯ��������ֵ�Ĳ�ͬ�в�ͬ�ĸ���ʹ����ֵ���ӡ�
// 
// 	float fAddVal = static_cast<float>( nViceVal - nMainVal ) * 0.8f;
// 	int32_t nAddVal = static_cast<int32_t>( fAddVal );
// 	if ( fAddVal > nAddVal )
// 	{
// 		nAddVal += 1;
// 	}
// 	m_nLucky += nAddVal;
// 
// 	if ( m_nLucky >= 100 )
// 	{
// 		broadcastPetLucky( m_nLucky );
// 	}
// 
// 	m_nRein += nRein;
// 	return true;
// }

bool CPet::calStartAttrIllusion( int32_t& nMainAttr, int32_t nViceAttr, int32_t nKey )
{
	if ( nMainAttr > nViceAttr )
	{
		return false;
	}

	//����������A ������������B��B�϶���A����ܽ��г�ʼ���Իû���
	//A = (B �C A) * 0.8 ������A��������ȡ����

	float fAddVal = static_cast<float>( nViceAttr - nMainAttr ) * 0.8f * static_cast<float>( nKey ) / 100.0f;
	int32_t nAddVal = static_cast<int32_t>( fAddVal );
	if ( fAddVal > nAddVal )
	{
		nAddVal += 1;
	}
	nMainAttr += nAddVal;
	return true;
}

bool CPet::calGrowAttrIllusion( int32_t& nMainAttr, int32_t nMaxAttr, int32_t nGrowRatio, int32_t nRein, int32_t nKey )
{
	double fAdd = 0;
	if ( nMainAttr < nMaxAttr )
	{
		//�ɳ���(n+1) =( ( max�ɳ��� �C �ɳ���(n) ) / ( 0.0 + ( 1 + �ɳ��ʻû�ת������) * 20.0f ) + 2.0f/( 490 + �ɳ��ʻû�ת������ * 8  )* max�ɳ��� ) * �ɳ�ϵ�� 
		fAdd = ( static_cast<double>( nMaxAttr - nMainAttr ) / ( 0.0f + ( nRein + 1 )* 20.0f ) + 2.0f/( 490.0f + nRein * 8 ) * nMaxAttr ) * ( static_cast<float>( nGrowRatio ) / 1000 );
		nMainAttr += static_cast<int32_t>( fAdd * nKey / 100 );
	}
	else
	{
		//�ɳ���(n+1) = ( 1.7 / (�ɳ��ʻû�ת������ + 770 ) ) *max�ɳ���
		fAdd = 1.7f / ( nRein + 770) * nMaxAttr;
		nMainAttr += static_cast<int32_t>( fAdd * nKey / 100 );
	}
	return true;
}

SkillId_t CPet::RandSkill()
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return 0;
	}

	int8_t nFirstEmptyPos = -1;
	SkillId_t nSkillId = pCfgPet->RandSkill();
	if ( nSkillId <= 0 )
	{
		return 0;
	}
	int8_t nSkillBarSize = getSkillBarSize();
	for ( int8_t i = 1; i < nSkillBarSize; ++i )
	{
		if ( 0 == m_vSkill[i].nId )
		{
			if ( nFirstEmptyPos < 0 )
			{
				nFirstEmptyPos = i;
			}
		}
		else if ( m_vSkill[i].nId == nSkillId )
		{
			return 0;
		}
	}
	
	if ( nFirstEmptyPos > 0 )
	{
		if ( LearnSkill( nSkillId, nFirstEmptyPos ) )
		{
			return nSkillId;
		}
	}
	return 0;
}

void CPet::ReSetBaseAttr( CfgPetGift* pCfgPetGift )
{
	if ( NULL == pCfgPetGift )
	{
		return;
	}
	memcpy( m_vAttr,pCfgPetGift->m_vMaxAttr, sizeof( m_vAttr ) );
	m_nLevel		= pCfgPetGift->nLevel;
	m_nGrowTimes	= pCfgPetGift->nGrowTimes * PET_REIN_RATE;
	m_nRein			= m_nGrowTimes;
	calPoints();
}

void CPet::AddBaseAttr( PET_ATTR attr, int32_t val )
{
	m_vAttr[attr] += val;
	attrChange( attr );
	calPoints();
	onChange();
}

void CPet::initBaseAttr( const CfgPetEgg& petEgg )
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return;
	}

	// �����������
	int32_t nPecent	= CFG_DATA.GetPetAttrInitRateTable().GetLuckyRate();
	m_nLucky = pCfgPet->m_nLucky*nPecent/100;
	for ( int32_t i = 0; i < PET_ATTR_COUNT; ++i )
	{
		if ( petEgg.vAttr[i] > 0 )
		{
			m_vAttr[i] = petEgg.vAttr[i];
		}
		else
		{
			if ( i < PET_ATTR_GROW_HP )
			{
				nPecent	= 100;// CFG_DATA.GetPetAttrInitRateTable().GetStartRate();
			}
			else
			{
				nPecent = CFG_DATA.GetPetAttrInitRateTable().GetGrowRate();
			}
			m_vAttr[i] = pCfgPet->m_vMaxAttr[i]*nPecent/100;
		}
	}

	adjustAttr( m_vAttr[PET_ATTR_START_PHY_ATK_MIN], m_vAttr[PET_ATTR_START_PHY_ATK_MAX] );
	adjustAttr( m_vAttr[PET_ATTR_START_MAG_ATK_MIN], m_vAttr[PET_ATTR_START_MAG_ATK_MAX] );
	adjustAttr( m_vAttr[PET_ATTR_GROW_PHY_ATK_MIN], m_vAttr[PET_ATTR_GROW_PHY_ATK_MAX] );
	adjustAttr( m_vAttr[PET_ATTR_GROW_MAG_ATK_MIN], m_vAttr[PET_ATTR_GROW_MAG_ATK_MAX] );
}

void CPet::initBaseAttr()
{
	const CfgPetData* pCfgPet = CFG_DATA.GetPetTable().GetPet( m_nBaseId );
	if ( NULL == pCfgPet )
	{
		return;
	}

	if ( IsInsidePet( m_nBaseId ) )
	{
		m_nLucky = 50;
		for ( int32_t i = 0; i < PET_ATTR_COUNT; ++i )
		{
			if ( IsInsidePet(m_nBaseId))
			{
				if ( i == PET_ATTR_GROW_MAG_ATK_MIN || i == PET_ATTR_GROW_PHY_ATK_MIN || i == PET_ATTR_START_PHY_ATK_MIN || i == PET_ATTR_START_MAG_ATK_MIN )
				{
					continue;
				}
			}
			if ( i < PET_ATTR_GROW_HP )
			{
				m_vAttr[i] = pCfgPet->m_vMaxAttr[i];//*15/100;
			}
			else
			{
				m_vAttr[i] = pCfgPet->m_vMaxAttr[i]*33/100;
			}
		}
	}
	else
	{
		// �����������
		int32_t nPecent	= CFG_DATA.GetPetAttrInitRateTable().GetLuckyRate();
		m_nLucky = pCfgPet->m_nLucky*nPecent/100;
		for ( int32_t i = 0; i < PET_ATTR_COUNT; ++i )
		{
			if ( i < PET_ATTR_GROW_HP )
			{
				nPecent	= 100;	//CFG_DATA.GetPetAttrInitRateTable().GetStartRate();
			}
			else
			{
				nPecent = CFG_DATA.GetPetAttrInitRateTable().GetGrowRate();
			}
			m_vAttr[i] = pCfgPet->m_vMaxAttr[i]*nPecent/100;
		}
	}

	adjustAttr( m_vAttr[PET_ATTR_START_PHY_ATK_MIN], m_vAttr[PET_ATTR_START_PHY_ATK_MAX] );
	adjustAttr( m_vAttr[PET_ATTR_START_MAG_ATK_MIN], m_vAttr[PET_ATTR_START_MAG_ATK_MAX] );
	adjustAttr( m_vAttr[PET_ATTR_GROW_PHY_ATK_MIN], m_vAttr[PET_ATTR_GROW_PHY_ATK_MAX] );
	adjustAttr( m_vAttr[PET_ATTR_GROW_MAG_ATK_MIN], m_vAttr[PET_ATTR_GROW_MAG_ATK_MAX] );
}

void CPet::adjustAttr( int32_t& nVal, int32_t nMaxVal )
{
	if ( nVal > nMaxVal )
	{
		nVal = nMaxVal;
	}
}

void CPet::onChange()
{
	++m_nFlag;
	PET_MANAGER.UpdatePet( this );
	m_bNeedSyncSelf = true;
}

CharId_t CPet::GetOwnerId() const
{
	return m_nOwner;
}

void CPet::SetOwnerId( CharId_t nCharId )
{
	m_nOwner = nCharId;
}

int32_t CPet::GetRankFlag() const
{
	return m_nRankFlag;
}

void CPet::ResetRankFlag()
{
	m_nRankFlag = 0;
}

bool CPet::CheckAttrChange( PET_ATTR attr ) const
{
	return ( m_nRankFlag & ( 1 << attr ) ) != 0;
}

void CPet::attrChange( PET_ATTR attr )
{
	m_nRankFlag |= ( 1 << attr );
}

void CPet::ResetRecord()
{
	bool bChange = false;
	for ( int32_t i = 0; i < PET_RECORD_SIZE; ++i )
	{
		if ( m_vRecord[i] > 0 )
		{
			bChange = true;
			m_vRecord[i] = 0;
		}
	}
	if ( bChange )
	{
		onChange();
	}
}

int8_t CPet::getSkillBarSize() const
{
	int8_t nSize = 0;
	if ( m_nPoints < 1000 )
	{
		nSize = 1;
	}
	else if ( m_nPoints < 3000 )
	{
		nSize = 2;
	}
	else if ( m_nPoints < 5000 )
	{
		nSize = 3;
	}
	else if ( m_nPoints < 10000 )
	{
		nSize = 4;
	}
	else
	{
		nSize = 5;
	}

	++nSize;	// ����˶�һ�����ͨ����
	return nSize;
}

bool CPet::IsPetBorn() const
{
	return m_bPetBorn;
}

void CPet::SetPetBorn()
{
	m_bPetBorn = true;
	onChange();
}

void CPet::GetPetData( SocialPetData& petData )
{
	petData.nBaseId	= m_nBaseId;
	petData.nPetId		= m_nPetId;
	petData.nPoints	= m_nPoints;
	petData.nRankFlag	= m_nRankFlag;
	petData.nOwner		= m_nOwner;
	snprintf( petData.strName, MAX_NAME_CCH_LENGTH, m_strName );
	memcpy( petData.vAttr, m_vAttr, sizeof( m_vAttr ) );
}

void CPet::SetRankIndex( PET_RANK_TYPE nRankType, int32_t nRankIndex )
{
	switch( nRankType )
	{
	case PRT_POINTS:				m_RankIndex.nPointsIndex = nRankIndex;									break;
// 	case PRT_START_HP:				m_RankIndex.vAttrIndex[PET_ATTR_START_HP]			= nRankIndex;		break;
// 	case PRT_START_PHY_ATK_MIN:		m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_ATK_MIN]	= nRankIndex;		break;
// 	case PRT_START_PHY_ATK_MAX:		m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_ATK_MAX]	= nRankIndex;		break;
// 	case PRT_START_PHY_DEF:			m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_DEF]		= nRankIndex;		break;
// 	case PRT_START_MAG_ATK_MIN:		m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_ATK_MIN]	= nRankIndex;		break;
// 	case PRT_START_MAG_ATK_MAX:		m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_ATK_MAX]	= nRankIndex;		break;
// 	case PRT_START_MAG_DEF:			m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_DEF]		= nRankIndex;		break;
	case PRT_GROW_HP:				m_RankIndex.vAttrIndex[PET_ATTR_GROW_HP]			= nRankIndex;		break;
	case PRT_GROW_PHY_ATK_MIN:		m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_ATK_MIN]	= nRankIndex;		break;
	case PRT_GROW_PHY_ATK_MAX:		m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_ATK_MAX]	= nRankIndex;		break;
	case PRT_GROW_PHY_DEF:			m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_DEF]		= nRankIndex;		break;
	case PRT_GROW_MAG_ATK_MIN:		m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_ATK_MIN]	= nRankIndex;		break;
	case PRT_GROW_MAG_ATK_MAX:		m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_ATK_MAX]	= nRankIndex;		break;
	case PRT_GROW_MAG_DEF:			m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_DEF]		= nRankIndex;		break;
	default:break;
	}

	m_bNeedSyncSelf	= true;
	m_bNeedSyncStatus = true;
}

int32_t CPet::GetRankIndex( PET_RANK_TYPE nRankType ) const
{
	switch( nRankType )
	{
	case PRT_POINTS:				return m_RankIndex.nPointsIndex;
// 	case PRT_START_HP:				return m_RankIndex.vAttrIndex[PET_ATTR_START_HP];
// 	case PRT_START_PHY_ATK_MIN:		return m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_ATK_MIN];
// 	case PRT_START_PHY_ATK_MAX:		return m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_ATK_MAX];
// 	case PRT_START_PHY_DEF:			return m_RankIndex.vAttrIndex[PET_ATTR_START_PHY_DEF];
// 	case PRT_START_MAG_ATK_MIN:		return m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_ATK_MIN];
// 	case PRT_START_MAG_ATK_MAX:		return m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_ATK_MAX];
// 	case PRT_START_MAG_DEF:			return m_RankIndex.vAttrIndex[PET_ATTR_START_MAG_DEF];
	case PRT_GROW_HP:				return m_RankIndex.vAttrIndex[PET_ATTR_GROW_HP];
	case PRT_GROW_PHY_ATK_MIN:		return m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_ATK_MIN];
	case PRT_GROW_PHY_ATK_MAX:		return m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_ATK_MAX];
	case PRT_GROW_PHY_DEF:			return m_RankIndex.vAttrIndex[PET_ATTR_GROW_PHY_DEF];
	case PRT_GROW_MAG_ATK_MIN:		return m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_ATK_MIN];
	case PRT_GROW_MAG_ATK_MAX:		return m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_ATK_MAX];
	case PRT_GROW_MAG_DEF:			return m_RankIndex.vAttrIndex[PET_ATTR_GROW_MAG_DEF];
	default:break;
	}
	return 0;
}

bool CPet::UseLuckyItem()
{
	++m_nLucky;
	if ( m_nLucky >= 100 )
	{
		broadcastPetLucky( m_nLucky );
	}
	calPoints();
	onChange();
	return true;
}

void CPet::broadcastPetGrowAttr( int32_t nPoints )
{
	Player* pPlayer = GAME_SERVICE.getPlayer( m_nOwner, 0, false );
	if ( NULL == pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PET_BROADCASE );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( PBCT_GROW_ATTR );
	packet->writeInt64( pPlayer->getCid() );
	packet->writeUTF8( pPlayer->getName() );
	packet->writeInt32( this->GetBaseId() );
	packet->writeUTF8( this->GetName() );
	packet->writeInt64( this->GetPetId() );
	packet->writeInt32( nPoints );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast(packet);
}

void CPet::broadcastPetStartAttr( int8_t nAttr, int32_t nVal )
{
	Player* pPlayer = GAME_SERVICE.getPlayer( m_nOwner, 0, false );
	if ( NULL == pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PET_BROADCASE );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( PBCT_START_ATTR );
	packet->writeInt64( pPlayer->getCid() );
	packet->writeUTF8( pPlayer->getName() );
	packet->writeInt32( this->GetBaseId() );
	packet->writeUTF8( this->GetName() );
	packet->writeInt64( this->GetPetId() );
	packet->writeInt8( nAttr );
	packet->writeInt32( nVal );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast(packet);
}

void CPet::broadcastPetLucky( int16_t nVal )
{
	Player* pPlayer = GAME_SERVICE.getPlayer( m_nOwner, 0, false );
	if ( NULL == pPlayer )
	{
		return;
	}

	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_PET_BROADCASE );
	if (NULL == packet)
	{
		return;
	}

	packet->writeInt8( PBCT_LUCKY );
	packet->writeInt64( pPlayer->getCid() );
	packet->writeUTF8( pPlayer->getName() );
	packet->writeInt32( this->GetBaseId() );
	packet->writeUTF8( this->GetName() );
	packet->writeInt64( this->GetPetId() );
	packet->writeInt16( nVal );

	packet->setSize( packet->getWOffset() );
	GAME_SERVICE.worldBroadcast(packet);
}

int32_t CPet::calIllusionRein( int8_t nUseItem )
{
	switch ( nUseItem )
	{
	case PIIT_NONE:				return 10;
	case PIIT_LUCKY_GRASS:		return 10;
	case PIIT_GOD_GRASS:		return 15;
	default:	break;
	}
	return 10;
}

int32_t CPet::calIllusionKey( int8_t nUseItem )
{
	switch ( nUseItem )
	{
	case PIIT_NONE:				return RANDOM.generate( 66, 100 );
	case PIIT_LUCKY_GRASS:		return 100;
	case PIIT_GOD_GRASS:		return 150;
	default:	break;
	}
	return 0;
}
