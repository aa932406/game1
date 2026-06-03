../obj/Thread.o: Thread.cpp ../include/stdafx.h ../include/Thread.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Thread.cpp -o ../obj/Thread.o
