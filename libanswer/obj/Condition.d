../obj/Condition.o: Condition.cpp ../include/stdafx.h ../include/Condition.h \
 ../include/Mutex.h ../include/DayTime.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Condition.cpp -o ../obj/Condition.o
