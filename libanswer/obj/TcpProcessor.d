../obj/TcpProcessor.o: TcpProcessor.cpp ../include/stdafx.h ../include/Logger.h \
 ../include/NetPacket.h ../include/NetPacketPool.h ../include/SafeQueue.h \
 ../include/Mutex.h ../include/TcpAcceptor.h ../include/ObjectPool.h \
 ../include/TcpConnection.h ../include/InetAddress.h ../include/Thread.h \
 ../include/TcpProcessor.h ../include/BlockingQueue.h \
 ../include/Condition.h ../include/TcpServer.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX TcpProcessor.cpp -o ../obj/TcpProcessor.o
