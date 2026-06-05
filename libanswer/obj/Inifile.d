../obj/Inifile.o: Inifile.cpp ../include/stdafx.h ../include/Inifile.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Inifile.cpp -o ../obj/Inifile.o
