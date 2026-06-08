#include "PlayerMail.h"
#include "GameService.h"
#include "EquipManager.h"
using namespace Answer;



CPlayerMail::CPlayerMail()
{
	m_MailInfo.clear();
}

CPlayerMail::~CPlayerMail()
{

}

void CPlayerMail::OnCleanUp()
{
	m_MailInfo.clear();
}

void CPlayerMail::OnLoadFromDB( const PlayerDBData& dbData )
{
	m_MailInfo = dbData.m_MailDBData.m_MailInfo;
}

void CPlayerMail::OnSaveToDB( PlayerDBData& dbData )
{
	dbData.m_MailDBData.m_MailInfo = m_MailInfo;
}

void CPlayerMail::OnUpdate( int64_t curTick )
{

}

void CPlayerMail::OnDaySwitch( int32_t nDiffDays )
{

}

void CPlayerMail::GetInterestsProtocol( ProcIdList& procList )
{
	procList.push_back( CM_READ_MAIL );
	procList.push_back( CM_ASK_MAIL_LIST );
	procList.push_back( CM_GET_FU_JIAN );
	procList.push_back( CM_DEL_MAIL );
	procList.push_back( IM_DB_UPDATE_NEW_MAIL );
}

int32_t CPlayerMail::DispatchNetDatas( ProcId_t nProcId, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	switch( nProcId )
	{
	case CM_READ_MAIL:				return OnReadMail( inPacket );
	case CM_ASK_MAIL_LIST:  		return OnRequestMailList( inPacket );
	case CM_GET_FU_JIAN:			return OnGetFuJian( inPacket ); 	
	case CM_DEL_MAIL:				return OnDeleteMail( inPacket );
	case IM_DB_UPDATE_NEW_MAIL:		return OnReciveNewMail( inPacket );
	default:
		return ERR_SYETEM_ERR;
	}
}

int32_t	CPlayerMail::OnReadMail( Answer::NetPacket *inPacket )
{
	if ( NULL == m_pPlayer || NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t MailId = inPacket->readInt32();
	MailInfoMap::iterator it = m_MailInfo.find( MailId );
	if ( it == m_MailInfo.end() )
	{
		return ERR_SYETEM_ERR;
	}
	it->second.HasRead = 1;
	SendMailContent( MailId );
	return ERR_OK;
}

int32_t	CPlayerMail::OnRequestMailList( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	SendMailList();
	return ERR_OK;
}

int32_t	CPlayerMail::OnGetFuJian( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket || NULL == m_pPlayer )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t MailId = inPacket->readInt32();
	MailInfoMap::iterator it = m_MailInfo.find( MailId );
	if ( it == m_MailInfo.end() )
	{
		return ERR_SYETEM_ERR;
	}
	if ( it->second.Extract != 1 ) //û�и����򸽼�����ȡ
	{
		return ERR_SYETEM_ERR;
	}
	int32_t ItemCount = 0;
	MemChrBagVector ItemFuJian;
	std::list<int32_t> Eggs;
	for ( int32_t i = 0; i < MAIL_MAX_FU_JIAN_COUNT; ++i )
	{
		if ( it->second.Item[i].itemId <= 0 || it->second.Item[i].itemCount <= 0 )
		{
			continue;
		}
		++ItemCount;
		if ( it->second.Item[i].itemClass == IC_PET_EGG )
		{
			Eggs.push_back( it->second.Item[i].itemId );
		}
		else
		{
			ItemFuJian.push_back( it->second.Item[i] );
		}
	}

	int32_t FreeSlotCount = m_pPlayer->GetBag().GetFreeSlotCount();
	if ( FreeSlotCount < static_cast<int32_t>(ItemFuJian.size()) )
	{
		m_pPlayer->TiShiInfo(BAG_SLOT_NOT_ENOUGH);
		return ERR_SYETEM_ERR;
	}

	if ( !m_pPlayer->GetBag().AddItemsAndEggs( ItemFuJian, IACR_MAIL ) )
	{
		return ERR_SYETEM_ERR;
	}

	it->second.HasRead	 = 1;	//��Ϊ�Ѷ�
	it->second.Extract	 = 2;	//��������ȡ
	SendMailContent( MailId );
	GAME_SERVICE.replySuccess( m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), inPacket->getProc());
	return ERR_OK;
}

int32_t CPlayerMail::OnDeleteMail( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	int32_t MailId = inPacket->readInt32();
	MailInfoMap::iterator it = m_MailInfo.find( MailId );
	if ( it == m_MailInfo.end() )
	{
		return ERR_SYETEM_ERR;
	}
	m_MailInfo.erase(it);
	SendMailList();
	return ERR_OK;
}

int32_t CPlayerMail::OnReciveNewMail( Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return ERR_SYETEM_ERR;
	}
	MailInfo MaiStu = {};
	MaiStu.MailId		= inPacket->readInt32();
	MaiStu.SysMailId	= inPacket->readInt32();
	MaiStu.SenderId		= inPacket->readInt64();
	snprintf(MaiStu.SenderName, sizeof(MaiStu.SenderName)-1, inPacket->readUTF8(true).c_str());
	MaiStu.ReceiveId	= inPacket->readInt64();
	snprintf(MaiStu.ReceiveName, sizeof(MaiStu.ReceiveName)-1, inPacket->readUTF8(true).c_str());
	MaiStu.SendTime		= inPacket->readInt32();
	MaiStu.HasRead		= inPacket->readInt8();
	MaiStu.Extract		= inPacket->readInt8();
	snprintf(MaiStu.MailTitle, sizeof(MaiStu.MailTitle)-1, inPacket->readUTF8(true).c_str());
	snprintf(MaiStu.MailContent, sizeof(MaiStu.MailContent)-1, inPacket->readUTF8(true).c_str());
	MaiStu.Param		= inPacket->readUTF8(true);
	if ( MaiStu.Extract == 1 )
	{
		int8_t Count = inPacket->readInt8();
		if ( Count >= MAIL_MAX_FU_JIAN_COUNT || Count <= 0  )
		{
			return ERR_SYETEM_ERR;
		}
		for ( int32_t i = 0; i < Count; ++i )
		{
			int8_t Index = inPacket->readInt8();
			if ( Index >= MAIL_MAX_FU_JIAN_COUNT || Index < 0 )
			{
				continue;
			}
			MaiStu.Item[Index].itemId		= inPacket->readInt32();		
			MaiStu.Item[Index].itemClass	= inPacket->readInt8();	
			MaiStu.Item[Index].itemCount	= inPacket->readInt32();	
			MaiStu.Item[Index].bind			= inPacket->readInt8();		
			MaiStu.Item[Index].endTime		= inPacket->readInt32();	
			MaiStu.Item[Index].srcId		= inPacket->readInt64();		
		}
	}
	m_MailInfo[MaiStu.MailId]	= MaiStu;
	SendNewMail();
	return ERR_OK;
}

void CPlayerMail::SendMailList()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}

	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_MAIL_LIST );
	if (NULL == packet)
	{
		return;
	}
	int32_t CurTime = m_pPlayer->getNow();
	MailInfoMap::iterator it = m_MailInfo.begin();
	int32_t nSize = 0;
	packet->writeInt32( nSize );
	for ( ; it != m_MailInfo.end(); ++it )
	{
		if ( it->second.SendTime + MAIL_MAX_KEEP_TIME < CurTime )
		{
			continue;
		}
		packet->writeInt32( it->second.MailId );
		packet->writeInt32( it->second.SysMailId );
		packet->writeInt64( it->second.SenderId );
		packet->writeUTF8( it->second.SenderName );
		packet->writeInt64( it->second.ReceiveId );
		packet->writeUTF8( it->second.ReceiveName );
		packet->writeInt32( it->second.SendTime );
		packet->writeInt8( it->second.HasRead );
		packet->writeInt8( it->second.Extract );
		packet->writeUTF8( it->second.MailTitle );
		if ( it->second.Extract == 1 )
		{
			packet->writeInt32( it->second.Item[0].itemId );
			packet->writeInt8( it->second.Item[0].itemClass );
		}
		else
		{
			packet->writeInt32( 0 );
			packet->writeInt8( 0 );
		}
		nSize++;
	}
	*(int32_t*)packet->getBuffer() = nSize;
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CPlayerMail::SendMailContent( int32_t MailId )
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	MailInfoMap::iterator it = m_MailInfo.find( MailId );
	if ( it == m_MailInfo.end() )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_MAIL_CONTENT );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt32( it->second.MailId );
	packet->writeUTF8( it->second.MailContent );
	packet->writeInt8( it->second.Extract );
	if ( it->second.Extract == 1 || it->second.Extract == 2 )
	{ 
		int8_t Count = 0;
		int32_t Offset = packet->getWOffset();
		packet->writeInt8( Count );
		for ( int8_t i = 0; i < MAIL_MAX_FU_JIAN_COUNT; ++i )
		{
			if ( it->second.Item[i].itemId <= 0 || it->second.Item[i].itemCount <= 0 )
			{
				continue;
			}
			if ( IC_EQUIP == it->second.Item[i].itemClass )
			{
				MemEquip Equip = EQUIP_MANAGER.GetMemEquip( it->second.Item[i].srcId );
				if ( Equip.id > 0 )
				{
					m_pPlayer->sendEquipInfo( Equip );
				}
			}
			packet->writeInt8(i);
			packet->writeInt32( it->second.Item[i].itemId );
			packet->writeInt8( it->second.Item[i].itemClass );	
			packet->writeInt32( it->second.Item[i].itemCount );
			packet->writeInt8( it->second.Item[i].bind );	
			packet->writeInt32( it->second.Item[i].endTime );
			packet->writeInt64( it->second.Item[i].srcId );
			Count++;
		}
		*(int8_t*)( packet->getBuffer() + Offset ) =  Count;
	}
	PackParam( it->second.Param, packet );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}

void CPlayerMail::PackParam( std::string Param, Answer::NetPacket *inPacket )
{
	if ( NULL == inPacket )
	{
		return;
	}
	if ( Param.empty() )
	{
		inPacket->writeInt32( 0 );
		return;
	}
	StringVector vStr = Answer::StringUtility::split( Param, "|" );
	int32_t nSize = vStr.size();
	inPacket->writeInt32( nSize );
	StringVector::iterator it = vStr.begin();
	for ( ; it != vStr.end(); ++it  )
	{
		inPacket->writeUTF8(*it);
	}
}

void CPlayerMail::SendNewMail()
{
	if ( NULL == m_pPlayer )
	{
		return;
	}
	NetPacket *packet = GAME_SERVICE.popNetpacket( PACK_DISPATCH, SM_SEND_NEW_MAIL );
	if (NULL == packet)
	{
		return;
	}
	packet->writeInt8( 0 );
	packet->setSize(packet->getWOffset());
	GAME_SERVICE.sendPacketTo(m_pPlayer->getConnId(), m_pPlayer->getGateIndex(), packet);
}
