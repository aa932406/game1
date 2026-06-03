#!/bin/sh

function kill()
{
	pgrep $1 | xargs kill -9
	
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

kill gamebwserver
kill globalbwserver
kill gatebwserver
kill dbbwserver

