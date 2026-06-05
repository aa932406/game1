../obj/TcpClient.o: TcpClient.cpp ../include/stdafx.h ../include/Logger.h \
 ../include/SockOpts.h ../include/TcpClient.h ../include/InetAddress.h \
 ../include/NetPacket.h ../include/NetPacketPool.h ../include/SafeQueue.h \
 ../include/Mutex.h ../include/Thread.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX TcpClient.cpp -o ../obj/TcpClient.o
