#pragma once

#include "TcpClient.h"

namespace Answer
{
	class ANSWER_EXPORT_SYMBOL TcpService
		: public Answer::TcpClient
	{
	public:
		TcpService(int recvBufferSize, int sendBufferSize, unsigned int bufferSize, unsigned int initCount, unsigned int maxCount, std::string name);
		virtual ~TcpService();

	protected:
		virtual void onNetPacket(Answer::NetPacket *inPacket) = 0;

	public:
		void sendPacketTo(int16_t index, Answer::NetPacket *inPacket);
		int32_t replySuccess(int16_t index, uint16_t proc, int64_t addon = 0);
		int32_t replyfailure(int16_t index, uint16_t proc, int32_t errcode, int64_t addon = 0);
	};
}

