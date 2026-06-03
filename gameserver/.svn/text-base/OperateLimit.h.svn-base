#ifndef __TPOC_OPERATE_LIMIT_H__
#define __TPOC_OPERATE_LIMIT_H__

#include <map>
#include <string>
#include "Shared.h"
#include "ExtSystemBase.h"

class CExtOperateLimit : public CExtSystemBase
{
public:
	CExtOperateLimit();
	virtual ~CExtOperateLimit();

public:
	virtual void	OnCleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );

public:
	int32_t			GetLimitCount( int32_t LimitId ) const;
	void			UpdateLimitCount( int32_t LimitId, int32_t LimitCount );
	void			AddLimitCount( int32_t LimitId, int32_t LimitCount );
	void			Reset( int32_t LimitId );
	void			ResetRange( int32_t MinId, int32_t MaxId, int32_t DiffDay );

	bool			CheckCountIsLimited( int32_t LimitId, int32_t LimitCount ) const;
	bool			CheckIsLimitedForever( int32_t LimitId ) const;

	void			NotifyLimitInfo();

private:
	void			NotifyLimitInfo( const Int32List& rcList );
	bool			isNeedNotify( int32_t nLimitId );

private:
	OperateLimitMap	m_mOperateLimit;	
};


#endif	//__TPOC_OPERATE_LIMIT_H__