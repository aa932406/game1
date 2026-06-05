../obj/TcpServer.o: TcpServer.cpp ../include/stdafx.h ../include/NetPacket.h \
 ../include/Logger.h ../include/NetPacketPool.h ../include/SafeQueue.h \
 ../include/Mutex.h ../include/TcpAcceptor.h ../include/ObjectPool.h \
 ../include/TcpConnection.h ../include/InetAddress.h ../include/Thread.h \
 ../include/TcpServer.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX TcpServer.cpp -o ../obj/TcpServer.o
