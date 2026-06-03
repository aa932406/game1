#!/bin/sh

cd ../bin

nohup ./dbserver &
sleep 2
nohup ./gateserver &
sleep 2
nohup ./globalserver &
sleep 2
nohup ./gameserver 1 &
sleep 2
