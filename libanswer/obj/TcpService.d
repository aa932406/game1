../obj/TcpService.o: TcpService.cpp ../include/stdafx.h ../include/TcpService.h \
 ../include/TcpClient.h ../include/InetAddress.h ../include/NetPacket.h \
 ../include/Logger.h ../include/NetPacketPool.h ../include/SafeQueue.h \
 ../include/Mutex.h ../include/Thread.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX TcpService.cpp -o ../obj/TcpService.o
