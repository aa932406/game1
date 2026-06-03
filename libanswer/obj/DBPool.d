../obj/DBPool.o: DBPool.cpp ../include/stdafx.h ../include/Database.h \
 /usr/include/mysql/mysql.h /usr/include/mysql/mysql_version.h \
 /usr/include/mysql/mysql_com.h /usr/include/mysql/mysql_time.h \
 /usr/include/mysql/my_list.h /usr/include/mysql/typelib.h \
 /usr/include/mysql/my_alloc.h ../include/DBPool.h \
 ../include/BlockingQueue.h ../include/Condition.h ../include/Mutex.h \
 ../include/SafeQueue.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX DBPool.cpp -o ../obj/DBPool.o
