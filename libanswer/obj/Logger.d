../obj/Logger.o: Logger.cpp ../include/stdafx.h ../include/Logger.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Logger.cpp -o ../obj/Logger.o
