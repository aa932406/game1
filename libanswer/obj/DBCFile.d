../obj/DBCFile.o: DBCFile.cpp ../include/stdafx.h ../include/DBCFile.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX DBCFile.cpp -o ../obj/DBCFile.o
