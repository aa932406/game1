../obj/RwLock.o: RwLock.cpp ../include/stdafx.h ../include/RwLock.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX RwLock.cpp -o ../obj/RwLock.o
