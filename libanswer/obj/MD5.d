../obj/MD5.o: MD5.cpp ../include/stdafx.h ../include/MD5.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX MD5.cpp -o ../obj/MD5.o
