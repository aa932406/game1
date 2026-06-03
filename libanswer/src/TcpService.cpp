#include "stdafx.h"

#include "TcpService.h"

using namespace Answer;

TcpService::TcpService(int recvBufferSize, int sendBufferSize, unsigned int bufferSize, unsigned int initCount, unsigned int maxCount, std::string name)
	: TcpClient(recvBufferSize, sendBufferSize, bufferSize, initCount, maxCount, name)
{

}

TcpService::~TcpService()
{

}

void TcpService::sendPacketTo(int16_t index, Answer::NetPacket *inPacket)
{
	if (inPacket != NULL)
	{
		uint32_t oldSize = inPacket->getSize();
		if (oldSize == 0)
		{
			int32_t proc = inPacket->getProc();
			LOG_ERROR("TcpService::sendPacketTo size == 0 with proc = %d\n", proc);
		}
		uint32_t needSize = sizeof(int16_t)+sizeof(int16_t);
		if (inPacket->rightShift(needSize))
		{
			inPacket->writeInt16(1);
			inPacket->writeInt16(index);
			inPacket->setSize(oldSize+needSize);
			sendPacket(inPacket);
		}
		else
		{
			NetPacket *packet = popNetpacket(sizeof(int16_t)+sizeof(int16_t)+inPacket->getSize());
			packet->writeInt16(1);
			packet->writeInt16(index);
			packet->write(inPacket->getBuffer(), inPacket->getSize());
			packet->setType(inPacket->getType());
			packet->setProc(inPacket->getProc());
			packet->setSize(packet->getWOffset());
			inPacket->destroy();
			sendPacket(packet);
		}
	}
}

int32_t TcpService::replySuccess(int16_t index, uint16_t proc, int64_t addon /* = 0 */)
{
	NetPacket *packet = popNetpacket();
	packet->writeInt16(1);
	packet->writeInt16(index);
	packet->writeUInt8(1);
	packet->writeInt64(addon);
	packet->setType(PACK_PROCREPLY);
	packet->setProc(proc);
	packet->setSize(packet->getWOffset());
	sendPacket(packet);
	return ERR_ANSWER_OK;
}

int32_t TcpService::replyfailure(int16_t index, uint16_t proc, int32_t errcode, int64_t addon/* =0 */)
{
	NetPacket *packet = popNetpacket();
	packet->writeInt16(1);
	packet->writeInt16(index);
	packet->writeUInt8(0);
	packet->writeInt32(errcode);
	packet->writeInt64(addon);
	packet->setType(PACK_PROCREPLY);
	packet->setProc(proc);
	packet->setSize(packet->getWOffset());
	sendPacket(packet);
	return errcode;
}
