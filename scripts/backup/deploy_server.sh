#!/bin/sh

PROJECT=/root/kunlun_src_trunk_server_gameserver
SVN=svn://127.0.0.1/kunlun/src/trunk/server/gameserver

svn co $SVN --username louhuang --password louhuang $PROJECT

cd $PROJECT/scripts

sh stop.sh

if [ -e ../bin/core.* ];then
	echo "core file in the bin directory, exit..."
	exit $corenum
fi

if [ "$1" = "cleanlog" ];then
    sh cleanlog.sh
fi

sh build.sh
sh start.sh

