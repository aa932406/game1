../obj/DayTime.o: DayTime.cpp ../include/stdafx.h ../include/DayTime.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX DayTime.cpp -o ../obj/DayTime.o
