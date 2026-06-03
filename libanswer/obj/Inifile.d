../obj/Inifile.o: Inifile.cpp ../include/stdafx.h ../include/Inifile.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Inifile.cpp -o ../obj/Inifile.o
