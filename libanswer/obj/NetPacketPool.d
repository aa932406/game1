../obj/NetPacketPool.o: NetPacketPool.cpp ../include/stdafx.h \
 ../include/NetPacket.h ../include/Logger.h ../include/NetPacketPool.h \
 ../include/SafeQueue.h ../include/Mutex.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX NetPacketPool.cpp -o ../obj/NetPacketPool.o
