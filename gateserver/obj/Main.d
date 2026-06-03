obj/Main.o: Main.cpp stdafx.h ../libanswer/include/libanswer.h \
 ../libanswer/include/stdafx.h ../libanswer/include/Application.h \
 ../libanswer/include/Logger.h ../libanswer/include/ArrayList.h \
 ../libanswer/include/SpinLock.h ../libanswer/include/SafeQueue.h \
 ../libanswer/include/Mutex.h ../libanswer/include/Condition.h \
 ../libanswer/include/Database.h /usr/include/mysql/mysql.h \
 /usr/include/mysql/mysql_version.h /usr/include/mysql/mysql_com.h \
 /usr/include/mysql/mysql_time.h /usr/include/mysql/my_list.h \
 /usr/include/mysql/typelib.h /usr/include/mysql/my_alloc.h \
 ../libanswer/include/DayTime.h ../libanswer/include/DBCFile.h \
 ../libanswer/include/DBPool.h ../libanswer/include/BlockingQueue.h \
 ../libanswer/include/InetAddress.h ../libanswer/include/Inifile.h \
 ../libanswer/include/MD5.h ../libanswer/include/NetPacket.h \
 ../libanswer/include/NetPacketPool.h ../libanswer/include/ObjectPool.h \
 ../libanswer/include/Random.h ../libanswer/include/RwLock.h \
 ../libanswer/include/Singleton.h ../libanswer/include/StringUtility.h \
 ../libanswer/include/TcpConnection.h ../libanswer/include/TcpServer.h \
 ../libanswer/include/TcpService.h ../libanswer/include/TcpClient.h \
 ../libanswer/include/Thread.h ../libanswer/include/Zip.h \
 ../share/Shared.h ../share/Attribute.h ../share/PDUDefine.h \
 ../share/Type.h GateLogger.h GateServer.h User.h ServiceServer.h \
 PHPServer.h
	g++ -c -g -O2 -Wall -I../share -I../libanswer/include -I/usr/include/mysql -DLIBANSWER_LINUX Main.cpp -o obj/Main.o
