../obj/TcpMultiplexor.o: TcpMultiplexor.cpp ../include/stdafx.h \
 ../include/DayTime.h ../include/Logger.h ../include/SockOpts.h \
 ../include/TcpConnection.h ../include/InetAddress.h \
 ../include/SafeQueue.h ../include/Mutex.h ../include/TcpMultiplexor.h \
 ../include/Thread.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX TcpMultiplexor.cpp -o ../obj/TcpMultiplexor.o
