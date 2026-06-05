//////////////////////////////////////////////////////////////////////////
// 翅膀系统
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_CHAR_WING_H__
#define __TPOC_CHAR_WING_H__

#include "ExtSystemBase.h"

class CExtCharWing : public CExtSystemBase
{
public:
	CExtCharWing(){}
	virtual ~CExtCharWing(){}

	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData* dbData );
	virtual void	OnSaveToDB( PlayerDBData* dbData );

	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	virtual void	AddCharAttr();
	virtual void	OnDaySwitch( int32_t nDiffDays );

	bool			IsFunctionOpen() const;
	int32_t			GetLevel() const { return m_Level; }
	int32_t			GetLuck() const { return m_Luck; }
	int32_t			GetHuanHua() const { return m_HuanHua; }

	bool			LevelUp( int32_t UseWingLevel, int32_t UpLevel, int32_t ItemId, int32_t itemCount );

private:
	int32_t			onRequestInfo( Answer::NetPacket* inPacket );	// 862
	int32_t			onWingUpLevel( Answer::NetPacket* inPacket );	// 863
	int32_t			onWingHuanHua( Answer::NetPacket* inPacket );	// 864

	void			ClearLuck();
	void			SendWingInfo();

private:
	int32_t			m_Level;			// 翅膀等级
	int32_t			m_Luck;				// 幸运值
	int64_t			m_LaseUpdateTick;	// 上次更新tick
	int32_t			m_HuanHua;			// 幻化等级
};

#endif	//__TPOC_CHAR_WING_H__
