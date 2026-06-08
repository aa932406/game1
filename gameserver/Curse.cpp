#include "Curse.h"
#include "CfgData.h"
#include "Player.h"
#include "GameService.h"

#include "KaiFuHuoDong.h"

Curse::Curse()
{
}

Curse::~Curse()
{
}

void Curse::GetInterestsProtocol(ProcIdList& procList)
{
	procList.push_back(268);
}

int32_t Curse::DispatchNetDatas(ProcId_t nProcId, Answer::NetPacket *inPacket)
{
	if (!inPacket)
		return 10002;
	if (nProcId == 268)
		return OnCurseLevelUp(inPacket);
	return 10002;
}

void Curse::AddCharAttr()
{
	if (!m_pPlayer)
		return;

	int32_t CurLevel = m_pPlayer->getRecord(1150);
	DamnationCfg* CurCfg = CFG_DATA->GetDamnationCfg(CurLevel);
	if (CurCfg)
	{
		for (auto it = CurCfg->AttrList.begin(); it != CurCfg->AttrList.end(); ++it)
		{
			m_pPlayer->AddAttrValue((CObjAttrs::Index_T)it->m_nAddAttrType, it->m_nAddAttrValue);
		}
	}
}

int32_t Curse::OnCurseLevelUp(Answer::NetPacket* inPacket)
{
	if (!m_pPlayer || !inPacket)
		return 10002;

	int32_t CurLevel = m_pPlayer->getRecord(1150);
	DamnationCfg* CurCfg = CFG_DATA->GetDamnationCfg(CurLevel);
	DamnationCfg* NextCfg = CFG_DATA->GetDamnationCfg(CurLevel + 1);
	if (!CurCfg || !NextCfg)
		return 10002;

	// Check cost money
	if (CurCfg->CostMoney > 0)
	{
		CExtCurrency* Currency = m_pPlayer->GetCurrency();
		if (Currency->GetMoneyBindAndNoBind() < CurCfg->CostMoney)
			return 10002;
	}

	// Check cost items
	if (!CurCfg->CostItems.empty())
	{
		CExtCharBag* Bag = m_pPlayer->GetBag();
		if (!Bag->RemoveItem(&CurCfg->CostItems, ICR_CURSE_LEVEL_UP))
			return 10002;
	}

	// Deduct money
	if (CurCfg->CostMoney > 0)
	{
		CExtCurrency* Currency = m_pPlayer->GetCurrency();
		if (!Currency->DecMoneyAndNoBind(CurCfg->CostMoney, MCR_CURSE_LEVEL_UP, 0))
			return 10002;
	}

	// Level up
	m_pPlayer->updateRecord(1150, CurLevel + 1);
	m_pPlayer->sendUpdateSocialPlayerInfo(PII_ZU_ZHOU, CurLevel + 1);
	m_pPlayer->RecalcAttr();

	KAI_FU_HUO_DONG->SendKaiFuHuoDongIcon( m_pPlayer );

	if ( NextCfg->GongGaoId > 0 )
	{
		NetPacket* packet = GAME_SERVICE.popNetpacket( m_pPlayer->getConnId(), Answer::PACK_DISPATCH, SM_SEND_NOTICE_PARAM );
		if ( packet != NULL )
		{
			packet->writeInt32( NextCfg->GongGaoId );
			packet->writeUTF8( m_pPlayer->getName() );
			packet->writeInt64( m_pPlayer->getCid() );
			packet->writeInt32( CurLevel + 1 );
			packet->setSize( packet->getWOffset() );
			GAME_SERVICE.worldBroadcast( m_pPlayer->getConnId(), packet );
		}
	}


	return 0;
}

int32_t Curse::DamageValue(int64_t MaxHp)
{
	if (!m_pPlayer)
		return 10002;

	int32_t CurLevel = m_pPlayer->getRecord(1150);
	DamnationCfg* CurCfg = CFG_DATA->GetDamnationCfg(CurLevel);
	if (!CurCfg)
		return 0;

	if (CurCfg->HpPecent > 0 && CurCfg->Probability > 0)
	{
		int32_t nRand = Answer::Singleton<Answer::Random>::instance()->generate(1, 1000);
		if (CurCfg->Probability <= nRand)
			return 0;
		return (int32_t)(MaxHp * CurCfg->HpPecent / 100);
	}
	return 0;
}
