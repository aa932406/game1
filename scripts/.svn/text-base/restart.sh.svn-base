#!/bin/sh
sh stop.sh

if [ -e ../bin/core.* ];then
	echo "core file in the bin directory, exit..."
	exit $corenum
fi

if [ "$1" = "cleanlog" ];then
    sh cleanlog.sh
fi

#sh build.sh
sh start.sh