#pragma once
//////////////////////////////////////////////////////////////////////////
// 称号系统
// Protocol: 860 (穿戴称号), 861 (卸下称号)
// SM: 0x2E90 (11920) 称号信息
//////////////////////////////////////////////////////////////////////////

#include "ExtSystemBase.h"
#include "DataStructs.h"
#include "CfgData.h"
#include <map>
#include <string>
#include <vector>

// 协议常量
#define SM_SEND_TITLE_INFO		0x2E90		// 11920

// 称号战力信息
struct TitleBattle
{
	int32_t TitleId;
	int32_t Battle;
};
typedef std::list<TitleBattle> TitleBattleList;

// 称号运行时对象
struct CharTitle
{
	const CfgTitle*	cfgTitle;
	int32_t			nState;			// 0=未获得, 1=已获得, 2=已穿戴

	CharTitle() : cfgTitle( NULL ), nState( 0 ) {}
	CharTitle( const CfgTitle* title ) : cfgTitle( title ), nState( 0 ) {}

	// ——— 从 cfgTitle 派生的 inline 方法 ———
	int32_t			GetId() const			{ return cfgTitle ? cfgTitle->nId : 0; }
	int32_t			GetType() const			{ return cfgTitle ? cfgTitle->nType : 0; }
	int32_t			GetPriority() const		{ return cfgTitle ? cfgTitle->nPriority : 0; }
	bool			IsSpecialTitle() const	{ return cfgTitle ? ( cfgTitle->nSpecial != 0 ) : false; }
	int32_t			GetState() const		{ return nState; }
	const AttrAddonVector*	GetAttr() const		{ return cfgTitle ? &cfgTitle->vGetAttr : NULL; }
	const AttrAddonVector*	DressAttr() const	{ return cfgTitle ? &cfgTitle->vDressAttr : NULL; }

	// ——— 状态方法 ———
	bool	IsGet() const	{ return nState == 1 || nState == 2; }
	bool	IsDress() const	{ return nState == 2; }
	bool	Dress()			{ if ( nState != 1 ) return false; nState = 2; return true; }
	bool	UnDress()		{ if ( nState != 2 ) return false; nState = 1; return true; }
	void	Get()			{ if ( !nState ) nState = 1; }
	void	Lost()			{ nState = 0; }

	// ——— 条件检查 ———
	bool	CheckJob( Job_t nJob ) const
	{
		return !cfgTitle->nJob || cfgTitle->nJob == nJob;
	}

	bool	CheckSex( Sex_t nSex ) const
	{
		return !cfgTitle->nSex || cfgTitle->nSex == nSex;
	}

	bool	CheckPlatform( const std::string& platform ) const
	{
		return cfgTitle->sPlatform == "-1" || cfgTitle->sPlatform == platform;
	}

	bool	IsInParams( int32_t nParam ) const
	{
		for ( size_t i = 0; i < cfgTitle->vParams.size(); ++i )
		{
			if ( cfgTitle->vParams[i] == nParam )
				return true;
		}
		return false;
	}

	int32_t	GetCardTitleParams() const
	{
		if ( !cfgTitle->vParams.empty() )
			return cfgTitle->vParams[0];
		return 0;
	}

	// ——— 战力计算 ———
	static int32_t CalcBattle( const AttrAddonVector* attrs )
	{
		if ( NULL == attrs ) return 0;
		int32_t nBattle = 0;
		for ( size_t i = 0; i < attrs->size(); ++i )
		{
			nBattle += (*attrs)[i].addon;
		}
		return nBattle;
	}

	int32_t	GetTitleBattle() const		{ return CalcBattle( GetAttr() ); }
	int32_t	DressTitleBattle() const	{ return CalcBattle( DressAttr() ); }
};

// 称号扩展系统
class CExtCharTitle : public CExtSystemBase
{
	friend class CExtSystemMgr;
	friend class CExtCharTitle;
public:
	CExtCharTitle();
	virtual ~CExtCharTitle();

	virtual void	Init( Player* pPlayer );
	virtual void	OnCleanUp();
	virtual void	OnUpdate( int64_t curTick );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual	int32_t	DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket );

	bool	IsFunctionOpen() const;

	// 对外接口
	void	InitTitle();
	void	CheckAddTitle( int8_t type, int32_t param );
	void	RemoveTitle( int32_t type, int32_t param );
	void	OnLevelUp( int32_t nLevel );
	void	SendTitleInfo();
	void	AppendDressTitle( Answer::NetPacket* packet );
	void	AddCharAttr();
	void	GetTitleInfo( TitleBattleList* GetTitleList, TitleBattleList* DressTitleList );
	void	HideActivityTitle( bool bCleanActivityTitle );
	bool	SetActivityTitle( int8_t nPos, int32_t nTitle );
	int32_t	GetDressTitleId();

protected:
	// 协议处理
	int32_t		onDressTitle( Answer::NetPacket* inPacket );		// 860
	int32_t		onUnDressTitle( Answer::NetPacket* inPacket );		// 861

	// 内部方法
	bool		dressTitle( int32_t nId );
	bool		unDressTitle( int32_t nId );
	void		autoDressTitle( int32_t nId );
	void		initTitleMap();
	void		resetTitleMap();
	void		addAttr( const AttrAddonVector* attrAddons );
	bool		isTitleHide( int32_t nId );
	void		hideTitle( int32_t nId );
	void		unHideTitle( int32_t nId );

protected:
	std::map<int, CharTitle>	m_mCharTitle;			// 所有称号
	CharTitle*					m_vDress[3];			// 已穿戴称号（最多3个）
	int32_t						m_nDressTitle;			// 已穿戴数量
	int32_t						m_nDressNormalTitle;	// 已穿戴普通称号数量
	int32_t						m_nBattleRankTop;		// 排行榜最高战力
	int8_t						m_bShowActivityTitle;	// 是否显示活动称号
	int32_t						m_vActivityTitle[3];	// 活动称号ID列表
	int64_t						m_LastUpdateTick;		// 上次更新tick
};
