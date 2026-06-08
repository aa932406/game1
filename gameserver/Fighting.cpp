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
	//�ȼ�ս����
	int32_t LevelFighting = m_pPlayer->getLevel();
	//�ó���Ϣ
		
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

	//��ʿ��Ϣ
	int32_t KnightCount			= m_pPlayer->GetCharPet().GetKnightCount();
	int32_t DouHunQuality		= m_pPlayer->GetCharPet().GetKnightPoints( PK_DOUHUN );
	int32_t ShengZhanQuality	= m_pPlayer->GetCharPet().GetKnightPoints( PK_SHENGZHAN );
	int32_t GuangHuiQuality		= m_pPlayer->GetCharPet().GetKnightPoints( PK_GUANGHUI );
		//ս����

	//װ��
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
	//����
	int32_t FaBaoSumLevel		= 0;
	int32_t FaBaoCount			= m_pPlayer->GetPlayerFaBao().GetFaBaoCount( FaBaoSumLevel );
	//����ս����
	int8_t	BattleFaBaoLevel	= 0;
	int32_t BattleFaBaoAddBattle= 0;
	m_pPlayer->GetPlayerFaBao().GetBattleFaBaoInfo( BattleFaBaoLevel, BattleFaBaoAddBattle );
	//����
	int32_t	JunTuanPost			= m_pPlayer->GetCharFamily().GetPosition();
	int32_t	JunTuanBattle		= m_pPlayer->GetCharFamily().GetFamilyAddBattle();
	//��λ
	int32_t	TitlePost			= m_pPlayer->GetPlayerJueWei().GetJueWei();
	int32_t	TitleBattle			= m_pPlayer->GetPlayerJueWei().GetBattleValues();
	//����
	int32_t	SoulLevel			= m_pPlayer->GetSoulLevel();
	int32_t SoulBattle			= CFG_DATA.GetSoulAttrTable().GetAddBattle( SoulLevel );
	//����֮ս
	int32_t DungeonId			= m_pPlayer->GetOperateLimit().GetLimitCount( PR_LAST_FINISH_UP_TOWER_DUNGEON );
	int32_t ZSZZBattle			= 0;
	int32_t ZSZZStar			= 0;
	CfgDungeon* pCfgDungeon		= CFG_DATA.getDungeon(DungeonId);
	if ( pCfgDungeon != NULL )
	{
		ZSZZStar   = pCfgDungeon->star;
		ZSZZBattle = pCfgDungeon->Battle;
	}
	//�������ս����
	int32_t QiShiCount			=	m_pPlayer->GetCharPet().GetQiShiCount();
	int32_t QiShiBattle			= 	m_pPlayer->GetCharPet().GetQiShiAddBattle();
	//��λս����
	int32_t GuanWeiBattle		= 	m_pPlayer->GetPlayerGuanWei().GetAddBattle();
	Answer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_BATTLE_INFO );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( Type_Level );
	packet->writeInt32( LevelFighting );						//����ȼ�
	packet->writeInt32( LevelFighting );						//����ȼ�ս����

	packet->writeInt8( Type_Ling_Sou );
//	packet->writeUTF8( LingSouName	);							//��������
	packet->writeInt32( LingSouPoints );						//�����Ǽ�
	packet->writeInt32( LingSouPoints / 100 );					//����ս����

	packet->writeInt8( Type_Huan_Sou_Star );
	packet->writeInt64( PetInfo[0].m_PetId );					//��һֻ�ó�id
	packet->writeInt32( PetInfo[0].m_PetQuality );				//��һֻ�ó�����
	packet->writeInt32( PetInfo[0].m_PetQuality / 100 );		//��һֻ�ó��Ǽ�ս����

	packet->writeInt64( PetInfo[1].m_PetId );					//�ڶ�ֻ�ó�id
	packet->writeInt32( PetInfo[1].m_PetQuality );				//�ڶ�ֻ�ó�����
	packet->writeInt32( PetInfo[1].m_PetQuality / 100 );		//�ڶ�ֻ�ó��Ǽ�ս����

	packet->writeInt64( PetInfo[2].m_PetId );					//����ֻ�ó�id
	packet->writeInt32( PetInfo[2].m_PetQuality );				//����ֻ�ó�����
	packet->writeInt32( PetInfo[2].m_PetQuality / 100 );		//����ֻ�ó��Ǽ�ս����

	packet->writeInt8( Type_Huan_Sou_Rand );
	packet->writeInt32( PetInfo[0].m_PetRank );					//��һֻ���а�����
	packet->writeInt32( GetPetRankBattle( PetInfo[0].m_PetRank ) );	//��һֻ�ó�����ս����
	packet->writeInt32( PetInfo[1].m_PetRank );					//�ڶ�ֻ���а�����
	packet->writeInt32( GetPetRankBattle( PetInfo[1].m_PetRank ) );	//�ڶ�ֻ�ó�����ս����
	packet->writeInt32( PetInfo[2].m_PetRank );					//����ֻ���а�����
	packet->writeInt32( GetPetRankBattle( PetInfo[2].m_PetRank ) );	//����ֻ�ó�����ս����

	packet->writeInt8( Type_Huan_Sou_Talent );
	packet->writeInt32( PetInfo[0].m_PetFightingLevel );		//��һֻ�ó�ս�����츳�ȼ�
	packet->writeInt32( PetInfo[0].m_PetFighting );				//��һֻ�ó�ս���츳ս����
	packet->writeInt32( PetInfo[1].m_PetFightingLevel );		//�ڶ�ֻ�ó�ս�����츳�ȼ�
	packet->writeInt32( PetInfo[1].m_PetFighting );				//�ڶ�ֻ�ó�ս���츳ս����
	packet->writeInt32( PetInfo[2].m_PetFightingLevel );		//����ֻ�ó�ս�����츳�ȼ�
	packet->writeInt32( PetInfo[2].m_PetFighting );				//����ֻ�ó�ս���츳ս����
	
	packet->writeInt8( Type_QiShi_Appoint );
	packet->writeInt32( KnightCount );							//��������ʿ����
	packet->writeInt32( KnightCount );							//��������ʿս����

	packet->writeInt8( Type_QiShi_Special );
	packet->writeInt32( DouHunQuality );						//������ʿ����
	packet->writeInt32( GetPetKnightBattle( PK_DOUHUN ) );		//������ʿս����
	packet->writeInt32( ShengZhanQuality );						//ʥս��ʿ����
	packet->writeInt32( GetPetKnightBattle( PK_SHENGZHAN) );	//ʥս��ʿս����
	packet->writeInt32( GuangHuiQuality );						//�����ʿ����
	packet->writeInt32( GetPetKnightBattle( PK_GUANGHUI ) );	//�����ʿս����

	packet->writeInt8( Type_Equip_Base );
	packet->writeInt32( EquipAllCount );						//����װ���ļ���
	packet->writeInt32( EquipLevelBattle );						//����װ��ս����
	packet->writeInt32( EquipAllStar );							//���װ���Ǽ�
	packet->writeInt32( EquipAllStarBattle );					//���װ���Ǽ�ս����

	packet->writeInt8( Type_Equip_Quality );
	packet->writeInt32( EquipQualityBattle );					//װ��Ʒ��ս����

	packet->writeInt8( Type_Equip_Gem );
	packet->writeInt32( GemHoleCount );							//װ����ʯ�׸���
	packet->writeInt32( GemHoleCount );							//װ����ʯ�׼ӵ�ս����
	packet->writeInt32( BattleGemCount );						//ս������ʯ����
	packet->writeInt32( BattleGemAddBattle );					//ս������ʯ�ӵ�ս����
	packet->writeInt32( GemCount );								//��ʯ����
	packet->writeInt32( GemLevelBattle );						//��ʯ�ȼ�ս��

	packet->writeInt8( Type_Fa_Bao );
	packet->writeInt32( FaBaoCount );							//��������
	packet->writeInt32( FaBaoSumLevel );						//��������ս����
	packet->writeInt32( BattleFaBaoLevel );						//ս���������ĵȼ�
	packet->writeInt32( BattleFaBaoAddBattle );					//ս����������ս����

	packet->writeInt8( Type_JunTuan_Post );
	packet->writeInt32( JunTuanPost );							//����ְλ	
	packet->writeInt32( JunTuanBattle );						//����ս����

	packet->writeInt8( Type_The_Title );
	packet->writeInt32( TitlePost );							//��λ�ȼ�
	packet->writeInt32( TitleBattle	);							//��λս��

	packet->writeInt8( Type_Soul );								
	packet->writeInt32( SoulLevel );							//�����ȼ�
	packet->writeInt32( SoulBattle );							//����ս����
	
	packet->writeInt8( Type_Guan_Wei );							
	packet->writeInt32( m_pPlayer->getRecord( RP_CUR_GUAN_WEI) );//��ǰ��λ
	packet->writeInt32(GuanWeiBattle);							//��λս����

	packet->writeInt8( Type_Guan_Wei_Qi_Shi );										
	packet->writeInt8( QiShiCount );							//��ʿ����
	packet->writeInt32( QiShiBattle );							//��ʿս����

	packet->writeInt8(Type_Zhu_Sheng_Zi_Zhan);					//����֮ս
	packet->writeInt32( ZSZZStar );								//����֮ս����
	packet->writeInt32( ZSZZBattle );							//����֮սս����

	packet->writeInt8( Type_Ling_Sou_Rand );					//�������а�
	packet->writeInt32( SoulRank );								//��������
	packet->writeInt32( GetPetRankBattle( SoulRank ) );			//��������ս����

	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
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
	//�ȼ�ս����
	int32_t LevelFighting = m_pPlayer->getLevel();
	//����
	int32_t		LingSouPoints	= m_pPlayer->GetCharInsidePet().GetPoint();
	int32_t		SoulRank		 = m_pPlayer->GetCharInsidePet().GetRank( PRT_POINTS );
	//�ó���Ϣ
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

	//��ʿ��Ϣ
	int32_t KnightCount			= m_pPlayer->GetCharPet().GetKnightCount();

	//װ��
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
	//����
	int32_t FaBaoSumLevel		= 0;
	int32_t FaBaoCount			= m_pPlayer->GetPlayerFaBao().GetFaBaoCount( FaBaoSumLevel );
	//����ս����
	int8_t	BattleFaBaoLevel	= 0;
	int32_t BattleFaBaoAddBattle= 0;
	m_pPlayer->GetPlayerFaBao().GetBattleFaBaoInfo( BattleFaBaoLevel, BattleFaBaoAddBattle );
	//����
	int32_t	JunTuanPost			= m_pPlayer->GetCharFamily().GetPosition();
	int32_t	JunTuanBattle		= m_pPlayer->GetCharFamily().GetFamilyAddBattle();
	//��λ
	int32_t	TitlePost			= m_pPlayer->GetPlayerJueWei().GetJueWei();
	int32_t	TitleBattle			= m_pPlayer->GetPlayerJueWei().GetBattleValues();
	//����
	int32_t	SoulLevel			= m_pPlayer->GetSoulLevel();
	int32_t SoulBattle			= CFG_DATA.GetSoulAttrTable().GetAddBattle( SoulLevel );
	//����֮ս
	int32_t DungeonId			= m_pPlayer->GetOperateLimit().GetLimitCount( PR_LAST_FINISH_UP_TOWER_DUNGEON );
	int32_t ZSZZBattle			= 0;
	int32_t ZSZZStar			= 0;
	CfgDungeon* pCfgDungeon		= CFG_DATA.getDungeon(DungeonId);
	if ( pCfgDungeon != NULL )
	{
		ZSZZStar   = pCfgDungeon->star;
		ZSZZBattle = pCfgDungeon->Battle;
	}
	//�������ս����
	int32_t QiShiBattle			= 	m_pPlayer->GetCharPet().GetQiShiAddBattle();
	//��λս����
	int32_t GuanWeiBattle		= 	m_pPlayer->GetPlayerGuanWei().GetAddBattle();
	//����ս��ʤ���ų�����ս��
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
