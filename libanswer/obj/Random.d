../obj/Random.o: Random.cpp ../include/stdafx.h ../include/Random.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Random.cpp -o ../obj/Random.o
