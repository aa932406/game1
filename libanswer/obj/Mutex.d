../obj/Mutex.o: Mutex.cpp ../include/stdafx.h ../include/Mutex.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Mutex.cpp -o ../obj/Mutex.o
