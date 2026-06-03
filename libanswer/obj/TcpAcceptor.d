../obj/TcpAcceptor.o: TcpAcceptor.cpp ../include/stdafx.h ../include/Logger.h \
 ../include/InetAddress.h ../include/SockOpts.h ../include/TcpAcceptor.h \
 ../include/ObjectPool.h ../include/Mutex.h ../include/SafeQueue.h \
 ../include/TcpConnection.h ../include/Thread.h \
 ../include/TcpMultiplexor.h ../include/TcpProcessor.h \
 ../include/BlockingQueue.h ../include/Condition.h \
 ../include/NetPacketPool.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX TcpAcceptor.cpp -o ../obj/TcpAcceptor.o
