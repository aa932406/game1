#include "CharTitle.h"
#include "Player.h"
#include "GameService.h"
#include "ActivityManager.h"
#include "FunctionOpen.h"
#include "OperateLimit.h"
#include "CfgData.h"

using namespace Answer;

CExtCharTitle::CExtCharTitle()
{
	OnCleanUp();
}

CExtCharTitle::~CExtCharTitle()
{

}

void CExtCharTitle::Init( Player* pPlayer )
{
	CExtSystemBase::Init( pPlayer );
	initTitleMap();
}

void CExtCharTitle::OnCleanUp()
{
	m_nDressTitle = 0;
	m_nDressNormalTitle = 0;
	m_nBattleRankTop = 0;
	m_bShowActivityTitle = 0;
	m_LastUpdateTick = 0;
	for ( int32_t i = 0; i < 3; ++i )
	{
		m_vDress[i] = NULL;
		m_vActivityTitle[i] = 0;
	}
	resetTitleMap();
	m_mCharTitle.clear();
}

void CExtCharTitle::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( 860 );
	procList.push_back( 861 );
}

int32_t CExtCharTitle::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}
	if ( !IsFunctionOpen() )
	{
		return ERR_INVALID_DATA;
	}
	if ( nProcId == 860 )
	{
		return onDressTitle( inPacket );
	}
	if ( nProcId == 861 )
	{
		return onUnDressTitle( inPacket );
	}
	return 0;
}

bool CExtCharTitle::IsFunctionOpen() const
{
	return true;
}

int32_t CExtCharTitle::onDressTitle( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}
	int32_t nId = inPacket->readInt32();
	if ( !dressTitle( nId ) )
	{
		return ERR_INVALID_DATA;
	}
	unHideTitle( nId );
	m_pPlayer->recalcAttr();
	m_pPlayer->setSyncStatusFlag();
	return 0;
}

int32_t CExtCharTitle::onUnDressTitle( Answer::NetPacket* inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_INVALID_DATA;
	}
	int32_t nId = inPacket->readInt32();
	if ( !unDressTitle( nId ) )
	{
		return ERR_INVALID_DATA;
	}
	hideTitle( nId );
	m_pPlayer->recalcAttr();
	m_pPlayer->setSyncStatusFlag();
	return 0;
}

bool CExtCharTitle::dressTitle( int32_t nId )
{
	std::map<int, CharTitle>::iterator iter = m_mCharTitle.find( nId );
	if ( iter == m_mCharTitle.end() )
	{
		return false;
	}
	CharTitle* title = &iter->second;
	if ( m_nDressTitle > 2 )
	{
		return false;
	}
	if ( !title->IsSpecialTitle() && m_nDressNormalTitle > 0 )
	{
		return false;
	}
	if ( !title->Dress() )
	{
		return false;
	}
	if ( !title->IsSpecialTitle() )
	{
		m_vDress[m_nDressTitle] = title;
		++m_nDressNormalTitle;
	}
	else
	{
		int32_t i = 0;
		for ( ; i < m_nDressTitle; ++i )
		{
			CharTitle* pTitle = m_vDress[i];
			if ( NULL == pTitle )
				break;
			if ( title->GetPriority() < pTitle->GetPriority() || !pTitle->IsSpecialTitle() )
			{
				for ( int32_t j = m_nDressTitle; j > i; --j )
				{
					m_vDress[j] = m_vDress[j - 1];
				}
				break;
			}
		}
		m_vDress[i] = title;
	}
	++m_nDressTitle;
	return true;
}

bool CExtCharTitle::unDressTitle( int32_t nId )
{
	std::map<int, CharTitle>::iterator iter = m_mCharTitle.find( nId );
	if ( iter == m_mCharTitle.end() )
	{
		return false;
	}
	CharTitle* title = &iter->second;
	if ( !title->UnDress() )
	{
		return false;
	}
	for ( int32_t i = 0; i < m_nDressTitle; ++i )
	{
		CharTitle* pTitle = m_vDress[i];
		if ( pTitle != NULL && pTitle->GetId() == nId )
		{
			for ( int32_t j = i; j < m_nDressTitle - 1; ++j )
			{
				m_vDress[j] = m_vDress[j + 1];
			}
			m_vDress[m_nDressTitle - 1] = NULL;
			break;
		}
	}
	--m_nDressTitle;
	if ( !title->IsSpecialTitle() )
	{
		--m_nDressNormalTitle;
	}
	return true;
}

void CExtCharTitle::SendTitleInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket* packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_TITLE_INFO );
	if ( NULL == packet )
	{
		return;
	}
	int32_t nCount = 0;
	uint32_t oldOffset = packet->getWOffset();
	packet->writeInt32( 0 ); // placeholder for count

	for ( std::map<int, CharTitle>::iterator iter = m_mCharTitle.begin(); iter != m_mCharTitle.end(); ++iter )
	{
		CharTitle& title = iter->second;
		if ( title.IsGet() && ( title.GetType() != 7 || title.GetCardTitleParams() > 0 ) )
		{
			packet->writeInt32( title.GetId() );
			packet->writeInt8( (int8_t)title.GetState() );
			if ( title.GetType() == 7 )
			{
				int32_t nRecord = m_pPlayer->getRecord( title.GetCardTitleParams() );
				packet->writeInt32( nRecord );
			}
			else if ( title.GetType() == 10 )
			{
				int32_t nRecord = m_pPlayer->getRecord( title.GetCardTitleParams() + 31301 );
				packet->writeInt32( nRecord );
			}
			else
			{
				packet->writeInt32( 1 );
			}
			++nCount;
		}
	}

	uint32_t offset = packet->getWOffset();
	packet->setWOffset( oldOffset );
	packet->writeInt32( nCount );
	packet->setWOffset( offset );
	packet->setSize( packet->getWOffset() );

	GAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CExtCharTitle::AppendDressTitle( Answer::NetPacket* packet )
{
	if ( m_bShowActivityTitle )
	{
		for ( int32_t i = 0; i < 3; ++i )
		{
			packet->writeInt32( m_vActivityTitle[i] );
		}
	}
	else
	{
		for ( int32_t i = 0; i < 3; ++i )
		{
			if ( m_vDress[i] != NULL )
			{
				packet->writeInt32( m_vDress[i]->GetId() );
			}
			else
			{
				packet->writeInt32( 0 );
			}
		}
	}
}

void CExtCharTitle::AddCharAttr()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	for ( std::map<int, CharTitle>::iterator iter = m_mCharTitle.begin(); iter != m_mCharTitle.end(); ++iter )
	{
		CharTitle& title = iter->second;
		if ( title.IsGet() )
		{
			addAttr( title.GetAttr() );
			if ( title.IsDress() )
			{
				addAttr( title.DressAttr() );
			}
		}
	}
}

void CExtCharTitle::addAttr( const AttrAddonVector* attrAddons )
{
	if ( NULL == m_pPlayer || NULL == attrAddons )
	{
		return;
	}
	for ( size_t i = 0; i < attrAddons->size(); ++i )
	{
		if ( (*attrAddons)[i].addon > 0 )
		{
			m_pPlayer->AddAttrValue( (CObjAttrs::Index_T)(*attrAddons)[i].index, (*attrAddons)[i].addon );
		}
	}
}

void CExtCharTitle::GetTitleInfo( TitleBattleList* GetTitleList, TitleBattleList* DressTitleList )
{
	for ( std::map<int, CharTitle>::iterator iter = m_mCharTitle.begin(); iter != m_mCharTitle.end(); ++iter )
	{
		CharTitle& title = iter->second;
		if ( title.IsGet() )
		{
			TitleBattle stu;
			stu.TitleId = title.GetId();
			stu.Battle = title.GetTitleBattle();
			GetTitleList->push_back( stu );
			if ( title.IsDress() )
			{
				stu.Battle = title.DressTitleBattle();
				DressTitleList->push_back( stu );
			}
		}
	}
}

void CExtCharTitle::InitTitle()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	// 城战获胜家族成员
	FamilyId_t winFamily = ACTIVITY_MANAGER.GetCityWarWinner();
	if ( winFamily > 0 && m_pPlayer->getFamilyId() == winFamily )
	{
		CheckAddTitle( 1, m_pPlayer->getFamilyPosition() );
	}

	// 无双战获胜
	FamilyId_t peerless = ACTIVITY_MANAGER.GetPeerlessWarWinner();
	if ( peerless > 0 && m_pPlayer->getCid() == peerless )
	{
		CheckAddTitle( 2, 1 );
	}

	// 时限称号 - 记录 1700~1898
	for ( int32_t i = 1700; i <= 1898; ++i )
	{
		int32_t nRecord = m_pPlayer->getRecord( i );
		if ( nRecord == 1 || m_pPlayer->getNow() < nRecord )
		{
			CheckAddTitle( 7, i );
		}
	}

	// 时限称号 - 记录 31301~31399
	for ( int32_t i = 31301; i <= 31399; ++i )
	{
		int32_t nRecord = m_pPlayer->getRecord( i );
		if ( nRecord == 1 || m_pPlayer->getNow() < nRecord )
		{
			CheckAddTitle( 10, i - 31301 );
		}
	}
}

void CExtCharTitle::CheckAddTitle( int8_t type, int32_t param )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	// type 3 需要功能开启
	if ( type == 3 )
	{
		if ( !m_pPlayer->GetPlayerFunctionOpen().IsOpened( 25 ) )
		{
			return;
		}
	}

	bool bChange = false;
	int32_t nAddNormal = 0;
	int32_t nNormalPriority = 0;

	for ( std::map<int, CharTitle>::iterator iter = m_mCharTitle.begin(); iter != m_mCharTitle.end(); ++iter )
	{
		CharTitle& title = iter->second;
		if ( title.GetType() != type )
		{
			continue;
		}
		if ( !title.CheckJob( m_pPlayer->getJob() ) )
		{
			continue;
		}
		if ( !title.CheckSex( m_pPlayer->getSex() ) )
		{
			continue;
		}
		if ( !title.CheckPlatform( "" ) )
		{
			continue;
		}

		if ( title.IsInParams( param ) )
		{
			if ( !title.IsGet() )
			{
				title.Get();
				if ( title.IsSpecialTitle() )
				{
					bChange = true;
					autoDressTitle( iter->first );
				}
				else
				{
					bChange = true;
					if ( nNormalPriority == 0 || title.GetPriority() < nNormalPriority )
					{
						int32_t nLimitId = iter->first + 30000;
						if ( !m_pPlayer->GetOperateLimit().GetLimitCount( nLimitId ) )
						{
							nAddNormal = iter->first;
						}
						nNormalPriority = title.GetPriority();
					}
				}
			}
		}
		else
		{
			// 非时限称号且已获得 -> 失去称号
			if ( title.GetType() != 7 && title.GetType() != 8 && title.IsGet() )
			{
				if ( title.IsDress() )
				{
					unDressTitle( title.GetId() );
				}
				unHideTitle( title.GetId() );
				bChange = true;
				title.Lost();
			}
		}
	}

	if ( nAddNormal > 0 )
	{
		autoDressTitle( nAddNormal );
	}
	if ( bChange )
	{
		m_pPlayer->recalcAttr();
		m_pPlayer->setSyncStatusFlag();
	}
	SendTitleInfo();
}

void CExtCharTitle::RemoveTitle( int32_t type, int32_t param )
{
	bool bChange = false;
	for ( std::map<int, CharTitle>::iterator iter = m_mCharTitle.begin(); iter != m_mCharTitle.end(); ++iter )
	{
		CharTitle& title = iter->second;
		if ( title.GetType() != type )
		{
			continue;
		}
		if ( param <= 0 )
		{
			if ( !title.IsGet() )
				continue;
			if ( title.IsDress() )
			{
				unDressTitle( title.GetId() );
			}
		}
		else
		{
			if ( !title.IsInParams( param ) )
				continue;
			if ( title.IsDress() )
			{
				unDressTitle( title.GetId() );
			}
		}
		bChange = true;
		title.Lost();
	}
	if ( bChange )
	{
		m_pPlayer->recalcAttr();
		m_pPlayer->setSyncStatusFlag();
		SendTitleInfo();
	}
}

void CExtCharTitle::OnUpdate( int64_t curTick )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( curTick - m_LastUpdateTick <= 59999 )
	{
		return;
	}
	m_LastUpdateTick = curTick;

	// 检查时限称号 1700~1898
	for ( int32_t i = 1700; i <= 1898; ++i )
	{
		int32_t nRecord = m_pPlayer->getRecord( i );
		if ( nRecord >= 2 && m_pPlayer->getNow() > nRecord )
		{
			RemoveTitle( 7, i );
			m_pPlayer->updateRecord( i, 0 );
		}
	}

	// 检查时限称号 31301~31399
	for ( int32_t i = 31301; i <= 31399; ++i )
	{
		int32_t nRecord = m_pPlayer->getRecord( i );
		if ( nRecord >= 2 && m_pPlayer->getNow() > nRecord )
		{
			RemoveTitle( 10, i - 31301 );
			m_pPlayer->updateRecord( i, 0 );
		}
	}
}

void CExtCharTitle::autoDressTitle( int32_t nId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	if ( isTitleHide( nId ) )
	{
		return;
	}
	std::map<int, CharTitle>::iterator iter = m_mCharTitle.find( nId );
	if ( iter == m_mCharTitle.end() )
	{
		return;
	}

	CharTitle& title = iter->second;

	// 等级称号(5)检查玩家等级 >= 300 时不穿戴
	if ( title.GetType() == 5 && m_pPlayer->getLevel() >= 300 )
	{
		return;
	}

	if ( title.IsSpecialTitle() )
	{
		// 特殊称号最多穿3个，如果已经3个则替换最低优先级的
		if ( m_nDressTitle > 2 && m_vDress[2] != NULL )
		{
			if ( m_vDress[2]->GetPriority() > title.GetPriority() )
			{
				unDressTitle( m_vDress[2]->GetId() );
				dressTitle( nId );
			}
		}
		else
		{
			dressTitle( nId );
		}
	}
	else
	{
		// 普通称号最多穿1个
		if ( m_nDressTitle > 2 )
			return;
		if ( m_nDressNormalTitle <= 0 )
		{
			dressTitle( nId );
		}
		else if ( m_vDress[m_nDressTitle] != NULL )
		{
			if ( m_vDress[m_nDressTitle]->GetPriority() > title.GetPriority() )
			{
				unDressTitle( m_vDress[m_nDressTitle]->GetId() );
				dressTitle( nId );
			}
		}
	}
}

void CExtCharTitle::initTitleMap()
{
	const CfgTitleTable* pTitleTable = CFG_DATA.GetTitleTable();
	if ( NULL == pTitleTable )
	{
		return;
	}
	const std::map<int, CfgTitle>* cfgTitleMap = pTitleTable->GetTitleMap();
	if ( NULL == cfgTitleMap )
	{
		return;
	}
	for ( std::map<int, CfgTitle>::const_iterator iter = cfgTitleMap->begin(); iter != cfgTitleMap->end(); ++iter )
	{
		CharTitle title( &iter->second );
		m_mCharTitle.insert( std::make_pair( iter->first, title ) );
	}
}

void CExtCharTitle::resetTitleMap()
{
	for ( std::map<int, CharTitle>::iterator iter = m_mCharTitle.begin(); iter != m_mCharTitle.end(); ++iter )
	{
		iter->second.Lost();
	}
}

void CExtCharTitle::HideActivityTitle( bool bCleanActivityTitle )
{
	m_bShowActivityTitle = 0;
	if ( bCleanActivityTitle )
	{
		for ( int32_t i = 0; i < 3; ++i )
		{
			m_vActivityTitle[i] = 0;
		}
	}
}

bool CExtCharTitle::SetActivityTitle( int8_t nPos, int32_t nTitle )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	if ( nPos < 0 || nPos > 2 )
	{
		return false;
	}
	m_vActivityTitle[nPos] = nTitle;
	m_pPlayer->setSyncStatusFlag();
	return true;
}

int32_t CExtCharTitle::GetDressTitleId()
{
	for ( int32_t i = 0; i < 3; ++i )
	{
		if ( m_vDress[i] != NULL )
		{
			return m_vDress[i]->GetId();
		}
	}
	return 0;
}

void CExtCharTitle::OnLevelUp( int32_t nLevel )
{
	if ( nLevel != 300 || NULL == m_pPlayer )
	{
		return;
	}
	// 等级达到300后卸下等级称号
	for ( std::map<int, CharTitle>::iterator iter = m_mCharTitle.begin(); iter != m_mCharTitle.end(); ++iter )
	{
		if ( iter->second.GetType() == 5 && iter->second.IsDress() )
		{
			unDressTitle( iter->first );
		}
	}
	m_pPlayer->setSyncStatusFlag();
	SendTitleInfo();
}

bool CExtCharTitle::isTitleHide( int32_t nId )
{
	if ( NULL == m_pPlayer )
	{
		return false;
	}
	return m_pPlayer->GetOperateLimit().GetLimitCount( nId + 30000 ) == 1;
}

void CExtCharTitle::hideTitle( int32_t nId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	m_pPlayer->GetOperateLimit().UpdateLimitCount( nId + 30000, 1 );
}

void CExtCharTitle::unHideTitle( int32_t nId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	m_pPlayer->GetOperateLimit().UpdateLimitCount( nId + 30000, 0 );
}
