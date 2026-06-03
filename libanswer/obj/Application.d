../obj/Application.o: Application.cpp ../include/stdafx.h \
 ../include/Application.h ../include/Logger.h ../include/DayTime.h \
 ../include/Mutex.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Application.cpp -o ../obj/Application.o
