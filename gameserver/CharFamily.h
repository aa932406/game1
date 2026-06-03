#ifndef __CHAR_FAMILY_H__
#define __CHAR_FAMILY_H__

#include "ExtSystemBase.h"

class Player;
class CExtCharFamily : public CExtSystemBase
{
public:
	CExtCharFamily();
	virtual ~CExtCharFamily();

public:
	virtual void		OnCleanUp();
	virtual void		OnLoadFromDB( const PlayerDBData& dbData );
	virtual void		OnSaveToDB( PlayerDBData& dbData );
	virtual void		OnDaySwitch( int32_t nDiffDays );
	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

private:
	int32_t				onContribution( Answer::NetPacket* inPacket );
	int32_t				onRegistPet( Answer::NetPacket* inPacket );
	int32_t				onUnRegistPet( Answer::NetPacket* inPacket );

	int32_t				onSocialCreateFamily( Answer::NetPacket* inPacket );
	int32_t				onSocialUpdateFamilyInfo( Answer::NetPacket* inPacket );


	int32_t				onRequestFamilyWarPillarInfo( Answer::NetPacket* inPacket );
	int32_t				onFamilyWarAddPillarMoney( Answer::NetPacket* inPacket );
	int32_t				onSocialFamilyWarPillarAddMoney( Answer::NetPacket* inPacket );

	int32_t				onReceiveFamilyTask( Answer::NetPacket* inPacket );
	int32_t				onGetFamilyTaskReward( Answer::NetPacket* inPacket );

public:
	FamilyId_t			GetFamilyId() const;
	std::string			GetFamilyName() const;
	int32_t				GetFamilyLevel() const;
	int8_t				GetPosition() const;
	int32_t				GetContribution() const;
	int32_t				GetFamilyAddBattle() const;
	int32_t				GetFamilyTotomAddBattle() const;
	bool				TotomIsOpened( int32_t PetBaseId );
	void				OnSynPetContribution();
	void				SendAddFamilyTaskCount();
	void				AddContribution( int32_t GongXian, int32_t JunTuanZiJin );
private:
	bool				isFunctionOpen() const;
	int32_t				getMaxRegistPetNum( int32_t nLevel );
	void				sendSocialAddContribution( int32_t nMoney, int32_t nGold );
	void				sendSocialRegistPet( PetId_t nPetId );
	void				sendSocialUnRegistPet( PetId_t nPetId );
	void				sendSocialUpdatePetContribution();
	void				sendSocialAddTaskContribution( int32_t GongXian, int32_t JunTuanZiJin );
	void				recalPetAddContribute();
	int32_t				calPetAddContribute();

private:
	FamilyId_t			m_nFamilyId;
	int8_t				m_nPosition;
	int32_t				m_nContribution;
	int32_t				m_nRegistPetCount;
	int32_t				m_nPetContribution;
	bool				m_IsLogin;

	CObjPet*			m_vRegistPetList[MAX_PET_ID+1];			// 注册宠物
	int8_t				m_vPetRegistTime[MAX_PET_ID+1];			// 宠物注册时间
};

#endif	//__CHAR_FAMILY_H__
