#!/usr/bin/env python3
"""
Generate CGoblin.h and CGoblin.cpp from decompiled code.
CGoblin is a new module - no existing source files exist.
Has 43 functions across 6 sub-systems.
"""

import os

# ============================================================
# 1. Generate GoblinInfo data structures in DataStructs.h
# ============================================================
# First check if GoblinInfo struct already exists
ds_path = "gameserver/DataStructs.h"
with open(ds_path, 'r') as f:
    ds = f.read()

if 'struct GoblinInfo' not in ds:
    # Add GoblinInfo struct before last #endif
    goblin_struct = """
// Goblin system data structures
struct GoblinInfo
{
\tint32_t\tGoblinLevel;
\tint32_t\tGoblinRes;

\tGoblinInfo() : GoblinLevel(0), GoblinRes(0) {}
};

struct CGoblinData
{
\tstd::map<int32_t, GoblinInfo>\tm_GoblinInfoMap;
\tstd::map<int32_t, int32_t>\tm_ShouHuRefiningLeveMap;
\tstd::map<int32_t, int32_t>\tm_WingEquipPolishMap;
\tstd::map<int32_t, int32_t>\tm_MoFuZhuNengMap;
\tstd::map<int32_t, int32_t>\tm_WingEquipRefiningMap;
\tstd::map<int32_t, int32_t>\tm_VipEquipPosLevelMap;
};
"""
    ds = ds.replace('#endif // __DATA_STRUCTS_H__', goblin_struct + '\n#endif // __DATA_STRUCTS_H__')
    # Also try common patterns
    ds = ds.replace('#endif', goblin_struct + '\n#endif')
    
    with open(ds_path, 'w') as f:
        f.write(ds)
    print("✅ Added GoblinInfo/CGoblinData to DataStructs.h")
else:
    print("ℹ️ GoblinInfo already exists in DataStructs.h")


# ============================================================
# 2. Generate CGoblin.h
# ============================================================
header = '''#ifndef __C_GOBLIN_H__
#define __C_GOBLIN_H__

#include "ExtSystemBase.h"
#include "DataStructs.h"

class CGoblin : public CExtSystemBase
{
public:
\tCGoblin();
\tvirtual ~CGoblin();

\tvirtual void\t\t\tOnLoadFromDB( const PlayerDBData& dbData );
\tvirtual void\t\t\tOnSaveToDB( PlayerDBData& dbData );
\tvirtual void\t\t\tOnCleanUp();
\tvirtual void\t\t\tGetInterestsProtocol( ProcIdList& procList );
\tvirtual int32_t\t\t\tDispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket );

\tint32_t\t\t\t\tGetAddAttrRate( int32_t nType );
\tbool\t\t\t\tAddGoblinRes( int8_t nType, int32_t Values );
\tvoid\t\t\t\tSendAllGoblinInfo();
\tint32_t\t\t\t\tOnGoblinLevelUp( Answer::NetPacket *inPacket );
\tvoid\t\t\t\tSendGoblinInfo( int32_t nType );
\tvoid\t\t\t\tAddChrAttr();
\tvoid\t\t\t\tAppendInfo( Answer::NetPacket *packet );

\t// ShouHu Refining
\tvoid\t\t\t\tSendAllShouHuRefiningInfo();
\tvoid\t\t\t\tAddShouHuChrAttr();
\tvoid\t\t\t\tAppendShouHuInfo( Answer::NetPacket *packet );
\tint32_t\t\t\t\tGetShouHuSuitId();
\tint32_t\t\t\t\tOnShouHuRefiningLevelUp( Answer::NetPacket *inPacket );
\tvoid\t\t\t\tSendShouHuRefiningInfo( int32_t nType );

\t// Wing Equip Polish
\tvoid\t\t\t\tSendAllWingEquipPolishInfo();
\tvoid\t\t\t\tAddWingEquipPolishChrAttr();
\tvoid\t\t\t\tAppendWingEquipPolishInfo( Answer::NetPacket *packet );
\tint32_t\t\t\t\tGetWingEquipPolishSuitId();
\tint32_t\t\t\t\tOnWingEquipPolishLevelUp( Answer::NetPacket *inPacket );
\tvoid\t\t\t\tSendWingEquipPolishInfo( int32_t nSlot );

\t// MoFu ZhuNeng
\tvoid\t\t\t\tSendAllMoFuZhuNengInfo();
\tint32_t\t\t\t\tGetMoFuChrAttr( int32_t Slot );
\tint32_t\t\t\t\tOnMoFuZhuNeng( Answer::NetPacket *inPacket );
\tvoid\t\t\t\tSendMoFuZhuNengInfo( int32_t nSlot );

\t// Wing Equip Refining
\tvoid\t\t\t\tSendAllWingEquipRefiningInfo();
\tvoid\t\t\t\tAddWingEquipRefiningChrAttr();
\tvoid\t\t\t\tAppendWingEquipRefiningInfo( Answer::NetPacket *packet );
\tint32_t\t\t\t\tGetWingEquipRefiningSuitId();
\tint32_t\t\t\t\tOnWingEquipRefiningLevelUp( Answer::NetPacket *inPacket );
\tvoid\t\t\t\tSendWingEquipRefiningInfo( int32_t nSlot );
\tint32_t\t\t\t\tGetWingEquipRefiningAttr( int32_t nSlot );

\t// Vip Equip Pos Level
\tvoid\t\t\t\tSendAllVipEquipPosLevelInfo();
\tvoid\t\t\t\tAddVipEquipPosLevelCharAttr();
\tvoid\t\t\t\tSendVipEquipPosLevelInfo( int32_t nSlot );
\tint32_t\t\t\t\tGetVipEquipPosLevelSuitId();
\tint32_t\t\t\t\tOnVipEquipPosLevellUp( Answer::NetPacket *inPacket );

private:
\tbool\t\t\t\tIsGoblinType( int32_t nType );
\tbool\t\t\t\tIsLeftType( int32_t nType );
\tint32_t\t\t\t\tGetSuitId( int32_t IsLeft );

\tstd::map<int32_t, GoblinInfo>\tm_GoblinInfoMap;
\tstd::map<int32_t, int32_t>\tm_ShouHuRefiningLeveMap;
\tstd::map<int32_t, int32_t>\tm_WingEquipPolishMap;
\tstd::map<int32_t, int32_t>\tm_MoFuZhuNengMap;
\tstd::map<int32_t, int32_t>\tm_WingEquipRefiningMap;
\tstd::map<int32_t, int32_t>\tm_VipEquipPosLevelMap;
};

#define GOBLIN\t\tAnswer::Singleton<CGoblin>::instance()

#endif
'''

with open('gameserver/Goblin.h', 'w') as f:
    f.write(header)
print("✅ gameserver/Goblin.h generated")


# ============================================================
# 3. Generate CGoblin.cpp
# ============================================================
cpp = '''#include "stdafx.h"
#include "Goblin.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"
#include "EquipManager.h"
#include "DBService.h"

using namespace Answer;

// Helper: check if nType is a valid Goblin type (29-34)
static bool IsGoblinTypeImpl( int32_t nType )
{
\treturn nType >= 29 && nType <= 34;
}

// Helper: determine if type is "left" (29-31) or "right" (32-34)
static bool IsLeftTypeImpl( int32_t nType )
{
\treturn nType >= 29 && nType <= 31;
}

CGoblin::CGoblin()
{
}

CGoblin::~CGoblin()
{
}

void CGoblin::OnLoadFromDB( const PlayerDBData& dbData )
{
\tm_GoblinInfoMap\t\t\t= dbData.m_CGoblinData.m_GoblinInfoMap;
\tm_ShouHuRefiningLeveMap\t= dbData.m_CGoblinData.m_ShouHuRefiningLeveMap;
\tm_WingEquipPolishMap\t= dbData.m_CGoblinData.m_WingEquipPolishMap;
\tm_MoFuZhuNengMap\t\t= dbData.m_CGoblinData.m_MoFuZhuNengMap;
\tm_WingEquipRefiningMap\t= dbData.m_CGoblinData.m_WingEquipRefiningMap;
\tm_VipEquipPosLevelMap\t= dbData.m_CGoblinData.m_VipEquipPosLevelMap;

\t// Apply VIP equip pos level suit talent
\tint32_t SuitId = GetVipEquipPosLevelSuitId();
\tif ( SuitId > 0 )
\t{
\t\tconst VipEQuipPosSuit* pCfg = CFG_DATA.GetVipEQuipPosSuit( SuitId );
\t\tif ( pCfg != NULL && pCfg->nTalentId > 0 && pCfg->TalentLevel > 0 )
\t\t{
\t\t\tm_pPlayer->GetCharSkill().AddOtherSkill( pCfg->nTalentId, pCfg->TalentLevel );
\t\t}
\t}
}

void CGoblin::OnSaveToDB( PlayerDBData& dbData )
{
\tdbData.m_CGoblinData.m_GoblinInfoMap\t\t\t= m_GoblinInfoMap;
\tdbData.m_CGoblinData.m_ShouHuRefiningLeveMap\t= m_ShouHuRefiningLeveMap;
\tdbData.m_CGoblinData.m_WingEquipPolishMap\t\t= m_WingEquipPolishMap;
\tdbData.m_CGoblinData.m_MoFuZhuNengMap\t\t\t= m_MoFuZhuNengMap;
\tdbData.m_CGoblinData.m_WingEquipRefiningMap\t\t= m_WingEquipRefiningMap;
\tdbData.m_CGoblinData.m_VipEquipPosLevelMap\t\t= m_VipEquipPosLevelMap;
}

void CGoblin::OnCleanUp()
{
\tm_GoblinInfoMap.clear();
\tm_ShouHuRefiningLeveMap.clear();
\tm_WingEquipPolishMap.clear();
\tm_MoFuZhuNengMap.clear();
\tm_WingEquipRefiningMap.clear();
\tm_VipEquipPosLevelMap.clear();
}

void CGoblin::GetInterestsProtocol( ProcIdList& procList )
{
\tprocList.push_back( 550 );\t// CM_GOBLIN_LEVEL_UP (0x226)
\tprocList.push_back( 546 );\t// CM_SHOU_HU_REFINING (0x222)
\tprocList.push_back( 547 );\t// CM_WING_EQUIP_POLISH (0x223)
\tprocList.push_back( 548 );\t// CM_MO_FU_ZHU_NENG (0x224)
\tprocList.push_back( 549 );\t// CM_WING_EQUIP_REFINING (0x225)
\tprocList.push_back( 542 );\t// CM_VIP_EQUIP_POS_LEVEL (0x21E)
}

int32_t CGoblin::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
\tif ( NULL == m_pPlayer || NULL == inPacket )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tswitch ( nProcId )
\t{
\tcase 542:\treturn OnVipEquipPosLevellUp( inPacket );
\tcase 546:\treturn OnShouHuRefiningLevelUp( inPacket );
\tcase 547:\treturn OnWingEquipPolishLevelUp( inPacket );
\tcase 548:\treturn OnMoFuZhuNeng( inPacket );
\tcase 549:\treturn OnWingEquipRefiningLevelUp( inPacket );
\tcase 550:\treturn OnGoblinLevelUp( inPacket );
\tdefault:\treturn ERR_SYETEM_ERR;
\t}
}

// ========== Goblin Core ==========

bool CGoblin::IsGoblinType( int32_t nType )
{
\treturn IsGoblinTypeImpl( nType );
}

bool CGoblin::IsLeftType( int32_t nType )
{
\treturn IsLeftTypeImpl( nType );
}

int32_t CGoblin::GetSuitId( int32_t IsLeft )
{
\tint32_t Start = IsLeft ? 29 : 32;
\tint32_t End   = IsLeft ? 31 : 34;
\tint32_t SuitId = 0;
\tfor ( int32_t i = Start; i <= End; ++i )
\t{
\t\tstd::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.find( i );
\t\tif ( it == m_GoblinInfoMap.end() )
\t\t{
\t\t\treturn 0;
\t\t}
\t\tconst GoblinCfg* pCfg = CFG_DATA.GetGoblinCfg( i, it->second.GoblinLevel );
\t\tif ( NULL == pCfg || pCfg->SuitId <= 0 )
\t\t{
\t\t\treturn 0;
\t\t}
\t\tif ( SuitId == 0 || pCfg->SuitId < SuitId )
\t\t{
\t\t\tSuitId = pCfg->SuitId;
\t\t}
\t}
\treturn SuitId;
}

int32_t CGoblin::GetAddAttrRate( int32_t nType )
{
\tif ( !IsGoblinTypeImpl( nType ) )
\t{
\t\treturn 0;
\t}
\tstd::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.find( nType );
\tif ( it != m_GoblinInfoMap.end() )
\t{
\t\tconst GoblinCfg* pCfg = CFG_DATA.GetGoblinCfg( nType, it->second.GoblinLevel );
\t\tif ( pCfg != NULL )
\t\t{
\t\t\treturn pCfg->UpAttr;
\t\t}
\t}
\treturn 0;
}

bool CGoblin::AddGoblinRes( int8_t nType, int32_t Values )
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn false;
\t}
\tif ( !IsGoblinTypeImpl( nType ) || Values <= 0 )
\t{
\t\treturn false;
\t}
\tm_GoblinInfoMap[nType].GoblinRes += Values;
\tSendGoblinInfo( nType );
\treturn true;
}

void CGoblin::SendAllGoblinInfo()
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD1 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.begin(); it != m_GoblinInfoMap.end(); ++it )
\t{
\t\tGoblinInfo& info = it->second;
\t\tif ( info.GoblinLevel > 0 || info.GoblinRes > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( info.GoblinLevel );
\t\t\tpacket->writeInt32( info.GoblinRes );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CGoblin::OnGoblinLevelUp( Answer::NetPacket *inPacket )
{
\tif ( NULL == inPacket || NULL == m_pPlayer )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tint32_t nType = inPacket->readInt8();
\tif ( !IsGoblinTypeImpl( nType ) )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tbool IsLeft = IsLeftTypeImpl( nType );
\tint32_t OldSuitId = GetSuitId( IsLeft );
\tint32_t NewLevel = m_GoblinInfoMap[nType].GoblinLevel + 1;
\tconst GoblinCfg* pCfg = CFG_DATA.GetGoblinCfg( nType, NewLevel );
\tif ( NULL == pCfg || pCfg->ConstCurr < 0 )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tif ( m_GoblinInfoMap[nType].GoblinRes < pCfg->ConstCurr )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tm_GoblinInfoMap[nType].GoblinRes -= pCfg->ConstCurr;
\tm_GoblinInfoMap[nType].GoblinLevel++;
\tSendGoblinInfo( nType );
\tm_pPlayer->RecalcAttr();
\tGAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), nType );

\tint32_t NewSuitId = GetSuitId( IsLeft );
\tif ( NewSuitId != OldSuitId )
\t{
\t\tint32_t GongGaoId = IsLeft ? 477 : 478;
\t\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
\t\tif ( packet != NULL )
\t\t{
\t\t\tpacket->writeInt32( GongGaoId );
\t\t\tpacket->writeInt64( m_pPlayer->getCid() );
\t\t\tpacket->writeUTF8( m_pPlayer->getName() );
\t\t\tpacket->writeInt32( NewSuitId );
\t\t\tpacket->setSize( packet->getWOffset() );
\t\t\tpacket->setProc( SM_SEND_NOTICE_PARAM );
\t\t\tGAME_SERVICE.worldBroadcast( 0, packet );
\t\t}
\t}
\treturn ERR_OK;
}

void CGoblin::SendGoblinInfo( int32_t nType )
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD0 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tstd::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.find( nType );
\tif ( it == m_GoblinInfoMap.end() )
\t{
\t\tpacket->writeInt32( nType );
\t\tpacket->writeInt32( 0 );
\t\tpacket->writeInt32( 0 );
\t}
\telse
\t{
\t\tpacket->writeInt32( nType );
\t\tpacket->writeInt32( it->second.GoblinLevel );
\t\tpacket->writeInt32( it->second.GoblinRes );
\t}
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddChrAttr()
{
\tfor ( std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.begin(); it != m_GoblinInfoMap.end(); ++it )
\t{
\t\tint32_t AttrRate = GetAddAttrRate( it->first );
\t\tif ( AttrRate > 0 )
\t\t{
\t\t\t// Add attribute based on cfg
\t\t\tconst GoblinCfg* pCfg = CFG_DATA.GetGoblinCfg( it->first, it->second.GoblinLevel );
\t\t\tif ( pCfg != NULL && pCfg->m_nAddAttrType > 0 )
\t\t\t{
\t\t\t\tm_pPlayer->AddAttr( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, AttrRate );
\t\t\t}
\t\t}
\t}
}

void CGoblin::AppendInfo( Answer::NetPacket *packet )
{
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,GoblinInfo>::iterator it = m_GoblinInfoMap.begin(); it != m_GoblinInfoMap.end(); ++it )
\t{
\t\tif ( it->second.GoblinLevel > 0 || it->second.GoblinRes > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second.GoblinLevel );
\t\t\tpacket->writeInt32( it->second.GoblinRes );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
}


// ========== ShouHu Refining ==========

void CGoblin::SendAllShouHuRefiningInfo()
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD2 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,int32_t>::iterator it = m_ShouHuRefiningLeveMap.begin(); it != m_ShouHuRefiningLeveMap.end(); ++it )
\t{
\t\tif ( it->second > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddShouHuChrAttr()
{
\tfor ( std::map<int32_t,int32_t>::iterator it = m_ShouHuRefiningLeveMap.begin(); it != m_ShouHuRefiningLeveMap.end(); ++it )
\t{
\t\tconst ShouHuRefiningCfg* pCfg = CFG_DATA.GetShouHuRefiningCfg( it->first, it->second );
\t\tif ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
\t\t{
\t\t\tm_pPlayer->AddAttr( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, pCfg->m_nAddAttrValue );
\t\t}
\t}
}

void CGoblin::AppendShouHuInfo( Answer::NetPacket *packet )
{
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,int32_t>::iterator it = m_ShouHuRefiningLeveMap.begin(); it != m_ShouHuRefiningLeveMap.end(); ++it )
\t{
\t\tif ( it->second > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
}

int32_t CGoblin::GetShouHuSuitId()
{
\t// Find lowest suit level using cfg
\tint32_t SuitId = 0;
\tfor ( std::map<int32_t,int32_t>::iterator it = m_ShouHuRefiningLeveMap.begin(); it != m_ShouHuRefiningLeveMap.end(); ++it )
\t{
\t\tconst ShouHuRefiningCfg* pCfg = CFG_DATA.GetShouHuRefiningCfg( it->first, it->second );
\t\tif ( pCfg != NULL && pCfg->SuitId > 0 )
\t\t{
\t\t\tif ( SuitId == 0 || pCfg->SuitId < SuitId )
\t\t\t{
\t\t\t\tSuitId = pCfg->SuitId;
\t\t\t}
\t\t}
\t}
\treturn SuitId;
}

int32_t CGoblin::OnShouHuRefiningLevelUp( Answer::NetPacket *inPacket )
{
\tif ( NULL == inPacket || NULL == m_pPlayer )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tint32_t nType = inPacket->readInt8();
\tint32_t NewLevel = m_ShouHuRefiningLeveMap[nType] + 1;
\tconst ShouHuRefiningCfg* pCfg = CFG_DATA.GetShouHuRefiningCfg( nType, NewLevel );
\tif ( NULL == pCfg )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\t// Check cost
\tif ( pCfg->NeedGold > 0 )
\t{
\t\tif ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
\t\t{
\t\t\treturn ERR_SYETEM_ERR;
\t\t}
\t\tm_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_SHOU_HU_REFINING, 0 );
\t}
\tm_ShouHuRefiningLeveMap[nType] = NewLevel;
\tm_pPlayer->RecalcAttr();
\tSendShouHuRefiningInfo( nType );
\tGAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
\treturn ERR_OK;
}

void CGoblin::SendShouHuRefiningInfo( int32_t nType )
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD3 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tpacket->writeInt32( nType );
\tpacket->writeInt32( m_ShouHuRefiningLeveMap[nType] );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}


// ========== Wing Equip Polish ==========

void CGoblin::SendAllWingEquipPolishInfo()
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD4 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,int32_t>::iterator it = m_WingEquipPolishMap.begin(); it != m_WingEquipPolishMap.end(); ++it )
\t{
\t\tif ( it->second > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddWingEquipPolishChrAttr()
{
\tfor ( std::map<int32_t,int32_t>::iterator it = m_WingEquipPolishMap.begin(); it != m_WingEquipPolishMap.end(); ++it )
\t{
\t\tconst WingPolishCfg* pCfg = CFG_DATA.GetWingPolishCfg( it->first, it->second );
\t\tif ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
\t\t{
\t\t\tm_pPlayer->AddAttr( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, pCfg->m_nAddAttrValue );
\t\t}
\t}
}

void CGoblin::AppendWingEquipPolishInfo( Answer::NetPacket *packet )
{
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,int32_t>::iterator it = m_WingEquipPolishMap.begin(); it != m_WingEquipPolishMap.end(); ++it )
\t{
\t\tif ( it->second > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
}

int32_t CGoblin::GetWingEquipPolishSuitId()
{
\tint32_t SuitId = 0;
\tfor ( std::map<int32_t,int32_t>::iterator it = m_WingEquipPolishMap.begin(); it != m_WingEquipPolishMap.end(); ++it )
\t{
\t\tconst WingPolishCfg* pCfg = CFG_DATA.GetWingPolishCfg( it->first, it->second );
\t\tif ( pCfg != NULL && pCfg->SuitId > 0 )
\t\t{
\t\t\tif ( SuitId == 0 || pCfg->SuitId < SuitId )
\t\t\t{
\t\t\t\tSuitId = pCfg->SuitId;
\t\t\t}
\t\t}
\t}
\treturn SuitId;
}

int32_t CGoblin::OnWingEquipPolishLevelUp( Answer::NetPacket *inPacket )
{
\tif ( NULL == inPacket || NULL == m_pPlayer )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tint32_t nSlot = inPacket->readInt8();
\tint32_t NewLevel = m_WingEquipPolishMap[nSlot] + 1;
\tconst WingPolishCfg* pCfg = CFG_DATA.GetWingPolishCfg( nSlot, NewLevel );
\tif ( NULL == pCfg )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\t// Check cost
\tif ( pCfg->NeedGold > 0 )
\t{
\t\tif ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
\t\t{
\t\t\treturn ERR_SYETEM_ERR;
\t\t}
\t\tm_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_WING_POLISH, 0 );
\t}
\tm_WingEquipPolishMap[nSlot] = NewLevel;
\tm_pPlayer->RecalcAttr();
\tSendWingEquipPolishInfo( nSlot );
\tGAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
\treturn ERR_OK;
}

void CGoblin::SendWingEquipPolishInfo( int32_t nSlot )
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD5 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tpacket->writeInt32( nSlot );
\tpacket->writeInt32( m_WingEquipPolishMap[nSlot] );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}


// ========== MoFu ZhuNeng ==========

void CGoblin::SendAllMoFuZhuNengInfo()
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD6 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,int32_t>::iterator it = m_MoFuZhuNengMap.begin(); it != m_MoFuZhuNengMap.end(); ++it )
\t{
\t\tif ( it->second > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CGoblin::GetMoFuChrAttr( int32_t Slot )
{
\tstd::map<int32_t,int32_t>::iterator it = m_MoFuZhuNengMap.find( Slot );
\tif ( it == m_MoFuZhuNengMap.end() )
\t{
\t\treturn 0;
\t}
\tconst MoFuZhuNengCfg* pCfg = CFG_DATA.GetMoFuZhuNengCfg( Slot, it->second );
\tif ( pCfg != NULL && pCfg->m_nAddAttrType > 0 )
\t{
\t\treturn pCfg->m_nAddAttrValue;
\t}
\treturn 0;
}

int32_t CGoblin::OnMoFuZhuNeng( Answer::NetPacket *inPacket )
{
\tif ( NULL == inPacket || NULL == m_pPlayer )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tint32_t nSlot = inPacket->readInt8();
\tint32_t NewLevel = m_MoFuZhuNengMap[nSlot] + 1;
\tconst MoFuZhuNengCfg* pCfg = CFG_DATA.GetMoFuZhuNengCfg( nSlot, NewLevel );
\tif ( NULL == pCfg )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\t// Check cost
\tif ( pCfg->NeedGold > 0 )
\t{
\t\tif ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
\t\t{
\t\t\treturn ERR_SYETEM_ERR;
\t\t}
\t\tm_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_MO_FU_ZHU_NENG, 0 );
\t}
\tm_MoFuZhuNengMap[nSlot] = NewLevel;
\tm_pPlayer->RecalcAttr();
\tSendMoFuZhuNengInfo( nSlot );
\tGAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
\treturn ERR_OK;
}

void CGoblin::SendMoFuZhuNengInfo( int32_t nSlot )
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD7 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tpacket->writeInt32( nSlot );
\tpacket->writeInt32( m_MoFuZhuNengMap[nSlot] );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}


// ========== Wing Equip Refining ==========

void CGoblin::SendAllWingEquipRefiningInfo()
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD8 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.begin(); it != m_WingEquipRefiningMap.end(); ++it )
\t{
\t\tif ( it->second > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddWingEquipRefiningChrAttr()
{
\tfor ( std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.begin(); it != m_WingEquipRefiningMap.end(); ++it )
\t{
\t\tconst WingRefiningCfg* pCfg = CFG_DATA.GetWingRefiningCfg( it->first, it->second );
\t\tif ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
\t\t{
\t\t\tm_pPlayer->AddAttr( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, pCfg->m_nAddAttrValue );
\t\t}
\t}
}

void CGoblin::AppendWingEquipRefiningInfo( Answer::NetPacket *packet )
{
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.begin(); it != m_WingEquipRefiningMap.end(); ++it )
\t{
\t\tif ( it->second > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
}

int32_t CGoblin::GetWingEquipRefiningSuitId()
{
\tint32_t SuitId = 0;
\tfor ( std::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.begin(); it != m_WingEquipRefiningMap.end(); ++it )
\t{
\t\tconst WingRefiningCfg* pCfg = CFG_DATA.GetWingRefiningCfg( it->first, it->second );
\t\tif ( pCfg != NULL && pCfg->SuitId > 0 )
\t\t{
\t\t\tif ( SuitId == 0 || pCfg->SuitId < SuitId )
\t\t\t{
\t\t\t\tSuitId = pCfg->SuitId;
\t\t\t}
\t\t}
\t}
\treturn SuitId;
}

int32_t CGoblin::OnWingEquipRefiningLevelUp( Answer::NetPacket *inPacket )
{
\tif ( NULL == inPacket || NULL == m_pPlayer )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tint32_t nSlot = inPacket->readInt8();
\tint32_t NewLevel = m_WingEquipRefiningMap[nSlot] + 1;
\tconst WingRefiningCfg* pCfg = CFG_DATA.GetWingRefiningCfg( nSlot, NewLevel );
\tif ( NULL == pCfg )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\t// Check cost
\tif ( pCfg->NeedGold > 0 )
\t{
\t\tif ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
\t\t{
\t\t\treturn ERR_SYETEM_ERR;
\t\t}
\t\tm_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_WING_REFINING, 0 );
\t}
\tm_WingEquipRefiningMap[nSlot] = NewLevel;
\tm_pPlayer->RecalcAttr();
\tSendWingEquipRefiningInfo( nSlot );
\tGAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
\treturn ERR_OK;
}

void CGoblin::SendWingEquipRefiningInfo( int32_t nSlot )
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CD9 );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tpacket->writeInt32( nSlot );
\tpacket->writeInt32( m_WingEquipRefiningMap[nSlot] );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CGoblin::GetWingEquipRefiningAttr( int32_t nSlot )
{
\tstd::map<int32_t,int32_t>::iterator it = m_WingEquipRefiningMap.find( nSlot );
\tif ( it == m_WingEquipRefiningMap.end() )
\t{
\t\treturn 0;
\t}
\tconst WingRefiningCfg* pCfg = CFG_DATA.GetWingRefiningCfg( nSlot, it->second );
\tif ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
\t{
\t\treturn pCfg->m_nAddAttrValue;
\t}
\treturn 0;
}


// ========== Vip Equip Pos Level ==========

void CGoblin::SendAllVipEquipPosLevelInfo()
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CDA );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tint32_t Count = 0;
\tint32_t Oldoffset = packet->getWOffset();
\tpacket->writeInt32( 0 );
\tfor ( std::map<int32_t,int32_t>::iterator it = m_VipEquipPosLevelMap.begin(); it != m_VipEquipPosLevelMap.end(); ++it )
\t{
\t\tif ( it->second > 0 )
\t\t{
\t\t\tpacket->writeInt32( it->first );
\t\t\tpacket->writeInt32( it->second );
\t\t\t++Count;
\t\t}
\t}
\tint32_t NewWoffset = packet->getWOffset();
\tpacket->setWOffset( Oldoffset );
\tpacket->writeInt32( Count );
\tpacket->setWOffset( NewWoffset );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

void CGoblin::AddVipEquipPosLevelCharAttr()
{
\tint32_t SuitId = GetVipEquipPosLevelSuitId();
\tif ( SuitId > 0 )
\t{
\t\tconst VipEQuipPosSuit* pCfg = CFG_DATA.GetVipEQuipPosSuit( SuitId );
\t\tif ( pCfg != NULL && pCfg->nTalentId > 0 && pCfg->TalentLevel > 0 )
\t\t{
\t\t\tm_pPlayer->GetCharSkill().AddOtherSkill( pCfg->nTalentId, pCfg->TalentLevel );
\t\t}
\t}
\tfor ( std::map<int32_t,int32_t>::iterator it = m_VipEquipPosLevelMap.begin(); it != m_VipEquipPosLevelMap.end(); ++it )
\t{
\t\tconst VipEquipPosLevelCfg* pCfg = CFG_DATA.GetVipEquipPosLevelCfg( it->first, it->second );
\t\tif ( pCfg != NULL && pCfg->m_nAddAttrType > 0 && pCfg->m_nAddAttrValue > 0 )
\t\t{
\t\t\tm_pPlayer->AddAttr( (CObjAttrs::Index_T)pCfg->m_nAddAttrType, pCfg->m_nAddAttrValue );
\t\t}
\t}
}

void CGoblin::SendVipEquipPosLevelInfo( int32_t nSlot )
{
\tif ( NULL == m_pPlayer )
\t{
\t\treturn;
\t}
\tAnswer::NetPacket *packet = GAME_SERVICE.popNetpacket( Answer::PACK_DISPATCH, 0x2CDB );
\tif ( NULL == packet )
\t{
\t\treturn;
\t}
\tpacket->writeInt32( nSlot );
\tpacket->writeInt32( m_VipEquipPosLevelMap[nSlot] );
\tpacket->setSize( packet->getWOffset() );
\tGAME_SERVICE.sendPacketTo( m_pPlayer->getGateIndex(), packet );
}

int32_t CGoblin::GetVipEquipPosLevelSuitId()
{
\tint32_t SuitId = 0;
\tfor ( std::map<int32_t,int32_t>::iterator it = m_VipEquipPosLevelMap.begin(); it != m_VipEquipPosLevelMap.end(); ++it )
\t{
\t\tconst VipEquipPosLevelCfg* pCfg = CFG_DATA.GetVipEquipPosLevelCfg( it->first, it->second );
\t\tif ( pCfg != NULL && pCfg->SuitId > 0 )
\t\t{
\t\t\tif ( SuitId == 0 || pCfg->SuitId < SuitId )
\t\t\t{
\t\t\t\tSuitId = pCfg->SuitId;
\t\t\t}
\t\t}
\t}
\treturn SuitId;
}

int32_t CGoblin::OnVipEquipPosLevellUp( Answer::NetPacket *inPacket )
{
\tif ( NULL == inPacket || NULL == m_pPlayer )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\tint32_t nSlot = inPacket->readInt8();
\tint32_t NewLevel = m_VipEquipPosLevelMap[nSlot] + 1;
\tconst VipEquipPosLevelCfg* pCfg = CFG_DATA.GetVipEquipPosLevelCfg( nSlot, NewLevel );
\tif ( NULL == pCfg )
\t{
\t\treturn ERR_SYETEM_ERR;
\t}
\t// Check cost
\tif ( pCfg->NeedGold > 0 )
\t{
\t\tif ( m_pPlayer->GetCurrency( CURRENCY_GOLD ) < pCfg->NeedGold )
\t\t{
\t\t\treturn ERR_SYETEM_ERR;
\t\t}
\t\tm_pPlayer->DecCurrency( CURRENCY_GOLD, pCfg->NeedGold, GCR_VIP_EQUIP_POS, 0 );
\t}
\tm_VipEquipPosLevelMap[nSlot] = NewLevel;
\tm_pPlayer->RecalcAttr();
\tSendVipEquipPosLevelInfo( nSlot );
\tGAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc(), 0 );
\treturn ERR_OK;
}
'''

with open('gameserver/Goblin.cpp', 'w') as f:
    f.write(cpp)
print("✅ gameserver/Goblin.cpp generated")
print("Ready to compile!")
