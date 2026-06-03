
#include <algorithm>

#include "stdafx.h"
#include "PetEgg.h"
#include "CfgData.h"
#include "PetManager.h"

using namespace Answer;

PetEgg::PetEgg()
:m_nBag( 0 ), m_nSlot( 0 )
{
	CleanUp();
}

PetEgg::~PetEgg()
{

}

void PetEgg::CleanUp()
{
	m_nBaseId		= 0;
	m_nState		= PES_NORMAL;
	m_nStartTime	= 0;
	m_nPetId		= 0;
}

bool PetEgg::IsEmpty() const
{
	return 0 == m_nBaseId;
}

int8_t PetEgg::GetBag() const
{
	return m_nBag;
}

int32_t PetEgg::GetSlot() const
{
	return m_nSlot;
}

int32_t PetEgg::GetBaseId() const
{
	return m_nBaseId;
}

PetId_t	PetEgg::GetPetId() const
{
	return m_nPetId;
}

int32_t	PetEgg::GetStartTime() const
{
	return m_nStartTime;
}

PET_EGG_STATE PetEgg::GetState() const
{
	return m_nState;
}

void PetEgg::Init( int32_t nBaseId )
{
	m_nBaseId		= nBaseId;
	m_nState		= PES_NORMAL;
	m_nStartTime	= 0;
	m_nPetId		= 0;
}

void PetEgg::Init( const DBPetEgg& egg )
{
	m_nBaseId		= egg.nBaseId;
	m_nState		= static_cast<PET_EGG_STATE>( egg.nState );
	m_nStartTime	= egg.nStartTime;
	m_nPetId		= egg.nPetId;
}

void PetEgg::Set( const PetEgg& egg )
{
	m_nBaseId	= egg.m_nBaseId;
	m_nState	= egg.m_nState;
	m_nStartTime= egg.m_nStartTime;
	m_nPetId	= egg.m_nPetId;
}

void PetEgg::SetBagSlot( int8_t nBag, int32_t nSlot )
{
	m_nBag		= nBag;
	m_nSlot		= nSlot;
}

void PetEgg::StartHatch( int32_t nStartTime )
{
	m_nStartTime	= nStartTime;
	m_nState		= PES_HATCHING;
}

void PetEgg::StopHatch()
{
	m_nStartTime	= 0;
	m_nState		= PES_NORMAL;
}

void PetEgg::EndHatch( PetId_t nPetId )
{
	m_nPetId = nPetId;
	m_nState = PES_CAN_OPEN;
}

void PetEgg::AppendInfo( Answer::NetPacket* packet ) const
{
	if ( NULL == packet )
	{
		return;
	}

	packet->writeInt8( m_nBag );
	packet->writeInt32( m_nSlot );
	packet->writeInt32( m_nBaseId );
	packet->writeInt8( m_nState );
	packet->writeInt32( m_nStartTime );
	packet->writeInt64( m_nPetId );
	int32_t nFlag = 0;
	CPet* pPet = PET_MANAGER.GetPet( m_nPetId );
	if ( pPet != NULL )
	{
		nFlag = pPet->GetFlag();
	}
	packet->writeInt32( nFlag );
}
