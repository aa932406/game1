../obj/SockOpts.o: SockOpts.cpp ../include/stdafx.h ../include/Logger.h \
 ../include/SockOpts.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX SockOpts.cpp -o ../obj/SockOpts.o
