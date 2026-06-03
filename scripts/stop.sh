#!/bin/sh

function stop()
{
	pgrep $1 | xargs kill -35
	
	while true
	do
		num=$(pgrep $1 | wc -l)
		if [ "$num" -lt "1" ]
		then
			break
		fi
		sleep 1
	done
}

stop gateserver
stop gameserver
stop globalserver
stop dbserver
