#ifndef __CHOU_JIANG_H__
#define __CHOU_JIANG_H__

#include "ExtSystemBase.h"
#include "CfgData.h"

class ChouJiang:
	public CExtSystemBase
{
public:
	ChouJiang();
	~ChouJiang();
	void			CleanUp();
	virtual void	OnLoadFromDB( const PlayerDBData& dbData );
	virtual void	OnSaveToDB( PlayerDBData& dbData );
	virtual void	GetInterestsProtocol( ProcIdList& procList );
	virtual int32_t DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

	void			SendChouJiangItem();
	void			GetChouJiangStu( IconStateList& IconList );
	ShowIcon		GetShowIconStu();
	void			SendHuoDongIcon();
private:
	int32_t			OnAskChouJiang( Answer::NetPacket *inPacket );	//客户端发过来的请求抽奖
	int32_t			OnChouJiang( Answer::NetPacket *inPacket );		//中心服检测后请求抽奖
	int32_t			OnAskChouJiangRecord( Answer::NetPacket *inPacket );
	int32_t			OnGetItem( Answer::NetPacket *inPacket );
	int32_t			OnTidy( Answer::NetPacket *inPacket );


	void			SendChouJiangRecord();			
	void			AddChouJiangRecord( MemChrBag& CJItem, int32_t Time, int8_t IsRecord );
	int32_t			ToGlobalAskChouJiangRecord();
	void			CheckGlobalPoint( int8_t ChouJiangType, int8_t ChouJiangTimes );				//到中心服检测幸运值
	void			CleanLuckyPoint();
	void			ChangeGlobalPoint(  int32_t AddCount, bool IsClean );
	bool			CheckChouJiangItemList( ChouJiangCost* pCJCost,int32_t& BindTimes, int32_t& AllTimes,std::vector<int32_t> &BindBagSlotVt, std::vector<int32_t>& UnBindBagSlotVt );
	int32_t			NoAddLuckPointChoujiang( int8_t ChouJiangType, int8_t ChouJiangTimes  );
	int32_t			AddLuckPointChouJiang( int8_t ChouJiangType, int8_t ChouJiangTimes, int8_t Special );
	void			GongGao(  int8_t ItemClass, int32_t ItemId, int64_t SrcId );
	void			SendGetItem( std::list<int32_t>& ItemList );
	void			SendChouJiangItemChang( std::list<int32_t>& ItemList );
	void			SendNewRecord( MemChrBag& CJItem, int32_t Time );
	bool			AddItem( CJCfgList& CJCfgItem, int8_t IsBind = IBS_UNBIND );
	void			GetItem( int32_t Slot );
	int32_t			GetFreeCount();
private:
	CJRecordList  m_RecordList;						//抽奖记录
	MemChrBag	  m_ItemList[MAX_ITEM_LIST];		//抽奖物品列表
	int32_t		  m_LuckyPoint;						//个人幸运值
};
#endif