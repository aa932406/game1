#ifndef __GAMESERVER_SPECIAL_EQUIP_H__
#define __GAMESERVER_SPECIAL_EQUIP_H__

#include "ExtSystemBase.h"

class Player;
struct ShowIcon;
#include "DataStructs.h"

class CSpecialEquip : public CExtSystemBase
{
public:
	CSpecialEquip( Player* pPlayer )
	{
		m_pPlayer = pPlayer;
	}
	virtual ~CSpecialEquip() {}

	virtual void		GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t		DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );
	virtual void		OnLoadFromDB(){}
	virtual void		OnSaveToDB( PlayerDBData& dbData ){}
	virtual void		OnCleanUp(){}
	virtual void		OnUpdate( int64_t curTick ){}

	// SpecialEquip methods
	void	InitSkill();
	bool	IsActivation( int32_t Day );
	int32_t	CanActivationCount();
	int32_t	OnActivation( Answer::NetPacket *inPacket );
	bool	CanActivation( int32_t nIndex );
	void	SendActivationInfo();
	void	GetSpecialEquipIcon( IconStateList& IconList );
	void	SendSpecialEquipIcon();
};

#endif	//__GAMESERVER_SPECIAL_EQUIP_H__
