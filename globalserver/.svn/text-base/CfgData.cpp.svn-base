
#include "stdafx.h"
#include "FileDef.h"
#include "CfgData.h"

using namespace Answer;
using namespace std;

CfgData::CfgData()
{
}

CfgData::~CfgData()
{

}

bool CfgData::init()
{
	InitFamilyTable();
	InitFamilyPositionTable();
	InitFamilyTotomActiveCostTable();
	InitFamilyTotomOpen();
	InitTotomOpen();

	InitHallOfFameIndexTable();
	InitHallOfFameRewardTable();
	InitHallOfFameRobotTable();
	return true;
}

void CfgData::InitFamilyTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_TABLE 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	CfgFamily family;
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		family.CleanUp();
		family.nLevel		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.nExp			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.nBattle		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.nMaxMembers	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nTotomCount	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string totoms	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;
		StringVector vTotom = StringUtility::split( totoms, ":" );
		for ( uint32_t j = 0; j < vTotom.size(); ++j )
		{
			m_cfgFamilyTable.AddActiveTotom( atoi( vTotom[j].c_str() ), family.nLevel );
		}
		family.vPosition[FP_VICE]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_HONOR_VICE]		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_ELDER]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_HONOR_ELDER]	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_SENETE]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_HONOR_SENETE]	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_ELIT]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		family.vPosition[FP_SENIOR]			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		
		m_cfgFamilyTable.Add( family );
	}
}

void CfgData::InitFamilyPositionTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_POSITION_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_POSITION_TABLE 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	CfgFamilyPosition position;
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		bzero( &position, sizeof( position ) );
		int8_t	nPosition			= readFile.Search_Posistion( i, 0 )->iValue;
		position.nNeedContribution	= readFile.Search_Posistion( i, 2 )->iValue;
		position.nShareBattleRatio	= readFile.Search_Posistion( i, 4 )->iValue;

		m_cfgFamilyTable.Add( nPosition, position );
	}
}

void CfgData::InitFamilyTotomActiveCostTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_TOTEM_ACTIVE_COST_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_TOTEM_ACTIVE_COST_TABLE 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		int8_t	nBattle		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t nCostMoney	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgFamilyTable.AddTotomActiveCost( nBattle, nCostMoney );
	}
}

void CfgData::InitFamilyTotomOpen()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_FAMILY_TOTEM_OPEN );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_FAMILY_TOTEM_OPEN 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgTotomOpen stu;
		int32_t nIndex = 0;
		stu.BaseId		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.OpenCost	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.StarTotom	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		m_cfgFamilyTable.AddTotomOpenCfg( stu.BaseId, stu );
	}
}

void CfgData::InitTotomOpen()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_OPEN_TOTEM_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_OPEN_TOTEM_TABLE 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}
	m_cfgOpenTotomMap.clear();
	m_FreeList.clear();
	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		CfgOpenTotomCondition stu;
		int32_t nIndex = 0;
		stu.m_Num			= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.m_OpenCost		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		int32_t BasePetId	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		if ( stu.m_OpenCost <= 0 && BasePetId > 0 )
		{
			m_FreeList.push_back( BasePetId );
		}
		m_cfgOpenTotomMap[stu.m_Num] = stu;
	}
}

const int32_t CfgData::GetOpenTotomNeedMoney( int32_t Num ) const
{
	OpenTotomConditionMap::const_iterator it = m_cfgOpenTotomMap.find( Num );
	if ( it != m_cfgOpenTotomMap.end() )
	{
		return it->second.m_OpenCost;
	}
	return 0;
}

std::list<int32_t> CfgData::GetFreeOpenTotom()
{
	return m_FreeList;
}


const CfgFamilyTable& CfgData::GetFamilyTable() const
{
	return m_cfgFamilyTable;
}

void CfgData::InitHallOfFameRewardTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_HALL_OF_FAME_REWARD_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_HALL_OF_FAME_REWARD_TABLE 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		HallOfFameReward reward; 
		int32_t nIndex = 0;
		reward.nIndexMin	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		reward.nIndexMax	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		reward.nHonor		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		std::string items	= readFile.Search_Posistion( i, nIndex )->pString;	++nIndex;

		ItemData honor = {};
		honor.m_nClass	= IC_CURRENCY;
		honor.m_nId		= CURRENCY_HORNOR_ID;
		honor.m_nCount	= reward.nHonor;
		reward.items.push_back( honor );

		if ( items.size() > 3 )
		{
			StringVector vItems = Answer::StringUtility::split( items, "|" );
			for ( uint32_t j = 0; j < vItems.size(); ++j )
			{
				StringVector vParam = Answer::StringUtility::split( vItems[j], ":" );
				if ( vParam.size() == 3 )
				{
					ItemData item = {};
					item.m_nId		= atoi( vParam[0].c_str() );
					item.m_nClass	= atoi( vParam[1].c_str() );
					item.m_nCount	= atoi( vParam[2].c_str() );
					reward.items.push_back( item );
				}
			}
		}

		m_cfgHallOfFameTable.AddReward( reward );
	}
}

void CfgData::InitHallOfFameIndexTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_HALL_OF_FAME_INDEX_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_HALL_OF_FAME_INDEX_TABLE 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		HallOfFameIndex stu; 
		int32_t nIndex = 0;
		stu.nIndexMin	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nIndexMax	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nFrontMin	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nFrontMax	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nBackMin	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		stu.nBackMax	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgHallOfFameTable.AddIndex( stu );
	}
}

void CfgData::InitHallOfFameRobotTable()
{
	CDBCFile readFile(0);
	bool ret = readFile.OpenFromTXT( FILE_HALL_OF_FAME_ROBOT_TABLE );
	if ( ret == false )
	{
		LOG_ERROR("open FILE_HALL_OF_FAME_ROBOT_TABLE 失败,请检查文件名大小写");
		return;
	}

	int32_t iBaseTableCount		=	readFile.GetRecordsNum();
	int32_t iBaseColumnCount	=	readFile.GetFieldsNum();
	if ( iBaseColumnCount <= 0 )
	{
		return;
	}

	for( int32_t i = 0;i < iBaseTableCount; ++i )
	{
		int32_t nIndex = 0;
		int32_t nFameIndex	= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;
		++nIndex;
		int32_t nBattle		= readFile.Search_Posistion( i, nIndex )->iValue;	++nIndex;

		m_cfgHallOfFameTable.AddRobot( nFameIndex, nBattle );
	}
}

const CfgHallOfFameTable& CfgData::GetHallOfFameTable() const
{
	return m_cfgHallOfFameTable;
}
