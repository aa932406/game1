../obj/DBCFile.o: DBCFile.cpp ../include/stdafx.h ../include/DBCFile.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX DBCFile.cpp -o ../obj/DBCFile.o
