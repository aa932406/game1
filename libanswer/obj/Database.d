../obj/Database.o: Database.cpp ../include/stdafx.h ../include/StringUtility.h \
 ../include/Database.h /usr/include/mysql/mysql.h \
 /usr/include/mysql/field_types.h /usr/include/mysql/my_list.h \
 /usr/include/mysql/mysql_com.h /usr/include/mysql/my_command.h \
 /usr/include/mysql/my_compress.h /usr/include/mysql/mysql_version.h \
 /usr/include/mysql/mysql_time.h /usr/include/mysql/errmsg.h \
 ../include/Logger.h /usr/include/mysql/errmsg.h
	x86_64-linux-gnu-g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX Database.cpp -o ../obj/Database.o
