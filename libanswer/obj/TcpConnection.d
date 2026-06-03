../obj/TcpConnection.o: TcpConnection.cpp ../include/stdafx.h \
 ../include/DayTime.h ../include/Logger.h ../include/NetPacket.h \
 ../include/NetPacketPool.h ../include/SafeQueue.h ../include/Mutex.h \
 ../include/SockOpts.h ../include/TcpConnection.h \
 ../include/InetAddress.h ../include/TcpProcessor.h \
 ../include/BlockingQueue.h ../include/Condition.h ../include/Thread.h \
 ../include/Zip.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX TcpConnection.cpp -o ../obj/TcpConnection.o
