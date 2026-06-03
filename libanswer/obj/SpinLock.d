../obj/SpinLock.o: SpinLock.cpp ../include/stdafx.h ../include/SpinLock.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX SpinLock.cpp -o ../obj/SpinLock.o
