../obj/InetAddress.o: InetAddress.cpp ../include/stdafx.h \
 ../include/InetAddress.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX InetAddress.cpp -o ../obj/InetAddress.o
