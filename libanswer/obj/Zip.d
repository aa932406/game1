../obj/Zip.o: Zip.cpp ../include/stdafx.h ../include/Logger.h ../include/Zip.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Zip.cpp -o ../obj/Zip.o
