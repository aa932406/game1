#ifndef __FA_BAO_H__
#define __FA_BAO_H__
#include "ExtSystemBase.h"

class CFaBao
	:public CExtSystemBase
{
public:
	CFaBao();
	~CFaBao();

	virtual void			OnLoadFromDB( const PlayerDBData& dbData );
	virtual void			OnSaveToDB( PlayerDBData& dbData );
	virtual void			OnCleanUp();
	virtual void			GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t			DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

public:
	bool					AddFaBaoRes( FaBaoResourceType Type, int32_t AddValues );
	bool					DecFaBaoRes( FaBaoResourceType Type, int32_t DecValues );
	int32_t					GetFaBaoRes( FaBaoResourceType Type );
	void					AddPlayerAttr();
	int32_t					GetFaBaoCount( int32_t& FaBaoSumLevel );
	int32_t					GetBattleFaBaoInfo( int8_t& FaBaoLevel, int32_t& FaBaoBattle );	//获取战斗力法宝加的战斗力,和等级
	void					PackFaBaoInfo( Answer::NetPacket *inPacket );
	int32_t					GetFaBaoLevel( int8_t Type );
private:
	int32_t					OnBuyFaBaoRes( Answer::NetPacket* inPacket );
	int32_t					OnAskFaBaoInfo( Answer::NetPacket *inPacket );
	int32_t					OnUpFaBaoLevel( Answer::NetPacket *inPacket );
	int32_t					OnDressFaBao( Answer::NetPacket *inPacket );
	void					SendFaBaoInfo();
	void					GongGao( int32_t FaBaoID );
	bool					CheckFaBaoType( FaBaoType Type );
	bool					CheckFaBaoResType( FaBaoResourceType Type );
private:
	int8_t	m_FaBaoId[FA_BAO_TYPE_COUNT];
	int8_t	m_FaBaoDress[FA_BAO_TYPE_COUNT];			//法宝是否穿戴
	int32_t m_UpFaBaoResource[FA_BAO_RES_COUNT];
};

#endif