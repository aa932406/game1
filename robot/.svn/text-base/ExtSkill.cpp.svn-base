#include "stdafx.h"

#include "ExtSkill.h"
#include "Robot.h"
#include "CfgData.h"
#include "ClientServer.h"

using namespace Answer;

CExtSkill::CExtSkill()
{
	OnCleanUp();
}

CExtSkill::~CExtSkill()
{
}

void CExtSkill::OnCleanUp()
{
	m_skills.clear();
	m_nSkillFlag = 0;
}

void CExtSkill::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( SM_SKILL_LIST );
}

int32_t CExtSkill::DispatchNetDatas( ProcId_t nProcId, NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}

	switch( nProcId )
	{
	case SM_SKILL_LIST:		return onSkillList( inPacket );
	default:
		break;
	}
	return ERR_OK;
}

int32_t	CExtSkill::onSkillList( Answer::NetPacket* inPacket )
{
	m_skills.clear();
	//bool bLearnedSkill = false;
	inPacket->readInt32();	// 不知是什么东西
	int32_t nCount	= inPacket->readInt32();
	for ( int32_t i = 0; i < nCount; ++i )
	{
		Skill skill = {};
		skill.nSkillId		= inPacket->readInt32();
		skill.nSkillLevel	= inPacket->readInt32();
		if ( skill.nSkillId > 0 )
		{
			updateSkill( skill );
			//m_skills.push_back( skill );
			//bLearnedSkill = true;
		}
	}

	//if ( !bLearnedSkill )
	//{
	//	sendLearnSkill();
	//}

	return ERR_OK;
}

void CExtSkill::updateSkill( const Skill& skill )
{
	SkillList::iterator iter = m_skills.begin();
	SkillList::iterator eiter = m_skills.end();
	for ( ; iter != eiter; ++iter )
	{
		if ( iter->nSkillId == skill.nSkillId )
		{
			iter->nSkillLevel = skill.nSkillLevel;
			return;
		}
	}

	m_skills.push_back( skill );
}

int32_t	CExtSkill::GetSkillId( int64_t curTick )
{
	std::vector<Skill*> vSkill;
	SkillList::iterator iter = m_skills.begin();
	SkillList::iterator eiter = m_skills.end();
	for ( ; iter != eiter; ++iter )
	{
		CfgSkill *pCfgSkill = CFG_DATA.getSkill( iter->nSkillId );
		if ( pCfgSkill != NULL && pCfgSkill->type == SK_ACTIVE && pCfgSkill->cd + iter->nLastUseTick < curTick )
		{
			if ( pCfgSkill->kind != SK_XP && pCfgSkill->kind != SK_HORSERACING && pCfgSkill->kind != SK_PUSH )
			{
				vSkill.push_back( &(*iter) );
			}
		}
	}
	if ( vSkill.empty() )
	{
		return 0;
	}

	if ( vSkill.size() == 1 )
	{
		return vSkill[0]->nSkillId;
	}

	int32_t nRand = RANDOM.generate( 0, vSkill.size()-1 );
	return vSkill[nRand]->nSkillId;
}

int32_t CExtSkill::GetSkillFlag()
{
	return ++m_nSkillFlag;
}

void CExtSkill::CheckLearnSkill( int32_t nBookId, int32_t nSlot )
{
	int32_t nSkillId = 0;
	int32_t nSkillLevel = 0;
	bool bFind = false;
	for ( int32_t i = 0; i < 300; ++i )
	{
		nSkillId = i+1;
		CfgSkill *pCfgSkill = CFG_DATA.getSkill( nSkillId );
		if ( pCfgSkill != NULL && pCfgSkill->job == m_pRobot->getJob() )
		{
			Skill* pSkill = GetSkill( nSkillId );
			if ( pSkill != NULL )
			{
				nSkillLevel = pSkill->nSkillLevel;
			}

			if ( nBookId == CFG_DATA.GetSkillLevelUpTable().GetBook( nSkillId, nSkillLevel ) )
			{
				bFind = true;
				break;
			}
		}
	}

	if ( bFind )
	{
		NetPacket* packet = CLIENT_SERVER.popNetpacket();
		if ( NULL == packet )
		{
			return;
		}

		packet->writeInt32( nSkillId );
		packet->writeInt32( nSlot );

		packet->setType( PACK_PROC );
		packet->setProc( CM_UPGRADE_SKILL_LEVEL );
		packet->setSize( packet->getWOffset() );

		m_pRobot->Dispatch( packet );
	}
}


Skill* CExtSkill::GetSkill( int32_t nId )
{
	for ( SkillList::iterator iter = m_skills.begin(); iter != m_skills.end(); ++iter )
	{
		if ( iter->nSkillId == nId )
		{
			return &(*iter);
		}
	}
	return NULL;
}

void CExtSkill::sendLearnSkill()
{
	NetPacket* packet = CLIENT_SERVER.popNetpacket();
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt32( 16 );

	packet->setType( PACK_PROC );
	packet->setProc( CM_DEBUG_CMD );
	packet->setSize( packet->getWOffset() );

	m_pRobot->Dispatch( packet );
}
