../obj/StringUtility.o: StringUtility.cpp ../include/stdafx.h \
 ../include/StringUtility.h
	g++ -c -g -O2 -Wall -I../include -I/usr/include/mysql -DLIBANSWER_LINUX StringUtility.cpp -o ../obj/StringUtility.o
