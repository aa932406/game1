#include "Fighting.h"
#include "CharPet.h"
#include "Equip.h"
#include "GameService.h"
#include "FaBao.h"
#include "JueWei.h"
#include "ActivityManager.h"
CFighting::CFighting()
{

}

CFighting::~CFighting()
{

}

void CFighting::OnCleanUp()
{
	m_nBattle = 0;
}

void CFighting::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.chr.data.battle = m_nBattle;
}

void CFighting::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_ASK_BATTLE_INFO );
}

int32_t CFighting::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch ( nProcId )
	{
	case CM_ASK_BATTLE_INFO:			return OnAskFightingInfo( inPacket );
	default:
		return ERR_SYETEM_ERR;
	}
}

int32_t CFighting::GetBattle() const
{
	return m_nBattle;
}

int32_t	CFighting::OnAskFightingInfo( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	SendFightingInfo();
	return ERR_OK;
}

void CFighting::SendFightingInfo()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	//等级战斗力
	int32_t LevelFighting = m_pPlayer->getLevel();
	//幻宠信息
		
	int32_t		LingSouPoints	= m_pPlayer->GetCharInsidePet().GetPoint();
	int32_t		SoulRank		 = m_pPlayer->GetCharInsidePet().GetRank( PRT_POINTS );
	CPetFighting PetInfo[PSP_SIZE];
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_pPlayer->GetCharPet().GetFightPet(i);		
		if ( NULL != pPet )
		{
			PetInfo[i].m_PetId					= pPet->GetPetId();
			PetInfo[i].m_PetBaseId				= pPet->GetBaseId();
			PetInfo[i].m_PetQuality				= pPet->GetPoints();
			PetInfo[i].m_PetRank				= pPet->GetRankIndex( PRT_POINTS );
			PetInfo[i].m_PetFightingLevel	    = pPet->GetBattleTianFuLevel();						
			PetInfo[i].m_PetFighting			= pPet->GetBattleTianFuBattle();						
		}
	}

	//骑士信息
	int32_t KnightCount			= m_pPlayer->GetCharPet().GetKnightCount();
	int32_t DouHunQuality		= m_pPlayer->GetCharPet().GetKnightPoints( PK_DOUHUN );
	int32_t ShengZhanQuality	= m_pPlayer->GetCharPet().GetKnightPoints( PK_SHENGZHAN );
	int32_t GuangHuiQuality		= m_pPlayer->GetCharPet().GetKnightPoints( PK_GUANGHUI );
		//战斗力

	//装备
//	int32_t EquipSuitCount		= m_pPlayer->GetEquip().GetSuitEquipCount();
//	int32_t EquipLowestStar		= m_pPlayer->GetEquip().GetLowestStar();
	int32_t EquipAllCount		= m_pPlayer->GetEquip().GetEquipAllCount();
	int32_t EquipLevelBattle	= m_pPlayer->GetEquip().GetEquipBaseBattle();
	int32_t EquipAllStarBattle  = 0;
	int32_t EquipAllStar		= m_pPlayer->GetEquip().GetEquipAllStar( EquipAllStarBattle );
	int32_t EquipQualityBattle	= 0;
	int32_t GemHoleCount		= 0;
	int32_t BattleGemCount		= 0;
	int32_t GemCount			= 0;
	int32_t GemLevelBattle		= 0;
	m_pPlayer->GetEquip().GetEquipInfo( GemHoleCount, BattleGemCount,  GemCount, EquipQualityBattle, GemLevelBattle );
	int32_t BattleGemAddBattle	= m_pPlayer->GetEquip().GetGemAddEffectTypeRate( GEM_TYPE_BATTLE );
	//法宝
	int32_t FaBaoSumLevel		= 0;
	int32_t FaBaoCount			= m_pPlayer->GetPlayerFaBao().GetFaBaoCount( FaBaoSumLevel );
	//法宝战斗力
	int8_t	BattleFaBaoLevel	= 0;
	int32_t BattleFaBaoAddBattle= 0;
	m_pPlayer->GetPlayerFaBao().GetBattleFaBaoInfo( BattleFaBaoLevel, BattleFaBaoAddBattle );
	//军团
	int32_t	JunTuanPost			= m_pPlayer->GetCharFamily().GetPosition();
	int32_t	JunTuanBattle		= m_pPlayer->GetCharFamily().GetFamilyAddBattle();
	//爵位
	int32_t	TitlePost			= m_pPlayer->GetPlayerJueWei().GetJueWei();
	int32_t	TitleBattle			= m_pPlayer->GetPlayerJueWei().GetBattleValues();
	//魂力
	int32_t	SoulLevel			= m_pPlayer->GetSoulLevel();
	int32_t SoulBattle			= CFG_DATA.GetSoulAttrTable().GetAddBattle( SoulLevel );
	//诸神之战
	int32_t DungeonId			= m_pPlayer->GetOperateLimit().GetLimitCount( PR_LAST_FINISH_UP_TOWER_DUNGEON );
	int32_t ZSZZBattle			= 0;
	int32_t ZSZZStar			= 0;
	CfgDungeon* pCfgDungeon		= CFG_DATA.getDungeon(DungeonId);
	if ( pCfgDungeon != NULL )
	{
		ZSZZStar   = pCfgDungeon->star;
		ZSZZBattle = pCfgDungeon->Battle;
	}
	//坐骑佩戴战斗力
	int32_t QiShiCount			=	m_pPlayer->GetCharPet().GetQiShiCount();
	int32_t QiShiBattle			= 	m_pPlayer->GetCharPet().GetQiShiAddBattle();
	//官位战斗力
	int32_t GuanWeiBattle		= 	m_pPlayer->GetPlayerGuanWei().GetAddBattle();
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_BATTLE_INFO );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( Type_Level );
	packet->writeInt32( LevelFighting );						//人物等级
	packet->writeInt32( LevelFighting );						//人物等级战斗力

	packet->writeInt8( Type_Ling_Sou );
//	packet->writeUTF8( LingSouName	);							//灵兽名字
	packet->writeInt32( LingSouPoints );						//灵兽星级
	packet->writeInt32( LingSouPoints / 100 );					//灵兽战斗力

	packet->writeInt8( Type_Huan_Sou_Star );
	packet->writeInt64( PetInfo[0].m_PetId );					//第一只幻宠id
	packet->writeInt32( PetInfo[0].m_PetQuality );				//第一只幻宠评分
	packet->writeInt32( PetInfo[0].m_PetQuality / 100 );		//第一只幻宠星级战斗力

	packet->writeInt64( PetInfo[1].m_PetId );					//第二只幻宠id
	packet->writeInt32( PetInfo[1].m_PetQuality );				//第二只幻宠评分
	packet->writeInt32( PetInfo[1].m_PetQuality / 100 );		//第二只幻宠星级战斗力

	packet->writeInt64( PetInfo[2].m_PetId );					//第三只幻宠id
	packet->writeInt32( PetInfo[2].m_PetQuality );				//第三只幻宠评分
	packet->writeInt32( PetInfo[2].m_PetQuality / 100 );		//第三只幻宠星级战斗力

	packet->writeInt8( Type_Huan_Sou_Rand );
	packet->writeInt32( PetInfo[0].m_PetRank );					//第一只排行榜排名
	packet->writeInt32( GetPetRankBattle( PetInfo[0].m_PetRank ) );	//第一只幻宠排行战斗力
	packet->writeInt32( PetInfo[1].m_PetRank );					//第二只排行榜排名
	packet->writeInt32( GetPetRankBattle( PetInfo[1].m_PetRank ) );	//第二只幻宠排行战斗力
	packet->writeInt32( PetInfo[2].m_PetRank );					//第三只排行榜排名
	packet->writeInt32( GetPetRankBattle( PetInfo[2].m_PetRank ) );	//第三只幻宠排行战斗力

	packet->writeInt8( Type_Huan_Sou_Talent );
	packet->writeInt32( PetInfo[0].m_PetFightingLevel );		//第一只幻宠战斗力天赋等级
	packet->writeInt32( PetInfo[0].m_PetFighting );				//第一只幻宠战力天赋战斗力
	packet->writeInt32( PetInfo[1].m_PetFightingLevel );		//第二只幻宠战斗力天赋等级
	packet->writeInt32( PetInfo[1].m_PetFighting );				//第二只幻宠战力天赋战斗力
	packet->writeInt32( PetInfo[2].m_PetFightingLevel );		//第三只幻宠战斗力天赋等级
	packet->writeInt32( PetInfo[2].m_PetFighting );				//第三只幻宠战力天赋战斗力
	
	packet->writeInt8( Type_QiShi_Appoint );
	packet->writeInt32( KnightCount );							//以任命骑士个数
	packet->writeInt32( KnightCount );							//以任命骑士战斗力

	packet->writeInt8( Type_QiShi_Special );
	packet->writeInt32( DouHunQuality );						//斗魂骑士评分
	packet->writeInt32( GetPetKnightBattle( PK_DOUHUN ) );		//斗魂骑士战斗力
	packet->writeInt32( ShengZhanQuality );						//圣战骑士评分
	packet->writeInt32( GetPetKnightBattle( PK_SHENGZHAN) );	//圣战骑士战斗力
	packet->writeInt32( GuangHuiQuality );						//光辉骑士评分
	packet->writeInt32( GetPetKnightBattle( PK_GUANGHUI ) );	//光辉骑士战斗力

	packet->writeInt8( Type_Equip_Base );
	packet->writeInt32( EquipAllCount );						//合适装备的件数
	packet->writeInt32( EquipLevelBattle );						//合适装备战斗力
	packet->writeInt32( EquipAllStar );							//最低装备星级
	packet->writeInt32( EquipAllStarBattle );					//最低装备星级战斗力

	packet->writeInt8( Type_Equip_Quality );
	packet->writeInt32( EquipQualityBattle );					//装备品质战斗力

	packet->writeInt8( Type_Equip_Gem );
	packet->writeInt32( GemHoleCount );							//装备宝石孔个数
	packet->writeInt32( GemHoleCount );							//装备宝石孔加的战斗力
	packet->writeInt32( BattleGemCount );						//战斗力宝石个数
	packet->writeInt32( BattleGemAddBattle );					//战斗力宝石加的战斗力
	packet->writeInt32( GemCount );								//宝石个数
	packet->writeInt32( GemLevelBattle );						//宝石等级战斗

	packet->writeInt8( Type_Fa_Bao );
	packet->writeInt32( FaBaoCount );							//法宝个数
	packet->writeInt32( FaBaoSumLevel );						//法宝个数战斗力
	packet->writeInt32( BattleFaBaoLevel );						//战斗力法宝的等级
	packet->writeInt32( BattleFaBaoAddBattle );					//战斗力法宝的战斗力

	packet->writeInt8( Type_JunTuan_Post );
	packet->writeInt32( JunTuanPost );							//军团职位	
	packet->writeInt32( JunTuanBattle );						//军团战斗力

	packet->writeInt8( Type_The_Title );
	packet->writeInt32( TitlePost );							//爵位等级
	packet->writeInt32( TitleBattle	);							//爵位战斗

	packet->writeInt8( Type_Soul );								
	packet->writeInt32( SoulLevel );							//魂力等级
	packet->writeInt32( SoulBattle );							//魂力战斗力
	
	packet->writeInt8( Type_Guan_Wei );							
	packet->writeInt32( m_pPlayer->getRecord( RP_CUR_GUAN_WEI) );//当前官位
	packet->writeInt32(GuanWeiBattle);							//官位战斗力

	packet->writeInt8( Type_Guan_Wei_Qi_Shi );										
	packet->writeInt8( QiShiCount );							//骑士个数
	packet->writeInt32( QiShiBattle );							//骑士战斗力

	packet->writeInt8(Type_Zhu_Sheng_Zi_Zhan);					//诸神之战
	packet->writeInt32( ZSZZStar );								//诸神之战层数
	packet->writeInt32( ZSZZBattle );							//诸神之战战斗力

	packet->writeInt8( Type_Ling_Sou_Rand );					//灵兽排行榜
	packet->writeInt32( SoulRank );								//灵兽排名
	packet->writeInt32( GetPetRankBattle( SoulRank ) );			//灵兽排名战斗力

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getGateIndex(), packet);
}

int32_t CFighting::GetPetKnightBattle( PET_KNIGHT knight )
{
	if ( NULL == m_pPlayer )
	{
		return 0;
	}

	const CfgPetKnight* pCfgKnight = CFG_DATA.GetPetKnightTable().GetKnight( knight );
	if ( NULL == pCfgKnight )
	{
		return 0;
	}

	if ( pCfgKnight->nEffectType != PKE_ADD_BATTLE )
	{
		return 0;
	}

	int32_t nPoints = m_pPlayer->GetCharPet().GetKnightPoints( knight );
	return pCfgKnight->GetEffectValue( nPoints );
}

int32_t CFighting::GetPetRankBattle( int32_t PetRank )
{
	if ( PetRank <= 0 )
	{
		return 0;
	}
	if ( PetRank == 1 )
	{
		return 30;
	}
	else if ( PetRank == 2 )
	{
		return 20;
	}
	else if ( PetRank == 3 )
	{
		return 15;
	}
	else if ( PetRank <= 10 )
	{
		return 10;
	}
	else if ( PetRank <= 15 )
	{
		return 5;
	}
	return 0;
}

void CFighting::AddFighting()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	//等级战斗力
	int32_t LevelFighting = m_pPlayer->getLevel();
	//灵兽
	int32_t		LingSouPoints	= m_pPlayer->GetCharInsidePet().GetPoint();
	int32_t		SoulRank		 = m_pPlayer->GetCharInsidePet().GetRank( PRT_POINTS );
	//幻宠信息
	CPetFighting PetInfo[PSP_SIZE];
	for ( int32_t i = 0; i < PSP_SIZE; ++i )
	{
		CObjPet* pPet = m_pPlayer->GetCharPet().GetFightPet(i);		
		if ( NULL != pPet )
		{
			PetInfo[i].m_PetId					= pPet->GetPetId();
			PetInfo[i].m_PetBaseId				= pPet->GetBaseId();
			PetInfo[i].m_PetQuality				= pPet->GetPoints();
			PetInfo[i].m_PetRank				= pPet->GetRankIndex( PRT_POINTS );
			PetInfo[i].m_PetFightingLevel	    = pPet->GetBattleTianFuLevel();						
			PetInfo[i].m_PetFighting			= pPet->GetBattleTianFuBattle();						
		}
	}

	//骑士信息
	int32_t KnightCount			= m_pPlayer->GetCharPet().GetKnightCount();

	//装备
	int32_t EquipAllStarBattle  = 0;
//	int32_t EquipSuitCount		= m_pPlayer->GetEquip().GetSuitEquipCount();
//	int32_t EquipLowestStar		= m_pPlayer->GetEquip().GetLowestStar();
	int32_t EquipAllCount		= m_pPlayer->GetEquip().GetEquipAllCount();
	int32_t EquipLevelBattle	= m_pPlayer->GetEquip().GetEquipBaseBattle();
	int32_t EquipAllStar		= m_pPlayer->GetEquip().GetEquipAllStar( EquipAllStarBattle );
	int32_t EquipQualityBattle	= 0;
	int32_t GemHoleCount		= 0;
	int32_t BattleGemCount		= 0;
	int32_t GemCount			= 0;
	int32_t GemLevelBattle		= 0;
	m_pPlayer->GetEquip().GetEquipInfo( GemHoleCount, BattleGemCount,  GemCount, EquipQualityBattle, GemLevelBattle );
	int32_t BattleGemAddBattle	= m_pPlayer->GetEquip().GetGemAddEffectTypeRate( GEM_TYPE_BATTLE );
	//法宝
	int32_t FaBaoSumLevel		= 0;
	int32_t FaBaoCount			= m_pPlayer->GetPlayerFaBao().GetFaBaoCount( FaBaoSumLevel );
	//法宝战斗力
	int8_t	BattleFaBaoLevel	= 0;
	int32_t BattleFaBaoAddBattle= 0;
	m_pPlayer->GetPlayerFaBao().GetBattleFaBaoInfo( BattleFaBaoLevel, BattleFaBaoAddBattle );
	//军团
	int32_t	JunTuanPost			= m_pPlayer->GetCharFamily().GetPosition();
	int32_t	JunTuanBattle		= m_pPlayer->GetCharFamily().GetFamilyAddBattle();
	//爵位
	int32_t	TitlePost			= m_pPlayer->GetPlayerJueWei().GetJueWei();
	int32_t	TitleBattle			= m_pPlayer->GetPlayerJueWei().GetBattleValues();
	//魂力
	int32_t	SoulLevel			= m_pPlayer->GetSoulLevel();
	int32_t SoulBattle			= CFG_DATA.GetSoulAttrTable().GetAddBattle( SoulLevel );
	//诸神之战
	int32_t DungeonId			= m_pPlayer->GetOperateLimit().GetLimitCount( PR_LAST_FINISH_UP_TOWER_DUNGEON );
	int32_t ZSZZBattle			= 0;
	int32_t ZSZZStar			= 0;
	CfgDungeon* pCfgDungeon		= CFG_DATA.getDungeon(DungeonId);
	if ( pCfgDungeon != NULL )
	{
		ZSZZStar   = pCfgDungeon->star;
		ZSZZBattle = pCfgDungeon->Battle;
	}
	//坐骑佩戴战斗力
	int32_t QiShiBattle			= 	m_pPlayer->GetCharPet().GetQiShiAddBattle();
	//官位战斗力
	int32_t GuanWeiBattle		= 	m_pPlayer->GetPlayerGuanWei().GetAddBattle();
	//军团战获胜军团长附加战斗
	int32_t FamilyLeaderBattle	= 0;
	if ( m_pPlayer->getFamilyId() > 0 && m_pPlayer->getFamilyId() == ACTIVITY_MANAGER.GetFamilyWarWinner() && m_pPlayer->getFamilyPosition() == FP_LEADER )
	{
		FamilyLeaderBattle = FAMILY_LEADER_BATTLE;
	}
	int32_t TotalBattle		= 0;
	TotalBattle += LevelFighting;
	TotalBattle += LingSouPoints / 100;
	TotalBattle += PetInfo[0].m_PetQuality / 100;
	TotalBattle += GetPetRankBattle( PetInfo[0].m_PetRank );
	TotalBattle += PetInfo[0].m_PetFighting;
	TotalBattle += PetInfo[1].m_PetQuality / 100;
	TotalBattle += GetPetRankBattle( PetInfo[1].m_PetRank );
	TotalBattle += PetInfo[1].m_PetFighting;
	TotalBattle += PetInfo[2].m_PetQuality / 100;
	TotalBattle += GetPetRankBattle( PetInfo[2].m_PetRank );
	TotalBattle += PetInfo[2].m_PetFighting;
	TotalBattle += KnightCount;
	TotalBattle += GetPetKnightBattle( PK_DOUHUN );
	TotalBattle += GetPetKnightBattle( PK_SHENGZHAN );
	TotalBattle	+= GetPetKnightBattle( PK_GUANGHUI );
	TotalBattle	+= EquipLevelBattle;
	TotalBattle += EquipAllStarBattle;
	TotalBattle += EquipQualityBattle;
	TotalBattle += GemHoleCount;
	TotalBattle += BattleGemAddBattle;
	TotalBattle += GemLevelBattle;
	TotalBattle += FaBaoSumLevel;
	TotalBattle += BattleFaBaoAddBattle;
	TotalBattle += JunTuanBattle;
	TotalBattle += TitleBattle;
	TotalBattle += ZSZZBattle;
	TotalBattle += QiShiBattle;
	TotalBattle += GuanWeiBattle;
	TotalBattle += SoulBattle;
	TotalBattle += GetPetRankBattle( SoulRank );
	TotalBattle += FamilyLeaderBattle;
	if ( m_nBattle != TotalBattle )
	{
		m_nBattle = TotalBattle;
		m_pPlayer->sendUpdateSocialPlayerInfo( PII_BATTLE, TotalBattle );
	}
	if ( m_nBattle > 0 )
	{
		m_pPlayer->AddAttrValue( CObjAttrs::ATTR_BATTLE , TotalBattle );
	}
}
