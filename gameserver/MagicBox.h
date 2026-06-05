#ifndef __TPOC_MAGIC_BOX_H__
#define __TPOC_MAGIC_BOX_H__

#include "ExtSystemBase.h"
#include "DataStructs.h"
#include "CfgData.h"

class CExtMagicBox : public CExtSystemBase
{
public:
	CExtMagicBox() {}
	virtual ~CExtMagicBox() {}

	// CExtSystemBase overrides
	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	OnUpdate( int64_t curTick );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	// Public helpers
	bool			AddPoints( int32_t nValue );
	bool			ActiveScroll( int32_t nId );
	bool			isActive( int32_t nId ) const;
	void			SendMagicBoxInfo();
	void			SendItemCombiPoint();
	int32_t			getMaxPoints() const { return 500; }
	int32_t			getPointsReviveValue() const { return 5; }

private:
	// Request handlers
	int32_t	onRequestInfo( Answer::NetPacket* inPacket );
	int32_t	onItemCombi( Answer::NetPacket* inPacket );
	int32_t	onOrnamentCombi( Answer::NetPacket* inPacket );
	int32_t	onEquipCombi( Answer::NetPacket* inPacket );
	int32_t	onItemDecompose( Answer::NetPacket* inPacket );

	// Helpers
	int32_t	randomIndex( const Int32Vector& vParam );
	void	sendItemCombiResult( int32_t nId, int32_t nSuccessTimes, int32_t nFailTimes );
	void	broadcastItemCombi( int32_t ItemId, int8_t ItemClass );
	std::string saveString( const Int32List& lst );
	void	loadString( Int32List& lst, const std::string& str );

private:
	int32_t			m_nCombiPoints;
	int32_t			m_nLastReviveTime;
	Int32List		m_lActiveScrolls;
	Int32List		m_lSuccessIds;
};

#endif	//__TPOC_MAGIC_BOX_H__
